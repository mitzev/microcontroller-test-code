//=========================================================
// src/Interrupts.c: generated by Hardware Configurator
//
// This file will be regenerated when saving a document.
// leave the sections inside the "$[...]" comment tags alone
// or they will be overwritten!!
//=========================================================

// USER INCLUDES
#include <SI_EFM8LB1_Register_Enums.h>

xdata uint8_t buffer[513];
uint8_t address = 1;
int16_t bufferIndex = -1;

//-----------------------------------------------------------------------------
// UART1_ISR
//-----------------------------------------------------------------------------
//
// UART1 ISR Content goes here. Remember to clear flag bits:
// SCON1::RI (Receive Interrupt Flag)
// SCON1::TI (Transmit Interrupt Flag)
// UART1FCN1::RFRQ (Receive FIFO Request)
// UART1FCN1::TFRQ (Transmit FIFO Request)
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (UART1_ISR, UART1_IRQn)
{
	uint8_t temp;
//	P0_B6 = 1;
	if(SCON1_RBX == 0)
	{
		// break
//		P0_B0 = 1;
		bufferIndex = 0;
//		P0_B0 = 0;
	}

	while(SCON1_RI)
	{
		temp = SBUF1;

		if(bufferIndex >= 0) {
			buffer[bufferIndex++] = temp;
		}

		if(bufferIndex > 512)
		{
//			P0_B7 = 1;
			SFRPAGE = 0x00; // our ISR will be called w/ SFRPAGE = 0x20
			PCA0CPH0 = buffer[address+0];
			PCA0CPH1 = buffer[address+1];
			PCA0CPH2 = buffer[address+2];
			bufferIndex = -1;
			SFRPAGE = 0x20;
//			P0_B7 = 0;
		}
	}

//	P0_B6 = 0;
}

