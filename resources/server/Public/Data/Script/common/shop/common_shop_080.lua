--���ܣ��촫����װ����-����

x560080_g_ScriptId = 560080
x560080_g_MissionName="�촫����װ����"
x560080_g_ShopList={80}
--**********************************

--������ں���

--**********************************

function x560080_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560080_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560080_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	local nLevel = GetLevel(sceneId, selfId)
	if nLevel >= 35 then
		AddQuestNumText(sceneId, x560080_g_ScriptId, x560080_g_MissionName,10)
	else
		return
	end

end



--**********************************

--����������

--**********************************

function x560080_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560080_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560080_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560080_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560080_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560080_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560080_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560080_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end