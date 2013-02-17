/*==================================================================================================

    Module Name:  usb_hwinterface_layer.c

    General Description: This file contains all API's and functions of USB IP Layer .

====================================================================================================
    Copyright (C) 2006,2007,2008 Freescale Semiconductor, Inc. All Rights Reserved
    THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
    BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
    Freescale Semiconductor, Inc.


Revision History:
                            Modification     Tracking
Author                          Date          Number     Description of Changes
-------------------------   ------------    ----------   -------------------------------------------
Siva Pothireddy              22-Jul-2008    ENGcm06721   Reset check in the USB enumeration flow needs to be changed
Siva Pothireddy              07-Jul-2008    ENGcm06427   Warnings Fixed.
Siva Pothireddy               06/05/2008     ENGcm05551   Setting of PFSC,Mode select has to be done
                                                         before R/S bit getting set
Prabhat Singh                  08/oct/2007      engcm00737    Detecting usb reset
Mahima Verma                 11/Sep/2007    TLSbo96294   Configure the USB to work in BURSTSIZE=UNSPECIFIED.
Mahima Verma                 13/Sep/2007    TLSbo96384   USB Enumeration fails for Device address set above 63.
Mahima Verma                 20/Aug/2007    TLSbo95872   Endianess change .
Mahima Verma                 19/Jul/2007    TLSbo94597   Changes in USB to support simulator testing.
Mahima Verma                 11/Jun/2007    TLSbo93857   Porting to Marley.
Suresh Kumar                 18/Oct/2006    TLSbo80774   Ported to Zappa.
Bharat Bhushan               24-Aug-2006    TLSbo76463   Porting to SKYE+ .
Bharat Bhushan               08/04/2006     TLSbo74988   Changes for handling setup commands after enumeration.
Bharat Bhushan               04/08/2006     TLSbo74877   Maximum Packet Size changed from 0x08 to 0x40 for EP0
Bharat Bhushan               05/10/2006     TLSbo68884   Initial Version ( USB Layer Architecture).


-------------------------   ------------    ----------   -------------------------------------------
Portability: Portable.


====================================================================================================
                                        INCLUDE FILES
==================================================================================================*/

#include "su_basictypes.h"
#include <usb_common.h>
#include <usb_hwinterface_layer.h>
#include <usb_ipl_tl_extern.h>
#include <usb_ipl_al_extern.h>
#include "bl_transreceiver.h"
#include <string.h>
/*==================================================================================================
                                     GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                     LOCAL CONSTANTS
==================================================================================================*/

/*=================================================================================================
                                 LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

static void ipl_clear_dqh(void);
static void ipl_setup_qhead(struct dqh_t* );
static void ipl_setup_transfer_desc(struct dtd_t* );
static void ipl_device_only_mode(void);
static U32  ipl_get_dqh(U8, U8);
static U32 ipl_get_dtd(U8, U8 ) ;
static U32 get_rxd_buffer(void);
static void free_buffer(U32 );
static U32 alloc_buffer(void);
static void ipl_init_hw(void);

/*==================================================================================================
                                      LOCAL VARIABLES
==================================================================================================*/
static U32 g_buffer_address_base; /* Base address of the buffer allocated to IP Layer */
static U32 g_buffer_length;	/* length of the buffer */

static buffer_map_t g_buffer_map; /* Buffer information used for data transfer */

static U8  g_in_endpoint;         /* Number of Endpoint configured as IN */
static U8  g_out_endpoint;        /* Number of Endpoint configured as OUT*/
static U8  g_max_ep_supported;   /* Number of Endpoints configured in system */

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
                                     LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================

FUNCTION: ipl_init_hw

DESCRIPTION:
   	This Function Initialise the USB Core .

ARGUMENTS PASSED:
	None

RETURN VALUE:
	None

IMPORTANT NOTES:
	None

==================================================================================================*/
void ipl_init_hw(void)
{
    struct dqh_t qhead;
    U32 total_bytes;

    /* Init to Device mode only */
    ipl_device_only_mode();

    /* Clear the dQH before initialized */
    ipl_clear_dqh();

    /******************************************************************************
    / =================
    / dQH0 for EP0OUT
    / =================
    / Initialize device queue heads in system memory
    / 8 bytes for the 1st setup packet */

    total_bytes 	= 0x8;
    qhead.dqh_base 	= ipl_get_dqh(EP0,OUT);
    qhead.zlt 		= ZLT_DISABLE;
    qhead.mps 		= MPS_64;
    qhead.ios 		= IOS_SET;
    qhead.next_link_ptr = ipl_get_dtd(EP0,OUT);
    qhead.terminate 	= NOT_TERMINATE;
    qhead.total_bytes  	= total_bytes;
    qhead.ioc 		= IOC_SET;
    qhead.status 	= NO_STATUS;
    qhead.buffer_ptr0  	= 0;
    qhead.current_offset = 0;
    qhead.buffer_ptr1  	= 0;
    qhead.buffer_ptr2 	= 0;
    qhead.buffer_ptr3  	= 0;
    qhead.buffer_ptr4 	= 0;

    /* Set Device Queue Head */
    ipl_setup_qhead(&qhead);

    /* ==================
    END of dQH0 setup
    ====================*/

    /*=================
    dQH1 for EP0IN
    ================= */

    total_bytes 	= 0x8;
    qhead.dqh_base 	= ipl_get_dqh(EP0,IN);
    qhead.zlt 		= ZLT_DISABLE;
    qhead.mps 		= MPS_64;
    qhead.ios 		= IOS_SET;
    qhead.next_link_ptr = ipl_get_dtd(EP0,IN);
    qhead.terminate 	= TERMINATE;
    qhead.total_bytes  	= total_bytes;
    qhead.ioc 		= IOC_SET;
    qhead.status 	= NO_STATUS;
    qhead.buffer_ptr0  	= g_buffer_map.ep0_buffer_addrs;
    qhead.current_offset = (g_buffer_map.ep0_buffer_addrs & 0xFFF);
    qhead.buffer_ptr1  	= 0;
    qhead.buffer_ptr2 	= 0;
    qhead.buffer_ptr3  	= 0;
    qhead.buffer_ptr4 	= 0;

    /* Set Device Queue Head */
    ipl_setup_qhead(&qhead);

    /* ==================
    /  END of dQH1 setup
    /  ================*/

    /* Configure ENDPOINTLISTADDR Pointer */
    *(VP_U32)USB_OTG_ENDPOINTLISTADDR = g_buffer_map.ep_dqh_base_addrs;

    /* Set OTG termination, controls the pulldown on DM */
    *(VP_U32)USB_OTG_OTGSC |= BIT3;

    /* Disable Setup Lockout by writing '1' to SLOM in USBMODE */
    *(VP_U32)USB_OTG_USBMODE |= BIT3;

    /* Set Run/Stop bit to Run Mode */
    *(VP_U32)USB_OTG_USBCMD |= BIT0;
}

