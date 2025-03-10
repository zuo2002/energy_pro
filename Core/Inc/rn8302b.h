#ifndef _RN8302_H_
#define _RN8302_H_
 
#include "main.h"
#include "stdio.h"
 
//---------------------- RN8302计量寄存器地址定义---------------------------------------------------//
/* Exported define ------------------------------------------------------------*/
/*"*********************全波计量参数寄存器********************************************************"*/
#define	RN8302_UAWAV		0x0000	/*"	A 相电压采样数据	"*/                
#define	RN8302_UBWAV        0x0001	/*"	B 相电压采样数据	"*/                
#define	RN8302_UCWAV        0x0002	/*"	C 相电压采样数据	"*/                
#define	RN8302_IAWAV        0x0003	/*"	A 相电流采样数据	"*/                
#define	RN8302_IBWAV        0x0004	/*"	B 相电流采样数据	"*/                
#define	RN8302_ICWAV        0x0005	/*"	C 相电流采样数据	"*/                
#define	RN8302_INWAV        0x0006	/*"	零线电流采样数据	"*/                
#define	RN8302_UA           0x0007	/*"	A 相电压有效值	"*/                    
#define	RN8302_UB           0x0008	/*"	B 相电压有效值	"*/                    
#define	RN8302_UC           0x0009	/*"	C 相电压有效值	"*/                    
#define	RN8302_USUM         0x000A	/*"	电压矢量和有效值	"*/                
#define	RN8302_IA           0x000B	/*"	A 相电流有效值	"*/                    
#define	RN8302_IB           0x000C	/*"	B 相电流有效值	"*/                    
#define	RN8302_IC           0x000D	/*"	C 相电流有效值	"*/                    
#define	RN8302_IN           0x000E	/*"	零线电流有效值	"*/                    
#define	RN8302_ISUM         0x0010	/*"	电流矢量和有效值	"*/                
#define	RN8302_IA_NVM1      0x0011	/*"	NVM1 A 相电流有效值	"*/                
#define	RN8302_IB_NVM1      0x0012	/*"	NVM1 B 相电流有效值	"*/                
#define	RN8302_IC_NVM1      0x0013	/*"	NVM1 C 相电流有效值	"*/                
#define	RN8302_PA           0x0014	/*"	A 相有功功率	"*/                    
#define	RN8302_PB           0x0015	/*"	B 相有功功率	"*/                    
#define	RN8302_PC           0x0016	/*"	C 相有功功率	"*/                    
#define	RN8302_PT           0x0017	/*"	合相有功功率	"*/                    
#define	RN8302_QA           0x0018	/*"	A 相无功功率	"*/                    
#define	RN8302_QB           0x0019	/*"	B 相无功功率	"*/                    
#define	RN8302_QC           0x001A	/*"	C 相无功功率	"*/                    
#define	RN8302_QT           0x001B	/*"	合相无功功率	"*/                    
#define	RN8302_SA           0x001C	/*"	A 相视在功率	"*/                    
#define	RN8302_SB           0x001D	/*"	B 相视在功率	"*/                    
#define	RN8302_SC           0x001E	/*"	C 相视在功率	"*/                    
#define	RN8302_STA          0x001F	/*"	RMS 合相视在功率	"*/                
#define	RN8302_PfA          0x0020	/*"	A 相功率因数	"*/                    
#define	RN8302_PfB          0x0021	/*"	B 相功率因数	"*/                    
#define	RN8302_PfC          0x0022	/*"	C 相功率因数	"*/                    
#define	RN8302_PfTA         0x0023	/*"	RMS 合相功率因数	"*/                
#define	RN8302_PAFCnt       0x0024	/*"	A 相有功快速脉冲计数	"*/            
#define	RN8302_PBFCnt       0x0025	/*"	B 相有功快速脉冲计数	"*/            
#define	RN8302_PCFCnt       0x0026	/*"	C 相有功快速脉冲计数	"*/            
#define	RN8302_PTFCnt       0x0027	/*"	合相有功快速脉冲计数	"*/            
#define	RN8302_QAFCnt       0x0028	/*"	A 相无功快速脉冲计数	"*/            
#define	RN8302_QBFCnt       0x0029	/*"	B 相无功快速脉冲计数	"*/            
#define	RN8302_QCFCnt       0x002A	/*"	C 相无功快速脉冲计数	"*/            
#define	RN8302_QTFCnt       0x002B	/*"	合相无功快速脉冲计数	"*/            
#define	RN8302_SAFCnt       0x002C	/*"	A 相视在快速脉冲计数	"*/            
#define	RN8302_SBFCnt       0x002D	/*"	B 相视在快速脉冲计数	"*/            
#define	RN8302_SCFCnt       0x002E	/*"	C 相视在快速脉冲计数	"*/            
#define	RN8302_STFACnt      0x002F	/*"	RMS 合相视在快速脉冲计数	"*/        
#define	RN8302_EPA          0x0030	/*"	A 相有功能量寄存器	"*/                
#define	RN8302_EPB          0x0031	/*"	B 相有功能量寄存器	"*/                
#define	RN8302_EPC          0x0032	/*"	C 相有功能量寄存器	"*/                
#define	RN8302_EPT			    0x0033	/*"	合相有功能量寄存器	"*/                
#define	RN8302_PosEPA       0x0034	/*"	A 相正向有功能量寄存器	"*/            
#define	RN8302_PosEPB       0x0035	/*"	B 相正向有功能量寄存器	"*/            
#define	RN8302_PosEPC       0x0036	/*"	C 相正向有功能量寄存器	"*/            
#define	RN8302_PosEPT       0x0037	/*"	合相正向有功能量寄存器	"*/            
#define	RN8302_NegEPA       0x0038	/*"	A 相反向有功能量寄存器	"*/            
#define	RN8302_NegEPB       0x0039	/*"	B 相反向有功能量寄存器	"*/            
#define	RN8302_NegEPC       0x003A	/*"	C 相反向有功能量寄存器	"*/            
#define	RN8302_NegEPT       0x003B	/*"	合相反向有功能量寄存器	"*/            
#define	RN8302_EQA          0x003C	/*"	A 相无功能量寄存器	"*/                
#define	RN8302_EQB          0x003D	/*"	B 相无功能量寄存器	"*/                
#define	RN8302_EQC          0x003E	/*"	C 相无功能量寄存器	"*/                
#define	RN8302_EQT          0x003F	/*"	合相无功能量寄存器	"*/                
#define	RN8302_PosEQA       0x0040	/*"	A 相正向无功能量寄存器	"*/            
#define	RN8302_PosEQB       0x0041	/*"	B 相正向无功能量寄存器	"*/            
#define	RN8302_PosEQC       0x0042	/*"	C 相正向无功能量寄存器	"*/            
#define	RN8302_PosEQT       0x0043	/*"	合相正向无功能量寄存器	"*/            
#define	RN8302_NegEQA       0x0044	/*"	A 相反向无功能量寄存器	"*/            
#define	RN8302_NegEQB       0x0045	/*"	B 相反向无功能量寄存器	"*/            
#define	RN8302_NegEQC       0x0046	/*"	C 相反向无功能量寄存器	"*/            
#define	RN8302_NegEQT       0x0047	/*"	合相反向无功能量寄存器	"*/            
#define	RN8302_ESA          0x0048	/*"	A 相视在能量寄存器	"*/                
#define	RN8302_ESB          0x0049	/*"	B 相视在能量寄存器	"*/                
#define	RN8302_ESC          0x004A	/*"	C 相视在能量寄存器	"*/                
#define	RN8302_ESTA         0x004B	/*"	RMS 合相视在能量寄存器	"*/            
#define	RN8302_STV          0x004C	/*"	PQS 合相视在功率	"*/                
#define	RN8302_PfTV         0x004D	/*"	PQS 合相功率因数	"*/                
#define	RN8302_STFVCnt      0x004E	/*"	PQS 合相视在快速脉冲计数	"*/        
#define	RN8302_ESTV         0x004F	/*"	PQS 合相视在能量寄存器	"*/    
/*"*********************基波谐波计量参数寄存器********************************************************"*/
#define	RN8302_YUA          0x0050	/*"	采样通道 UA 基波相角寄存器	"*/        
#define	RN8302_YUB          0x0051	/*"	采样通道 UB 基波相角寄存器	"*/        
#define	RN8302_YUC          0x0052	/*"	采样通道 UC 基波相角寄存器	"*/        
#define	RN8302_YIA          0x0053	/*"	采样通道 IA 基波相角寄存器	"*/        
#define	RN8302_YIB          0x0054	/*"	采样通道 IB 基波相角寄存器	"*/        
#define	RN8302_YIC          0x0055	/*"	采样通道 IC 基波相角寄存器	"*/        
#define	RN8302_YIN          0x0056	/*"	采样通道 IN 基波相角寄存器	"*/        
#define	RN8302_UFreq        0x0057	/*"	电压线频率	"*/                        
#define	RN8302_FUA          0x0058	/*"	A 相基波电压有效值	"*/                
#define	RN8302_FUB          0x0059	/*"	B 相基波电压有效值	"*/                
#define	RN8302_FUC          0x005A	/*"	C 相基波电压有效值	"*/                
#define	RN8302_FIA          0x005B	/*"	A 相基波电流有效值	"*/                
#define	RN8302_FIB          0x005C	/*"	B 相基波电流有效值	"*/                
#define	RN8302_FIC          0x005D	/*"	C 相基波电流有效值	"*/                
#define	RN8302_FPA          0x005E	/*"	A 相基波有功功率	"*/                
#define	RN8302_FPB          0x005F	/*"	B 相基波有功功率	"*/                
#define	RN8302_FPC          0x0060	/*"	C 相基波有功功率	"*/                
#define	RN8302_FPT          0x0061	/*"	合相基波有功功率	"*/                
#define	RN8302_FQA          0x0062	/*"	A 相基波无功功率	"*/                
#define	RN8302_FQB          0x0063	/*"	B 相基波无功功率	"*/                
#define	RN8302_FQC          0x0064	/*"	C 相基波无功功率	"*/                
#define	RN8302_FQT          0x0065	/*"	合相基波无功功率	"*/                
#define	RN8302_FSA          0x0066	/*"	A 相基波视在功率	"*/                
#define	RN8302_FSB          0x0067	/*"	B 相基波视在功率	"*/                
#define	RN8302_FSC          0x0068	/*"	C 相基波视在功率	"*/                
#define	RN8302_FSTA         0x0069	/*"	RMS 合相基波视在功率	"*/            
#define	RN8302_FPfA         0x006A	/*"	A 相基波功率因数	"*/                
#define	RN8302_FPfB         0x006B	/*"	B 相基波功率因数	"*/                
#define	RN8302_FPfC         0x006C	/*"	C 相基波功率因数	"*/                
#define	RN8302_FPfTA        0x006D	/*"	RMS 合相基波功率因数	"*/            
#define	RN8302_FPAFCnt      0x006E	/*"	A 相基波有功快速脉冲计数	"*/        
#define	RN8302_FPBFCnt      0x006F	/*"	B 相基波有功快速脉冲计数	"*/        
#define	RN8302_FPCFCnt      0x0070	/*"	C 相基波有功快速脉冲计数	"*/        
#define	RN8302_FPTFCnt      0x0071	/*"	合相基波有功快速脉冲计数	"*/        
#define	RN8302_FQAFCnt      0x0072	/*"	A 相基波无功快速脉冲计数	"*/        
#define	RN8302_FQBFCnt      0x0073	/*"	B 相基波无功快速脉冲计数	"*/        
#define	RN8302_FQCFCnt      0x0074	/*"	C 相基波无功快速脉冲计数	"*/        
#define	RN8302_FQTFCnt      0x0075	/*"	合相基波无功快速脉冲计数	"*/        
#define	RN8302_FSAFCnt      0x0076	/*"	A 相基波视在快速脉冲计数	"*/        
#define	RN8302_FSBFCnt      0x0077	/*"	B 相基波视在快速脉冲计数	"*/        
#define	RN8302_FSCFCnt      0x0078	/*"	C 相基波视在快速脉冲计数	"*/        
#define	RN8302_FSTAFCnt     0x0079	/*"	RMS 合相基波视在快速脉冲计数	"*/    
#define	RN8302_FEPA         0x007A	/*"	A 相基波有功电能	"*/                
#define	RN8302_FEPB         0x007B	/*"	B 相基波有功电能	"*/                
#define	RN8302_FEPC         0x007C	/*"	C 相基波有功电能	"*/                
#define	RN8302_FEPT         0x007D	/*"	合相基波有功电能	"*/                
#define	RN8302_PosFEPA      0x007E	/*"	A 相基波正向有功能量寄存器	"*/        
#define	RN8302_PosFEPB      0x007F	/*"	B 相基波正向有功能量寄存器	"*/        
#define	RN8302_PosFEPC      0x0080	/*"	C 相基波正向有功能量寄存器	"*/        
#define	RN8302_PosFEPT      0x0081	/*"	合相基波正向有功能量寄存器	"*/        
#define	RN8302_NegFEPA      0x0082	/*"	A 相基波反向有功能量寄存器	"*/        
#define	RN8302_NegFEPB      0x0083	/*"	B 相基波反向有功能量寄存器	"*/        
#define	RN8302_NegFEPC      0x0084	/*"	C 相基波反向有功能量寄存器	"*/        
#define	RN8302_NegFEPT      0x0085	/*"	合相基波反向有功能量寄存器	"*/        
#define	RN8302_FEQA         0x0086	/*"	A 相基波无功电能	"*/                
#define	RN8302_FEQB         0x0087	/*"	B 相基波无功电能	"*/                
#define	RN8302_FEQC         0x0088	/*"	C 相基波无功电能	"*/                
#define	RN8302_FEQT         0x0089	/*"	合相基波无功电能	"*/                
#define	RN8302_PosFEQA      0x008A	/*"	A 相正向基波无功能量寄存器	"*/        
#define	RN8302_PosFEQB      0x008B	/*"	B 相正向基波无功能量寄存器	"*/        
#define	RN8302_PosFEQC      0x008C	/*"	C 相正向基波无功能量寄存器	"*/        
#define	RN8302_PosFEQT      0x008D	/*"	合相正向基波无功能量寄存器	"*/        
#define	RN8302_NegFEQA      0x008E	/*"	A 相反向基波无功能量寄存器	"*/        
#define	RN8302_NegFEQB      0x008F	/*"	B 相反向基波无功能量寄存器	"*/        
#define	RN8302_NegFEQC      0x0090	/*"	C 相反向基波无功能量寄存器	"*/        
#define	RN8302_NegFEQT      0x0091	/*"	合相反向基波无功能量寄存器	"*/        
#define	RN8302_FESA         0x0092	/*"	A 相基波视在能量寄存器	"*/            
#define	RN8302_FESB         0x0093	/*"	B 相基波视在能量寄存器	"*/            
#define	RN8302_FESC         0x0094	/*"	C 相基波视在能量寄存器	"*/            
#define	RN8302_FESTA        0x0095	/*"	RMS 合相基波视在能量寄存器	"*/        
#define	RN8302_HUA          0x0096	/*"	A 相谐波电压有效值	"*/                
#define	RN8302_HUB          0x0097	/*"	B 相谐波电压有效值	"*/                
#define	RN8302_HUC          0x0098	/*"	C 相谐波电压有效值	"*/                
#define	RN8302_HIA          0x0099	/*"	A 相谐波电流有效值	"*/                
#define	RN8302_HIB          0x009A	/*"	B 相谐波电流有效值	"*/                
#define	RN8302_HIC          0x009B	/*"	C 相谐波电流有效值	"*/                
#define	RN8302_FSTV         0x009C	/*"	PQS 合相基波视在功率	"*/            
#define	RN8302_FPfTV        0x009D	/*"	PQS 合相基波功率因数	"*/            
#define	RN8302_FSTVFCnt     0x009E	/*"	PQS 合相基波视在快速脉冲计数	"*/    
#define	RN8302_FESTV        0x009F	/*"	PQS 合相基波视在能量寄存器	"*/        
/*"*********************EMM 校表寄存器 I********************************************************"*/
#define	RN8302_HFConst1     0x0100	/*"	高频脉冲计数寄存器 1	"*/            
#define	RN8302_HFConst2     0x0101	/*"	高频脉冲计数寄存器 2	"*/            
#define	RN8302_IStart_PS    0x0102	/*"	有功视在启动电流阈值寄存器	"*/        
#define	RN8302_IStart_Q     0x0103	/*"	无功启动电流阈值寄存器	"*/            
#define	RN8302_LostVoltT    0x0104	/*"	失压阈值寄存器	"*/                    
#define	RN8302_ZXOT         0x0105	/*"	过零阈值寄存器	"*/                    
#define	RN8302_PRTH1L       0x0106	/*"	相位分段校正电流阈值 1 下限	"*/        
#define	RN8302_PRTH1H       0x0107	/*"	相位分段校正电流阈值 1 上限	"*/        
#define	RN8302_PRTH2L       0x0108	/*"	相位分段校正电流阈值 2 下限	"*/        
#define	RN8302_PRTH2H       0x0109	/*"	相位分段校正电流阈值 2 上限	"*/        
#define	RN8302_IRegion3L    0x010A	/*"	电流阈值 3 下限	"*/                    
#define	RN8302_IRegion3H    0x010B	/*"	电流阈值 3 上限	"*/                    
#define	RN8302_PHSUA        0x010C	/*"	采样通道 UA 相位校正寄存器	"*/        
#define	RN8302_PHSUB        0x010D	/*"	采样通道 UB 相位校正寄存器	"*/        
#define	RN8302_PHSUC        0x010E	/*"	采样通道 UC 相位校正寄存器	"*/        
#define	RN8302_PHSIA        0x010F	/*"	采样通道 IA 分段相位校正寄存器	"*/    
#define	RN8302_PHSIB        0x0110	/*"	采样通道 IB 分段相位校正寄存器	"*/    
#define	RN8302_PHSIC        0x0111	/*"	采样通道 IC 分段相位校正寄存器	"*/    
#define	RN8302_PHSIN        0x0112	/*"	采样通道 IN 相位校正	"*/            
#define	RN8302_GSUA         0x0113	/*"	采样通道 UA 通道增益	"*/            
#define	RN8302_GSUB         0x0114	/*"	采样通道 UB 通道增益	"*/            
#define	RN8302_GSUC         0x0115	/*"	采样通道 UC 通道增益	"*/            
#define	RN8302_GSIA         0x0116	/*"	采样通道 IA 通道增益	"*/            
#define	RN8302_GSIB         0x0117	/*"	采样通道 IB 通道增益	"*/            
#define	RN8302_GSIC         0x0118	/*"	采样通道 IC 通道增益	"*/            
#define	RN8302_GSIN         0x0119	/*"	采样通道 IN 通道增益	"*/            
#define	RN8302_DCOS_UA		0x011A	/*"	采样通道 UA 直流 Offset 校正	"*/    
#define	RN8302_DCOS_UB      0x011B	/*"	采样通道 UB 直流 Offset 校正	"*/    
#define	RN8302_DCOS_UC      0x011C	/*"	采样通道 UC 直流 Offset 校正	"*/    
#define	RN8302_DCOS_IA      0x011D	/*"	采样通道 IA 直流 Offset 校正	"*/    
#define	RN8302_DCOS_IB      0x011E	/*"	采样通道 IB 直流 Offset 校正	"*/    
#define	RN8302_DCOS_IC      0x011F	/*"	采样通道 IC 直流 Offset 校正	"*/    
#define	RN8302_DCOS_IN      0x0120	/*"	采样通道 IN 直流 Offset 校正	"*/    
#define	RN8302_UA_OS        0x0121	/*"	A 相电压有效值 Offset	"*/            
#define	RN8302_UB_OS        0x0122	/*"	B 相电压有效值 Offset	"*/            
#define	RN8302_UC_OS        0x0123	/*"	C 相电压有效值 Offset	"*/            
#define	RN8302_IA_OS        0x0124	/*"	A 相电流有效值 Offset	"*/            
#define	RN8302_IB_OS        0x0125	/*"	B 相电流有效值 Offset	"*/            
#define	RN8302_IC_OS        0x0126	/*"	C 相电流有效值 Offset	"*/            
#define	RN8302_IN_OS        0x0127	/*"	零线电流 1 有效值 Offset	"*/        
#define	RN8302_GPA          0x0128	/*"	A 相有功功率增益	"*/                
#define	RN8302_GPB          0x0129	/*"	B 相有功功率增益	"*/                
#define	RN8302_GPC          0x012A	/*"	C 相有功功率增益	"*/                
#define	RN8302_GQA          0x012B	/*"	A 相无功功率增益	"*/                
#define	RN8302_GQB          0x012C	/*"	B 相无功功率增益	"*/                
#define	RN8302_GQC          0x012D	/*"	C 相无功功率增益	"*/                
#define	RN8302_GSA          0x012E	/*"	A 相视在功率增益	"*/                
#define	RN8302_GSB          0x012F	/*"	B 相视在功率增益	"*/                
#define	RN8302_GSC          0x0130	/*"	C 相视在功率增益	"*/                
#define	RN8302_PA_PHSL      0x0131	/*"	A 相有功分段相位校正寄存器-低段	"*/    
#define	RN8302_PB_PHSL      0x0132	/*"	B 相有功分段相位校正寄存器-低段	"*/    
#define	RN8302_PC_PHSL      0x0133	/*"	C 相有功分段相位校正寄存器-低段	"*/    
#define	RN8302_QA_PHSL      0x0134	/*"	A 相无功分段相位校正寄存器-低段	"*/    
#define	RN8302_QB_PHSL      0x0135	/*"	B 相无功分段相位校正寄存器-低段	"*/    
#define	RN8302_QC_PHSL      0x0136	/*"	C 相无功分段相位校正寄存器-低段	"*/    
#define	RN8302_PA_OS        0x0137	/*"	A 相有功功率 Offset	"*/                
#define	RN8302_PB_OS        0x0138	/*"	B 相有功功率 Offset	"*/                
#define	RN8302_PC_OS        0x0139	/*"	C 相有功功率 Offset	"*/                
#define	RN8302_QA_OS        0x013A	/*"	A 相无功功率 Offset	"*/                
#define	RN8302_QB_OS        0x013B	/*"	B 相无功功率 Offset	"*/                
#define	RN8302_QC_OS        0x013C	/*"	C 相无功功率 Offset	"*/                
#define	RN8302_FUA_OS       0x013D	/*"	A 相基波电压有效值 Offset	"*/        
#define	RN8302_FUB_OS       0x013E	/*"	B 相基波电压有效值 Offset	"*/        
#define	RN8302_FUC_OS       0x013F	/*"	C 相基波电压有效值 Offse	"*/        
#define	RN8302_FIA_OS       0x0140	/*"	A 相基波电流有效值 Offset	"*/        
#define	RN8302_FIB_OS       0x0141	/*"	B 相基波电流有效值 Offset	"*/        
#define	RN8302_FIC_OS       0x0142	/*"	C 相基波电流有效值 Offse	"*/        
#define	RN8302_GFPA         0x0143	/*"	A 相基波有功功率增益	"*/            
#define	RN8302_GFPB         0x0144	/*"	B 相基波有功功率增益	"*/            
#define	RN8302_GFPC         0x0145	/*"	C 相基波有功功率增益	"*/            
#define	RN8302_GFQA         0x0146	/*"	A 相基波无功功率增益	"*/            
#define	RN8302_GFQB         0x0147	/*"	B 相基波无功功率增益	"*/            
#define	RN8302_GFQC         0x0148	/*"	C 相基波无功功率增益	"*/            
#define	RN8302_GFSA         0x0149	/*"	A 相基波视在功率增益	"*/            
#define	RN8302_GFSB         0x014A	/*"	B 相基波视在功率增益	"*/            
#define	RN8302_GFSC         0x014B	/*"	C 相基波视在功率增益	"*/            
#define	RN8302_FPA_PHS      0x014C	/*"	A 相基波有功相位校正寄存器	"*/        
#define	RN8302_FPB_PHS      0x014D	/*"	B 相基波有功相位校正寄存器	"*/        
#define	RN8302_FPC_PHS      0x014E	/*"	C 相基波有功相位校正寄存器	"*/        
#define	RN8302_FQA_PHS      0x014F	/*"	A 相基波无功相位校正寄存器	"*/        
#define	RN8302_FQB_PHS      0x0150	/*"	B 相基波无功相位校正寄存器	"*/        
#define	RN8302_FQC_PHS      0x0151	/*"	C 相基波无功相位校正寄存器	"*/        
#define	RN8302_FPA_OS       0x0152	/*"	A 相基波有功功率 Offset	"*/            
#define	RN8302_FPB_OS       0x0153	/*"	B 相基波有功功率 Offset	"*/            
#define	RN8302_FPC_OS       0x0154	/*"	C 相基波有功功率 Offset	"*/            
#define	RN8302_FQA_OS       0x0155	/*"	A 相基波无功功率 Offset	"*/            
#define	RN8302_FQB_OS       0x0156	/*"	B 相基波无功功率 Offset	"*/            
#define	RN8302_FQC_OS       0x0157	/*"	C 相基波无功功率 Offset	"*/            
#define	RN8302_SAGCFG       0x0158	/*"	电压暂降阈值配置	"*/                
#define	RN8302_OVLVL        0x0159	/*"	过压阈值配置	"*/                    
#define	RN8302_OILVL        0x015A	/*"	过流阈值配置	"*/     
/*"*********************EMM 配置和状态寄存器********************************************************"*/
#define	RN8302_CFCFG        0x0160	/*"	CF 引脚配置寄存器	"*/                
#define	RN8302_EMUCFG       0x0161	/*"	EMU 配置寄存器	"*/                    
#define	RN8302_EMUCON       0x0162	/*"	EMU 控制寄存器	"*/                    
#define	RN8302_WSAVECON     0x0163	/*"	采样数据写缓存控制寄存器	"*/        
#define	RN8302_EMMIE        0x0164	/*"	EMM 中断允许寄存器，写保护	"*/        
#define	RN8302_EMMIF        0x0165	/*"	EMM 中断标志和状态寄存器	"*/        
#define	RN8302_PQSign       0x0166	/*"	有功无功功率方向寄存器	"*/            
#define	RN8302_Noload       0x0167	/*"	潜动启动状态寄存器	"*/                
#define	RN8302_IRegionS     0x0168	/*"	电流分区状态寄存器	"*/                
#define	RN8302_PHASES       0x0169	/*"	相电压电流状态寄存器	"*/            
#define	RN8302_CheckSum1    0x016A	/*"	EMM 校表和配置寄存器校验和	"*/        
/*"*********************NVM1 配置和状态寄存器********************************************************"*/
#define	RN8302_NVM1CFG      0x0170	/*"	NVM1 配置寄存器	"*/                    
#define	RN8302_NVM1IF       0x0171	/*"	NVM1 状态寄存器	"*/  
/*"*********************NVM2 配置和状态寄存器********************************************************"*/
#define	RN8302_NVM2CFG      0x0172	/*"	NVM2 配置寄存器	"*/                    
#define	RN8302_NVM2CMPA     0x0173	/*"	NVM2 IA 比较器控制寄存器	"*/        
#define	RN8302_NVM2CMPB     0x0174	/*"	NVM2 IB 比较器控制寄存器	"*/        
#define	RN8302_NVM2CMPC     0x0175	/*"	NVM2 IC 比较器控制寄存器	"*/        
#define	RN8302_NVM2IF       0x0176	/*"	全失压状态寄存器	"*/ 
/*"*********************系统配置寄存器********************************************************"*/
#define	RN8302_WREN         0x0180	/*"	写使能寄存器	"*/                    
#define	RN8302_WMSW         0x0181	/*"	工作模式切换寄存器	"*/                
#define	RN8302_SOFTRST      0x0182	/*"	软件复位寄存器	"*/                    
#define	RN8302_ADCCFG       0x0183	/*"	ADC 配置寄存器	"*/                    
#define	RN8302_MODSEL       0x0186	/*"	三相四线/三相三线模式选择寄存器	"*/    
/*"*********************系统状态寄存器********************************************************"*/
#define	RN8302_SYSSR        0x018A	/*"	系统状态寄存器	"*/                    
#define	RN8302_CheckSum2    0x018B	/*"	NVM1、 NVM2、系统配置寄存器校验和	"*/
#define	RN8302_RData        0x018C	/*"	上一次 SPI 读出的数据	"*/            
#define	RN8302_WData        0x018D	/*"	上一次 SPI 写入的数据	"*/            
#define	RN8302_LRBufAddr    0x018E	/*"	最后一次读波形缓存的地址	"*/        
#define	RN8302_DeviceID     0x018F	/*"	RN8302 Device ID	"*/           
/*"*********************EMM 校表寄存器 II********************************************************"*/
#define	RN8302_ZXOTU        0x0190	/*"	电压夹角及测频阈值寄存器	"*/        
#define	RN8302_AUOTDC_EN    0x0191	/*"	直流 OFFSET 自动校正使能寄存器	"*/    
#define	RN8302_ZXOTCFG      0x0192	/*"	过零计算配置及标志寄存器	"*/        
#define	RN8302_IN_WaveEN    0x0194	/*"	IN 波形缓存使能寄存器	"*/            
#define	RN8302_PA_PHSM      0x01B0 	/*"	A 相有功分段相位校正寄存器-中段	"*/    
#define	RN8302_PA_PHSH      0x01B1	/*"	A 相有功分段相位校正寄存器-高段	"*/    
#define	RN8302_PB_PHSM      0x01B2	/*"	B 相有功分段相位校正寄存器-中段	"*/    
#define	RN8302_PB_PHSH      0x01B3	/*"	B 相有功分段相位校正寄存器-高段	"*/    
#define	RN8302_PC_PHSM      0x01B4	/*"	C 相有功分段相位校正寄存器-中段	"*/    
#define	RN8302_PC_PHSH      0x01B5	/*"	C 相有功分段相位校正寄存器-高段	"*/    
#define	RN8302_QA_PHSM      0x01B6	/*"	A 相无功分段相位校正寄存器-中段	"*/    
#define	RN8302_QA_PHSH      0x01B7	/*"	A 相无功分段相位校正寄存器-高段	"*/    
#define	RN8302_QB_PHSM      0x01B8	/*"	B 相无功分段相位校正寄存器-中段	"*/    
#define	RN8302_QB_PHSH      0x01B9	/*"	B 相无功分段相位校正寄存器-高段	"*/    
#define	RN8302_QC_PHSM      0x01BA 	/*"	C 相无功分段相位校正寄存器-中段	"*/    
#define	RN8302_QC_PHSH		0x01BB 	/*"	C 相无功分段相位校正寄存器-高段	"*/    
   						


