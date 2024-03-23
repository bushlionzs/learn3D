-------------------------
--***********************
--Const
--***********************
-------------------------

x300363_g_ScriptId 					= 300363
x300363_g_MissionName				= "【师徒】徒弟报名"
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
	local Readme_1 = "#Y【师徒】徒弟报名#r"
	local Readme_2 = "\t#W等级已达到20级并且没有师傅的玩家可以在这里进行徒弟资格的报名。报名之后，玩家可以在查询徒弟功能中找到你的信息，从而更方便地让希望成为师傅的玩家找到你。\n\t你想报名#G成为徒弟#W吗？"
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
