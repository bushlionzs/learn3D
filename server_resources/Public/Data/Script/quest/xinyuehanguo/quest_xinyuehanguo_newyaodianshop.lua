--���ܣ����ִ�ҩ��
--NPC�����ִ�ҩ��ҽ��

x211041_g_ScriptId = 211041
x211041_g_MissionName="ҩƷ�̵�"
x211041_g_ShopList={16}
--**********************************

--������ں���

--**********************************

function x211041_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x211041_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x211041_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211041_g_ScriptId, x211041_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211041_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211041_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211041_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211041_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211041_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211041_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211041_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211041_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end