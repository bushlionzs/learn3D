--########################################
--##��� 2v2 ս�����ű� by rj 2010-9-24 ##
--########################################

x303101_g_scriptId 					=   303101
x303101_g_GrowPointScriptId         = 	303104
-------------------------------------------------------------
--����A����Ϣ
-------------------------------------------------------------
x303101_TeamInfoA					= 	{}							  
x303101_TeamInfoB					= 	{}

-------------------------------------------------------------
--�ȼ�����
-------------------------------------------------------------									  									  
x303101_LevelFlag					= 	{}

-------------------------------------------------------------
--���������Ϣ
-------------------------------------------------------------									  
x303101_SceneInfo					= 	{}

-------------------------------------------------------------
--�������������Ϣ
-------------------------------------------------------------
x303101_g_SceneMapNavPath			= 	{	{"zhanchang_mshuangrenzhanchang/zhanchang_mshuangrenzhanchang.scn", 1, 1},	--����1
											{"zhanchang_mshuangrenzhanchang/zhanchang_mshuangrenzhanchang.scn", 2, 0},	--����2
											{"zhanchang_mshuangrenzhanchang/zhanchang_mshuangrenzhanchang.scn", 3, 0},	--����3
										}
										
x303101_g_TempImpassable			=	{
											{Left = 89, Top = 71,Right = 168, Bottom = 183, Flag = 1},
										}

-------------------------------------------------------------
--ս������λ����Ϣ
-------------------------------------------------------------
x303101_g_EnterScenePos				=	{
											{ {79, 124}, {79, 131}, {176, 124}, {176, 132} },	--���볡�������꣬������ĳ������Ӧ
											{ {27, 106}, {23, 107}, {101,107}, {104,107} },
											{ {31, 102}, {27, 99}, {93, 28}, {98, 29} },
										}

x303101_g_CloseTick					= 	10														--�رճ�������ʱ
x303101_g_LimitTotalHoldTime		=	4 * 60													--ս�����ʱ��
x303101_g_Kick_Down					=	4														--���˵���ʱ
x303101_g_GameId					=	1221													--�淨ID

-------------------------------------------------------------
--��һ�����Ӫ��Ϣ
-------------------------------------------------------------										
x303101_g_CampFlag					= 	{5, 6}												--������Ӫ��

-------------------------------------------------------------
--�������
-------------------------------------------------------------
x303101_g_Winner_Bonus_Level		= 	1				--��
x303101_g_Winner_Bonus_Mark			= 	30
x303101_g_Loser_Bonus_Level			= 	1				--��
x303101_g_Loser_Bonus_Mark			= 	7
x303101_g_Other_Bonus_Mark			= 	7

-------------------------------------------------------------
--���״̬
-------------------------------------------------------------
x303101_g_State_Invalid				= 	-1
x303101_g_State_Signup				=  	0
x303101_g_State_SignupFinished		=  	1
x303101_g_State_Begin				=  	2
x303101_g_State_End					=  	3
x303101_g_CurrentState				= 	{}

-------------------------------------------------------------
--���buf���࣬������Ҽ���β�ͬ���� 2010-11-3 by rj
-------------------------------------------------------------
x303101_g_RandBuf_40				= 	{30000, 30010, 30020, 30030, 30040, 30050, 30060}
x303101_g_RandBuf_50				= 	{30001, 30011, 30021, 30031, 30041, 30051, 30061}
x303101_g_RandBuf_60				= 	{30002, 30012, 30022, 30032, 30042, 30052, 30062}
x303101_g_RandBuf_70				= 	{30003, 30013, 30023, 30033, 30043, 30053, 30063}
x303101_g_RandBuf_80				= 	{30004, 30014, 30024, 30034, 30044, 30054, 30064}
x303101_g_RandBuf_90				= 	{30005, 30015, 30025, 30035, 30045, 30055, 30065}
x303101_g_RandBuf_100				= 	{30006, 30016, 30026, 30036, 30046, 30056, 30066}
x303101_g_RandBufName				= 	{}				--�ɼ�����buf��Ӧ���֣�key��bufid

-------------------------------------------------------------
--��ý������� 2010-11-3 by rj
-------------------------------------------------------------
x303101_g_Award_ItemID				= 	12266663		--������ƷID
x888888_g_AwardGetBufList			= 	{9011,9012,9013}	--���ƻ����ɻ��buf
x303101_g_Award_LevelInfo			=  					--����������Ϣ����ͬ�����в�ͬ����Ӯ����
{ 
{minlevel = 40, maxlevel = 49, win = 1, lose = 0, normal = 0}, 
{minlevel = 50, maxlevel = 59, win = 1, lose = 0, normal = 0}, 
{minlevel = 60, maxlevel = 69, win = 2, lose = 0, normal = 0}, 
{minlevel = 70, maxlevel = 79, win = 2, lose = 0, normal = 0}, 
{minlevel = 80, maxlevel = 89, win = 3, lose = 0, normal = 0}, 
{minlevel = 90, maxlevel = 99, win = 3, lose = 0, normal = 0}, 
{minlevel = 100, maxlevel = 160, win = 3, lose = 0, normal = 0}, 
}

-------------------------------------------------------------
--�ɼ��������� 2010-11-3 by rj
-------------------------------------------------------------
x303101_g_GrowPoint_RefreshInterval	= 	20				--�ɼ�����ˢ�¼��
x303101_g_GrowPoint_TimerTbl		= 	{}				--�ɼ����䶨ʱ������

-------------------------------------------------------------
--���ս���������� 2010-11-8 by rj
-------------------------------------------------------------
x303101_g_BattleHonour_WinVal		= 	40				--ʤ�����ս������
x303101_g_BattleHonour_NormalVal	= 	10				--ƽ�ֻ��ս������
x303101_g_BattleHonour_LoseVal		= 	10				--��ֻ��ս������

function x303101_OnMapInit(sceneId)
	
	--����A����Ϣ
	x303101_TeamInfoA[sceneId]			= {	
											{GUID = -1, DIE = 0, ENTER = 0,LEAVE = 0 },
											{GUID = -1, DIE = 0, ENTER = 0,LEAVE = 0 }
										  }
	
	--����B����Ϣ
	x303101_TeamInfoB[sceneId]			= {	
											{GUID = -1, DIE = 0, ENTER = 0, LEAVE = 0 },
											{GUID = -1, DIE = 0, ENTER = 0, LEAVE = 0 }
										  }

	--�ȼ�����
	x303101_LevelFlag[sceneId]			= 0
	
	--���������Ϣ
	x303101_SceneInfo[sceneId]			= {
											TICKCOUNT = 0,
											ISCLOSING = 0,
											LEAVECOUNTDOWN = 0,
											RESULT = 0,
											LIMITHOLDTIME = 5 * 60,
										  }
										  
	x303101_g_CurrentState[sceneId]		= x303101_g_State_Invalid
	x303101_g_GrowPoint_TimerTbl[sceneId] = 0
	
	--��ʼ���������buf���֣�key��bufid
	x303101_g_RandBufName[30000] = "��������250��"
	x303101_g_RandBufName[30001] = "��������400��"
	x303101_g_RandBufName[30002] = "��������550��"
	x303101_g_RandBufName[30003] = "��������700��"
	x303101_g_RandBufName[30004] = "��������1000��"
	x303101_g_RandBufName[30005] = "��������1300��"
	x303101_g_RandBufName[30006] = "��������1600��"
	x303101_g_RandBufName[30010] = "��������250��"
	x303101_g_RandBufName[30011] = "��������400��"
	x303101_g_RandBufName[30012] = "��������550��"
	x303101_g_RandBufName[30013] = "��������700��"
	x303101_g_RandBufName[30014] = "��������1000��"
	x303101_g_RandBufName[30015] = "��������1300��"
	x303101_g_RandBufName[30016] = "��������1600��"
	x303101_g_RandBufName[30020] = "Ѫ����������2500��"
	x303101_g_RandBufName[30021] = "Ѫ����������4000��"
	x303101_g_RandBufName[30022] = "Ѫ����������5500��"
	x303101_g_RandBufName[30023] = "Ѫ����������7000��"
	x303101_g_RandBufName[30024] = "Ѫ����������10000��"
	x303101_g_RandBufName[30025] = "Ѫ����������13000��"
	x303101_g_RandBufName[30026] = "Ѫ����������16000��"
	x303101_g_RandBufName[30030] = "��������10��"
	x303101_g_RandBufName[30031] = "��������15��"
	x303101_g_RandBufName[30032] = "��������20��"
	x303101_g_RandBufName[30033] = "��������25��"
	x303101_g_RandBufName[30034] = "��������30��"
	x303101_g_RandBufName[30035] = "��������40��"
	x303101_g_RandBufName[30036] = "��������50��"
	x303101_g_RandBufName[30040] = "��������10��"
	x303101_g_RandBufName[30041] = "��������15��"
	x303101_g_RandBufName[30042] = "��������20��"
	x303101_g_RandBufName[30043] = "��������25��"
	x303101_g_RandBufName[30044] = "��������30��"
	x303101_g_RandBufName[30045] = "��������40��"
	x303101_g_RandBufName[30046] = "��������50��"
	x303101_g_RandBufName[30050] = "��������10��"
	x303101_g_RandBufName[30051] = "��������15��"
	x303101_g_RandBufName[30052] = "��������20��"
	x303101_g_RandBufName[30053] = "��������25��"
	x303101_g_RandBufName[30054] = "��������30��"
	x303101_g_RandBufName[30055] = "��������40��"
	x303101_g_RandBufName[30056] = "��������50��"
	x303101_g_RandBufName[30060] = "��������10��"
	x303101_g_RandBufName[30061] = "��������15��"
	x303101_g_RandBufName[30062] = "��������20��"
	x303101_g_RandBufName[30063] = "��������25��"
	x303101_g_RandBufName[30064] = "��������30��"
	x303101_g_RandBufName[30065] = "��������40��"
	x303101_g_RandBufName[30066] = "��������50��"

