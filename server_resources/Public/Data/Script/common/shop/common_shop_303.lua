--���ܣ���ҩƷ��

x560303_g_ScriptId = 560303
x560303_g_MissionName="ҩƷ��"
x560303_g_ShopList={303}
--**********************************

--������ں���

--**********************************

function x560303_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560303_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560303_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560303_g_ScriptId, x560303_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560303_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560303_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560303_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560303_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560303_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560303_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560303_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560303_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end