--���ܣ�ӡ���鱦����������Ʒ�䷽��

x560810_g_ScriptId = 560810
x560810_g_MissionName="ӡ���鱦����������Ʒ�䷽��"
x560810_g_ShopList={810}
--**********************************

--������ں���

--**********************************

function x560810_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560810_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560810_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560810_g_ScriptId, x560810_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560810_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560810_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560810_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560810_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560810_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560810_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560810_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560810_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end