/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "st7567.h"
#include "rn8302b.h"
#include "at24c02.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <usart.h>
#include "modbus.h"
void blinkOnIncrement(int variable);
void menu(void);
void Interface_set(void);
uint8_t Get_Keyval(void);
void Current_set(void);
void deplete(void);//����
void Current_Volt_Interface(void);//������ѹ����
void Power_Interface(void);//���ʽ���
void Default_Interface(void);//Ĭ�Ͻ���
void warning_Interface(void);//������ֵҳ��
void Voltage_limit(void);//��ѹ������Χ����
void is_reset(void);//ȷ���ָ�������
void ammeter_set(void);//�������
int hexToComplementInt(const char* hexNum);
uint32_t floatToUint32(float f);
void sendByte(uint8_t byte);
void sendByte_485(uint8_t byte);
void sendFloatAsFourBytes_485(float f) ;
void sendFloatAsFourBytes(float f) ;
void Send_EnergyData(uint8_t Tx_mode_flag);
uint32_t increaseVariable(uint32_t *variable);
uint32_t decreaseVariable(uint32_t *variable);
void Range_detection();
float absoluteValue(float num);
void connection_set(void);//��������

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint8_t page_flag=0;//ҳ����λ

float Ratio=1000;
uint8_t null[60];

float U_volt=220.5,V_volt=220.6,W_volt=220.3;//���ѹ����
float U_current=1.5,V_current=1.6,W_current=1.3;//���ѹ����
float Three_phase_power;//�����ܹ���

float yushu=0;

uint8_t Line1=0;
uint8_t Line2=2;
uint8_t Line3=4;
uint8_t Line4=6;
uint8_t Line5=8;
uint8_t Line6=10;

uint32_t input_current=5000;//һ�α��
uint32_t output_current=50;//���α��
uint32_t input_current_new;//ȷ��һ��
uint32_t output_current_new;//ȷ�϶���
uint8_t input_current_code[4]={0x00,0x00,0x00,0x00};
uint8_t output_current_code[4]={0x00,0x00,0x00,0x00};

float data;

uint8_t eeprom[4]={0x00,0x00,0x13,0x88};
uint8_t eeprom1[4]={0x00,0x00,0x00,0x05};


int i;

uint32_t t=0;

uint8_t page1[4]={0x01},page2[4]={0x02},page3[4]={0x03},page4[4]={0x04};//��ʾ�������
uint8_t page_buff[1];

uint32_t UA ;//��ѹ�Ĵ���
uint32_t UB ;
uint32_t UC ;
float UA_val;//��ѹʵ��ֵ
float UB_val;
float UC_val;
uint32_t UA_val_u32,UB_val_u32,UC_val_u32;
uint16_t UA_val_h,UA_val_l;

uint32_t Voltage_threshold_Top=300;
uint8_t Voltage_threshold_Top_code[4];//��ѹ����
uint32_t Voltage_threshold_Bottom=100;
uint8_t Voltage_threshold_Bottom_code[4];//��ѹ����


uint32_t IA ;//��������ֵ
uint32_t IB ;
uint32_t IC ;
float IA_val;//����ʵ��ֵ
float IB_val;
float IC_val;
uint32_t Current_threshold_A;//������ֵ
uint32_t Current_threshold_B;
uint32_t Current_threshold_C;
uint32_t Current_threshold_ALL=50;
uint8_t Current_threshold_ALL_code[4];

int32_t PA;
int32_t PB;
int32_t PC;
float PA_val;//��yougong����ʵ��ֵ
float PB_val;
float PC_val;
float Power_threshold_A;//������ֵ
float Power_threshold_B;
float Power_threshold_C;
uint32_t Power_threshold_ALL=1000;
uint8_t Power_threshold_ALL_code[4];

int32_t FEQT ;
float FEQT_val;

uint32_t Deplete_A ;
float Deplete_A_val;
uint32_t Deplete_A_Initial ;
uint8_t Deplete_A_Code[4];

uint32_t Deplete_B ;
float Deplete_B_val;
uint32_t Deplete_B_Initial ;
uint8_t Deplete_B_Code[4];

uint32_t Deplete_C ;
float Deplete_C_val;//���๦��
uint32_t Deplete_C_Initial ;
uint8_t Deplete_C_Code[4];

uint32_t Deplete_all ;//���๦��
float Deplete_all_val;
uint32_t Deplete_all_Initial ;
uint8_t Deplete_all_Code[4];
int Deplete;

uint8_t combinedArr[16];//�ϲ�����

uint32_t Deplete_threshold_ALL=0;
uint8_t Deplete_threshold_ALL_code[4];

uint32_t FPTFCnt_all;//���๦�����������
uint32_t FPTFCnt_all_val;//���๦���������

uint32_t UFreq;
float UFreq_val;


uint32_t RN8302_HFConst_1=0;
uint32_t RN8302_HFConst_2=0;

extern uint8_t KEY_falg;
uint8_t menu_flag=2;

uint8_t key_temp;

float pwr;

uint8_t connection_mode=0x00;//����ģʽ

typedef struct {
  int32_t value : 24;  // ����һ��λ���Ա��ռ��24λ���洢ֵ
} int24_t_simulated;
	 
typedef struct {
	 int32_t value : 18;
} int18_t_simulated;

int18_t_simulated powerFactorRegister;

int24_t_simulated myNumber;

float convertToFloat(int24_t_simulated number);
int convertToSignedInt(int18_t_simulated number);

extern uint8_t err[4];

uint8_t Electricity_meter_Add=0x00;//����ַ
uint8_t	Gather_Frequency=1;//������ɼ�Ƶ�ʣ���n��ɼ�һ��
uint8_t UART_frequency=2;//����Ƶ�ʣ�n�뷢��һ��
uint32_t UART_BaudRate=115200;//���Ͳ�����

// �������ȫ�ֱ���
int isIncreasingPressed = 0;
// ע�ͣ���־�Ƿ����ڽ�������������0 ��ʾδ������������1 ��ʾ������������
int incrementSpeed = 1;
// ע�ͣ��������ٶȣ���ʼΪ 1��
int inStartTime = 0;
// ע�ͣ�����������ʼ��ʱ���ǡ�
int inElapsedTime = 0;
// ע�ͣ���������������ʱ�䡣
const int inSpeedUpThreshold = 30; 
// ע�ͣ���Լ���� 1 �루����ѭ��ÿ��ִ�� 33.3 ���룩�������ж������ٶ��Ƿ�������

// �Լ����ȫ�ֱ���
int isDecreasingPressed = 0;
// ע�ͣ���־�Ƿ����ڽ����Լ�������0 ��ʾδ�����Լ�����1 ��ʾ�����Լ�����
int decrementSpeed = 1;
// ע�ͣ��Լ����ٶȣ���ʼΪ 1��
int deStartTime = 0;
// ע�ͣ��Լ�������ʼ��ʱ���ǡ�
int deElapsedTime = 0;
// ע�ͣ��Լ�����������ʱ�䡣
const int deSpeedUpThreshold = 30; 
// ע�ͣ���Լ���� 1 �루����ѭ��ÿ��ִ�� 1 ���룩�������ж��Լ��ٶ��Ƿ�������

uint8_t USER_ERR_FALG;

