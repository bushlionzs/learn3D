--���ܣ���������ʯ��

x560305_g_ScriptId = 560305
x560305_g_MissionName="������ʯ��"
x560305_g_ShopList={305}
--**********************************

--������ں���

--**********************************

function x560305_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560305_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560305_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560305_g_ScriptId, x560305_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560305_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560305_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560305_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560305_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560305_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560305_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560305_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560305_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end