--���ܣ��촫����װ����-����

x560083_g_ScriptId = 560083
x560083_g_MissionName="�촫����װ����"
x560083_g_ShopList={83}
--**********************************

--������ں���

--**********************************

function x560083_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560083_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560083_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	local nLevel = GetLevel(sceneId, selfId)
	if nLevel >= 35 then
		AddQuestNumText(sceneId, x560083_g_ScriptId, x560083_g_MissionName,10)
	else
		return
	end

end



--**********************************

--����������

--**********************************

function x560083_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560083_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560083_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560083_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560083_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560083_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560083_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560083_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end