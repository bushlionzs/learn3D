--���ܣ���������
--NPC�����º��� ����˹


x211011_g_ScriptId = 211011
x211011_g_MissionName="��������"

--**********************************

--������ں���

--**********************************

function x211011_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y��������")
		AddQuestText(sceneId, "�������ǵĵ��̣��͵��������ֵ����ġ�ֻҪ������Ƿ��������ģ����õ��ϵ�Ǳ������������Ͼ����г���ͷ�ص�һ�졣���������ٺ١����ٺ١����ҵĵ��أ��ѵ������ڵ�˳��ǣ���ˣ��Ҹ��Ҵ���İ������²��ˡ���")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--�о��¼�

--**********************************

function x211011_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211011_g_ScriptId, x211011_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211011_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211011_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211011_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211011_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211011_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211011_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211011_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211011_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end