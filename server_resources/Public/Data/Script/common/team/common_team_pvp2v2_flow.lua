x303001_g_scriptId 					=   303001

-------------------------------------------------------------
--����A����Ϣ
-------------------------------------------------------------
x303001_TeamInfoA					= {}							  
x303001_TeamInfoB					= {}
									  
-------------------------------------------------------------
--�ȼ�����
-------------------------------------------------------------									  									  
x303001_LevelFlag					= {}

-------------------------------------------------------------
--���������Ϣ
-------------------------------------------------------------									  
x303001_SceneInfo					= {}

-------------------------------------------------------------
--�������������Ϣ
-------------------------------------------------------------
x303001_g_SceneMapNavPath			= 	{	{"zhanchang_shuangrenzhanchang/zhanchang_shuangrenzhanchang.scn",	1,1},	--����1
											{"zhanchang_shuangrenzhanchang/zhanchang_shuangrenzhanchang.scn",	2,0},	--����2
											{"zhanchang_shuangrenzhanchang/zhanchang_shuangrenzhanchang.scn",	3,0},	--����3
										}
										
x303001_g_TempImpassable			=	{
											{Left = 89,Top = 71,Right =  168,Bottom = 183,Flag=1},
										}

-------------------------------------------------------------
--ս������λ����Ϣ
-------------------------------------------------------------
x303001_g_EnterScenePos				=	{
											{ {79, 124},{79, 131},{ 176, 124},{ 176, 132}	},		--���볡�������꣬������ĳ������Ӧ
											{ {27,106},{23,107},{101,107},{104,107}	},
											{ {31,102},{27, 99},{ 93, 28},{ 98, 29} },
										}
										
x303001_g_CloseTick					= 	10													--�رճ�������ʱ
x303001_g_LimitTotalHoldTime		=	4*60												--ս�����ʱ��

x303001_g_Kick_Down					=	4													--���˵���ʱ

x303001_g_GameId					=	1221												--�淨ID

-------------------------------------------------------------
--��һ�����Ӫ��Ϣ
-------------------------------------------------------------										
x303001_g_CampFlag					= { 5, 6 }												--������Ӫ��


-------------------------------------------------------------
--�������
-------------------------------------------------------------
x303001_g_Winner_Bonus_Level		= 1				--��
x303001_g_Winner_Bonus_Mark			= 30

x303001_g_Loser_Bonus_Level			= 1				--��
x303001_g_Loser_Bonus_Mark			= 7

x303001_g_Other_Bonus_Mark			= 7


-------------------------------------------------------------
--���״̬
-------------------------------------------------------------
x303001_g_State_Invalid				= -1
x303001_g_State_Signup				=  0
x303001_g_State_SignupFinished		=  1
x303001_g_State_Begin				=  2
x303001_g_State_End					=  3

x303001_g_CurrentState				= {}



function x303001_OnMapInit(sceneId)
	
	--����A����Ϣ
	x303001_TeamInfoA[sceneId]			= {	
											{GUID=-1,DIE=0,ENTER=0,LEAVE=0 },
											{GUID=-1,DIE=0,ENTER=0,LEAVE=0 }
										  }
	
	--����B����Ϣ
	x303001_TeamInfoB[sceneId]			= {	
											{GUID=-1,DIE=0,ENTER=0,LEAVE=0 },
											{GUID=-1,DIE=0,ENTER=0,LEAVE=0 }
										  }
										  
	--�ȼ�����
	x303001_LevelFlag[sceneId]			= 0
	
	--���������Ϣ
	x303001_SceneInfo[sceneId]			= {
											TICKCOUNT = 0,
											ISCLOSING = 0,
											LEAVECOUNTDOWN = 0,
											RESULT = 0,
											LIMITHOLDTIME = 5*60,
										  }
										  
	x303001_g_CurrentState[sceneId]		= x303001_g_State_Invalid
	
	
	
end

----------------------------------------------------------------------------------------------
--ȡ��2V2ս������
----------------------------------------------------------------------------------------------
function x303001_GetBattleSceneType(sceneId)

    local name = GetBattleSceneName(sceneId)
    for i,item in x303001_g_SceneMapNavPath do
        if name == item[1] then
            return item[2]
        end
    end

    return -1
	
end

----------------------------------------------------------------------------------------------
--ս���Ƿ�����
----------------------------------------------------------------------------------------------
function x303001_IsBattleSceneValid(sceneId)

    local name = GetBattleSceneName(sceneId)
    for i,item in x303001_g_SceneMapNavPath do
        if name == item[1] then
            return item[3]
        end
    end

    return 0
	
end

----------------------------------------------------------------------------------------------
--��ͨ����״̬����
----------------------------------------------------------------------------------------------
function x303001_OnBattleState_NormalScene(sceneId,state)

	--�޶�Ϊ�󶼺�����
	if sceneId ~= 0 and sceneId ~= 50 and sceneId ~= 150 and sceneId ~= 250 and sceneId ~= 350 then
		return
	end

	--���״̬����
	if state == x303001_g_State_Signup then

        if x303001_g_CurrentState[sceneId] ~= x303001_g_State_Signup then
            local msg = format("P2BL:x303001_g_State_Signup,SceneId=%d ",sceneId  )
            WriteLog(1,msg)
        end
        
        x303001_g_CurrentState[sceneId] = x303001_g_State_Signup
        
    elseif state == x303001_g_State_SignupFinished then

        if x303001_g_CurrentState[sceneId] ~= x303001_g_State_SignupFinished then
            local msg = format("P2BL:x303001_g_State_SignupFinished,SceneId=%d ",sceneId )
            WriteLog(1,msg)
        end
        
        x303001_g_CurrentState[sceneId] = x303001_g_State_SignupFinished            
        
--    elseif state == x303001_g_State_Begin then
--
--        if x303001_g_CurrentState[sceneId] ~= x303001_g_State_Begin then
--            local msg = format("P2BL:x303001_g_State_Begin,SceneId=%d ",sceneId )
--            WriteLog(1,msg)
--        end
--        
--        x303001_g_CurrentState[sceneId] = x303001_g_State_Begin
--
--    elseif state == x303001_g_State_End then
--        x303001_g_CurrentState[sceneId] = x303001_g_State_End
--
--        --��¼��־
--        local msg = format("P2BL:x303001_g_State_End, SceneId=%d",sceneId )
--        WriteLog(1,msg)

    end
    
end

----------------------------------------------------------------------------------------------
--ս������״̬����
----------------------------------------------------------------------------------------------
function x303001_OnBattleState_BattleScene(sceneId,state)

	--����Ƿ���PVP2v2������
    local nBattleScene = x303001_GetBattleSceneType( sceneId )
    if  nBattleScene <= 0 then
        return
    end
    
    --��鳡���Ƿ���Ч
    local nBattleSceneValid = x303001_IsBattleSceneValid(sceneId)
    if nBattleSceneValid ~= 1 then
    	return	
    end

    if state == x303001_g_State_Signup then
    	
    	--����Ѿ���ʼ�����⴦��һ��
    	if x303001_g_CurrentState[sceneId] == x303001_g_State_Begin then
    		return
    	end
    	
        if x303001_g_CurrentState[sceneId] ~= x303001_g_State_Signup then
            local msg = format("P2BL:x303001_g_State_Signup,SceneId=%d,2 ",sceneId  )
            WriteLog(1,msg)
        end
        
        x303001_g_CurrentState[sceneId] = x303001_g_State_Signup
        PVP2v2RegisterScene( sceneId )

