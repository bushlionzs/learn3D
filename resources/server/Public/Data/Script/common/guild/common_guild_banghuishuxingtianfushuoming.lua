--MisDescBegin 
x300773_g_ScriptId 					= 	300719
x300773_g_MissionName				= 	"帮会属性天赋" 
x300773_g_MissionInfo				= 	"巡按任务信息" 
--MisDescEnd

function x300719_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300719_ProcEventEntry(sceneId, selfId,targetId)	--点击该任务后执行此脚本
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y【帮会】帮会属性天赋#r#W"
		local Readme_2 = "  1，#G属性天赋研究：#W“属性天赋”的技能只有帮主能够研究，只有当玩家所在帮会研究了相关技能的时候，才能进行技能学习。#r"
		local Readme_3 = "  2，#G属性天赋学习：#W当玩家天赋达到10级时，可以开始“属性天赋”养成，“属性天赋”养成的等级与天赋等级相关，即需要一定的天赋等级才能完成“属性天赋”养成。学习属性天赋需要帮贡，三级以上属性学习时，还要消耗声望、威望。每级技能消耗的帮贡、声望、威望不同。#r"
		local Readme = Readme_1..Readme_2..Readme_3
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300773_g_ScriptId, -1 );
end 

function x300719_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x300719_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300719_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300719_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300719_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300719_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300719_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300719_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300719_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end