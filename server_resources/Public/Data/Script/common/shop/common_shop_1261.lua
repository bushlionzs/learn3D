--���ܣ�ר���츳����̵�

x561261_g_ScriptId = 561261
x561261_g_MissionName="ר���츳����̵�"
x561261_g_ShopList={1261}
--**********************************

--������ں���

--**********************************

function x561261_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x561261_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x561261_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 80 then
		AddQuestNumText(sceneId, x561261_g_ScriptId, x561261_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x561261_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x561261_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x561261_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x561261_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x561261_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x561261_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x561261_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x561261_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end