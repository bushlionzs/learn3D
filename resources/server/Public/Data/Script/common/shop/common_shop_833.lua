--���ܣ�ͻ�ʶ����������������䷽��

x560833_g_ScriptId = 560833
x560833_g_MissionName="ͻ�ʶ������������䷽��"
x560833_g_ShopList={833}
--**********************************

--������ں���

--**********************************

function x560833_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560833_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560833_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560833_g_ScriptId, x560833_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560833_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560833_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560833_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560833_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560833_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560833_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560833_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560833_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end