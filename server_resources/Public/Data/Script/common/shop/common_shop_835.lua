--���ܣ�ͻ�ʶ�������������Ʒ�䷽��

x560835_g_ScriptId = 560835
x560835_g_MissionName="ͻ�ʶ�������������Ʒ�䷽��"
x560835_g_ShopList={835}
--**********************************

--������ں���

--**********************************

function x560835_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560835_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560835_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560835_g_ScriptId, x560835_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560835_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560835_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560835_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560835_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560835_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560835_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560835_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560835_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end