--�淨���󶼸���--��������--���

x560913_g_ScriptId = 560913
x560913_g_MissionName="���Ĳ�ׯ"
x560913_g_ShopList={913}
--**********************************

--������ں���

--**********************************

function x560913_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560913_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560913_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

		AddQuestNumText(sceneId, x560913_g_ScriptId, x560913_g_MissionName,10)

end



--**********************************

--����������

--**********************************

function x560913_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560913_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560913_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560913_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560913_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560913_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560913_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560913_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end