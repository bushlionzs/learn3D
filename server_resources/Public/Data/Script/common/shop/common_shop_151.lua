--���ܣ����������䷽��

x560151_g_ScriptId = 560151
x560151_g_MissionName="���������䷽��"
x560151_g_ShopList={151}
--**********************************

--������ں���

--**********************************

function x560151_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560151_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560151_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	
                AddQuestNumText(sceneId, x560151_g_ScriptId, x560151_g_MissionName,10)

--	local nLevel = GetLevel(sceneId,selfId)
--	if nLevel >= 60 then
--		AddQuestNumText(sceneId, x560151_g_ScriptId, x560151_g_MissionName,10)
--	else
--		return
--	end
	
end



--**********************************

--����������

--**********************************

function x560151_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560151_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560151_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560151_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560151_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560151_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560151_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560151_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end