--�淨���󶼸���--��������--ˮ����

x560912_g_ScriptId = 560912
x560912_g_MissionName="ʩ��ˮ��"
x560912_g_ShopList={912}
--**********************************

--������ں���

--**********************************

function x560912_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560912_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560912_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

		AddQuestNumText(sceneId, x560912_g_ScriptId, x560912_g_MissionName,10)

end



--**********************************

--����������

--**********************************

function x560912_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560912_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560912_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560912_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560912_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560912_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560912_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560912_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end