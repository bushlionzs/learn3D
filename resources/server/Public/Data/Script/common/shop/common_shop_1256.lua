--���ܣ���ʯҩ������̵�

x561256_g_ScriptId = 561256
x561256_g_MissionName="��ʯҩ������̵�"
x561256_g_ShopList={1256}
--**********************************

--������ں���

--**********************************

function x561256_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x561256_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x561256_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 60 then
		AddQuestNumText(sceneId, x561256_g_ScriptId, x561256_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x561256_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x561256_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x561256_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x561256_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x561256_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x561256_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x561256_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x561256_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end