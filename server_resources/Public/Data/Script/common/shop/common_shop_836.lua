--���ܣ�����������ͷ��������䷽��

x560836_g_ScriptId = 560836
x560836_g_MissionName="����������ͷ��������䷽��"
x560836_g_ShopList={836}
--**********************************

--������ں���

--**********************************

function x560836_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560836_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560836_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560836_g_ScriptId, x560836_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560836_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560836_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560836_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560836_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560836_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560836_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560836_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560836_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end