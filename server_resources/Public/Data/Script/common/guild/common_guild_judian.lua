
x300918_g_scriptId                      = 300918
x300918_g_TotalBattleTime               = 60 * 30     	--ս������ʱ��1800��        19:00-19:30

--�淨����
x300918_g_SceneName                     = { 
											{Name="yewai_caizhoucheng/yewai_caizhoucheng.scn",				Script=300918,MapId= 6,Toggle=1,Buf = {-1,9420,9421,9422,9423}},
											{Name="yewai_suiyecheng/yewai_suiyecheng.scn",					Script=300918,MapId= 9,Toggle=1,Buf = {-1,9400,9401,9402,9403}},
											{Name="yewai_bageda/yewai_bageda.scn",							Script=300918,MapId=13,Toggle=1,Buf = {-1,9416,9417,9418,9419}},
											{Name="yewai_jifugongguo/yewai_jifugongguo.scn",				Script=300918,MapId=18,Toggle=1,Buf = {-1,9412,9413,9414,9415}},
											{Name="yewai_shenshengluomadiguo/yewai_shenshengluomadiguo.scn",Script=300918,MapId=21,Toggle=1,Buf = {-1,9428,9429,9430,9431}},
											{Name="yewai_yelusaleng/yewai_yelusaleng.scn",					Script=300918,MapId=24,Toggle=1,Buf = {-1,-1,-1,-1,-1}},
											{Name="test/test.scn",											Script=300918,MapId=27,Toggle=0,Buf = {-1,-1,-1,-1,-1}},
											{Name="test/test.scn",											Script=300918,MapId=31,Toggle=0,Buf = {-1,-1,-1,-1,-1}},
											{Name="test/test.scn",											Script=300918,MapId=34,Toggle=0,Buf = {-1,-1,-1,-1,-1}},
										  }
x300918_g_BattleType					= 2

x300918_g_Laird_Signup                  = 300     --����
x300918_g_Laird_WaitBattle              = 301     --�����������ȴ�����ս��
x300918_g_Laird_BeginBattle             = 302     --��ʼ����ս��
x300918_g_Laird_EndBattle               = 303     --��������ս��

--�������
x300918_g_MaxScore                     = 49	     --��0��ʼ����
x300918_g_BonusTips                    = "#G�������#R%d#G�㾭��,#R%d#G���ṱ��,#R%d#G��ᾭ��!" --������ʾ
x300918_g_BonusTips1                   = "������˽���" --������ʾ


--���齱��
x300918_g_WinPrise                     = 1000*0.5*20              --��ʤ�����齱��ϵ����ֻ��ȼ��й�
x300918_g_LosePrise                    = 1000*0.1*20              --ʧ�ܷ����齱��ϵ����ֻ��ȼ��й�
x300918_g_DeucePrise                   = 1000*0.3*20              --սƽʱ���齱��ϵ����ֻ��ȼ��й�

--�ﹱ����
x300918_g_WinBangGong                  = 25
x300918_g_DeuceBangGong                = 20

--��ᾭ��
x300918_g_WinBangExp                   = 2
x300918_g_LoseBangExp                  = 2
x300918_g_DeuceBangExp                 = 2

x300918_g_Guild_Camp_A                 = 5
x300918_g_Guild_Camp_B                 = 6

x300918_g_Leader_Index                 = 5

x300918_g_Kick_Down                    = 8


--���״̬����
x300918_g_BattleState		   		   = {}
x300918_g_BattleEnterFlag	   		   = {}
x300918_g_GuildA					   = {}
x300918_g_GuildB					   = {}
x300918_g_CountryA					   = {}
x300918_g_CountryB					   = {}
x300918_g_LairdMapID				   = {}
x300918_g_HasLaird					   = {}
x300918_g_CountDownState			   = {}
x300918_g_CountDownTime				   = {}
x300918_g_CountTime				       = {}
x300918_g_GuildAidA					   = {}
x300918_g_GuildAidB					   = {}


--�ݵ������Ϣ
x300918_g_LairdSceneInfo					= {	--ս����ͼ��Ϣ
												{NpcGUID=123839,LairdScene=6, LairdSceneName="���ݳ�  ����ԭ��",  	Level=45, Flag0=500,Flag1=15000}, 
												{NpcGUID=123839,LairdScene=9, LairdSceneName="��Ҷ��  �����ǣ�",    Level=60, Flag0=501,Flag1=15001},
												{NpcGUID=123839,LairdScene=13,LairdSceneName="�͸��  �����ǣ�",	Level=70, Flag0=502,Flag1=15002},
												{NpcGUID=123839,LairdScene=18,LairdSceneName="����������˹����",  Level=80, Flag0=503,Flag1=15003},
												{NpcGUID=123839,LairdScene=21,LairdSceneName="����۹�����ŷ��",    Level=90, Flag0=504,Flag1=15004},
												{NpcGUID=123839,LairdScene=24,LairdSceneName="Ү·���䣨��������",	Level=100,Flag0=505,Flag1=15005},
												{NpcGUID=123839,LairdScene=27,LairdSceneName="����    ����季�",    Level=110,Flag0=506,Flag1=15006},
												{NpcGUID=123839,LairdScene=31,LairdSceneName="���    �����ģ�",  	Level=120,Flag0=507,Flag1=15007},
												{NpcGUID=123839,LairdScene=34,LairdSceneName="צ�۵�  ������",    Level=130,Flag0=508,Flag1=15008},
												
												{NpcGUID=126139,LairdScene=6, LairdSceneName="���ݳ�  ����ԭ��",    Level=45, Flag0=1500,Flag1=25000}, 
												{NpcGUID=126139,LairdScene=9, LairdSceneName="��Ҷ��  �����ǣ�",	Level=60, Flag0=1501,Flag1=25001},
												{NpcGUID=126139,LairdScene=13,LairdSceneName="�͸��  �����ǣ�",	Level=70, Flag0=1502,Flag1=25002},
												{NpcGUID=126139,LairdScene=18,LairdSceneName="����������˹����",  Level=80, Flag0=1503,Flag1=22003},
												{NpcGUID=126139,LairdScene=21,LairdSceneName="����۹�����ŷ��",    Level=90, Flag0=1504,Flag1=25004},
												{NpcGUID=126139,LairdScene=24,LairdSceneName="Ү·���䣨��������",  Level=100,Flag0=1505,Flag1=25005},
												{NpcGUID=126139,LairdScene=27,LairdSceneName="����    ����季�",    Level=110,Flag0=1506,Flag1=25006},
												{NpcGUID=126139,LairdScene=31,LairdSceneName="���    �����ģ�",    Level=120,Flag0=1507,Flag1=25007},
												{NpcGUID=126139,LairdScene=34,LairdSceneName="צ�۵�  ������",    Level=130,Flag0=1508,Flag1=25008},
												                                                                              
												{NpcGUID=129741,LairdScene=6, LairdSceneName="���ݳ�  ����ԭ��",   Level=45, Flag0=2500,Flag1=35000}, 
												{NpcGUID=129741,LairdScene=9, LairdSceneName="��Ҷ��  �����ǣ�",  Level=60, Flag0=2501,Flag1=35001},
												{NpcGUID=129741,LairdScene=13,LairdSceneName="�͸��  �����ǣ�",	Level=70, Flag0=2502,Flag1=35002},
												{NpcGUID=129741,LairdScene=18,LairdSceneName="����������˹����", Level=80, Flag0=2503,Flag1=33003},
												{NpcGUID=129741,LairdScene=21,LairdSceneName="����۹�����ŷ��",   Level=90, Flag0=2504,Flag1=35004},
												{NpcGUID=129741,LairdScene=24,LairdSceneName="Ү·���䣨��������", Level=100,Flag0=2505,Flag1=35005},
												{NpcGUID=129741,LairdScene=27,LairdSceneName="����    ����季�",   Level=110,Flag0=2506,Flag1=35006},
												{NpcGUID=129741,LairdScene=31,LairdSceneName="���    �����ģ�",   Level=120,Flag0=2507,Flag1=35007},
												{NpcGUID=129741,LairdScene=34,LairdSceneName="צ�۵�  ������",   Level=130,Flag0=2508,Flag1=35008},
												                                                                              
												{NpcGUID=132165,LairdScene=6, LairdSceneName="���ݳ�  ����ԭ��",    Level=45, Flag0=3500,Flag1=45000}, 
												{NpcGUID=132165,LairdScene=9, LairdSceneName="��Ҷ��  �����ǣ�",  Level=60, Flag0=3501,Flag1=45001},
												{NpcGUID=132165,LairdScene=13,LairdSceneName="�͸��  �����ǣ�",	Level=70, Flag0=3502,Flag1=45002},
												{NpcGUID=132165,LairdScene=18,LairdSceneName="����������˹����",  Level=80, Flag0=3503,Flag1=44003},
												{NpcGUID=132165,LairdScene=21,LairdSceneName="����۹�����ŷ��",    Level=90, Flag0=3504,Flag1=45004},
												{NpcGUID=132165,LairdScene=24,LairdSceneName="Ү·���䣨��������",  Level=100,Flag0=3505,Flag1=45005},
												{NpcGUID=132165,LairdScene=27,LairdSceneName="����    ����季�",    Level=110,Flag0=3506,Flag1=45006},
												{NpcGUID=132165,LairdScene=31,LairdSceneName="���    �����ģ�",    Level=120,Flag0=3507,Flag1=45007},
												{NpcGUID=132165,LairdScene=34,LairdSceneName="צ�۵�  ������",    Level=130,Flag0=3508,Flag1=45008},
											   }                                                                              
											   
											   
--��̬�赲����,��һ����
x300918_g_TempImpassable_Door1			=	{ 																		--ս�����ŷ�Χ
												{ Left = 19,Top = 89,Right =  232,Bottom = 168 },
											}
											
x300918_g_TempImpassable_Door1_Effect	=   { 32, 33 }																--ս������

--��̬�赲����,˫���ĵڶ�����,��Ҫ�ֿ�����
x300918_g_TempImpassable_Door2			=	{																		--�������ŵķ�Χ
												{Left =  46,Top = 60,Right =  54,Bottom = 68},
												{Left = 196,Top = 191,Right = 205,Bottom = 199},
											}
											
x300918_g_TempImpassable_Door2_Effect	=   { 34, 35 }																--������Ҫ������Ч
x300918_g_TempImpassable_Door2_State	=	{} 																		--0��ʾ������Ч,1��ʾ����Ч

--��������ش���
x300918_g_DoorGrowPointA				=	730																		--A��������
x300918_g_DoorGrowPointB				=	731																		--B��������

x300918_g_DoorGrowPointA_LairdState		=	{}																		--ռ��ʱ���߼�,�����з�ռ��ʱ��Ҫ��һ��ռ�쵹��ʱ״̬�Լ�ռ�쵹��ʱ����,�������᲻��Ҫ���߼�(�ݶ�)
x300918_g_DoorGrowPointB_LairdState		=	{}																		--ռ��ʱ���߼�,�����з�ռ��ʱ��Ҫ��һ��ռ�쵹��ʱ״̬�Լ�ռ�쵹��ʱ����,�������᲻��Ҫ���߼�(�ݶ�)

--BOSS���
x300918_g_BossA							=	{}																		--A��Boss�б�
x300918_g_BossB							=	{}																		--B��Boss�б�

--�Ʒ����
x300918_g_ScoreA						=	{}																		--A���Ʒ�
x300918_g_ScoreB						=	{}																		--B���Ʒ�
x300918_g_IntervalScoreA				=	{}																		--A���ڲ��Ʒ�
x300918_g_IntervalScoreB				=	{}																		--B���ڲ��Ʒ�

--��Ԯ���ݱ���
x300918_g_PlayerAidList					=	{}																		--��Ԯ�б�  ���ڱ�������ʹ�õ���Ԯ����

----------------------------------------------------------------------------------------------
--��ʼ������Ԯ�����б�
----------------------------------------------------------------------------------------------	
function x300918_InitPlayerAidList(sceneId)
	
	x300918_g_PlayerAidList[sceneId]		= {
												[6]  = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
												[9]  = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
												[13] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
												[18] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
												[21] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
												[24] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
												[27] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
												[31] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
												[34] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  -1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
											  }	
end

----------------------------------------------------------------------------------------------
--����ָ����Ԯ����A
----------------------------------------------------------------------------------------------	
function x300918_ResetPlayerAidListAByCustom(sceneId,nLairdMapId )
	
	if nLairdMapId ~= 6  and nLairdMapId ~= 9  and nLairdMapId ~= 13 and 
	   nLairdMapId ~= 18 and nLairdMapId ~= 21 and nLairdMapId ~= 24 and 
	   nLairdMapId ~= 27 and nLairdMapId ~= 31 and nLairdMapId ~= 34 then
		return
	end 

	for i = 1,10 do
		x300918_g_PlayerAidList[sceneId][nLairdMapId][i] = -1	
	end
end

----------------------------------------------------------------------------------------------
--����ָ����Ԯ����B
----------------------------------------------------------------------------------------------	
function x300918_ResetPlayerAidListBByCustom(sceneId,nLairdMapId )
	
	if nLairdMapId ~= 6  and nLairdMapId ~= 9  and nLairdMapId ~= 13 and 
	   nLairdMapId ~= 18 and nLairdMapId ~= 21 and nLairdMapId ~= 24 and 
	   nLairdMapId ~= 27 and nLairdMapId ~= 31 and nLairdMapId ~= 34 then
		return
	end 

	for i = 11,20 do
		x300918_g_PlayerAidList[sceneId][nLairdMapId][i] = -1	
	end
end

