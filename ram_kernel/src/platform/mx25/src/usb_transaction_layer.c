/*==================================================================================================
                                                                               
    Module Name:  usb_transaction_layer.c

    General Description: This file contains the USB transaction Layer functionality .

====================================================================================================
    Copyright (C) 2006,2007,2008 Freescale Semiconductor, Inc. All Rights Reserved
    THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
    BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
    Freescale Semiconductor, Inc.
  

Revision History:
                            Modification     Tracking
Author                          Date          Number     Description of Changes
-------------------------   ------------    ----------   -------------------------------------------
Radhish                      21/05/2008     ENGcm05761   Add the missing break statement in tl_init fn
Radhish                      05/05/2008     ENGcm05524   Remove the Enumeration Flow in LPB case
Radhish                      11/04/2008     ENGcm05241   Stall Fix For Senna
Radhish                      29/02/2008     ENGcm03622   LPB Support for Senna 
Radhish                      05/02/2008     ENGcm03236   Added Senna related string descriptors
Prabhat Singh                05/09/2007     TLSbo95960   Merged TLSbo95965 CR for USB enumeration from Carmel  
SaiKiran Bollu               06/29/2007     TLSbo94222   Ported to Ringo from Carmel 1.1
Radhish Ayyappan             06/19/2007     TLSbo93893   Fix GET_DESCRIPTOR of DEVICE type to return
                                                         0x12 bytes instead of 0x40 bytes.
Balvinder Singh              03/12/2007     TLSbo92286   Ported ULPI HS from Skyeplus
Bharat Bhushan               31-Jan-2007    TLSbo89520   Handling Reset before chirping starts .
Bharat Bhushan               03-Jan-2007    TLSbo87117   USB driver making byte access in NFC buffer
                                                         in handling GET CONFIGURATION USB2.0 request.
Bharat Bhushan               03-Nov-2006    TLSbo82380   Changes for testing on softsim .
Bharat Bhushan               24-Aug-2006    TLSbo76463   Porting to SKYE+ .
Bharat Bhushan               04/08/2006     TLSbo74877   Maximum Packet Size changed from 0x08 to 
                                                         0x40 for EP0.
Bharat Bhushan               05/10/2006     TLSbo68884   Initial Version ( USB Layer Architecture).


-------------------------   ------------    ----------   ------------------------------------------- 
Portability: Portable.


====================================================================================================
                                        INCLUDE FILES
==================================================================================================*/
#include "su_basictypes.h"
#include "usb_common.h"
#include "usb_transaction_layer.h"
#include "usb_ipl_tl_extern.h"
#include "usb_tl_al_extern.h"
#include "platform.h"
/*==================================================================================================
                                     GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                     LOCAL CONSTANTS
==================================================================================================*/
#define IIM_BASE_ADDR               0x53ff0000
#define IIM_FB0_BASE                (IIM_BASE_ADDR + 0x0800)

/*=================================================================================================
                                 LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

static void tl_handle_setup_phase(void);
static void tl_handle_get_descriptor(void);
static void tl_handle_set_addrs(void);
static void tl_fill_buffer_ep0in(U8 type, U32 buffer_addrs);
static void tl_handle_set_configuration(void);
static void tl_handle_get_device_desc(void);
static void tl_handle_get_device_qf_desc(void);
static void tl_handle_get_config_desc(U8 descriptor);
static void tl_handle_get_string_desc(void);
static void tl_status_phase(U8 Direction);
static void tl_handle_get_configuration(void);

/*==================================================================================================
                                      LOCAL VARIABLES
==================================================================================================*/
/* USB Device Descriptor according to USB2.0 Specification */
usb_device_desc_t g_usb_device_desc = {
    USB_DEV_DESC_LEN,
    USB_DEV_DESC_TYPE,             
    USB_DEV_DESC_SPEC_LB,              
    USB_DEV_DESC_SPEC_HB,        
    USB_DEV_DESC_DEV_CLASS,          
    USB_DEV_DESC_DEV_SUBCLASS,        
    USB_DEV_DESC_DEV_PROTOCOL,         
    USB_DEV_DESC_EP0_MAXPACKETSIZE,     
    USB_DEV_DESC_VENDORID_LB,               
    USB_DEV_DESC_VENDORID_HB,               
    USB_DEV_DESC_PRODUCTID_LB,               
    USB_DEV_DESC_PRODUCTID_HB,               
    USB_DEV_DESC_DEV_RELEASE_NUM_LB,          
    USB_DEV_DESC_DEV_RELEASE_NUM_HB,         
    USB_DEV_DESC_DEV_STRING_IND_MANUFACTURE,
    USB_DEV_DESC_DEV_STRING_IND_PRODUCT,  
    USB_DEV_DESC_DEV_STRING_IND_SERIAL_NUM,
    USB_DEV_DESC_DEV_NUM_CONFIGURATIONS
};

/* USB Device Qualifier Descriptor according to USB2.0 Specification */
usb_device_qualifier_desc_t g_usb_device_qf_desc = {
    USB_DEV_QUALIFIER_DESC_LEN,
    USB_DEV_QUALIFIER_DESC_TYPE,
    USB_DEV_DESC_SPEC_LB,              
    USB_DEV_DESC_SPEC_HB,        
    USB_DEV_DESC_DEV_CLASS,          
    USB_DEV_DESC_DEV_SUBCLASS,        
    USB_DEV_DESC_DEV_PROTOCOL,         
    USB_DEV_DESC_EP0_MAXPACKETSIZE,     
    USB_DEV_DESC_NUM_OT_SPEED_CONF,
    USB_DEV_DESC_RESERVED 
};

/* USB Config Descriptor according to USB2.0 Specification */
/* Full Speed Non Secure */
usb_config_desc_t g_usb_config_desc_fs_ns = {
    USB_DEV_CONFIG_DESC_LEN,   
    USB_DEV_CONFIG_DESC_TYPE,   
    USB_DEV_CONFIG_DESC_TTL_LEN_LB ,   
    USB_DEV_CONFIG_DESC_TTL_LEN_HB ,   
    USB_DEV_CONFIG_DESC_NUM_0F_INF,  
    USB_DEV_CONFIG_DESC_CONFIG_VALUE ,  
    USB_DEV_CONFIG_DESC_STRING_INDEX, 
    USB_DEV_CONFIG_DESC_ATTRIBUTES,    
    USB_DEV_CONFIG_DESC_MAX_POWER,
	{
/* USB Interface Descriptor according to USB2.0 Specification */
        USB_DEV_INF_DESC_LEN,  
        USB_DEV_INF_DESC_TYPE,  
        USB_DEV_INF_DESC_INF_INDEX, 
        USB_DEV_INF_DESC_ALT_SETTING,
        USB_DEV_INF_DESC_NUM_OF_EP,  /* NOTE : This should not be more than 2 */
        USB_DEV_INF_DESC_INF_CLASS, 
        USB_DEV_INF_DESC_INF_SUBCLASS_NS_BLANK,   
        USB_DEV_INF_DESC_INF_PROTOCOL, 
        USB_DEV_INF_DESC_STRING_INDEX,  
	},
    { {
/* USB Endpoint 1 Descriptors according to USB2.0 Specification */
        USB_EP1_DESC_SIZE,
        USB_EP1_DESC_TYPE,
        USB_EP1_DESC_EP_ADDR,
        USB_EP1_DESC_ATTRIBUTES, 
        USB_EP1_DESC_MAX_PACKET_SIZE_FS_LB, 
        USB_EP1_DESC_MAX_PACKET_SIZE_FS_HB, 
        USB_EP1_DESC_INTERVAL,  
     },
     {  
/* USB Endpoint 2 Descriptors according to USB2.0 Specification */
        USB_EP2_DESC_SIZE, 
        USB_EP2_DESC_TYPE,
        USB_EP2_DESC_EP_ADDR,    
        USB_EP2_DESC_ATTRIBUTES,  
        USB_EP2_DESC_MAX_PACKET_SIZE_FS_LB,  
        USB_EP2_DESC_MAX_PACKET_SIZE_FS_HB,  
        USB_EP2_DESC_INTERVAL    
    } }
};