--    elseif state == x303001_g_State_SignupFinished then
--
--        --���״̬�Ƿ��Ѿ��ù�
--        if x303001_g_CurrentState[sceneId] ~= x303001_g_State_SignupFinished then
--            local msg = format("P2BL:x303001_g_State_SignupFinished,SceneId=%d,2",sceneId )
--            WriteLog(1,msg)
--        end
--
--        --���û�������
--        x303001_g_CurrentState[sceneId] = x303001_g_State_SignupFinished

    elseif state == x303001_g_State_Begin then

        --���״̬�Ƿ��Ѿ��ù�
        if x303001_g_CurrentState[sceneId] ~= x303001_g_State_Begin then
            local msg = format("P2BL:x303001_g_State_Begin,SceneId=%d,2",sceneId )
            WriteLog(1,msg)
        end

        --���û�������            
        x303001_g_CurrentState[sceneId] = x303001_g_State_Begin
        x303001_OnBattleSceneReady( sceneId,x303001_g_LimitTotalHoldTime )

    elseif state == x303001_g_State_End then

        if x303001_g_CurrentState[sceneId] > x303001_g_State_Begin or x303001_g_CurrentState[sceneId] < x303001_g_State_Signup then
            
            --��¼��־
            local msg = format("P2BL:x303001_g_State_End,Result:nState > x303001_g_State_Begin or nState < x303001_g_State_Signup  SceneId=%d,state=%d,2",sceneId, x303001_g_CurrentState[sceneId] )
            WriteLog(1,msg)

            --�����淨�Ľű��Ĳ�ͬ��������س�ʼ���ص�
            x303001_OnBattleSceneClose( sceneId,0 )

            --��¼��־
            local msg = format("P2BL:x303001_g_State_End, SceneId=%d,2",sceneId )
            WriteLog(1,msg)
            return
        end

        --����״̬�������
		x303001_g_CurrentState[sceneId] = x303001_g_State_End
        x303001_OnBattleSceneClose( sceneId,1 )

        --��¼��־
        local msg = format("P2BL:x303001_g_State_End, SceneId=%d,2",sceneId )
        WriteLog(1,msg)
    end
end

----------------------------------------------------------------------------------------------
--ս��״̬
----------------------------------------------------------------------------------------------
function x303001_OnBattleState(sceneId,state)

	local sceneType = GetSceneType(sceneId);
	if sceneType == 0 then
		x303001_OnBattleState_NormalScene(sceneId,state)
	elseif sceneType == 2 then
		x303001_OnBattleState_BattleScene(sceneId,state)
	end
end


----------------------------------------------------------------------------------------------
--ս���Ƿ����ڱ���
----------------------------------------------------------------------------------------------
function x303001_IsBattleSignup( sceneId )

	if sceneId == 0  or sceneId == 50 or sceneId == 150 or sceneId == 250 or sceneId == 350 then
		if x303001_g_CurrentState[sceneId] == x303001_g_State_Signup then
			return 1
		end
	end
	
	return 0
	
end

----------------------------------------------------------------------------------------------
--����ս������
----------------------------------------------------------------------------------------------
function x303001_OnBattleMatchInfo( sceneId, leaderguid1,otherguid1,leaderguid2,otherguid2,nLevelFlag )
	
	--����A����Ϣ
	x303001_TeamInfoA[sceneId]			= {	
											{GUID=leaderguid1,DIE=0,ENTER=0,LEAVE=0 },
											{GUID=otherguid1, DIE=0,ENTER=0,LEAVE=0 },
										  }

	--����B����Ϣ								  
	x303001_TeamInfoB[sceneId]			= {	
											{GUID=leaderguid2,DIE=0,ENTER=0,LEAVE=0 },
											{GUID=otherguid2, DIE=0,ENTER=0,LEAVE=0 },
										  }
										  
	--�ȼ�����
	x303001_LevelFlag[sceneId]			= nLevelFlag
end

---------------------------------------------------------------------------------------------------
--ȡ�������Ӫ
---------------------------------------------------------------------------------------------------
function x303001_GetPlayerCampFlag( sceneId,selfId)
	
	local GUID = GetPlayerGUID(sceneId,selfId)
	
	local p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		return 0
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		return 0
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		return 1
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		return 1
	end
	
	return -1
	
end

---------------------------------------------------------------------------------------------------
--�������λ��
---------------------------------------------------------------------------------------------------
function x303001_GetPlayerPos( sceneId,selfId )
	
	local GUID = GetPlayerGUID(sceneId,selfId)
	local nIndex = x303001_GetBattleSceneType(sceneId)
	
	--�����Ч
	if nIndex < 1 or nIndex > getn(x303001_g_EnterScenePos) then
		return 100,100
	end
	
	local p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		local x = x303001_g_EnterScenePos[nIndex][1][1]
		local z = x303001_g_EnterScenePos[nIndex][1][2]
		return x,z
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		local x = x303001_g_EnterScenePos[nIndex][2][1]
		local z = x303001_g_EnterScenePos[nIndex][2][2]
		return x,z
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		local x = x303001_g_EnterScenePos[nIndex][3][1]
		local z = x303001_g_EnterScenePos[nIndex][3][2]
		return x,z
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		local x = x303001_g_EnterScenePos[nIndex][4][1]
		local z = x303001_g_EnterScenePos[nIndex][4][2]
		return x,z
	end
	
	return 100,100
end


----------------------------------------------------------------------------------------------
--������볡��
----------------------------------------------------------------------------------------------
function x303001_AskBattleSceneEnter( sceneId,selfId)

	--��GLServer�������ս��
	PVP2v2AskBattleSceneEnter(sceneId,selfId)
	
end

---------------------------------------------------------------------------------------------------
--������븱��
---------------------------------------------------------------------------------------------------
function x303001_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 0
end

----------------------------------------------------------------------------------------------
--��ȷ����
----------------------------------------------------------------------------------------------
function x303001_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--Ĭ�϶Ի�
----------------------------------------------------------------------------------------------
function x303001_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)	
end

