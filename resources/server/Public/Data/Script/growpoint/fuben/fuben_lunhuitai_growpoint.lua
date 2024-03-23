--生长点

x301028_g_GrowpointId = 548 		--对应生长点ID
x301028_g_MinLevel = 20   	

x301028_g_MissionName=""

x301028_g_ItemIndex = -1
--x301028_g_ItemIndex = 
x700028_g_HasOpen = {}		
--0-39，40-59，60-79，80-110
x301028_g_LevelItemTab           	= 	{  	--等级对应的经验倍数
											{ level =39,
												items = {
															{itemId = 11000200, count = 6},
															{itemId = 11050001, count = 6},
														},
													
											},
											{ level =59,
												items = {
															{itemId = 11000201, count = 6},
															{itemId = 11050002, count = 6},
														},
											},
											{ level =79,
												items = {
															{itemId = 11000202, count = 6},
															{itemId = 11050003, count = 6},
														},
											},
											{ level =99,
												items = {
															{itemId = 11000203, count = 6},
															{itemId = 11050004, count = 6},
														},
										  },
											{ level =119,
												items = {
															{itemId = 11000203, count = 6},
															{itemId = 11050005, count = 6},
														},
											},
											{ level =200,
												items = {
															{itemId = 11000203, count = 6},
															{itemId = 11050005, count = 6},
														},
											},
										}	
										

function x301028_HaveAccepted(sceneId, selfId)
	
end



--生成函数开始************************************************************************
function 	x301028_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301028_g_GrowpointId, sceneId, 0, x301028_g_ItemIndex)
	SetGrowPointObjID(sceneId,x301028_g_GrowpointId,x, y,ItemBoxId)
	
	x700028_g_HasOpen[sceneId] = {}
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301028_OnOpen(sceneId,selfId,targetId)
		return x301028_OnOpenItemBox(sceneId, selfId, targetId, x301028_g_GrowpointId, x301028_g_ItemIndex)	
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301028_OnRecycle(sceneId,selfId,targetId)
	return   x301028_OnGuildRecycle( sceneId, selfId, targetId, x301028_g_GrowpointId, x301028_g_ItemIndex )
	
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301028_OnProcOver(sceneId,selfId,targetId)
	local myGuid = GetPlayerGUID( sceneId,selfId )
	myGuid = format("%u", myGuid)
	local t = 0
	
	
	
	
	local humancount = GetFuben_PlayerCount(sceneId)
  	for i=0, 6-1 do
        local paramidx = 248 + i
        local nGUID = GetFubenData_Param(sceneId, paramidx  )
        nGUID = format("%u", nGUID)	
    		if nGUID == myGuid then
    			t = i
    			break
		    end
       			
        
    end
    
    
	local level = GetLevel(sceneId, selfId)
	BeginAddItem( sceneId )
	
	for i,item in x301028_g_LevelItemTab do
		if level <= item.level then
			for j,s in item.items do
				AddItem( sceneId, s.itemId, s.count )	
				--print( s.itemId, s.count)
			end
			
			break
			
		end
	end
	local ret = EndAddItem( sceneId, selfId )
	--print( "ret------------>",ret,t)
	if ret > 0 then
		x700028_g_HasOpen[sceneId][myGuid] = 1
		AddItemListToPlayer(sceneId,selfId) 
		SetFubenData_Param(sceneId, 200+t,1);
		--print("sssssssssssssssss")
	else
		Msg2Player(sceneId, selfId, "背包已满或空间不够，请清理背包。", 0, 2)
		return 1
		
	end
	
	
-- 	local humancount = GetFuben_PlayerCount(sceneId)
--  	for i=0, humancount do
--        local paramidx = 248 + i
--        local nGUID = GetFubenData_Param(sceneId, paramidx  )
--    		--print(nGUID, paramidx,humancount,i)
--        if nGUID == myGuid then
--		    SetFubenData_Param(sceneId, 200+i,1);
--      		return
--        end
--    end

	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301028_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	--print("x301028_OpenCheck")
	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end


--**********************************************************************
--采集任务
--打开ItemBox
function x301028_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )

	if GetBagSpace(sceneId, selfId) <= 0 then
		Msg2Player(sceneId, selfId, "背包已满，请清理背包。", 0, 2)
		return 1
	end
	local myGuid = GetPlayerGUID( sceneId,selfId )
	myGuid = format("%u", myGuid)
 	
 	if x700028_g_HasOpen[sceneId][myGuid] ~= nil and x700028_g_HasOpen[sceneId][myGuid] == 1 then	
 		str = "您只能采集一次！"
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		
		return 1
	end
	
	return 0
end

function x301028_ShowTipsToAll(sceneId, str)

	local nHumanCount = GetScenePlayerCount( sceneId)
    if nHumanCount > 0 then
        for i = 0, nHumanCount do
            local objId = GetScenePlayerObjId( sceneId,i)
            if objId >= 0 then
                Msg2Player(sceneId, objId, str, 0, 2)
            end
        end
    end
end

--回收
function x301028_OnGuildRecycle( sceneId, selfId, targetId, gpType, needItemID )

	
--	local level = GetLevel(sceneId, selfId)
--	BeginAddItem( sceneId )
--	for i,item in x301028_g_LevelItemTab do
--		if level <= item.level then
--			for j,s in item.items do
--				AddItem( sceneId, s.itemId, s.count )	
--				print( s.itemId, s.count)
--			end
--			break
--		end
--	end
--	local ret = EndAddItem( sceneId, selfId )
--	print( "ret",ret)
--	if ret > 0 then
--		AddItemListToPlayer(sceneId,selfId) 
--	else
--		Msg2Player(sceneId, selfId, "背包已满或空间不够，请清理背包。", 0, 2)
--		return 1
--		
--	end
	SetGrowPointIntervalContainer(sceneId, x301028_g_GrowpointId, 1)
	
	return 0
	
end