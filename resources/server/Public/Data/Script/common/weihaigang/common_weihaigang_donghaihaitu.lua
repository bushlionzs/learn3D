--***********************
--Const
--***********************
-------------------------

--MisDescBegin


x300577_g_MissionId 				= 	9333                     --任务ID
x300577_g_ScriptId 					= 	300577                  --脚本ID
x300577_g_MissionKind 				= 	1                       --任务类型
x300577_g_LevelLess					= 	40                      --场景开放等级  <=0 表示不限制


x300577_g_MissionName				= 	"【个人】东海海图"
x300577_g_MissionName1				= 	"你听说过“东海海图”吗？"
x300577_g_MissionTarget				= 	"和扬武号的每个水手交谈，打听东海海图的下落。"
x300577_g_MissionInfo				= 	""
x300577_g_ContinueInfo				= 	""
x300577_g_MissionCompleted			= 	""
x300577_g_MissionHelp				=	"东海海图应该在扬武号的某个水手手中，但是他并不会把海图轻易交给你。"          --任务提示信息

--目标
x300577_g_ExtTarget					=	{ {type=20,n=1,target="东海海图"}}

--奖励

x300577_g_ExpBonus					= 	0;--x300577_AddExpAward               	--奖励：经验
x300577_g_BonusItem					=	{{item=11000202, n=8}}	--奖励：物品

x300577_g_BonusMoney1               = 	0
x300577_g_BonusMoney2               =   0
x300577_g_BonusMoney3               =   0

x300577_g_BonusChoiceItem           =   {}


--MisDescEnd


x300577_g_NpcList = {143099,143100,143101,143102,143103,143104,143105,143106}
x300577_g_ItemAcceptMission  = 13810129   --接任务是给的物品
x300577_g_ItemChain = {13810121,13810122,13810123,13810124,13810125,13810126,13810127}  --7个中间物品
x300577_g_ItemSubmitMission  = 13810120  --交任务时所需物品


x300577_g_RandomCount =10
x300577_g_RandomList = {
							{1,2,3,4,5,6,7,8},
							{8,7,6,5,4,3,2,1},
							{1,3,5,7,2,4,6,8},
							{2,4,6,8,1,3,5,7},
							{6,8,4,1,5,3,7,2},
							{2,4,6,5,8,3,1,7},
							{4,5,6,7,1,8,2,3},
							{3,4,6,5,8,7,2,1},
							{4,7,8,5,6,3,2,1},
							{2,3,4,5,6,7,8,1}
						}


x300577_g_ReplyNpcId = 143146

x300577_g_PositionId = 85054

x300577_g_GameId	= 1014

