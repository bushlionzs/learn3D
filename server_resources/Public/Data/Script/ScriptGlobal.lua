math.randomseed( GetCurrentTime() )

--*******************************************************************************
--MissionData�и������ݵĶ���
--*******************************************************************************

MD_GUOJIARENWU_RANDMISSIONID		= {0, 0, 18}
MD_GUOJIARENWU_RANDMISSIONTYPE      = {0, 18, 4}	    --��֤ÿ�ι�����������������Ͳ�ͬ
MD_GUOJIARENWU_LASTDAY				= {0, 22, 9}	    --���������ڻ�������������

MD_GUOJIARENWU_CIRCLE				= {1, 0, 6}		    --���ֻ����ļ���
MD_GUOJIARENWU_HIGH					= {1, 6, 8}		    --����߶���ļ���
MD_GUOJIARENWU_ABANDON				= {1,14,12}	    	--���һ�η���ʱ��
MD_WUTING_CHANGEID                  = {1,26, 5}       	-- ��������ID���������������ߺ������߻ָ�����

MD_BANGHUI_RANDMISSIONID			= {2, 0,18}
MD_BANGHUI_RANDMISSIONTYPE			= {2,18, 4}	    	--��֤ÿ�ΰ����������������Ͳ�ͬ
MD_BANGHUI_LASTDAY					= {2,22, 9}	    	--���������ڻ�������������

MD_BANGHUI_CIRCLE					= {3, 0, 4}			--���ֻ����ļ���
MD_BANGHUI_ABANDON_DAY				= {3, 4, 9}			--��������
MD_BANGHUI_ABANDON					= {3,13,11}	    	--����ʱ�䣨���ӣ�
MD_BANGHUI_HIGH                     = {3,24, 8}

MD_TONGQU_ROUND 					= {4, 0, 1}		    --rounds
MD_TONGQU_CIRCLE 					= {4, 1, 3}	    	--������ļ���
MD_TONGQU_DATE 						= {4, 4, 9}	   	 	--���һ�ν�����ʱ��
DQ_SHOUBIAN_COUNT					= {4,13, 7}	    	--�����ر߳ɹ�����
MD_BUS_PATROL_RECORD				= {4,20, 3}
MD_SKILL_LING_SHUANG				= {4,23, 9}	    	--��˫ʱ��¼ʣ��˫��ʱ��

MD_EQUIP_EXCHANGE1_DAY				= {5, 0, 9}
MD_EQUIP_EXCHANGE1_DAYCOUNT			= {5, 9, 7}	
MD_EQUIP_EXCHANGE2_DAY				= {5,16, 9}
MD_EQUIP_EXCHANGE2_DAYCOUNT			= {5,25, 7}

MD_EQUIP_EXCHANGE3_DAY				= {6, 0, 9}
MD_EQUIP_EXCHANGE3_DAYCOUNT			= {6, 9, 7}	
MD_EQUIP_EXCHANGE4_DAY				= {6,16, 9}
MD_EQUIP_EXCHANGE4_DAYCOUNT			= {6,25, 7}

MD_EQUIP_EXCHANGE5_DAY				= {7, 0, 9}
MD_EQUIP_EXCHANGE5_DAYCOUNT			= {7, 9, 7}	

MD_DATI_JISHI_KAIGUAN				= {7,16, 4}       	--����Ҵ����ʱ����
MD_XIANJIN_FUBEN_TALK_PARAM			= {7,20, 4}       	--�ֽ𸱱��Ի�����

MD_ZHENGSHUI_DATE					= {8, 0,  9}       	--��һ�ν�����ʱ�䣬����Ϊ��λ(0-365)�����Ա�ʾ512
MD_ZHENGSHUI_ABANDON        		= {8, 9, 11}       	--���һ�η�����˰����ʱ�䣨��0����ĵ�N���ӣ�
MD_ZHENGSHUI_HIGHREWARD     		= {8, 20, 3}       	--��˰�߽�������ÿ��ǰ������˰Ϊ�߽���֮�����ڵͽ�
MD_ZHENGSHUI_ROUND	        		= {8, 23, 3}       	--��˰��������3λ�����Ե�8��
MD_ZHENGSHUI_TIMES                  = {8, 26, 4}        --������˰������ɼ��������10��

MD_SHILIAN_LUNHUITAI				= {10, 0, 9}		--�ֻ�̨������ʱ�䣬����Ϊ��λ(0-365)�����Ա�ʾ512
MD_SHILIAN_JINKUANGDONG				= {10, 9, 9}		--��󶴽�����ʱ�䣬����Ϊ��λ(0-365)�����Ա�ʾ512
MD_SHILIAN_QIULONGDAO				= {10,18, 9}		--������������ʱ�䣬����Ϊ��λ(0-365)�����Ա�ʾ512

MD_SHILIAN_ZHANSHENMU				= {11, 0, 9}		--ս��Ĺ������ʱ�䣬����Ϊ��λ(0-365)�����Ա�ʾ512
MD_SHILIAN_JINGJIAOTANG				= {11, 9, 9}		--�����ý�����ʱ�䣬����Ϊ��λ(0-365)�����Ա�ʾ512
MD_SHILIAN_HUANGHEWU				= {11,18, 9}		--�ƺ��������ʱ�䣬����Ϊ��λ(0-365)�����Ա�ʾ512

MD_SHILIAN_JINFUOSHOU				= {12, 0, 9}		--����ֽ�����ʱ�䣬����Ϊ��λ(0-365)�����Ա�ʾ512
MD_WUTING_ENTERMINUTE               = {12, 9,20}      	-- ��������ʱ�䣬�Է���Ϊ��λ��ÿһ��ĵ�N���ӣ����527040

MD_FUBEN_TANBAO_DATE        		= {13, 0, 9}	    --̽�����������
MD_FUBEN_TANBAO_ENTERTIME   		= {13, 9, 5}	    --̽�������ʱ���

MD_GUILD_KILLMONSTER_DATE			= {14, 0, 9}		--���ɱ������
MD_GUILD_KILLMONSTER_COUNT			= {14, 9, 7}		--���ɱ�ֵ��ռ�����
MD_GUILD_GATHER_DATE				= {14,16, 9}		--���ɼ�����
MD_GUILD_GATHER_COUNT				= {14,25, 7}		--���ɼ����ռ�����

MD_DOUBLE_DATE 						= {15, 0,10} 		--��˫���ڼ�¼,����ܼ�¼��2028��
MD_DOUBLE_TIMES						= {15,10, 9}		--ÿ����˫������¼,����¼336��
MD_DOUBLE_TIMES_FLAG				= {15,19, 4}		--��˫ѡ���ʶ

MD_MYSELF_CONVOY_DATE				= {16, 0, 9}		--�����������ڣ�
MD_MYSELF_CONVOY_COUNT				= {16, 9, 7}		--�������ڵ��ռ�����

MD_GUILD_ANZHAN_DATE				= {16,16, 9}		--��ᰵս���ڣ���9��BIT[0,8]�����366
MD_GUILD_ANZHAN_COUNT				= {16,25, 7}		--��ᰵս���ռ���������7��BIT[9,15]�����127

MD_PAO_QIAN_DATE					= {17, 0, 9}		--��Ǯ���ڣ�
MD_PAO_QIAN_COUNT					= {17, 9, 7}		--��Ǯ���ռ�����

DQ_SHOUBIAN_DATE					= {17,16, 9}		--�����ر����ڣ����366
DQ_SHOUBIAN_DAYCOUNT				= {17,25, 7}		--�����رߵ��մ��������127

DQ_SHAGUAI_LOULAN_DATE				= {18, 0, 9}		--����ɱ�����ڣ����366
DQ_SHAGUAI_LOULAN_DAYCOUNT			= {18, 9, 7}		--����ɱ�ֵ��մ��������127
DQ_SHAGUAI_LAIYIN_DATE				= {18,16, 9}		--����ɱ�����ڣ����366
DQ_SHAGUAI_LAIYIN_DAYCOUNT			= {18,25, 7}		--����ɱ�ֵ��մ��������127

DQ_SHAGUAI_KUNLUN_DATE				= {19, 0, 9}		--����ɱ�����ڣ����366
DQ_SHAGUAI_KUNLUN_DAYCOUNT			= {19, 9, 7}		--����ɱ�ֵ��մ��������127
DQ_SHAGUAI_DUNHUANG_DATE			= {19,16, 9}		--����ɱ�����ڣ����366
DQ_SHAGUAI_DUNHUANG_DAYCOUNT		= {19,25, 7}		--����ɱ�ֵ��մ��������127

DQ_CITAN_LOULAN_DATE				= {20, 0, 9}		--���Ҵ�̽���ڣ����366
DQ_CITAN_LOULAN_DAYCOUNT			= {20, 9, 7}		--���Ҵ�̽���մ��������127
DQ_CITAN_LAIYIN_DATE				= {20,16, 9}		--���Ҵ�̽���ڣ����366
DQ_CITAN_LAIYIN_DAYCOUNT			= {20,25, 7}		--���Ҵ�̽���մ��������127

DQ_CITAN_KUNLUN_DATE				= {21, 0, 9}		--���Ҵ�̽���ڣ����366
DQ_CITAN_KUNLUN_DAYCOUNT			= {21, 9, 7}		--���Ҵ�̽���մ��������127
DQ_CITAN_DUNHUANG_DATE				= {21,16, 9}		--���Ҵ�̽���ڣ����366
DQ_CITAN_DUNHUANG_DAYCOUNT			= {21,25, 7}		--���Ҵ�̽���մ��������127

DQ_MIBAO_LOULAN_DATE				= {22, 0, 9}		--�����鱨���ڣ����366
DQ_MIBAO_LOULAN_DAYCOUNT			= {22, 9, 7}		--�����鱨���մ��������127
DQ_MIBAO_LAIYIN_DATE				= {22,16, 9}		--�����鱨���ڣ����366
DQ_MIBAO_LAIYIN_DAYCOUNT			= {22,25, 7}		--�����鱨���մ��������127

DQ_MIBAO_KUNLUN_DATE				= {23, 0, 9}		--�����鱨���ڣ����366
DQ_MIBAO_KUNLUN_DAYCOUNT			= {23, 9, 7}		--�����鱨���մ��������127
DQ_MIBAO_DUNHUANG_DATE				= {23,16, 9}		--�����鱨���ڣ����366
DQ_MIBAO_DUNHUANG_DAYCOUNT			= {23,25, 7}		--�����鱨���մ��������127

DQ_DUOQI_LOULAN_DATE				= {24, 0, 9}		--����������ڣ����366
DQ_DUOQI_LOULAN_DAYCOUNT			= {24, 9, 7}		--������쵱�մ��������127
DQ_DUOQI_LAIYIN_DATE				= {24,16, 9}		--����������ڣ����366
DQ_DUOQI_LAIYIN_DAYCOUNT			= {24,25, 7}		--������쵱�մ��������127

DQ_DUOQI_KUNLUN_DATE				= {25, 0, 9}		--����������ڣ����366
DQ_DUOQI_KUNLUN_DAYCOUNT			= {25, 9, 7}		--������쵱�մ��������127
DQ_DUOQI_DUNHUANG_DATE				= {25,16, 9}		--����������ڣ����366
DQ_DUOQI_DUNHUANG_DAYCOUNT			= {25,25, 7}		--������쵱�մ��������127

MD_COUNTRYBATTLELITE_DATE			= {26,16, 9}		--С��ս����
MD_COUNTRYBATTLELITE_CAMP			= {26,25, 1}		--С��ս��Ӫ
MD_COUNTRYBATTLELITE_KILLCOUNT      = {26,26, 5}		--С��ս�󽫾���ɱ�д󽫾�����

MD_LEVELUP_LEVEL					= {27, 0, 5}		--�����ȡ���Էѵĵȼ������31

MD_TIANJIANG_BAOXIANG_DATE 			= {27,23, 9}		--�콵�������

MD_TIANJIANG_BAOXIANG_ACCEPTED1     = {28, 0, 1}
MD_TIANJIANG_BAOXIANG_ACCEPTED2     = {28, 1, 1}
MD_TIANJIANG_BAOXIANG_ACCEPTED3     = {28, 2, 1}

MD_TIEREN_ACCEPTTIME_DAY 			= {28, 3, 9}		--�������������ʱ����
MD_TIEREN_ACCEPTTIME_MINUTE			= {28,12,11}		--�������������ʱ�����
MD_TIEREN_COMMITTIME 				= {28,23, 9}		--�������������ʱ��

MD_YAOXIE_DIGONG_DAY				= {29, 0, 9}		--��а�ع�������ʱ��
MD_YAOXIE_DIGONG_MINUTE				= {29, 9,11}		--��а�ع���������ʱ�����
MD_YAOXIE_DIGONG_COUNT				= {29,20, 1}		--�����ع�����

MD_FRIEND_MISSION_COMPLETE_DATE 	= {31, 0, 9} 		--����������ɵ�ʱ��
MD_FRIEND_MISSION_KILLMONSTER_NUM   = {31, 9, 9} 		--��������ɱ�ָ���
MD_FRIEND_MISSION_COMPLETE_TIMES    = {31,18, 9} 		--�����������

MD_COUNTRY_FULI_1 					= {31,27, 1}		--��;��¼�Ƿ���ȡ���Ҹ���1 ����:1
MD_COUNTRY_FULI_2 					= {31,28, 1}		--��;��¼�Ƿ���ȡ���Ҹ���2 ����:1
MD_COUNTRY_FULI_3 					= {31,29, 1}		--��;��¼�Ƿ���ȡ���Ҹ���3 ����:1
MD_COUNTRY_FULI_4 					= {31,30, 1}		--��;��¼�Ƿ���ȡ���Ҹ���4 ����:1

MD_SPOUSE_MISSION_DATE              = 
                                    {
									  { 32, 0, 9},     --���������һ�������ʱ��
									  { 32, 9, 9},     --��������ڶ��������ʱ��
									  { 32,18, 9}      --������������������ʱ��
   									} 

MD_BUS_MISSION_COMPLETE_DATE 		= {33, 0, 9} 	    --bus���ɵ�ʱ��
MD_BUS_MISSION_PATROL1 				= {33, 9, 7} 	    --bus�Ѳ�ߵ�1ID
MD_BUS_MISSION_PATROL2 				= {33,16, 7}      	--bus�Ѳ�ߵ�2ID
MD_BUS_MISSION_PATROL3 				= {33,23, 7}     	--bus�Ѳ�ߵ�3ID


--���Ҳ������
--begin
--��ʶ�������������
MD_YIGUODUOQI_COMMIT_DATE			= {34, 0, 9}
MD_YIGUODUOQI_COMMIT_LOULAN 		= {34, 9, 1}
MD_YIGUODUOQI_COMMIT_LAIYIN 		= {34,10, 1}
MD_YIGUODUOQI_COMMIT_KUNLUN 		= {34,11, 1}
MD_YIGUODUOQI_COMMIT_DUNHUANG 		= {34,12, 1}
MD_DIGUOCITAN_COMMIT_LOULAN 		= {34,13, 1}	
MD_DIGUOCITAN_COMMIT_LAIYIN 		= {34,14, 1}
MD_DIGUOCITAN_COMMIT_KUNLUN 		= {34,15, 1}
MD_DIGUOCITAN_COMMIT_DUNHUANG 		= {34,16, 1}

MD_DIGUOCITAN_COMMIT_DATE 			= {35, 0, 9}
MD_DIGUOQIANGLIANG_COMMIT_DATE 		= {35, 9, 9}
MD_DIGUOQIANGLIANG_COMMIT_LOULAN 	= {35,18, 1}
MD_DIGUOQIANGLIANG_COMMIT_LAIYIN 	= {35,19, 1}
MD_DIGUOQIANGLIANG_COMMIT_KUNLUN 	= {35,20, 1}
MD_DIGUOQIANGLIANG_COMMIT_DUNHUANG  = {35,21, 1}
MD_SHAGUAI_COMMIT_DATE 				= {35,22, 9}

MD_SHAGUAI_COMMIT_LOULAN 			= {36, 0, 1}	
MD_SHAGUAI_COMMIT_LAIYIN 			= {36, 1, 1}	
MD_SHAGUAI_COMMIT_KUNLUN 			= {36, 2, 1}	
MD_SHAGUAI_COMMIT_DUNHUANG 			= {36, 3, 1}	

MD_WUTING_GETBASEBUFF_TIME          = {36, 4,20}       	-- ��ȡ��������������ʱ�䣬һ���еĵ�N����

MD_FRIEND_COMPLETE_DAY 				= {37, 0, 9}
MD_FRIEND_COMPLETE_TIMES 			= {37, 9, 9}

MD_MJFY_DATE						= {37,18, 9}		--���̷���date
--MD_MJFY_DAYCOUNT					= {37,27, 5}		--���̷���daycount
MD_ZDOUXI_DATE 						= {38, 0, 9}		--��������Ϸdate
--MD_ZDOUXI_DAYCOUNT 					= {38, 9, 9}		--��������Ϸdaycount

MD_SHENGSICAISHEN_DATE              = {38,18, 9}       	--����������������

MD_SHANXIN_TIME1					= {39, 0,32}		--���ľ�����ϴ�ʹ��ʱ��
MD_SHANXIN_TIME2					= {40, 0,32}		--���Ľ�Ǯ���ϴ�ʹ��ʱ��
MD_SHANXIN_TIME3					= {41, 0,32}		--�����齫���ϴ�ʹ��ʱ��


MD_COLLECTHORSE_TIMES               = {42, 0, 4}       	-- �ռ�ս������ÿ����ɴ���
MD_COLLECTHORSE_DATE                = {42, 4, 9}       	-- �ռ�ս�������������

MD_DAOBAOKE_TIMES                   = {42,17, 4}      	-- ����������ÿ����ɴ���
MD_DAOBAOKE_DATE                    = {42,21, 9}      	-- �����������������

MD_XIANJIN2YINKA_FLAG				= {43, 0, 4}		--�ֽ�����ѡ���ʶ
MD_XIANJIN2YINKA_DATE				= {43, 4, 9}	    --�ֽ���������
MD_XIANJIN2YINKA_DAYCOUNT			= {43,13, 7}	    --�ֽ������ѽӴ���

