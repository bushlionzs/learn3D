--���ܣ���˹��������������Ʒ�䷽��

x560854_g_ScriptId = 560854
x560854_g_MissionName="��˹��������������Ʒ�䷽��"
x560854_g_ShopList={854}
--**********************************

--������ں���

--**********************************

function x560854_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560854_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560854_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560854_g_ScriptId, x560854_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560854_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560854_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560854_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560854_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560854_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560854_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560854_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560854_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end