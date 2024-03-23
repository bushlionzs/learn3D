
--�������
--MisDescBegin
--�ű���
x300641_g_ScriptId = 300641


--�����ı�����
x300641_g_MissionName="���ս������"
x300641_g_CountryID = 3
--MisDescEnd


function x300641_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_GUILDBATTLE ) == 0 then
        return
    end

	local guild = GetGuildID(sceneId, selfId)
	if guild == -1 then
		return 1
	end

    if GetGuildBattleStatus(sceneId) ~= STATE_GUILD_BATTLE_BATTLE then
        return 1
    end

	AddQuestNumText(sceneId,x300641_g_ScriptId,x300641_g_MissionName,3);
end


function x300641_ProcEventEntry( sceneId, selfId, targetId ,idScript,idExt )

--	if GetGuildBattleStatus(sceneId) ~= STATE_GUILD_BATTLE_BATTLE then
-- 		BeginQuestEvent(sceneId)
--		AddQuestText(sceneId, "ս��δ����");
--		EndQuestEvent(sceneId)
--		DispatchQuestTips(sceneId,selfId)
--		return
--	end

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_GUILDBATTLE ) == 0 then
        return
    end

    local state,msg = x300641_CheckPlayerState( sceneId,selfId )
    if state == 1 then
        
        BeginQuestEvent(sceneId)
        AddQuestText( sceneId, msg );
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,targetId)
        return
    end

    GuildBattleAskEnterScene(sceneId, selfId)

    return 1
end

function x300641_OnEnterSceneError( sceneId,selfId,nError )
    

    if nError == 1 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�����û�п�ʼ��");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

        return 0

    elseif nError == 2 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ����û�а�ᣡ");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

    elseif nError == 3 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�������ڵİ�ỹû�б�����");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

        return 0

    elseif nError == 4 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�����ս��û�п�ʼ��");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

        return 0

    elseif nError == 5 then

        
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�������ڵİ���ڴ˴ΰ��ս���ֿգ�");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

        return 0

    elseif nError == 6 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�����İ����Ϣ���䲻��ȷ��");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

        return 0

    elseif nError == 7 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�������ǰ�����");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

        return 0

    elseif nError == 8 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�����İ���Ա����10�ˣ�");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

        return 0

    elseif nError == 9 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ���Ѿ���������İ�ս��������");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

        return 0

    elseif nError == 10 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�����ս�����Ѵ����ޣ�");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

        return 0
    elseif nError == 11 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�����ս�Ѿ�������");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

        return 0

    else
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��δ֪����");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

        return 0

    end
end

function x300641_CheckPlayerState( sceneId,selfId )
    

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

    local IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId,7702 )
    if IsHaveFlag ~= 0 then
        ErrorMsg = "�ڶ���״̬�£����ܽ���ս��"
        return 1,ErrorMsg
    end

    return 0

end


--********************
--����������
--**********************************
function x300641_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x300641_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x300641_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--����
--**********************************
function x300641_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300641_CheckSubmit( sceneId, selfId )
end

--**********************************
--�ύ
--**********************************
function x300641_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