----------------------------------------------------------------------------------------------
--���ָ��ս������ԮA
----------------------------------------------------------------------------------------------	
function x300918_AddPlayerAidAByCustom(sceneId,nLairdMapid,GUID)
	
	if nLairdMapId ~= 6  and nLairdMapId ~= 9  and nLairdMapId ~= 13 and 
	   nLairdMapId ~= 18 and nLairdMapId ~= 21 and nLairdMapId ~= 24 and 
	   nLairdMapId ~= 27 and nLairdMapId ~= 31 and nLairdMapId ~= 34 then
		return
	end 

	for i = 1,10 do
		if x300918_g_PlayerAidList[sceneId][nLairdMapId][i] == -1 then
			x300918_g_PlayerAidList[sceneId][nLairdMapId][i] = GUID
			return
		end
	end
end

----------------------------------------------------------------------------------------------
--���ָ��ս������ԮB
----------------------------------------------------------------------------------------------	
function x300918_AddPlayerAidBByCustom(sceneId,nLairdMapid,GUID)
	
	if nLairdMapId ~= 6  and nLairdMapId ~= 9  and nLairdMapId ~= 13 and 
	   nLairdMapId ~= 18 and nLairdMapId ~= 21 and nLairdMapId ~= 24 and 
	   nLairdMapId ~= 27 and nLairdMapId ~= 31 and nLairdMapId ~= 34 then
		return
	end 

	for i = 11,20 do
		if x300918_g_PlayerAidList[sceneId][nLairdMapId][i] == -1 then
			x300918_g_PlayerAidList[sceneId][nLairdMapId][i] = GUID
			return
		end
	end
end

----------------------------------------------------------------------------------------------
--�Ƴ�ָ������Ԯ
----------------------------------------------------------------------------------------------	
function x300918_RemovePlayerAidByCustom(sceneId,nLairdMapId,GUID)
	
	if nLairdMapId ~= 6  and nLairdMapId ~= 9  and nLairdMapId ~= 13 and 
	   nLairdMapId ~= 18 and nLairdMapId ~= 21 and nLairdMapId ~= 24 and 
	   nLairdMapId ~= 27 and nLairdMapId ~= 31 and nLairdMapId ~= 34 then
		return
	end 
	
	for i,item in x300918_g_PlayerAidList[sceneId][nLairdMapId] do
		if item == GUID then
			item = -1
			return
		end
	end
end

----------------------------------------------------------------------------------------------
--�������Ƿ�����Ԯ�б���
----------------------------------------------------------------------------------------------	
function x300918_IsPlayerInPlayerAidList(sceneId,selfId)

	local nGUID = GetGUID(sceneId,selfId)
	for i,PlayerAidList in x300918_g_PlayerAidList[sceneId] do
		for j,PlayerAid in PlayerAidList do
			if PlayerAid == nGUID then
				return 1
			end
		end
	end

	return 0
end

----------------------------------------------------------------------------------------------
--ͬ����Ԯ����
----------------------------------------------------------------------------------------------
function x300918_ProcPlayerAidSyncLw(sceneId,nLairdMapId,nCampFlag,nGUID1,nGUID2,nGUID3,nGUID4,nGUID5 )
	
	if nLairdMapId ~= 6  and nLairdMapId ~= 9  and nLairdMapId ~= 13 and 
	   nLairdMapId ~= 18 and nLairdMapId ~= 21 and nLairdMapId ~= 24 and 
	   nLairdMapId ~= 27 and nLairdMapId ~= 31 and nLairdMapId ~= 34 then
		return
	end 
	
	if nCampFlag == 0 then
		
		x300918_g_PlayerAidList[sceneId][nLairdMapId][1] = nGUID1
		x300918_g_PlayerAidList[sceneId][nLairdMapId][2] = nGUID2
		x300918_g_PlayerAidList[sceneId][nLairdMapId][3] = nGUID3
		x300918_g_PlayerAidList[sceneId][nLairdMapId][4] = nGUID4
		x300918_g_PlayerAidList[sceneId][nLairdMapId][5] = nGUID5
	else
		
		x300918_g_PlayerAidList[sceneId][nLairdMapId][11] = nGUID1
		x300918_g_PlayerAidList[sceneId][nLairdMapId][12] = nGUID2
		x300918_g_PlayerAidList[sceneId][nLairdMapId][13] = nGUID3
		x300918_g_PlayerAidList[sceneId][nLairdMapId][14] = nGUID4
		x300918_g_PlayerAidList[sceneId][nLairdMapId][15] = nGUID5
		
	end
	
end

function x300918_ProcPlayerAidSyncHi(sceneId,nLairdMapId,nCampFlag,nGUID6,nGUID7,nGUID8,nGUID9,nGUID10 )
	
	if nLairdMapId ~= 6  and nLairdMapId ~= 9  and nLairdMapId ~= 13 and 
	   nLairdMapId ~= 18 and nLairdMapId ~= 21 and nLairdMapId ~= 24 and 
	   nLairdMapId ~= 27 and nLairdMapId ~= 31 and nLairdMapId ~= 34 then
		return
	end 
	
	if nCampFlag == 0 then
		
		x300918_g_PlayerAidList[sceneId][nLairdMapId][6]  = nGUID6
		x300918_g_PlayerAidList[sceneId][nLairdMapId][7]  = nGUID7
		x300918_g_PlayerAidList[sceneId][nLairdMapId][8]  = nGUID8
		x300918_g_PlayerAidList[sceneId][nLairdMapId][9]  = nGUID9
		x300918_g_PlayerAidList[sceneId][nLairdMapId][10] = nGUID10
	else
		
		x300918_g_PlayerAidList[sceneId][nLairdMapId][16] = nGUID6
		x300918_g_PlayerAidList[sceneId][nLairdMapId][17] = nGUID7
		x300918_g_PlayerAidList[sceneId][nLairdMapId][18] = nGUID8
		x300918_g_PlayerAidList[sceneId][nLairdMapId][19] = nGUID9
		x300918_g_PlayerAidList[sceneId][nLairdMapId][20] = nGUID10
		
	end
	
end

----------------------------------------------------------------------------------------------
--������ʼ������
----------------------------------------------------------------------------------------------	
function x300918_OnMapInit(sceneId)
	
	--���״̬����
	x300918_g_BattleState[sceneId]				   	= -1
	x300918_g_BattleEnterFlag[sceneId]			   	= 0
	x300918_g_GuildA[sceneId]					   	= -1
	x300918_g_GuildB[sceneId]					   	= -1
	x300918_g_CountryA[sceneId]					   	= -1
	x300918_g_CountryB[sceneId]					   	= -1
	x300918_g_LairdMapID[sceneId]				   	= -1
	x300918_g_HasLaird[sceneId]					   	= 0
	x300918_g_CountDownState[sceneId]			   	= -1
	x300918_g_CountDownTime[sceneId]			   	= -1
	x300918_g_CountTime[sceneId]				   	= -1
	
	x300918_g_GuildAidA[sceneId]					= {}
	x300918_g_GuildAidB[sceneId]					= {}
	
	x300918_g_TempImpassable_Door2_State[sceneId]	= {  0,  0 } 																--0��ʾ������Ч,1��ʾ����Ч
	
	x300918_g_DoorGrowPointA_LairdState[sceneId]	= { LairdCountDownState = 0,LairdCountDownTime = -1,LairdCamp = -1 }		--ռ��ʱ���߼�,�����з�ռ��ʱ��Ҫ��һ��ռ�쵹��ʱ״̬�Լ�ռ�쵹��ʱ����,�������᲻��Ҫ���߼�(�ݶ�)
	x300918_g_DoorGrowPointB_LairdState[sceneId]	= { LairdCountDownState = 0,LairdCountDownTime = -1,LairdCamp = -1 }		--ռ��ʱ���߼�,�����з�ռ��ʱ��Ҫ��һ��ռ�쵹��ʱ״̬�Լ�ռ�쵹��ʱ����,�������᲻��Ҫ���߼�(�ݶ�)

	
	--BOSS���
	x300918_g_BossA[sceneId]						=	nil																		--A��Boss�б�
	x300918_g_BossB[sceneId]						=	nil																		--B��Boss�б�
	
	--�Ʒ����
	x300918_g_ScoreA[sceneId]						=	0																		--A���Ʒ�
	x300918_g_ScoreB[sceneId]						=	0																		--B���Ʒ�
	x300918_g_IntervalScoreA[sceneId]				=	0																		--A���ڲ��Ʒ�
	x300918_g_IntervalScoreB[sceneId]				=	0																		--B���ڲ��Ʒ�
	
	--��ʼ����Ԯ����
	x300918_InitPlayerAidList(sceneId)
	
end

----------------------------------------------------------------------------------------------
--ͬ����ǰ�ݵ�ս����Ϣ
----------------------------------------------------------------------------------------------		
function x300918_ProcSyncLairdInfo(sceneId,nGuildId,nCountryId)
	
	local nObjId = 1
	if IsObjValid(sceneId,nObjId) ~=1 then
		return
	end
	
	if nCountryId < 0 or nCountryId > 3 then
		return
	end
	
	local nCamp = nCountryId + 16
	SetMonsterCamp(sceneId,nObjId,nCamp)
end

----------------------------------------------------------------------------------------------
--ȡ�õ�ǰ�ݵ�ս����԰����Ϣ
----------------------------------------------------------------------------------------------		
function x300918_GetMatchGuild(sceneId)
	return x300918_g_GuildA[sceneId],x300918_g_GuildB[sceneId]
end											   
										
										
function x300918_GetCountTime(sceneId)
	return x300918_g_CountTime[sceneId]
end
	   
----------------------------------------------------------------------------------------------
--ȡ�þݵ��ͼ����
----------------------------------------------------------------------------------------------											   
function x300918_GetLairdSceneCount(sceneId)
	return getn(x300918_g_LairdSceneInfo)
end

----------------------------------------------------------------------------------------------
--ȡ�þݵ�ĳ����ͼ��ϸ��Ϣ
----------------------------------------------------------------------------------------------		
function x300918_GetLairdSceneInfo(sceneId,nIndex)

	if nIndex < 1 or nIndex > getn(x300918_g_LairdSceneInfo) then
		return
	end
	
	local item = x300918_g_LairdSceneInfo[nIndex]
	return item.NpcGUID,item.LairdScene,item.LairdSceneName,item.Level,item.Flag0,item.Flag1
end

----------------------------------------------------------------------------------------------
--ȡ�þݵ��ͼ����
----------------------------------------------------------------------------------------------
function x300918_GetLairdSceneInfo_Name(nLairdMapId)
	
	local strName = ""
	for i,item in x300918_g_LairdSceneInfo do
		if item.LairdScene == nLairdMapId then
			strName = item.LairdSceneName
			break
		end
	end
	
	return strName
	
end


----------------------------------------------------------------------------------------------
--ȡ��ս��״̬
----------------------------------------------------------------------------------------------
function x300918_GetBattleState(sceneId)
	
	return x300918_g_BattleState[sceneId]
	
end

----------------------------------------------------------------------------------------------
--ȡ��ս��������
----------------------------------------------------------------------------------------------
function x300918_GetBattleEnterSceneFlag(sceneId)
	return x300918_g_BattleEnterFlag[sceneId];
end

----------------------------------------------------------------------------------------------
--���ý�ս�����
----------------------------------------------------------------------------------------------
function x300918_SetBattleEnterSceneFlag(sceneId,nEnterSceneFlag)
	x300918_g_BattleEnterFlag[sceneId] = nEnterSceneFlag
end

----------------------------------------------------------------------------------------------
--����Ƿ�������ս��������������Ƿ���0���Ƿ���1
----------------------------------------------------------------------------------------------
function x300918_GetLairdBattleSceneScript( sceneId )

    local name = GetBattleSceneName(sceneId)
    for i,item in x300918_g_SceneName do
        if name == item.Name and item.Toggle == 1 then
            return item.Script
        end
    end

    return 0
end

----------------------------------------------------------------------------------------------
--����Ƿ���A��Ԯ
----------------------------------------------------------------------------------------------
function x300918_IsPlayerAidA(sceneId,selfId)
	
	local nGUID = GetGUID(sceneId,selfId)
	
	for i,item in x300918_g_GuildAidA[sceneId] do
		if item == nGUID then
			return 1
		end
	end
	
	
	return 0
	
end

----------------------------------------------------------------------------------------------
--����Ƿ���B��Ԯ
----------------------------------------------------------------------------------------------
function x300918_IsPlayerAidB(sceneId,selfId)
	
	local nGUID = GetGUID(sceneId,selfId)
	
	for i,item in x300918_g_GuildAidB[sceneId] do
		if item == nGUID then
			return 1
		end
	end
	
	
	return 0
	
end



----------------------------------------------------------------------------------------------
--Ĭ�ϴ���
----------------------------------------------------------------------------------------------
function x300918_ProcEventEntry( sceneId, selfId, targetId, MissionId,nExtId )
	BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "\t��л��Ϊ���ͼ�����������Ĺ��ף�" )
    	CallScriptFunction(300950,"CallbackEnumEvent", sceneId, selfId, targetId, 0)
    	CallScriptFunction(300951,"CallbackEnumEvent", sceneId, selfId, targetId, 0)
    	CallScriptFunction(300952,"CallbackEnumEvent", sceneId, selfId, targetId, 0)
		CallScriptFunction(300953,"CallbackEnumEvent", sceneId, selfId, targetId, 0)
		CallScriptFunction(300954,"CallbackEnumEvent", sceneId, selfId, targetId, 0)
		CallScriptFunction(300955,"CallbackEnumEvent", sceneId, selfId, targetId, 0)
		CallScriptFunction(300956,"CallbackEnumEvent", sceneId, selfId, targetId, 0)
		CallScriptFunction(300957,"CallbackEnumEvent", sceneId, selfId, targetId, 0)
		CallScriptFunction(300958,"CallbackEnumEvent", sceneId, selfId, targetId, 0)
		CallScriptFunction(302506,"CallbackEnumEvent", sceneId, selfId, targetId, 0)
    	
    EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end


