--���ܣ���Ʒ�̵�

x560105_g_ScriptId = 560105
x560105_g_MissionName="���ַ��ߵ�"
x560105_g_ShopList={105}
--**********************************

--������ں���

--**********************************

function x560105_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560105_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560105_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560105_g_ScriptId, x560105_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560105_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560105_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560105_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560105_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560105_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560105_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560105_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560105_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end