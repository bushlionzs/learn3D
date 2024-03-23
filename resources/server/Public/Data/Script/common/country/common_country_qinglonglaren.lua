x310112_g_ScriptId = 310112
x310112_g_MissionName="����ս������"

x310112_g_QingLong_Signup                  	= 200     --����
x310112_g_QingLong_WaitBattle              	= 201     --�����������ȴ�����ս��
x310112_g_QingLong_BeginBattle             	= 202     --��ʼ����ս��
x310112_g_QingLong_EndBattle               	= 203     --��������ս��

function x310112_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_QINGLONGBATTLELITE ) == 0 then
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
	local nBattleStatus = CallScriptFunction(310110,"GetBattleState",sceneId)
    if nBattleStatus ~= x310112_g_QingLong_BeginBattle then
    	return 1
    end

    if CallScriptFunction(310110,"GetBattleEnterSceneFlag",sceneId) ~= 1 then
       return 1
    end

	AddQuestNumText(sceneId,x310112_g_ScriptId,x310112_g_MissionName,3);
end


function x310112_ProcEventEntry( sceneId, selfId, targetId )
    
    --����ս״̬
    local nBattleStatus = CallScriptFunction(310110,"GetBattleState",sceneId)
    if nBattleStatus ~= x310112_g_QingLong_BeginBattle then
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


    if CallScriptFunction(310110,"GetBattleEnterSceneFlag",sceneId) ~= 1 then
        
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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_QINGLONGBATTLELITE ) == 0 then
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
    AddQuestText( sceneId, "ȷ��Ҫ��������ս����" )
    EndQuestEvent( sceneId )
    DispatchQuestInfo( sceneId, selfId, targetId, x310112_g_ScriptId,-1 )

    return 1
end

--********************
--����������
--**********************************
function x310112_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

--**********************************
--����
--**********************************
function x310112_ProcAccept( sceneId, selfId )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_QINGLONGBATTLELITE ) == 0 then
        return
    end
    
    --����Ƿ��й���
    local nHumanGUID = GetPlayerGUID( sceneId,selfId )
    local nCountryId,nKingGUID,szKingName,nCountryGold = GetCountrySimpleData( sceneId,selfId )
    if nKingGUID <= 0 or nHumanGUID == nKingGUID then
    	return    	
    end
	
	local nBattleStatus = CallScriptFunction(310110,"GetBattleState",sceneId)
    if nBattleStatus ~= x310112_g_QingLong_BeginBattle then
    	return
    end

    local guild = GetGuildID(sceneId, selfId)
	if guild == -1 then
		return
	end

    if CallScriptFunction(310110,"GetBattleEnterSceneFlag",sceneId) ~= 1 then
        return
    end

    --���״̬
    local state,msg = CallScriptFunction(800021,"BattleTransCheckPlayerState", sceneId,selfId )
    if state == 1 then
        return
    end

    --��������ս��
    GameBattleRequestEnterScene(sceneId, selfId,1) 
end

function x310112_OnQingLongBattleChangeScene(sceneId,selfId,nRetCode,newSceneID,nBattleCamp)
	
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

			NewWorld( sceneId , selfId , newSceneID , PosX , PosZ,310112 )
		end
		
	else
		x310112_OnQingLongBattleTransError(sceneId,selfId,nRetCode )
	end
end

function x310112_OnQingLongBattleTransError(sceneId,selfId,nRetCode )

	if nRetCode == 200 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "û�п�ʼ")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 201 then
	
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "û�а��")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )

	elseif nRetCode == 202 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "���û�б���")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 203 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "ս���Ѿ�����")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 204 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "�ֿ�")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 205 then
	
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "������ʱ���ѹ�")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 206 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "����Ѿ������������")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 207 then
		
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
function x310112_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--����
--**********************************
function x310112_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--����Ƿ�����ύ
--**********************************
function x310112_CheckSubmit( sceneId, selfId )
end

--**********************************
--�ύ
--**********************************
function x310112_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