----------------------------------------------------------------------------------------------
--�����
----------------------------------------------------------------------------------------------
function x300918_OnBattleStateEvent( sceneId, state  )

	--�Ϸ�����
    if GetMergeDBToggle() == 1 then
        return
    end
    
  --�������ݿ⿪��
	local UpdateDBflag = GetUpdateDBBeforeToggle()
	if UpdateDBflag==1 then
		return
	end
    
    --���Է�����
    --if GetTestServerToggle() == 0 then
    --    return
    --end

    --ս���Լ��Ŀ���
    if GetBattleSceneToggle( BATTLESCENE_TYPE_LAIRDGBATTLELITE ) == 0 then
        return
    end


	local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
	if  nScriptId == 0 then

		-----------------------------------------------------------------------------------
		--������������ͨ����
		-----------------------------------------------------------------------------------
		
        if state == x300918_g_Laird_Signup then

            --���״̬�Ƿ��Ѿ��ù�
            if x300918_g_BattleState[sceneId] ~= x300918_g_Laird_Signup then
                local msg = format("LBL:x300918_g_Laird_Signup,SceneId=%d ",sceneId  )
                WriteLog(1,msg)
            end

            
            x300918_g_BattleState[sceneId] = x300918_g_Laird_Signup
            
        elseif state == x300918_g_Laird_WaitBattle then

            --���״̬�Ƿ��Ѿ��ù�
            if x300918_g_BattleState[sceneId] ~= x300918_g_Laird_WaitBattle then
                local msg = format("LBL:x300918_g_Laird_WaitBattle,SceneId=%d ",sceneId )
                WriteLog(1,msg)
            end
            
            --��������
            x300918_g_BattleState[sceneId] = x300918_g_Laird_WaitBattle
            
        elseif state == x300918_g_Laird_BeginBattle then

            --���״̬�Ƿ��Ѿ��ù�
            if x300918_g_BattleState[sceneId] == x300918_g_Laird_BeginBattle then
                local msg = format("LBL:x300918_g_Laird_BeginBattle,SceneId=%d ",sceneId )
                WriteLog(1,msg)
            end
            
            --��ʼ����ս��
            x300918_g_BattleState[sceneId] = x300918_g_Laird_BeginBattle
            x300918_g_BattleEnterFlag[sceneId] = 1

        elseif state == x300918_g_Laird_EndBattle then
            
            --����ս������
            x300918_g_BattleState[sceneId] = x300918_g_Laird_EndBattle

            local msg = format("LBL:x300918_g_Laird_EndBattle, SceneId=%d",sceneId )
            WriteLog(1,msg)

        end

	elseif nScriptId == 300918 then
	
		-----------------------------------------------------------------------------------
		--��������������ս������
		-----------------------------------------------------------------------------------

        if state == x300918_g_Laird_Signup then

            --���״̬�Ƿ��Ѿ��ù�
            if x300918_g_BattleState[sceneId] ~= x300918_g_Laird_Signup then
                
                --��¼��־
                local msg = format("LBL:x300918_g_Laird_Signup,SceneId=%d,2 ",sceneId  )
                WriteLog(1,msg)

            end

            --GameBattleSceneAskInit( sceneId,2 )                                             --��GLServerע��һ��
            x300918_g_BattleState[sceneId] = x300918_g_Laird_Signup		                      	--����״̬

        elseif state == x300918_g_Laird_WaitBattle then

            --���״̬�Ƿ��Ѿ��ù�
            if x300918_g_BattleState[sceneId] ~= x300918_g_Laird_WaitBattle then
                local msg = format("LBL:x300918_g_Laird_WaitBattle,SceneId=%d,2",sceneId )
                WriteLog(1,msg)
            end

            --���û�������
            x300918_g_BattleState[sceneId] = x300918_g_Laird_WaitBattle
            
        elseif state == x300918_g_Laird_BeginBattle then

            --���״̬�Ƿ��Ѿ��ù�
            if x300918_g_BattleState[sceneId] ~= x300918_g_Laird_BeginBattle then
                local msg = format("LBL:x300918_g_Laird_BeginBattle,SceneId=%d,2",sceneId )
                WriteLog(1,msg)
            end

            --���û�������            
            x300918_g_BattleState[sceneId] = x300918_g_Laird_BeginBattle
            x300918_OnBattleSceneReady( sceneId,( x300918_g_TotalBattleTime) )

        elseif state == x300918_g_Laird_EndBattle then

            if x300918_g_BattleState[sceneId] > x300918_g_Laird_BeginBattle or x300918_g_BattleState[sceneId] < x300918_g_Laird_Signup then
                
                local msg = format("LBL:x300918_g_Laird_EndBattle,Result:nState > x300918_g_Laird_BeginBattle or nState < x300918_g_Laird_Signup  SceneId=%d,state=%d,2",sceneId, state )
                WriteLog(1,msg)

                --�����淨�Ľű��Ĳ�ͬ��������س�ʼ���ص�
                x300918_OnBattleSceneClose( sceneId )

                local msg = format("LBL:x300918_g_Laird_EndBattle, SceneId=%d,2",sceneId )
                WriteLog(1,msg)
                return
            end

            --����״̬�������
    		x300918_g_BattleState[sceneId] = x300918_g_Laird_EndBattle 
            x300918_OnBattleSceneClose( sceneId )

            local msg = format("LBL:x300918_g_Laird_EndBattle, SceneId=%d,3",sceneId )
            WriteLog(1,msg)
        end
	end
end

----------------------------------------------------------------------------------------------
--����ս��������
----------------------------------------------------------------------------------------------
function x300918_ProcTiming( sceneId,uTime )

    --����Ƿ�������ս�������б���������������������ǣ��򲻴���
    local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end
       
    x300918_OnBattleSceneTimer( sceneId, uTime)
end


----------------------------------------------------------------------------------------------
--��ҽ����¼�
----------------------------------------------------------------------------------------------
function x300918_OnPlayerEnter( sceneId, playerId )

    --����Ƿ�������ս�������б���������������������ǣ��򲻴���
    local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

    local status = x300918_g_BattleState[sceneId]
    if status ~= x300918_g_Laird_BeginBattle then
    
        --x300918_SetAllPlayerNeedKick( sceneId )
        
        --local msg = format("LBL:x300918_OnBattlePlayerEnter Kick,Player,SceneId=%d,playerId=%d status=%d",sceneId,playerId,status )
        --WriteLog(1,msg)
        return
    end


    --ȡ�ð��A�Ͱ��B
    local nGuildA = x300918_g_GuildA[sceneId]
    local nGuildB = x300918_g_GuildB[sceneId]

    local nGuildId = GetGuildID( sceneId,playerId )

    --������ս���е���Ӫ����
    local nSendCCamp = -1
    if nGuildId == nGuildA or x300918_IsPlayerAidA(sceneId,playerId) == 1 then
        nSendCCamp = 0
    elseif nGuildId == nGuildB or x300918_IsPlayerAidB(sceneId,playerId) == 1 then
        nSendCCamp = 1
    else
--        SetPlayerRuntimeData( sceneId,playerId,RD_BATTLE_SCENE_KICK_DOWN ,x300918_g_Kick_Down) 
--        --��¼��־
--        local msg = format("LBL:x300918_OnBattlePlayerEnter Kick 2,Player,SceneId=%d,playerId=%d",sceneId,playerId )
--        WriteLog(1,msg)
        return

    end

    --�������趨
    --GameBattleSetDisable(sceneId, playerId, 0, nSendCCamp,2 )

    local strGuildA = GetGuildName( nGuildA )
    local strGuildB = GetGuildName( nGuildB )

    --GameBattleSendBattleInfo( sceneId, playerId, strGuildA, strGuildB,2 )
    --GameBattleSyncScoreInfo( sceneId, playerId, x300918_g_ScoreA[sceneId], x300918_g_ScoreB[sceneId], 2 )

    --��ҽ���ս���������֮ǰ������
    SetPlayerRuntimeData(sceneId,playerId,RD_KING_BATTLE_BEKILLED,0)

    --������Ӫ
    if nGuildId == nGuildA or x300918_IsPlayerAidA(sceneId,playerId) == 1 then
        --SetCurCamp(sceneId,playerId,x300918_g_Guild_Camp_A)
        --SetPos(sceneId,playerId, 66,78)

    elseif nGuildId == nGuildB or x300918_IsPlayerAidB(sceneId,playerId) == 1 then
        --SetCurCamp(sceneId,playerId,x300918_g_Guild_Camp_B)
        --SetPos(sceneId,playerId,185,182)    	
    end

    SetPlayerRuntimeData( sceneId,playerId,RD_BATTLE_SCENE_KICK_DOWN,-1)

    --�����ԭ�ȵĳ������б���
    local scenePre = GetPlayerRuntimeData(sceneId,playerId,RD_HUMAN_SCENE_PRE ) - 1
    if scenePre >= 0 then
        
        local CurX = GetPlayerRuntimeData(sceneId,playerId,RD_HUMAN_POSX_PRE)
        local CurZ = GetPlayerRuntimeData(sceneId,playerId,RD_HUMAN_POSZ_PRE)

        SetPlayerBakSceneInfo(sceneId,playerId,scenePre,CurX,CurZ)

        SetPlayerRuntimeData(sceneId,playerId,RD_HUMAN_SCENE_PRE,0)
        SetPlayerRuntimeData(sceneId,playerId,RD_HUMAN_POSX_PRE,0)
        SetPlayerRuntimeData(sceneId,playerId,RD_HUMAN_POSZ_PRE,0)

    end
--    
--    --������1�赲
--	x300918_SetTempImpassable_Door1_Effect(sceneId,playerId)
--	
--	--������2�赲
--	x300918_SetTempImpassable_Door2_Effect(sceneId,playerId)
	
end

----------------------------------------------------------------------------------------------
--����뿪�¼�
----------------------------------------------------------------------------------------------
function x300918_OnPlayerLeave( sceneId, playerId )

    --����Ƿ�������ս�������б���������������������ǣ��򲻴���
    local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

    local nCountryId = GetCurCountry(sceneId,playerId )
    SetCurCamp( sceneId,playerId,nCountryId )

    GameBattleSetDisable(sceneId, playerId,1,-1,2)
end

----------------------------------------------------------------------------------------------
--����˻�
----------------------------------------------------------------------------------------------
function x300918_OnPlayerLeaveGuild( sceneId,selfId )
--
--    --����Ƿ�������ս�������б���������������������ǣ��򲻴���
--    local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
--    if  nScriptId == 0 then
--        return
--    end
--    
--    x300918_LairdBattleKickPlayer( sceneId,selfId )
--    GameBattleSetDisable(sceneId, selfId,1,-1,2)

end

----------------------------------------------------------------------------------------------
--��������ս����������Ϣ
----------------------------------------------------------------------------------------------
function x300918_OnSetLairdBattleMatchInfo( sceneId,nGuildA,nGuildB,nCountryA,nCountryB,nLairdMapId,nHasLaird )

    --����Ƿ�������ս�������б���������������������ǣ��򲻴���
    local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

	--����д����.�벻Ҫ��
    x300918_g_GuildA[sceneId] = nGuildB 
    x300918_g_GuildB[sceneId] = nGuildA
    x300918_g_LairdMapID[sceneId] = nLairdMapId
    x300918_g_HasLaird[sceneId] = nHasLaird
    
    x300918_g_CountryA[sceneId] = nCountryB 
    x300918_g_CountryB[sceneId] = nCountryA

    --debug
    local a = x300918_g_GuildA[sceneId]
    local b = x300918_g_GuildB[sceneId]
    local ca = x300918_g_CountryA[sceneId]
    local cb = x300918_g_CountryB[sceneId]
    local c = x300918_g_LairdMapID[sceneId]
    local d = x300918_g_HasLaird[sceneId]

    local msg = format( "LBL:LAIRD_BATTLE_MATCHINFO:sceneId=%d,A=%d,B=%d,CA=%d,CB=%d,LairdMap=%d,HasLaird=%d", sceneId, a, b,ca,cb, c, d )
    WriteLog(1,msg)
end


----------------------------------------------------------------------------------------------
--��������ս����������Ϣ
----------------------------------------------------------------------------------------------
function x300918_OnSetLairdBattleMatchInfo_PlayerAid0( sceneId,guildtype,GUID0,GUID1,GUID2,GUID3,GUID4)

    --����Ƿ�������ս�������б���������������������ǣ��򲻴���
    local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

	--����д����.�벻Ҫ��
	if guildtype == 0 then
	    x300918_g_GuildAidB[sceneId][1] = GUID0 
	    x300918_g_GuildAidB[sceneId][2] = GUID1
	    x300918_g_GuildAidB[sceneId][3] = GUID2
	    x300918_g_GuildAidB[sceneId][4] = GUID3
	    x300918_g_GuildAidB[sceneId][5] = GUID4
	else
		x300918_g_GuildAidA[sceneId][1] = GUID0 
	    x300918_g_GuildAidA[sceneId][2] = GUID1
	    x300918_g_GuildAidA[sceneId][3] = GUID2
	    x300918_g_GuildAidA[sceneId][4] = GUID3
	    x300918_g_GuildAidA[sceneId][5] = GUID4
	end
    
end


