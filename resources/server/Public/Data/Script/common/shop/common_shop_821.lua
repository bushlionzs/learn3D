--���ܣ��ɹ�ѱ������ħ�༼���䷽��

x560821_g_ScriptId = 560821
x560821_g_MissionName="�ɹ�ѱ������ħ�༼���䷽��"
x560821_g_ShopList={821}
--**********************************

--������ں���

--**********************************

function x560821_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560821_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560821_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560821_g_ScriptId, x560821_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560821_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560821_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560821_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560821_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560821_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560821_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560821_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560821_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end