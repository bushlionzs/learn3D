--���ܣ���ҩ��ʦ�䷽�̵�

x560321_g_ScriptId = 560321
x560321_g_MissionName="��ҩ��ʦ�䷽�̵�"
x560321_g_ShopList={321}
--**********************************

--������ں���

--**********************************

function x560321_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560321_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560321_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560321_g_ScriptId, x560321_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560321_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560321_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560321_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560321_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560321_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560321_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560321_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560321_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end