--���ܣ�ƽ���츳����̵�

x561260_g_ScriptId = 561260
x561260_g_MissionName="ƽ���츳����̵�"
x561260_g_ShopList={1260}
--**********************************

--������ں���

--**********************************

function x561260_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x561260_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x561260_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 80 then
		AddQuestNumText(sceneId, x561260_g_ScriptId, x561260_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x561260_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x561260_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x561260_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x561260_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x561260_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x561260_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x561260_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x561260_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end