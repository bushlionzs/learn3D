--���ܣ���Ʒ�̵�

x560130_g_ScriptId = 560130
x560130_g_MissionName="������ʯ"
x560130_g_ShopList={130}
--**********************************

--������ں���

--**********************************

function x560130_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560130_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560130_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560130_g_ScriptId, x560130_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560130_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560130_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560130_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560130_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560130_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560130_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560130_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560130_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end