----------------------------------------------------------------------------------------------
--��������ս����������Ϣ
----------------------------------------------------------------------------------------------
function x300918_OnSetLairdBattleMatchInfo_PlayerAid1( sceneId,guildtype,GUID5,GUID6,GUID7,GUID8,GUID9)

    --����Ƿ�������ս�������б���������������������ǣ��򲻴���
    local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

	--����д����.�벻Ҫ��
	if guildtype == 0 then
	    x300918_g_GuildAidB[sceneId][6]  = GUID5
	    x300918_g_GuildAidB[sceneId][7]  = GUID6
	    x300918_g_GuildAidB[sceneId][8]  = GUID7
	    x300918_g_GuildAidB[sceneId][9]  = GUID8
	    x300918_g_GuildAidB[sceneId][10] = GUID9
	else
		x300918_g_GuildAidA[sceneId][6]  = GUID5 
	    x300918_g_GuildAidA[sceneId][7]  = GUID6
	    x300918_g_GuildAidA[sceneId][8]  = GUID7
	    x300918_g_GuildAidA[sceneId][9]  = GUID8
	    x300918_g_GuildAidA[sceneId][10] = GUID9
	end
end

----------------------------------------------------------------------------------------------
--�����������
----------------------------------------------------------------------------------------------
function x300918_OnPlayerNewConnectEnter( sceneId, selfId )

    --����Ƿ�������ս�������б���������������������ǣ��򲻴���
    local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

    local BattleSceneFlag = GetPlayerRuntimeData(sceneId,selfId,RD_BATTLESCENE_ENTER_FLAG)
    if BattleSceneFlag == 0 then

        --�����ߵ����,����Kick����ʱ��׼���ߵ�
        SetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN,x300918_g_Kick_Down)

        local name = GetName(sceneId,selfId)
        if name == nil then
            name = "ErrorName"
        end
        local msg = format( "LBL:x300918_OnPlayerNewConnectEnter 0,need kick,sceneId=%d,selfId=%d,name=%s", sceneId, selfId, name )
        WriteLog(1,msg)

    else

        --�ӱ�һ��������ת���������
        --ͬ������������,��ʱ��RD_BATTLESCENE_ENTER_FLAGֵĿǰ�޷���0��
        --ֻ��������뿪ս��������ʱ��������ǲ�ͬ��������Ŀ����������
        local name = GetName(sceneId,selfId)
        if name == nil then
            name = "ErrorName"
        end
        local msg = format( "LBL:x300918_OnPlayerNewConnectEnter 1,sceneId=%d,selfId=%d,name=%s", sceneId, selfId, name )
        WriteLog(1,msg)

        SetPlayerRuntimeData(sceneId,selfId,RD_BATTLESCENE_ENTER_FLAG,0)

    end
end

----------------------------------------------------------------------------------------------
--�����������
----------------------------------------------------------------------------------------------
function x300918_OnPlayerDie( sceneId, selfId, killerId  )

    --����Ƿ�������ս�������б���������������������ǣ��򲻴���
    local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end
    
    --���״̬�����û�п������򲻴���
    local status = x300918_g_BattleState[sceneId]
    if status ~= x300918_g_Laird_BeginBattle then
        return
    end
    
    --���˵���ս��˫�������
    local nGuildId = GetGuildID(sceneId,selfId)
    if nGuildId ~= x300918_g_GuildA[sceneId] and x300918_IsPlayerAidA(sceneId,selfId) ~= 1 and
       nGuildId ~= x300918_g_GuildB[sceneId] and x300918_IsPlayerAidB(sceneId,selfId) ~= 1 then
        return
    end
    
    --A����������,B���ӷ�
    if GetCurCamp(sceneId,selfId) == x300918_g_Guild_Camp_A then
    	x300918_g_ScoreB[sceneId] = x300918_g_ScoreB[sceneId] + 1
    end
    
    --B����������,A���ӷ�
    if GetCurCamp(sceneId,selfId) == x300918_g_Guild_Camp_B then
    	x300918_g_ScoreA[sceneId] = x300918_g_ScoreA[sceneId] + 1
    end
    
    --���ֱ仯
    x300918_LairdSyncGuildScore(sceneId)

    --��¼��ɱ����
    local nBeKilled = GetPlayerRuntimeData(sceneId,selfId,RD_KING_BATTLE_BEKILLED ) + 1
    SetPlayerRuntimeData(sceneId,selfId,RD_KING_BATTLE_BEKILLED,nBeKilled)

    --�����ɱ����
    --local ObjType = GetObjType(sceneId, killerId)

    --ɱ�������߲�������ң���ɱ��������6�����ڣ�����6�Σ�
--    if IsPlayerStateNormal( sceneId,killerId ) == 1 and ObjType == 1 and nBeKilled <= 6 then
--
--        AddGuildUserPoint(sceneId,killerId,10)
--
--        local msg = "�������10��ﹱ"
--        local name = GetName(sceneId,killerId )
--
--        LuaScenceM2Player(sceneId, killerId, msg, name , 2,1)
--    
--    end

    --�������Σ�������ʾ
    --if nBeKilled <= 6 then 

        local str = format("#G%s�ڡ����ҡ��������ս�б�ɱ��",GetName(sceneId,selfId ) )
        LuaThisScenceM2Wrold(sceneId,str,3,1)
        LuaThisScenceM2Wrold(sceneId,str,2,1)
    --end

    --�����Σ�����ʾ
--    if nBeKilled == 6 then
--
--        local nCountryId = GetCurCountry( sceneId,selfId)
--
--        local str = format("#G%s�ڡ����ҡ�����ս���У��������������������뿪ս����",GetName(sceneId,selfId ) )
--        LuaAllScenceM2Country(sceneId,str,nCountryId,3,1)
--        LuaAllScenceM2Country(sceneId,str,nCountryId,2,1)
--
--        --���뵹��ʱ��������ֹһֱ��ɱ�������˳�ս��
--        local KickDown = GetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ) 
--        if KickDown <= 0 or KickDown > 4 then
--            SetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ,4) 
--        end
--    end

end

-------------------------------------------------------------------------------
--���״̬�Ƿ�����
-------------------------------------------------------------------------------
function x300918_CheckPlayerState( sceneId,selfId )
    

    local state
    local ErrorMsg

    state = IsPlayerStateNormal(sceneId,selfId )
    if state == 0 then
        ErrorMsg = "״̬�쳣"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_MENTALGAME )
    if state == 1 then
        ErrorMsg = "���ڴ���״̬�����ܽ���ս��"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_STALL )
    if state == 1 then
        ErrorMsg = "���ڰ�̯״̬�����ܽ���ս��"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_DIE )
    if state == 1 then
        ErrorMsg = "��������״̬�����ܽ���ս��"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_CRASHBOX )
    if state == 1 then
        ErrorMsg = "��������״̬�����ܽ���ս��"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_AUTOPLAY )
    if state == 1 then
        ErrorMsg = "���ڹһ�״̬�����ܽ���ս��"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_SUBTRAIN )
    if state == 1 then
        ErrorMsg = "���ڴ���״̬�����ܽ���ս��"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_BUS )
    if state == 1 then
        ErrorMsg = "����BUS״̬�����ܽ���ս��"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_PKMODE )
    if state == 1 then
        ErrorMsg = "PKֵ���߻��ڿ�ģʽ�����ܽ���ս��"
        return 1,ErrorMsg
    end

    return 0

end

-------------------------------------------------------------------------------
--����ս����ش��ͽű�
-------------------------------------------------------------------------------
function x300918_OnLairdBattleChangeScene( sceneId,selfId,newSceneID,Flag )
    

    --����ڼ��������Ա�����
	if sceneId == PK_PUNISH_PRISON_SCENE_ID then
		BeginQuestEvent(sceneId)
		local strText = "�����ﻹ����ʵ,����,û�š�"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return
	end

    local PosX = 100
    local PosZ = 100


    if sceneId == newSceneID then
        
        if Flag == 0 then
		    SetPos( sceneId , selfId , 68 ,76 )
        else
            SetPos( sceneId , selfId , 182,181 )
        end
	else
        
        --���״̬
        local state,msg = x300918_CheckPlayerState( sceneId,selfId )
        if state == 1 then
            
            BeginQuestEvent(sceneId)
            AddQuestText( sceneId, msg );
            EndQuestEvent(sceneId)
            DispatchQuestTips(sceneId,selfId)
            return
        end

        --��¼һ��RuntimeData
        local nCurX,nCurZ = GetWorldPos( sceneId,selfId )
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_SCENE_PRE,sceneId + 1)
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSX_PRE,nCurX)
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSZ_PRE,nCurZ)
        SetPlayerRuntimeData(sceneId,selfId,RD_BATTLESCENE_ENTER_FLAG,1)

		NewWorld( sceneId , selfId , newSceneID , PosX , PosZ,300918 )
	end
end

function x300918_DoPlayerRelive( sceneId, selfId )
	
	if GetHp(sceneId,selfId) > 0 then
		return
	end
	
    RestoreHp(sceneId, selfId,0)
	RestoreRage(sceneId, selfId,100)
	ClearMutexState(sceneId, selfId, 6)
	SendReliveResult(sceneId, selfId,1)	

    --�������״̬
    RelivePlayerNM(sceneId,selfId,2)	
    SetPlayerMutexState(sceneId,selfId,PLAYER_STATE_DIE,0)
end

--����ս������
function x300918_OnPlayerRelive( sceneId, selfId )

--    --����Ƿ�������ս��
--    local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
--    if nScriptId == 0 then
--        return
--    end
--    
--    --������������Ƿ񳬹�6��
--    local nBeKilled = GetPlayerRuntimeData(sceneId,selfId,RD_KING_BATTLE_BEKILLED )
--    if nBeKilled >= 6 then
--        
--        --����һ�α���
--        local KickDown = GetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ) 
--        if KickDown <= 0 or KickDown > 4 then
--            SetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ,4) 
--        end
--        
--        return
--    end
--    
--    --ִ�и������
--    ClearRageRecoverTick(sceneId, selfId)
--	RestoreHp(sceneId, selfId,100)
--	RestoreRage(sceneId, selfId,100)
--	ClearMutexState(sceneId, selfId, 6)
--	SendReliveResult(sceneId, selfId,1)
--
--	--�õ������������A��B��
--    local nGuildId = GetGuildID( sceneId,selfId )
--    local nGuildA = x300918_g_GuildA[sceneId]
--    local nGuildB = x300918_g_GuildB[sceneId]
--
--    if nGuildId == nGuildA or x300918_IsPlayerAidA(sceneId,selfId) == 1 then
--
--        x300918_OnLairdBattleChangeScene(sceneId,selfId,sceneId,0)
--    else
--        x300918_OnLairdBattleChangeScene(sceneId,selfId,sceneId,1)
--    end

end


----------------------------------------------------------------------------------------------
--���쳡����ʼ��
----------------------------------------------------------------------------------------------
function x300918_OnBattleSceneReady( sceneId,totalTime )

	local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

    --��������س�ʼ��
    x300918_g_CountDownState[sceneId] = -1
    x300918_g_CountDownTime[sceneId] = 10

    --��������ʱ��
    x300918_g_CountTime[sceneId] = totalTime
    
    --�����赲״̬
    x300918_g_TempImpassable_Door2_State[sceneId]	=	{  1,  1 }
    
    --�����赲
    --x300918_SetTempImpassable_Door1(sceneId)
    --x300918_SetTempImpassable_Door2(sceneId)
    
    --����������
    --x300918_ResetDoorA(sceneId)
    --x300918_ResetDoorB(sceneId)
    
    --�����ڲ�����
    x300918_g_ScoreA[sceneId] =	0
	x300918_g_ScoreB[sceneId] =	0
	x300918_g_IntervalScoreA[sceneId] =	0
	x300918_g_IntervalScoreB[sceneId] =	0
    
    
end

----------------------------------------------------------------------------------------------
--��ʾ�ݵ���Ϣ
----------------------------------------------------------------------------------------------
function x300918_ShowLairdSceneInfo( sceneId )
	
	local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end
    
    local nGuildId = GetSceneLairdGuildId(sceneId)    
    if nGuildId < 0 then
    	return
    end
    
    local nCountryId = GetSceneLairdCountryId(sceneId)
    if nCountryId < 0 or nCountryId > 3 then
    	return
    end
    
    local strGuildName = GetGuildName(nGuildId)
    local strGuildLeaderName = GetGuildLeaderName(nGuildId)
    local strCountryName = CallScriptFunction(888894,"GetCountryName",sceneId,nCountryId)
    local strLairdSceneName = x300918_GetLairdSceneInfo_Name(sceneId)
    
    local strMsg = format("�������ս������#G%s#o��#R%s#oռ����%s",strCountryName,strGuildName,strLairdSceneName)
    
    LuaAllScenceM2Wrold(sceneId, strMsg, 2, 1)
	LuaAllScenceM2Wrold(sceneId, strMsg, 3, 1)
    
end

----------------------------------------------------------------------------------------------
--�رմ���
----------------------------------------------------------------------------------------------
function x300918_OnBattleSceneClose( sceneId )

	x300918_ShowLairdSceneInfo( sceneId )
	
    if x300918_g_CountDownState[sceneId] == 1 then
        return
    end

    local status = x300918_g_BattleState[sceneId]
	if status == x300918_g_Laird_EndBattle then
		x300918_BattleGenResult( sceneId,0 )
	end


end

----------------------------------------------------------------------------------------------
--����ս��������
----------------------------------------------------------------------------------------------
function x300918_OnBattleSceneTimer( sceneId,uTime )
	
	--����BOSS��Ӫ����
    x300918_FixBossCampOp( sceneId )
    
    --BOSS״̬����
    x300918_UpdateBossState(sceneId)

    --�������Kick״̬
    --x300918_UpdatePlayerKickState( sceneId )

    local BattleStatus = x300918_g_BattleState[sceneId]
    if BattleStatus ~= x300918_g_Laird_BeginBattle then
    	--��BOSS����Ѫ�������ս�����
    	x300918_FullBossHp(sceneId)
        return
    end

    --��ʱ
    ----------------------------------------------------------------------------------------------
    local nTime = x300918_g_CountTime[sceneId] - 1
    x300918_g_CountTime[sceneId] = nTime

    --����ʱ����
    ----------------------------------------------------------------------------------------------
    if x300918_g_CountDownState[sceneId] == 1 then

	    --����ʱ״̬
	    local time = x300918_g_CountDownTime[sceneId]
	    if time > 0 then

		    x300918_g_CountDownTime[sceneId] = time - 1
