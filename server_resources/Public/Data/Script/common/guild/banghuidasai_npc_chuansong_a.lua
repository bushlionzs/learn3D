
--MisDescBegin
--�ű���
x550524_g_ScriptId = 550524


--�����ı�����
x550524_g_MissionName="ɽկǰ�ߴ���"
--x550524_g_CountryID = 3
--MisDescEnd

x550524_g_ChuanSong_X = 226.027695
x550524_g_ChuanSong_Z = 232.85527



function x550524_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

    --ս��δ����
    if GetGuildBattleStatus(sceneId) ~= 3 then
        AddQuestNumText(sceneId,x550524_g_ScriptId,"�뿪ս��",3,2)
        return
    end

    --����A��Ӫ������Ч
	local nGuildA = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_A_GUILD )
    local nGuildB = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_B_GUILD )

    local nGuildId = GetGuildID( sceneId,selfId )

    --������ս���е���Ӫ����
    local nFlag = -1
    if nGuildId == nGuildA then
        nFlag = 0
    elseif nGuildId == nGuildB then
        nFlag = 1
    end
    
    if nFlag == 0 or nFlag == -1 then
	    --AddQuestNumText(sceneId,x550524_g_ScriptId,"ǰ�ߴ���",13,1)
        AddQuestNumText(sceneId,x550524_g_ScriptId,"�뿪ս��",3,2)
    end
end


function x550524_ProcEventEntry( sceneId, selfId, targetId,idScript,idExt )

    if idExt == 2 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"�����Ҫ�뿪ս����")
        EndQuestEvent(sceneId)
        DispatchQuestInfo(sceneId,selfId,targetId,x550524_g_ScriptId,-1)
        return 1

    end

	if GetGuildBattleStatus(sceneId) ~= 3 then
 		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "ս��δ����");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end

    --����A��Ӫ������Ч
	local nGuildA = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_A_GUILD )
    local nGuildB = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_B_GUILD )

    local nGuildId = GetGuildID( sceneId,selfId )

    local nFlag = 0
    if nGuildId == nGuildA then
        nFlag = 0
    elseif nGuildId == nGuildB then
        nFlag = 1
    end

    if nFlag ~= 0 then
        return
    end

    if idExt == 1 then
        SetPos(sceneId,selfId,x550524_g_ChuanSong_X,x550524_g_ChuanSong_Z)
    end


end

--********************
--����������
--**********************************
function x550524_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x550524_ProcAccept( sceneId, selfId )
    CallScriptFunction( GUILDBATTLE_SCRIPTID,"OnPlayerLeave",sceneId, selfId)
    TimerCommand( sceneId, selfId, 1, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, GUILDBATTLE_SCRIPTID,-1,-1);
    CallScriptFunction( GUILDBATTLE_SCRIPTID,"GuildBattleKickPlayer",sceneId,selfId)
end

--**********************************
--����
--**********************************
function x550524_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--����
--**********************************
function x550524_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--����Ƿ�����ύ
--**********************************
function x550524_CheckSubmit( sceneId, selfId )
end

--**********************************
--�ύ
--**********************************
function x550524_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

