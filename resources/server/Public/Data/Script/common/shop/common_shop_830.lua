--���ܣ�ͻ�ʶ����������������䷽��

x560830_g_ScriptId = 560830
x560830_g_MissionName="ͻ�ʶ������������䷽��"
x560830_g_ShopList={830}
--**********************************

--������ں���

--**********************************

function x560830_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560830_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560830_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560830_g_ScriptId, x560830_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560830_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560830_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560830_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560830_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560830_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560830_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560830_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560830_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end