x300577_g_BuffId    = 7714
-- 物品奖励
x300577_g_ItemId    = 12030028

	
-- 任务奖励物品列表
x300577_g_RewardTable       = {
                                { minLevel = 40, maxLevel = 60,  items = { { id = 11000201, cnt = 8 }, { id = 11050002, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 60, maxLevel = 80,  items = { { id = 11000202, cnt = 8 }, { id = 11050003, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 80, maxLevel = 999, items = { { id = 11000203, cnt = 8 }, { id = 11050004, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
}






function x300577_GetMissionId( sceneId, selfId )
	return x300577_g_MissionId
end

function x300577_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	if MissionId==nil then
		return
	end

	local level = GetLevel( sceneId,selfId )
    if level < x300577_g_LevelLess then
       return
    end

	local myMissionId = x300577_GetMissionId( sceneId, selfId )
	
	if MissionId~=myMissionId then
		return
	end
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		AddQuestNumText(sceneId, myMissionId, x300577_g_MissionName,8,1);
	else
		local state = GetQuestStateNM(sceneId, selfId, targetId, myMissionId);

		
		AddQuestNumText(sceneId, myMissionId, x300577_g_MissionName,state,state);

	end


	
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300577_ProcEventEntry( sceneId, selfId, targetId, MissionId, nExt )
	
	if GetGameOpenById(x300577_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300577_g_MissionId) == 0 then
		x300577_ShowTips(sceneId, selfId, "此活动今天不开放，详情请到大都包打处听查询每日新鲜事")
		return
	end

	local myMissionId = x300577_GetMissionId( sceneId, selfId )	
	
	
	
	
	if nExt>10 then --跟npc对话时
		if nExt>=20 then
			return
		end

		local iIndex = nExt-10

		if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
			return
		end

		x300577_DispatchNpcTalkInfo( sceneId, selfId, targetId,myMissionId,iIndex )

	
	else
		
		if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
			x300577_DispatchMissionInfo( sceneId, selfId, targetId, myMissionId, 0 )
		else
			if nExt==7 then -- 任务完成
				x300577_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
				
				
			else
				
				x300577_DispatchContinueInfo( sceneId, selfId, targetId,myMissionId )
			end
		end
	end
end


function x300577_ProcAcceptCheck(sceneId, selfId, targetId, MissionId )
	
	if GetGameOpenById(x300577_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300577_g_MissionId) == 0 then
		
		return 0;
	end
	return 1;

end

function x300577_CheckRequest(sceneId, selfId)
	if GetGameOpenById(x300577_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300577_g_MissionId) == 0 then
		x300577_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0
	end
	local myMissionId = x300577_GetMissionId( sceneId, selfId )

	if GetLevel(sceneId, selfId) <x300577_g_LevelLess then
		x300577_ShowTips(sceneId, selfId, "你等级不足")
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) > 0 then
		x300577_ShowTips(sceneId, selfId, "你已经有这个任务，请先完成这个任务")
		return 0;
	end

    local day = GetDayOfYear()
    if GetQuestData(sceneId, selfId, MD_DHHT_DATE[1], MD_DHHT_DATE[2],MD_DHHT_DATE[3] ) == day then
        x300577_ShowTips(sceneId, selfId, "很抱歉，您今天已经做过此任务，不能再次领取")
        return 0;
    end

    if GetQuestData( sceneId, selfId, MD_RICHANG_DAY[ 1], MD_RICHANG_DAY[ 2], MD_RICHANG_DAY[ 3] ) == day then
        if GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[ 1], MD_RICHANG_COUNT[ 2], MD_RICHANG_COUNT[ 3] ) >= 3 then
            Msg2Player( sceneId, selfId, "你不能再领取今天的日常任务了", 8, 3)
            return 0
        end
    else
        SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 0)
    end

	return 1;

end

function x300577_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
	
	
	if GetGameOpenById(x300577_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300577_g_MissionId) == 0 then
		x300577_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	

	if x300577_CheckRequest(sceneId, selfId)<=0 then
		
		return 0;
	end

	local myMissionId = x300577_GetMissionId( sceneId, selfId )

	--------------------------- add for Mission full check --------------
	local bFullMission = IsQuestFullNM(sceneId,selfId)
	
	if bFullMission>0 then
		x300577_ShowTips(sceneId, selfId, "任务已满，无法接受任务")
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

	

	local ret = AddQuest( sceneId, selfId, myMissionId, x300577_g_ScriptId, 0, 0, 0,1)-- 给玩家添加任务		
		
	if ret > 0 then

		BeginAddItem(sceneId)
		AddItem( sceneId, x300577_g_ItemAcceptMission, 1 )
		
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
			
			AddItemListToPlayer(sceneId,selfId)
			
			
			
		else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"背包空间不足，无法领取本任务。")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)

			DelQuestNM( sceneId, selfId, myMissionId )

			return 0;	
		end


		local str = "您接受了任务："..x300577_g_MissionName;
		x300577_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)
		
		local myMissionId = x300577_GetMissionId( sceneId, selfId )
		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
		
		
		local nRandomType = random(1,x300577_g_RandomCount)

		SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300577_g_BuffId, 0)

		SetQuestByIndex( sceneId, selfId, misIndex, 6, nRandomType )
		SetQuestByIndex( sceneId, selfId, misIndex, 5, 1 )
		GamePlayScriptLog(sceneId, selfId, 841)
		return 1
	else
		
		x300577_ShowTips(sceneId, selfId, "接受任务错误")
	
	end


