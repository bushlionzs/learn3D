--���ܣ����ִ崫��
--NPC������

x211040_g_ScriptId = 211040
x211040_g_MissionName="�����̵�"
--**********************************

--������ں���

--**********************************

function x211040_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	DispatchShopItem( sceneId, selfId, targetId, 14 )
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

function x211040_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x211040_g_ScriptId, x211040_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211040_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211040_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211040_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211040_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211040_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211040_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211040_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211040_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end