/*==================================================================================================

FUNCTION: ipl_init

DESCRIPTION:
   	This function does the IP Layer Initialisation

ARGUMENTS PASSED:
 	usb_plat_config_data_t* config_data_ptr

RETURN VALUE:
	None

IMPORTANT NOTES:
	        There are two buffers each of size 0x200 ( 512 ) will be used for bulk data
       	transfer. So total 0x400(1k) will be used for bulk data transfer and this will be the
	last 1k of the allocated buffer.
       	There is 0x40 ( 64 ) size of the buffer will be used for data transfer over control
	endpoint ( EP0 )
	Rest of the buffer area will be used for endpoint data  structires ( device qhead and
	device transfer descriptor ).
==================================================================================================*/
void
ipl_init(usb_plat_config_data_t* config_data_ptr)
{
    U32 temp;

    /* Base address of the buffer allocated to IP Layer */
    g_buffer_address_base =  config_data_ptr->buffer_address;

    /* length of the buffer */
    g_buffer_length = config_data_ptr->buffer_size;

    /* Maximum Number of EPs to be confiured */
    g_max_ep_supported = (( g_buffer_length - TOTAL_DATA_BUFFER_SIZE)/(BUFFER_USED_PER_EP));

    /* Base of queue Head Pointer */
    g_buffer_map.ep_dqh_base_addrs = g_buffer_address_base;

    /* Total size of qhead */
    temp = (SIZE_OF_QHD * (g_max_ep_supported * 2));

    /* Base Address of device transfer descriptor */
    g_buffer_map.ep_dtd_base_addrs = (g_buffer_map.ep_dqh_base_addrs + temp);

    /* Total size of transfer descriptor */
    temp =  ((dTD_SIZE_EPIN * g_max_ep_supported) + (dTD_SIZE_EPOUT * g_max_ep_supported ));

    /* Base Address of EP0 Buffer */
    g_buffer_map.ep0_buffer_addrs = (g_buffer_map.ep_dtd_base_addrs + temp  );

    /* transfer buffer 1 */
    g_buffer_map.buffer1_address=(g_buffer_address_base + g_buffer_length -(BULK_BUFFER_SIZE*NUM_OF_BULK_BUFFER));
    g_buffer_map.buffer1_status = BUFFER_FREE;

    /* transfer buffer 2 */
    g_buffer_map.buffer2_address = g_buffer_map.buffer1_address + BULK_BUFFER_SIZE;
    g_buffer_map.buffer2_status = BUFFER_FREE;

    ipl_init_hw();
}

/*==================================================================================================

FUNCTION: ipl_check_usb_device_reset

DESCRIPTION:
   	This function check if reset event is received on USB bus.

ARGUMENTS PASSED:
	None

RETURN VALUE:
	BOOL 	status 	TRUE	If reset received.
			FALSE	If reset not received.

IMPORTANT NOTES:
	None

==================================================================================================*/
BOOL
ipl_check_usb_device_reset(void)
{
    BOOL status=FALSE;
	/*Check for Reset*/
    if ((*(VP_U32)USB_OTG_USBSTS) & BIT6)
    {
	status=TRUE;
    }
return status;
}

/*==================================================================================================*/

