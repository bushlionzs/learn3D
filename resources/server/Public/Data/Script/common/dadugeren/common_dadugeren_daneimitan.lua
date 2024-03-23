--***********************
--Const
--***********************
-------------------------

--MisDescBegin


x300572_g_MissionId 				= 	9325                     --任务ID
x300572_g_ScriptId 					= 	300572                  --脚本ID
x300572_g_MissionKind 				= 	1                       --任务类型
x300572_g_LevelLess					= 	40                      --场景开放等级  <=0 表示不限制


x300572_g_MissionName				= 	"【个人】大内密探"
x300572_g_MissionName1				= 	"这个......上算乾坤？"
x300572_g_MissionTarget				= 	"  找到伪装成#G算命先生半仙刘#W的大内密探，他通常在钟楼一带走动"
x300572_g_MissionInfo				= 	""
x300572_g_ContinueInfo				= 	""
x300572_g_MissionCompleted			= 	""
x300572_g_MissionHelp				=	"半仙刘通常会在钟楼一带行走。"          --任务提示信息

--目标
x300572_g_ExtTarget					=	{ {type=20,n=1,target="大内密探"}}

--奖励

x300572_g_ExpBonus					= 	0;--x300572_AddExpAward               	--奖励：经验
x300572_g_BonusItem					=	{}	--奖励：物品

x300572_g_BonusMoney1               = 	0
x300572_g_BonusMoney2               =   0
x300572_g_BonusMoney3               =   0

x300572_g_BonusChoiceItem           =   {}


--MisDescEnd


x300572_g_HourCountLimited			=	1

x300572_g_EnterTime					=	{                       --接受任务的时间
											{min=0*60+0,  max=23*60+59},
										}

x300572_g_SubNpcId = 139137
x300572_g_ReplyNpcId = 139134

x300572_g_GameId	= 1010
x300572_g_BuffId	= 7715


x300572_g_nTypeCount = 4

x300572_g_TypeList = {
						{name="@npc_141022",id=1178, tipname = "东瀛刺客" },
						{name="@npc_141023",id=1179, tipname = "高丽细作" },
						{name="@npc_141024",id=1180, tipname = "爪哇奸细" },
						{name="@npc_141025",id=1181, tipname = "安南密探" }
					 }	


x300572_g_BonusChoiceItem2   = {
								{10019000,10077000,10238000,10208000,10268000,10248000,10258000,10278000},
								{10028000,10087000,10238010,10208010,10268010,10248010,10258010,10278010},
								{10038000,10097000,10238020,10208020,10268020,10248020,10258020,10278020},
								{10048000,10107000,10238030,10208030,10268030,10248030,10258030,10278030},
								{10058000,10117000,10238040,10208040,10268040,10248040,10258040,10278040},
								{10068000,10127000,10238050,10208050,10268050,10248050,10258050,10278050}
									
								}


