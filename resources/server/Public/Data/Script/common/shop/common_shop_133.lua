--���ܣ���Ʒ�̵�

x560133_g_ScriptId = 560133
x560133_g_MissionName="�鱦�ӹ��䷽�̵�"
x560133_g_ShopList={133}
--**********************************

--������ں���

--**********************************

function x560133_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560133_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560133_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560133_g_ScriptId, x560133_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560133_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560133_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560133_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560133_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560133_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560133_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560133_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560133_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end