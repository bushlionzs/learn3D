--���ܣ������������·�������䷽��

x560837_g_ScriptId = 560837
x560837_g_MissionName="�����������·�������䷽��"
x560837_g_ShopList={837}
--**********************************

--������ں���

--**********************************

function x560837_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560837_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560837_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560837_g_ScriptId, x560837_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560837_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560837_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560837_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560837_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560837_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560837_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560837_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560837_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end