--
--		    local str = format("#G�����ҡ�����ս������,#R%d��#G��ս���Զ��ر�",time)
--
--		    LuaThisScenceM2Guild(sceneId,str,x300918_g_GuildA[sceneId],3,1)
--		    LuaThisScenceM2Guild(sceneId,str,x300918_g_GuildB[sceneId],3,1)

		else

            --�ߵ��������
            --x300918_RestoreAllPlayerCamp( sceneId )
	    	--x300918_LairdBattleKickAllPlayer(sceneId)

			--�������
			x300918_g_BattleState[sceneId]				   = -1
			x300918_g_GuildA[sceneId]					   = -1
			x300918_g_GuildB[sceneId]					   = -1
			x300918_g_CountryA[sceneId]					   = -1
			x300918_g_CountryB[sceneId]					   = -1
			x300918_g_LairdMapID[sceneId]				   = -1
			x300918_g_HasLaird[sceneId]					   = 0
			x300918_g_CountDownState[sceneId]			   = -1
			x300918_g_CountDownTime[sceneId]			   = -1
			x300918_g_CountTime[sceneId]			       = -1
			x300918_g_GuildAidA[sceneId]					= {}
			x300918_g_GuildAidB[sceneId]					= {}
			
			--�����ڲ�����
		    x300918_g_ScoreA[sceneId] =	0
			x300918_g_ScoreB[sceneId] =	0
			x300918_g_IntervalScoreA[sceneId] =	0
			x300918_g_IntervalScoreB[sceneId] =	0
            
            --��¼��־
            local msg = format("LBL:x300918_OnBattleSceneTimer LairdBattleFinished,SceneId=%d,LeaveTime h= %d,m=%d",sceneId, floor(nTime/60),mod(nTime,60) )
            WriteLog(1,msg)

	    end

	    return

	end
	
	--��Ѫ����
	local nMod = mod(nTime,600)
	if nMod == 0 then
		--10���ӻ�һ��Ѫ
		x300918_FixBossHp(sceneId)		
	end
	
--	
--	--һ���Ӻ�ʼ
--    ----------------------------------------------------------------------------------------------
--	if nTime == 29*60 then

--		x300918_ClearTempImpassable_Door1(sceneId)
--	end
--
--    --����Ƿ����
--    ----------------------------------------------------------------------------------------------
--    if nTime < 28*60 then
--        local bIsFinished = x300918_CheckIsFinished( sceneId)
--        if bIsFinished == 1 then
--            
--            local status = x300918_g_BattleState[sceneId]
--            if status == x300918_g_Laird_BeginBattle then
--
--                x300918_BattleGenResult( sceneId,1 )
--                return
--            end
--
--        end
--    end
--	
--
--    --��ʱ��ʱ��ͬ��
--    ----------------------------------------------------------------------------------------------
--    x300918_SyncGuildPower( sceneId )
--
--    --С��ͼ����ʾ����
--    x300918_UpdateSceneDataFlag( sceneId )

end

----------------------------------------------------------------------------------------------
--������Ӫ
----------------------------------------------------------------------------------------------
function x300918_FixBossCampOp( sceneId )
	
	
	local nObjId = 1
	if IsObjValid(sceneId,nObjId ) ~= 1 or GetHp(sceneId,nObjId) <= 0 then
		return
	end
	
	
	--������Ӫ����
    local status = x300918_g_BattleState[sceneId]
    if status ~= x300918_g_Laird_BeginBattle then
    
    	--ս��û�п���
        local nCurCamp = GetMonsterCamp(sceneId,nObjId)		
		if nCurCamp == 20 then
			return
		end
		
		SetMonsterCamp(sceneId,nObjId,20)
		return
		
    else
    	
    	--ս����������
    	local nGuildId = GetSceneLairdGuildId( sceneId )
		if nGuildId < 0 then
			
			--û�б�ռ��Ĵ���
			local nCurCamp = GetMonsterCamp(sceneId,nObjId)		
			if nCurCamp == 21 then
				return
			end
			
			SetMonsterCamp(sceneId,nObjId,21)
			return
		else
			
			--�Ѿ���ռ��Ĵ���
			local nCountryId = GetSceneLairdCountryId(sceneId)
			if nCountryId < 0 or nCountryId > 3 then
				return
			end
			
			local nToSetCamp = nCountryId + 16
			local nCurCamp = GetMonsterCamp(sceneId,nObjId)		
			if nToSetCamp == nCurCamp then
				return
			end
			
			SetMonsterCamp(sceneId,nObjId,nToSetCamp)
			return
		end
    end
		
end

----------------------------------------------------------------------------------------------
--Boss��ظ���
----------------------------------------------------------------------------------------------
function x300918_UpdateBossState(sceneId)
	
	
	--���OBJ��Ч��
	local nObjId = 1
	if IsObjValid(sceneId,nObjId ) ~= 1 or GetHp(sceneId,nObjId) <= 0 then
		return
	end
	
	--�Զ��ָ�BUF
	if IsHaveSpecificImpact(sceneId,nObjId,13524)~=1 then
		SendSpecificImpactToUnit(sceneId, nObjId, nObjId, nObjId, 13524, 0)	
	end
	
	--��ֹ��ѪBUF
	if IsHaveSpecificImpact(sceneId,nObjId,8354)~=1 then
		SendSpecificImpactToUnit(sceneId, nObjId, nObjId, nObjId, 8354, 0)	
	end
	
	
	--��ʼ����BUF
	for i,item in x300918_g_SceneName do
		
		if item.Toggle == 1 and item.MapId == sceneId then
			
			--���ݵȼ����ϱ���BUF �����0��ʼ
			local nLairdLevel = GetSceneLairdLevel(sceneId)
			if nLairdLevel == 1 then
				
				--һ����ʱ��
				if item.Buf[1] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[1])~=1 then
					SendSpecificImpactToUnit(sceneId, nObjId, nObjId, nObjId, item.Buf[1], 0)	
				end
				
				--�������BUF,���ܻ����������˵����,������������������BUG
				if item.Buf[2] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[2])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[2], 0)	
				end		
				
				if item.Buf[3] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[3])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[3], 0)	
				end
				
				if item.Buf[4] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[4])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[4], 0)	
				end
				
				if item.Buf[5] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[4])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[5], 0)	
				end
				
			elseif nLairdLevel == 2 then
				
				--������ʱ��
				if item.Buf[2] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[2])~=1 then
					SendSpecificImpactToUnit(sceneId, nObjId, nObjId, nObjId, item.Buf[2], 0)	
				end
				
				--�������BUF,���ܻ����������˵����,������������������BUG
				if item.Buf[1] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[1])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[1], 0)	
				end	
				
				if item.Buf[3] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[3])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[3], 0)	
				end
				
				if item.Buf[4] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[4])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[4], 0)	
				end
				
				if item.Buf[5] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[4])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[5], 0)	
				end
			elseif nLairdLevel == 3 then
				
				--������ʱ��
				if item.Buf[3] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[3])~=1 then
					SendSpecificImpactToUnit(sceneId, nObjId, nObjId, nObjId, item.Buf[3], 0)	
				end
				
				--�������BUF,���ܻ����������˵����,������������������BUG
				if item.Buf[1] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[1])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[1], 0)	
				end		
				
				if item.Buf[2] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[2])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[2], 0)	
				end
				
				if item.Buf[4] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[4])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[4], 0)	
				end
				
				if item.Buf[5] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[4])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[5], 0)	
				end
			elseif nLairdLevel == 4 then
				
				--�ļ���ʱ��
				if item.Buf[4] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[4])~=1 then
					SendSpecificImpactToUnit(sceneId, nObjId, nObjId, nObjId, item.Buf[4], 0)	
				end
				
				--�������BUF,���ܻ����������˵����,������������������BUG
				if item.Buf[1] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[1])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[1], 0)	
				end		
				
				if item.Buf[2] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[2])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[2], 0)	
				end		
				
				if item.Buf[3] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[3])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[3], 0)	
				end
				
				if item.Buf[5] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[4])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[5], 0)	
				end
				
			elseif nLairdLevel == 5 then
				
				--�弶��ʱ��
				if item.Buf[5] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[5])~=1 then
					SendSpecificImpactToUnit(sceneId, nObjId, nObjId, nObjId, item.Buf[5], 0)	
				end
				
				
				--�������BUF,���ܻ����������˵����,������������������BUG
				if item.Buf[1] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[1])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[1], 0)	
				end		
				
				if item.Buf[2] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[2])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[2], 0)	
				end		
				
				if item.Buf[3] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[3])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[3], 0)	
				end
				
				if item.Buf[4] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[4])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[4], 0)	
				end
			
			else
				
				--���BUF,���ܻ����������˵����,������������������BUG
				if item.Buf[1] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[1])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[1], 0)	
				end		
				
				if item.Buf[2] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[2])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[2], 0)	
				end		
				
				if item.Buf[3] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[3])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[3], 0)	
				end
				
				if item.Buf[4] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[4])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[4], 0)	
				end
				
				if item.Buf[5] ~= -1 and IsHaveSpecificImpact(sceneId,nObjId,item.Buf[4])==1 then
					CancelSpecificImpact(sceneId, nObjId,item.Buf[5], 0)	
				end
			
			end
			
			return
			
		end
		
	end

end

----------------------------------------------------------------------------------------------
--���û�Ѫ
----------------------------------------------------------------------------------------------
function x300918_FixBossHp(sceneId)
	
	local nObjId = 1
	if IsObjValid(sceneId,nObjId ) ~= 1 or GetHp(sceneId,nObjId) <= 0 then
		return
	end
	
	--���û�Ѫ
	local nHp = floor(GetMaxHp(sceneId,nObjId)* 0.05)
	SetHp(sceneId,nObjId,nHp)
end

----------------------------------------------------------------------------------------------
--��BOSS����Ѫ
----------------------------------------------------------------------------------------------
function x300918_FullBossHp(sceneId)

	local nObjId = 1
	if IsObjValid(sceneId,nObjId ) ~= 1 then
		return
	end
	
	--��ǰѪ��
	local nCurHp = GetHp(sceneId,nObjId)
	if nCurHp <= 0 then
		return
	end
	
	--����Ѫ״̬
	if nCurHp == GetMaxHp(sceneId,nObjId) then
		return
	end
	
	--����Ѫ
	SetHp(sceneId,nObjId,GetMaxHp(sceneId,nObjId))
end

----------------------------------------------------------------------------------------------
--����Ƿ���Խ���
----------------------------------------------------------------------------------------------
function x300918_CheckIsFinished( sceneId )

    
    --�ռ���Ϣ
    local nGuildA = x300918_g_GuildA[sceneId]
    local nGuildB = x300918_g_GuildB[sceneId]


	--˫��������,������Ԯ
    local nGuildA_MemberCount = 0
    local nGuildB_MemberCount = 0


    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local nGuildId = GetGuildID( sceneId,objId )
            if nGuildId == nGuildA or x300918_IsPlayerAidA(sceneId,objId) == 1 then		
                nGuildA_MemberCount = nGuildA_MemberCount + 1
            elseif nGuildId == nGuildB  or x300918_IsPlayerAidB(sceneId,objId) == 1  then
                nGuildB_MemberCount = nGuildB_MemberCount + 1
            end
        end
    end

    if nGuildA_MemberCount == 0 and nGuildB_MemberCount == 0 then
        return 1
    end

    --һ�����ˣ�����Խ���
    if nGuildA_MemberCount == 0 and nGuildB_MemberCount > 0 then
        return 1
    end

    if nGuildB_MemberCount == 0 and nGuildA_MemberCount > 0 then
        return 1
    end

    return 0

end


