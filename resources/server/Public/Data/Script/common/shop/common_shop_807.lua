--���ܣ�ӡ���鱦���챦ʯ�౦ʯ�䷽��

x560807_g_ScriptId = 560807
x560807_g_MissionName="ӡ���鱦���챦ʯ�౦ʯ�䷽��"
x560807_g_ShopList={807}
--**********************************

--������ں���

--**********************************

function x560807_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560807_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560807_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560807_g_ScriptId, x560807_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560807_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560807_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560807_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560807_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560807_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560807_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560807_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560807_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end