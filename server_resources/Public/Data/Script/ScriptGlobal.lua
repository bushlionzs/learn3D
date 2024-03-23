math.randomseed( GetCurrentTime() )

--*******************************************************************************
--MissionData中各个数据的定义
--*******************************************************************************

MD_GUOJIARENWU_RANDMISSIONID		= {0, 0, 18}
MD_GUOJIARENWU_RANDMISSIONTYPE      = {0, 18, 4}	    --保证每次国家任务随机到的类型不同
MD_GUOJIARENWU_LASTDAY				= {0, 22, 9}	    --接任务日期或放弃任务的日期

MD_GUOJIARENWU_CIRCLE				= {1, 0, 6}		    --当轮环数的技术
MD_GUOJIARENWU_HIGH					= {1, 6, 8}		    --当天高额奖励的计数
MD_GUOJIARENWU_ABANDON				= {1,14,12}	    	--最后一次放弃时间
MD_WUTING_CHANGEID                  = {1,26, 5}       	-- 舞厅变身ID，用来在舞厅下线后再上线恢复变身

MD_BANGHUI_RANDMISSIONID			= {2, 0,18}
MD_BANGHUI_RANDMISSIONTYPE			= {2,18, 4}	    	--保证每次帮会任务随机到的类型不同
MD_BANGHUI_LASTDAY					= {2,22, 9}	    	--接任务日期或放弃任务的日期

MD_BANGHUI_CIRCLE					= {3, 0, 4}			--当轮环数的计数
MD_BANGHUI_ABANDON_DAY				= {3, 4, 9}			--放弃日期
MD_BANGHUI_ABANDON					= {3,13,11}	    	--放弃时间（分钟）
MD_BANGHUI_HIGH                     = {3,24, 8}

MD_TONGQU_ROUND 					= {4, 0, 1}		    --rounds
MD_TONGQU_CIRCLE 					= {4, 1, 3}	    	--子任务的计数
MD_TONGQU_DATE 						= {4, 4, 9}	   	 	--最后一次接任务时间
DQ_SHOUBIAN_COUNT					= {4,13, 7}	    	--国家守边成功次数
MD_BUS_PATROL_RECORD				= {4,20, 3}
MD_SKILL_LING_SHUANG				= {4,23, 9}	    	--冻双时记录剩余双倍时间

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

MD_DATI_JISHI_KAIGUAN				= {7,16, 4}       	--防外挂答题计时开关
MD_XIANJIN_FUBEN_TALK_PARAM			= {7,20, 4}       	--现金副本对话参数

MD_ZHENGSHUI_DATE					= {8, 0,  9}       	--第一次接任务时间，以天为单位(0-365)最大可以表示512
MD_ZHENGSHUI_ABANDON        		= {8, 9, 11}       	--最后一次放弃征税任务时间（从0点起的第N分钟）
MD_ZHENGSHUI_HIGHREWARD     		= {8, 20, 3}       	--征税高奖计数，每天前五轮征税为高奖，之后都属于低奖
MD_ZHENGSHUI_ROUND	        		= {8, 23, 3}       	--征税任务环数，3位最大可以到8环
MD_ZHENGSHUI_TIMES                  = {8, 26, 4}        --当天征税任务完成计数，最多10次

MD_SHILIAN_LUNHUITAI				= {10, 0, 9}		--轮回台接任务时间，以天为单位(0-365)最大可以表示512
MD_SHILIAN_JINKUANGDONG				= {10, 9, 9}		--金矿洞接任务时间，以天为单位(0-365)最大可以表示512
MD_SHILIAN_QIULONGDAO				= {10,18, 9}		--囚龙岛接任务时间，以天为单位(0-365)最大可以表示512

MD_SHILIAN_ZHANSHENMU				= {11, 0, 9}		--战神墓接任务时间，以天为单位(0-365)最大可以表示512
MD_SHILIAN_JINGJIAOTANG				= {11, 9, 9}		--井教堂接任务时间，以天为单位(0-365)最大可以表示512
MD_SHILIAN_HUANGHEWU				= {11,18, 9}		--黄河坞接任务时间，以天为单位(0-365)最大可以表示512

MD_SHILIAN_JINFUOSHOU				= {12, 0, 9}		--金佛手接任务时间，以天为单位(0-365)最大可以表示512
MD_WUTING_ENTERMINUTE               = {12, 9,20}      	-- 舞厅进入时间，以分钟为单位，每一年的第N分钟，最大527040

MD_FUBEN_TANBAO_DATE        		= {13, 0, 9}	    --探宝活动进入日期
MD_FUBEN_TANBAO_ENTERTIME   		= {13, 9, 5}	    --探宝活动进入时间段

MD_GUILD_KILLMONSTER_DATE			= {14, 0, 9}		--帮会杀怪日期
MD_GUILD_KILLMONSTER_COUNT			= {14, 9, 7}		--帮会杀怪单日计数器
MD_GUILD_GATHER_DATE				= {14,16, 9}		--帮会采集日期
MD_GUILD_GATHER_COUNT				= {14,25, 7}		--帮会采集单日计数器

MD_DOUBLE_DATE 						= {15, 0,10} 		--领双日期记录,最大能记录到2028年
MD_DOUBLE_TIMES						= {15,10, 9}		--每周领双次数记录,最大记录336次
MD_DOUBLE_TIMES_FLAG				= {15,19, 4}		--领双选项标识

MD_MYSELF_CONVOY_DATE				= {16, 0, 9}		--个人运镖日期，
MD_MYSELF_CONVOY_COUNT				= {16, 9, 7}		--个人运镖单日计数器

MD_GUILD_ANZHAN_DATE				= {16,16, 9}		--帮会暗战日期，用9个BIT[0,8]，最大366
MD_GUILD_ANZHAN_COUNT				= {16,25, 7}		--帮会暗战单日计数器，用7个BIT[9,15]，最大127

MD_PAO_QIAN_DATE					= {17, 0, 9}		--跑钱日期，
MD_PAO_QIAN_COUNT					= {17, 9, 7}		--跑钱单日计数器

DQ_SHOUBIAN_DATE					= {17,16, 9}		--国家守边日期，最大366
DQ_SHOUBIAN_DAYCOUNT				= {17,25, 7}		--国家守边当日次数，最大127

DQ_SHAGUAI_LOULAN_DATE				= {18, 0, 9}		--国家杀怪日期，最大366
DQ_SHAGUAI_LOULAN_DAYCOUNT			= {18, 9, 7}		--国家杀怪当日次数，最大127
DQ_SHAGUAI_LAIYIN_DATE				= {18,16, 9}		--国家杀怪日期，最大366
DQ_SHAGUAI_LAIYIN_DAYCOUNT			= {18,25, 7}		--国家杀怪当日次数，最大127

DQ_SHAGUAI_KUNLUN_DATE				= {19, 0, 9}		--国家杀怪日期，最大366
DQ_SHAGUAI_KUNLUN_DAYCOUNT			= {19, 9, 7}		--国家杀怪当日次数，最大127
DQ_SHAGUAI_DUNHUANG_DATE			= {19,16, 9}		--国家杀怪日期，最大366
DQ_SHAGUAI_DUNHUANG_DAYCOUNT		= {19,25, 7}		--国家杀怪当日次数，最大127

DQ_CITAN_LOULAN_DATE				= {20, 0, 9}		--国家刺探日期，最大366
DQ_CITAN_LOULAN_DAYCOUNT			= {20, 9, 7}		--国家刺探当日次数，最大127
DQ_CITAN_LAIYIN_DATE				= {20,16, 9}		--国家刺探日期，最大366
DQ_CITAN_LAIYIN_DAYCOUNT			= {20,25, 7}		--国家刺探当日次数，最大127

DQ_CITAN_KUNLUN_DATE				= {21, 0, 9}		--国家刺探日期，最大366
DQ_CITAN_KUNLUN_DAYCOUNT			= {21, 9, 7}		--国家刺探当日次数，最大127
DQ_CITAN_DUNHUANG_DATE				= {21,16, 9}		--国家刺探日期，最大366
DQ_CITAN_DUNHUANG_DAYCOUNT			= {21,25, 7}		--国家刺探当日次数，最大127

DQ_MIBAO_LOULAN_DATE				= {22, 0, 9}		--国家情报日期，最大366
DQ_MIBAO_LOULAN_DAYCOUNT			= {22, 9, 7}		--国家情报当日次数，最大127
DQ_MIBAO_LAIYIN_DATE				= {22,16, 9}		--国家情报日期，最大366
DQ_MIBAO_LAIYIN_DAYCOUNT			= {22,25, 7}		--国家情报当日次数，最大127

DQ_MIBAO_KUNLUN_DATE				= {23, 0, 9}		--国家情报日期，最大366
DQ_MIBAO_KUNLUN_DAYCOUNT			= {23, 9, 7}		--国家情报当日次数，最大127
DQ_MIBAO_DUNHUANG_DATE				= {23,16, 9}		--国家情报日期，最大366
DQ_MIBAO_DUNHUANG_DAYCOUNT			= {23,25, 7}		--国家情报当日次数，最大127

DQ_DUOQI_LOULAN_DATE				= {24, 0, 9}		--异国夺旗日期，最大366
DQ_DUOQI_LOULAN_DAYCOUNT			= {24, 9, 7}		--异国夺旗当日次数，最大127
DQ_DUOQI_LAIYIN_DATE				= {24,16, 9}		--异国夺旗日期，最大366
DQ_DUOQI_LAIYIN_DAYCOUNT			= {24,25, 7}		--异国夺旗当日次数，最大127

DQ_DUOQI_KUNLUN_DATE				= {25, 0, 9}		--异国夺旗日期，最大366
DQ_DUOQI_KUNLUN_DAYCOUNT			= {25, 9, 7}		--异国夺旗当日次数，最大127
DQ_DUOQI_DUNHUANG_DATE				= {25,16, 9}		--异国夺旗日期，最大366
DQ_DUOQI_DUNHUANG_DAYCOUNT			= {25,25, 7}		--异国夺旗当日次数，最大127

MD_COUNTRYBATTLELITE_DATE			= {26,16, 9}		--小国战日期
MD_COUNTRYBATTLELITE_CAMP			= {26,25, 1}		--小国战阵营
MD_COUNTRYBATTLELITE_KILLCOUNT      = {26,26, 5}		--小国战大将军或杀敌大将军个数

MD_LEVELUP_LEVEL					= {27, 0, 5}		--标记领取测试费的等级，最大31

MD_TIANJIANG_BAOXIANG_DATE 			= {27,23, 9}		--天降宝箱相关

MD_TIANJIANG_BAOXIANG_ACCEPTED1     = {28, 0, 1}
MD_TIANJIANG_BAOXIANG_ACCEPTED2     = {28, 1, 1}
MD_TIANJIANG_BAOXIANG_ACCEPTED3     = {28, 2, 1}

MD_TIEREN_ACCEPTTIME_DAY 			= {28, 3, 9}		--铁人三项，接任务时间天
MD_TIEREN_ACCEPTTIME_MINUTE			= {28,12,11}		--铁人三项，接任务时间分钟
MD_TIEREN_COMMITTIME 				= {28,23, 9}		--铁人三项，交任务时间

MD_YAOXIE_DIGONG_DAY				= {29, 0, 9}		--妖邪地宫接任务时间
MD_YAOXIE_DIGONG_MINUTE				= {29, 9,11}		--妖邪地宫，接任务时间分钟
MD_YAOXIE_DIGONG_COUNT				= {29,20, 1}		--妖牙地宫次数

MD_FRIEND_MISSION_COMPLETE_DATE 	= {31, 0, 9} 		--好友任务完成的时间
MD_FRIEND_MISSION_KILLMONSTER_NUM   = {31, 9, 9} 		--好友任务杀怪个数
MD_FRIEND_MISSION_COMPLETE_TIMES    = {31,18, 9} 		--好友任务次数

MD_COUNTRY_FULI_1 					= {31,27, 1}		--用途记录是否领取国家福利1 长度:1
MD_COUNTRY_FULI_2 					= {31,28, 1}		--用途记录是否领取国家福利2 长度:1
MD_COUNTRY_FULI_3 					= {31,29, 1}		--用途记录是否领取国家福利3 长度:1
MD_COUNTRY_FULI_4 					= {31,30, 1}		--用途记录是否领取国家福利4 长度:1

MD_SPOUSE_MISSION_DATE              = 
                                    {
									  { 32, 0, 9},     --夫妻任务第一环的完成时间
									  { 32, 9, 9},     --夫妻任务第二环的完成时间
									  { 32,18, 9}      --夫妻任务第三环的完成时间
   									} 

MD_BUS_MISSION_COMPLETE_DATE 		= {33, 0, 9} 	    --bus活动完成的时间
MD_BUS_MISSION_PATROL1 				= {33, 9, 7} 	    --bus活动巡逻点1ID
MD_BUS_MISSION_PATROL2 				= {33,16, 7}      	--bus活动巡逻点2ID
MD_BUS_MISSION_PATROL3 				= {33,23, 7}     	--bus活动巡逻点3ID


--国家补偿相关
--begin
--标识异国任务完成情况
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

MD_WUTING_GETBASEBUFF_TIME          = {36, 4,20}       	-- 领取舞厅基础奖励的时间，一年中的第N分钟

MD_FRIEND_COMPLETE_DAY 				= {37, 0, 9}
MD_FRIEND_COMPLETE_TIMES 			= {37, 9, 9}

MD_MJFY_DATE						= {37,18, 9}		--明教风云date
--MD_MJFY_DAYCOUNT					= {37,27, 5}		--明教风云daycount
MD_ZDOUXI_DATE 						= {38, 0, 9}		--赵王府斗戏date
--MD_ZDOUXI_DAYCOUNT 					= {38, 9, 9}		--赵王府斗戏daycount

MD_SHENGSICAISHEN_DATE              = {38,18, 9}       	--生死财神任务日期

MD_SHANXIN_TIME1					= {39, 0,32}		--善心经验包上次使用时间
MD_SHANXIN_TIME2					= {40, 0,32}		--善心金钱包上次使用时间
MD_SHANXIN_TIME3					= {41, 0,32}		--善心麻将包上次使用时间


MD_COLLECTHORSE_TIMES               = {42, 0, 4}       	-- 收集战马任务每日完成次数
MD_COLLECTHORSE_DATE                = {42, 4, 9}       	-- 收集战马任务完成日期

MD_DAOBAOKE_TIMES                   = {42,17, 4}      	-- 盗宝客任务每日完成次数
MD_DAOBAOKE_DATE                    = {42,21, 9}      	-- 盗宝客任务完成日期

