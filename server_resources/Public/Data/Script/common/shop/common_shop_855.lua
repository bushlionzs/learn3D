--���ܣ���˹��������������Ʒ�䷽��

x560855_g_ScriptId = 560855
x560855_g_MissionName="��˹��������������Ʒ�䷽��"
x560855_g_ShopList={855}
--**********************************

--������ں���

--**********************************

function x560855_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560855_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560855_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560855_g_ScriptId, x560855_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560855_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560855_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560855_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560855_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560855_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560855_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560855_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560855_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end