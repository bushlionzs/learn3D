--���ܣ������������̵�

x561500_g_ScriptId = 561500
x561500_g_MissionName="�����̵�"
x561500_g_EXShopList={0}
--**********************************

--������ں���

--**********************************

function x561500_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	local curTime = GetMinOfDay()

	if GetWeek() ~= 0 and GetWeek() ~= 6 or curTime < 540 or curTime >= 1320 then
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����̵�ֻ����ĩ12�㵽22��֮�俪��",8,3)
    	return
	else
		DispatchDynamicShopItem(sceneId, selfId, targetId, x561500_g_EXShopList[1])
	end
end



--**********************************

--�о��¼�

--**********************************

function x561500_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 85 then
		AddQuestNumText(sceneId, x561500_g_ScriptId, x561500_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x561500_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x561500_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x561500_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x561500_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x561500_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x561500_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x561500_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x561500_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end