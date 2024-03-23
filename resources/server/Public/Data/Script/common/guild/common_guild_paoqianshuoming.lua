--MisDescBegin 
x300704_g_ScriptId 					= 	300704
x300704_g_MissionName				= 	"帮会跑商" 
x300704_g_MissionInfo				= 	"巡按任务信息" 
--MisDescEnd

function x300704_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300704_ProcEventEntry(sceneId, selfId,targetId)	--点击该任务后执行此脚本
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y【帮会跑商说明】#r#W"
		local Readme_2 = "  1.#G接取任务：#W在不低于#G三级#W的帮会中，所有成员都可以接取该任务，每天每个帮会可以完成100次该任务，接取任务后要缴纳#G5两#W银卡或现银的押金，完成后返还5两银卡。#r"
		local Readme_3 = "  2.#G任务介绍：#W接取跑商任务后，会得到#G三件帮会货物#W和一张#G帮会银票#W在王城地区找到城西商人，城东商人和在王城内游走的王城游商，将身上的帮会货物出售给他们，赚足完成任务的所需金额。注意：货物一定要尽量出售给出价最高的商人，才能赚取足够的金钱。#r"
			local Readme_4 = "  3.#G注意事项：#G王城游商#W对所有货物都是高价收购，但如果有其他人在你之前在王城游商出售了和你相同的货物后，5分钟内王城游商不会再收购这件商品。#r"
		local Readme_5 = "  4.#G任务奖励：#W成功完成此任务，您将获得不菲的#G经验#W奖励和#G20两#W帮会金钱。" 
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300704_g_ScriptId, -1 );
end 

function x300704_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x300704_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300704_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300704_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300704_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300704_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300704_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300704_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300704_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end