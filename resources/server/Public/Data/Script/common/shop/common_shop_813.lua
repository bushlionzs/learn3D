--���ܣ�ӡ���鱦������ʯ�౦ʯ�䷽��

x560813_g_ScriptId = 560813
x560813_g_MissionName="ӡ���鱦������ʯ�౦ʯ�䷽��"
x560813_g_ShopList={813}
--**********************************

--������ں���

--**********************************

function x560813_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560813_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560813_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560813_g_ScriptId, x560813_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560813_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560813_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560813_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560813_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560813_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560813_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560813_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560813_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end