
x540202_g_ScriptId = 540202
x540202_g_MissionName = "���ɿ���˵����" 
x540202_g_ContinueInfo="\tѧϰ#R�ɿ�#W���ܺ���#G��ԭ��ͼ#W�����ھ򵽸�������ܲ��ϣ��ص����£�\n#W\n#Y1~2������#W  �����ھ�#G������ʯ#W\n#Y�ھ�ص�   #G���ѺӲ�ԭ�����ղ�\n#W\n#Y3~4������#W  �����ھ�#G�м���ʯ#W\n#Y�ھ�ص�   #G���ղ�����������\n#W\n#Y5~6������#W  �����ھ�#G�߼���ʯ#W\n#Y�ھ�ص�   #G���Ҳ���������\n#W\n#Y7~8������#W  �����ھ�#Gʥͽ����ʯ#W\n#Y�ھ�ص�   #G����������ӹ��\n#W��ע�⣺�糡����û������ܲɼ�����ڵģ�����Ҫǰ�������������ͼ�вɼ����磺������ԭ-���Ѻӣ������� �糡-���Ѻӡ�"

function x540202_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	AddQuestNumText(sceneId, x540202_g_ScriptId, x540202_g_MissionName, 13, 1)
		
end

function x540202_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x540202_g_MissionName)
		AddQuestText(sceneId,x540202_g_ContinueInfo)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, targetId)

end
