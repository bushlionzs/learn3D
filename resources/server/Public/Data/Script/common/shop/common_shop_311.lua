--���ܣ��������̵꣺4��������

x560311_g_ScriptId = 560311
x560311_g_MissionName="�ļ����＼��"
x560311_g_ShopList={311}
--**********************************

--������ں���

--**********************************

function x560311_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560311_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560311_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 60 then
		AddQuestNumText(sceneId, x560311_g_ScriptId, x560311_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560311_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560311_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560311_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560311_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560311_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560311_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560311_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560311_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end