---------------------------------------------------------------------------------------------------
--��ҽ���ս��ʱ�Ĵ���
---------------------------------------------------------------------------------------------------
function x303001_OnPlayerEnter(sceneId, selfId)

	--����Ƿ���PVP2v2������
    local nBattleScene = x303001_GetBattleSceneType( sceneId )
    if  nBattleScene <= 0 then
        return
    end
    
    --��鳡���Ƿ���Ч
    local nBattleSceneValid = x303001_IsBattleSceneValid(sceneId)
    if nBattleSceneValid ~= 1 then
    	return	
    end
	
	--�����ԭ�ȵĳ������б���
    local scenePre = GetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_SCENE_PRE ) - 1
    if scenePre >= 0 then
        
        local CurX = GetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSX_PRE)
        local CurZ = GetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSZ_PRE)

        SetPlayerBakSceneInfo(sceneId,selfId,scenePre,CurX,CurZ)

        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_SCENE_PRE,0)
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSX_PRE,0)
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSZ_PRE,0)

    end
    
	--�����ʼ�رգ�����ҽ���ҲҪ�߳�ȥ
	local leaveFlag = x303001_SceneInfo[sceneId].ISCLOSING
	if leaveFlag > 0 then
		
		x303001_SetPlayerNeedKick(sceneId,selfId)
		
		local msg = format("P2BL:x303001_OnPlayerEnterFinished kick 0 SceneId=%d ",sceneId  )
		WriteLog(1,msg)
		
		return
	end
	
	--��������Ч
	if x303001_CheckPlayerValid(sceneId,selfId ) == 0 then
		
		x303001_SetPlayerNeedKick(sceneId,selfId)
		
		local msg = format("P2BL:x303001_OnPlayerEnterFinished kick 1 SceneId=%d ",sceneId  )
		WriteLog(1,msg)
		
		return
	end
	
	--��������������
	if x303001_GetPlayerDieFlag(sceneId,selfId ) == 1 then
		
		x303001_SetPlayerNeedKick(sceneId,selfId)
		
		local msg = format("P2BL:x303001_OnPlayerEnterFinished kick 2 SceneId=%d ",sceneId  )
		WriteLog(1,msg)
		
		return
	end
	
	--�������Ѿ�����������
	if x303001_GetPlayerEnterSceneFlag( sceneId,selfId ) == 1 then
		
		x303001_SetPlayerNeedKick(sceneId,selfId)
		
		local msg = format("P2BL:x303001_OnPlayerEnterFinished kick 3 SceneId=%d ",sceneId  )
		WriteLog(1,msg)
		
		return
	end
	
	--���������Ӫ
	local nCampFlag = x303001_GetPlayerCampFlag( sceneId,selfId)
	if nCampFlag < 0 or nCampFlag > 1 then
		
		x303001_SetPlayerNeedKick(sceneId,selfId)
		
		local msg = format("P2BL:x303001_OnPlayerEnterFinished kick 4 SceneId=%d ",sceneId  )
		WriteLog(1,msg)
		
		return
	end
	
	SetCurCamp(sceneId,selfId,x303001_g_CampFlag[nCampFlag+1])

	--�������λ��
	local x,z = x303001_GetPlayerPos( sceneId,selfId)
	SetPos(sceneId,selfId,x,z)
	
	--��¼һ������
	local name = GetName(sceneId,selfId)
	local msg = format("P2BL:x303001_OnPlayerEnterFinished playerEnter SceneId=%d x = %d, z = %d flag = %d name=%s",sceneId,x,z,nCampFlag ,name )
	WriteLog(1,msg)
	
	--������ҽ��볡�����
	x303001_SetPlayerEnterSceneFlag( sceneId,selfId)
	
	--���ÿͻ��������Ϣ
	SetPVP2v2BattleDisable( sceneId,selfId,0,nCampFlag)
	
	--����Ƿ���Բ�����Ч
	if x303001_SceneInfo[sceneId].TICKCOUNT < 31 then
		CallScriptFunction(UTILITY_SCRIPT,"PlayClientMapColor", sceneId, selfId, 0, 0)
	end
	
	--��¼�淨��־
	GamePlayScriptLog(sceneId,selfId,x303001_g_GameId)
	
end

---------------------------------------------------------------------------------------------------
--����뿪����
---------------------------------------------------------------------------------------------------
function x303001_OnPlayerLeave( sceneId,selfId)

	local nDebug = 1
	if nDebug == 1 then
		
		local n2v2LevelPre = GetPVP2V2Level(sceneId,selfId)
		local name = GetName(sceneId,selfId)
		local msg = format("P2BL:x303001_OnPlayerLeave 0 SceneId=%d Name=%s 2v2LevelPre = %d", sceneId, name, n2v2LevelPre  )
        WriteLog(1,msg)
	end

	--����Ƿ���PVP2v2������
    local nBattleScene = x303001_GetBattleSceneType( sceneId )
    if  nBattleScene <= 0 then
        return
    end
    
    --��鳡���Ƿ���Ч
    local nBattleSceneValid = x303001_IsBattleSceneValid(sceneId)
    if nBattleSceneValid ~= 1 then
    	return	
    end
	
	--�����ʼ�رգ�������뿪������
	local leaveFlag = x303001_SceneInfo[sceneId].ISCLOSING
	if leaveFlag > 0 then
		return
	end
	
	--���û�п�ʼ�ر�
	if x303001_GetPlayerLeaveSceneFlag( sceneId,selfId) == 0 then
		
		x303001_SetPlayerLeaveSceneFlag( sceneId,selfId)
		
		local n2v2LevelPre = GetPVP2V2Level(sceneId,selfId)
		
		--��;�˳����Ƿ�ս���ж�ʤ��������£��˳����ȼ���һ�ͷ�
		x303001_SubPVP2V2Level(sceneId,selfId,x303001_g_Loser_Bonus_Level)
		
		local n2v2LevelAfter = GetPVP2V2Level(sceneId,selfId)
		
		--��¼�����־
		local name = GetName(sceneId,selfId)
		local msg = format("P2BL:x303001_OnPlayerLeave 1 SceneId=%d Name=%s 2v2LevelPre = %d 2v2LevelAfter=%d", sceneId, name, n2v2LevelPre, n2v2LevelAfter  )
        WriteLog(1,msg)
	end	
end

