--���ܣ�������������������Ʒ�䷽��

x560841_g_ScriptId = 560841
x560841_g_MissionName="������������������Ʒ�䷽��"
x560841_g_ShopList={841}
--**********************************

--������ں���

--**********************************

function x560841_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560841_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560841_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560841_g_ScriptId, x560841_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560841_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560841_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560841_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560841_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560841_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560841_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560841_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560841_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end