/*==================================================================================================

FUNCTION: ipl_check_bus_reset

DESCRIPTION:
   	This function check if reset event is received on USB bus.

ARGUMENTS PASSED:
	None

RETURN VALUE:
	BOOL 	status 	TRUE	If reset received.
			FALSE	If reset not received.

IMPORTANT NOTES:
	None

==================================================================================================*/
BOOL
ipl_check_bus_reset(void)
{
    BOOL status=FALSE;
    if ((*(VP_U32)USB_OTG_USBSTS) & BIT6)
    {
	status=TRUE;
    }
return status;
}
/*==================================================================================================

FUNCTION:  ipl_check_setup_token

DESCRIPTION:
	This function check if Setup Token is received on USB bus.

ARGUMENTS PASSED:
	None

RETURN VALUE:
	U8 	status 	TRUE	If Setup Token received.
			FALSE	If Setup Token not received.

IMPORTANT NOTES:
	None

==================================================================================================*/
BOOL
ipl_check_setup_token(void)
{
    BOOL status =  FALSE;
    if ((*(VP_U32)USB_OTG_ENDPTSETUPSTAT) & BIT0)
    {
        status= TRUE;
    }
return status;
}
/*==================================================================================================

FUNCTION: ipl_is_interface_high_speed

DESCRIPTION: 
	This function return the speed at which the selected interface working.

ARGUMENTS PASSED:
	None
  
RETURN VALUE:
	U8 	interface_speed 	0	If interface is working at FS. 
	 	 			1	If interface is working at HS.
	
IMPORTANT NOTES:
	Note : Low Speed is not supported.

==================================================================================================*/
BOOL
ipl_is_interface_high_speed(void)
{
    BOOL speed = FALSE; /* Full Speed by default */

#ifndef SIMULATOR_TESTING
    while(!((*(VP_U32)USB_OTG_USBSTS) & 4 ));
#endif

    if(((*(VP_U32)USB_OTG_PORTSC1) & USB_OTG_INF_SPEED_MASK) == USB_OTG_INF_SPEED_HS)
    {
        speed = TRUE;
    }
return speed;
}
/*==================================================================================================

FUNCTION: ipl_handle_bus_reset

DESCRIPTION:
   	This function Handle the reset event from USB Host

ARGUMENTS PASSED:
	None

RETURN VALUE:
	None

IMPORTANT NOTES:
	None

==================================================================================================*/
void
ipl_handle_bus_reset(void)
{
    U32 temp,total_bytes;
    struct dqh_t qhead;

    *(VP_U32)USB_OTG_USBCMD &= ~BIT0;
    (*(VP_U32)USB_OTG_USBSTS) &= BIT6;

    /*Reading and writing back the ENDPTSETUPSTAT register
      clears the setup token semaphores */
    temp = (*(VP_U32)USB_OTG_ENDPTSETUPSTAT);
    (*(VP_U32)USB_OTG_ENDPTSETUPSTAT) = temp;

    /*Reading and writing back the ENDPTCOMPLETE register
      clears the endpoint complete status bits */
    temp = (*(VP_U32)USB_OTG_ENDPTCOMPLETE);
    (*(VP_U32)USB_OTG_ENDPTCOMPLETE) = temp;

    while((*(VP_U32)USB_OTG_ENDPTPRIME));

    (*(VP_U32)USB_OTG_ENDPTFLUSH) = 0xFFFFFFFF;

    ipl_clear_dqh();

    /* Initialize device queue heads in system memory for EP0OUT */
    total_bytes = 0x8;

    qhead.dqh_base	= ipl_get_dqh(EP0,OUT);
    qhead.zlt		= ZLT_DISABLE;
    qhead.mps		= MPS_64;
    qhead.ios		= IOS_SET;
    qhead.next_link_ptr	= 0;
    qhead.terminate 	= TERMINATE;
    qhead.total_bytes	= total_bytes;
    qhead.ioc		= IOC_SET;
    qhead.status 	= NO_STATUS;
    qhead.buffer_ptr0	= 0;
    qhead.current_offset = 0;
    qhead.buffer_ptr1	= 0;
    qhead.buffer_ptr2	= 0;
    qhead.buffer_ptr3	= 0;
    qhead.buffer_ptr4	= 0;

    ipl_setup_qhead(&qhead);

    /* Initialize device queue heads in system memory for EP0IN */
    qhead.dqh_base 	= ipl_get_dqh(EP0,IN);
    qhead.zlt 		= ZLT_DISABLE;
    qhead.mps 		= MPS_64;
    qhead.ios 		= IOS_SET;
    qhead.next_link_ptr  	= 0;
    qhead.terminate 	= TERMINATE;
    qhead.total_bytes  	= 0;
    qhead.ioc 		= IOC_SET;
    qhead.status 	= NO_STATUS;
    qhead.buffer_ptr0  	= 0;
    qhead.current_offset = 0;
    qhead.buffer_ptr1  	= 0;
    qhead.buffer_ptr2 	= 0;
    qhead.buffer_ptr3  	= 0;
    qhead.buffer_ptr4      = 0;

    ipl_setup_qhead(&qhead);

    *(VP_U32)USB_OTG_ENDPOINTLISTADDR = g_buffer_map.ep_dqh_base_addrs;

    *(VP_U32)USB_OTG_USBCMD |= BIT0;


}
/*==================================================================================================

FUNCTION: ipl_set_device_address

DESCRIPTION:
   	This function set the Device Address

ARGUMENTS PASSED:
	U8 Address	: Address of Device to be Set.

RETURN VALUE:
	None

IMPORTANT NOTES:
	None

==================================================================================================*/
void
ipl_set_device_address(U16 Address)
{
    /* set the USB Device address */
    *(VP_U32)USB_OTG_DEVICEADDR = ((U32)Address & 0x7F) << 25;
}



/*==================================================================================================

FUNCTION: ipl_send_stall_handshake

DESCRIPTION:
   	This function Send/Receive the STALL HANDSHAKE to  USB Host

ARGUMENTS PASSED:
	U8 endpoint  -	Endpoint Number .
	U8 direction -	IN/OUT :  direction of EndPoint.

RETURN VALUE:
	None

IMPORTANT NOTES:
	None

==================================================================================================*/
void
ipl_send_stall_handshake(U8 endpoint , U8 direction)
{
    if( direction == OUT )
    {
    *(VP_U32)( USB_OTG_ENDPTCTRL0 + (4*endpoint) ) |= STALL_RX;
    }
    else
    {
    *(VP_U32)( USB_OTG_ENDPTCTRL0 + (4*endpoint) ) |= STALL_TX;
    }
}
/*==================================================================================================

FUNCTION: ipl_set_configuration

DESCRIPTION:
   	This function Handle the SET CONFIGRATION Request.

ARGUMENTS PASSED:
 	 usb_end_pt_info_t* config_data;

RETURN VALUE:
	None

IMPORTANT NOTES:
	None

==================================================================================================*/
void
ipl_set_configuration(usb_end_pt_info_t* config_data)
{
    struct dtd_t td;
    U32 total_bytes = 0x0;
    U32 buffer_addrs_page0 = 0;
    U32 dqh_address = 0;
    U32 dtd_address = 0;
    U8  endpt_num,direction;

    struct dqh_t qhead;

    /* get endpoint number to be configured and its direction */
    endpt_num= config_data->end_pt_no;
    direction= config_data->direction;

    /* Check if the endpoint number and direction is withing the permitted range or not */
    if (( endpt_num != EP0 ) && (endpt_num <= ( g_max_ep_supported - 1)) &&
		    ( direction == OUT || direction == IN))
    {
	/* get the device q head and deice TD */
	dqh_address = ipl_get_dqh(endpt_num,direction);
        dtd_address = ipl_get_dtd(endpt_num,direction);

        if ( direction ==  OUT )
	    {
                total_bytes = BULK_BUFFER_SIZE ;

		qhead.dqh_base		= dqh_address;
		qhead.zlt 		= ZLT_DISABLE;
		qhead.mps 		= config_data->max_pkt_size;
		qhead.ios 		= IOS_SET;
		qhead.next_link_ptr 	= dtd_address ;
	        qhead.terminate 	= TERMINATE;
		qhead.total_bytes	= total_bytes;
		qhead.ioc 		= IOC_SET;
		qhead.status 		= NO_STATUS;
		qhead.buffer_ptr0	= 0;
		qhead.current_offset	= 0;
		qhead.buffer_ptr1	= 0;
		qhead.buffer_ptr2 	= 0;
		qhead.buffer_ptr3	= 0;
		qhead.buffer_ptr4 	= 0;

		ipl_setup_qhead(&qhead);

		/* Endpoint 1 : MPS = 64, OUT (Rx endpoint) */
		*(VP_U32)(USB_OTG_ENDPTCTRL0 + (0x4*endpt_num))= 0x00080048;

		/* Enable EP1 OUT */
		*(VP_U32)(USB_OTG_ENDPTCTRL0 + ( 0x4 * endpt_num)) |= EPOUT_ENABLE;

	        /* allocate buffer for receiving data */
	       	buffer_addrs_page0 = alloc_buffer();

		/* OUT setup dTD */
		td.dtd_base 		= dtd_address;
		td.next_link_ptr  	= dtd_address + 0x20;
		td.terminate 		= TERMINATE;
		td.total_bytes  	= total_bytes;
	       	td.ioc 			= IOC_SET;
	       	td.status 		= ACTIVE;
	       	td.buffer_ptr0  	= buffer_addrs_page0;
	       	td.current_offset 	= (buffer_addrs_page0 & 0xFFF);
	       	td.buffer_ptr1  	= 0x0;
		td.buffer_ptr2 		= 0x0;
	       	td.buffer_ptr3  	= 0x0;
		td.buffer_ptr4  	= 0x0;

		/* Set the Transfer Descriptor	*/
		ipl_setup_transfer_desc(&td);

		/* 1. write dQH next ptr and dQH terminate bit to 0 */
		*(VP_U32)(dqh_address+0x8)= dtd_address;

		/* 2. clear active & halt bit in dQH */
		*(VP_U32)(dqh_address+0xC) &= ~0xFF;

		/* 3. prime endpoint by writing '1' in ENDPTPRIME */
		*(VP_U32)USB_OTG_ENDPTPRIME |= (  EPOUT_PRIME << endpt_num );

		/* Endpoint Configured for output */
		g_out_endpoint= endpt_num;
	    }
	else
	    {
                total_bytes = 0x4 ;

		qhead.dqh_base		= ipl_get_dqh(endpt_num,direction);
		qhead.zlt 		= ZLT_DISABLE;
		qhead.mps 		= config_data->max_pkt_size;
		qhead.ios 		= IOS_SET;
		qhead.next_link_ptr 	= ipl_get_dtd(endpt_num,direction);
	        qhead.terminate 	= TERMINATE;
		qhead.total_bytes	= total_bytes;
		qhead.ioc 		= IOC_SET;
		qhead.status 		= NO_STATUS;
		qhead.buffer_ptr0	= 0;
		qhead.current_offset	= 0;
		qhead.buffer_ptr1	= 0;
		qhead.buffer_ptr2 	= 0;
		qhead.buffer_ptr3	= 0;
		qhead.buffer_ptr4 	= 0;

		ipl_setup_qhead(&qhead);

		/* Endpoint Configured for Input */
	    	g_in_endpoint= endpt_num;

		/* Endpoint 2: MPS = 64, IN (Tx endpoint) */
	     	*(VP_U32)(USB_OTG_ENDPTCTRL0 + (0x4*endpt_num)) = 0x00480008;

		/* Enable EP2 IN */
		*(VP_U32)(USB_OTG_ENDPTCTRL0 + (0x4*endpt_num)) |= EPIN_ENABLE;

		/* 3. prime endpoint by writing '1' in ENDPTPRIME */
           #ifndef SIMULATOR_TESTING
        	*(VP_U32)USB_OTG_ENDPTPRIME |= (EPIN_PRIME << g_in_endpoint);
           #endif
	    }
    }
    else
    {
        /* error handling TBD */
    }

}

