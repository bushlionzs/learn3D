--���ܣ�ӡ���鱦������ʯ�౦ʯ�䷽��

x560808_g_ScriptId = 560808
x560808_g_MissionName="ӡ���鱦������ʯ�౦ʯ�䷽��"
x560808_g_ShopList={808}
--**********************************

--������ں���

--**********************************

function x560808_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560808_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560808_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560808_g_ScriptId, x560808_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560808_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560808_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560808_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560808_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560808_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560808_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560808_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560808_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end