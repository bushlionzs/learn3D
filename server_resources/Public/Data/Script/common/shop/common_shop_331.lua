--���ܣ������

x560331_g_ScriptId = 560331
x560331_g_MissionName="���ӡ�䷽�̵�"
x560331_g_ShopList={331}
--**********************************

--������ں���

--**********************************

function x560331_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	
	if GetTopListInfo_MinLevel( GetWorldID( sceneId, selfId) ) < 80 then
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ���ȼ����а����һ�����δ��80�������̵���δ����",8,3)
    return
  end

	DispatchShopItem( sceneId, selfId, targetId, x560331_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560331_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560331_g_ScriptId, x560331_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560331_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560331_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560331_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560331_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560331_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560331_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560331_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560331_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end