/*==================================================================================================

FUNCTION: ipl_send_data

DESCRIPTION:
   	This function Send Data on the USB channel.
ARGUMENTS PASSED:
 	 U8 endptno			: Endpoint number on which data it to be send.
	 usb_buffer_descriptor_t *bd 	: This is the pointer to the buffer descriptor.
	 BOOL zlt			: Boolean to decide whether Zero Length Packet is to
					  be send or not
RETURN VALUE:
	USB_SUCCESS - The buffer was successfully processed by the USB device and data sent to the Host.
	USB_FAILURE - Some failure occurred in transmitting the data.

IMPORTANT NOTES:
	None

==================================================================================================*/
usb_status_t
ipl_send_data(U8 endptno , usb_buffer_descriptor_t* bd,BOOL zlt)
{
    struct dtd_t td;
    U32 total_bytes ;
    U32 dtd_address,dqh_address;
    U32 buffer_addrs_page0;
    U8* buffer_src_ptr = 0x0;
    U32* buffer_dest_ptr = 0x0;
    U32 size = 0x0;
    usb_status_t status = USB_SUCCESS;

    /* varify Endpoint Number and address */
    if((endptno == EP0) ||(( endptno == g_in_endpoint) && ( bd->buffer != NULL)))
    {
        /* Get Device Transfer Descriptor of the requested endpoint */
        dtd_address = ipl_get_dtd(endptno,IN);

        /* Get Device Queue head of the requested endpoint */
        dqh_address = ipl_get_dqh(endptno,IN);

        /* Get Total Bytes to Be recieved */
        total_bytes = bd->size;

        switch(endptno)
        {
            case EP0 :
	        td.dtd_base 		= dtd_address;
		td.next_link_ptr  	= 0;
		td.terminate 		= TERMINATE;
		td.total_bytes  	= total_bytes;
		td.ioc 			= IOC_SET;
		td.status 		= ACTIVE;
		td.buffer_ptr0  	= g_buffer_map.ep0_buffer_addrs;
		td.current_offset 	= (g_buffer_map.ep0_buffer_addrs & 0xFFF);
		td.buffer_ptr1  	= 0;
		td.buffer_ptr2 		= 0;
		td.buffer_ptr3  	= 0;
		td.buffer_ptr4  	= 0;

		/* Set the transfer descriptor */
		ipl_setup_transfer_desc(&td);

	       	/* Enable ZLT when data size is in multiple of Maximum Packet Size  */
		if(zlt)
	       	{
                    /* set ZLT enable */
		    (*(VP_U32)(dqh_address)) &= ~0x20000000;
	       	}

		/* 1. write dQH next ptr and dQH terminate bit to 0  */
		*(VP_U32)(dqh_address+0x8)= (dtd_address);

		/* 2. clear active & halt bit in dQH */
	       	*(VP_U32)(dqh_address+0xC) &= ~0xFF;

	       	/* 3. prime endpoint by writing '1' in ENDPTPRIME */
		*(VP_U32)USB_OTG_ENDPTPRIME |= BIT16;

		/* wait for complete set and clear */
		while (!((*(VP_U32)USB_OTG_ENDPTCOMPLETE) & EPIN_COMPLETE));

		*(VP_U32)USB_OTG_ENDPTCOMPLETE = EPIN_COMPLETE;

		status = USB_SUCCESS;

                break;

	    default :

		/* allocate memory for data transfer */
	       	buffer_addrs_page0 = alloc_buffer();
	       	buffer_dest_ptr = (U32 *)buffer_addrs_page0 ;

		/* Get the source data pointer */
		buffer_src_ptr =(U8 *) bd->buffer;

	       	if(buffer_addrs_page0 != (U32)NULL)
	       	{
		    while(total_bytes)
		    {
                        if(total_bytes < BULK_BUFFER_SIZE )
		        {
		            size = total_bytes;
		        }
		        else
		        {
		            size = BULK_BUFFER_SIZE;
		        }

			/* copy the data to the allocated buffer */
    			//copy_to_buffer(buffer_src_ptr,buffer_dest_ptr,size);
			memcpy(buffer_dest_ptr, buffer_src_ptr, size);
    			td.dtd_base 		= dtd_address;
    			td.next_link_ptr  	= dtd_address + 0x20 ;
		    	td.terminate 		= TERMINATE;
			td.total_bytes  	= total_bytes;
			td.ioc 			= IOC_SET;
    			td.status 		= ACTIVE;
    			td.buffer_ptr0  	= buffer_addrs_page0;
    			td.current_offset 	= (buffer_addrs_page0 & 0xFFF);
    			td.buffer_ptr1  	= 0;
    			td.buffer_ptr2 		= 0;
    			td.buffer_ptr3  	= 0;
    			td.buffer_ptr4  	= 0;

    			/* Set the Transfer Descriptor  */
    			ipl_setup_transfer_desc(&td);

    			/* 1. write dQH next ptr and dQH terminate bit to 0  */
    			*(VP_U32)(dqh_address+0x8)= (dtd_address);

    			/* 2. clear active & halt bit in dQH */
    			*(VP_U32)(dqh_address+0xC) &= ~0xFF;

    			/* 3. prime endpoint by writing '1' in ENDPTPRIME */
    			*(VP_U32)USB_OTG_ENDPTPRIME = ( EPIN_PRIME << endptno);

    			/* wait for complete set and clear */
    			while (!((*(VP_U32)USB_OTG_ENDPTCOMPLETE) & (EPIN_COMPLETE<<endptno)));

    			*(VP_U32)USB_OTG_ENDPTCOMPLETE = ( EPIN_COMPLETE << endptno);

    			total_bytes -= size;

    			buffer_src_ptr += size;
	    	    }

	    	    /* Free the allocated buffer as transmitt is complete */
	    	    free_buffer(buffer_addrs_page0);

	    	    status = USB_SUCCESS;
		}
		else
		{
			/* Return Error - TBD */
		}
	}
    }
    else
    {
        status = USB_INVALID ;
    }
    return status;
}

