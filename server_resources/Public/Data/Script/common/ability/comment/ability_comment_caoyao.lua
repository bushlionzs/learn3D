
x540200_g_ScriptId = 540200
x540200_g_MissionName = "���ɼ�����˵����" 
x540200_g_ContinueInfo="\tѧϰ#R�ɼ�#W���ܺ���#G��ԭ��ͼ#W���Բɼ�����������ܲ��ϣ��ص����£�\n#Y\n1~2������#W  ���Բɼ�#G�컨���ʲ�#W\n#Y�ɼ��ص�   #G���ѺӲ�ԭ�����ղ�\n#Y\n3~4������#W  ���Բɼ�#G���ߣ������#W\n#Y�ɼ��ص�   #G���ղ�����������\n#W\n#Y5~6������#W  ���Բɼ�#G���飬��ɰ#W\n#Y�ɼ��ص�   #G���Ҳ���������\n#W\n#Y7~8������#W  ���Բɼ�#G���磬��֦#W\n#Y�ɼ��ص�   #G����������ӹ��\n#W��ע�⣺�糡����û������ܲɼ�����ڵģ�����Ҫǰ�������������ͼ�вɼ����磺������ԭ-���Ѻӣ������� �糡-���Ѻӡ�"

function x540200_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	AddQuestNumText(sceneId, x540200_g_ScriptId, x540200_g_MissionName, 13, 1)
		
end

function x540200_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x540200_g_MissionName)
		AddQuestText(sceneId,x540200_g_ContinueInfo)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, targetId)

end
