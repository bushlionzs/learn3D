--���ܣ�ӡ���鱦���̱�ʯ�౦ʯ�䷽��

x560814_g_ScriptId = 560814
x560814_g_MissionName="ӡ���鱦���̱�ʯ�౦ʯ�䷽��"
x560814_g_ShopList={814}
--**********************************

--������ں���

--**********************************

function x560814_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560814_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560814_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560814_g_ScriptId, x560814_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560814_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560814_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560814_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560814_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560814_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560814_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560814_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560814_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end