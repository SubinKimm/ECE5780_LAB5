/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();


RCC->AHBENR |= RCC_AHBENR_GPIOCEN; // GPIOC Enable
RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // GPIOB Enable

//GPIO_InitTypeDef initStr = {GPIO_PIN_11 | GPIO_PIN_13,
//GPIO_MODE_AF_PP,
//GPIO_SPEED_FREQ_LOW,
//GPIO_NOPULL};
//HAL_GPIO_Init(GPIOB, &initStr); // Initialize pins PB11, PB13

GPIO_InitTypeDef initStr = { GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9,
GPIO_MODE_OUTPUT_PP,
GPIO_SPEED_FREQ_LOW,
GPIO_NOPULL};
HAL_GPIO_Init(GPIOC, &initStr); // Initialize pins PC6, PC7, PC8, PC9

// PB11
GPIOB->MODER |= (2 << 22);          // AF mode 
GPIOB->OTYPER |= (1 << 11);         //open-drain output
GPIOB->AFR[1] |= (1 << 12); //I2C2_SDA AF mode

// PB13
GPIOB->MODER |= (2 << 26);  // AF mode 
GPIOB->OTYPER |= (1 << 13); //open-drain output 
GPIOB->AFR[1] |= (5 << 20); // I2C2_SCL AF mode 

// PB14
GPIOB->MODER |= (1 << 28);  // output mode 
GPIOB->OTYPER &= ~(1 << 14); // push-pulloutput
GPIOB->ODR |= (1 << 14); // pin high

//PC0
GPIOC->MODER |= (1 << 0); // output
GPIOC->OTYPER &= ~(1 << 0); // push-pulloutput
GPIOC->ODR |= (1 << 0); // pin high


RCC->APB1ENR |= RCC_APB1ENR_I2C2EN; // Enable the I2C2 peripheral

I2C2->TIMINGR |= (1 << 28); // PSC // Configuration
I2C2->TIMINGR |= (0x4 << 20); // SCLDEL
I2C2->TIMINGR |= (0x2 << 16); // SDADEL
I2C2->TIMINGR |= (0xF << 8); // SCLH
I2C2->TIMINGR |= (0x13 << 0); // SCLL

I2C2->CR1 |= (1 << 0);


volatile int done = 0;

//////////////////////////////////////////////////////////////////////////////////////////
//// Set L3GD20
//I2C2->CR2 |= (0x69 << 1); // set the S3GD20 slave address
//I2C2->CR2 |= (1 << 16); // transmit = 1
//I2C2->CR2 &= ~(1 << 10); // set the RD_WRN bit to indicate a write operation
//I2C2->CR2 |= (1 << 13); // set the start bit








//	
//  while (1) // Wait TXIS flag is set
//  {
//		if((I2C_ISR_NACKF & I2C_ISR_TXIS) == 0) 
//		{
//			done;
//		}
//		
//		if((I2C2->ISR & I2C_ISR_TXIS) != 0) 
//		{
//			break;
//		}
//  }
//	
//	I2C2->TXDR |= 0x0F; // "WHO_AM_I" register address into the I2C TXDR
//	
//	while(1) // Wait TC flag is set
//	{
//		if((I2C2->ISR & I2C_ISR_TC) != 0) 
//			{
//				break;
//				
//			}
//	}
//	// Reload CR2 register
//	I2C2->CR2 |= (0x69 << 1); // set the S3GD20 slave address
//	I2C2->CR2 |= (1 << 16); // transmit = 1
//	I2C2->CR2 |= (1 << 10); // set the RD_WRN bit to indicate a read operation
//	I2C2->CR2 |= (1 << 13); // set the start bit
//	
//		
//	while(1) // Wait RXNE flag is set
//	{
//		if((I2C_ISR_NACKF & I2C_ISR_RXNE) == 0) 
//		{
//			done;
//		}
//		
//		if((I2C2->ISR & I2C_ISR_RXNE) != 0) 
//		{
//			break;
//		}
//	}
//	
//	while(1) // Wait TC flag is set
//	{
//		if((I2C2->ISR & I2C_ISR_TC) != 0) 
//		{
//			break;
//		}
//	}
//	
//	if(I2C2->RXDR == 0xD3) // Check the value of the RXDR register to see if it matched 0xD3.
//	{
//		GPIOC->ODR |= (1 << 6); // Turn on RED led
//	}

//	I2C2->CR2 |= (1 << 14) ; // STOP bit
// 
	
	
	
	
////////////////////////////////////////////////////////////////////////////////////////

//8-bit two data registers for X, Y axis
	int8_t X1;
	int8_t X2;
	int8_t Y1;
	int8_t Y2;
	
	//16-bit register for X, Y axis
	int16_t X;
	int16_t Y;
	