end

----------------------------------------------------------------------------------------------
--�����Ʒ
----------------------------------------------------------------------------------------------
function x303101_AddItem(sceneId, playerId, nItemID, nType)

	local nItemNum = 0
	local nPlayerLevel = GetLevel(sceneId, playerId)
	
	--�ҳ�������Ľ�������
    for i, item in x303101_g_Award_LevelInfo do
        if nPlayerLevel >= item.minlevel and nPlayerLevel <= item.maxlevel then
            if nType == 0 then
            	nItemNum = item.normal
            elseif nType == 1 then
            	nItemNum = item.win
            elseif nType == 2 then
            	nItemNum = item.lose
            end
        end
    end
    
	if nItemNum > 0 then
	
		--�����Ƿ���buf������Ƿ�󶨵���Ʒ
		local bHaveBuf = 0
		for i, item in x888888_g_AwardGetBufList do
			if IsHaveSpecificImpact(sceneId, playerId, item) > 0 then
				bHaveBuf = 1
				break
			end
		end
		
		BeginAddItem(sceneId)

		if bHaveBuf == 1 then
			AddItem(sceneId, nItemID, nItemNum)
		else
            AddBindItem(sceneId, nItemID, nItemNum)
		end
		
		if EndAddItem(sceneId, playerId) > 0 then
			AddItemListToPlayer(sceneId, playerId)
	 		WriteLog(1, format("MP2BL:x303101_AddItem 1 SceneId=%d PlayerGUID=%u Param1=%u Param2=%d Param3=%d", 
	 			sceneId, GetGUID(sceneId, playerId), nItemID, nItemNum, nType))
		else
			Msg2Player(sceneId, playerId, "�����������޷���ý�����Ʒ", 8, 3)
			Msg2Player(sceneId, playerId, "�����������޷���ý�����Ʒ", 8, 2)
	 		WriteLog(1, format("MP2BL:x303101_AddItem 2 SceneId=%d PlayerGUID=%u Param1=%u Param2=%d Param3=%d", 
	 			sceneId, GetGUID(sceneId, playerId), nItemID, nItemNum, nType))
		end
	end
end

----------------------------------------------------------------------------------------------
--ȡ��2V2ս������
----------------------------------------------------------------------------------------------
function x303101_GetBattleSceneType(sceneId)

    local name = GetBattleSceneName(sceneId)
    for i, item in x303101_g_SceneMapNavPath do
        if name == item[1] then
            return item[2]
        end
    end
    return -1
end

----------------------------------------------------------------------------------------------
--ս���Ƿ�����
----------------------------------------------------------------------------------------------
function x303101_IsBattleSceneValid(sceneId)

    local name = GetBattleSceneName(sceneId)
    for i, item in x303101_g_SceneMapNavPath do
        if name == item[1] then
            return item[3]
        end
    end
    return 0
end

----------------------------------------------------------------------------------------------
--��������״̬�ص�
----------------------------------------------------------------------------------------------
function x303101_OnMBattleState_SignupScene(sceneId, state)

	--�����Ǳ�������
	if GetSceneType(sceneId) ~= 8 then
		return
	end

	--���״̬����ע�⣬����������ս�������� x303101_g_CurrentState ���������߳������������ݡ�
	if state == x303101_g_State_Signup then

        if x303101_g_CurrentState[sceneId] ~= x303101_g_State_Signup then
            WriteLog(1, format("MP2BL:x303101_g_State_Signup, SceneId=%d", sceneId))
        end
        
        x303101_g_CurrentState[sceneId] = x303101_g_State_Signup
        
    elseif state == x303101_g_State_SignupFinished then

        if x303101_g_CurrentState[sceneId] ~= x303101_g_State_SignupFinished then
            WriteLog(1, format("MP2BL:x303101_g_State_SignupFinished,SceneId=%d", sceneId))
        end
        
        x303101_g_CurrentState[sceneId] = x303101_g_State_SignupFinished
    elseif state == x303101_g_State_Begin then
    
   	 	--�����ս����ʼ�������������ϵ�����������ǩ֤��ʹ�䲻�����Ҫ������
   		CallScriptFunction(MPVP2V2_SIGNUP_SCRIPT, "Set2V2SignAndClean", sceneId)
    end
end

----------------------------------------------------------------------------------------------
--ս��״̬
----------------------------------------------------------------------------------------------
function x303101_OnMBattleState(sceneId, state)

	local sceneType = GetSceneType(sceneId)
	if sceneType == 8 then
		x303101_OnMBattleState_SignupScene(sceneId, state)
	elseif sceneType == 7 then
		x303101_OnBattleState_BattleScene(sceneId, state)
	end
end

----------------------------------------------------------------------------------------------
--ս������״̬����
----------------------------------------------------------------------------------------------
function x303101_OnBattleState_BattleScene(sceneId, state)

	--����Ƿ���PVP2v2������
    if  x303101_GetBattleSceneType(sceneId) <= 0 then
        return
    end
    
    --��鳡���Ƿ���Ч
    if x303101_IsBattleSceneValid(sceneId) ~= 1 then
    	return	
    end

    if state == x303101_g_State_Signup then
    	
    	--����Ƿ��Ѿ���ʼ
    	if x303101_g_CurrentState[sceneId] == x303101_g_State_Begin then
    		return
    	end
    	
        if x303101_g_CurrentState[sceneId] ~= x303101_g_State_Signup then
            WriteLog(1, format("MP2BL:x303101_g_State_Signup, SceneId=%d", sceneId))
        end
        
        --���õ�ǰ����������ʼ��־��������� 2v2 ������ע��
        x303101_g_CurrentState[sceneId] = x303101_g_State_Signup
        MPVP2v2RegisterScene(sceneId)
        
    elseif state == x303101_g_State_Begin then

        if x303101_g_CurrentState[sceneId] ~= x303101_g_State_Begin then
            WriteLog(1, format("MP2BL:x303101_g_State_Begin, SceneId=%d", sceneId))
        end

        --����ս����ʼ״̬��������ʼǰԤ����
        x303101_g_CurrentState[sceneId] = x303101_g_State_Begin
        x303101_OnBattleSceneReady(sceneId, x303101_g_LimitTotalHoldTime)

    elseif state == x303101_g_State_End then

		--�ر�С��ʱ�쳣״̬
        if x303101_g_CurrentState[sceneId] > x303101_g_State_Begin or x303101_g_CurrentState[sceneId] < x303101_g_State_Signup then
            
            WriteLog(1, format("MP2BL:x303101_g_State_End,Result:nState > x303101_g_State_Begin or nState < x303101_g_State_Signup SceneId=%d, state=%d", 
            	sceneId, x303101_g_CurrentState[sceneId]))

            x303101_OnBattleSceneClose(sceneId, 0)
            WriteLog(1, format("MP2BL:x303101_g_State_End, SceneId=%d", sceneId))
            return
        end

        --����״̬��С������������
		x303101_g_CurrentState[sceneId] = x303101_g_State_End
        x303101_OnBattleSceneClose(sceneId, 1)

        WriteLog(1, format("MP2BL:x303101_g_State_End, SceneId=%d", sceneId))
    end
end

----------------------------------------------------------------------------------------------
--ս���Ƿ����ڱ���
----------------------------------------------------------------------------------------------
function x303101_IsBattleSignup(sceneId)

	--�����Ǳ����������Ѿ���ʼ����
	if GetSceneType(sceneId) == 8 and x303101_g_CurrentState[sceneId] == x303101_g_State_Signup then
		return 1
	end
	return 0
end

----------------------------------------------------------------------------------------------
--��������ǩ֤
----------------------------------------------------------------------------------------------
function x303101_SetSignupSign(sceneId, humanId)

	--�Կ�������ǩ֤����¼ǩ֤ʱ��
	SetQuestData(sceneId, humanId, MD_MBATTLE_SIGNSTATE[1], MD_MBATTLE_SIGNSTATE[2], MD_MBATTLE_SIGNSTATE[3], 1)
	SetQuestData(sceneId, humanId, MD_MBATTLE_SIGNTIME[1], MD_MBATTLE_SIGNTIME[2], MD_MBATTLE_SIGNTIME[3], MBATTLE_SIGNUP_SIGNTIME)
end

----------------------------------------------------------------------------------------------
--ս��ƥ�������Ϣ�ص�
----------------------------------------------------------------------------------------------
function x303101_OnMBattleMatchInfo(sceneId, leaderguid1, otherguid1, leaderguid2, otherguid2, nLevelFlag)
	
	--����A����Ϣ
	x303101_TeamInfoA[sceneId]			= {	
											{GUID = leaderguid1, DIE = 0, ENTER = 0, LEAVE = 0},
											{GUID = otherguid1, DIE = 0, ENTER = 0, LEAVE = 0},
										  }

	--����B����Ϣ								  
	x303101_TeamInfoB[sceneId]			= {	
											{GUID = leaderguid2, DIE = 0, ENTER = 0, LEAVE = 0},
											{GUID = otherguid2, DIE = 0, ENTER = 0, LEAVE = 0},
										  }
										  
	--�ȼ�����
	x303101_LevelFlag[sceneId]			= nLevelFlag
	
	--���òɼ����ʼ���������������вɼ���
	CallScriptFunction(x303101_g_GrowPointScriptId, "OnInit", sceneId)
	--���³�ʼ���ɼ���ʱ������	
	x303101_g_GrowPoint_TimerTbl[sceneId] = 0
