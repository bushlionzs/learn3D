--���ܣ�װ��ǿ����

x560307_g_ScriptId = 560307
x560307_g_MissionName="װ��ǿ����"
x560307_g_ShopList={307}
--**********************************

--������ں���

--**********************************

function x560307_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560307_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560307_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560307_g_ScriptId, x560307_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560307_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560307_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560307_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560307_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560307_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560307_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560307_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560307_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end