/*==================================================================================================

FUNCTION: ipl_receive_data

DESCRIPTION:
   	This function Handle the Status Token (IN/OUT) from USB Host

ARGUMENTS PASSED:
 	 U8 endptno			: Endpoint number on which data it to be send.
	 usb_buffer_descriptor_t *bd 	: This is the pointer to the buffer descriptor.

RETURN VALUE:
	USB_SUCCESS - 	: The buffer was successfully processed by the USB device and
			  data is received from the host.
	USB_FAILURE - 	: Some failure occurred in receiving the data.
	USB_INVALID -   : If the endpoint is invalid.

IMPORTANT NOTES:
	None

==================================================================================================*/
usb_status_t
ipl_receive_data(U8 endptno, usb_buffer_descriptor_t* bd)
{
    struct dtd_t td;
    usb_status_t status = USB_FAILURE;
    U32 total_bytes;
    U32 dtd_address;
    U32 dqh_address;
    U32 received_buffer_addrs = 0x0;
    U32* buffer_ptr = 0x0;
    U32 received_data_length = 0x0;
    U32 data_size = 0x0;
    U8* destination_ptr = 0x0;
    U32* temp = 0x0;

    U32 buffer_addrs_page0;

    /* varify Endpoint Number and address */
    if((endptno == EP0) ||(( endptno == g_out_endpoint) && ( bd->buffer != NULL)))
    {
        /* Get Device Device Queue Head of the requested endpoint */
        dqh_address = ipl_get_dqh(endptno,OUT);

	/* Get Device Transfer Descriptor of the requested endpoint */
        dtd_address = ipl_get_dtd(endptno,OUT);

        switch (endptno)
        {
	    case EP0 :

		/* Get the total bytes to be received	*/
		total_bytes = bd->size;

	        td.dtd_base		= dtd_address;
	    	td.next_link_ptr	= dtd_address + 0x20;
	       	td.terminate 		= TERMINATE;
	      	td.total_bytes		= total_bytes;
	       	td.ioc			= IOC_SET;
	       	td.status		= ACTIVE;
	       	td.buffer_ptr0		= g_buffer_map.ep0_buffer_addrs;
	       	td.current_offset	= (g_buffer_map.ep0_buffer_addrs & 0xFFF);
	       	td.buffer_ptr1		= 0;
	       	td.buffer_ptr2		= 0;
	       	td.buffer_ptr3		= 0;
	       	td.buffer_ptr4		= 0;

		/* Set the Transfer Descriptor	*/
		ipl_setup_transfer_desc(&td);

		/* 1. write dQH next ptr and dQH terminate bit to 0 */
		*(VP_U32)(dqh_address+0x8)= dtd_address;

		/* 2. clear active & halt bit in dQH */
		*(VP_U32)(dqh_address+0xC) &= ~0xFF;

		/* 3. prime endpoint by writing '1' in ENDPTPRIME */
		*(VP_U32)USB_OTG_ENDPTPRIME |= (  EPOUT_PRIME << endptno );

#ifndef SIMULATOR_TESTING
		/* 4. Wait for the Complete Status */
 		while (!((*(VP_U32)USB_OTG_ENDPTCOMPLETE) & ( EPOUT_COMPLETE << endptno)));

		/*clear the complete status */
		(*(VP_U32)USB_OTG_ENDPTCOMPLETE) = (EPOUT_COMPLETE << endptno);
#endif

		status = USB_SUCCESS;
		break;

	    default :

                if ((*(VP_U32)USB_OTG_ENDPTCOMPLETE) & ( EPOUT_COMPLETE << endptno))
                {
		    /*clear the complete status */
		    (*(VP_U32)USB_OTG_ENDPTCOMPLETE) = (EPOUT_COMPLETE << endptno);


	            /* get the address of the buffer in which data is received */
		    received_buffer_addrs = get_rxd_buffer();

		    if( received_buffer_addrs == (U32)NULL)
		    {
                        status = USB_INVALID;
		        break;
		    }
		    buffer_ptr = (U32 *)received_buffer_addrs;

		    /* calculate the received data length using number of bytes left in TD */
		    temp =  (U32 *)dtd_address;
		    temp++; /* pointer to total bytes in dtd */
		    received_data_length = (BULK_BUFFER_SIZE - (((*temp) >> 16 )&0x7FFF));

		    /* get the dTD buffer pointer */
	            buffer_addrs_page0 = alloc_buffer();

		    if( buffer_addrs_page0 == (U32)NULL)
		    {
                        status = USB_INVALID;
		        break;
		    }
       	            /* Get the total bytes to be received	*/
		    total_bytes = BULK_BUFFER_SIZE;

                    /* OUT setup dTD */
		    td.dtd_base 		= dtd_address;
		    td.next_link_ptr  	= dtd_address + 0x20;
		    td.terminate 		= TERMINATE;
		    td.total_bytes  	= total_bytes;
	       	    td.ioc 			= IOC_SET;
	       	    td.status 		= ACTIVE;
	       	    td.buffer_ptr0  	= buffer_addrs_page0;
	       	    td.current_offset 	= ( buffer_addrs_page0 & 0xFFF );
	       	    td.buffer_ptr1  	= 0x0;
		    td.buffer_ptr2 		= 0x0;
	       	    td.buffer_ptr3  	= 0x0;
		    td.buffer_ptr4  	= 0x0;

		    /* Set the Transfer Descriptor	*/
		    ipl_setup_transfer_desc(&td);

		    /* 1. write dQH next ptr and dQH terminate bit to 0 */
		    *(VP_U32)(dqh_address+0x8)= dtd_address;

	    	    /* 2. clear active & halt bit in dQH */
		    *(VP_U32)(dqh_address+0xC) &= ~0xFF;

    
		    /* 3. prime endpoint by writing '1' in ENDPTPRIME */
		    *(VP_U32)USB_OTG_ENDPTPRIME |= (  EPOUT_PRIME << endptno );


		    /* Copy the data from buffer to destionation pointed by buffer descriptor */
		    destination_ptr = ( U8 *)( bd->buffer);

                    if(received_data_length < bd->size)
		    {
		        data_size = received_data_length ;
	            }
		    else
		    {
	                data_size = bd->size;
		    }
		    //copy_from_buffer(buffer_ptr,destination_ptr,data_size);
		    memcpy(destination_ptr, buffer_ptr,data_size);
		    /* free the buffer after copying the data */
		    free_buffer(received_buffer_addrs);

		    /* update the total bytes received in buffer descriptor */
		    bd->bytes_transfered = data_size ;

		    status = USB_SUCCESS;
	        }
                else
                {
                    /* Endpoint Not complete is taken as 0 length data received and SUCCESS case */
		    /* update the total bytes received in buffer descriptor */
		    bd->bytes_transfered = 0x0 ;
		    status = USB_SUCCESS;
                }

                break;
	}
    }
    else
    {
        status = USB_INVALID ;
    }

    return status;
}
/*==================================================================================================

FUNCTION: ipl_receive_setup_data

DESCRIPTION:
	This function receive setupdata from host .

ARGUMENTS PASSED:
	BufferDesc - This is the pointer to the buffer descriptor. Caller provides storage for the
	             buffer and the data,


RETURN VALUE:
	USB_SUCCESS - 	: The buffer was successfully processed by the USB device and
			  data is received from the host.
	USB_FAILURE - 	: Some failure occurred in receiving the data.
	USB_INVALID -: If the endpoint is invalid.

IMPORTANT NOTES:
	None

==================================================================================================*/
usb_status_t
ipl_receive_setup_data(usb_buffer_descriptor_t* bd)
{
    volatile struct dqh_setup_t * dqh_word ;
    U32 dqh_address;
    usb_status_t status = USB_FAILURE;
    U32 temp;
    /* varify that the address passed is not NULL */
    if( bd->buffer != NULL )
    {
        /* Get the Device Queue Head Address for EP0 OUT   */
        dqh_address = ipl_get_dqh(EP0,OUT);
        dqh_word = (volatile struct dqh_setup_t*)dqh_address;

	/* write '1' to clear corresponding bit in ENDPTSETUPSTAT */
	*(VP_U32)USB_OTG_ENDPTSETUPSTAT = BIT0;

	do
        {
	    /* write '1' to Setup Tripwire (SUTW) in USBCMD register */
	    *(VP_U32)USB_OTG_USBCMD |= BIT13;

	    /* Copy the SetupBuffer into local software byte array */
	    temp  = (dqh_word->dqh_word10);

/* This is due to the simulator bug for word variant access on EMI but actually design has word invariant access */

            *((U8 *)(bd->buffer)) = (U8 )(temp & 0x000000FF);
            (bd->buffer) =(U8 *)(bd->buffer) + 1;
            *((U8 *)(bd->buffer)) = (U8 )((temp & 0x0000FF00)>>8);
            (bd->buffer) =(U8 *)(bd->buffer) + 1;
            *((U8 *)(bd->buffer)) = (U8 )((temp & 0x00FF0000)>>16);
            (bd->buffer) =(U8 *)(bd->buffer) + 1;
            *((U8 *)(bd->buffer)) = (U8 )((temp & 0xFF000000)>>24);
            (bd->buffer) =(U8 *)(bd->buffer) + 1;

            temp  = (dqh_word->dqh_word11);
            *((U8 *)(bd->buffer)) = (U8 )(temp & 0x000000FF);
            (bd->buffer) =(U8 *)(bd->buffer) + 1;
            *((U8 *)(bd->buffer)) = (U8 )((temp & 0x0000FF00)>>8);
            (bd->buffer) =(U8 *)(bd->buffer) + 1;
            *((U8 *)(bd->buffer)) = (U8 )((temp & 0x00FF0000)>>16);
            (bd->buffer) =(U8 *)(bd->buffer) + 1;
            *((U8 *)(bd->buffer)) = (U8 )((temp & 0xFF000000)>>24);
            (bd->buffer) =(U8 *)(bd->buffer) + 1;

	}while (!(*(VP_U32)USB_OTG_USBCMD & BIT13));

        /* Write '0' to clear SUTW in USBCMD register */
        *(VP_U32)USB_OTG_USBCMD &= ~BIT13;

        status = USB_SUCCESS;
    }
    else
    {
        status = USB_INVALID;
    }
    return status;
}
/*==================================================================================================

FUNCTION: ipl_get_ep0_rxtx_buffer

DESCRIPTION:
   	This function returns the buffer address for EP0

ARGUMENTS PASSED:
	None

RETURN VALUE:
	None

IMPORTANT NOTES:
	None

==================================================================================================*/
U32 ipl_get_ep0_rxtx_buffer()
{
    return (g_buffer_map.ep0_buffer_addrs) ;
}

