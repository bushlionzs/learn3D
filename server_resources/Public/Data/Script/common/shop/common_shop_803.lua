--���ܣ���ԭ��ҩ���ָ���ҩˮ�䷽��

x560803_g_ScriptId = 560803
x560803_g_MissionName="��ԭ��ҩ���ָ���ҩˮ�䷽��"
x560803_g_ShopList={803}
--**********************************

--������ں���

--**********************************

function x560803_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560803_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560803_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560803_g_ScriptId, x560803_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560803_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560803_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560803_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560803_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560803_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560803_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560803_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560803_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end