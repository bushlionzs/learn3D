--���ܣ���Ʒ�̵�

x560132_g_ScriptId = 560132
x560132_g_MissionName="ҩƷ�����䷽�̵�"
x560132_g_ShopList={132}
--**********************************

--������ں���

--**********************************

function x560132_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560132_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560132_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560132_g_ScriptId, x560132_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560132_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560132_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560132_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560132_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560132_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560132_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560132_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560132_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end