--���ܣ��������̵꣺5��������

x560312_g_ScriptId = 560312
x560312_g_MissionName="�弶���＼��"
x560312_g_ShopList={312}
--**********************************

--������ں���

--**********************************

function x560312_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560312_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560312_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 60 then
		AddQuestNumText(sceneId, x560312_g_ScriptId, x560312_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560312_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560312_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560312_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560312_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560312_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560312_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560312_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560312_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end