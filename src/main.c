/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/



#include "PUF_extraction.h"
#include "hex-loader.h"
#include "present.h"

#define APPLICATION_ADDRESS 0x20000000        //Indirizzo utilizzato dal linker per linkare l'applicazione utente
#define CONFIG_PARAMETERS_ADDRESS 0x08040000
//void SystemClock_Config(void);
void Delay(uint32_t delay);

uint8_t key[352];
uint8_t * helper_data_addr = CONFIG_PARAMETERS_ADDRESS;
uint8_t * helper_data;
//uint8_t hex_file_enc_addr [4];
uint8_t * bin_file_enc_addr = CONFIG_PARAMETERS_ADDRESS+4;
uint8_t * sram_puf_addr     = CONFIG_PARAMETERS_ADDRESS+8;
char * bin_file_enc; // questo indirizzo va aggiustato
uint8_t * sram_puf;
uint8_t * bin_file_size = CONFIG_PARAMETERS_ADDRESS+12;

static char bin_file[15000]; //definizione statica del file binario che verrà poi caricato dalla flash all'indirizzo indicato

int main(void)
{
    //Modifica branch...è solo questo commento
    
	uint32_t length;
    /* Configure the system clock */
    //SystemClock_Config(); <---
    int i = 0;

    //Conversione indirizzo di memoria helper_data
    uint8_t bufferizzo = *helper_data_addr;
    uint8_t bufferizzo1 = *(helper_data_addr+1);
    uint8_t bufferizzo2 = *(helper_data_addr+2);
    uint8_t bufferizzo3 = *(helper_data_addr+3);

    //indirizzo effettivo (in flash) dell'Helper Data
    helper_data = bufferizzo << 24 | bufferizzo1 << 16 | bufferizzo2 << 8 | bufferizzo3;

    //Conversione indirizzo di memoria bin_file codificato
    bufferizzo = *bin_file_enc_addr;
    bufferizzo1 = *(bin_file_enc_addr+1);
    bufferizzo2 = *(bin_file_enc_addr+2);
    bufferizzo3 = *(bin_file_enc_addr+3);

    //indirizzo effettivo (in flash) del bin_file codificato
   bin_file_enc = bufferizzo << 24 | bufferizzo1 << 16 | bufferizzo2 << 8 | bufferizzo3;

   //Conversione indirizzo di memoria da cui prelevare la SRAM PUF
   bufferizzo = *sram_puf_addr;
   bufferizzo1 = *(sram_puf_addr+1);
   bufferizzo2 = *(sram_puf_addr+2);
   bufferizzo3 = *(sram_puf_addr+3);

   //indirizzo effettivo (in ram) dell'SRAM PUF
   sram_puf = bufferizzo << 24 | bufferizzo1 << 16 | bufferizzo2 << 8 | bufferizzo3;

   //estrazione della PUF ed utilizzo dell'Helper Data (anch'esso già precaricato in flash nell'indirizzo ottenuto)
    extractPUFfromMemory((uint8_t*) sram_puf /*0x2001F540*/, helper_data, 2816, key);

    //impostazione hex_size da file di configurazione
    int bin_size = bin_file_size[0]<<8 | bin_file_size[1];

    //impostare keylow e keyghigh
    uint64_t keylow;
    uint64_t keyhigh;

    for(i=0;i<8;i++)
	{
		keylow = (keylow << 8) | key[i];
		keyhigh = (keyhigh << 8) | key[i+8];
	}

    // Trasferimento file binario (codificato) da flash a ram
    memcpy(bin_file,bin_file_enc,sizeof(uint8_t)*bin_size);


    // Decrypt del file binario con la chiave estratta.
    for(i=0;i<(sizeof(bin_file)/8);i++)  present_decode((uint64_t*)(bin_file+i*8),keylow,keyhigh);


    uint8_t* binImage = (uint8_t*) APPLICATION_ADDRESS;
	 for (i = 0; i < sizeof(bin_file); i++)
		 (*(binImage + i)) = bin_file[i];

	 typedef void (*pFunction)(void);


	 pFunction appEntry;
	 uint32_t appStack;

	 /* Get the application stack pointer (First entry in the application vector table) */
	 appStack = (uint32_t) *((__IO uint32_t*)APPLICATION_ADDRESS);

	 /* Get the application entry point (Second entry in the application vector table) */
	 appEntry = (pFunction) *(__IO uint32_t*) (APPLICATION_ADDRESS + 4);

	 /* Reconfigure vector table offset register to match the application location */
	 SCB->VTOR = APPLICATION_ADDRESS;

	 /* Set the application stack pointer */
	 __set_MSP(appStack);

	 /* Start the application */
	 appEntry();


}


void Delay(uint32_t delay) {
	while (delay--);
}
/* System Clock Configuration

void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

  HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_PLLCLK, RCC_MCODIV_2);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  // SysTick_IRQn interrupt configuration
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}
*/
