--���ܣ���Ʒ�̵�

x560150_g_ScriptId = 560150
x560150_g_MissionName="����̵�"

--**********************************

--������ں���

--**********************************

function x560150_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�

	CallScriptFunction(560888, "OnDispatchGoldShopItem", sceneId, selfId, 0,0)

end



--**********************************

--�о��¼�

--**********************************

function x560150_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560150_g_ScriptId, x560150_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560150_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560150_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560150_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560150_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560150_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560150_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560150_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560150_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end