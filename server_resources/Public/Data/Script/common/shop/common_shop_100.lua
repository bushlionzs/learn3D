--���ܣ���Ʒ�̵�

x560100_g_ScriptId = 560100
x560100_g_MissionName="����������"
x560100_g_ShopList={100}
--**********************************

--������ں���

--**********************************

function x560100_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560100_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560100_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560100_g_ScriptId, x560100_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560100_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560100_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560100_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560100_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560100_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560100_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560100_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560100_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end