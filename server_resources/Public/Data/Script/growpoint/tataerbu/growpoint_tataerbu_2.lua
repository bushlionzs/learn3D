--生长点


--脚本号 301026




--动态变量初始化方法

x301026_g_MissionId = 117


--生成函数开始************************************************************************

function 		x301026_OnCreate(sceneId,growPointType,x,y)
	
	local ItemBoxId = ItemBoxEnterScene(x,y,34,sceneId,0,13010260)
	
	
	
end






--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301026_OnOpen(sceneId,selfId,targetId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x301026_g_MissionId)
	if IsHaveQuest(sceneId,selfId, x301026_g_MissionId) > 0 then
			if GetQuestParam(sceneId,selfId,misIndex,0) == 0 then
				if GetItemCount(sceneId,selfId,13010026) < 1 then
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
function	 x301026_OnRecycle(sceneId,selfId,targetId)
	BeginAddItem(sceneId)                                                    
	AddItem( sceneId,13010026, 1 )             
	local ret = EndAddItem(sceneId,selfId)                                 
	if ret > 0 then                                                  
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,format("得到炮弹   %d/1", GetItemCount(sceneId,selfId,13010026)+1))
	        EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)
		AddItemListToPlayer(sceneId,selfId) 
		return 1 
	else                                                             
		BeginQuestEvent(sceneId)                                      
		AddQuestText(sceneId,"物品栏已满！")                    
		EndQuestEvent(sceneId)                                        
		DispatchQuestTips(sceneId,selfId) 
		return 0
	end   
 
	
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301026_OnProcOver(sceneId,selfId,targetId)

end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301026_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

end