end

function x300577_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x300577_ProcQuestAbandon( sceneId, selfId, MissionId )

	local myMissionId = x300577_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	

	local n = GetItemCount( sceneId, selfId, x300577_g_ItemAcceptMission );
	if n > 0 then
		DelItem(sceneId, selfId,x300577_g_ItemAcceptMission,n)
		
	end

	n = GetItemCount( sceneId, selfId, x300577_g_ItemSubmitMission );
	if n > 0 then
		DelItem(sceneId, selfId,x300577_g_ItemSubmitMission,n)
		
	end

	for i,item in x300577_g_ItemChain do
		n = GetItemCount( sceneId, selfId, item );
		if n > 0 then
			DelItem(sceneId, selfId,item,n)
			
		end
	end




	local ret = DelQuestNM( sceneId, selfId, myMissionId )

	if ret>0 then

		local str = "您放弃了任务："..x300577_g_MissionName;
	    x300577_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)

        local today = GetDayOfYear()
		SetQuestData( sceneId, selfId, MD_DHHT_DATE[1], MD_DHHT_DATE[2], MD_DHHT_DATE[3], today)
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
		x300577_ShowTips(sceneId, selfId, "放弃任务失败")
	end

	
end



function x300577_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	
	if GetGameOpenById(x300577_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300577_g_MissionId) == 0 then
		x300577_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	local myMissionId = x300577_GetMissionId( sceneId, selfId )
	
	if x300577_CheckSubmit(sceneId, selfId )>0 then
		local today = GetDayOfYear()
        local count = GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3] )
        if today == GetQuestData(sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2],MD_RICHANG_DAY[3] ) and count >= 3 then
            Msg2Player( sceneId, selfId, "今天的日常任务已经不能再交了，请明天再来", 8, 3)
            return 0
        end

		local nRet = x300577_GiveReward(sceneId,selfId,selectId)

		if nRet<=0 then
			return
		end
		local ret = DelQuestNM( sceneId, selfId, myMissionId )

		if ret>0 then
            CallScriptFunction( 270300, "OnSubmissionFinished", sceneId, selfId, x300577_g_MissionId)

			local str = "您完成了任务:"..x300577_g_MissionName;
			x300577_ShowTips(sceneId, selfId, str)
			Msg2Player(sceneId,selfId,str,8,2)

			local n = GetItemCount( sceneId, selfId, x300577_g_ItemSubmitMission );
			if n > 0 then
				DelItem(sceneId, selfId,x300577_g_ItemSubmitMission,n)
				
			
			end

            SetQuestData( sceneId, selfId, MD_DHHT_DATE[1], MD_DHHT_DATE[2], MD_DHHT_DATE[3], GetDayOfYear() )

            --if IsHaveSpecificImpact( sceneId, selfId, x300577_g_BuffId) == 1 then
            --    CancelSpecificImpact( sceneId, selfId, x300577_g_BuffId)
            --    if random( 1, 100) <= 20 then
            --        --BeginAddItem( sceneId)
            --        Msg2Player( sceneId, selfId, format( "%s实在了得，在非常短的时间内就找回了东海海图。", 
            --            GetName( sceneId, selfId) ), CHAT_TYPE_WORLD, CHAT_MAIN_WINDOW)
            --    end
            --end
            if IsHaveSpecificImpact( sceneId, selfId, x300577_g_BuffId) == 1 then
                CancelSpecificImpact( sceneId, selfId, x300577_g_BuffId)
                if random( 1, 100) <= 20 then
                    BeginAddItem( sceneId)
                    AddItem( sceneId, x300577_g_ItemId, 1)
                    local ret = EndAddItem( sceneId, selfId)
                    if ret == 1 then
                        AddItemListToPlayer( sceneId, selfId)
                        LuaThisScenceM2Wrold( sceneId, format( "%s实在了得，在非常短的时间内就找回了东海海图，特奖励一个@item_%d。", 
                            GetName( sceneId, selfId), x300577_g_ItemId), 1, 1)
                    else
                        Msg2Player( sceneId, selfId, "物品栏已满，无法获得物品", 8, 3)
                    end
                end
            end

			GamePlayScriptLog(sceneId, selfId, 842)
			
		else
			x300577_ShowTips(sceneId, selfId, "交任务失败")
		end
		
	end
