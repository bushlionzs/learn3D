--MisDescBegin 
x310402_g_ScriptId 					= 	310402
x310402_g_MissionName				= 	"【离线代练说明】" 
x310402_g_MissionInfo				= 	"离线代练说明" 
--MisDescEnd

function x310402_ProcEnumEvent( sceneId, selfId, targetId )
	AddQuestNumText(sceneId, x310402_g_ScriptId,x310402_g_MissionName,13,1)
end

function x310402_ProcEventEntry(sceneId, selfId,targetId)	--点击该任务后执行此脚本
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y【离线代练说明】#r#W"
		local Readme_2 = "\t只有不低于#G40#W级的玩家才可以使用离线代练。\n\t开始离线代练后您的离线代练时间将累积计算到您下次上线为止，之后您可花费一定的金钱领取对应的离线经验，离线代练时间最多可累积7天。"
		local Readme_3 = "\n\t可选择您要领取的离线经验档次，不同的档次需要花费不同数量的金钱。"
		local Readme_4 = "\n\t#G低档#W：普通经验效率，需要花费#G银币#W，#G40#W级可使用\n"..
										 "\t#G中档#W：双倍经验效率，需要花费#G金币#W，#G60#W级可使用\n"..
										 "\t#G高档#W：三倍经验效率，需要花费#G金币#W，#G70#W级可使用"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x310402_g_ScriptId, -1 );
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x310402_g_ScriptId,x310402_g_MissionName)
end 

function x310402_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x310402_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x310402_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x310402_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x310402_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x310402_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x310402_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x310402_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x310402_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end