function x600000_OnActiveEvent(sceneId, selfId)

	BeginAddItem(sceneId)
		AddItem( sceneId,12010100,1)
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		AddItemListToPlayer(sceneId,selfId)	
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "���������̣�")
			EndQuestEvent()
	else 
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "��Ʒ���������޷��õ����̣���")
		EndQuestEvent()	
	end	
	DispatchQuestTips(sceneId, selfId);

end