MD_XIANJIN2YINKA_FLAG				= {43, 0, 4}		--现金换银卡选项标识
MD_XIANJIN2YINKA_DATE				= {43, 4, 9}	    --现金换银卡日期
MD_XIANJIN2YINKA_DAYCOUNT			= {43,13, 7}	    --现金换银卡已接次数

MD_YIZHESANYOU_DATE                 = {43,20, 9}       	-- 益者三友任务日期

MD_WULINDAHUI_DATE                  = {44, 5, 9}        --武林大会任务日期

MD_YIZHESANYOU_COUNTER              = {44,14, 3}       	-- 益者三友每日计次

MD_WUTING_EXP_2                     = {44,17,10}      	-- 保存舞厅双倍经验Buff保存(分钟)
MD_WUTING_EXP_4                     = {45, 0,10}      	-- 保存舞厅四倍经验Buff保存(分钟)
MD_WUTING_CREDIT_4                  = {45,10,10}      	-- 保存舞厅四倍经验Buff保存(分钟)
MD_WUTING_CREDIT_8                  = {45,20,10}      	-- 保存舞厅八倍经验Buff保存(分钟)
MD_COUNTRY_BETRAY_LASTDAY			= {46, 0,16}		-- 最后一次叛国日期
--MD_LVZHUANG40_HOUR					= {46, 16, 5}		--40级绿装玩法完成小时	
--MD_LVZHUANG40_HOURCOUNT				= {46, 21, 5}		--40级绿装玩法完成次数

MD_LVZHUANG50_DATE					= {47, 0, 9}		--50级绿装玩法完成时间	
--MD_LVZHUANG50_DAYCOUNT				= {47, 9, 5}		--50级绿装玩法完成次数

MD_LVZHUANG60_HOUR					= {47, 14, 5}		--60级绿装玩法完成小时	
MD_LVZHUANG60_HOURCOUNT				= {47, 19, 5}		--60级绿装玩法完成次数

MD_DHHT_DATE 						= {48, 0, 9}		--东海海图date
--MD_DHHT_DAYCOUNT 					= {48, 9, 5}		--东海海图daycount

MD_HDJR_DATE						= {48,14, 9}		--黄道吉日date
--MD_HDJR_DAYCOUNT					= {48,23, 5}		--黄道吉日daycount
MD_LVZHUANG70_DATE					= {49, 0, 9}		--70级绿装玩法完成时间	
--MD_LVZHUANG70_DAYCOUNT				= {49, 9, 5}		--70级绿装玩法完成次数

MD_ZHUCE_DATE						= {51, 0, 1}		--补充资料记录
MD_PVP2V2_CLEARMARK_DATE			= {51, 1,16}		--清理pvp2v2每周积分累积值的日期
MD_LVZHUANG40_DATE					= {49,14,9}			--40级绿装Date
MD_LVZHUANG60_DATE					= {49,23,9}			--60级绿装Date

MD_COUNTRYBATTLELITE_RONGYU			= {54, 0,  16}		--屠城城荣誉每日上限


MD_FUBEN_TRY_HUOCAISHENDIAN			= {55, 0, 1}		--副本试练：活财神殿
MD_FUBEN_TRY_DONGHAIHAIYAN			= {55, 3, 1}		--副本试练：
MD_FUBEN_TRY_DAWUSHI				= {55, 4, 1}		--副本试练：
MD_FUBEN_TRY_HUOQIYING				= {55, 5, 1}		--副本试练：
MD_FUBEN_TRY_HESHIBISHANG			= {55, 6, 1}		--副本试练：
MD_FUBEN_TRY_HESHIBIXIA				= {55, 7, 1}		--副本试练：
MD_FUBEN_TRY_FUTUTA6				= {55,10, 1}		--副本试练：
MD_FUBEN_TRY_HUANGJINKUANGDONG		= {55,11, 1}		--副本试练：
MD_FUBEN_TRY_GUMU					= {55,12, 1}		--副本试练：
MD_FUBEN_TRY_FUTUTA4				= {55,13, 1}		--副本试练：
MD_FUBEN_TRY_LANLONGCHENGBAO		= {55,14, 1}		--副本试练：
MD_FUBEN_TRY_HUDI					= {55,15, 1}		--副本试练：
MD_FUBEN_TRY_QIULONGDAO				= {55,18, 1}		--副本试练：
MD_FUBEN_TRY_ZHULUOJI				= {55,19, 1}		--副本试练：
MD_FUBEN_TRY_TIANJINGKENG			= {55,20, 1}		--副本试练：
MD_FUBEN_TRY_BAMIYANG				= {55,23, 1}		--副本试练：

MD_POLO_DATE                        = {56, 0, 9}       	--婆罗洲任务完成日期
MD_DANCERY_8MANA                    = {56, 9,10}      	--保存舞厅8倍威望Buff剩余时间(分钟)

MD_YUEBING_FIRSTDAY					= {56,19, 9}		--月饼礼盒使用时限

MD_SNZX_DATE						= {57, 0, 9}  		--圣女之选日期     9位
--MD_SNZX_DAYCOUNT					= {57, 9, 5}  		--圣女之选次数 5位

MD_XCZL_DATE						= {57,14, 9}  		--心诚则灵日期     9位 
--MD_XCZL_DAYCOUNT					= {57,23, 5} 		--心诚则灵次数  5位

MD_WUTING_OFFLINE_DATE				= {58, 0, 9}		--舞厅离线挂机日期
MD_WUTING_OFFLINE_TIME				= {58, 9,11}		--舞厅离线挂机时间
MD_WUTING_OFFLINE_FLAG				= {58,20, 1}		--舞厅离线挂机标记

MD_RUOGUO_NEW_TASK_FLAG				= {58,21, 7}		--弱国任务Task类型
MD_RUOGUO_NEW_DATE					= {59, 0,16}		--弱国任务星期
MD_RUOGUO_NEW_DAYCOUNT				= {59,16, 7}		--弱国任务次数
MD_RUOGUO_NEW_DAY_SUCCESS_COUNT		= {59,23, 7}		--弱国任务成功次数

MD_WUTING_PRECONTRACT_DATE          = {60, 0, 9}       	--舞厅预约日期
MD_WUTING_PRECONTRACT_TIME          = {60, 9,11}       	--舞厅预约时间
MD_WUTING_PRECONTRACT_FLAG          = {60,20, 1}       	--舞厅预约标记
									  
MD_LUCKSEED_TIMES    				= {61,26, 2} 		-- 普通祈福种子使用次数 2Bit
MD_GOLDHOPESEED_TIMES				= {62, 0, 5}		-- 黄金许愿种子使用次数 5Bit
MD_HOPESEED_DAY       				= {62, 9, 9}		-- 普通许愿种子使用日期 9Bit
MD_SEED_SCORE         				= {63, 0,17}		-- 许愿种子积分保存 17Bit
MD_LUCKSEED_DAY       				= {63,21, 9}		-- 普通祈福种子使用日期 9Bit

MD_GUILD_CIRCLE_MISSION_DATE	 	= {64, 0, 9}		--帮会跑环任务日期
MD_GUILD_CIRCLE_MISSION_DAYCOUNT	= {64, 9, 7}		--帮会跑环任务已接次数
MD_GUILD_CIRCLE_MISSION_CURRENT_ID  = {64, 16,9}		--帮会跑环任务现在的次数

MD_YUEBING_BOX_DATE 				= {65, 0, 9}		-- VIP月饼礼盒使用日期 9Bit

MD_GETGIFT1 						= {65, 9, 1}		-- 第一次领奖标记 1Bit
MD_GETGIFT2 						= {65,10, 1}		-- 第二次领奖标记 1Bit
MD_GETGIFT3 						= {65,11, 1}		-- 第三次领奖标记 1Bit
MD_GETGIFT4 						= {65,12, 1}		-- 第四次领奖标记 1Bit
MD_GETGIFT_DAY 						= {65,13, 9}		-- 领奖日期 9Big

MD_NEIZHENG_WEEKCOUNT               = {66, 0, 3}		-- 内政周高奖计次 3Bit
MD_NEIZHENG_WEEK                    = {66, 3,15}		-- 内政高奖完成周 15Bit

MD_KILLCOUNT_DAY					= {66,18, 9}		--杀人数记录日期 9Bit

MD_COUNTRY_PERSON_REDEEM_WEEK       = {67, 0,15}		-- 国民津贴领取周 15Bit

MD_LABA_COUNT     					= {67,15,16}		--小喇叭使用次数 16Bit
MD_AMATIVE_POINT  					= {68, 0,20}		--恋爱指数 20Bit
MD_AMATIVE_DAY    					= {68,20, 9}		--恋爱指数日期 9Bit
MD_YANHUA_COUNT   					= {69, 0,16}		--烟花使用数量   16Bit
MD_BAOZANG_COUNT  					= {69,16,16}		--完成“大漠盗宝客”任务次数  16Bit
MD_LABA_DAY       					= {70, 0, 9}		--小喇叭使用日期 9Bit
MD_YANHUA_DAY     					= {70, 9, 9}		--烟花使用日期   9Bit
MD_BAOZANG_DAY    					= {70,18, 9}		--完成“大漠盗宝客”任务日期  9Bit

MD_GUILD_BHZ_WIN_COUNT		    	= {70,27, 5}		--帮会津贴-帮会战本周胜利次数  5 位
MD_GUILD_BHZ_LOSE_COUNT				= {71, 0, 5}    	--帮会津贴-帮会战本周失败次数   5 位
MD_GUILD_BHZ_PING_COUNT				= {71, 5, 5}	    --帮会津贴-帮会战本周平次数     5 位
MD_GUILD_YB_DATE					= {71,10, 9} 	    --帮会津贴-帮会运镖完成日期     9 位
MD_GUILD_BHZ_DATE					= {71,19, 9}		--帮会津贴-帮会战完成日期 		9 位 
MD_GUILD_YB_WEEK_COUNT				= {72, 0, 5}	    --帮会津贴-帮会运镖本周完成次数 5 位

MD_GUILD_JINTIE_DATE				= {72, 5, 9}		--帮会津贴领取日期9位
MD_GUILD_JINTIE_DAYCOUNT		    = {72,14, 5}		--帮会津贴领取次数5位

MD_TULONG_COUNT  					= {72,19,10}		--召唤天龙魂次数  10Bit
MD_TULONG_DAY    					= {73, 0, 9}		--召唤天龙魂日期  9Bit

MD_CUXIAO_DAY						= {73, 9,16}		--岁末促销道具开启时限，30后才可再次使用此道具

MD_MENTAL_SCORE						= {74, 0,16}		--智力竞赛分数，一共七天，最大920*7
MD_MENTAL_WEEK						= {74,16, 9}		--智力竞赛周

MD_HANLEJUBAOPEN_DAY				= {75, 0,32}		--欢乐聚宝盆道具

MD_TOPLIST_PRISE_FLAG				= {76, 0, 8}  		--排行榜领奖标记 8位
MD_TOPLIST_PRISE_DATE  				= {76, 8, 9}		--排行榜领奖标记日期 9位

MD_EXCHANGE_EXP_BATTLESCORE 		= {76,17, 9}		-- 战场积分换经验日期 9bit

MD_CUXIAO1_DAY						= {77, 0,16}		--欢乐如意锦囊开启时限，30后才可再次使用此道具, 16bit

MD_HUOLIDAN_DAY						= {78, 0, 9}		--强效活力丹，一天使用一次 长度9bit
MD_PVP2V2_LEVEL_DAY  				= {78, 9, 9}		--记录pvp2v2等级的刷新时间 9Bit

MD_THREELOOP_FINFLAG				= {78,18, 1}		--标记是否完成三环副本
MD_THREELOOP_FUBENINDEX				= {78,19, 4}		--三环副本索引值
MD_THREELOOP_SUBDATE				= {78,23, 9}		--提交三环副本任务日期

MD_CHENGJIOU_BANGGONG				= {79, 0, 9}		--帮贡换经验，一天兑换一次 长度9bit
MD_CHENGJIOU_SHENGWANG				= {79, 9, 9}		--声望换经验，一天兑换一次 长度9bit
MD_CHENGJIOU_RONGYU					= {79,18, 9}		--荣誉换经验，一天兑换一次 长度9bit

MD_ZHANCHEYAYUN_COUNT 				= {80,24, 7} 		--战车押运单日计数器 长度 7
MD_ZHANCHEYAYUN_DATE 				= {81, 0, 9} 		--战车押运日期 长度 9

MD_GUOZHI_DAY						= {81, 9, 9}		--果汁果乐幸运探索包 日期 9
MD_GUOZHI_DAYCOUNT					= {81,18, 3}		--果汁果乐幸运探索包 次数 3

MD_SHOUHU_DATE						= {81,21, 9}		--守护津贴计天,青龙守护和朱雀守护共享一个,一天最多只能领一次,所以只记一个

MD_SANHUAN_FUBEN_TALK_MODE			= {82, 0, 4}		--三环副本模式对话
MD_CHANCHU_FUBEN_TALK_MODE			= {82, 4, 4}		--产出副本模式对话	
MD_CHANCHU_FUBEN_TALK_LEVEL			= {82, 8, 4}		--产出副本等级对话	

MD_QUIZ_DATE 						= {82,12, 9}		--猜谜活动日期 长度 9
MD_QUIZ_COUNT						= {82,21, 5}		--猜谜活动单日计数器 长度 5

MD_CHANCHU_FUBEN_TALK_NPC_OBJID		= {83, 0,32}		--产出副本objid

MD_WEIWANG_EXP_WEEK					= {84, 0,12}		--威望经验包上次使用时间
MD_WEIWANG_EXP_TIMES				= {84,12, 4}		--威望经验包使用次数
MD_WEIWANG_MONEY_WEEK				= {84,16,12}		--威望金钱包上次使用时间
MD_WEIWANG_MONEY_TIMES				= {84,28, 4}		--威望金钱包使用次数
MD_WEIWANG_MAJIANG_WEEK				= {85, 0,12}		--威望麻将包上次使用时间
MD_WEIWANG_MAJIANG_TIMES			= {85,12, 4}		--威望麻将包使用次数
MD_WEIWANG_SHENGWANG_WEEK			= {85,16,12}		--威望声望包上次使用时间
MD_WEIWANG_SHENGWANG_TIMES			= {85,28, 4}		--威望声望包使用次数
MD_WEIWANG_HONOR_WEEK			 	= {86, 0,12}		--威望荣誉包上次使用时间
MD_WEIWANG_HONOR_TIMES		  		= {86,12, 4}		--威望荣誉包使用次数
MD_WEIWANG_GUILD_WEEK			 	= {86,16,12}		--威望帮贡包上次使用时间
MD_WEIWANG_GUILD_TIMES		  		= {86,28, 4}		--威望帮贡包使用次数

MD_JUDIANMONEY_DATE					= {87, 0, 9}		--据点领钱日期
MD_JUDIANEXP_DATE					= {87, 9, 9}		--据点领经验日期