-- 任务奖励物品列表
x300572_g_RewardTable       = {
                                { minLevel = 40, maxLevel = 60,  items = { { id = 11000201, cnt = 8 }, { id = 11050002, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 60, maxLevel = 80,  items = { { id = 11000202, cnt = 8 }, { id = 11050003, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 80, maxLevel = 999, items = { { id = 11000203, cnt = 8 }, { id = 11050004, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
}



function x300572_GetMissionId( sceneId, selfId )
	return x300572_g_MissionId
end

function x300572_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	local level = GetLevel( sceneId,selfId )
    if level < x300572_g_LevelLess then
       return
    end

	local myMissionId = x300572_GetMissionId( sceneId, selfId )
	
	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		AddQuestNumText(sceneId, myMissionId, x300572_g_MissionName,8,1);
	else
		local state = GetQuestStateNM(sceneId, selfId, targetId, myMissionId);

		
		AddQuestNumText(sceneId, myMissionId, x300572_g_MissionName,state,state);

	end


	
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300572_ProcEventEntry( sceneId, selfId, targetId, MissionId, nExt )
	
	if GetGameOpenById(x300572_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300572_g_MissionId) == 0 then
		x300572_ShowTips(sceneId, selfId, "此活动今天不开放，详情请到大都包打处听查询每日新鲜事")
		return
	end

	local myMissionId = x300572_GetMissionId( sceneId, selfId )	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId )>0 then
		if nExt==30 then
			x300572_GiveSubMission(sceneId, selfId, targetId, MissionId,2)
			return
		end
	end

	
	
	
		
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		x300572_DispatchMissionInfo( sceneId, selfId, targetId, myMissionId, 0 )
	else
		if nExt==7 then -- 任务完成
			x300572_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
			
			
		else
			
			x300572_DispatchContinueInfo( sceneId, selfId, targetId,myMissionId )
		end
	end
	
end


function x300572_ProcAcceptCheck(sceneId, selfId, targetId, MissionId )
	
	if GetGameOpenById(x300572_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300572_g_MissionId) == 0 then
		
		return 0;
	end
	return 1;

end

function x300572_CheckRequest(sceneId, selfId)
	if GetGameOpenById(x300572_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300572_g_MissionId) == 0 then
		x300572_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0
	end
	local myMissionId = x300572_GetMissionId( sceneId, selfId )

	if GetLevel(sceneId, selfId) <x300572_g_LevelLess then
		x300572_ShowTips(sceneId, selfId, "等级不足")
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) > 0 then
		x300572_ShowTips(sceneId, selfId, "你已经有这个任务，请先完成这个任务")
		return 0;
	end

	if  x300572_CheckCommonCondition_Time(sceneId, selfId)<=0 then
		return 0;
	end

    local today = GetDayOfYear()
    if GetQuestData(sceneId, selfId, MD_LVZHUANG40_DATE[1], MD_LVZHUANG40_DATE[2],MD_LVZHUANG40_DATE[3] ) == today then
        x300572_ShowTips(sceneId, selfId, "很抱歉，您今天已经做过此任务，不能再次领取")
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

function x300572_CheckCommonCondition_Time(sceneId, selfId)
	local hour,minute,sec =GetHourMinSec();
	local nowtime = hour*60+minute
	
	for i, item in x300572_g_EnterTime do
		if nowtime >= item.min and nowtime <= item.max then
			
			
			return 1;
			
		end
	end
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "请在14：00-21：59来接任务");
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	return 0;
end

function x300572_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
	
	
	if GetGameOpenById(x300572_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300572_g_MissionId) == 0 then
		x300572_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	if x300572_CheckRequest(sceneId, selfId)<=0 then
		
		return 0;
	end

	local myMissionId = x300572_GetMissionId( sceneId, selfId )

	--------------------------- add for Mission full check --------------
	local bFullMission = IsQuestFullNM(sceneId,selfId)
	
	if bFullMission>0 then
		x300572_ShowTips(sceneId, selfId, "任务已满，无法接受任务")
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

	local ret = AddQuest( sceneId, selfId, myMissionId, x300572_g_ScriptId, 1, 0, 0,1)-- 给玩家添加任务		
		
	if ret > 0 then
		local str = "您接受了任务"..x300572_g_MissionName;
		x300572_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)
		
		local myMissionId = x300572_GetMissionId( sceneId, selfId )
		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
		SetQuestByIndex( sceneId, selfId, misIndex, 5, 0 )

        SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300572_g_BuffId, 0)
		GamePlayScriptLog(sceneId, selfId, 801)
		
		return 1
	else
		
		x300572_ShowTips(sceneId, selfId, "接受任务错误")
	
	end


end

function x300572_GiveSubMission(sceneId, selfId, targetId, MissionId, nExt)
	
	if GetGameOpenById(x300572_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300572_g_MissionId) == 0 then
		x300572_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end
	local myMissionId = x300572_GetMissionId( sceneId, selfId )

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 5, 1 )  --还没有答题
	SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )

	local killType = random(1, x300572_g_nTypeCount)
	SetQuestByIndex( sceneId, selfId, misIndex, 1, killType )
	SetQuestByIndex( sceneId, selfId, misIndex, 2, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 3, 0 )

    if IsHaveSpecificImpact( sceneId, selfId, x300572_g_BuffId) == 1 then
        CancelSpecificImpact( sceneId, selfId, x300572_g_BuffId)
        SetQuestByIndex( sceneId, selfId, misIndex, 4, 1)
    else
        SetQuestByIndex( sceneId, selfId, misIndex, 4, 3)
    end

	x300572_ShowSubMission( sceneId, selfId, targetId,MissionId, nExt )

	x300572_QuestLogRefresh( sceneId, selfId, myMissionId );
