--���ܣ���ֵ����̵�

x561254_g_ScriptId = 561254
x561254_g_MissionName="��ֵ����̵�"
x561254_g_ShopList={1254}
--**********************************

--������ں���

--**********************************

function x561254_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x561254_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x561254_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 60 then
		AddQuestNumText(sceneId, x561254_g_ScriptId, x561254_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x561254_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x561254_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x561254_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x561254_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x561254_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x561254_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x561254_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x561254_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end