/*==================================================================================================

FUNCTION: ipl_setup_transfer_desc

DESCRIPTION:
   	This function is used to setup the dTD

ARGUMENTS PASSED:
	U32 dtd_base - Base Address of the dTD
	U32 next_link_ptr - Next Link Pointer,
	U8 	terminate - terminate - TERMINATE; not terminate - NOT_TERMINATE
	U16 total_bytes - Total Bytes to be transfered in this dQH
	U8 	ioc - interrupt on complete, set - IOC_SET, not set - IOC_NOTSET
	U8 	Status - Status
	U32 buffer_ptr0 - Buffer Pointer page 0
	U16 current_offset - current offset
	U32 buffer_ptr1 - Buffer Pointer page 1
	U32 buffer_ptr2 - Buffer Pointer page 1
	U32 buffer_ptr3 - Buffer Pointer page 1
	U32 buffer_ptr4 - Buffer Pointer page 1

RETURN VALUE:
	None

IMPORTANT NOTES:
	None

==================================================================================================*/
void ipl_setup_transfer_desc(struct dtd_t* td)
{
    volatile struct dtd_setup_t* dtd_word = (volatile struct dtd_setup_t *) td->dtd_base;

    /* Bit31:5 Next Link Pointer ; Bit0 terminate */
    dtd_word->dtd_word0 = ((td->next_link_ptr & 0xFFFFFFE0) | td->terminate);

    /* Bit30:16 total_bytes, Bit15 ioc, Bit7:0 status */
    dtd_word->dtd_word1 = ((((U32)td->total_bytes & 0x7FFF) << 16)| ((U32)td->ioc <<15) | (td->status));

    /* Bit31:12 Buffer Pointer Page 0 ; Bit11:0 Current Offset */
    dtd_word->dtd_word2 = ((td->buffer_ptr0 & 0xFFFFF000) | (td->current_offset & 0xFFF));

    /* Bit31:12 Buffer Pointer Page 1 ; Bit10:0 Frame Number */
    dtd_word->dtd_word3 = (td->buffer_ptr1 & 0xFFFFF000);

    /* Bit31:12 Buffer Pointer Page 2 ; */
    dtd_word->dtd_word4 = (td->buffer_ptr2 & 0xFFFFF000);

    /* Bit31:12 Buffer Pointer Page 3 ; */
    dtd_word->dtd_word5 = (td->buffer_ptr3 & 0xFFFFF000);

    /* Bit31:12 Buffer Pointer Page 4 ; */
    dtd_word->dtd_word6 = (td->buffer_ptr4 & 0xFFFFF000);

}
/*==================================================================================================

FUNCTION: ipl_device_only_mode

DESCRIPTION:
   	This function is used to configure the USB OTG port to Device only mode

ARGUMENTS PASSED:
	None

RETURN VALUE:
	None

IMPORTANT NOTES:
	None

==================================================================================================*/
void ipl_device_only_mode(void)
{
    /* Set to Device only mode */
    /* *(VP_U32)USB_OTG_MIRROR_REG |= 0x1; */

#ifndef SIMULATOR_TESTING
    /* Reset */
    *(VP_U32)USB_OTG_USBCMD |= BIT1;

    /* wait for the Reset complete */
    while (*(VP_U32)USB_OTG_USBCMD & BIT1);
#endif

    /* set to device controller */
    *(VP_U32)USB_OTG_USBMODE = 0x2;

    /* check that device controller was configured to device mode only */
    while (!(*(VP_U32)USB_OTG_USBMODE == 0x2));
}
/*==================================================================================================

FUNCTION: ipl_clear_dqh

DESCRIPTION:
   	This function is used to Clear the DQH before initiate

ARGUMENTS PASSED:
	None

RETURN VALUE:
	None

IMPORTANT NOTES:
	None

==================================================================================================*/
void ipl_clear_dqh(void)
{
    U8 i = 0;
    VP_U32 ep_q_hdr_base;

    ep_q_hdr_base = ((VP_U32)g_buffer_map.ep_dqh_base_addrs);

    /* Clear the dQH Memory */
    for ( i = 0; i < (SIZE_OF_QHD*g_max_ep_supported*2)/sizeof(U32) ; i++)
    {
        *ep_q_hdr_base++ = 0;
    }
}
/*==================================================================================================

FUNCTION: ipl_setup_qhead

DESCRIPTION:
   	This function is used to setup the dQH
	 ------------------------
	|	EP2 IN	(64 bytes)	 |
	|				 |
	 ------------------------	dQH5
	|	EP2 OUT	(64 bytes)	 |
	| 			 	 |
	 ------------------------	dQH4
	|	EP1 IN	(64 bytes)	 |
	| 				 |
	 ------------------------	dQH3
	|	EP1 OUT	(64 bytes)	 |
	| 				 |
	 ------------------------ 	dQH2
	|	EP0 IN	(64 bytes)	 |
	| 				 |
	 ------------------------	dQH1
	|	EP0 OUT	(64 bytes)	 |
	| 				 |
	 ------------------------	dQH0
ARGUMENTS PASSED:
	U32 dqh_base - Base Address of the dQH
	U8 	zlt - zero lengh packet termination (enable - ZLT_ENABLE; disable - ZLT_DISABLE)
	U16 mps - Max packet length
	U8 	ios - interrupt on Setup
	U32 next_link_ptr - Next Link Pointer,
	U8 	terminate - terminate - TERMINATE; not terminate - NOT_TERMINATE
	U16 total_bytes - Total Bytes to be transfered in this dQH
	U8 	ioc - interrupt on complete, set - IOC_SET, not set - IOC_NOTSET
	U8 	status - status
	U32 buffer_ptr0 - Buffer Pointer page 0
	U16 current_offset - current offset
	U32 buffer_ptr1 - Buffer Pointer page 1
	U32 buffer_ptr2 - Buffer Pointer page 1
	U32 buffer_ptr3 - Buffer Pointer page 1
	U32 buffer_ptr4 - Buffer Pointer page 1

RETURN VALUE:
	None

IMPORTANT NOTES:
	None

==================================================================================================*/
void ipl_setup_qhead(struct dqh_t* qhead)
{
    volatile struct dqh_setup_t* dqh_word = (volatile struct dqh_setup_t*) qhead->dqh_base;

    /*======
    0x0
    ======
    Bit31:30 Mult; Bit29 zlt; Bit26:16 mps; Bit15 ios */
    dqh_word->dqh_word0 = (((U32)(qhead->zlt) << 29)|((U32)(qhead->mps) <<16) | ((U32)(qhead->ios) <<15));

    /*======
    0x4
    ======
    Current dTD Pointer => for hw use, not modified by DCD software */
    dqh_word->dqh_word1 = 0x0;

    /*======
    0x8
    ======
    Next dTD Pointer */
    dqh_word->dqh_word2 = (((qhead->next_link_ptr) & 0xFFFFFFE0) | qhead->terminate);

    /*======
    0xC
    ======
    Bit30:16 total_bytes; Bit15 ioc; Bit11:10 MultO; Bit7:0 status */
    dqh_word->dqh_word3 = ((((U32)(qhead->total_bytes) & 0x7FFF)  << 16) | ((U32)(qhead->ioc) <<15) | (qhead->status));

    /*======
    0x10
    ======
    Bit31:12 Buffer Pointer (Page 0) */
    dqh_word->dqh_word4 = ((qhead->buffer_ptr0 & 0xFFFFF000) | (qhead->current_offset & 0xFFF));

    /*======
    0x14
    ======
    Bit31:12 Buffer Pointer (Page 1) */
    dqh_word->dqh_word5 = (qhead->buffer_ptr1 & 0xFFFFF000);

    /*======
    0x18
    ======
    Bit31:12 Buffer Pointer (Page 2) */
    dqh_word->dqh_word6 = (qhead->buffer_ptr2 & 0xFFFFF000);

    /*======
    0x1C
    ======
    Bit31:12 Buffer Pointer (Page 3) */
    dqh_word->dqh_word7 = (qhead->buffer_ptr3 & 0xFFFFF000);

    /*======
    0x20
    ======
    Bit31:12 Buffer Pointer (Page 4) */
    dqh_word->dqh_word8 = (qhead->buffer_ptr4 & 0xFFFFF000);

    /*======
    0x24
    ======
    Reserved */
    dqh_word->dqh_word9 = 0;

    /*======
    0x28
    ======
    Setup Buffer 0 */
    dqh_word->dqh_word10 = 0;

    /*======
    0x2C
    ======
    Setup Buffer 1 */
    dqh_word->dqh_word11 = 0;
}
/*==================================================================================================

FUNCTION: ipl_get_dqh

DESCRIPTION:
   	This function return the qHD pointer for the required endpoint and direction

ARGUMENTS PASSED:
	U8 endpt_number -	Endpoint Number .
	U8 direction -	IN : qHD of IN EndPoint is to be returned
			OUT: qHD of OUT EndPoint is to be returned

RETURN VALUE:
	U32 Address : This function return the base address of the qHead structure of the requested Endpoint.

IMPORTANT NOTES:
	None

==================================================================================================*/
U32
ipl_get_dqh(U8 endpt_number , U8 direction)
{
    /* direction OUT = 0 and IN = 1 */
    return (g_buffer_map.ep_dqh_base_addrs + (SIZE_OF_QHD * (endpt_number * 2 + direction)));
}