----------------------------------------------------------------------------------------------
--�õ���ʤ����0ΪA����ʤ��1ΪB����ʤ��-1Ϊƽ��
----------------------------------------------------------------------------------------------
function x300918_GetWinner(sceneId)

	local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

    --�ռ���Ϣ
    local nGuildA = x300918_g_GuildA[sceneId]
    local nGuildB = x300918_g_GuildB[sceneId]

    local nGuildA_MemberCount = 0
    local nGuildB_MemberCount = 0

    local nGuildA_GuildIn = 0
    local nGuildB_GuildIn = 0

    local nGuildA_GuilderDie = 0
    local nGuildB_GuilderDie = 0

    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local nGuildId = GetGuildID( sceneId,objId )
            if nGuildId == nGuildA or x300918_IsPlayerAidA(sceneId,objId) == 1  then
                nGuildA_MemberCount = nGuildA_MemberCount + 1
            elseif nGuildId == nGuildB or x300918_IsPlayerAidB(sceneId,objId) == 1 then
                nGuildB_MemberCount = nGuildB_MemberCount + 1
            end

            local pos = GetGuildOfficial(sceneId, objId)
	        if pos == x300918_g_Leader_Index then
                if nGuildId == nGuildA then
                    nGuildA_GuildIn = 1
                    nGuildA_GuilderDie = GetPlayerRuntimeData(sceneId,objId,RD_KING_BATTLE_BEKILLED )
                else
                    nGuildB_GuildIn = 1
                    nGuildB_GuilderDie = GetPlayerRuntimeData(sceneId,objId,RD_KING_BATTLE_BEKILLED )
                end
            end
        end
    end


    --ʤ���ж�
    local nScoreA = x300918_g_ScoreA[sceneId] + x300918_g_IntervalScoreA[sceneId]
    local nScoreB = x300918_g_ScoreB[sceneId] + x300918_g_IntervalScoreB[sceneId]
    
    
    if ( nGuildA_MemberCount == 0 and nGuildB_MemberCount == 0 ) or
       ( nGuildA_MemberCount ~= 0 and nGuildB_MemberCount ~= 0 ) then
       
    	--˫����û���˻򶼶����˵�����£����Ȱ��������ж���Ӯ
    	
    	
    	if nScoreA > nScoreB then
	    	--���ָߵ�Ӯ
	    	return 0
	    elseif nScoreA < nScoreB then
	    	--���ָߵ�Ӯ
	    	return 1
	    else
	    	--������ͬ�Ĵ���
	    	
		    if nGuildA_MemberCount > 0 and nGuildB_MemberCount > 0 then
		    	
		    	--˫��������
		    	
		    	
		        if nGuildA_MemberCount > nGuildB_MemberCount then
		        	--�����˶��Ӯ
		            return 0
		        elseif nGuildA_MemberCount < nGuildB_MemberCount then
		        	--�����˶��Ӯ
		            return 1
		        else
		        	
		        	--������ȣ����������ڵ�Ӯ
		            
		            if nGuildA_GuildIn == 1 and nGuildB_GuildIn == 0 then
		                --������ͬ�������ڵ�ΪӮ
		                return 0
		            elseif nGuildA_GuildIn == 0 and nGuildB_GuildIn == 1 then
		                --������ͬ�������ڵ�ΪӮ
		                return 1
		            else
		                --������ͬ�������ڣ��������Ĵ���ΪӮ
		                if nGuildA_GuilderDie > nGuildB_GuilderDie then
		                    return 1
		
		                elseif nGuildA_GuilderDie < nGuildB_GuilderDie then
		                    return 0
		                else
		                
		                	--����ͬ�����Ӯ
		                	local nRandWin = random(0,1)
		                	if nRandWin < 0 then nRandWin = 0 end
		                	if nRandWin > 1 then nRandWin = 1 end
		                
		                    return nRandWin
		                end
		            end
		        end
		    else
		    	
		    	--û���ҷ�����ͬ
		    	
		    	--�����������ͬ���������
            	local nRandWin = random(0,1)
            	if nRandWin < 0 then nRandWin = 0 end
            	if nRandWin > 1 then nRandWin = 1 end
            
                return nRandWin
		    end
	    end
    else
    	--ֻ��һ�����˵Ĵ���
    
	    --�ж��������Ӯ
	    if nGuildA_MemberCount == 0 and nGuildB_MemberCount > 0 then
	        return 1
	    else
	        return 0
	    end
	end

    return 1
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x300918_BattleBonus( sceneId,selfId,battleResult )

	local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

end

----------------------------------------------------------------------------------------------
--����������
----------------------------------------------------------------------------------------------
function x300918_LairdBattleBonus( sceneId ,battleResult )

    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            x300918_BattleBonus( sceneId,objId,battleResult)
        end
    end
end


----------------------------------------------------------------------------------------------
--�ָ���Ӫ
----------------------------------------------------------------------------------------------
function x300918_RestorePlayerCamp( sceneId,selfId )
    local nCountryId = GetCurCountry( sceneId,selfId )
    SetCurCamp(sceneId,selfId,nCountryId )
end

----------------------------------------------------------------------------------------------
--�ָ���Ӫ
----------------------------------------------------------------------------------------------
function x300918_RestoreAllPlayerCamp( sceneId )

    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local nCountryId = GetCurCountry( sceneId,objId )
            SetCurCamp(sceneId,objId,nCountryId )
        end
    end
end


----------------------------------------------------------------------------------------------
--���ɰ�ս���
----------------------------------------------------------------------------------------------
function x300918_BattleGenResult( sceneId, callerId  )
    
    local nGuildA = x300918_g_GuildA[sceneId]
    local nGuildB = x300918_g_GuildB[sceneId]

    local nLairdMapId = x300918_g_LairdMapID[sceneId]

    if nGuildA == nGuildB then
        return
    end

--    local nWinner = x300918_GetWinner( sceneId )
--    if nWinner == 0 then
--        --��ս����ȡ
--
--        local strGuildName = GetGuildName(nGuildA)
--        local strGuildLeaderName = GetGuildLeaderName(nGuildA)
--        local strLairdSceneName = x300918_GetLairdSceneInfo_Name(nLairdMapId)
--        
--        local str = format("#G%s�����%s�����ҡ�����ս����ʤ����%s�����������ı����� ",strGuildName,strLairdSceneName,strGuildLeaderName)
--        LuaAllScenceM2Wrold(sceneId, str, 2, 1)
--        LuaAllScenceM2Wrold(sceneId, str, 3, 1)
--
--        GameBattleSendResultToGL( x300918_g_BattleType,0,x300918_g_LairdMapID[sceneId],x300918_g_GuildA[sceneId],x300918_g_GuildB[sceneId])
--
--    else
--        --�ݵ㷽��ȡ
--        local strGuildName = GetGuildName(nGuildB)
--        local strGuildLeaderName = GetGuildLeaderName(nGuildB)
--        local strLairdSceneName = x300918_GetLairdSceneInfo_Name(nLairdMapId)
--        
--        local str = format("#G%s����Ž�һ�µĶ�ס����ս��������%s�����ı�����  ",strGuildName,strLairdSceneName )
--        if x300918_g_HasLaird[sceneId] == 0 then
--        	str = format("#G%s�����%s�����ҡ�����ս����ʤ����%s�����������ı����� ",strGuildName,strLairdSceneName,strGuildLeaderName)
--        end
--        LuaAllScenceM2Wrold(sceneId, str, 2, 1)
--        LuaAllScenceM2Wrold(sceneId, str, 3, 1)
--
--        GameBattleSendResultToGL( x300918_g_BattleType,1,x300918_g_LairdMapID[sceneId],x300918_g_GuildA[sceneId],x300918_g_GuildB[sceneId])
--    end

    --���뵹��ʱ״̬,�����õ���ʱ��
    x300918_g_CountDownState[sceneId] = 1
    x300918_g_CountDownTime[sceneId] = 10

    local nTime = x300918_g_CountTime[sceneId]
        
    --��¼��־
    local msg = format("LBL:x300918_BattleGenResult SceneId=%d,LeaveTime h= %d,m=%d,CallerId=%d",sceneId, floor(nTime/60),mod(nTime,60), callerId )
    WriteLog(1,msg)

    x300918_g_GuildA[sceneId] = -1
    x300918_g_GuildB[sceneId] = -1
    
    x300918_g_CountryA[sceneId] = -1
    x300918_g_CountryB[sceneId] = -1
    
    x300918_g_GuildAidA[sceneId]					= {}
	x300918_g_GuildAidB[sceneId]					= {}

    --x300918_SetAllPlayerNeedKick(sceneId)
    --ClearLairdBattleSceneData(sceneId)
    
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x300918_LairdBattleKickPlayer( sceneId,selfId )

    x300918_DoPlayerRelive( sceneId,selfId )

    x300918_RestorePlayerCamp( sceneId,selfId)

    --ֻҪ����뿪ս����������������÷�
    SetPlayerRuntimeData(sceneId,selfId,RD_BATTLESCENE_ENTER_FLAG,0)

    --�������BakScene��Ϣ������BakScene��ϢΪ׼
    local nBakSceneId,x,z = GetPlayerBakSceneInfo(sceneId,selfId )
    if nBakSceneId >= 0 then
        NewWorld(sceneId,selfId,nBakSceneId,x,z,300918)
        return
    end

    --ѡ��һ�����ʵĳ������ͳ�ȥ
    local nCountry = GetCurCountry(sceneId,selfId)
    if nCountry == 0 then
        
        --¥��
        local nDestSceneId = 50
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,300918)

    elseif nCountry == 1 then
        
        --��ɽ
        local nDestSceneId = 150
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,300918)

    elseif nCountry == 2 then

        --����
        local nDestSceneId = 250
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,300918)

    elseif nCountry == 3 then
        
        --�ػ�
        local nDestSceneId = 350
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,300918)

    end
end

----------------------------------------------------------------------------------------------
--�ߵ����������е���
----------------------------------------------------------------------------------------------
function x300918_LairdBattleKickAllPlayer( sceneId )
    
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            
            x300918_LairdBattleKickPlayer( sceneId,objId)

        end
    end
end


----------------------------------------------------------------------------------------------
--ͬ����ս����ʱ��ȫ����ң���ǰ������
----------------------------------------------------------------------------------------------
function x300918_SyncBattleTimeToAllPlayer( sceneId ,nTime )

    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then

            TimerCommand( sceneId, objId, 1, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, GUILDBATTLE_SCRIPTID,-1,-1);                 --��ǿ�ƹر�

            if nTime > 0 then
                TimerCommand( sceneId, objId, 2, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, GUILDBATTLE_SCRIPTID, nTime, nTime );
            end
        end
    end    
end

----------------------------------------------------------------------------------------------
--ͬ����ս����ʱ�ر���Ϣ��ȫ����ң���ǰ������
----------------------------------------------------------------------------------------------
function x300918_SyncBattleTimeCloseToAllPlayer(sceneId )
    
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then

            TimerCommand( sceneId, objId, 1, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, GUILDBATTLE_SCRIPTID,-1,-1);                 --��ǿ�ƹر�
        end
    end    

end

----------------------------------------------------------------------------------------------
--ͬ���������
----------------------------------------------------------------------------------------------
function x300918_SyncGuildPower( sceneId )
    
    local nGuildA = x300918_g_GuildA[sceneId]
    local nGuildB = x300918_g_GuildB[sceneId]

    local nGuildA_Count = 0
    local nGuildB_Count = 0

    --ͳ��������������ڲ��ܴ�����ҵ��ߵ�����������������������ͬ���������
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local nGuildId = GetGuildID( sceneId,objId )
            if nGuildId == nGuildA or x300918_IsPlayerAidA(sceneId,objId) == 1 then
                nGuildA_Count = nGuildA_Count + 1
            elseif nGuildId == nGuildB or x300918_IsPlayerAidB(sceneId,objId) == 1 then
                nGuildB_Count = nGuildB_Count + 1
            end
        end
    end

    --ͬ�������
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            GameBattleSyncPowerInfo(sceneId,objId,nGuildA_Count,nGuildB_Count,2)
        end
    end

end

----------------------------------------------------------------------------------------------
--����С��ͼ
----------------------------------------------------------------------------------------------
function x300918_UpdateSceneDataFlag( sceneId )

    local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end
    
    ClearSceneMapDataFlag( sceneId )

	-- SetSceneMapDataFlag( sceneId,10,8,"���뷽������",73,180,-1)
	-- SetSceneMapDataFlag( sceneId,11,8,"�ݵ㷽������",215,47,-1)

    --���°�����λ��
    local GuildLeaderA = -1
    local GuildLeaderB = -1
    
    local nGuildA = x300918_g_GuildA[sceneId]
    local nGuildB = x300918_g_GuildB[sceneId]

    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            
            local pos = GetGuildOfficial(sceneId, objId)
	        if pos == x300918_g_Leader_Index then
                local nGuild = GetGuildID( sceneId,objId )
                if nGuild == nGuildA then
                    GuildLeaderA = objId
                elseif nGuild == nGuildB then
                    GuildLeaderB = objId
                end
            end
        end
    end


    local a_leader_name = ""
    local a_leader_x = 0
    local a_leader_z = 0
    
    if GuildLeaderA > 0 then
        
        a_leader_name = GetName(sceneId,GuildLeaderA)
        a_leader_x,a_leader_z = GetWorldPos(sceneId,GuildLeaderA)
    end

    local b_leader_name = ""
    local b_leader_x = 0
    local b_leader_z = 0
    
    if GuildLeaderB > 0 then

        b_leader_name = GetName(sceneId,GuildLeaderB)
        b_leader_x,b_leader_z = GetWorldPos(sceneId,GuildLeaderB)
    end

    --���Ͱ���״̬
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            
            if GuildLeaderA > 0 and GuildLeaderA ~= objId then
                SetSceneMapDataFlagToPlayer( sceneId,objId,12,8,a_leader_name,a_leader_x,a_leader_z,-1)
            end

            if GuildLeaderB > 0 and GuildLeaderB ~= objId then
                SetSceneMapDataFlagToPlayer( sceneId,objId,13,8,b_leader_name,b_leader_x,b_leader_z,-1)
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--��GLServer������ͬ������ս��ʱ��Ķ���
----------------------------------------------------------------------------------------------
function x300918_OnSyncLairdBattleTime( sceneId,nTime )
    
    if x300918_GetLairdBattleSceneScript( sceneId ) == 0 then
        return
    end

    local nTime_new = x300918_g_TotalBattleTime - NumberCastIntToUInt( nTime )
    x300918_g_CountTime[sceneId] = nTime_new
    
    if x300918_g_GuildA[sceneId] ~= -1 then
    	WriteLog(1,"LBL:x300918_OnSyncLairdBattleTime x300918_g_CountTime[sceneId]=%d",x300918_g_CountTime[sceneId])
    end

    --��ʱ��ʱ��ͬ��
    ----------------------------------------------------------------------------------------------
    --x300918_SyncBattleTimeToAllPlayer( sceneId, nTime_new )
end

