--���ܣ���˹��������������Ʒ�䷽��

x560853_g_ScriptId = 560853
x560853_g_MissionName="��˹��������������Ʒ�䷽��"
x560853_g_ShopList={853}
--**********************************

--������ں���

--**********************************

function x560853_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560853_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560853_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560853_g_ScriptId, x560853_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560853_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560853_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560853_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560853_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560853_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560853_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560853_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560853_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end