--���ܣ��ɹ�ѱ������ͨ�༼���䷽��

x560816_g_ScriptId = 560816
x560816_g_MissionName="�ɹ�ѱ������ͨ�༼���䷽��"
x560816_g_ShopList={816}
--**********************************

--������ں���

--**********************************

function x560816_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560816_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560816_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560816_g_ScriptId, x560816_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560816_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560816_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560816_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560816_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560816_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560816_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560816_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560816_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end