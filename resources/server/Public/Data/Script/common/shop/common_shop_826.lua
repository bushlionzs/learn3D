--���ܣ��ɹ�ѱ���������༼���䷽��

x560826_g_ScriptId = 560826
x560826_g_MissionName="�ɹ�ѱ���������༼���䷽��"
x560826_g_ShopList={826}
--**********************************

--������ں���

--**********************************

function x560826_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560826_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560826_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560826_g_ScriptId, x560826_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560826_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560826_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560826_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560826_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560826_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560826_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560826_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560826_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end