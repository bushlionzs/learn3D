--���ܣ���˹��������ָ����Ʒ�䷽��

x560852_g_ScriptId = 560852
x560852_g_MissionName="��˹��������ָ����Ʒ�䷽��"
x560852_g_ShopList={852}
--**********************************

--������ں���

--**********************************

function x560852_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560852_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560852_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560852_g_ScriptId, x560852_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560852_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560852_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560852_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560852_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560852_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560852_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560852_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560852_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end