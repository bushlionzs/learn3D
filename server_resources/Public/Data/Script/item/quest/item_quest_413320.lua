--波斯高原召唤剑灵
x413320_g_scriptId  = 413320
x413320_g_Impact1   = -1--效果ID，先无视好了
x413320_g_MissionId = 765
x413320_g_doing =0
x413320_g_jianling =0
--**********************************
--事件交互入口
--**********************************
function x413320_ProcEventEntry( sceneId, selfId, bagIndex )
    local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x413320_g_Impact1 )
  		
    if bCplay == 1 then
    	if GetItemCount(sceneId,selfId,13060032) == 0 then
        x413320_g_jianling=CreateMonster(sceneId, 930,119,224,5,1,-1,-1,21,60000)
        CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 19 )
    	end
    end

    return bCplay


-- 不需要这个接口，但要保留空函数
end


function x413320_IsSkillLikeScript( sceneId, selfId)
 
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x413320_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x413320_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413320_OnDeplete( sceneId, selfId )

	return 1
end

function x413320_OnActivateOnce( sceneId, selfId )
end

function x413320_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
