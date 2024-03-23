--生长点


--脚本号 301027




--动态变量初始化方法

x301027_g_MissionId = 117


--生成函数开始************************************************************************

function 		x301027_OnCreate(sceneId,growPointType,x,y)
	
	local ItemBoxId = ItemBoxEnterScene(x,y,35,sceneId,0,13010270)
	
	
	
end






--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301027_OnOpen(sceneId,selfId,targetId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x301027_g_MissionId)
	if IsHaveQuest(sceneId,selfId, x301027_g_MissionId) > 0 then
			if GetQuestParam(sceneId,selfId,misIndex,0) == 0 then
				if GetItemCount(sceneId,selfId,13010026) == 1 then
						return 0
				end
		  else
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"您无法这样做")                    
					EndQuestEvent(sceneId)                                        
					DispatchQuestTips(sceneId,selfId)
					return 1 
			end
	else
		BeginQuestEvent(sceneId)                                      
		AddQuestText(sceneId,"您没有这个任务")                    
		EndQuestEvent(sceneId)                                        
		DispatchQuestTips(sceneId,selfId) 
		return 1
	end

end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301027_OnRecycle(sceneId,selfId,targetId)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"发射火炮 1/1")  
	  EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)

		return 0
 
	
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301027_OnProcOver(sceneId,selfId,targetId)

end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301027_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

end