MD_YIZHESANYOU_DATE                 = {43,20, 9}       	-- ����������������

MD_WULINDAHUI_DATE                  = {44, 5, 9}        --���ִ����������

MD_YIZHESANYOU_COUNTER              = {44,14, 3}       	-- ��������ÿ�ռƴ�

MD_WUTING_EXP_2                     = {44,17,10}      	-- ��������˫������Buff����(����)
MD_WUTING_EXP_4                     = {45, 0,10}      	-- ���������ı�����Buff����(����)
MD_WUTING_CREDIT_4                  = {45,10,10}      	-- ���������ı�����Buff����(����)
MD_WUTING_CREDIT_8                  = {45,20,10}      	-- ���������˱�����Buff����(����)
MD_COUNTRY_BETRAY_LASTDAY			= {46, 0,16}		-- ���һ���ѹ�����
--MD_LVZHUANG40_HOUR					= {46, 16, 5}		--40����װ�淨���Сʱ	
--MD_LVZHUANG40_HOURCOUNT				= {46, 21, 5}		--40����װ�淨��ɴ���

MD_LVZHUANG50_DATE					= {47, 0, 9}		--50����װ�淨���ʱ��	
--MD_LVZHUANG50_DAYCOUNT				= {47, 9, 5}		--50����װ�淨��ɴ���

MD_LVZHUANG60_HOUR					= {47, 14, 5}		--60����װ�淨���Сʱ	
MD_LVZHUANG60_HOURCOUNT				= {47, 19, 5}		--60����װ�淨��ɴ���

MD_DHHT_DATE 						= {48, 0, 9}		--������ͼdate
--MD_DHHT_DAYCOUNT 					= {48, 9, 5}		--������ͼdaycount

MD_HDJR_DATE						= {48,14, 9}		--�Ƶ�����date
--MD_HDJR_DAYCOUNT					= {48,23, 5}		--�Ƶ�����daycount
MD_LVZHUANG70_DATE					= {49, 0, 9}		--70����װ�淨���ʱ��	
--MD_LVZHUANG70_DAYCOUNT				= {49, 9, 5}		--70����װ�淨��ɴ���

MD_ZHUCE_DATE						= {51, 0, 1}		--�������ϼ�¼
MD_PVP2V2_CLEARMARK_DATE			= {51, 1,16}		--����pvp2v2ÿ�ܻ����ۻ�ֵ������
MD_LVZHUANG40_DATE					= {49,14,9}			--40����װDate
MD_LVZHUANG60_DATE					= {49,23,9}			--60����װDate

MD_COUNTRYBATTLELITE_RONGYU			= {54, 0,  16}		--���ǳ�����ÿ������


MD_FUBEN_TRY_HUOCAISHENDIAN			= {55, 0, 1}		--����������������
MD_FUBEN_TRY_DONGHAIHAIYAN			= {55, 3, 1}		--����������
MD_FUBEN_TRY_DAWUSHI				= {55, 4, 1}		--����������
MD_FUBEN_TRY_HUOQIYING				= {55, 5, 1}		--����������
MD_FUBEN_TRY_HESHIBISHANG			= {55, 6, 1}		--����������
MD_FUBEN_TRY_HESHIBIXIA				= {55, 7, 1}		--����������
MD_FUBEN_TRY_FUTUTA6				= {55,10, 1}		--����������
MD_FUBEN_TRY_HUANGJINKUANGDONG		= {55,11, 1}		--����������
MD_FUBEN_TRY_GUMU					= {55,12, 1}		--����������
MD_FUBEN_TRY_FUTUTA4				= {55,13, 1}		--����������
MD_FUBEN_TRY_LANLONGCHENGBAO		= {55,14, 1}		--����������
MD_FUBEN_TRY_HUDI					= {55,15, 1}		--����������
MD_FUBEN_TRY_QIULONGDAO				= {55,18, 1}		--����������
MD_FUBEN_TRY_ZHULUOJI				= {55,19, 1}		--����������
MD_FUBEN_TRY_TIANJINGKENG			= {55,20, 1}		--����������
MD_FUBEN_TRY_BAMIYANG				= {55,23, 1}		--����������

MD_POLO_DATE                        = {56, 0, 9}       	--�����������������
MD_DANCERY_8MANA                    = {56, 9,10}      	--��������8������Buffʣ��ʱ��(����)

MD_YUEBING_FIRSTDAY					= {56,19, 9}		--�±����ʹ��ʱ��

MD_SNZX_DATE						= {57, 0, 9}  		--ʥŮ֮ѡ����     9λ
--MD_SNZX_DAYCOUNT					= {57, 9, 5}  		--ʥŮ֮ѡ���� 5λ

MD_XCZL_DATE						= {57,14, 9}  		--�ĳ���������     9λ 
--MD_XCZL_DAYCOUNT					= {57,23, 5} 		--�ĳ��������  5λ

MD_WUTING_OFFLINE_DATE				= {58, 0, 9}		--�������߹һ�����
MD_WUTING_OFFLINE_TIME				= {58, 9,11}		--�������߹һ�ʱ��
MD_WUTING_OFFLINE_FLAG				= {58,20, 1}		--�������߹һ����

MD_RUOGUO_NEW_TASK_FLAG				= {58,21, 7}		--��������Task����
MD_RUOGUO_NEW_DATE					= {59, 0,16}		--������������
MD_RUOGUO_NEW_DAYCOUNT				= {59,16, 7}		--�����������
MD_RUOGUO_NEW_DAY_SUCCESS_COUNT		= {59,23, 7}		--��������ɹ�����

MD_WUTING_PRECONTRACT_DATE          = {60, 0, 9}       	--����ԤԼ����
MD_WUTING_PRECONTRACT_TIME          = {60, 9,11}       	--����ԤԼʱ��
MD_WUTING_PRECONTRACT_FLAG          = {60,20, 1}       	--����ԤԼ���
									  
MD_LUCKSEED_TIMES    				= {61,26, 2} 		-- ��ͨ������ʹ�ô��� 2Bit
MD_GOLDHOPESEED_TIMES				= {62, 0, 5}		-- �ƽ���Ը����ʹ�ô��� 5Bit
MD_HOPESEED_DAY       				= {62, 9, 9}		-- ��ͨ��Ը����ʹ������ 9Bit
MD_SEED_SCORE         				= {63, 0,17}		-- ��Ը���ӻ��ֱ��� 17Bit
MD_LUCKSEED_DAY       				= {63,21, 9}		-- ��ͨ������ʹ������ 9Bit

MD_GUILD_CIRCLE_MISSION_DATE	 	= {64, 0, 9}		--����ܻ���������
MD_GUILD_CIRCLE_MISSION_DAYCOUNT	= {64, 9, 7}		--����ܻ������ѽӴ���
MD_GUILD_CIRCLE_MISSION_CURRENT_ID  = {64, 16,9}		--����ܻ��������ڵĴ���

MD_YUEBING_BOX_DATE 				= {65, 0, 9}		-- VIP�±����ʹ������ 9Bit

MD_GETGIFT1 						= {65, 9, 1}		-- ��һ���콱��� 1Bit
MD_GETGIFT2 						= {65,10, 1}		-- �ڶ����콱��� 1Bit
MD_GETGIFT3 						= {65,11, 1}		-- �������콱��� 1Bit
MD_GETGIFT4 						= {65,12, 1}		-- ���Ĵ��콱��� 1Bit
MD_GETGIFT_DAY 						= {65,13, 9}		-- �콱���� 9Big

MD_NEIZHENG_WEEKCOUNT               = {66, 0, 3}		-- �����ܸ߽��ƴ� 3Bit
MD_NEIZHENG_WEEK                    = {66, 3,15}		-- �����߽������ 15Bit

MD_KILLCOUNT_DAY					= {66,18, 9}		--ɱ������¼���� 9Bit

MD_COUNTRY_PERSON_REDEEM_WEEK       = {67, 0,15}		-- ���������ȡ�� 15Bit

MD_LABA_COUNT     					= {67,15,16}		--С����ʹ�ô��� 16Bit
MD_AMATIVE_POINT  					= {68, 0,20}		--����ָ�� 20Bit
MD_AMATIVE_DAY    					= {68,20, 9}		--����ָ������ 9Bit
MD_YANHUA_COUNT   					= {69, 0,16}		--�̻�ʹ������   16Bit
MD_BAOZANG_COUNT  					= {69,16,16}		--��ɡ���Į�����͡��������  16Bit
MD_LABA_DAY       					= {70, 0, 9}		--С����ʹ������ 9Bit
MD_YANHUA_DAY     					= {70, 9, 9}		--�̻�ʹ������   9Bit
MD_BAOZANG_DAY    					= {70,18, 9}		--��ɡ���Į�����͡���������  9Bit

MD_GUILD_BHZ_WIN_COUNT		    	= {70,27, 5}		--������-���ս����ʤ������  5 λ
MD_GUILD_BHZ_LOSE_COUNT				= {71, 0, 5}    	--������-���ս����ʧ�ܴ���   5 λ
MD_GUILD_BHZ_PING_COUNT				= {71, 5, 5}	    --������-���ս����ƽ����     5 λ
MD_GUILD_YB_DATE					= {71,10, 9} 	    --������-��������������     9 λ
MD_GUILD_BHZ_DATE					= {71,19, 9}		--������-���ս������� 		9 λ 
MD_GUILD_YB_WEEK_COUNT				= {72, 0, 5}	    --������-������ڱ�����ɴ��� 5 λ

MD_GUILD_JINTIE_DATE				= {72, 5, 9}		--��������ȡ����9λ
MD_GUILD_JINTIE_DAYCOUNT		    = {72,14, 5}		--��������ȡ����5λ

MD_TULONG_COUNT  					= {72,19,10}		--�ٻ����������  10Bit
MD_TULONG_DAY    					= {73, 0, 9}		--�ٻ�����������  9Bit

MD_CUXIAO_DAY						= {73, 9,16}		--��ĩ�������߿���ʱ�ޣ�30��ſ��ٴ�ʹ�ô˵���

MD_MENTAL_SCORE						= {74, 0,16}		--��������������һ�����죬���920*7
MD_MENTAL_WEEK						= {74,16, 9}		--����������

MD_HANLEJUBAOPEN_DAY				= {75, 0,32}		--���־۱������

MD_TOPLIST_PRISE_FLAG				= {76, 0, 8}  		--���а��콱��� 8λ
MD_TOPLIST_PRISE_DATE  				= {76, 8, 9}		--���а��콱������� 9λ

MD_EXCHANGE_EXP_BATTLESCORE 		= {76,17, 9}		-- ս�����ֻ��������� 9bit

MD_CUXIAO1_DAY						= {77, 0,16}		--����������ҿ���ʱ�ޣ�30��ſ��ٴ�ʹ�ô˵���, 16bit

MD_HUOLIDAN_DAY						= {78, 0, 9}		--ǿЧ��������һ��ʹ��һ�� ����9bit
MD_PVP2V2_LEVEL_DAY  				= {78, 9, 9}		--��¼pvp2v2�ȼ���ˢ��ʱ�� 9Bit

MD_THREELOOP_FINFLAG				= {78,18, 1}		--����Ƿ������������
MD_THREELOOP_FUBENINDEX				= {78,19, 4}		--������������ֵ
MD_THREELOOP_SUBDATE				= {78,23, 9}		--�ύ����������������

MD_CHENGJIOU_BANGGONG				= {79, 0, 9}		--�ﹱ�����飬һ��һ�һ�� ����9bit
MD_CHENGJIOU_SHENGWANG				= {79, 9, 9}		--���������飬һ��һ�һ�� ����9bit
MD_CHENGJIOU_RONGYU					= {79,18, 9}		--���������飬һ��һ�һ�� ����9bit

MD_ZHANCHEYAYUN_COUNT 				= {80,24, 7} 		--ս��Ѻ�˵��ռ����� ���� 7
MD_ZHANCHEYAYUN_DATE 				= {81, 0, 9} 		--ս��Ѻ������ ���� 9

MD_GUOZHI_DAY						= {81, 9, 9}		--��֭��������̽���� ���� 9
MD_GUOZHI_DAYCOUNT					= {81,18, 3}		--��֭��������̽���� ���� 3

MD_SHOUHU_DATE						= {81,21, 9}		--�ػ���������,�����ػ�����ȸ�ػ�����һ��,һ�����ֻ����һ��,����ֻ��һ��

MD_SANHUAN_FUBEN_TALK_MODE			= {82, 0, 4}		--��������ģʽ�Ի�
MD_CHANCHU_FUBEN_TALK_MODE			= {82, 4, 4}		--��������ģʽ�Ի�	
MD_CHANCHU_FUBEN_TALK_LEVEL			= {82, 8, 4}		--���������ȼ��Ի�	

MD_QUIZ_DATE 						= {82,12, 9}		--���ջ���� ���� 9
MD_QUIZ_COUNT						= {82,21, 5}		--���ջ���ռ����� ���� 5

MD_CHANCHU_FUBEN_TALK_NPC_OBJID		= {83, 0,32}		--��������objid

MD_WEIWANG_EXP_WEEK					= {84, 0,12}		--����������ϴ�ʹ��ʱ��
MD_WEIWANG_EXP_TIMES				= {84,12, 4}		--���������ʹ�ô���
MD_WEIWANG_MONEY_WEEK				= {84,16,12}		--������Ǯ���ϴ�ʹ��ʱ��
MD_WEIWANG_MONEY_TIMES				= {84,28, 4}		--������Ǯ��ʹ�ô���
MD_WEIWANG_MAJIANG_WEEK				= {85, 0,12}		--�����齫���ϴ�ʹ��ʱ��
MD_WEIWANG_MAJIANG_TIMES			= {85,12, 4}		--�����齫��ʹ�ô���
MD_WEIWANG_SHENGWANG_WEEK			= {85,16,12}		--�����������ϴ�ʹ��ʱ��
MD_WEIWANG_SHENGWANG_TIMES			= {85,28, 4}		--����������ʹ�ô���
MD_WEIWANG_HONOR_WEEK			 	= {86, 0,12}		--�����������ϴ�ʹ��ʱ��
MD_WEIWANG_HONOR_TIMES		  		= {86,12, 4}		--����������ʹ�ô���
MD_WEIWANG_GUILD_WEEK			 	= {86,16,12}		--�����ﹱ���ϴ�ʹ��ʱ��
MD_WEIWANG_GUILD_TIMES		  		= {86,28, 4}		--�����ﹱ��ʹ�ô���

MD_JUDIANMONEY_DATE					= {87, 0, 9}		--�ݵ���Ǯ����
MD_JUDIANEXP_DATE					= {87, 9, 9}		--�ݵ��쾭������

MD_WEIWANG_MOONCAKE_WEEK			= {87,18,12}		--��;:�����±����ϴ�ʹ��ʱ��	 ���ȣ�12
MD_WEIWANG_CHARCOAL_WEEK			= {88, 0,12}		--��;:����ľ̿���ϴ�ʹ��ʱ��      ���ȣ�12
MD_WEIWANG_SUIHUO_WEEK				= {88,12,12}		--��;:�����̽����ˮ���ϴ�ʹ��ʱ��      ���ȣ�12
MD_WEIWANG_XUANCHAI_WEEK			= {89, 0,12}		--��;:�����̽�����Ųʣ��ϴ�ʹ��ʱ��      ���ȣ�12
MD_WEIWANG_HAILAN_WEEK				= {89,12,12}		--��;:�����̽�����������ϴ�ʹ��ʱ��      ���ȣ�12
MD_WEIWANG_YUNGUANG_WEEK			= {90, 0,12}		--��;:�����̽�����ι⣩�ϴ�ʹ��ʱ��      ���ȣ�12

MD_WEIWANG_ITEM_WEEK_1				= {91, 0,12}		--��;:�������ϰ��ϴ�ʹ��ʱ��	 ���ȣ�12
MD_WEIWANG_ITEM_WEEK_2				= {91,12,12}		--��;:�������ϰ��ϴ�ʹ��ʱ��    ���ȣ�12

MD_XINBINGSUCHENG_DATECOUNT 		= {91,24, 3}		--�±��ٳ� ���ȣ�3   ÿ�մ���

MD_BANGHUI_TIMES 					= {91,27, 4}		--�������ÿ�ռ��������10�Σ� 4Bits

MD_DANCERY_XP8X10                   = {92, 0,10}        -- ����8������10Сʱʱ��
MD_DANCERY_CREDIT8X10               = {92,10,10}        -- ����8������10Сʱʱ��
MD_DANCERY_MANA8X10                 = {92,20,10}        -- ����8������10Сʱʱ��

MD_LEVEL_TITLE                      = {93, 0, 6}        -- �ȼ��ƺ���ȡ�ܼ���

MD_DENGMI_DATE						= {93,14, 9}		--��������
MD_DENGMI_SCORE						= {93,23, 5}        --����
MD_DENGMI_NPC1						= {93,28, 1}        --NPC1�Ƿ���
MD_DENGMI_NPC2						= {93,29, 1}		--NPC2�Ƿ���
MD_DENGMI_NPC3						= {93,30, 1}		--NPC3�Ƿ���
MD_DENGMI_NPC4						= {93,31, 1}		--NPC4�Ƿ���

MD_RICHANG_DAY   					= {94, 0, 9}		-- �ճ��淨������� 9bit
MD_RICHANG_COUNT 					= {94, 9, 2}	 	-- �ճ��淨ÿ����ɼ��� 2bit

MD_QUIZ_ANSWER 						= {94,11,10}		-- �����˹ٽ���������Ŀ ��Ŀ ���ȣ�10
MD_ZHUISHA_CIRCLE					= {94,21, 4}		-- ����׷ɱ�����񻷼��� 4Bit

MD_DENGMI_NO1  						= {95, 0, 7} 		--����1���
MD_DENGMI_NO2  						= {95, 7, 7} 		--����2���
MD_DENGMI_NO3  						= {95,14, 7} 		--����3���
MD_DENGMI_NO4  						= {95,21, 7} 		--����4���

MD_HONGLAN_DATE						= {96, 0, 9}		--�������ֳ��淨 ����			
MD_HONGLAN_COUNT        			= {96, 9, 4}		--�������ֳ��淨 ����	

