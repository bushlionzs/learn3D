--���ܣ�������
--NPC���������ϰ�

x211058_g_ScriptId = 211058
x211058_g_MissionName="��ʯ�̵�һ"
x211058_g_ShopList={8}
--**********************************

--������ں���

--**********************************

function x211058_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x211058_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x211058_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211058_g_ScriptId, x211058_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211058_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211058_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211058_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211058_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211058_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211058_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211058_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211058_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end