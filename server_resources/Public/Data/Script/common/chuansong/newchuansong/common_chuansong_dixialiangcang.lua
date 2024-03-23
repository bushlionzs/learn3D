function x550502_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,550502,"离开粮仓",0,1)--增加按钮C
  --AddQuestNumText(sceneId,ScriptId,MissionName,state,index)
								--MissionName：按钮名称
								--state:头顶显示规则
								--index:索引（下面判断用）
end

--点击（按钮）点击该任务后执行此脚本
function x550502_ProcEventEntry( sceneId, selfId, targetId,state,index)	

if index == 1 then

	local Readme_1 = "#Y传送回本国边塞#r"
	
	local Readme_2 = "\t#W您好，您可以通过我传送回本国边塞，但是需要您付给我#G50文银卡#W作为路费。#r"
	
	local Readme_3 = "#r您是否要回到边塞？"
	
	local Readme = Readme_1..Readme_2..Readme_3	

	BeginQuestEvent(sceneId);AddQuestText(sceneId,Readme);EndQuestEvent(sceneId);DispatchQuestInfo(sceneId, selfId, targetId, 550502, -1)
	
	end
	
end


--点击（确定）
function x550502_ProcAcceptCheck( sceneId, selfId, NPCId )


	local x550502posX = 0
	local x550502posY = 0
	local x550502pos = random(1,2)

	if GetMoney(sceneId, selfId, 1) >= 50 then
	
				if GetCurCountry(sceneId,selfId) == 0 then--楼兰

						x550502posX= 273 + x550502pos
						
						x550502posY= 233 + x550502pos
						
						CostMoney( sceneId , selfId , 1 , 50,302 )

						NewWorld(sceneId,selfId,51,x550502posX,x550502posY, 550502)	
						
				elseif GetCurCountry(sceneId,selfId) == 1 then--天山
				
						x550502posX= 273 + x550502pos
						
						x550502posY= 233 + x550502pos

						CostMoney( sceneId , selfId, 1 , 50,302 )
						
						NewWorld(sceneId,selfId,151,x550502posX,x550502posY, 550502)
						
				elseif GetCurCountry(sceneId,selfId) == 2 then--昆仑
				
						x550502posX= 273 + x550502pos
						
						x550502posY= 233 + x550502pos
						
						CostMoney( sceneId , selfId, 1 , 50,302 )
						
						NewWorld(sceneId,selfId,251,x550502posX,x550502posY, 550502)
						
				elseif GetCurCountry(sceneId,selfId) == 3 then--敦煌

						x550502posX= 273 + x550502pos
						
						x550502posY= 233 + x550502pos
						
						CostMoney( sceneId , selfId, 1 , 50,302 )
						
						NewWorld(sceneId,selfId,351,x550502posX,x550502posY, 550502)
						
				end
		
	else
	
		Msg2Player(sceneId,selfId,"很抱歉，您包裹中的银卡不够支付路费，无法使用回国传送！",8,2)	
	
	end
	
end





















--**********************************
--接受
--**********************************
function x550502_ProcAccept( sceneId, selfId )
end

--**********************************
--放弃
--**********************************
function x550502_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x550502_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x550502_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x550502_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x550502_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x550502_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x550502_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end







