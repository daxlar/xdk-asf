/**
 * \file
 *
 * \brief AVR UC3 IISC drivers
 *
 * Copyright (c) 2010-2018 Microchip Technology Inc. and its subsidiaries.
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
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#ifndef _AVR32_DRIVERS_IISC_H_
#define _AVR32_DRIVERS_IISC_H_

/**
 * \defgroup group_avr32_drivers_iisc IISC - Inter-IC Sound Controller
 *
 * IISC provides a 5-wire, bidirectional, synchronous, digital audio link with off-chip audio devices: ISDI, ISDO, IWS, ISCK and IMCK pins.
 *
 * \{
 */

#include <avr32/io.h>
#include "compiler.h"
#include "status_codes.h"

#define IISC_RETRY_VALUE   10000

//! IISC modes.
enum iisc_mode {
	IISC_MODE_MASTER = 1,
	IISC_MODE_SLAVE,
	IISC_MODE_TDM_MASTER,
	IISC_MODE_TDM_SLAVE
};

/**
 * \brief IISC configuration struct
 */
typedef struct {
	//!  Mode I2S-mode \n
	//!   - \ref IISC_MODE_MASTER Two output channels.\n
	//!   - \ref IISC_MODE_SLAVE Two output channels sampled with an external
	//!   clock received from the RX_CLOCK line.\n
	//!   - \ref IISC_MODE_TDM_MASTER TDM Master Mode.\n
	//!   - \ref IISC_MODE_TDM_SLAVE TDM Slave Mode.\n
	enum iisc_mode mode;

	//!  Option Parameter \n
	//!   - \ref IISC_DATALENGTH \n
	//!   - \ref IISC_OVERSAMPLING \n
	//!   - \ref IISC_TXDMA_MULTIPLE, \ref  IISC_TXDMA_SINGLE, \ref  IISC_RXDMA_MULTIPLE,
	//!     \ref IISC_TXDMA_SINGLE \n
	//!   - \ref IISC_FORMAT_TDM_LJ
	//!   - \ref IISC_FORMAT_LJ
	unsigned int option;

	//!  Number of TX Channels \n
	unsigned int num_tx_channels;

	//!  Number of RX Channels \n
	unsigned int num_rx_channels;
} iisc_opt_t;

/**
 * ! \brief IISC data length configuration macro
 */
#define IISC_DATALENGTH(x) (AVR32_IISC_MR_DATALENGTH##x \
		<< AVR32_IISC_MR_DATALENGTH_OFFSET)
//! @{
//!< Set datalength to 32 bits
#define IISC_DATALENGTH_32  (IISC_DATALENGTH(_32) )
//!< Set datalength to 24 bits
#define IISC_DATALENGTH_24  (IISC_DATALENGTH(_24) )
//!< Set datalength to 20 bits
#define IISC_DATALENGTH_20  (IISC_DATALENGTH(_20) )
//!< Set datalength to 18 bits
#define IISC_DATALENGTH_18  (IISC_DATALENGTH(_18) )
//!< Set datalength to 16 bits
#define IISC_DATALENGTH_16  (IISC_DATALENGTH(_16) )
//!< Set datalength to 16 bits compact stereo (left sample in bits 15 through 0
//! and right samples in bits 31 through 16 of the same word)
#define IISC_DATALENGTH_16C (IISC_DATALENGTH(_16C))
//!< Set datalength to 8 bits
#define IISC_DATALENGTH_8   (IISC_DATALENGTH(_8 ) )
//!< Set datalength to 8 bits compact stereo (left sample in bits 7 through 0
//! and right samples in bits 15 through 8 of the same word)
#define IISC_DATALENGTH_8C  (IISC_DATALENGTH(_8C) )
//! @}

/*! \name IISC oversampling frequency
 */
#define IISC_OVERSAMPLING(x) (AVR32_IISC_MR_IMCKFS##x \
		<< AVR32_IISC_MR_IMCKFS_OFFSET)
//! @{
#define IISC_OVERSAMPLING_x16   (IISC_OVERSAMPLING(_16)  )    //!< x16
#define IISC_OVERSAMPLING_x32   (IISC_OVERSAMPLING(_32)  )    //!< x32
#define IISC_OVERSAMPLING_x64   (IISC_OVERSAMPLING(_64)  )    //!< x64
#define IISC_OVERSAMPLING_x128  (IISC_OVERSAMPLING(_128) )    //!< x128
#define IISC_OVERSAMPLING_x256  (IISC_OVERSAMPLING(_256) )    //!< x256
#define IISC_OVERSAMPLING_x384  (IISC_OVERSAMPLING(_384) )    //!< x384
#define IISC_OVERSAMPLING_x512  (IISC_OVERSAMPLING(_512) )    //!< x512
#define IISC_OVERSAMPLING_x768  (IISC_OVERSAMPLING(_768) )    //!< x768
#define IISC_OVERSAMPLING_x1024 (IISC_OVERSAMPLING(_1024))    //!< x1024
//! @}