MD_XIANGZI_DATE						= {96,13, 9}		--���ֳ��淨���������� ���� 9
MD_XIANGZI_COUNT        			= {96,22, 5}		--���ֳ��淨���������� ���� 5

MD_FUBEN_SANHUANTOTAL    			= {97, 0,13}		--�����������ܴ��� 13
MD_YIZHESANYOU_ITEM_DAY          	= {97,13, 9}		--���������ύ��Ʒ���� 9λ

MD_FUBEN_TIANFU_DATE 	 			= {97,22, 9}		--�츳����_�������� 9λ
MD_FUBEN_TIANFU_DAYCOUNT 			= {98, 0, 3}		--�츳����_�������3λ

MD_DANCERY_CREDIT4X10 				= {98, 3,10}		--10Сʱ4������ʱ�䣨10Bits��
MD_DANCERY_XP4X10 					= {98,13,10}		--10Сʱ4������ʱ�䣨10Bits��

MD_TJMJ_TIMES						= {98,23, 6}		--ÿ���콵ħ����ɴ�����6Bits��
MD_TJMJ_DATE						= {99, 0, 9}		--�콵ħ��������ڣ�9Bits��

MD_YOULECHANG_DATE       			= {99, 9, 9}		--���һ�ν������ֳ�������9

MD_WABAO_USETIME 					= {99,18,14}		--�����������ʱ��-�루14Bit��
MD_WABAO_FINISHED 					= {100, 0, 2}		--��ɴ���(2Bit)
MD_WABAO_WEEK 						= {100, 2, 6}		--�ܼ���(6Bit)
MD_WABAO_TIMES 						= {100, 8, 2}		--������ɴ���(2Bit)
MD_WABAO_DUIHUAN1                   = {100,10, 1}       --�����ڱ��һ����
MD_WABAO_DUIHUAN2                   = {100,11, 1}       --�����ڱ��һ����
MD_MOJUN_DUIHUAN                    = {100,12, 1}       --�콵ħ���һ����
MD_MOJUN_WEEK                       = {100,13,12}       --�콵ħ���һ��ܼ���

MD_FUBEN_HUAPI_DAYCOUNT         	= {100,25, 3}		--���Բ��Ƥ���� ����3λ
MD_FUBEN_HUAPI_DATE					= {101, 0, 9}       --���Բ��Ƥ���� ���� 9λ

MD_FUBEN_WEEKEND_SANFAN_DATE		= {101, 9, 9}       --�������� ���� 9λ

MD_GUILD_CIRCLE_MISSION_DATE_NV	 	= {101,18,12}		--����ܻ���������

MD_OFFLINE_TRAIN_FLAG     			= {102, 0, 1}      	--���ߴ�����Ч��־
MD_OFFLINE_TRAIN_MIN       			= {102, 1,15}	    --���ߴ���ʣ�����

MD_TIANFU_DONGSHUANG 				= {102,16,10}		--��˫buff����(����)

--MD_WULONG_DUIHUAN_DATE				= {103, 0, 9}		--��������һ�������  ����MD add by czg 2010-9-14 0:04:37 ����ɾ��
MD_DAGUANYUAN_DATE 					= {103, 9, 9}		--���԰��������

MD_LINGDIJINGONG_1_DATE       		= {103,18, 9}		--���ȣ�9
MD_LINGDIJINGONG_1_DAYCOUNT   		= {103,27, 4}		--���ȣ�4

MD_LINGDIJINGONG_2_DATE       		= {104, 0, 9}		--���ȣ�9
MD_LINGDIJINGONG_2_DAYCOUNT   		= {104, 9, 4}		--���ȣ�4

MD_LINGDIJINGONG_3_DATE       		= {104,13, 9}		--���ȣ�9
MD_LINGDIJINGONG_3_DAYCOUNT   		= {104,22, 4}		--���ȣ�4

MD_LINGDIJINGONG_4_DATE       		= {105, 0, 9}		--���ȣ�9
MD_LINGDIJINGONG_4_DAYCOUNT   		= {104,26, 4}		--���ȣ�4

MD_LINGDIJINGONG_5_DATE       		= {105, 9, 9}		--���ȣ�9
MD_LINGDIJINGONG_5_DAYCOUNT   		= {105,18, 4}		--���ȣ�4

MD_LINGDIJINGONG_6_DATE       		= {105,22, 9}		--���ȣ�9
MD_LINGDIJINGONG_6_DAYCOUNT   		= {106, 0, 4}		--���ȣ�4

MD_LINGDIJINGONG_7_DATE		  		= {106, 4, 9}		--���ȣ�9
MD_LINGDIJINGONG_7_DAYCOUNT   		= {106,13, 4}		--���ȣ�4

MD_LINGDIJINGONG_8_DATE       		= {106,17, 9}		--���ȣ�9
MD_LINGDIJINGONG_8_DAYCOUNT   		= {106,26, 4}		--���ȣ�4

MD_LINGDIJINGONG_9_DATE       		= {107, 0, 9}		--���ȣ�9
MD_LINGDIJINGONG_9_DAYCOUNT   		= {107, 9, 4}		--���ȣ�4

MD_DAGUANYUAN_SHOP_DATE        		= {107,13, 9}		--9λ ����
MD_DAGUANYUAN_SHOP_DAYCOUNT    		= {107,22, 4}		--4λ ����

MD_WULONG_DUIHUAN_DATE				= {108, 0,12}		--��������һ��ĵڼ���

MD_MBATTLE_SIGNSTATE			    = {108,21, 1}		--���ս��ǩ֤״̬ 0 �رձ���ǩ֤ 1 ��������ǩ֤������ս������
MD_MBATTLE_SIGNTIME			    	= {109, 0,10}		--���ս��ǩ֤ʱ�䣬10bit���뵥λ����� 1024 ��

MD_HUANGDIMILING_DATE        		= {109,10, 9}		--�ʵ�����ʱ��
MD_YANHUA_WEEK 						= {109,19,10}		--��2009��1��1�վ���N��   

MD_GUILD_SUCHENG_DATE    			= {110, 0, 9}		--����ٳɹ����� 9λ
MD_ITEM_OTHER_197_DATE 				= {111,12, 9}		--9λ ���������CDʱ��
MD_HUODONG_JIERILINGJIANG_DATE		= {111,21, 9}		--9λ �����콱

MD_TISHENSHADAI_DATE				= {112, 0, 9}		--���ר�����������
MD_TISHENSHADAI_DAYCOUNT			= {112, 9, 8}		--���ר�����������

MD_BATTLEHONOUR_WEEKDAY				= {112,17,12}		--ս��������¼������
MD_BATTLEHONOUR_WEEKVALUE			= {113, 0,24}		--ս��������
MD_FANGYUZHILU_DATE					= {114, 9 ,9}     	--����֮·����
MD_FANGYUZHILU_DAYCOUNT				= {114,18 ,3}   	--����֮·����

MD_WABAO_DAYFLAG 					= {114,21, 1} 		-- �ڱ��������������ֱ��1Bit
MD_ZHUANGONG_COEFFICIENT			= {114,22, 1}		--ְҵר���츳���� 1bit
MD_ZHUANGONG_COEFFICIENT_RESET		= {114,23, 1}		--ְҵר���츳 ��־�Ƿ���й�ϵ������
MD_HORSE_COMPOSE_DATE				= {116, 0,15}	    --���һ����˺ϳ�����

--------------------------------------------------------------------------------------------------------------------
--ע:�벻Ҫ�ڴ�������������κ�MD
MD_FEAST_BEGIN						= {180, 0, 0}		--���ʼMD

MD_CURRENT_FEAST_ID 				= 6					--��������ʱ��,��������ֵ
MD_FEAST_INDEX   					= {180, 0,16}		--��;�Ǽ�¼��������� ����:16

--MD_CURRENT_FEAST_ID = 0
MD_XINGYUN_ZUANSHI					= {180,16, 5}		--��;��¼����ȡ��ʯ��ʣ����� ����:5
MD_XINGYUN_XISHIJI					= {180,21, 5}		--��;��¼����ȡϴʯ����ʣ����� ����:5
MD_XINGYUN_ZHANGMENPAI				= {180,26, 5}		--��;��¼����ȡ�����Ƶ�ʣ����� ����:5
MD_XINGYUN_JINYANZHUANG				= {181, 0, 5}		--��;��¼����ȡ����װ��ʣ����� ����:5  
MD_XINGYUN_YUEBING					= {181, 5, 5}		--��;��¼����ȡ�±���ʣ����� ����:5   
MD_XINGYUN_BANGGONG					= {181,10, 5}		--��;��¼����ȡ�ﹱ��ʣ����� ����:5   
MD_XINGYUN_RONGYU					= {181,15, 5}		--��;��¼����ȡ������ʣ����� ����:5   
MD_XINGYUN_SHENGWANG				= {181,20, 5}		--��;��¼����ȡ������ʣ����� ����:5   
MD_XINGYUN_ZHANCHANG				= {181,25, 5}		--��;��¼����ȡս�����ֵ�ʣ����� ����:5 
MD_XINGYUN_XIANYIN					= {182, 0, 5}		--��;��¼����ȡ������ʣ�����

--MD_CURRENT_FEAST_ID = 1
MD_QINGMING_DAY 					= {180, 16,9}		--�����ڻ��
MD_QINGMING_COUNT 					= {180, 25,5}		--�����ڻ����
MD_YUREN_COUNT1						= {180, 30,1} 		--���˽ڻһ��byte
MD_YUREN_COUNT2 					= {180, 31,1} 		--���˽ڻһ��byte
MD_YUREN_COUNT3 					= {181,  0,1} 		--���˽ڻһ��byte

--MD_CURRENT_FEAST_ID = 2
MD_LINGJIANG_TIME1					= {180,16, 1}   	--����ͽ�
MD_LINGJIANG_TIME2					= {180,17, 1}   	--����ͽ�

--MD_CURRENT_FEAST_ID = 3
MD_NEICE_LINGJIANG_TIME1			= {180,16, 1}   	--�ڲ�������
MD_NEICE_LINGJIANG_TIME2			= {180,17, 1}   	--�ڲ�������
MD_NEICE_LINGJIANG_TIME3			= {180,18, 1}   	--�ڲ�������

--MD_CURRENT_FEAST_ID = 4
MD_ZHONGQIU_DAY1					= {180,16, 9} 		--��������
MD_ZHONGQIU_DAY2					= {181,0 , 9} 		--��������

--MD_CURRENT_FEAST_ID = 5
MD_JINLINGJIANG_DAY1					= {180,16, 9} 		--���ά����
MD_JINLINGJIANG_DAY2					= {181,0 , 9} 		--���ά����

--MD_CURRENT_FEAST_ID = 6
MD_GANENJIE_DAY1					= {180,16, 9} 		--�ж�������
MD_GANENJIE_DAY2					= {181,0 , 9} 		--�ж�������


MD_FEAST_END						= {190, 0, 0}		--�����MD
--------------------------------------------------------------------------------------------------------------------
--�벻���ڴ��������MD
MD_VERSION_BEGIN					= 191				--�汾������ʼ

MD_VERSION_FLAG_0					= {191, 0, 1}		--�汾����0
MD_VERSION_FLAG_1					= {191, 1, 1}		--�汾����1
MD_VERSION_FLAG_2					= {191, 2, 1}		--�汾����2

MD_VERSION_BEGIN					= 195				--�汾���ƽ���
--------------------------------------------------------------------------------------------------------------------

MD_FUBEN_TALK_INDEX					= {198, 0,16}		--�����ĸ�����Index
MD_FUBEN_ZHUJIAZHUANG2_DATE			= {199, 0, 9}	    --ף��ׯ2����
MD_FUBEN_ZHUJIAZHUANG2_DAYCOUNT		= {199, 9, 7}	    --ף��ׯ2�ѽӴ���
MD_FUBEN_ZHUJIAZHUANG3_DATE			= {199,16, 9}	    --ף��ׯ3����
MD_FUBEN_ZHUJIAZHUANG3_DAYCOUNT		= {199,25, 7}	    --ף��ׯ3�ѽӴ���

MD_FUBEN_DAWUSHI_DATE				= {200, 0, 9}	    --����������
MD_FUBEN_DAWUSHI_DAYCOUNT			= {200, 9, 7}	    --�������ѽӴ���
MD_FUBEN_JUNYAOYAOKOU_DATE			= {200,16, 9}	    --��Ҥ������
MD_FUBEN_JUNYAOYAOKOU_DAYCOUNT		= {200,25, 7}	    --��Ҥ������

MD_FUBEN_DONGHAIHAIYAN_DATE			= {201,16, 9}	    --��Ѩ����
MD_FUBEN_DONGHAIHAIYAN_DAYCOUNT		= {201,25, 7}	    --��Ѩ�ѽӴ���

MD_FUBEN_HUOQIYING_DATE				= {202, 0, 9}	    --�ƺ�������
MD_FUBEN_HUOQIYING_DAYCOUNT			= {202, 9, 7}	    --�ƺ����ѽӴ���
MD_FUBEN_HESHIBISHANG_DATE			= {202,16, 9}	    --���������
MD_FUBEN_HESHIBISHANG_DAYCOUNT		= {202,25, 7}	    --������ѽӴ���

MD_FUBEN_HESHIBIXIA_DATE		    = {203, 0, 9}	    --���ǵ�����
MD_FUBEN_HESHIBIXIA_DAYCOUNT		= {203, 9, 7}	    --���ǵ��ѽӴ���
MD_FUBEN_GOULANQUTAI_DATE		  	= {203,16, 9}	    --������̨����
MD_FUBEN_GOULANQUTAI_DAYCOUNT		= {203,25, 7}	    --������̨�ѽӴ���

MD_FUBEN_FUTUTA6_DATE				= {204, 0, 9}	    --��վ�����
MD_FUBEN_FUTUTA6_DAYCOUNT			= {204, 9, 7}	    --��վ��ѽӴ���
MD_FUBEN_HUANGJINKUANGDONG_DATE		= {204,16, 9}	    --�ƽ������
MD_FUBEN_HUANGJINKUANGDONG_DAYCOUNT	= {204,25, 7}	    --�ƽ���ѽӴ�

MD_FUBEN_GUMU_DATE					= {205, 0, 9}	    --��Ĺ����
MD_FUBEN_GUMU_DAYCOUNT				= {205, 9, 7}	    --��Ĺ����
MD_FUBEN_FUTUTA4_DATE				= {205,16, 9}	    --��4����
MD_FUBEN_FUTUTA4_DAYCOUNT			= {205,25, 7}	    --��4����

MD_FUBEN_LANLONGCHENGBAO_DATE		= {206, 0, 9}	    --�����Ǳ�����
MD_FUBEN_LANLONGCHENGBAO_DAYCOUNT	= {206, 9, 7}	    --�����Ǳ�����

MD_FUBEN_YONGYISENGLIN_DATE			= {207,16, 9}	    --��ҹɭ������
MD_FUBEN_YONGYISENGLIN_DAYCOUNT		= {207,25, 7}	    --��ҹɭ������

MD_FUBEN_QIULONGDAO_DATE			= {209, 0, 9}	    --����������
MD_FUBEN_QIULONGDAO_DAYCOUNT		= {209, 9, 7}	
MD_FUBEN_ZHULUOJI_DATE				= {209,16, 9}	    --٪�޼�����
MD_FUBEN_ZHULUOJI_DAYCOUNT			= {209,25, 7}

MD_FUBEN_TIANJINGKENG_DATE			= {210, 0, 9}	    --�쾮������
MD_FUBEN_TIANJINGKENG_DAYCOUNT		= {210, 9, 7}

MD_HESHIBI_INTER_DATE				= {211, 0, 9}	    --�����3����Ƕ����
MD_HESHIBI_INTER_DAYCOUNT			= {211, 9, 7}

MD_FUBEN_FOSHOU_DATE				= {211,16, 9}	    --���������
MD_FUBEN_FOSHOU_DAYCOUNT			= {211,25, 7}

MD_FUBEN_BAMIYANG_DATE				= {212, 0, 9}	    --������ʯ������
MD_FUBEN_BAMIYANG_DAYCOUNT			= {212, 9, 7}

MD_GUOYUN_DATE 						= {213, 0,32 }		--�ϴ���ȡ���˲���ʱ��
MD_CHUGUO_DATE 						= {214, 0,32}		--�ϴ���ȡ��������ʱ��

--�µ������MD
MD_QUEST_DENGMI_DATE				= {215, 0, 9}		--�ϴβµ���ʱ��
MD_QUEST_DENGMI_COUNT				= {215, 9, 5}		--�µ��մ�����������31��
MD_QUEST_DENGMI_NPC					= 
									{
									   {215,14,9},		--NPC1�ĵ�ǰ��������
									   {215,23,9},		--NPC2�ĵ�ǰ��������
									   {216,0, 9},		--NPC3�ĵ�ǰ��������
									   {216,9, 9},		--NPC4�ĵ�ǰ��������
									   {216,18,9},		--NPC5�ĵ�ǰ��������
									}
									
MD_FRIEND_GUID_1 					= {217, 0,32} 		--���������Ӧ�ĺ���1
MD_FRIEND_GUID_2 					= {218, 0,32} 		--���������Ӧ�ĺ���2
MD_FRIEND_GUID_3 					= {219, 0,32} 		--���������Ӧ�ĺ���3
MD_FRIEND_GUID_4 					= {220, 0,32} 		--���������Ӧ�ĺ���4
MD_FRIEND_GUID_5 					= {221, 0,32} 		--���������Ӧ�ĺ���5

MD_FUBEN_DATI 						= {222, 0,16} 		--����������֤
MD_FUBEN_ENTERTICK 					= {222,16,16} 		--���븱����ʱ

MD_FUBEN_DATISTEP 					= {223, 0,16} 		--��������step
MD_DATI_ACTIVE_ID 					= {223,16,16}		--DATI �����GameId

