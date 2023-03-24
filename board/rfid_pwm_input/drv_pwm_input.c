#include "board.h"
#include "drv_config.h"

//#define DRV_DEBUG
#define LOG_TAG             "drv.pwminput"
#include <drv_log.h>

#define BSP_USING_PWM_INPUT4

#ifdef BSP_USING_PWM_INPUT4
#ifndef PWM_INPUT4_CONFIG
#define PWM_INPUT4_CONFIG                     			\
    {                                           		\
		.tim_handler.Instance = TIM4,                	\
		.name = "pulse4"             					\
    }
#endif /* PWM_INPUT4_CONFIG */
#endif /* BSP_USING_PWM_INPUT4 */

enum
{
#ifdef BSP_USING_PWM_INPUT4
    PWM_INPUT4_INDEX,
#endif
};

struct stm32_pwm_input_device{
    struct rt_device parent;
    TIM_HandleTypeDef tim_handler;
    DMA_HandleTypeDef hdma_tim_ch1;
    DMA_HandleTypeDef hdma_tim_ch2;
    rt_uint16_t timer_ch1[5];
    rt_uint16_t timer_ch2[5];
    const char *name;
};

static struct stm32_pwm_input_device stm32_pwm_input_obj[] =
        {
#ifdef BSP_USING_PWM_INPUT4
                PWM_INPUT4_CONFIG,
#endif
        };

