--***********************
--Const
--***********************
-------------------------

--MisDescBegin


x300580_g_MissionId 				= 	9500                     --任务ID
x300580_g_ScriptId 					= 	300580                  --脚本ID
x300580_g_MissionKind 				= 	1                       --任务类型
x300580_g_LevelLess					= 	40                      --场景开放等级  <=0 表示不限制


x300580_g_MissionName				= 	"【个人】心诚则灵"
x300580_g_MissionName1				= 	"你可听说过紫青侠女？"
x300580_g_MissionTarget				= 	"\t前往#G天云水晶#W处接受考验"
x300580_g_MissionInfo				= 	""
x300580_g_ContinueInfo				= 	""
x300580_g_MissionCompleted			= 	""
x300580_g_MissionHelp				=	""          --任务提示信息

--目标
x300580_g_ExtTarget					=	{ {type=20,n=1,target="【个人】心诚则灵"}}

--奖励

x300580_g_ExpBonus					= 	0;--x300580_AddExpAward               	--奖励：经验
x300580_g_BonusChoiceItem			={{item=11000203,n=6},{item=11000203,n=7},{item=11000203,n=8}}	--奖励：物品

x300580_g_BonusMoney1               = 	0
x300580_g_BonusMoney2               =   0
x300580_g_BonusMoney3               =   0




--MisDescEnd

x300580_G_GAMESTEP					=	6
x300580_G_QUESTIONID				=	5
x300580_G_ACTIONFLAG				=	4
x300580_G_FRAME						=	3
x300580_G_ANWER_STEP				=	2

x300580_Min_Step					=	6
x300580_Max_Step					=	8

x300580_Round_wait					=	5 --下一轮等待
x300580_g_Answer_Wait				=	1 --可以答题等待

x300580_g_BuffId					=	7903
x300580_g_ItemId                    =   12030028

x300580_g_DayCountLimited			=	1

x300580_g_QuestCountList ={4,8,8,8,8,8,8,8}  --每一轮问题的个数
x300580_g_QuestList ={
						{ --第1轮
							{0},
							{1},
							{2},
							{3},
						},

						{ --第2轮
							{0,1},
							{1,2},
							{2,3},
							{3,2},
							{3,3},
							{2,2},
							{1,3},
							{0,3},
						},

						{ --第3轮
							{0,1,2},
							{0,1,3},
							{2,1,2},
							{3,1,2},
							{3,3,2},
							{1,1,2},
							{3,2,2},
							{1,1,3},
						},

						{ --第4轮
							{0,1,2,3},
							{3,1,3,3},
							{2,1,2,3},
							{0,1,3,2},
							{1,2,1,3},
							{3,3,2,1},
							{1,3,1,3},
							{2,1,2,0},
						},

						{ --第5轮
							{0,1,2,3,0},
							{2,1,2,2,0},
							{3,3,2,1,0},
							{1,1,2,1,3},
							{3,1,2,3,0},
							{0,2,2,1,3},
							{1,2,2,3,0},
							{0,3,2,1,2},
						},

						{ --第6轮
							{0,1,3,2,0,1},
							{2,1,2,1,1,3},
							{3,1,3,2,2,1},
							{0,3,1,2,3,1},
							{1,2,3,2,0,1},
							{1,3,2,3,3,1},
							{2,3,2,3,0,1},
							{3,1,0,3,0,1},
						},

						{ --第7轮
							{1,3,2,0,0,1,2},
							{1,2,3,3,2,0,1},
							{2,1,2,0,3,1,2},
							{3,1,2,1,0,3,2},
							{2,1,0,3,2,1,2},
							{3,2,2,1,0,3,2},
							{1,1,2,3,1,0,2},
							{0,1,3,1,2,2,3},
						},

						{ --第8轮
							{0,1,2,3,0,1,2,3},
							{0,1,3,3,0,1,1,3},
							{1,1,2,2,0,2,3,1},
							{3,1,3,3,0,3,2,1},
							{2,1,2,0,1,3,2,2},
							{1,1,2,3,1,0,2,2},
							{2,3,2,1,0,1,1,3},
							{1,1,2,3,0,2,3,2},
						},
					 }