---------------------------------------------------------------------------------------------------
--ս����ʱ��
---------------------------------------------------------------------------------------------------
function x303001_ProcTiming(sceneId, nowTime)

	--����Ƿ���PVP2v2������
    local nBattleScene = x303001_GetBattleSceneType( sceneId )
    if  nBattleScene <= 0 then
        return
    end
    
    --��鳡���Ƿ���Ч
    local nBattleSceneValid = x303001_IsBattleSceneValid(sceneId)
    if nBattleSceneValid ~= 1 then
    	return	
    end

	x303001_UpdatePlayerKickState(sceneId)

	local leaveFlag = x303001_SceneInfo[sceneId].ISCLOSING
	if leaveFlag > 0 then

		--��ʾxx����˳�����
		local leaveCountDown = x303001_SceneInfo[sceneId].LEAVECOUNTDOWN + 1
		x303001_SceneInfo[sceneId].LEAVECOUNTDOWN = leaveCountDown

		if leaveCountDown >= x303001_g_CloseTick then
			
			local humancount = GetScenePlayerCount(sceneId);
			for	i = 0, humancount - 1 do
				local humanId = GetScenePlayerObjId(sceneId, i);
                --x303001_DoPlayerRelive( sceneId,humanId,100)
                TimerCommand( sceneId, humanId, 1, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, x303001_g_scriptId, -1, -1 );	--���Ͷ�ʱ��������ʱ��ͬ��

                --�������˺���
                x303001_SetPlayerNeedKick(sceneId,humanId)
                local msg = format("P2BL:x303001_ProcTiming kick 1 SceneId=%d ",sceneId  )
                WriteLog(1,msg)
			end
			
		elseif leaveCountDown < x303001_g_CloseTick then
			
			local humancount = GetScenePlayerCount(sceneId);
			for	i = 0, humancount - 1 do
				local humanId = GetScenePlayerObjId(sceneId, i);
 				local str = format("����ս������%d���ر�", x303001_g_CloseTick - leaveCountDown);
  				BeginQuestEvent(sceneId);
  				AddQuestText(sceneId, str);
  				EndQuestEvent(sceneId);
  				DispatchQuestTips(sceneId, humanId);
			end
			
		end

	else
		
		if x303001_g_CurrentState[sceneId] ~= x303001_g_State_Begin then
			return
		end
		
		local nowTickCount = x303001_SceneInfo[sceneId].TICKCOUNT + 1;
		x303001_SceneInfo[sceneId].TICKCOUNT = nowTickCount
		
		--����30�룬�����̬�赲
		if nowTickCount == 31 then
			x303001_ClearTempImpassable(sceneId)
		end
		
		--������һ���Ӻ󣬿�ʼ��ʤ��
		if nowTickCount >= 60 then
			if x303001_CheckBattleFinished( sceneId ) == 1 then
				x303001_OnBattleSceneClose( sceneId,2 )
				
				
				local msg = format("P2BL:x303001_ProcTiming sceneId=%d,nowTickCount=%d 000 ",sceneId ,nowTickCount )
                WriteLog(1,msg)
                
			end
		end

		--������ʱ��
		if nowTickCount >= x303001_g_LimitTotalHoldTime then
			local humancount = GetScenePlayerCount(sceneId);
			for i = 0, humancount - 1 do
				local humanId = GetScenePlayerObjId(sceneId, i);
				
				BeginQuestEvent(sceneId);
					AddQuestText(sceneId, format("����ս��ʱ���ѵ�������%d���رգ�",x303001_g_CloseTick));
				EndQuestEvent();
				DispatchQuestTips(sceneId, humanId);
			end
		end

        if nowTickCount == x303001_g_LimitTotalHoldTime then
            x303001_OnBattleSceneClose( sceneId,3 )
            
            local msg = format("P2BL:x303001_ProcTiming sceneId=%d,nowTickCount=%d 001 ",sceneId ,nowTickCount )
            WriteLog(1,msg)
        end
	end
end

---------------------------------------------------------------------------------------------------
--�������
---------------------------------------------------------------------------------------------------
function x303001_OnPlayerDie(sceneId, selfId, killerId)	
	
	--����Ƿ���PVP2v2������
    local nBattleScene = x303001_GetBattleSceneType( sceneId )
    if  nBattleScene <= 0 then
        return
    end
    
    --��鳡���Ƿ���Ч
    local nBattleSceneValid = x303001_IsBattleSceneValid(sceneId)
    if nBattleSceneValid ~= 1 then
    	return	
    end
    
	x303001_SetPlayerDieFlag( sceneId,selfId )
	if x303001_CheckBattleFinished( sceneId ) == 1 then
		x303001_OnBattleSceneClose( sceneId,4 )	
		
		local msg = format("P2BL:x303001_OnPlayerDie sceneId=%d  002 ",sceneId )
        WriteLog(1,msg)
	end
end

---------------------------------------------------------------------------------------------------
--��Ҹ���
---------------------------------------------------------------------------------------------------
function x303001_OnPlayerRelive(sceneId, selfId, ReliveType)
	
	--����Ƿ���PVP2v2������
    local nBattleScene = x303001_GetBattleSceneType( sceneId )
    if  nBattleScene <= 0 then
        return
    end
    
    --��鳡���Ƿ���Ч
    local nBattleSceneValid = x303001_IsBattleSceneValid(sceneId)
    if nBattleSceneValid ~= 1 then
    	return	
    end
	
	local leaveFlag = x303001_SceneInfo[sceneId].ISCLOSING;
	if leaveFlag > 0 then
		return
	end
	
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "˫��ս����������֮ǰ���ܸ�������ĵȴ���");
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	
end

---------------------------------------------------------------------------------------------------
--��������
---------------------------------------------------------------------------------------------------
function x303001_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

---------------------------------------------------------------------------------------------------
--�뿪����
---------------------------------------------------------------------------------------------------
function x303001_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
end

---------------------------------------------------------------------------------------------------
--�����ر�
---------------------------------------------------------------------------------------------------
function x303001_OnSceneClose( sceneId )
	--��GlServer֪ͨ���������Ѿ��ر�
	PVP2v2SendMakeBattleSceneClose(sceneId)
end

---------------------------------------------------------------------------------------------------
--����
---------------------------------------------------------------------------------------------------
function x303001_DoPlayerRelive( sceneId, selfId, value )

	--ֻ����������ҽ��д���
	local nHp = GetHp(sceneId,selfId)
	if nHp <= 0 then
	
		ClearRageRecoverTick(sceneId, selfId)
		RestoreHp(sceneId, selfId,value)
		RestoreRage(sceneId, selfId,value)
		ClearMutexState(sceneId, selfId, 6)
		SendReliveResult(sceneId, selfId,1)
	end
	
	--������,���һ�Ѫ
	LastMount(sceneId, selfId )
	RestoreHp(sceneId, selfId,0)
end

---------------------------------------------------------------------------------------------------
--����
---------------------------------------------------------------------------------------------------
function x303001_KickPlayer(sceneId,selfId)

	--�������״̬
    x303001_DoPlayerRelive( sceneId, selfId, 100 )
    x303001_RestorePlayerCamp(sceneId,selfId)
    SetPlayerRuntimeData(sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ,0)
    
    SetPVP2v2BattleDisable( sceneId,selfId,1,0)


    --�������BakScene��Ϣ������BakScene��ϢΪ׼
    local nBakSceneId,x,z = GetPlayerBakSceneInfo(sceneId,selfId )
    if nBakSceneId >= 0 then
        NewWorld(sceneId,selfId,nBakSceneId,x,z,x303001_g_scriptId)
        return
    end

    --���û��BakScene��Ϣ�����͵��������ִ�
    local nCountry = GetCurCountry(sceneId,selfId)
    if nCountry == 0 then
        
        --¥��
        local nDestSceneId = 50
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,x303001_g_scriptId)

    elseif nCountry == 1 then
        
        --��ɽ
        local nDestSceneId = 150
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,x303001_g_scriptId)

    elseif nCountry == 2 then

        --����
        local nDestSceneId = 250
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,x303001_g_scriptId)

    elseif nCountry == 3 then
        
        --�ػ�
        local nDestSceneId = 350
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,x303001_g_scriptId)
        
    end
end


---------------------------------------------------------------------------------------------------
--�ָ���Ӫ
---------------------------------------------------------------------------------------------------
function x303001_RestorePlayerCamp(sceneId,selfId)

	local nCountryId = GetCurCountry( sceneId,selfId )
    SetCurCamp(sceneId,selfId,nCountryId )
    
end

