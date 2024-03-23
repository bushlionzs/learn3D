--***********************
--Const
--***********************
-------------------------

--MisDescBegin


x300575_g_MissionId 				= 	9331                     --任务ID
x300575_g_ScriptId 					= 	300575                  --脚本ID
x300575_g_MissionKind 				= 	1                       --任务类型
x300575_g_LevelLess					= 	40                      --场景开放等级  <=0 表示不限制


x300575_g_MissionName				= 	"【个人】谍影重重"
x300575_g_MissionName1				= 	"这个......上算乾坤？"
x300575_g_MissionTarget				= 	"消灭东瀛岛国派来的忍者"
x300575_g_MissionInfo				= 	""
x300575_g_ContinueInfo				= 	""
x300575_g_MissionCompleted			= 	""
x300575_g_MissionHelp				=	"根据情报，东瀛岛国的忍者们似乎在城外埋伏。"          --任务提示信息

--目标
x300575_g_ExtTarget					=	{ {type=20,n=1,target="谍影重重"}}

--奖励

x300575_g_ExpBonus					= 	0;--x300575_AddExpAward               	--奖励：经验
x300575_g_BonusItem					=	{}	--奖励：物品

x300575_g_BonusMoney1               = 	0
x300575_g_BonusMoney2               =   0
x300575_g_BonusMoney3               =   0

x300575_g_BonusChoiceItem           =   {}


--MisDescEnd


x300575_g_EnterTime					=	{                       --接受任务的时间
											{min=0*60+0,  max=23*60+59},
										}

x300575_g_SubNpcId = 139137
x300575_g_ReplyNpcId = 143049

x300575_g_GameId	= 1012
-- 杀怪掉落物品
x300575_g_ItemList  = {
                        12030113, 
                        12030114, 
                        12030115, 
}
-- 掉落概率
x300575_g_DropProbability   = 100
x300575_g_ItemId            = 12030028

x300575_g_TypeList = {
						{name="@npc_85050",id=1208,count=3, tipname = "武藏流忍者" },
						{name="@npc_85051",id=1207,count=3, tipname = "甲贺流忍者" },
						{name="@npc_85052",id=1206,count=3, tipname = "伊贺流忍者" },
						{name="@npc_85053",id=1209,count=3, tipname = "伊纪流忍者" }
					 }	


x300575_g_BonusChoiceItem2   = {
								{10019200,10077200,10238200,10208200,10268200,10248200,10258200,10278200},
								{10028200,10087200,10238210,10208210,10268210,10248210,10258210,10278210},
								{10038200,10097200,10238220,10208220,10268220,10248220,10258220,10278220},
								{10048200,10107200,10238230,10208230,10268230,10248230,10258230,10278230},
								{10058200,10117200,10238240,10208240,10268240,10248240,10258240,10278240},
								{10068200,10127200,10238250,10208250,10268250,10248250,10258250,10278250}
									
								}