x300580_g_GameId	= 1025

x300580_g_PlayNpcId  = 110102
x300580_g_ReplyNpcId = 110102

-- 任务奖励物品列表
x300580_g_RewardTable       = {
                                { minLevel = 40, maxLevel = 60,  items = { { id = 11000201, cnt = 8 }, { id = 11050002, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 60, maxLevel = 80,  items = { { id = 11000202, cnt = 8 }, { id = 11050003, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 80, maxLevel = 999, items = { { id = 11000203, cnt = 8 }, { id = 11050004, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
}

function x300580_GetMissionId( sceneId, selfId )
	return x300580_g_MissionId
end

function x300580_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
	local level = GetLevel( sceneId,selfId )
    if level < x300580_g_LevelLess then
       return
    end

	local myMissionId = x300580_GetMissionId( sceneId, selfId )
	
	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		AddQuestNumText(sceneId, myMissionId, x300580_g_MissionName,8,1);
	else
		--local state = GetQuestStateNM(sceneId, selfId, targetId, myMissionId);

		
		--AddQuestNumText(sceneId, myMissionId, x300580_g_MissionName,state,state);

	end


	
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300580_ProcEventEntry( sceneId, selfId, targetId, MissionId, nExt )
	
	if nExt==nil then
		return
	end

	if GetGameOpenById(x300580_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300580_g_MissionId) == 0 then
		x300580_ShowTips(sceneId, selfId, "此活动今天不开放，详情请到大都包打处听查询每日新鲜事")
		return
	end

	local myMissionId = x300580_GetMissionId( sceneId, selfId )	
	
	
	
	
		
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		x300580_DispatchMissionInfo( sceneId, selfId, targetId, myMissionId, 0 )
	else
		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	
		local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )
		local nCurrentStep = GetQuestParam( sceneId, selfId, misIndex, x300580_G_GAMESTEP )

		if nExt==7 then
			x300580_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
		elseif nExt==10 then
			x300580_DispatchStartGame( sceneId, selfId, targetId,myMissionId )

			x300580_StartPlayGame(sceneId, selfId, 0)
		elseif nExt==11 then
			x300580_DispatchStartGame( sceneId, selfId, targetId,myMissionId )

			x300580_StartPlayGame(sceneId, selfId, 1)
		elseif nExt>=20 then
			x300580_DispatchDifficultLevel( sceneId, selfId, targetId,myMissionId, nExt-20 )

			SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
			SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
			x300580_OnStartDifficultLevel(sceneId, selfId)
			--x300580_OnPlayNextRound(sceneId, selfId)
		end
		
	end
end

--// system function start
function x300580_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	
	if npcGuid ~= x300580_g_PlayNpcId and npcGuid ~= x300580_g_ReplyNpcId then
		return
	end

	local myMissionId = x300580_GetMissionId( sceneId, selfId )

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		return 0;
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	
	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )
	local nCurrentStep = GetQuestParam( sceneId, selfId, misIndex, x300580_G_GAMESTEP )
	local nActionFlag = GetQuestParam( sceneId, selfId, misIndex, x300580_G_ACTIONFLAG )

	if npcGuid == x300580_g_PlayNpcId then
		--if bCompleted<=0 then
			if nCurrentStep==0 then
				if nActionFlag==0 then
				AddQuestNumText(sceneId, myMissionId, "我来接受考验",2,10);
				end
			elseif nCurrentStep>=x300580_Min_Step  and nCurrentStep<=x300580_Max_Step then
				local nActionFlag = GetQuestParam( sceneId, selfId, misIndex, x300580_G_ACTIONFLAG )

				if nActionFlag==4 then
					AddQuestNumText(sceneId, myMissionId, format("开始第%d轮考验",nCurrentStep+1),2,(20+nCurrentStep+1-x300580_Min_Step));
				end
			
			end
			
			if nCurrentStep>0 then	
				if IsHaveSpecificImpact(sceneId, selfId, x300580_g_BuffId)<=0 then
					if bCompleted<=0 then
						AddQuestNumText(sceneId, myMissionId, "重新挑战",2,11);
					end
					
				end
			else
				if IsHaveSpecificImpact(sceneId, selfId, x300580_g_BuffId)<=0 then
					if nActionFlag>0 then
						
						if bCompleted<=0 then
							AddQuestNumText(sceneId, myMissionId, "重新挑战",2,11);
						end
						
					end
				end
			end
		--end
	end
	
	if npcGuid == x300580_g_ReplyNpcId then
		if bCompleted>0 then
			local state = GetQuestStateNM(sceneId, selfId, npcId, myMissionId);
			AddQuestNumText(sceneId, myMissionId, x300580_g_MissionName,state,state);
		end
	end

	
	
end

function x300580_StartPlayGame(sceneId, selfId, nMode)

	if nMode==nil then
		return
	end

	local myMissionId = x300580_GetMissionId( sceneId, selfId )

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		return
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nCurrentStep = GetQuestParam( sceneId, selfId, misIndex, x300580_G_GAMESTEP )

	if nMode ==0 then

		if IsHaveSpecificImpact(sceneId, selfId, x300580_g_BuffId)<=0 then
			SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId, x300580_g_BuffId,0 )  --给玩家加buff计时
		
		end
		
		x300580_OnOneRoundCompleted(sceneId, selfId)
		
		--SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_GAMESTEP, 1 )

		
		--x300580_StartChuTi(sceneId, selfId, 1)
	elseif nMode==1 then
		x300580_ShowTips(sceneId, selfId, format("%d秒后开始第一轮",x300580_Round_wait))
		x300580_Restart(sceneId, selfId) --重新开始答题
	
	end

	

	
	
end



function x300580_StartChuTi(sceneId, selfId, nStep)

	if nStep<=0 or nStep>8 then
		return
	end

	local myMissionId = x300580_GetMissionId( sceneId, selfId )

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		return
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	
	local nCount = x300580_g_QuestCountList[nStep]
	
	local nQuestionId = random(1,nCount)

	

	
	
	SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_QUESTIONID, nQuestionId )	--出题id
	SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_ACTIONFLAG, 1 )	--动作Flag

	SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_FRAME, 0 )

	if IsHaveSpecificImpact(sceneId, selfId, x300580_g_BuffId)<=0 then
		SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId, x300580_g_BuffId,0 )  --给玩家加buff计时
		
	end
