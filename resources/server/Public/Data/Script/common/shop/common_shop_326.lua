--���ܣ����մ�ʦ�䷽�̵�

x560326_g_ScriptId = 560326
x560326_g_MissionName="���մ�ʦ�䷽�̵�"
x560326_g_ShopList={326}
--**********************************

--������ں���

--**********************************

function x560326_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560326_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560326_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560326_g_ScriptId, x560326_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560326_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560326_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560326_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560326_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560326_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560326_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560326_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560326_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end