MD_HEIJIN_DATI						= {224, 0,13} 		--�ڽ������֤
MD_HEIJIN_ENTERTICK 				= {224,13,13} 		--�ڽ�������ʱ
MD_HEIJIN_DATISTEP 					= {224,26, 6} 		--�ڽ����step
--�����ʵ����
MD_WULONG_DATE 						= {225, 0, 9}		--�ϴδ���ʱ��
MD_WULONG_STEP 						= {225, 9, 3}		--����ڼ��׶�
MD_WULONG_COUNT 					= {225,12, 5}		--���˶��ٸ�
MD_WULONG_RIGHT_COUNT 				= {225,17, 5}		--��Զ��ٸ�
MD_WULONG_LAST_ANSWER 				= {225,22, 5}		--�ϴδ𵽵ڼ���
MD_WULONG_ERROR_COUNT 				= {225,27, 3}		--������
MD_WULONG_TIME_BEGIN 				= {226, 0,32}		--���⿪ʼʱ��

MD_LOGIN_ANSWER_DATI 				= {227, 0,13} 		--��½������֤
MD_LOGIN_ANSWER_ENTERTICK 			= {227,13,13} 		--��½��ʱ
MD_LOGIN_ANSWER_DATISTEP 			= {227,26, 6} 		--��½����step


MD_ENCRYPT_ARITH1					= {228, 0, 8}       --��������㷨1
MD_ENCRYPT_ARITH2					= {228, 8, 8}		--��������㷨2
MD_ENCRYPT_ARITH3					= {228,16, 8}		--��������㷨3
MD_DATI_RESULT						= {228,24, 8}		--�����
--�±��ٳ�
MD_XINBINGSUCHENG_FIRST 			= {229, 0, 1}		--�Ƿ��ǵ�һ��������
MD_XINBINGSUCHENG_DATE 				= {229, 1, 9} 		--�ϴ�������ʱ��
--�����ʵ����
MD_WULONG_LAST_QUESTION 			= {229,10,16} 		--��һ������id
MD_WULONG_GUOGUANLING 				= {229,26, 1} 		--ʹ�ù��������
MD_WULONG_HEIBAILING 				= {229,27, 2} 		--ʹ�úڰ������

MD_MASTER_PRENTICE_COM_DAY 			= {230, 0, 9} 		--ʦͽ������ɵ�����
MD_MASTER_PRENTICE_COM_TIMES 		= {230, 9, 9} 		--ʦͽ������ɵĴ���

MD_SHANXIN_TIME4					= {231, 0, 9}		--�����������ϴ�ʹ��ʱ��
MD_SHANXIN_TIME5					= {231, 9, 9}		--�����������ϴ�ʹ��ʱ��
MD_SHANXIN_TIME6					= {231,18, 9}		--���İﹱ���ϴ�ʹ��ʱ��
MD_SHANXIN_TIME7					= {232, 0, 9}		--���Ĳ��ϰ��ϴ�ʹ��ʱ��

MD_WEIWANG_ITEM_WEEK				= {232,9,12}		--�������ϰ��ϴ�ʹ��ʱ��
MD_WEIWANG_ITEM_TIMES		  		= {232,21,4}		--�������ϰ�ʹ�ô���

--���ͷ����
MD_TRANS_MAP1						= {233, 0,14}
MD_TRANS_POS_X1						= {233,14, 9}
MD_TRANS_POS_Z1						= {233,23, 9}
MD_TRANS_MAP2						= {234, 0,14}
MD_TRANS_POS_X2						= {234,14, 9}
MD_TRANS_POS_Z2						= {234,23, 9}
MD_TRANS_MAP3						= {235, 0,14}
MD_TRANS_POS_X3						= {235,14, 9}
MD_TRANS_POS_Z3						= {235,23, 9}
MD_TRANS_MAP4						= {236, 0,14}
MD_TRANS_POS_X4						= {236,14, 9}
MD_TRANS_POS_Z4						= {236,23, 9}
MD_TRANS_MAP5						= {237, 0,14}
MD_TRANS_POS_X5						= {237,14, 9}
MD_TRANS_POS_Z5						= {237,23, 9}
MD_TRANS_TIME						= {238, 0,32}
--end

MD_FUBEN_ZHANSHENMU1_DATE				= {239, 0, 9}		--̽��ս��Ĺ��һ������
MD_FUBEN_ZHANSHENMU1_DAYCOUNT       	= {239, 9, 6}   	--̽��ս��Ĺ��һ���ѽӴ���
MD_FUBEN_ZHANSHENMU2_DATE				= {239,15, 9}		--̽��ս��Ĺ����������
MD_FUBEN_ZHANSHENMU2_DAYCOUNT       	= {239,24, 6}		--̽��ս��Ĺ�������ѽӴ���

MD_FUBEN_TRY_ZHUJIAZHUANG1				= {239,30, 1}		--������������ף��ׯ��һ��																				
MD_FUBEN_TRY_ZHUJIAZHUANG2				= {239,31, 1}		--������������ף��ׯ������

MD_FUBEN_ZHANSHENMU3_DATE				= {240, 0, 9}		--̽��ս��Ĺ����������	
MD_FUBEN_ZHANSHENMU3_DAYCOUNT       	= {240, 9, 6}		--̽��ս��Ĺ�������ѽӴ���
MD_FUBEN_SHENMIAO1_DATE					= {240,15, 9}		--ӡ������һ������     
MD_FUBEN_SHENMIAO1_DAYCOUNT				= {240,24, 6}       --ӡ������һ���ѽӴ���

MD_FUBEN_TRY_ZHUJIAZHUANG3				= {240,30, 1}		--������������ף��ׯ������
MD_FUBEN_TRY_ZHANSHENMU1  				= {240,31, 1}		--��������̽��ս��Ĺ��һ��																				

MD_FUBEN_SHENMIAO2_DATE					= {241, 0, 9}       --ӡ��������������           
MD_FUBEN_SHENMIAO2_DAYCOUNT				= {241, 9, 6}       --ӡ�����������ѽӴ���       
MD_FUBEN_SHENMIAO3_DATE					= {241,15, 9}       --ӡ��������������	         
MD_FUBEN_SHENMIAO3_DAYCOUNT				= {241,24, 6}       --ӡ�����������ѽӴ���    

MD_FUBEN_TRY_ZHANSHENMU2  				= {241,30, 1}		--��������̽��ս��Ĺ������																				
MD_FUBEN_TRY_ZHANSHENMU3  				= {241,31, 1}		--��������̽��ս��Ĺ������		       

MD_FUBEN_JIAOTANG1_DATE					= {242, 0, 9}		--���õ����ܣ�һ������           
MD_FUBEN_JIAOTANG1_DAYCOUNT         	= {242, 9, 6}       --���õ����ܣ�һ���ѽӴ���       
MD_FUBEN_JIAOTANG2_DATE					= {242,15, 9}       --���õ����ܣ���������
MD_FUBEN_JIAOTANG2_DAYCOUNT         	= {242,24, 6}       --���õ����ܣ������ѽӴ���

MD_FUBEN_TRY_SHENMIAO1    				= {242,30, 1}		--��������ӡ������һ��  																				
MD_FUBEN_TRY_SHENMIAO2    				= {242,31, 1}		--��������ӡ����������         

MD_FUBEN_JIAOTANG3_DATE					= {243, 0, 9}       --���õ����ܣ���������	         
MD_FUBEN_JIAOTANG3_DAYCOUNT         	= {243, 9, 6}       --���õ����ܣ������ѽӴ���   	

MD_FUBEN_TRY_SHENMIAO3					= {243,15, 1}       --��������ӡ����������  
MD_FUBEN_TRY_JIAOTANG1					= {243,16, 1}       --�����������õ����ܣ�һ��
MD_FUBEN_TRY_JIAOTANG2					= {243,17, 1}       --�����������õ����ܣ�����
MD_FUBEN_TRY_JIAOTANG3					= {243,18, 1}       --�����������õ����ܣ�����

MD_FUBEN_QIULONGDAO_TODAY          		= {243,19, 9}		--�������� ���ȣ�9
--MD_FUBEN_QIULONGDAO_TODAYCOUNT     	= {243,28, 3}      	--�������� ���ȣ�3   ���� CZG ��Ҫɾ�� 2010-9-7 15:33:13

MD_FUBEN_XIAOQIAN_DATE					= {244, 3, 9}       --ٻŮ�Ļ긱�� ���� 9λ
MD_FUBEN_XIAOQIAN_FLAG					= {244,12, 1}       --ٻŮ�Ļ긱���һ����
MD_FUBEN_HUAPI_FLAG						= {244,13, 1}       --��Ƥ�����һ����

MD_FUBEN_DAGUANYUAN_SHANGXIANG_DATE     = {245, 0, 9}     	--���԰��������
MD_FUBEN_DAGUANYUAN_SHANGXIANG_DAYCOUNT = {245, 9, 7}     	--���԰�������

MD_QUEST_MIGONGCHUE_ACCEPTDATE			= {245,16, 9}       --�����Թ��������������
MD_QUEST_MIGONGCHUE_CURRING				= {245,25, 5}      	--�Թ��ܻ���ǰ����
MD_QUEST_MIGONGCHUE_TODAYRING			= {246, 0, 5}		--����������Թ��ܻ�����

MD_FUBEN_QIULONGDAO_TODAYCOUNT     		= {249,19, 4}      	--�������� ���ȣ�4
MD_FUBEN_SANHUAN_LASTINDEX    			= {249,23, 7}   	--�ϴ���������������ֵ 7


--*******************************************************************************
--������
--*******************************************************************************
GUILD_KILLMONSTER_SCRIPT			= 300619
GUILD_GATHER_SCRIPT					= 300621
GUILD_PAOBANGGONG_SCRIPT			= 300640
GUILDBATTLE_SCRIPTID				= 300643
KINGBATTLE_FLOW_SCRIPT				= 300813
GUILD_CONTEND_SCRIPT                = 300615
MIGONGSHUANGBEI_SCRIPT				= 310001
YAOXIEDIGONG_SCRIPT					= 310033
COMMON_CHUANSONG_NORMAL				= 800019
CHUANSONG_SCENEMAP_SCRIPT			= 800021
SYSTEM_MAIL_SCRIPT					= 888887
SCENE_SCRIPT_ID						= 888888
MISSION_SCRIPT						= 888891
COUNTRY_BATTLE_LITE_SCRIPT          = 310150
PVP2V2_BATTLE_SCRIPT          		= 303001
PVP6V6_BATTLE_SCRIPT          		= 303006
ZHUQUE_BATTLE_SCRIPT				= 310113
QINGLONG_BATTLE_SCRIPT				= 310110
LAIRD_BATTLE_SCRIPT					= 300918
UTILITY_SCRIPT 						= 888894
FUBEN_COMMON_SCRIPT					= 700081
QIANGTANDENGLU_SCRIPT				= 310400
FUBEN_COMMON_SCRIPT_CALL			= 700103
MPVP2V2_SIGNUP_SCRIPT          		= 303100
MPVP2V2_BATTLE_SCRIPT          		= 303101


SCENE_LOULANWANGCHENG			    = 50		-- ¥������
SCENE_LOULANBIANJING			    = 51		-- ¥���߾�
SCENE_LAIYINWANGCHENG			    = 150		-- ��ɽ����
SCENE_LAIYINBIANJING			    = 151		-- ��ɽ�߾�
SCENE_KUNLUNWANGCHENG			    = 250		-- ��������
SCENE_KUNLUNBIANJING			    = 251		-- ���ر߾�
SCENE_DUNHUANGWANGCHENG		        = 350		-- �ػ�����
SCENE_DUNHUANGBIANJING		        = 351		-- �ػͱ߾�

--*******************************************************************************
--��������
--*******************************************************************************
FUBEN_EXAMPLE		                = 999
FUBEN_HUOCAISHENDIAN	            = 998
FUBEN_JUNYAOYAOKOU                  = 997
FUBEN_GOULANQUTAI                   = 996
FUBEN_DONGHAIHAIYAN                 = 995
FUBEN_BIWULEITAI                    = 994
FUBEN_DAWUSHI                       = 993
FUBEN_HUOQIYING                     = 992
FUBEN_JINLUANDIAN                 	= 991
FUBEN_HESHIBI                    	= 990
FUBEN_GOULANQUTAI                   = 989
FUBEN_SHIZIJING                     = 987
FUBEN_FUTUTA6                       = 986
FUBEN_HUANGJINKUANGDONG             = 985
FUBEN_DIJIAO			            = 984
FUBEN_GUMU				            = 983
FUBEN_FUTUTA4			            = 982
FUBEN_LANLONGCHENGBAO	            = 981
FUBEN_HUDI				            = 980
FUBEN_SHANGGUMIDAO		            = 979
FUBEN_YONGYISENGLIN		            = 978
FUBEN_QIULONGDAO		            = 977
FUBEN_ZHULUOJI			            = 976
FUBEN_TIANJINGKENG		            = 975
FUBEN_HUOSHANMUDI		            = 974
FUBEN_FOSHOU			            = 973
FUBEN_BAMIYANG			            = 972
FUBEN_PVP_2V2						= 971
FUBEN_ZHUJIAZHUANG1					= 970	
FUBEN_ZHUJIAZHUANG2					= 969
FUBEN_ZHUJIAZHUANG3					= 968
FUBEN_TANSUO_ZHANSHENMU_1			= 967--�����顿̽��ս��Ĺ��һ��
FUBEN_TANSUO_ZHANSHENMU_2			= 966--�����顿̽��ս��Ĺ������
FUBEN_TANSUO_ZHANSHENMU_3			= 965--�����顿̽��ս��Ĺ������
FUBEN_YINDUSHENMIAO1				= 964--�����顿ӡ������һ��
FUBEN_YINDUSHENMIAO2				= 963--�����顿ӡ����������
FUBEN_YINDUSHENMIAO3				= 962--�����顿ӡ����������
FUBEN_JIAOTANGMIMI1					= 961--�����顿���õ����ܣ�һ��
FUBEN_JIAOTANGMIMI2					= 960--�����顿���õ����ܣ�����
FUBEN_JIAOTANGMIMI3					= 959--�����顿���õ����ܣ�����
FUBEN_XIANJINJINKUANGDONG			= 958--�����顿�������
FUBEN_QIANFOKU1               		= 957--�����顿ǧ���1
FUBEN_QIANFOKU2               		= 956--�����顿ǧ���2
FUBEN_QIANFOKU3               		= 955--�����顿ǧ���3
FUBEN_QIANFOKU4               		= 954--�����顿ǧ���4
FUBEN_QIANFOKU5               		= 953--�����顿ǧ���5
FUBEN_QIANFOKU6               		= 952--�����顿ǧ���6
FUBEN_TIANFU		                = 951--�츳����_���� 
FUBEN_HUAPI							= 950--��Ƥ
FUBEN_QIANNVYOUHUN					= 949--ٻŮ�Ļ�

--*******************************************************************************
--ս������
--*******************************************************************************
BATTLESCENE_TYPE_GUILDBATTLE		= 0			--���ս
BATTLESCENE_TYPE_KINGBATTLE			= 1			--��������ս
BATTLESCENE_TYPE_WORLDCUPBATTLE		= 2			--���籭
BATTLESCENE_TYPE_COUNTRYBATTLELITE	= 3			--����ս
BATTLESCENE_TYPE_ZHUQUEBATTLELITE	= 4			--��ȸ�ػ�
BATTLESCENE_TYPE_QINGLONGBATTLELITE	= 5			--�����ػ�
BATTLESCENE_TYPE_LAIRDGBATTLELITE	= 6			--�ݵ�����


--*******************************************************************************
--����ű�
--*******************************************************************************
MISSION_TYPE_KILLMONSTER		    = 1 		--���
MISSION_TYPE_DELIVERY			    = 2 		--����
MISSION_TYPE_HUSONG				    = 3 		--����
MISSION_TYPE_ENTERAREA			    = 4 		--����̽��
MISSION_TYPE_LOOKITEM			    = 5 		--�ռ���Ʒ
MISSION_TYPE_USEITEM		  	    = 6 		--ʹ����Ʒ

--*******************************************************************************
--����PKģʽ
--*******************************************************************************
PK_MODE_GUOJIA		                = 0			--����
PK_MODE_SHANE				        = 1			--�ƶ�
PK_MODE_BANGHUI		                = 2			--���
PK_MODE_JIAZU				        = 3			--����
PK_MODE_DUIWU				        = 4			--����
PK_MODE_HUNZHAN		                = 5			--��ս

--*******************************************************************************
--�����������ʱ�����������ͣ�����ֵ���������Ķ�
--*******************************************************************************
RD_HUMAN_MENTALGAME		            = 0	        --����
RD_HUMAN_NAME_COLOR		            = 1	        --������ֵ���ɫ

RD_HUMAN_AWARE_INDEX1			    = 2			--��Ʒ��trophy.tab���е�����
RD_HUMAN_AWARE_INDEX2			    = 3			
RD_HUMAN_AWARE_INDEX3			    = 4
RD_HUMAN_AWARE_INDEX4			    = 5
RD_HUMAN_AWARE_INDEX5			    = 6

RD_HUMAN_AWARE_DB_INDEX1		    = 7			--��Ʒ��DB�е�����
RD_HUMAN_AWARE_DB_INDEX2		    = 8			
RD_HUMAN_AWARE_DB_INDEX3		    = 9
RD_HUMAN_AWARE_DB_INDEX4		    = 10
RD_HUMAN_AWARE_DB_INDEX5		    = 11
RD_HUMAN_CURR_AWARD_NPCID		    = 12		--��ǰ�콱NPC
RD_HUMAN_CURR_AWARD_INDEX		    = 13		--��ǰ�콱����Ʒ����

RD_GUILDBATTLE_BEKILLED             = 14        --�������ս����ɱ����
RD_GUILDBATTLE_KILLEDOTHER          = 15        --�������ս��ɱ�˴���
RD_GUILDBATTLE_GETFLAG              = 16        --�������ս���������

RD_KING_BATTLE_BEKILLED             = 17        --��������ս����ɱ����

RD_HUMAN_AWARE_NUM1				    = 18		--ÿ�ֽ����ĸ���		
RD_HUMAN_AWARE_NUM2				    = 19			
RD_HUMAN_AWARE_NUM3				    = 20
RD_HUMAN_AWARE_NUM4				    = 21
RD_HUMAN_AWARE_NUM5				    = 22

