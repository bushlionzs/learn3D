--突厥王城召唤突厥伏兵
x413312_g_scriptId  = 413312
x413312_g_Impact1   = -1--效果ID，先无视好了
x413312_g_MissionId = 710
x413312_g_doing =0
x413312_g_shashe =0
--**********************************
--事件交互入口
--**********************************
function x413312_ProcEventEntry( sceneId, selfId, bagIndex )
    local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x413312_g_Impact1 )
  		
    if bCplay == 1 then
    	if GetItemCount(sceneId,selfId,13060025) == 0 then
        x413312_g_shashe=CreateMonster(sceneId, 908,86,155,5,1,-1,-1,21,60000)
        x413312_g_shashe=CreateMonster(sceneId, 908,85,154,5,1,-1,-1,21,60000)
        x413312_g_shashe=CreateMonster(sceneId, 908,85,165,5,1,-1,-1,21,60000)
        x413312_g_shashe=CreateMonster(sceneId, 908,86,160,5,1,-1,-1,21,60000)
        x413312_g_shashe=CreateMonster(sceneId, 908,85,160,5,1,-1,-1,21,60000)
        x413312_g_shashe=CreateMonster(sceneId, 908,84,160,5,1,-1,-1,21,60000)
        x413312_g_shashe=CreateMonster(sceneId, 908,86,165,5,1,-1,-1,21,60000)
        x413312_g_shashe=CreateMonster(sceneId, 908,86,150,5,1,-1,-1,21,60000)
        CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 15 )
    	end
    end

    return bCplay


-- 不需要这个接口，但要保留空函数
end


function x413312_IsSkillLikeScript( sceneId, selfId)
 
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x413312_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x413312_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413312_OnDeplete( sceneId, selfId )

	return 1
end

function x413312_OnActivateOnce( sceneId, selfId )
end

function x413312_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
