--���ܣ������������̵�

x561259_g_ScriptId = 561259
x561259_g_MissionName="�����������̵�"
x561259_g_ShopList={1259}
--**********************************

--������ں���

--**********************************

function x561259_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x561259_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x561259_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 85 then
		AddQuestNumText(sceneId, x561259_g_ScriptId, x561259_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x561259_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x561259_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x561259_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x561259_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x561259_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x561259_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x561259_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x561259_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end