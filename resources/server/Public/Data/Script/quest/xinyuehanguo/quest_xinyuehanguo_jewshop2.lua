--���ܣ�������
--NPC���������ϰ�

x211059_g_ScriptId = 211059
x211059_g_MissionName="��ʯ�̵��"
x211059_g_ShopList={9}
--**********************************

--������ں���

--**********************************

function x211059_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x211059_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x211059_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211059_g_ScriptId, x211059_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211059_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211059_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211059_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211059_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211059_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211059_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211059_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211059_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end