/* Full Speed Secure */
usb_config_desc_t g_usb_config_desc_fs_s = {
    USB_DEV_CONFIG_DESC_LEN,   
    USB_DEV_CONFIG_DESC_TYPE,   
    USB_DEV_CONFIG_DESC_TTL_LEN_LB ,   
    USB_DEV_CONFIG_DESC_TTL_LEN_HB ,   
    USB_DEV_CONFIG_DESC_NUM_0F_INF,  
    USB_DEV_CONFIG_DESC_CONFIG_VALUE ,  
    USB_DEV_CONFIG_DESC_STRING_INDEX, 
    USB_DEV_CONFIG_DESC_ATTRIBUTES,    
    USB_DEV_CONFIG_DESC_MAX_POWER,
	{
/* USB Interface Descriptor according to USB2.0 Specification */
        USB_DEV_INF_DESC_LEN,  
        USB_DEV_INF_DESC_TYPE,  
        USB_DEV_INF_DESC_INF_INDEX, 
        USB_DEV_INF_DESC_ALT_SETTING,
        USB_DEV_INF_DESC_NUM_OF_EP,  /* NOTE : This should not be more than 2 */
        USB_DEV_INF_DESC_INF_CLASS, 
        USB_DEV_INF_DESC_INF_SUBCLASS_S_BLANK,   
        USB_DEV_INF_DESC_INF_PROTOCOL, 
        USB_DEV_INF_DESC_STRING_INDEX,  
    },
    { {
/* USB Endpoint 1 Descriptors according to USB2.0 Specification */
        USB_EP1_DESC_SIZE,
        USB_EP1_DESC_TYPE,
        USB_EP1_DESC_EP_ADDR,
        USB_EP1_DESC_ATTRIBUTES, 
        USB_EP1_DESC_MAX_PACKET_SIZE_FS_LB, 
        USB_EP1_DESC_MAX_PACKET_SIZE_FS_HB, 
        USB_EP1_DESC_INTERVAL,  
     },
     {
/* USB Endpoint 2 Descriptors according to USB2.0 Specification */
        USB_EP2_DESC_SIZE, 
        USB_EP2_DESC_TYPE,
        USB_EP2_DESC_EP_ADDR,    
        USB_EP2_DESC_ATTRIBUTES,  
        USB_EP2_DESC_MAX_PACKET_SIZE_FS_LB,  
        USB_EP2_DESC_MAX_PACKET_SIZE_FS_HB,  
        USB_EP2_DESC_INTERVAL    
    } }
};

/* High Speed Non Secure */
usb_config_desc_t g_usb_config_desc_hs_ns = {
    USB_DEV_CONFIG_DESC_LEN,   
    USB_DEV_CONFIG_DESC_TYPE,   
    USB_DEV_CONFIG_DESC_TTL_LEN_LB ,   
    USB_DEV_CONFIG_DESC_TTL_LEN_HB ,   
    USB_DEV_CONFIG_DESC_NUM_0F_INF,  
    USB_DEV_CONFIG_DESC_CONFIG_VALUE ,  
    USB_DEV_CONFIG_DESC_STRING_INDEX, 
    USB_DEV_CONFIG_DESC_ATTRIBUTES,    
    USB_DEV_CONFIG_DESC_MAX_POWER,
    {
/* USB Interface Descriptor according to USB2.0 Specification */
    USB_DEV_INF_DESC_LEN,  
    USB_DEV_INF_DESC_TYPE,  
    USB_DEV_INF_DESC_INF_INDEX, 
    USB_DEV_INF_DESC_ALT_SETTING,
    USB_DEV_INF_DESC_NUM_OF_EP,  /* NOTE : This should not be more than 2 */
    USB_DEV_INF_DESC_INF_CLASS, 
    USB_DEV_INF_DESC_INF_SUBCLASS_NS_BLANK,   
    USB_DEV_INF_DESC_INF_PROTOCOL, 
    USB_DEV_INF_DESC_STRING_INDEX,  
    },
    { {
/* USB Endpoint 1 Descriptors according to USB2.0 Specification */
    USB_EP1_DESC_SIZE,
    USB_EP1_DESC_TYPE,
    USB_EP1_DESC_EP_ADDR,
    USB_EP1_DESC_ATTRIBUTES, 
    USB_EP1_DESC_MAX_PACKET_SIZE_HS_LB, 
    USB_EP1_DESC_MAX_PACKET_SIZE_HS_HB, 
    USB_EP1_DESC_INTERVAL,  
     },
     {
/* USB Endpoint 2 Descriptors according to USB2.0 Specification */
    USB_EP2_DESC_SIZE, 
    USB_EP2_DESC_TYPE,
    USB_EP2_DESC_EP_ADDR,    
    USB_EP2_DESC_ATTRIBUTES,  
    USB_EP2_DESC_MAX_PACKET_SIZE_HS_LB,  
    USB_EP2_DESC_MAX_PACKET_SIZE_HS_HB,  
    USB_EP2_DESC_INTERVAL    
    } }
};

