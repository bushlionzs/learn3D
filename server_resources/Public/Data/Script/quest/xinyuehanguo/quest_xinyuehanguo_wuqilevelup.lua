--���ܣ�����ǿ������
--NPC������ǿ����ʦ

--MisDescBegin
x211026_g_ScriptId = 211026

x211026_g_MissionName = "ǿ�������̵�"

x211026_g_ShopList ={6}
--MisDescEnd
--**********************************

--������ں���

--**********************************

function x211026_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x211026_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x211026_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x211026_g_ScriptId, x211026_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211026_ProcAcceptCheck(sceneId, selfId, targetId)

end



--**********************************

--����

--**********************************

function x211026_ProcAccept(sceneId, selfId)
    
end



--**********************************

--����

--**********************************

function x211026_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211026_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211026_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211026_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211026_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211026_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end