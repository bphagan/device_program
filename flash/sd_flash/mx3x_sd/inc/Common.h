/******************************************************************************

 C   H E A D E R   F I L E

 (c) Copyright Motorola Semiconductors Hong Kong Limited 2000-2001
 ALL RIGHTS RESERVED

*******************************************************************************

 Project Name : DBMX1 System Test Program
 Project No.  : 
 Title        : 
 File Name    : Common.h    
 Last Modified: Nov 6, 2001

 Description  : Public data type

 Assumptions  : 
 
 Dependency Comments :

 Project Specific Data :

******************************************************************************/
#include "define.h"

#ifndef COMMON_TYPES_INC
#define COMMON_TYPES_INC


/*****************************Marcos******************************************/
#define TRUE 1
#define FALSE 0
/*************************** Header File Includes ****************************/
/********************************* Constants *********************************/
/******************************** Enumeration ********************************/
/****************************** Basic Data types *****************************/

/* Typedefs for integer types */
typedef unsigned char   U8;     /* unsigned 8 bit data  */
typedef unsigned short  U16;    /* unsigned 16 bit data */
typedef unsigned int    U32;    /* unsigned 32 bit data */
typedef unsigned int    UINT32;    /* unsigned 32 bit data */
typedef char        S8;         /* signed 8 bit data  */
typedef short       S16;        /* signed 16 bit data */
typedef int         S32;        /* signed 32 bit data */

typedef U8 *    P_U8;           /* unsigned 8 bit data  */
typedef volatile U8 * VP_U8;
typedef U16 *   P_U16;          /* unsigned 16 bit data */
typedef volatile U16 * VP_U16;
typedef U32 *   P_U32;          /* unsigned 32 bit data */
typedef volatile U32 * VP_U32;	/* volatile unsigned 32 bit data */
typedef S8 *    P_S8;           /* signed 8 bit data  */
typedef S16 *   P_S16;          /* signed 16 bit data */
typedef S32 *   P_S32;          /* signed 32 bit data */

typedef U16     TEXT;           /* 16-bit text data */
typedef P_U16   P_TEXT;         /* 16-bit text data */

typedef U8  BOOL;               /* Boolean, TRUE/FALSE */

typedef void    VOID;           /* void */
typedef void *  P_VOID;         /* pointer to void */

typedef unsigned char UINT8;     /* unsigned 8 bit data  */
typedef unsigned short  UINT16;    /* unsigned 16 bit data */
/************************* Structure/Union Data types ************************/

typedef U16 STATUS;

/*  point structure  */
typedef struct
{
    U16 x;      /*  x point  */
    U16 y;      /*  y point  */
} POINT, *P_POINT;

/*  area structure  */
typedef struct  
{
    POINT   top;        /*  Top left corner  */
    POINT   bottom;     /*  Bottom right corner  */
} AREA, *P_AREA;


/********************************** Macros ***********************************/
/*************************** Function prototype (S) **************************/
#ifdef DEBUG
#define debugprintf printf
#else
#define debugprintf 
#endif


#endif