/* High Speed Secure */
usb_config_desc_t g_usb_config_desc_hs_s = {
    USB_DEV_CONFIG_DESC_LEN,   
    USB_DEV_CONFIG_DESC_TYPE,   
    USB_DEV_CONFIG_DESC_TTL_LEN_LB ,   
    USB_DEV_CONFIG_DESC_TTL_LEN_HB ,   
    USB_DEV_CONFIG_DESC_NUM_0F_INF,  
    USB_DEV_CONFIG_DESC_CONFIG_VALUE ,  
    USB_DEV_CONFIG_DESC_STRING_INDEX, 
    USB_DEV_CONFIG_DESC_ATTRIBUTES,    
    USB_DEV_CONFIG_DESC_MAX_POWER,
    {
/* USB Interface Descriptor according to USB2.0 Specification */
    USB_DEV_INF_DESC_LEN,  
    USB_DEV_INF_DESC_TYPE,  
    USB_DEV_INF_DESC_INF_INDEX, 
    USB_DEV_INF_DESC_ALT_SETTING,
    USB_DEV_INF_DESC_NUM_OF_EP,  /* NOTE : This should not be more than 2 */
    USB_DEV_INF_DESC_INF_CLASS, 
    USB_DEV_INF_DESC_INF_SUBCLASS_S_BLANK,   
    USB_DEV_INF_DESC_INF_PROTOCOL, 
    USB_DEV_INF_DESC_STRING_INDEX,  
    },
    { {
/* USB Endpoint 1 Descriptors according to USB2.0 Specification */
    USB_EP1_DESC_SIZE,
    USB_EP1_DESC_TYPE,
    USB_EP1_DESC_EP_ADDR,
    USB_EP1_DESC_ATTRIBUTES, 
    USB_EP1_DESC_MAX_PACKET_SIZE_HS_LB, 
    USB_EP1_DESC_MAX_PACKET_SIZE_HS_HB, 
    USB_EP1_DESC_INTERVAL,  
     },
     {
/* USB Endpoint 2 Descriptors according to USB2.0 Specification */
    USB_EP2_DESC_SIZE, 
    USB_EP2_DESC_TYPE,
    USB_EP2_DESC_EP_ADDR,    
    USB_EP2_DESC_ATTRIBUTES,  
    USB_EP2_DESC_MAX_PACKET_SIZE_HS_LB,  
    USB_EP2_DESC_MAX_PACKET_SIZE_HS_HB,  
    USB_EP2_DESC_INTERVAL    
     } }
};

/* USB String Descriptors 0, according to USB2.0 Specification */
usb_str0_desc_t g_usb_otg_str0_desc = {
    USB_STR0_DESC_SIZE,
    USB_STR0_DESC_TYPE,
    USB_LANGUAGE_ID_LB,
    USB_LANGUAGE_ID_HB
};

/* 
 STRING DESCRIPTOR
 See table 9-15 in USB2.0 spec (www.usb.org)
 iManufacturer
*/
usb_str1_desc_t g_usb_otg_string_desc1 = {
	USB_STR1_DESC_SIZE, 		/* bLength */
	USB_STR1_DESC_TYPE,		/* bDescriptorType */
	{
	'F', 0x00,			/* bString */
	'r', 0x00,
	'e', 0x00,
	'e', 0x00,
	's', 0x00,
	'c', 0x00,
	'a', 0x00,
	'l', 0x00,
	'e', 0x00,
	' ', 0x00,
	'S', 0x00,
	'e', 0x00,
	'm', 0x00,
	'i', 0x00,
	'C', 0x00,
	'o', 0x00,
	'n', 0x00,
	'd', 0x00,
	'u', 0x00,
	'c', 0x00,
	't', 0x00,
	'o', 0x00,
	'r', 0x00,
	' ', 0x00,
	'I', 0x00,
	'n', 0x00,
	'c', 0x00,
	' ', 0x00
	}
};
	 
/* STRING DESCRIPTOR
   See table 9-15 in USB2.0 spec (www.usb.org)
   iProduct
*/
usb_str2_desc_t g_usb_otg_string_desc2_se = {
	USB_STR2_DESC_SIZE_SE,      	/* bLength */
	USB_STR2_DESC_TYPE,		/* bDescriptorType */
	{
	'S', 0x00,	                /* bString */
	'E', 0x00,		
	' ', 0x00,			
	'B', 0x00,
	'l', 0x00,	
	'a', 0x00,		
	'n', 0x00,	
	'k', 0x00,		
	' ', 0x00,			
	'S', 0x00,			
	'E', 0x00,
	'N', 0x00,
	'N', 0x00,
	'A', 0x00
	}
};
usb_str2_desc_t g_usb_otg_string_desc2_sp = {
	USB_STR2_DESC_SIZE_S,      	/* bLength */
	USB_STR2_DESC_TYPE,		/* bDescriptorType */
	{
	'S', 0x00,	                /* bString */
	'P', 0x00,	                /* bString */
	' ', 0x00,			
	'B', 0x00,
	'l', 0x00,	
	'a', 0x00,		
	'n', 0x00,	
	'k', 0x00,		
	' ', 0x00,			
	'S', 0x00,			
	'E', 0x00,
	'N', 0x00,
	'N', 0x00,
	'A', 0x00
        }
};

usb_str2_desc_t g_usb_otg_string_desc2_ns = {
	USB_STR2_DESC_SIZE_NS,      	/* bLength */
	USB_STR2_DESC_TYPE,		/* bDescriptorType */
	{
	'N', 0x00,	                /* bString */
	'S', 0x00,		
	' ', 0x00,			
	'B', 0x00,
	'l', 0x00,	
	'a', 0x00,		
	'n', 0x00,	
	'k', 0x00,		
	' ', 0x00,			
	'S', 0x00,			
	'E', 0x00,
	'N', 0x00,
	'N', 0x00,
	'A', 0x00
        }
};


/* STRING DESCRIPTOR
   See table 9-15 in USB2.0 spec (www.usb.org)
   iSerialNumber */
usb_str3_desc_t g_usb_otg_string_desc3 = {
	USB_STR3_DESC_SIZE,			/* bLength */
	USB_STR3_DESC_TYPE,			/* bDescriptorType */
	{
	'F', 0x00,			/* bString */
	'r', 0x00,
	'e', 0x00,
	'e', 0x00,
	's', 0x00,
	'c', 0x00,
	'a', 0x00,
	'l', 0x00,
	'e', 0x00,
	' ', 0x00,
        'F', 0x00,
        'l', 0x00,
        'a', 0x00,
        's', 0x00,
        'h', 0x00
        }
};

usb_state_t g_usb_dev_state = USB_DEV_DUMMY_STATE; /* State os USB Device */
static U8 g_usb_setup_data[SETUP_DATA_LENGTH];		/* Length of setup data received */
static usb_end_pt_info_t  g_end_pt_info[USB_DEV_INF_DESC_NUM_OF_EP]; /* Array to keep information about the endpoints used */
static U8 g_number_of_endpoints;     /* Number of endpoints */
static usb_desc_t g_usb_desc;     /* USB Descriptors */
/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
/*==================================================================================================
                                     LOCAL FUNCTIONS
==================================================================================================*/


