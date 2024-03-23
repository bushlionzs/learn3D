--生长点

x301201_g_GrowpointId = 151 --对应生长点ID
x301201_g_ItemIndex = 10020010 --对应收集物品的ID


--生成函数开始************************************************************************
function 	x301201_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301201_g_GrowpointId, sceneId, 0, x301201_g_ItemIndex)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301201_OnOpen(sceneId,selfId,targetId)
--if IsHaveQuest(sceneId,selfId, 2715) > 0 then
if GetItemCount(sceneId,selfId,10020010) == 0 then
	if GetZhiye( sceneId, selfId)==1 then
		 return 0  
	else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"与你的职业不符") 
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId) 
			 return 1
	end
else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"你已经有一把武器了") 
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId) 
			 return 1
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
function	 x301201_OnRecycle(sceneId,selfId,targetId)
	BeginAddItem(sceneId)                                                    
		AddBindItem( sceneId,10020010, 1 )                     
		local ret = EndAddItem(sceneId,selfId)                                 
	  if ret > 0 then                                                  
	    AddItemListToPlayer(sceneId,selfId) 
			else                                                             
		  BeginQuestEvent(sceneId)                                      
		  AddQuestText(sceneId,"物品栏已满，请整理下再来！")                    
		  EndQuestEvent(sceneId)                                        
		  DispatchQuestTips(sceneId,selfId)                      
	   end           	                 
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301201_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


