--���ܣ���ף�
--NPC�����º��� ����

x211014_g_ScriptId = 211014
x211014_g_MissionName="��ף�"

--**********************************

--������ں���

--**********************************

function x211014_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y��ף�")
		AddQuestText(sceneId, "ÿ����յ��������Ҷ����кܶ����ף�����Ȼ�е�ʱ�򣬹�������һ�ã�ÿ�춼�п����ǽ��գ�����ô���Ȼ�ǡ����Ǻǣ���������˵�˰ɡ�")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end



--**********************************

--�о��¼�

--**********************************

function x211014_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211014_g_ScriptId, x211014_g_MissionName)
end



--**********************************

--����������

--**********************************

function x211014_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x211014_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--����

--**********************************

function x211014_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--����Ƿ�����ύ

--**********************************

function x211014_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--�ύ

--**********************************

function x211014_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--ɱ����������

--**********************************

function x211014_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--���������¼�

--**********************************

function x211014_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x211014_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end