/*==================================================================================================

FUNCTION: tl_init

DESCRIPTION: 
	This Function does the Transaction Layer initialisation.

ARGUMENTS PASSED:
	None

RETURN VALUE:
	None
	
IMPORTANT NOTES:
	
==================================================================================================*/
void
tl_init(void)
{
    U8 i;
    BOOL hs_interface;
    U8 u8Type = 0;

    /* Check the type of interface selected i.e FS or HS */
    hs_interface = ipl_is_interface_high_speed();
   
    /* Select the common descriptors , these descriptor are independent of speed and security mode */ 
    g_usb_desc.device_desc = &g_usb_device_desc ;
    g_usb_desc.device_qf_desc = &g_usb_device_qf_desc;
    g_usb_desc.str_desc0 = &g_usb_otg_str0_desc;
    g_usb_desc.str_desc1 = &g_usb_otg_string_desc1;
    g_usb_desc.str_desc3 = &g_usb_otg_string_desc3;

    u8Type = (U8)((*((volatile U8 *)(IIM_FB0_BASE + 0x10))) & 0x7);

    switch(u8Type)
    {
        case HAB_SEC_DISABLED:
            /* Select the descriptors which are specific to Non Secure Boot */
            g_usb_desc.str_desc2 = &g_usb_otg_string_desc2_ns;

            if(hs_interface)
            {
                /* Selct the descriptors which are speed dependent also */
                g_usb_desc.config_desc = &g_usb_config_desc_hs_ns;
                g_usb_desc.ot_speed_config_desc = &g_usb_config_desc_fs_ns;
            }
            else
            {
                /* Selct the descriptors which are speed dependent also */
                g_usb_desc.config_desc = &g_usb_config_desc_fs_ns;
                g_usb_desc.ot_speed_config_desc = &g_usb_config_desc_hs_ns;
            }
        break;
         
        case HAB_ENGINEERING:
            /* Select the descriptors which are specific to Secure Engineering Boot */
            g_usb_desc.str_desc2 = &g_usb_otg_string_desc2_se;

            if(hs_interface)
            {
                /* Selct the descriptors which are speed dependent also */
                g_usb_desc.config_desc = &g_usb_config_desc_hs_s;
                g_usb_desc.ot_speed_config_desc = &g_usb_config_desc_fs_s;
            }
            else
            {
                /* Selct the descriptors which are speed dependent also */
                g_usb_desc.config_desc = &g_usb_config_desc_fs_s;
                g_usb_desc.ot_speed_config_desc = &g_usb_config_desc_hs_s;
            }
        break;    
        
        default:
            /* Select the descriptors which are specific to Secure Production Boot */
            g_usb_desc.str_desc2 = &g_usb_otg_string_desc2_sp;

            if(hs_interface)
            {
                /* Selct the descriptors which are speed dependent also */
                g_usb_desc.config_desc = &g_usb_config_desc_hs_s;
                g_usb_desc.ot_speed_config_desc = &g_usb_config_desc_fs_s;
            }
            else
            {
                /* Selct the descriptors which are speed dependent also */
                g_usb_desc.config_desc = &g_usb_config_desc_fs_s;
                g_usb_desc.ot_speed_config_desc = &g_usb_config_desc_hs_s;
            }
        break;
    }

  
    /* Get Number of Endpoints supported from Configuration Descriptor ( Use Secure Config Descriptor as Endpoint information for
       both Secure and Non Secure is same */
    g_number_of_endpoints = g_usb_desc.config_desc->usb_interface_desc.num_of_endpts;
   
   /* Store the Endpoint specific information in local variable structure to this Layer */
    for ( i = 0 ; i< g_number_of_endpoints ; i++)
    {
        g_end_pt_info[i].end_pt_no = ((g_usb_desc.config_desc->usb_endpoint_desc[i].endpoint_addrs) & ENDPT_NUMBER_MASK);
    	
	g_end_pt_info[i].direction = (((g_usb_desc.config_desc->usb_endpoint_desc[i].endpoint_addrs) & ENDPT_DIR_MASK )>>ENDPT_DIR_SHIFT);
	
	g_end_pt_info[i].transfer_type = (g_usb_desc.config_desc->usb_endpoint_desc[i].attributes & ENDPT_TRNS_TYPE_MASK);
	
	g_end_pt_info[i].max_pkt_size = ((g_usb_desc.config_desc->usb_endpoint_desc[i].max_pkt_size_l) | (( g_usb_desc.config_desc->usb_endpoint_desc[i].max_pkt_size_h ) << 8 ));
    }
}
/*==================================================================================================

FUNCTION: tl_get_state

DESCRIPTION: 
   	This function return the current state of USB Bus.

ARGUMENTS PASSED:
	None
  
RETURN VALUE:
	usb_state_t  g_usb_dev_state : State of the USB Bus .  	

IMPORTANT NOTES:
	
==================================================================================================*/
usb_state_t
tl_get_state(void)
{
    return g_usb_dev_state;
}
/*==================================================================================================

FUNCTION: tl_configure

DESCRIPTION: 
   	This function Does the enumeration of the USB . 

ARGUMENTS PASSED:
	None
  
RETURN VALUE:
	None
	

IMPORTANT NOTES:
	
==================================================================================================*/
void
tl_configure(void)
{
#ifdef SIMULATOR_TESTING
    int i;
#endif

    while(g_usb_dev_state!= USB_DEV_CONFIGURED_STATE)
    {

        /* Check if Bus Reset Received */
        if(ipl_check_bus_reset() == TRUE)
        {
    	    /* Handle Bus Reset */
            tl_handle_bus_reset(); 
        }	
    
#ifdef SIMULATOR_TESTING
        /* Required to wait endlessly for setup pkt , not checking for reset as per behavior in simulator */
        while(g_usb_dev_state != USB_DEV_CONFIGURED_STATE)
        {
#endif
            /* Check if Reset is already received and Setup Token Received */
            if((g_usb_dev_state != USB_DEV_DUMMY_STATE) && (ipl_check_setup_token() == TRUE))
            {
	            /* Handle Setup Token */
                tl_handle_setup_phase();
            }
#ifdef SIMULATOR_TESTING
        }
    /* Delay needs to be introduced for CORE simulated in simulator to reach DONE state */
    for(i =0;i<1000000;i++);
#endif
    }
}

/*==================================================================================================

FUNCTION: tl_send_data

DESCRIPTION: 
   	This function Handle the Send Request on USB Bus 

ARGUMENTS PASSED:
	usb_buffer_descriptor_t* bd
  
RETURN VALUE:
	

IMPORTANT NOTES:
	
==================================================================================================*/
usb_status_t
tl_send_data(usb_buffer_descriptor_t* bd)
{
    usb_status_t status = USB_FAILURE;
    U8 i,endpoint = 0x0;

#ifndef SIMULATOR_TESTING    
    /* Check if Bus Reset Received */
    if(ipl_check_bus_reset() == TRUE)
    {
	/* Handle Bus Reset and return Failure*/
        tl_handle_bus_reset(); 
    }
    /* Check if set up token Received */
    else if(ipl_check_setup_token() == TRUE)
    {
	/* Handle the setup token*/
        tl_handle_setup_phase(); 
    }
#endif
 
    /* Check the State of USB . If It is in  configured state than send data */
    if ( g_usb_dev_state == USB_DEV_CONFIGURED_STATE )
    {
        /* buffer pointer should not be NULL */
        if( bd->buffer != NULL )
	{
	    /* Get the endpoint number which is configured for IN */
	    for ( i = 0 ; i< g_number_of_endpoints ; i++)
	    {
                if(g_end_pt_info[i].direction == IN)
		{
		    endpoint = g_end_pt_info[i].end_pt_no;
		    break;
		}		    
	    }
	    /* Check for endpoint number */
	    if(endpoint)
	    {
		/* Send Data */
                status = (usb_status_t )ipl_send_data(endpoint,bd,FALSE);
	    }
	    else
	    {
	        status = USB_INVALID; /* If no endpoint is configured */
	    }
	}
	else
	{
	    status = USB_INVALID; /* if the buffer pointer is NULL */
	}
    }
    return(status);
}

