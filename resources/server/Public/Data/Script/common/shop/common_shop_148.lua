--���ܣ����������䷽

x560148_g_ScriptId = 560148
x560148_g_MissionName="���������䷽��"
x560148_g_ShopList={148}
--**********************************

--������ں���

--**********************************

function x560148_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560148_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560148_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

--	local nLevel = GetLevel(sceneId,selfId)
--	if nLevel >= 60 then
		AddQuestNumText(sceneId, x560148_g_ScriptId, x560148_g_MissionName,10)
--	else
--		return
--	end
	
end



--**********************************

--����������

--**********************************

function x560148_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560148_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560148_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560148_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560148_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560148_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560148_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560148_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end