--���ܣ��������̵꣺3��������

x560310_g_ScriptId = 560310
x560310_g_MissionName="�������＼��"
x560310_g_ShopList={310}
--**********************************

--������ں���

--**********************************

function x560310_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560310_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560310_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 50 then
		AddQuestNumText(sceneId, x560310_g_ScriptId, x560310_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560310_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560310_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560310_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560310_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560310_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560310_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560310_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560310_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end