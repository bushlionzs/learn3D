
x400200_g_scriptId = 400200
x400200_g_Impact1 = 7528 --效果ID，先无视好了

function x400200_ProcEventEntry( sceneId, selfId, bagIndex )
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"褶皱的黑羽密信")
						AddQuestText(sceneId,"\n\t计划已经开始实施，我们正在建立秘密的基地，锁儿罕会继续利用骸骨召唤古老的米底亚人来切断这里的补给，其他的人也已经开始行动，你们永远不会是孤军奋战，事成之后，我们会履行诺言。\n \n\t窑厂内秘藏的晶石有一种神奇的力量，能够使野兽与人产生同化，这正是你们长期以来所追求的力量，这就算我们兑现承诺的第一步吧。\n \n \n\t\t\t\t勃鲁合")
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, selfId, 400200, 2700);
		
end

function x400200_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑

end

function x400200_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x400200_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400200_OnDeplete( sceneId, selfId )
	return 1
end

function x400200_OnActivateOnce( sceneId, selfId )
end

function x400200_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
