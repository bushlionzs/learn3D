--���ܣ���˹��������������Ʒ�䷽��

x560849_g_ScriptId = 560849
x560849_g_MissionName="��˹��������������Ʒ�䷽��"
x560849_g_ShopList={849}
--**********************************

--������ں���

--**********************************

function x560849_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560849_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560849_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560849_g_ScriptId, x560849_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560849_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560849_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560849_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560849_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560849_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560849_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560849_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560849_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end