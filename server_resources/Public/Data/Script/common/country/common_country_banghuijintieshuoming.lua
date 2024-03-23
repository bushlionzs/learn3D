--MisDescBegin 
x300794_g_ScriptId 					= 	300794
x300794_g_MissionName				= 	"【介绍】帮会津贴" 
x300794_g_MissionInfo				= 	"津贴介绍" 
--MisDescEnd

function x300794_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300794_ProcEventEntry(sceneId, selfId,targetId)	--点击该任务后执行此脚本
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y【介绍】帮会津贴#r#W"
		local Readme_2 = "\t帮会津贴，是每一个为帮会作出贡献的帮众都可以领取的奖励。#r"
		local Readme_3 = "\t参与#G成功护送神兽#W的次数，#G帮会战的战果#W，将直接影响每周帮会津贴的多少。#r"
		local Readme_4 = "\t等级不低于#G60#W，每周功勋值不低于#G28点#W的玩家，每#G周日#W可以在我这里领取一周的帮会津贴。#r"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300794_g_ScriptId, -1 );
end 

function x300794_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x300794_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300794_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300794_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300794_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300794_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300794_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300794_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300794_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end