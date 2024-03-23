-------------------------
--***********************
--Const
--***********************
-------------------------

x300362_g_ScriptId 					= 300362
x300362_g_MissionName				= "��ʦͽ��ʦ������"
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x300362_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x300362_g_ScriptId, x300362_g_MissionName,3,0);
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x300362_ProcEventEntry(sceneId, selfId, targetId)
	local Readme_1 = "#Y��ʦͽ��ʦ������#r"
	local Readme_2 = "\t#W50�����ϲ���3����û���չ�ͽ�ܵ���ҿ������������ʦ���ʸ�ı���������֮����ҿ����ڲ�ѯʦ���������ҵ������Ϣ���Ӷ����������ϣ����Ϊͽ�ܵ�����ҵ��㡣\n\t���뱨��#G��Ϊʦ��#W��"
	local Readme = Readme_1..Readme_2
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, Readme);
	EndQuestEvent();
	DispatchQuestInfo(sceneId, selfId, targetId, x300362_g_ScriptId,-1);
	
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x300362_ProcAcceptCheck(sceneId, selfId, targetId)

	return 1;

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x300362_ProcAccept(sceneId, selfId)
	
	MasterCandidate(sceneId, selfId)

end