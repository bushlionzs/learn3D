--训练藏獒

--MisDescBegin
x300503_g_ScriptId = 300503
x300503_g_MissionName="机械法训练"
x300503_g_MissionId = 5600
--MisDescEnd
--**********************************

--任务入口函数

--**********************************

function x300503_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
		local winorlose ="\n本次训练失败"
		local misIndex = GetQuestIndexByID(sceneId,selfId,x300503_g_MissionId)
			SetQuestByIndex(sceneId,selfId,misIndex,0,GetQuestParam(sceneId,selfId,misIndex,0)-1)
		if GetQuestParam(sceneId,selfId,misIndex,2) < 100 then
			SetQuestByIndex(sceneId,selfId,misIndex,2,GetQuestParam(sceneId,selfId,misIndex,2)+5)
		end
		if GetQuestParam(sceneId,selfId,misIndex,3) < 100 then
			SetQuestByIndex(sceneId,selfId,misIndex,3,GetQuestParam(sceneId,selfId,misIndex,3)+5)
		end
		if GetQuestParam(sceneId,selfId,misIndex,1) > random (1,100) then
				SetQuestByIndex(sceneId,selfId,misIndex,4,GetQuestParam(sceneId,selfId,misIndex,4)+5)
				winorlose ="\n训练成功得到#G5#W分"
		end                                                                                      
			SetQuestByIndex(sceneId,selfId,misIndex,1,GetQuestParam(sceneId,selfId,misIndex,1)-10)
					if GetQuestParam(sceneId,selfId,misIndex,0) > 0 then
											--local feed1=format("机械法(成功几率%d%%)",GetQuestParam(sceneId,selfId,misIndex,1))
      								--local feed2=format("食物法(成功几率%d%%)",GetQuestParam(sceneId,selfId,misIndex,2))
      								--local feed3=format("模仿法(成功几率%d%%)",GetQuestParam(sceneId,selfId,misIndex,3))
      	    					--BeginQuestEvent(sceneId)
		 									--AddQuestText(sceneId,"机械法训练如果成功的话，这只藏獒会得到5分；食物法训练如果成功的话，这只藏獒会得到4到6分；模仿法训练如果成功的话，这只藏獒会得到3到7分；选择一种方法训练藏獒吧。") 
		 									--AddQuestText(sceneId,format("\n你还能训练这只藏獒  #G%d#W  次",GetQuestParam(sceneId,selfId,misIndex,0)))
		 									--AddQuestText(sceneId,format("\n你现在训练的藏獒得分为  #G%d#W",GetQuestParam(sceneId,selfId,misIndex,4))) 
		 									--AddQuestNumText(sceneId, x300503_g_ScriptId, feed1)
      								--AddQuestNumText(sceneId, x300504_g_ScriptId, feed2)
      								--AddQuestNumText(sceneId, x300505_g_ScriptId, feed3)
            					--EndQuestEvent()
            					--DispatchQuestEventList(sceneId, selfId, targetId)
            					BeginQuestEvent(sceneId)
            					AddQuestText(sceneId,"机械法训练如果成功的话，这只藏獒会得到5分；食物法训练如果成功的话，这只藏獒会得到4到6分；模仿法训练如果成功的话，这只藏獒会得到3到7分；如果重复用一种方法训练的话，成功的几率会降低。选择一种方法训练藏獒吧。") 
		 									AddQuestText(sceneId,winorlose) 
		 									AddQuestText(sceneId,format("\n你还能训练这只藏獒  #G%d#W  次",GetQuestParam(sceneId,selfId,misIndex,0)))
		 									AddQuestText(sceneId,format("\n你现在训练的藏獒得分为  #G%d#W",GetQuestParam(sceneId,selfId,misIndex,4))) 
		 									AddQuestNumText(sceneId, x300503_g_ScriptId, "机械法训练藏獒")
		 									EndQuestEvent()
		 									DispatchQuestEventList(sceneId, selfId, targetId)
          elseif GetQuestParam(sceneId,selfId,misIndex,0) == 0 then
          			BeginQuestEvent(sceneId)
          			AddQuestText(sceneId,format("你的藏獒得分为#G%d#W,去把这只藏獒给孙相马带过去吧。",GetQuestParam(sceneId,selfId,misIndex,4))) 
          			EndQuestEvent()
            		DispatchQuestEventList(sceneId, selfId, targetId)
         end

	
end
function x300503_ProcEnumEvent(sceneId, selfId, targetId, MissionId)


    if IsHaveQuest(sceneId,selfId, x300503_g_MissionId) > 0 then
        
        local misIndex = GetQuestIndexByID(sceneId,selfId,x300503_g_MissionId)
        if GetQuestParam(sceneId,selfId,misIndex,0) > 0 then
            AddQuestNumText(sceneId, x300503_g_ScriptId, "机械法训练藏獒")
        end
    end
	
end

