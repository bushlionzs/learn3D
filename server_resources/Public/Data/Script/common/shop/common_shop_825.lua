--���ܣ��ɹ�ѱ���������༼���䷽��

x560825_g_ScriptId = 560825
x560825_g_MissionName="�ɹ�ѱ���������༼���䷽��"
x560825_g_ShopList={825}
--**********************************

--������ں���

--**********************************

function x560825_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560825_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560825_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560825_g_ScriptId, x560825_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560825_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560825_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560825_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560825_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560825_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560825_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560825_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560825_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end