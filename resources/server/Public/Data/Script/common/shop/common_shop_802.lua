--���ܣ���ԭ��ҩ����������Ʒ�䷽��

x560802_g_ScriptId = 560802
x560802_g_MissionName="��ԭ��ҩ����������Ʒ�䷽��"
x560802_g_ShopList={802}
--**********************************

--������ں���

--**********************************

function x560802_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560802_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560802_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560802_g_ScriptId, x560802_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560802_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560802_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560802_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560802_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560802_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560802_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560802_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560802_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end