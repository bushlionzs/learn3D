--���ܣ���ҫ֤֮�̵�

x560203_g_ScriptId = 560203
x560203_g_MissionName="��ҫ֤֮�̵�"
x560203_g_ShopList={203}
--**********************************

--������ں���

--**********************************

function x560203_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560203_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560203_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 1 then
		AddQuestNumText(sceneId, x560203_g_ScriptId, x560203_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560203_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560203_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560203_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560203_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560203_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560203_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560203_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560203_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end