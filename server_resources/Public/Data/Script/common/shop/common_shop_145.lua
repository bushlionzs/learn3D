--���ܣ���˼����̵�

x560145_g_ScriptId = 560145
x560145_g_MissionName="��˼����̵�"
x560145_g_ShopList={145}
--**********************************

--������ں���

--**********************************

function x560145_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560145_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560145_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560145_g_ScriptId, x560145_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560145_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560145_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560145_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560145_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560145_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560145_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560145_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560145_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end