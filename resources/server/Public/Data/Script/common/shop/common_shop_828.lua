--���ܣ��ɹ�ѱ������ħ�༼���䷽��

x560828_g_ScriptId = 560828
x560828_g_MissionName="�ɹ�ѱ������ħ�༼���䷽��"
x560828_g_ShopList={828}
--**********************************

--������ں���

--**********************************

function x560828_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560828_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560828_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560828_g_ScriptId, x560828_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560828_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560828_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560828_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560828_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560828_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560828_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560828_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560828_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end