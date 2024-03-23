--生长点

x310013_g_GrowpointId = 402 		--对应生长点ID
x310013_g_MinLevel = 20   	
x310013_g_ItemIndex =  12030051


x310013_g_MissionList = {8022,8023,8024,8025,8026,8027,8028,8029,8030,8031,8032,8033,8034,8035,8036,8037,8038,8039,8040, 8041, 8042, 8043, 8044, 8045}
x310013_g_ItemNum = 3
x310013_g_ItemList = {12030051, 12030052, 12030053}
x310013_g_MaterialNum = 8
x310013_g_MaterialList ={11020001, 11020002, 11020006, 11020007, 11030001, 11030003, 11030401, 11030402}

function x310013_HaveAccepted(sceneId, selfId)

	for i, item in x310013_g_MissionList do
		if IsHaveQuestNM( sceneId, selfId, item ) > 0 then
			return 1
		end
	end
	return -1
end

function x310013_RandItem(sceneId, selfId)
	local kindIndex = random(1, 3);
	
	if kindIndex == 1 then
		local itemIndex = random(1, x310013_g_ItemNum)
		return x310013_g_ItemList[itemIndex]
	end

	if kindIndex == 2 then
		local materialIndex = random(1, x310013_g_MaterialNum)
		return x310013_g_MaterialList[materialIndex]
	end

    return -1

end


--生成函数开始************************************************************************
function 	x310013_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x310013_g_GrowpointId, sceneId, 0, x310013_g_ItemIndex)
	SetGrowPointObjID(sceneId,x310013_g_GrowpointId,x, y,ItemBoxId)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x310013_OnOpen(sceneId,selfId,targetId)
		--PrintStr("x310013_OnOpen")
    return x310013_OnOpenItemBox(sceneId, selfId, targetId, x310013_g_GrowpointId, x310013_g_ItemIndex)	
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x310013_OnRecycle(sceneId,selfId,targetId)
	return   x310013_OnGuildRecycle( sceneId, selfId, targetId, x310013_g_GrowpointId, x310013_g_ItemIndex )
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x310013_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x310013_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end


--**********************************************************************
--采集任务
--打开ItemBox
function x310013_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	
	if x310013_HaveAccepted(sceneId, selfId) < 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"您没有任务【个人】天降宝箱，请您关注系统公告。")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return -31
	end
	    
	if GetLevel(sceneId, selfId) < x310013_g_MinLevel then  		--等级不够 
		return -31
	end

	return 0
end

--回收
function x310013_OnGuildRecycle( sceneId, selfId, targetId, gpType, needItemID )
  	
	--决定一次采集多少
	local itemAdd = 1
	needItemID = x310013_RandItem(sceneId, selfId)

	if needItemID == nil or needItemID < 0 then 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"箱子里什么也没有")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		return 1
	end

	BeginAddItem( sceneId )
	AddItem( sceneId, needItemID, itemAdd )
	local ret = EndAddItem( sceneId, selfId )
	if ret > 0 then
		--SetGrowPointCurrSeedNum( sceneId, gpType, seedNum-1 )
		AddItemListToPlayer(sceneId,selfId)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,format("#Y获得物品#G#{_ITEM%d}#Y！", needItemID))
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		
		return 1
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"背包已满，请整理背包！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end
	
end