--���ܣ�������
--NPC���������ϰ�

x211062_g_ScriptId = 211062
x211062_g_MissionName="����̵��"
x211062_g_ShopList={12}
--**********************************

--������ں���

--**********************************

function x211062_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x211062_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x211062_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211062_g_ScriptId, x211062_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211062_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211062_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211062_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211062_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211062_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211062_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211062_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211062_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end