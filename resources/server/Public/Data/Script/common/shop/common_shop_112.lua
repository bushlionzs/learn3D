--���ܣ�����ѱ���䷽��

x560112_g_ScriptId = 560112
x560112_g_MissionName="����ѱ���䷽��"
x560112_g_ShopList={112}
--**********************************

--������ں���

--**********************************

function x560112_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560112_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560112_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560112_g_ScriptId, x560112_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560112_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560112_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560112_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560112_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560112_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560112_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560112_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560112_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end