/*==================================================================================================

FUNCTION: ipl_get_dtd

DESCRIPTION:
   	This function return the dTD pointer for the required endpoint and direction

ARGUMENTS PASSED:
	U8 endpt_number -	Endpoint Number .
	U8 direction -	IN : dTD of IN EndPoint is to be returned
			OUT: dTD of OUT EndPoint is to be returned

RETURN VALUE:
	None

IMPORTANT NOTES:
	None

==================================================================================================*/
U32
ipl_get_dtd(U8 endpt_number, U8 direction)
{
    /* If Maximum EPs supported in n then EPno will range from 0 to (n-1) */
    return (g_buffer_map.ep_dtd_base_addrs + (SIZE_OF_DTD0 + SIZE_OF_DTD1) * ( endpt_number * 2 + direction));
}



/*==================================================================================================

FUNCTION: alloc_buffer

DESCRIPTION:
   	This function allocate the free buffer available

ARGUMENTS PASSED:
 	None

RETURN VALUE:
	U32 address : address of the allocated buffer

IMPORTANT NOTES:
	If Buffer1 is FREE then return Buffer1 and mark this as Busy else check for buffer2 . If
	none of the buffer is free then return NULL.

==================================================================================================*/

U32 alloc_buffer(void)
{
    U32 buffer_addr = (U32)NULL;

    /* Check if buffer1 is free then mark it busy and return address */
    if (g_buffer_map.buffer1_status == BUFFER_FREE )
    {
        buffer_addr = g_buffer_map.buffer1_address;
	g_buffer_map.buffer1_status = BUFFER_IN_USE;
    }
    /* Check if buffer2 is free then mark it busy and return address */
    else if(g_buffer_map.buffer2_status == BUFFER_FREE)
    {
        buffer_addr = g_buffer_map.buffer2_address;
	g_buffer_map.buffer2_status = BUFFER_IN_USE;
    }

    return buffer_addr ;
}

