
x305004_g_ScriptId = 305004
x305004_g_MissionName = "��ħ������˵����" 
x305004_g_ContinueInfo="\tʮ��ħ���Ĳ����Ǹ��������˵ã���Ű���ԡ����Ǻ��п��ܳ��������µص㣡\n#Y\n���պ��Ҳ���#G�����踮��\n \n#Y�����ɲ���#G��������ɽ��\n \n#Y����������#G�����������  \n \n#Y�������׶�����#G��Ī˹�ƹ�����\n \n#W\n�������ħ���������������ϵĸ��ֲƱ���"
function x305004_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	AddQuestNumText(sceneId, x305004_g_ScriptId, x305004_g_MissionName, 13, 1)
		
end

function x305004_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x305004_g_MissionName)
		AddQuestText(sceneId,x305004_g_ContinueInfo)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, targetId)

end
