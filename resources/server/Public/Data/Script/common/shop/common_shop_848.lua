--���ܣ���˹��������ָ����Ʒ�䷽��

x560848_g_ScriptId = 560848
x560848_g_MissionName="��˹��������ָ����Ʒ�䷽��"
x560848_g_ShopList={848}
--**********************************

--������ں���

--**********************************

function x560848_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560848_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560848_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560848_g_ScriptId, x560848_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560848_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560848_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560848_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560848_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560848_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560848_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560848_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560848_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end