---------------------------------------------------------------------------------------------------
--ʱ��ͬ��������ʱ���ù�
---------------------------------------------------------------------------------------------------
function x303001_SyncBattleTimeToAllPlayer(sceneId,nTime)
	
	local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then

            TimerCommand( sceneId, objId, 1, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, x303001_g_scriptId,-1,-1)

            if nTime > 0 then
                TimerCommand( sceneId, objId, 2, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, x303001_g_scriptId, nTime, nTime );
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--��GLServer������ͬ����������սʱ��Ķ���
----------------------------------------------------------------------------------------------
function x303001_OnSyncBattleTime( sceneId,nTime )
    
    --����Ƿ���PVP2v2������
    local nBattleScene = x303001_GetBattleSceneType( sceneId )
    if  nBattleScene <= 0 then
        return
    end
    
    --��鳡���Ƿ���Ч
    local nBattleSceneValid = x303001_IsBattleSceneValid(sceneId)
    if nBattleSceneValid ~= 1 then
    	return	
    end
    
    x303001_SceneInfo[sceneId].TICKCOUNT = NumberCastIntToUInt( nTime )
    local DownTickCount = x303001_g_LimitTotalHoldTime - NumberCastIntToUInt( nTime )
    x303001_SyncBattleTimeToAllPlayer( sceneId, DownTickCount )
end

---------------------------------------------------------------------------------------------------
--���ս������
---------------------------------------------------------------------------------------------------
function x303001_CheckBattleFinished( sceneId )

	---------------------------------------------------------------------------------------------------	
	--1��ֻ��һ����һ���˫����������
	---------------------------------------------------------------------------------------------------
	if  x303001_CheckTeamA_AllLeave( sceneId ) == 1 or x303001_CheckTeamB_AllLeave( sceneId ) == 1 then
		return 1
	end
	
	---------------------------------------------------------------------------------------------------
	--2��ĳ����Ҷ�����
	---------------------------------------------------------------------------------------------------
	if x303001_CheckTeamA_AllDie( sceneId ) == 1 or x303001_CheckTeamB_AllDie( sceneId ) == 1 then
		return 1
	end
	
	---------------------------------------------------------------------------------------------------
	--3��ֻ��һ�����һ��������һ���뿪���������
	---------------------------------------------------------------------------------------------------
	if x303001_CheckTeamA_Live( sceneId ) == 0 or x303001_CheckTeamB_Live( sceneId ) == 0 then
		return 1
	end
	
	
	return 0
end

---------------------------------------------------------------------------------------------------
--��ս������
---------------------------------------------------------------------------------------------------
function x303001_GiveBattleBonus( sceneId,nResult )
	
	if nResult == -1 then
		
		LuaThisScenceM2Wrold( sceneId,"ƽ��",5,1)
		
		x303001_OnGiveTeamA(sceneId,-1)
		x303001_OnGiveTeamB(sceneId,-1)
		
	elseif nResult == 0 then
		
		LuaThisScenceM2Wrold( sceneId,"���Ҿ���ʤ",5,1)
		
		x303001_OnGiveTeamA(sceneId,0)
		x303001_OnGiveTeamB(sceneId,0)
		
	elseif nResult == 1 then
		
		LuaThisScenceM2Wrold( sceneId,"��������ʤ",5,1)
		
		x303001_OnGiveTeamA(sceneId,1)
		x303001_OnGiveTeamB(sceneId,1)
	end
end

---------------------------------------------------------------------------------------------------
--����A�Ļ�
---------------------------------------------------------------------------------------------------
function x303001_OnGiveTeamA( sceneId, nBonusType )
		
	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			
			local GUID = GetPlayerGUID( sceneId,humanId )

			local p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][1].GUID)
			if GUID == p then
				
				local name = GetName(sceneId,humanId)
				if name == nil then
					name = "Error "
				end
				
				if nBonusType == -1 then
					
					LuaScenceM2Player( sceneId,humanId,format("#G���#R%d#G��ս������",x303001_g_Other_Bonus_Mark),name,2,1)
					
					x303001_AddPVP2V2Level(sceneId,humanId,0)
					AddPVP2V2Mark(sceneId,humanId,x303001_g_Other_Bonus_Mark)
					
				elseif nBonusType == 0 then			
					
					if x303001_LevelFlag[sceneId] == 1 then
						LuaScenceM2Player( sceneId,humanId,"#Gս���ȼ�������⣨20�����ϣ����޷����ս���ȼ���",name,2,1)
					else
						LuaScenceM2Player( sceneId,humanId,format("#Gս���ȼ�+%d",x303001_g_Winner_Bonus_Level),name,2,1)
						x303001_AddPVP2V2Level(sceneId,humanId,x303001_g_Winner_Bonus_Level)
					end
					
					
					LuaScenceM2Player( sceneId,humanId,format("#G���#R%d#G��ս������",x303001_g_Winner_Bonus_Mark),name,2,1)
					AddPVP2V2Mark(sceneId,humanId,x303001_g_Winner_Bonus_Mark)	
					
				elseif nBonusType == 1 then
					
					LuaScenceM2Player( sceneId,humanId,format("#Gս���ȼ�-%d",x303001_g_Loser_Bonus_Level),name,2,1)
					LuaScenceM2Player( sceneId,humanId,format("#G���#R%d#G��ս������",x303001_g_Loser_Bonus_Mark),name,2,1)	
					
					x303001_SubPVP2V2Level(sceneId,humanId,x303001_g_Loser_Bonus_Level)
					AddPVP2V2Mark(sceneId,humanId,x303001_g_Loser_Bonus_Mark)
					
				end
				
			end
			
			p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][2].GUID)
			if GUID == p then
				
				local name = GetName(sceneId,humanId)
				if name == nil then
					name = "Error "
				end
				
				if nBonusType == -1 then
					
					LuaScenceM2Player( sceneId,humanId,format("#G���#R%d#G��ս������",x303001_g_Other_Bonus_Mark),name,2,1)
					
					x303001_AddPVP2V2Level(sceneId,humanId,0)
					AddPVP2V2Mark(sceneId,humanId,x303001_g_Other_Bonus_Mark)
					
				elseif nBonusType == 0 then
					
					if x303001_LevelFlag[sceneId] == 1 then
						LuaScenceM2Player( sceneId,humanId,"#Gս���ȼ�������⣨20�����ϣ����޷����ս���ȼ���",name,2,1)
					else
						LuaScenceM2Player( sceneId,humanId,format("#Gս���ȼ�+%d",x303001_g_Winner_Bonus_Level),name,2,1)	
						x303001_AddPVP2V2Level(sceneId,humanId,x303001_g_Winner_Bonus_Level)
					end
					
					LuaScenceM2Player( sceneId,humanId,format("#G���#R%d#G��ս������",x303001_g_Winner_Bonus_Mark),name,2,1)
					AddPVP2V2Mark(sceneId,humanId,x303001_g_Winner_Bonus_Mark)				
					
				elseif nBonusType == 1 then
					
					LuaScenceM2Player( sceneId,humanId,format("#Gս���ȼ�-%d",x303001_g_Loser_Bonus_Level),name,2,1)
					LuaScenceM2Player( sceneId,humanId,format("#G���#R%d#G��ս������",x303001_g_Loser_Bonus_Mark),name,2,1)	
					
					x303001_SubPVP2V2Level(sceneId,humanId,x303001_g_Loser_Bonus_Level)
					AddPVP2V2Mark(sceneId,humanId,x303001_g_Loser_Bonus_Mark)
				end
			end
		end
	end
end

