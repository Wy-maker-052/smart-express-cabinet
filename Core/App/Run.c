#include "Run.h"

uint8_t Munu_Flag = 0;

uint8_t Array[4] = {0};
uint8_t Voice_Array[1] = {0};
uint8_t Temporary[4] = {0};
uint8_t flag = 0;


extern uint8_t n, Rx_Fulfill;
extern uint16_t b;
extern uint32_t Time_Count;

extern uint8_t Data[4];




uint16_t Random_Number()
{
    srand(b);
    // 生成一个min到max之间的随机整数
    uint16_t max = 4177, min = 713, num = 0;
    double decimals = 0, random = 0, a;
    random = (double)min + (max - min) * rand() / (RAND_MAX + 1.0) * 1671;
    
    decimals = modf(random, &a);
    num = decimals * 10000;
    
    
    return num;


}



void Run_Init(void)
{
    HAL_Delay(20);
    OLED_Init();
    Matrix_KeyInit();
    stmflash_read(FLASH_SAVE_ADDR, (uint16_t *)Array, 4);
}




void Main_Interface()
{
    uint8_t Num = 0;
    ETime_TimerTypeDef Time = {0};
    uint8_t first = 1;
    if (flag == 2)
    {
        OLED_ShowText(40, 0, "主菜单", 16);
        OLED_ShowText(16, 16, "1.存快递", 16);
        OLED_ShowText(16, 32, "2.取快递", 16);
        OLED_ShowText(16, 48, "3.语音查询取件", 16);
    }
    while (1)
    {
        if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == 1 || flag == 2)																		//红外检测
        {
            flag = 1;
            Etimer_TimeStart(&Time);
        }
        if (Etimer_GetTime(&Time) > 3000)
        {
            first = 1;
            flag = 0;
            Etimer_ClearTime(&Time);
            Etimer_TimeStop(&Time);
            OLED_Clear();
            OLED_Update();
        }
        
        
        if (flag == 1)
        {
            if (first == 1)
            {
                OLED_ShowText(40, 0, "主菜单", 16);
                OLED_ShowText(16, 16, "1.存快递", 16);
                OLED_ShowText(16, 32, "2.取快递", 16);
                OLED_ShowText(16, 48, "3.语音查询取件", 16);
                first = 0;
            }
        }
        
        
        Num = Press_NumberConfirm();
        if (Num == 1)
        {
            Munu_Flag = 1;
            Maglock_On();
            break;
        
        }
        else if (Num == 2)
        {
            Munu_Flag = 2;
            break;
        
        }
        else if (Num == 3)
        {
            Munu_Flag = 3;
            break;
        
        }
        
        
    }

    OLED_Clear();
    OLED_Update();
}




