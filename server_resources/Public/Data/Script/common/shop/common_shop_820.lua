--���ܣ��ɹ�ѱ�����ظ��༼���䷽��

x560820_g_ScriptId = 560820
x560820_g_MissionName="�ɹ�ѱ�����ظ��༼���䷽��"
x560820_g_ShopList={820}
--**********************************

--������ں���

--**********************************

function x560820_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560820_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560820_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560820_g_ScriptId, x560820_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560820_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560820_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560820_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560820_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560820_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560820_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560820_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560820_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end