---------------------------------------------------------------------------------------------------
--����B�Ļ�
---------------------------------------------------------------------------------------------------
function x303001_OnGiveTeamB( sceneId, nBonusType )

	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			
			local GUID = GetPlayerGUID( sceneId,humanId )

			local p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][1].GUID)
			if GUID == p then
				
				local name = GetName(sceneId,humanId)
				if name == nil then
					name = "Error "
				end
				
				if nBonusType == -1 then
					
					LuaScenceM2Player( sceneId,humanId,format("#G���#R%d#G��ս������",x303001_g_Other_Bonus_Mark),name,2,1)
					
					x303001_AddPVP2V2Level(sceneId,humanId,0)
					AddPVP2V2Mark(sceneId,humanId,x303001_g_Other_Bonus_Mark)
					
				elseif nBonusType == 0 then
					
					LuaScenceM2Player( sceneId,humanId,format("#Gս���ȼ�-%d",x303001_g_Loser_Bonus_Level),name,2,1)
					LuaScenceM2Player( sceneId,humanId,format("#G���#R%d#G��ս������",x303001_g_Loser_Bonus_Mark),name,2,1)
					
					x303001_SubPVP2V2Level(sceneId,humanId,x303001_g_Loser_Bonus_Level)
					AddPVP2V2Mark(sceneId,humanId,x303001_g_Loser_Bonus_Mark)
					
				elseif nBonusType == 1 then					
					
					
					if x303001_LevelFlag[sceneId] == 2 then
						LuaScenceM2Player( sceneId,humanId,"#Gս���ȼ�������⣨20�����ϣ����޷����ս���ȼ���",name,2,1)
					else
						LuaScenceM2Player( sceneId,humanId,format("#Gս���ȼ�+%d",x303001_g_Winner_Bonus_Level),name,2,1)
						x303001_AddPVP2V2Level(sceneId,humanId,x303001_g_Winner_Bonus_Level)
					end
					
					LuaScenceM2Player( sceneId,humanId,format("#G���#R%d#G��ս������",x303001_g_Winner_Bonus_Mark),name,2,1)
					AddPVP2V2Mark(sceneId,humanId,x303001_g_Winner_Bonus_Mark)	
					
				end
				
			end
			
			p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][2].GUID)
			if GUID == p then
				
				local name = GetName(sceneId,humanId)
				if name == nil then
					name = "Error "
				end
				
				if nBonusType == -1 then
					
					LuaScenceM2Player( sceneId,humanId,format("#G���#R%d#G��ս������",x303001_g_Other_Bonus_Mark),name,2,1)		
					
					x303001_AddPVP2V2Level(sceneId,humanId,0)
					AddPVP2V2Mark(sceneId,humanId,x303001_g_Other_Bonus_Mark)	
					
				elseif nBonusType == 0 then
					
					LuaScenceM2Player( sceneId,humanId,format("#Gս���ȼ�-%d",x303001_g_Loser_Bonus_Level),name,2,1)
					LuaScenceM2Player( sceneId,humanId,format("#G���#R%d#G��ս������",x303001_g_Loser_Bonus_Mark),name,2,1)
					
					x303001_SubPVP2V2Level(sceneId,humanId,x303001_g_Loser_Bonus_Level)
					AddPVP2V2Mark(sceneId,humanId,x303001_g_Loser_Bonus_Mark)
					
				elseif nBonusType == 1 then
					
					if x303001_LevelFlag[sceneId] == 2 then
						LuaScenceM2Player( sceneId,humanId,"#Gս���ȼ�������⣨20�����ϣ����޷����ս���ȼ���",name,2,1)
					else
						LuaScenceM2Player( sceneId,humanId,format("#Gս���ȼ�+%d",x303001_g_Winner_Bonus_Level),name,2,1)
						x303001_AddPVP2V2Level(sceneId,humanId,x303001_g_Winner_Bonus_Level)
					end
					
					LuaScenceM2Player( sceneId,humanId,format("#G���#R%d#G��ս������",x303001_g_Winner_Bonus_Mark),name,2,1)	
					AddPVP2V2Mark(sceneId,humanId,x303001_g_Winner_Bonus_Mark)	
					
				end
			end
		end
	end
	
end

---------------------------------------------------------------------------------------------------
--����ս�����
---------------------------------------------------------------------------------------------------
function x303001_GenBattleResult( sceneId )

	--����Ѿ���ʼ�رգ������������
	if x303001_SceneInfo[sceneId].ISCLOSING == 1 then
		return
	end
	
	local nResult = -1 

	---------------------------------------------------------------------------------------------------	
	--1��ֻ��һ�����
	---------------------------------------------------------------------------------------------------
	
	--��A������ڣ�B����Ҳ��ڣ���ΪA��Ӯ	
	if  x303001_CheckTeamA_AllLeave( sceneId ) == 0 and x303001_CheckTeamB_AllLeave( sceneId ) == 1 then
		nResult = 0
		x303001_GiveBattleBonus( sceneId,nResult )
		return
	end
	
	--��A����Ҳ��ڣ�B������ڣ���ΪB��Ӯ
	if  x303001_CheckTeamA_AllLeave( sceneId ) == 1 and x303001_CheckTeamB_AllLeave( sceneId ) == 0 then
		nResult = 1
		x303001_GiveBattleBonus( sceneId,nResult )
		return
	end
	
	---------------------------------------------------------------------------------------------------
	--2��ĳ����Ҷ�����
	---------------------------------------------------------------------------------------------------
	
	--��A�����û��ȫ������B�����ȫ��������ΪA��Ӯ
	if x303001_CheckTeamA_AllDie( sceneId ) == 0 and x303001_CheckTeamB_AllDie( sceneId ) == 1 then
		nResult = 0
		x303001_GiveBattleBonus( sceneId,nResult )
		return
	end
	
	--��A�����ȫ������B�����û��ȫ��������ΪB��Ӯ
	if x303001_CheckTeamA_AllDie( sceneId ) == 1 and x303001_CheckTeamB_AllDie( sceneId ) == 0 then
		nResult = 1
		x303001_GiveBattleBonus( sceneId,nResult )
		return
	end
	
	---------------------------------------------------------------------------------------------------
	--3.���ĳ����һ��ŵ����
	---------------------------------------------------------------------------------------------------
	if x303001_CheckTeamA_Live( sceneId ) == 1 and x303001_CheckTeamB_Live( sceneId ) == 0 then
		nResult = 0
		x303001_GiveBattleBonus( sceneId,nResult )
		return
	end
	
	if x303001_CheckTeamA_Live( sceneId ) == 0 and x303001_CheckTeamB_Live( sceneId ) == 1 then
		nResult = 1
		x303001_GiveBattleBonus( sceneId,nResult )
		return
	end
	
	---------------------------------------------------------------------------------------------------
	--4�������ŵ���ҵ�����
	---------------------------------------------------------------------------------------------------
	if x303001_GetTeamA_LiveCount(sceneId ) > x303001_GetTeamB_LiveCount(sceneId)  then
		nResult = 0
		x303001_GiveBattleBonus( sceneId,nResult )
		return
	end
	
	if x303001_GetTeamA_LiveCount(sceneId ) < x303001_GetTeamB_LiveCount(sceneId)  then
		nResult = 1
		x303001_GiveBattleBonus( sceneId,nResult )
		return
	end	
	
	---------------------------------------------------------------------------------------------------
	--5��������1��2,3,4
	---------------------------------------------------------------------------------------------------
	
	--�������,��Ϊսƽ�����û�ˣ�������
	if  x303001_CheckTeamA_AllLeave( sceneId ) == 0 and x303001_CheckTeamB_AllLeave( sceneId ) == 0 then
		nResult = -1
		x303001_GiveBattleBonus( sceneId,nResult )
		return
	end
		