-- 任务奖励物品列表
x300575_g_RewardTable       = {
                                { minLevel = 40, maxLevel = 60,  items = { { id = 11000201, cnt = 8 }, { id = 11050002, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 60, maxLevel = 80,  items = { { id = 11000202, cnt = 8 }, { id = 11050003, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 80, maxLevel = 999, items = { { id = 11000203, cnt = 8 }, { id = 11050004, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
}


function x300575_GetMissionId( sceneId, selfId )
	return x300575_g_MissionId
end

function x300575_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	local level = GetLevel( sceneId,selfId )
    if level < x300575_g_LevelLess then
       return
    end

	local myMissionId = x300575_GetMissionId( sceneId, selfId )
	
	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		AddQuestNumText(sceneId, myMissionId, x300575_g_MissionName,8,1);
	else
		local state = GetQuestStateNM(sceneId, selfId, targetId, myMissionId);

		
		AddQuestNumText(sceneId, myMissionId, x300575_g_MissionName,state,state);

	end


	
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300575_ProcEventEntry( sceneId, selfId, targetId, MissionId, nExt )
	
	if GetGameOpenById(x300575_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300575_g_MissionId) == 0 then
		x300575_ShowTips(sceneId, selfId, "此活动今天不开放，详情请到大都包打处听查询每日新鲜事")
		return
	end

	local myMissionId = x300575_GetMissionId( sceneId, selfId )	
	
	

	
	
	
		
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		x300575_DispatchMissionInfo( sceneId, selfId, targetId, myMissionId, 0 )
	else
		if nExt==7 then -- 任务完成
			x300575_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
			
			
		else
			
			x300575_DispatchContinueInfo( sceneId, selfId, targetId,myMissionId )
		end
	end
	
end


function x300575_ProcAcceptCheck(sceneId, selfId, targetId, MissionId )
	
	if GetGameOpenById(x300575_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300575_g_MissionId) == 0 then
		
		return 0;
	end
	return 1;

end

function x300575_CheckRequest(sceneId, selfId)
	if GetGameOpenById(x300575_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300575_g_MissionId) == 0 then
		x300575_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0
	end
	local myMissionId = x300575_GetMissionId( sceneId, selfId )

	if GetLevel(sceneId, selfId) <x300575_g_LevelLess then
		x300575_ShowTips(sceneId, selfId, "等级不足")
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) > 0 then
		x300575_ShowTips(sceneId, selfId, "你已经有这个任务，请先完成这个任务")
		return 0;
	end

	if  x300575_CheckCommonCondition_Time(sceneId, selfId)<=0 then
		return 0;
	end

    local today = GetDayOfYear()
    if GetQuestData(sceneId, selfId, MD_LVZHUANG60_DATE[1], MD_LVZHUANG60_DATE[2], MD_LVZHUANG60_DATE[3] ) == today then
        x300575_ShowTips(sceneId, selfId, "很抱歉，您今天已经做过此任务，不能再次领取")
        return 0;
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

function x300575_CheckCommonCondition_Time(sceneId, selfId)
	local hour,minute,sec =GetHourMinSec();
	local nowtime = hour*60+minute
	
	for i, item in x300575_g_EnterTime do
		if nowtime >= item.min and nowtime <= item.max then
			
			
			return 1;
			
		end
	end
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "请14：00-21：59来接任务");
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	return 0;
end

function x300575_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
	
	
	if GetGameOpenById(x300575_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300575_g_MissionId) == 0 then
		x300575_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	if x300575_CheckRequest(sceneId, selfId)<=0 then
		
		return 0;
	end

	local myMissionId = x300575_GetMissionId( sceneId, selfId )

	--------------------------- add for Mission full check --------------
	local bFullMission = IsQuestFullNM(sceneId,selfId)
	
	if bFullMission>0 then
		x300575_ShowTips(sceneId, selfId, "任务已满，无法接受任务")
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

	local ret = AddQuest( sceneId, selfId, myMissionId, x300575_g_ScriptId, 1, 0, 0,0)-- 给玩家添加任务		
		
	if ret > 0 then
		local str = "您接受了任务："..x300575_g_MissionName;
		x300575_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)
		
		local myMissionId = x300575_GetMissionId( sceneId, selfId )
		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
		SetQuestByIndex( sceneId, selfId, misIndex, 5, 0 )

		x300575_GiveSubMission(sceneId, selfId, targetId, myMissionId,2)
		GamePlayScriptLog(sceneId, selfId, 821)
		return 1
	else
		
		x300575_ShowTips(sceneId, selfId, "接受任务错误")
	
	end


end

function x300575_GetKillType()
	local hour,minute,sec =GetHourMinSec();
	
	
	local tr=hour-20+1
	
	if tr>4 or tr < 1 then 
		return random(1,4)  
  end
  
  	return tr
  
end

function x300575_GiveSubMission(sceneId, selfId, targetId, MissionId, nExt)
	
	if GetGameOpenById(x300575_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300575_g_MissionId) == 0 then
		x300575_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end
	local myMissionId = x300575_GetMissionId( sceneId, selfId )

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 5, 1 )  --还没有答题
	SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )

	local killType = x300575_GetKillType()
	SetQuestByIndex( sceneId, selfId, misIndex, 1, killType )
	SetQuestByIndex( sceneId, selfId, misIndex, 2, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 3, 0 )

	x300575_ShowSubMission( sceneId, selfId, targetId,MissionId, nExt )

	x300575_QuestLogRefresh( sceneId, selfId, myMissionId );
end

function x300575_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x300575_ProcQuestAbandon( sceneId, selfId, MissionId )

	local myMissionId = x300575_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	local ret = DelQuestNM( sceneId, selfId, myMissionId )

	if ret>0 then

		local str = "您放弃了任务："..x300575_g_MissionName;
	    x300575_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)

        local today = GetDayOfYear()
		SetQuestData(sceneId, selfId, MD_LVZHUANG60_DATE[1], MD_LVZHUANG60_DATE[2], MD_LVZHUANG60_DATE[3], today)
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
		x300575_ShowTips(sceneId, selfId, "放弃任务失败")
	end

	
end



function x300575_ProcQuestSubmit( sceneId, selfId, targetId, selectRadioId, MissionId )
	
	if GetGameOpenById(x300575_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300575_g_MissionId) == 0 then
		x300575_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	local myMissionId = x300575_GetMissionId( sceneId, selfId )
	
	if x300575_CheckSubmit(sceneId, selfId )>0 then
		local today = GetDayOfYear()
        local count = GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3] )
        if today == GetQuestData(sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2],MD_RICHANG_DAY[3] ) and count >= 3 then
            Msg2Player( sceneId, selfId, "今天的日常任务已经不能再交了，请明天再来", 8, 3)
            return 0
        end

		local nRet = x300575_GiveRewardTest(sceneId,selfId,selectRadioId)

		if nRet<=0 then
			return 0
		end

        if x300575_GiveReward(sceneId,selfId,selectRadioId) <= 0 then
            return 0
        end

        local ret = DelQuestNM( sceneId, selfId, myMissionId )

		if ret>0 then
            CallScriptFunction( 270300, "OnSubmissionFinished", sceneId, selfId, x300575_g_MissionId)

			local str = "您完成了任务:"..x300575_g_MissionName;
			x300575_ShowTips(sceneId, selfId, str)
			Msg2Player(sceneId,selfId,str,8,2)

			SetQuestData(sceneId, selfId, MD_LVZHUANG60_DATE[1], MD_LVZHUANG60_DATE[2], MD_LVZHUANG60_DATE[3], GetDayOfYear() )

            if x300575_DelDroppedItems( sceneId, selfId) == 1 then
                BeginAddItem( sceneId)
                AddItem( sceneId, x300575_g_ItemId, 1)
                local ret = EndAddItem( sceneId, selfId)
                if ret == 1 then
                    AddItemListToPlayer( sceneId, selfId)
                    LuaThisScenceM2Wrold( sceneId, format( "%s实在了得，竟然搜集到了完整的情报，特奖励一个@item_%d。", 
                        GetName( sceneId, selfId), x300575_g_ItemId), 1, 1)
                else
                    Msg2Player( sceneId, selfId, "物品栏已满，无法获得物品", 8, 3)
                end
            end

			GamePlayScriptLog(sceneId, selfId, 822)
			
		else
			x300575_ShowTips(sceneId, selfId, "交任务失败")
		end
		
	end
