--���ܣ�ͻ�ʶ����������������䷽��

x560834_g_ScriptId = 560834
x560834_g_MissionName="ͻ�ʶ������������䷽��"
x560834_g_ShopList={834}
--**********************************

--������ں���

--**********************************

function x560834_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560834_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560834_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560834_g_ScriptId, x560834_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560834_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560834_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560834_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560834_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560834_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560834_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560834_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560834_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end