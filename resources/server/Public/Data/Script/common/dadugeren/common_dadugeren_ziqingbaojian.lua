--***********************
--Const
--***********************
-------------------------

--MisDescBegin


x300573_g_MissionId 				= 	9330                     --任务ID
x300573_g_ScriptId 					= 	300573                  --脚本ID
x300573_g_MissionKind 				= 	1                       --任务类型
x300573_g_LevelLess					= 	40                      --场景开放等级  <=0 表示不限制


x300573_g_MissionName				= 	"【个人】紫青宝剑"
x300573_g_MissionName1				= 	"你可听说过紫青侠女？"
x300573_g_MissionTarget				= 	"按照#G紫青宝剑#W的指引，找到紫云的#G有缘人"
x300573_g_MissionInfo				= 	""
x300573_g_ContinueInfo				= 	""
x300573_g_MissionCompleted			= 	""
x300573_g_MissionHelp				=	""          --任务提示信息

--目标
x300573_g_ExtTarget					=	{ {type=20,n=1,target="【个人】紫青宝剑"}}

--奖励

x300573_g_ExpBonus					= 	0;--x300573_AddExpAward               	--奖励：经验
x300573_g_BonusItem					=	{}	--奖励：物品

x300573_g_BonusMoney1               = 	0
x300573_g_BonusMoney2               =   0
x300573_g_BonusMoney3               =   0

x300573_g_BonusChoiceItem           =   {}


--MisDescEnd



x300573_g_NpcCount =30
x300573_g_NpcList = {						
					 {id=139405,name = "有缘人", x=223, z=34},
           {id=139406,name = "有缘人", x=210, z=34},
           {id=139405,name = "有缘人", x=223, z=34},
           {id=139406,name = "有缘人", x=210, z=34},
           {id=139405,name = "有缘人", x=223, z=34},
           {id=139406,name = "有缘人", x=210, z=34},
           {id=139405,name = "有缘人", x=223, z=34},
           {id=139406,name = "有缘人", x=210, z=34},
           {id=139405,name = "有缘人", x=223, z=34},
           {id=139406,name = "有缘人", x=210, z=34},
           {id=139405,name = "有缘人", x=223, z=34},
           {id=139406,name = "有缘人", x=210, z=34},
           {id=139405,name = "有缘人", x=223, z=34},
           {id=139406,name = "有缘人", x=210, z=34},
           {id=139405,name = "有缘人", x=223, z=34},
           {id=139406,name = "有缘人", x=210, z=34},
           {id=139405,name = "有缘人", x=223, z=34},
           {id=139406,name = "有缘人", x=210, z=34},
           {id=139405,name = "有缘人", x=223, z=34},
           {id=139406,name = "有缘人", x=210, z=34},
           {id=139405,name = "有缘人", x=223, z=34},
           {id=139406,name = "有缘人", x=210, z=34},
           {id=139405,name = "有缘人", x=223, z=34},
           {id=139406,name = "有缘人", x=210, z=34},
           {id=139405,name = "有缘人", x=223, z=34},
           {id=139406,name = "有缘人", x=210, z=34},
           {id=139405,name = "有缘人", x=223, z=34},
           {id=139406,name = "有缘人", x=210, z=34},
           {id=139405,name = "有缘人", x=223, z=34},
           {id=139406,name = "有缘人", x=210, z=34}


					}

x300573_g_GameId	= 1011

x300573_g_TaskItemId = 13810110
x300573_g_ItemId        = 12030028


x300573_g_BonusChoiceItem2   = {
								{10019100,10077100,10238100,10208100,10268100,10248100,10258100,10278100},
								{10028100,10087100,10238110,10208110,10268110,10248110,10258110,10278110},
								{10038100,10097100,10238120,10208120,10268120,10248120,10258120,10278120},
								{10048100,10107100,10238130,10208130,10268130,10248130,10258130,10278130},
								{10058100,10117100,10238140,10208140,10268140,10248140,10258140,10278140},
								{10068100,10127100,10238150,10208150,10268150,10248150,10258150,10278150}
									
								}

