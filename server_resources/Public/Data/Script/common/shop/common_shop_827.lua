--���ܣ��ɹ�ѱ�����ظ��༼���䷽��

x560827_g_ScriptId = 560827
x560827_g_MissionName="�ɹ�ѱ�����ظ��༼���䷽��"
x560827_g_ShopList={827}
--**********************************

--������ں���

--**********************************

function x560827_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, x560827_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x560827_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560827_g_ScriptId, x560827_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--����������

--**********************************

function x560827_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x560827_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x560827_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x560827_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x560827_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x560827_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x560827_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x560827_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end