uint8_t key_buzzer;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId OperationHandle;
osThreadId Display_InformaHandle;
osThreadId Read_ACenergyHandle;
osThreadId Ethernet_Rs485Handle;
osThreadId myTask05Handle;
osThreadId myTask06Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartTask02(void const * argument);
void StartTask03(void const * argument);
void StartTask04(void const * argument);
void StartTask05(void const * argument);
void StartTask06(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of Operation */
  osThreadDef(Operation, StartDefaultTask, osPriorityHigh, 0, 128);
  OperationHandle = osThreadCreate(osThread(Operation), NULL);

  /* definition and creation of Display_Informa */
  osThreadDef(Display_Informa, StartTask02, osPriorityIdle, 0, 128);
  Display_InformaHandle = osThreadCreate(osThread(Display_Informa), NULL);

  /* definition and creation of Read_ACenergy */
  osThreadDef(Read_ACenergy, StartTask03, osPriorityLow, 0, 128);
  Read_ACenergyHandle = osThreadCreate(osThread(Read_ACenergy), NULL);

  /* definition and creation of Ethernet_Rs485 */
  osThreadDef(Ethernet_Rs485, StartTask04, osPriorityHigh, 0, 128);
  Ethernet_Rs485Handle = osThreadCreate(osThread(Ethernet_Rs485), NULL);

  /* definition and creation of myTask05 */
  osThreadDef(myTask05, StartTask05, osPriorityBelowNormal, 0, 128);
  myTask05Handle = osThreadCreate(osThread(myTask05), NULL);

  /* definition and creation of myTask06 */
  osThreadDef(myTask06, StartTask06, osPriorityRealtime, 0, 128);
  myTask06Handle = osThreadCreate(osThread(myTask06), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
//	AT24C02_write(0x40,null,60);
//	osDelay(50);
//	AT24C02_write(0x04,eeprom1,4);
//	osDelay(50);

				


				AT24C02_read(0x00,input_current_code, 4);
				input_current=input_current_code[0]<<24|input_current_code[1]<<16|input_current_code[2]<<8|input_current_code[3];
				AT24C02_read(0x04,output_current_code, 4);
				output_current=output_current_code[0]<<24|output_current_code[1]<<16|output_current_code[2]<<8|output_current_code[3];
				AT24C02_read(0x14,Voltage_threshold_Top_code,4);
				Voltage_threshold_Top=Voltage_threshold_Top_code[0]<<24|Voltage_threshold_Top_code[1]<<16|Voltage_threshold_Top_code[2]<<8|Voltage_threshold_Top_code[3];
				AT24C02_read(0x18,Voltage_threshold_Bottom_code,4);
				Voltage_threshold_Bottom=Voltage_threshold_Bottom_code[0]<<24|Voltage_threshold_Bottom_code[1]<<16|Voltage_threshold_Bottom_code[2]<<8|Voltage_threshold_Bottom_code[3];
				AT24C02_read(0x22,Current_threshold_ALL_code,4);
				Current_threshold_ALL=Current_threshold_ALL_code[0]<<24|Current_threshold_ALL_code[1]<<16|Current_threshold_ALL_code[2]<<8|Current_threshold_ALL_code[3];
				AT24C02_read(0x26,Power_threshold_ALL_code,4);
				Power_threshold_ALL=Power_threshold_ALL_code[3]<<8|Power_threshold_ALL_code[2]<<24|Power_threshold_ALL_code[1]<<16|Power_threshold_ALL_code[0];
				input_current_new=input_current;
				AT24C02_read(0x30,Deplete_threshold_ALL_code,4);
				Deplete_threshold_ALL=Deplete_threshold_ALL_code[3]<<24|Deplete_threshold_ALL_code[2]<<8|Deplete_threshold_ALL_code[1]<<16|Deplete_threshold_ALL_code[0];
				
				
				
				AT24C02_read(0x40,Deplete_A_Code,4);
				Deplete_A_Initial=Deplete_A_Code[3]<<24|Deplete_A_Code[2]<<8|Deplete_A_Code[1]<<16|Deplete_A_Code[0];
				AT24C02_read(0x44,Deplete_B_Code,4);
				Deplete_B_Initial=Deplete_B_Code[3]<<24|Deplete_B_Code[2]<<8|Deplete_B_Code[1]<<16|Deplete_B_Code[0];
				AT24C02_read(0x48,Deplete_C_Code,4);
				Deplete_C_Initial=Deplete_C_Code[3]<<24|Deplete_C_Code[2]<<8|Deplete_C_Code[1]<<16|Deplete_C_Code[0];
				AT24C02_read(0x52,Deplete_all_Code,4);
				Deplete_all_Initial=Deplete_all_Code[3]<<24|Deplete_all_Code[2]<<8|Deplete_all_Code[1]<<16|Deplete_all_Code[0];
				
				AT24C02_read(0x08,page_buff,1);
				
				output_current_new=output_current;
				Ratio=input_current_new/(float)(output_current_new/10.0);
				
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the Operation thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {

		UA=READ_SPI(RN8302_UA ,4);//��ȡ��ѹ��Чֵ   ת��ϵ��=232.7/40,354,702=5.766366
		U_volt=UA_val=0.000011964538*UA;
		UB=READ_SPI(RN8302_UB ,4);//��ȡ��ѹ��Чֵ   ת��ϵ��=232.7/2,211,394,492=1.052277
		V_volt=UB_val=0.000011964879*UB;
		UC=READ_SPI(RN8302_UC ,4);//��ȡ��ѹ��Чֵ   ת��ϵ��=232.7/2,211,301,255=1.052321
		W_volt=UC_val=0.000011964741*UC;
		UA_val_u32=(uint32_t)UA_val*1000;UB_val_u32=(uint32_t)UB_val;UC_val_u32=(uint32_t)UC_val;
		UA_val_h=UA_val_u32<<16;UA_val_l=UA_val_u32;
		
		IA=READ_SPI(RN8302_IA,4);//��ȡ������Чֵ    ת��ϵ��=1000/12,404,291=0.000080616
		IA_val=((IA*0.0000027644127));
		IB=READ_SPI(RN8302_IB,4);//��ȡ������Чֵ		 ת��ϵ��=1000/11,802,996=0.00008472
		IB_val=((IB*0.0000027644127));
		IC=READ_SPI(RN8302_IC,4);//��ȡ������Чֵ		 ת��ϵ��=1000/9339229=0.000107079
		IC_val=((IC*0.0000027644127));
		
							//0.00000000089
		//���ڻ�����150��5    0.054/1,232,186=0.00000044
		//�󻥸�����ȣ�5000/5=1000
		//С��������ȣ�5000/2.5=2000 A:0.0000006011  B:0.0000006021  C:0.0000006036
		//ʵ�ʵ���=�Ĵ���ֵ*ϵ��*��ֵ
		
		Ratio=input_current_new/(float)(output_current_new/10.0);
		
		PA=(int32_t)(READ_SPI(RN8302_PA  ,4));//��ȡ�й�����
		Power_threshold_A=PA;
		PA_val=absoluteValue((0.000300414466015*Power_threshold_A));
		PB=(int32_t)READ_SPI(RN8302_PB  ,4);//��ȡ�й�����
		Power_threshold_B=PB;
		PB_val=absoluteValue((0.00030014466015*Power_threshold_B));
		PC=(int32_t)READ_SPI(RN8302_PC  ,4);//��ȡ�й�����
		Power_threshold_C=PC;
		PC_val=absoluteValue((0.00030014466015*Power_threshold_C));
		
		FEQT =(int32_t)READ_SPI(RN8302_PT ,4);//��ȡ�й�����
		Three_phase_power=FEQT;
		FEQT_val=absoluteValue(0.000300414466015*Three_phase_power*2000.0/(Ratio));
		
		myNumber.value=READ_SPI(RN8302_PfTA ,3);//��ȡ��������
		pwr=convertToFloat(myNumber);
		osDelay(50);
		
		Deplete_A=READ_SPI(RN8302_EPA  ,3);/*"	A ���й������Ĵ���	"*/  
		Deplete_A_val=((Deplete_A+Deplete_A_Initial)*0.001088138291632);
		Deplete_A_Code[0]=(Deplete_A+Deplete_A_Initial)>>24;Deplete_A_Code[1]=(Deplete_A+Deplete_A_Initial)>>16;Deplete_A_Code[2]=(Deplete_A+Deplete_A_Initial)>>8;Deplete_A_Code[0]=(Deplete_A+Deplete_A_Initial);
											
		
		
		Deplete_B=READ_SPI(RN8302_EPB ,3);/*"	B ���й������Ĵ���	"*/   
		Deplete_B_val=((Deplete_B+Deplete_B_Initial)*0.001088138291632);
		Deplete_B_Code[0]=(Deplete_B+Deplete_B_Initial)>>24;Deplete_B_Code[1]=(Deplete_B+Deplete_B_Initial)>>16;Deplete_B_Code[2]=(Deplete_B+Deplete_B_Initial)>>8;Deplete_B_Code[0]=(Deplete_B+Deplete_B_Initial);
		
		Deplete_C=READ_SPI(RN8302_EPC ,3);/*"	C ���й������Ĵ���	"*/   
		Deplete_C_val=((Deplete_C+Deplete_C_Initial)*0.001088138291632);
		
		Deplete_C_Code[0]=(Deplete_C+Deplete_C_Initial)>>24;Deplete_C_Code[1]=(Deplete_C+Deplete_C_Initial)>>16;Deplete_C_Code[2]=(Deplete_C+Deplete_C_Initial)>>8;Deplete_C_Code[0]=(Deplete_C+Deplete_C_Initial);

		
		Deplete_all=READ_SPI(RN8302_EPT   ,3);/*"	�����й������Ĵ���	"*/   
		Deplete_all_val=((Deplete_all+Deplete_all_Initial)*0.001088138291632);
		Deplete_all_Code[0]=(Deplete_all+Deplete_all_Initial)>>24;Deplete_all_Code[1]=(Deplete_all+Deplete_all_Initial)>>16;Deplete_all_Code[2]=(Deplete_all+Deplete_all_Initial)>>8;Deplete_all_Code[0]=(Deplete_all+Deplete_all_Initial);
		Deplete=Deplete_all_val;
		
		UFreq  =READ_SPI(RN8302_UFreq ,3);/*"	��ѹƵ�ʼĴ���	"*/   
		UFreq_val=(float)(65536000.0/(float)UFreq);
		
		
//    unsigned char *pSrc[4] = {Deplete_A_Code, Deplete_B_Code, Deplete_C_Code, Deplete_all_Code};
//    for (int i = 0; i < 4; i++) {
//        for (int j = 0; j < 4; j++) {
//            combinedArr[i * 4 + j] = pSrc[i][j];
//        }
//    }//�ϲ�������ٶϵ籣��
	
//		printf("A���ѹ:%.1fV B���ѹ:%.1fV C���ѹ:%.1fV\r\n",UA_val,UB_val,UC_val);
//		printf("A�����:%.2fA B�����:%.2fA C�����:%.2fA\r\n",IA_val,	IB_val,IC_val);
//		printf("A�๦��:%.1fW B�๦��:%.1fW C�๦��:%.1fW ���๦��:%.1fW\r\n",PA_val,	PB_val,PC_val,FEQT_val);
//		printf("A����ʱ���ģ�%.1FW/H B����ʱ���ģ�%.1FW/H C����ʱ���ģ�%.1F �����ۼƹ���:%.1FW/H\r\n",Deplete_A_val,Deplete_B_val,Deplete_C_val,Deplete_all_val);
//		printf("��ѹƵ�ʣ�%d",UFreq );
//		printf("���๦��������%.2f",pwr);

//unsigned int num = 0x436CB08F;
//    float f = *(float *)&num;
//    printf("Converted float value: %f\n", f);
    osDelay(500);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the Display_Informa thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void const * argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
  for(;;)
  {
key_temp=Get_Keyval();/***************************************����ɨ��**********************************/

		if(page_flag==0)/***************************************��ҳ��**********************************/
		{
			AT24C02_read(0x08,page_buff,1);
			switch(page_buff[0])
			{
				case 0x01:
					Default_Interface();
				break;
				case 0x02:
					Current_Volt_Interface();
				break;
				case 0x03:
					Power_Interface();
				break;
				case 0x04:
					deplete();
				break;
				default:
					//Default_Interface();
				break;
			}
			
			
			if(Get_Keyval()==4)
			{
				while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
				page_flag=1;
				LDZ_Clear();
			}
	}
		
	
/*   page_flag   */
/*  0-����Ĭ�Ͻ���   */
/*  1-���˵� >       ��������          �������        ������ֵ          �ָ�����  */
	//��������->Ĭ�Ͻ��桢��ѹ���������๦�ʡ������ܺ�
	//�������->һ����Ȧ��������Ȧ

		else if(page_flag==1)/***************************************ĸ�˵�**********************************/
		{
			menu();
			while(page_flag==1)
			{
				if(Get_Keyval()==1)
				{
					while(HAL_GPIO_ReadPin(K1_GPIO_Port,K1_Pin)==0);
					menu_flag++;
					if(menu_flag>4)menu_flag=1;//�˵��޷�
				}
				if(Get_Keyval()==2)
				{
					while(HAL_GPIO_ReadPin(K2_GPIO_Port,K2_Pin)==0);
					menu_flag--;
					if(menu_flag<1)menu_flag=4;//�˵��޷�
				}
				switch(menu_flag)
				{
					case 1 :
						LDZ_ShowASC16(0,0,12);
						LDZ_ShowASC16(2,0,13);
						LDZ_ShowASC16(4,0,13);
						LDZ_ShowASC16(6,0,13);
					if(Get_Keyval()==4)//����ȷ�ϼ�
					{
						while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
						page_flag=2;
						LDZ_Clear();
					}
					break;break;
					
					case 2 :
						LDZ_ShowASC16(0,0,13);
						LDZ_ShowASC16(2,0,12);
						LDZ_ShowASC16(4,0,13);
						LDZ_ShowASC16(6,0,13);
					if(Get_Keyval()==4)//����ȷ�ϼ�
					{
						while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
						page_flag=3;
					}
					break;break;
					
					case 3 :
						LDZ_ShowASC16(0,0,13);
						LDZ_ShowASC16(2,0,13);
						LDZ_ShowASC16(4,0,12);
						LDZ_ShowASC16(6,0,13);
					if(Get_Keyval()==4)//����ȷ�ϼ�
					{
						while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
						page_flag=6;
					}
					break;
					
					case 4 :
						LDZ_ShowASC16(0,0,13);
						LDZ_ShowASC16(2,0,13);
						LDZ_ShowASC16(4,0,13);
						LDZ_ShowASC16(6,0,12);
					if(Get_Keyval()==4)//����ȷ�ϼ�
					{
						while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
						page_flag=14;
					}
					break;
					default:break;
				}
				if(Get_Keyval()==3)
				{
					while(HAL_GPIO_ReadPin(K3_GPIO_Port,K3_Pin)==0);
					page_flag=0;LDZ_Clear();
					break;
				}
			}
		}
		
		else if(page_flag==2)//��������
		{
			Interface_set();
			while(page_flag==2)
			{
				if(Get_Keyval()==1)
				{
					while(HAL_GPIO_ReadPin(K1_GPIO_Port,K1_Pin)==0);
					menu_flag++;
					if(menu_flag>4)menu_flag=1;//�˵��޷�
				}
				if(Get_Keyval()==2)
				{
					while(HAL_GPIO_ReadPin(K2_GPIO_Port,K2_Pin)==0);
					menu_flag--;
					if(menu_flag<1)menu_flag=4;//�˵��޷�
				}
				switch(menu_flag)
				{
					case 1 :
						LDZ_ShowASC16(0,0,12);
						LDZ_ShowASC16(2,0,13);
						LDZ_ShowASC16(4,0,13);
						LDZ_ShowASC16(6,0,13);
						if(Get_Keyval()==4)//����ȷ�ϼ�
						{
							while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
							AT24C02_write(0x08,page1,1);//
							AT24C02_read(0x08,page_buff,1);
							page_flag=0;LDZ_Clear();
						}
					break;
					
					case 2 :
						LDZ_ShowASC16(0,0,13);
						LDZ_ShowASC16(2,0,12);
						LDZ_ShowASC16(4,0,13);
						LDZ_ShowASC16(6,0,13);
						if(Get_Keyval()==4)//����ȷ�ϼ�
						{
							while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
							AT24C02_write(0x08,page2,1);//
							AT24C02_read(0x08,page_buff,1);
							page_flag=0;LDZ_Clear();
						}
					break;
					
					case 3 :
						LDZ_ShowASC16(0,0,13);
						LDZ_ShowASC16(2,0,13);
						LDZ_ShowASC16(4,0,12);
						LDZ_ShowASC16(6,0,13);
						if(Get_Keyval()==4)//����ȷ�ϼ�
						{
							while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
							AT24C02_write(0x08,page3,1);//
							AT24C02_read(0x08,page_buff,1);
							page_flag=0;LDZ_Clear();
						}
					break;
					
					case 4 :
						LDZ_ShowASC16(0,0,13);
						LDZ_ShowASC16(2,0,13);
						LDZ_ShowASC16(4,0,13);
						LDZ_ShowASC16(6,0,12);
						if(Get_Keyval()==4)//����ȷ�ϼ�
						{
							while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
							AT24C02_write(0x08,page4,1);//
							AT24C02_read(0x08,page_buff,1);
							page_flag=0;LDZ_Clear();
						}
					break;
					default:break;
				}
			if(Get_Keyval()==3)
				{
					while(HAL_GPIO_ReadPin(K3_GPIO_Port,K3_Pin)==0);
					page_flag=1;
					break;
				}
			}
			
		}
		
	  else if(page_flag==3)//�������
		{
			Current_set();
			while(page_flag==3)
			{
				AT24C02_read(0x00,input_current_code, 4);
				input_current=input_current_code[0]<<24|input_current_code[1]<<16|input_current_code[2]<<8|input_current_code[3];
				AT24C02_read(0x04,output_current_code, 4);
				output_current=output_current_code[0]<<24|output_current_code[1]<<16|output_current_code[2]<<8|output_current_code[3];
				Ratio=input_current/output_current;
					if(Get_Keyval()==1)
				{
					while(HAL_GPIO_ReadPin(K1_GPIO_Port,K1_Pin)==0);
					//while(KEY_falg!=0);
					menu_flag++;
					if(menu_flag>2)menu_flag=1;//�˵��޷�
				}
				if(Get_Keyval()==2)
				{
					while(HAL_GPIO_ReadPin(K2_GPIO_Port,K2_Pin)==0);
					//while(KEY_falg!=0);
					menu_flag--;
					if(menu_flag<1)menu_flag=2;//�˵��޷�
				}
				switch(menu_flag)
				{
					case 1 :
						LDZ_ShowASC16(4,0,12);
						LDZ_ShowASC16(6,0,13);
					if(Get_Keyval()==4)//����ȷ�ϼ�
					{
						while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
						page_flag=4;//һ�α�Ƚ���
					}
					break;
					
					case 2 :
						LDZ_ShowASC16(4,0,13);
						LDZ_ShowASC16(6,0,12);
					if(Get_Keyval()==4)//����ȷ�ϼ�
					{
						while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
						page_flag=5;//һ�α�Ƚ���
					}
					break;

					default:break;
				}
			if(Get_Keyval()==3)
				{
					while(HAL_GPIO_ReadPin(K3_GPIO_Port,K3_Pin)==0);
					page_flag=1;//�������˵�
					break;
				}
				
				LDZ_ShowASC16(2, 0, (input_current/1000)%10); 
				LDZ_ShowASC16(2,8 , (input_current/100)%10); 
				LDZ_ShowASC16(2,16, (input_current/10)%10); 
				LDZ_ShowASC16(2,24, input_current%10); 
				
				LDZ_ShowASC16(2,45,11);
				
				LDZ_ShowASC16(2,64, (output_current/100)%10); 
				LDZ_ShowASC16(2,64+8 , (output_current/10)%10); 
				LDZ_ShowASC16(2, 64+16, 10);
				LDZ_ShowASC16(2,64+24, output_current%10); 
			}
			
		}

		else if(page_flag==4)//һ�α��
		{
			uint8_t tim;
			LDZ_Clear();
			while(page_flag==4)
			{
				if(Get_Keyval()==1)
				{
					if(input_current<9999)
					input_current++;
				}

				if(Get_Keyval()==2)
				{
					if(input_current>0)
					input_current--;
				}
				tim=0;

			LDZ_ShowASC16(3, 66-25, (input_current/1000)%10); 
			LDZ_ShowASC16(3, 77-25, (input_current/100)%10); 
			LDZ_ShowASC16(3, 88-25, (input_current/10)%10); 
			LDZ_ShowASC16(3, 99-25, input_current%10); 
				
				
			if(Get_Keyval()==3)
				{
					while(HAL_GPIO_ReadPin(K3_GPIO_Port,K3_Pin)==0);
					page_flag=3;//�������˵�
					break;
				}
				if(Get_Keyval()==4)
				{
					while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
					input_current_code[0]=input_current>>24;input_current_code[1]=input_current>>16;input_current_code[2]=input_current>>8;input_current_code[3]=input_current;
					AT24C02_write(0x00, input_current_code, 4);
					page_flag=3;//�������˵�
					input_current_new=input_current;
					output_current_new=output_current;
					break;
				}
			}
		}
		
		else if(page_flag==5)//���α��
		{
			uint8_t tim;
			LDZ_Clear();
			while(page_flag==5)
			{
				if(Get_Keyval()==1)
				{
					while(HAL_GPIO_ReadPin(K1_GPIO_Port,K1_Pin)==0);
					//while(KEY_falg!=0);
					if(output_current<9999)
					output_current+=5;
				}
				if(Get_Keyval()==2)
				{
					while(HAL_GPIO_ReadPin(K2_GPIO_Port,K2_Pin)==0);
					//while(KEY_falg!=0);
					if(output_current>1)
					output_current-=5;
				}

			LDZ_ShowASC16(3, 66-25, (output_current/100)%10); 
			LDZ_ShowASC16(3, 77-25, (output_current/10)%10); 
			LDZ_ShowASC16(3, 88-25, 10);
			LDZ_ShowASC16(3, 99-25, output_current%10); 

			if(Get_Keyval()==3)
				{
					while(HAL_GPIO_ReadPin(K3_GPIO_Port,K3_Pin)==0);
					page_flag=3;//�������˵�
					break;
				}
				if(Get_Keyval()==4)
				{
					while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
					output_current_code[0]=output_current>>24;output_current_code[1]=output_current>>16;output_current_code[2]=output_current>>8;output_current_code[3]=output_current;
					AT24C02_write(0x04, output_current_code, 4);
					page_flag=3;//�������˵�
					output_current_new=output_current;
					input_current_new=input_current;
					break;
				}
			}
		}
		else if(page_flag==6)//��ֵҳ��
		{
			warning_Interface();
			while(page_flag==6)
			{
				if(Get_Keyval()==1)
				{
					while(HAL_GPIO_ReadPin(K1_GPIO_Port,K1_Pin)==0);
					menu_flag++;
					if(menu_flag>4)menu_flag=1;//�˵��޷�
				}
				if(Get_Keyval()==2)
				{
					while(HAL_GPIO_ReadPin(K2_GPIO_Port,K2_Pin)==0);
					menu_flag--;
					if(menu_flag<1)menu_flag=4;//�˵��޷�
				}
				switch(menu_flag)
				{
					case 1 ://��ѹ
						LDZ_ShowASC16(0,0,12);
						LDZ_ShowASC16(2,0,13);
						LDZ_ShowASC16(4,0,13);
						LDZ_ShowASC16(6,0,13);
						if(Get_Keyval()==4)//����ȷ�ϼ�
						{
							while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
							page_flag=7;
						}
					break;
					
					case 2 ://����
						LDZ_ShowASC16(0,0,13);
						LDZ_ShowASC16(2,0,12);
						LDZ_ShowASC16(4,0,13);
						LDZ_ShowASC16(6,0,13);
						if(Get_Keyval()==4)//����ȷ�ϼ�
						{
							while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
							
							page_flag=8;
						}
					break;
					
					case 3 ://�繦��
						LDZ_ShowASC16(0,0,13);
						LDZ_ShowASC16(2,0,13);
						LDZ_ShowASC16(4,0,12);
						LDZ_ShowASC16(6,0,13);
						if(Get_Keyval()==4)//����ȷ�ϼ�
						{
							while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
							page_flag=10;
						}
					break;
					
					case 4 ://�ܺ�
						LDZ_ShowASC16(0,0,13);
						LDZ_ShowASC16(2,0,13);
						LDZ_ShowASC16(4,0,13);
						LDZ_ShowASC16(6,0,12);
						if(Get_Keyval()==4)//����ȷ�ϼ�
						{
							while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
							page_flag=11;
						}
					break;
					default:break;
				}
			if(Get_Keyval()==3)
				{
					while(HAL_GPIO_ReadPin(K3_GPIO_Port,K3_Pin)==0);
					page_flag=1;
					break;
				}
		}
	}
	
		else if(page_flag==7)//��ѹ��ֵҳ��
		{
			Voltage_limit();
			while(page_flag==7)
			{
				if(Get_Keyval()==1)
				{
					while(HAL_GPIO_ReadPin(K1_GPIO_Port,K1_Pin)==0);
					menu_flag++;
					if(menu_flag>2)menu_flag=1;//�˵��޷�
				}
				if(Get_Keyval()==2)
				{
					while(HAL_GPIO_ReadPin(K2_GPIO_Port,K2_Pin)==0);
					menu_flag--;
					if(menu_flag<1)menu_flag=2;//�˵��޷�
				}
				switch(menu_flag)
				{
					case 1 ://��ѹ����

						LDZ_ShowASC16(2,0,12);
						LDZ_ShowASC16(4,0,13);

						if(Get_Keyval()==4)//����ȷ�ϼ�
						{
							while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
							page_flag=9;
						}
					break;
					
					case 2 :

						LDZ_ShowASC16(2,0,13);
						LDZ_ShowASC16(4,0,12);

						if(Get_Keyval()==4)//����ȷ�ϼ�
						{
							while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
							
							page_flag=12;
							break;
						}
					break;
					
					
					default:break;
				}
			if(Get_Keyval()==3)
				{
					while(HAL_GPIO_ReadPin(K3_GPIO_Port,K3_Pin)==0);
					page_flag=1;
					break;
				}
				
		}
	}
		
	else if(page_flag==8)//������ֵ����ҳ��
		{
			LDZ_Clear();
			while(page_flag==8)
			{
				if(Current_threshold_ALL >99 )Current_threshold_ALL=99;
				
				if(Get_Keyval()==1)
				{
					while(HAL_GPIO_ReadPin(K1_GPIO_Port,K1_Pin)==0);
					Current_threshold_ALL++;
				}
				if(Get_Keyval()==2)
				{
					while(HAL_GPIO_ReadPin(K2_GPIO_Port,K2_Pin)==0);
					
					if(Current_threshold_ALL >0 ) Current_threshold_ALL--;
				}
				
			if(Get_Keyval()==3)
				{
					while(HAL_GPIO_ReadPin(K3_GPIO_Port,K3_Pin)==0);
					page_flag=6;
					break;
				}
				LDZ_ShowASC16(3,66-25 , (Current_threshold_ALL/100)%10); 
				LDZ_ShowASC16(3,77-25, (Current_threshold_ALL/10)%10); 
				LDZ_ShowASC16(3,88-25, Current_threshold_ALL%10); 
				LDZ_ShowENG16(3, 99-25, 0);
				
				if(Get_Keyval()==3)
				{
					while(HAL_GPIO_ReadPin(K3_GPIO_Port,K3_Pin)==0);
					page_flag=6;//�������˵�
					break;
				}
				else if(Get_Keyval()==4)
				{
					while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
					Current_threshold_ALL_code[0]=Current_threshold_ALL>>24;Current_threshold_ALL_code[1]=Current_threshold_ALL>>16;
					Current_threshold_ALL_code[2]=Current_threshold_ALL>>8;Current_threshold_ALL_code[3]=Current_threshold_ALL;
					AT24C02_write(0x22,Current_threshold_ALL_code,4);
					page_flag=6;//�������˵�
					break;
				}
		}
	}
		
		else if(page_flag==9)//��ѹ��ֵ����ҳ��
		{
			LDZ_Clear();
			while(page_flag==9)
			{
				if(Voltage_threshold_Top>999)Voltage_threshold_Top=999;
				
				if(Get_Keyval()==1)
				{
					if(Voltage_threshold_Top<999)
					{
						Voltage_threshold_Top = increaseVariable(&Voltage_threshold_Top);
						//Voltage_threshold_Top++;
					}else Voltage_threshold_Top=999;
				}
				else
					{// �ɿ���ʱ���ñ�־���ٶ�
                        // �ɿ���ʱ���ñ�־���ٶȺ�ʱ����ر���
            isIncreasingPressed = 0;
            // ע�ͣ�����������־Ϊδ���¡�
            
            incrementSpeed = 1;
            // ע�ͣ����������ٶ�Ϊ 1��
            
            inElapsedTime = 0;
            // ע�ͣ���������������ʱ��Ϊ 0��
            inStartTime = 0;
            // ע�ͣ�����������ʼʱ����Ϊ 0��
						
					}
					
				if(Get_Keyval()==2)
				{
					if(Voltage_threshold_Top >0 )
					{
						Voltage_threshold_Top=decreaseVariable(&Voltage_threshold_Top);
//						Voltage_threshold_Top--;
					}
				}
				else
					{// �ɿ���ʱ���ñ�־���ٶ�
                        // �ɿ���ʱ���ñ�־���ٶȺ�ʱ����ر���
            isIncreasingPressed = 0;
            // ע�ͣ�����������־Ϊδ���¡�
            
            incrementSpeed = 1;
            // ע�ͣ����������ٶ�Ϊ 1��
            
            inElapsedTime = 0;
            // ע�ͣ���������������ʱ��Ϊ 0��
            inStartTime = 0;
            // ע�ͣ�����������ʼʱ����Ϊ 0��
						
					}
				
			if(Get_Keyval()==3)
				{
					while(HAL_GPIO_ReadPin(K3_GPIO_Port,K3_Pin)==0);
					page_flag=6;
					break;
				}
				LDZ_ShowASC16(3,66-25 , (Voltage_threshold_Top/100)%10); 
				LDZ_ShowASC16(3,77-25, (Voltage_threshold_Top/10)%10); 
				LDZ_ShowASC16(3,88-25, Voltage_threshold_Top%10); 
				LDZ_ShowENG16(3, 99-25, 21);
				
				if(Get_Keyval()==3)
				{
					while(HAL_GPIO_ReadPin(K3_GPIO_Port,K3_Pin)==0);
					page_flag=6;//�������˵�
					break;
				}
				else if(Get_Keyval()==4)
				{
					while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
					Voltage_threshold_Top_code[0]=Voltage_threshold_Top>>24;Voltage_threshold_Top_code[1]=Voltage_threshold_Top>>16;
					Voltage_threshold_Top_code[2]=Voltage_threshold_Top>>8;Voltage_threshold_Top_code[3]=Voltage_threshold_Top;
					AT24C02_write(0x14,Voltage_threshold_Top_code,4);
					osDelay(100);
					page_flag=6;//�������˵�
					break;
				}
		}
	}
		
	else if(page_flag==10)//������ֵҳ��
		{
			LDZ_Clear();
			while(page_flag==10)
			{
				if(Get_Keyval()==1)
				{
					if(Power_threshold_ALL<90000)
					{
						Power_threshold_ALL = increaseVariable(&Power_threshold_ALL);
						//Power_threshold_ALL++;
					}
				}
				else
					{// �ɿ���ʱ���ñ�־���ٶ�
                        // �ɿ���ʱ���ñ�־���ٶȺ�ʱ����ر���
            isIncreasingPressed = 0;
            // ע�ͣ�����������־Ϊδ���¡�
            
            incrementSpeed = 1;
            // ע�ͣ����������ٶ�Ϊ 1��
            
            inElapsedTime = 0;
            // ע�ͣ���������������ʱ��Ϊ 0��
            inStartTime = 0;
            // ע�ͣ�����������ʼʱ����Ϊ 0��
						
					}
				if(Get_Keyval()==2)
				{
					if(Power_threshold_ALL >= 0 ) 
					{
						Power_threshold_ALL=decreaseVariable(&Power_threshold_ALL);
					}else if(Power_threshold_ALL >99999 ) Power_threshold_ALL = 0;
				}
				else
					{

            isDecreasingPressed = 0;
            // ע�ͣ������Լ���־Ϊδ���¡�
            decrementSpeed = 1;
            // ע�ͣ������Լ��ٶ�Ϊ 1��
            deElapsedTime = 0;
            // ע�ͣ������Լ�������ʱ��Ϊ 0��
            deStartTime = 0;
            // ע�ͣ������Լ���ʼʱ����Ϊ 0��
					}
				
			if(Get_Keyval()==3)
				{
					while(HAL_GPIO_ReadPin(K3_GPIO_Port,K3_Pin)==0);
					page_flag=6;
					break;
				}
				LDZ_ShowASC16(3,44-15 , (Power_threshold_ALL/10000)%10); 
				LDZ_ShowASC16(3,55-15 , (Power_threshold_ALL/1000)%10); 
				LDZ_ShowASC16(3,66-15 , (Power_threshold_ALL/100)%10); 
				LDZ_ShowASC16(3,77-15, (Power_threshold_ALL/10)%10); 
				LDZ_ShowASC16(3,88-15, Power_threshold_ALL%10); 
				LDZ_ShowENG16(3, 99-15, 22);
				
				if(Get_Keyval()==3)
				{
					while(HAL_GPIO_ReadPin(K3_GPIO_Port,K3_Pin)==0);
					page_flag=6;//�������˵�
					break;
				}
				else if(Get_Keyval()==4)
				{
					while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
					Power_threshold_ALL_code[0]=Power_threshold_ALL>>24;Power_threshold_ALL_code[1]=Power_threshold_ALL>>16;
					Power_threshold_ALL_code[3]=Power_threshold_ALL>>8;Power_threshold_ALL_code[0]=Power_threshold_ALL;
					AT24C02_write(0x26,Power_threshold_ALL_code,4);
					osDelay(100);
					page_flag=6;//�������˵�
					break;
				}
		}
	}
		
	else if(page_flag==11)//������ֵҳ��
		{
			LDZ_Clear();
			while(page_flag==11)
			{
				if(Get_Keyval()==1)
				{
					if(Deplete_threshold_ALL<90000)
						Deplete_threshold_ALL= increaseVariable(&Deplete_threshold_ALL);
//					Deplete_threshold_ALL++;
				}
				else {
					// �ɿ���ʱ���ñ�־���ٶ�
                        // �ɿ���ʱ���ñ�־���ٶȺ�ʱ����ر���
            isIncreasingPressed = 0;
            // ע�ͣ�����������־Ϊδ���¡�
            
            incrementSpeed = 1;
            // ע�ͣ����������ٶ�Ϊ 1��
            
            inElapsedTime = 0;
            // ע�ͣ���������������ʱ��Ϊ 0��
            inStartTime = 0;
            // ע�ͣ�����������ʼʱ����Ϊ 0��

				}
			
					if(Get_Keyval()==2)
					{
						if(Deplete_threshold_ALL>0)
							{
								Deplete_threshold_ALL=decreaseVariable(&Deplete_threshold_ALL);
		//					Deplete_threshold_ALL--;
							}
					}
					else
					{
            isDecreasingPressed = 0;
            // ע�ͣ������Լ���־Ϊδ���¡�
            decrementSpeed = 1;
            // ע�ͣ������Լ��ٶ�Ϊ 1��
            deElapsedTime = 0;
            // ע�ͣ������Լ�������ʱ��Ϊ 0��
            deStartTime = 0;
            // ע�ͣ������Լ���ʼʱ����Ϊ 0��
						if(Deplete_threshold_ALL<1) Deplete_threshold_ALL=0;
					}
			if(Get_Keyval()==3)
				{
					while(HAL_GPIO_ReadPin(K3_GPIO_Port,K3_Pin)==0);
					page_flag=6;
					break;
				}
				LDZ_ShowASC16(3,44-20 , (Deplete_threshold_ALL/10000)%10); 
				LDZ_ShowASC16(3,55-20 , (Deplete_threshold_ALL/1000)%10); 
				LDZ_ShowASC16(3,66-20 , (Deplete_threshold_ALL/100)%10); 
				LDZ_ShowASC16(3,77-20, (Deplete_threshold_ALL/10)%10); 
				LDZ_ShowASC16(3,88-20, Deplete_threshold_ALL%10); 
				LDZ_ShowENG16(3, 99-20, 22);LDZ_ShowENG16(3, 110-20, 7);//��WH��
				
				if(Get_Keyval()==3)
				{
					while(HAL_GPIO_ReadPin(K3_GPIO_Port,K3_Pin)==0);
					page_flag=6;//�������˵�
					break;
				}
				else if(Get_Keyval()==4)
				{
					while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
					Deplete_threshold_ALL_code[0]=Deplete_threshold_ALL>>24;Deplete_threshold_ALL_code[1]=Deplete_threshold_ALL>>16;
					Deplete_threshold_ALL_code[2]=Deplete_threshold_ALL>>8;Deplete_threshold_ALL_code[0]=Deplete_threshold_ALL;
					AT24C02_write(0x30,Deplete_threshold_ALL_code,4);
					osDelay(100);
					page_flag=6;//�������˵�
					break;
				}
		}
	}
		
else if(page_flag==12)//��ѹ��ֵ����ҳ��
		{
			LDZ_Clear();
			while(page_flag==12)
			{
				if(Get_Keyval()==1)
				{
					if(Voltage_threshold_Bottom<999)
					{
						Voltage_threshold_Bottom = increaseVariable(&Voltage_threshold_Bottom);
						//Voltage_threshold_Top++;
					}
				}
				else
					{// �ɿ���ʱ���ñ�־���ٶ�
                        // �ɿ���ʱ���ñ�־���ٶȺ�ʱ����ر���
            isIncreasingPressed = 0;
            // ע�ͣ�����������־Ϊδ���¡�
            
            incrementSpeed = 1;
            // ע�ͣ����������ٶ�Ϊ 1��
            
            inElapsedTime = 0;
            // ע�ͣ���������������ʱ��Ϊ 0��
            inStartTime = 0;
            // ע�ͣ�����������ʼʱ����Ϊ 0��
						
					}
					
				if(Get_Keyval()==2)
				{
					if(Voltage_threshold_Bottom>0)
						Voltage_threshold_Bottom=decreaseVariable(&Voltage_threshold_Bottom);
						//Voltage_threshold_Top--;
				}
				else
					{
						isDecreasingPressed = 0;
            // ע�ͣ������Լ���־Ϊδ���¡�
            decrementSpeed = 1;
            // ע�ͣ������Լ��ٶ�Ϊ 1��
            deElapsedTime = 0;
            // ע�ͣ������Լ�������ʱ��Ϊ 0��
            deStartTime = 0;
            // ע�ͣ������Լ���ʼʱ����Ϊ 0��
					}
				
			if(Get_Keyval()==3)
				{
					while(HAL_GPIO_ReadPin(K3_GPIO_Port,K3_Pin)==0);
					page_flag=6;
					break;
				}
				LDZ_ShowASC16(3,66-25 , (Voltage_threshold_Bottom/100)%10); 
				LDZ_ShowASC16(3,77-25, (Voltage_threshold_Bottom/10)%10); 
				LDZ_ShowASC16(3,88-25, Voltage_threshold_Bottom%10); 
				LDZ_ShowENG16(3, 99-25, 21);
				
				if(Get_Keyval()==3)
				{
					while(HAL_GPIO_ReadPin(K3_GPIO_Port,K3_Pin)==0);
					page_flag=6;//�������˵�
					break;
				}
				if(Get_Keyval()==4)
				{
					while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
					Voltage_threshold_Bottom_code[0]=Voltage_threshold_Bottom>>24;Voltage_threshold_Bottom_code[1]=Voltage_threshold_Bottom>>16;
					Voltage_threshold_Bottom_code[2]=Voltage_threshold_Bottom>>8;Voltage_threshold_Bottom_code[3]=Voltage_threshold_Bottom;
					AT24C02_write(0x18,Voltage_threshold_Bottom_code,4);
					osDelay(100);
					page_flag=6;//�������˵�
					break;
				}
		}
	}
		
	else if(page_flag==13)//�ָ�ҳ��
		{
			LDZ_Clear();
			is_reset();
			while(page_flag==13)
			{
				if(Get_Keyval()==1)
				{
					while(HAL_GPIO_ReadPin(K1_GPIO_Port,K1_Pin)==0);
					menu_flag++;
					if(menu_flag>2)menu_flag=1;//�˵��޷�
				}
				if(Get_Keyval()==2)
				{
					while(HAL_GPIO_ReadPin(K2_GPIO_Port,K2_Pin)==0);
					menu_flag--;
					if(menu_flag<1)menu_flag=2;//�˵��޷�
				}
				switch(menu_flag)
				{
					case 1 ://ȡ��
						LDZ_ShowASC16(3,0,12);
						LDZ_ShowASC16(5,0,13);
						if(Get_Keyval()==4)//����ȷ�ϼ�
						{
							while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
							page_flag=1;
						}
					break;
					
					case 2 ://ȷ��
						LDZ_ShowASC16(3,0,13);
						LDZ_ShowASC16(5,0,12);
						if(Get_Keyval()==4)//����ȷ�ϼ�
						{
							 while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
						  	AT24C02_write(0x40,null,4);
								AT24C02_write(0x44,null,4);
								AT24C02_write(0x48,null,4);
								AT24C02_write(0x52,null,4);
							 HAL_PWR_DisablePVD(); /* ʧ��PVD */
								for(int i=0;i<128;i+=1)
								{
									LDZ_ShowASC16(0, i, 12);
									osDelay(10);
								}
							LDZ_Clear();

							NVIC_SystemReset();
						}
					break;
					default:break;
				}
				if(Get_Keyval()==3)
				{
					while(HAL_GPIO_ReadPin(K3_GPIO_Port,K3_Pin)==0);
					page_flag=1;//�������˵�
					break;
				}
		}
	}
	else if(page_flag==14)//�������/���߷�ʽ
	{
		LDZ_Clear();
		ammeter_set();
		while(page_flag==14)
			{
				if(Get_Keyval()==1)
				{
					while(HAL_GPIO_ReadPin(K1_GPIO_Port,K1_Pin)==0);
					menu_flag++;
					if(menu_flag>2)menu_flag=1;//�˵��޷�
				}
				if(Get_Keyval()==2)
				{
					while(HAL_GPIO_ReadPin(K2_GPIO_Port,K2_Pin)==0);
					menu_flag--;
					if(menu_flag<1)menu_flag=2;//�˵��޷�
				}
				switch(menu_flag)
				{
					case 1 ://
						LDZ_ShowASC16(3,0,12);
						LDZ_ShowASC16(5,0,13);
						if(Get_Keyval()==4)//����ȷ�ϼ�
						{
							while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
							page_flag=15;
						}
					break;
					
					case 2 ://ȷ��
						LDZ_ShowASC16(3,0,13);
						LDZ_ShowASC16(5,0,12);
						if(Get_Keyval()==4)//����ȷ�ϼ�
						{
							while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
							page_flag=13;
						}
					break;
					default:break;
				}
				if(Get_Keyval()==3)
				{
					while(HAL_GPIO_ReadPin(K3_GPIO_Port,K3_Pin)==0);
					page_flag=1;//�������˵�
					break;
				}
		}
		
	}		
	else if(page_flag==15)//�������/���߷�ʽ
	{
		LDZ_Clear();
		connection_set();
		while(page_flag==15)
			{
				if(Get_Keyval()==1)
				{
					while(HAL_GPIO_ReadPin(K1_GPIO_Port,K1_Pin)==0);
					menu_flag++;
					if(menu_flag>2)menu_flag=1;//�˵��޷�
				}
				if(Get_Keyval()==2)
				{
					while(HAL_GPIO_ReadPin(K2_GPIO_Port,K2_Pin)==0);
					menu_flag--;
					if(menu_flag<1)menu_flag=2;//�˵��޷�
				}
				switch(menu_flag)
				{
					case 1 ://
						LDZ_ShowASC16(3,0,12);
						LDZ_ShowASC16(5,0,13);
						if(Get_Keyval()==4)//����ȷ�ϼ�-��������
						{
							while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
							connection_mode=0x00;
							AT24C02_write(0x11,&connection_mode,1);
							NVIC_SystemReset();
						}
					break;
					
					case 2 ://ȷ��
						LDZ_ShowASC16(3,0,13);
						LDZ_ShowASC16(5,0,12);
						if(Get_Keyval()==4)//����ȷ�ϼ�-��������
						{
							while(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0);
							connection_mode=0x01;
							AT24C02_write(0x11,&connection_mode,1);
							NVIC_SystemReset();
						}
					break;
					default:break;
				}
				if(Get_Keyval()==3)
				{
					while(HAL_GPIO_ReadPin(K3_GPIO_Port,K3_Pin)==0);
					page_flag=1;//�������˵�
					break;
				}
		}
		
	}	
	
	
	osDelay(40);
}
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the Read_ACenergy thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void const * argument)
{
  /* USER CODE BEGIN StartTask03 */
  /* Infinite loop */
  for(;;)
  {	
		//if(HAL_GPIO_ReadPin(ETHERNET_STA_GPIO_Port,ETHERNET_STA_Pin)==0){}
		uint8_t head=0xaa;
		Send_EnergyData(0);//��������
		osDelay(2000);
  }
  /* USER CODE END StartTask03 */
}

/* USER CODE BEGIN Header_StartTask04 */
/**
* @brief Function implementing the Ethernet_Rs485 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask04 */
void StartTask04(void const * argument)
{
  /* USER CODE BEGIN StartTask04 */
  /* Infinite loop */
  for(;;)
  {
		blinkOnIncrement(Deplete_all);//��������led
		
		HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,key_buzzer);
		
			
    osDelay(1);
  }
  /* USER CODE END StartTask04 */
}

/* USER CODE BEGIN Header_StartTask05 */
/**
* @brief Function implementing the myTask05 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask05 */
void StartTask05(void const * argument)
{
  /* USER CODE BEGIN StartTask05 */
  /* Infinite loop */
  for(;;)
  {
		Range_detection();//�����ֵ
		if(USER_ERR_FALG)
		{
			
			HAL_GPIO_TogglePin(ERR_LD_GPIO_Port,ERR_LD_Pin);
		}
		else
			HAL_GPIO_WritePin(ERR_LD_GPIO_Port,ERR_LD_Pin,0);
    osDelay(500);
  }
  /* USER CODE END StartTask05 */
}

/* USER CODE BEGIN Header_StartTask06 */
/**
* @brief Function implementing the myTask06 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask06 */
void StartTask06(void const * argument)
{
  /* USER CODE BEGIN StartTask06 */
  /* Infinite loop */
  for(;;)
  {
		Modbus_Event();//������Ϊ�ӻ�ʹ��ʱ
    osDelay(1);
  }
  /* USER CODE END StartTask06 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void menu(void)//���˵�
{
	LDZ_Clear();
	LDZ_ShowCHN16(Line1, 16, 3); LDZ_ShowCHN16(0,16+16, 4); LDZ_ShowCHN16(0, 16+32, 5); LDZ_ShowCHN16(0, 16+48, 6); //��������
	LDZ_ShowCHN16(Line2, 16, 7); LDZ_ShowCHN16(2,16+16, 8); LDZ_ShowCHN16(2, 16+32, 9); LDZ_ShowCHN16(2, 16+48, 10); //�������
	LDZ_ShowCHN16(Line3, 16, 11); LDZ_ShowCHN16(4,16+16, 12); LDZ_ShowCHN16(4, 16+32, 13); LDZ_ShowCHN16(4, 16+48,14); //������ֵ
	LDZ_ShowCHN16(Line4, 16, 63); LDZ_ShowCHN16(6,16+16, 64); LDZ_ShowCHN16(6, 16+32, 65); LDZ_ShowCHN16(6, 16+48, 66); //�������
}

void Interface_set(void)//��������
{
	LDZ_Clear();
	LDZ_ShowCHN16(Line1, 16, 19); LDZ_ShowCHN16(Line1,16+16, 20); LDZ_ShowCHN16(Line1, 16+32, 21); LDZ_ShowCHN16(Line1, 16+48, 22); //Ĭ�Ͻ���
	LDZ_ShowCHN16(Line2, 16, 25); LDZ_ShowCHN16(Line2,16+16, 26); LDZ_ShowCHN16(Line2, 16+32, 25); LDZ_ShowCHN16(Line2, 16+48, 27); //������ѹ
	LDZ_ShowCHN16(Line3, 16, 23); LDZ_ShowCHN16(Line3,16+16, 24); LDZ_ShowCHN16(Line3, 16+32, 28); LDZ_ShowCHN16(Line3, 16+48,29); //���๦��
	LDZ_ShowCHN16(Line4, 16, 23); LDZ_ShowCHN16(Line4,16+16, 24); LDZ_ShowCHN16(Line4, 16+32, 28); LDZ_ShowCHN16(Line4, 16+48,30); //���๦��
}

void Current_set(void)//�����������
{
	LDZ_Clear();
	LDZ_ShowCHN16(Line1, 0, 9); LDZ_ShowCHN16(Line1,16, 10);  LDZ_ShowASC16(Line1,32,11);
	LDZ_ShowCHN16(Line3, 16, 31); LDZ_ShowCHN16(Line3,16+16, 32); LDZ_ShowCHN16(Line3, 16+32, 33); LDZ_ShowCHN16(Line3, 16+48, 34); 
	LDZ_ShowCHN16(Line4, 16, 38); LDZ_ShowCHN16(Line4,16+16, 32); LDZ_ShowCHN16(Line4, 16+32, 33); LDZ_ShowCHN16(Line4, 16+48,34); 
}

void Default_Interface(void)//Ĭ�Ͻ���
{
	LDZ_ShowENG16(0, 30, 0);//��������
	LDZ_ShowENG16(0, 67, 1);
	LDZ_ShowENG16(0, 100, 2);
	LDZ_ShowENG16(2, 0, 21);
	LDZ_ShowENG16(4, 0, 0);
	LDZ_ShowCHN16(6, 0, 1);LDZ_ShowCHN16(6, 16, 2);LDZ_ShowASC16(6, 32, 11);
	//��ѹ
	LDZ_ShowASC16(2, 24, (uint8_t)U_volt/100); LDZ_ShowASC16(2, 32, ((uint8_t)U_volt%100)/10); LDZ_ShowASC16(2, 40, (uint8_t)U_volt%10); //A���ѹ
	LDZ_ShowASC16(2, 24+38, (uint8_t)V_volt/100); LDZ_ShowASC16(2, 32+38, ((uint8_t)V_volt%100)/10); LDZ_ShowASC16(2, 40+38, (uint8_t)V_volt%10); //B���ѹ
	LDZ_ShowASC16(2, 24+74, (uint8_t)(UC_val/100)); LDZ_ShowASC16(2, 32+74, ((uint8_t)UC_val%100)/10); LDZ_ShowASC16(2, 40+74, (uint8_t)UC_val%10); //C���ѹ
	//����
	LDZ_ShowASC16(4, 20, IA_val/10);LDZ_ShowASC16(4, 28, (uint8_t)IA_val%10); LDZ_ShowASC16(4, 36, 10); LDZ_ShowASC16(4, 40, Take_smallernumber(IA_val)); //A�����
	LDZ_ShowASC16(4, 20+38, IB_val/10);LDZ_ShowASC16(4, 28+38, (uint8_t)IB_val%10); LDZ_ShowASC16(4, 36+38, 10); LDZ_ShowASC16(4, 40+38, Take_smallernumber(IB_val)); //B���ѹ
	LDZ_ShowASC16(4, 20+74, IC_val/10);LDZ_ShowASC16(4, 28+74, (uint8_t)IC_val%10); LDZ_ShowASC16(4, 36+74, 10); LDZ_ShowASC16(4, 40+74, Take_smallernumber(IC_val)); //C���ѹ
	//���๦��
	LDZ_ShowASC16(6, 44, (uint8_t)FEQT_val/100000); 
	LDZ_ShowASC16(6, 55, (uint8_t)(FEQT_val/10000)%10); 
	LDZ_ShowASC16(6, 66, (uint8_t)(FEQT_val/1000)%10); 
	LDZ_ShowASC16(6, 77, (uint8_t)(FEQT_val/100)%10); 
	LDZ_ShowASC16(6, 88, (uint8_t)(FEQT_val/10)%10); 
	LDZ_ShowASC16(6, 99, (uint8_t)FEQT_val%10); 
	LDZ_ShowENG16(6, 108, 22);
	//Ƶ��
	LDZ_ShowASC16(0, 0, (uint8_t)UFreq_val/10);LDZ_ShowASC16(0, 8, (uint8_t)UFreq_val%10);
}

void Current_Volt_Interface(void)//������ѹ����
{
	LDZ_ShowENG16(0, 30, 0);//��������
	LDZ_ShowENG16(0, 67, 1);
	LDZ_ShowENG16(0, 105, 2);
	LDZ_ShowENG16(3, 0, 21);
	LDZ_ShowENG16(6, 0, 0);
	//��ѹ
	LDZ_ShowASC16(3, 24, (uint8_t)U_volt/100); LDZ_ShowASC16(3, 32, ((uint8_t)U_volt%100)/10); LDZ_ShowASC16(3, 40, (uint8_t)U_volt%10); //A���ѹ
	LDZ_ShowASC16(3, 24+38, (uint8_t)V_volt/100); LDZ_ShowASC16(3, 32+38, ((uint8_t)V_volt%100)/10); LDZ_ShowASC16(3, 40+38, (uint8_t)V_volt%10); //B���ѹ
	LDZ_ShowASC16(3, 24+74, (uint8_t)(UC_val/100)); LDZ_ShowASC16(3, 32+74, ((uint8_t)UC_val%100)/10); LDZ_ShowASC16(3, 40+74, (uint8_t)UC_val%10); //C���ѹ
	//����
	LDZ_ShowASC16(6, 24, IA_val/100);LDZ_ShowASC16(6, 32, IA_val/10);LDZ_ShowASC16(6, 40, IA_val); //LDZ_ShowASC16(6, 36, 10); LDZ_ShowASC16(6, 40, Take_smallernumber(IA_val)); //A�����
	LDZ_ShowASC16(6, 24+38, IB_val/100);LDZ_ShowASC16(6, 32+38, IB_val/10);LDZ_ShowASC16(6, 40+38, IB_val); //LDZ_ShowASC16(6, 36+38, 10); LDZ_ShowASC16(6, 40+38, Take_smallernumber(IB_val)); //B�����
	LDZ_ShowASC16(6, 24+74, IC_val/100);LDZ_ShowASC16(6, 32+74, IC_val/10);LDZ_ShowASC16(6, 40+74, IC_val); //LDZ_ShowASC16(6, 36+74, 10); LDZ_ShowASC16(6, 40+74, Take_smallernumber(IC_val)); //C�����
	//Ƶ��
	LDZ_ShowASC16(0, 0, (uint8_t)UFreq_val/10);LDZ_ShowASC16(0, 8, (uint8_t)UFreq_val%10);
}

void Power_Interface(void)//���ʽ���
{

	LDZ_ShowENG16(0, 0, 15);LDZ_ShowENG16(0, 8, 0);LDZ_ShowASC16(0, 16, 11);//��PA:��
	LDZ_ShowASC16(0, 56-32, (uint8_t)PA_val/10000); 
	LDZ_ShowASC16(0, 66-32, (uint8_t)(PA_val/1000)%10); 
	LDZ_ShowASC16(0, 77-32, (uint8_t)(PA_val/100)%10); 
	LDZ_ShowASC16(0, 88-32, (uint8_t)(PA_val/10)%10); 
	LDZ_ShowASC16(0, 99-32, (uint8_t)PA_val%10); 
	LDZ_ShowENG16(0, 108-32, 22);
	
	LDZ_ShowENG16(2, 0, 15);LDZ_ShowENG16(2, 8, 1);LDZ_ShowASC16(2, 16, 11);//��PB:��
	LDZ_ShowASC16(2, 56-32, (uint8_t)PB_val/10000); 
	LDZ_ShowASC16(2, 66-32, (uint8_t)(PB_val/1000)%10); 
	LDZ_ShowASC16(2, 77-32, (uint8_t)(PB_val/100)%10); 
	LDZ_ShowASC16(2, 88-32, (uint8_t)(PB_val/10)%10); 
	LDZ_ShowASC16(2, 99-32, (uint8_t)PB_val%10); 
	LDZ_ShowENG16(2, 108-32, 22);
	
	LDZ_ShowENG16(4, 0, 15);LDZ_ShowENG16(4, 8, 2);LDZ_ShowASC16(4, 16, 11);//��PC:��
	LDZ_ShowASC16(4, 56-32, (uint8_t)PC_val/10000); 
	LDZ_ShowASC16(4, 66-32, (uint8_t)(PC_val/1000)%10); 
	LDZ_ShowASC16(4, 77-32, (uint8_t)(PC_val/100)%10); 
	LDZ_ShowASC16(4, 88-32, (uint8_t)(PC_val/10)%10); 
	LDZ_ShowASC16(4, 99-32, (uint8_t)PC_val%10); 
	LDZ_ShowENG16(4, 108-32, 22);
	
	LDZ_ShowCHN16(6, 0, 1);LDZ_ShowCHN16(6, 16, 2);LDZ_ShowASC16(6, 32, 11);//���ܹ��ʡ�	
	LDZ_ShowASC16(6, 44, (uint8_t)(FEQT_val/1000000));
	LDZ_ShowASC16(6, 55, (uint8_t)(FEQT_val/100000)%10); 
	LDZ_ShowASC16(6, 66, (uint8_t)(FEQT_val/10000)%10); 
	LDZ_ShowASC16(6, 77, (uint8_t)(FEQT_val/1000)%10); 
	LDZ_ShowASC16(6, 88, (uint8_t)(FEQT_val/100)%10); 
	LDZ_ShowASC16(6, 99, (uint8_t)(FEQT_val/10)%10); 
	LDZ_ShowASC16(6, 110, (uint8_t)FEQT_val%10); 
	LDZ_ShowENG16(6, 120, 22);
	
}

void deplete(void)//����
{
	LDZ_ShowENG16(0, 0, 16);LDZ_ShowENG16(0, 8, 0);LDZ_ShowASC16(0, 16, 11);//��QA:��
	LDZ_ShowASC16(0, 56-32, (uint8_t)Deplete_A_val/10000); 
	LDZ_ShowASC16(0, 66-32, (uint8_t)(Deplete_A_val/1000)%10); 
	LDZ_ShowASC16(0, 77-32, (uint8_t)(Deplete_A_val/100)%10); 
	LDZ_ShowASC16(0, 88-32, (uint8_t)(Deplete_A_val/10)%10); 
	LDZ_ShowASC16(0, 99-32, (uint8_t)Deplete_A_val%10); 
	LDZ_ShowENG16(0, 110-32, 22);LDZ_ShowENG16(0, 120-32, 7);//��WH��
	
	LDZ_ShowENG16(2, 0, 16);LDZ_ShowENG16(2, 8, 1);LDZ_ShowASC16(2, 16, 11);//��QB:��
	LDZ_ShowASC16(2, 56-32, (uint8_t)Deplete_B_val/10000); 
	LDZ_ShowASC16(2, 66-32, (uint8_t)(Deplete_B_val/1000)%10); 
	LDZ_ShowASC16(2, 77-32, (uint8_t)(Deplete_B_val/100)%10); 
	LDZ_ShowASC16(2, 88-32, (uint8_t)(Deplete_B_val/10)%10); 
	LDZ_ShowASC16(2, 99-32, (uint8_t)Deplete_B_val%10); 
	LDZ_ShowENG16(2, 110-32, 22);LDZ_ShowENG16(2, 120-32, 7);//��WH��
	
	LDZ_ShowENG16(4, 0, 16);LDZ_ShowENG16(4, 8, 2);LDZ_ShowASC16(4, 16, 11);//��QC:��
	LDZ_ShowASC16(4, 56-32, (uint8_t)Deplete_C_val/10000); 
	LDZ_ShowASC16(4, 66-32, (uint8_t)(Deplete_C_val/1000)%10); 
	LDZ_ShowASC16(4, 77-32, (uint8_t)(Deplete_C_val/100)%10); 
	LDZ_ShowASC16(4, 88-32, (uint8_t)(Deplete_C_val/10)%10); 
	LDZ_ShowASC16(4, 99-32, (uint8_t)Deplete_C_val%10); 
	LDZ_ShowENG16(4, 110-32, 22);LDZ_ShowENG16(4, 120-32, 7);//��WH��
	
	LDZ_ShowCHN16(6, 0, 28);LDZ_ShowCHN16(6, 16, 30);//���ܹ���
	LDZ_ShowASC16(6, 33, (uint8_t)Deplete_all_val/10000); 
	LDZ_ShowASC16(6, 44, (uint8_t)Deplete_all_val/10000); 
	LDZ_ShowASC16(6, 55, (uint8_t)Deplete_all_val/10000); 
	LDZ_ShowASC16(6, 66, (uint8_t)(Deplete_all_val/1000)%10); 
	LDZ_ShowASC16(6, 77, (uint8_t)(Deplete_all_val/100)%10); 
	LDZ_ShowASC16(6, 88, (uint8_t)(Deplete_all_val/10)%10); 
	LDZ_ShowASC16(6, 99, (uint8_t)Deplete_all_val%10); 
	LDZ_ShowENG16(6, 110, 22);LDZ_ShowENG16(6, 119, 7);//��WH��
}

void warning_Interface(void)//��ֵ����ҳ��
{
	LDZ_Clear();
	LDZ_ShowCHN16(0, 16, 25); LDZ_ShowCHN16(0,16+16, 26);LDZ_ShowCHN16(0, 16+32, 13); LDZ_ShowCHN16(0, 16+48,14); 
	LDZ_ShowCHN16(Line2, 16, 25); LDZ_ShowCHN16(Line2, 32, 27);LDZ_ShowCHN16(2, 16+32, 13); LDZ_ShowCHN16(2, 16+48,14); 
	LDZ_ShowCHN16(Line3, 16, 28); LDZ_ShowCHN16(Line3, 32,29);LDZ_ShowCHN16(4, 16+32, 13); LDZ_ShowCHN16(4, 16+48,14); 
	LDZ_ShowCHN16(Line4, 16, 28); LDZ_ShowCHN16(Line4, 32,30);LDZ_ShowCHN16(6, 16+32, 13); LDZ_ShowCHN16(6, 16+48,14); 
}

void Voltage_limit(void)//��ѹ������ֵ
{
	LDZ_Clear();
	LDZ_ShowCHN16(Line2, 16, 25); LDZ_ShowCHN16(Line2, 32, 26);LDZ_ShowCHN16(2, 16+32, 40); LDZ_ShowCHN16(2, 16+48,41);// 
	LDZ_ShowCHN16(Line3, 16, 25); LDZ_ShowCHN16(Line3, 32,26);LDZ_ShowCHN16(4, 16+32, 39); LDZ_ShowCHN16(4, 16+48,41); 
}

void is_reset(void)//ȷ���ָ�������
{
	LDZ_Clear();
	LDZ_ShowCHN16(3, 16, 49); LDZ_ShowCHN16(3, 32, 50);
	LDZ_ShowCHN16(5, 16, 47); LDZ_ShowCHN16(5, 32,48);
}

void ammeter_set(void)//�������
{
	LDZ_Clear();
	LDZ_ShowCHN16(0, 16-16, 70); LDZ_ShowCHN16(0, 32-16, 71);LDZ_ShowCHN16(0, 48-16, 72);//��ǰ��
	LDZ_ShowCHN16(3, 16, 55); LDZ_ShowCHN16(3, 32, 56);LDZ_ShowCHN16(3, 48, 57); LDZ_ShowCHN16(3, 64,58);//���߷�ʽ
	LDZ_ShowCHN16(5, 16, 67); LDZ_ShowCHN16(5, 32, 68);LDZ_ShowCHN16(5, 48, 63); LDZ_ShowCHN16(5, 64,69);//�������
}
void connection_set(void)//��������
{
	LDZ_Clear();
	LDZ_ShowCHN16(3, 16, 59); LDZ_ShowCHN16(3, 32, 61);LDZ_ShowCHN16(3, 48, 60); LDZ_ShowCHN16(3, 64,62);//��������
	LDZ_ShowCHN16(5, 16, 59); LDZ_ShowCHN16(5, 32, 61);LDZ_ShowCHN16(5, 48, 59); LDZ_ShowCHN16(5, 64,62);//��������
}

uint8_t Get_Keyval(void)
{
	uint8_t KEY_falg=0;
//	HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,1);
//			HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,0);

		if(HAL_GPIO_ReadPin(K1_GPIO_Port,K1_Pin)==0)
		{
			key_buzzer=1;
			osDelay(3);
			key_buzzer=0;
			KEY_falg=1;
			key_temp=1;
		}
		if(HAL_GPIO_ReadPin(K2_GPIO_Port,K2_Pin)==0)
		{
			key_buzzer=1;
			osDelay(3);
			key_buzzer=0;
			KEY_falg=2;
			key_temp=2;
		}
		if(HAL_GPIO_ReadPin(K3_GPIO_Port,K3_Pin)==0)
		{
			key_buzzer=1;
			osDelay(3);
			key_buzzer=0;
			KEY_falg=3;
			key_temp=3;
		}
		if(HAL_GPIO_ReadPin(K4_GPIO_Port,K4_Pin)==0)
		{
			key_buzzer=1;
			osDelay(3);
			key_buzzer=0;
			KEY_falg=4;
			key_temp=4;
		}
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)==1&&HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2)==1&&HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_10)==1&&HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)==1)
		{	
			
			KEY_falg=0;
			key_temp=0;
		}
	return KEY_falg;
}

void PVD_IRQHandler(void)
{
	if(__HAL_PWR_GET_FLAG( PWR_FLAG_PVDO ))    /* 1ΪVDDС��PVD��ֵ,������� */
	{
		while(1)
		{
		AT24C02_write(0x52, Deplete_all_Code, 4);//�����������
		}
	}
}



float convertToFloat(int24_t_simulated number) {//���з��� 24 λ����ת��Ϊ������
		 int32_t signedValue = number.value;
		 if (signedValue & 0x800000) {
				 // ���������з�����չ��ת��
				 return (float)((int32_t)(0xFFFFFFFF - signedValue)+1) / (float)(1 << 23);
		 } else {
				 // ������ֱ��ת��
				 return (float)signedValue / (float)(1 << 23);
		 }
 }

int convertToSignedInt(int18_t_simulated number) {//���з��� 18 λ����ת��Ϊ����
	 int32_t signedValue = number.value;
	 if (signedValue & 0x20000) {
			 // ���������з�����չ
			 return signedValue | 0xFFFC0000;
	 } else {
			 // ������ֱ�ӷ���
			 return signedValue;
	 }
}

uint32_t floatToUint32(float f) {//��float��uint32_t֮�����ת��
    uint32_t result;
    *(float*)&result = f;
    return result;
}

void blinkOnIncrement(int variable) {
    static int previousValue;
    if (variable > previousValue) {
        // ���� LED ���ӵ� GPIOA ���� 5
        HAL_GPIO_WritePin(PULSE_LD_GPIO_Port,PULSE_LD_Pin,1);
        osDelay(150);
        HAL_GPIO_WritePin(PULSE_LD_GPIO_Port,PULSE_LD_Pin,0);
        previousValue = variable;
    }
}

float absoluteValue(float num) {
    return num < 0? -num : num;
}

void Send_EnergyData(uint8_t Tx_mode_flag)
{
/*
modbus/tcp  ethernet/rs485Э�����
*/
//****************************************tcp*****************************************
	
	//************�����************//
	
	//����  ASCII ��
	
	printf("UA: %fV\n", UA_val);
	printf("UB: %fV\n", UB_val);
	printf("UC: %fV\n", UC_val);//A���ѹ+B���ѹ+C���ѹ��float��
	printf("IA: %fA\n", IA_val);
	printf("IB: %fA\n", IB_val);
	printf("IC: %fA\n", IC_val);//A�����+B�����+C�������float��
	printf("PA: %fW\n", PA_val);
	printf("PB: %fW\n", PB_val);
	printf("PC: %fW\n", PC_val);
	printf("FEQT: %fW\n", FEQT_val);//A�๦��+B�๦��+C�๦��+���๦�ʣ�float��
	printf("Deplete_A: %fW/h\n", Deplete_A_val);
	printf("Deplete_B: %fW/h\n", Deplete_B_val);
	printf("Deplete_C: %fW/h\n", Deplete_C_val);
	printf("Deplete_all: %fW/h\n", Deplete_all_val);//A���й�����+B���й�����+C���й����� + �����ۼ��й����ʣ�float��
	printf("power_factor: %f\n", pwr);//ȡ����������float��
	printf("UFreq: %fHz\n", UFreq_val);//��ѹƵ�ʣ�float��
	
	
	//���� HEX ����
//	sendFloatAsFourBytes(UA_val);
//	sendFloatAsFourBytes(UB_val);
//	sendFloatAsFourBytes(UC_val);//A���ѹ+B���ѹ+C���ѹ��float��
//	
//	sendFloatAsFourBytes(IA_val);
//	sendFloatAsFourBytes(IB_val);
//	sendFloatAsFourBytes(IC_val);//A�����+B�����+C�������float��
//	
//	sendFloatAsFourBytes(PA_val);
//	sendFloatAsFourBytes(PB_val);
//	sendFloatAsFourBytes(PC_val);
//	sendFloatAsFourBytes(FEQT_val);//A�๦��+B�๦��+C�๦��+���๦�ʣ�float��
//	
//	sendFloatAsFourBytes(Deplete_A_val);
//	sendFloatAsFourBytes(Deplete_B_val);
//	sendFloatAsFourBytes(Deplete_C_val);
//	sendFloatAsFourBytes(Deplete_all_val);//A���й�����+B���й�����+C���й����� + �����ۼ��й����ʣ�float��

//	sendFloatAsFourBytes(pwr);//ȡ����������float��
//	
//	sendFloatAsFourBytes(UFreq);//��ѹƵ�ʣ�float��
	
	
	
	
	//************�����************//

//		sendFloatAsFourBytes(UART_BaudRate);//���Ͳ�����
//	sendFloatAsFourBytes(UART_frequency);//����Ƶ��
//	sendFloatAsFourBytes(Gather_Frequency);//������ɼ�Ƶ��
//	sendFloatAsFourBytes(Electricity_meter_Add);//������ɼ�Ƶ��
	
	
	//****************************************485*****************************************
	
	//************�����************//
//	RS485DIR_RX;//���ǿ���485����
//	sendFloatAsFourBytes_485(UA_val);
//	sendFloatAsFourBytes_485(UB_val);
//	sendFloatAsFourBytes_485(UC_val);//A���ѹ+B���ѹ+C���ѹ��float��
//	
//	sendFloatAsFourBytes_485(IA_val);
//	sendFloatAsFourBytes_485(IB_val);
//	sendFloatAsFourBytes_485(IC_val);//A�����+B�����+C�������float��
//	
//	sendFloatAsFourBytes_485(PA_val);
//	sendFloatAsFourBytes_485(PB_val);
//	sendFloatAsFourBytes_485(PC_val);
//	sendFloatAsFourBytes_485(FEQT_val);//A�๦��+B�๦��+C�๦��+���๦�ʣ�float��
//	
//	sendFloatAsFourBytes_485(Deplete_A_val);
//	sendFloatAsFourBytes_485(Deplete_B_val);
//	sendFloatAsFourBytes_485(Deplete_C_val);
//	sendFloatAsFourBytes_485(Deplete_all_val);//A���й�����+B���й�����+C���й�������float�� + �����ۼ��й����ʣ�int��

//	sendFloatAsFourBytes_485(pwr);//ȡ����������float��
//	
//	sendFloatAsFourBytes_485(UFreq_val);//��ѹƵ�ʣ�unsigned int��
}
void sendByte(uint8_t byte) {
  HAL_UART_Transmit(&huart2, &byte, 1, HAL_MAX_DELAY);
}

void sendByte_485(uint8_t byte) {
	
  HAL_UART_Transmit(&huart1, &byte, 1, HAL_MAX_DELAY);
}

void sendFloatAsFourBytes_485(float f) {
    uint32_t temp;
    memcpy(&temp, &f, sizeof(temp));
    uint8_t bytes[4];
    bytes[0] = (temp >> 24) & 0xFF;
    bytes[1] = (temp >> 16) & 0xFF;
    bytes[2] = (temp >> 8) & 0xFF;
    bytes[3] = temp & 0xFF;
    for (int i = 0; i < 4; i++) {
        sendByte_485(bytes[i]);
    }
}

void sendFloatAsFourBytes(float f) {
    uint32_t temp;
    memcpy(&temp, &f, sizeof(temp));
    uint8_t bytes[4];
    bytes[0] = (temp >> 24) & 0xFF;
    bytes[1] = (temp >> 16) & 0xFF;
    bytes[2] = (temp >> 8) & 0xFF;
    bytes[3] = temp & 0xFF;
    for (int i = 0; i < 4; i++) {
       sendByte(bytes[i]);
    }
}

void Range_detection()
{
	if((UA_val>Voltage_threshold_Top||UB_val>Voltage_threshold_Top||UC_val>Voltage_threshold_Top||
		UA_val<Voltage_threshold_Bottom||UB_val<Voltage_threshold_Bottom||UB_val<Voltage_threshold_Bottom) && Voltage_threshold_Top>2)
	{
		USER_ERR_FALG=1;
		//�����ѹ����
	}
	else if((IA_val>Current_threshold_ALL||IB_val>Current_threshold_ALL||IB_val>Current_threshold_ALL) && Current_threshold_ALL>0)
	{
		USER_ERR_FALG=2;
		//�����������
	}
	else if(((uint32_t)PA_val>Power_threshold_ALL||(uint32_t)PB_val>Power_threshold_ALL||(uint32_t)PC_val>Power_threshold_ALL) && Power_threshold_ALL>1)
	{
		USER_ERR_FALG=3;
		//���๦�ʱ���
	}
	else if((Deplete>Deplete_threshold_ALL) && Deplete_threshold_ALL>0)
	{
		USER_ERR_FALG=4;
		//�ۼ��й����ı���
	}
	else USER_ERR_FALG=0;
}



// ���庯�� increaseVariable���������ӱ�����ʵ�ְ�ʱ��Խ������Խ��Ĺ���
// ��������
uint32_t increaseVariable(uint32_t *variable) {
    if (!isIncreasingPressed) {
        isIncreasingPressed = 1;
        inStartTime = inElapsedTime;
        incrementSpeed = 1;
    } else if (!isIncreasingPressed && inStartTime > 0) {
        isIncreasingPressed = 1;
        inStartTime = inElapsedTime;
        incrementSpeed = 1;
    }

    if (isIncreasingPressed) {
        if (inStartTime == 0) {
            inStartTime = inElapsedTime;
        }
        inElapsedTime++;
        if (inElapsedTime - inStartTime > inSpeedUpThreshold) {
            incrementSpeed++;
        }
        *variable += incrementSpeed;
    }

    return *variable;
}

#define SLOW_DOWN_THRESHOLD 500
#define SLOW_DOWN_FACTOR 0
     // �Լ�����
     uint32_t decreaseVariable(uint32_t *variable) {
         if (!isDecreasingPressed) {
             isDecreasingPressed = 1;
             deStartTime = deElapsedTime;
             decrementSpeed = 1;
         } else if (!isDecreasingPressed && deStartTime > 0) {
             isDecreasingPressed = 1;
             deStartTime = deElapsedTime;
             decrementSpeed = 1;
         }
         if (isDecreasingPressed) {
             if (deStartTime == 0) {
                 deStartTime = deElapsedTime;
             }
             deElapsedTime++;
             if (deElapsedTime - deStartTime > deSpeedUpThreshold) {
                 decrementSpeed++;
             }
             if (*variable > 0) {
                 if (*variable < SLOW_DOWN_THRESHOLD) {
                     uint32_t tempSpeed = (uint32_t)(decrementSpeed * SLOW_DOWN_FACTOR);
                     // ȷ�����ټ�ȥ1
                     *variable -= tempSpeed > 0? tempSpeed : 1;
                 } else {
                     uint32_t tempSpeed = *variable > decrementSpeed? decrementSpeed : *variable;
                     *variable -= tempSpeed;
                 }
             }
         }
         return *variable;
     }

/* USER CODE END Application */