end

function x300575_GiveRewardTest(sceneId,selfId,selectRadioId)
	
	if GetGameOpenById(x300575_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300575_g_MissionId) == 0 then
		x300575_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	
	

	BeginAddItem(sceneId)
		AddItem( sceneId, selectRadioId, 1 )
		
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		
		

		return 1;
	else
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"背包空间不足，无法获得任务奖励物品，交任务失败")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0;	
	end
	
	
	
end

function x300575_GiveReward(sceneId,selfId,selectRadioId)
	
	if GetGameOpenById(x300575_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300575_g_MissionId) == 0 then
		x300575_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

    -- 检查玩家选择的奖励是不是可判定非绑定的
	local level = GetLevel( sceneId, selfId)
    local canBind = 0
    local count = 0
    local id = 0
    for i, item in x300575_g_RewardTable do
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
        for i, item in x300575_g_RewardTable do
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



function x300575_CheckSubmit(sceneId, selfId )
	
	if GetGameOpenById(x300575_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300575_g_MissionId) == 0 then
		x300575_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	local myMissionId = x300575_GetMissionId( sceneId, selfId )
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
function x300575_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId, nExt )

	
	
	BeginQuestEvent(sceneId)

		
	
	AddQuestText(sceneId,"#Y"..x300575_g_MissionName)
	AddQuestText(sceneId,"\t方才得到的情报，那东瀛岛国，竟然也敢派出他们那些所谓的“忍者”，来我威海港伺机破坏。\n\t更为可笑的是，那东瀛岛国的忍者们居然分为：甲贺，武藏，伊贺，伊纪的四大流派。号称每个流派都有其独特的“威力”。\n\t此等可笑弱小之徒，实不值我元军前往，不如就由你前去给他们点颜色看看？")
	AddQuestText( sceneId,"#Y任务目标:")
			
	AddQuestText( sceneId,x300575_g_MissionTarget)
	AddQuestText(sceneId," ")

	--1、经验
	local level = GetLevel(sceneId, selfId)
	-- local nExpBonus = level*0;
	
	-- if nExpBonus > 0 then
		-- AddQuestExpBonus( sceneId, nExpBonus)
	-- end

	-- local ZhiYe= GetZhiye( sceneId, selfId)
	-- for i, item in x300575_g_BonusChoiceItem2[ZhiYe+1] do
		
		-- AddQuestRadioItemBonus(sceneId, item, 1)
		
	-- end
    for i, item in x300575_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end

	EndQuestEvent()
	
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300575_g_ScriptId, MissionId,0);
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300575_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	local myMissionId = x300575_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300575_g_MissionName)
		AddQuestText(sceneId,"\t怎么？！难道一东瀛小国的忍者也能让你如此惧怕？")
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300575_g_ScriptId, MissionId,0);
	


