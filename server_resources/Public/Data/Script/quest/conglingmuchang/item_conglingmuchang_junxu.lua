
------------------------------------------------------------------------------------------
--一般物品的默认脚本

--脚本号

x203400_g_scriptId 		= 203400 
x203400_g_BonusItem     = {{item = 10201001,n=1},{item = 10261001,n=1}}


function x203400_ProcEventEntry( sceneId, selfId, bagIndex )
local bCplay =  DelItem(sceneId, selfId,13010122,1)
    if bCplay == 1 then
      	BeginAddItem(sceneId)
		AddBindItem( sceneId, 10201001, 1 )

		AddBindItem( sceneId, 10261001, 1 )

	local ret = EndAddItem(sceneId,selfId)

	if ret>0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"你打开了新兵装备，获得了家传腰带和家传头盔！")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			AddItemListToPlayer(sceneId,selfId)
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"背包已满，无法得到物品！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	end
    end
        return bCplay
end

function x203400_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑

end

function x203400_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。

end

function x203400_OnConditionCheck( sceneId, selfId )
	return 0
end

function x203400_OnDeplete( sceneId, selfId )
	return 0
end

function x203400_OnActivateOnce( sceneId, selfId )
end

function x203400_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
