--���ܣ������������·�������䷽��

x560843_g_ScriptId = 560843
x560843_g_MissionName="�����������·�������䷽��"
x560843_g_ShopList={843}
--**********************************

--������ں���

--**********************************

function x560843_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560843_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560843_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560843_g_ScriptId, x560843_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560843_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560843_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560843_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560843_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560843_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560843_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560843_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560843_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end