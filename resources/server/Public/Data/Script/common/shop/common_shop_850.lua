--���ܣ���˹��������������Ʒ�䷽��

x560850_g_ScriptId = 560850
x560850_g_MissionName="��˹��������������Ʒ�䷽��"
x560850_g_ShopList={850}
--**********************************

--������ں���

--**********************************

function x560850_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560850_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560850_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560850_g_ScriptId, x560850_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560850_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560850_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560850_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560850_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560850_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560850_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560850_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560850_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end