--���ܣ�ͻ�ʶ����������������䷽��

x560831_g_ScriptId = 560831
x560831_g_MissionName="ͻ�ʶ������������䷽��"
x560831_g_ShopList={831}
--**********************************

--������ں���

--**********************************

function x560831_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560831_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560831_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560831_g_ScriptId, x560831_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560831_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560831_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560831_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560831_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560831_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560831_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560831_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560831_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end