end

---------------------------------------------------------------------------------------------------
--ȡ��������ڶ���
---------------------------------------------------------------------------------------------------
function x303101_GetPlayerTeamIndex(sceneId, selfId)
	
	local GUID = GetPlayerGUID(sceneId, selfId)
	
	local p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		return 0
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		return 0
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		return 1
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		return 1
	end
	
	return -1
end

---------------------------------------------------------------------------------------------------
--ȡ�����λ��
---------------------------------------------------------------------------------------------------
function x303101_GetPlayerPos(sceneId, selfId)
	
	local GUID = GetPlayerGUID(sceneId, selfId)
	local nIndex = x303101_GetBattleSceneType(sceneId)
	
	--�����Ч
	if nIndex < 1 or nIndex > getn(x303101_g_EnterScenePos) then
		return 100, 100
	end
	
	local p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		local x = x303101_g_EnterScenePos[nIndex][1][1]
		local z = x303101_g_EnterScenePos[nIndex][1][2]
		return x, z
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		local x = x303101_g_EnterScenePos[nIndex][2][1]
		local z = x303101_g_EnterScenePos[nIndex][2][2]
		return x, z
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		local x = x303101_g_EnterScenePos[nIndex][3][1]
		local z = x303101_g_EnterScenePos[nIndex][3][2]
		return x, z
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		local x = x303101_g_EnterScenePos[nIndex][4][1]
		local z = x303101_g_EnterScenePos[nIndex][4][2]
		return x, z
	end
	
	return 100,100
end


---------------------------------------------------------------------------------------------------
--��ҽ���ս��ʱ�Ĵ���
---------------------------------------------------------------------------------------------------
function x303101_OnPlayerEnter(sceneId, selfId)

	--����Ƿ���PVP2v2������
    if x303101_GetBattleSceneType(sceneId) <= 0 then
        return
    end
    
    --��鳡���Ƿ���Ч
    if x303101_IsBattleSceneValid(sceneId) ~= 1 then
    	return	
    end
	
	--ȡ�ñ���Ļ��˳���
    local scenePre = GetPlayerRuntimeData(sceneId,selfId, RD_HUMAN_SCENE_PRE) - 1
    if scenePre >= 0 then
    
        --������˳�����Ϣ
        local CurX = GetPlayerRuntimeData(sceneId, selfId, RD_HUMAN_POSX_PRE)
        local CurZ = GetPlayerRuntimeData(sceneId, selfId, RD_HUMAN_POSZ_PRE)
        SetPlayerBakSceneInfo(sceneId, selfId, scenePre, CurX, CurZ)
        
        SetPlayerRuntimeData(sceneId, selfId, RD_HUMAN_SCENE_PRE, 0)
        SetPlayerRuntimeData(sceneId, selfId, RD_HUMAN_POSX_PRE, 0)
        SetPlayerRuntimeData(sceneId, selfId, RD_HUMAN_POSZ_PRE, 0)
    end
    
	--�ٴ����ߣ������ʼ�رգ�Ҫ�߳�ȥ
	if x303101_SceneInfo[sceneId].ISCLOSING > 0 then
		
		--��ս������������ս���ѽ����ص���������ʱ��Ҫ��������ǩ֤
		x303101_SetPlayerNeedKick(sceneId, selfId)
		WriteLog(1, format("MP2BL:x303101_OnPlayerEnterFinished kick 0 SceneId=%d ", sceneId))
		return
	end
	
	--��������Ч���ٴ����߲��Ǳ�������ң�
	if x303101_CheckPlayerValid(sceneId, selfId) == 0 then
		x303101_SetPlayerNeedKick(sceneId, selfId)
		WriteLog(1, format("MP2BL:x303101_OnPlayerEnterFinished kick 1 SceneId=%d ", sceneId))
		return
	end
	
	--��������������
	if x303101_GetPlayerDieFlag(sceneId, selfId) == 1 then
		x303101_SetPlayerNeedKick(sceneId, selfId)
		WriteLog(1, format("MP2BL:x303101_OnPlayerEnterFinished kick 2 SceneId=%d ", sceneId))		
		return
	end
	
	--�������Ѿ�����������
	if x303101_GetPlayerEnterSceneFlag(sceneId, selfId) == 1 then
		x303101_SetPlayerNeedKick(sceneId, selfId)
		WriteLog(1, format("MP2BL:x303101_OnPlayerEnterFinished kick 3 SceneId=%d ", sceneId))
		return
	end
	
	--��֤���ڶ�������
	local nTeamIndex = x303101_GetPlayerTeamIndex(sceneId, selfId)
	if nTeamIndex < 0 or nTeamIndex > 1 then
		x303101_SetPlayerNeedKick(sceneId, selfId)
		WriteLog(1, format("MP2BL:x303101_OnPlayerEnterFinished kick 4 SceneId=%d ", sceneId))
		return
	end
	
	--���ö�ս��Ӫ�����Ի��࿪������
	SetCurCamp(sceneId, selfId, x303101_g_CampFlag[nTeamIndex + 1])

	--�������λ��
	local x, z = x303101_GetPlayerPos(sceneId, selfId)
	SetPos(sceneId, selfId, x, z)
	
	WriteLog(1, format("MP2BL:x303101_OnPlayerEnterFinished playerEnter SceneId=%d x = %d, z = %d flag = %d name=%s", 
		sceneId, x, z, nTeamIndex, GetName(sceneId, selfId)))
	
	--������ҽ��볡�����
	x303101_SetPlayerEnterSceneFlag(sceneId, selfId)
	
	--�Զ��������������������ɫ
	SetMPVP2v2BattleDisable(sceneId, selfId, 0, nTeamIndex)
	
	--����Ƿ���Բ�����Ч
	if x303101_SceneInfo[sceneId].TICKCOUNT < 31 then
		CallScriptFunction(UTILITY_SCRIPT,"PlayClientMapColor", sceneId, selfId, 0, 0)
	end
	
	--�������buf 2010-11-3 by rj
	-- local nPlayerLevel = GetLevel(sceneId, selfId)
	
	-- local tblBuffer = {}
	
	-- if nPlayerLevel >= 40 and nPlayerLevel <= 49 then
		-- tblBuffer = x303101_g_RandBuf_40
	-- elseif nPlayerLevel >= 50 and nPlayerLevel <= 59 then
		-- tblBuffer = x303101_g_RandBuf_50
	-- elseif nPlayerLevel >= 60 and nPlayerLevel <= 69 then
		-- tblBuffer = x303101_g_RandBuf_60
	-- elseif nPlayerLevel >= 70 and nPlayerLevel <= 79 then
		-- tblBuffer = x303101_g_RandBuf_70
	-- elseif nPlayerLevel >= 80 and nPlayerLevel <= 89 then
		-- tblBuffer = x303101_g_RandBuf_80
	-- elseif nPlayerLevel >= 90 and nPlayerLevel <= 99 then
		-- tblBuffer = x303101_g_RandBuf_90
	-- elseif nPlayerLevel >= 100 then
		-- tblBuffer = x303101_g_RandBuf_100
	-- end
	
	-- local nBufNum = getn(tblBuffer)
	-- if nBufNum > 0 then
		-- local bufIdx = random(1, nBufNum)
		-- SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, tblBuffer[bufIdx], 0)
		-- if x303101_g_RandBufName[tblBuffer[bufIdx]] ~= nil then
			-- Msg2Player(sceneId, selfId, format("����ս����������䵽�ˡ�%s��Ч��", x303101_g_RandBufName[tblBuffer[bufIdx]]), 8, 2)
			-- Msg2Player(sceneId, selfId, format("����ս����������䵽�ˡ�%s��Ч��", x303101_g_RandBufName[tblBuffer[bufIdx]]), 8, 3)	
			-- RestoreHp(sceneId, selfId,0)
			-- RestoreRage(sceneId, selfId,100)
			-- WriteLog(1, format("MP2BL:x303101_OnPlayerEnter 1 SceneId=%d PlayerGUID=%u Param1=%d", sceneId, GetGUID(sceneId, selfId), tblBuffer[bufIdx]))				
		-- end
	-- end
end

---------------------------------------------------------------------------------------------------
--����뿪����
---------------------------------------------------------------------------------------------------
function x303101_OnPlayerLeave(sceneId, selfId)

	local nDebug = 1
	
	if nDebug == 1 then
        WriteLog(1, format("MP2BL:x303101_OnPlayerLeave 0 SceneId=%d Name=%s 2v2 LevelPre = %d", sceneId, GetName(sceneId,selfId), GetPVP2V2Level(sceneId,selfId)))
	end

	--����Ƿ���PVP2v2������
    if  x303101_GetBattleSceneType(sceneId) <= 0 then
        return
    end
    
    --��鳡���Ƿ���Ч
    if x303101_IsBattleSceneValid(sceneId) ~= 1 then
    	return	
    end
	
	--�����ʼ�رգ�������뿪����������������
	if x303101_SceneInfo[sceneId].ISCLOSING > 0 then
		return
	end

	if x303101_GetPlayerLeaveSceneFlag(sceneId, selfId) == 0 then
		
		x303101_SetPlayerLeaveSceneFlag(sceneId, selfId)
		
		local n2v2LevelPre = GetPVP2V2Level(sceneId, selfId)
		
		--��;�˳����Ƿ�ս���ж�ʤ��������£��˳����ȼ���һ�ͷ�
		x303101_SubPVP2V2Level(sceneId, selfId, x303101_g_Loser_Bonus_Level)
		
		local n2v2LevelAfter = GetPVP2V2Level(sceneId,selfId)

        WriteLog(1, format("MP2BL:x303101_OnPlayerLeave 1 SceneId=%d Name=%s 2v2LevelPre = %d 2v2LevelAfter=%d", 
        	sceneId, GetName(sceneId, selfId), n2v2LevelPre, n2v2LevelAfter))
	end	