void Express_Deposit()
{
    
    uint8_t Num = 0, Stage_Flag = 0, i = 0;
    uint16_t Random = 0, Past_Time = 0, ETime_10S = 0;
    OLED_ShowText(40, 0, "存快递", 16);
    Maglock_Off();
    Voice_Array[0] = 5;
    while (1)
    {

        if (HAL_GPIO_ReadPin(Maglock_In_GPIO_Port, Maglock_In_Pin))
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
        else
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
        
        
        
        Num = Press_NumberConfirm();
        if (Num == 1 && Stage_Flag == 0)											//获取取件码
        {
            Random = Random_Number();
            


            if (Random < 1000 && Random > 100)
            {
                Array[0] = 0;
                Array[1] = Random / 100;
                Array[2] = Random / 10 % 10;
                Array[3] = Random % 10;
            }
            
            
            else if (Random < 100)
            {
                Array[0] = 0;
                Array[1] = 0;
                Array[2] = Random / 100;
                Array[3] = Random % 10;
            }
            
            else
            {
                Array[0] = Random / 1000;
                Array[1] = Random / 100 % 10;
                Array[2] = Random / 10 % 10;
                Array[3] = Random % 10;
            }
            
            
            stmflash_write(FLASH_SAVE_ADDR, (uint16_t *)Array, 4);
            
            Stage_Flag = 1;
            Past_Time = Time_Count;
            OLED_ShowText(0, 20, "取件码为:", 16);
            HAL_UART_Transmit(&huart2, Voice_Array, 1, 0xFFFF);
            
            for (i = 0; i < 4; i++)
            {
                OLED_ShowNum(36 + 8 * i, 36, Array[i], 1, 8);
                OLED_Update();
            
            }
            
        }
        if (Num == 13)							//取消返回主界面
        {
            Munu_Flag = 0;
            flag = 2;
            break;
        
        }
        
        
        
        
        if (Stage_Flag == 1 && Time_Count - Past_Time > 4)																				//取件码显示
        {
            OLED_ClearArea(0, 20, 128, 36);
            OLED_Update();
            Stage_Flag = 2;
            OLED_ShowText(0, 16, "提示", 16);
            OLED_ShowText(0, 32, "查看取件码", 16);
            OLED_ShowText(0, 48, "关闭箱门返回", 16);
            
            ETime_10S = Time_Count;
            
        }
        
        if (Num == 2 && Stage_Flag == 2)																													//再次显示取件码
        {
            OLED_ClearArea(0, 16, 128, 32);
            OLED_Update();
            Stage_Flag = 1;
            Past_Time = Time_Count;
            OLED_ShowText(0, 20, "取件码为:", 16);
            
            for (i = 0; i < 4; i++)
            {
                OLED_ShowNum(36 + 8 * i, 36, Array[i], 1, 8);
                OLED_Update();
            
            }
        
        }
        
        if (Stage_Flag == 2 && Time_Count - ETime_10S > 10)																			//10秒超时
        {
            ETime_10S = Time_Count;
            if (HAL_GPIO_ReadPin(Maglock_In_GPIO_Port, Maglock_In_Pin) == 1)												//未关闭箱门
            {
                Voice_Array[0] = 4;
                HAL_UART_Transmit(&huart2, Voice_Array, 1, 0xFFFF);
            
            }
            
        }
        
    }

    OLED_Clear();
    OLED_Update();
}




void Fetch_ExpressDelivery()
{
    uint8_t Num = 0, Num_Dispose = 0, i = 0, a = 0, Code_Flag = 0, Error_Count = 1, Past_Time = 0;
    
    OLED_ShowText(40, 0, "取快递", 16);
    for (a = 0; a < 4; a++)
        OLED_ShowString(30 + 16 * a, 30, "*", 8);
    OLED_Update();
    
    Voice_Array[0] = 1;
    HAL_UART_Transmit(&huart2, Voice_Array, 1, 0xFFFF);
    
    while (1)
    {
        if (HAL_GPIO_ReadPin(Maglock_In_GPIO_Port, Maglock_In_Pin))
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
        else
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
        
        
        Num = Press_NumberConfirm();
        if (Num < 11 && Num != 0 && i < 4)
        {
            switch (Num)
            {
                case 1: Num_Dispose = 1; break;
                case 2: Num_Dispose = 2; break;
                case 3: Num_Dispose = 3; break;
                case 4: Num_Dispose = 4; break;
                case 5: Num_Dispose = 5; break;
                case 6: Num_Dispose = 6; break;
                case 7: Num_Dispose = 7; break;
                case 8: Num_Dispose = 8; break;
                case 9: Num_Dispose = 9; break;
                case 10: Num_Dispose = 0; break;
                
            }
            Temporary[i] = Num_Dispose;
            OLED_ShowNum(30 + 16 * i, 30, Temporary[i], 1, 8);
            OLED_Update();
            i++;

        }
            
        if (Num == 11)																																					//删除
        {
            if (i > 0)
            {
                i--;
                OLED_ShowString(30 + 16 * i, 30, "*", 8);
                OLED_Update();
                Temporary[i] = 0;			
            }

        }
        
        
        if (Num == 12 && i == 4)																																//确认并验证取件码
        {
            Code_Flag = 0, i = 0;			
            for (a = 0; a < 4; a++)
            {
                if (Array[a] != Temporary[a])
                {
                    Code_Flag = 1;
                    break;
                }
                else
                    Code_Flag = 2;
                
            }
            
            
            if (Code_Flag == 1)																																	//取件码错误
            {
                if (Error_Count < 3)
                {
                    OLED_ShowText(20, 16, "取件码错误", 16);
                    OLED_ShowText(20, 32, "请重新输入", 16);				
                    Voice_Array[0] = 2;
                    HAL_UART_Transmit(&huart2, Voice_Array, 1, 0xFFFF);
                }
                Error_Count++;
                if (Error_Count > 3)																																//错误次数过多锁定
                {
                    uint8_t Second = 5;
                    Past_Time = Time_Count;
                    Munu_Flag = 0;
                    OLED_ShowText(18, 16, "错误次数过多", 16);
                    OLED_ShowText(16, 32, "系统锁定5秒", 16);
                    OLED_ShowText(24, 48, "请稍后再试", 16);
                    while (1)
                    {
                        if (Time_Count - Past_Time == 1)
                        {
                            Past_Time = Time_Count;
                            Second--;
                            OLED_ShowNum(80, 32, Second, 1, 8);
                            OLED_Update();
                        }
                        
                        if (Second == 0)
                            break;
                        
                    }

                    break;
                }
                HAL_Delay(1000);
                OLED_ClearArea(0, 16, 128, 48);
                for (a = 0; a < 4; a++)
                    OLED_ShowString(30 + 16 * a, 30, "*", 8);
                OLED_Update();
            }
                

            else if (Code_Flag == 2)																																//验证通过
            {
                i = 5;
                memset(Array, 0, 4);
                stmflash_write(FLASH_SAVE_ADDR, (uint16_t *)Array, 4);
                Maglock_On();
                OLED_ClearArea(0, 16, 128, 64);
                OLED_Update();
                OLED_ShowText(16, 30, "关闭箱门返回", 16);
                
            }
        
            
            memset(Temporary, 0, 4);
            Maglock_Off();
            
        }
        
        
        if (Num == 13)							//取消返回主界面
        {
            Munu_Flag = 0;
            flag = 2;
            break;
        
        }
    
    }


    OLED_Clear();
    OLED_Update();

}



