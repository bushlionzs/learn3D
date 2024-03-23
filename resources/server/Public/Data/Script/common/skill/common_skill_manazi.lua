function x600000_OnActiveEvent(sceneId, selfId)

	BeginAddItem(sceneId)
		AddItem( sceneId,12010100,1)
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		AddItemListToPlayer(sceneId,selfId)	
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "你获得了马奶！")
			EndQuestEvent()
	else 
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "物品栏已满，无法得到马奶！！")
		EndQuestEvent()	
	end	
	DispatchQuestTips(sceneId, selfId);

end