end

function x300577_GiveReward(sceneId,selfId,selectRadioId)
	
	if GetGameOpenById(x300577_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300577_g_MissionId) == 0 then
		x300577_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	

	local level = GetLevel( sceneId, selfId)
    local canBind = 0
    local count = 0
    local id = 0
    for i, item in x300577_g_RewardTable do
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
        for i, item in x300577_g_RewardTable do
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



function x300577_CheckSubmit(sceneId, selfId )
	
	if GetGameOpenById(x300577_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300577_g_MissionId) == 0 then
		x300577_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	local myMissionId = x300577_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )
	

	if (bCompleted)<=0 then
		return 0
	end

	local n = GetItemCount( sceneId, selfId, x300577_g_ItemSubmitMission );
	if n > 0 then
		return 1;
		
	else
		x300577_ShowTips(sceneId, selfId, "所需任务道具不足")
		return 0;
	end

	return 1;
end



---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x300577_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId, nExt )

	
	
	BeginQuestEvent(sceneId)

		
	
	AddQuestText(sceneId,"#Y"..x300577_g_MissionName)
	AddQuestText(sceneId,"\t我大元水师东征在即，马可波罗大人前日派遣他的副使携带#G东海海图#W前来威海港。\n\t不料，这位副使大人一时贪杯，不慎将这东海海图遗失。\n\t多方寻找之下，我们发现此图落入了扬武号某个水手的手中。你可否帮忙去将那海图取回？我给你准备了些东西，你可以用这个来和水手们打交道。")
	AddQuestText( sceneId,"#Y任务目标:")
			
	AddQuestText( sceneId,x300577_g_MissionTarget)
	AddQuestText(sceneId," ")

	--1、经验
	local level = GetLevel(sceneId, selfId)
    for i, item in x300577_g_RewardTable do
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

	
	-- for i, item2 in x300577_g_BonusItem do
		
		-- AddQuestItemBonus(sceneId, item2.item, item2.n)
		
	-- end

	EndQuestEvent()
	
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300577_g_ScriptId, MissionId,0);
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300577_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	local myMissionId = x300577_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300577_g_MissionName)
		AddQuestText(sceneId,"\t此图事关重大，不仅东海沿岸的地形地貌，连很多无人知晓的小岛的标注都尽在其中。若是落入敌国之手，后果不堪设想啊。")
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300577_g_ScriptId, MissionId,0);
	


end







---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300577_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	local myMissionId = x300577_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300577_g_MissionName)
		AddQuestText(sceneId,"\t你真的将这东海海图完好无损的带回来了？太好了！#Y@myname#W，这是你应得的奖励！")
	
	
	
	--1、经验
	local level = GetLevel(sceneId, selfId)
    for i, item in x300577_g_RewardTable do
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

	-- for i, item2 in x300577_g_BonusItem do
		
		-- AddQuestItemBonus(sceneId, item2.item, item2.n)
		
	-- end
		
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300577_g_ScriptId, MissionId);

end



