--生长点

x300627_g_GrowpointId = 128 		--对应生长点ID
x300627_g_MinLevel = 40   	
x300627_g_ItemIndex = 13011006 	--对应收集物品的ID
x300627_g_ItemNum = 1	     	--敌国抢粮时所需要的物品个数
		--敦煌兵器库 
x300627_g_MissionId = 7034

x300627_g_CountryDunhuang = 376 --四个国家的场景id
x300627_g_CountryLoulan = 76
x300627_g_CountryKunlun = 276
x300627_g_CountryLaiyin = 176

x300627_g_MissionId1 = 7661
x300627_g_MissionId2 = 7652
x300627_g_MissionId3 = 7658
x300627_g_MissionId4 = 7655

x300627_g_MissionId5 = 7673
x300627_g_MissionId6 = 7664
x300627_g_MissionId7 = 7670
x300627_g_MissionId8 = 7667

x300627_g_MissionId9 = 7580
x300627_g_MissionId10 = 7562
x300627_g_MissionId11 = 7574
x300627_g_MissionId12 = 7568

x300627_g_MissionId13 = 7685
x300627_g_MissionId14 = 7676
x300627_g_MissionId15 = 7682
x300627_g_MissionId16 = 7679

--生成函数开始************************************************************************
function 	x300627_OnCreate(sceneId,growPointType,x,y)
	SetGrowPointCurrSeedNum( sceneId, growPointType, 201 )
	local ItemBoxId = ItemBoxEnterScene(x, y, x300627_g_GrowpointId, sceneId, 0, x300627_g_ItemIndex)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x300627_OnOpen(sceneId,selfId,targetId)
	
    return x300627_OnOpenItemBox(sceneId, selfId, targetId, x300627_g_GrowpointId, x300627_g_ItemIndex)	
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x300627_OnRecycle(sceneId,selfId,targetId)
	return   x300627_OnGuildRecycle( sceneId, selfId, targetId, x300627_g_GrowpointId, x300627_g_ItemIndex )
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x300627_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x300627_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end


--**********************************************************************
--采集任务
--打开ItemBox
function x300627_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	local MissionId = -1
	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId1 ) > 0 then
		MissionId = x300627_g_MissionId1
	end	

	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId2 ) > 0 then
		MissionId = x300627_g_MissionId2
	end	

	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId3 ) > 0 then
		MissionId = x300627_g_MissionId3
	end	
	
	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId4 ) > 0 then
		MissionId = x300627_g_MissionId4
	end	
	
	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId5 ) > 0 then
		MissionId = x300627_g_MissionId5
	end	
	
	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId6 ) > 0 then
		MissionId = x300627_g_MissionId6
	end	
	
	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId7 ) > 0 then
		MissionId = x300627_g_MissionId7
	end	
	
	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId8 ) > 0 then
		MissionId = x300627_g_MissionId8
	end	
	
	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId9 ) > 0 then
		MissionId = x300627_g_MissionId9
	end	
	
	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId10 ) > 0 then
		MissionId = x300627_g_MissionId10
	end	
	
	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId11 ) > 0 then
		MissionId = x300627_g_MissionId11
	end	
	
	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId12 ) > 0 then
		MissionId = x300627_g_MissionId12
	end	
	
	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId13 ) > 0 then
		MissionId = x300627_g_MissionId13
	end	
	
	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId14 ) > 0 then
		MissionId = x300627_g_MissionId14
	end	
	
	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId15 ) > 0 then
		MissionId = x300627_g_MissionId15
	end	
	
	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId16 ) > 0 then
		MissionId = x300627_g_MissionId16
	end	

	if MissionId == -1 then
		return 1
	end

	if x300627_CountryCheck( sceneId, selfId, MissionId ) < 0 then
		return 1
	end
	
	if GetItemCount( sceneId, selfId, x300627_g_ItemIndex ) > 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"您已经获得情报了,赶快去回复任务吧！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"您已经获得情报了,赶快去回复任务吧！",8,2)
		
		return 1
	end
	 
	--local misIndex = GetQuestIndexByID( sceneId, selfId, x300627_g_MissionId )
	--local GetQuestParam(sceneId, selfId,misIndex,7) == 1 then         
		--任务完成不能集
		--return 1
	--end     

	if GetLevel(sceneId, selfId) < x300627_g_MinLevel then  		--等级不够 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"您还没到45级")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 1
	end

	return 0
end

