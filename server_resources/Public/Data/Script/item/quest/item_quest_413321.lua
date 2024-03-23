--波斯高原召唤旭烈兀
x413321_g_scriptId  = 413321
x413321_g_Impact1   = 7520--效果ID，先无视好了
x413321_g_MissionId = 770
x413321_g_doing =0
x413321_g_xueliewu =0
x413321_g_mengguwushi1= 0
x413321_g_mengguwushi2=	0
x413321_g_mengguwushi3=	0
x413321_g_mengguwushi4=	0
x413321_g_mengguwushi5=	0
--**********************************
--事件交互入口
--**********************************
function x413321_ProcEventEntry( sceneId, selfId, bagIndex )
    local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x413321_g_Impact1 )
  		
    if bCplay == 1 then
    	if GetItemCount(sceneId,selfId,13060033) == 0 then
        x413321_g_xuliewu=CreateMonster(sceneId, 931,204,219,0,1,-1,-1,24,90000)
        x413321_g_mengguwushi1=CreateMonster(sceneId, 937,205,216,0,1,-1,-1,24,90000)
        x413321_g_mengguwushi2=CreateMonster(sceneId, 937,204,217,0,1,-1,-1,24,90000)
        x413321_g_mengguwushi3=CreateMonster(sceneId, 937,205,218,0,1,-1,-1,24,90000)
        x413321_g_mengguwushi4=CreateMonster(sceneId, 937,205,219,0,1,-1,-1,24,90000)
        x413321_g_mengguwushi5=CreateMonster(sceneId, 937,204,218,0,1,-1,-1,24,90000)
        CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 19 )
    	end
    end

    return bCplay


-- 不需要这个接口，但要保留空函数
end


function x413321_IsSkillLikeScript( sceneId, selfId)
 
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x413321_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x413321_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413321_OnDeplete( sceneId, selfId )

	return 1
end

function x413321_OnActivateOnce( sceneId, selfId )
end

function x413321_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
