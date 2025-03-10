#ifndef _RN8302_H_
#define _RN8302_H_
 
#include "main.h"
#include "stdio.h"
 
//---------------------- RN8302�����Ĵ�����ַ����---------------------------------------------------//
/* Exported define ------------------------------------------------------------*/
/*"*********************ȫ�����������Ĵ���********************************************************"*/
#define	RN8302_UAWAV		0x0000	/*"	A ���ѹ��������	"*/                
#define	RN8302_UBWAV        0x0001	/*"	B ���ѹ��������	"*/                
#define	RN8302_UCWAV        0x0002	/*"	C ���ѹ��������	"*/                
#define	RN8302_IAWAV        0x0003	/*"	A �������������	"*/                
#define	RN8302_IBWAV        0x0004	/*"	B �������������	"*/                
#define	RN8302_ICWAV        0x0005	/*"	C �������������	"*/                
#define	RN8302_INWAV        0x0006	/*"	���ߵ�����������	"*/                
#define	RN8302_UA           0x0007	/*"	A ���ѹ��Чֵ	"*/                    
#define	RN8302_UB           0x0008	/*"	B ���ѹ��Чֵ	"*/                    
#define	RN8302_UC           0x0009	/*"	C ���ѹ��Чֵ	"*/                    
#define	RN8302_USUM         0x000A	/*"	��ѹʸ������Чֵ	"*/                
#define	RN8302_IA           0x000B	/*"	A �������Чֵ	"*/                    
#define	RN8302_IB           0x000C	/*"	B �������Чֵ	"*/                    
#define	RN8302_IC           0x000D	/*"	C �������Чֵ	"*/                    
#define	RN8302_IN           0x000E	/*"	���ߵ�����Чֵ	"*/                    
#define	RN8302_ISUM         0x0010	/*"	����ʸ������Чֵ	"*/                
#define	RN8302_IA_NVM1      0x0011	/*"	NVM1 A �������Чֵ	"*/                
#define	RN8302_IB_NVM1      0x0012	/*"	NVM1 B �������Чֵ	"*/                
#define	RN8302_IC_NVM1      0x0013	/*"	NVM1 C �������Чֵ	"*/                
#define	RN8302_PA           0x0014	/*"	A ���й�����	"*/                    
#define	RN8302_PB           0x0015	/*"	B ���й�����	"*/                    
#define	RN8302_PC           0x0016	/*"	C ���й�����	"*/                    
#define	RN8302_PT           0x0017	/*"	�����й�����	"*/                    
#define	RN8302_QA           0x0018	/*"	A ���޹�����	"*/                    
#define	RN8302_QB           0x0019	/*"	B ���޹�����	"*/                    
#define	RN8302_QC           0x001A	/*"	C ���޹�����	"*/                    
#define	RN8302_QT           0x001B	/*"	�����޹�����	"*/                    
#define	RN8302_SA           0x001C	/*"	A �����ڹ���	"*/                    
#define	RN8302_SB           0x001D	/*"	B �����ڹ���	"*/                    
#define	RN8302_SC           0x001E	/*"	C �����ڹ���	"*/                    
#define	RN8302_STA          0x001F	/*"	RMS �������ڹ���	"*/                
#define	RN8302_PfA          0x0020	/*"	A �๦������	"*/                    
#define	RN8302_PfB          0x0021	/*"	B �๦������	"*/                    
#define	RN8302_PfC          0x0022	/*"	C �๦������	"*/                    
#define	RN8302_PfTA         0x0023	/*"	RMS ���๦������	"*/                
#define	RN8302_PAFCnt       0x0024	/*"	A ���й������������	"*/            
#define	RN8302_PBFCnt       0x0025	/*"	B ���й������������	"*/            
#define	RN8302_PCFCnt       0x0026	/*"	C ���й������������	"*/            
#define	RN8302_PTFCnt       0x0027	/*"	�����й������������	"*/            
#define	RN8302_QAFCnt       0x0028	/*"	A ���޹������������	"*/            
#define	RN8302_QBFCnt       0x0029	/*"	B ���޹������������	"*/            
#define	RN8302_QCFCnt       0x002A	/*"	C ���޹������������	"*/            
#define	RN8302_QTFCnt       0x002B	/*"	�����޹������������	"*/            
#define	RN8302_SAFCnt       0x002C	/*"	A �����ڿ����������	"*/            
#define	RN8302_SBFCnt       0x002D	/*"	B �����ڿ����������	"*/            
#define	RN8302_SCFCnt       0x002E	/*"	C �����ڿ����������	"*/            
#define	RN8302_STFACnt      0x002F	/*"	RMS �������ڿ����������	"*/        
#define	RN8302_EPA          0x0030	/*"	A ���й������Ĵ���	"*/                
#define	RN8302_EPB          0x0031	/*"	B ���й������Ĵ���	"*/                
#define	RN8302_EPC          0x0032	/*"	C ���й������Ĵ���	"*/                
#define	RN8302_EPT			    0x0033	/*"	�����й������Ĵ���	"*/                
#define	RN8302_PosEPA       0x0034	/*"	A �������й������Ĵ���	"*/            
#define	RN8302_PosEPB       0x0035	/*"	B �������й������Ĵ���	"*/            
#define	RN8302_PosEPC       0x0036	/*"	C �������й������Ĵ���	"*/            
#define	RN8302_PosEPT       0x0037	/*"	���������й������Ĵ���	"*/            
#define	RN8302_NegEPA       0x0038	/*"	A �෴���й������Ĵ���	"*/            
#define	RN8302_NegEPB       0x0039	/*"	B �෴���й������Ĵ���	"*/            
#define	RN8302_NegEPC       0x003A	/*"	C �෴���й������Ĵ���	"*/            
#define	RN8302_NegEPT       0x003B	/*"	���෴���й������Ĵ���	"*/            
#define	RN8302_EQA          0x003C	/*"	A ���޹������Ĵ���	"*/                
#define	RN8302_EQB          0x003D	/*"	B ���޹������Ĵ���	"*/                
#define	RN8302_EQC          0x003E	/*"	C ���޹������Ĵ���	"*/                
#define	RN8302_EQT          0x003F	/*"	�����޹������Ĵ���	"*/                
#define	RN8302_PosEQA       0x0040	/*"	A �������޹������Ĵ���	"*/            
#define	RN8302_PosEQB       0x0041	/*"	B �������޹������Ĵ���	"*/            
#define	RN8302_PosEQC       0x0042	/*"	C �������޹������Ĵ���	"*/            
#define	RN8302_PosEQT       0x0043	/*"	���������޹������Ĵ���	"*/            
#define	RN8302_NegEQA       0x0044	/*"	A �෴���޹������Ĵ���	"*/            
#define	RN8302_NegEQB       0x0045	/*"	B �෴���޹������Ĵ���	"*/            
#define	RN8302_NegEQC       0x0046	/*"	C �෴���޹������Ĵ���	"*/            
#define	RN8302_NegEQT       0x0047	/*"	���෴���޹������Ĵ���	"*/            
#define	RN8302_ESA          0x0048	/*"	A �����������Ĵ���	"*/                
#define	RN8302_ESB          0x0049	/*"	B �����������Ĵ���	"*/                
#define	RN8302_ESC          0x004A	/*"	C �����������Ĵ���	"*/                
#define	RN8302_ESTA         0x004B	/*"	RMS �������������Ĵ���	"*/            
#define	RN8302_STV          0x004C	/*"	PQS �������ڹ���	"*/                
#define	RN8302_PfTV         0x004D	/*"	PQS ���๦������	"*/                
#define	RN8302_STFVCnt      0x004E	/*"	PQS �������ڿ����������	"*/        
#define	RN8302_ESTV         0x004F	/*"	PQS �������������Ĵ���	"*/    
/*"*********************����г�����������Ĵ���********************************************************"*/
#define	RN8302_YUA          0x0050	/*"	����ͨ�� UA ������ǼĴ���	"*/        
#define	RN8302_YUB          0x0051	/*"	����ͨ�� UB ������ǼĴ���	"*/        
#define	RN8302_YUC          0x0052	/*"	����ͨ�� UC ������ǼĴ���	"*/        
#define	RN8302_YIA          0x0053	/*"	����ͨ�� IA ������ǼĴ���	"*/        
#define	RN8302_YIB          0x0054	/*"	����ͨ�� IB ������ǼĴ���	"*/        
#define	RN8302_YIC          0x0055	/*"	����ͨ�� IC ������ǼĴ���	"*/        
#define	RN8302_YIN          0x0056	/*"	����ͨ�� IN ������ǼĴ���	"*/        
#define	RN8302_UFreq        0x0057	/*"	��ѹ��Ƶ��	"*/                        
#define	RN8302_FUA          0x0058	/*"	A �������ѹ��Чֵ	"*/                
#define	RN8302_FUB          0x0059	/*"	B �������ѹ��Чֵ	"*/                
#define	RN8302_FUC          0x005A	/*"	C �������ѹ��Чֵ	"*/                
#define	RN8302_FIA          0x005B	/*"	A �����������Чֵ	"*/                
#define	RN8302_FIB          0x005C	/*"	B �����������Чֵ	"*/                
#define	RN8302_FIC          0x005D	/*"	C �����������Чֵ	"*/                
#define	RN8302_FPA          0x005E	/*"	A ������й�����	"*/                
#define	RN8302_FPB          0x005F	/*"	B ������й�����	"*/                
#define	RN8302_FPC          0x0060	/*"	C ������й�����	"*/                
#define	RN8302_FPT          0x0061	/*"	��������й�����	"*/                
#define	RN8302_FQA          0x0062	/*"	A ������޹�����	"*/                
#define	RN8302_FQB          0x0063	/*"	B ������޹�����	"*/                
#define	RN8302_FQC          0x0064	/*"	C ������޹�����	"*/                
#define	RN8302_FQT          0x0065	/*"	��������޹�����	"*/                
#define	RN8302_FSA          0x0066	/*"	A ��������ڹ���	"*/                
#define	RN8302_FSB          0x0067	/*"	B ��������ڹ���	"*/                
#define	RN8302_FSC          0x0068	/*"	C ��������ڹ���	"*/                
#define	RN8302_FSTA         0x0069	/*"	RMS ����������ڹ���	"*/            
#define	RN8302_FPfA         0x006A	/*"	A �������������	"*/                
#define	RN8302_FPfB         0x006B	/*"	B �������������	"*/                
#define	RN8302_FPfC         0x006C	/*"	C �������������	"*/                
#define	RN8302_FPfTA        0x006D	/*"	RMS ���������������	"*/            
#define	RN8302_FPAFCnt      0x006E	/*"	A ������й������������	"*/        
#define	RN8302_FPBFCnt      0x006F	/*"	B ������й������������	"*/        
#define	RN8302_FPCFCnt      0x0070	/*"	C ������й������������	"*/        
#define	RN8302_FPTFCnt      0x0071	/*"	��������й������������	"*/        
#define	RN8302_FQAFCnt      0x0072	/*"	A ������޹������������	"*/        
#define	RN8302_FQBFCnt      0x0073	/*"	B ������޹������������	"*/        
#define	RN8302_FQCFCnt      0x0074	/*"	C ������޹������������	"*/        
#define	RN8302_FQTFCnt      0x0075	/*"	��������޹������������	"*/        
#define	RN8302_FSAFCnt      0x0076	/*"	A ��������ڿ����������	"*/        
#define	RN8302_FSBFCnt      0x0077	/*"	B ��������ڿ����������	"*/        
#define	RN8302_FSCFCnt      0x0078	/*"	C ��������ڿ����������	"*/        
#define	RN8302_FSTAFCnt     0x0079	/*"	RMS ����������ڿ����������	"*/    
#define	RN8302_FEPA         0x007A	/*"	A ������й�����	"*/                
#define	RN8302_FEPB         0x007B	/*"	B ������й�����	"*/                
#define	RN8302_FEPC         0x007C	/*"	C ������й�����	"*/                
#define	RN8302_FEPT         0x007D	/*"	��������й�����	"*/                
#define	RN8302_PosFEPA      0x007E	/*"	A ����������й������Ĵ���	"*/        
#define	RN8302_PosFEPB      0x007F	/*"	B ����������й������Ĵ���	"*/        
#define	RN8302_PosFEPC      0x0080	/*"	C ����������й������Ĵ���	"*/        
#define	RN8302_PosFEPT      0x0081	/*"	������������й������Ĵ���	"*/        
#define	RN8302_NegFEPA      0x0082	/*"	A ����������й������Ĵ���	"*/        
#define	RN8302_NegFEPB      0x0083	/*"	B ����������й������Ĵ���	"*/        
#define	RN8302_NegFEPC      0x0084	/*"	C ����������й������Ĵ���	"*/        
#define	RN8302_NegFEPT      0x0085	/*"	������������й������Ĵ���	"*/        
#define	RN8302_FEQA         0x0086	/*"	A ������޹�����	"*/                
#define	RN8302_FEQB         0x0087	/*"	B ������޹�����	"*/                
#define	RN8302_FEQC         0x0088	/*"	C ������޹�����	"*/                
#define	RN8302_FEQT         0x0089	/*"	��������޹�����	"*/                
#define	RN8302_PosFEQA      0x008A	/*"	A ����������޹������Ĵ���	"*/        
#define	RN8302_PosFEQB      0x008B	/*"	B ����������޹������Ĵ���	"*/        
#define	RN8302_PosFEQC      0x008C	/*"	C ����������޹������Ĵ���	"*/        
#define	RN8302_PosFEQT      0x008D	/*"	������������޹������Ĵ���	"*/        
#define	RN8302_NegFEQA      0x008E	/*"	A �෴������޹������Ĵ���	"*/        
#define	RN8302_NegFEQB      0x008F	/*"	B �෴������޹������Ĵ���	"*/        
#define	RN8302_NegFEQC      0x0090	/*"	C �෴������޹������Ĵ���	"*/        
#define	RN8302_NegFEQT      0x0091	/*"	���෴������޹������Ĵ���	"*/        
#define	RN8302_FESA         0x0092	/*"	A ��������������Ĵ���	"*/            
#define	RN8302_FESB         0x0093	/*"	B ��������������Ĵ���	"*/            
#define	RN8302_FESC         0x0094	/*"	C ��������������Ĵ���	"*/            
#define	RN8302_FESTA        0x0095	/*"	RMS ����������������Ĵ���	"*/        
#define	RN8302_HUA          0x0096	/*"	A ��г����ѹ��Чֵ	"*/                
#define	RN8302_HUB          0x0097	/*"	B ��г����ѹ��Чֵ	"*/                
#define	RN8302_HUC          0x0098	/*"	C ��г����ѹ��Чֵ	"*/                
#define	RN8302_HIA          0x0099	/*"	A ��г��������Чֵ	"*/                
#define	RN8302_HIB          0x009A	/*"	B ��г��������Чֵ	"*/                
#define	RN8302_HIC          0x009B	/*"	C ��г��������Чֵ	"*/                
#define	RN8302_FSTV         0x009C	/*"	PQS ����������ڹ���	"*/            
#define	RN8302_FPfTV        0x009D	/*"	PQS ���������������	"*/            
#define	RN8302_FSTVFCnt     0x009E	/*"	PQS ����������ڿ����������	"*/    
#define	RN8302_FESTV        0x009F	/*"	PQS ����������������Ĵ���	"*/        
/*"*********************EMM У��Ĵ��� I********************************************************"*/
#define	RN8302_HFConst1     0x0100	/*"	��Ƶ��������Ĵ��� 1	"*/            
#define	RN8302_HFConst2     0x0101	/*"	��Ƶ��������Ĵ��� 2	"*/            
#define	RN8302_IStart_PS    0x0102	/*"	�й���������������ֵ�Ĵ���	"*/        
#define	RN8302_IStart_Q     0x0103	/*"	�޹�����������ֵ�Ĵ���	"*/            
#define	RN8302_LostVoltT    0x0104	/*"	ʧѹ��ֵ�Ĵ���	"*/                    
#define	RN8302_ZXOT         0x0105	/*"	������ֵ�Ĵ���	"*/                    
#define	RN8302_PRTH1L       0x0106	/*"	��λ�ֶ�У��������ֵ 1 ����	"*/        
#define	RN8302_PRTH1H       0x0107	/*"	��λ�ֶ�У��������ֵ 1 ����	"*/        
#define	RN8302_PRTH2L       0x0108	/*"	��λ�ֶ�У��������ֵ 2 ����	"*/        
#define	RN8302_PRTH2H       0x0109	/*"	��λ�ֶ�У��������ֵ 2 ����	"*/        
#define	RN8302_IRegion3L    0x010A	/*"	������ֵ 3 ����	"*/                    
#define	RN8302_IRegion3H    0x010B	/*"	������ֵ 3 ����	"*/                    
#define	RN8302_PHSUA        0x010C	/*"	����ͨ�� UA ��λУ���Ĵ���	"*/        
#define	RN8302_PHSUB        0x010D	/*"	����ͨ�� UB ��λУ���Ĵ���	"*/        
#define	RN8302_PHSUC        0x010E	/*"	����ͨ�� UC ��λУ���Ĵ���	"*/        
#define	RN8302_PHSIA        0x010F	/*"	����ͨ�� IA �ֶ���λУ���Ĵ���	"*/    
#define	RN8302_PHSIB        0x0110	/*"	����ͨ�� IB �ֶ���λУ���Ĵ���	"*/    
#define	RN8302_PHSIC        0x0111	/*"	����ͨ�� IC �ֶ���λУ���Ĵ���	"*/    
#define	RN8302_PHSIN        0x0112	/*"	����ͨ�� IN ��λУ��	"*/            
#define	RN8302_GSUA         0x0113	/*"	����ͨ�� UA ͨ������	"*/            
#define	RN8302_GSUB         0x0114	/*"	����ͨ�� UB ͨ������	"*/            
#define	RN8302_GSUC         0x0115	/*"	����ͨ�� UC ͨ������	"*/            
#define	RN8302_GSIA         0x0116	/*"	����ͨ�� IA ͨ������	"*/            
#define	RN8302_GSIB         0x0117	/*"	����ͨ�� IB ͨ������	"*/            
#define	RN8302_GSIC         0x0118	/*"	����ͨ�� IC ͨ������	"*/            
#define	RN8302_GSIN         0x0119	/*"	����ͨ�� IN ͨ������	"*/            
#define	RN8302_DCOS_UA		0x011A	/*"	����ͨ�� UA ֱ�� Offset У��	"*/    
#define	RN8302_DCOS_UB      0x011B	/*"	����ͨ�� UB ֱ�� Offset У��	"*/    
#define	RN8302_DCOS_UC      0x011C	/*"	����ͨ�� UC ֱ�� Offset У��	"*/    
#define	RN8302_DCOS_IA      0x011D	/*"	����ͨ�� IA ֱ�� Offset У��	"*/    
#define	RN8302_DCOS_IB      0x011E	/*"	����ͨ�� IB ֱ�� Offset У��	"*/    
#define	RN8302_DCOS_IC      0x011F	/*"	����ͨ�� IC ֱ�� Offset У��	"*/    
#define	RN8302_DCOS_IN      0x0120	/*"	����ͨ�� IN ֱ�� Offset У��	"*/    
#define	RN8302_UA_OS        0x0121	/*"	A ���ѹ��Чֵ Offset	"*/            
#define	RN8302_UB_OS        0x0122	/*"	B ���ѹ��Чֵ Offset	"*/            
#define	RN8302_UC_OS        0x0123	/*"	C ���ѹ��Чֵ Offset	"*/            
#define	RN8302_IA_OS        0x0124	/*"	A �������Чֵ Offset	"*/            
#define	RN8302_IB_OS        0x0125	/*"	B �������Чֵ Offset	"*/            
#define	RN8302_IC_OS        0x0126	/*"	C �������Чֵ Offset	"*/            
#define	RN8302_IN_OS        0x0127	/*"	���ߵ��� 1 ��Чֵ Offset	"*/        
#define	RN8302_GPA          0x0128	/*"	A ���й���������	"*/                
#define	RN8302_GPB          0x0129	/*"	B ���й���������	"*/                
#define	RN8302_GPC          0x012A	/*"	C ���й���������	"*/                
#define	RN8302_GQA          0x012B	/*"	A ���޹���������	"*/                
#define	RN8302_GQB          0x012C	/*"	B ���޹���������	"*/                
#define	RN8302_GQC          0x012D	/*"	C ���޹���������	"*/                
#define	RN8302_GSA          0x012E	/*"	A �����ڹ�������	"*/                
#define	RN8302_GSB          0x012F	/*"	B �����ڹ�������	"*/                
#define	RN8302_GSC          0x0130	/*"	C �����ڹ�������	"*/                
#define	RN8302_PA_PHSL      0x0131	/*"	A ���й��ֶ���λУ���Ĵ���-�Ͷ�	"*/    
#define	RN8302_PB_PHSL      0x0132	/*"	B ���й��ֶ���λУ���Ĵ���-�Ͷ�	"*/    
#define	RN8302_PC_PHSL      0x0133	/*"	C ���й��ֶ���λУ���Ĵ���-�Ͷ�	"*/    
#define	RN8302_QA_PHSL      0x0134	/*"	A ���޹��ֶ���λУ���Ĵ���-�Ͷ�	"*/    
#define	RN8302_QB_PHSL      0x0135	/*"	B ���޹��ֶ���λУ���Ĵ���-�Ͷ�	"*/    
#define	RN8302_QC_PHSL      0x0136	/*"	C ���޹��ֶ���λУ���Ĵ���-�Ͷ�	"*/    
#define	RN8302_PA_OS        0x0137	/*"	A ���й����� Offset	"*/                
#define	RN8302_PB_OS        0x0138	/*"	B ���й����� Offset	"*/                
#define	RN8302_PC_OS        0x0139	/*"	C ���й����� Offset	"*/                
#define	RN8302_QA_OS        0x013A	/*"	A ���޹����� Offset	"*/                
#define	RN8302_QB_OS        0x013B	/*"	B ���޹����� Offset	"*/                
#define	RN8302_QC_OS        0x013C	/*"	C ���޹����� Offset	"*/                
#define	RN8302_FUA_OS       0x013D	/*"	A �������ѹ��Чֵ Offset	"*/        
#define	RN8302_FUB_OS       0x013E	/*"	B �������ѹ��Чֵ Offset	"*/        
#define	RN8302_FUC_OS       0x013F	/*"	C �������ѹ��Чֵ Offse	"*/        
#define	RN8302_FIA_OS       0x0140	/*"	A �����������Чֵ Offset	"*/        
#define	RN8302_FIB_OS       0x0141	/*"	B �����������Чֵ Offset	"*/        
#define	RN8302_FIC_OS       0x0142	/*"	C �����������Чֵ Offse	"*/        
#define	RN8302_GFPA         0x0143	/*"	A ������й���������	"*/            
#define	RN8302_GFPB         0x0144	/*"	B ������й���������	"*/            
#define	RN8302_GFPC         0x0145	/*"	C ������й���������	"*/            
#define	RN8302_GFQA         0x0146	/*"	A ������޹���������	"*/            
#define	RN8302_GFQB         0x0147	/*"	B ������޹���������	"*/            
#define	RN8302_GFQC         0x0148	/*"	C ������޹���������	"*/            
#define	RN8302_GFSA         0x0149	/*"	A ��������ڹ�������	"*/            
#define	RN8302_GFSB         0x014A	/*"	B ��������ڹ�������	"*/            
#define	RN8302_GFSC         0x014B	/*"	C ��������ڹ�������	"*/            
#define	RN8302_FPA_PHS      0x014C	/*"	A ������й���λУ���Ĵ���	"*/        
#define	RN8302_FPB_PHS      0x014D	/*"	B ������й���λУ���Ĵ���	"*/        
#define	RN8302_FPC_PHS      0x014E	/*"	C ������й���λУ���Ĵ���	"*/        
#define	RN8302_FQA_PHS      0x014F	/*"	A ������޹���λУ���Ĵ���	"*/        
#define	RN8302_FQB_PHS      0x0150	/*"	B ������޹���λУ���Ĵ���	"*/        
#define	RN8302_FQC_PHS      0x0151	/*"	C ������޹���λУ���Ĵ���	"*/        
#define	RN8302_FPA_OS       0x0152	/*"	A ������й����� Offset	"*/            
#define	RN8302_FPB_OS       0x0153	/*"	B ������й����� Offset	"*/            
#define	RN8302_FPC_OS       0x0154	/*"	C ������й����� Offset	"*/            
#define	RN8302_FQA_OS       0x0155	/*"	A ������޹����� Offset	"*/            
#define	RN8302_FQB_OS       0x0156	/*"	B ������޹����� Offset	"*/            
#define	RN8302_FQC_OS       0x0157	/*"	C ������޹����� Offset	"*/            
#define	RN8302_SAGCFG       0x0158	/*"	��ѹ�ݽ���ֵ����	"*/                
#define	RN8302_OVLVL        0x0159	/*"	��ѹ��ֵ����	"*/                    
#define	RN8302_OILVL        0x015A	/*"	������ֵ����	"*/     
/*"*********************EMM ���ú�״̬�Ĵ���********************************************************"*/
#define	RN8302_CFCFG        0x0160	/*"	CF �������üĴ���	"*/                
#define	RN8302_EMUCFG       0x0161	/*"	EMU ���üĴ���	"*/                    
#define	RN8302_EMUCON       0x0162	/*"	EMU ���ƼĴ���	"*/                    
#define	RN8302_WSAVECON     0x0163	/*"	��������д������ƼĴ���	"*/        
#define	RN8302_EMMIE        0x0164	/*"	EMM �ж�����Ĵ�����д����	"*/        
#define	RN8302_EMMIF        0x0165	/*"	EMM �жϱ�־��״̬�Ĵ���	"*/        
#define	RN8302_PQSign       0x0166	/*"	�й��޹����ʷ���Ĵ���	"*/            
#define	RN8302_Noload       0x0167	/*"	Ǳ������״̬�Ĵ���	"*/                
#define	RN8302_IRegionS     0x0168	/*"	��������״̬�Ĵ���	"*/                
#define	RN8302_PHASES       0x0169	/*"	���ѹ����״̬�Ĵ���	"*/            
#define	RN8302_CheckSum1    0x016A	/*"	EMM У������üĴ���У���	"*/        
/*"*********************NVM1 ���ú�״̬�Ĵ���********************************************************"*/
#define	RN8302_NVM1CFG      0x0170	/*"	NVM1 ���üĴ���	"*/                    
#define	RN8302_NVM1IF       0x0171	/*"	NVM1 ״̬�Ĵ���	"*/  
/*"*********************NVM2 ���ú�״̬�Ĵ���********************************************************"*/
#define	RN8302_NVM2CFG      0x0172	/*"	NVM2 ���üĴ���	"*/                    
#define	RN8302_NVM2CMPA     0x0173	/*"	NVM2 IA �Ƚ������ƼĴ���	"*/        
#define	RN8302_NVM2CMPB     0x0174	/*"	NVM2 IB �Ƚ������ƼĴ���	"*/        
#define	RN8302_NVM2CMPC     0x0175	/*"	NVM2 IC �Ƚ������ƼĴ���	"*/        
#define	RN8302_NVM2IF       0x0176	/*"	ȫʧѹ״̬�Ĵ���	"*/ 
/*"*********************ϵͳ���üĴ���********************************************************"*/
#define	RN8302_WREN         0x0180	/*"	дʹ�ܼĴ���	"*/                    
#define	RN8302_WMSW         0x0181	/*"	����ģʽ�л��Ĵ���	"*/                
#define	RN8302_SOFTRST      0x0182	/*"	�����λ�Ĵ���	"*/                    
#define	RN8302_ADCCFG       0x0183	/*"	ADC ���üĴ���	"*/                    
#define	RN8302_MODSEL       0x0186	/*"	��������/��������ģʽѡ��Ĵ���	"*/    
/*"*********************ϵͳ״̬�Ĵ���********************************************************"*/
#define	RN8302_SYSSR        0x018A	/*"	ϵͳ״̬�Ĵ���	"*/                    
#define	RN8302_CheckSum2    0x018B	/*"	NVM1�� NVM2��ϵͳ���üĴ���У���	"*/
#define	RN8302_RData        0x018C	/*"	��һ�� SPI ����������	"*/            
#define	RN8302_WData        0x018D	/*"	��һ�� SPI д�������	"*/            
#define	RN8302_LRBufAddr    0x018E	/*"	���һ�ζ����λ���ĵ�ַ	"*/        
#define	RN8302_DeviceID     0x018F	/*"	RN8302 Device ID	"*/           
/*"*********************EMM У��Ĵ��� II********************************************************"*/
#define	RN8302_ZXOTU        0x0190	/*"	��ѹ�нǼ���Ƶ��ֵ�Ĵ���	"*/        
#define	RN8302_AUOTDC_EN    0x0191	/*"	ֱ�� OFFSET �Զ�У��ʹ�ܼĴ���	"*/    
#define	RN8302_ZXOTCFG      0x0192	/*"	����������ü���־�Ĵ���	"*/        
#define	RN8302_IN_WaveEN    0x0194	/*"	IN ���λ���ʹ�ܼĴ���	"*/            
#define	RN8302_PA_PHSM      0x01B0 	/*"	A ���й��ֶ���λУ���Ĵ���-�ж�	"*/    
#define	RN8302_PA_PHSH      0x01B1	/*"	A ���й��ֶ���λУ���Ĵ���-�߶�	"*/    
#define	RN8302_PB_PHSM      0x01B2	/*"	B ���й��ֶ���λУ���Ĵ���-�ж�	"*/    
#define	RN8302_PB_PHSH      0x01B3	/*"	B ���й��ֶ���λУ���Ĵ���-�߶�	"*/    
#define	RN8302_PC_PHSM      0x01B4	/*"	C ���й��ֶ���λУ���Ĵ���-�ж�	"*/    
#define	RN8302_PC_PHSH      0x01B5	/*"	C ���й��ֶ���λУ���Ĵ���-�߶�	"*/    
#define	RN8302_QA_PHSM      0x01B6	/*"	A ���޹��ֶ���λУ���Ĵ���-�ж�	"*/    
#define	RN8302_QA_PHSH      0x01B7	/*"	A ���޹��ֶ���λУ���Ĵ���-�߶�	"*/    
#define	RN8302_QB_PHSM      0x01B8	/*"	B ���޹��ֶ���λУ���Ĵ���-�ж�	"*/    
#define	RN8302_QB_PHSH      0x01B9	/*"	B ���޹��ֶ���λУ���Ĵ���-�߶�	"*/    
#define	RN8302_QC_PHSM      0x01BA 	/*"	C ���޹��ֶ���λУ���Ĵ���-�ж�	"*/    
#define	RN8302_QC_PHSH		0x01BB 	/*"	C ���޹��ֶ���λУ���Ĵ���-�߶�	"*/    
   						


#define	RN8302_WREN_EN      0xE5 	/*"	дʹ������	"*/    
#define	RN8302_WREN_DIS     0xDC 	/*"	д��������	"*/    



#define RN8302_SpiTXDFLT			0xFF		/*" spiĬ�ϴ�������"*/  
 
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