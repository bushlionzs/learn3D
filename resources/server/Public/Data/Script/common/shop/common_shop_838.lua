--���ܣ���������������������䷽��

x560838_g_ScriptId = 560838
x560838_g_MissionName="��������������������䷽��"
x560838_g_ShopList={838}
--**********************************

--������ں���

--**********************************

function x560838_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560838_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560838_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560838_g_ScriptId, x560838_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560838_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560838_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560838_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560838_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560838_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560838_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560838_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560838_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end