----------------------------------------------------------------------------------------------
--�������������Ҫ�ߵ�
----------------------------------------------------------------------------------------------
function x300918_SetAllPlayerNeedKick( sceneId )
    
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local KickDown = GetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ) 
            if KickDown <= 0 or KickDown > x300918_g_Kick_Down then                
                SetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ,x300918_g_Kick_Down) 
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--��������ߵ�״̬
----------------------------------------------------------------------------------------------
function x300918_UpdatePlayerKickState( sceneId )
    
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local KickDown = GetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ) 
            if KickDown > 0 then                
                KickDown = KickDown - 1 
                if KickDown == 0 then
                    --����ʱΪ�㣬�ߵ�
                    SetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ,-1) 
                    x300918_LairdBattleKickPlayer( sceneId,objId )                    
                else
                    --���򣬼�������ʱ
                    SetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ,KickDown) 
                end
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--�����¼�-����BOSS
----------------------------------------------------------------------------------------------
function x300918_CreateBoss(sceneId)

	x300918_DestroyBoss(sceneId)

	x300918_g_BossA[sceneId] = {}
	x300918_g_BossB[sceneId] = {}

	--���������ָ������,����Ϊ���Դ����µĹ���
	local nIndexFrom = GetFubenDataPosByScriptID( x300918_g_scriptId )
	local nDataCount = GetFubenDataCountByScriptID( x300918_g_scriptId )
	
	--��¼��־
	local msg = format("LBL:x300918_CreateBoss before sceneId=%d,monstercount=%d,si = %d,sc = %d",sceneId,GetMonsterCount(sceneId),nIndexFrom,nDataCount)
	WriteLog(1,msg)
	
	for i = 0,nDataCount-1 do
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x300918_g_scriptId,nIndexFrom,i)
		
		
		
		if idScript == x300918_g_scriptId then
			
            for j=0,count -1 do
            
            	local lx = x + random(-r,r)
            	local lz = z + random(-r,r)
            	
            	if flag == 0 and flag1 >= 1 and flag1 <= 3  then
            	
            		--A��Ӫ��BOSS
					if title~="" then
						local objId = CreateMonster(sceneId, type, lx, lz, ai, aiscript, x300918_g_scriptId, -1, camp, -1,facedir, "", title)
						x300918_g_BossA[sceneId][flag1] = objId
					else
						local objId = CreateMonster(sceneId, type, lx, lz, ai, aiscript, x300918_g_scriptId, -1, camp, -1,facedir)
						x300918_g_BossA[sceneId][flag1] = objId
					end
					
				elseif flag == 1 and flag1 >= 1 and flag1 <= 3 then
					
					--B��Ӫ��BOSS
					if title~="" then
						local objId = CreateMonster(sceneId, type, lx, lz, ai, aiscript, x300918_g_scriptId, -1, camp, -1,facedir, "", title)
						x300918_g_BossB[sceneId][flag1] = objId
					else
						local objId = CreateMonster(sceneId, type, lx, lz, ai, aiscript, x300918_g_scriptId, -1, camp, -1,facedir)
						x300918_g_BossB[sceneId][flag1] = objId
					end
				end
			end
        end
	end
	
	--��¼��־
	msg = format("LBL:x300918_CreateBoss after sceneId=%d,monstercount=%d",sceneId,GetMonsterCount(sceneId))
	WriteLog(1,msg)
end

----------------------------------------------------------------------------------------------
--�����¼�-ɾ��BOSS
----------------------------------------------------------------------------------------------
function x300918_DestroyBoss(sceneId)
	
	if x300918_g_BossA[sceneId] ~= nil then
	
		--���A��BOSS
		for i,item in x300918_g_BossA[sceneId] do
			
			if item >=0 and IsObjValid(sceneId,item) == 1 and GetHp(sceneId,item) > 0 then
				DeleteMonster(sceneId,item)
			end
		end
		
		x300918_g_BossA[sceneId] = nil
	
	end
	
	
	if x300918_g_BossB[sceneId] ~= nil then
	
		--���B��BOSS
		for i,item in x300918_g_BossB[sceneId] do
			
			if item >=0 and IsObjValid(sceneId,item) == 1 and GetHp(sceneId,item) > 0 then
				DeleteMonster(sceneId,item)
			end
		end
		
		x300918_g_BossB[sceneId] = nil
		
	end
	
end


----------------------------------------------------------------------------------------------
--������������
----------------------------------------------------------------------------------------------
function x300918_OnGenerateLaird(sceneId,nResult,nGuildA,nGuildB )
	
	GameBattleSendResultToGL( x300918_g_BattleType,nResult,x300918_g_LairdMapID[sceneId],nGuildA,nGuildB)
	
end

----------------------------------------------------------------------------------------------
--�����������
----------------------------------------------------------------------------------------------
function x300918_ProcLairdLevelup(sceneId,nLairdMapId)
	
	local nRandom = random(1,100)
	if nRandom > 10 then
		return
	end
	
	local _,strLairdSceneName = GetBattleSceneNameNM(nLairdMapId)
	local nLairdSceneLevel = GetSceneLairdLevel(nLairdMapId)
	local strMsg = nil
	
	if sceneId == 76 then
		
		
		CreateMonster(sceneId, 3059, 211, 203, 24, -1, -1, -1, 21, -1, 0, "", "" )
		strMsg = format("%sͼ��������������䣬¥��������������֮��",strLairdSceneName)
		
	elseif sceneId == 176 then
	
		CreateMonster(sceneId, 3059,  43,  35, 24, -1, -1, -1, 21, -1, 0, "", "" )
		strMsg = format("%sͼ��������������䣬��ɽ������������֮��",strLairdSceneName)

	elseif sceneId == 276 then
	
		CreateMonster(sceneId, 3059, 211, 203, 24, -1, -1, -1, 21, -1, 0, "", "" )
		strMsg = format("%sͼ��������������䣬���ذ�����������֮��",strLairdSceneName)

	elseif sceneId == 376 then
	
		CreateMonster(sceneId, 3059,  43,  35, 24, -1, -1, -1, 21, -1, 0, "", "" )
		strMsg = format("%sͼ��������������䣬�ػͰ�����������֮��",strLairdSceneName)
		
	end
	
	if strMsg ~= nil then
	
		
	
		LuaAllScenceM2Wrold(sceneId,strMsg,CHAT_PLANE_SCROLL,1)
		LuaAllScenceM2Wrold(sceneId,strMsg,CHAT_LEFTDOWN,1)
		LuaAllScenceM2Wrold(sceneId,strMsg,CHAT_MAIN_RIGHTDOWN,1)
	end
	
	
end

----------------------------------------------------------------------------------------------
--�����¼�-������������
----------------------------------------------------------------------------------------------
function x300918_OnDie(sceneId,selfId,killerId)
	
	--����ǳ���ɱ��,��Ҫȡ�����˵���Ϣ
	local ObjType = GetObjType(sceneId, killerId)
	if ObjType == 3 then
		ObjType = 1
		killerId = GetOwnerID(sceneId, killerId)
	end
	
	--�������Ƿ���Ч
	if killerId < 0 or IsPlayerStateNormal(sceneId,killerId) ~= 1 then
		--��������Ч�����ﲻ������������
		return
	end

    --����Ƿ�������ս�������б���������������������ǣ��򲻴���
    local nScriptId = x300918_GetLairdBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

	--ս���Ƿ���
    local status = x300918_g_BattleState[sceneId]
    if status ~= x300918_g_Laird_BeginBattle then
        return
    end

	--����ս�����
	local nGuildId = GetGuildID(sceneId,killerId)
	local nGuildA = x300918_g_GuildA[sceneId]
	local nGuildB = x300918_g_GuildB[sceneId]
	
	if nGuildA == nGuildB then
		return
	end
	
	local nCountryID = GetCurCountry(sceneId,killerId)
	
	if nCountryID == x300918_g_CountryA[sceneId]  then
		x300918_OnGenerateLaird(sceneId,0,nGuildA,nGuildB )
		
        local strGuildName = GetGuildName(nGuildA)
        local strGuildLeaderName = GetGuildLeaderName(nGuildA)
        local strLairdSceneName = x300918_GetLairdSceneInfo_Name(sceneId)
        
        local str = format("#G%s����ڰ���%s�Ĵ�����ռ����%s��",strGuildName,strGuildLeaderName,strLairdSceneName)
        LuaAllScenceM2Wrold(sceneId, str, 2, 1)
        LuaAllScenceM2Wrold(sceneId, str, 3, 1)
        
        local nCampId = GetCurCountry(sceneId,killerId) + 16
        SetMonsterCamp(sceneId,selfId,nCampId)
		
	elseif nCountryID == x300918_g_CountryB[sceneId]  then
		x300918_OnGenerateLaird(sceneId,1,nGuildA,nGuildB )
		
		local strGuildName = GetGuildName(nGuildB)
        local strGuildLeaderName = GetGuildLeaderName(nGuildB)
        local strLairdSceneName = x300918_GetLairdSceneInfo_Name(sceneId)
        
        local str = format("#G%s����ڰ���%s�Ĵ�����ռ����%s��",strGuildName,strGuildLeaderName,strLairdSceneName)
        LuaAllScenceM2Wrold(sceneId, str, 2, 1)
        LuaAllScenceM2Wrold(sceneId, str, 3, 1)
        
        local nCampId = GetCurCountry(sceneId,killerId) + 16
        SetMonsterCamp(sceneId,selfId,nCampId)
	end
	
--	--A���������������	
--	local nBossACount = getn(x300918_g_BossA[sceneId])
--	for i,item in x300918_g_BossA[sceneId] do
--	
--		if item == selfId then
--			if i < nBossACount then
--				
--				--�������һ���Ĵ���
--				--local objId = x300918_g_BossA[sceneId][i+1]
--				--if objId >=0 and IsObjValid(sceneId,objId) == 1 and GetHp(sceneId,objId) > 0 then
--				--	SetMonsterCamp(sceneId,objId,x300918_g_Guild_Camp_A)
--				--end
--				x300918_g_BossA[sceneId][i] = -1
--				x300918_g_ScoreB[sceneId] = x300918_g_ScoreB[sceneId] + 50
--				x300918_OnBossDie(sceneId, 0 )
--				x300918_LairdSyncGuildScore(sceneId)
--				local msg = "˹����������ս���ػ�������������ɱ"
--				LuaThisScenceM2Wrold( sceneId,msg,3,1)
--				LuaThisScenceM2Wrold( sceneId,msg,2,1)
--				return
--				
--			else
--				--���һ���Ĵ���
--				x300918_g_IntervalScoreB[sceneId] = 1000000
--				x300918_BattleGenResult( sceneId,2)
--				local msg = "˹����������ս�챻������������"
--				LuaThisScenceM2Wrold( sceneId,msg,3,1)
--				LuaThisScenceM2Wrold( sceneId,msg,2,1)
--				return
--			end
--			
--		end
--		
--	end
--	
--	--B���������������
--	local nBossBCount = getn(x300918_g_BossB[sceneId])
--	for i,item in x300918_g_BossB[sceneId] do
--	
--		if item == selfId then
--			if i < nBossBCount then
--				
--				--�������һ���Ĵ���
--				--local objId = x300918_g_BossB[sceneId][i+1]
--				--if objId >=0 and IsObjValid(sceneId,objId) == 1 and GetHp(sceneId,objId) > 0 then
--				--	SetMonsterCamp(sceneId,objId,x300918_g_Guild_Camp_B)
--				--end
--				x300918_g_BossB[sceneId][i] = -1
--				x300918_g_ScoreA[sceneId] = x300918_g_ScoreA[sceneId] + 50
--				x300918_OnBossDie(sceneId, 1 )
--    			x300918_LairdSyncGuildScore(sceneId)
--				local msg = "����������ս���ػ���˹����������ɱ"
--				LuaThisScenceM2Wrold( sceneId,msg,3,1)
--				LuaThisScenceM2Wrold( sceneId,msg,2,1)
--				return
--			else
--				--���һ���Ĵ���
--				x300918_g_IntervalScoreA[sceneId] = 1000000
--				x300918_BattleGenResult( sceneId,3)
--				local msg = "����������ս�챻˹������������"
--				LuaThisScenceM2Wrold( sceneId,msg,3,1)
--				LuaThisScenceM2Wrold( sceneId,msg,2,1)
--				return
--			end
--		end
--	end
end

----------------------------------------------------------------------------------------------
--������������
----------------------------------------------------------------------------------------------
function x300918_OnBossDie(sceneId, flag )

	if flag == 0 then
		
		local nBossACount = getn(x300918_g_BossA[sceneId])
		local nBossADieCount = 0
		for i,item in x300918_g_BossA[sceneId] do
			if x300918_g_BossA[sceneId][i] == -1 then
				nBossADieCount = nBossADieCount + 1
			end			
		end
		
		if nBossADieCount == nBossACount -1 then
			
			local objId = x300918_g_BossA[sceneId][nBossACount]
			if objId >=0 and IsObjValid(sceneId,objId) == 1 and GetHp(sceneId,objId) > 0 then
				SetMonsterCamp(sceneId,objId,x300918_g_Guild_Camp_A)
			end
		end
		
	elseif flag == 1 then
		
		local nBossBCount = getn(x300918_g_BossB[sceneId])
		local nBossBDieCount = 0
		for i,item in x300918_g_BossB[sceneId] do
			if x300918_g_BossB[sceneId][i] == -1 then
				nBossBDieCount = nBossBDieCount + 1
			end			
		end
		
		if nBossBDieCount == nBossBCount -1 then
			
			local objId = x300918_g_BossB[sceneId][nBossBCount]
			if objId >=0 and IsObjValid(sceneId,objId) == 1 and GetHp(sceneId,objId) > 0 then
				SetMonsterCamp(sceneId,objId,x300918_g_Guild_Camp_B)
			end
		end
	end	
end

----------------------------------------------------------------------------------------------
--�ɼ����¼�-ȡ����A����
----------------------------------------------------------------------------------------------
function x300918_GetDoorA(sceneId)
	return x300918_g_DoorGrowPointA
end