/*==================================================================================================

FUNCTION: free_buffer

DESCRIPTION:
   	This function put the buffer in free state.

ARGUMENTS PASSED:
	U32 address : address of the buffer .

RETURN VALUE:
 	None

IMPORTANT NOTES:
	None

==================================================================================================*/
void free_buffer(U32 address)
{
    if( address == g_buffer_map.buffer1_address )
    {
        g_buffer_map.buffer1_status = BUFFER_FREE;
    }
    else if ( address == g_buffer_map.buffer2_address )
    {
        g_buffer_map.buffer2_status = BUFFER_FREE;
    }
}
/*==================================================================================================

FUNCTION: get_rxd_buffer

DESCRIPTION:
   	This function return the buffer in which data was received.

ARGUMENTS PASSED:
 	None

RETURN VALUE:
	U32 address : address of the buffer .

IMPORTANT NOTES:
        Whenever this function is called one of the buffer will be busy and other should be free.

==================================================================================================*/
U32 get_rxd_buffer(void)
{
    U32 address = (U32)NULL;

    /* check if the buffer1 was used for receiving data */
    if( g_buffer_map.buffer1_status == BUFFER_IN_USE)
    {
        address = g_buffer_map.buffer1_address;
    }
    /* check if the buffer2 was used for receiving data */
    else if( g_buffer_map.buffer2_status == BUFFER_IN_USE)
    {
        address = g_buffer_map.buffer2_address ;
    }
    return address;
}

