--���ܣ�ӡ���鱦���Ʊ�ʯ�౦ʯ�䷽��

x560806_g_ScriptId = 560806
x560806_g_MissionName="ӡ���鱦���Ʊ�ʯ�౦ʯ�䷽��"
x560806_g_ShopList={806}
--**********************************

--������ں���

--**********************************

function x560806_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560806_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560806_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560806_g_ScriptId, x560806_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560806_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560806_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560806_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560806_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560806_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560806_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560806_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560806_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end