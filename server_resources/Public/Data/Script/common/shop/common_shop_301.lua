--���ܣ��󶼷��ߵ�

x560301_g_ScriptId = 560301
x560301_g_MissionName="�󶼷��ߵ�"
x560301_g_ShopList={301}
--**********************************

--������ں���

--**********************************

function x560301_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560301_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560301_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560301_g_ScriptId, x560301_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560301_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560301_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560301_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560301_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560301_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560301_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560301_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560301_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end