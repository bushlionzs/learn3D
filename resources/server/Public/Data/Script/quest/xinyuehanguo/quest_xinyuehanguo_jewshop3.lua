--���ܣ�������
--NPC���������ϰ�

x211060_g_ScriptId = 211060
x211060_g_MissionName="�����̵��"
x211060_g_ShopList={10}
--**********************************

--������ں���

--**********************************

function x211060_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x211060_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x211060_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211060_g_ScriptId, x211060_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211060_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211060_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211060_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211060_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211060_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211060_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211060_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211060_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end