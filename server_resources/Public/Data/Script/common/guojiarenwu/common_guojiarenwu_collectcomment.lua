
--MisDescBegin
x300502_g_ScriptId = 300502
x300502_g_LevelLess	= 	30 
x300502_g_MissionName = "���ռ���������˵����" 
x300502_g_ContinueInfo="\t#W������ʮ��Ϊһ�֣�ÿ��ֻ�����һ�֡��������У�Ҳ������ռ��˻�#G��������ռ�ͬһ��Ʒ#W���������������㽫���÷��Ľ�����\n\t#G�������������񣬵����޷��ٴ���ȡ�ռ����������ˡ�\n\t#W�����ͨ����Ұ���ֵ����ò��ϣ�Ҳ����ȥ��@npc_138591��@npc_138592��@npc_138593ѧϰ����ܻ������Ĳ��ϡ�"
--MisDescEnd

function x300502_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	AddQuestNumText(sceneId, x300502_g_ScriptId, x300502_g_MissionName, 13, 1)
		
end

function x300502_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300502_g_MissionName)
		AddQuestText(sceneId,x300502_g_ContinueInfo)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, targetId)

end
