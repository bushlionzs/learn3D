--���ܣ�����������ͷ��������䷽��

x560842_g_ScriptId = 560842
x560842_g_MissionName="����������ͷ��������䷽��"
x560842_g_ShopList={842}
--**********************************

--������ں���

--**********************************

function x560842_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560842_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560842_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560842_g_ScriptId, x560842_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560842_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560842_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560842_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560842_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560842_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560842_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560842_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560842_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end