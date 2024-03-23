--MisDescBegin 
x300796_g_ScriptId 					= 	300796
x300796_g_MissionName				= 	"【介绍】国运津贴" 
x300796_g_MissionInfo				= 	"津贴介绍" 
--MisDescEnd

function x300796_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300796_ProcEventEntry(sceneId, selfId,targetId)	--点击该任务后执行此脚本
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y【介绍】国运津贴#r#W"
		local Readme_2 = "\t国运津贴是对在国运任务中做出贡献的#G国家官员#W和#G国王帮会成员#W的奖励。#r"
		local Readme_3 = "\t在发布#G国运令#W时间内，国内每个玩家#G完成国运任务#W的次数将直接影响国运津贴的多少。#r"
		local Readme_4 = "\t每周一到周日，每天国运令期间国运任务的成功次数将会累计，在周日，可以领取一周的国运津贴。#G国王#W领取#G四倍#W国运津贴，#G国家大臣#W领取#G两倍#W国运津贴，#G国王帮众#W领取#G一倍#W国运津贴。#r"
		local Readme_5 = "\t国家官员或者国王帮会成员，等级不低于#G60#W，每周功勋值不低于#G38点#W，每#G周日#W可以在我这里领取一周的国运津贴。"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300796_g_ScriptId, -1 );
end 

function x300796_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x300796_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300796_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300796_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300796_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300796_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300796_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300796_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300796_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end