MD_WEIWANG_MOONCAKE_WEEK			= {87,18,12}		--用途:威望月饼包上次使用时间	 长度：12
MD_WEIWANG_CHARCOAL_WEEK			= {88, 0,12}		--用途:威望木炭包上次使用时间      长度：12
MD_WEIWANG_SUIHUO_WEEK				= {88,12,12}		--用途:威望鎏金包（水火）上次使用时间      长度：12
MD_WEIWANG_XUANCHAI_WEEK			= {89, 0,12}		--用途:威望鎏金包（炫彩）上次使用时间      长度：12
MD_WEIWANG_HAILAN_WEEK				= {89,12,12}		--用途:威望鎏金包（海蓝）上次使用时间      长度：12
MD_WEIWANG_YUNGUANG_WEEK			= {90, 0,12}		--用途:威望鎏金包（晕光）上次使用时间      长度：12

MD_WEIWANG_ITEM_WEEK_1				= {91, 0,12}		--用途:威望材料包上次使用时间	 长度：12
MD_WEIWANG_ITEM_WEEK_2				= {91,12,12}		--用途:威望材料包上次使用时间    长度：12

MD_XINBINGSUCHENG_DATECOUNT 		= {91,24, 3}		--新兵速成 长度：3   每日次数

MD_BANGHUI_TIMES 					= {91,27, 4}		--帮会任务每日计数（最大10次） 4Bits

MD_DANCERY_XP8X10                   = {92, 0,10}        -- 舞厅8倍经验10小时时间
MD_DANCERY_CREDIT8X10               = {92,10,10}        -- 舞厅8倍声望10小时时间
MD_DANCERY_MANA8X10                 = {92,20,10}        -- 舞厅8倍威望10小时时间

MD_LEVEL_TITLE                      = {93, 0, 6}        -- 等级称号领取周计数

MD_DENGMI_DATE						= {93,14, 9}		--灯谜日期
MD_DENGMI_SCORE						= {93,23, 5}        --积分
MD_DENGMI_NPC1						= {93,28, 1}        --NPC1是否答过
MD_DENGMI_NPC2						= {93,29, 1}		--NPC2是否答过
MD_DENGMI_NPC3						= {93,30, 1}		--NPC3是否答过
MD_DENGMI_NPC4						= {93,31, 1}		--NPC4是否答过

MD_RICHANG_DAY   					= {94, 0, 9}		-- 日常玩法完成日期 9bit
MD_RICHANG_COUNT 					= {94, 9, 2}	 	-- 日常玩法每日完成计数 2bit

MD_QUIZ_ANSWER 						= {94,11,10}		-- 保存仕官晋级答题题目 题目 长度：10
MD_ZHUISHA_CIRCLE					= {94,21, 4}		-- 三环追杀令任务环计数 4Bit

MD_DENGMI_NO1  						= {95, 0, 7} 		--灯谜1编号
MD_DENGMI_NO2  						= {95, 7, 7} 		--灯谜2编号
MD_DENGMI_NO3  						= {95,14, 7} 		--灯谜3编号
MD_DENGMI_NO4  						= {95,21, 7} 		--灯谜4编号

MD_HONGLAN_DATE						= {96, 0, 9}		--新添游乐场玩法 日期			
MD_HONGLAN_COUNT        			= {96, 9, 4}		--新添游乐场玩法 次数	

MD_XIANGZI_DATE						= {96,13, 9}		--游乐场玩法——抢箱子 日期 9
MD_XIANGZI_COUNT        			= {96,22, 5}		--游乐场玩法——抢箱子 次数 5

MD_FUBEN_SANHUANTOTAL    			= {97, 0,13}		--三环副本的总次数 13
MD_YIZHESANYOU_ITEM_DAY          	= {97,13, 9}		--益者三友提交物品日期 9位

MD_FUBEN_TIANFU_DATE 	 			= {97,22, 9}		--天赋副本_比武日期 9位
MD_FUBEN_TIANFU_DAYCOUNT 			= {98, 0, 3}		--天赋副本_比武次数3位

MD_DANCERY_CREDIT4X10 				= {98, 3,10}		--10小时4倍声望时间（10Bits）
MD_DANCERY_XP4X10 					= {98,13,10}		--10小时4倍经验时间（10Bits）

MD_TJMJ_TIMES						= {98,23, 6}		--每日天降魔君完成次数（6Bits）
MD_TJMJ_DATE						= {99, 0, 9}		--天降魔君完成日期（9Bits）

MD_YOULECHANG_DATE       			= {99, 9, 9}		--最后一次进入游乐场的日期9

MD_WABAO_USETIME 					= {99,18,14}		--完成任务所需时间-秒（14Bit）
MD_WABAO_FINISHED 					= {100, 0, 2}		--完成次数(2Bit)
MD_WABAO_WEEK 						= {100, 2, 6}		--周计数(6Bit)
MD_WABAO_TIMES 						= {100, 8, 2}		--周日完成次数(2Bit)
MD_WABAO_DUIHUAN1                   = {100,10, 1}       --周六挖宝兑换标记
MD_WABAO_DUIHUAN2                   = {100,11, 1}       --周日挖宝兑换标记
MD_MOJUN_DUIHUAN                    = {100,12, 1}       --天降魔君兑换标记
MD_MOJUN_WEEK                       = {100,13,12}       --天降魔君兑换周计数

MD_FUBEN_HUAPI_DAYCOUNT         	= {100,25, 3}		--大观圆画皮副本 次数3位
MD_FUBEN_HUAPI_DATE					= {101, 0, 9}       --大观圆画皮副本 日期 9位

MD_FUBEN_WEEKEND_SANFAN_DATE		= {101, 9, 9}       --三番副本 日期 9位

MD_GUILD_CIRCLE_MISSION_DATE_NV	 	= {101,18,12}		--帮会跑环任务日期

MD_OFFLINE_TRAIN_FLAG     			= {102, 0, 1}      	--离线代练生效标志
MD_OFFLINE_TRAIN_MIN       			= {102, 1,15}	    --离线代练剩余分钟

MD_TIANFU_DONGSHUANG 				= {102,16,10}		--冻双buff保存(分钟)

--MD_WULONG_DUIHUAN_DATE				= {103, 0, 9}		--五龙最近兑换的日期  废弃MD add by czg 2010-9-14 0:04:37 请铁删除
MD_DAGUANYUAN_DATE 					= {103, 9, 9}		--大观园进入日期

MD_LINGDIJINGONG_1_DATE       		= {103,18, 9}		--长度：9
MD_LINGDIJINGONG_1_DAYCOUNT   		= {103,27, 4}		--长度：4

MD_LINGDIJINGONG_2_DATE       		= {104, 0, 9}		--长度：9
MD_LINGDIJINGONG_2_DAYCOUNT   		= {104, 9, 4}		--长度：4

MD_LINGDIJINGONG_3_DATE       		= {104,13, 9}		--长度：9
MD_LINGDIJINGONG_3_DAYCOUNT   		= {104,22, 4}		--长度：4

MD_LINGDIJINGONG_4_DATE       		= {105, 0, 9}		--长度：9
MD_LINGDIJINGONG_4_DAYCOUNT   		= {104,26, 4}		--长度：4

MD_LINGDIJINGONG_5_DATE       		= {105, 9, 9}		--长度：9
MD_LINGDIJINGONG_5_DAYCOUNT   		= {105,18, 4}		--长度：4

MD_LINGDIJINGONG_6_DATE       		= {105,22, 9}		--长度：9
MD_LINGDIJINGONG_6_DAYCOUNT   		= {106, 0, 4}		--长度：4

MD_LINGDIJINGONG_7_DATE		  		= {106, 4, 9}		--长度：9
MD_LINGDIJINGONG_7_DAYCOUNT   		= {106,13, 4}		--长度：4

MD_LINGDIJINGONG_8_DATE       		= {106,17, 9}		--长度：9
MD_LINGDIJINGONG_8_DAYCOUNT   		= {106,26, 4}		--长度：4

MD_LINGDIJINGONG_9_DATE       		= {107, 0, 9}		--长度：9
MD_LINGDIJINGONG_9_DAYCOUNT   		= {107, 9, 4}		--长度：4

MD_DAGUANYUAN_SHOP_DATE        		= {107,13, 9}		--9位 日期
MD_DAGUANYUAN_SHOP_DAYCOUNT    		= {107,22, 4}		--4位 次数

MD_WULONG_DUIHUAN_DATE				= {108, 0,12}		--五龙最近兑换的第几周

MD_MBATTLE_SIGNSTATE			    = {108,21, 1}		--跨服战场签证状态 0 关闭报名签证 1 开启报名签证。所有战场公用
MD_MBATTLE_SIGNTIME			    	= {109, 0,10}		--跨服战场签证时间，10bit，秒单位，最大 1024 秒

MD_HUANGDIMILING_DATE        		= {109,10, 9}		--皇帝密令时间
MD_YANHUA_WEEK 						= {109,19,10}		--从2009年1月1日距今第N周   

MD_GUILD_SUCHENG_DATE    			= {110, 0, 9}		--帮会速成功日期 9位
MD_ITEM_OTHER_197_DATE 				= {111,12, 9}		--9位 天尊麒麟金卡CD时间
MD_HUODONG_JIERILINGJIANG_DATE		= {111,21, 9}		--9位 节日领奖

MD_TISHENSHADAI_DATE				= {112, 0, 9}		--获得专精经验的日期
MD_TISHENSHADAI_DAYCOUNT			= {112, 9, 8}		--获得专精经验的人数

MD_BATTLEHONOUR_WEEKDAY				= {112,17,12}		--战场荣誉记录周索引
MD_BATTLEHONOUR_WEEKVALUE			= {113, 0,24}		--战场周荣誉
MD_FANGYUZHILU_DATE					= {114, 9 ,9}     	--防御之路日期
MD_FANGYUZHILU_DAYCOUNT				= {114,18 ,3}   	--防御之路次数

MD_WABAO_DAYFLAG 					= {114,21, 1} 		-- 挖宝任务周六日区分标记1Bit
MD_ZHUANGONG_COEFFICIENT			= {114,22, 1}		--职业专攻天赋制作 1bit
MD_ZHUANGONG_COEFFICIENT_RESET		= {114,23, 1}		--职业专攻天赋 标志是否进行过系数重置
MD_HORSE_COMPOSE_DATE				= {116, 0,15}	    --最近一次骑乘合成日期

--------------------------------------------------------------------------------------------------------------------
--注:请不要在此区间添加其他任何MD
MD_FEAST_BEGIN						= {180, 0, 0}		--活动开始MD

MD_CURRENT_FEAST_ID 				= 6					--当活动变更的时候,请更新这个值
MD_FEAST_INDEX   					= {180, 0,16}		--用途是记录活动的索引号 长度:16

--MD_CURRENT_FEAST_ID = 0
MD_XINGYUN_ZUANSHI					= {180,16, 5}		--用途记录是领取钻石的剩余次数 长度:5
MD_XINGYUN_XISHIJI					= {180,21, 5}		--用途记录是领取洗石剂的剩余次数 长度:5
MD_XINGYUN_ZHANGMENPAI				= {180,26, 5}		--用途记录是领取掌门牌的剩余次数 长度:5
MD_XINGYUN_JINYANZHUANG				= {181, 0, 5}		--用途记录是领取经验装的剩余次数 长度:5  
MD_XINGYUN_YUEBING					= {181, 5, 5}		--用途记录是领取月饼的剩余次数 长度:5   
MD_XINGYUN_BANGGONG					= {181,10, 5}		--用途记录是领取帮贡的剩余次数 长度:5   
MD_XINGYUN_RONGYU					= {181,15, 5}		--用途记录是领取荣誉的剩余次数 长度:5   
MD_XINGYUN_SHENGWANG				= {181,20, 5}		--用途记录是领取声望的剩余次数 长度:5   
MD_XINGYUN_ZHANCHANG				= {181,25, 5}		--用途记录是领取战场积分的剩余次数 长度:5 
MD_XINGYUN_XIANYIN					= {182, 0, 5}		--用途记录是领取现银的剩余次数

--MD_CURRENT_FEAST_ID = 1
MD_QINGMING_DAY 					= {180, 16,9}		--清明节活动天
MD_QINGMING_COUNT 					= {180, 25,5}		--清明节活动次数
MD_YUREN_COUNT1						= {180, 30,1} 		--愚人节活动一个byte
MD_YUREN_COUNT2 					= {180, 31,1} 		--愚人节活动一个byte
MD_YUREN_COUNT3 					= {181,  0,1} 		--愚人节活动一个byte

--MD_CURRENT_FEAST_ID = 2
MD_LINGJIANG_TIME1					= {180,16, 1}   	--封测送金卡
MD_LINGJIANG_TIME2					= {180,17, 1}   	--封测送金卡

--MD_CURRENT_FEAST_ID = 3
MD_NEICE_LINGJIANG_TIME1			= {180,16, 1}   	--内测送银卡
MD_NEICE_LINGJIANG_TIME2			= {180,17, 1}   	--内测送银卡
MD_NEICE_LINGJIANG_TIME3			= {180,18, 1}   	--内测送银卡

--MD_CURRENT_FEAST_ID = 4
MD_ZHONGQIU_DAY1					= {180,16, 9} 		--中秋送礼
MD_ZHONGQIU_DAY2					= {181,0 , 9} 		--中秋送礼

--MD_CURRENT_FEAST_ID = 5
MD_JINLINGJIANG_DAY1					= {180,16, 9} 		--金翎奖送礼
MD_JINLINGJIANG_DAY2					= {181,0 , 9} 		--金翎奖送礼

--MD_CURRENT_FEAST_ID = 6
MD_GANENJIE_DAY1					= {180,16, 9} 		--感恩节送礼
MD_GANENJIE_DAY2					= {181,0 , 9} 		--感恩节送礼


MD_FEAST_END						= {190, 0, 0}		--活动结束MD
--------------------------------------------------------------------------------------------------------------------
--请不在在此区域添加MD
MD_VERSION_BEGIN					= 191				--版本控制起始

MD_VERSION_FLAG_0					= {191, 0, 1}		--版本控制0
MD_VERSION_FLAG_1					= {191, 1, 1}		--版本控制1
MD_VERSION_FLAG_2					= {191, 2, 1}		--版本控制2

MD_VERSION_BEGIN					= 195				--版本控制结束
--------------------------------------------------------------------------------------------------------------------