end







---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300575_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	local myMissionId = x300575_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300575_g_MissionName)
		AddQuestText(sceneId,"\t事情办完了？好！这就是那东瀛小国自不量力的下场。\n\t#Y@myname#W，消灭这些忍者虽不是什么大功，但这些装备，你也可随意挑选一件。")
	
	
	
	--1、经验
	local level = GetLevel(sceneId, selfId)
    for i, item in x300575_g_RewardTable do
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
	-- for i, item in x300575_g_BonusChoiceItem2[ZhiYe+1] do
		
		-- AddQuestRadioItemBonus(sceneId, item, 1)
		
	-- end
		
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300575_g_ScriptId, MissionId);

end


---------------------------------------------------------------------------------------------------
--向客户端发送题目
---------------------------------------------------------------------------------------------------
function x300575_ShowSubMission( sceneId, selfId, NPCId,MissionId, nExt )


	
	local myMissionId = x300575_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )


	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300575_g_MissionName)
		AddQuestText(sceneId,format("\t唔......下算九幽！\n\t既然你能说出切口，定然是达鲁花将军派你来的。\n\t我已经打探清楚，最近一批"..x300575_g_TypeList[value2].name.."在大都城外聚集，图谋不轨，你速去将他们消灭，然后报知将军！"))
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300575_g_ScriptId, MissionId,0);
	


end







---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300575_QuestLogRefresh( sceneId, selfId, MissionId)
	
	if IsHaveQuestNM( sceneId, selfId, x300575_g_MissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end	
		
	BeginQuestEvent(sceneId)	
			
		
	AddQuestLogCustomText( sceneId,
							"",						-- 标题
							x300575_GetMissionName(sceneId,selfId),        -- 任务名字
							x300575_GetMissionTask(sceneId,selfId),		--任务目标
							"@npc_"..x300575_GetReplyNpcId(sceneId,selfId),			--任务NPC
							x300575_GetMissionMethod(sceneId,selfId),               --任务攻略
							x300575_GetMissionText(sceneId,selfId),	--任务描述
							x300575_GetMissionHelp(sceneId,selfId)					--任务小提示
							)

	--1、经验
	local level = GetLevel(sceneId, selfId)
    for i, item in x300575_g_RewardTable do
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
	-- for i, item in x300575_g_BonusChoiceItem2[ZhiYe+1] do
		
		-- AddQuestRadioItemBonus(sceneId, item, 1)
		
	-- end

	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	

end

function x300575_GetMissionName(sceneId,selfId)
	

	return x300575_g_MissionName;
end

function x300575_GetMissionTask(sceneId,selfId)
	local myMissionId = x300575_GetMissionId( sceneId, selfId )
	
	if IsHaveQuestNM( sceneId,selfId,myMissionId) ~= 1 then
		return ""
	end
	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	
	
	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )

	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )

	local nCount = getn(x300575_g_TypeList)
	if value2 < 1 or value2 > nCount then
		return ""
	end
	

	local strTable = "  ";
	local str1 = strTable.."消灭#G"..x300575_g_TypeList[value2].name.."#W"..format("(%d/%d)",value1,x300575_g_TypeList[value2].count)
	--local str2 = "\n"..strTable.."找到#G“小生”#W"..format("(%d/1)",value2)

	if value1>=1 then
		str1 = "#G"..str1
	else
		str1 = "#W"..str1
	end

	return str1
