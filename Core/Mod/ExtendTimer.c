/**
 * @file ExtendTimer.c
 * @author 雨啸青锋 (chenzhiyao@mail.yxqfx.cn)
 * @brief 可以无限扩展的软件定时器，可以定时运行任务，定时状态，以及计时
 * @version 1.2
 * @date 2024-03-05
 * 
 * 
 */
#include "ExtendTimer.h"


/****
 *
 * 定时器扩展
 * 
 * 轮询  标志位
 * 
 * EtimerTicks 
 * 
 * 2023年11月8日 
 *
 * 2023年11月11日 更新 修复一个重复初始化问题
 * 
 * 2023年11月29日 添加计时功能 删掉不必要的逻辑
 * 
 * 2024年03月04日 
 *
 * 版本 V1.2
 * 	
 * 
 * 
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

 //ETimerFlagTypeDef* ETimerFlag_handle = NULL;
ETimer_TaskTypeDef * ETimerTask_handle = NULL;
volatile unsigned int _EtimerTicks;
 

/**
 * @brief 标志位状态置位器启动
 * 
 * @param ETimerFlag 
 * @param timer 
 */
void Etimer_FlagStart(ETimer_FlagTypeDef *ETimerFlag,ETIMER_DATA_T timer)
{	
	ETimerFlag-> repeat = timer;
	ETimerFlag -> cur_expired_time = _EtimerTicks;
	//ETimerFlag -> next = NULL;
	ETimerFlag -> sw = true;

}

/**
 * @brief 获取状态 并且清空标志位
 * @param ETimerFlag 
 * @return 
 */
bool Etimer_GetFlag(ETimer_FlagTypeDef *ETimerFlag)//获取状态 并且清空
{
 	ETimer_FlagTypeDef *ETimer = ETimerFlag;
	if(ETimerFlag -> sw  == false) return false;
	
	if(_EtimerTicks - (ETimer->cur_expired_time)>=ETimer->repeat)//判断时间
	{		
			ETimer->cur_expired_time = _EtimerTicks;
			return true;//时间到 标志位置 true
	}
	return false;
}

/**
 * @brief 标志位事件停止
 * @param ETimerFlag 
 */
void Etimer_FlagStop(ETimer_FlagTypeDef *ETimerFlag)
{
	ETimerFlag -> sw = false;
}


/**********************************************************************************************************************************************
 * @brief 任务初始化
 * @param ETimerTask 
 * @param timer 
 * @param fun 
 * @param arg 
 */
void Etimer_TaskInit(ETimer_TaskTypeDef *ETimerTask,uint32_t timer,void (*fun)(void *arg),void *arg)
{
	ETimerTask ->repeat = timer;
	ETimerTask ->cur_expired_time = _EtimerTicks;
	ETimerTask ->fun = fun;
	ETimerTask ->arg = arg;
	ETimerTask->next = NULL;
	
}

/**
 * @brief 任务启动
 * @param ETimerTask 
 */
int8_t Etimer_TaskStart(ETimer_TaskTypeDef *ETimerTask)
{	
	ETimer_TaskTypeDef *ETimerTaskH = ETimerTask_handle;
	ETimerTask->next = NULL;
	
	if(ETimerTask_handle == NULL) ETimerTask_handle = ETimerTask;//第一次
	else
	{
		if(ETimerTaskH == ETimerTask) return -1;// 判断是否重复
		 while(ETimerTaskH->next) {//寻找下一个的空指针
				if(ETimerTaskH->next == ETimerTask)
					return -1;
			 //寻找插入
			 ETimerTaskH = ETimerTaskH->next;
		 }
		 ETimerTaskH ->next = ETimerTask;
	}
	return 0;
}
/**
 * @brief 任务停止
 * @param ETimerTask 
 */
int8_t Etimer_TaskStop(ETimer_TaskTypeDef *ETimerTask)
{	
	ETimer_TaskTypeDef *ETimerTaskHan = ETimerTask_handle; //获取第一个节点地址
	
	while(ETimerTaskHan)
	{
		if(ETimerTaskHan == ETimerTask)//如果是第一个 清除 
		{
			ETimerTask_handle = ETimerTask -> next;
			break; 
		}
		if(ETimerTaskHan->next == ETimerTask)//找到清除节点的上一个地址 
		{
			ETimerTaskHan->next = ETimerTask->next;//将清除节点的下一个地址赋值上一个节点 
			break; 
		}
		ETimerTaskHan = ETimerTaskHan->next;
	}
	return 0;
}

/**
 * @brief 任务运行
 * @param  
 */
void Etimer_Taskloop(void)
{
	ETimer_TaskTypeDef *ETimerTaskHan = ETimerTask_handle;
	while (ETimerTaskHan)
	{
		if (_EtimerTicks - ETimerTaskHan->cur_expired_time >=  ETimerTaskHan->repeat)//判断时间
		{
			ETimerTaskHan->cur_expired_time = _EtimerTicks;
			ETimerTaskHan->fun(ETimerTaskHan->arg);//函数运行
		}
		ETimerTaskHan = ETimerTaskHan ->next;
	}
}




/***************计时***************************/
/**
 * @brief 计时开始
 * @param ETimeTimer 
 */
void Etimer_TimeStart(ETime_TimerTypeDef *ETimeTimer)
{
	ETimeTimer ->cw = true;
	ETimeTimer ->old_time = _EtimerTicks;
}


void Etimer_TimeInitStart(ETime_TimerTypeDef *ETimeTimer)
{
	ETimeTimer -> cw = true;
	ETimeTimer -> old_time = _EtimerTicks;
	ETimeTimer -> cur_time = 0;
	
}

void Etimer_TimeInit(ETime_TimerTypeDef *ETimeTimer)
{
	ETimeTimer -> cw = false;
	ETimeTimer -> old_time = _EtimerTicks;
	ETimeTimer -> cur_time = 0;
	
}


/**
 * @brief 获取计时时间
 * @param ETimeTimer 
 */
uint32_t Etimer_GetTime(ETime_TimerTypeDef *ETimeTimer)
{
	uint32_t _timer = _EtimerTicks;
	if(ETimeTimer -> cw == true)
	{
		ETimeTimer -> cur_time += (_timer - ETimeTimer ->old_time);
		ETimeTimer -> old_time = _timer;
	}
	return ETimeTimer->cur_time;
}

/**
 * @brief 计时停止
 * @param ETimeTimer 
**/
void Etimer_TimeStop(ETime_TimerTypeDef *ETimeTimer)
{
	ETimeTimer ->old_time = _EtimerTicks;
	ETimeTimer -> cw = false;
}

/**
 * @brief 计时器清0
 *
**/
void Etimer_ClearTime(ETime_TimerTypeDef *ETimeTimer)
{
	ETimeTimer ->cur_time = 0;
	ETimeTimer ->old_time = _EtimerTicks;
}



/************************************/


/**
 * @brief 标志位及任务的时基
 * @param  
 */
void Etimer_Ticks(void)
{
	_EtimerTicks+=CFG_TIMER_1_TICK_N_MS;

}

/*****************/








/**/

/********************/

