--���ܣ����������䷽

x560318_g_ScriptId = 560318
x560318_g_MissionName="���������䷽�̵�"
x560318_g_ShopList={318}
--**********************************

--������ں���

--**********************************

function x560318_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560318_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560318_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

--	local nLevel = GetLevel(sceneId,selfId)
--	if nLevel >= 60 then
		AddQuestNumText(sceneId, x560318_g_ScriptId, x560318_g_MissionName,10)
--	else
--		return
--	end
	
end



--**********************************

--����������

--**********************************

function x560318_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560318_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560318_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560318_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560318_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560318_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560318_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560318_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end