--���ܣ��ɹ�ѱ���������༼���䷽��

x560824_g_ScriptId = 560824
x560824_g_MissionName="�ɹ�ѱ���������༼���䷽��"
x560824_g_ShopList={824}
--**********************************

--������ں���

--**********************************

function x560824_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560824_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560824_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560824_g_ScriptId, x560824_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560824_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560824_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560824_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560824_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560824_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560824_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560824_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560824_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end