end


function x300580_ProcAcceptCheck(sceneId, selfId, targetId, MissionId )
	
	if GetGameOpenById(x300580_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300580_g_MissionId) == 0 then
		return
	end
	return 1;

end

function x300580_CheckRequest(sceneId, selfId)
	if GetGameOpenById(x300580_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300580_g_MissionId) == 0 then
		x300580_ShowTips(sceneId, selfId, "此活动今天不开放")
		return
	end
	local myMissionId = x300580_GetMissionId( sceneId, selfId )

	if GetLevel(sceneId, selfId) <x300580_g_LevelLess then
		x300580_ShowTips(sceneId, selfId, "你等级不足")
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) > 0 then
		x300580_ShowTips(sceneId, selfId, "你已经有这个任务，请先完成这个任务")
		return 0;
	end

    if GetQuestData(sceneId, selfId, MD_XCZL_DATE[1], MD_XCZL_DATE[2],MD_XCZL_DATE[3] ) == GetDayOfYear() then
        x300580_ShowTips(sceneId, selfId, "很抱歉，您今天已经做过此任务，不能再次领取")
        return 0;
    end

    if GetQuestData( sceneId, selfId, MD_RICHANG_DAY[ 1], MD_RICHANG_DAY[ 2], MD_RICHANG_DAY[ 3] ) == GetDayOfYear() then
        if GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[ 1], MD_RICHANG_COUNT[ 2], MD_RICHANG_COUNT[ 3] ) >= 3 then
            Msg2Player( sceneId, selfId, "你不能再领取今天的日常任务了", 8, 3)
            return 0
        end
    else
        SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 0)
    end

	return 1;

