--���ܣ���ԭ��ҩ���ָ���ҩˮ�䷽��

x560800_g_ScriptId = 560800
x560800_g_MissionName="��ԭ��ҩ���ָ���ҩˮ�䷽��"
x560800_g_ShopList={800}
--**********************************

--������ں���

--**********************************

function x560800_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560800_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560800_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560800_g_ScriptId, x560800_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560800_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560800_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560800_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560800_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560800_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560800_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560800_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560800_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end