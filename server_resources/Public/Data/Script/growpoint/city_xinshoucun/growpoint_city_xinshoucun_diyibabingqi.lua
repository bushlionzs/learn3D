--生长点

x301307_g_GrowpointId = 172 --对应生长点ID
x301307_g_ItemIndex = {10011001,10021001,10031001,10041001,10051001,10061001} --对应收集物品的ID

--生成函数开始************************************************************************
function 	x301307_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301307_g_GrowpointId, sceneId, 0, x301307_g_ItemIndex[1])
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301307_OnOpen(sceneId,selfId,targetId)
if IsHaveQuest(sceneId,selfId, 3002) > 0 then
local zhiye =GetZhiye( sceneId, selfId)+1
if GetItemCount(sceneId,selfId,x301307_g_ItemIndex[zhiye]) == 0 then
	
		  return 0
	
else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"你已经获得了前辈的馈赠，别太贪心") 
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId) 
			return 1
end

else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"你没有此任务") 
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId) 
			return 1
end
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301307_OnRecycle(sceneId,selfId,targetId)
	BeginAddItem(sceneId)  
	if GetZhiye( sceneId, selfId) == 0   then                                               
		AddItem( sceneId,10011001, 1 )
			BeginQuestEvent(sceneId)                                      
		  AddQuestText(sceneId,"你获得了物品：#R家传刀")                    
		  EndQuestEvent(sceneId)                                        
		  DispatchQuestTips(sceneId,selfId) 
	end  
	if  GetZhiye( sceneId, selfId) ==1   then
		AddItem( sceneId,10021001, 1 )
					BeginQuestEvent(sceneId)                                      
		  AddQuestText(sceneId,"你获得了物品：#R家传剑")                    
		  EndQuestEvent(sceneId)                                        
		  DispatchQuestTips(sceneId,selfId) 
	end    
	if  GetZhiye( sceneId, selfId) ==2   then
		AddItem( sceneId,10031001, 1 )
					BeginQuestEvent(sceneId)                                      
		  AddQuestText(sceneId,"你获得了物品：#R家传弓")                    
		  EndQuestEvent(sceneId)                                        
		  DispatchQuestTips(sceneId,selfId) 
	end    
	if  GetZhiye( sceneId, selfId) ==3   then
		AddItem( sceneId,10041001, 1 )
					BeginQuestEvent(sceneId)                                      
		  AddQuestText(sceneId,"你获得了物品：#R家传枪")                    
		  EndQuestEvent(sceneId)                                        
		  DispatchQuestTips(sceneId,selfId) 
	end    
	if  GetZhiye( sceneId, selfId) ==4   then
		AddItem( sceneId,10051001, 1 ) 
					BeginQuestEvent(sceneId)                                      
		  AddQuestText(sceneId,"你获得了物品：#R家传杖")                    
		  EndQuestEvent(sceneId)                                        
		  DispatchQuestTips(sceneId,selfId) 
	end    
	if  GetZhiye( sceneId, selfId) ==5   then
		AddItem( sceneId,10061001, 1 )
					BeginQuestEvent(sceneId)                                      
		  AddQuestText(sceneId,"你获得了物品：#R家传槌")                    
		  EndQuestEvent(sceneId)                                        
		  DispatchQuestTips(sceneId,selfId) 
	end         
		local ret = EndAddItem(sceneId,selfId)                                 
	  if ret > 0 then                                                  
	    AddItemListToPlayer(sceneId,selfId) 
	  else                                                             
		  BeginQuestEvent(sceneId)                                      
		  AddQuestText(sceneId,"物品栏已满，请整理再来！")                    
		  EndQuestEvent(sceneId)                                        
		  DispatchQuestTips(sceneId,selfId)                      
	   end           	               
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301307_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


