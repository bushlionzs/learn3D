--���ܣ��ɹ�ѱ���䷽��

x560113_g_ScriptId = 560113
x560113_g_MissionName="�ɹ�ѱ���䷽��"
x560113_g_ShopList={113}
--**********************************

--������ں���

--**********************************

function x560113_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560113_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560113_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560113_g_ScriptId, x560113_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560113_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560113_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560113_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560113_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560113_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560113_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560113_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560113_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end