--���ܣ��촫����װ����-��ǹ

x560081_g_ScriptId = 560081
x560081_g_MissionName="�촫����װ����"
x560081_g_ShopList={81}
--**********************************

--������ں���

--**********************************

function x560081_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560081_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560081_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	local nLevel = GetLevel(sceneId, selfId)
	if nLevel >= 35 then
		AddQuestNumText(sceneId, x560081_g_ScriptId, x560081_g_MissionName,10)
	else
		return
	end

end



--**********************************

--����������

--**********************************

function x560081_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560081_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560081_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560081_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560081_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560081_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560081_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560081_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end