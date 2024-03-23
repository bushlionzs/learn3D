--生长点
--MisDescBegin
x300650_g_GrowpointId = 101 --对应生长点ID
x300650_g_ItemIndex = 13011005 --对应收集物品的ID
x300650_g_BufIndex = 7631
x300650_g_GroupPoint	=	{ {type=10,id =101,target = "黑木"}}
--MisDescEnd

x300650_g_GrowpointPos = {
							{posx1=69, posz1=88,posx2=10, posz2=16,posx3=84, posz3=61,posx4 = 84, posz4 = 61,posx5 = 84, posz5 = 61,},
							{posx1=88, posz1=31,posx2=14, posz2=97,posx3=72, posz3=106,posx4 = 84, posz4 = 61,posx5 = 84, posz5 = 61,},
							{posx1=84, posz1=61,posx2=21, posz2=24,posx3=29, posz3=107,posx4 = 44, posz4 = 68,posx5 = 45, posz5 = 40,},							
		}

--生成函数开始************************************************************************
function 	x300650_OnCreate(sceneId,growPointType,x,y)
	
	local ItemBoxId = ItemBoxEnterScene(x, y, x300650_g_GrowpointId, sceneId, 0, x300650_g_ItemIndex)
	SetGrowPointObjID(sceneId,x300650_g_GrowpointId,x, y,ItemBoxId)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x300650_OnOpen(sceneId,selfId,targetId)
	return x300650_OnOpenItemBox(sceneId, selfId, targetId, x300650_g_GrowpointId, x300650_g_ItemIndex)
	--return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox", sceneId, selfId, targetId, x300650_g_GrowpointId, x300650_g_ItemIndex )
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x300650_OnRecycle(sceneId,selfId,targetId)
	return   x300650_OnGuildRecycle( sceneId, selfId, targetId, x300650_g_GrowpointId, x300650_g_ItemIndex )
	--return CallScriptFunction( MISSION_SCRIPT, "OnRecycle", sceneId, selfId, targetId, x300650_g_GrowpointId, x300650_g_ItemIndex )
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x300650_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x300650_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, -1 )
end


--**********************************************************************
--采集任务
--打开ItemBox
function x300650_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )

	local MissionId, needItemCount, collNum = GetItemIdInItemBoxNM( sceneId, selfId, targetId, gpType, needItemID )
	if MissionId == -1 then
		return  --没有这个任务
	end

	--如果该任务已经完成直接退出
	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --任务已经完成
		return 1
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没这个任务直接退出
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"您没有这个任务")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 1
	end
	local level = GetLevel(sceneId,selfId)
	if level > 60 then
	return 1
	end

	local itemCountNow = GetItemCount( sceneId, selfId, needItemID )
	if itemCountNow >= needItemCount then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"物品已经收集齐全")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 1
	end

	return 0
end

