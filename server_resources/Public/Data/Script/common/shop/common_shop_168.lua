--���ܣ�6���ﹱ�̵�

x560168_g_ScriptId = 560168
x560168_g_MissionName="�߼��ﹱ�̵�"
x560168_g_ShopList={168}
--**********************************

--������ں���

--**********************************

function x560168_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560168_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560168_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560168_g_ScriptId, x560168_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560168_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560168_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560168_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560168_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560168_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560168_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560168_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560168_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end