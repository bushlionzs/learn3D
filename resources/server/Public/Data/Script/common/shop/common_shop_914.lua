--�淨���󶼸���--��������--���

x560914_g_ScriptId = 560914
x560914_g_MissionName="�䱦�̵�"
x560914_g_ShopList={914}
--**********************************

--������ں���

--**********************************

function x560914_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560914_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560914_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

		AddQuestNumText(sceneId, x560914_g_ScriptId, x560914_g_MissionName,10)

end



--**********************************

--����������

--**********************************

function x560914_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560914_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560914_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560914_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560914_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560914_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560914_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560914_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end