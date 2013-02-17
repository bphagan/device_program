/*****************************************************************************
Copyright 2008 Freescale Semiconductor, Inc. All Rights Reserved.

This file contains copyrighted material. Use of this file is
restricted by the provisions of a Freescale Software License
Agreement, which has either been electronically accepted by
you or has been expressly executed between the parties.
 *****************************************************************************/

/*
 *  DESCRIPTION:
 *      The su_basictypes.h header file contains constants and basic types
 *      that are described in the user guide and reference manual. 
 */

/************** REVISION HISTORY **********************************************

 *****************************************************************************/

#ifndef SU_BASICTYPES_H
#define SU_BASICTYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/************** HEADER FILE INCLUDES *****************************************/


/************** CONSTANTS ****************************************************/

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/************** STRUCTURES, ENUMS, AND TYPEDEFS ******************************/

/* Basic Types defined in the SUAPI User and Reference Manual, Appendix B */

typedef signed char INT8;
typedef unsigned char UINT8;
typedef short int INT16;
typedef unsigned short int UINT16;
typedef int INT32;
typedef unsigned int UINT32;


typedef UINT8           U8;         /* unsigned 8 bit data  */
typedef UINT16          U16;        /* unsigned 16 bit data */
typedef UINT32          U32;        /* unsigned 32 bit data */
typedef INT8            S8;         /* signed 8 bit data  */
typedef INT16           S16;        /* signed 16 bit data */
typedef INT32           S32;        /* signed 32 bit data */


typedef U8*             P_U8;           /* unsigned 8 bit data  */
typedef volatile U8*    VP_U8;
typedef U16*            P_U16;          /* unsigned 16 bit data */
typedef volatile U16*   VP_U16;
typedef U32*            P_U32;          /* unsigned 32 bit data */
typedef volatile U32*   VP_U32; /* volatile unsigned 32 bit data */
typedef S8*             P_S8;           /* signed 8 bit data  */
typedef S16*            P_S16;          /* signed 16 bit data */
typedef S32*            P_S32;          /* signed 32 bit data */


/* The typedefs for INT64 and UINT64 have been ifdefed because Microsoft
 * Visual C++ doesn't define "long long" as a type.
 */

#ifdef _WIN32

/* VC++ compiler does not allow long long */
typedef __int64 INT64;
typedef unsigned __int64 UINT64;

/*
 * BOOL is defined in the VC++ MFC as int. In
 * order to allow compilation, we make it the same here.
 * Beware of incompatibilities between VC++ compiled objects
 * and objects compiled with other compilers.
 */
typedef int BOOL; 

#ifndef BOOLEAN
typedef unsigned char BOOLEAN;
#endif

#else

typedef long long int INT64;
typedef unsigned long long int UINT64;

typedef unsigned char BOOL;
typedef unsigned char BOOLEAN;

#endif /* _WIN32 */

/************** FUNCTION PROTOTYPES ******************************************/

/************** CLASS DEFINITIONS ********************************************/

/************** GLOBAL VARIABLES *********************************************/
#ifdef __cplusplus
}
#endif
#endif

