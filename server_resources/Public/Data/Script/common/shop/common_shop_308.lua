--���ܣ��������̵꣺2��������

x560308_g_ScriptId = 560308
x560308_g_MissionName="�������＼��"
x560308_g_ShopList={308}
--**********************************

--������ں���

--**********************************

function x560308_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560308_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560308_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	
	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 30 then
		AddQuestNumText(sceneId, x560308_g_ScriptId, x560308_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560308_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560308_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560308_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560308_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560308_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560308_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560308_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560308_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end