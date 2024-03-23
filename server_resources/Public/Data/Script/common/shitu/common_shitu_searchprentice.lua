--帮会升级
--MisDescBegin
--脚本号
x800040_g_ScriptId = 800040

--上一个任务的ID
--g_MissionIdPre =



--任务文本描述
x800040_g_MissionName="【师徒】查找徒弟"

--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x800040_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800040_g_ScriptId,x800040_g_MissionName,3,0);
end

function x800040_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本
	local Readme_1 = "#Y【师徒】查找徒弟#r"
	local Readme_2 = "\t#W您可以通过我的帮助找到您乖巧的徒弟，成功结成师徒关系可在未来的日子里获得丰厚的奖励。#r\t您是否要#G查找徒弟#W？"
	local Readme = Readme_1..Readme_2
	BeginQuestEvent(sceneId);AddQuestText(sceneId, Readme);EndQuestEvent();DispatchQuestInfo(sceneId, selfId, targetId, x800040_g_ScriptId,-1);
end

--**********************************
--列举事件
--**********************************



--********************
--检测接受条件
--**********************************
function x800040_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x800040_ProcAccept( sceneId, selfId )

end

--**********************************
--放弃
--**********************************
function x800040_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--继续
--**********************************
function x800040_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--检测是否可以提交
--**********************************
function x800040_CheckSubmit( sceneId, selfId )
end

--**********************************
--提交
--**********************************
function x800040_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

--**********************************
--杀死怪物或玩家
--**********************************
function x800040_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

--**********************************
--进入区域事件
--**********************************
function x800040_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x800040_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