end

function x300572_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x300572_ProcQuestAbandon( sceneId, selfId, MissionId )

	local myMissionId = x300572_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	local ret = DelQuestNM( sceneId, selfId, myMissionId )

	if ret>0 then

		local str = "您放弃了任务:"..x300572_g_MissionName;
	    x300572_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)

        local today = GetDayOfYear()
		SetQuestData( sceneId, selfId, MD_LVZHUANG40_DATE[1], MD_LVZHUANG40_DATE[2], MD_LVZHUANG40_DATE[3], today)
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
		x300572_ShowTips(sceneId, selfId, "放弃任务失败")
	end

	
end



function x300572_ProcQuestSubmit( sceneId, selfId, targetId, selectRadioId, MissionId )
	
	if GetGameOpenById(x300572_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300572_g_MissionId) == 0 then
		x300572_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end
	
	if IsHaveQuestNM( sceneId, selfId, x300572_g_MissionId ) <= 0 then
		return
	end

	local myMissionId = x300572_GetMissionId( sceneId, selfId )
	
	if x300572_CheckSubmit(sceneId, selfId )>0 then
		local today = GetDayOfYear()
        local count = GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3] )
        if today == GetQuestData(sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2],MD_RICHANG_DAY[3] ) and count >= 3 then
            Msg2Player( sceneId, selfId, "今天的日常任务已经不能再交了，请明天再来", 8, 3)
            return 0
        end

		local nRet = x300572_GiveReward(sceneId,selfId,selectRadioId)

		if nRet<=0 then
			return
		end
		local ret = DelQuestNM( sceneId, selfId, myMissionId )

		if ret>0 then
            CallScriptFunction( 270300, "OnSubmissionFinished", sceneId, selfId, x300572_g_MissionId)

			local str = "您完成了任务:"..x300572_g_MissionName;
			x300572_ShowTips(sceneId, selfId, str)
			Msg2Player(sceneId,selfId,str,8,2)

			SetQuestData(sceneId, selfId, MD_LVZHUANG40_DATE[1], MD_LVZHUANG40_DATE[2], MD_LVZHUANG40_DATE[3], GetDayOfYear() )

			GamePlayScriptLog(sceneId, selfId, 802)
			
		else
			x300572_ShowTips(sceneId, selfId, "交任务失败")
		end
		
	end
end

function x300572_GiveReward(sceneId,selfId,selectRadioId)
	
	if GetGameOpenById(x300572_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300572_g_MissionId) == 0 then
		x300572_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	
	

    -- 检查玩家选择的奖励是不是可判定非绑定的
	local level = GetLevel( sceneId, selfId)
    local canBind = 0
    local count = 0
    local id = 0
    for i, item in x300572_g_RewardTable do
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
        for i, item in x300572_g_RewardTable do
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

		return 1;
	else
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"背包空间不足，无法获得任务奖励物品，交任务失败")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0;	
	end
	
	
	
end