end

---------------------------------------------------------------------------------------------------
--ս����ʱ��
---------------------------------------------------------------------------------------------------
function x303101_ProcTiming(sceneId, nowTime)

	--����Ƿ���PVP2v2������
    if  x303101_GetBattleSceneType(sceneId) <= 0 then
        return
    end
    
    --��鳡���Ƿ���Ч
    if x303101_IsBattleSceneValid(sceneId) ~= 1 then
    	return	
    end

	x303101_UpdatePlayerKickState(sceneId)

	--�Ѿ���ʼ�ر���
	if x303101_SceneInfo[sceneId].ISCLOSING > 0 then

		local leaveCountDown = x303101_SceneInfo[sceneId].LEAVECOUNTDOWN + 1
		x303101_SceneInfo[sceneId].LEAVECOUNTDOWN = leaveCountDown
		
		if leaveCountDown >= x303101_g_CloseTick then
		
			--����ʱ��������
			local humanCount = GetScenePlayerCount(sceneId)
			for	i = 0, humanCount - 1 do
				local humanId = GetScenePlayerObjId(sceneId, i)
                TimerCommand(sceneId, humanId, 1, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, x303101_g_scriptId, -1, -1)	--���Ͷ�ʱ��������ʱ��ͬ��

                --�������˺���
                x303101_SetPlayerNeedKick(sceneId, humanId)
                WriteLog(1, format("MP2BL:x303101_ProcTiming kick 1 SceneId=%d ", sceneId))
			end
		elseif leaveCountDown < x303101_g_CloseTick then  
		
			--��ʾxx����˳�����
			local humanCount = GetScenePlayerCount(sceneId)
			for	i = 0, humanCount - 1 do
				local humanId = GetScenePlayerObjId(sceneId, i)
  				Msg2Player(sceneId, humanId, format("����ս������%d���ر�", x303101_g_CloseTick - leaveCountDown), 8, 3)
			end			
		end
	else
		if x303101_g_CurrentState[sceneId] ~= x303101_g_State_Begin then
			return
		end
		
		local nowTickCount = x303101_SceneInfo[sceneId].TICKCOUNT + 1;
		x303101_SceneInfo[sceneId].TICKCOUNT = nowTickCount
		
		--����30�룬�����̬�赲
		if nowTickCount == 31 then
			x303101_ClearTempImpassable(sceneId)
		end
			
		--ÿ N ����ս���ǹرյ���ʱ״̬��������ҵ�����½�����Դˢ�£�����ʹ�� nowTickCount ���ֵ����ͬ��ʱ�亯����ʱ�ı������ĳ��ִ�� 2010-11-3 by rj
		x303101_g_GrowPoint_TimerTbl[sceneId] = x303101_g_GrowPoint_TimerTbl[sceneId] + 1
		if mod(x303101_g_GrowPoint_TimerTbl[sceneId], x303101_g_GrowPoint_RefreshInterval) == 0 then
			if GetScenePlayerCount(sceneId) ~= 0 then
				CallScriptFunction(x303101_g_GrowPointScriptId, "OnTimeMakeGrowPoint", sceneId)
			end
		end
		
		--������һ���Ӻ󣬿�ʼ��ʤ�����ճ��������ﱻ�����ɣ��ճ�Ҳ��������ս����ʼ������״̬���� ISCLOSING �ģ�
		if nowTickCount >= 60 then
			if x303101_CheckBattleFinished(sceneId) == 1 then
				x303101_OnBattleSceneClose(sceneId, 2)			
                WriteLog(1, format("MP2BL:x303101_ProcTiming sceneId=%d,nowTickCount=%d 000", sceneId, nowTickCount))
			end
		end

		--ս����ʱ��������������һ��Ϊ 4 ���ӣ���ʱ�ᷢ�� x303101_g_State_End ���н��������з�ֹ��Ϣ�������н�����
		if nowTickCount >= x303101_g_LimitTotalHoldTime then
			local humanCount = GetScenePlayerCount(sceneId)
			for i = 0, humanCount - 1 do
				local humanId = GetScenePlayerObjId(sceneId, i)
  				Msg2Player(sceneId, humanId, format("����ս��ʱ���ѵ�������%d���رգ�", x303101_g_CloseTick), 8, 3)
			end
			
            x303101_OnBattleSceneClose(sceneId, 3)
            WriteLog(1, format("MP2BL:x303101_ProcTiming sceneId=%d, nowTickCount=%d 001", sceneId, nowTickCount))
		end
	end
end

---------------------------------------------------------------------------------------------------
--�������
---------------------------------------------------------------------------------------------------
function x303101_OnPlayerDie(sceneId, selfId, killerId)	
	
	--����Ƿ���PVP2v2������
    if  x303101_GetBattleSceneType(sceneId) <= 0 then
        return
    end
    
    --��鳡���Ƿ���Ч
    if x303101_IsBattleSceneValid(sceneId) ~= 1 then
    	return	
    end
    
	x303101_SetPlayerDieFlag(sceneId, selfId)
	
	--���ս���Ƿ�ɽ���������������⣬����Ҫ��ʱ�� 1 ���Ӻ������
	if x303101_CheckBattleFinished(sceneId) == 1 then
		x303101_OnBattleSceneClose(sceneId, 4)	
        WriteLog(1, format("MP2BL:x303101_OnPlayerDie sceneId=%d  002", sceneId))
	end
end

---------------------------------------------------------------------------------------------------
--��Ҹ���, 2v2 ս����Ҳ�����������
---------------------------------------------------------------------------------------------------
function x303101_OnPlayerRelive(sceneId, selfId, ReliveType)
	
	--����Ƿ���PVP2v2������
    if  x303101_GetBattleSceneType(sceneId) <= 0 then
        return
    end
    
    --��鳡���Ƿ���Ч
    if x303101_IsBattleSceneValid(sceneId) ~= 1 then
    	return	
    end

	--ս�������󲻿ɸ���
	if x303101_SceneInfo[sceneId].ISCLOSING > 0 then
		return
	end
	
  	Msg2Player(sceneId, selfId, "���˫��ս����������֮ǰ���ܸ�������ĵȴ���", 8, 3)
end

---------------------------------------------------------------------------------------------------
--�������ʱʹ��
---------------------------------------------------------------------------------------------------
function x303101_DoPlayerRelive(sceneId, selfId, value)

	--ֻ����������ҽ��д���
	local nHp = GetHp(sceneId, selfId)
	if nHp <= 0 then
	
		ClearRageRecoverTick(sceneId, selfId)
		RestoreHp(sceneId, selfId, value)
		RestoreRage(sceneId, selfId, value)
		ClearMutexState(sceneId, selfId, 6)
		SendReliveResult(sceneId, selfId,1)
	end
	
	--������,���һ�Ѫ
	LastMount(sceneId, selfId)
	RestoreHp(sceneId, selfId, 0)
end

---------------------------------------------------------------------------------------------------
--����
---------------------------------------------------------------------------------------------------
function x303101_KickPlayer(sceneId, selfId)
	
	--��������ǩ֤
	x303101_SetSignupSign(sceneId, selfId)

	--�������״̬
    x303101_DoPlayerRelive(sceneId, selfId, 100)
    x303101_RestorePlayerCamp(sceneId, selfId)
    SetPlayerRuntimeData(sceneId, selfId, RD_BATTLE_SCENE_KICK_DOWN, 0)
    
    --��ԭ������ɫ
    SetMPVP2v2BattleDisable(sceneId, selfId, 1, 0)

	--���������ս���л�õ� buf
	CallScriptFunction(x303101_g_GrowPointScriptId, "RecyclePlayerAllBuf", sceneId, selfId)	
	
	local tblBuffer = {}
	local nPlayerLevel = GetLevel(sceneId, selfId)

	if nPlayerLevel >= 40 and nPlayerLevel <= 49 then
		tblBuffer = x303101_g_RandBuf_40
	elseif nPlayerLevel >= 50 and nPlayerLevel <= 59 then
		tblBuffer = x303101_g_RandBuf_50
	elseif nPlayerLevel >= 60 and nPlayerLevel <= 69 then
		tblBuffer = x303101_g_RandBuf_60
	elseif nPlayerLevel >= 70 and nPlayerLevel <= 79 then
		tblBuffer = x303101_g_RandBuf_70
	elseif nPlayerLevel >= 80 and nPlayerLevel <= 89 then
		tblBuffer = x303101_g_RandBuf_80
	elseif nPlayerLevel >= 90 and nPlayerLevel <= 99 then
		tblBuffer = x303101_g_RandBuf_90
	elseif nPlayerLevel >= 100 then
		tblBuffer = x303101_g_RandBuf_100
	end
	
	for i, item in tblBuffer do
        DispelSpecificImpact(sceneId, selfId, item, 1)
    end
	
    --�������BakScene��Ϣ������BakScene��ϢΪ׼
    local nBakSceneId, x, z = GetPlayerBakSceneInfo(sceneId, selfId)
    if nBakSceneId >= 0 then
        NewWorld(sceneId ,selfId, nBakSceneId, x, z, x303101_g_scriptId)
        return
    end

    --���û�� BakScene ��Ϣ�����͵�����
    local nCountry = GetCurCountry(sceneId,selfId)
    if nCountry == 0 then
        NewWorld(sceneId, selfId, 50, 123, 57, x303101_g_scriptId)
    elseif nCountry == 1 then
        NewWorld(sceneId, selfId, 150, 123, 57, x303101_g_scriptId)
    elseif nCountry == 2 then
        NewWorld(sceneId, selfId, 250, 123, 57, x303101_g_scriptId)
    elseif nCountry == 3 then
        NewWorld(sceneId, selfId, 350, 123, 57, x303101_g_scriptId)
    end
