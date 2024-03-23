--点击（NPC）
function x300720_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

			AddQuestNumText(sceneId,300720,"【帮会】帮会介绍",0,1)--增加按钮B

  --AddQuestNumText(sceneId,ScriptId,MissionName,state,index)
								--MissionName：按钮名称
								--state:头顶显示规则
								--index:索引（下面判断用）

end

--点击（按钮）点击该任务后执行此脚本
function x300720_ProcEventEntry( sceneId, selfId, targetId,state,index)	

	if index == 1 then
	
			BeginQuestEvent(sceneId)

			local Readme_1 = "#Y帮会介绍#r#W #r"			
			
			local Readme_2 = "一，如果#G创建帮会#W您必须满足三个条件#r #r"
			
			local Readme_3 = "\t建立帮会需要#G30级#W以上。#r #r"
			
			local Readme_4 = "\t您需要花费#G5两金卡#W。#r #r"
			
			local Readme_5 = "\t您需要拥有#G“帮会令”#W。#r #r"
			
			local Readme_6 = "二，如果#G加入帮会#W您必须满足一个条件#r #r"
			
			local Readme_7 = "\t加入帮会需要#G20级#W以上。#r #r"

			local Readme_8 = "三，#G创建帮会#W成功#G10天后#W如果人数#G未达到10人#W系统将#G自动解散帮会#W。#r #r"	
			
			local Readme_9=  "四，#G帮会令：#W您需要打败边境的#G令火鸟#W。（王城420，190附近），#W并有#G一定几率获得。"
			
			local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5..Readme_6..Readme_7..Readme_8..Readme_9
			
			AddQuestText( sceneId,Readme)
			
			EndQuestEvent(sceneId)

			DispatchQuestEventList(sceneId,selfId,targetId)	
			
	end
	
end


--点击（确定）
function x300720_ProcAcceptCheck( sceneId, selfId, NPCId )

		--BeginQuestEvent(sceneId);AddQuestText(sceneId,bb);EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId);Msg2Player(sceneId,selfId,"帮会介绍",8,2)

end






















--**********************************
--接受
--**********************************
function x300720_ProcAccept( sceneId, sceneId )

end

--**********************************
--放弃
--**********************************
function x300720_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x300720_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x300720_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x300720_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x300720_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x300720_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x300720_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end


