--生长点
--MisDescBegin
x301462_g_GrowpointId = 134 --对应生长点ID
x301462_g_ItemIndex = 13011607 --对应收集物品的ID
x301462_g_BufIndex = 7600
x301462_g_GroupPoint	=	{ {type=10,id =134,target = "丹木"}}
--MisDescEnd

x301462_g_Growpointlevel = {
							{MissionId = 7006, level = 60,itmID =13011005,needItemCount = 5,collNum = 1},
							{MissionId = 7011, level = 75,itmID =13011602,needItemCount = 5,collNum = 1},
							{MissionId = 7012, level = 85,itmID =13011604,needItemCount = 5,collNum = 1},
							{MissionId = 7746, level = 95,itmID =13011605,needItemCount = 5,collNum = 1},
							{MissionId = 7747, level = 105,itmID =13011606,needItemCount = 5,collNum = 1},							
							{MissionId = 7780, level = 115,itmID =13011607,needItemCount = 5,collNum = 1},								
							{MissionId = 7013, level = 60,itmID =13011005,needItemCount = 5,collNum = 1},
							{MissionId = 7014, level = 75,itmID =13011602,needItemCount = 5,collNum = 1},
							{MissionId = 7015, level = 85,itmID =13011604,needItemCount = 5,collNum = 1},
							{MissionId = 7748, level = 95,itmID =13011605,needItemCount = 5,collNum = 1},
							{MissionId = 7749, level = 105,itmID =13011606,needItemCount = 5,collNum = 1},							
							{MissionId = 7781, level = 115,itmID =13011607,needItemCount = 5,collNum = 1},								
							{MissionId = 7698, level = 60,itmID =13011005,needItemCount = 5,collNum = 1},
							{MissionId = 7699, level = 75,itmID =13011602,needItemCount = 5,collNum = 1},
							{MissionId = 7700, level = 85,itmID =13011604,needItemCount = 5,collNum = 1},
							{MissionId = 7750, level = 95,itmID =13011605,needItemCount = 5,collNum = 1},
							{MissionId = 7751, level = 105,itmID =13011606,needItemCount = 5,collNum = 1},							
							{MissionId = 7782, level = 115,itmID =13011607,needItemCount = 5,collNum = 1},								
							{MissionId = 7701, level = 60,itmID =13011005,needItemCount = 5,collNum = 1},
							{MissionId = 7702, level = 75,itmID =13011602,needItemCount = 5,collNum = 1},
							{MissionId = 7703, level = 85,itmID =13011604,needItemCount = 5,collNum = 1},						
							{MissionId = 7752, level = 95,itmID =13011605,needItemCount = 5,collNum = 1},
							{MissionId = 7753, level = 105,itmID =13011606,needItemCount = 5,collNum = 1},	
							{MissionId = 7783, level = 115,itmID =13011607,needItemCount = 5,collNum = 1},						
		}                                                       

x301462_g_GrowpointPos = {
							 {posx1=176, posz1=216,posx2=38, posz2=131,posx3=205, posz3=175,--posx4 = 67.879761, posz4 = 92.065254,posx5 = 32.79665, posz5 = 204.992188,posx6 = 197.990417, posz6 = 97.425476,posx7 = 224.641403, posz7 = 104.538422,posx8 = 58.52943, posz8 = 82.746719,posx9 = 47.733585, posz9 = 74.672951,
							 },							
		}		

--生成函数开始************************************************************************
function 	x301462_OnCreate(sceneId,growPointType,x,y)
	
	local ItemBoxId = ItemBoxEnterScene(x, y, x301462_g_GrowpointId, sceneId, 0, x301462_g_ItemIndex)
	SetGrowPointObjID(sceneId,x301462_g_GrowpointId,x, y,ItemBoxId)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301462_OnOpen(sceneId,selfId,targetId)
	return x301462_OnOpenItemBox(sceneId, selfId, targetId, x301462_g_GrowpointId, x301462_g_ItemIndex)
	--return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox", sceneId, selfId, targetId, x301462_g_GrowpointId, x301462_g_ItemIndex )
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301462_OnRecycle(sceneId,selfId,targetId)
	return   x301462_OnGuildRecycle( sceneId, selfId, targetId, x301462_g_GrowpointId, x301462_g_ItemIndex )
	--return CallScriptFunction( MISSION_SCRIPT, "OnRecycle", sceneId, selfId, targetId, x301462_g_GrowpointId, x301462_g_ItemIndex )
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301462_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function x301462_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, -1 )
end


--**********************************************************************
--采集任务
--打开ItemBox
function x301462_GetMissionDesc(sceneId, selfId)
	for i,itm in x301462_g_Growpointlevel do
		if IsHaveQuestNM(sceneId, selfId,itm.MissionId ) > 0 then
			return itm
		end
	end
	return nil
end

