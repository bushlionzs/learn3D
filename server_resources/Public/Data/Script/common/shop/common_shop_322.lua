--���ܣ��鱦��ʦ�䷽�̵�

x560322_g_ScriptId = 560322
x560322_g_MissionName="�鱦��ʦ�䷽�̵�"
x560322_g_ShopList={322}
--**********************************

--������ں���

--**********************************

function x560322_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560322_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560322_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560322_g_ScriptId, x560322_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560322_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560322_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560322_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560322_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560322_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560322_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560322_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560322_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end