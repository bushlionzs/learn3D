--���ܣ����ε�
--NPC�����ε��ϰ�

x211021_g_ScriptId = 211021
x211021_g_MissionName="�����̵�"
x211021_g_ShopList={5}
--**********************************

--������ں���

--**********************************

function x211021_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x211021_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x211021_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211021_g_ScriptId, x211021_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211021_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211021_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211021_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211021_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211021_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211021_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211021_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211021_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end