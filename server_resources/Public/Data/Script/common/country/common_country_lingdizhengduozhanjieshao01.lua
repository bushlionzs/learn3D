--MisDescBegin 
x300935_g_ScriptId 					= 	300935
x300935_g_MissionName				= 	"【领地介绍】" 
x300935_g_MissionInfo				= 	"【领主战场说明】" 
--MisDescEnd

function x300935_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300935_ProcEventEntry(sceneId, selfId,targetId)	--点击该任务后执行此脚本
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y【领地介绍】#r#W"
		local Readme_2   = "1、游戏中，共有#G9个#W领地可供争夺，根据#G等级排行榜#W最后一名的#G玩家等级#W开放对应可争夺地图。#r #r"
		local Readme_3   = "2、领地及相应开放等级为：#r#G蔡州城           （45级）#W#r#G碎叶城           （60级）#W#r#G巴格达           （70级）#W#r#G基辅公国         （80级）#W#r#G神圣罗马帝国     （90级）#W#r#G耶路撒冷        （100级）#W#r#G福冈            （110级）#W#r#G缅甸            （120级）#W#r#G爪哇岛          （130级）#W#r #r"
		local Readme_4   = "3、占领领地的帮会成员于每周六可以领取津贴和海量经验，帮主领取的奖励为帮众的四倍。#r"		
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300935_g_ScriptId, -1 );
end 

function x300935_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x300935_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300935_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300935_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300935_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300935_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300935_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300935_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300935_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end