--�淨���󶼸���--��������--���

x560915_g_ScriptId = 560915
x560915_g_MissionName="�����̵�"
x560915_g_ShopList={915}
--**********************************

--������ں���

--**********************************

function x560915_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560915_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560915_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

		AddQuestNumText(sceneId, x560915_g_ScriptId, x560915_g_MissionName,10)

end



--**********************************

--����������

--**********************************

function x560915_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560915_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560915_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560915_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560915_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560915_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560915_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560915_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end