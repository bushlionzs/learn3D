--���ܣ�������
--NPC���������ϰ�

x211061_g_ScriptId = 211061
x211061_g_MissionName="����̵�һ"
x211061_g_ShopList={11}
--**********************************

--������ں���

--**********************************

function x211061_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x211061_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x211061_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211061_g_ScriptId, x211061_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211061_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211061_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211061_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211061_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211061_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211061_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211061_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211061_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end