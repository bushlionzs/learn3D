--���ܣ�ҹ�������̵�

x561252_g_ScriptId = 561252
x561252_g_MissionName="ҹ�������̵�"
x561252_g_ShopList={1252}
--**********************************

--������ں���

--**********************************

function x561252_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x561252_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x561252_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 80 then
		AddQuestNumText(sceneId, x561252_g_ScriptId, x561252_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x561252_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x561252_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x561252_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x561252_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x561252_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x561252_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x561252_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x561252_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end