void Voice_Mode()
{
    extern uint8_t Rx_Flag;
    uint8_t Num = 0, a = 0, Code_Flag = 0, ETime_10S = Time_Count, Count = 0;
    Bsp_UsartInit();
    n = 0;
    Voice_Array[0] = 3;  // 首次提示输入取件码
    HAL_UART_Transmit(&huart2, Voice_Array, 1, 0xFFFF);
    HAL_UART_Receive_IT(&huart2, &Rx_Flag, 1);
    OLED_ShowText(16, 0, "语音查询取件", 16);
    while (1)
    {
        
        if (HAL_GPIO_ReadPin(Maglock_In_GPIO_Port, Maglock_In_Pin))
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
        else
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
        
        Num = Press_NumberConfirm();
        
        if (Rx_Fulfill == 1)																																			//判断是否接收到语音输入
        {
            Rx_Fulfill = 0;
            for (a = 0; a < 4; a++)
            {
                if (Array[a] != Data[a])
                {
                    Code_Flag = 1;
                    break;
                }
                else
                    Code_Flag = 2;
                
            }
            
            if (Code_Flag == 1)  // 验证失败
            {
                OLED_ClearArea(0, 16, 128, 64);
                OLED_Update();
                Voice_Array[0] = 2;  // 提示取件码错误
                HAL_UART_Transmit(&huart2, Voice_Array, 1, 0xFFFF);
            }
            else if (Code_Flag == 2)  // 验证成功
            {
                Maglock_On();
                OLED_ShowText(16, 30, "关闭箱门返回", 16);
                memset(Array, 0, 4);
                stmflash_write(FLASH_SAVE_ADDR, (uint16_t *)Array, 4);
                Maglock_Off();
            }
        }
        
        // 超时检查逻辑：10秒未收到输入则提醒，累计2次后返回主界面
        if (Time_Count - ETime_10S > 15)																													//10秒未收到输入
        {
            ETime_10S = Time_Count;
            if (n == 0 && Code_Flag == 0)  // 未收到有效输入且未验证
            {
                Count++;  // 累计提醒次数
                if (Count >= 2)  // 提醒两次后返回主界面
                {
                    Munu_Flag = 0;  // 切换到主界面
                    flag = 2;
                    break;
                }
                // 发送提醒语音
                Voice_Array[0] = 3;
                HAL_UART_Transmit(&huart2, Voice_Array, 1, 0xFFFF);
            }
        }
        
        if (Num == 13)  // 取消操作返回主界面
        {
            Munu_Flag = 0;
            flag = 2;
            break;
        }
    }

    OLED_Clear();
    OLED_Update();
}




void Run()
{
    switch (Munu_Flag)
    {
        case 0: Main_Interface(); break;
        case 1: Express_Deposit(); break;
        case 2: Fetch_ExpressDelivery(); break;
        case 3: Voice_Mode(); break;
    }
}