function x300572_CheckSubmit(sceneId, selfId )
	
	if GetGameOpenById(x300572_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300572_g_MissionId) == 0 then
		x300572_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	local myMissionId = x300572_GetMissionId( sceneId, selfId )
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
function x300572_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId, nExt )

	
	
	BeginQuestEvent(sceneId)

		
	
	AddQuestText(sceneId,"#Y"..x300572_g_MissionName)
	AddQuestText(sceneId,"\t方才，我收到消息，有蛮夷之国派出了部分人马，悄悄潜入大都。虽不知他们是何企图，但这般藏头露尾，定然没有什么好事。\n\t你可速去找到我手下的首席密探，他化装成了一个算命先生，在大都钟楼一带走动。\n\t记住，和他的切口是：#G上算乾坤#W。")
	AddQuestText( sceneId,"#Y任务目标:")
			
	AddQuestText( sceneId,x300572_g_MissionTarget)
	AddQuestText(sceneId," ")

	--1、经验
	local level = GetLevel(sceneId, selfId)
    for i, item in x300572_g_RewardTable do
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
	-- for i, item in x300572_g_BonusChoiceItem2[ZhiYe+1] do
		
		-- AddQuestRadioItemBonus(sceneId, item, 1)
		
	-- end

	EndQuestEvent()
	
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300572_g_ScriptId, MissionId,0);
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300572_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	local myMissionId = x300572_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300572_g_MissionName)
		AddQuestText(sceneId,"\t怎么？！你还没找到密探？他这次应该化装成了一个算命先生，就在钟楼一带走动。")
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300572_g_ScriptId, MissionId,0);
	


end







---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300572_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	local myMissionId = x300572_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300572_g_MissionName)
		AddQuestText(sceneId,"\t好！这等蛮夷小国也敢派人来我大元国都造次，真是可笑之极。\n\t#Y@myname#W，你此次功劳不小，这些装备，可随意挑选一件。")
	
	
	
	--1、经验
	local level = GetLevel(sceneId, selfId)
    for i, item in x300572_g_RewardTable do
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
	-- for i, item in x300572_g_BonusChoiceItem2[ZhiYe+1] do
		
		-- AddQuestRadioItemBonus(sceneId, item, 1)
		
	-- end
		
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300572_g_ScriptId, MissionId);

end


---------------------------------------------------------------------------------------------------
--向客户端发送题目
---------------------------------------------------------------------------------------------------
function x300572_ShowSubMission( sceneId, selfId, NPCId,MissionId, nExt )


	
	local myMissionId = x300572_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )


	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300572_g_MissionName)
		AddQuestText(sceneId,format("\t唔......下算九幽！\n\t既然你能说出切口，定然是达鲁花将军派你来的。\n\t我已经打探清楚，最近一批"..x300572_g_TypeList[value2].name.."在大都城外聚集，图谋不轨，你速去将他们消灭，然后报知将军！"))
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300572_g_ScriptId, MissionId,0);
	


end







---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300572_QuestLogRefresh( sceneId, selfId, MissionId)
	
	
		
	BeginQuestEvent(sceneId)	
			
		
	AddQuestLogCustomText( sceneId,
							"",						-- 标题
							x300572_GetMissionName(sceneId,selfId),        -- 任务名字
							x300572_GetMissionTask(sceneId,selfId),		--任务目标
							"@npc_"..x300572_GetReplyNpcId(sceneId,selfId),			--任务NPC
							x300572_GetMissionMethod(sceneId,selfId),               --任务攻略
							x300572_GetMissionText(sceneId,selfId),	--任务描述
							x300572_GetMissionHelp(sceneId,selfId)					--任务小提示
							)

	--1、经验
	local level = GetLevel(sceneId, selfId)
    for i, item in x300572_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end

	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	

end

function x300572_GetMissionName(sceneId,selfId)
	

	return x300572_g_MissionName;
end

function x300572_GetMissionTask(sceneId,selfId)
	local myMissionId = x300572_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

	if nStep==0 then
		
		return "  找到伪装成#G算命先生半仙刘#W的大内密探，他通常在钟楼一带走动"
	end
	

	
	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )

	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )

    local killCount = GetQuestParam( sceneId, selfId, misIndex, 4)


	local strTable ="  ";
	local str1 = strTable.."消灭#G"..x300572_g_TypeList[value2].name.."#W"..format("(%d/%d)",value1,killCount)
	--local str2 = "\n"..strTable.."找到#G“小生”#W"..format("(%d/1)",value2)

	if value1>=killCount then
		str1 = "#G"..str1
	else
		str1 = "#W"..str1
	end

	return str1
