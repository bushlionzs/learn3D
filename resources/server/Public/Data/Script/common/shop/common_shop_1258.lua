--���ܣ���˵��߽���̵�

x561258_g_ScriptId = 561258
x561258_g_MissionName="��˵��߽���̵�"
x561258_g_ShopList={1258}
--**********************************

--������ں���

--**********************************

function x561258_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x561258_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x561258_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 40 then
		AddQuestNumText(sceneId, x561258_g_ScriptId, x561258_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x561258_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x561258_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x561258_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x561258_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x561258_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x561258_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x561258_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x561258_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end