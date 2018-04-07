// Initfile file -- to be edit

// Initialize Everything (PORT A, C, and F)
// Port A: USB UART usage
// Port C: Comm between boards
// Port F: LED lights
void UARTandGPIO_Init(void){
  SYSCTL_RCGCUART_R |= 0x03;            // activate UART0 and 1
  SYSCTL_RCGCGPIO_R |= 0x25;            // activate port A, C, and F
  while((SYSCTL_PRUART_R&0x03) == 0){}; // Wait for UARTs to be ready
  while((SYSCTL_PRGPIO_R&0x25) == 0){}; // Wait for GPIOs to be ready
  
  
  // ------------------------------------------------------------------Setup UART0
  UART0_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
  UART0_IBRD_R = 325;                   // IBRD = int(50,000,000 / (16 * 9600)) = int(325.521)
  UART0_FBRD_R = 33;                    // FBRD = int(0.521) = 33
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART0_CTL_R |= UART_CTL_UARTEN;       // enable UART
  GPIO_PORTA_AFSEL_R |= 0x03;           // enable alt funct on PA1-0
  GPIO_PORTA_DEN_R |= 0x03;             // enable digital I/O on PA1-0
                                        // configure PA1-0 as UART
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFFF0)+0x00000001;
  GPIO_PORTA_AMSEL_R &= ~0x03;          // disable analog functionality on PA
  
  
  // ------------------------------------------------------------------Setup UART1
  UART1_CTL_R &= ~UART_CTL_UARTEN;      // disable UART1
  UART1_IBRD_R = 325;                   // IBRD = int(50,000,000 / (16 * 9600)) = int(325.521)
  UART1_FBRD_R = 33;                    // FBRD = int(0.521) = 33
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART1_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART1_CTL_R |= UART_CTL_UARTEN;       // enable UART
  GPIO_PORTC_AFSEL_R |= 0x03;           // enable alt funct on PC4-5
  GPIO_PORTC_DEN_R |= 0x03;             // enable digital I/O on PC4-5
                                        // configure PA1-0 as UART
  GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFFFFFFF0)+0x00000011;
  GPIO_PORTC_AMSEL_R &= ~0x03;          // disable analog functionality on PA
  
  
  // ------------------------------------------------------------------Setup PortF
  GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;    // Allow input
  GPIO_PORTF_CR_R = 0x1F;               // Commit input
  GPIO_PORTF_AFSEL_R = 0;
  GPIO_PORTF_AMSEL_R = 0;
  GPIO_PORTF_PCTL_R = 0;
  GPIO_PORTF_DIR_R = 0x0E;              // set bits for LEDs Output
  GPIO_PORTF_PUR_R = 0x11;              // Pull up bits 0, 4 for input (Switches)
  GPIO_PORTF_DEN_R = 0x1F;              // Enable all for I/O
  
}