end

function x300572_GetReplyNpcId(sceneId,selfId)
	return x300572_g_ReplyNpcId;
end

function x300572_GetMissionMethod(sceneId,selfId)

	local myMissionId = x300572_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

	if nStep==0 then
		
		return "找到伪装成#G算命先生半仙刘#W的大内密探，他通常在钟楼一带走动。"
	end

	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )

	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )

	local killCount = GetQuestParam( sceneId, selfId, misIndex, 4)

	local strTable = "";
	local str1 = strTable.."消灭#G"..x300572_g_TypeList[value2].name.."#W"..format("(%d/%d)",value1,killCount)
	--local str2 = "\n"..strTable.."找到#G“小生”#W"..format("(%d/1)",value2)

	if value1>=killCount then
		str1 = "#G"..str1
	else
		str1 = "#W"..str1
	end

	return str1

	
end

function x300572_GetMissionText(sceneId,selfId)
	return "\t方才，我收到消息，有蛮夷之国派出了部分人马，悄悄潜入大都。虽不知他们是何企图，但这般藏头露尾，定然没有什么好事。\n\t你可速去找到我手下的首席密探，他化装成了一个算命先生，在大都钟楼一带走动。\n\t记住，和他的切口是：#G上算乾坤#W。"
end

function x300572_GetMissionHelp(sceneId,selfId)
	return "\t半仙刘通常会在钟楼一带打探消息。"
end



function x300572_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300572_QuestLogRefresh( sceneId, selfId, MissionId );
end

--// system function start
function x300572_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	
	local myMissionId = x300572_GetMissionId( sceneId, selfId )

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		return
	end


	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	
	
	
	
	
	local bFind =0;
	local iIndex=0
	
	if npcGuid==x300572_g_SubNpcId then
		bFind=1;
		
	end

	

	if bFind==0 then
		return
	end

	local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

	if nStep~=0 then
		return
	end



	
	


	AddQuestNumText(sceneId, x300572_g_MissionId, x300572_g_MissionName1,2,30);
	
	
	

	
end



function x300572_CheckSceneOnKill(sceneId, selfId)
	if sceneId==36 or sceneId==37 or sceneId==38 then
		return 1
	else
		return 0
	end
end

function x300572_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

	local HumenNum = GetMonsterOwnerCount( sceneId, objId ) --取得这个怪物死后拥有分配权的人数
	for i = 0, HumenNum-1 do
		local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --取得拥有分配权的人的objId
		if humanObjId ~= -1 then
		local myMissionId = x300572_GetMissionId( sceneId, humanObjId )
			if IsHaveQuestNM( sceneId, humanObjId, myMissionId ) > 0 then	--如果这个人拥有任务
				x300572_OnValidKillObject( sceneId, humanObjId, objdataId, objId, MissionId )
			end
		end
	end
	
end

function x300572_OnValidKillObject( sceneId, selfId, objdataId, objId, MissionId )

	if x300572_CheckSceneOnKill(sceneId, selfId)<=0 then
		return 0;
	end

	local myMissionId = x300572_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

	if nStep~=1 then
		return
	end

	

	
	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )

	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )

    local killCount = GetQuestParam( sceneId, selfId, misIndex, 4)

	if value1>=killCount then
		return
	end

	

	if x300572_g_TypeList[value2].id~=objdataId then
		return
	end

	

	SetQuestByIndex( sceneId, selfId, misIndex, 0, value1+1 )

	if (value1+1)==killCount then
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
	end

	x300572_ShowTips(sceneId, selfId, format("消灭"..x300572_g_TypeList[value2].tipname.."(%d/%d)",value1+1,killCount ))

	x300572_QuestLogRefresh( sceneId, selfId, myMissionId );
	
end




--// system end