end

function x300580_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
	
	
	if GetGameOpenById(x300580_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300580_g_MissionId) == 0 then
		x300580_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0
	end

	if x300580_CheckRequest(sceneId, selfId)<=0 then
		
		return 0;
	end

	local myMissionId = x300580_GetMissionId( sceneId, selfId )

	--------------------------- add for Mission full check --------------
	local bFullMission = IsQuestFullNM(sceneId,selfId)
	
	if bFullMission>0 then
		x300580_ShowTips(sceneId, selfId, "任务已满，无法接受任务")
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

	local ret = AddQuest( sceneId, selfId, myMissionId, x300580_g_ScriptId, 0, 0, 0,1)-- 给玩家添加任务		
		
	if ret > 0 then
		
		
		local myMissionId = x300580_GetMissionId( sceneId, selfId )
		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

		

		local str = "您接受了任务："..x300580_g_MissionName;
		x300580_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)
		

	
		
		SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_GAMESTEP, 0 )

		
		GamePlayScriptLog(sceneId, selfId, 1551)
		return 1
	else
		
		x300580_ShowTips(sceneId, selfId, "接受任务错误")
	
	end


end



function x300580_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x300580_ProcQuestAbandon( sceneId, selfId, MissionId )

	local myMissionId = x300580_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	local ret = DelQuestNM( sceneId, selfId, myMissionId )

	if ret>0 then
		CancelSpecificImpact( sceneId, selfId, x300580_g_BuffId)

		local str = "您放弃了任务:"..x300580_g_MissionName;
	    x300580_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)

        local today = GetDayOfYear()
		SetQuestData( sceneId, selfId, MD_XCZL_DATE[1], MD_XCZL_DATE[2], MD_XCZL_DATE[3], today)
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
		x300580_ShowTips(sceneId, selfId, "放弃任务失败")
	end

	
end



function x300580_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	
	if GetGameOpenById(x300580_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300580_g_MissionId) == 0 then
		x300580_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0
	end

	

	local myMissionId = x300580_GetMissionId( sceneId, selfId )
	
	if x300580_CheckSubmit(sceneId, selfId )>0 then
		local today = GetDayOfYear()
        local count = GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3] )
        if today == GetQuestData(sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2],MD_RICHANG_DAY[3] ) and count >= 3 then
            Msg2Player( sceneId, selfId, "今天的日常任务已经不能再交了，请明天再来", 8, 3)
            return 0
        end

		local nRet = x300580_GiveReward(sceneId,selfId,selectId)

		if nRet<=0 then
			return
		end
		local ret = DelQuestNM( sceneId, selfId, myMissionId )

		if ret>0 then
			CallScriptFunction( 270300, "OnSubmissionFinished", sceneId, selfId, x300580_g_MissionId)
			
			local str = "您完成了任务:"..x300580_g_MissionName;
			x300580_ShowTips(sceneId, selfId, str)
			Msg2Player(sceneId,selfId,str,8,2)

			GamePlayScriptLog(sceneId, selfId, 1552)
            SetQuestData( sceneId, selfId, MD_XCZL_DATE[1], MD_XCZL_DATE[2], MD_XCZL_DATE[3], GetDayOfYear() )

			CancelSpecificImpact( sceneId, selfId, x300580_g_BuffId)
			
		else
			x300580_ShowTips(sceneId, selfId, "交任务失败")
		end
		
	end
end

