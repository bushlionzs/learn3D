--���ܣ�����������ѥ��������䷽��

x560840_g_ScriptId = 560840
x560840_g_MissionName="����������ѥ��������䷽��"
x560840_g_ShopList={840}
--**********************************

--������ں���

--**********************************

function x560840_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560840_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560840_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560840_g_ScriptId, x560840_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560840_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560840_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560840_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560840_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560840_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560840_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560840_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560840_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end