--���ܣ���Ʒ�̵�

x560131_g_ScriptId = 560131
x560131_g_MissionName="�鱦�ӹ��䷽�̵�"
x560131_g_ShopList={131}
--**********************************

--������ں���

--**********************************

function x560131_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560131_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560131_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560131_g_ScriptId, x560131_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560131_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560131_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560131_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560131_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560131_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560131_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560131_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560131_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end