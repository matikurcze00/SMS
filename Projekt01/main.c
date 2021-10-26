/* ***************************************
* projekt01 : konfiguracja zegarow *
*************************************** */
# include "stm32f10x.h"
# include <stdbool.h > // true , false
# define DELAY_TIME 8000000
bool RCC_Config ( void ) ;
void GPIO_Config ( void ) ;
void LEDOn ( void ) ;
void LEDOff ( void ) ;
void Delay ( unsigned int) ;

int main ( void ) {
	RCC_Config () ; // konfiguracja RCC
	GPIO_Config () ; // konfiguracja GPIO
	
	while (1) { // petla glowna programu
		LEDOn () ; // wlaczenie diody
		Delay ( DELAY_TIME ) ; // odczekanie 1s
		LEDOff () ; // wylaczenie diody
		Delay ( DELAY_TIME ) ; // odczekanie 1s
		}
}

bool RCC_Config ( void ) {
ErrorStatus HSEStartUpStatus ; // zmienna opisujaca rezultat
// uruchomienia HSE
// konfigurowanie sygnalow taktujacych
RCC_DeInit () ; // reset ustawie n RCC
RCC_HSEConfig ( RCC_HSE_ON ) ; // wlacz HSE
HSEStartUpStatus = RCC_WaitForHSEStartUp () ; // czekaj na gotowosc HSE
if( HSEStartUpStatus == SUCCESS ) {
FLASH_PrefetchBufferCmd ( FLASH_PrefetchBuffer_Enable ) ;//
FLASH_SetLatency ( FLASH_Latency_2 ) ; // zwloka Flasha : 2 takty
RCC_HCLKConfig ( RCC_SYSCLK_Div1 ) ; // HCLK = SYSCLK /1
RCC_PCLK2Config ( RCC_HCLK_Div1 ) ; // PCLK2 = HCLK /1
RCC_PCLK1Config ( RCC_HCLK_Div2 ) ; // PCLK1 = HCLK /2
RCC_PLLConfig ( RCC_PLLSource_HSE_Div1 , RCC_PLLMul_9 ) ; // PLLCLK = ( HSE /1) *9
// czyli 8 MHz * 9 = 72 MHz
RCC_PLLCmd ( ENABLE ) ; // wlacz PLL
while ( RCC_GetFlagStatus ( RCC_FLAG_PLLRDY ) == RESET ) ; // czekaj na uruchomienie PLL
RCC_SYSCLKConfig ( RCC_SYSCLKSource_PLLCLK ) ; // ustaw PLL jako zrodlo
// sygnalu zegarowego
while ( RCC_GetSYSCLKSource () != 0x08) ; // czekaj az PLL bedzie
// sygnalem zegarowym systemu
// konfiguracja sygnalow taktujacych uzywanych peryferii
RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOA , ENABLE ) ;// wlacz taktowanie portu GPIO A
RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOB , ENABLE ) ;// wlacz taktowanie portu GPIO B
return true ;
}
return false ;
}
void GPIO_Config ( void ) {
// konfigurowanie portow GPIO
GPIO_InitTypeDef GPIO_InitStructure ;
GPIO_InitStructure . GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 ; // pin 8 i 9
GPIO_InitStructure . GPIO_Speed = GPIO_Speed_2MHz ; // czestotliwosc zmiany 2 MHz
GPIO_InitStructure . GPIO_Mode = GPIO_Mode_Out_PP ; // wyjscie w trybie push - pull
GPIO_Init (GPIOB , & GPIO_InitStructure ) ; // inicjaliacja portu B
GPIO_InitStructure . GPIO_Pin = GPIO_Pin_0 ;
GPIO_InitStructure . GPIO_Mode = GPIO_Mode_IN_FLOATING ; // wejscie w trybie pull -up
GPIO_Init (GPIOA , & GPIO_InitStructure ) ;
}

void LEDOn ( void ) {
// wlaczenie diody LED podlaczonej do pinu 8 portu B
GPIO_WriteBit (GPIOB , GPIO_Pin_8 , Bit_SET ) ;
}

void LEDOff ( void ) {
// wylaczenie diody LED podlaczonej do pinu 8 portu B
GPIO_WriteBit (GPIOB , GPIO_Pin_8 , Bit_RESET ) ;
}

void Delay ( unsigned int counter ) {
// opoznienie programowe
while ( counter--) { // sprawdzenie warunku
__NOP () ; // No Operation
__NOP () ; // No Operation
}
}

