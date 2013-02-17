/*****************************************************************************
 *                                                                           *
 *  (c) Copyright Motorola 1998-2001, All rights reserved.                   *
 *  Motorola Confidential Proprietary                                        *
 *  Contains confidential proprietary information of Motorola, Inc.          *
 *  Reverse engineering is prohibited.                                       *
 *  The copyright notice does not imply publication.                         *
 *                                                                           *
 *****************************************************************************/

/*
 *  DESCRIPTION:
 *      The suapi.h header file contains constants, structures, enums,
 *  typedefs, function prototypes, class definitions, and global
 *  variable external references that comprise the user interface to SUAPI.
 */
 
/************** REVISION HISTORY **********************************************
 *
 * Date         Author      Reference
 * ==========   ========    ==========================
 * 1998-06-30   rclayton    File Prototype
 * 1998-12-04   jjohlas     SUAPI VRTXmc on M.CORE
 * 1999-01-19   jjohlas     Changes from code review
 * 1999-02-01   jjohlas     Changes from inspection
 * 1999-02-09   rclayton    Changed type of SU_SEMA_HANDLE
 * 1999-03-09   rclayton    Removal of UINT32 type (CR 2695)
 * 1999-03-25   epayne      Added #defines for version numbers (CR 2947).
 * 1999-04-01   epayne      Service Hook support (CR 2956).
 * 1999-05-03   honnigse    Mutex semaphore addition (CR 2955).
 * 1999-05-05   rclayton    Remove Heap and Fixed Memory. (CR 3067)
 * 1999-05-06   honnigse    Added suDisableSched and suEnableSched (CR 3102).
 * 1999-05-10   honnigse    Changes from review (CR 3102).
 * 1999-05-26   honnigse    Added SU_TICKS_MAX macro (CR 3288).
 * 1999-05-28   honnigse    Added suTicksToMsec (CR 3289).
 * 1999-05-25   tgraves     Grief changes for Task Services (CR 3542).
 * 1999-06-01   tgraves     Adding new types (CR 3545).
 * 1999-06-03   afay        Changed semaphore functions (CR 3543)
 * 1999-06-04   rclayton    Changes for new mem alloc interface.
 * 1999-06-07   honnigse    Unlimited queue support (CR 3211).
 * 1999-06-15   tgraves     Fix bugs from CR 3288/3289 (CR 3694).
 * 1999-06-15   honnigse    Add prototypes for internal port services (CR 3668)
 * 1999-06-17   honnigse    Port and message handling (CR 3439).
 * 1999-06-17   dvannoy     Change Timer interface (CR 3549).
 * 1999-06-28   tgraves     Changing BSP to PAL (CR 3316).
 * 1999-06-29   afay        Added suGetTimeInTicks (CR 3771)
 * 1999-06-30   pduda       GRiEF changes for Event services (CR 3544). 
 * 1999-07-07   epayne      Change SU_MESSAGE to void * (CR 3757).
 * 1999-07-19   rclayton    Removed SU_ERROR and substituted suError (CR 3947).
 * 1999-07-20   honnigse    Remove nqueuetaskregistrations (CR 3981).
 * 1999-07-23   epayne      Add suGetNumMessagesOnQueue() service (CR 3068).  
 * 1999-07-23   achan       Added missing function prototype to fix compiler
 *                          warning (CR 3920).
 * 1999-07-27   rdubey      Changed SU_VERSION per SUAPI UG&RM2.9 (CR 3948).
 * 1999-08-03   hyang       Added name services (CR 3438).
 * 1999-08-06   rdubey      Added interface for suGetPortIdFromPortHandle 
 *                          (CR 4046).
 * 1999-08-26   achan       Added defines, typedefs, error codes, internal
 *                          function prototypes for low power services (CR4044).
 * 1999-08-27   nhoch       Added stddef.h to includes (CR 4277)
 * 1999-08-30   jjohlas     Variable and cyclic timers (CR 2800, CR 4361).
 * 1999-08-31   honnigse    Using jump tables to support OnCore ROM (CR 3069).
 * 1999-09-01   nhoch       Split suapi.h into the following headers (CR 4359)
 *              su_error.h, su_event.h, su_int.h, su_memory.h,
 *              su_port, su_queue, su_sema.h, su_task.h, su_timer.h,
 *              su_types.h, su_nameservices.h, su_panic.h.
 * 1999-09-28   achan       Added ff1 prototype to fix compiler warnings -
 *                          should remove when compiler is fixed (CR4027)
 * 1999-10-11   speechu     Fix/Add SU_RTOS defines (CR 4704)
 * 1999-12-08   achan       Fix __ff1 prototype (CR 5465)
 * 1999-12-01   vagarwal    Added su_time.h to the list of header files (CR5254)
 * 1999-11-24   rdubey      Included su_flags.h (CR 4635).
 * 2000-03-08   jjohlas     Included su_panic.h (CR 7025).
 * 2000-04-25   vagarwal    Adding version 2.0 (CR 6471).
 * 2000-07-25   tgraves     Included su_cache.h (CR 8258).
 * 2000-07-20   nhoch       Adding suspend/resume (CR 7816).
 * 2000-07-19   nhoch       Adding atomic ops (CR 7815).
 * 2000-08-28   achan       Add su_misc.h (CR 5438).
 * 2000-10-05   speechu     Added FF0 (CR 9180).
 * 2000-10-10   vagarwal    Moving version related defines to su_version.h 
 *		            (CR 8187).
 * 2001-01-16   vagarwal    Removed SU_TICKS_MAX and SU_TICKS_MIN (CR 10496).
 * 2001-02-01   tgraves     Add su_runlevel.h (CR 7132).
 * 2001-02-20   achan       Fix __ff1() declaration (CR 10860).
 *****************************************************************************/


#ifndef SUAPI_INCLUDE 
#define SUAPI_INCLUDE  

#ifdef __cplusplus
extern "C" {
#endif 

/************** HEADER FILE INCLUDES *****************************************/
#include <stdarg.h>
#include <stddef.h>
#include <limits.h>
#include "su_basictypes.h"

/************** CONSTANTS ****************************************************/

/************** STRUCTURES, ENUMS, AND TYPEDEFS ******************************/

/************** FUNCTION PROTOTYPES ******************************************/

/************** MACRO DEFINITIONS ********************************************/

/************** CLASS DEFINITIONS ********************************************/

/************** GLOBAL VARIABLES *********************************************/

#ifdef __cplusplus
}
#endif
#endif /* SUAPI_INCLUDE */

