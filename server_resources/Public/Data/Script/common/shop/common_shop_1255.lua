--���ܣ��ʼ���������̵�

x561255_g_ScriptId = 561255
x561255_g_MissionName="�ʼ���������̵�"
x561255_g_ShopList={1255}
--**********************************

--������ں���

--**********************************

function x561255_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x561255_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x561255_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 30 then
		AddQuestNumText(sceneId, x561255_g_ScriptId, x561255_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x561255_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x561255_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x561255_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x561255_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x561255_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x561255_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x561255_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x561255_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end