x413303_g_scriptId  = 413303--召唤沙蛇脚本
x413303_g_Impact1   = -1--效果ID，先无视好了
x413303_g_MissionId = 474
x413303_g_doing =0
x413303_g_shashe =0
--**********************************
--事件交互入口
--**********************************
function x413303_ProcEventEntry( sceneId, selfId, bagIndex )
    local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x413303_g_Impact1 )
  
    if bCplay == 1 then
        x413303_g_shashe=CreateMonster(sceneId, 816,186,200,5,1,-1,-1,21,120000)
        x413303_g_shashe=CreateMonster(sceneId, 816,184,213,5,1,-1,-1,21,120000)
    end

    return bCplay


-- 不需要这个接口，但要保留空函数
end


function x413303_IsSkillLikeScript( sceneId, selfId)
 
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x413303_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x413303_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413303_OnDeplete( sceneId, selfId )

	return 1
end

function x413303_OnActivateOnce( sceneId, selfId )
end

function x413303_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
