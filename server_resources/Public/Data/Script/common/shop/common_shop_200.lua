--���ܣ���Ʒ�̵�

x560200_g_ScriptId = 560200
x560200_g_MissionName="�н����˵ĵ���"
x560200_g_ShopList={200}
--**********************************

--������ں���

--**********************************

function x560200_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560200_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560200_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560200_g_ScriptId, x560200_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560200_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560200_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560200_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560200_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560200_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560200_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560200_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560200_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end