--���ܣ�4���ﹱ�̵�

x560158_g_ScriptId = 560158
x560158_g_MissionName="�ļ��ﹱ�̵�"
x560158_g_ShopList={158}
--**********************************

--������ں���

--**********************************

function x560158_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560158_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560158_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560158_g_ScriptId, x560158_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560158_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560158_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560158_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560158_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560158_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560158_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560158_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560158_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end