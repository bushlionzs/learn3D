x310084_g_ScriptId = 310084

x310084_g_MissionName = "����������˵����"
x310084_g_MissionComment = "\tÿ��#G12��15~12��45,14��15~14��45,16��15~16��45��18��15~18��45#W���������佫�Ӵ˴����٣�����һ�ܺ󷵻أ�#G����20��#W����ҽ�������ѳ������������������������������䣡�����ڳ����н������У�ÿ��һ��ʱ�佫����#G�߶�����������#W������������#GԽ��#W����õ�#G����#W�ͻ�#GԽ��#W����ӭ������\n\t����ĺ�ֻ��#R����8��#W�������ڹ涨ʱ���ڣ��ڷ�����վ���������ϳ���\n\tע�⣬��������ʻ���󽫲��ٽ��ܳ˿���;�ϳ������������ŶӵȺ�"

function x310084_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x310084_g_MissionName)
			AddQuestText(sceneId,x310084_g_MissionComment)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId, targetId)

end



--**********************************

--�о��¼�

--**********************************

function x310084_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

		AddQuestNumText(sceneId, x310084_g_ScriptId, x310084_g_MissionName,13,1)
	
end