MD_FUBEN_TALK_INDEX					= {198, 0,16}		--进入哪个副本Index
MD_FUBEN_ZHUJIAZHUANG2_DATE			= {199, 0, 9}	    --祝家庄2日期
MD_FUBEN_ZHUJIAZHUANG2_DAYCOUNT		= {199, 9, 7}	    --祝家庄2已接次数
MD_FUBEN_ZHUJIAZHUANG3_DATE			= {199,16, 9}	    --祝家庄3日期
MD_FUBEN_ZHUJIAZHUANG3_DAYCOUNT		= {199,25, 7}	    --祝家庄3已接次数

MD_FUBEN_DAWUSHI_DATE				= {200, 0, 9}	    --景教堂日期
MD_FUBEN_DAWUSHI_DAYCOUNT			= {200, 9, 7}	    --景教堂已接次数
MD_FUBEN_JUNYAOYAOKOU_DATE			= {200,16, 9}	    --钧窑场日期
MD_FUBEN_JUNYAOYAOKOU_DAYCOUNT		= {200,25, 7}	    --钧窑场日期

MD_FUBEN_DONGHAIHAIYAN_DATE			= {201,16, 9}	    --龙穴日期
MD_FUBEN_DONGHAIHAIYAN_DAYCOUNT		= {201,25, 7}	    --龙穴已接次数

MD_FUBEN_HUOQIYING_DATE				= {202, 0, 9}	    --黄河坞日期
MD_FUBEN_HUOQIYING_DAYCOUNT			= {202, 9, 7}	    --黄河坞已接次数
MD_FUBEN_HESHIBISHANG_DATE			= {202,16, 9}	    --和氏璧日期
MD_FUBEN_HESHIBISHANG_DAYCOUNT		= {202,25, 7}	    --和氏璧已接次数

MD_FUBEN_HESHIBIXIA_DATE		    = {203, 0, 9}	    --金銮殿日期
MD_FUBEN_HESHIBIXIA_DAYCOUNT		= {203, 9, 7}	    --金銮殿已接次数
MD_FUBEN_GOULANQUTAI_DATE		  	= {203,16, 9}	    --勾栏曲台日期
MD_FUBEN_GOULANQUTAI_DAYCOUNT		= {203,25, 7}	    --勾栏曲台已接次数

MD_FUBEN_FUTUTA6_DATE				= {204, 0, 9}	    --虚空镜日期
MD_FUBEN_FUTUTA6_DAYCOUNT			= {204, 9, 7}	    --虚空镜已接次数
MD_FUBEN_HUANGJINKUANGDONG_DATE		= {204,16, 9}	    --黄金矿洞日期
MD_FUBEN_HUANGJINKUANGDONG_DAYCOUNT	= {204,25, 7}	    --黄金矿洞已接次

MD_FUBEN_GUMU_DATE					= {205, 0, 9}	    --古墓日期
MD_FUBEN_GUMU_DAYCOUNT				= {205, 9, 7}	    --古墓日期
MD_FUBEN_FUTUTA4_DATE				= {205,16, 9}	    --浮4日期
MD_FUBEN_FUTUTA4_DAYCOUNT			= {205,25, 7}	    --浮4日期

MD_FUBEN_LANLONGCHENGBAO_DATE		= {206, 0, 9}	    --蓝龙城堡日期
MD_FUBEN_LANLONGCHENGBAO_DAYCOUNT	= {206, 9, 7}	    --蓝龙城堡日期

MD_FUBEN_YONGYISENGLIN_DATE			= {207,16, 9}	    --永夜森林日期
MD_FUBEN_YONGYISENGLIN_DAYCOUNT		= {207,25, 7}	    --永夜森林日期

MD_FUBEN_QIULONGDAO_DATE			= {209, 0, 9}	    --囚笼岛日期
MD_FUBEN_QIULONGDAO_DAYCOUNT		= {209, 9, 7}	
MD_FUBEN_ZHULUOJI_DATE				= {209,16, 9}	    --侏罗纪日期
MD_FUBEN_ZHULUOJI_DAYCOUNT			= {209,25, 7}

MD_FUBEN_TIANJINGKENG_DATE			= {210, 0, 9}	    --天井坑日期
MD_FUBEN_TIANJINGKENG_DAYCOUNT		= {210, 9, 7}

MD_HESHIBI_INTER_DATE				= {211, 0, 9}	    --和氏璧3环内嵌任务
MD_HESHIBI_INTER_DAYCOUNT			= {211, 9, 7}

MD_FUBEN_FOSHOU_DATE				= {211,16, 9}	    --金佛手日期
MD_FUBEN_FOSHOU_DAYCOUNT			= {211,25, 7}

MD_FUBEN_BAMIYANG_DATE				= {212, 0, 9}	    --巴米杨石窟日期
MD_FUBEN_BAMIYANG_DAYCOUNT			= {212, 9, 7}

MD_GUOYUN_DATE 						= {213, 0,32 }		--上次领取国运补偿时间
MD_CHUGUO_DATE 						= {214, 0,32}		--上次领取出国补偿时间

--猜灯谜相关MD
MD_QUEST_DENGMI_DATE				= {215, 0, 9}		--上次猜灯谜时间
MD_QUEST_DENGMI_COUNT				= {215, 9, 5}		--猜灯谜次数，不超过31次
MD_QUEST_DENGMI_NPC					= 
									{
									   {215,14,9},		--NPC1的当前答题索引
									   {215,23,9},		--NPC2的当前答题索引
									   {216,0, 9},		--NPC3的当前答题索引
									   {216,9, 9},		--NPC4的当前答题索引
									   {216,18,9},		--NPC5的当前答题索引
									}
									
MD_FRIEND_GUID_1 					= {217, 0,32} 		--好友任务对应的好友1
MD_FRIEND_GUID_2 					= {218, 0,32} 		--好友任务对应的好友2
MD_FRIEND_GUID_3 					= {219, 0,32} 		--好友任务对应的好友3
MD_FRIEND_GUID_4 					= {220, 0,32} 		--好友任务对应的好友4
MD_FRIEND_GUID_5 					= {221, 0,32} 		--好友任务对应的好友5

MD_FUBEN_DATI 						= {222, 0,16} 		--副本答题认证
MD_FUBEN_ENTERTICK 					= {222,16,16} 		--进入副本计时

MD_FUBEN_DATISTEP 					= {223, 0,16} 		--副本答题step
MD_DATI_ACTIVE_ID 					= {223,16,16}		--DATI 激活的GameId

MD_HEIJIN_DATI						= {224, 0,13} 		--黑金答题认证
MD_HEIJIN_ENTERTICK 				= {224,13,13} 		--黑金接任务计时
MD_HEIJIN_DATISTEP 					= {224,26, 6} 		--黑金答题step
--乌龙词典相关
MD_WULONG_DATE 						= {225, 0, 9}		--上次答题时间
MD_WULONG_STEP 						= {225, 9, 3}		--答题第几阶段
MD_WULONG_COUNT 					= {225,12, 5}		--答了多少个
MD_WULONG_RIGHT_COUNT 				= {225,17, 5}		--答对多少个
MD_WULONG_LAST_ANSWER 				= {225,22, 5}		--上次答到第几题
MD_WULONG_ERROR_COUNT 				= {225,27, 3}		--答错次数
MD_WULONG_TIME_BEGIN 				= {226, 0,32}		--答题开始时间

MD_LOGIN_ANSWER_DATI 				= {227, 0,13} 		--登陆答题认证
MD_LOGIN_ANSWER_ENTERTICK 			= {227,13,13} 		--登陆计时
MD_LOGIN_ANSWER_DATISTEP 			= {227,26, 6} 		--登陆答题step


MD_ENCRYPT_ARITH1					= {228, 0, 8}       --答题加密算法1
MD_ENCRYPT_ARITH2					= {228, 8, 8}		--答题加密算法2
MD_ENCRYPT_ARITH3					= {228,16, 8}		--答题加密算法3
MD_DATI_RESULT						= {228,24, 8}		--问题答案
--新兵速成
MD_XINBINGSUCHENG_FIRST 			= {229, 0, 1}		--是否是第一次领任务
MD_XINBINGSUCHENG_DATE 				= {229, 1, 9} 		--上次领任务时间
--乌龙词典相关
MD_WULONG_LAST_QUESTION 			= {229,10,16} 		--上一个问题id
MD_WULONG_GUOGUANLING 				= {229,26, 1} 		--使用过关令次数
MD_WULONG_HEIBAILING 				= {229,27, 2} 		--使用黑白令次数

MD_MASTER_PRENTICE_COM_DAY 			= {230, 0, 9} 		--师徒任务完成的天数
MD_MASTER_PRENTICE_COM_TIMES 		= {230, 9, 9} 		--师徒任务完成的次数

MD_SHANXIN_TIME4					= {231, 0, 9}		--善心声望包上次使用时间
MD_SHANXIN_TIME5					= {231, 9, 9}		--善心荣誉包上次使用时间
MD_SHANXIN_TIME6					= {231,18, 9}		--善心帮贡包上次使用时间
MD_SHANXIN_TIME7					= {232, 0, 9}		--善心材料包上次使用时间

MD_WEIWANG_ITEM_WEEK				= {232,9,12}		--威望材料包上次使用时间
MD_WEIWANG_ITEM_TIMES		  		= {232,21,4}		--威望材料包使用次数

--传送符相关
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

MD_FUBEN_ZHANSHENMU1_DATE				= {239, 0, 9}		--探索战神墓（一）日期
MD_FUBEN_ZHANSHENMU1_DAYCOUNT       	= {239, 9, 6}   	--探索战神墓（一）已接次数
MD_FUBEN_ZHANSHENMU2_DATE				= {239,15, 9}		--探索战神墓（二）日期
MD_FUBEN_ZHANSHENMU2_DAYCOUNT       	= {239,24, 6}		--探索战神墓（二）已接次数

MD_FUBEN_TRY_ZHUJIAZHUANG1				= {239,30, 1}		--【试练】三打祝家庄（一）																				
MD_FUBEN_TRY_ZHUJIAZHUANG2				= {239,31, 1}		--【试练】三打祝家庄（二）

MD_FUBEN_ZHANSHENMU3_DATE				= {240, 0, 9}		--探索战神墓（三）日期	
MD_FUBEN_ZHANSHENMU3_DAYCOUNT       	= {240, 9, 6}		--探索战神墓（三）已接次数
MD_FUBEN_SHENMIAO1_DATE					= {240,15, 9}		--印度神庙（一）日期     
MD_FUBEN_SHENMIAO1_DAYCOUNT				= {240,24, 6}       --印度神庙（一）已接次数

MD_FUBEN_TRY_ZHUJIAZHUANG3				= {240,30, 1}		--【试练】三打祝家庄（三）
MD_FUBEN_TRY_ZHANSHENMU1  				= {240,31, 1}		--【试练】探索战神墓（一）																				

MD_FUBEN_SHENMIAO2_DATE					= {241, 0, 9}       --印度神庙（二）日期           
MD_FUBEN_SHENMIAO2_DAYCOUNT				= {241, 9, 6}       --印度神庙（二）已接次数       
MD_FUBEN_SHENMIAO3_DATE					= {241,15, 9}       --印度神庙（三）日期	         
MD_FUBEN_SHENMIAO3_DAYCOUNT				= {241,24, 6}       --印度神庙（三）已接次数    

MD_FUBEN_TRY_ZHANSHENMU2  				= {241,30, 1}		--【试练】探索战神墓（二）																				
MD_FUBEN_TRY_ZHANSHENMU3  				= {241,31, 1}		--【试练】探索战神墓（三）		       

MD_FUBEN_JIAOTANG1_DATE					= {242, 0, 9}		--教堂的秘密（一）日期           
MD_FUBEN_JIAOTANG1_DAYCOUNT         	= {242, 9, 6}       --教堂的秘密（一）已接次数       
MD_FUBEN_JIAOTANG2_DATE					= {242,15, 9}       --教堂的秘密（二）日期
MD_FUBEN_JIAOTANG2_DAYCOUNT         	= {242,24, 6}       --教堂的秘密（二）已接次数

MD_FUBEN_TRY_SHENMIAO1    				= {242,30, 1}		--【试练】印度神庙（一）  																				
MD_FUBEN_TRY_SHENMIAO2    				= {242,31, 1}		--【试练】印度神庙（二）         

MD_FUBEN_JIAOTANG3_DATE					= {243, 0, 9}       --教堂的秘密（三）日期	         
MD_FUBEN_JIAOTANG3_DAYCOUNT         	= {243, 9, 6}       --教堂的秘密（三）已接次数   	

MD_FUBEN_TRY_SHENMIAO3					= {243,15, 1}       --【试练】印度神庙（三）  
MD_FUBEN_TRY_JIAOTANG1					= {243,16, 1}       --【试练】教堂的秘密（一）
MD_FUBEN_TRY_JIAOTANG2					= {243,17, 1}       --【试练】教堂的秘密（二）
MD_FUBEN_TRY_JIAOTANG3					= {243,18, 1}       --【试练】教堂的秘密（三）

MD_FUBEN_QIULONGDAO_TODAY          		= {243,19, 9}		--三番副本 长度：9
--MD_FUBEN_QIULONGDAO_TODAYCOUNT     	= {243,28, 3}      	--三番副本 长度：3   废弃 CZG 不要删除 2010-9-7 15:33:13

MD_FUBEN_XIAOQIAN_DATE					= {244, 3, 9}       --倩女幽魂副本 日期 9位
MD_FUBEN_XIAOQIAN_FLAG					= {244,12, 1}       --倩女幽魂副本兑换标记
MD_FUBEN_HUAPI_FLAG						= {244,13, 1}       --画皮副本兑换标记

MD_FUBEN_DAGUANYUAN_SHANGXIANG_DATE     = {245, 0, 9}     	--大观园上香日期
MD_FUBEN_DAGUANYUAN_SHANGXIANG_DAYCOUNT = {245, 9, 7}     	--大观园上香次数

MD_QUEST_MIGONGCHUE_ACCEPTDATE			= {245,16, 9}       --接受迷宫除恶任务的日期
MD_QUEST_MIGONGCHUE_CURRING				= {245,25, 5}      	--迷宫跑环当前环数
MD_QUEST_MIGONGCHUE_TODAYRING			= {246, 0, 5}		--本日做完的迷宫跑环环数

MD_FUBEN_QIULONGDAO_TODAYCOUNT     		= {249,19, 4}      	--三番副本 长度：4
MD_FUBEN_SANHUAN_LASTINDEX    			= {249,23, 7}   	--上次三环副本的索引值 7


--*******************************************************************************
--场景号
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


SCENE_LOULANWANGCHENG			    = 50		-- 楼兰王城
SCENE_LOULANBIANJING			    = 51		-- 楼兰边境
SCENE_LAIYINWANGCHENG			    = 150		-- 天山王城
SCENE_LAIYINBIANJING			    = 151		-- 天山边境
SCENE_KUNLUNWANGCHENG			    = 250		-- 昆仑王城
SCENE_KUNLUNBIANJING			    = 251		-- 昆仑边境
SCENE_DUNHUANGWANGCHENG		        = 350		-- 敦煌王城
SCENE_DUNHUANGBIANJING		        = 351		-- 敦煌边境