function x300577_DispatchNpcTalkInfo( sceneId, selfId, NPCId,MissionId,iIndex )
	local myMissionId = x300577_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )


	local nRandomType = GetQuestParam( sceneId, selfId, misIndex, 6 )



	local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

	
	
	
	
	local nCurrentStep = x300577_g_RandomList[nRandomType][nStep];


	local nPosInList =0
	for i,item in x300577_g_RandomList[nRandomType] do
		nPosInList = nPosInList+1
		if item==iIndex then
			break;
		end
	end

	if iIndex==nCurrentStep then --如果就是要找的npc

			
		
		SetQuestByIndex( sceneId, selfId, misIndex, 4, iIndex )  --保存点的哪个npc

		SetQuestByIndex( sceneId, selfId, misIndex, 3, NPCId )  --保存点npc id

		local item1=0;
		local item2=0
		if nPosInList==1 then
			item1 = x300577_g_ItemAcceptMission
			item2 = x300577_g_ItemChain[1]
		elseif nPosInList==2 then
			item1 = x300577_g_ItemChain[1]
			item2 = x300577_g_ItemChain[2]
		elseif nPosInList==3 then
			item1 = x300577_g_ItemChain[2]
			item2 = x300577_g_ItemChain[3]
		elseif nPosInList==4 then
			item1 = x300577_g_ItemChain[3]
			item2 = x300577_g_ItemChain[4]
		elseif nPosInList==5 then
			item1 = x300577_g_ItemChain[4]
			item2 = x300577_g_ItemChain[5]
		elseif nPosInList==6 then
			item1 = x300577_g_ItemChain[5]
			item2 = x300577_g_ItemChain[6]
		elseif nPosInList==7 then
			item1 = x300577_g_ItemChain[6]
			item2 = x300577_g_ItemChain[7]
		elseif nPosInList==8 then
			item1 = x300577_g_ItemChain[7]
			item2 = x300577_g_ItemSubmitMission
		else
			return
		end

		local str= "\t东海海图？唔......有那么点印象。\n\t不过，我现在很想要那@item_"..item1.."#W，我愿意用我的@item_"..item2.."#W来交换，或许能对你找那海图有点用处。"
		
		


		x300577_DispatchExchangeInfo( sceneId, selfId, NPCId, str,item1,item2 )

		return
	end


	
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300577_g_MissionName)
		

		if iIndex==nCurrentStep then --如果就是要找的npc

			

			return

			
		
		else
			if nPosInList==1 then
				AddQuestText(sceneId,"\t东海海图？唔......有那么点印象。\n\t不过，我现在很想要那@item_"..x300577_g_ItemAcceptMission.."#W，我愿意用我的@item_"..x300577_g_ItemChain[1].."#W来交换，或许能对你找那海图有点用处。")
			elseif nPosInList==2 then
				AddQuestText(sceneId,"\t东海海图？唔......有那么点印象。\n\t不过，我现在很想要那@item_"..x300577_g_ItemChain[1].."#W，我愿意用我的@item_"..x300577_g_ItemChain[2].."#W来交换，或许能对你找那海图有点用处。")
			elseif nPosInList==3 then
				AddQuestText(sceneId,"\t东海海图？唔......有那么点印象。\n\t不过，我现在很想要那@item_"..x300577_g_ItemChain[2].."#W，我愿意用我的@item_"..x300577_g_ItemChain[3].."#W来交换，或许能对你找那海图有点用处。")
			elseif nPosInList==4 then
				AddQuestText(sceneId,"\t东海海图？唔......有那么点印象。\n\t不过，我现在很想要那@item_"..x300577_g_ItemChain[3].."#W，我愿意用我的@item_"..x300577_g_ItemChain[4].."#W来交换，或许能对你找那海图有点用处。")
			elseif nPosInList==5 then
				AddQuestText(sceneId,"\t东海海图？唔......有那么点印象。\n\t不过，我现在很想要那@item_"..x300577_g_ItemChain[4].."#W，我愿意用我的@item_"..x300577_g_ItemChain[5].."#W来交换，或许能对你找那海图有点用处。")
			elseif nPosInList==6 then
				AddQuestText(sceneId,"\t东海海图？唔......有那么点印象。\n\t不过，我现在很想要那@item_"..x300577_g_ItemChain[5].."#W，我愿意用我的@item_"..x300577_g_ItemChain[6].."#W来交换，或许能对你找那海图有点用处。")
			elseif nPosInList==7 then
				AddQuestText(sceneId,"\t东海海图？唔......有那么点印象。\n\t不过，我现在很想要那@item_"..x300577_g_ItemChain[6].."#W，我愿意用我的@item_"..x300577_g_ItemChain[7].."#W来交换，或许能对你找那海图有点用处。")
			elseif nPosInList==8 then
				AddQuestText(sceneId,"\t东海海图？这你可算是问对人了！\n\t不过，没有那@item_"..x300577_g_ItemChain[7].."#W，我是绝不会把@item_"..x300577_g_ItemSubmitMission.."#W交给你的！")
			else
				return
			end
		end
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300577_g_ScriptId, myMissionId,0);

	