/*==================================================================================================

FUNCTION: tl_receive_data

DESCRIPTION: 
	This Function Handles the received request on usb bus

ARGUMENTS PASSED:
	usb_buffer_descriptor_t* bd
  
RETURN VALUE:
	

IMPORTANT NOTES:
	
==================================================================================================*/
usb_status_t
tl_receive_data(usb_buffer_descriptor_t* bd)
{
    usb_status_t status = USB_FAILURE; 
    U8 i,endpoint = 0x0;

#ifndef SIMULATOR_TESTING   
    /* Check if Bus Reset Received  */
    if(ipl_check_bus_reset() == TRUE)
    {
	/* Handle Bus Reset and return Failure */
        tl_handle_bus_reset(); 
    }
    /* Check if set up token Received. */
    else if(ipl_check_setup_token() == TRUE)
    {
	/* Handle the setup token */
        tl_handle_setup_phase(); 
    }
#endif

    /* Check the State of USB . If It is in  configured state than receive data */
    if ( g_usb_dev_state == USB_DEV_CONFIGURED_STATE )
    {
        /* buffer pointer should not be NULL */
	if( bd->buffer != NULL )
	{
	    /* Get the endpoint number which is configured for OUT */
	    for ( i = 0 ; i< g_number_of_endpoints ; i++)
	    {
                if(g_end_pt_info[i].direction == OUT)
		{
		    endpoint = g_end_pt_info[i].end_pt_no;
		    break;
		}		    
	    }
	    /* endpoint number should not be EP0 */
	    if(endpoint)
	    {
		/* Receive data */
                status = (usb_status_t )ipl_receive_data(endpoint,bd);
	    }
	    else
	    {
	        status = USB_INVALID; /* If no endpoint is configured */
	    }
	}
	else
	{
	    status = USB_INVALID; /* if the buffer pointer is NULL */
	}
    }
    return(status);
}

/*==================================================================================================

FUNCTION: tl_handle_setup_phase

DESCRIPTION: 
   	This function Handle the Setup Token from USB Host

ARGUMENTS PASSED:
	None
  
RETURN VALUE:
	None
	

IMPORTANT NOTES:
	
==================================================================================================*/
void tl_handle_setup_phase(void)
{
    usb_buffer_descriptor_t bd ;
    usb_status_t status;

    /* Receive the SetUp Data */
    bd.buffer = (P_U32)g_usb_setup_data;
    bd.size   = 0;
    status = ipl_receive_setup_data(&bd);

    if( status == USB_SUCCESS)
    { 
        /* Parser the Setup Request Type */
        switch (g_usb_setup_data[BREQUEST])             
        { 
            case USB_GET_DESCRIPTOR:
                /* Handle the GET DESCRIPTOR Request */
	        tl_handle_get_descriptor();
	    break;
	
	    case USB_SET_ADDRESS:
                /* Handle the SET ADDRESS Request */
	        tl_handle_set_addrs();
             	
	    break;
	    
	    case USB_SET_CONFIGURATION:
                /* Handle the SET CONFIGURATION Request */
	        if ((g_usb_setup_data[WINDEX_LOWBYTE] == 0) &&
                    (g_usb_setup_data[WINDEX_HIGHBYTE] == 0) &&
                    (g_usb_setup_data[WLENGTH_LOWBYTE] == 0) &&
                    (g_usb_setup_data[WLENGTH_HIGHBYTE] == 0) &&
                    (g_usb_setup_data[WVALUE_HIGHBYTE] == 0)) 
	        {
                    tl_handle_set_configuration();
	        }
	        else
	        {
	            /* Send STALL Handshake   */
	            ipl_send_stall_handshake(EP0,OUT);
	        }

	    break;
	    case USB_GET_CONFIGURATION:
	        /* GET CONFIGURATION request handler */
	        tl_handle_get_configuration();

	    default:
	
	        /* Send STALL Handshake   */
	        ipl_send_stall_handshake(EP0,OUT);
	        ipl_send_stall_handshake(EP0,IN);
                
	    break;
	    }
        /* service watch dog */
        *(volatile U16 *)(WDOG_WSR) = 0x5555;
	    *(volatile U16 *)(WDOG_WSR) = 0xAAAA; 
    }    
}

/*==================================================================================================

FUNCTION: tl_handle_get_descriptor

DESCRIPTION: 
   	This function Handle the GET DESCRIPTOR request

ARGUMENTS PASSED:
	None
  
RETURN VALUE:
	None
	
IMPORTANT NOTES:
	None
		
==================================================================================================*/

void tl_handle_get_descriptor()
{
    switch (g_usb_setup_data[WVALUE_HIGHBYTE])
    {
        case DEVICE_DESC:  	/* device descriptor*/
			
            tl_handle_get_device_desc();
	    break;

	case CONF_DESC:  	/* configuration descriptor*/

	    tl_handle_get_config_desc(CONF_DESC);
	    break;

	case STRING_DESC:	/* string descriptor*/

	    tl_handle_get_string_desc();
	    break;

	case DEVICE_QUALIFIER:

	    tl_handle_get_device_qf_desc();  /* device qualifier descriptor */
	    break;

	case OTHER_SPEED_CONF_DESC:

	    tl_handle_get_config_desc(OTHER_SPEED_CONF_DESC); /* other speed configuration descriptor */
            break;

	default:	/* Send STALL Handshake  */
	    
	    ipl_send_stall_handshake(EP0,IN);
	    break;
    }
}


/*==================================================================================================

FUNCTION:  tl_handle_set_configuration

DESCRIPTION: 
   	This function Handle the SET CONFIGURATION request

ARGUMENTS PASSED:
	None
  
RETURN VALUE:
	None
	
IMPORTANT NOTES:
	None
		
==================================================================================================*/