RD_GUJI_SCENEID                     = 23        --�ż�̽�������Ŀ�곡��Id
RD_GUJI_ITEMID                      = 24        --�ż�̽�������������ƷId

RD_COLLECT_HORSE				    = 25		--�ռ�ս������ID

RD_TONGQU_CD					    = 26		--ͯȤ��cdʱ��
RD_CANGKU_EXT				        = 27		--�ֿ���ҵ����¼

RD_BATTLE_SCENE_KICK_DOWN           = 28

RD_HUMAN_SCENE_PRE                  = 29        --��¼��һ������
RD_HUMAN_POSX_PRE                   = 30        --��¼��һ������λ��X
RD_HUMAN_POSZ_PRE                   = 31        --��¼��һ������λ��Z

RD_COLLECT_HORSE_HIGH			    = 32		--�ռ�ս��ID��λ
RD_COLLECT_HORSE_LOW			    = 33		--�ռ�ս��ID��λ

RD_BATTLESCENE_ENTER_FLAG           = 34        --ս�������־
RD_GUILDCONTEND_KILL_LEADER         = 28        --���������ɱ��������
RD_GUILDCONTEND_KILL_ASSIST         = 29        --���������ɱ����������
RD_GUILDCONTEND_KILL_FAMILY         = 30        --���������ɱ���峤����
RD_GUILDCONTEND_KILL_GOLD           = 31        --���������ɱ�ƽ�������
RD_GUILDCONTEND_KILL_OTHER          = 32        --���������ɱ��ͨ���ڼ���
RD_GUILDCONTEND_DIECOUNT            = 33        --�����������ɱ����
RD_GUILDCONTEND_SCORE               = 34        --������������˻���

RD_DANCERY_BODYID                   = 35        --��������ID�������ϣ�����MD_WUTING_CHANGEID

RD_EVENT_REQUEST_NPCID				= 36		--NPCID ��ռλ�ýű��в����õ�
RD_EVENT_REQUEST_MISSION_SCRIPT_ID	= 37		--�����ű�ID ��ռλ�ýű��в����õ�

RD_COUNTRYBATTLELITE_KINGISSUE_NPC	= 38		--С��ս����NPCID

RD_QUEST_DENGMI_NPC_FLAG			= 39		--���մ����ǣ�NPC
RD_QUEST_DENGMI_CUR_DENGMI			= 40		--���մ����ǣ���ǰ��Ŀ���

RD_CURR_ENCRYPT_INDEX				= 41		--��ǰ�����㷨������
RD_LAST_ENCRYPT_INDEX				= 42		--�ϴμ����㷨������
RD_CURR_ENCRYPT_COUNT				= 43		--���ܼ���
RD_ENCRYPT_UNRESPOND_TIME			= 44		--����δ��Ӧ��ʱ

RD_QUEST_WULONG_CUR_ANSWER			= 45		--�����ʵ䵱ǰ�Ĵ�
RD_VIP_BOX                          = 46        --VIP���κ�ѡ��id

RD_PVP6V6_RELIVE_DOWNCOUNT			= 47		--PVP6V6��������ʱ
RD_PVP6V6_BATTLE_MONEY				= 48		--PVP6V6ս������

RD_STOCK_TRANS_MONEY_TIME			= 49		--��Ʊϵͳ��ֵ��ת����ȴʱ��
RD_STOCK_BUY_TIME					= 50		--��Ʊϵͳ������ȴʱ��
RD_STOCK_SALE_TIME					= 51		--��Ʊϵͳ������ȴʱ��
RD_STOCK_REPEAL_TIME				= 52		--��Ʊϵͳ������ȴʱ��
RD_STOCK_ASK_WORLD_LIST_TIME		= 53		--��Ʊϵͳ������̵���ȴʱ��
RD_STOCK_ASK_RECORD_TIME			= 54		--��Ʊϵͳ������ʷ��¼��ȴʱ��
RD_STOCK_AASK_MARKET_LIST_TIME		= 55		--��Ʊϵͳ�����ϼ��б����ȴʱ��
RD_TRANS_ITEM_TIME					= 56		--���ͷ�ʹ�õ�ʱ��

RD_COUNTRYBATTLELITE_ADDQUESTFLAG	= 57		--���������
RD_COMMON_NPCID						= 58		--ͨ��NPCID����
RD_ROOKIE_BOX						= 60		--���ֿ�
RD_HUANGJINKUANGDONG_OPT			= 61		--�ر����һ�����
RD_FUBENPARAM_MODE					= 62		--����ģʽ
--RD_COMMON_LOULAN_YUNBIAO    = 63		--¥�����ڵĶԻ���ı��  û��RD��Դ��,����	[	RD_GUILDCONTEND_KILL_LEADER        	= 28 ]
--RD_COMMON_TIANSHAN_YUNBIAO  = 64		--��ɽ���ڵĶԻ���ı��  û��RD��Դ��,����	[	RD_GUILDCONTEND_KILL_ASSIST         = 29 ]
--RD_COMMON_KUNLUN_YUNBIAO    = 65		--�������ڵĶԻ���ı��  û��RD��Դ��,����	[	RD_GUILDCONTEND_KILL_FAMILY         = 30 ]
--RD_COMMON_DUNHUANG_YUNBIAO  = 66		--�ػ����ڵĶԻ���ı��  û��RD��Դ��,����	[	RD_GUILDCONTEND_KILL_GOLD           = 31 ]
--$$$$$$$$$$$$$$
--RD��Դ�Ѿ�û����,�����ؼӴ���Դ  Add By chenzhiguo 2010-6-11 21:31:59
--$$$$$$$$$$$$$$

--*******************************************************************************
--����������������
--*******************************************************************************
CD_INDEX_DESTROY_ISSUE_TIME         		= 0       	--�й��ƻ��ϴ����˵�ʱ��
CD_INDEX_DESTROY_ISSUE_COUNT        		= 1      	--�й��ƻ����˴���
CD_INDEX_DESTROY_ISSUE_SCENE	    		= 2			--�����������ڳ���	
CD_INDEX_MISSION_CAOBAOTU           		= 4         --�ر�ͼ��Ϣ
CD_INDEX_GUOYUN_COUNT			    		= 5			--�����ڼ���ɾ��鳵����
CD_INDEX_CHUGUO_COUNT			    		= 6			--�����ڼ���ɳ�������ļ���


CD_INDEX_COUNTRYBATTLELITE_DATE     		= 7         --С��ս����
CD_INDEX_COUNTRYBATTLELITE_CAMP     		= 8         --С��ս��Ӫ
CD_INDEX_COUNTRYBATTLELITE_KILLCOUNT		= 9         --С��ս�󽫾���¼
CD_INDEX_COUNTRYBATTLELITE_KINGISUSE		= 10		--С��ս���˴���
CD_INDEX_COUNTRYBATTLELITE_MATCH_COUNTRY	= 11		--С��ս��Թ���
CD_INDEX_COUNTRYBATTLELITE_FINISHED			= 12		--С��ս�������
CD_INDEX_COUNTRYBATTLELITE_KINGISUE_NPC		= 13		--С��ս�������

CD_INDEX_POLUOZHOU_RANDOM_DAY               = 14        -- ��������������˫������������ڣ�ÿ��һ�죩

CD_INDEX_GUOYUN_DAY							= 15		--���������ʱ��
CD_INDEX_CHUGUO_DAY							= 16		--���������ʱ��

CD_INDEX_GUILDCONTEND_TURNNUMBER    		= 20        -- ���������ȫ���ִκţ�¥�����浱ǰȫ���ִκţ���ɽ���汣�汾�±�����ʼʱ���ִκţ����ر������±�����ʼʱ���ִκ�

CD_INDEX_GUOYUN_KING 						= 21
CD_INDEX_GUOYUN_QUEEN 						= 22
CD_INDEX_GUOYUN_GENERAL 					= 23
CD_INDEX_GUOYUN_RMINISTER 					= 24
CD_INDEX_GUOYUN_LMINISTER 					= 25
CD_INDEX_GUOYUN_RGUARD						= 26
CD_INDEX_GUOYUN_LGUARD						= 27

CD_INDEX_CHUGUO_KING 						= 28
CD_INDEX_CHUGUO_QUEEN 						= 29
CD_INDEX_CHUGUO_GENERAL 					= 30
CD_INDEX_CHUGUO_RMINISTER 					= 31
CD_INDEX_CHUGUO_LMINISTER 					= 32
CD_INDEX_CHUGUO_RGUARD 						= 33
CD_INDEX_CHUGUO_LGUARD 						= 34

CD_INDEX_STRENGTH							= 35		--����ʵ��
CD_INDEX_STRENGTH_Y							= 36		--���չ���ʵ��
CD_INDEX_STRENGTH_DAY						= 37		--����ʵ����¼ʱ��

CD_INDEX_CHINAJOY_TIMES						= 38		--ChinaJoy ����
CD_INDEX_CHINAJOY_DATE						= 39		--ChinaJoy ����

CD_INDEX_RUOGUO_SHOUJI_DATE					= 40		--���������ϴ��ռ�����
CD_INDEX_RUOGUO_SHOUJI_FLAG					= 41		--���������ռ�Index

CD_INDEX_MOJUN_KILL_COUNT1					= 42		--ʮ��ħ����ɱ����
CD_INDEX_MOJUN_KILL_COUNT2					= 43
CD_INDEX_MOJUN_KILL_COUNT3					= 44
CD_INDEX_MOJUN_KILL_COUNT4					= 45


CD_INDEX_RUOGUO_START_FLAG					= 46		--���������Ƿ���
CD_INDEX_MOJUN_KILL_COUNT					= 47  		--����ʮ��ħ����ɱ�ļ��� 

CD_INDEX_STRENGTH_WEEKTOTAL					= 48
CD_INDEX_STRENGTH_WEEKTOTAL_Y				= 49
CD_INDEX_STRENGTH_WEEKTOTAL_DAY				= 50

CD_INDEX_MINSTER_KILLDATE					= 51		--���Ҵ󳼴�ɱ
CD_INDEX_CREATEKING_DATE					= 52		--������������

CD_INDEX_CREATE_QINGLONG_DATE				= 53		--������������
CD_INDEX_CREATE_ZHUQUE_DATE					= 54		--��ȸ��������

CD_INDEX_BE_DELATED_KING_GUID				= 55		--����������GUID
CD_PIONEER_FUNS                             = 56        -- ��˿�ȷ��Ż
CD_INDEX_KING_DEMISE_COUNT					= 57
CD_INDEX_QINGLONG_DEMISE_DATE				= 58
CD_INDEX_QINGLONG_DEMISE_COUNT				= 59
CD_INDEX_ZHUQUE_DEMISE_DATE					= 60
CD_INDEX_ZHUQUE_DEMISE_COUNT				= 61

CD_INDEX_ZHAOJILIN_DATE						= 62
CD_INDEX_ZHAOJILIN_DAYCOUNT					= 63
CD_INDEX_ZHAOJILIN_TIME						= 64

CD_ZHAOJILIN_SCENE							= 65
CD_ZHAOJILIN_POS_X							= 66
CD_ZHAOJILIN_POS_Z							= 67

CD_PRECONTRACT_GUOYUN                       = 68        -- ����ԤԼ
CD_PRECONTRACT_CHUGUO                       = 69        -- ����ԤԼ
CD_PRECONTRACT_MUJI                         = 70        -- ����ļ��ԤԼ

CD_RICHANG_QUESTID                          = 71        -- �ճ��淨ID

CD_YOULECHANG_CAIPIAO1						= 72        -- �޵�������
CD_YOULECHANG_CAIPIAO2						= 73        -- �޵�������

CD_DAGUANYUAN_CAIPIAO1                      = 74        -- ���԰˫�Ǳ�ϲ
CD_DAGUANYUAN_CAIPIAO2                      = 75        -- ���԰˫�Ǳ�ϲ
CD_INDEX_KING_DEMISE_DATE					= 76

CD_LASTWEEK_PINGFEN_DATE					= 77 		-- �������ܵĽ�Ǯ���Ѽ�¼ʱ��
CD_LASTWEEK_PINGFEN_MONEY					= 78 		-- �������ܵĽ�Ǯ���ѵ�����
CD_CURWEEK_PINGFEN_DATE						= 79 		-- ���ұ��ܵĽ�Ǯ���Ѽ�¼ʱ��
CD_CURWEEK_PINGFEN_MONEY					= 80 		-- ���ұ��ܵĽ�Ǯ���Ѽ�¼ʱ��

CD_LASTWEEK_STRONG_WEAK_JIFEN				= 81		--��������ǿ������
CD_LASTWEEK_STRONG_WEAK_JIFEN_DATE			= 82		--��������ǿ������ʱ��
CD_CURWEEK_STRONG_WEAK_JIFEN				= 83		--���ұ���ǿ������
CD_CURWEEK_STRONG_WEAK_JIFEN_DATE			= 84		--���ұ���ǿ������ʱ��
CD_STRONG_WEAK_LEVEL						= 85		--����ǿ���ȼ�

CD_STRONG_WEAK_GUILD_JIFEN					= 86		--�������Ĺ���ǿ������,��һˢ�µ�����ǿ������֣�Ȼ������
CD_STRONG_WEAK_GUILD_JIFEN_DATE			   	= 87		--�������Ĺ���ǿ�����ֵ�ʱ��,��һ����


--*******************************************************************************
--������������������ο�GameDefine_Guild.h��
--*******************************************************************************
GD_GUILD_INDEX_YUNBIAO_SSUE_TIME    		= 0         --������ڷ���ʱ��
GD_GUILD_INDEX_YUNBIAO_STATE        		= 1     	--�������״̬
GD_GUILD_INDEX_YUNBIAO_ACCEPT_TIME  		= 2  	    --������ڽ���ʱ��
GD_GUILD_INDEX_KILL_ISSUE_TIME      		= 3         --���ɱ�ֵķ���ʱ��
GD_GUILD_INDEX_GATHER_ISSUE_TIME    		= 4         --���ɼ��ķ���ʱ��
GD_GUILD_INDEX_BATTLE_SINGUP 				= 5		    --���ս�������ݣ�����ǰ����
GD_GUILD_INDEX_BATTL_STATE					= 6         --���ս״̬ 0���ѽ�����1�������� ,-1δ��ʼ
GD_GUILD_INDEX_BATTL_WIN_NUM        		= 7         --���ս��ʤ����
GD_GUILD_INDEX_BATTL_LOSE_NUM       		= 8         --���սʧ�ܳ���
GD_GUILD_INDEX_BATTL_DEUCE_NUM      		= 9         --���սƽ�ֳ���
GD_GUILD_INDEX_BATTL_SINGUP_RESULT			= 10	    --���ս�����Ƿ�ɹ� ������������
GD_GUILD_INDEX_SHOPACTIVE_PARAM0			= 11
GD_GUILD_INDEX_SHOPACTIVE_PARAM1			= 12
GD_GUILD_INDEX_SHOPACTIVE_PARAM2			= 13
GD_GUILD_INDEX_SHOPACTIVE_PARAM3			= 14
GD_GUILD_INDEX_CONTEND_TURN_NUMBER  		= 15        --����������ִ�����
GD_GUILD_INDEX_WORLDCUP_FLAG				= 16
GD_GUILD_INDEX_LAST_RESULT					= 17
GD_GUILD_INDEX_LAST_GB_SCORE				= 18
GD_GUILD_INDEX_ADDEXP_DATE					= 19        --��Ὠ�裨ѭ�����ϴ����Ӱ�ᾭ������
GD_GUILD_INDEX_ADDEXP_VALUE					= 20        --��Ὠ�裨ѭ�����������Ӱ�ᾭ�����
GD_GUILD_INDEX_CONTEND_STATE        		= 21        --���������״̬

GD_GUILD_INDEX_CONVOKE_COUNT				= 22		--����ټ�����
GD_GUILD_INDEX_CONVOKE_DAY					= 23		--����ټ�ʱ��

GD_GUILD_INDEX_CONTEND_WIN_COUNT    		= 24        --���������ȡʤ����
GD_GUILD_INDEX_CONTEND_LOSE_COUNT   		= 25        --���������ʧ������

GD_GUILD_INDEX_MINISTER_GUILD_DATE			= 26		--���Ҵ�ս��̨�İ��
GD_GUILD_INDEX_VIP_COLLECT_COUNT			= 27		--���VIPļ����������Ҫÿ������
GD_GUILD_INDEX_GET_MONEY_COUNT				= 28		--�����Ǯ(�淨)��������Ҫÿ������
GD_GUILD_INDEX_MULTI_MISSION_HUSHOU			= 29		--���౶����(����)����ÿ������
GD_GUILD_INDEX_MULTI_MISSION_HEIMU			= 30		--���౶����(��ľ)����ÿ������
GD_GUILD_INDEX_MULTI_MISSION_ANZHAN			= 31		--���౶����(��ս)����ÿ������
GD_GUILD_INDEX_MULTI_MISSION_CHUYAO			= 32		--���౶����(����)����ÿ������
GD_GUILD_INDEX_MULTI_MISSION_MUJI			= 33		--���౶����(ļ��)����ÿ������
GD_GUILD_INDEX_MULTI_MISSION_TODAY			= 34		--���շ����İ��౶������ÿ������
GD_GUILD_INDEX_CHIEF_MULTIMISSION_DAY		= 35		--������ȡ�౶����������
GD_GUILD_INDEX_ASSCHIEF_MULTIMISSION_DAY	= 36		--��������ȡ�౶����������
GD_GUILD_WORLDCUP_TITLE_TIME                = 37        --���籭ͷ���ƺű���ʱ��
GD_GUILD_LAIRDBATTLE_SCENEID				= 38		--�ݵ��ػ�ռ��ĳ���
GD_GUILD_INDEX_YUNBIAO_RING_MIS_TIME  		= 39  	    --������ڻ��������ʱ��
GD_GUILD_LAIRDBATTLE_DATE					= 40		--�ݵ��ػ�ռ���ʱ��

