--���ܣ����ҹ����̵�
--NPC���о�����

--MisDescBegin
x211037_g_ScriptId = 211037

x211037_g_MissionName = "���ҹ����̵�"
x211037_g_ShopList = {1}
--MisDescEnd
--**********************************

--������ں���

--**********************************

function x211037_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y���ҹ����̵�")
		AddQuestText(sceneId, "����������ƥ�����𡣷��ǶԹ�����ҵ�й�֮�ˣ����Ҷ����������ǵġ���������һƥ���ʣ�������������·�ϣ�һ�����ǣ��Ҿ�֪ͨ���ǰ����ȡ��\n������ֻ������#G������ҵ#W���й�֮�ˡ��Թ��ҷ�չ�����й�����Ӧ��ȥ�Ҷ���Ĵ�˾��")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	--DispatchShopItem( sceneId, selfId, targetId, x211037_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x211037_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x211037_g_ScriptId, x211037_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211037_ProcAcceptCheck(sceneId, selfId, targetId)

end



--**********************************

--����

--**********************************

function x211037_ProcAccept(sceneId, selfId)
    
end



--**********************************

--����

--**********************************

function x211037_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211037_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211037_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211037_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211037_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211037_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end