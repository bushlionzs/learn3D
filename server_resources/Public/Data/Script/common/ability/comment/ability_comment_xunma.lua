
x540201_g_ScriptId = 540201
x540201_g_MissionName = "����׽����˵����" 
x540201_g_ContinueInfo="\tѧϰ#R��׽#W���ܺ���#G��ԭ��ͼ#W���Բ�׽����������ܲ��ϣ��ص����£�\n#Y\n1~2������#W  ���Բ�׽#G���#W\n#Y��׽�ص�   #G���ѺӲ�ԭ�����ղ�\n#W\n#Y3~4������#W  ���Բ�׽#Gţ�#W\n#Y��׽�ص�   #G���ղ�����������\n#W\n#Y5~6������#W  ���Բ�׽#G��Ѫ����#W\n#Y��׽�ص�   #G���Ҳ���������\n#W\n#Y7~8������#W  ���Բ�׽#G��Ѫ���#W\n#Y��׽�ص�   #G����������ӹ��\n#W��ע�⣺�糡����û������ܲɼ�����ڵģ�����Ҫǰ�������������ͼ�вɼ����磺������ԭ-���Ѻӣ������� �糡-���Ѻӡ�"

function x540201_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	AddQuestNumText(sceneId, x540201_g_ScriptId, x540201_g_MissionName, 13, 1)
		
end

function x540201_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x540201_g_MissionName)
		AddQuestText(sceneId,x540201_g_ContinueInfo)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, targetId)

end
