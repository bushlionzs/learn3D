--���ܣ�����ҩƷ�䷽��

x560135_g_ScriptId = 560135
x560135_g_MissionName="����ҩƷ�䷽��"
x560135_g_ShopList={135}
--**********************************

--������ں���

--**********************************

function x560135_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560135_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560135_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x560135_g_ScriptId, x560135_g_MissionName,10)
end



--**********************************

--����������

--**********************************

function x560135_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560135_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560135_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560135_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560135_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560135_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560135_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560135_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end