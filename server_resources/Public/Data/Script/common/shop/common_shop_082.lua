--���ܣ��촫����װ����-��֪

x560082_g_ScriptId = 560082
x560082_g_MissionName="�촫����װ����"
x560082_g_ShopList={82}
--**********************************

--������ں���

--**********************************

function x560082_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560082_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560082_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	local nLevel = GetLevel(sceneId, selfId)
	if nLevel >= 35 then
		AddQuestNumText(sceneId, x560082_g_ScriptId, x560082_g_MissionName,10)
	else
		return
	end

end



--**********************************

--����������

--**********************************

function x560082_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560082_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560082_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560082_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560082_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560082_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560082_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560082_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end