x310115_g_ScriptId = 310115
x310115_g_MissionName="��ȸս������"

x310115_g_ZhuQue_Signup                  	= 100     --����
x310115_g_ZhuQue_WaitBattle              	= 101     --�����������ȴ���ȸս��
x310115_g_ZhuQue_BeginBattle             	= 102     --��ʼ��ȸս��
x310115_g_ZhuQue_EndBattle               	= 103     --������ȸս��

function x310115_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_ZHUQUEBATTLELITE ) == 0 then
        return
    end

	local guild = GetGuildID(sceneId, selfId)
	if guild == -1 then
		return 1
	end
	
	--����Ƿ��й���
    local nHumanGUID = GetPlayerGUID( sceneId,selfId )
    local nCountryId,nKingGUID,szKingName,nCountryGold = GetCountrySimpleData( sceneId,selfId )
    if nKingGUID <= 0 or nHumanGUID == nKingGUID then
    	return    	
    end
	
	--���״̬
	local nBattleStatus = CallScriptFunction(310113,"GetBattleState",sceneId)
    if nBattleStatus ~= x310115_g_ZhuQue_BeginBattle then
    	return 1
    end

    if CallScriptFunction(310113,"GetBattleEnterSceneFlag",sceneId) ~= 1 then
       return 1
    end

	AddQuestNumText(sceneId,x310115_g_ScriptId,x310115_g_MissionName,3);
end


function x310115_ProcEventEntry( sceneId, selfId, targetId )
    
    --��ȸս��״̬
    local nBattleStatus = CallScriptFunction(310113,"GetBattleState",sceneId)
    if nBattleStatus ~= x310115_g_ZhuQue_BeginBattle then
 		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "ս��δ���ţ�");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 1
	end

    local guild = GetGuildID(sceneId, selfId)
	if guild == -1 then
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "û�а��,�����������ս����");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 1
	end


    if CallScriptFunction(310113,"GetBattleEnterSceneFlag",sceneId) ~= 1 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "���ڲ��ܽ���ս����");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
        return 1
    end

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_ZHUQUEBATTLELITE ) == 0 then
       return
    end
    
    --����Ƿ��й���
    local nHumanGUID = GetPlayerGUID( sceneId,selfId )
    local nCountryId,nKingGUID,szKingName,nCountryGold = GetCountrySimpleData( sceneId,selfId )
    if nKingGUID <= 0 or nHumanGUID == nKingGUID then
    	return    	
    end
    

    --���״̬
    local state,msg = CallScriptFunction(800021,"BattleTransCheckPlayerState", sceneId,selfId )
    if state == 1 then
        
        BeginQuestEvent(sceneId)
        AddQuestText( sceneId, msg );
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 1
    end

    BeginQuestEvent( sceneId )
    AddQuestText( sceneId, "ȷ��Ҫ������ȸս����" )
    EndQuestEvent( sceneId )
    DispatchQuestInfo( sceneId, selfId, targetId, x310115_g_ScriptId,-1 )

    return 1
end

--********************
--����������
--**********************************
function x310115_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

--**********************************
--����
--**********************************
function x310115_ProcAccept( sceneId, selfId )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_ZHUQUEBATTLELITE ) == 0 then
        return
    end
    
    --����Ƿ��й���
    local nHumanGUID = GetPlayerGUID( sceneId,selfId )
    local nCountryId,nKingGUID,szKingName,nCountryGold = GetCountrySimpleData( sceneId,selfId )
    if nKingGUID <= 0 or nHumanGUID == nKingGUID then
    	return    	
    end
	
	local nBattleStatus = CallScriptFunction(310113,"GetBattleState",sceneId)
    if nBattleStatus ~= x310115_g_ZhuQue_BeginBattle then
    	return
    end

    local guild = GetGuildID(sceneId, selfId)
	if guild == -1 then
		return
	end

    if CallScriptFunction(310113,"GetBattleEnterSceneFlag",sceneId) ~= 1 then
        return
    end

    --���״̬
    local state,msg = CallScriptFunction(800021,"BattleTransCheckPlayerState", sceneId,selfId )
    if state == 1 then
        return
    end

    --������ȸս��
    GameBattleRequestEnterScene(sceneId, selfId,0) 
end

function x310115_OnZhuQueBattleChangeScene(sceneId,selfId,nRetCode,newSceneID,nBattleCamp)
	
	if nRetCode == 0 then
		
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
			    SetPos( sceneId , selfId , 47 , 218 )
	        else
	            SetPos( sceneId , selfId , 209,35 )
	        end
		else
	        
	        --���״̬
	        local state,msg = CallScriptFunction(800021,"BattleTransCheckPlayerState", sceneId,selfId )
	        if state == 1 then
	            
	            BeginQuestEvent(sceneId)
	            AddQuestText( sceneId, msg );
	            EndQuestEvent(sceneId)
	            DispatchQuestTips(sceneId,selfId)
	            return
	        end
	        
	        --����Ƿ���Դ���
			if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneID) == 0 then
				return
			end
	
	        --��¼һ��RuntimeData
	        local nCurX,nCurZ = GetWorldPos( sceneId,selfId )
	        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_SCENE_PRE,sceneId + 1)
	        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSX_PRE,nCurX)
	        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSZ_PRE,nCurZ)
	        SetPlayerRuntimeData(sceneId,selfId,RD_BATTLESCENE_ENTER_FLAG,1)

			NewWorld( sceneId , selfId , newSceneID , PosX , PosZ,310115 )
		end
		
	else
		x310115_OnZhuQueBattleTransError(sceneId,selfId,nRetCode )
	end
end

function x310115_OnZhuQueBattleTransError(sceneId,selfId,nRetCode )

	if nRetCode == 100 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "û�п�ʼ")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 101 then
	
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "û�а��")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )

	elseif nRetCode == 102 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "���û�б���")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 103 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "ս���Ѿ�����")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 104 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "�ֿ�")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 105 then
	
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "������ʱ���ѹ�")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 106 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "����Ѿ������������")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 107 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "ս������Ѵ�����")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	else
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "δ֪����")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	end

end

--**********************************
--����
--**********************************
function x310115_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--����
--**********************************
function x310115_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--����Ƿ�����ύ
--**********************************
function x310115_CheckSubmit( sceneId, selfId )
end

--**********************************
--�ύ
--**********************************
function x310115_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