end


---------------------------------------------------------------------------------------------------
--������A�Ƿ�ȫ���뿪
---------------------------------------------------------------------------------------------------
function x303001_CheckTeamA_AllLeave( sceneId )

	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			
			local GUID = GetPlayerGUID( sceneId,humanId )
			
			--1
			local p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][1].GUID)
			if GUID == p then
				return 0
			end
			
			--2
			p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][2].GUID)
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
function x303001_CheckTeamB_AllLeave( sceneId )
	
	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			
			local GUID = GetPlayerGUID( sceneId,humanId )
			
			--3
			local p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][1].GUID)
			if GUID == p then
				return 0
			end
			
			--4
			p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][2].GUID)
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
function x303001_CheckTeamA_AllDie( sceneId )
	
	--���м���
	
	local nCount = 0
	if x303001_TeamInfoA[sceneId][1].DIE == 1 then
		nCount = nCount + 1
	end
	
	if x303001_TeamInfoA[sceneId][2].DIE == 1 then
		nCount = nCount + 1
	end
	
	--������Ϊ2��ʾA����Ҷ�����
	if nCount == 2 then
		return 1
	end
	
	return 0
end

---------------------------------------------------------------------------------------------------
--�����ŵ����
---------------------------------------------------------------------------------------------------
function x303001_CheckTeamA_Live( sceneId )
	
	--���ֻ��һ����ң����ж�������������
	local nLiveCount = 0
	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			
			local GUID = GetPlayerGUID( sceneId,humanId )
			
			--1
			local p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][1].GUID)
			if GUID == p then
				if x303001_TeamInfoA[sceneId][1].DIE ~= 1 then
					nLiveCount = nLiveCount + 1
				end
			end
			
			--2
			p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][2].GUID)
			if GUID == p then
				if x303001_TeamInfoA[sceneId][2].DIE ~= 1 then
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
--�����ŵ����
---------------------------------------------------------------------------------------------------
function x303001_CheckTeamB_Live( sceneId )
	
	--���ֻ��һ����ң����ж�������������
	local nLiveCount = 0
	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			
			local GUID = GetPlayerGUID( sceneId,humanId )
			
			--1
			local p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][1].GUID)
			if GUID == p then
				if x303001_TeamInfoB[sceneId][1].DIE ~= 1 then
					nLiveCount = nLiveCount + 1
				end
			end
			
			--2
			p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][2].GUID)
			if GUID == p then
				if x303001_TeamInfoB[sceneId][2].DIE ~= 1 then
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
--ȡ�û��ŵ���ҵ�����
---------------------------------------------------------------------------------------------------
function x303001_GetTeamA_LiveCount( sceneId )
	
	--���ֻ��һ����ң����ж�������������
	local nLiveCount = 0
	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			
			local GUID = GetPlayerGUID( sceneId,humanId )
			
			--1
			local p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][1].GUID)
			if GUID == p then
				if x303001_TeamInfoA[sceneId][1].DIE ~= 1 then
					nLiveCount = nLiveCount + 1
				end
			end
			
			--2
			p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][2].GUID)
			if GUID == p then
				if x303001_TeamInfoA[sceneId][2].DIE ~= 1 then
					nLiveCount = nLiveCount + 1
				end
			end
		end
		
	end
	
	return nLiveCount
end

---------------------------------------------------------------------------------------------------
--�����ŵ����
---------------------------------------------------------------------------------------------------
function x303001_GetTeamB_LiveCount( sceneId )
	
	--���ֻ��һ����ң����ж�������������
	local nLiveCount = 0
	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			
			local GUID = GetPlayerGUID( sceneId,humanId )
			
			--1
			local p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][1].GUID)
			if GUID == p then
				if x303001_TeamInfoB[sceneId][1].DIE ~= 1 then
					nLiveCount = nLiveCount + 1
				end
			end
			
			--2
			p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][2].GUID)
			if GUID == p then
				if x303001_TeamInfoB[sceneId][2].DIE ~= 1 then
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
function x303001_CheckTeamB_AllDie( sceneId )
	
	--���м���
	
	local nCount = 0
	if x303001_TeamInfoB[sceneId][1].DIE == 1 then
		nCount = nCount + 1
	end
	
	if x303001_TeamInfoB[sceneId][2].DIE == 1 then
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
function x303001_CheckPlayerValid( sceneId,selfId )
	
	local GUID = GetPlayerGUID(sceneId,selfId)

	local p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		return 1
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		return 1
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		return 1
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		return 1
	end
	
	return 0

end

---------------------------------------------------------------------------------------------------
--ȡ������������
---------------------------------------------------------------------------------------------------
function x303001_GetPlayerDieFlag( sceneId,selfId )
	
	local GUID = GetPlayerGUID(sceneId,selfId)

	local p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		return x303001_TeamInfoA[sceneId][1].DIE;
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		return x303001_TeamInfoA[sceneId][2].DIE;
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		return x303001_TeamInfoB[sceneId][1].DIE;
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		return x303001_TeamInfoB[sceneId][2].DIE;
	end
	
	return 1
	
end

---------------------------------------------------------------------------------------------------
--��������������
---------------------------------------------------------------------------------------------------
function x303001_SetPlayerDieFlag( sceneId,selfId )

	local GUID = GetPlayerGUID(sceneId,selfId)

	local p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		x303001_TeamInfoA[sceneId][1].DIE = 1
		return
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		x303001_TeamInfoA[sceneId][2].DIE = 1
		return
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		x303001_TeamInfoB[sceneId][1].DIE = 1
		return
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		x303001_TeamInfoB[sceneId][2].DIE = 1
		return
	end
	
end

---------------------------------------------------------------------------------------------------
--ȡ����ҽ���ս�����
---------------------------------------------------------------------------------------------------
function x303001_GetPlayerEnterSceneFlag( sceneId,selfId)

	local GUID = GetPlayerGUID(sceneId,selfId)

	local p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		return x303001_TeamInfoA[sceneId][1].ENTER
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		return x303001_TeamInfoA[sceneId][2].ENTER
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		return x303001_TeamInfoB[sceneId][1].ENTER
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		return x303001_TeamInfoB[sceneId][2].ENTER
	end
	
	return 1
end

---------------------------------------------------------------------------------------------------
--������ҽ���ս�����
---------------------------------------------------------------------------------------------------
function x303001_SetPlayerEnterSceneFlag( sceneId,selfId)

	--������ҽ�����
	local GUID = GetPlayerGUID(sceneId,selfId)

	local p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		x303001_TeamInfoA[sceneId][1].ENTER = 1
		return
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		x303001_TeamInfoA[sceneId][2].ENTER = 1
		return
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		x303001_TeamInfoB[sceneId][1].ENTER = 1
		return
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		x303001_TeamInfoB[sceneId][2].ENTER = 1
		return
	end
end

