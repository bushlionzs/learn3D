--���ܣ��ɹ�ѱ���������༼���䷽��

x560817_g_ScriptId = 560817
x560817_g_MissionName="�ɹ�ѱ���������༼���䷽��"
x560817_g_ShopList={817}
--**********************************

--������ں���

--**********************************

function x560817_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560817_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560817_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560817_g_ScriptId, x560817_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560817_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560817_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560817_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560817_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560817_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560817_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560817_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560817_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end