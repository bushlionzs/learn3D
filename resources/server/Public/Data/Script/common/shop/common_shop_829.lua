--���ܣ��ɹ�ѱ������������Ʒ�䷽��

x560829_g_ScriptId = 560829
x560829_g_MissionName="�ɹ�ѱ������������Ʒ�䷽��"
x560829_g_ShopList={829}
--**********************************

--������ں���

--**********************************

function x560829_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560829_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560829_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560829_g_ScriptId, x560829_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560829_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560829_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560829_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560829_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560829_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560829_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560829_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560829_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end