function x301462_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	local missionDesc = x301462_GetMissionDesc(sceneId, selfId)
	if missionDesc == nil then
		Msg2Player(sceneId,selfId,"很抱歉，您没有【帮会】帮会图腾任务，无法采集",8,2)
		Msg2Player(sceneId,selfId,"很抱歉，您没有【帮会】帮会图腾任务，无法采集",8,3)
		return 1
	end
	local MissionId = missionDesc.MissionId
	local needItemCount = missionDesc.needItemCount
	local collNum = missionDesc.collNum 
	local needItemID = missionDesc.itmID
	local itemCountNow = GetItemCount( sceneId, selfId, needItemID )
		if itemCountNow >= needItemCount then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"物品已经收集齐全")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 1
	end
	if MissionId == -1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您没有任务");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,"很抱歉，您没有任务",8,2)
		return 0 --没有这个任务
	end
	
	if IsQuestHaveDoneNM( sceneId, selfId, missionDesc.MissionId ) > 0 then --任务已经完成
		return 1
	end
	
	local level = GetLevel(sceneId,selfId)
	if sceneId == 23 and level > 105 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"您的等级过高")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"很抱歉，您的等级高于本地图，请去更高等级的地图完成任务。",8,2)
		return 1
	end
	if sceneId == 24 and level > 110 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"您的等级过高")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"很抱歉，您的等级高于本地图，请去更高等级的地图完成任务。",8,2)
		return 1
	end
	if sceneId == 25 and level > 115 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"您的等级过高")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"很抱歉，您的等级高于本地图，请去更高等级的地图完成任务。",8,2)
		return 1
	end
end

function x301462_OnGuildRecycle( sceneId, selfId, targetId, gpType, needItemID )
	local missionDesc = x301462_GetMissionDesc(sceneId, selfId)
	if missionDesc == nil then
		return 1
	end
	local MissionId = missionDesc.MissionId
	local needItemCount = missionDesc.needItemCount
	local collNum = missionDesc.collNum 
	local needItemID = missionDesc.itmID
	local level = GetLevel(sceneId,selfId)
	if level <=  115 then
		if sceneId == 24 then
			 local nRet = random(1,80000)
			 if nRet <= 10 then --采集点全部变怪
					local name = GetName(sceneId,selfId)
					local msg1 = "由于"..name.."在收集图腾时触发了天变，耶路撒冷附近出现天龙之魂"
					LuaAllScenceM2Wrold(sceneId, msg1, CHAT_PLANE_SCROLL, 1)
					LuaAllScenceM2Wrold(sceneId, msg1, CHAT_LEFTDOWN, 1)
					LuaAllScenceM2Wrold(sceneId, msg1, CHAT_MAIN_RIGHTDOWN, 1)
					CreateMonster(sceneId,3059,x301462_g_GrowpointPos[1].posx1, x301462_g_GrowpointPos[1].posz1, 16,-1, -1,13079463,21,1000 * 60 *15 )
					CreateMonster(sceneId,3059,x301462_g_GrowpointPos[1].posx2, x301462_g_GrowpointPos[1].posz2, 16,-1, -1,13079463,21,1000 * 60 *15 )
					CreateMonster(sceneId,3059,x301462_g_GrowpointPos[1].posx3, x301462_g_GrowpointPos[1].posz3, 16,-1, -1,13079463,21,1000 * 60 *15 )
					-- CreateMonster(sceneId,3059,x301462_g_GrowpointPos[1].posx4, x301462_g_GrowpointPos[1].posz4, 16,50, -1,13079463,21,1000 * 60 *5 )
					-- CreateMonster(sceneId,3059,x301462_g_GrowpointPos[1].posx5, x301462_g_GrowpointPos[1].posz5, 16,50, -1,13079463,21,1000 * 60 *5 )
					-- CreateMonster(sceneId,3059,x301462_g_GrowpointPos[1].posx6, x301462_g_GrowpointPos[1].posz6, 16,50, -1,13079463,21,1000 * 60 *5 )
					-- CreateMonster(sceneId,3059,x301462_g_GrowpointPos[1].posx7, x301462_g_GrowpointPos[1].posz7, 16,50, -1,13079463,21,1000 * 60 *5 )
					-- CreateMonster(sceneId,3059,x301462_g_GrowpointPos[1].posx8, x301462_g_GrowpointPos[1].posz8, 16,50, -1,13079463,21,1000 * 60 *5 )
					-- CreateMonster(sceneId,3059,x301462_g_GrowpointPos[1].posx9, x301462_g_GrowpointPos[1].posz9, 16,50, -1,13079463,21,1000 * 60 *5 )
				return 1
			end                                                                                   
		end
	--决定一次采集多少
		local itemCountNow = GetItemCount( sceneId, selfId, needItemID )
		local itemAdd = needItemCount - itemCountNow
		itemAdd = random(itemAdd)
		if itemAdd < collNum then
			itemAdd = collNum
		end

		BeginAddItem( sceneId )
		AddItem( sceneId, needItemID, itemAdd )
		local ret = EndAddItem( sceneId, selfId )
		if ret > 0 then
			 AddItemListToPlayer(sceneId,selfId)
			 return 1
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"无法得到采集物品，请整理背包！")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return 0
		end
	end
    return 0
end

--**********************************************************************

