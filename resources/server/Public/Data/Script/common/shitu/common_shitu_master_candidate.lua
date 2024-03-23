-------------------------
--***********************
--Const
--***********************
-------------------------

x300362_g_ScriptId 					= 300362
x300362_g_MissionName				= "【师徒】师傅报名"
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
	local Readme_1 = "#Y【师徒】师傅报名#r"
	local Readme_2 = "\t#W50级以上并且3天内没有收过徒弟的玩家可以在这里进行师傅资格的报名。报名之后，玩家可以在查询师傅功能中找到你的信息，从而更方便地让希望成为徒弟的玩家找到你。\n\t你想报名#G成为师傅#W吗？"
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