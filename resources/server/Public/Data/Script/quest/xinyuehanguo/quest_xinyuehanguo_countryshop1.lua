--���ܣ����ҷ�չ�̵�
--NPC����˾��

--MisDescBegin
x211036_g_ScriptId = 211036

x211036_g_MissionName = "���ҷ�չ�̵�"
x211036_g_ShopList = {1}
--MisDescEnd
--**********************************

--������ں���

--**********************************

function x211036_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y���ҷ�չ�̵�")
		AddQuestText(sceneId, "Ϊ�˹�����Ҷ�Ϊ���������ף���������ȥ�ɹ��˺ܶ�ö����Խ������Թ��й�֮�ˡ�������Ʒ��û�вɹ��꣬һ�����⿪���һἰʱ֪ͨ���ǰ�����������䣡�����㻹����ȥ�����Щ���Ͳ��ǣ�\n������ֻ������#G���ҽ���#W���й�֮�ˡ��Թ����й�����Ӧ��ȥ�Ҷ�����о�������")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	--DispatchShopItem( sceneId, selfId, targetId, x211036_g_ShopList[1] )
end



--**********************************

--�о��¼�

--**********************************

function x211036_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x211036_g_ScriptId, x211036_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211036_ProcAcceptCheck(sceneId, selfId, targetId)

end



--**********************************

--����

--**********************************

function x211036_ProcAccept(sceneId, selfId)
    
end



--**********************************

--����

--**********************************

function x211036_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211036_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211036_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211036_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211036_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211036_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end