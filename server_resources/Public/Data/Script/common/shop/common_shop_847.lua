--���ܣ�������������������Ʒ�䷽��

x560847_g_ScriptId = 560847
x560847_g_MissionName="������������������Ʒ�䷽��"
x560847_g_ShopList={847}
--**********************************

--������ں���

--**********************************

function x560847_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560847_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560847_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560847_g_ScriptId, x560847_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560847_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560847_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560847_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560847_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560847_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560847_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560847_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560847_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end