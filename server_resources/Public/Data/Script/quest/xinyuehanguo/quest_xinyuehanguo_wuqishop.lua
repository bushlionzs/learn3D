--���ܣ�������
--NPC���������ϰ�

x211019_g_ScriptId = 211019
x211019_g_MissionName="�����̵�"
x211019_g_ShopList={3}
--**********************************

--������ں���

--**********************************

function x211019_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x211019_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x211019_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211019_g_ScriptId, x211019_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211019_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211019_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211019_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211019_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211019_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211019_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211019_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211019_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end