function x300580_GiveReward( sceneId, selfId, selectRadioId)
	
	if GetGameOpenById(x300580_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300580_g_MissionId) == 0 then
		x300580_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0
	end

	local myMissionId = x300580_GetMissionId( sceneId, selfId )

	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		return 0;
	end
	
    -- 检查玩家选择的奖励是不是可判定非绑定的
	local level = GetLevel( sceneId, selfId)
    local canBind = 0
    local count = 0
    local id = 0
    for i, item in x300580_g_RewardTable do
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
        for i, item in x300580_g_RewardTable do
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
	local ret1 = EndAddItem(sceneId,selfId)

	if ret1 > 0 then
		
		AddItemListToPlayer(sceneId,selfId)
		
		
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,format("您获得了物品：@itemid_%d",id))
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

        local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId)
        local circle = GetQuestParam( sceneId, selfId, misIndex, x300580_G_ANWER_STEP)
        local giveReward = 0
        if circle == 7 then
            if random( 1, 100) <= 20 then
                giveReward = 1
            end
        elseif circle == 8 then
            giveReward = 1
        end
        if giveReward == 1 then
            BeginAddItem( sceneId)
            AddItem( sceneId, x300580_g_ItemId, 1)
            local ret = EndAddItem( sceneId, selfId)
            if ret == 1 then
                AddItemListToPlayer( sceneId, selfId)
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



function x300580_CheckSubmit(sceneId, selfId )
	
	if GetGameOpenById(x300580_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300580_g_MissionId) == 0 then
		x300580_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0
	end

	local myMissionId = x300580_GetMissionId( sceneId, selfId )
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
function x300580_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId, nExt )

	
	
	BeginQuestEvent(sceneId)

		
	
	AddQuestText(sceneId,"#Y"..x300580_g_MissionName)
	AddQuestText(sceneId,"\t这里流传着一个古老传说：海天遮日之时，会伴随巨大灾难，唯有破解水晶之谜，才能化解这一场浩劫。\n\t最近这几个月海面狂风肆虐，已经影响此地百姓的生活及我方部队的运输。同时北方海岸的古老水晶在沉寂数百年后再次不时发出四色光芒。\n\t#Y@myname#W，你是否愿意前去一探水晶的奥秘？")
	AddQuestText( sceneId,"#Y")
	AddQuestText( sceneId,"#Y任务目标：")	
	AddQuestText( sceneId,x300580_g_MissionTarget)
	AddQuestText(sceneId," ")

	--1、经验
	local level = GetLevel(sceneId, selfId)
    for i, item in x300580_g_RewardTable do
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
	-- --2.物品
	
	-- for i, item in x300580_g_BonusChoiceItem do
	    -- AddQuestRadioItemBonus(sceneId, item.item, item.n)
	-- end

	
	EndQuestEvent()
	
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300580_g_ScriptId, MissionId,0);
end


---------------------------------------------------------------------------------------------------
--点击NpC开始游戏
---------------------------------------------------------------------------------------------------
function x300580_DispatchStartGame( sceneId, selfId, NPCId,MissionId )

	local myMissionId = x300580_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300580_g_MissionName)
		AddQuestText(sceneId,"\t请注意，考验已经开始")
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300580_g_ScriptId, MissionId,0);
	


end

---------------------------------------------------------------------------------------------------
--点击NpC挑战高难度
---------------------------------------------------------------------------------------------------
function x300580_DispatchDifficultLevel( sceneId, selfId, NPCId,MissionId, nExt )

	local myMissionId = x300580_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end



	
	
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300580_g_MissionName)
		AddQuestText(sceneId,format("\t第%d轮考验马上开始",x300580_Min_Step+nExt))
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300580_g_ScriptId, MissionId,0);
	


end




---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300580_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	local myMissionId = x300580_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300580_g_MissionName)
		AddQuestText(sceneId,"通过这次考验，你是否是百姓期待的人便可知晓！")
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300580_g_ScriptId, MissionId,0);
	


end







---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300580_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	local myMissionId = x300580_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	
	local nCurrentStep = GetQuestParam( sceneId, selfId, misIndex, x300580_G_GAMESTEP )
	
	local nCount =0;

	
	if nCurrentStep >= x300580_Min_Step then
		nCount = nCurrentStep
	else
		return 0
	end
	
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300580_g_MissionName)
		AddQuestText(sceneId,"\t#Y@myname#W，感谢上天眷顾！在你破解了水晶之谜后，远方海面上的狂风减退，乌云也渐渐消散开来。\n\t收下这些礼物，这是百姓对你的敬意。")
	
	local level = GetLevel(sceneId, selfId)
    for i, item in x300580_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end
	
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300580_g_ScriptId, MissionId);