// Set/Initialize the L3GD20
I2C2->CR2 |= (0x69 << 1); // set the S3GD20 slave address
I2C2->CR2 &= ~(1 << 16); // transmit = 2
I2C2->CR2 |= (1 << 17);
I2C2->CR2 &= ~(1 << 10); // set the RD_WRN bit to indicate a write operation
I2C2->CR2 |= (1 << 13); // set the start bit
	
  while (1) // Wait TXIS flag is set
  {
		if((I2C_ISR_NACKF & I2C_ISR_TXIS) == 0) 
		{
			done;
		}
		
		if((I2C2->ISR & I2C_ISR_TXIS) != 0) 
		{
			break;
		}
  }
	
	I2C2->TXDR = 0x20; // CTRL_REG1 register address into the I2C TXDR
	
	while (1) // Wait TXIS flag is set
  {
		if((I2C_ISR_NACKF & I2C_ISR_TXIS) == 0) 
		{
			done;
		}
		
		if((I2C2->ISR & I2C_ISR_TXIS) != 0) 
		{
			break;
		}
  }
	
	I2C2->TXDR = 0xB; // Enable normal or sleep mode, Yen, Xen (1011)
	
	while(1) // Wait TC flag is set
	{
		if((I2C2->ISR & I2C_ISR_TC) != 0) 
			{
				break;
				
			}
	}
	
	I2C2->CR2 |= (1 << 14) ; // STOP bit
	
	
	
	while(1) // Read and save the value of the X and Y axis data registers every 100ms
	{
		HAL_Delay(100);
		
		// Read and store the X data
		I2C2->CR2 &= ~(1 << 17); // transmit = 1
		I2C2->CR2 |= (1 << 16);
		I2C2->CR2 &= ~(1 << 10); // set the RD_WRN bit to indicate a write operation
		I2C2->CR2 |= (1 << 13); // set the start bit
		
		while (1) // Wait TXIS flag is set
  {
		if((I2C_ISR_NACKF & I2C_ISR_TXIS) == 0) 
		{
			done;
		}
		
		if((I2C2->ISR & I2C_ISR_TXIS) != 0) 
		{
			break;
		}
  }
	
	I2C2->TXDR = 0xA8; // Read both registers in same transaction
	
	while(1) // Wait TC flag is set
	{
		if((I2C2->ISR & I2C_ISR_TC) != 0) 
			{
				break;
				
			}
	}
	
	
	I2C2->CR2 &= ~(1 << 16); // transmit = 2
	I2C2->CR2 |= (1 << 17);
	I2C2->CR2 |= (1 << 10); // set the RD_WRN bit to indicate a read operation
	I2C2->CR2 |= (1 << 13); // set the start bit
	
	while(1) // Wait RXNE flag is set
	{
		if((I2C_ISR_NACKF & I2C_ISR_RXNE) == 0) 
		{
			done;
		}
		
		if((I2C2->ISR & I2C_ISR_RXNE) != 0) 
		{
			break;
		}
	}
	
	X1 = I2C2->RXDR; // Store X_L data to the X1
	
	while(1) // Wait RXNE flag is set
	{
		if((I2C_ISR_NACKF & I2C_ISR_RXNE) == 0) 
		{
			done;
		}
		
		if((I2C2->ISR & I2C_ISR_RXNE) != 0) 
		{
			break;
		}
	}
	
	X2 = I2C2->RXDR; // Store X_H data to the X2
	
	while(1) // Wait TC flag is set
	{
		if((I2C2->ISR & I2C_ISR_TC) != 0) 
		{
			break;
		}
	}
	I2C2->CR2 |= (1 << 14) ; // STOP bit
	
	
	// Read and store the Y data
	I2C2->CR2 &= ~(1 << 17); // transmit = 1
	I2C2->CR2 |= (1 << 16);
	I2C2->CR2 &= ~(1 << 10); // set the RD_WRN bit to indicate a write operation
	I2C2->CR2 |= (1 << 13); // set the start bit
		
		while (1) // Wait TXIS flag is set
  {
		if((I2C_ISR_NACKF & I2C_ISR_TXIS) == 0) 
		{
			done;
		}
		
		if((I2C2->ISR & I2C_ISR_TXIS) != 0) 
		{
			break;
		}
  }
	
	I2C2->TXDR |= 0xAA; // Read Y axis registers in same transaction
	
	while(1) // Wait TC flag is set
	{
		if((I2C2->ISR & I2C_ISR_TC) != 0) 
			{
				break;
				
			}
	}
	
	
	I2C2->CR2 &= ~(1 << 16); // transmit = 2
	I2C2->CR2 |= (1 << 17);
	I2C2->CR2 |= (1 << 10); // set the RD_WRN bit to indicate a read operation
	I2C2->CR2 |= (1 << 13); // set the start bit
	
	while(1) // Wait RXNE flag is set
	{
		if((I2C_ISR_NACKF & I2C_ISR_RXNE) == 0) 
		{
			done;
		}
		
		if((I2C2->ISR & I2C_ISR_RXNE) != 0) 
		{
			break;
		}
	}
	
	Y1 = I2C2->RXDR; // Store Y_L data to the Y1
	
	while(1) // Wait RXNE flag is set
	{
		if((I2C_ISR_NACKF & I2C_ISR_RXNE) == 0) 
		{
			done;
		}
		
		if((I2C2->ISR & I2C_ISR_RXNE) != 0) 
		{
			break;
		}
	}
	
	Y2 = I2C2->RXDR; // Store Y_H data to the Y2
	
	while(1) // Wait TC flag is set
	{
		if((I2C2->ISR & I2C_ISR_TC) != 0) 
		{
			break;
		}
	}
	I2C2->CR2 |= (1 << 14) ; // STOP bit
	
	
	
	
	// Combine 8-bit registers in one 16-bit register
	X = ((int16_t)X2 << 8)| X1;
	Y = ((int16_t)Y2 << 8)| Y1;
	
	int thr = 80;
	if(X < -thr) 
	{
		GPIOC->ODR |= (1 << 8);
		GPIOC->ODR &= ~(1 << 9);
	}
	
	else if(X > thr) 
	{
		GPIOC->ODR |= (1 << 9);
		GPIOC->ODR &= ~(1 << 8);
	}
	
	else if(Y < -thr) 
	{
		GPIOC->ODR |= (1 << 7);
		GPIOC->ODR &= ~(1 << 6);
	}
	
	else if(Y > thr) 
	{
		GPIOC->ODR |= (1 << 6);
		GPIOC->ODR &= ~(1 << 7);
	}
	} // R&S while loop end
	
} // main method end

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
