--���ܣ���������������������䷽��

x560839_g_ScriptId = 560839
x560839_g_MissionName="��������������������䷽��"
x560839_g_ShopList={839}
--**********************************

--������ں���

--**********************************

function x560839_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560839_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560839_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560839_g_ScriptId, x560839_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560839_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560839_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560839_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560839_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560839_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560839_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560839_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560839_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end