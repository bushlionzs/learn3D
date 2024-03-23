
--MisDescBegin
--脚本号
x550526_g_ScriptId = 550526


--任务文本描述
x550526_g_MissionName="山庄前线传送者"
--x550526_g_CountryID = 3
--MisDescEnd

x550526_g_ChuanSong_X = 22.041122
x550526_g_ChuanSong_Z = 23.897568



function x550526_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

    --战场未开放
    if GetGuildBattleStatus(sceneId) ~= 3 then
        AddQuestNumText(sceneId,x550526_g_ScriptId,"离开战场",3,2)
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
    else
        nFlag = 1
    end

    if nFlag == 1 then
	    --AddQuestNumText(sceneId,x550526_g_ScriptId,"前线传送",13,1)
        AddQuestNumText(sceneId,x550526_g_ScriptId,"离开战场",3,2)
    end
end


function x550526_ProcEventEntry( sceneId, selfId, targetId,idScript,idExt )

    if idExt == 2 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"你真的要离开战场吗？")
        EndQuestEvent(sceneId)
        DispatchQuestInfo(sceneId,selfId,targetId,x550526_g_ScriptId,-1)
        return 1
    end

	if GetGuildBattleStatus(sceneId) ~= 3 then
 		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "战场未开放");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end

    --仅对A阵营的人有效
	local nGuildA = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_A_GUILD )
    local nGuildB = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_B_GUILD )

    local nGuildId = GetGuildID( sceneId,selfId )

    --设置在战场中的阵营属性
    local nFlag = 1
    if nGuildId == nGuildA then
        nFlag = 0
    elseif nGuildId == nGuildB then
        nFlag = 1
    end

    if nFlag ~= 1 then
        return
    end

    if idExt == 1 then
        SetPos(sceneId,selfId,x550526_g_ChuanSong_X,x550526_g_ChuanSong_Z)
    end


end

--********************
--检测接受条件
--**********************************
function x550526_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x550526_ProcAccept( sceneId, selfId )
    CallScriptFunction( GUILDBATTLE_SCRIPTID,"OnPlayerLeave",sceneId, selfId)
    TimerCommand( sceneId, selfId, 1, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, GUILDBATTLE_SCRIPTID,-1,-1);
    CallScriptFunction( GUILDBATTLE_SCRIPTID,"GuildBattleKickPlayer",sceneId,selfId)
end

--**********************************
--放弃
--**********************************
function x550526_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--继续
--**********************************
function x550526_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--检测是否可以提交
--**********************************
function x550526_CheckSubmit( sceneId, selfId )
end

--**********************************
--提交
--**********************************
function x550526_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

