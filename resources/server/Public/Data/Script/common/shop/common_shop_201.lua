--���ܣ�תְ���߽���̵�

x560201_g_ScriptId = 560201
x560201_g_MissionName="תְ���߽���̵�"
x560201_g_ShopList={201}
--**********************************

--������ں���

--**********************************

function x560201_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560201_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560201_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 70 then
		AddQuestNumText(sceneId, x560201_g_ScriptId, x560201_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560201_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560201_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560201_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560201_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560201_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560201_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560201_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560201_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end