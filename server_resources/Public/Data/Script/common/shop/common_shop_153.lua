--���ܣ�ͻ�ʶ����䷽��

x560153_g_ScriptId = 560153
x560153_g_MissionName="ͻ�ʶ����䷽��"
x560153_g_ShopList={153}
--**********************************

--������ں���

--**********************************

function x560153_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560153_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560153_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

--	local nLevel = GetLevel(sceneId,selfId)
--	if nLevel >= 60 then
		AddQuestNumText(sceneId, x560153_g_ScriptId, x560153_g_MissionName,10)
--	else
--		return
--	end
	
end



--**********************************

--����������

--**********************************

function x560153_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560153_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560153_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560153_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560153_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560153_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560153_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560153_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end