end


---------------------------------------------------------------------------------------------------
--交换物品显示
---------------------------------------------------------------------------------------------------
function x300577_DispatchExchangeInfo( sceneId, selfId, NPCId, str,item1,item2 )

	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId,"#Y"..x300577_g_MissionName)
		AddQuestText(sceneId,str)
		--AddQuestText(sceneId," ")

		


	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, NPCId, x300577_g_ScriptId, -1);
end



----------------------------------------------------------------------------------------------
--点确定后
----------------------------------------------------------------------------------------------
function x300577_ProcAccept( sceneId, selfId )

	local myMissionId = x300577_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )


	local nRandomType = GetQuestParam( sceneId, selfId, misIndex, 6 )

	local iIndex = GetQuestParam( sceneId, selfId, misIndex, 4 )
	local npcID = GetQuestParam( sceneId, selfId, misIndex, 3 )



	local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

	
	
	local nPosInList =0
	for i,item in x300577_g_RandomList[nRandomType] do
		nPosInList = nPosInList+1
		if item==iIndex then
			break;
		end
	end
	
	local nCurrentStep = x300577_g_RandomList[nRandomType][nStep];

	
	
	if iIndex~=nCurrentStep then
		return
	end

	

	local item1=0;
	local item2=0
	if nPosInList==1 then
		item1 = x300577_g_ItemAcceptMission
		item2 = x300577_g_ItemChain[1]
	elseif nPosInList==2 then
		item1 = x300577_g_ItemChain[1]
		item2 = x300577_g_ItemChain[2]
	elseif nPosInList==3 then
		item1 = x300577_g_ItemChain[2]
		item2 = x300577_g_ItemChain[3]
	elseif nPosInList==4 then
		item1 = x300577_g_ItemChain[3]
		item2 = x300577_g_ItemChain[4]
	elseif nPosInList==5 then
		item1 = x300577_g_ItemChain[4]
		item2 = x300577_g_ItemChain[5]
	elseif nPosInList==6 then
		item1 = x300577_g_ItemChain[5]
		item2 = x300577_g_ItemChain[6]
	elseif nPosInList==7 then
		item1 = x300577_g_ItemChain[6]
		item2 = x300577_g_ItemChain[7]
	elseif nPosInList==8 then
		item1 = x300577_g_ItemChain[7]
		item2 = x300577_g_ItemSubmitMission
	else
		return
	end
	
	

	
	
	local n = GetItemCount( sceneId, selfId, item1 );
	if n > 0 then
		DelItem(sceneId, selfId,item1,n)
		
	else
		x300577_ShowTips(sceneId,selfId, "#W你好像丢失了@item_"..item1.."#W，任务已失败请放弃。")
		return
	end

	

	BeginAddItem(sceneId)
	AddItem( sceneId, item2, 1 )
	
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		
		AddItemListToPlayer(sceneId,selfId)
		
		
		
	else
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"你的背包已满，请清理物品栏后再来。")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

		DelQuestNM( sceneId, selfId, myMissionId )

		return 0;	
	end


	SetQuestByIndex( sceneId, selfId, misIndex, 5, nStep+1 ) --完成sub任务

	if(nStep==8) then
		SetQuestByIndex( sceneId, selfId, misIndex, 0, 1 )
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
	end


	x300577_QuestLogRefresh( sceneId, selfId, myMissionId );


	
		

	x300577_ShowTips(sceneId,selfId, "#W你用@item_"..item1.."#W换到了@item_"..item2)
	
		
