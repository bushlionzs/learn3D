x310075_g_ScriptId = 310075

x310075_g_MissionName = "�����η��ɹ�˵����"
x310075_g_MissionComment = "\t��͢ÿ��һ��ʱ�����ί��Ұ·�����η��ɹ�һЩ�����Ļ������ƽ�����·�æ����֪���ð���˭�����������鰡��\n\t��ʵֻ��Ҫǣ����ƥӵ�г�͢��ӡ���������������ȡ���������η�˵��ԭί��������ת����������վ�ͺã���ȴ���Ҳ�����Ը���æ���ѵ���͢���ò������ڵ����������ǻ����Ӧ�ı���ġ�\n\tע�������#Gÿ��16��30~17��30#W���ţ�#G�ȼ���40������#W����ҿ�����ȡ����"

function x310075_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x310075_g_MissionName)
			AddQuestText(sceneId,x310075_g_MissionComment)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId, targetId)

end



--**********************************

--�о��¼�

--**********************************

function x310075_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

		--AddQuestNumText(sceneId, x310075_g_ScriptId, x310075_g_MissionName,13,1)
	
end