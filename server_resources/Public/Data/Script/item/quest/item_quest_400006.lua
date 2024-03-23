x400006_g_scriptId  = 400006--火炮弹脚本
x400006_g_Impact1   = 1241--效果ID，先无视好了
x400006_g_Impact2   = -1 --不用


--**********************************
--事件交互入口
--**********************************
function x400006_ProcEventEntry( sceneId, selfId, bagIndex )
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"你必须到达60级，接受之后你就会接受武林大会任务")
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, selfId, 270000, 3533);
-- 不需要这个接口，但要保留空函数
end


function x400006_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x400006_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x400006_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400006_OnDeplete( sceneId, selfId )

	return 1
end

function x400006_OnActivateOnce( sceneId, selfId )
end

function x400006_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
