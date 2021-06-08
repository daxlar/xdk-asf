/*****************************************************************************
 *
 * \file
 *
 * \brief PDCA driver for AVR32 UC3.
 *
 * This file defines a useful set of functions for the PDCA interface on AVR32
 * devices.
 *
 * Copyright (c) 2009-2018 Microchip Technology Inc. and its subsidiaries.
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
 ******************************************************************************/
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef _PDCA_H_
#define _PDCA_H_

/**
 * \defgroup group_avr32_drivers_pdca UC3 Peripheral DMA Controller
 *
 * The Peripheral DMA controller (PDCA) transfers data between on-chip
 * peripheral modules such as USART, SPI, SSC and on- and off-chip memories.
 *
 * @{
 */

#include <avr32/io.h>
#include <stdint.h>
#include <stdbool.h>

/** Size of PDCA transfer: byte. */
#define PDCA_TRANSFER_SIZE_BYTE               AVR32_PDCA_BYTE

/** Size of PDCA transfer: half-word. */
#define PDCA_TRANSFER_SIZE_HALF_WORD          AVR32_PDCA_HALF_WORD

/** Size of PDCA transfer: word. */
#define PDCA_TRANSFER_SIZE_WORD               AVR32_PDCA_WORD

/** \name PDCA Driver Status Codes
 */
/** @{ */
#define PDCA_SUCCESS 0
#define PDCA_INVALID_ARGUMENT -1
/** @} */

/** \name PDCA Transfer Status Codes
 */
/** @{ */
#define PDCA_TRANSFER_ERROR                   AVR32_PDCA_TERR_MASK
#define PDCA_TRANSFER_COMPLETE                AVR32_PDCA_TRC_MASK
#define PDCA_TRANSFER_COUNTER_RELOAD_IS_ZERO  AVR32_PDCA_RCZ_MASK
/** @} */

/** PDCA channel options. */
typedef struct {
	/** Memory address. */
	volatile void *addr;
	/** Transfer counter. */
	uint32_t size;
	/** Next memory address. */
	volatile void *r_addr;
	/** Next transfer counter. */
	uint32_t r_size;
	/** Select peripheral ID. */
	uint32_t pid;
	/** Select the size of the transfer (byte, half-word or word). */
	uint32_t transfer_size;
#if (AVR32_PDCA_H_VERSION >= 120)
	/* Note: the options in this preprocessor section are only available
	 * from the PDCA IP version 1.2.0 on. */
	/** Enable (\c 1) or disable (\c 0) the transfer upon event trigger. */
	bool etrig;
#endif
} pdca_channel_options_t;

/** \brief Get PDCA channel handler
 *
 * \param pdca_ch_number  PDCA channel
 *
 * \return channel handled or PDCA_INVALID_ARGUMENT
 */
volatile avr32_pdca_channel_t *pdca_get_handler(
		uint8_t pdca_ch_number);

/** \brief Set the channel configuration
 *
 * \param pdca_ch_number PDCA channel
 * \param opt channel option
 */
uint32_t pdca_init_channel(uint8_t pdca_ch_number,
		const pdca_channel_options_t *opt);

/** \brief Get the PDCA channel transfer enable status
 *
 * \param pdca_ch_number PDCA channel
 *
 * \return \c true if channel transfer is enabled, else \c false
 */
bool pdca_get_channel_status(uint8_t pdca_ch_number);

/** \brief Disable the PDCA for the given channel
 *
 * \param pdca_ch_number PDCA channel
 */
void pdca_disable(uint8_t pdca_ch_number);

/** \brief Enable the PDCA for the given channel
 *
 * \param pdca_ch_number PDCA channel
 */
void pdca_enable(uint8_t pdca_ch_number);

/** \brief Get PDCA channel load size (or remaining size if transfer started)
 *
 * \param pdca_ch_number PDCA channel
 *
 * \return size           current size to transfer
 */
