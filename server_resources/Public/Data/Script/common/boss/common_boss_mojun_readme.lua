
x305003_g_ScriptId = 305003
x305003_g_MissionName = "��ʮ��ħ��˵����" 
x305003_g_ContinueInfo="\t���֪��ʮ��ħ�������Ǻ��п��ܳ��������µص㣺\n#Y\n���֮��\n#G̩ɽ��192��77��\n#Y��ˮ֮��\n#G���˸���128��45��\n#Y��������֮��\n#G���˸���128��204��\n#Y����ɽ֮��\n#G���˸���128��128��\n#Yѩɽ֮��\n#G̫��ɽ��142��48��\n#Y���֮��\n#G���踮��47��179��\n#Yƽԭ֮��\n#G���ݳǣ�65��141��\n#Y�߼���֮��\n#G���루161��40��\n#YɳĮ֮��\n#G������ɽ��188��206��\n#Y����֮��\n#G��Ҷ�ǣ�49��103��\n#Y����֮��\n#G��ɳĮ��103��190��\n#Y����֮��\n#G���ΰ뵺��176��138��\n#Y�͸��֮��\n#G�͸�87��155��\n#Y���֮��\n#G��˹��ԭ��92��191��\n#Y������֮��\n#G��������230��126��\n#Y�ٺ�֮��\n#GĪ˹�ƣ�77��181��\n#Y������֮��\n#G����������217��118��\n#Y����֮��\n#G����������130��225��\n#Y�������֮��\n#G���������83��225��\n#Y����֮��\n#G��ʥ����66��222��\n#Y����˹��֮��\n#G��ռͥ��122��191��\n#Y����ʿ��֮��\n#G����ʿ�217��182��\n#Yʥ��֮��\n#GҮ·���䣨43��36��\n#YҶ����֮��\n#G¥��������211��203��\n#Y��Ѫ֮��\n#G��ɽ������43��45��\n#YĻ��֮��\n#G���ذ�����211��203��\n#YĮ��֮��\n#G�ػͰ�����43��45��\n#W\nÿ����������80�����µ�ʮ��ħ���󣬺�������������������˸���128��128����"
function x305003_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	AddQuestNumText(sceneId, x305003_g_ScriptId, x305003_g_MissionName, 13, 1)
end

function x305003_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x305003_g_MissionName)
		AddQuestText(sceneId,x305003_g_ContinueInfo)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, targetId)
end
