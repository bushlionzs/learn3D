--���ܣ����״�ʦ�䷽�̵�

x560325_g_ScriptId = 560325
x560325_g_MissionName="���״�ʦ�䷽�̵�"
x560325_g_ShopList={325}
--**********************************

--������ں���

--**********************************

function x560325_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560325_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560325_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560325_g_ScriptId, x560325_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560325_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560325_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560325_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560325_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560325_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560325_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560325_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560325_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end