----------------------------------------------------------------------------------------------
--�ɼ����¼�-ȡ����B����
----------------------------------------------------------------------------------------------
function x300918_GetDoorB(sceneId)	
	return x300918_g_DoorGrowPointB
end

----------------------------------------------------------------------------------------------
--�ɼ����¼�-������A
----------------------------------------------------------------------------------------------
function x300918_ResetDoorA(sceneId)

	x300918_g_DoorGrowPointA_LairdState[sceneId] = { LairdCountDownState = 0,LairdCountDownTime = -1,LairdCamp = -1 }
	RecycleGrowPointByType(sceneId,x300918_g_DoorGrowPointA,1000)
	
	local msg = format("LBL:x300918_ResetDoorA sceneId=%d",sceneId)
	WriteLog(1,msg)
end

----------------------------------------------------------------------------------------------
--�ɼ����¼�-������B
----------------------------------------------------------------------------------------------
function x300918_ResetDoorB(sceneId)
	x300918_g_DoorGrowPointB_LairdState[sceneId] = { LairdCountDownState = 0,LairdCountDownTime = -1,LairdCamp = -1 }
	RecycleGrowPointByType(sceneId,x300918_g_DoorGrowPointB,1000)
	
	local msg = format("LBL:x300918_ResetDoorB sceneId=%d",sceneId)
	WriteLog(1,msg)
end


----------------------------------------------------------------------------------------------
--�ɼ����¼�-A�� ����Ƿ���Կ�ʼ
----------------------------------------------------------------------------------------------
function x300918_OnOpenDoorA_Check(sceneId,selfId)
	
	--��Ӫ���
	local nCampId = GetCurCamp(sceneId,selfId)
	if nCampId ~= x300918_g_Guild_Camp_B then
		return 1
	end

	return 0	
end

----------------------------------------------------------------------------------------------
--�ɼ����¼�-A�� ����Ƿ���Կ�ʼ
----------------------------------------------------------------------------------------------
function x300918_OnOpenDoorB_Check(sceneId,selfId)

	--��Ӫ���
	local nCampId = GetCurCamp(sceneId,selfId)
	if nCampId ~= x300918_g_Guild_Camp_A then
		return 1
	end
	
	return 0
end

----------------------------------------------------------------------------------------------
--�ɼ����¼�-����A��
----------------------------------------------------------------------------------------------
function x300918_OnOpenDoorA(sceneId,selfId)
	
	--��Ӫ���
	local nCampId = GetCurCamp(sceneId,selfId)
	if nCampId ~= x300918_g_Guild_Camp_B then
		return 0
	end

	--������Ч
	x300918_g_TempImpassable_Door2_State[sceneId][1] = 0
	
	--�����̬�赲
	x300918_ClearTempImpassable_Door2(sceneId,1)
	
	--���������
	SetGrowPointIntervalContainer(sceneId,x300918_g_DoorGrowPointA,-1)
	
	--���������ʾ
	local msg = "˹���������ڳǴ��ű�������������"
	LuaThisScenceM2Wrold( sceneId,msg,3,1)
	LuaThisScenceM2Wrold( sceneId,msg,2,1)
	
	local msg = format("LBL:x300918_OnOpenDoorA sceneId=%d",sceneId)
	WriteLog(1,msg)
	
	return 1	
end

----------------------------------------------------------------------------------------------
--�ɼ����¼�-����B��
----------------------------------------------------------------------------------------------
function x300918_OnOpenDoorB(sceneId,selfId)

	--��Ӫ���
	local nCampId = GetCurCamp(sceneId,selfId)
	if nCampId ~= x300918_g_Guild_Camp_A then
		return 0
	end

	--������Ч
	x300918_g_TempImpassable_Door2_State[sceneId][2] = 0
	
	--�����̬�赲
	x300918_ClearTempImpassable_Door2(sceneId,2)
	
	--���������
	SetGrowPointIntervalContainer(sceneId,x300918_g_DoorGrowPointB,-1)
	
	--���������ʾ
	local msg = "���������ڳǴ��ű�˹������������"
	LuaThisScenceM2Wrold( sceneId,msg,3,1)
	LuaThisScenceM2Wrold( sceneId,msg,2,1)
	
	local msg = format("LBL:x300918_OnOpenDoorB sceneId=%d",sceneId)
	WriteLog(1,msg)
	
	return 1
end

----------------------------------------------------------------------------------------------
--��̬�赲-���ö�̬�赲1����Ч
----------------------------------------------------------------------------------------------
function x300918_SetTempImpassable_Door1_Effect(sceneId,selfId)
	
	if x300918_g_CountTime[sceneId] <= 18*60 then
		return
	end
	
	for i,itm in x300918_g_TempImpassable_Door1_Effect do
		CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,selfId,itm )		
	end
	
	
	local msg = format("LBL:x300918_SetTempImpassable_Door1_Effect sceneId=%d name=%s",sceneId,GetName(sceneId,selfId))
	WriteLog(1,msg)
	
end

----------------------------------------------------------------------------------------------
--��̬�赲-�����̬�赲1����Ч
----------------------------------------------------------------------------------------------
function x300918_ClearTempImpassable_Door1_Effect(sceneId,selfId)
	for i,itm in x300918_g_TempImpassable_Door1_Effect do
		CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,selfId,itm )		
	end
	
	local msg = format("LBL:x300918_ClearTempImpassable_Door1_Effect sceneId=%d name=%s",sceneId,GetName(sceneId,selfId))
	WriteLog(1,msg)
end


----------------------------------------------------------------------------------------------
--��̬�赲-���ö�̬�赲1
----------------------------------------------------------------------------------------------
function x300918_SetTempImpassable_Door1(sceneId)
	for i,itm in x300918_g_TempImpassable_Door1 do
		AddSceneTempImpassable(sceneId,itm.Left,itm.Top,itm.Right,itm.Bottom)
	end
	
	local msg = format("LBL:x300918_SetTempImpassable_Door1 sceneId=%d",sceneId)
	WriteLog(1,msg)
end

----------------------------------------------------------------------------------------------
--��̬�赲-�����̬�赲1
----------------------------------------------------------------------------------------------
function x300918_ClearTempImpassable_Door1(sceneId)
	
	--�㲥��ʼ
	LuaThisScenceM2Wrold( sceneId,"ս����ʼ",5,1)
	
	--ɾ����̬�赲
	for i,itm in x300918_g_TempImpassable_Door1 do
		DelSceneTempImpassable(sceneId,itm.Left,itm.Top,itm.Right,itm.Bottom)
	end
	
	--�����Ч
	local nHumanCount = GetScenePlayerCount( sceneId )
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 and IsPlayerStateNormal(sceneId,objId) == 1 then
            x300918_ClearTempImpassable_Door1_Effect(sceneId,objId)
        end
    end
    
    --��������
    x300918_CreateBoss(sceneId)
    
    local msg = format("LBL:x300918_ClearTempImpassable_Door1 sceneId=%d",sceneId)
	WriteLog(1,msg)
end

----------------------------------------------------------------------------------------------
--��̬�赲-���ö�̬�赲2����Ч
----------------------------------------------------------------------------------------------
function x300918_SetTempImpassable_Door2_Effect(sceneId,selfId)
	for i,itm in x300918_g_TempImpassable_Door2_State[sceneId] do
		if itm == 1 then
			CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,selfId,x300918_g_TempImpassable_Door2_Effect[i] )		
		end
	end	
	
	local msg = format("LBL:x300918_SetTempImpassable_Door2_Effect sceneId=%d name=%s",sceneId,GetName(sceneId,selfId))
	WriteLog(1,msg)
end

----------------------------------------------------------------------------------------------
--��̬�赲-�����̬�赲2����Ч
----------------------------------------------------------------------------------------------
function x300918_ClearTempImpassable_Door2_Effect(sceneId,selfId,nIndex)

	if nIndex < 1 or nIndex > getn(x300918_g_TempImpassable_Door2_Effect) then
		return
	end
	
	local itm = x300918_g_TempImpassable_Door2_Effect[nIndex]
	CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,selfId,itm )
	
	local msg = format("LBL:x300918_ClearTempImpassable_Door2_Effect sceneId=%d name=%s index=%d",sceneId,GetName(sceneId,selfId),nIndex)
	WriteLog(1,msg)
end


----------------------------------------------------------------------------------------------
--��̬�赲-���ö�̬�赲2
----------------------------------------------------------------------------------------------
function x300918_SetTempImpassable_Door2(sceneId)
	
	for i,itm in x300918_g_TempImpassable_Door2 do
		AddSceneTempImpassable(sceneId,itm.Left,itm.Top,itm.Right,itm.Bottom)
	end
	
	local msg = format("LBL:x300918_SetTempImpassable_Door2 sceneId=%d",sceneId)
	WriteLog(1,msg)
end

----------------------------------------------------------------------------------------------
--��̬�赲-�����̬�赲2
----------------------------------------------------------------------------------------------
function x300918_ClearTempImpassable_Door2(sceneId,nIndex)
	
	if nIndex < 1 or nIndex > getn(x300918_g_TempImpassable_Door2) then
		return
	end
	
	--ɾ����̬�赲
	local itm = x300918_g_TempImpassable_Door2[nIndex]
	DelSceneTempImpassable(sceneId,itm.Left,itm.Top,itm.Right,itm.Bottom)
	
	--�����Ч
	local nHumanCount = GetScenePlayerCount( sceneId )
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 and IsPlayerStateNormal(sceneId,objId) == 1 then
            x300918_ClearTempImpassable_Door2_Effect(sceneId,objId,nIndex)
        end
    end
    
    local msg = format("LBL:x300918_ClearTempImpassable_Door2_Effect sceneId=%d index=%d",sceneId,nIndex)
	WriteLog(1,msg)
end

----------------------------------------------------------------------------------------------
--ͬ�����ֱ仯 
----------------------------------------------------------------------------------------------
function x300918_LairdSyncGuildScore(sceneId)
	
--	local nHumanCount = GetScenePlayerCount( sceneId )
--    for i = 0,nHumanCount-1 do
--        local objId = GetScenePlayerObjId( sceneId,i)
--        if objId >= 0 and IsPlayerStateNormal(sceneId,objId) == 1 then
--            GameBattleSyncScoreInfo(sceneId,objId,x300918_g_ScoreA[sceneId],x300918_g_ScoreB[sceneId],2)
--        end
--    end
	
	
end

----------------------------------------------------------------------------------------------
--���Ͱ���ͬ���� 
----------------------------------------------------------------------------------------------
function x300918_TransGuildMemberToAround(sceneId,selfId,campId,x,z)

	--��Ч�Լ��
	if IsPlayerStateNormal(sceneId,selfId) ~= 1 or GetHp(sceneId,selfId) <= 0 then
		return
	end
	
	--��Ӫ���
	local nSelfCamp = GetCurCamp(sceneId,selfId)
	if nSelfCamp ~= campId then
		return
	end
	
	local msg = "����ʹ��������ս���ټ�,�����ٻ����������!"

	--����
	local nHumanCount = GetScenePlayerCount( sceneId )
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId ~=  selfId and IsPlayerStateNormal(sceneId,objId) == 1 and GetHp(sceneId,objId) > 0 and GetCurCamp(sceneId,objId) == campId then
        	
        	local tx = x + random(-3,3)
        	local tz = z + random(-3,3)
        	
            SetPos(sceneId,objId,tx,tz)
            
            Msg2Player(sceneId, objId, msg, 8, 2)
            Msg2Player(sceneId, objId, msg, 8, 3)
        end
    end	
	
end

----------------------------------------------------------------------------------------------
--ȡ�ð��A�Ļ��� 
----------------------------------------------------------------------------------------------
function x300918_GetBattleScoreA(sceneId)
	return x300918_g_ScoreA[sceneId]
end

----------------------------------------------------------------------------------------------
--ȡ�ð��B�Ļ��� 
----------------------------------------------------------------------------------------------
function x300918_GetBattleScoreB(sceneId)
	return x300918_g_ScoreB[sceneId]
end

----------------------------------------------------------------------------------------------
--���ð��A�Ļ��� 
----------------------------------------------------------------------------------------------
function x300918_SetBattleScoreA(sceneId,nScore)
	
	x300918_g_ScoreA[sceneId] = nScore
	
	if x300918_g_ScoreA[sceneId] < 0 then
		x300918_g_ScoreA[sceneId] = 0 
	end
	
	x300918_LairdSyncGuildScore(sceneId)	
end

----------------------------------------------------------------------------------------------
--���ð��B�Ļ��� 
----------------------------------------------------------------------------------------------
function x300918_SetBattleScoreB(sceneId,nScore)
	x300918_g_ScoreB[sceneId] = nScore
	
	if x300918_g_ScoreB[sceneId] < 0 then
		x300918_g_ScoreB[sceneId] = 0 
	end
	
	x300918_LairdSyncGuildScore(sceneId)	
end


----------------------------------------------------------------------------------------------
--�����¼�-���������¼�A
----------------------------------------------------------------------------------------------
function x300918_ProcAreaEnteredA(sceneId, selfId, zoneId, MissionId)
end

----------------------------------------------------------------------------------------------
--�����¼�-�뿪�����¼�A
----------------------------------------------------------------------------------------------
function x300918_ProcAreaLeavedA(sceneId,selfId,zoneId,MissionId)
end

----------------------------------------------------------------------------------------------
--�����¼�-���������¼�B
----------------------------------------------------------------------------------------------
function x300918_ProcAreaEnteredB(sceneId, selfId, zoneId, MissionId)
end

----------------------------------------------------------------------------------------------
--�����¼�-�뿪�����¼�B
----------------------------------------------------------------------------------------------
function x300918_ProcAreaLeavedB(sceneId,selfId,zoneId,MissionId)
end