
-------------------------
--***********************
--Const
--***********************
-------------------------

x800006_g_ScriptId 					= 800006
x800006_g_MissionName				= "【婚姻】我要结婚"

-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x800006_ProcEnumEvent(sceneId, selfId, targetId, eventId, index)
	AddQuestNumText(sceneId, x800006_g_ScriptId, x800006_g_MissionName,3);
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x800006_ProcEventEntry(sceneId, selfId, targetId)
	BeginQuestEvent(sceneId);
	local Readme_0 = "#Y【婚姻】我要结婚#W#r"
	local Readme_1 = "\t在成吉思汗中，#G好友度#W很高的#G男女双方#W可以结为夫妻。#r"
	local Readme_2 = "\t双方必须#G组队前往#W（需2人组队）#r"
	local Readme_3 = "\t双方等级必须为#G40级以上#W。#r"
	local Readme_4 = "\t双方各自的好友度需#G1000点#W以上#r"
	local Readme_5 = "\t男方包裹中必须有#G红绳#W才可求婚#r"
	local Readme_6 = "\t男方必须有#G131两421文银子#W才可求婚。#r"
	local Readme_7 = "\t男女双方必须#G同时在线#W并同时#G在我身边#W才能完成结婚。#r #r"
	local Readme_8 = "\t如果你们满足了以上条件就可以结婚了。#r"
	local Readme_9 = "\t#R红绳：需要接受“寻找红绳”任务，并通过打败泰山的#G姻缘魔兽#R，#G姻缘魔圣#R，并获得其逃跑时掉落的道具，并回到大都找到#G结婚助理#R进行合成才能获得红绳。"
	local Readme = Readme_0..Readme_1..Readme_2..Readme_3..Readme_4..Readme_5..Readme_6..Readme_7..Readme_8..Readme_9

	
	AddQuestText(sceneId, Readme);
	EndQuestEvent();
	DispatchQuestInfo(sceneId, selfId, targetId, x800006_g_ScriptId, -1);
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x800006_ProcAcceptCheck(sceneId, selfId, targetId)

	return 1;

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x800006_ProcAccept(sceneId, selfId, targetId)

end