end

function x300575_GetReplyNpcId(sceneId,selfId)
	return x300575_g_ReplyNpcId;
end

function x300575_GetMissionMethod(sceneId,selfId)
	return "\t消灭东瀛岛国派来的忍者。"
end

function x300575_GetMissionText(sceneId,selfId)
	return "\t方才得到的情报，那东瀛岛国，竟然也敢派出他们那些所谓的“忍者”，来我威海港伺机破坏。听说那东瀛岛国的忍者们居然分为四大流派，着实可笑之极。\n\t此等弱小之徒，实不值我元军前往，不如就由你前去给他们点颜色看看？"
end

function x300575_GetMissionHelp(sceneId,selfId)
	return "\t根据情报，东瀛岛国的忍者们似乎在城外埋伏。"
end



function x300575_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300575_QuestLogRefresh( sceneId, selfId, MissionId );
end

--// system function start
function x300575_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	
	
	
	
	

	
end



function x300575_CheckSceneOnKill(sceneId, selfId)
	if sceneId==15 then
		return 1
	else
		return 0
	end
end

function x300575_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

	local HumenNum = GetMonsterOwnerCount( sceneId, objId ) --取得这个怪物死后拥有分配权的人数
	for i = 0, HumenNum-1 do
		local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --取得拥有分配权的人的objId
		if humanObjId ~= -1 then
			local myMissionId = x300575_GetMissionId( sceneId, humanObjId )
	
			if IsHaveQuestNM( sceneId, humanObjId, myMissionId ) > 0 then	--如果这个人拥有任务
				x300575_OnValidKillObject( sceneId, humanObjId, objdataId, objId, MissionId )
			end
		end
	end
	
end

function x300575_OnValidKillObject( sceneId, selfId, objdataId, objId, MissionId )

	if x300575_CheckSceneOnKill(sceneId, selfId)<=0 then
		return 0;
	end

	local myMissionId = x300575_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )
	

	if nStep~=1 then
		return
	end

	

	
	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )

	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )

	if value1>=x300575_g_TypeList[value2].count then
		return
	end

	

	if x300575_g_TypeList[value2].id~=objdataId then
		return
	end

	SetQuestByIndex( sceneId, selfId, misIndex, 0, value1+1 )

    -- 没完成任务才掉落物品
    if GetQuestParam( sceneId, selfId, misIndex, 7) == 0 and random( 1, 100) <= x300575_g_DropProbability then
        BeginAddItem( sceneId)
        if IsHaveSpecificImpact( sceneId, selfId, 9011) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9012) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9013) == 1 then
            AddItem( sceneId, x300575_g_ItemList[ random( 1, 3) ], 1)
        else
            AddBindItem( sceneId, x300575_g_ItemList[ random( 1, 3) ], 1)
        end
        if EndAddItem( sceneId, selfId) == 0 then
            Msg2Player( sceneId, selfId, "背包已满，无法获得掉落物品", 8, 3)
        else
            AddItemListToPlayer( sceneId, selfId)
        end
    end

	if (value1+1)==x300575_g_TypeList[value2].count then
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
	end

	x300575_ShowTips(sceneId, selfId, format("消灭"..x300575_g_TypeList[value2].tipname.."(%d/%d)",value1+1,x300575_g_TypeList[value2].count ))

	x300575_QuestLogRefresh( sceneId, selfId, myMissionId );
	
end

-- 删除掉落物品，如果三件物品都有就返回1，否则返回0
function x300575_DelDroppedItems( sceneId, selfId)
    local allItems = 1
    for i, item in x300575_g_ItemList do
        local iCount = GetItemCountInBag( sceneId, selfId, item)
        if iCount > 0 then
            DelItem( sceneId, selfId, item, iCount)
        else
            allItems = 0
        end
    end

    return allItems
end

--// system end




