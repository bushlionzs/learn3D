--���ܣ�3���ﹱ�̵�

x560157_g_ScriptId = 560157
x560157_g_MissionName="�����ﹱ�̵�"
x560157_g_ShopList={157}
--**********************************

--������ں���

--**********************************

function x560157_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560157_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560157_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560157_g_ScriptId, x560157_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560157_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560157_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560157_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560157_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560157_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560157_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560157_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560157_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end