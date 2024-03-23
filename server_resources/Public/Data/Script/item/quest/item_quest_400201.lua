
x400201_g_scriptId = 400201
x400201_g_Impact1 = 7528 --效果ID，先无视好了

function x400201_ProcEventEntry( sceneId, selfId, bagIndex )
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"沾有血迹的黑羽密信")
						AddQuestText(sceneId,"\n\t感谢你的加入，当我们的计划成功时，你就是王国新的领导者，海都大王也已经奉命开始行动，海湾的能量晶石会使我们的巫师部队的能力大大提升。那些迦色尼人都是一群唯利是图的蛮荒人，他们的智力甚至不如那些失败了的阿兰人。\n \n\t秘密的聚集地已经初具规模，相信举杯庆祝的日子已经不远了。\n \n \n\t\t\t\t勃鲁合")
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, selfId, 400201, 2700);
		
end

function x400201_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑

end

function x400201_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x400201_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400201_OnDeplete( sceneId, selfId )
	return 1
end

function x400201_OnActivateOnce( sceneId, selfId )
end

function x400201_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