end

---------------------------------------------------------------------------------------------------
--�ָ���Ӫ������ʱʹ��
---------------------------------------------------------------------------------------------------
function x303101_RestorePlayerCamp(sceneId,selfId)
    SetCurCamp(sceneId, selfId, GetCurCountry(sceneId, selfId))
end

---------------------------------------------------------------------------------------------------
--ʱ��ͬ��
---------------------------------------------------------------------------------------------------
function x303101_SyncBattleTimeToAllPlayer(sceneId, nTime)
	
	--����ս�����пͻ���ʱ����ʾ
	local nHumanCount = GetScenePlayerCount(sceneId)
    for i = 0, nHumanCount - 1 do
        local objId = GetScenePlayerObjId(sceneId, i)
        if objId >= 0 then
            TimerCommand(sceneId, objId, 1, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, x303101_g_scriptId, -1, -1)
            if nTime > 0 then
                TimerCommand(sceneId, objId, 2, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, x303101_g_scriptId, nTime, nTime)
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--ʱ��ͬ���ص�
----------------------------------------------------------------------------------------------
function x303101_OnMSyncBattleTime(sceneId, nTime)
    
    --����Ƿ���PVP2v2������
    if  x303101_GetBattleSceneType(sceneId) <= 0 then
        return
    end
    
    --��鳡���Ƿ���Ч
    if x303101_IsBattleSceneValid(sceneId) ~= 1 then
    	return	
    end
    
	--����ս�����пͻ���ʱ����ʾ
    x303101_SceneInfo[sceneId].TICKCOUNT = NumberCastIntToUInt(nTime)
    local DownTickCount = x303101_g_LimitTotalHoldTime - NumberCastIntToUInt(nTime)
    x303101_SyncBattleTimeToAllPlayer(sceneId, DownTickCount)
end

---------------------------------------------------------------------------------------------------
--���ս������
---------------------------------------------------------------------------------------------------
function x303101_CheckBattleFinished(sceneId)

	--1��ֻ��һ����һ���˫����������
	if  x303101_CheckTeamA_AllLeave(sceneId) == 1 or x303101_CheckTeamB_AllLeave(sceneId) == 1 then
		return 1
	end
	
	--2��ĳ����Ҷ�����
	if x303101_CheckTeamA_AllDie(sceneId) == 1 or x303101_CheckTeamB_AllDie(sceneId) == 1 then
		return 1
	end
	
	--3��ֻ��һ�����һ��������һ���뿪���������
	if x303101_CheckTeamA_Live(sceneId) == 0 or x303101_CheckTeamB_Live(sceneId) == 0 then
		return 1
	end
		
	return 0
end

---------------------------------------------------------------------------------------------------
--��ս������
---------------------------------------------------------------------------------------------------
function x303101_GiveBattleBonus(sceneId, nResult)
	
	if nResult == -1 then
		LuaThisScenceM2Wrold(sceneId, "ƽ��", 5, 1)
		x303101_OnGiveTeamA(sceneId, -1)
		x303101_OnGiveTeamB(sceneId, -1)
	elseif nResult == 0 then
		 LuaThisScenceM2Wrold(sceneId, "������ʤ", 5, 1)		
		x303101_OnGiveTeamA(sceneId, 0)
		x303101_OnGiveTeamB(sceneId, 0)
	elseif nResult == 1 then
		 LuaThisScenceM2Wrold(sceneId, "�췽��ʤ", 5, 1)
		x303101_OnGiveTeamA(sceneId, 1)
		x303101_OnGiveTeamB(sceneId, 1)
	end
end

---------------------------------------------------------------------------------------------------
--����A�Ľ���
---------------------------------------------------------------------------------------------------
function x303101_OnGiveTeamA(sceneId, nBonusType)
		
	local humanCount = GetScenePlayerCount(sceneId)
	for	i = 0, humanCount - 1 do
		
		local humanId = GetScenePlayerObjId(sceneId, i)
		if IsPlayerStateNormal(sceneId, humanId) == 1 then
			
			local GUID = GetPlayerGUID(sceneId, humanId)

			local p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][1].GUID)
			if GUID == p then
				
				local name = GetName(sceneId, humanId)
				if name == nil then
					name = "Error "
				end
				
				if nBonusType == -1 then
					
					LuaScenceM2Player(sceneId, humanId, format("#G���#R%d#G��ս������", x303101_g_Other_Bonus_Mark), name, 2, 1)
					x303101_AddPVP2V2Level(sceneId, humanId, 0)
					AddPVP2V2Mark(sceneId, humanId, x303101_g_Other_Bonus_Mark)
					x303101_AddItem(sceneId, humanId, x303101_g_Award_ItemID, 0)
					CallScriptFunction(SCENE_SCRIPT_ID, "AddBattleHonour", sceneId, humanId, x303101_g_BattleHonour_NormalVal)
					
				elseif nBonusType == 0 then			
					
					if x303101_LevelFlag[sceneId] == 1 then
						LuaScenceM2Player(sceneId, humanId, "#Gս���ȼ�������⣨20�����ϣ����޷����ս���ȼ���", name, 2, 1)
					else
						LuaScenceM2Player(sceneId, humanId, format("#Gս���ȼ�+%d", x303101_g_Winner_Bonus_Level), name, 2, 1)
						x303101_AddPVP2V2Level(sceneId, humanId, x303101_g_Winner_Bonus_Level)
					end

					LuaScenceM2Player( sceneId,humanId,format("#G���#R%d#G��ս������",x303101_g_Winner_Bonus_Mark),name,2,1)
					AddPVP2V2Mark(sceneId,humanId,x303101_g_Winner_Bonus_Mark)	
					x303101_AddItem(sceneId, humanId, x303101_g_Award_ItemID, 1)
					CallScriptFunction(SCENE_SCRIPT_ID, "AddBattleHonour", sceneId, humanId, x303101_g_BattleHonour_WinVal)
															
				elseif nBonusType == 1 then
					
					LuaScenceM2Player(sceneId, humanId, format("#Gս���ȼ�-%d", x303101_g_Loser_Bonus_Level), name, 2, 1)
					LuaScenceM2Player(sceneId, humanId, format("#G���#R%d#G��ս������", x303101_g_Loser_Bonus_Mark) ,name, 2, 1)	
					x303101_SubPVP2V2Level(sceneId, humanId, x303101_g_Loser_Bonus_Level)
					AddPVP2V2Mark(sceneId, humanId, x303101_g_Loser_Bonus_Mark)
					x303101_AddItem(sceneId, humanId, x303101_g_Award_ItemID, 2)
					CallScriptFunction(SCENE_SCRIPT_ID, "AddBattleHonour", sceneId, humanId, x303101_g_BattleHonour_LoseVal)
				end
				
			end
			
			p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][2].GUID)
			if GUID == p then
				
				local name = GetName(sceneId, humanId)
				if name == nil then
					name = "Error "
				end
				
				if nBonusType == -1 then
					
					LuaScenceM2Player(sceneId, humanId, format("#G���#R%d#G��ս������", x303101_g_Other_Bonus_Mark), name, 2, 1)
					x303101_AddPVP2V2Level(sceneId, humanId, 0)
					AddPVP2V2Mark(sceneId, humanId, x303101_g_Other_Bonus_Mark)
					x303101_AddItem(sceneId, humanId, x303101_g_Award_ItemID, 0)
					CallScriptFunction(SCENE_SCRIPT_ID, "AddBattleHonour", sceneId, humanId, x303101_g_BattleHonour_NormalVal)
					
				elseif nBonusType == 0 then
					
					if x303101_LevelFlag[sceneId] == 1 then
						LuaScenceM2Player(sceneId, humanId, "#Gս���ȼ�������⣨20�����ϣ����޷����ս���ȼ���", name, 2, 1)
					else
						LuaScenceM2Player(sceneId, humanId, format("#Gս���ȼ�+%d", x303101_g_Winner_Bonus_Level), name, 2, 1)	
						x303101_AddPVP2V2Level(sceneId, humanId, x303101_g_Winner_Bonus_Level)
					end
					
					LuaScenceM2Player(sceneId, humanId, format("#G���#R%d#G��ս������", x303101_g_Winner_Bonus_Mark), name, 2, 1)
					AddPVP2V2Mark(sceneId, humanId, x303101_g_Winner_Bonus_Mark)				
					x303101_AddItem(sceneId, humanId, x303101_g_Award_ItemID, 1)
					CallScriptFunction(SCENE_SCRIPT_ID, "AddBattleHonour", sceneId, humanId, x303101_g_BattleHonour_WinVal)
					
				elseif nBonusType == 1 then
					
					LuaScenceM2Player(sceneId, humanId, format("#Gս���ȼ�-%d", x303101_g_Loser_Bonus_Level), name, 2, 1)
					LuaScenceM2Player(sceneId, humanId, format("#G���#R%d#G��ս������", x303101_g_Loser_Bonus_Mark), name, 2, 1)	
					
					x303101_SubPVP2V2Level(sceneId, humanId, x303101_g_Loser_Bonus_Level)
					AddPVP2V2Mark(sceneId, humanId, x303101_g_Loser_Bonus_Mark)
					x303101_AddItem(sceneId, humanId, x303101_g_Award_ItemID, 2)
					CallScriptFunction(SCENE_SCRIPT_ID, "AddBattleHonour", sceneId, humanId, x303101_g_BattleHonour_LoseVal)
				end
			end
		end
	end
