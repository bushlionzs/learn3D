--���ܣ��������ӡ��

x560202_g_ScriptId = 560202
x560202_g_MissionName="�������ӡ��"
x560202_g_ShopList={202}
--**********************************

--������ں���

--**********************************

function x560202_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560202_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560202_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 40 then
		AddQuestNumText(sceneId, x560202_g_ScriptId, x560202_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560202_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560202_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560202_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560202_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560202_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560202_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560202_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560202_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end