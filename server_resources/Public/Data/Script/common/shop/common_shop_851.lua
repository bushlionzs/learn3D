--���ܣ���˹��������������Ʒ�䷽��

x560851_g_ScriptId = 560851
x560851_g_MissionName="��˹��������������Ʒ�䷽��"
x560851_g_ShopList={851}
--**********************************

--������ں���

--**********************************

function x560851_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560851_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560851_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560851_g_ScriptId, x560851_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560851_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560851_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560851_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560851_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560851_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560851_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560851_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560851_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end