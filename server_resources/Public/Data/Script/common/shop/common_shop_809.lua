--���ܣ�ӡ���鱦���̱�ʯ�౦ʯ�䷽��

x560809_g_ScriptId = 560809
x560809_g_MissionName="ӡ���鱦���̱�ʯ�౦ʯ�䷽��"
x560809_g_ShopList={809}
--**********************************

--������ں���

--**********************************

function x560809_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560809_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560809_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560809_g_ScriptId, x560809_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560809_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560809_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560809_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560809_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560809_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560809_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560809_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560809_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end