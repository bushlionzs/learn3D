--���ܣ����ߵ�
--NPC�����ߵ��ϰ�

x211020_g_ScriptId = 211020
x211020_g_MissionName="�����̵�"
x211020_g_ShopList={4}
--**********************************

--������ں���

--**********************************

function x211020_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x211020_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x211020_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211020_g_ScriptId, x211020_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211020_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211020_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211020_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211020_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211020_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211020_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211020_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211020_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end