--*******************************************************************************
--副本类型
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
FUBEN_TANSUO_ZHANSHENMU_1			= 967--【队伍】探索战神墓（一）
FUBEN_TANSUO_ZHANSHENMU_2			= 966--【队伍】探索战神墓（二）
FUBEN_TANSUO_ZHANSHENMU_3			= 965--【队伍】探索战神墓（三）
FUBEN_YINDUSHENMIAO1				= 964--【队伍】印度神庙（一）
FUBEN_YINDUSHENMIAO2				= 963--【队伍】印度神庙（二）
FUBEN_YINDUSHENMIAO3				= 962--【队伍】印度神庙（三）
FUBEN_JIAOTANGMIMI1					= 961--【队伍】教堂的秘密（一）
FUBEN_JIAOTANGMIMI2					= 960--【队伍】教堂的秘密（二）
FUBEN_JIAOTANGMIMI3					= 959--【队伍】教堂的秘密（三）
FUBEN_XIANJINJINKUANGDONG			= 958--【队伍】产出金矿洞
FUBEN_QIANFOKU1               		= 957--【队伍】千佛窟1
FUBEN_QIANFOKU2               		= 956--【队伍】千佛窟2
FUBEN_QIANFOKU3               		= 955--【队伍】千佛窟3
FUBEN_QIANFOKU4               		= 954--【队伍】千佛窟4
FUBEN_QIANFOKU5               		= 953--【队伍】千佛窟5
FUBEN_QIANFOKU6               		= 952--【队伍】千佛窟6
FUBEN_TIANFU		                = 951--天赋副本_比武 
FUBEN_HUAPI							= 950--画皮
FUBEN_QIANNVYOUHUN					= 949--倩女幽魂

--*******************************************************************************
--战场类型
--*******************************************************************************
BATTLESCENE_TYPE_GUILDBATTLE		= 0			--帮会战
BATTLESCENE_TYPE_KINGBATTLE			= 1			--国王争夺战
BATTLESCENE_TYPE_WORLDCUPBATTLE		= 2			--世界杯
BATTLESCENE_TYPE_COUNTRYBATTLELITE	= 3			--屠城战
BATTLESCENE_TYPE_ZHUQUEBATTLELITE	= 4			--朱雀守护
BATTLESCENE_TYPE_QINGLONGBATTLELITE	= 5			--青龙守护
BATTLESCENE_TYPE_LAIRDGBATTLELITE	= 6			--据点争夺


--*******************************************************************************
--任务脚本
--*******************************************************************************
MISSION_TYPE_KILLMONSTER		    = 1 		--打怪
MISSION_TYPE_DELIVERY			    = 2 		--送信
MISSION_TYPE_HUSONG				    = 3 		--护送
MISSION_TYPE_ENTERAREA			    = 4 		--区域探索
MISSION_TYPE_LOOKITEM			    = 5 		--收集物品
MISSION_TYPE_USEITEM		  	    = 6 		--使用物品

--*******************************************************************************
--场景PK模式
--*******************************************************************************
PK_MODE_GUOJIA		                = 0			--国家
PK_MODE_SHANE				        = 1			--善恶
PK_MODE_BANGHUI		                = 2			--帮会
PK_MODE_JIAZU				        = 3			--家族
PK_MODE_DUIWU				        = 4			--队伍
PK_MODE_HUNZHAN		                = 5			--混战

--*******************************************************************************
--玩家身上运行时数据索引类型，索引值不可以随便改动
--*******************************************************************************
RD_HUMAN_MENTALGAME		            = 0	        --答题活动
RD_HUMAN_NAME_COLOR		            = 1	        --玩家名字的颜色

RD_HUMAN_AWARE_INDEX1			    = 2			--奖品在trophy.tab表中的索引
RD_HUMAN_AWARE_INDEX2			    = 3			
RD_HUMAN_AWARE_INDEX3			    = 4
RD_HUMAN_AWARE_INDEX4			    = 5
RD_HUMAN_AWARE_INDEX5			    = 6

RD_HUMAN_AWARE_DB_INDEX1		    = 7			--奖品在DB中的索引
RD_HUMAN_AWARE_DB_INDEX2		    = 8			
RD_HUMAN_AWARE_DB_INDEX3		    = 9
RD_HUMAN_AWARE_DB_INDEX4		    = 10
RD_HUMAN_AWARE_DB_INDEX5		    = 11
RD_HUMAN_CURR_AWARD_NPCID		    = 12		--当前领奖NPC
RD_HUMAN_CURR_AWARD_INDEX		    = 13		--当前领奖的物品索引

RD_GUILDBATTLE_BEKILLED             = 14        --帮会争夺战：被杀次数
RD_GUILDBATTLE_KILLEDOTHER          = 15        --帮会争夺战：杀人次数
RD_GUILDBATTLE_GETFLAG              = 16        --帮会争夺战：夺旗次数

RD_KING_BATTLE_BEKILLED             = 17        --国王争夺战：被杀次数

RD_HUMAN_AWARE_NUM1				    = 18		--每种奖励的个数		
RD_HUMAN_AWARE_NUM2				    = 19			
RD_HUMAN_AWARE_NUM3				    = 20
RD_HUMAN_AWARE_NUM4				    = 21
RD_HUMAN_AWARE_NUM5				    = 22

RD_GUJI_SCENEID                     = 23        --古迹探疑任务的目标场景Id
RD_GUJI_ITEMID                      = 24        --古迹探疑任务的任务物品Id

RD_COLLECT_HORSE				    = 25		--收集战马类型ID

RD_TONGQU_CD					    = 26		--童趣的cd时间
RD_CANGKU_EXT				        = 27		--仓库玩家点击记录

RD_BATTLE_SCENE_KICK_DOWN           = 28

RD_HUMAN_SCENE_PRE                  = 29        --记录上一个场景
RD_HUMAN_POSX_PRE                   = 30        --记录上一个场景位置X
RD_HUMAN_POSZ_PRE                   = 31        --记录上一个场景位置Z

RD_COLLECT_HORSE_HIGH			    = 32		--收集战马ID高位
RD_COLLECT_HORSE_LOW			    = 33		--收集战马ID低位

RD_BATTLESCENE_ENTER_FLAG           = 34        --战场进入标志
RD_GUILDCONTEND_KILL_LEADER         = 28        --帮会争霸赛杀帮主计数
RD_GUILDCONTEND_KILL_ASSIST         = 29        --帮会争霸赛杀副帮主计数
RD_GUILDCONTEND_KILL_FAMILY         = 30        --帮会争霸赛杀家族长计数
RD_GUILDCONTEND_KILL_GOLD           = 31        --帮会争霸赛杀黄金家族计数
RD_GUILDCONTEND_KILL_OTHER          = 32        --帮会争霸赛杀普通帮众计数
RD_GUILDCONTEND_DIECOUNT            = 33        --帮会争霸赛被杀次数
RD_GUILDCONTEND_SCORE               = 34        --帮会争霸赛个人积分

RD_DANCERY_BODYID                   = 35        --舞厅变身ID，已作废，改用MD_WUTING_CHANGEID

RD_EVENT_REQUEST_NPCID				= 36		--NPCID ，占位用脚本中不会用到
RD_EVENT_REQUEST_MISSION_SCRIPT_ID	= 37		--任务或脚本ID ，占位用脚本中不会用到

RD_COUNTRYBATTLELITE_KINGISSUE_NPC	= 38		--小国战拉人NPCID

RD_QUEST_DENGMI_NPC_FLAG			= 39		--灯谜答题标记，NPC
RD_QUEST_DENGMI_CUR_DENGMI			= 40		--灯谜答题标记，当前题目编号

RD_CURR_ENCRYPT_INDEX				= 41		--当前加密算法的索引
RD_LAST_ENCRYPT_INDEX				= 42		--上次加密算法的索引
RD_CURR_ENCRYPT_COUNT				= 43		--加密计数
RD_ENCRYPT_UNRESPOND_TIME			= 44		--加密未响应计时

RD_QUEST_WULONG_CUR_ANSWER			= 45		--乌龙词典当前的答案
RD_VIP_BOX                          = 46        --VIP首饰盒选择id

RD_PVP6V6_RELIVE_DOWNCOUNT			= 47		--PVP6V6死亡倒计时
RD_PVP6V6_BATTLE_MONEY				= 48		--PVP6V6战场货币

RD_STOCK_TRANS_MONEY_TIME			= 49		--股票系统充值、转账冷却时间
RD_STOCK_BUY_TIME					= 50		--股票系统购买冷却时间
RD_STOCK_SALE_TIME					= 51		--股票系统出售冷却时间
RD_STOCK_REPEAL_TIME				= 52		--股票系统撤单冷却时间
RD_STOCK_ASK_WORLD_LIST_TIME		= 53		--股票系统请求大盘的冷却时间
RD_STOCK_ASK_RECORD_TIME			= 54		--股票系统请求历史记录冷却时间
RD_STOCK_AASK_MARKET_LIST_TIME		= 55		--股票系统请求上架列表的冷却时间
RD_TRANS_ITEM_TIME					= 56		--传送符使用的时间

RD_COUNTRYBATTLELITE_ADDQUESTFLAG	= 57		--添加任务标记
RD_COMMON_NPCID						= 58		--通用NPCID处理
RD_ROOKIE_BOX						= 60		--新手卡
RD_HUANGJINKUANGDONG_OPT			= 61		--藏宝洞兑换操作
RD_FUBENPARAM_MODE					= 62		--副本模式
--RD_COMMON_LOULAN_YUNBIAO    = 63		--楼兰运镖的对话框的标记  没有RD资源了,复用	[	RD_GUILDCONTEND_KILL_LEADER        	= 28 ]
--RD_COMMON_TIANSHAN_YUNBIAO  = 64		--天山运镖的对话框的标记  没有RD资源了,复用	[	RD_GUILDCONTEND_KILL_ASSIST         = 29 ]
--RD_COMMON_KUNLUN_YUNBIAO    = 65		--昆仑运镖的对话框的标记  没有RD资源了,复用	[	RD_GUILDCONTEND_KILL_FAMILY         = 30 ]
--RD_COMMON_DUNHUANG_YUNBIAO  = 66		--敦煌运镖的对话框的标记  没有RD资源了,复用	[	RD_GUILDCONTEND_KILL_GOLD           = 31 ]
--$$$$$$$$$$$$$$
--RD资源已经没有了,请慎重加此资源  Add By chenzhiguo 2010-6-11 21:31:59
--$$$$$$$$$$$$$$

--*******************************************************************************
--国家任务数据索引
--*******************************************************************************
CD_INDEX_DESTROY_ISSUE_TIME         		= 0       	--敌国破坏上次拉人的时间
CD_INDEX_DESTROY_ISSUE_COUNT        		= 1      	--敌国破坏拉人次数
CD_INDEX_DESTROY_ISSUE_SCENE	    		= 2			--国王拉人所在场景	
CD_INDEX_MISSION_CAOBAOTU           		= 4         --藏宝图信息
CD_INDEX_GUOYUN_COUNT			    		= 5			--国运期间完成经验车几次
CD_INDEX_CHUGUO_COUNT			    		= 6			--出国期间完成出国任务的几次


CD_INDEX_COUNTRYBATTLELITE_DATE     		= 7         --小国战日期
CD_INDEX_COUNTRYBATTLELITE_CAMP     		= 8         --小国战阵营
CD_INDEX_COUNTRYBATTLELITE_KILLCOUNT		= 9         --小国战大将军记录
CD_INDEX_COUNTRYBATTLELITE_KINGISUSE		= 10		--小国战拉人次数
CD_INDEX_COUNTRYBATTLELITE_MATCH_COUNTRY	= 11		--小国战配对国家
CD_INDEX_COUNTRYBATTLELITE_FINISHED			= 12		--小国战结束标记
CD_INDEX_COUNTRYBATTLELITE_KINGISUE_NPC		= 13		--小国战结束标记

CD_INDEX_POLUOZHOU_RANDOM_DAY               = 14        -- 保存婆罗洲任务双倍经验随机日期（每周一天）

CD_INDEX_GUOYUN_DAY							= 15		--发国运令的时间
CD_INDEX_CHUGUO_DAY							= 16		--发出国令的时间

CD_INDEX_GUILDCONTEND_TURNNUMBER    		= 20        -- 帮会争霸赛全局轮次号，楼兰保存当前全局轮次号，天山保存保存本月比赛开始时的轮次号，昆仑保存上月比赛开始时的轮次号

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

CD_INDEX_STRENGTH							= 35		--国家实力
CD_INDEX_STRENGTH_Y							= 36		--昨日国家实力
CD_INDEX_STRENGTH_DAY						= 37		--国家实力记录时间

CD_INDEX_CHINAJOY_TIMES						= 38		--ChinaJoy 次数
CD_INDEX_CHINAJOY_DATE						= 39		--ChinaJoy 日期

CD_INDEX_RUOGUO_SHOUJI_DATE					= 40		--弱国任务上次收集日期
CD_INDEX_RUOGUO_SHOUJI_FLAG					= 41		--弱国任务收集Index

CD_INDEX_MOJUN_KILL_COUNT1					= 42		--十八魔君被杀次数
CD_INDEX_MOJUN_KILL_COUNT2					= 43
CD_INDEX_MOJUN_KILL_COUNT3					= 44
CD_INDEX_MOJUN_KILL_COUNT4					= 45


CD_INDEX_RUOGUO_START_FLAG					= 46		--弱国任务是否开启
CD_INDEX_MOJUN_KILL_COUNT					= 47  		--所有十八魔君被杀的计数 

CD_INDEX_STRENGTH_WEEKTOTAL					= 48
CD_INDEX_STRENGTH_WEEKTOTAL_Y				= 49
CD_INDEX_STRENGTH_WEEKTOTAL_DAY				= 50

CD_INDEX_MINSTER_KILLDATE					= 51		--国家大臣刺杀
CD_INDEX_CREATEKING_DATE					= 52		--国王上任日期

CD_INDEX_CREATE_QINGLONG_DATE				= 53		--青龙上任日期
CD_INDEX_CREATE_ZHUQUE_DATE					= 54		--朱雀上任日期

CD_INDEX_BE_DELATED_KING_GUID				= 55		--被弹劾国王GUID
CD_PIONEER_FUNS                             = 56        -- 粉丝先锋团活动
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

CD_PRECONTRACT_GUOYUN                       = 68        -- 国运预约
CD_PRECONTRACT_CHUGUO                       = 69        -- 出国预约
CD_PRECONTRACT_MUJI                         = 70        -- 国家募集预约