---------------------------------------------------------------------------------------------------
--ȡ������뿪ս�����
---------------------------------------------------------------------------------------------------
function x303001_GetPlayerLeaveSceneFlag( sceneId,selfId)

	local GUID = GetPlayerGUID(sceneId,selfId)

	local p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		return x303001_TeamInfoA[sceneId][1].LEAVE
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		return x303001_TeamInfoA[sceneId][2].LEAVE
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		return x303001_TeamInfoB[sceneId][1].LEAVE
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		return x303001_TeamInfoB[sceneId][2].LEAVE
	end
	
	return 1
end

---------------------------------------------------------------------------------------------------
--������ҽ���ս�����
---------------------------------------------------------------------------------------------------
function x303001_SetPlayerLeaveSceneFlag( sceneId,selfId)

	--������ҽ�����
	local GUID = GetPlayerGUID(sceneId,selfId)

	local p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][1].GUID)
	if GUID == p then
		x303001_TeamInfoA[sceneId][1].LEAVE = 1
		return
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoA[sceneId][2].GUID)
	if GUID == p then
		x303001_TeamInfoA[sceneId][2].LEAVE = 1
		return
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][1].GUID)
	if GUID == p then
		x303001_TeamInfoB[sceneId][1].LEAVE = 1
		return
	end
	
	p = NumberCastIntToUInt(x303001_TeamInfoB[sceneId][2].GUID)
	if GUID == p then
		x303001_TeamInfoB[sceneId][2].LEAVE = 1
		return
	end
end

---------------------------------------------------------------------------------------------------
--ս��׼������
---------------------------------------------------------------------------------------------------
function x303001_OnBattleSceneReady(sceneId,nTotalTime)
	
	--���������Ϣ							  
	x303001_SceneInfo[sceneId] = {
						TICKCOUNT = 0,
						ISCLOSING = 0,
						LEAVECOUNTDOWN = 0,
						RESULT = 0,
						LIMITHOLDTIME = nTotalTime,
				  	  }
				  	  
	local msg = format("P2BL:x303001_OnBattleSceneReady SceneId=%d ",sceneId  )
	WriteLog(1,msg)
	
	
	--���ö�̬�赲
	x303001_SetTempImpassable(sceneId)
		
end

---------------------------------------------------------------------------------------------------
--ս���ر�
---------------------------------------------------------------------------------------------------
function x303001_OnBattleSceneClose(sceneId,flag )
	
	x303001_GenBattleResult( sceneId )
	
	if x303001_SceneInfo[sceneId].ISCLOSING == 1	then
		return
	end
	
	--���������Ϣ							  
	x303001_SceneInfo[sceneId].ISCLOSING = 1	
	x303001_SceneInfo[sceneId].TICKCOUNT = 0
	local msg = format("P2BL:x303001_OnBattleSceneClose SceneId=%d flag=%d",sceneId,flag  )
	WriteLog(1,msg)
	
end

---------------------------------------------------------------------------------------------------
--ս���ر�
---------------------------------------------------------------------------------------------------
function x303001_OnBattleMatchOOD(sceneId,selfId)
	
	local name = GetName(sceneId,selfId)
	LuaScenceM2Player( sceneId,selfId,"˫��ս���������ڵĶ��鱾���ֿգ�",name,2,1)	
	LuaScenceM2Player( sceneId,selfId,"˫��ս���������ڵĶ��鱾���ֿգ�",name,3,1)	
	
end

---------------------------------------------------------------------------------------------------
--���������Ҫ�߳�ȥ
---------------------------------------------------------------------------------------------------
function x303001_SetPlayerNeedKick( sceneId,selfId)
	
	local KickDown = GetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ) 
    if KickDown <= 0 or KickDown > x303001_g_Kick_Down then                
        SetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ,x303001_g_Kick_Down) 
    end
	
end

----------------------------------------------------------------------------------------------
--�������������Ҫ�ߵ�
----------------------------------------------------------------------------------------------
function x303001_SetAllPlayerNeedKick( sceneId )
    
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local KickDown = GetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ) 
            if KickDown <= 0 or KickDown > x303001_g_Kick_Down then                
                SetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ,x303001_g_Kick_Down) 
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--��������ߵ�״̬
----------------------------------------------------------------------------------------------
function x303001_UpdatePlayerKickState( sceneId )
    
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
                    x303001_KickPlayer( sceneId,objId )                    
                else
                    --���򣬼�������ʱ
                    SetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ,KickDown) 
                end
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--���ɶ�̬�赲
----------------------------------------------------------------------------------------------
function x303001_SetTempImpassable(sceneId)
	
	local nIndex = x303001_GetBattleSceneType(sceneId)
	
	for i,itm in x303001_g_TempImpassable do
		if itm.Flag == nIndex then
			AddSceneTempImpassable(sceneId,itm.Left,itm.Top,itm.Right,itm.Bottom)
		end
	end
	
end

----------------------------------------------------------------------------------------------
--ɾ����̬�赲
----------------------------------------------------------------------------------------------
function x303001_ClearTempImpassable(sceneId)
	
	LuaThisScenceM2Wrold( sceneId,"ս����ʼ",5,1)
	
	local nIndex = x303001_GetBattleSceneType(sceneId)
	
	for i,itm in x303001_g_TempImpassable do
		if itm.Flag == nIndex then
			DelSceneTempImpassable(sceneId,itm.Left,itm.Top,itm.Right,itm.Bottom)
		end
	end
	
	--�����Ч
	local nHumanCount = GetScenePlayerCount( sceneId )
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            CallScriptFunction(UTILITY_SCRIPT,"StopClientMapColor", sceneId, objId, 0)
        end
    end
end

function x303001_AddPVP2V2Level(mapId,playerId,delta)
	local day = GetQuestData( mapId, playerId, MD_PVP2V2_LEVEL_DAY[1], MD_PVP2V2_LEVEL_DAY[2], MD_PVP2V2_LEVEL_DAY[3] )
	local curday = GetWeekFirstDay()
	if day ~= curday then
		local value = GetPVP2V2Level(mapId,playerId)
		SubPVP2V2Level(mapId,playerId,value)
		AddPVP2V2Level(mapId,playerId,500)
		SetQuestData( mapId, playerId, MD_PVP2V2_LEVEL_DAY[1], MD_PVP2V2_LEVEL_DAY[2], MD_PVP2V2_LEVEL_DAY[3], curday )
	end	
	AddPVP2V2Level(mapId,playerId,delta)
end

function x303001_SubPVP2V2Level(mapId,playerId,delta)
	local day = GetQuestData( mapId, playerId, MD_PVP2V2_LEVEL_DAY[1], MD_PVP2V2_LEVEL_DAY[2], MD_PVP2V2_LEVEL_DAY[3] )
	local curday = GetWeekFirstDay()
	if day ~= curday then
		local value = GetPVP2V2Level(mapId,playerId)
		SubPVP2V2Level(mapId,playerId,value)
		AddPVP2V2Level(mapId,playerId,500)
		SetQuestData( mapId, playerId, MD_PVP2V2_LEVEL_DAY[1], MD_PVP2V2_LEVEL_DAY[2], MD_PVP2V2_LEVEL_DAY[3], curday )
	end	
	SubPVP2V2Level(mapId,playerId,delta)
end