end







---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300580_QuestLogRefresh( sceneId, selfId, MissionId)
	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没这个任务直接退出
		return 0
	end
		
	BeginQuestEvent(sceneId)	
			
		
	AddQuestLogCustomText( sceneId,
							"",						-- 标题
							x300580_GetMissionName(sceneId,selfId),        -- 任务名字
							x300580_GetMissionTask(sceneId,selfId),		--任务目标
							x300580_GetReplyNpcId(sceneId,selfId),			--任务NPC
							x300580_GetMissionMethod(sceneId,selfId),               --任务攻略
							x300580_GetMissionText(sceneId,selfId),	--任务描述
							x300580_GetMissionHelp(sceneId,selfId)					--任务小提示
							)

	--1、经验
	local level = GetLevel(sceneId, selfId)
    for i, item in x300580_g_RewardTable do
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
	
	-- --2.物品
	
	-- for i, item in x300580_g_BonusChoiceItem do
	    -- AddQuestRadioItemBonus(sceneId, item.item, item.n)
	-- end

	

	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	

end

function x300580_GetMissionName(sceneId,selfId)
	

	return x300580_g_MissionName;
end

function x300580_GetMissionTask(sceneId,selfId)
	local myMissionId = x300580_GetMissionId( sceneId, selfId )

	

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	
	local nValue = GetQuestParam( sceneId, selfId, misIndex, 0 )

	--local str = "  通过#G火雷弹安放图#W找到#G"..format("#W(%d/1)",nValue)
		local str = "  #Y任务回复:@npc_110102"
	
		
	return str;
end

function x300580_GetReplyNpcId(sceneId,selfId)
	
	return "@npc_"..x300580_g_ReplyNpcId
	
end

function x300580_GetMissionMethod(sceneId,selfId)
	return "\t记住四个采集点上的#G水晶特效颜色#W，每次随机闪烁特效，记住#G闪烁的次数和顺序#W，在特效播放过后，按照原有播放顺序依次点击四块#G小水晶#W完成考验。"
end

function x300580_GetMissionText(sceneId,selfId)
	return "\t这里流传着一个古老传说：海天遮日之时，会伴随巨大灾难，唯有破解水晶之谜，才能化解这一场浩劫。\n\t最近这几个月海面狂风肆虐，已经影响此地百姓的生活及我方部队的运输。同时北方海岸的古老水晶在沉寂数百年后再次不时发出四色光芒。\n\t#Y@myname#W，你是否愿意前去一探水晶的奥秘？"
end

function x300580_GetMissionHelp(sceneId,selfId)
	return ""
end


function x300580_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300580_QuestLogRefresh( sceneId, selfId, MissionId );
end





function x300580_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end




