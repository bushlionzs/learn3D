--���ܣ��ɹ�ѱ���������༼���䷽��

x560819_g_ScriptId = 560819
x560819_g_MissionName="�ɹ�ѱ���������༼���䷽��"
x560819_g_ShopList={819}
--**********************************

--������ں���

--**********************************

function x560819_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560819_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560819_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560819_g_ScriptId, x560819_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560819_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560819_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560819_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560819_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560819_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560819_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560819_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560819_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end