--���ܣ��ɹ�ѱ������ͨ�༼���䷽��

x560823_g_ScriptId = 560823
x560823_g_MissionName="�ɹ�ѱ������ͨ�༼���䷽��"
x560823_g_ShopList={823}
--**********************************

--������ں���

--**********************************

function x560823_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560823_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560823_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560823_g_ScriptId, x560823_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560823_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560823_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560823_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560823_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560823_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560823_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560823_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560823_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end