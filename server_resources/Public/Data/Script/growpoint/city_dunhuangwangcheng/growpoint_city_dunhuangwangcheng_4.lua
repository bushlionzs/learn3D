--生长点

x301005_g_GrowpointId = 6 --对应生长点ID
x301005_g_ItemIndex = 13020006 --对应收集物品的ID


--生成函数开始************************************************************************
function 	x301005_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301005_g_GrowpointId, sceneId, 0, x301005_g_ItemIndex)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301005_OnOpen(sceneId,selfId,targetId)
	if IsHaveQuest(sceneId,selfId, 2893) > 0 then
		if GetItemCount(sceneId,selfId,x301005_g_ItemIndex) < 5 then
				return 0
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"你已经采够了芨芨草") 
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId) 
			return 1
		end
	else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"你没有接此任务") 
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId) 
			return 1
	end
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301005_OnRecycle(sceneId,selfId,targetId)
	BeginAddItem(sceneId)                                                    
		AddItem( sceneId,x301005_g_ItemIndex, 1 )             
	  local ret = EndAddItem(sceneId,selfId)                                 
	  if ret > 0 then                                                  
	    AddItemListToPlayer(sceneId,selfId) 
	    BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"得到一棵芨芨草") 
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId) 
		return 1
	  else                                                             
		  BeginQuestEvent(sceneId)                                      
		  AddQuestText(sceneId,"物品栏已满，请整理下再来！")                    
		  EndQuestEvent(sceneId)                                        
		  DispatchQuestTips(sceneId,selfId)                      
	   end           	   
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301005_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