uint32_t pdca_get_load_size(uint8_t pdca_ch_number);

/** \brief Set PDCA channel load values
 *
 * \param pdca_ch_number PDCA channel
 * \param addr           address where data to load are stored
 * \param size           size of the data block to load
 */
void pdca_load_channel(uint8_t pdca_ch_number, volatile void *addr,
		uint32_t size);

/** \brief Get PDCA channel reload size
 *
 * \param pdca_ch_number PDCA channel
 *
 * \return size           current reload size
 */
uint32_t pdca_get_reload_size(uint8_t pdca_ch_number);

/** \brief Set PDCA channel reload values
 *
 * \param pdca_ch_number PDCA channel
 * \param addr           address where data to load are stored
 * \param size           size of the data block to load
 */
void pdca_reload_channel(uint8_t pdca_ch_number,
		volatile void *addr, uint32_t size);

/** \brief Set the peripheral function to use with the PDCA channel
 *
 * \param pdca_ch_number PDCA channel
 * \param pid the peripheral ID
 */
void pdca_set_peripheral_select(uint8_t pdca_ch_number,
		uint32_t pid);

/** \brief Set the size of the transfer
 *
 * \param pdca_ch_number PDCA channel
 * \param transfer_size size of the transfer (byte, half-word or word)
 */
void pdca_set_transfer_size(uint8_t pdca_ch_number,
		uint32_t transfer_size);

#if (AVR32_PDCA_H_VERSION >= 120)
/* Note: the functions in this preprocessor section are only available from the
 * PDCA IP version 1.2.0 on. */

/** \brief Disable the event-triggered transfer feature
 *
 * \param pdca_ch_number PDCA channel
 */
void pdca_disable_event_trigger(uint8_t pdca_ch_number);

/** \brief Enable the event-triggered transfer feature
 *
 * \param pdca_ch_number PDCA channel
 */
void pdca_enable_event_trigger(uint8_t pdca_ch_number);
#endif

/** \brief Disable PDCA transfer error interrupt
 *
 * \param pdca_ch_number PDCA channel
 */
void pdca_disable_interrupt_transfer_error(uint8_t pdca_ch_number);

/** \brief Enable PDCA transfer error interrupt
 *
 * \param pdca_ch_number PDCA channel
 */
void pdca_enable_interrupt_transfer_error(uint8_t pdca_ch_number);

/** \brief Disable PDCA transfer interrupt when completed (ie TCR and TCRR are
 * both zero)
 *
 * \param pdca_ch_number PDCA channel
 */
void pdca_disable_interrupt_transfer_complete(uint8_t pdca_ch_number);

/** \brief Enable PDCA transfer interrupt when completed (ie TCR and TCRR are
 * both zero)
 *
 * \param pdca_ch_number PDCA channel
 */
void pdca_enable_interrupt_transfer_complete(uint8_t pdca_ch_number);

/** \brief Disable PDCA transfer interrupt when TCRR reaches zero
 *
 * \param pdca_ch_number PDCA channel
 */
void pdca_disable_interrupt_reload_counter_zero(
		uint8_t pdca_ch_number);

/** \brief Enable PDCA transfer interrupt when TCRR reaches zero
 *
 * \param pdca_ch_number PDCA channel
 */
void pdca_enable_interrupt_reload_counter_zero(
		uint8_t pdca_ch_number);

/** \brief Get PDCA channel transfer status
 *
 * \param pdca_ch_number PDCA channel
 *
 * \return PDCA transfer status with the following bit-masks:\n
 *           - \c PDCA_TRANSFER_ERROR;\n
 *           - \c PDCA_TRANSFER_COMPLETE;\n
 *           - \c PDCA_TRANSFER_COUNTER_RELOAD_IS_ZERO.
 */
uint32_t pdca_get_transfer_status(uint8_t pdca_ch_number);

/** @} */

#endif  /* _PDCA_H_ */