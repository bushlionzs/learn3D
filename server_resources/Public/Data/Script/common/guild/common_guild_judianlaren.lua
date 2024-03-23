x300920_g_ScriptId = 300920
x300920_g_MissionName="�����ҡ���������ս��"

x300920_g_Laird_Signup                  	= 300     --����
x300920_g_Laird_WaitBattle              	= 301     --�����������ȴ�����ս��
x300920_g_Laird_BeginBattle             	= 302     --��ʼ����ս��
x300920_g_Laird_EndBattle               	= 303     --��������ս��

function x300920_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

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

	local guild = GetGuildID(sceneId, selfId)
	if guild == -1 then
		return 1
	end
	
	local nBattleStatus = CallScriptFunction(300918,"GetBattleState",sceneId)
    if nBattleStatus ~= x300920_g_Laird_BeginBattle then
    	return 1
    end

    if CallScriptFunction(300918,"GetBattleEnterSceneFlag",sceneId) ~= 1 then
       return 1
    end

	AddQuestNumText(sceneId,x300920_g_ScriptId,x300920_g_MissionName,3);
end


function x300920_ProcEventEntry( sceneId, selfId, targetId )
    
    --����ս��״̬
    local nBattleStatus = CallScriptFunction(300918,"GetBattleState",sceneId)
    if nBattleStatus ~= x300920_g_Laird_BeginBattle then
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


    if CallScriptFunction(300918,"GetBattleEnterSceneFlag",sceneId) ~= 1 then
        
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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_LAIRDGBATTLELITE ) == 0 then
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
    DispatchQuestInfo( sceneId, selfId, targetId, x300920_g_ScriptId,-1 )

    return 1
end

--********************
--����������
--**********************************
function x300920_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

--**********************************
--����
--**********************************
function x300920_ProcAccept( sceneId, selfId )

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
	
	local nBattleStatus = CallScriptFunction(300918,"GetBattleState",sceneId)
    if nBattleStatus ~= x300920_g_Laird_BeginBattle then
    	return
    end

    local guild = GetGuildID(sceneId, selfId)
	if guild == -1 then
		return
	end

    if CallScriptFunction(300918,"GetBattleEnterSceneFlag",sceneId) ~= 1 then
        return
    end

    --���״̬
    local state,msg = CallScriptFunction(800021,"BattleTransCheckPlayerState", sceneId,selfId )
    if state == 1 then
        return
    end

    --��������ս��
    GameBattleRequestEnterScene(sceneId, selfId,2) 
end

function x300920_OnLairdBattleChangeScene(sceneId,selfId,nRetCode,newSceneID,nBattleCamp)
	
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
			    SetPos( sceneId , selfId , 43 ,90 )
	        else
	            SetPos( sceneId , selfId , 205,147 )
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

			NewWorld( sceneId , selfId , newSceneID , PosX , PosZ,300920 )
		end
		
	else
		x300920_OnLairdBattleTransError(sceneId,selfId,nRetCode )
	end
end

function x300920_OnLairdBattleTransError(sceneId,selfId,nRetCode )

	if nRetCode == 300 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "û�п�ʼ")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 301 then
	
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "û�а��")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )

	elseif nRetCode == 302 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "���û�б���")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 303 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "ս���Ѿ�����")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 304 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "�ֿ�")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 305 then
	
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "������ʱ���ѹ�")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 306 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "����Ѿ������������")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 307 then
		
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
function x300920_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--����
--**********************************
function x300920_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300920_CheckSubmit( sceneId, selfId )
end

--**********************************
--�ύ
--**********************************
function x300920_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

