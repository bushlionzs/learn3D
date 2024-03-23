function x550529_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,550529,"离开迷雾镇",0,1)--增加按钮C
  --AddQuestNumText(sceneId,ScriptId,MissionName,state,index)
								--MissionName：按钮名称
								--state:头顶显示规则
								--index:索引（下面判断用）
end

--点击（按钮）点击该任务后执行此脚本
function x550529_ProcEventEntry( sceneId, selfId, targetId,state,index)	

if index == 1 then

	local Readme_1 = "#Y离开迷雾镇#r"
	
	local Readme_2 = "\t#W您好，您可以通过我离开迷雾镇，请问您是否要离开？"
	
	local Readme = Readme_1..Readme_2

	BeginQuestEvent(sceneId);AddQuestText(sceneId,Readme);EndQuestEvent(sceneId);DispatchQuestInfo(sceneId, selfId, targetId, 550529, -1)
	
	end
	
end


--点击（确定）
function x550529_ProcAcceptCheck( sceneId, selfId, NPCId )

	local x550529pos = random(1,2)
	
	local x550529posX = 0
	
	local x550529posY = 0

				if GetCurCountry(sceneId,selfId) == 0 then--楼兰		
						
						x550529posX= 381 + x550529pos
						
						x550529posY= 69 + x550529pos
						
						NewWorld(sceneId,selfId,50,x550529posX,x550529posY,550529)	
						
				elseif GetCurCountry(sceneId,selfId) == 1 then--天山
										
						x550529posX= 381 + x550529pos
						
						x550529posY= 69 + x550529pos

						NewWorld(sceneId,selfId,150,x550529posX,x550529posY,550529)
						
				elseif GetCurCountry(sceneId,selfId) == 2 then--昆仑
								
						x550529posX= 381 + x550529pos
						
						x550529posY= 69 + x550529pos
						
						NewWorld(sceneId,selfId,250,x550529posX,x550529posY,550529)
						
				elseif GetCurCountry(sceneId,selfId) == 3 then--敦煌

						x550529posX= 381 + x550529pos
						
						x550529posY= 69 + x550529pos
						
						NewWorld(sceneId,selfId,350,x550529posX,x550529posY,550529)
						
				end
	
end





















--**********************************
--接受
--**********************************
function x550529_ProcAccept( sceneId, selfId )
end

--**********************************
--放弃
--**********************************
function x550529_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x550529_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x550529_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x550529_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x550529_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x550529_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x550529_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end