GD_GUILD_ACTIVITY_PARAM1					= 41		--����Ծ�Ȳ���1
GD_GUILD_ACTIVITY_PARAM2					= 42		--����Ծ�Ȳ���2
GD_GUILD_ACTIVITY_PARAM3					= 43		--����Ծ�Ȳ���3
GD_GUILD_ACTIVITY_PARAM4					= 44		--����Ծ�Ȳ���4
GD_GUILD_ACTIVITY_PARAM5					= 45		--����Ծ�Ȳ���5
GD_GUILD_ACTIVITY_PARAM6					= 46		--����Ծ�Ȳ���6
GD_GUILD_ACTIVITY_PARAM7					= 47		--����Ծ�Ȳ���7
GD_GUILD_ACTIVITY_PARAM8					= 48		--����Ծ�Ȳ���8

GD_GUILD_LAIRDBATTLE_REDEEM_DATE			= 49		--�ݵ��ػ���ȡ��ؽ�Ǯʱ��
GD_GUILD_LAIRDBATTLE_LEVEL					= 50		--�ݵ��ػ����ɵȼ�

GD_GUILD_HANDIN_DATE                        = 51        --����������
GD_GUILD_HANDIN_MONEY                       = 52        --���ÿ�վ�����

GD_GUILD_LAIRDBATTLE_CURRENT_EXP			= 53		--�ݵ��ᵱǰ����

GD_GUILD_LASTMONTH_GUILD_MEMBER_MONEY	= 54			--���������������Ա���µ����ѽ��
GD_GUILD_CURMONTH_GUILD_MEMBER_MONEY	= 55			--���������������Ա���µ����ѽ��
GD_GUILD_LASTMONTH						= 56
GD_GUILD_CURMONTH						= 57

--*******************************************************************************
--���౶������ֵ
--*******************************************************************************
GUILD_MULTI_MISSION_HUSHOU 					= 0			-- ����
GUILD_MULTI_MISSION_HEIMU					= 1			-- ��ľ
GUILD_MULTI_MISSION_ANZHAN					= 2			-- ��ս
GUILD_MULTI_MISSION_CHUYAO					= 3			-- ����
GUILD_MULTI_MISSION_MUJI					= 4			-- ļ��

--*******************************************************************************
--��ִ���ʼ� param0 �Ŀ���ֵ
--*******************************************************************************
MAIL_REPUDIATE				        		= 1			--ǿ�����
MAIL_BETRAYMASTER			        		= 2			--��ʦ
MAIL_EXPELPRENTICE			        		= 3			--����ͽ��
MAIL_UPDATE_ATTR			        		= 4			--����ˢ��
MAIL_UNSWEAR				        		= 5			--������
MAIL_PRENTICE_EXP			        		= 6			--ͽ�ܸ�ʦ������
MAIL_LEAVE_GUILD			        		= 7			--�뿪��ᣨ�����Ǳ��߻��ɢ��
MAIL_GIVE_MONEY				        		= 8			--��Ǯ
MAIL_GIVE_ITEM				        		= 9			--����Ʒ
MAIL_DELETE_MISSION		            		= 10		--ɾ������
MAIL_GIVE_MONEY2MASTER	            		= 11		--��ʦ��Ǯ
MAIL_GIVE_EXP				        		= 12		--������
MAIL_MASTER_AWARD							= 13		--ͽ��������ʦ���Ľ���



--*******************************************************************************
--���ս���е���������,LD��ʾֻ�洢�ڳ�����������һ��LOCAL����
--ǰ32λΪͨ�����ݣ���32λΪ��ͬ�淨���е�����
--�������ݱ����ڳ�����
--*******************************************************************************
--��ս״̬
STATE_GUILD_BATTLE_READY            		= 0		    --ս������׼������
STATE_GUILD_BATTLE_SIGNUP           		= 1		    --��ʼ����
STATE_GUILD_BATTLE_SIGNUP_FINISH    		= 2	        --��������
STATE_GUILD_BATTLE_BATTLE           		= 3		    --��ʼս��
STATE_GUILD_BATTLE_BATTLE_FINISH    		= 4	        --ս������

--*******************************************************************************
--���սͨ������
--*******************************************************************************
LD_GUILD_BATTLE_TYPE			    		= 0  		--���ս�淨����
LD_GUILD_BATTLE_SCRIPT			    		= 1  		--�����ű�ID
LD_GUILD_BATTLE_A_SOCRE 		    		= 2			--A������
LD_GUILD_BATTLE_B_SOCRE 		    		= 3			--B������
LD_GUILD_BATTLE_LAST_TICK		    		= 4  		--��һ������ʱ��
LD_GUILD_BATTLE_A_GUILD			    		= 5  		--A�����ID
LD_GUILD_BATTLE_B_GUILD			    		= 6  		--B�����ID
LD_GUILD_BATTLE_COUNT_DOWN_STATE    		= 7  		--�������ĵ���ʱ�˳�״̬
LD_GUILD_BATTLE_COUNT_DOWN_TIME     		= 8 		--����ʱ(��λ��)
LD_GUILD_BATTLE_COUNT_ITME          		= 9         --ս���ѹ���ʱ��
LD_GUILD_BATTLE_REFRESH_MAP         		= 10        --ս���ѹ���ʱ��
LD_GUILD_BATTLE_BARN1_GUILD		    		= 11 		--�����������ID
LD_GUILD_BATTLE_BARN2_GUILD		    		= 12 		--�����������ID
LD_GUILD_BATTLE_BARN3_GUILD		    		= 13 		--�����������ID
LD_GUILD_BATTLE_BARN4_GUILD		    		= 14 		--�����������ID
LD_GUILD_BATTLE_A_FLAG_NUM		    		= 15		--A���������
LD_GUILD_BATTLE_B_FLAG_NUM		    		= 16		--B���������
LD_GUILD_BATTLE_BARN1_TIME		    		= 17 		--���ֱ�ռ��ʱ��
LD_GUILD_BATTLE_BARN2_TIME		    		= 18 		--���ֱ�ռ��ʱ��
LD_GUILD_BATTLE_BARN3_TIME		    		= 19 		--���ֱ�ռ��ʱ��
LD_GUILD_BATTLE_BARN4_TIME		    		= 20 		--���ֱ�ռ��ʱ��
LD_GUILD_BATTLE_FLAG_TIME           		= 21        --���Ӷ��ߺ�ļ�ʱ
LD_GUILD_BATTLE_FLAG_OWNER          		= 22        --���ӵ�ǰ������
LD_GUILD_BATTLE_FLAG_NOW_X          		= 23        --���ӵ�ǰ����X
LD_GUILD_BATTLE_FLAG_NOW_Y          		= 24        --���ӵ�ǰ����Y
LD_GUILD_BATTLE_FLAG_A_ID					= 25		--���ս��ս��A��Ϣ
LD_GUILD_BATTLE_FLAG_B_ID					= 26		--���ս��ս��B��Ϣ

--����淨1��ȫ�ֱ���
LD_GUILD_BATTLE_DEC_SPEED_BUF 	    		= 7700      --���ٺ�����BUS
LD_GUILD_BATTLE_INC_DEFENCE_BUF     		= 7701      --�ӷ���BUF
--LD_GUILD_BATTLE_FLAG_BUF 		    		= 1210      --����BUF
LD_GUILD_BATTLE_FLAG_COUNT          		= 9         --����淨1������������0��ʼ���� 
LD_GUILD_BATTLE_FLAG_GROW_POINT     		= 111 	    --����������ID
LD_GUILD_BATTLE_FLAG_X              		= 128       --����ԭʼ����X
LD_GUILD_BATTLE_FLAG_Y              		= 128       --����ԭʼ����Y

--*******************************************************************************
--���籭״̬
--*******************************************************************************
STATE_GUILD_WORLDCUP_SIGNUP         		= 10    	--��ʼ����
STATE_GUILD_WORLDCUP_SIGNUPEND      		= 11    	--��������
STATE_GUILD_WORLDCUP_PREPARE				= 12		--׼��״̬
STATE_GUILD_WORLDCUP_START					= 13		--������ʼ
STATE_GUILD_WORLDCUP_END					= 14		--��������
STATE_GUILD_WORLDCUP_FINISHED				= 15		--���±�������
STATE_GUILD_WORLDCUP_DISABLESIGNUP  		= 16    	--��ֹ�����׶�

--*******************************************************************************
--���籭����
--*******************************************************************************
LD_GUILD_WORLDCUP_GROUPTYPE         		= 0         --������籭�����Ϣ
LD_GUILD_WORLDCUP_A_GUILD           		= 1         --���A
LD_GUILD_WORLDCUP_B_GUILD           		= 2         --���B
LD_GUILD_WORLDCUP_FLAG              		= 3         -- 
LD_GUILD_WORLDCUP_A_SOCRE           		= 4         --���籭ս�����A�÷�
LD_GUILD_WORLDCUP_B_SOCRE           		= 5         --���籭ս�����B�÷�
LD_GUILD_WORLDCUP_COUNT_ITME        		= 6         -- 
LD_GUILD_CONTEND_TURNNUMBER         		= 7         --������籭�ִκ�
LD_GUILD_WORLDCUP_FLAGOCCUPY                = 8         --ս�����ı�ռ��ʱ��
LD_GUILD_WORLDCUP_STATE                     = 9         --����״̬
LD_GUILD_WORLDCUP_VERSUS1                   = 10        --����1
LD_GUILD_WORLDCUP_VERSUS2                   = 11        --����2
LD_GUILD_WORLDCUP_VERSUS3                   = 12        --����3
LD_GUILD_WORLDCUP_VERSUS4                   = 13        --����4
LD_GUILD_WORLDCUP_VERSUS5                   = 14        --����5
LD_GUILD_WORLDCUP_VERSUS6                   = 15        --����6
LD_GUILD_WORLDCUP_VERSUS7                   = 16        --����7
LD_GUILD_WORLDCUP_VERSUS8                   = 17        --����8
LD_GUILD_WORLDCUP_A_GB_SCORE                = 18        --���A��ս����
LD_GUILD_WORLDCUP_B_GB_SCORE                = 19        --���B��ս����
LD_GUILD_WORLDCUP_SWITCH                    = 20        --������籭������Ϣ
LD_GUILD_WORLDCUP_A_COUNT                   = 21        --������籭ս����A�������
LD_GUILD_WORLDCUP_B_COUNT                   = 22        --������籭ս����B�������
LD_GUILD_WORLDCUP_CATCHFLAG_A               = 23        --���籭ս��A��ȡ��Obj
LD_GUILD_WORLDCUP_CATCHFLAG_B               = 24        --���籭ս��B��ȡ��Obj

--*******************************************************************************
--��������ս���
--*******************************************************************************
--��������ս״̬
STATE_KING_BATTLE_READY             		= 0		    --ս������׼������
STATE_KING_BATTLE_SIGNUP            		= 1		    --��ʼ����
STATE_KING_BATTLE_SIGNUP_FINISH     		= 2	        --��������
STATE_KING_BATTLE_BATTLE            		= 3		    --��ʼս��
STATE_KING_BATTLE_BATTLE_FINISH     		= 4	        --ս������

LD_KING_BATTLE_TYPE			        		= 0  		--���ս�淨����
LD_KING_BATTLE_SCRIPT			    		= 1  	    --�����ű�ID
LD_KING_BATTLE_LAST_TICK		    		= 2  		--��һ������ʱ��
LD_KING_BATTLE_A_GUILD			    		= 3  		--A�����ID
LD_KING_BATTLE_B_GUILD			    		= 4  		--B�����ID
LD_KING_BATTLE_COUNTRYID            		= 5         --����
LD_KING_BATTLE_COUNT_DOWN_STATE     		= 6  		--�������ĵ���ʱ�˳�״̬
LD_KING_BATTLE_COUNT_DOWN_TIME      		= 7 		--����ʱ(��λ��)
LD_KING_BATTLE_COUNT_ITME           		= 8         --ս���ѹ���ʱ��

--*******************************************************************************
--���ս�����
--*******************************************************************************
MBATTLE_SIGNUP_SIGNTIME						= 1023		--����ǩ֤ʱ��

--*******************************************************************************
--��Ϻ���IsPlayerMutexStateʹ�ã�IsPlayerStateNormal�ж�����Ƿ���������Ϸ״̬��
--SetPlayerMutexState���������״̬
--*******************************************************************************
PLAYER_STATE_STALL                  		= 0         --��̯
PLAYER_STATE_FUBEN              			= 1         --����
PLAYER_STATE_GUILDBATTLEFIELDSCENE  		= 2         --ս��
PLAYER_STATE_ARENASSCENE            		= 3         --��̨
PLAYER_STATE_CITSCENE               		= 4         --����
PLAYER_STATE_PRISONSCENE            		= 5         --����
PLAYER_STATE_DIE                    		= 6         --����
PLAYER_STATE_BUS                    		= 7         --BUS
PLAYER_STATE_CRASHBOX               		= 8         --����
PLAYER_STATE_EXCHANGE               		= 9         --����
PLAYER_STATE_MENTALGAME             		= 10        --����
PLAYER_STATE_TEAMFOLLOW             		= 11        --��Ӹ���
PLAYER_STATE_AUTOPLAY               		= 12        --�һ�
PLAYER_STATE_SUBTRAIN               		= 13        --����
PLAYER_STATE_PRISON                 		= 14        --����
PLAYER_STATE_OPENBOX                		= 15        --����
PLAYER_STATE_PROTECTTIME            		= 16        --����ʱ��
PLAYER_STATE_KEYBORDMOVE            		= 17        --�����ƶ�
PLAYER_STATE_TIESAN                 		= 18        --��������
PLAYER_STATE_READYFUBEN         			= 19        --���븱��״̬
PLAYER_STATE_DUOQIBUFF						= 20		--����������buffʱ��״̬
PLAYER_STATE_TONGQUBUFF						= 21		--ͯȤ������buffʱ��״̬
PLAYER_STATE_PKMODE							= 22		--����PKģʽ״̬
PLAYER_STATE_FORBID_RIDE					= 23		--��ֹ����״̬
PLAYER_STATE_WEDDING						= 24		--����״̬
PLAYER_STATE_ENJAIL							= 25		--����״̬
PLAYER_STATE_Award							= 26		--�콱״̬
PLAYER_STATE_TransGold						= 27		--��ȡ�ֽ�״̬
PLAYER_STATE_DANCERY                		= 28
PLAYER_STATE_BLACKGOLD                      = 29        -- �ڽ����
	

--*******************************************************************************
--��ְͨ������
--��Ϻ���CountryGetOfficerGUID(nCountryID,cp)��IsSpecialCountryOffical(sceneId,selfId,cp)
--*******************************************************************************
COUNTRY_POSITION_INVALID					= -1
COUNTRY_POSITION_MEMBER						= 0
COUNTRY_POSITION_GUARDS						= 1
COUNTRY_POSITION_LGUARD						= 2
COUNTRY_POSITION_RGUARD						= 3
COUNTRY_POSITION_LMINISTER					= 4
COUNTRY_POSITION_RMINISTER					= 5
COUNTRY_POSITION_GENERAL					= 6
COUNTRY_POSITION_QUEEN						= 7
COUNTRY_POSITION_KING						= 8
COUNTRY_POSITION_QINGLONG_LEADER 			= 9
COUNTRY_POSITION_QINGLONG_MEMBER 			= 10
COUNTRY_POSITION_ZHUQUE_LEADER 				= 11
COUNTRY_POSITION_ZHUQUE_MEMBER 				= 12
	
--*******************************************************************************
--����Ƶ����λ�����
--*******************************************************************************
CHAT_TYPE_NORMAL                    		= 0         --��ͨ˵����Ϣ
CHAT_TYPE_TEAM                      		= 1	        --������Ϣ
CHAT_TYPE_WORLD                     		= 2         --����
CHAT_TYPE_USER                      		= 3         --˽����Ϣ
CHAT_TYPE_SYSTEM                    		= 4         --ϵͳ��Ϣ
CHAT_TYPE_JIAZU                     		= 5         --������Ϣ
CHAT_TYPE_GUILD                     		= 6         --������Ϣ
CHAT_TYPE_COUNTRY                   		= 7         --����
CHAT_TYPE_SELF                      		= 8		    --���ͻ���ʹ�õ���Ϣ
	
CHAT_MAIN_WINDOW                    		= 0		    --��ʾ������������촰����
CHAT_LEFTDOWN                       		= 1			--���½Ǹ��˵�ϵͳ��ʾ��
CHAT_RIGHTDOWN                      		= 2			--���½�ϵͳ��ϵͳ��ʾ��
CHAT_PLUMB_SCROLL                   		= 3		    --��ֱ������ʾ��
CHAT_PLANE_SCROLL                   		= 4		    --ˮƽ������ʾ��
CHAT_MAIN_RIGHTDOWN                 		= 5	        --�м䣬���½Ǵ�����
CHAT_MIDDLE_BOTTOM_SCROLL           		= 6	        --�м��²��Ĺ�����
CHAT_MIDDLE_BOTTOM_TEXT             		= 7	        --�м��²������ֿ�
CHAT_MIDDLE_ANIM                    		= 8			--�м�Ķ�����

--*******************************************************************************
--����Msg2player�����һ������
--*******************************************************************************
MSG2PLAYER_PARA                     		= 8
CHAT_MIDDLE_ANIM                    		= 8			--�м�Ķ�����

--*******************************************************************************
--��ս��ص�ȫ�ֱ���
--*******************************************************************************
GUILDBATTLE_TIMERID                 		= 7009
GUILDBATTLE_TIMERTYPE               		= 2

--*******************************************************************************
--ѭ������mission param ������
--*******************************************************************************
MP_CIRCLE			                		= 6         --��ǰ����
MP_MAXCIRCLE	                    		= 7         --�����

--*******************************************************************************
--PK�ͷ����
--*******************************************************************************
PK_PUNISH_PRISON_SCENE_ID					= 12	--�����ĳ���ID
PK_PUNISH_PRISON_TIME_BUF_ID				= 7201	--��������ʱBUF  7201: 1Сʱ��7200: 10���� 
PK_PUNISH_DIER_RED_NAME_DECRE_PK			= 1		--������ұ�ɱ����PK˥��ֵ
PK_PUNISH_KILL_GREEN_NAME_INCRE_PK			= 50	--ɱ���������PK����ֵ
PK_PUNISH_KILL_GREEN_CASHBOX_INCRE_PK		= 50	--ɱ����������ڳ�PK����ֵ