function x300580_OnClickBox( sceneId, selfId, nIndex)

	if GetGameOpenById(x300580_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300580_g_MissionId) == 0 then
		return 0
	end
	local myMissionId = x300580_GetMissionId( sceneId, selfId )

	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		x300580_ShowTips(sceneId, selfId, "你没有心诚则灵任务")
		return 0;
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )
	local nCurrentStep = GetQuestParam( sceneId, selfId, misIndex, x300580_G_GAMESTEP )

	if bCompleted>0 then
		if nCurrentStep<8 then
			x300580_ShowTips(sceneId, selfId, "恭喜你通过了考验，请去天云水晶处选择完成任务或挑战更高难度")
		else
			x300580_ShowTips(sceneId, selfId, "恭喜你通过了考验，请去天云水晶处完成任务")
		end
		return
	end

	if IsHaveSpecificImpact(sceneId, selfId, x300580_g_BuffId)<=0 then
		x300580_ShowTips(sceneId, selfId, "请点击天云水晶开始考验")
		return
	end

	local nAcitionFlag = GetQuestParam( sceneId, selfId, misIndex, x300580_G_ACTIONFLAG )
	

	if nCurrentStep<=0 then
		x300580_ShowTips(sceneId, selfId, "考验还未开始")
		return
	end

	if nAcitionFlag~=2 then
		x300580_ShowTips(sceneId, selfId, "现在还不能点击水晶")
		return
	end

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, x300580_G_QUESTIONID )

	local nAnswerStep = GetQuestParam( sceneId, selfId, misIndex, x300580_G_ANWER_STEP )+1

	local nCurrentAnswer = x300580_g_QuestList[nCurrentStep][nQuestionId][nAnswerStep]

	--x300580_ShowTips(sceneId, selfId, format("%d",nIndex))
	if nCurrentAnswer==nIndex then
		x300580_PlayGameEffect( sceneId, selfId, nIndex)
		SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_ANWER_STEP, nAnswerStep )
		x300580_ShowTips(sceneId, selfId, "正确！")

		if nAnswerStep>=nCurrentStep then
			x300580_OnOneRoundCompleted(sceneId, selfId)
		end
	else
		if (nCurrentStep-1)<x300580_Min_Step then
			x300580_ShowTips(sceneId, selfId, "错误！")
		else
		x300580_OnAnswerWrong(sceneId, selfId)
	end
	end
	
end

function x300580_OnAnswerWrong(sceneId, selfId)  --回答错误
	
	x300580_ShowTips(sceneId, selfId, format("回答错误，%d秒后重新开始第一轮",x300580_Round_wait))
	x300580_Restart(sceneId, selfId)
	
end


function x300580_Restart(sceneId, selfId) --重新开始答题
	if GetGameOpenById(x300580_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300580_g_MissionId) == 0 then
		return 0
	end
	local myMissionId = x300580_GetMissionId( sceneId, selfId )

	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		return 0;
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nCurrentStep = GetQuestParam( sceneId, selfId, misIndex, x300580_G_GAMESTEP )
	
	SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_GAMESTEP, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_ANWER_STEP, 0 )

	SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_FRAME, 0 )

	
	SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_ACTIONFLAG, 3 )	--动作Flag
	
	if IsHaveSpecificImpact(sceneId, selfId, x300580_g_BuffId)<=0 then
		SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId, x300580_g_BuffId,0 )  --给玩家加buff计时
		
	end
end


function x300580_OnOneRoundCompleted(sceneId, selfId)  --回答一轮完成
	if GetGameOpenById(x300580_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300580_g_MissionId) == 0 then
		return 0
	end
	local myMissionId = x300580_GetMissionId( sceneId, selfId )

	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		return 0;
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nCurrentStep = GetQuestParam( sceneId, selfId, misIndex, x300580_G_GAMESTEP )
	
	
	--SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_ANWER_STEP, 0 )

	
	SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_FRAME, 0 )

	if nCurrentStep==0 then
		SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_ACTIONFLAG, 3 )	--动作Flag
		x300580_ShowTips(sceneId, selfId, format("%d秒后开始第一轮考验",x300580_Round_wait))
	elseif nCurrentStep<x300580_Min_Step then
		SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_ACTIONFLAG, 3 )	--动作Flag
		x300580_ShowTips(sceneId, selfId, format("恭喜你通过本轮考验，%d秒后开始下一轮",x300580_Round_wait))
	elseif nCurrentStep<x300580_Max_Step then
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
		SetQuestByIndex( sceneId, selfId, misIndex, 0, 1 )

		SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_ACTIONFLAG, 4 )	--动作Flag
		x300580_ShowTips(sceneId, selfId, format("恭喜你通过前%d轮考验，你可以选择现在领取奖励，或者继续挑战第%d轮考验获得更高的奖励。",nCurrentStep,nCurrentStep+1))
	else
		SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_ACTIONFLAG, 10 )	--动作Flag
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
		SetQuestByIndex( sceneId, selfId, misIndex, 0, 1 )

		x300580_ShowTips(sceneId, selfId, "恭喜你，成功通过了所有的考验！")
	end

	if IsHaveSpecificImpact(sceneId, selfId, x300580_g_BuffId)<=0 then
		SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId, x300580_g_BuffId,0 )  --给玩家加buff计时
		
	end
