-------------------------
--***********************
--Const
--***********************
-------------------------

x300363_g_ScriptId 					= 300363
x300363_g_MissionName				= "��ʦͽ��ͽ�ܱ���"
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x300363_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x300363_g_ScriptId, x300363_g_MissionName,3,0);
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x300363_ProcEventEntry(sceneId, selfId, targetId)
	local Readme_1 = "#Y��ʦͽ��ͽ�ܱ���#r"
	local Readme_2 = "\t#W�ȼ��Ѵﵽ20������û��ʦ������ҿ������������ͽ���ʸ�ı���������֮����ҿ����ڲ�ѯͽ�ܹ������ҵ������Ϣ���Ӷ����������ϣ����Ϊʦ��������ҵ��㡣\n\t���뱨��#G��Ϊͽ��#W��"
	local Readme = Readme_1..Readme_2
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, Readme);
	EndQuestEvent();
	DispatchQuestInfo(sceneId, selfId, targetId, x300363_g_ScriptId,-1);
	
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x300363_ProcAcceptCheck(sceneId, selfId, targetId)

	return 1;

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x300363_ProcAccept(sceneId, selfId)
	
	PrenticeCandidate(sceneId, selfId)

end
