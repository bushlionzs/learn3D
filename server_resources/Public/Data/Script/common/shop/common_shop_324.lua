--���ܣ������ʦ�䷽�̵�

x560324_g_ScriptId = 560324
x560324_g_MissionName="�����ʦ�䷽�̵�"
x560324_g_ShopList={324}
--**********************************

--������ں���

--**********************************

function x560324_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560324_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560324_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560324_g_ScriptId, x560324_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560324_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560324_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560324_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560324_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560324_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560324_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560324_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560324_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end