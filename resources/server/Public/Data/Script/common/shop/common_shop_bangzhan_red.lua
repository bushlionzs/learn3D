--���ܣ���Ʒ�̵�  A

x560400_g_ScriptId = 560400
x560400_g_MissionName="ҩƷ��"
x560400_g_ShopList={101}
--**********************************

--������ں���

--**********************************

function x560400_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560400_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560400_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	local camp = GetCurCamp(sceneId,selfId)
	
	if camp == 5 then
		AddQuestNumText(sceneId, x560400_g_ScriptId, x560400_g_MissionName,10)
	else 	
		return
	end


end



--**********************************

--����������

--**********************************

function x560400_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560400_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560400_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560400_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560400_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560400_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560400_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560400_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end