CD_RICHANG_QUESTID                          = 71        -- 日常玩法ID

CD_YOULECHANG_CAIPIAO1						= 72        -- 无敌幸运星
CD_YOULECHANG_CAIPIAO2						= 73        -- 无敌幸运星

CD_DAGUANYUAN_CAIPIAO1                      = 74        -- 大观园双星报喜
CD_DAGUANYUAN_CAIPIAO2                      = 75        -- 大观园双星报喜
CD_INDEX_KING_DEMISE_DATE					= 76

CD_LASTWEEK_PINGFEN_DATE					= 77 		-- 国家上周的金钱消费记录时间
CD_LASTWEEK_PINGFEN_MONEY					= 78 		-- 国家上周的金钱消费的数额
CD_CURWEEK_PINGFEN_DATE						= 79 		-- 国家本周的金钱消费记录时间
CD_CURWEEK_PINGFEN_MONEY					= 80 		-- 国家本周的金钱消费记录时间

CD_LASTWEEK_STRONG_WEAK_JIFEN				= 81		--国家上周强弱积分
CD_LASTWEEK_STRONG_WEAK_JIFEN_DATE			= 82		--国家上周强弱积分时间
CD_CURWEEK_STRONG_WEAK_JIFEN				= 83		--国家本周强弱积分
CD_CURWEEK_STRONG_WEAK_JIFEN_DATE			= 84		--国家本周强弱积分时间
CD_STRONG_WEAK_LEVEL						= 85		--国家强弱等级

CD_STRONG_WEAK_GUILD_JIFEN					= 86		--缓存帮会榜的国家强弱积分,周一刷新到国家强弱榜积分，然后重置
CD_STRONG_WEAK_GUILD_JIFEN_DATE			   	= 87		--缓存帮会榜的国家强弱积分的时间,周一重置


--*******************************************************************************
--帮会任务数据索引（参考GameDefine_Guild.h）
--*******************************************************************************
GD_GUILD_INDEX_YUNBIAO_SSUE_TIME    		= 0         --帮会运镖发布时间
GD_GUILD_INDEX_YUNBIAO_STATE        		= 1     	--帮会运镖状态
GD_GUILD_INDEX_YUNBIAO_ACCEPT_TIME  		= 2  	    --帮会运镖接受时间
GD_GUILD_INDEX_KILL_ISSUE_TIME      		= 3         --帮会杀怪的发布时间
GD_GUILD_INDEX_GATHER_ISSUE_TIME    		= 4         --帮会采集的发布时间
GD_GUILD_INDEX_BATTLE_SINGUP 				= 5		    --帮会战报名数据：报名前请求
GD_GUILD_INDEX_BATTL_STATE					= 6         --帮会战状态 0：已结束，1：进行中 ,-1未开始
GD_GUILD_INDEX_BATTL_WIN_NUM        		= 7         --帮会战获胜场次
GD_GUILD_INDEX_BATTL_LOSE_NUM       		= 8         --帮会战失败场次
GD_GUILD_INDEX_BATTL_DEUCE_NUM      		= 9         --帮会战平局场次
GD_GUILD_INDEX_BATTL_SINGUP_RESULT			= 10	    --帮会战报名是否成功 ：报名后请求
GD_GUILD_INDEX_SHOPACTIVE_PARAM0			= 11
GD_GUILD_INDEX_SHOPACTIVE_PARAM1			= 12
GD_GUILD_INDEX_SHOPACTIVE_PARAM2			= 13
GD_GUILD_INDEX_SHOPACTIVE_PARAM3			= 14
GD_GUILD_INDEX_CONTEND_TURN_NUMBER  		= 15        --帮会争霸赛轮次数据
GD_GUILD_INDEX_WORLDCUP_FLAG				= 16
GD_GUILD_INDEX_LAST_RESULT					= 17
GD_GUILD_INDEX_LAST_GB_SCORE				= 18
GD_GUILD_INDEX_ADDEXP_DATE					= 19        --帮会建设（循环）上次增加帮会经验日期
GD_GUILD_INDEX_ADDEXP_VALUE					= 20        --帮会建设（循环）当日增加帮会经验计数
GD_GUILD_INDEX_CONTEND_STATE        		= 21        --帮会争霸赛状态

GD_GUILD_INDEX_CONVOKE_COUNT				= 22		--帮会召集次数
GD_GUILD_INDEX_CONVOKE_DAY					= 23		--帮会召集时间

GD_GUILD_INDEX_CONTEND_WIN_COUNT    		= 24        --帮会争霸赛取胜计数
GD_GUILD_INDEX_CONTEND_LOSE_COUNT   		= 25        --帮会争霸赛失利计数

GD_GUILD_INDEX_MINISTER_GUILD_DATE			= 26		--国家大战下台的帮会
GD_GUILD_INDEX_VIP_COLLECT_COUNT			= 27		--帮会VIP募集次数，需要每日清零
GD_GUILD_INDEX_GET_MONEY_COUNT				= 28		--帮会跑钱(玩法)次数，需要每日清零
GD_GUILD_INDEX_MULTI_MISSION_HUSHOU			= 29		--帮会多倍任务(护兽)，需每周清零
GD_GUILD_INDEX_MULTI_MISSION_HEIMU			= 30		--帮会多倍任务(黑木)，需每周清零
GD_GUILD_INDEX_MULTI_MISSION_ANZHAN			= 31		--帮会多倍任务(暗战)，需每周清零
GD_GUILD_INDEX_MULTI_MISSION_CHUYAO			= 32		--帮会多倍任务(除妖)，需每周清零
GD_GUILD_INDEX_MULTI_MISSION_MUJI			= 33		--帮会多倍任务(募集)，需每周清零
GD_GUILD_INDEX_MULTI_MISSION_TODAY			= 34		--今日发布的帮会多倍任务，需每日清零
GD_GUILD_INDEX_CHIEF_MULTIMISSION_DAY		= 35		--帮主领取多倍任务奖励日期
GD_GUILD_INDEX_ASSCHIEF_MULTIMISSION_DAY	= 36		--副帮主领取多倍任务奖励日期
GD_GUILD_WORLDCUP_TITLE_TIME                = 37        --世界杯头顶称号保存时间
GD_GUILD_LAIRDBATTLE_SCENEID				= 38		--据点守护占领的场景
GD_GUILD_INDEX_YUNBIAO_RING_MIS_TIME  		= 39  	    --帮会运镖环任务接受时间
GD_GUILD_LAIRDBATTLE_DATE					= 40		--据点守护占领的时间

GD_GUILD_ACTIVITY_PARAM1					= 41		--帮会活跃度参数1
GD_GUILD_ACTIVITY_PARAM2					= 42		--帮会活跃度参数2
GD_GUILD_ACTIVITY_PARAM3					= 43		--帮会活跃度参数3
GD_GUILD_ACTIVITY_PARAM4					= 44		--帮会活跃度参数4
GD_GUILD_ACTIVITY_PARAM5					= 45		--帮会活跃度参数5
GD_GUILD_ACTIVITY_PARAM6					= 46		--帮会活跃度参数6
GD_GUILD_ACTIVITY_PARAM7					= 47		--帮会活跃度参数7
GD_GUILD_ACTIVITY_PARAM8					= 48		--帮会活跃度参数8

GD_GUILD_LAIRDBATTLE_REDEEM_DATE			= 49		--据点守护领取领地金钱时间
GD_GUILD_LAIRDBATTLE_LEVEL					= 50		--据点守护养成等级

GD_GUILD_HANDIN_DATE                        = 51        --帮会捐献日期
GD_GUILD_HANDIN_MONEY                       = 52        --帮会每日捐献数

GD_GUILD_LAIRDBATTLE_CURRENT_EXP			= 53		--据点帮会当前经验

GD_GUILD_LASTMONTH_GUILD_MEMBER_MONEY	= 54			--帮主扶持任务帮会成员上月的消费金额
GD_GUILD_CURMONTH_GUILD_MEMBER_MONEY	= 55			--帮主扶持任务帮会成员本月的消费金额
GD_GUILD_LASTMONTH						= 56
GD_GUILD_CURMONTH						= 57

--*******************************************************************************
--帮会多倍任务定义值
--*******************************************************************************
GUILD_MULTI_MISSION_HUSHOU 					= 0			-- 护兽
GUILD_MULTI_MISSION_HEIMU					= 1			-- 黑木
GUILD_MULTI_MISSION_ANZHAN					= 2			-- 暗战
GUILD_MULTI_MISSION_CHUYAO					= 3			-- 除妖
GUILD_MULTI_MISSION_MUJI					= 4			-- 募集

--*******************************************************************************
--可执行邮件 param0 的可能值
--*******************************************************************************
MAIL_REPUDIATE				        		= 1			--强制离婚
MAIL_BETRAYMASTER			        		= 2			--叛师
MAIL_EXPELPRENTICE			        		= 3			--开除徒弟
MAIL_UPDATE_ATTR			        		= 4			--属性刷新
MAIL_UNSWEAR				        		= 5			--解除结拜
MAIL_PRENTICE_EXP			        		= 6			--徒弟给师傅经验
MAIL_LEAVE_GUILD			        		= 7			--离开帮会（可能是被踢或解散）
MAIL_GIVE_MONEY				        		= 8			--给钱
MAIL_GIVE_ITEM				        		= 9			--给物品
MAIL_DELETE_MISSION		            		= 10		--删除任务
MAIL_GIVE_MONEY2MASTER	            		= 11		--给师傅钱
MAIL_GIVE_EXP				        		= 12		--给经验
MAIL_MASTER_AWARD							= 13		--徒弟升级给师傅的奖励



--*******************************************************************************
--帮会战场中的数据索引,LD表示只存储在场景中类似于一个LOCAL数据
--前32位为通用数据，后32位为不同玩法特有的数据
--下列数据保存在场景中
--*******************************************************************************
--帮战状态
STATE_GUILD_BATTLE_READY            		= 0		    --战斗场景准备好了
STATE_GUILD_BATTLE_SIGNUP           		= 1		    --开始报名
STATE_GUILD_BATTLE_SIGNUP_FINISH    		= 2	        --报名结束
STATE_GUILD_BATTLE_BATTLE           		= 3		    --开始战斗
STATE_GUILD_BATTLE_BATTLE_FINISH    		= 4	        --战斗结束

--*******************************************************************************
--帮会战通用数据
--*******************************************************************************
LD_GUILD_BATTLE_TYPE			    		= 0  		--帮会战玩法类型
LD_GUILD_BATTLE_SCRIPT			    		= 1  		--场景脚本ID
LD_GUILD_BATTLE_A_SOCRE 		    		= 2			--A方积分
LD_GUILD_BATTLE_B_SOCRE 		    		= 3			--B方积分
LD_GUILD_BATTLE_LAST_TICK		    		= 4  		--上一次心跳时间
LD_GUILD_BATTLE_A_GUILD			    		= 5  		--A方帮会ID
LD_GUILD_BATTLE_B_GUILD			    		= 6  		--B方帮会ID
LD_GUILD_BATTLE_COUNT_DOWN_STATE    		= 7  		--活动结束后的倒计时退出状态
LD_GUILD_BATTLE_COUNT_DOWN_TIME     		= 8 		--倒计时(单位秒)
LD_GUILD_BATTLE_COUNT_ITME          		= 9         --战场已过的时间
LD_GUILD_BATTLE_REFRESH_MAP         		= 10        --战场已过的时间
LD_GUILD_BATTLE_BARN1_GUILD		    		= 11 		--粮仓所属帮会ID
LD_GUILD_BATTLE_BARN2_GUILD		    		= 12 		--粮仓所属帮会ID
LD_GUILD_BATTLE_BARN3_GUILD		    		= 13 		--粮仓所属帮会ID
LD_GUILD_BATTLE_BARN4_GUILD		    		= 14 		--粮仓所属帮会ID
LD_GUILD_BATTLE_A_FLAG_NUM		    		= 15		--A方夺旗次数
LD_GUILD_BATTLE_B_FLAG_NUM		    		= 16		--B方夺旗次数
LD_GUILD_BATTLE_BARN1_TIME		    		= 17 		--粮仓被占领时间
LD_GUILD_BATTLE_BARN2_TIME		    		= 18 		--粮仓被占领时间
LD_GUILD_BATTLE_BARN3_TIME		    		= 19 		--粮仓被占领时间
LD_GUILD_BATTLE_BARN4_TIME		    		= 20 		--粮仓被占领时间
LD_GUILD_BATTLE_FLAG_TIME           		= 21        --旗子夺走后的计时
LD_GUILD_BATTLE_FLAG_OWNER          		= 22        --旗子当前所有者
LD_GUILD_BATTLE_FLAG_NOW_X          		= 23        --旗子当前坐标X
LD_GUILD_BATTLE_FLAG_NOW_Y          		= 24        --旗子当前坐标Y
LD_GUILD_BATTLE_FLAG_A_ID					= 25		--帮会战中战旗A信息
LD_GUILD_BATTLE_FLAG_B_ID					= 26		--帮会战中战旗B信息

--帮会玩法1的全局变量
LD_GUILD_BATTLE_DEC_SPEED_BUF 	    		= 7700      --减速和旗子BUS
LD_GUILD_BATTLE_INC_DEFENCE_BUF     		= 7701      --加防御BUF
--LD_GUILD_BATTLE_FLAG_BUF 		    		= 1210      --旗子BUF
LD_GUILD_BATTLE_FLAG_COUNT          		= 9         --帮会玩法1夺旗总数，从0开始计数 
LD_GUILD_BATTLE_FLAG_GROW_POINT     		= 111 	    --旗子生长点ID
LD_GUILD_BATTLE_FLAG_X              		= 128       --旗子原始坐标X
LD_GUILD_BATTLE_FLAG_Y              		= 128       --旗子原始坐标Y

--*******************************************************************************
--世界杯状态
--*******************************************************************************
STATE_GUILD_WORLDCUP_SIGNUP         		= 10    	--开始报名
STATE_GUILD_WORLDCUP_SIGNUPEND      		= 11    	--报名结束
STATE_GUILD_WORLDCUP_PREPARE				= 12		--准备状态
STATE_GUILD_WORLDCUP_START					= 13		--比赛开始
STATE_GUILD_WORLDCUP_END					= 14		--比赛结束
STATE_GUILD_WORLDCUP_FINISHED				= 15		--该月比赛结束
STATE_GUILD_WORLDCUP_DISABLESIGNUP  		= 16    	--禁止报名阶段