--回收
function x300650_OnGuildRecycle( sceneId, selfId, targetId, gpType, needItemID )

	local MissionId, needItemCount, collNum = GetItemIdInItemBoxNM( sceneId, selfId, targetId, gpType, needItemID )
	if MissionId == -1 then
		return 0 --没有这个任务
	end

	--如果该任务已经完成直接退出
	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --任务已经完成
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没这个任务直接退出
		return 0
	end

	local itemCountNow = GetItemCount( sceneId, selfId, needItemID )
	if itemCountNow >= needItemCount then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"物品已经收集齐全")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end

	--随机触发的事件
	local nRet = random(1,1160)   --采集点变怪、采集点全部消失、变经验、BUF、采集点全部变怪     10、10+5、15+50、65+50、115+1

	if nRet <= 10 then
		 --采集点消失并原地刷出一只怪
		local x = GetItemBoxWorldPosX(sceneId,targetId)
		local z = GetItemBoxWorldPosZ(sceneId,targetId)
   		CreateMonster(sceneId,9562, x, z, 16,50, -1,13079463,21,1000 * 60 *3 )
		BeginQuestEvent(sceneId);AddQuestText( sceneId, "黑木变成怪物对你进行攻击");EndQuestEvent( sceneId );DispatchQuestTips( sceneId, selfId )
		return 1
	-- elseif nRet <= 15 then
	    --场景内采集点全部消失
		-- local name = GetName(sceneId,selfId)
	    -- LuaThisScenceM2Wrold(sceneId,"由于"..name.."在采集中触发了地变，所有黑木消失",2,1)
		-- RecycleGrowPointByType(sceneId,x300650_g_GrowpointId,1000 * 60 *3)
	    -- return 0
	elseif nRet <= 65 then
  		--采集点消失并获得经验
        AddExp(sceneId, selfId,10000)
		BeginQuestEvent(sceneId);AddQuestText( sceneId, "黑木逃走，得到10000点经验");EndQuestEvent( sceneId );DispatchQuestTips( sceneId, selfId )
	    return 1
 	elseif nRet <= 115 then
        --采集点消失并获得BUF
		local Ret = SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x300650_g_BufIndex, 0);
        SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x300650_g_BufIndex, 0);
		BeginQuestEvent(sceneId);AddQuestText( sceneId, "黑木逃走，给你留下了点好处");EndQuestEvent( sceneId );DispatchQuestTips( sceneId, selfId )
 	    return 1
   	-- elseif nRet <= 116 then
 	    --集点全部变怪
		-- RecycleGrowPointByType(sceneId,x300650_g_GrowpointId,1000 * 60 *3)
	    -- local name = GetName(sceneId,selfId)
	    -- LuaThisScenceM2Wrold(sceneId,"由于"..name.."在采集中触发了天灾，所有黑木消失变成怪物",2,1)
			-- if sceneId == 4 then
				-- CreateMonster(sceneId,9562,x300650_g_GrowpointPos[1].posx1, x300650_g_GrowpointPos[1].posz1, 16,50, -1,13079463,21,1000 * 60 *5 )
				-- CreateMonster(sceneId,9562,x300650_g_GrowpointPos[1].posx2, x300650_g_GrowpointPos[1].posz2, 16,50, -1,13079463,21,1000 * 60 *5 )				
			-- elseif sceneId == 5 then
				-- CreateMonster(sceneId,9562,x300650_g_GrowpointPos[2].posx1, x300650_g_GrowpointPos[2].posz1, 16,50, -1,13079463,21,1000 * 60 *5 )
				-- CreateMonster(sceneId,9562,x300650_g_GrowpointPos[2].posx2, x300650_g_GrowpointPos[2].posz2, 16,50, -1,13079463,21,1000 * 60 *5 )				
				-- CreateMonster(sceneId,9562,x300650_g_GrowpointPos[2].posx3, x300650_g_GrowpointPos[2].posz3, 16,50, -1,13079463,21,1000 * 60 *1 )					
			-- elseif sceneId == 6 then
				-- CreateMonster(sceneId,9562,x300650_g_GrowpointPos[3].posx1, x300650_g_GrowpointPos[3].posz1, 16,50, -1,13079463,21,1000 * 60 *5 )
				-- CreateMonster(sceneId,9562,x300650_g_GrowpointPos[3].posx2, x300650_g_GrowpointPos[3].posz2, 16,50, -1,13079463,21,1000 * 60 *5 )				
				-- CreateMonster(sceneId,9562,x300650_g_GrowpointPos[3].posx3, x300650_g_GrowpointPos[3].posz3, 16,50, -1,13079463,21,1000 * 60 *5 )								
				-- CreateMonster(sceneId,9562,x300650_g_GrowpointPos[3].posx4, x300650_g_GrowpointPos[3].posz4, 16,50, -1,13079463,21,1000 * 60 *5 )				
				-- CreateMonster(sceneId,9562,x300650_g_GrowpointPos[3].posx5, x300650_g_GrowpointPos[3].posz5, 16,50, -1,13079463,21,1000 * 60 *5 )								
			-- end
 	    -- return 0
	end

	--决定一次采集多少
	local itemAdd = needItemCount - itemCountNow
	if collNum == -1 then
		itemAdd = 1
	else
		if itemAdd > collNum then
			itemAdd = collNum
		end
	end
	if itemAdd > 1 then
		itemAdd = random(itemAdd)
		if itemAdd == 0 then
			itemAdd = 1
		end
	end

	BeginAddItem( sceneId )
	AddItem( sceneId, needItemID, itemAdd )
	local ret = EndAddItem( sceneId, selfId )
	if ret > 0 then
		AddItemListToPlayer(sceneId,selfId)
		return 1
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"无法得到采集物品，请整理道具栏！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end

end

--**********************************************************************