void tl_handle_set_configuration()
{
    usb_end_pt_info_t config_data ; 
    U8 i;
	
    switch (g_usb_dev_state)
    {
	case USB_DEV_ADDRESSED_STATE :
            if (g_usb_setup_data[WVALUE_LOWBYTE] == USB_DEV_VALUE_OF_UNCONFIG)
	    {	
		/* Send Ack to Host*/
		tl_status_phase(IN);
	    }
            /* Check if the configuration value received request is same as in Config descriptor */
	    else if(g_usb_setup_data[WVALUE_LOWBYTE] == g_usb_desc.config_desc->configuration_value)
	    {
		/* Configure endpoints */
		for ( i = 0 ; i< g_number_of_endpoints ; i++)
		{
		    config_data.end_pt_no	= g_end_pt_info[i].end_pt_no; 
		    config_data.direction  	= g_end_pt_info[i].direction;
		    config_data.transfer_type	= g_end_pt_info[i].transfer_type;
		    config_data.max_pkt_size	= g_end_pt_info[i].max_pkt_size;
		
		    ipl_set_configuration(&config_data);
		}

		/* Send Ack to Host*/
		tl_status_phase(IN);

		g_usb_dev_state = USB_DEV_CONFIGURED_STATE ;
	    }
	    else
	    {
		/* Invalid configuration value.  Send STALL Handshake */
	        ipl_send_stall_handshake(EP0,IN);
	    }
	break;	
	case USB_DEV_CONFIGURED_STATE :
	    if(g_usb_setup_data[WVALUE_LOWBYTE] == USB_DEV_CONFIG_DESC_CONFIG_VALUE)
	    {
		/* Send Ack to Host*/
		tl_status_phase(IN);
	    }
	    else if (g_usb_setup_data[WVALUE_LOWBYTE] == USB_DEV_VALUE_OF_UNCONFIG)
	    {	
		/* Send Ack to Host*/
		tl_status_phase(IN);

		/* Change USB State to Addressed State	*/
		g_usb_dev_state = USB_DEV_ADDRESSED_STATE;
	    }
	break;
	default :
	        /* Send STALL Handshake */
	        ipl_send_stall_handshake(EP0,IN);
	break;	
    }
}
/*==================================================================================================

FUNCTION:  tl_handle_get_configuration

DESCRIPTION: 
   	This function Handle the GET CONFIGURATION request

ARGUMENTS PASSED:
	None
  
RETURN VALUE:
	None
	
IMPORTANT NOTES:
	None
		
==================================================================================================*/
void tl_handle_get_configuration(void)
{
    usb_buffer_descriptor_t bd;
    U32 buffer_addrs;
    U32* buffer_ptr;
    
    if((g_usb_setup_data[WINDEX_LOWBYTE] == 0) &&
        (g_usb_setup_data[WINDEX_HIGHBYTE] == 0) &&
       	(g_usb_setup_data[WVALUE_LOWBYTE] == 0) &&
       	(g_usb_setup_data[WVALUE_HIGHBYTE] == 0) &&
	(g_usb_setup_data[WLENGTH_LOWBYTE] == LEN_OF_CONFIG_VALUE) &&
       	(g_usb_setup_data[WLENGTH_HIGHBYTE] == 0)) 
    {
        switch(g_usb_dev_state)
	{
	    case USB_DEV_DEFAULT_STATE :
	        /* Send STALL Handshake */
	        ipl_send_stall_handshake(EP0,IN);

		break;
	    case USB_DEV_ADDRESSED_STATE:
		/* If the Device is in Address state then return 0x0 : See USB2.0 Spec */
		buffer_addrs = ipl_get_ep0_rxtx_buffer();
		buffer_ptr = (U32 *)buffer_addrs;

		*buffer_ptr = 0x0;

		bd.buffer = buffer_ptr;
		bd.size=LEN_OF_CONFIG_VALUE;

		ipl_send_data(EP0,&bd,FALSE);

		/* Receive Ack from Host*/
		tl_status_phase(OUT);
		
		break;
	    case USB_DEV_CONFIGURED_STATE:
		buffer_addrs = ipl_get_ep0_rxtx_buffer();
		buffer_ptr = (U32 *)buffer_addrs;

		*buffer_ptr = (UINT32 )g_usb_desc.config_desc->configuration_value;

		bd.buffer = buffer_ptr;
		bd.size=LEN_OF_CONFIG_VALUE;

		ipl_send_data(EP0,&bd,FALSE);
		
		/* Receive Ack from Host*/
		tl_status_phase(OUT);
		
		break;
	    default:
	        /* Send STALL Handshake */
	        ipl_send_stall_handshake(EP0,IN);
	}

    } 
}
/*==================================================================================================

FUNCTION: tl_handle_set_addrs

DESCRIPTION: 
   	This function Handle the SET ADDRESS Request from USB Host

ARGUMENTS PASSED:
	None
  
RETURN VALUE:
	None
	

IMPORTANT NOTES:
	
==================================================================================================*/
void tl_handle_set_addrs()
{
    U16 device_addrs;
   
    /* Get the Device Address to be SET from the Setup Data  */
    device_addrs = g_usb_setup_data[WVALUE_LOWBYTE] + (g_usb_setup_data[WVALUE_HIGHBYTE]<<8);
       
    if ((g_usb_setup_data[WINDEX_LOWBYTE] == 0) &&
          (g_usb_setup_data[WINDEX_HIGHBYTE] == 0) &&
	  (g_usb_setup_data[WLENGTH_LOWBYTE] == 0) &&
	  (g_usb_setup_data[WLENGTH_HIGHBYTE] == 0) &&
      	  (device_addrs <= USB_MAX_DEVICE_ADDR))
    { 
        switch(g_usb_dev_state)
	{
	    case USB_DEV_DEFAULT_STATE :
	        
		/* Send Ack to Host */
		tl_status_phase(IN);

		if (device_addrs == USB_DEFAULT_ADDR)
		{
		/* no handling needed */   
		}
		else
		{
		    /* Set the Device Address */
	            ipl_set_device_address(device_addrs);
	
		    /* Change state to ADDRESSED STATE  */
		    g_usb_dev_state = USB_DEV_ADDRESSED_STATE;
		}
	      	break;
		
	    case USB_DEV_ADDRESSED_STATE :
		    
		/* Send Ack to Host */
		tl_status_phase(IN);

		if ( device_addrs == USB_DEFAULT_ADDR )
		{
		    /* Set the Device Address */
		    ipl_set_device_address(USB_DEFAULT_ADDR);
		
		    /* Change state to ADDRESSED STATE  */
	    	    g_usb_dev_state = USB_DEV_DEFAULT_STATE;    
    		}
		else
		{
		    /* Set the Device Address */
	            ipl_set_device_address(device_addrs);
		}
	    	break;
	
    	    case USB_DEV_CONFIGURED_STATE :
	    	
	
	    	if ( device_addrs == USB_DEFAULT_ADDR)
	    	{
         	    /* Send Ack to Host */
   		    tl_status_phase(IN);
                      
		    /* Set the Device Address */
		    ipl_set_device_address(device_addrs);
		
	    	    /* Change state to ADDRESSED STATE  */
    		    g_usb_dev_state = USB_DEV_DEFAULT_STATE;    
		}
		else
		{
		    /* Send STALL Handshake  */ 
		    ipl_send_stall_handshake(EP0,IN);
		}
	    default :
    		break;
	}
    }
    else
    {
        /* Send STALL Handshake */
        ipl_send_stall_handshake(EP0,IN);	
    }
    
}
/*==================================================================================================

FUNCTION: tl_handle_get_device_desc

DESCRIPTION: 
   	This function Handle the GET DEVICE DESCRIPTOR request

ARGUMENTS PASSED:
	None
  
RETURN VALUE:
	None
	
IMPORTANT NOTES:
	None
		
==================================================================================================*/
void tl_handle_get_device_desc(void)
{
    usb_buffer_descriptor_t bd ;
    U32 buffer_addrs;
    U16 desc_length = 0x0;
    BOOL zlt = FALSE;
	
    /* get the buffer address for data transfer over EP0 */
    buffer_addrs = ipl_get_ep0_rxtx_buffer();
	
    /* Fill the buffer with the descriptor data */
    tl_fill_buffer_ep0in(FILL_DEVICE_DESC,buffer_addrs);

    /* Get the length of descriptor requested */
    desc_length = g_usb_setup_data[WLENGTH_LOWBYTE];
    desc_length |= ( g_usb_setup_data[WLENGTH_HIGHBYTE] <<0x8);

    /* If requested length of descriptor is lesser than actual length of descriotor then send 
     * requested length of descroptor only else send the actual length of descriptor*/

#ifdef SIMULATOR_TESTING
    if(desc_length <= g_usb_desc.device_desc->length)
    {
        bd.size = desc_length;
    }
    else
    {
        bd.size = g_usb_desc.device_desc->length;
        if ( bd.size > 8)
	{
	    zlt = TRUE;
	}
    }
#else   
    if( g_usb_dev_state == USB_DEV_DEFAULT_STATE )
    {
        bd.size = MPS_8;
    }
    else 
    {
        bd.size = USB_DEV_DESC_LEN;
    }
#endif

    /* Send descriptor */
    ipl_send_data(EP0,&bd,zlt);	
	
    /* Status Phase -- OUT */
    tl_status_phase(OUT); 
}

