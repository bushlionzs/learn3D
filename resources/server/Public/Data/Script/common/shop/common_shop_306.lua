--���ܣ��󶼱�ʯ�̵�

x560306_g_ScriptId = 560306
x560306_g_MissionName="��ʯ�̵�"
x560306_g_ShopList={306}
--**********************************

--������ں���

--**********************************

function x560306_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560306_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560306_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560306_g_ScriptId, x560306_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560306_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560306_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560306_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560306_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560306_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560306_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560306_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560306_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end