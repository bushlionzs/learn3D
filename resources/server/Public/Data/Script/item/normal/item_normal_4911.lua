--author: jiangchao
--desc	: 专精重置道具,使用本道具洗掉所有的专防技能中的点数

x404911_g_scriptId  = 404911 
x404911_g_MissionID = 9093

function x404911_ProcEventEntry( sceneId, selfId, BagIndex )
	--将所有的专防技能中的点数洗掉
	--此接口需要shangyu提供脚本接口
	
	local strText = "#Y【专精天赋】专防训练点数重置：#W\n\t使用专精重置之书将会重置您的专精天赋专防训练点数，是否确认使用？"
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, strText)
	EndQuestEvent(sceneId)
	--DispatchQuestTips(sceneId, selfId)
	--DispatchQuestInfo(sceneId, selfId, selfId, x404911_g_scriptId, x404911_g_MissionID,  0)
	DispatchQuestInfoNM(sceneId, selfId, selfId, x404911_g_scriptId, x404911_g_MissionID,  0)
	--Msg2Player(sceneId,selfId,strText, 8, 2)
	return 
	
	
end

function x404911_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x404911_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x404911_OnConditionCheck( sceneId, selfId )
	return 0
end

function x404911_OnDeplete( sceneId, selfId )

	return 0
end

function x404911_OnActivateOnce( sceneId, selfId )
end

function x404911_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end

function x404911_OnDie(sceneId, selfId, killerId)--怪死亡添加日志
		
end



function x404911_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	local ret = DelItemByIDInBag( sceneId, selfId, 12030219, 1) --删除物品
	ReallocateInherenceZhuanFangPoint( sceneId, selfId )
	Msg2Player(sceneId,selfId,"专精点数重置", 8, 2)
end



