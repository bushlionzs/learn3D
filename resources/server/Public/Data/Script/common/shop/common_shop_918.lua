--�淨���󶼸���--��������--���

x560918_g_ScriptId = 560918
x560918_g_MissionName="�ļ��������̵�"
x560918_g_ShopList={918}
--**********************************

--������ں���

--**********************************

function x560918_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560918_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560918_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

		AddQuestNumText(sceneId, x560918_g_ScriptId, x560918_g_MissionName,10)

end



--**********************************

--����������

--**********************************

function x560918_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560918_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560918_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560918_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560918_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560918_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560918_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560918_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end