/*==================================================================================================

FUNCTION: tl_handle_get_device_qf_desc

DESCRIPTION: 
   	This function Handle the GET DEVICE QUALIFIER DESCRIPTOR request

ARGUMENTS PASSED:
	None
  
RETURN VALUE:
	None
	
IMPORTANT NOTES:
	None
		
==================================================================================================*/
void tl_handle_get_device_qf_desc(void)
{
    usb_buffer_descriptor_t bd ;
    U32 buffer_addrs;
    U16 desc_length = 0x0;
    BOOL zlt = FALSE;
	
    /* get the buffer address for data transfer over EP0 */
    buffer_addrs = ipl_get_ep0_rxtx_buffer();
	
    /* Fill the buffer with the descriptor data */
    tl_fill_buffer_ep0in(FILL_DEVICE_QF_DESC,buffer_addrs);

    /* Get the length of descriptor requested */
    desc_length = g_usb_setup_data[WLENGTH_LOWBYTE];
    desc_length |= ( g_usb_setup_data[WLENGTH_HIGHBYTE] <<0x8);

    /* If requested length of descriptor is lesser than actual length of descriotor then send 
     * requested length of descroptor only else send the actual length of descriptor*/
    if(desc_length <= g_usb_desc.device_qf_desc->length)
    {
        bd.size = desc_length;
    }
    else
    {
        bd.size = g_usb_desc.device_qf_desc->length;
        if ( bd.size > MPS_64)
	{
	    zlt = TRUE;
	}
    }

    /* Send descriptor */
    ipl_send_data(EP0,&bd,zlt);	
	
    /* Status Phase -- OUT */
    tl_status_phase(OUT); 
}

/*==================================================================================================

FUNCTION: tl_handle_get_config_desc

DESCRIPTION: 
   	This function Handle the GET CONFIGURATION DESCRIPTOR request

ARGUMENTS PASSED:
	U8 	other_speed 	0  : If the selected config descriptor is requested.
                                1  : If other speed config descriptor is requested. 
RETURN VALUE:
	None
	
IMPORTANT NOTES:
	None
		
==================================================================================================*/
void tl_handle_get_config_desc(U8 other_speed)
{
    usb_buffer_descriptor_t bd;
    U32 buffer_addrs;
    U16 desc_length_req = 0x0;
    U16 desc_length = 0x0;
    BOOL zlt = FALSE;

    /* get the buffer address for data transfer over EP0 */
    buffer_addrs = ipl_get_ep0_rxtx_buffer();

    if(other_speed == OTHER_SPEED_CONF_DESC)
    {
        /* Fill the buffer with the descriptor data */
        tl_fill_buffer_ep0in(FILL_OT_CONF_DESC, buffer_addrs);
    
	/* total length of descriptor */
	desc_length = ((g_usb_desc.ot_speed_config_desc->total_length_l) | ( g_usb_desc.ot_speed_config_desc->total_length_h << 0x8 ));
    }
    else
    {
        /* Fill the buffer with the descriptor data */
        tl_fill_buffer_ep0in(FILL_CONF_DESC, buffer_addrs);
    
	/* total length of descriptor */
	desc_length = ((g_usb_desc.config_desc->total_length_l) | ( g_usb_desc.config_desc->total_length_h << 0x8 ));
    }    
    /* Get the length of descriptor requested */
    desc_length_req = g_usb_setup_data[WLENGTH_LOWBYTE];
    desc_length_req |= ( g_usb_setup_data[WLENGTH_HIGHBYTE] <<0x8);


    /* If requested length of descriptor is lesser than actual length of descriotor then send 
     * requested length of descroptor only else send the actual length of descriptor*/
    if(desc_length_req <= desc_length)
    {
        bd.size = desc_length_req;
    }
    else
    {
        bd.size = desc_length;
        if ( bd.size > MPS_64)
	{
	    zlt = TRUE;
	}
    }
    ipl_send_data(EP0,&bd,zlt);	
	
    /* Status Phase -- OUT */
    tl_status_phase(OUT); 
}
/*==================================================================================================

FUNCTION: tl_handle_get_string_desc

DESCRIPTION: 
   	This function Handle the GET STRING DESCRIPTOR request

ARGUMENTS PASSED:
	None
  
RETURN VALUE:
	None
	
IMPORTANT NOTES:
	None
		
==================================================================================================*/

void tl_handle_get_string_desc(void)
{
    usb_buffer_descriptor_t bd;
    U32 buffer_addrs;
    U16 desc_length_req = 0x0;
    U16 length_of_desc = 0x0;
    BOOL zlt = FALSE;

    /* Get Buufer to fill the data to be received/transmitted.    */ 
    buffer_addrs = ipl_get_ep0_rxtx_buffer();
	   
    /* Get the length of descriptor requested */
    desc_length_req = g_usb_setup_data[WLENGTH_LOWBYTE];
    desc_length_req |= ( g_usb_setup_data[WLENGTH_HIGHBYTE] <<0x8);

    switch (g_usb_setup_data[WVALUE_LOWBYTE])
    {
        case STR_DES0:
            tl_fill_buffer_ep0in(FILL_STR_DES0,buffer_addrs);
    
	    /* If requested length of descriptor is lesser than actual length of descriotor then send 
	     * requested length of descroptor only else send the actual length of descriptor*/
	    if(desc_length_req <= g_usb_desc.str_desc0->length )
	    {
	        bd.size = desc_length_req;
	    }
	    else
	    {
		bd.size = g_usb_desc.str_desc0->length;
                if (  bd.size > MPS_64)
	        {
	            zlt = TRUE;
	        }
	    }
	    /* Data Phase -- IN */
	    ipl_send_data(EP0,&bd,zlt);	
	
	    /* Status Phase -- OUT */
	    tl_status_phase(OUT); 
        
	    break;
        
        case STR_DES1:		/*iManufacturer */
            tl_fill_buffer_ep0in(FILL_STR_DES1,buffer_addrs);
	    
	    /* If requested length of descriptor is lesser than actual length of descriotor then send 
	     * requested length of descroptor only else send the actual length of descriptor*/
	    if(desc_length_req <= g_usb_desc.str_desc1->length )
	    {
	        bd.size = desc_length_req;
	    }
	    else
	    {
		bd.size = g_usb_desc.str_desc1->length;
                if (  bd.size > MPS_64)
	        {
	            zlt = TRUE;
	        }
	    }
	    /* Data Phase -- IN */
	    ipl_send_data(EP0,&bd,zlt);	
	
	    /* Status Phase -- OUT */
	    tl_status_phase(OUT); 
        
	    break;
        
        case STR_DES2:		/*iProduct */
            tl_fill_buffer_ep0in(FILL_STR_DES2,buffer_addrs );
	  
                length_of_desc = g_usb_desc.str_desc2->length; 

	    /* If requested length of descriptor is lesser than actual length of descriotor then send 
	     * requested length of descroptor only else send the actual length of descriptor*/
	    if(desc_length_req <= length_of_desc )
	    {
	        bd.size = desc_length_req;
	    }
	    else
	    {
		bd.size = length_of_desc;
                if (  bd.size > MPS_64)
	        {
	            zlt = TRUE;
	        }
	    }
	    /* Data Phase -- IN */
	    ipl_send_data(EP0,&bd,zlt);	
	
	    /* Status Phase -- OUT */
	    tl_status_phase(OUT); 
       
	    break;
        
        case STR_DES3:	
		/* send zero length data */
                tl_status_phase(IN);
	
		/* Status Phase -- OUT */
                tl_status_phase(OUT);
		break;

        case STR_DES4:		/*iSerialNumber */
        case STR_DES5:		/*iSerialNumber */
            tl_fill_buffer_ep0in(FILL_STR_DES3,buffer_addrs );
            
	    /* If requested length of descriptor is lesser than actual length of descriotor then send 
	     * requested length of descroptor only else send the actual length of descriptor*/
	    if(desc_length_req <= g_usb_desc.str_desc3->length )
	    {
	        bd.size = desc_length_req;
	    }
	    else
	    {
		bd.size = g_usb_desc.str_desc3->length;
                if (  bd.size > MPS_64)
	        {
	            zlt = TRUE;
	        }
	    }
	
	    /* Data Phase -- IN */
	    ipl_send_data(EP0,&bd,zlt);	
	
	    /* Status Phase -- OUT */
	    tl_status_phase(OUT); 
        
	    break;
	default:
	    /* Send STALL Handshake  */
	    ipl_send_stall_handshake(EP0,IN);
	    
	    break;

    }
}

