--���ܣ�ҩ��
--NPC��ҩ���ϰ�

x211024_g_ScriptId = 211024
x211024_g_MissionName="ҩƷ�̵�"
x211024_g_ShopList={101}
--**********************************

--������ں���

--**********************************

function x211024_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x211024_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x211024_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211024_g_ScriptId, x211024_g_MissionName, 10)
end



--**********************************

--����������

--**********************************

function x211024_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211024_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211024_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211024_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211024_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211024_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211024_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211024_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end