end

---------------------------------------------------------------------------------------------------
--����B�Ľ���
---------------------------------------------------------------------------------------------------
function x303101_OnGiveTeamB( sceneId, nBonusType )

	local humanCount = GetScenePlayerCount(sceneId)
	for	i = 0, humanCount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i)
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			
			local GUID = GetPlayerGUID(sceneId, humanId)

			local p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][1].GUID)
			if GUID == p then
				
				local name = GetName(sceneId, humanId)
				if name == nil then
					name = "Error "
				end
				
				if nBonusType == -1 then
					
					LuaScenceM2Player(sceneId, humanId, format("#G���#R%d#G��ս������", x303101_g_Other_Bonus_Mark), name, 2, 1)
					x303101_AddPVP2V2Level(sceneId, humanId, 0)
					AddPVP2V2Mark(sceneId, humanId, x303101_g_Other_Bonus_Mark)
					x303101_AddItem(sceneId, humanId, x303101_g_Award_ItemID, 0)
					CallScriptFunction(SCENE_SCRIPT_ID, "AddBattleHonour", sceneId, humanId, x303101_g_BattleHonour_NormalVal)
					
				elseif nBonusType == 0 then
					
					LuaScenceM2Player(sceneId, humanId, format("#Gս���ȼ�-%d", x303101_g_Loser_Bonus_Level), name, 2, 1)
					LuaScenceM2Player(sceneId, humanId, format("#G���#R%d#G��ս������", x303101_g_Loser_Bonus_Mark), name, 2, 1)
					x303101_SubPVP2V2Level(sceneId, humanId, x303101_g_Loser_Bonus_Level)
					AddPVP2V2Mark(sceneId, humanId, x303101_g_Loser_Bonus_Mark)
					x303101_AddItem(sceneId, humanId, x303101_g_Award_ItemID, 2)
					CallScriptFunction(SCENE_SCRIPT_ID, "AddBattleHonour", sceneId, humanId, x303101_g_BattleHonour_LoseVal)
					
				elseif nBonusType == 1 then					

					if x303101_LevelFlag[sceneId] == 2 then
						LuaScenceM2Player(sceneId, humanId,"#Gս���ȼ�������⣨20�����ϣ����޷����ս���ȼ���", name, 2, 1)
					else
						LuaScenceM2Player(sceneId, humanId,format("#Gս���ȼ�+%d", x303101_g_Winner_Bonus_Level), name, 2, 1)
						x303101_AddPVP2V2Level(sceneId, humanId, x303101_g_Winner_Bonus_Level)
					end
					
					LuaScenceM2Player(sceneId, humanId, format("#G���#R%d#G��ս������", x303101_g_Winner_Bonus_Mark), name, 2, 1)
					AddPVP2V2Mark(sceneId, humanId, x303101_g_Winner_Bonus_Mark)	
					x303101_AddItem(sceneId, humanId, x303101_g_Award_ItemID, 1)
					CallScriptFunction(SCENE_SCRIPT_ID, "AddBattleHonour", sceneId, humanId, x303101_g_BattleHonour_WinVal)
				end
				
			end
			
			p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][2].GUID)
			if GUID == p then
				
				local name = GetName(sceneId, humanId)
				if name == nil then
					name = "Error "
				end
				
				if nBonusType == -1 then
					
					LuaScenceM2Player(sceneId, humanId, format("#G���#R%d#G��ս������",x303101_g_Other_Bonus_Mark), name, 2, 1)		
					x303101_AddPVP2V2Level(sceneId, humanId, 0)
					AddPVP2V2Mark(sceneId, humanId, x303101_g_Other_Bonus_Mark)	
					x303101_AddItem(sceneId, humanId, x303101_g_Award_ItemID, 0)
					CallScriptFunction(SCENE_SCRIPT_ID, "AddBattleHonour", sceneId, humanId, x303101_g_BattleHonour_NormalVal)
					
				elseif nBonusType == 0 then
					
					LuaScenceM2Player(sceneId, humanId, format("#Gս���ȼ�-%d", x303101_g_Loser_Bonus_Level), name, 2, 1)
					LuaScenceM2Player(sceneId, humanId, format("#G���#R%d#G��ս������", x303101_g_Loser_Bonus_Mark), name, 2, 1)
					x303101_SubPVP2V2Level(sceneId, humanId, x303101_g_Loser_Bonus_Level)
					AddPVP2V2Mark(sceneId, humanId, x303101_g_Loser_Bonus_Mark)
					x303101_AddItem(sceneId, humanId, x303101_g_Award_ItemID, 2)
					CallScriptFunction(SCENE_SCRIPT_ID, "AddBattleHonour", sceneId, humanId, x303101_g_BattleHonour_LoseVal)
					
				elseif nBonusType == 1 then
					
					if x303101_LevelFlag[sceneId] == 2 then
						LuaScenceM2Player(sceneId, humanId, "#Gս���ȼ�������⣨20�����ϣ����޷����ս���ȼ���", name, 2, 1)
					else
						LuaScenceM2Player(sceneId, humanId, format("#Gս���ȼ�+%d", x303101_g_Winner_Bonus_Level), name, 2, 1)
						x303101_AddPVP2V2Level(sceneId, humanId,x303101_g_Winner_Bonus_Level)
					end
					
					LuaScenceM2Player(sceneId, humanId, format("#G���#R%d#G��ս������", x303101_g_Winner_Bonus_Mark), name, 2, 1)	
					AddPVP2V2Mark(sceneId, humanId, x303101_g_Winner_Bonus_Mark)	
					x303101_AddItem(sceneId, humanId, x303101_g_Award_ItemID, 1)
					CallScriptFunction(SCENE_SCRIPT_ID, "AddBattleHonour", sceneId, humanId, x303101_g_BattleHonour_WinVal)
				end
			end
		end
	end
end

---------------------------------------------------------------------------------------------------
--��ս������
---------------------------------------------------------------------------------------------------
function x303101_GenBattleResult(sceneId)

	--����Ѿ���ʼ�رգ������������
	if x303101_SceneInfo[sceneId].ISCLOSING == 1 then
		return
	end
	
	local nResult = -1 

	---------------------------------------------------------------------------------------------------	
	--1��ֻ��һ�����
	---------------------------------------------------------------------------------------------------
	
	--��A������ڣ�B����Ҳ��ڣ���ΪA��Ӯ	
	if  x303101_CheckTeamA_AllLeave(sceneId) == 0 and x303101_CheckTeamB_AllLeave(sceneId) == 1 then
		nResult = 0
		x303101_GiveBattleBonus(sceneId, nResult)
		return
	end
	
	--��A����Ҳ��ڣ�B������ڣ���ΪB��Ӯ
	if  x303101_CheckTeamA_AllLeave(sceneId) == 1 and x303101_CheckTeamB_AllLeave(sceneId) == 0 then
		nResult = 1
		x303101_GiveBattleBonus(sceneId, nResult)
		return
	end
	
	---------------------------------------------------------------------------------------------------
	--2��ĳ����Ҷ�����
	---------------------------------------------------------------------------------------------------
	
	--��A�����û��ȫ������B�����ȫ��������ΪA��Ӯ
	if x303101_CheckTeamA_AllDie(sceneId) == 0 and x303101_CheckTeamB_AllDie(sceneId) == 1 then
		nResult = 0
		x303101_GiveBattleBonus(sceneId, nResult)
		return
	end
	
	--��A�����ȫ������B�����û��ȫ��������ΪB��Ӯ
	if x303101_CheckTeamA_AllDie(sceneId) == 1 and x303101_CheckTeamB_AllDie(sceneId) == 0 then
		nResult = 1
		x303101_GiveBattleBonus(sceneId, nResult)
		return
	end
	
	---------------------------------------------------------------------------------------------------
	--3.���ĳ����һ��ŵ����
	---------------------------------------------------------------------------------------------------
	if x303101_CheckTeamA_Live(sceneId) == 1 and x303101_CheckTeamB_Live(sceneId) == 0 then
		nResult = 0
		x303101_GiveBattleBonus(sceneId, nResult)
		return
	end
	
	if x303101_CheckTeamA_Live(sceneId) == 0 and x303101_CheckTeamB_Live(sceneId) == 1 then
		nResult = 1
		x303101_GiveBattleBonus(sceneId, nResult)
		return
	end
	
	---------------------------------------------------------------------------------------------------
	--4�������ŵ���ҵ�����
	---------------------------------------------------------------------------------------------------
	if x303101_GetTeamA_LiveCount(sceneId) > x303101_GetTeamB_LiveCount(sceneId)  then
		nResult = 0
		x303101_GiveBattleBonus(sceneId, nResult)
		return
	end
	
	if x303101_GetTeamA_LiveCount(sceneId) < x303101_GetTeamB_LiveCount(sceneId)  then
		nResult = 1
		x303101_GiveBattleBonus(sceneId, nResult)
		return
	end	
	
	---------------------------------------------------------------------------------------------------
	--5��������1��2,3,4
	---------------------------------------------------------------------------------------------------
	
	--�����������Ϊսƽ�����û�ˣ�������
	if  x303101_CheckTeamA_AllLeave(sceneId) == 0 and x303101_CheckTeamB_AllLeave(sceneId) == 0 then
		nResult = -1
		x303101_GiveBattleBonus(sceneId, nResult)
		return
	end
		