end


function x300580_OnStartDifficultLevel(sceneId, selfId)  --开始高难度挑战
	if GetGameOpenById(x300580_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300580_g_MissionId) == 0 then
		return 0
	end
	local myMissionId = x300580_GetMissionId( sceneId, selfId )

	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		return 0;
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nCurrentStep = GetQuestParam( sceneId, selfId, misIndex, x300580_G_GAMESTEP )
	
	
	--SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_ANWER_STEP, 0 )

	
	SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_FRAME, 0 )

	
	SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_ACTIONFLAG, 3 )	--动作Flag
	x300580_ShowTips(sceneId, selfId, format("%d秒后开始第%d轮考验",x300580_Round_wait,nCurrentStep+1))

	if IsHaveSpecificImpact(sceneId, selfId, x300580_g_BuffId)<=0 then
		SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId, x300580_g_BuffId,0 )  --给玩家加buff计时
		
	end
end


function x300580_OnPlayNextRound(sceneId, selfId)
	if GetGameOpenById(x300580_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300580_g_MissionId) == 0 then
		return 0
	end
	local myMissionId = x300580_GetMissionId( sceneId, selfId )

	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		return 0;
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nCurrentStep = GetQuestParam( sceneId, selfId, misIndex, x300580_G_GAMESTEP )+1

	SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_GAMESTEP, nCurrentStep )

	x300580_StartChuTi(sceneId, selfId, nCurrentStep)
end

function x300580_PlayGameEffect( sceneId, selfId, nIndex)
	CallScriptFunction(UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 25+nIndex )
end

------------------------------------------------
-- buff start 
-------------------------------------------------
--间隔发作时调用
function x300580_OnIntervalOverEvent( sceneId, selfId )

	
	
	local myMissionId = x300580_GetMissionId( sceneId, selfId )

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		return 0;
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )

	if bCompleted>0 then
		return
	end

	

	local nCurrentStep = GetQuestParam( sceneId, selfId, misIndex, x300580_G_GAMESTEP )

	if nCurrentStep<0 then
		return
	end

	local nActionFlag = GetQuestParam( sceneId, selfId, misIndex, x300580_G_ACTIONFLAG )
	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, x300580_G_QUESTIONID )
	local nFrame = GetQuestParam( sceneId, selfId, misIndex, x300580_G_FRAME )+1  --当前是第几帧

	if nActionFlag==1 then --出题
		SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_FRAME, nFrame )
			
		if nFrame<=nCurrentStep then
			
			local nIndex = x300580_g_QuestList[nCurrentStep][nQuestionId][nFrame]

			x300580_PlayGameEffect( sceneId, selfId, nIndex)
		end

		if nFrame>=nCurrentStep+x300580_g_Answer_Wait then
			SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_FRAME, 0 )
			SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_ANWER_STEP, 0 )
			SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_ACTIONFLAG, 2 ) --等于2表示播放完毕，等待玩家输入
			x300580_ShowTips(sceneId, selfId, "可以开始按照刚才发光的顺序点击小水晶了")	
		end
	elseif nActionFlag==3 then  --答完等待出题
		SetQuestByIndex( sceneId, selfId, misIndex, x300580_G_FRAME, nFrame )
		if nFrame>=x300580_Round_wait then
			x300580_OnPlayNextRound(sceneId, selfId)
		end
	end

	

	
	
end

--生效时调用
function x300580_OnActiveEvent( sceneId, selfId )

end

--效果消散时调用
function x300580_OnFadeOutEvent( sceneId, selfId )

	
end


------------------------------------------------
-- buff end 
-------------------------------------------------













