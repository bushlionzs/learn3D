--�淨���󶼸���--��������--ҩ��

x560911_g_ScriptId = 560911
x560911_g_MissionName="������ҩ��"
x560911_g_ShopList={911}
--**********************************

--������ں���

--**********************************

function x560911_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560911_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560911_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

		AddQuestNumText(sceneId, x560911_g_ScriptId, x560911_g_MissionName,10)

end



--**********************************

--����������

--**********************************

function x560911_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560911_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560911_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560911_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560911_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560911_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560911_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560911_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end