end






---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300577_QuestLogRefresh( sceneId, selfId, MissionId)
	
	
		
	BeginQuestEvent(sceneId)	
			
		
	AddQuestLogCustomText( sceneId,
							"",						-- 标题
							x300577_GetMissionName(sceneId,selfId),        -- 任务名字
							x300577_GetMissionTask(sceneId,selfId),		--任务目标
							"@npc_"..x300577_GetReplyNpcId(sceneId,selfId),			--任务NPC
							x300577_GetMissionMethod(sceneId,selfId),               --任务攻略
							x300577_GetMissionText(sceneId,selfId),	--任务描述
							x300577_GetMissionHelp(sceneId,selfId)					--任务小提示
							)

	--1、经验
	local level = GetLevel(sceneId, selfId)
    for i, item in x300577_g_RewardTable do
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

	-- for i, item2 in x300577_g_BonusItem do
		
		-- AddQuestItemBonus(sceneId, item2.item, item2.n)
		
	-- end

	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	

end

function x300577_GetMissionName(sceneId,selfId)
	

	return x300577_g_MissionName;
end

function x300577_GetMissionTask(sceneId,selfId)
	local myMissionId = x300577_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	
	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	local strTable = "  ";
	local str1 = strTable.."去@npc_85055和@npc_85056的扬武号的水手那里找回#G东海海图#W"..format("(%d/1)",value1)

	if value1>=1 then
		str1 = "#G"..str1
	else
		str1 = "#W"..str1
	end

	return str1
end

function x300577_GetReplyNpcId(sceneId,selfId)
	return x300577_g_ReplyNpcId;
end

function x300577_GetMissionMethod(sceneId,selfId)
	return "\t#G东海海图#W应该落在扬武号的某个水手手中，去问问他们吧。"
end

function x300577_GetMissionText(sceneId,selfId)
	return "\t我大元水师东征在即，马可波罗大人前日派遣他的副使携带#G东海海图#W前来威海港。\n\t不料，这位副使大人一时贪杯，不慎将这东海海图遗失。\n\t多方寻找之下，我们发现此图落入了扬武号某个水手的手中。你可否帮忙去将那海图取回？"
end

function x300577_GetMissionHelp(sceneId,selfId)
	return "\t扬武号的水手们可不是那么好打交道，他们不会白白告诉你海图的下落。"
end



function x300577_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300577_QuestLogRefresh( sceneId, selfId, MissionId );
end

--// system function start
function x300577_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )

	
	local myMissionId = x300577_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	

	
	
	
	local bFind =0;
	local iIndex=0
	for i,item in x300577_g_NpcList do
		iIndex = iIndex+1;
		if npcGuid==item then
			bFind=1;
			break;
		end
	end

	

	if bFind==0 then
		return
	end

	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )

	if bCompleted>0 then
		return
	end

	local nRandomType = GetQuestParam( sceneId, selfId, misIndex, 6 )



	local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

	
	
	local nPosInList =0
	for i,item in x300577_g_RandomList[nRandomType] do
		nPosInList = nPosInList+1
		if item==iIndex then
			break;
		end
	end
	
	

	if nPosInList>=nStep then --只响应完成的npc
	
	
		AddQuestNumText(sceneId, x300577_g_MissionId, x300577_g_MissionName1,2,iIndex+10);
	end
	
	
	

	
end


function x300577_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end



--// system end




