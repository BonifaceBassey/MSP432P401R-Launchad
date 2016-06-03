#include "drivers/inc/msp.h"

/* DriverLib Includes */
#include "drivers/driverlib/MSP432P4xx/driverlib.h"

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

const eUSCI_UART_Config uartConfig =
{
    EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
    78,                                      // BRDIV = 78
    2,                                       // UCxBRF = 2
    0,                                       // UCxBRS = 0
    EUSCI_A_UART_NO_PARITY,                  // No Parity
    EUSCI_A_UART_LSB_FIRST,                  // MSB First
    EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
    EUSCI_A_UART_MODE,                       // UART mode
    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
};


int main(void)
{
    /* Halting WDT  */
    WDT_A_holdTimer();
    /* Halting WDT and disabling master interrupts */
    //WDTCTL = WDTPW | WDTHOLD;                 // Stop WDT

    /* Configure pins P1.2 and P1.3 in UART mode.
     * Doesn't matter if they are set to inputs or outputs
     */
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
                GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Setting DCO (clock) to 12MHz */
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_12);

    /* Configuring UART Module */
    UART_initModule(EUSCI_A0_BASE, &uartConfig);

    /* Enable UART module */
    UART_enableModule(EUSCI_A0_BASE);

    /*Enable UART interrupt */
    UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    Interrupt_enableInterrupt(INT_EUSCIA0);
	Interrupt_enableMaster();

    /* Send the 'c' character over UART */
    UART_transmitData(EUSCI_A2_BASE, 'c');

    while(1)
    {
       MAP_PCM_gotoLPM0();
    }
}


//USCIA0 interrupt handler.
void EUSCIA0_IRQHandler(void)
{
    int receiveByte = UCA0RXBUF;

    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0); 
    UART_transmitData(EUSCI_A0_BASE, receiveByte);	// Echo back.
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

}