--*******************************************************************************
--��а�ع�����id
--*******************************************************************************
YX_LOULAN_SCENE_ID1 						= 83
YX_LOULAN_SCENE_ID2 						= 84
YX_LOULAN_SCENE_ID3 						= 85
YX_LOULAN_SCENE_ID4 						= 79
YX_LOULAN_SCENE_ID5 						= 96
YX_LOULAN_SCENE_ID6 						= 97
YX_LOULAN_SCENE_ID7 						= 95
YX_LOULAN_SCENE_ID8 						= 112
YX_LOULAN_SCENE_ID9 						= 113
                                			
YX_LAIYIN_SCENE_ID1 						= 183
YX_LAIYIN_SCENE_ID2 						= 184
YX_LAIYIN_SCENE_ID3 						= 185
YX_LAIYIN_SCENE_ID4 						= 179
YX_LAIYIN_SCENE_ID5 						= 196
YX_LAIYIN_SCENE_ID6 						= 197
YX_LAIYIN_SCENE_ID7 						= 195
YX_LAIYIN_SCENE_ID8 						= 212
YX_LAIYIN_SCENE_ID9 						= 213                                			
                                			
YX_KUNLUN_SCENE_ID1 						= 283
YX_KUNLUN_SCENE_ID2 						= 284
YX_KUNLUN_SCENE_ID3 						= 285
YX_KUNLUN_SCENE_ID4 						= 279
YX_KUNLUN_SCENE_ID5 						= 296
YX_KUNLUN_SCENE_ID6 						= 297
YX_KUNLUN_SCENE_ID7 						= 295
YX_KUNLUN_SCENE_ID8 						= 312
YX_KUNLUN_SCENE_ID9 						= 313
                                			
YX_DUNHUANG_SCENE_ID1 						= 383
YX_DUNHUANG_SCENE_ID2 						= 384
YX_DUNHUANG_SCENE_ID3 						= 385
YX_DUNHUANG_SCENE_ID4 						= 379
YX_DUNHUANG_SCENE_ID5 						= 396
YX_DUNHUANG_SCENE_ID6 						= 397
YX_DUNHUANG_SCENE_ID7 						= 395
YX_DUNHUANG_SCENE_ID8 						= 412
YX_DUNHUANG_SCENE_ID9 						= 413

--*******************************************************************************
--��а�ع�human����
--*******************************************************************************
YX_LOULAN_HUMAN_NUM1 						= 0
YX_LOULAN_HUMAN_NUM2 						= 0
YX_LOULAN_HUMAN_NUM3 						= 0
YX_LOULAN_HUMAN_NUM4 						= 0
YX_LOULAN_HUMAN_NUM5 						= 0
YX_LOULAN_HUMAN_NUM6 						= 0
YX_LOULAN_HUMAN_NUM7 						= 0
YX_LOULAN_HUMAN_NUM8 						= 0
YX_LOULAN_HUMAN_NUM9 						= 0
                                			
YX_LAIYIN_HUMAN_NUM1 						= 0
YX_LAIYIN_HUMAN_NUM2 						= 0
YX_LAIYIN_HUMAN_NUM3 						= 0
YX_LAIYIN_HUMAN_NUM4 						= 0
YX_LAIYIN_HUMAN_NUM5 						= 0
YX_LAIYIN_HUMAN_NUM6 						= 0
YX_LAIYIN_HUMAN_NUM7 						= 0
YX_LAIYIN_HUMAN_NUM8 						= 0
YX_LAIYIN_HUMAN_NUM9 						= 0
                                			
YX_KUNLUN_HUMAN_NUM1 						= 0
YX_KUNLUN_HUMAN_NUM2 						= 0
YX_KUNLUN_HUMAN_NUM3 						= 0
YX_KUNLUN_HUMAN_NUM4 						= 0
YX_KUNLUN_HUMAN_NUM5 						= 0
YX_KUNLUN_HUMAN_NUM6 						= 0
YX_KUNLUN_HUMAN_NUM7 						= 0
YX_KUNLUN_HUMAN_NUM8 						= 0
YX_KUNLUN_HUMAN_NUM9 						= 0
                                			
YX_DUNHUANG_HUMAN_NUM1 						= 0
YX_DUNHUANG_HUMAN_NUM2 						= 0
YX_DUNHUANG_HUMAN_NUM3 						= 0
YX_DUNHUANG_HUMAN_NUM4 						= 0
YX_DUNHUANG_HUMAN_NUM5 						= 0
YX_DUNHUANG_HUMAN_NUM6 						= 0
YX_DUNHUANG_HUMAN_NUM7 						= 0
YX_DUNHUANG_HUMAN_NUM8 						= 0
YX_DUNHUANG_HUMAN_NUM9 						= 0

--*******************************************************************************
--��а�ع�objId����
--*******************************************************************************
YX_LOULAN_MONSTER_OBJ_ID1 					= {}
YX_LOULAN_MONSTER_OBJ_NUM1 					= 0
YX_LAIYIN_MONSTER_OBJ_ID1 					= {}
YX_LAIYIN_MONSTER_OBJ_NUM1 					= 0
YX_KUNLUN_MONSTER_OBJ_ID1 					= {}
YX_KUNLUN_MONSTER_OBJ_NUM1 					= 0
YX_DUNHUANG_MONSTER_OBJ_ID1 				= {}
YX_DUNHUANG_MONSTER_OBJ_NUM1 				= 0
                                			
YX_LOULAN_MONSTER_OBJ_ID2 					= {}
YX_LOULAN_MONSTER_OBJ_NUM2 					= 0
YX_LAIYIN_MONSTER_OBJ_ID2 					= {}
YX_LAIYIN_MONSTER_OBJ_NUM2 					= 0
YX_KUNLUN_MONSTER_OBJ_ID2 					= {}
YX_KUNLUN_MONSTER_OBJ_NUM2 					= 0
YX_DUNHUANG_MONSTER_OBJ_ID2 				= {}
YX_DUNHUANG_MONSTER_OBJ_NUM2 				= 0
                                			
YX_LOULAN_MONSTER_OBJ_ID3 					= {}
YX_LOULAN_MONSTER_OBJ_NUM3 					= 0
YX_LAIYIN_MONSTER_OBJ_ID3 					= {}
YX_LAIYIN_MONSTER_OBJ_NUM3 					= 0
YX_KUNLUN_MONSTER_OBJ_ID3 					= {}
YX_KUNLUN_MONSTER_OBJ_NUM3 					= 0
YX_DUNHUANG_MONSTER_OBJ_ID3 				= {}
YX_DUNHUANG_MONSTER_OBJ_NUM3 				= 0
                                			
YX_LOULAN_MONSTER_OBJ_ID4 					= {}
YX_LOULAN_MONSTER_OBJ_NUM4 					= 0
YX_LAIYIN_MONSTER_OBJ_ID4 					= {}
YX_LAIYIN_MONSTER_OBJ_NUM4 					= 0
YX_KUNLUN_MONSTER_OBJ_ID4 					= {}
YX_KUNLUN_MONSTER_OBJ_NUM4 					= 0
YX_DUNHUANG_MONSTER_OBJ_ID4 				= {}
YX_DUNHUANG_MONSTER_OBJ_NUM4 				= 0
                                			
YX_LOULAN_MONSTER_OBJ_ID5 					= {}
YX_LOULAN_MONSTER_OBJ_NUM5 					= 0
YX_LAIYIN_MONSTER_OBJ_ID5 					= {}
YX_LAIYIN_MONSTER_OBJ_NUM5 					= 0
YX_KUNLUN_MONSTER_OBJ_ID5 					= {}
YX_KUNLUN_MONSTER_OBJ_NUM5 					= 0
YX_DUNHUANG_MONSTER_OBJ_ID5 				= {}
YX_DUNHUANG_MONSTER_OBJ_NUM5 				= 0
                                			
YX_LOULAN_MONSTER_OBJ_ID6 					= {}
YX_LOULAN_MONSTER_OBJ_NUM6 					= 0
YX_LAIYIN_MONSTER_OBJ_ID6 					= {}
YX_LAIYIN_MONSTER_OBJ_NUM6 					= 0
YX_KUNLUN_MONSTER_OBJ_ID6 					= {}
YX_KUNLUN_MONSTER_OBJ_NUM6 					= 0
YX_DUNHUANG_MONSTER_OBJ_ID6 				= {}
YX_DUNHUANG_MONSTER_OBJ_NUM6 				= 0
                                			
YX_LOULAN_MONSTER_OBJ_ID7 					= {}
YX_LOULAN_MONSTER_OBJ_NUM7 					= 0
YX_LAIYIN_MONSTER_OBJ_ID7 					= {}
YX_LAIYIN_MONSTER_OBJ_NUM7 					= 0
YX_KUNLUN_MONSTER_OBJ_ID7 					= {}
YX_KUNLUN_MONSTER_OBJ_NUM7 					= 0
YX_DUNHUANG_MONSTER_OBJ_ID7 				= {}
YX_DUNHUANG_MONSTER_OBJ_NUM7 				= 0
YX_LOULAN_MONSTER_OBJ_ID8 					= {}
YX_LOULAN_MONSTER_OBJ_NUM8 					= 0
YX_LAIYIN_MONSTER_OBJ_ID8 					= {}
YX_LAIYIN_MONSTER_OBJ_NUM8 					= 0
YX_KUNLUN_MONSTER_OBJ_ID8 					= {}
YX_KUNLUN_MONSTER_OBJ_NUM8 					= 0
YX_DUNHUANG_MONSTER_OBJ_ID8 				= {}
YX_DUNHUANG_MONSTER_OBJ_NUM8 				= 0

YX_LOULAN_MONSTER_OBJ_ID9 					= {}
YX_LOULAN_MONSTER_OBJ_NUM9 					= 0
YX_LAIYIN_MONSTER_OBJ_ID9 					= {}
YX_LAIYIN_MONSTER_OBJ_NUM9 					= 0
YX_KUNLUN_MONSTER_OBJ_ID9 					= {}
YX_KUNLUN_MONSTER_OBJ_NUM9 					= 0
YX_DUNHUANG_MONSTER_OBJ_ID9 				= {}
YX_DUNHUANG_MONSTER_OBJ_NUM9 				= 0

--��а�ع�timer���
--*******************************************************************************
YX_LOULAN_BROADCAST_NUM1 					= 0
YX_LOULAN_BROADCAST_NUM2 					= 0
YX_LOULAN_BROADCAST_NUM3 					= 0
YX_LOULAN_BROADCAST_NUM4 					= 0
YX_LOULAN_BROADCAST_NUM5 					= 0
YX_LOULAN_BROADCAST_NUM6 					= 0
YX_LOULAN_BROADCAST_NUM7 					= 0
YX_LOULAN_BROADCAST_NUM8 					= 0
YX_LOULAN_BROADCAST_NUM9 					= 0
                                			
YX_LAIYIN_BROADCAST_NUM1 					= 0
YX_LAIYIN_BROADCAST_NUM2 					= 0
YX_LAIYIN_BROADCAST_NUM3 					= 0
YX_LAIYIN_BROADCAST_NUM4 					= 0
YX_LAIYIN_BROADCAST_NUM5 					= 0
YX_LAIYIN_BROADCAST_NUM6 					= 0
YX_LAIYIN_BROADCAST_NUM7 					= 0
YX_LAIYIN_BROADCAST_NUM8 					= 0
YX_LAIYIN_BROADCAST_NUM9 					= 0
                                			
YX_KUNLUN_BROADCAST_NUM1 					= 0
YX_KUNLUN_BROADCAST_NUM2 					= 0
YX_KUNLUN_BROADCAST_NUM3 					= 0
YX_KUNLUN_BROADCAST_NUM4 					= 0
YX_KUNLUN_BROADCAST_NUM5 					= 0
YX_KUNLUN_BROADCAST_NUM6 					= 0
YX_KUNLUN_BROADCAST_NUM7 					= 0
YX_KUNLUN_BROADCAST_NUM8 					= 0
YX_KUNLUN_BROADCAST_NUM9 					= 0
                                			
YX_DUNHUANG_BROADCAST_NUM1 					= 0
YX_DUNHUANG_BROADCAST_NUM2 					= 0
YX_DUNHUANG_BROADCAST_NUM3 					= 0
YX_DUNHUANG_BROADCAST_NUM4 					= 0
YX_DUNHUANG_BROADCAST_NUM5 					= 0
YX_DUNHUANG_BROADCAST_NUM6 					= 0
YX_DUNHUANG_BROADCAST_NUM7 					= 0
YX_DUNHUANG_BROADCAST_NUM8					= 0
YX_DUNHUANG_BROADCAST_NUM9 					= 0
                                			
YX_LOULAN_CREATE_ROUNDS1 					= 0
YX_LOULAN_CREATE_ROUNDS2 					= 0
YX_LOULAN_CREATE_ROUNDS3 					= 0
YX_LOULAN_CREATE_ROUNDS4 					= 0
YX_LOULAN_CREATE_ROUNDS5 					= 0
YX_LOULAN_CREATE_ROUNDS6 					= 0
YX_LOULAN_CREATE_ROUNDS7 					= 0
YX_LOULAN_CREATE_ROUNDS8 					= 0
YX_LOULAN_CREATE_ROUNDS9 					= 0
                                			
YX_LAIYIN_CREATE_ROUNDS1 					= 0
YX_LAIYIN_CREATE_ROUNDS2 					= 0
YX_LAIYIN_CREATE_ROUNDS3 					= 0
YX_LAIYIN_CREATE_ROUNDS4 					= 0
YX_LAIYIN_CREATE_ROUNDS5 					= 0
YX_LAIYIN_CREATE_ROUNDS6 					= 0
YX_LAIYIN_CREATE_ROUNDS7 					= 0
YX_LAIYIN_CREATE_ROUNDS8 					= 0
YX_LAIYIN_CREATE_ROUNDS9 					= 0
                                			
YX_KUNLUN_CREATE_ROUNDS1 					= 0
YX_KUNLUN_CREATE_ROUNDS2 					= 0
YX_KUNLUN_CREATE_ROUNDS3 					= 0
YX_KUNLUN_CREATE_ROUNDS4 					= 0
YX_KUNLUN_CREATE_ROUNDS5 					= 0
YX_KUNLUN_CREATE_ROUNDS6 					= 0
YX_KUNLUN_CREATE_ROUNDS7 					= 0
YX_KUNLUN_CREATE_ROUNDS8					= 0
YX_KUNLUN_CREATE_ROUNDS9 					= 0
                                			
YX_DUNHUANG_CREATE_ROUNDS1 					= 0
YX_DUNHUANG_CREATE_ROUNDS2 					= 0
YX_DUNHUANG_CREATE_ROUNDS3 					= 0
YX_DUNHUANG_CREATE_ROUNDS4 					= 0
YX_DUNHUANG_CREATE_ROUNDS5 					= 0
YX_DUNHUANG_CREATE_ROUNDS6 					= 0
YX_DUNHUANG_CREATE_ROUNDS7 					= 0
YX_DUNHUANG_CREATE_ROUNDS8 					= 0
YX_DUNHUANG_CREATE_ROUNDS9 					= 0

--*******************************************************************************
--�������
--*******************************************************************************
HZ_KILL_COUNT                   			= 0
HZ_MONSTER_OBJ                  			= {}
HZ_MONSTER_BOSSOBJ              			= -1
HZ_KILL_MONSTERBOSS             			= 0

--*******************************************************************************
--ͯȤ��������������
--*******************************************************************************
TONGQU_COMMIT_NUM               			= 0

--*******************************************************************************
--���βɹ���������������
--*******************************************************************************
YUNYOU_COMMIT_NUM               			= 0
                                			
                                			
GOLD_SPEND_TYPE_SHOP_BUY					= 0		--����̵깺��
GOLD_SPEND_TYPE_LOSS_RELIVE					= 1		--ԭ�����𸴻�
                                			
SPOUSE_TASK                     			= {7540, 7541, 7542}
SPOUSE_TASK_POSITION_USE_ITEM				= 13080010
SPOUSE_NPC									= {140002,139818,139117 }
MAX_PRENTICE_NUM                			= 5
MASTER_PRENTICE_TIME_LIMIT      			= 72    --ʦͽ�����ϵ�� ���½�����ϵ��ʱ������Сʱ��

--*******************************************************************************
--�����ǵ����
--*******************************************************************************
WULONGCIDIAN_STEPIN_NAME					={}
WULONGCIDIAN_STEPIN_TIME					={}
WULONGCIDIAN_STEPIN_COUNT					=0
WULONGCIDIAN_AWARD_NAME						={}
WULONGCIDIAN_AWARD_TIME						={}
WULONGCIDIAN_AWARD_COUNT					=0
WULONGCIDIAN_AWARD_Draw						={}

--*******************************************************************************
--��̲��½����id
--*******************************************************************************
QT_LOULAN_SCENE_ID 							= 90
QT_LAIYIN_SCENE_ID 							= 190
QT_KUNLUN_SCENE_ID 							= 290
QT_DUNHUANG_SCENE_ID 						= 390

--*******************************************************************************
--��̲��½human����
--*******************************************************************************
QT_LOULAN_HUMAN_NUM 						= 0
QT_LAIYIN_HUMAN_NUM 						= 0
QT_KUNLUN_HUMAN_NUM 						= 0
QT_DUNHUANG_HUMAN_NUM 						= 0

--*******************************************************************************
--��̲��½objId����
--*******************************************************************************
QT_LOULAN_MONSTER_OBJ_ID 					= {}
QT_LOULAN_MONSTER_OBJ_NUM 					= 0
                                			
QT_LAIYIN_MONSTER_OBJ_ID 					= {}
QT_LAIYIN_MONSTER_OBJ_NUM 					= 0
                                			
QT_KUNLUN_MONSTER_OBJ_ID 					= {}
QT_KUNLUN_MONSTER_OBJ_NUM 					= 0
                                			
QT_DUNHUANG_MONSTER_OBJ_ID 					= {}
QT_DUNHUANG_MONSTER_OBJ_NUM 				= 0

--*******************************************************************************
--��̲��½timer���
--*******************************************************************************
QT_LOULAN_BROADCAST_NUM 					= 0
QT_LAIYIN_BROADCAST_NUM 					= 0
QT_KUNLUN_BROADCAST_NUM 					= 0
QT_DUNHUANG_BROADCAST_NUM 					= 0
                                			
