--���ܣ���������������������䷽��

x560844_g_ScriptId = 560844
x560844_g_MissionName="��������������������䷽��"
x560844_g_ShopList={844}
--**********************************

--������ں���

--**********************************

function x560844_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560844_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560844_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560844_g_ScriptId, x560844_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560844_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560844_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560844_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560844_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560844_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560844_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560844_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560844_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end