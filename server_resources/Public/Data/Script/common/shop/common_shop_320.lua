--���ܣ����������䷽

x560320_g_ScriptId = 560320
x560320_g_MissionName="װ��������ϵ�"
x560320_g_ShopList={320}
--**********************************

--������ں���

--**********************************

function x560320_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560320_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560320_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560320_g_ScriptId, x560320_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560320_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560320_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560320_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560320_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560320_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560320_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560320_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560320_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end