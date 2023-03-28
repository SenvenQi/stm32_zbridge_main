//
// Created by 天琪王 on 2023/3/28.
//
#include "protocol.h"

rt_uint16_t Bin_Buffer[555];
rt_uint16_t TT_Buffer[555];
rt_uint8_t TT_voltage[555];
rt_uint8_t RFID[555];


rt_uint8_t FindHeader(rt_uint16_t index)
{
    rt_uint16_t n;

    if((Bin_Buffer[index]==0)&&(Bin_Buffer[index+1]==1))//cym 1/0
    {
        index++;
        index++;
    }
    else
    {
        return (0);
    }

    for(n=0; n<9; n++)
    {
        if((Bin_Buffer[index]==1)&&(Bin_Buffer[index+1]==0))//cym 0/1
            index = index+2;
        else
            return (0);
    }

    return (1);
}

rt_uint8_t FindID(rt_uint16_t i)
{
    rt_uint8_t n;
    rt_uint8_t k;
    rt_uint8_t sum;
    rt_uint16_t Vendor,
            CardIDH ,
            CardIDL = 0;

    //-------------------- STEP1: 提取RFID有效数据
    if(i)
    {
        for(n=0; n<11; n++)RFID[n] = 0x00; //------ Buffer清零

        i = i+20;  //--- 有效数据流

        for(k=0; k<11; k++)
        {
            for(n=0; n<5; n++)
            {
                RFID[k] = RFID[k]<<1;

                if((Bin_Buffer[i]==1)&&(Bin_Buffer[i+1]==0))//cym 0/1
                {
                    RFID[k] |= 0x01;
                }
                i += 2;
            }
        }

    }

    //---------------------------- STEP2: 校对数据

    //---------------------- X 轴校验
    for(k=0; k<10; k++)
    {
        sum = 0;
        if(RFID[k]&0x01)sum++;
        if(RFID[k]&0x02)sum++;
        if(RFID[k]&0x04)sum++;
        if(RFID[k]&0x08)sum++;
        if(RFID[k]&0x10)sum++;

        if(sum%2) //--- 偶校验出错!
        {
            // MessageBox("X 轴校验出错!");
            return 0;
        }
    }

    //------------------- Y 轴校验
    sum = 0;
    for(k=0; k<11; k++)
    {
        sum ^= RFID[k];
    }

    if(sum&0x1E) //--- 偶校验出错!
    {
        //MessageBox("Y 轴校验出错!");
        return 0;
    }

    //------------------ STEP3: 获取RFID卡号(4个字节32位)
    for(k=0; k<10; k++)
    {
        RFID[k] = RFID[k]>>1; //---去掉校验值
    }

    Vendor  = 0;
    CardIDH = 0;
    CardIDL = 0;

    k = RFID[0]<<4;
    Vendor = k|RFID[1]; //--- 卡版本或供应商信息

    k = RFID[2]<<4;
    k |= RFID[3];
    CardIDH |= k<<8;

    k = RFID[4]<<4;
    k |= RFID[5];
    CardIDH |= k;

    k = RFID[6]<<4;
    k |= RFID[7];
    CardIDL |= k<<8;

    k = RFID[8]<<4;
    k |= RFID[9];
    CardIDL |= k;

    for (int j = 0; j < 10; ++j) {
        rt_kprintf("%x",RFID[j]);
    }
    rt_kprintf("\n");
    //------------------ STEP4: 显示解码结果
    return 1;
}
unsigned char Decode(void)
{
    rt_uint16_t min,max,avg,i,n;

    min = 0xFF;max = 0xFF;avg = 0xFF;i = 0xFF;n = 0xFF;

    //-------------------- STEP1: 找出 [平均值]
    for(i=1; i<256; i++) //---- 从1开始! 0字节是不可靠数据
    {
        if(TT_Buffer[i]<min)
        {
            min = TT_Buffer[i];
        }
        if(TT_Buffer[i]>max)
        {
            max = TT_Buffer[i];
        }
    }

    //数据过滤
//    if(min<100||max>1000)
//    {
//        //DEBUG("\r\n min: %d max: %d ; |舍弃 ! | \r\n",min,max);
//        return 0;
//    }

    avg=((min+max)/2);//-----平均值
    n = 0;

    //-------------------- STEP2: 提取原始数据
    for(i=1; i<256; i++) //---- 必须从1开始! 0字节是不可靠数据
    {
        if (TT_Buffer[i]<avg )//(abs((int)TT_Buffer[i] - 245)<=70)
        {
            if (TT_voltage[i]==1)
                Bin_Buffer[n++]=0;
            else
                Bin_Buffer[n++]=1;
        }
        else if (TT_Buffer[i]>avg )//(abs((int)TT_Buffer[i] - 485)<=70)
        {
            if (TT_voltage[i]==1)
            {
                Bin_Buffer[n++]=0;
                Bin_Buffer[n++]=0;
            }
            else
            {
                Bin_Buffer[n++]=1;
                Bin_Buffer[n++]=1;
            }
        }
    }

    //-------------------- STEP3: 查找RFID头标志(9个1)

    i = n-128;  //------- 有效起始点!
    while(i--)
    {
        if(FindHeader(i))
        {
            if(FindID(i))
            {
                return 1;
            }
        }
    }

    return 0;
}