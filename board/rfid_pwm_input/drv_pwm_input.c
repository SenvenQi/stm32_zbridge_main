#include "board.h"

TIM_HandleTypeDef htim4;

int MX_TIM4_Init(void)
{

    /* USER CODE BEGIN TIM4_Init 0 */

    /* USER CODE END TIM4_Init 0 */

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_SlaveConfigTypeDef sSlaveConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_IC_InitTypeDef sConfigIC = {0};

    /* USER CODE BEGIN TIM4_Init 1 */

    /* USER CODE END TIM4_Init 1 */
    htim4.Instance = TIM4;
    htim4.Init.Prescaler = 72-1;
    htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim4.Init.Period = 0xFFFF-1;
    htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_TIM_IC_Init(&htim4) != HAL_OK)
    {
        Error_Handler();
    }
    sSlaveConfig.SlaveMode = TIM_SLAVEMODE_RESET;
    sSlaveConfig.InputTrigger = TIM_TS_TI1FP1;
    sSlaveConfig.TriggerPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
    sSlaveConfig.TriggerFilter = 0;
    if (HAL_TIM_SlaveConfigSynchronization(&htim4, &sSlaveConfig) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
    sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
    sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
    sConfigIC.ICFilter = 0;
    if (HAL_TIM_IC_ConfigChannel(&htim4, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
    {
        Error_Handler();
    }
    sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
    sConfigIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
    if (HAL_TIM_IC_ConfigChannel(&htim4, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM4_Init 2 */
    HAL_TIM_Base_Start_IT(&htim4);
    HAL_TIM_IC_Start_IT(&htim4,TIM_CHANNEL_1);
    HAL_TIM_IC_Start_IT(&htim4,TIM_CHANNEL_2);
    /* USER CODE END TIM4_Init 2 */
    return RT_EOK;
}

rt_uint16_t risingCount;
rt_uint16_t fallingCount;
rt_uint16_t recordLastTime;
rt_uint8_t CardNo[4];
rt_uint8_t CardData[256];
rt_uint8_t EmptyFlip = 0;
rt_uint8_t StartFlag = 0;
rt_uint8_t GuideCount = 0;
rt_uint8_t GuideFlag = 0;
rt_uint16_t RcvPoint = 0;
rt_uint8_t ReciveCardState=0;
float duty;

rt_err_t Row_And_Col_Even_Check_First(void)
{
    rt_uint8_t i,j,checkSum;
    rt_uint8_t colSum[4];

    j=0;
    for(i=0;i<10;i++)
    {
        checkSum=CardData[j++];
        checkSum=checkSum+CardData[j++];
        checkSum=checkSum+CardData[j++];
        checkSum=checkSum+CardData[j++];
        checkSum=checkSum+CardData[j++];
        if(checkSum%2==1) return 1;
    }

    for(i=0;i<4;i++)
    {
        colSum[i]=CardData[i];
    }

    j=5;
    for(i=1;i<11;i++)
    {
        colSum[0]=colSum[0]+CardData[j++];
        colSum[1]=colSum[1]+CardData[j++];
        colSum[2]=colSum[2]+CardData[j++];
        colSum[3]=colSum[3]+CardData[j++];
        j++;
    }
    for(i=0;i<4;i++)
    {
        if(colSum[i]%2==1) return 1;
    }

    return 0;
}


rt_err_t Row_And_Col_Even_Check(void)
{
    rt_uint8_t i,j,checkSum;
    rt_uint8_t colSum[4];

    j=0;
    for(i=0;i<10;i++)
    {
        checkSum=CardData[j++];
        checkSum=checkSum+CardData[j++];
        checkSum=checkSum+CardData[j++];
        checkSum=checkSum+CardData[j++];
        checkSum=checkSum+CardData[j++];
        if(checkSum%2==1) return 1;
    }

    for(i=0;i<4;i++)
    {
        colSum[i]=CardData[i];
    }

    j=5;
    for(i=1;i<11;i++)
    {
        colSum[0]=colSum[0]+CardData[j++];
        colSum[1]=colSum[1]+CardData[j++];
        colSum[2]=colSum[2]+CardData[j++];
        colSum[3]=colSum[3]+CardData[j++];
        j++;
    }
    for(i=0;i<4;i++)
    {
        if(colSum[i]%2==1) return 1;
    }

    return 0;
}

void PickupCardNo(void)
{
    rt_uint8_t i,j,k,temp;
    k=10;
    for(i=0;i<=3;i++)
    {
        temp=0;
        for(j=0;j<4;j++)
        {
            temp=temp+CardData[k++];
            temp=temp<<1;
        }
        k++;
        for(j=0;j<4;j++)
        {
            temp=temp+CardData[k++];
            if(j<=2) temp=temp<<1;
        }
        k++;
        CardNo[i]=temp;
    }
    for(i=0;i<55;i++)
    {
        CardData[i]=0;
    }
}

rt_uint16_t getRising(){
    return fallingCount - risingCount;
}

rt_uint16_t getFalling(){
    return risingCount;
}

rt_uint16_t getCycle(rt_uint16_t curValue){
    if(curValue < recordLastTime){
        rt_uint16_t tempValue = 0x1ff - recordLastTime;
        return tempValue + curValue + 1;
    }
    return curValue - recordLastTime;
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
    rt_uint16_t tempValue;
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1){
        fallingCount = HAL_TIM_ReadCapturedValue(&htim4,TIM_CHANNEL_1);
        tempValue = getRising();
    }

    if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2){
        risingCount = HAL_TIM_ReadCapturedValue(&htim4,TIM_CHANNEL_2);
        tempValue = getFalling();
    }
    rt_uint16_t s = getCycle(tempValue);
    recordLastTime = tempValue;
    rt_kprintf("t:%d -- r:%d -- s:%d \r\n",tempValue,recordLastTime,s);
    if (s>0x190) {
        StartFlag = 1;
        EmptyFlip = 1;
    } else {
        if (EmptyFlip == 1) {
            EmptyFlip = 0;
            return;
        } else {
            EmptyFlip = 1;
        }
    }
    if(StartFlag == 0) return;
    if(GuideFlag == 0) {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
            GuideCount++;
        } else {
            GuideCount = 0;
        }
        if (GuideCount == 9) {
            GuideFlag = 1;
            RcvPoint = 0;
        }
    }
    else {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
            CardData[RcvPoint++] = 1;
        } else {
            CardData[RcvPoint++] = 0;
        }

        if (RcvPoint >= 55) //����11*5���������
        {
            rt_err_t temp = Row_And_Col_Even_Check_First(); //���ݵ��к��е�żУ��

            if (temp == 0) {

                rt_kprintf("ok!!!");
                ReciveCardState = 1;
            } else {
                rt_kprintf("failed!!!");
                ReciveCardState = 0;
            }

            GuideFlag = 0;
            GuideCount = 0;

        }
    }
}