/*==================================================================================================

FUNCTION: tl_fill_buffer_ep0in

DESCRIPTION: 
   	This function is used to fill the corresponding response for the data phase of SETUP Transfer

ARGUMENTS PASSED:
	U8 type: type of descriptor
	U32 buffer_addrs - buffer pointer to be filled
	 
RETURN VALUE:
	None
	

IMPORTANT NOTES:
	None
==================================================================================================*/

void tl_fill_buffer_ep0in(U8 type, U32 buffer_addrs)
{
    const U8 *data=0;

    U32 *buffer_page = (P_U32)buffer_addrs;
    
    int k = 0;
	
    switch (type)
    {
        case FILL_DEVICE_DESC:	/*5*32 bit */
	    data = (U8 *)g_usb_desc.device_desc;
    	    break;
	    
	case FILL_DEVICE_QF_DESC:
	    data = (U8 *)g_usb_desc.device_qf_desc;
            break;
	    
	case FILL_CONF_DESC:		/*8*32 bit */
	    data = (U8 *)g_usb_desc.config_desc;
	    break;	

	case FILL_OT_CONF_DESC:		/*8*32 bit */
	    data = (U8 *)g_usb_desc.ot_speed_config_desc;
	    break;	

	case FILL_STR_DES0:		/*1*32 bit */
	    data = (U8 *)g_usb_desc.str_desc0;
	    break;	

	case FILL_STR_DES1:		/*7*32 bit */
	    data =(U8 *)g_usb_desc.str_desc1; 
	    break;	

	case FILL_STR_DES2:		/*7*32 bit */
            data = (U8 *)g_usb_desc.str_desc2;
	    break;	

	case FILL_STR_DES3:		/*6*32 bit */
	    data = (U8 *)g_usb_desc.str_desc3;
	    break;
    }
    
    for (k=0; k<(MPS_64/sizeof(U32)); k++)
    {
    #ifdef SIMULATOR_TESTING
       
	#if (ENDIANESS == b)		
          *buffer_page = data[0] + (data[1] << 8) + (data[2] << 16) + (data[3] << 24);
        #else
          *buffer_page = data[3] + (data[2] << 8) + (data[1] << 16) + (data[0] << 24); 
		 
        #endif	
    #else 
         *buffer_page = data[0] + (data[1] << 8) + (data[2] << 16) + (data[3] << 24); 
    #endif
        
	buffer_page++;
	data += 4;
    }
}


/*==================================================================================================

FUNCTION: tl_status_phase

DESCRIPTION: 
   	This function Send/Receive the Status to/from Host.

ARGUMENTS PASSED:
	U8    direction		OUT 	Receive Status Command From Host
			 	IN 	Send Status Command to Host
  
RETURN VALUE:
	None
	

IMPORTANT NOTES:
	
==================================================================================================*/

void tl_status_phase(U8 direction)
{
    usb_buffer_descriptor_t bd ;
    /* Buffer pointer is not used for EP0 */
    bd.buffer = (U32 *) 0xFFFFFFFF;
    bd.size = 0x0;
    switch ( direction )
    {
	case OUT :
	    /*  Receive ZERO length Length Data */
	    ipl_receive_data(EP0,&bd);
    	    break;
	case IN :
	    /* Send ZERO length Length Data */
	    ipl_send_data(EP0,&bd,FALSE);
	    break;
    }
}



/*==================================================================================================

FUNCTION: tl_handle_bus_reset

DESCRIPTION: 
   	This function Handle the USB Bus Reset Event 

ARGUMENTS PASSED:
	None
  
RETURN VALUE:
	None
	
IMPORTANT NOTES:
	
==================================================================================================*/
void tl_handle_bus_reset()
{
    /* Change USB State to Default */
    g_usb_dev_state = USB_DEV_DEFAULT_STATE;
    
    /* Initialise the IP Layer  */
    ipl_handle_bus_reset();
}


/*==================================================================================================

FUNCTION: tl_check_for_bus_activity

DESCRIPTION: 
   	This function Check for Bus Reset Event 

ARGUMENTS PASSED:
	None
  
RETURN VALUE:
        BOOL rtn 	: return TRUE is BUS RESET event detected else return FALSE.	
	
IMPORTANT NOTES:
	
==================================================================================================*/
BOOL tl_check_for_bus_activity(void)
{
    BOOL rtn = FALSE;
    /* Check if Bus Reset Received */
    if(ipl_check_bus_reset() == TRUE)
    {
        rtn = TRUE;
    }

   return rtn;
}


#ifdef SIMULATOR_TESTING
void test_stub_set_config(void)
{
    U8 i;
    usb_end_pt_info_t config_data ;

    /* Configure endpoints */
    for ( i = 0 ; i< g_number_of_endpoints ; i++)
    {
        config_data.end_pt_no           = g_end_pt_info[i].end_pt_no;
        config_data.direction           = g_end_pt_info[i].direction;
        config_data.transfer_type       = g_end_pt_info[i].transfer_type;
        config_data.max_pkt_size        = g_end_pt_info[i].max_pkt_size;

        ipl_set_configuration(&config_data);
    }
}
#endif

