--���ܣ��̽����̵�

x561253_g_ScriptId = 561253
x561253_g_MissionName="�̽����̵�"
x561253_g_ShopList={1253}
--**********************************

--������ں���

--**********************************

function x561253_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x561253_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x561253_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 60 then
		AddQuestNumText(sceneId, x561253_g_ScriptId, x561253_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x561253_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x561253_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x561253_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x561253_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x561253_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x561253_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x561253_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x561253_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end