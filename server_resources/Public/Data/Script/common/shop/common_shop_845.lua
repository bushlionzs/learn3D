--���ܣ���������������������䷽��

x560845_g_ScriptId = 560845
x560845_g_MissionName="��������������������䷽��"
x560845_g_ShopList={845}
--**********************************

--������ں���

--**********************************

function x560845_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560845_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560845_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560845_g_ScriptId, x560845_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560845_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560845_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560845_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560845_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560845_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560845_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560845_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560845_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end