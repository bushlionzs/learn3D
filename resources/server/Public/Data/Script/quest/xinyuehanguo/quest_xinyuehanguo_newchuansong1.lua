--���ܣ����ִ崫��
--NPC������

x211064_g_ScriptId = 211064
x211064_g_MissionName="�����̵��"
--**********************************

--������ں���

--**********************************

function x211064_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, 15 )
	--if GetLevel( sceneId, selfId ) >= 10 then
	--	SetPos(sceneId, selfId,108,258)
	--	BeginQuestEvent(sceneId)
	--		strText = "�������˺������Ĺ㳡"
	--		AddQuestText(sceneId,strText);
	--	EndQuestEvent(sceneId)
	--	DispatchQuestTips(sceneId,selfId)
	--else
	--	BeginQuestEvent(sceneId)
	--		AddQuestText(sceneId, "#Y�������Ĺ㳡")
	--		AddQuestText(sceneId, "ֻ�д�����õ�����Ͽɵ�Ӣ�ۣ��ҲŻ����˽�������͵��������Ĺ㳡������10����ʱ�򣬾ͻ�õ���ҵ��Ͽɣ���Ϊ�����Ӣ�ۣ�")
	--	EndQuestEvent(sceneId)
	--	DispatchQuestEventList(sceneId,selfId,targetId)
	--end
end



--**********************************

--�о��¼�

--**********************************

function x211064_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x211064_g_ScriptId, x211064_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211064_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211064_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211064_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211064_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211064_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211064_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211064_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211064_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end