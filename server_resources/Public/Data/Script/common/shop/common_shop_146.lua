--���ܣ���˵����̵�

x560146_g_ScriptId = 560146
x560146_g_MissionName="��˵����̵�"
x560146_g_ShopList={146}
--**********************************

--������ں���

--**********************************

function x560146_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560146_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560146_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560146_g_ScriptId, x560146_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560146_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560146_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560146_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560146_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560146_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560146_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560146_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560146_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end