-- 任务奖励物品列表
x300573_g_RewardTable       = {
                                { minLevel = 40, maxLevel = 60,  items = { { id = 11000201, cnt = 8 }, { id = 11050002, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 60, maxLevel = 80,  items = { { id = 11000202, cnt = 8 }, { id = 11050003, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 80, maxLevel = 999, items = { { id = 11000203, cnt = 8 }, { id = 11050004, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
}


function x300573_GetMissionId( sceneId, selfId )
	return x300573_g_MissionId
end

function x300573_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	local level = GetLevel( sceneId,selfId )
    if level < x300573_g_LevelLess then
       return
    end

	local myMissionId = x300573_GetMissionId( sceneId, selfId )
	
	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		AddQuestNumText(sceneId, myMissionId, x300573_g_MissionName,8,1);
	else
		--local state = GetQuestStateNM(sceneId, selfId, targetId, myMissionId);

		
		--AddQuestNumText(sceneId, myMissionId, x300573_g_MissionName,state,state);

	end


	
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300573_ProcEventEntry( sceneId, selfId, targetId, MissionId, nExt )
	
	if GetGameOpenById(x300573_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300573_g_MissionId) == 0 then
		x300573_ShowTips(sceneId, selfId, "此活动今天不开放，详情请到大都包打处听查询每日新鲜事")
		return
	end

	local myMissionId = x300573_GetMissionId( sceneId, selfId )	
	
	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId )>0 then
		if nExt==30 then
			x300573_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
			return
		end
	end
		
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		x300573_DispatchMissionInfo( sceneId, selfId, targetId, myMissionId, 0 )
	else
		
	end
end


function x300573_ProcAcceptCheck(sceneId, selfId, targetId, MissionId )
	
	if GetGameOpenById(x300573_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300573_g_MissionId) == 0 then
		
		return 0;
	end
	return 1;

end

function x300573_CheckRequest(sceneId, selfId)
	if GetGameOpenById(x300573_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300573_g_MissionId) == 0 then
		x300573_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0
	end
	local myMissionId = x300573_GetMissionId( sceneId, selfId )

	if GetLevel(sceneId, selfId) <x300573_g_LevelLess then
		x300573_ShowTips(sceneId, selfId, "你等级不足")
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) > 0 then
		x300573_ShowTips(sceneId, selfId, "你已经有这个任务，请先完成这个任务")
		return 0;
	end

    local today = GetDayOfYear()
    if GetQuestData(sceneId, selfId, MD_LVZHUANG50_DATE[1], MD_LVZHUANG50_DATE[2],MD_LVZHUANG50_DATE[3] ) == today then
        x300573_ShowTips(sceneId, selfId, "很抱歉，您今天已经做过此任务，不能再次领取")
        return 0
    end

    if GetQuestData( sceneId, selfId, MD_RICHANG_DAY[ 1], MD_RICHANG_DAY[ 2], MD_RICHANG_DAY[ 3] ) == today then
        if GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[ 1], MD_RICHANG_COUNT[ 2], MD_RICHANG_COUNT[ 3] ) >= 3 then
            Msg2Player( sceneId, selfId, "你不能再领取今天的日常任务了", 8, 3)
            return 0
        end
    else
        SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 0)
    end

	return 1;

end

function x300573_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
	
	
	if GetGameOpenById(x300573_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300573_g_MissionId) == 0 then
		x300573_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	if x300573_CheckRequest(sceneId, selfId)<=0 then
		
		return 0;
	end

	local myMissionId = x300573_GetMissionId( sceneId, selfId )

	--------------------------- add for Mission full check --------------
	local bFullMission = IsQuestFullNM(sceneId,selfId)
	
	if bFullMission>0 then
		x300573_ShowTips(sceneId, selfId, "任务已满，无法接受任务")
		return 0
	end
	---------------------------- add end -------------------------------

	--检查前置任务
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,myMissionId  )
	if FrontMissiontId1 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
			return 0
		end
	end
	if FrontMissiontId2 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
			return 0
		end
	end
	if FrontMissiontId3 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
			return 0
		end
	end

	local ret = AddQuest( sceneId, selfId, myMissionId, x300573_g_ScriptId, 0, 0, 0,1)-- 给玩家添加任务		
		
	if ret > 0 then
		
		
		local myMissionId = x300573_GetMissionId( sceneId, selfId )
		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

		BeginAddItem(sceneId)
			AddItem( sceneId, x300573_g_TaskItemId, 1 )
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
			
			AddItemListToPlayer(sceneId,selfId)
			
			
		else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"背包空间不足，无法获得任务物品，接任务失败")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)

			DelQuestNM( sceneId, selfId, myMissionId )
			return 0;	
		end

		local str = "您接受了任务："..x300573_g_MissionName;
		x300573_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)


		--SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )

		local nNpcType = random(1,x300573_g_NpcCount)

		SetQuestByIndex( sceneId, selfId, misIndex, 6, nNpcType )
        SetQuestByIndex( sceneId, selfId, misIndex, 1, 0)

		
		GamePlayScriptLog(sceneId, selfId, 811)
		return 1
	else
		
		x300573_ShowTips(sceneId, selfId, "接受任务错误")
	
	end


