--���ܣ����������䷽

x560319_g_ScriptId = 560319
x560319_g_MissionName="�������＼��"
x560319_g_ShopList={319}
--**********************************

--������ں���

--**********************************

function x560319_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560319_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560319_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 80 then
		AddQuestNumText(sceneId, x560319_g_ScriptId, x560319_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560319_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560319_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560319_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560319_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560319_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560319_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560319_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560319_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end