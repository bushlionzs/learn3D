--���ܣ�ӡ���鱦���챦ʯ�౦ʯ�䷽��

x560812_g_ScriptId = 560812
x560812_g_MissionName="ӡ���鱦���챦ʯ�౦ʯ�䷽��"
x560812_g_ShopList={812}
--**********************************

--������ں���

--**********************************

function x560812_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560812_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560812_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560812_g_ScriptId, x560812_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560812_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560812_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560812_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560812_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560812_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560812_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560812_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560812_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end