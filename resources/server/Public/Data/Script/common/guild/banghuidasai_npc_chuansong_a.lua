
--MisDescBegin
--脚本号
x550524_g_ScriptId = 550524


--任务文本描述
x550524_g_MissionName="山寨前线传送"
--x550524_g_CountryID = 3
--MisDescEnd

x550524_g_ChuanSong_X = 226.027695
x550524_g_ChuanSong_Z = 232.85527



function x550524_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

    --战场未开放
    if GetGuildBattleStatus(sceneId) ~= 3 then
        AddQuestNumText(sceneId,x550524_g_ScriptId,"离开战场",3,2)
        return
    end

    --仅对A阵营的人有效
	local nGuildA = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_A_GUILD )
    local nGuildB = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_B_GUILD )

    local nGuildId = GetGuildID( sceneId,selfId )

    --设置在战场中的阵营属性
    local nFlag = -1
    if nGuildId == nGuildA then
        nFlag = 0
    elseif nGuildId == nGuildB then
        nFlag = 1
    end
    
    if nFlag == 0 or nFlag == -1 then
	    --AddQuestNumText(sceneId,x550524_g_ScriptId,"前线传送",13,1)
        AddQuestNumText(sceneId,x550524_g_ScriptId,"离开战场",3,2)
    end
end


function x550524_ProcEventEntry( sceneId, selfId, targetId,idScript,idExt )

    if idExt == 2 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"你真的要离开战场吗？")
        EndQuestEvent(sceneId)
        DispatchQuestInfo(sceneId,selfId,targetId,x550524_g_ScriptId,-1)
        return 1

    end

	if GetGuildBattleStatus(sceneId) ~= 3 then
 		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "战场未开放");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end

    --仅对A阵营的人有效
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
--检测接受条件
--**********************************
function x550524_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x550524_ProcAccept( sceneId, selfId )
    CallScriptFunction( GUILDBATTLE_SCRIPTID,"OnPlayerLeave",sceneId, selfId)
    TimerCommand( sceneId, selfId, 1, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, GUILDBATTLE_SCRIPTID,-1,-1);
    CallScriptFunction( GUILDBATTLE_SCRIPTID,"GuildBattleKickPlayer",sceneId,selfId)
end

--**********************************
--放弃
--**********************************
function x550524_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--继续
--**********************************
function x550524_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--检测是否可以提交
--**********************************
function x550524_CheckSubmit( sceneId, selfId )
end

--**********************************
--提交
--**********************************
function x550524_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

