--���ܣ���ԭ��ҩ����������Ʒ�䷽��

x560805_g_ScriptId = 560805
x560805_g_MissionName="��ԭ��ҩ����������Ʒ�䷽��"
x560805_g_ShopList={805}
--**********************************

--������ں���

--**********************************

function x560805_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560805_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560805_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560805_g_ScriptId, x560805_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560805_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560805_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560805_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560805_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560805_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560805_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560805_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560805_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end