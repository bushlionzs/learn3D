
x305050_g_ScriptId = 305050
x305050_g_MissionName = "��ʱ��֮��˵����" 
x305050_g_ContinueInfo="\t�����ڵ���̫���Ĺ�â��������ʪ����ӥ��˫���ɼ�˼�������ܵ��������˵���в����ʷ�Ĺ켣������Ȼ�仯��\n\t��ʿ�ǣ���ͨ��#G����֮��#W��ȥ��#G���Ҳ�#W��֮�����ʷ�������������ǰɣ�\n\tÿ��#G11��00��15��00��19��00��23��00#W����ÿ����ʷ�����г���30���������ˣ�����־��ץ��ʱ���˵У�"

function x305050_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	AddQuestNumText(sceneId, x305050_g_ScriptId, x305050_g_MissionName, 13, 1)
		
end

function x305050_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x305050_g_MissionName)
		AddQuestText(sceneId,x305050_g_ContinueInfo)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, targetId)

end
