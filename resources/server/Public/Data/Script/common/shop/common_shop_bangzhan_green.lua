--���ܣ���Ʒ�̵�  B

x560401_g_ScriptId = 560401
x560401_g_MissionName="ҩƷ��"
x560401_g_ShopList={101}
--**********************************

--������ں���

--**********************************

function x560401_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560401_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560401_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	local camp = GetCurCamp(sceneId,selfId)
	

	if camp == 6 then
        
		AddQuestNumText(sceneId, x560401_g_ScriptId, x560401_g_MissionName,10)
	else 	
		return
	end

end



--**********************************

--����������

--**********************************

function x560401_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560401_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560401_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560401_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560401_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560401_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560401_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560401_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end