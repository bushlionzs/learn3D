
--MisDescBegin
x300798_g_ScriptId = 300798
x300798_g_LevelLess	= 	75 
x300798_g_MissionName = "�������䱸˵����" 
x300798_g_ContinueInfo="\t��ȡ����#G75��#W������ҿ��Խ�ȡ�����䱸����ÿ������Ϊ#G30��#W��\n\t1.����������������ʱ��#G����#W�����ٴν�ȡ��\n\t2.����������û��ȫ����ɣ������Կɼ�����ɡ����磺#G�����������Ϊ(24/30)�������ܼ���������(24/30)��#W�������30��������޷�������ȡ��#G����#W�����ٴν�ȡ����\n\t3.��ҷ�����������ܲ������½�����һ������\n\t4.#W��ɵ�������Խ�࣬���#G���齱��#W�ͻ�Խ���\n\t5.��ɵ�30��ʱ�м��ʻ����һ��@item_10310003"
--MisDescEnd

function x300798_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	AddQuestNumText(sceneId, x300798_g_ScriptId, x300798_g_MissionName, 13, 1)
		
end

function x300798_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300798_g_MissionName)
		AddQuestText(sceneId,x300798_g_ContinueInfo)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, targetId)

end
