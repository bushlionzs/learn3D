
--MisDescBegin
--脚本号
x550527_g_ScriptId = 550527


--任务文本描述
x550527_g_MissionName="山庄回援传送者"
--x550527_g_CountryID = 3
--MisDescEnd

x550527_g_ChuanSong_X = 24.689863
x550527_g_ChuanSong_Z = 234.467072



function x550527_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

    --战场未开放
    if GetGuildBattleStatus(sceneId) ~= 3 then
        return
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

    if nFlag == 1 then
	    AddQuestNumText(sceneId,x550527_g_ScriptId,"回援传送",13,1)
    end
end


function x550527_ProcEventEntry( sceneId, selfId, targetId,idScript,idExt )

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

    SetPos(sceneId,selfId,x550527_g_ChuanSong_X,x550527_g_ChuanSong_Z)


end

--********************
--检测接受条件
--**********************************
function x550527_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x550527_ProcAccept( sceneId, selfId )

end

--**********************************
--放弃
--**********************************
function x550527_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--继续
--**********************************
function x550527_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--检测是否可以提交
--**********************************
function x550527_CheckSubmit( sceneId, selfId )
end

--**********************************
--提交
--**********************************
function x550527_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

