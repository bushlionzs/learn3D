--生长点

x301312_g_GrowpointId = 178 --对应生长点ID
x301312_g_ItemIndex = 13030089 --对应收集物品的ID


--生成函数开始************************************************************************
function 	x301312_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301312_g_GrowpointId, sceneId, 0, x301312_g_ItemIndex)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301312_OnOpen(sceneId,selfId,targetId)
if IsHaveQuest(sceneId,selfId, 1608) > 0 then
if GetItemCount(sceneId,selfId,13030089) == 0 then
		if GetItemCount(sceneId,selfId,13030087) == 1 then
	
		  return 0
		end
else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"鱼已经烤好了！") 
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId) 
			return 1
end
end

--else
--			BeginQuestEvent(sceneId)
--			AddQuestText(sceneId,"你没有接此任务") 
--			EndQuestEvent()
--			DispatchQuestTips(sceneId, selfId) 
--			return 1
end
--end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301312_OnRecycle(sceneId,selfId,targetId)
	BeginAddItem(sceneId)                                                    
		AddItem( sceneId,13030089, 1 )  
		AddQuestText(sceneId,"您获得了物品：烤鱼！")           
		local ret = EndAddItem(sceneId,selfId)                                 
	  if ret > 0 then                                                  
	    AddItemListToPlayer(sceneId,selfId) 
	    DelItem(sceneId, selfId, 13030087, 1)
	  else                                                             
		  BeginQuestEvent(sceneId)                                      
		  AddQuestText(sceneId,"物品栏已满，请整理下再来！")                    
		  EndQuestEvent(sceneId)                                        
		  DispatchQuestTips(sceneId,selfId)                      
	   end           	               
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301312_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