end



function x300573_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x300573_ProcQuestAbandon( sceneId, selfId, MissionId )

	local myMissionId = x300573_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	local ret = DelQuestNM( sceneId, selfId, myMissionId )

	if ret>0 then

		local str = "您放弃了任务:"..x300573_g_MissionName;
	    x300573_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)


		local n = GetItemCount( sceneId, selfId, x300573_g_TaskItemId );

	
		if n > 0 then
			DelItem(sceneId, selfId,x300573_g_TaskItemId,n)
			
		end

        local today = GetDayOfYear()
		SetQuestData(sceneId, selfId, MD_LVZHUANG50_DATE[1], MD_LVZHUANG50_DATE[2], MD_LVZHUANG50_DATE[3], today)
		if today == GetQuestData( sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2], MD_RICHANG_DAY[3] ) then
            local count = GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3] )
            if count < 3 then
                SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 1 + count)
            end
        else
            SetQuestData( sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2], MD_RICHANG_DAY[3], today)
            SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 1)
        end
	else
		x300573_ShowTips(sceneId, selfId, "放弃任务失败")
	end

	
end

function x300573_CheckSubmitNPC( sceneId,selfId,idScript,idMission,npcGUID )
	
	local myMissionId = x300573_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then	-- 如果没这个任务直接退出
		return 0
	end
	--送信任务
	for i, setitem in x300573_g_NpcList do
		if setitem.id == npcGUID then
			return 1
		end
	end
	
	
	--默认情况下，认为没有检查不通过
	return 0
	
end


function x300573_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	
	if GetGameOpenById(x300573_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300573_g_MissionId) == 0 then
		x300573_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	local myMissionId = x300573_GetMissionId( sceneId, selfId )
	
	if x300573_CheckSubmit(sceneId, selfId )>0 then
		local today = GetDayOfYear()
        local count = GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3] )
        if today == GetQuestData(sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2],MD_RICHANG_DAY[3] ) and count >= 3 then
            Msg2Player( sceneId, selfId, "今天的日常任务已经不能再交了，请明天再来", 8, 3)
            return 0
        end

		local nRet = x300573_GiveReward(sceneId,selfId,selectId)

		if nRet<=0 then
			return
		end
		local ret = DelQuestNM( sceneId, selfId, myMissionId )

		if ret>0 then
			CallScriptFunction( 270300, "OnSubmissionFinished", sceneId, selfId, x300573_g_MissionId)

			local n = GetItemCount( sceneId, selfId, x300573_g_TaskItemId );

	
			if n > 0 then
				DelItem(sceneId, selfId,x300573_g_TaskItemId,n)
				
			end

			local str = "您完成了任务:"..x300573_g_MissionName;
			x300573_ShowTips(sceneId, selfId, str)
			Msg2Player(sceneId,selfId,str,8,2)

            SetQuestData(sceneId, selfId, MD_LVZHUANG50_DATE[1], MD_LVZHUANG50_DATE[2], MD_LVZHUANG50_DATE[3], GetDayOfYear() )

			GamePlayScriptLog(sceneId, selfId, 812)
			
		else
			x300573_ShowTips(sceneId, selfId, "交任务失败")
		end
		
	end
end

function x300573_GiveReward(sceneId,selfId,selectRadioId)
	
	if GetGameOpenById(x300573_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300573_g_MissionId) == 0 then
		x300573_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	
    -- 检查玩家选择的奖励是不是可判定非绑定的
	local level = GetLevel( sceneId, selfId)
    local canBind = 0
    local count = 0
    local id = 0
    for i, item in x300573_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                if selectRadioId == iter.id then
                    if j <= 2 then
                        canBind = 1
                    end
                    count = iter.cnt
                    id = iter.id
                    break
                end
            end
            break
        end
    end

    -- 特殊情况处理，玩家在选择物品后升级跨越到下个奖励区时的处理
    if count == 0 then
        for i, item in x300573_g_RewardTable do
            for j, iter in item.items do
                if selectRadioId == iter.id then
                    if j <= 2 then
                        canBind = 1
                    end
                    count = iter.cnt
                    id = iter.id
                    break
                end
            end
        end
    end

    if id == 0 or count == 0 then
        return 0
    end

	BeginAddItem(sceneId)
    if IsHaveSpecificImpact( sceneId, selfId, 9011) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9012) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9013) == 1 then
        if canBind == 1 then
            AddItem( sceneId, id, count)
        else
            AddBindItem( sceneId, id, count)
        end
    else
		AddBindItem( sceneId, id, count)
    end
		
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		
		AddItemListToPlayer(sceneId,selfId)
		
		
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,format("您获得了物品：@itemid_%d",id))
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

        local myMissionId = x300573_GetMissionId( sceneId, selfId)
        local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId)
        local useCount = GetQuestParam( sceneId, selfId, misIndex, 1)
        if useCount <= 4 then
            BeginAddItem( sceneId)
            AddItem( sceneId, x300573_g_ItemId, 1)
            if EndAddItem( sceneId, selfId) == 1 then
                AddItemListToPlayer( sceneId, selfId)
                -- Msg2Player( sceneId, selfId, format( "你只查看不到四次就找到了，特奖励一个@item_%d。", 
                    -- x300573_g_ItemId), 8, 2)
            else
                Msg2Player( sceneId, selfId, "物品栏已满，无法获得额外奖励物品", 8, 3)
            end
        end

		return 1;
	else
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"背包空间不足，无法获得任务奖励物品，交任务失败")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0;	
	end
	
	
	
