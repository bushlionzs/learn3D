--���ܣ��촫����װ����-����

x560079_g_ScriptId = 560079
x560079_g_MissionName="�촫����װ����"
x560079_g_ShopList={79}
--**********************************

--������ں���

--**********************************

function x560079_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560079_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560079_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	local nLevel = GetLevel(sceneId, selfId)
	if nLevel >= 35 then
		AddQuestNumText(sceneId, x560079_g_ScriptId, x560079_g_MissionName,10)
	else
		return
	end

end



--**********************************

--����������

--**********************************

function x560079_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560079_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560079_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560079_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560079_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560079_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560079_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560079_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end