/*! \name IISC dma configuration
 */
#define IISC_TXDMA_MULTIPLE  (AVR32_IISC_MR_TXDMA_MULTIPLE << \
		AVR32_IISC_MR_TXDMA_OFFSET)
#define IISC_TXDMA_SINGLE    (AVR32_IISC_MR_TXDMA_SINGLE << \
		AVR32_IISC_MR_TXDMA_OFFSET)
#define IISC_RXDMA_MULTIPLE  (AVR32_IISC_MR_RXDMA_MULTIPLE << \
		AVR32_IISC_MR_RXDMA_OFFSET)
#define IISC_RXDMA_SINGLE    (AVR32_IISC_MR_RXDMA_SINGLE << \
		AVR32_IISC_MR_RXDMA_OFFSET)
//! @}

/*! \name IISC Format Configuration
 */
#define IISC_FORMAT_LJ          AVR32_IISC_MR_FORMAT_LJ
#define IISC_FORMAT_TDM_LJ      AVR32_IISC_MR_FORMAT_TDM_LJ
//! @}

/*! \brief Resets the IISC module
 *
 *  \param iisc pointer to the correct volatile avr32_iisc_t struct
 */
static inline void iisc_reset(volatile avr32_iisc_t *iisc)
{
	iisc->cr = AVR32_IISC_SWRST_MASK;
}

/*! \brief Enable the IISC module in transmission
 *
 *  \param iisc pointer to the correct volatile avr32_iisc_t struct
 */
static inline void iisc_enable_transmission(volatile avr32_iisc_t *iisc)
{
	iisc->cr = AVR32_IISC_CR_TXEN_MASK;
}

/*! \brief Disable the IISC module in transmission
 *
 *  \param iisc pointer to the correct volatile avr32_iisc_t struct
 */
static inline void iisc_disable_transmission(volatile avr32_iisc_t *iisc)
{
	iisc->cr = AVR32_IISC_CR_TXDIS_MASK;
}

/*! \brief Enable the IISC module in reception
 *
 *  \param iisc pointer to the correct volatile avr32_iisc_t struct
 */
static inline void iisc_enable_reception(volatile avr32_iisc_t *iisc)
{
	iisc->cr = AVR32_IISC_CR_RXEN_MASK;
}

/*! \brief Disable the IISC module in reception
 *
 *  \param iisc pointer to the correct volatile avr32_iisc_t struct
 */
static inline void iisc_disable_reception(volatile avr32_iisc_t *iisc)
{
	iisc->cr = AVR32_IISC_CR_RXDIS_MASK;
}

/*! \brief Enable the clocks for the IISC module
 *
 *  \param iisc pointer to the correct volatile avr32_iisc_t struct
 */
static inline void iisc_enable_clocks(volatile avr32_iisc_t *iisc)
{
	iisc->cr = AVR32_IISC_CKEN_MASK;
}

/*! \brief Disable the clocks for the IISC module
 *
 *  \param iisc pointer to the correct volatile avr32_iisc_t struct
 */
static inline void iisc_disable_clocks(volatile avr32_iisc_t *iisc)
{
	iisc->cr = AVR32_IISC_CKDIS_MASK;
}

void iisc_enable(volatile avr32_iisc_t *iisc);

void iisc_disable(volatile avr32_iisc_t *iisc);

status_code_t iisc_init(volatile avr32_iisc_t *iisc, iisc_opt_t iisc_opt);

status_code_t iisc_write(volatile avr32_iisc_t *iisc, uint32_t data);

status_code_t iisc_read(volatile avr32_iisc_t *iisc, uint32_t *data);

void iisc_disable_interrupts(volatile avr32_iisc_t *iisc,
		unsigned long int_mask);

void iisc_enable_interrupts(volatile avr32_iisc_t *iisc,
		unsigned long int_mask);

unsigned long iisc_get_status(volatile avr32_iisc_t *iisc);

/**
 * \}
 */

#endif // _AVR32_DRIVERS_IISC_H_