end



function x300573_CheckSubmit(sceneId, selfId )
	
	if GetGameOpenById(x300573_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300573_g_MissionId) == 0 then
		x300573_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	local myMissionId = x300573_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )
	

	if (bCompleted)<=0 then
		return 0
	end

	return 1;
end



---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x300573_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId, nExt )

	
	
	BeginQuestEvent(sceneId)

		
	
	AddQuestText(sceneId,"#Y"..x300573_g_MissionName)
	AddQuestText(sceneId,"\t这些天来，紫青宝剑一直在低鸣，莫非......\n\t#Y@myname#W，带上这把宝剑，帮我找到它指引的人吧。")
	AddQuestText( sceneId,"#Y任务目标:")
			
	AddQuestText( sceneId,x300573_g_MissionTarget)
	AddQuestText(sceneId," ")

	--1、经验
	local level = GetLevel(sceneId, selfId)
    for i, item in x300573_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end
	-- local nExpBonus = level*0;
	
	-- if nExpBonus > 0 then
		-- AddQuestExpBonus( sceneId, nExpBonus)
	-- end

	-- local ZhiYe= GetZhiye( sceneId, selfId)
	-- for i, item in x300573_g_BonusChoiceItem2[ZhiYe+1] do
		
		-- AddQuestRadioItemBonus(sceneId, item, 1)
		
	-- end

	EndQuestEvent()
	
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300573_g_ScriptId, MissionId,0);
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300573_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	local myMissionId = x300573_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300573_g_MissionName)
		AddQuestText(sceneId,"这紫青宝剑指引的有缘人，究竟是何人呢？")
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300573_g_ScriptId, MissionId,0);
	


end







---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300573_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	local myMissionId = x300573_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300573_g_MissionName)
		AddQuestText(sceneId,"\t#Y@myname#W，你说是这把宝剑指引你前来？这个......难道我竟然是那鼎鼎大名的紫青侠女的......")
	
	
	
	--1、经验
	local level = GetLevel(sceneId, selfId)
    for i, item in x300573_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end
	-- local nExpBonus = level*0;
	
	-- if nExpBonus > 0 then
		-- AddQuestExpBonus( sceneId, nExpBonus)
	-- end

	-- local ZhiYe= GetZhiye( sceneId, selfId)
	-- for i, item in x300573_g_BonusChoiceItem2[ZhiYe+1] do
		
		-- AddQuestRadioItemBonus(sceneId, item, 1)
		
	-- end
		
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300573_g_ScriptId, MissionId);

end







---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300573_QuestLogRefresh( sceneId, selfId, MissionId)
	local myMissionId = x300573_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then	-- 如果没这个任务直接退出
		return 0
	end
		
	BeginQuestEvent(sceneId)	
			
		
	AddQuestLogCustomText( sceneId,
							"",						-- 标题
							x300573_GetMissionName(sceneId,selfId),        -- 任务名字
							x300573_GetMissionTask(sceneId,selfId),		--任务目标
							x300573_GetReplyNpcId(sceneId,selfId),			--任务NPC
							x300573_GetMissionMethod(sceneId,selfId),               --任务攻略
							x300573_GetMissionText(sceneId,selfId),	--任务描述
							x300573_GetMissionHelp(sceneId,selfId)					--任务小提示
							)

	--1、经验
	local level = GetLevel(sceneId, selfId)
    for i, item in x300573_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end
	-- local nExpBonus = level*0;
	
	-- if nExpBonus > 0 then
		-- AddQuestExpBonus( sceneId, nExpBonus)
	-- end

	-- local ZhiYe= GetZhiye( sceneId, selfId)
	-- for i, item in x300573_g_BonusChoiceItem2[ZhiYe+1] do
		
		-- AddQuestRadioItemBonus(sceneId, item, 1)
		
	-- end

	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	

