--���ܣ��󶼣���˹�����䷽��

x560315_g_ScriptId = 560315
x560315_g_MissionName="��˹�����䷽��"
x560315_g_ShopList={315}
--**********************************

--������ں���

--**********************************

function x560315_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560315_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560315_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

--	local nLevel = GetLevel(sceneId,selfId)
--	if nLevel >= 60 then
		AddQuestNumText(sceneId, x560315_g_ScriptId, x560315_g_MissionName,10)
--	else
--		return
--	end
	
end



--**********************************

--����������

--**********************************

function x560315_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560315_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560315_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560315_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560315_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560315_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560315_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560315_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end