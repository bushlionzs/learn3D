--���ܣ���ԭ��ҩ����ǿ��ҩˮ�䷽��

x560804_g_ScriptId = 560804
x560804_g_MissionName="��ԭ��ҩ����ǿ��ҩˮ�䷽��"
x560804_g_ShopList={804}
--**********************************

--������ں���

--**********************************

function x560804_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560804_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560804_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560804_g_ScriptId, x560804_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560804_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560804_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560804_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560804_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560804_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560804_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560804_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560804_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end