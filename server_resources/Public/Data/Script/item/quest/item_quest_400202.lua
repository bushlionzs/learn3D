
x400202_g_scriptId = 400202
x400202_g_Impact1 = 7528 --效果ID，先无视好了

function x400202_ProcEventEntry( sceneId, selfId, bagIndex )
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"浸湿的黑羽密信")
						AddQuestText(sceneId,"\n\t受命于帖木儿陛下，笃哇大王将出兵边塞地区，夺取西凉三宝。珍珠渔港的能量晶矿对我们巫师部队的能力有很大的提升，我希望你能顺利地把它们运回来给我，至于那个富裕的渔港，所有的东西都是你们的。\n \n\t等你们带回我们想要的东西，一定还会有更丰厚的报酬，能力晶矿能不能破解佛光塔的机关目前还没有被验证，如果能够成功进入佛光塔，除了那件东西之外，所有的宝物都是你的。\n \n\t另外你的另一支部队，在波斯海湾也取得了不错的战绩，我们期待举杯同庆的日子。\n \n \n\t\t\t\t海都")
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, selfId, 400202, 2700);
		
end

function x400202_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑

end

function x400202_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x400202_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400202_OnDeplete( sceneId, selfId )
	return 1
end

function x400202_OnActivateOnce( sceneId, selfId )
end

function x400202_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
