--�淨���󶼸���--��������--���

x560917_g_ScriptId = 560917
x560917_g_MissionName="�����������̵�"
x560917_g_ShopList={917}
--**********************************

--������ں���

--**********************************

function x560917_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560917_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560917_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

		AddQuestNumText(sceneId, x560917_g_ScriptId, x560917_g_MissionName,10)

end



--**********************************

--����������

--**********************************

function x560917_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560917_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560917_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560917_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560917_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560917_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560917_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560917_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end