//u8 temp = 0;
//
//u16 tempValue;
//
//if(ReciveCardState == 1) return;
//
//if(curValue < recodLastTime)
//{
//tempValue = 0xff-recodLastTime;
//tempValue = tempValue+curValue+1;
//}
//else
//{
//tempValue = curValue-recodLastTime;
//}
//recodLastTime = curValue;
////����0x190Ϊһ������
//if(tempValue > 0x190)  //���ʱ��������������
//{
//startFlag = 1;
//EmptyFlip = 1;
//
//}
////С��0x190Ϊ�������
//else
//{
//if(EmptyFlip == 1)
//{
//EmptyFlip = 0; //EmptyFlipΪ0ʱ��ʾ������1��ʾ��������
//return;
//}
//else
//{
//EmptyFlip = 1;
//}
//}
//if(startFlag == 0) return;
////�ж�Ϊ��������ͷ
//if(GuideFlag == 0)
//{
//if(bitValue == 0)
//{
//GuideCount++;
//}
//else
//{
//GuideCount = 0;
//}
//if(GuideCount == 9)
//{
//GuideFlag = 1;
//RcvPoint = 0;
//}
//}
//else
//{
//if(bitValue ==0)
//{
//CardData[RcvPoint++] = 1;
//}
//else
//{
//CardData[RcvPoint++] = 0;
//}
//
//if(RcvPoint >= 55) //����11*5���������
//{
//temp = Row_And_Col_Even_Check_First(); //���ݵ��к��е�żУ��
//
//if(temp == 0)
//{
//ReciveCardState = 1;
//}
//else
//{
//ReciveCardState = 0;
//}
//
//GuideFlag = 0;
//GuideCount = 0;
//
//}
//}

