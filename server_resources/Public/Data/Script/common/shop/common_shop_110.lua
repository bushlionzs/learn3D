--���ܣ���Ʒ�̵�

x560110_g_ScriptId = 560110
x560110_g_MissionName="����ҩƷ"
x560110_g_ShopList={110}
--**********************************

--������ں���

--**********************************

function x560110_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560110_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560110_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560110_g_ScriptId, x560110_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560110_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560110_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560110_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560110_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560110_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560110_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560110_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560110_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end