--*******************************************************************************
--世界杯数据
--*******************************************************************************
LD_GUILD_WORLDCUP_GROUPTYPE         		= 0         --帮会世界杯组别信息
LD_GUILD_WORLDCUP_A_GUILD           		= 1         --帮会A
LD_GUILD_WORLDCUP_B_GUILD           		= 2         --帮会B
LD_GUILD_WORLDCUP_FLAG              		= 3         -- 
LD_GUILD_WORLDCUP_A_SOCRE           		= 4         --世界杯战场帮会A得分
LD_GUILD_WORLDCUP_B_SOCRE           		= 5         --世界杯战场帮会B得分
LD_GUILD_WORLDCUP_COUNT_ITME        		= 6         -- 
LD_GUILD_CONTEND_TURNNUMBER         		= 7         --帮会世界杯轮次号
LD_GUILD_WORLDCUP_FLAGOCCUPY                = 8         --战场旗帜被占领时间
LD_GUILD_WORLDCUP_STATE                     = 9         --比赛状态
LD_GUILD_WORLDCUP_VERSUS1                   = 10        --对阵1
LD_GUILD_WORLDCUP_VERSUS2                   = 11        --对阵2
LD_GUILD_WORLDCUP_VERSUS3                   = 12        --对阵3
LD_GUILD_WORLDCUP_VERSUS4                   = 13        --对阵4
LD_GUILD_WORLDCUP_VERSUS5                   = 14        --对阵5
LD_GUILD_WORLDCUP_VERSUS6                   = 15        --对阵6
LD_GUILD_WORLDCUP_VERSUS7                   = 16        --对阵7
LD_GUILD_WORLDCUP_VERSUS8                   = 17        --对阵8
LD_GUILD_WORLDCUP_A_GB_SCORE                = 18        --帮会A帮战积分
LD_GUILD_WORLDCUP_B_GB_SCORE                = 19        --帮会B帮战积分
LD_GUILD_WORLDCUP_SWITCH                    = 20        --帮会世界杯开关信息
LD_GUILD_WORLDCUP_A_COUNT                   = 21        --帮会世界杯战场中A帮会人数
LD_GUILD_WORLDCUP_B_COUNT                   = 22        --帮会世界杯战场中B帮会人数
LD_GUILD_WORLDCUP_CATCHFLAG_A               = 23        --世界杯战旗A夺取者Obj
LD_GUILD_WORLDCUP_CATCHFLAG_B               = 24        --世界杯战旗B夺取者Obj

--*******************************************************************************
--国王争夺战相关
--*******************************************************************************
--国王争夺战状态
STATE_KING_BATTLE_READY             		= 0		    --战斗场景准备好了
STATE_KING_BATTLE_SIGNUP            		= 1		    --开始报名
STATE_KING_BATTLE_SIGNUP_FINISH     		= 2	        --报名结束
STATE_KING_BATTLE_BATTLE            		= 3		    --开始战斗
STATE_KING_BATTLE_BATTLE_FINISH     		= 4	        --战斗结束

LD_KING_BATTLE_TYPE			        		= 0  		--帮会战玩法类型
LD_KING_BATTLE_SCRIPT			    		= 1  	    --场景脚本ID
LD_KING_BATTLE_LAST_TICK		    		= 2  		--上一次心跳时间
LD_KING_BATTLE_A_GUILD			    		= 3  		--A方帮会ID
LD_KING_BATTLE_B_GUILD			    		= 4  		--B方帮会ID
LD_KING_BATTLE_COUNTRYID            		= 5         --国家
LD_KING_BATTLE_COUNT_DOWN_STATE     		= 6  		--活动结束后的倒计时退出状态
LD_KING_BATTLE_COUNT_DOWN_TIME      		= 7 		--倒计时(单位秒)
LD_KING_BATTLE_COUNT_ITME           		= 8         --战场已过的时间

--*******************************************************************************
--跨服战场相关
--*******************************************************************************
MBATTLE_SIGNUP_SIGNTIME						= 1023		--报名签证时间

--*******************************************************************************
--配合函数IsPlayerMutexState使用（IsPlayerStateNormal判断玩家是否处于正常游戏状态）
--SetPlayerMutexState是设置相关状态
--*******************************************************************************
PLAYER_STATE_STALL                  		= 0         --摆摊
PLAYER_STATE_FUBEN              			= 1         --副本
PLAYER_STATE_GUILDBATTLEFIELDSCENE  		= 2         --战场
PLAYER_STATE_ARENASSCENE            		= 3         --擂台
PLAYER_STATE_CITSCENE               		= 4         --城市
PLAYER_STATE_PRISONSCENE            		= 5         --监狱
PLAYER_STATE_DIE                    		= 6         --死亡
PLAYER_STATE_BUS                    		= 7         --BUS
PLAYER_STATE_CRASHBOX               		= 8         --运镖
PLAYER_STATE_EXCHANGE               		= 9         --交易
PLAYER_STATE_MENTALGAME             		= 10        --答题
PLAYER_STATE_TEAMFOLLOW             		= 11        --组队跟随
PLAYER_STATE_AUTOPLAY               		= 12        --挂机
PLAYER_STATE_SUBTRAIN               		= 13        --代练
PLAYER_STATE_PRISON                 		= 14        --监狱
PLAYER_STATE_OPENBOX                		= 15        --开箱
PLAYER_STATE_PROTECTTIME            		= 16        --保护时间
PLAYER_STATE_KEYBORDMOVE            		= 17        --键盘移动
PLAYER_STATE_TIESAN                 		= 18        --铁人三项
PLAYER_STATE_READYFUBEN         			= 19        --进入副本状态
PLAYER_STATE_DUOQIBUFF						= 20		--夺旗任务有buff时的状态
PLAYER_STATE_TONGQUBUFF						= 21		--童趣任务有buff时的状态
PLAYER_STATE_PKMODE							= 22		--处于PK模式状态
PLAYER_STATE_FORBID_RIDE					= 23		--禁止骑马状态
PLAYER_STATE_WEDDING						= 24		--婚礼状态
PLAYER_STATE_ENJAIL							= 25		--囚禁状态
PLAYER_STATE_Award							= 26		--领奖状态
PLAYER_STATE_TransGold						= 27		--领取现金状态
PLAYER_STATE_DANCERY                		= 28
PLAYER_STATE_BLACKGOLD                      = 29        -- 黑金答题
	

--*******************************************************************************
--官职通用数据
--配合函数CountryGetOfficerGUID(nCountryID,cp)和IsSpecialCountryOffical(sceneId,selfId,cp)
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
--聊天频道和位置相关
--*******************************************************************************
CHAT_TYPE_NORMAL                    		= 0         --普通说话消息
CHAT_TYPE_TEAM                      		= 1	        --队聊消息
CHAT_TYPE_WORLD                     		= 2         --世界
CHAT_TYPE_USER                      		= 3         --私聊消息
CHAT_TYPE_SYSTEM                    		= 4         --系统消息
CHAT_TYPE_JIAZU                     		= 5         --家族消息
CHAT_TYPE_GUILD                     		= 6         --帮派消息
CHAT_TYPE_COUNTRY                   		= 7         --国家
CHAT_TYPE_SELF                      		= 8		    --仅客户端使用的消息
	
CHAT_MAIN_WINDOW                    		= 0		    --显示在主界面的聊天窗口内
CHAT_LEFTDOWN                       		= 1			--左下角个人的系统提示内
CHAT_RIGHTDOWN                      		= 2			--右下角系统的系统提示内
CHAT_PLUMB_SCROLL                   		= 3		    --垂直滚动提示内
CHAT_PLANE_SCROLL                   		= 4		    --水平滚动提示内
CHAT_MAIN_RIGHTDOWN                 		= 5	        --中间，右下角窗口内
CHAT_MIDDLE_BOTTOM_SCROLL           		= 6	        --中间下部的滚动框
CHAT_MIDDLE_BOTTOM_TEXT             		= 7	        --中间下部的文字框
CHAT_MIDDLE_ANIM                    		= 8			--中间的动画框

--*******************************************************************************
--定义Msg2player中最后一个变量
--*******************************************************************************
MSG2PLAYER_PARA                     		= 8
CHAT_MIDDLE_ANIM                    		= 8			--中间的动画框

--*******************************************************************************
--帮战相关的全局变量
--*******************************************************************************
GUILDBATTLE_TIMERID                 		= 7009
GUILDBATTLE_TIMERTYPE               		= 2

--*******************************************************************************
--循环任务mission param 的索引
--*******************************************************************************
MP_CIRCLE			                		= 6         --当前环数
MP_MAXCIRCLE	                    		= 7         --最大环数

--*******************************************************************************
--PK惩罚相关
--*******************************************************************************
PK_PUNISH_PRISON_SCENE_ID					= 12	--监狱的场景ID
PK_PUNISH_PRISON_TIME_BUF_ID				= 7201	--监狱倒计时BUF  7201: 1小时，7200: 10分钟 
PK_PUNISH_DIER_RED_NAME_DECRE_PK			= 1		--红名玩家被杀死，PK衰减值
PK_PUNISH_KILL_GREEN_NAME_INCRE_PK			= 50	--杀死绿名玩家PK增加值
PK_PUNISH_KILL_GREEN_CASHBOX_INCRE_PK		= 50	--杀死绿名玩家镖车PK增加值


--*******************************************************************************
--妖邪地宫场景id
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
--妖邪地宫human数量
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
--妖邪地宫objId数组
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

--妖邪地宫timer相关
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
--海贼相关
--*******************************************************************************
HZ_KILL_COUNT                   			= 0
HZ_MONSTER_OBJ                  			= {}
HZ_MONSTER_BOSSOBJ              			= -1
HZ_KILL_MONSTERBOSS             			= 0

--*******************************************************************************
--童趣交任务的玩家数量
--*******************************************************************************
TONGQU_COMMIT_NUM               			= 0

--*******************************************************************************
--云游采购交任务的玩家数量
--*******************************************************************************
YUNYOU_COMMIT_NUM               			= 0
                                			
                                			
GOLD_SPEND_TYPE_SHOP_BUY					= 0		--金币商店购物
GOLD_SPEND_TYPE_LOSS_RELIVE					= 1		--原地无损复活
                                			
SPOUSE_TASK                     			= {7540, 7541, 7542}
SPOUSE_TASK_POSITION_USE_ITEM				= 13080010
SPOUSE_NPC									= {140002,139818,139117 }
MAX_PRENTICE_NUM                			= 5
MASTER_PRENTICE_TIME_LIMIT      			= 72    --师徒解除关系后 重新建立关系的时间间隔（小时）

--*******************************************************************************
--乌龙辞典相关
--*******************************************************************************
WULONGCIDIAN_STEPIN_NAME					={}
WULONGCIDIAN_STEPIN_TIME					={}
WULONGCIDIAN_STEPIN_COUNT					=0
WULONGCIDIAN_AWARD_NAME						={}
WULONGCIDIAN_AWARD_TIME						={}
WULONGCIDIAN_AWARD_COUNT					=0
WULONGCIDIAN_AWARD_Draw						={}

--*******************************************************************************
--抢滩登陆场景id
--*******************************************************************************
QT_LOULAN_SCENE_ID 							= 90
QT_LAIYIN_SCENE_ID 							= 190
QT_KUNLUN_SCENE_ID 							= 290
QT_DUNHUANG_SCENE_ID 						= 390

--*******************************************************************************
--抢滩登陆human数量
--*******************************************************************************
QT_LOULAN_HUMAN_NUM 						= 0
QT_LAIYIN_HUMAN_NUM 						= 0
QT_KUNLUN_HUMAN_NUM 						= 0
QT_DUNHUANG_HUMAN_NUM 						= 0

--*******************************************************************************
--抢滩登陆objId数组
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
--抢滩登陆timer相关
--*******************************************************************************
QT_LOULAN_BROADCAST_NUM 					= 0
QT_LAIYIN_BROADCAST_NUM 					= 0
QT_KUNLUN_BROADCAST_NUM 					= 0
QT_DUNHUANG_BROADCAST_NUM 					= 0
                                			
QT_LOULAN_CREATE_ROUNDS 					= 0
QT_LAIYIN_CREATE_ROUNDS 					= 0
QT_KUNLUN_CREATE_ROUNDS 					= 0
QT_DUNHUANG_CREATE_ROUNDS 					= 0

HIDE_NAME 									= "蒙面人"

-- 国务预约最大次数
COUNTRY_PRECONTRACT_MAXTIMES                = 5

--*******************************************************************************
--排行榜相关
--*******************************************************************************
--排行榜数据，今日榜
WORLDCUP_TOPLIST_A							= 24	-- 世界杯A组
MERIT_TOPLIST								= 28	-- 帮会功德排行榜
AMATIVE_TOPLIST								= 30	-- 恋爱排行榜
SPOUSE_TOPLIST								= 32	-- 夫妻排行榜
MASTER_TOPLIST								= 34	-- 师傅排行榜
DATI_TOPLIST								= 36	-- 答题排行榜
TIEREN_TOPLIST								= 38	-- 铁人三项排行榜
WULONG_TOPLIST								= 40	-- 乌龙词典排行榜
BAOZANG_TOPLIST								= 42	-- 宝藏守卫排行榜
TULONG_TOPLIST								= 44	-- 屠龙排行榜排行榜
LABA_TOPLIST								= 46	-- 小喇叭排行榜
YANHUA_TOPLIST								= 48	-- 烟花排行榜
QIULONGDAO_TOPLIST							= 50	-- 囚龙岛排行榜
HESHIBI_TOPLIST								= 52	-- 和氏璧排行榜
CAISHENDIAN_TOPLIST							= 54	-- 财神殿排行榜
ZHUJIAZHUANG_TOPLIST						= 56	-- 祝家庄排行榜
LUNHUITAI_TOPLIST							= 58	-- 轮回台排行榜
JINGJIAOTANG_TOPLIST            			= 60    -- 景教堂（副本）排行榜
ZHANSHENMU_TOPLIST              			= 62    -- 战神墓（副本）排行榜
INDIANTEMPLE_TOPLIST            			= 64    -- 印度神庙（副本）排行榜

--排行榜数据，上周榜
LEVEL_TOP_LIST_BK							= 1		-- 上周，等级排行榜
MONEY_TOP_LIST_BK							= 3		-- 上周，金钱排行榜
HONOR_TOP_LIST_BK							= 5		-- 上周，荣誉排行榜
SHENGWANG_TOP_LIST_BK						= 7		-- 上周，声望排行榜
GP_TOP_LIST_BK								= 9		-- 上周，帮贡排行榜
HOT_VALUE_TOP_LIST_BK 						= 11	-- 上周，魅力排行榜
PK_TOP_LIST_BK								= 13	-- 上周，红名排行榜
KILL_COUNT_TOP_LIST_BK 						= 15	-- 上周，杀人排行榜
PVP2V2_TOPLIST_BK 							= 17	-- 上周，战场等级排行榜
PVP2V2_MARK_TOPLIST_BK 						= 19	-- 上周，战场积分排行榜
GUILD_TOP_LIST_BK 							= 21	-- 上周，帮会实力排行榜
GUILD_BATTLE_TOP_LIST_BK 					= 23	-- 上周，帮战积分排行榜
COUNTRY_TOP_LIST_BK							= 27	-- 上周，国家排行榜
                                			
