/**
* \file
* \brief This file describes all the standard timer measurement features (precision is 10ms).
*
* \author ------------------------------------------------------------------------------\n
* \author INGENICO Technical Software Department\n
* \author ------------------------------------------------------------------------------\n
* \author Copyright (c) 2009 - 2014 INGENICO.\n
* \author 28-32 boulevard de Grenelle 75015 Paris, France.\n
* \author All rights reserved.\n
* \author This source program is the property of the INGENICO Company mentioned above\n
* \author and may not be copied in any form or by any means, whether in part or in whole,\n
* \author except under license expressly granted by such INGENICO company.\n
* \author All copies of this source program, whether in part or in whole, and\n
* \author whether modified or not, must display this and all other\n
* \author embedded copyright and ownership notices in full.\n
**/

#ifndef __GTL_STDTIMER_H__INCLUDED__
#define __GTL_STDTIMER_H__INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

//! \addtogroup StdTimersDefines
//! @{

#define TIMER_STD_INFINITE			0x7fffffff		/*!< Infinite timeout value. */

//! @}


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \addtogroup StdTimersFunctions
//! @{

//! \brief Get the tick value.
//! \return The tick value.

unsigned long GTL_StdTimer_GetCurrent (void);



//! \brief Get the elapsed time.
//! \param[in] ulStartTime The tick value for the starting time.
//! \return The elapsed number of ticks.

unsigned long GTL_StdTimer_GetElapsed (const unsigned long ulStartTime);



//! \brief Get the remaining time of a timeout.
//! \param[in] ulStartTime The tick value for the starting time.
//! \param[in] nTimeout The timeout value. Use \ref TIMER_STD_INFINITE for an infinite timeout.
//! \return The remaining number of ticks. 0 if the timeout has expired.

unsigned long GTL_StdTimer_GetRemaining (const unsigned long ulStartTime, const unsigned int nTimeout);

//! @}

#ifdef __cplusplus
}
#endif

#endif