end


---------------------------------------------------------------------------------------------------
--������A�Ƿ�ȫ���뿪
---------------------------------------------------------------------------------------------------
function x303101_CheckTeamA_AllLeave(sceneId)

	local humanCount = GetScenePlayerCount(sceneId)
	for	i = 0, humanCount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i)
		if IsPlayerStateNormal(sceneId, humanId) == 1 then
			
			local GUID = GetPlayerGUID(sceneId, humanId)
			
			--1
			local p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][1].GUID)
			if GUID == p then
				return 0
			end
			
			--2
			p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][2].GUID)
			if GUID == p then
				return 0
			end
		end
	end
	
	return 1
end

---------------------------------------------------------------------------------------------------
--������A�Ƿ�ȫ���뿪
---------------------------------------------------------------------------------------------------
function x303101_CheckTeamB_AllLeave( sceneId )
	
	local humanCount = GetScenePlayerCount(sceneId)
	for	i = 0, humanCount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i)
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			
			local GUID = GetPlayerGUID(sceneId, humanId)

			--3
			local p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][1].GUID)
			if GUID == p then
				return 0
			end
			
			--4
			p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][2].GUID)
			if GUID == p then
				return 0
			end
		end
	end
	
	return 1
	
end


---------------------------------------------------------------------------------------------------
--������A�Ƿ�ȫ����û
---------------------------------------------------------------------------------------------------
function x303101_CheckTeamA_AllDie(sceneId)
	
	--���м���
	
	local nCount = 0
	if x303101_TeamInfoA[sceneId][1].DIE == 1 then
		nCount = nCount + 1
	end
	
	if x303101_TeamInfoA[sceneId][2].DIE == 1 then
		nCount = nCount + 1
	end
	
	--������Ϊ2��ʾA����Ҷ�����
	if nCount == 2 then
		return 1
	end
	
	return 0
end

---------------------------------------------------------------------------------------------------
--���A�ӻ��ŵ����
---------------------------------------------------------------------------------------------------
function x303101_CheckTeamA_Live(sceneId)
	
	--���ֻ��һ����ң����ж�������������
	local nLiveCount = 0
	local humanCount = GetScenePlayerCount(sceneId)
	
	for	i = 0, humanCount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i)
		if IsPlayerStateNormal(sceneId, humanId) == 1 then
			
			local GUID = GetPlayerGUID(sceneId, humanId)

			--1
			local p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][1].GUID)
			if GUID == p then
				if x303101_TeamInfoA[sceneId][1].DIE ~= 1 then
					nLiveCount = nLiveCount + 1
				end
			end

			--2
			p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][2].GUID)
			if GUID == p then
				if x303101_TeamInfoA[sceneId][2].DIE ~= 1 then
					nLiveCount = nLiveCount + 1
				end
			end
		end
	end

	if nLiveCount == 0 then
		return 0				
	end

	return 1
end

---------------------------------------------------------------------------------------------------
--���B�ӻ��ŵ����
---------------------------------------------------------------------------------------------------
function x303101_CheckTeamB_Live(sceneId)
	
	--���ֻ��һ����ң����ж�������������
	local nLiveCount = 0
	local humanCount = GetScenePlayerCount(sceneId);
	
	for	i = 0, humanCount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i)
		if IsPlayerStateNormal(sceneId, humanId) == 1 then
			
			local GUID = GetPlayerGUID(sceneId, humanId)
			
			--1
			local p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][1].GUID)
			if GUID == p then
				if x303101_TeamInfoB[sceneId][1].DIE ~= 1 then
					nLiveCount = nLiveCount + 1
				end
			end
			
			--2
			p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][2].GUID)
			if GUID == p then
				if x303101_TeamInfoB[sceneId][2].DIE ~= 1 then
					nLiveCount = nLiveCount + 1
				end
			end
		end
	end
	
	if nLiveCount == 0 then
		return 0				
	end
	
	return 1
end

---------------------------------------------------------------------------------------------------
--ȡ��A�ӻ��ŵ���ҵ�����
---------------------------------------------------------------------------------------------------
function x303101_GetTeamA_LiveCount(sceneId)
	
	--���ֻ��һ����ң����ж�������������
	local nLiveCount = 0
	local humanCount = GetScenePlayerCount(sceneId)
	
	for	i = 0, humanCount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i)
		if IsPlayerStateNormal(sceneId, humanId) == 1 then
			
			local GUID = GetPlayerGUID(sceneId, humanId)
			
			--1
			local p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][1].GUID)
			if GUID == p then
				if x303101_TeamInfoA[sceneId][1].DIE ~= 1 then
					nLiveCount = nLiveCount + 1
				end
			end
			
			--2
			p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][2].GUID)
			if GUID == p then
				if x303101_TeamInfoA[sceneId][2].DIE ~= 1 then
					nLiveCount = nLiveCount + 1
				end
			end
		end
	end
	
	return nLiveCount
end

---------------------------------------------------------------------------------------------------
--ȡ��B�ӻ��ŵ���ҵ�����
---------------------------------------------------------------------------------------------------
function x303101_GetTeamB_LiveCount(sceneId)
	
	--���ֻ��һ����ң����ж�������������
	local nLiveCount = 0
	local humanCount = GetScenePlayerCount(sceneId)
	
	for	i = 0, humanCount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i)
		if IsPlayerStateNormal(sceneId, humanId ) == 1 then
			
			local GUID = GetPlayerGUID( sceneId,humanId )
			
			--1
			local p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][1].GUID)
			if GUID == p then
				if x303101_TeamInfoB[sceneId][1].DIE ~= 1 then
					nLiveCount = nLiveCount + 1
				end
			end
			
			--2
			p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][2].GUID)
			if GUID == p then
				if x303101_TeamInfoB[sceneId][2].DIE ~= 1 then
					nLiveCount = nLiveCount + 1
				end
			end
		end
	end
	
	return nLiveCount
end



---------------------------------------------------------------------------------------------------
--������B�Ƿ�ȫ����û
---------------------------------------------------------------------------------------------------
function x303101_CheckTeamB_AllDie(sceneId)
	
	--���м���
	
	local nCount = 0
	if x303101_TeamInfoB[sceneId][1].DIE == 1 then
		nCount = nCount + 1
	end
	
	if x303101_TeamInfoB[sceneId][2].DIE == 1 then
		nCount = nCount + 1
	end
	
	--������Ϊ2��ʾB����Ҷ�����
	if nCount == 2 then
		return 1
	end
	
	return 0
end


---------------------------------------------------------------------------------------------------
--��������Ч��
---------------------------------------------------------------------------------------------------
function x303101_CheckPlayerValid(sceneId, selfId)
	
	local GUID = GetPlayerGUID(sceneId, selfId)

	local p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		return 1
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		return 1
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		return 1
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		return 1
	end
	
	return 0
end

---------------------------------------------------------------------------------------------------
--ȡ������������
---------------------------------------------------------------------------------------------------
function x303101_GetPlayerDieFlag(sceneId, selfId)
	
	local GUID = GetPlayerGUID(sceneId, selfId)

	local p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		return x303101_TeamInfoA[sceneId][1].DIE;
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		return x303101_TeamInfoA[sceneId][2].DIE;
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		return x303101_TeamInfoB[sceneId][1].DIE;
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		return x303101_TeamInfoB[sceneId][2].DIE;
	end
	
	return 1
end

---------------------------------------------------------------------------------------------------
--��������������
---------------------------------------------------------------------------------------------------
function x303101_SetPlayerDieFlag(sceneId, selfId)

	local GUID = GetPlayerGUID(sceneId, selfId)

	local p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		x303101_TeamInfoA[sceneId][1].DIE = 1
		return
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		x303101_TeamInfoA[sceneId][2].DIE = 1
		return
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		x303101_TeamInfoB[sceneId][1].DIE = 1
		return
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		x303101_TeamInfoB[sceneId][2].DIE = 1
		return
	end
end

---------------------------------------------------------------------------------------------------
--ȡ����ҽ���ս�����
---------------------------------------------------------------------------------------------------
function x303101_GetPlayerEnterSceneFlag(sceneId, selfId)

	local GUID = GetPlayerGUID(sceneId, selfId)

	local p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		return x303101_TeamInfoA[sceneId][1].ENTER
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		return x303101_TeamInfoA[sceneId][2].ENTER
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		return x303101_TeamInfoB[sceneId][1].ENTER
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		return x303101_TeamInfoB[sceneId][2].ENTER
	end
	
	return 1
end

---------------------------------------------------------------------------------------------------
--������ҽ���ս�����
---------------------------------------------------------------------------------------------------
function x303101_SetPlayerEnterSceneFlag(sceneId, selfId)

	--������ҽ�����
	local GUID = GetPlayerGUID(sceneId, selfId)

	local p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		x303101_TeamInfoA[sceneId][1].ENTER = 1
		return
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		x303101_TeamInfoA[sceneId][2].ENTER = 1
		return
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		x303101_TeamInfoB[sceneId][1].ENTER = 1
		return
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		x303101_TeamInfoB[sceneId][2].ENTER = 1
		return
	end
end