MERIT_TOPLIST_BK							= 29	-- 上周，帮会功德排行榜
AMATIVE_TOPLIST_BK							= 31	-- 上周，恋爱排行榜
SPOUSE_TOPLIST_BK							= 33	-- 上周，夫妻排行榜
MASTER_TOPLIST_BK							= 35	-- 上周，师徒排行榜
DATI_TOPLIST_BK								= 37	-- 上周，答题排行榜
TIEREN_TOPLIST_BK							= 39	-- 上周，铁人排行榜
WULONG_TOPLIST_BK							= 41	-- 上周，乌龙辞典排行榜
BAOZANG_TOPLIST_BK							= 43	-- 上周，宝藏排行榜
TULONG_TOPLIST_BK							= 45	-- 上周，屠龙排行榜
LABA_TOPLIST_BK								= 47	-- 上周，小喇叭排行榜
YANHUA_TOPLIST_BK							= 49	-- 上周，烟花排行榜
QIULONGDAO_TOPLIST_BK						= 51	-- 上周，囚龙岛排行榜
HESHIBI_TOPLIST_BK							= 53	-- 上周，和氏璧排行榜
CAISHENDIAN_TOPLIST_BK						= 55	-- 上周，财神殿排行榜
ZHUJIAZHUANG_TOPLIST_BK						= 57	-- 上周，祝家庄排行榜
LUNHUITAI_TOPLIST_BK						= 59	-- 上周，轮回台排行榜
JINGJIAOTANG                    			= 61    -- 上周，景教堂（副本）排行榜
ZHANSHENMU                      			= 63    -- 上周，战神墓（副本）排行榜
INDIANTEMPLE                    			= 65    -- 上周，印度神庙（副本）排行榜




--*******************************************************************************
--单个场景中使用替身沙袋和高级替身沙袋创建的怪物数量
GLOBAL_CREATE_MONSTER_CNT_PER_SCENE  = {}
--******************************************************************************* 
--enum eCurrencyActType   和act_define.h头文件一致
eCurrencyAct_Unknow							= 0 	------/* 未知 */
eCurrencyAct_SaveBank						= 1 	----/* 银行存 */
eCurrencyAct_TakeMoneyAtBank				= 2 	----/* 银行取 */
eCurrencyAct_ExchangeIncome					= 3 	----/* 货币交易收入 */
eCurrencyAct_ExchangeOutcome				= 4 	----/* 货币交易支出 */
eCurrencyAct_PrivatelyExchangeIncome		= 5 	----/* 货币通过摊位交易收入 */
eCurrencyAct_PrivatelyExchangeOutcome		= 6 	----/* 货币通过摊位交易支出 */
eCurrencyAct_PrivatelyExchangeTaxOutcome	= 7 	----/* 货币通过摊位税收支出 */
eCurrencyAct_PlayerShopExchangeOutcome		= 8 	----/* 货币通过玩家商店交易货物支出 钱入玩家商店 */
eCurrencyAct_BuyPlayerShopOutcome			= 9 	----/* 货币通过交易玩家商店支出 */
eCurrencyAct_CreatePlayerShopOutcome		= 10 	----/* 货币通过创建玩家商店支出 */
eCurrencyAct_PlayerShopSave					= 11 	----/* 玩家商店存 */
eCurrencyAct_PlayerShowTake					= 12 	----/* 玩家商店取 */
eCurrencyAct_ShopCost						= 13 	----/* 商店购买支出 */
eCurrencyAct_ShopSell						= 14 	----/* 商店出售收入 */
eCurrencyAct_ShopRepair						= 15 	----/* 商店修理支出 */
eCurrencyAct_ShopSpecialRepair				= 16 	----/* 商店特修支出 */
eCurrencyAct_TrainAbilityCost				= 17 	----/* 学习生活技能支出 */
eCurrencyAct_TrainSkillCost					= 19 	----/* 学习战斗技能 */
eCurrencyAct_CallScriptCost					= 20 	----/* 脚本调用金钱消耗 */
eCurrencyAct_CallScriptIncome				= 21 	----/* 脚本调用金钱收入 */
eCurrencyAct_DieCost						= 22 	----/* 死亡金钱惩罚 */
eCurrencyAct_PetCost						= 23 	----/* 宠物金钱消耗 */
eCurrencyAct_CreateGuildCost				= 24 	----/* 创建帮会金钱消耗 */
eCurrencyAct_GuildLevelUpCost				= 25 	----/* 帮会升级消耗 */
eCurrencyAct_ChallengeKingCost				= 26 	----/* 挑战国王消耗 */
eCurrencyAct_ApplyActAsKing					= 27 	----/* 申请当国王 */
eCurrencyAct_GuildLevelUpFailedHandBack		= 28 	----/* 帮会升级失败还钱 */
eCurrencyAct_CreateGuildFailedHandBack		= 29 	----/* 创建帮会金钱失败还钱 */
eCurrencyAct_ApplyKingFailedHandBack		= 30 	----/* 申请国王失败还钱 */
eCurrencyAct_CountryDonate					= 31 	----/* 国家捐赠 */
eCurrencyAct_CountryDelate					= 32 	----/* 国家弹劾 */
eCurrencyAct_DrillCost						= 33 	----/* 加孔金钱消耗 */
eCurrencyAct_EquipLevelUpCost				= 34 	----/* 装备升级消耗金钱 */
eCurrencyAct_EquipRemouldCost				= 35 	----/* 装备改造金钱消耗 */
eCurrencyAct_FoundEquipCost					= 36 	----/* 装备打造金钱消耗 */
eCurrencyAct_EquipInlayCost					= 37 	----/* 装备镶嵌金钱消耗 */
eCurrencyAct_EquipBindCost					= 40 	----/* 装备绑定金钱消耗 */
eCurrencyAct_EquipChangeCard				= 41 	----/* 装备换牌金钱消耗 */
eCurrencyAct_GMmodify						= 42 	----/* GM 修改 */
eCurrencyAct_HorseMating					= 43 	----/* 马交配 */
eCurrencyAct_HorseFindingMating				= 44 	----/* 发布骑乘征友消耗 [6/16/2008 wuwenbin] */
eCurrencyAct_HorseRiseHappy					= 46 	----/* 增加马的快乐度 */
eCurrencyAct_MarryCost						= 47 	----/* 结婚消耗 */
eCurrencyAct_DivorceCost					= 48 	----/* 离婚消耗 */
eCurrencyAct_PresentWeddingRB				= 49 	----/* 参加婚礼的红包 */
eCurrencyAct_CashAccountToChar				= 50 	----/* 从帐户转到角色的现金 */
eCurrencyAct_ChatCost						= 51 	----/* 聊天消耗 */
eCurrencyAct_ProxyTrain						= 52 	----/* 代练消耗 */
eCurrencyAct_Exchange						= 53 	----/* 金钱兑换 */
eCurrencyAct_TakeCountryFinancingAtBank		= 54 	----/* 提取国家资金 */
eCurrencyAct_CashVendueCost					= 55 	----/* 现金商店寄售预扣 */
eCurrencyAct_CashVendueFailedHandBack		= 56 	----/* 现金商店寄售失败返回 */
eCurrencyAct_CashShopBuyCost				= 57 	----/* 现金商店购买预扣 */
eCurrencyAct_CashShopBuyFailedHandBack		= 58 	----/* 现金商店购买失败返回 */
eCurrencyAct_CashShopBuySuccessed			= 59 	----/* 现金商店购买成功加现金 */
eCurrencyAct_CashShopRetakeAtBank			= 60 	----/* 现金寄售后通过银行领取现金 */
eCurrencyAct_OnHandSillerShopRetakeAtBank	= 61 	----/* 现金寄售后通过银行领取现银 */
eCurrencyAct_EquipColorChange				= 62 	----/* 黄装升紫装花费 */
eCurrencyAct_EquipPurpleWashAttr			= 63 	----/* 紫装洗属性花费 */
eCurrencyAct_EquipGemLevelUpCost			= 64 	----/* 宝石升级消耗 */
eCurrencyAct_EquipGemCompoundCost			= 65 	----/* 宝石合成消耗 */
eCurrencyAct_EquipGemTeardown				= 66 	----/* 宝石拆卸花费 */
eCurrencyAct_EquipCopyCost					= 67 	----/* 装备复制花费 */
eCurrencyAct_ExchangeGoldIncome				= 68 	----/* 现金交易收入 */
eCurrencyAct_ExchangeGoldOutcome			= 69 	----/* 现金交易支出 */
eCurrencyAct_PrivatelyExchangeIncomeGold 	= 70 	----/* 货币通过摊位交易收入，现金 */
eCurrencyAct_PrivatelyExchangeOutcomeGold 	= 71  ----/* 货币通过摊位交易支出 */
eCurrencyAct_2v2MarkScriptAdd				= 72 	----/* 2v2战场积分增加 */
eCurrencyAct_2v2MarkScriptSub				= 73 	----/* 2v2战场积分减少 */
eCurrencyAct_PrivatelyExchangeTax			= 74 	----/* 摊位交易收税，现银 */
eCurrencyAct_PrivatelyExchangeTaxGold		= 75 	----/* 摊位交易收税，现金 */
eCurrencyAct_EquipRecallAddMoney			= 76 	----/* 装备回收得到的钱*/
eCurrencyAct_ScriptChangeGP					= 77 	----/* 脚本调用，帮贡改变 */
eCurrencyAct_ServerSyncGP					= 78 	----/* GL同步帮贡值 */
eCurrencyAct_CharGoldToStock				= 79 	----/* 股票账户充值扣除，现金 */
eCurrencyAct_CharSillerToStock				= 80 	----/* 股票账户充值扣除，现银 */
eCurrencyAct_CharGoldToStockFailed			= 81 	----/* 股票账户充值失败，回滚现金 */
eCurrencyAct_CharSillerToStockFailed		= 82 	----/* 股票账户充值失败，回滚现银 */
eCurrencyAct_StockGoldToChar				= 83 	----/* 股票账户现金转账到角色，增加现金 */
eCurrencyAct_StockSillerToChar				= 84 	----/* 股票账户现银转账到角色，增加现银 */
eCurrencyAct_ScriptChangeMerit				= 85 	----/* 脚本调用，改变帮会功德值 */
eCurrencyAct_GMChangeMerit					= 86 	----/* GM命令改变帮会功德值 */
eCurrencyAct_ServerSyncMerit				= 87 	----/* GL同步帮会功德值 */
eCurrencyAct_StockRegisterCostMoney			= 88 	----/* 股票系统开户收费，扣除现银 */
eCurrencyAct_StockRegisterFailedAddMoney	= 89 	----/* 股票系统开户失败，返回现银 */
eCurrencyAct_BlueAddCost					= 90 	----/* 蓝属性附加的花费 */
eCurrencyAct_StockAutoSaleCostGold			= 91 	----// 委托卖金: 扣除本金和手续费 现金
eCurrencyAct_StockAccDieAddMoney			= 92 	----// 股票账户消亡: 资金返回角色
eCurrencyAct_StockSysBuyGold				= 93 	----// 股票系统：系统工具购买现金
eCurrencyAct_EquipSwitch					= 94 	----// 装备转化花费
eCurrencyAct_MentalBuyItem					= 95 	----/* 答题购买道具 */
eCurrencyAct_GuildSkillLevelUpCost			= 96 	----/* 帮会天赋技能升级消耗 */
eCurrencyAct_BlueProduceCost      			= 97 		----/*橙装打造消耗*/
eCurrencyAct_ConstBindCost					= 98 		----/*星座铭刻*/

----/* 100->200为玩法中使用人民币的操作类型 */
eCurrencyAct_TestFee						= 100 	----/* 测试费 */
eCurrencyAct_Prize							= 101 	----/* 领奖 */
eCurrencyAct_ScriptChangeActivity			= 102 	----/* 脚本调用，改变帮会活跃度 */
----/* 300->400为脚本玩法等操作类型 */
----/* 花钱*/
eCurrencyAct_Relive							= 300  ----/*复活*/
eCurrencyAct_NormalMission					= 301  ----/*一般任务*/
eCurrencyAct_ChuanSong						= 302  ----/*传送*/
eCurrencyAct_Betray							= 303  ----/*叛国*/
eCurrencyAct_Levelup						= 304  ----/*升级*/
eCurrencyAct_Hunyin							= 305  ----/*婚姻*/
eCurrencyAct_Wuting							= 306  ----/*舞厅*/
eCurrencyAct_GoldDel						= 307  ----/* 现金清除道具清除现金 */
eCurrencyAct_SuperSale						= 308  ----/* 现金促销活动 */
eCurrencyAct_OfflineTrain					= 309  ----/* 离线代练 */
eCurrencyAct_SubscribeToGuild				= 310  ----/* 捐献帮会金钱 */

eCurrencyAct_Wulongyin_mojun				= 311  ----/* 五龙印兑换-天降魔君 */
eCurrencyAct_Wulongyin_wabao				= 312  ----/* 五龙印兑换-挖宝大作战 */
eCurrencyAct_Wulongyin						= 313  ----/* 五龙印兑换 */
eCurrencyAct_Wulongyin_huapi				= 314  ----/* 五龙印兑换-画皮 */
eCurrencyAct_Wulongyin_qiannv				= 315  ----/* 五龙印兑换-倩女幽魂 */
eCurrencyAct_Qiangjiang						= 316  ----/* 购买生命琼浆 */
eCurrencyAct_Shangxiang						= 317  ----/* 上香请愿 */
eCurrencyAct_Baoxiang						= 318  ----/* 疯狂宝箱 */
eCurrencyAct_Xingbing_loulan				= 319  ----/* 新兵速成 楼兰 */
eCurrencyAct_Xingbing_tianshan				= 320  ----/* 新兵速成 天山 */
eCurrencyAct_Xingbing_kunlun				= 321  ----/* 新兵速成 昆仑 */
eCurrencyAct_Xingbing_dunhuang				= 322  ----/* 新兵速成 敦煌 */
eCurrencyAct_Mojun							= 323  ----/* 天降魔君 */
eCurrencyAct_Baolong						= 324  ----/* 暴龙大作战 */
eCurrencyAct_GuildSuCheng					= 325  ----/* 帮会速成 */
eCurrencyAct_ITEM_OTHER_195					= 326  ----/* 新星麒麟大礼包 */
eCurrencyAct_ITEM_OTHER_197					= 327  ----/* 天尊麒麟金卡” */
--eCurrencyAct_NUM

