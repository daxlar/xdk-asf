/**************************************************************************
 *
 * \file
 *
 * \brief Header file of the USB mass-storage example.
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 ***************************************************************************/
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */


#ifndef _MASS_STORAGE_EXAMPLE_H_
#define _MASS_STORAGE_EXAMPLE_H_


//_____ I N C L U D E S ____________________________________________________

#include "pm.h"


//_____ D E F I N I T I O N S ______________________________________________

#define APPLI_CPU_SPEED   66000000
#define APPLI_PBA_SPEED   66000000

/*! \name USART Used for STDIO
 */
//! @{
#define STDIO_USART                   DBG_USART
#define STDIO_USART_RX_PIN            DBG_USART_RX_PIN
#define STDIO_USART_RX_FUNCTION       DBG_USART_RX_FUNCTION
#define STDIO_USART_TX_PIN            DBG_USART_TX_PIN
#define STDIO_USART_TX_FUNCTION       DBG_USART_TX_FUNCTION
#define STDIO_USART_IRQ               AVR32_USART0_IRQ
#define STDIO_USART_BAUDRATE          DBG_USART_BAUDRATE
//! @}


//_____ M A C R O S ________________________________________________________


//_____ D E C L A R A T I O N S ____________________________________________

extern pm_freq_param_t pm_freq_param;


#endif  // _MASS_STORAGE_EXAMPLE_H_
