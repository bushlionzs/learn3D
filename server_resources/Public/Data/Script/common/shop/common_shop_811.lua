--���ܣ�ӡ���鱦���Ʊ�ʯ�౦ʯ�䷽��

x560811_g_ScriptId = 560811
x560811_g_MissionName="ӡ���鱦���Ʊ�ʯ�౦ʯ�䷽��"
x560811_g_ShopList={811}
--**********************************

--������ں���

--**********************************

function x560811_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560811_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560811_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560811_g_ScriptId, x560811_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560811_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560811_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560811_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560811_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560811_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560811_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560811_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560811_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end