--���ܣ�ӡ���鱦����������Ʒ�䷽��

x560815_g_ScriptId = 560815
x560815_g_MissionName="ӡ���鱦����������Ʒ�䷽��"
x560815_g_ShopList={815}
--**********************************

--������ں���

--**********************************

function x560815_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560815_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560815_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560815_g_ScriptId, x560815_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560815_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560815_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560815_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560815_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560815_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560815_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560815_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560815_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end