--回收
function x300627_OnGuildRecycle( sceneId, selfId, targetId, gpType, needItemID )
  	
	local MissionId = -1
	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId1 ) > 0 then
		MissionId = x300627_g_MissionId1
	end	

	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId2 ) > 0 then
		MissionId = x300627_g_MissionId2
	end	

	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId3 ) > 0 then
		MissionId = x300627_g_MissionId3
	end	

	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId4 ) > 0 then
		MissionId = x300627_g_MissionId4
	end	
	
	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId5 ) > 0 then
		MissionId = x300627_g_MissionId5
	end	
	
	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId6 ) > 0 then
		MissionId = x300627_g_MissionId6
	end	
	
	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId7 ) > 0 then
		MissionId = x300627_g_MissionId7
	end	
	
	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId8 ) > 0 then
		MissionId = x300627_g_MissionId8
	end	
	
	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId9 ) > 0 then
		MissionId = x300627_g_MissionId9
	end	
	
	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId10 ) > 0 then
		MissionId = x300627_g_MissionId10
	end	
	
	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId11 ) > 0 then
		MissionId = x300627_g_MissionId11
	end	
	
	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId12 ) > 0 then
		MissionId = x300627_g_MissionId12
	end	
	
	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId13 ) > 0 then
		MissionId = x300627_g_MissionId13
	end	
	
	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId14 ) > 0 then
		MissionId = x300627_g_MissionId14
	end	
	
	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId15 ) > 0 then
		MissionId = x300627_g_MissionId15
	end	
	
	if IsHaveQuestNM( sceneId, selfId, x300627_g_MissionId16 ) > 0 then
		MissionId = x300627_g_MissionId16
	end	
	


	if MissionId == -1 then
		return 1
	end

	local seedNum = GetGrowPointCurrSeedNum(sceneId, gpType)
		
	if seedNum <= 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"密报已经被洗劫一空")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end

  	local itemCountNow = GetItemCount( sceneId, selfId, needItemID )
	if itemCountNow >= x300627_g_ItemNum then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"已经获得密报了，快去交吧")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end


	--决定一次采集多少
	local itemAdd = 1

	BeginAddItem( sceneId )
	AddItem( sceneId, needItemID, itemAdd )
	local ret = EndAddItem( sceneId, selfId )
	if ret > 0 then
		--SetGrowPointCurrSeedNum( sceneId, gpType, seedNum-1 )
		AddItemListToPlayer(sceneId,selfId)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"您获得了密报：1/1")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		CallScriptFunction( 300733, "OnGetTargetItem", sceneId, selfId,MissionId )
		return 1
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"无法得到密报，请整理道具栏！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end
	
end

function x300627_CountryCheck( sceneId, selfId, MissionId )
	if MissionId == x300627_g_MissionId1 then
		if sceneId == x300627_g_CountryDunhuang then
			return 1
		end
	elseif MissionId == x300627_g_MissionId2 then
		if sceneId == x300627_g_CountryLoulan then
			return 1
		end
	elseif MissionId == x300627_g_MissionId3 then
		if sceneId == x300627_g_CountryKunlun then
			return 1
		end
	elseif MissionId == x300627_g_MissionId4 then
		if sceneId == x300627_g_CountryLaiyin then
			return 1
		end
	end
	
	if MissionId == x300627_g_MissionId5 then
		if sceneId == x300627_g_CountryDunhuang then
			return 1
		end
	elseif MissionId == x300627_g_MissionId6 then
		if sceneId == x300627_g_CountryLoulan then
			return 1
		end
	elseif MissionId == x300627_g_MissionId7 then
		if sceneId == x300627_g_CountryKunlun then
			return 1
		end
	elseif MissionId == x300627_g_MissionId8 then
		if sceneId == x300627_g_CountryLaiyin then
			return 1
		end
	end
	
	if MissionId == x300627_g_MissionId9 then
		if sceneId == x300627_g_CountryDunhuang then
			return 1
		end
	elseif MissionId == x300627_g_MissionId10 then
		if sceneId == x300627_g_CountryLoulan then
			return 1
		end
	elseif MissionId == x300627_g_MissionId11 then
		if sceneId == x300627_g_CountryKunlun then
			return 1
		end
	elseif MissionId == x300627_g_MissionId12 then
		if sceneId == x300627_g_CountryLaiyin then
			return 1
		end
	end
	
	if MissionId == x300627_g_MissionId13 then
		if sceneId == x300627_g_CountryDunhuang then
			return 1
		end
	elseif MissionId == x300627_g_MissionId14 then
		if sceneId == x300627_g_CountryLoulan then
			return 1
		end
	elseif MissionId == x300627_g_MissionId15 then
		if sceneId == x300627_g_CountryKunlun then
			return 1
		end
	elseif MissionId == x300627_g_MissionId16 then
		if sceneId == x300627_g_CountryLaiyin then
			return 1
		end
	end
	return -1
end

--**********************************************************************