rt_err_t pwm_input_init(rt_device_t pwm_input_device){
    TIM_SlaveConfigTypeDef sSlaveConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_IC_InitTypeDef sConfigIC = {0};
    struct stm32_pwm_input_device *stm32_device;
    stm32_device = (struct stm32_pwm_input_device*)pwm_input_device;

    stm32_device->tim_handler.Init.Prescaler = 144-1; //500k
    stm32_device->tim_handler.Init.CounterMode = TIM_COUNTERMODE_UP;
    stm32_device->tim_handler.Init.Period = 0xffff;
    stm32_device->tim_handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    stm32_device->tim_handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    if (HAL_TIM_Base_Init(&stm32_device->tim_handler) != HAL_OK){
        Error_Handler();
    }

    if (HAL_TIM_IC_Init(&stm32_device->tim_handler) != HAL_OK){
        Error_Handler();
    }

    sSlaveConfig.SlaveMode = TIM_SLAVEMODE_RESET;
    sSlaveConfig.InputTrigger = TIM_TS_TI1FP1;
    sSlaveConfig.TriggerPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
    sSlaveConfig.TriggerFilter = 0;
    if (HAL_TIM_SlaveConfigSynchro(&stm32_device->tim_handler, &sSlaveConfig) != HAL_OK){
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&stm32_device->tim_handler, &sMasterConfig) != HAL_OK){
        Error_Handler();
    }
    sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
    sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
    sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
    sConfigIC.ICFilter = 0;
    if (HAL_TIM_IC_ConfigChannel(&stm32_device->tim_handler, &sConfigIC, TIM_CHANNEL_1) != HAL_OK){
        Error_Handler();
    }
    sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
    sConfigIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
    if (HAL_TIM_IC_ConfigChannel(&stm32_device->tim_handler, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
    {
        Error_Handler();
    }

    /* DMA controller clock enable */
    __HAL_RCC_DMA1_CLK_ENABLE();

    /* TIM4 DMA Init */
    /* TIM4_CH1 Init */
    stm32_device->hdma_tim_ch1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    stm32_device->hdma_tim_ch1.Init.PeriphInc = DMA_PINC_DISABLE;
    stm32_device->hdma_tim_ch1.Init.MemInc = DMA_MINC_ENABLE;
    stm32_device->hdma_tim_ch1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    stm32_device->hdma_tim_ch1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    stm32_device->hdma_tim_ch1.Init.Mode = DMA_CIRCULAR;
    stm32_device->hdma_tim_ch1.Init.Priority = DMA_PRIORITY_MEDIUM;
    HAL_DMA_Init(&stm32_device->hdma_tim_ch1);

    __HAL_LINKDMA(&stm32_device->tim_handler,hdma[TIM_DMA_ID_CC1],stm32_device->hdma_tim_ch1);

    /* TIM4_CH2 Init */
    stm32_device->hdma_tim_ch2.Init.Direction = DMA_PERIPH_TO_MEMORY;
    stm32_device->hdma_tim_ch2.Init.PeriphInc = DMA_PINC_DISABLE;
    stm32_device->hdma_tim_ch2.Init.MemInc = DMA_MINC_ENABLE;
    stm32_device->hdma_tim_ch2.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    stm32_device->hdma_tim_ch2.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    stm32_device->hdma_tim_ch2.Init.Mode = DMA_CIRCULAR;
    stm32_device->hdma_tim_ch2.Init.Priority = DMA_PRIORITY_MEDIUM;
    HAL_DMA_Init(&stm32_device->hdma_tim_ch2);

    __HAL_LINKDMA(&stm32_device->tim_handler,hdma[TIM_DMA_ID_CC2],stm32_device->hdma_tim_ch2);


    HAL_TIM_IC_Start_DMA(&stm32_device->tim_handler, TIM_CHANNEL_1, (uint32_t*)&stm32_device->timer_ch1, 5);
    stm32_device->tim_handler.State = HAL_TIM_STATE_READY;
    HAL_TIM_IC_Start_DMA(&stm32_device->tim_handler, TIM_CHANNEL_2, (uint32_t*)&stm32_device->timer_ch2, 5);

    return RT_EOK;
}

static rt_err_t pwm_input_open(rt_device_t dev, rt_uint16_t oflag){
    return RT_EOK;
}

static rt_err_t pwm_input_close(rt_device_t dev){
    return RT_EOK;
}

static rt_err_t pwm_input_control(rt_device_t dev, int cmd, void *args){
    rt_err_t result;
    struct stm32_pwm_input_device *stm32_device;
    stm32_device = (struct stm32_pwm_input_device*)dev;

    result = RT_EOK;

    switch (cmd)
    {
        default:
            result = -RT_ENOSYS;
            break;
    }

    return result;
}

static rt_size_t pwm_input_write(rt_device_t dev,
                                 rt_off_t pos,
                                 const void* buffer,
                                 rt_size_t size){
    return 0;
}

//pos = 0 读取pwm周期 单位0.1ms
//pos = 1 读取pwm占空比 单位0.1%
static rt_size_t pwm_input_read(rt_device_t dev,
                                rt_off_t pos,
                                void* buffer,
                                rt_size_t size){
    rt_uint32_t* temp = (rt_uint32_t*)buffer;
    struct stm32_pwm_input_device *stm32_device;
    stm32_device = (struct stm32_pwm_input_device*)dev;
    rt_uint32_t total[2] = {0,0};
    if(pos == 0){
        for(uint8_t i = 0; i<5; i++){
            total[0] += stm32_device->timer_ch1[i];
            total[1] += stm32_device->timer_ch2[i];
        }
        total[0] /= 5;
        total[1] /= 5;

        uint32_t period_ms;
        //计算频率及占空比
        if(total[0] != 0){
            //TIM4 2*PCLK1
            uint32_t fre = 2*HAL_RCC_GetPCLK1Freq()/(stm32_device->tim_handler.Init.Prescaler+1);
            period_ms =  total[0]*10000/fre; //0.1ms
        }
        *temp = period_ms;
    }
    else if(pos == 1){
        for(uint8_t i = 0; i<5; i++){
            total[0] += stm32_device->timer_ch1[i];
            total[1] += stm32_device->timer_ch2[i];
        }
        total[0] /= 5;
        total[1] /= 5;
        uint32_t duty;
        //计算频率及占空比
        if(total[0] != 0){
            duty = (uint32_t)total[1]*1000 / (uint32_t)total[0];
        }
        *temp = duty;
    }
    else{
        return 0;
    }
    return 1;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops pwm_input_device_ops =
{
    pwm_input_init,
    pwm_input_open,
    pwm_input_close,
    pwm_input_read,
    pwm_input_write,
    pwm_input_control
};
#endif

int hw_pwm_input_init(void){
    int i;
    int result;
    struct rt_device *device;
    result = RT_EOK;
    for (i = 0; i < sizeof(stm32_pwm_input_obj) / sizeof(stm32_pwm_input_obj[0]); i++){
        device = &(stm32_pwm_input_obj[i].parent);

        device->type        = RT_Device_Class_Miscellaneous;
        device->rx_indicate = RT_NULL;
        device->tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
        device->ops         = &pwm_input_device_ops;
#else
        device->init        = pwm_input_init;
        device->open        = pwm_input_open;
        device->close       = pwm_input_close;
        device->read        = pwm_input_read;
        device->write       = pwm_input_write;
        device->control     = pwm_input_control;
#endif
        device->user_data   = RT_NULL;

        if (rt_device_register(device, stm32_pwm_input_obj[i].name, RT_DEVICE_FLAG_RDONLY | RT_DEVICE_FLAG_STANDALONE)!= RT_EOK){
            LOG_E("%s register failed", stm32_pwm_input_obj[i].name);
            return -RT_ERROR;
        }
    }
    return result;
}
INIT_BOARD_EXPORT(hw_pwm_input_init);

