--���ܣ�������ʯ�䷽��

x560125_g_ScriptId = 560125
x560125_g_MissionName="������ʯ�䷽��"
x560125_g_ShopList={125}
--**********************************

--������ں���

--**********************************

function x560125_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560125_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560125_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560125_g_ScriptId, x560125_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560125_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560125_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560125_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560125_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560125_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560125_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560125_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560125_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end