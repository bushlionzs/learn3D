--���ܣ�����������ѥ��������䷽��

x560846_g_ScriptId = 560846
x560846_g_MissionName="����������ѥ��������䷽��"
x560846_g_ShopList={846}
--**********************************

--������ں���

--**********************************

function x560846_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560846_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560846_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560846_g_ScriptId, x560846_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560846_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560846_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560846_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560846_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560846_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560846_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560846_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560846_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end