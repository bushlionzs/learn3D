--���ܣ��ɹ�ѱ���䷽��

x560114_g_ScriptId = 560114
x560114_g_MissionName="�ɹ�ѱ���䷽��"
x560114_g_ShopList={114}
--**********************************

--������ں���

--**********************************

function x560114_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560114_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560114_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560114_g_ScriptId, x560114_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560114_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560114_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560114_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560114_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560114_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560114_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560114_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560114_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end