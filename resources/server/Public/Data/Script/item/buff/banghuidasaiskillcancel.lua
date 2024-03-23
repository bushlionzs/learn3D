

--活动触发
function x300811_ProcEventEntry( sceneId, selfId, bufIndex,rorf )

	if rorf == 1 then --删除BUF
        if GetBattleSceneName( sceneId) == "zhanchang_shijiebeizhanchang/zhanchang_shijiebeizhanchang.scn" then
            -- 世界杯战场处理
            if IsPlayerMutexState( sceneId, selfId, PLAYER_STATE_DIE) ~= 1 then
                CancelSpecificImpact( sceneId, selfId, 7801)
                CancelSpecificImpact( sceneId, selfId, 7802)
                local x,y = GetWorldPos( sceneId, selfId)
                local growPointid = GetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID)
                if growPointid ~= 0 then
                    SetGrowPointPos( sceneId, growPointid, x + 1, y + 1)
                    SetGrowPointIntervalContainer( sceneId, growPointid, 1000)
                    SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_FLAGOCCUPY, -2)
                end
            end
            return
        end

        local nOwnerId = GetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_OWNER )
        if nOwnerId ~= -1 and nOwnerId == selfId then
            CancelSpecificImpact(sceneId,selfId,LD_GUILD_BATTLE_DEC_SPEED_BUF )
            local FlagNumA = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_FLAG_NUM)
            local FlagNumB = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_FLAG_NUM)
            if FlagNumA < LD_GUILD_BATTLE_FLAG_COUNT and FlagNumB < LD_GUILD_BATTLE_FLAG_COUNT then
                --双方夺旗数都小于3
                if GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_OWNER) ~= -1 then
                    --旗子有主
                    local x,y = GetWorldPos(sceneId, selfId)
                    SetGrowPointPos(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,x+1,y+1)
                    SetGrowPointIntervalContainer(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,1000)
                end
            end

            SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_OWNER,-1 )
            CallScriptFunction( GUILDBATTLE_SCRIPTID,"UpdateSceneDataFlag",sceneId,7 )
       end
	end


end

