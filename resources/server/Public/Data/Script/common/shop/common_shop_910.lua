--�淨���󶼸���--��������--�����׵�

x560910_g_ScriptId = 560910
x560910_g_MissionName="��������"
x560910_g_ShopList={910}
--**********************************

--������ں���

--**********************************

function x560910_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560910_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560910_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

		AddQuestNumText(sceneId, x560910_g_ScriptId, x560910_g_MissionName,10)

end



--**********************************

--����������

--**********************************

function x560910_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560910_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560910_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560910_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560910_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560910_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560910_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560910_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end