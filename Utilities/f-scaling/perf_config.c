#include "perf_config.h"
#include "stm32f7xx_ll_pwr.h"
#include "stm32f7xx_ll_rcc.h"
#include "stm32f7xx_ll_bus.h"
#include "stm32f7xx_ll_utils.h"
#include "stm32f7xx_ll_system.h"

/* Private Prototype ******************************************************************/
/* Private Variable *******************************************************************/
static PLLParamCon_TypeDef ClkConfig;
static uint8_t StandbyState = 0;

const PLLParamCon_TypeDef ClockRateScale_Low[] = { 
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_15, 144, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 244, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 248, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 252, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 256, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_15, 156, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 264, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_8, 134, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 272, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 276, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_15, 168, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 284, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 288, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 292, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 296, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_12, 144, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 304, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 308, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 312, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 316, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_15, 192, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 324, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 328, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 332, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 336, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_15, 204, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 344, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 348, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 352, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 356, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_15, 216, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 364, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 368, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 372, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 376, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_15, 228, LL_RCC_PLLP_DIV_4},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 192, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 194, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 196, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 198, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_12, 96, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 202, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 204, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 206, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 208, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_15, 126, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 212, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 214, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 216, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_8, 109, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_8, 110, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_8, 111, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_8, 112, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_8, 113, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_8, 114, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_8, 115, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_8, 116, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 234, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 236, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 238, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_15, 144, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 242, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 244, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 246, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 248, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_12, 120, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 252, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 254, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 256, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 258, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_15, 156, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 262, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 264, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 266, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_8, 134, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_15, 162, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 272, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 274, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 276, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 278, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_15, 168, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 282, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 284, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 286, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 288, LL_RCC_PLLP_DIV_2}
};
const PLLParamCon_TypeDef ClockRateScale_High[] = { 
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_15, 216, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 362, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 364, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 366, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 368, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_15, 222, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 372, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 374, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 376, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 378, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_15, 228, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 382, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 384, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 386, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 388, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_15, 234, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 392, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 394, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 396, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 398, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_12, 192, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_8, 201, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 404, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_8, 203, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 408, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_8, 205, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 412, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_8, 207, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 416, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 418, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_15, 252, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 422, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 424, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 426, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 428, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_15, 258, LL_RCC_PLLP_DIV_2},
{LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 432, LL_RCC_PLLP_DIV_2}
};
const PLLParamCon_TypeDef ClockRateScale_Medium = {LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 336, LL_RCC_PLLP_DIV_2};

void TaskPerf_ClockRateSwitch(uint16_t target_f) 
{
  /* Re-route clock source to LSI */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI);
  
  /* Disable PLL */
  LL_RCC_PLL_Disable();
  
  /*Low Range Frequency -------------------------------------------------------*/
  if (target_f >= LOWER_BND_LOW_CLK_RATE && target_f <= UPPER_BND_LOW_CLK_RATE)
  {
    /* Disable Overdrive Mode */
    /* Disable Overdrice Switching */
    PWR->CR1 &= ~(3 << 16);
    /* Using Scale 3 Mode (Low) */
    LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE3);
    
    /* Copy map pll configuration to ClkConfig var */
    ClkConfig = ClockRateScale_Low[target_f - LOWER_BND_LOW_CLK_RATE];
  }
  
  /*Medium Range Frequency ----------------------------------------------------*/
  else if (target_f == MID_CLK_RATE)
  {
    /* Disable Overdrive Mode */
    LL_PWR_DisableOverDriveMode();
    /* Disable Overdrice Switching */
    LL_PWR_DisableOverDriveSwitching();
    /* Copy map pll configuration to ClkConfig var */
    /* Using Scale 2 Mode (Medium) */
    LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE2);
    ClkConfig = ClockRateScale_Medium;
  }
  
  /*High Range Frequency ------------------------------------------------------------*/
  else if (target_f >= LOWER_BND_HIGH_CLK_RATE && target_f <= UPPER_BND_HIGH_CLK_RATE)
  {
    /* Enable Overdrive Mode */
    LL_PWR_EnableOverDriveMode();
    while(LL_PWR_IsActiveFlag_OD() != 1);
    /* Enable Overdrice Switching */
    LL_PWR_EnableOverDriveSwitching();  
    while(LL_PWR_IsActiveFlag_ODSW() != 1);
    /* Using Scale 1 Mode (High) */
    LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
    
    /* Copy map pll configuration to ClkConfig var */
    ClkConfig = ClockRateScale_High[target_f - LOWER_BND_HIGH_CLK_RATE];
  }
  
  /* Insanity case, trap in inf loop */
  else 
  {
    /*Standby at 8MHz*/
    if(target_f == 8) 
    {
      StandbyState = 1;
      PWR->CR1 &= ~(3 << 16);
      
      /*Set Flash Latency to 0 wait state*/
      LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);
      /*Re-route clock source to HSI*/
      LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);
      
      SysTick_Config((target_f * 1000000) / 1000);
      LL_SetSystemCoreClock(target_f * 1000000);
      
      return;
    }
    /*Anormaly clock rate*/
    else 
    {
      while(1);
    }
  }
  /*Re-configure FLASH LATENCY (in case of 2.7-3.3V supply)*/
  if(target_f > 30 && target_f <= 60)
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);
  else if(target_f > 60 && target_f <= 90)
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
  else if(target_f > 90 && target_f <= 120)
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_3);
  else if(target_f > 120 && target_f <= 150)
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_4);
  else if(target_f > 150 && target_f <= 180)
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_5);
  else if(target_f > 180 && target_f <= 210)
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_6);
  else if(target_f > 210 && target_f <= 216)
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_7);

  StandbyState = 0;
  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(ClkConfig.clock_src, 
                              ClkConfig.pll_m, 
                              ClkConfig.pll_n, 
                              ClkConfig.pll_p);

  LL_RCC_PLL_Enable();
  while(LL_RCC_PLL_IsReady() != 1);

  /* Sysclk activation on the main PLL */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) ;

  /* Update SystemCoreClock*/
  SysTick_Config((target_f * 1000000) / 1000);
  LL_SetSystemCoreClock(target_f * 1000000);
}

uint8_t TaskPerf_isOnStandby() 
{
  return StandbyState;
}