#define	RN8302_WREN_EN      0xE5 	/*"	写使能命令	"*/    
#define	RN8302_WREN_DIS     0xDC 	/*"	写保护命令	"*/    



#define RN8302_SpiTXDFLT			0xFF		/*" spi默认传输数据"*/  
 
#define SPI_CS_HIGH() 	HAL_GPIO_WritePin( Rn_nss_GPIO_Port, Rn_nss_Pin, GPIO_PIN_SET );
#define SPI_CS_LOW() 	HAL_GPIO_WritePin( Rn_nss_GPIO_Port, Rn_nss_Pin, GPIO_PIN_RESET );
 
void Write_SPI_OneByte(uint8_t TxData);
uint8_t Read_SPI_OneByte(void);
uint32_t READ_SPI(uint16_t Address,uint8_t Data_len);
void Write_SPI(uint16_t Address, uint32_t dwData,uint8_t Date_len);
void ReadAmmeterData(void);
void delay_us(uint32_t us);

static void RN8302_GraftDelay_us(uint32_t us);
static void RN8302_GraftDelay_ms(uint32_t ms);
void RN8302_GraftSpiInit(void);
static void RN8302_GraftSpiWriteByte(uint8_t TxData);
static uint8_t RN8302_GraftSpiReadByte(void);
void Write_SPI(uint16_t Address, uint32_t dwData,uint8_t Date_len);
static ErrorStatus RN8302_WriteData(uint16_t reg, uint8_t *buff, uint8_t data_len);


 
#endif