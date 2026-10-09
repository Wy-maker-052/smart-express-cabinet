/**
 * @file ExtendTimer.h
 * @author
 * @brief 
 * @version 1.2
 * @date 2024-03-05
 * @verbatim
 * 使用说明
 * 将时基Etimer_Ticks()放入定时器中，设置CFG_TIMER_1_TICK_N_MS宏定义值，值为一次中断多少ms
 * 定时任务：将Etimer_Taskloop()放入主函数循环里
 * 	1.使用结构体ETimer_TaskTypeDef创建一个句柄
 *  2.使用初始化函数Etimer_TaskInit()设置运行的任务函数、定时时间
 * 		Etimer_TaskInit(&TimerTask,500,task1,NULL);
 *  3.启动任务
 * 		Etimer_TaskStart(&TimerTask);
 * 	4.停止任务Etimer_TaskStop()
 * 定时置位：
 * 	1.使用结构体ETimer_FlagTypeDef创建一个句柄
 * 	2.使用Etimer_FlagStart()启动计时
 * 	3.Etimer_GetFlag()获取状态
 * 定时：
 * 	1.ETime_TimerTypeDef 创建一个句柄
 * 	2.Etimer_TimeStart()启动计时
 * 	3.Etimer_GetTime()获取计算
 * 	4.Etimer_TimeStop()停止计算
 * 
 * @endverbatim
 * 
 */
#ifndef _ExtendTimer_H_
#define _ExtendTimer_H_
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#ifdef __cplusplus
extern "C"{
#endif

#define CFG_TIMER_1_TICK_N_MS   1

//时间标志变量

#define ETIMER_DATA_T uint32_t
typedef ETIMER_DATA_T Etimer_data_t;

typedef struct ETIMERFLAG_T
{
    ETIMER_DATA_T cur_expired_time;//定时器过期时间
    ETIMER_DATA_T  repeat;//触发时间
    bool sw:1;
 }ETimer_FlagTypeDef;
 
 
typedef struct ETIMETASK_T
{
    ETIMER_DATA_T cur_expired_time;//记录时间
    ETIMER_DATA_T  repeat;//触发时间
    void (*fun)(void *arg);
	void *    arg;      
	struct ETIMETASK_T *next;//指向下一个目标
}ETimer_TaskTypeDef;

/*********/ 

 typedef struct ETIMETIMER_T
{
     ETIMER_DATA_T old_time;//记录旧时间
     ETIMER_DATA_T cur_time;//现在时间
     bool cw;
}ETime_TimerTypeDef;

//ETimerFlagTypeDef 创建应全局变量或者静态变量禁止使用局部变量
/*********标志位*********/ 
void Etimer_FlagStart(ETimer_FlagTypeDef *ETimerFlag,ETIMER_DATA_T timer);
bool Etimer_GetFlag(ETimer_FlagTypeDef *ETimerFlag);//获取状态 
void Etimer_FlagStop(ETimer_FlagTypeDef *ETimerFlag);


/*************任务******************/
void Etimer_TaskInit(ETimer_TaskTypeDef *ETimerTask,ETIMER_DATA_T timer,void (*fun)(void *arg),void *arg);
int8_t Etimer_TaskStop(ETimer_TaskTypeDef *ETimerTask);
int8_t Etimer_TaskStart(ETimer_TaskTypeDef *ETimerTask);
void Etimer_Taskloop(void);

/*************计时***********/
void Etimer_TimeStart(ETime_TimerTypeDef *ETimeTimer);
uint32_t Etimer_GetTime(ETime_TimerTypeDef *ETimeTimer);
void Etimer_TimeStop(ETime_TimerTypeDef *ETimeTimer);
void Etimer_TimeInitStart(ETime_TimerTypeDef *ETimeTimer);
void Etimer_TimeInit(ETime_TimerTypeDef *ETimeTimer);
void Etimer_ClearTime(ETime_TimerTypeDef *ETimeTimer);
	
	
void Etimer_Ticks(void);

#ifdef __cplusplus
}
#endif

#endif

