--���ܣ�ѱ���ʦ�䷽�̵�

x560323_g_ScriptId = 560323
x560323_g_MissionName="ѱ���ʦ�䷽�̵�"
x560323_g_ShopList={323}
--**********************************

--������ں���

--**********************************

function x560323_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560323_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560323_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560323_g_ScriptId, x560323_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560323_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560323_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560323_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560323_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560323_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560323_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560323_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560323_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end