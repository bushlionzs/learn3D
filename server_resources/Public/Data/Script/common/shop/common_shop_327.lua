--���ܣ�������10-50ר��

x560327_g_ScriptId = 560327
x560327_g_MissionName="������ƥ�̵�"
x560327_g_ShopList={327}
--**********************************

--������ں���

--**********************************

function x560327_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560327_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560327_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560327_g_ScriptId, x560327_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560327_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560327_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560327_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560327_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560327_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560327_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560327_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560327_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end