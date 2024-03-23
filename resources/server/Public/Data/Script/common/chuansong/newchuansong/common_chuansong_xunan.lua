
x550528_g_MissionId 				= 	7550                    --任务ID

function x550528_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,550528,"进入迷雾镇",0,1)--增加按钮C
end

--点击（按钮）点击该任务后执行此脚本
function x550528_ProcEventEntry( sceneId, selfId, targetId,state,index)	

	if index == 1 then

		local Readme_1 = "#Y迷雾镇#r"
	
		local Readme_2 = "\t#W我是把守迷雾镇的“追命巡捕”，您可以通过我传送进入迷雾镇#r #r"
	
		local Readme_3 = "#r您是否要进入迷雾镇？"
	
		local Readme = Readme_1..Readme_2..Readme_3	

		BeginQuestEvent(sceneId);AddQuestText(sceneId,Readme);EndQuestEvent(sceneId);DispatchQuestInfo(sceneId, selfId, targetId, 550528, -1)
	
	end
	
end


--点击（确定）
function x550528_ProcAcceptCheck( sceneId, selfId, NPCId )

	local posX = 0

	local posY = 0

	local bHaveMission = IsHaveQuestNM(sceneId, selfId, x550528_g_MissionId);

	if bHaveMission > 0 then		

			local pos = random(1,2)

			local Num = random(1,7)

			if 	Num == 1 then

					posX= 198 + pos

					posY= 27 +  pos

					NewWorld(sceneId,selfId,95,posX,posY,550528)
					
			elseif Num == 2 then

					posX= 235 + pos

					posY= 63 +  pos

					NewWorld(sceneId,selfId,95,posX,posY,550528)

			elseif Num == 3 then

					posX= 225 + pos

					posY= 165 +  pos

					NewWorld(sceneId,selfId,95,posX,posY,550528)

			elseif Num == 4 then

					posX= 153 + pos

					posY= 224 +  pos

					NewWorld(sceneId,selfId,95,posX,posY,550528)

			elseif Num == 5 then

					posX= 37 + pos

					posY= 220 +  pos

					NewWorld(sceneId,selfId,95,posX,posY,550528)

			elseif Num == 6 then

					posX= 37 + pos

					posY= 133 +  pos

					NewWorld(sceneId,selfId,95,posX,posY,550528)

			elseif Num == 7 then

					posX= 31 + pos

					posY= 45 +  pos

					NewWorld(sceneId,selfId,95,posX,posY,550528)

			end

	else
    	BeginQuestEvent( sceneId)
		AddQuestText( sceneId, "很抱歉，您未领取“巡案任务”不能进入迷雾镇！" )
    	EndQuestEvent()
        DispatchQuestTips( sceneId, selfId)

		Msg2Player( sceneId, selfId, "很抱歉，您未领取“巡案任务”不能进入迷雾镇！", 8, 2)
        

	end	

end


