--���ܣ��ɹ�ѱ���������༼���䷽��

x560818_g_ScriptId = 560818
x560818_g_MissionName="�ɹ�ѱ���������༼���䷽��"
x560818_g_ShopList={818}
--**********************************

--������ں���

--**********************************

function x560818_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560818_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560818_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560818_g_ScriptId, x560818_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560818_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560818_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560818_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560818_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560818_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560818_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560818_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560818_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end