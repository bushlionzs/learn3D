x310100_g_ScriptId = 310100
x310100_g_MissionName="����ս������"

function x310100_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_KINGBATTLE ) == 0 then
        return
    end

	local guild = GetGuildID(sceneId, selfId)
	if guild == -1 then
		return 1
	end

    if GetKingBattleStatus(sceneId) ~= STATE_KING_BATTLE_BATTLE then
        return 1
    end

    if GetKingBattleEnterSceneFlag(sceneId) ~= 1 then
        return 1
    end

	AddQuestNumText(sceneId,x310100_g_ScriptId,x310100_g_MissionName,3);
end


function x310100_ProcEventEntry( sceneId, selfId, targetId )
    --����ս��״̬
--	if GetKingBattleStatus(sceneId) ~= STATE_KING_BATTLE_BATTLE then
-- 		BeginQuestEvent(sceneId)
--		AddQuestText(sceneId, "ս��δ���ţ�");
--		EndQuestEvent(sceneId)
--		DispatchQuestTips(sceneId,selfId)
--		return 1
--	end
--
--    local guild = GetGuildID(sceneId, selfId)
--	if guild == -1 then
--        BeginQuestEvent(sceneId)
--		AddQuestText(sceneId, "û�а��,�����������ս����");
--		EndQuestEvent(sceneId)
--		DispatchQuestTips(sceneId,selfId)
--		return 1
--	end
--
--    if GetKingBattleEnterSceneFlag(sceneId) ~= 1 then
--        
--        BeginQuestEvent(sceneId)
--		AddQuestText(sceneId, "���ڲ��ܽ���ս����");
--		EndQuestEvent(sceneId)
--		DispatchQuestTips(sceneId,selfId)
--        return 1
--    end

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_KINGBATTLE ) == 0 then
        return
    end

    --���״̬
    local state,msg = x310100_CheckPlayerState( sceneId,selfId )
    if state == 1 then
        
        BeginQuestEvent(sceneId)
        AddQuestText( sceneId, msg );
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 1
    end

    BeginQuestEvent( sceneId )
    AddQuestText( sceneId, "ȷ��Ҫ�������ս����" )
    EndQuestEvent( sceneId )
    DispatchQuestInfo( sceneId, selfId, targetId, x310100_g_ScriptId,-1 )

    return 1
end

function x310100_CheckPlayerState( sceneId,selfId )
    

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


--********************
--����������
--**********************************
function x310100_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

--**********************************
--����
--**********************************
function x310100_ProcAccept( sceneId, selfId )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_KINGBATTLE ) == 0 then
        return
    end

    --����ս��״̬
	if GetKingBattleStatus(sceneId) ~= STATE_KING_BATTLE_BATTLE then
		return
	end

    local guild = GetGuildID(sceneId, selfId)
	if guild == -1 then
		return
	end

    if GetKingBattleEnterSceneFlag(sceneId) ~= 1 then
        return
    end

    --���״̬
    local state,msg = x310100_CheckPlayerState( sceneId,selfId )
    if state == 1 then
        return
    end

    --�������ս��
    RequestEnterKingBattleScene(sceneId, selfId)
    
end

function x310100_AskEnterKingBattle( sceneId,selfId )

    --���״̬
    local state,msg = x310100_CheckPlayerState( sceneId,selfId )
    if state == 1 then
        
        BeginQuestEvent(sceneId)
        AddQuestText( sceneId, msg );
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        
        return

    end

    --�������ս��
    RequestEnterKingBattleScene(sceneId, selfId)

end

--**********************************
--����
--**********************************
function x310100_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--����
--**********************************
function x310100_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--����Ƿ�����ύ
--**********************************
function x310100_CheckSubmit( sceneId, selfId )
end

--**********************************
--�ύ
--**********************************
function x310100_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