end

function x300573_GetMissionName(sceneId,selfId)
	

	return x300573_g_MissionName;
end

function x300573_GetMissionTask(sceneId,selfId)
	local myMissionId = x300573_GetMissionId( sceneId, selfId )

	

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nNpcIndex = GetQuestParam( sceneId, selfId, misIndex, 6 )

	
		
	return "  用#G紫青宝剑#W找到紫青侠女的#G"..x300573_g_NpcList[nNpcIndex].name;
end

function x300573_GetReplyNpcId(sceneId,selfId)
	local myMissionId = x300573_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nNpcIndex = GetQuestParam( sceneId, selfId, misIndex, 6 )

	return x300573_g_NpcList[nNpcIndex].name;
end

function x300573_GetMissionMethod(sceneId,selfId)
	return "\t紫青宝剑会指引你前去找到紫青侠女的有缘人，您可以#G右键#W点击使用#G紫青宝剑#W，根据宝剑给出的提示，慢慢寻找。"
end

function x300573_GetMissionText(sceneId,selfId)
	return "\t这些天来，紫青宝剑一直在低鸣，莫非......\n\t#Y@myname#W，带上这把宝剑，帮我找到它指引的人吧。"
end

function x300573_GetMissionHelp(sceneId,selfId)
	return "\t右键点击使用紫青宝剑，它会带你去找到紫青侠女的有缘人。"
end



function x300573_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300573_QuestLogRefresh( sceneId, selfId, MissionId );
end

--// system function start
function x300573_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	local myMissionId = x300573_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then	-- 如果没这个任务直接退出
		return 0
	end
	
	local myMissionId = x300573_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	
	local nNpcIndex = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	
	
	
	
		
	if npcGuid~=x300573_g_NpcList[nNpcIndex].id then
		return
		
	end

	

	SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
	AddQuestNumText(sceneId, x300573_g_MissionId, x300573_g_MissionName1,7,30);
	
end


function x300573_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end


function x300573_GetDirText(x,z,x1,z1)
	local strDir1 =""
	local strDir2 =""
	local strDir=""
	if x>x1 then
		strDir1 = "东"
	elseif x<x1 then
		strDir1 = "西"
	else
		if( z-z1<0) then
			strDir = "正北"
		else
			strDir = "正南"
		end

		return strDir
	end
	

	if z>z1 then
		strDir2 = "南"
	elseif z<z1 then
		strDir2 = "北"
	else
		if( x-x1<0) then
			strDir = "正西"
		else
			strDir = "正东"
		end

		return strDir
	end

	return strDir1..strDir2;


end

-----------------------------------------------------------------------------------------------
--定点使用物品任务
----------------------------------------------------------------------------------------------
function x300573_PositionUseItem( sceneId, selfId, BagIndex )
	

	local myMissionId = x300573_GetMissionId( sceneId, selfId )

	

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then	-- 如果没这个任务直接退出
		return 0
	end


	
	

	if(sceneId~=0) then  --如果不在大都
		x300573_ShowTips(sceneId, selfId, "在大都某个方向很远的地方")
		return
	end


	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nNpcIndex = GetQuestParam( sceneId, selfId, misIndex, 6 )
    local useCount = GetQuestParam( sceneId, selfId, misIndex, 1)
    SetQuestByIndex( sceneId, selfId, misIndex, 1, useCount + 1)

	local x = x300573_g_NpcList[nNpcIndex].x;
	local z = x300573_g_NpcList[nNpcIndex].z;

	

	local x1,z1 = GetWorldPos( sceneId, selfId )

	local strDir = 	x300573_GetDirText(x,z,x1,z1)

	strDir = "紫青宝剑低鸣着：在"..strDir.."方向,"
		
	
		
		

	local nDistance = (x1-x)*(x1-x) +(z1-z)*(z1-z)
	
	

	local str1 = "";
	if nDistance>80*80 then
		str1 = "很远的地方"
	elseif nDistance>50*50 then
		str1 = "离这里还有一些距离"
	elseif nDistance>30*30 then
		str1 = "离这里不远了"
	elseif nDistance>10*10 then
		str1 = "就快到了"
	else
		str1 = "紫青宝剑发出响亮的鸣声：看来有缘人就在你身旁不远处，快去把紫青宝剑交给他吧"
		x300573_ShowTips(sceneId, selfId, str1)
		return
	end

	x300573_ShowTips(sceneId, selfId, strDir..str1)
	
end



--// system end