---------------------------------------------------------------------------------------------------
--ȡ������뿪ս�����
---------------------------------------------------------------------------------------------------
function x303101_GetPlayerLeaveSceneFlag(sceneId, selfId)

	local GUID = GetPlayerGUID(sceneId, selfId)

	local p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		return x303101_TeamInfoA[sceneId][1].LEAVE
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		return x303101_TeamInfoA[sceneId][2].LEAVE
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		return x303101_TeamInfoB[sceneId][1].LEAVE
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		return x303101_TeamInfoB[sceneId][2].LEAVE
	end
	
	return 1
end

---------------------------------------------------------------------------------------------------
--������ҽ���ս�����
---------------------------------------------------------------------------------------------------
function x303101_SetPlayerLeaveSceneFlag(sceneId, selfId)

	--������ҽ�����
	local GUID = GetPlayerGUID(sceneId, selfId)

	local p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		x303101_TeamInfoA[sceneId][1].LEAVE = 1
		return
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		x303101_TeamInfoA[sceneId][2].LEAVE = 1
		return
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		x303101_TeamInfoB[sceneId][1].LEAVE = 1
		return
	end
	
	p = NumberCastIntToUInt(x303101_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		x303101_TeamInfoB[sceneId][2].LEAVE = 1
		return
	end
end

---------------------------------------------------------------------------------------------------
--ս��׼������
---------------------------------------------------------------------------------------------------
function x303101_OnBattleSceneReady(sceneId, nTotalTime)
	
	--���������Ϣ							  
	x303101_SceneInfo[sceneId] = {
						TICKCOUNT = 0,
						ISCLOSING = 0,
						LEAVECOUNTDOWN = 0,
						RESULT = 0,
						LIMITHOLDTIME = nTotalTime,
				  	  }
				  	  
	local msg = format("MP2BL:x303101_OnBattleSceneReady SceneId=%d", sceneId)
	WriteLog(1, msg)
	
	--���ö�̬�赲
	x303101_SetTempImpassable(sceneId)
end

---------------------------------------------------------------------------------------------------
--ս���ر�
---------------------------------------------------------------------------------------------------
function x303101_OnBattleSceneClose(sceneId, flag)
	
	x303101_GenBattleResult(sceneId)
	
	if x303101_SceneInfo[sceneId].ISCLOSING == 1 then
		return
	end
	
	--���òɼ����ʼ���������������вɼ���
	CallScriptFunction(x303101_g_GrowPointScriptId, "OnInit", sceneId)	
	
	--���������Ϣ							  
	x303101_SceneInfo[sceneId].ISCLOSING = 1	
	x303101_SceneInfo[sceneId].TICKCOUNT = 0
	local msg = format("MP2BL:x303101_OnBattleSceneClose SceneId=%d flag=%d", sceneId, flag)
	WriteLog(1, msg)
end

---------------------------------------------------------------------------------------------------
--������ƥ��ص�
---------------------------------------------------------------------------------------------------
function x303101_OnMBattleMatchOOD(sceneId, selfId)
		
	--��������ǩ֤
	SetQuestData(sceneId, selfId, MD_MBATTLE_SIGNSTATE[1], MD_MBATTLE_SIGNSTATE[2], MD_MBATTLE_SIGNSTATE[3], 1)
	SetQuestData(sceneId, selfId, MD_MBATTLE_SIGNTIME[1], MD_MBATTLE_SIGNTIME[2], MD_MBATTLE_SIGNTIME[3], MBATTLE_SIGNUP_SIGNTIME)

	local name = GetName(sceneId, selfId)
	LuaScenceM2Player(sceneId, selfId, "˫��ս���������ڵĶ��鱾���ֿգ�", name, 2, 1)	
	LuaScenceM2Player(sceneId, selfId, "˫��ս���������ڵĶ��鱾���ֿգ�", name, 3, 1)
end

---------------------------------------------------------------------------------------------------
--���������Ҫ�߳�ȥ
---------------------------------------------------------------------------------------------------
function x303101_SetPlayerNeedKick(sceneId, selfId)
	
	local KickDown = GetPlayerRuntimeData(sceneId, selfId, RD_BATTLE_SCENE_KICK_DOWN) 
    if KickDown <= 0 or KickDown > x303101_g_Kick_Down then                
        SetPlayerRuntimeData(sceneId, selfId, RD_BATTLE_SCENE_KICK_DOWN, x303101_g_Kick_Down) 
    end
end

----------------------------------------------------------------------------------------------
--�������������Ҫ�ߵ�
----------------------------------------------------------------------------------------------
function x303101_SetAllPlayerNeedKick(sceneId)
    
    local nHumanCount = GetScenePlayerCount(sceneId)
    for i = 0, nHumanCount - 1 do
        local objId = GetScenePlayerObjId(sceneId, i)
        if objId >= 0 then
            local KickDown = GetPlayerRuntimeData(sceneId, objId, RD_BATTLE_SCENE_KICK_DOWN) 
            if KickDown <= 0 or KickDown > x303101_g_Kick_Down then                
                SetPlayerRuntimeData(sceneId, objId, RD_BATTLE_SCENE_KICK_DOWN, x303101_g_Kick_Down) 
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--��������ߵ�״̬
----------------------------------------------------------------------------------------------
function x303101_UpdatePlayerKickState(sceneId)
    
    local nHumanCount = GetScenePlayerCount(sceneId)
    for i = 0, nHumanCount - 1 do
        local objId = GetScenePlayerObjId(sceneId, i)
        if objId >= 0 then
            local KickDown = GetPlayerRuntimeData(sceneId, objId, RD_BATTLE_SCENE_KICK_DOWN) 
            if KickDown > 0 then                
                KickDown = KickDown - 1 
                if KickDown == 0 then
                    --����ʱΪ�㣬�ߵ�
                    SetPlayerRuntimeData(sceneId, objId, RD_BATTLE_SCENE_KICK_DOWN, -1) 
                    x303101_KickPlayer(sceneId,objId )                    
                else
                    --���򣬼�������ʱ
                    SetPlayerRuntimeData(sceneId, objId, RD_BATTLE_SCENE_KICK_DOWN, KickDown) 
                end
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--���ɶ�̬�赲
----------------------------------------------------------------------------------------------
function x303101_SetTempImpassable(sceneId)
	
	local nIndex = x303101_GetBattleSceneType(sceneId)
	
	for i,itm in x303101_g_TempImpassable do
		if itm.Flag == nIndex then
			AddSceneTempImpassable(sceneId, itm.Left, itm.Top, itm.Right, itm.Bottom)
		end
	end
	
end

----------------------------------------------------------------------------------------------
--ɾ����̬�赲
----------------------------------------------------------------------------------------------
function x303101_ClearTempImpassable(sceneId)
	
	LuaThisScenceM2Wrold(sceneId, "ս����ʼ", 5, 1)
	
	local nIndex = x303101_GetBattleSceneType(sceneId)
	
	for i, itm in x303101_g_TempImpassable do
		if itm.Flag == nIndex then
			DelSceneTempImpassable(sceneId, itm.Left, itm.Top, itm.Right, itm.Bottom)
		end
	end
	
	--�����Ч
	local nHumanCount = GetScenePlayerCount(sceneId)
    for i = 0, nHumanCount - 1 do
        local objId = GetScenePlayerObjId(sceneId, i)
        if objId >= 0 then
            CallScriptFunction(UTILITY_SCRIPT, "StopClientMapColor", sceneId, objId, 0)
        end
    end
end

function x303101_AddPVP2V2Level(mapId, playerId, delta)

	local day = GetQuestData(mapId, playerId, MD_PVP2V2_LEVEL_DAY[1], MD_PVP2V2_LEVEL_DAY[2], MD_PVP2V2_LEVEL_DAY[3])
	local curday = GetWeekFirstDay()
	if day ~= curday then
		local value = GetPVP2V2Level(mapId, playerId)
		SubPVP2V2Level(mapId, playerId, value)
		AddPVP2V2Level(mapId, playerId, 500)
		SetQuestData(mapId, playerId, MD_PVP2V2_LEVEL_DAY[1], MD_PVP2V2_LEVEL_DAY[2], MD_PVP2V2_LEVEL_DAY[3], curday)
	end	
	AddPVP2V2Level(mapId, playerId, delta)
end

function x303101_SubPVP2V2Level(mapId, playerId, delta)

	local day = GetQuestData(mapId, playerId, MD_PVP2V2_LEVEL_DAY[1], MD_PVP2V2_LEVEL_DAY[2], MD_PVP2V2_LEVEL_DAY[3])
	local curday = GetWeekFirstDay()
	if day ~= curday then
		local value = GetPVP2V2Level(mapId, playerId)
		SubPVP2V2Level(mapId, playerId, value)
		AddPVP2V2Level(mapId, playerId, 500)
		SetQuestData(mapId, playerId, MD_PVP2V2_LEVEL_DAY[1], MD_PVP2V2_LEVEL_DAY[2], MD_PVP2V2_LEVEL_DAY[3], curday)
	end	
	SubPVP2V2Level(mapId, playerId, delta)
end

---------------------------------------------------------------------------------------------------
--������븱��
---------------------------------------------------------------------------------------------------
function x303101_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 0
end
----------------------------------------------------------------------------------------------
--��ȷ����
----------------------------------------------------------------------------------------------
function x303101_ProcAccept( sceneId, selfId )
end
----------------------------------------------------------------------------------------------
--Ĭ�϶Ի�
----------------------------------------------------------------------------------------------
function x303101_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)	
end
---------------------------------------------------------------------------------------------------
--��������
---------------------------------------------------------------------------------------------------
function x303101_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
---------------------------------------------------------------------------------------------------
--�뿪����
---------------------------------------------------------------------------------------------------
function x303101_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
end