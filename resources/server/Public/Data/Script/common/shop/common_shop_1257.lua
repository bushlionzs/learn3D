--���ܣ���ʯͼ�׽���̵�

x561257_g_ScriptId = 561257
x561257_g_MissionName="��ʯͼ�׽���̵�"
x561257_g_ShopList={1257}
--**********************************

--������ں���

--**********************************

function x561257_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x561257_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x561257_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 50 then
		AddQuestNumText(sceneId, x561257_g_ScriptId, x561257_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x561257_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x561257_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x561257_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x561257_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x561257_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x561257_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x561257_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x561257_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end