QT_LOULAN_CREATE_ROUNDS 					= 0
QT_LAIYIN_CREATE_ROUNDS 					= 0
QT_KUNLUN_CREATE_ROUNDS 					= 0
QT_DUNHUANG_CREATE_ROUNDS 					= 0

HIDE_NAME 									= "������"

-- ����ԤԼ������
COUNTRY_PRECONTRACT_MAXTIMES                = 5

--*******************************************************************************
--���а����
--*******************************************************************************
--���а����ݣ����հ�
WORLDCUP_TOPLIST_A							= 24	-- ���籭A��
MERIT_TOPLIST								= 28	-- ��Ṧ�����а�
AMATIVE_TOPLIST								= 30	-- �������а�
SPOUSE_TOPLIST								= 32	-- �������а�
MASTER_TOPLIST								= 34	-- ʦ�����а�
DATI_TOPLIST								= 36	-- �������а�
TIEREN_TOPLIST								= 38	-- �����������а�
WULONG_TOPLIST								= 40	-- �����ʵ����а�
BAOZANG_TOPLIST								= 42	-- �����������а�
TULONG_TOPLIST								= 44	-- �������а����а�
LABA_TOPLIST								= 46	-- С�������а�
YANHUA_TOPLIST								= 48	-- �̻����а�
QIULONGDAO_TOPLIST							= 50	-- ���������а�
HESHIBI_TOPLIST								= 52	-- ��������а�
CAISHENDIAN_TOPLIST							= 54	-- ��������а�
ZHUJIAZHUANG_TOPLIST						= 56	-- ף��ׯ���а�
LUNHUITAI_TOPLIST							= 58	-- �ֻ�̨���а�
JINGJIAOTANG_TOPLIST            			= 60    -- �����ã����������а�
ZHANSHENMU_TOPLIST              			= 62    -- ս��Ĺ�����������а�
INDIANTEMPLE_TOPLIST            			= 64    -- ӡ���������������а�

--���а����ݣ����ܰ�
LEVEL_TOP_LIST_BK							= 1		-- ���ܣ��ȼ����а�
MONEY_TOP_LIST_BK							= 3		-- ���ܣ���Ǯ���а�
HONOR_TOP_LIST_BK							= 5		-- ���ܣ��������а�
SHENGWANG_TOP_LIST_BK						= 7		-- ���ܣ��������а�
GP_TOP_LIST_BK								= 9		-- ���ܣ��ﹱ���а�
HOT_VALUE_TOP_LIST_BK 						= 11	-- ���ܣ��������а�
PK_TOP_LIST_BK								= 13	-- ���ܣ��������а�
KILL_COUNT_TOP_LIST_BK 						= 15	-- ���ܣ�ɱ�����а�
PVP2V2_TOPLIST_BK 							= 17	-- ���ܣ�ս���ȼ����а�
PVP2V2_MARK_TOPLIST_BK 						= 19	-- ���ܣ�ս���������а�
GUILD_TOP_LIST_BK 							= 21	-- ���ܣ����ʵ�����а�
GUILD_BATTLE_TOP_LIST_BK 					= 23	-- ���ܣ���ս�������а�
COUNTRY_TOP_LIST_BK							= 27	-- ���ܣ��������а�
                                			
MERIT_TOPLIST_BK							= 29	-- ���ܣ���Ṧ�����а�
AMATIVE_TOPLIST_BK							= 31	-- ���ܣ��������а�
SPOUSE_TOPLIST_BK							= 33	-- ���ܣ��������а�
MASTER_TOPLIST_BK							= 35	-- ���ܣ�ʦͽ���а�
DATI_TOPLIST_BK								= 37	-- ���ܣ��������а�
TIEREN_TOPLIST_BK							= 39	-- ���ܣ��������а�
WULONG_TOPLIST_BK							= 41	-- ���ܣ������ǵ����а�
BAOZANG_TOPLIST_BK							= 43	-- ���ܣ��������а�
TULONG_TOPLIST_BK							= 45	-- ���ܣ��������а�
LABA_TOPLIST_BK								= 47	-- ���ܣ�С�������а�
YANHUA_TOPLIST_BK							= 49	-- ���ܣ��̻����а�
QIULONGDAO_TOPLIST_BK						= 51	-- ���ܣ����������а�
HESHIBI_TOPLIST_BK							= 53	-- ���ܣ���������а�
CAISHENDIAN_TOPLIST_BK						= 55	-- ���ܣ���������а�
ZHUJIAZHUANG_TOPLIST_BK						= 57	-- ���ܣ�ף��ׯ���а�
LUNHUITAI_TOPLIST_BK						= 59	-- ���ܣ��ֻ�̨���а�
JINGJIAOTANG                    			= 61    -- ���ܣ������ã����������а�
ZHANSHENMU                      			= 63    -- ���ܣ�ս��Ĺ�����������а�
INDIANTEMPLE                    			= 65    -- ���ܣ�ӡ���������������а�




--*******************************************************************************
--����������ʹ������ɳ���͸߼�����ɳ�������Ĺ�������
GLOBAL_CREATE_MONSTER_CNT_PER_SCENE  = {}
--******************************************************************************* 
--enum eCurrencyActType   ��act_define.hͷ�ļ�һ��
eCurrencyAct_Unknow							= 0 	------/* δ֪ */
eCurrencyAct_SaveBank						= 1 	----/* ���д� */
eCurrencyAct_TakeMoneyAtBank				= 2 	----/* ����ȡ */
eCurrencyAct_ExchangeIncome					= 3 	----/* ���ҽ������� */
eCurrencyAct_ExchangeOutcome				= 4 	----/* ���ҽ���֧�� */
eCurrencyAct_PrivatelyExchangeIncome		= 5 	----/* ����ͨ��̯λ�������� */
eCurrencyAct_PrivatelyExchangeOutcome		= 6 	----/* ����ͨ��̯λ����֧�� */
eCurrencyAct_PrivatelyExchangeTaxOutcome	= 7 	----/* ����ͨ��̯λ˰��֧�� */
eCurrencyAct_PlayerShopExchangeOutcome		= 8 	----/* ����ͨ������̵꽻�׻���֧�� Ǯ������̵� */
eCurrencyAct_BuyPlayerShopOutcome			= 9 	----/* ����ͨ����������̵�֧�� */
eCurrencyAct_CreatePlayerShopOutcome		= 10 	----/* ����ͨ����������̵�֧�� */
eCurrencyAct_PlayerShopSave					= 11 	----/* ����̵�� */
eCurrencyAct_PlayerShowTake					= 12 	----/* ����̵�ȡ */
eCurrencyAct_ShopCost						= 13 	----/* �̵깺��֧�� */
eCurrencyAct_ShopSell						= 14 	----/* �̵�������� */
eCurrencyAct_ShopRepair						= 15 	----/* �̵�����֧�� */
eCurrencyAct_ShopSpecialRepair				= 16 	----/* �̵�����֧�� */
eCurrencyAct_TrainAbilityCost				= 17 	----/* ѧϰ�����֧�� */
eCurrencyAct_TrainSkillCost					= 19 	----/* ѧϰս������ */
eCurrencyAct_CallScriptCost					= 20 	----/* �ű����ý�Ǯ���� */
eCurrencyAct_CallScriptIncome				= 21 	----/* �ű����ý�Ǯ���� */
eCurrencyAct_DieCost						= 22 	----/* ������Ǯ�ͷ� */
eCurrencyAct_PetCost						= 23 	----/* �����Ǯ���� */
eCurrencyAct_CreateGuildCost				= 24 	----/* ��������Ǯ���� */
eCurrencyAct_GuildLevelUpCost				= 25 	----/* ����������� */
eCurrencyAct_ChallengeKingCost				= 26 	----/* ��ս�������� */
eCurrencyAct_ApplyActAsKing					= 27 	----/* ���뵱���� */
eCurrencyAct_GuildLevelUpFailedHandBack		= 28 	----/* �������ʧ�ܻ�Ǯ */
eCurrencyAct_CreateGuildFailedHandBack		= 29 	----/* ��������Ǯʧ�ܻ�Ǯ */
eCurrencyAct_ApplyKingFailedHandBack		= 30 	----/* �������ʧ�ܻ�Ǯ */
eCurrencyAct_CountryDonate					= 31 	----/* ���Ҿ��� */
eCurrencyAct_CountryDelate					= 32 	----/* ���ҵ��� */
eCurrencyAct_DrillCost						= 33 	----/* �ӿ׽�Ǯ���� */
eCurrencyAct_EquipLevelUpCost				= 34 	----/* װ���������Ľ�Ǯ */
eCurrencyAct_EquipRemouldCost				= 35 	----/* װ�������Ǯ���� */
eCurrencyAct_FoundEquipCost					= 36 	----/* װ�������Ǯ���� */
eCurrencyAct_EquipInlayCost					= 37 	----/* װ����Ƕ��Ǯ���� */
eCurrencyAct_EquipBindCost					= 40 	----/* װ���󶨽�Ǯ���� */
eCurrencyAct_EquipChangeCard				= 41 	----/* װ�����ƽ�Ǯ���� */
eCurrencyAct_GMmodify						= 42 	----/* GM �޸� */
eCurrencyAct_HorseMating					= 43 	----/* ���� */
eCurrencyAct_HorseFindingMating				= 44 	----/* ��������������� [6/16/2008 wuwenbin] */
eCurrencyAct_HorseRiseHappy					= 46 	----/* ������Ŀ��ֶ� */
eCurrencyAct_MarryCost						= 47 	----/* ������� */
eCurrencyAct_DivorceCost					= 48 	----/* ������� */
eCurrencyAct_PresentWeddingRB				= 49 	----/* �μӻ���ĺ�� */
eCurrencyAct_CashAccountToChar				= 50 	----/* ���ʻ�ת����ɫ���ֽ� */
eCurrencyAct_ChatCost						= 51 	----/* �������� */
eCurrencyAct_ProxyTrain						= 52 	----/* �������� */
eCurrencyAct_Exchange						= 53 	----/* ��Ǯ�һ� */
eCurrencyAct_TakeCountryFinancingAtBank		= 54 	----/* ��ȡ�����ʽ� */
eCurrencyAct_CashVendueCost					= 55 	----/* �ֽ��̵����Ԥ�� */
eCurrencyAct_CashVendueFailedHandBack		= 56 	----/* �ֽ��̵����ʧ�ܷ��� */
eCurrencyAct_CashShopBuyCost				= 57 	----/* �ֽ��̵깺��Ԥ�� */
eCurrencyAct_CashShopBuyFailedHandBack		= 58 	----/* �ֽ��̵깺��ʧ�ܷ��� */
eCurrencyAct_CashShopBuySuccessed			= 59 	----/* �ֽ��̵깺��ɹ����ֽ� */
eCurrencyAct_CashShopRetakeAtBank			= 60 	----/* �ֽ���ۺ�ͨ��������ȡ�ֽ� */
eCurrencyAct_OnHandSillerShopRetakeAtBank	= 61 	----/* �ֽ���ۺ�ͨ��������ȡ���� */
eCurrencyAct_EquipColorChange				= 62 	----/* ��װ����װ���� */
eCurrencyAct_EquipPurpleWashAttr			= 63 	----/* ��װϴ���Ի��� */
eCurrencyAct_EquipGemLevelUpCost			= 64 	----/* ��ʯ�������� */
eCurrencyAct_EquipGemCompoundCost			= 65 	----/* ��ʯ�ϳ����� */
eCurrencyAct_EquipGemTeardown				= 66 	----/* ��ʯ��ж���� */
eCurrencyAct_EquipCopyCost					= 67 	----/* װ�����ƻ��� */
eCurrencyAct_ExchangeGoldIncome				= 68 	----/* �ֽ������� */
eCurrencyAct_ExchangeGoldOutcome			= 69 	----/* �ֽ���֧�� */
eCurrencyAct_PrivatelyExchangeIncomeGold 	= 70 	----/* ����ͨ��̯λ�������룬�ֽ� */
eCurrencyAct_PrivatelyExchangeOutcomeGold 	= 71  ----/* ����ͨ��̯λ����֧�� */
eCurrencyAct_2v2MarkScriptAdd				= 72 	----/* 2v2ս���������� */
eCurrencyAct_2v2MarkScriptSub				= 73 	----/* 2v2ս�����ּ��� */
eCurrencyAct_PrivatelyExchangeTax			= 74 	----/* ̯λ������˰������ */
eCurrencyAct_PrivatelyExchangeTaxGold		= 75 	----/* ̯λ������˰���ֽ� */
eCurrencyAct_EquipRecallAddMoney			= 76 	----/* װ�����յõ���Ǯ*/
eCurrencyAct_ScriptChangeGP					= 77 	----/* �ű����ã��ﹱ�ı� */
eCurrencyAct_ServerSyncGP					= 78 	----/* GLͬ���ﹱֵ */
eCurrencyAct_CharGoldToStock				= 79 	----/* ��Ʊ�˻���ֵ�۳����ֽ� */
eCurrencyAct_CharSillerToStock				= 80 	----/* ��Ʊ�˻���ֵ�۳������� */
eCurrencyAct_CharGoldToStockFailed			= 81 	----/* ��Ʊ�˻���ֵʧ�ܣ��ع��ֽ� */
eCurrencyAct_CharSillerToStockFailed		= 82 	----/* ��Ʊ�˻���ֵʧ�ܣ��ع����� */
eCurrencyAct_StockGoldToChar				= 83 	----/* ��Ʊ�˻��ֽ�ת�˵���ɫ�������ֽ� */
eCurrencyAct_StockSillerToChar				= 84 	----/* ��Ʊ�˻�����ת�˵���ɫ���������� */
eCurrencyAct_ScriptChangeMerit				= 85 	----/* �ű����ã��ı��Ṧ��ֵ */
eCurrencyAct_GMChangeMerit					= 86 	----/* GM����ı��Ṧ��ֵ */
eCurrencyAct_ServerSyncMerit				= 87 	----/* GLͬ����Ṧ��ֵ */
eCurrencyAct_StockRegisterCostMoney			= 88 	----/* ��Ʊϵͳ�����շѣ��۳����� */
eCurrencyAct_StockRegisterFailedAddMoney	= 89 	----/* ��Ʊϵͳ����ʧ�ܣ��������� */
eCurrencyAct_BlueAddCost					= 90 	----/* �����Ը��ӵĻ��� */
eCurrencyAct_StockAutoSaleCostGold			= 91 	----// ί������: �۳������������ �ֽ�
eCurrencyAct_StockAccDieAddMoney			= 92 	----// ��Ʊ�˻�����: �ʽ𷵻ؽ�ɫ
eCurrencyAct_StockSysBuyGold				= 93 	----// ��Ʊϵͳ��ϵͳ���߹����ֽ�
eCurrencyAct_EquipSwitch					= 94 	----// װ��ת������
eCurrencyAct_MentalBuyItem					= 95 	----/* ���⹺����� */
eCurrencyAct_GuildSkillLevelUpCost			= 96 	----/* ����츳������������ */
eCurrencyAct_BlueProduceCost      			= 97 		----/*��װ��������*/
eCurrencyAct_ConstBindCost					= 98 		----/*��������*/

----/* 100->200Ϊ�淨��ʹ������ҵĲ������� */
eCurrencyAct_TestFee						= 100 	----/* ���Է� */
eCurrencyAct_Prize							= 101 	----/* �콱 */
eCurrencyAct_ScriptChangeActivity			= 102 	----/* �ű����ã��ı����Ծ�� */
----/* 300->400Ϊ�ű��淨�Ȳ������� */
----/* ��Ǯ*/
eCurrencyAct_Relive							= 300  ----/*����*/
eCurrencyAct_NormalMission					= 301  ----/*һ������*/
eCurrencyAct_ChuanSong						= 302  ----/*����*/
eCurrencyAct_Betray							= 303  ----/*�ѹ�*/
eCurrencyAct_Levelup						= 304  ----/*����*/
eCurrencyAct_Hunyin							= 305  ----/*����*/
eCurrencyAct_Wuting							= 306  ----/*����*/
eCurrencyAct_GoldDel						= 307  ----/* �ֽ������������ֽ� */
eCurrencyAct_SuperSale						= 308  ----/* �ֽ����� */
eCurrencyAct_OfflineTrain					= 309  ----/* ���ߴ��� */
eCurrencyAct_SubscribeToGuild				= 310  ----/* ���װ���Ǯ */

eCurrencyAct_Wulongyin_mojun				= 311  ----/* ����ӡ�һ�-�콵ħ�� */
eCurrencyAct_Wulongyin_wabao				= 312  ----/* ����ӡ�һ�-�ڱ�����ս */
eCurrencyAct_Wulongyin						= 313  ----/* ����ӡ�һ� */
eCurrencyAct_Wulongyin_huapi				= 314  ----/* ����ӡ�һ�-��Ƥ */
eCurrencyAct_Wulongyin_qiannv				= 315  ----/* ����ӡ�һ�-ٻŮ�Ļ� */
eCurrencyAct_Qiangjiang						= 316  ----/* ���������� */
eCurrencyAct_Shangxiang						= 317  ----/* ������Ը */
eCurrencyAct_Baoxiang						= 318  ----/* ����� */
eCurrencyAct_Xingbing_loulan				= 319  ----/* �±��ٳ� ¥�� */
eCurrencyAct_Xingbing_tianshan				= 320  ----/* �±��ٳ� ��ɽ */
eCurrencyAct_Xingbing_kunlun				= 321  ----/* �±��ٳ� ���� */
eCurrencyAct_Xingbing_dunhuang				= 322  ----/* �±��ٳ� �ػ� */
eCurrencyAct_Mojun							= 323  ----/* �콵ħ�� */
eCurrencyAct_Baolong						= 324  ----/* ��������ս */
eCurrencyAct_GuildSuCheng					= 325  ----/* ����ٳ� */
eCurrencyAct_ITEM_OTHER_195					= 326  ----/* ������������ */
eCurrencyAct_ITEM_OTHER_197					= 327  ----/* ��������𿨡� */
--eCurrencyAct_NUM

