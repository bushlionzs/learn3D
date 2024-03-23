
--MisDescBegin
--脚本号
x550525_g_ScriptId = 550525


--任务文本描述
x550525_g_MissionName="山寨回援传送者"
--x550525_g_CountryID = 3
--MisDescEnd

x550525_g_ChuanSong_X = 226.975891
x550525_g_ChuanSong_Z = 24.956709

function x550525_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

    --战场未开放
    if GetGuildBattleStatus(sceneId) ~= 3 then
        return
    end

    --仅对A阵营的人有效
	--得到玩家所属方，A或B方
    local nGuildA = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_A_GUILD )
    local nGuildB = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_B_GUILD )

    local nGuildId = GetGuildID( sceneId,selfId )

    --设置在战场中的阵营属性
     local nFlag = 0
    if nGuildId == nGuildA then
        nFlag = 0
    elseif nGuildId == nGuildB then
        nFlag = 1
    end

    if nFlag == 0 then
	    AddQuestNumText(sceneId,x550525_g_ScriptId,"回援传送",13,1)
    end
end


function x550525_ProcEventEntry( sceneId, selfId, targetId,idScript,idExt )

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
    local nFlag = 0
    if nGuildId == nGuildA then
        nFlag = 0
    elseif nGuildId == nGuildB then
        nFlag = 1
    end

    if nFlag ~= 0 then
        return
    end

    SetPos(sceneId,selfId,x550525_g_ChuanSong_X,x550525_g_ChuanSong_Z)


end

--********************
--检测接受条件
--**********************************
function x550525_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x550525_ProcAccept( sceneId, selfId )

end

--**********************************
--放弃
--**********************************
function x550525_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--继续
--**********************************
function x550525_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--检测是否可以提交
--**********************************
function x550525_CheckSubmit( sceneId, selfId )
end

--**********************************
--提交
--**********************************
function x550525_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

