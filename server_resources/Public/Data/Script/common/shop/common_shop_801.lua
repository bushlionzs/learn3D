--���ܣ���ԭ��ҩ����ǿ��ҩˮ�䷽��

x560801_g_ScriptId = 560801
x560801_g_MissionName="��ԭ��ҩ����ǿ��ҩˮ�䷽��"
x560801_g_ShopList={801}
--**********************************

--������ں���

--**********************************

function x560801_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560801_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560801_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560801_g_ScriptId, x560801_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560801_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560801_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560801_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560801_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560801_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560801_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560801_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560801_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end