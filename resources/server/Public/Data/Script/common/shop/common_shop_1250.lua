--���ܣ���ʯ�����̵�

x561250_g_ScriptId = 561250
x561250_g_MissionName="��ʯ�����̵�"
x561250_g_ShopList={1250}
--**********************************

--������ں���

--**********************************

function x561250_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x561250_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x561250_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 65 then
		AddQuestNumText(sceneId, x561250_g_ScriptId, x561250_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x561250_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x561250_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x561250_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x561250_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x561250_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x561250_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x561250_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x561250_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end