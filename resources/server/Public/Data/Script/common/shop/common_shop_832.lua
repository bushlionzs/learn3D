--���ܣ�ͻ�ʶ�������������Ʒ�䷽��

x560832_g_ScriptId = 560832
x560832_g_MissionName="ͻ�ʶ�������������Ʒ�䷽��"
x560832_g_ShopList={832}
--**********************************

--������ں���

--**********************************

function x560832_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560832_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560832_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560832_g_ScriptId, x560832_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560832_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560832_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560832_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560832_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560832_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560832_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560832_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560832_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end