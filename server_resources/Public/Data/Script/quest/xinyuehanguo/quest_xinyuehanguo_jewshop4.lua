--���ܣ�������
--NPC���������ϰ�

x211063_g_ScriptId = 211063
x211063_g_MissionName="��ʯ�̵���"
x211063_g_ShopList={13}
--**********************************

--������ں���

--**********************************

function x211063_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x211063_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x211063_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211063_g_ScriptId, x211063_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211063_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211063_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211063_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211063_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211063_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211063_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211063_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211063_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end