--���ܣ�����ҩƷ�䷽��

x560111_g_ScriptId = 560111
x560111_g_MissionName="����ҩƷ�䷽��"
x560111_g_ShopList={111}
--**********************************

--������ں���

--**********************************

function x560111_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560111_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560111_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560111_g_ScriptId, x560111_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560111_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560111_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560111_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560111_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560111_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560111_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560111_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560111_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end