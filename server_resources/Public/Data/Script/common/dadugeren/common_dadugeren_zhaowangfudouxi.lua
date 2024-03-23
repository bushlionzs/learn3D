--***********************
--Const
--***********************
-------------------------

--MisDescBegin


x300563_g_MissionId 				= 	9301                     --任务ID
x300563_g_ScriptId 					= 	300563                  --脚本ID
x300563_g_MissionKind 				= 	1                       --任务类型
x300563_g_LevelLess					= 	40                      --场景开放等级  <=0 表示不限制


x300563_g_MissionName				= 	"【个人】赵王府斗戏"
x300563_g_MissionName1				= 	"斗戏要开始了！"
x300563_g_MissionTarget				= 	"找到@npc_139114"
x300563_g_MissionInfo				= 	""
x300563_g_ContinueInfo				= 	""
x300563_g_MissionCompleted			= 	""
x300563_g_MissionHelp				=	""          --任务提示信息

--目标
x300563_g_ExtTarget					=	{ {type=20,n=1,target="赵王府斗戏"}}

--奖励

x300563_g_ExpBonus					= 	0;--x300563_AddExpAward               	--奖励：经验
x300563_g_BonusItem					=	{{item=11000201,n=8}}	--奖励：物品

x300563_g_BonusMoney1               = 	0
x300563_g_BonusMoney2               =   0
x300563_g_BonusMoney3               =   0

x300563_g_BonusChoiceItem           =   {}


--MisDescEnd

x300563_g_NpcList = {141501,141502,141503,141504,141505}
x300563_g_ReplyNpcId = 139114

x300563_g_GameId	= 1002

x300563_g_BuffId    = 7713
-- 物品奖励
x300563_g_ItemId    = 12030028
												
x300563_g_NpcTalkCount1 = 3
x300563_g_NpcTalkList1={"我虽是见宰相，似文王施礼；一头地离明妃，早宋玉悲秋。啊呀！戏要开演？老夫这就前往。","今日之事，宜相开譬。刘备负国，是非未决，羽亦何敢重欲干命！啊呀！戏要开演？老夫这就前往。","国家区区本以土地借卿家者，卿家军败远来，无以为资故也。今已得益州，既无奉还之意，但求三郡，又不从命。啊呀！戏要开演？老夫这就前往。"}	
	
x300563_g_NpcTalkCount2 = 3
x300563_g_NpcTalkList2={"十年不识君王面，始信婵娟解误人。戏要开演？小生知晓了。","老夫人事已休，将恩变为仇，著小生半途喜变作忧。红娘你且先行，教小姐权时落后。 戏要开演？小生知晓了。","满腹闲愁，数年禁受，天知否？天若是知我情由，怕不待和天瘦。戏要开演？小生知晓了。"}	

x300563_g_NpcTalkCount3 = 3
x300563_g_NpcTalkList3={"月色溶溶夜，花阴寂寂春；如何临皓魄，不见月中人？ 奴家这就去戏台~","待不寻思，怎奈心肠软，告天，天不应，奈何天。奴家这就去戏台~","晚妆残，乌云彩掸，轻匀了粉脸，乱挽起云鬟。将简贴儿拈，把妆盒儿按，开折封皮孜孜看，颠来倒去不害心烦。奴家这就去戏台~"}	

x300563_g_NpcTalkCount4 = 3
x300563_g_NpcTalkList4={"乌林之役，左将军身在行间，寝不脱介，戮力破魏，岂得徒劳，无一块壤，而足下来欲收地邪？勿需多言，关某自知前往。","夫土地者，惟德所在耳，何常之有！勿需多言，关某自知前往。","过五关斩六将，土鸡瓦狗也敢当道？勿需多言，关某自知前往。"}	

x300563_g_NpcTalkCount5 = 3
x300563_g_NpcTalkList5={"快行动些，误了时辰也。\n我已听那锣鼓声，洒家这就前去。","这等三伏天道，你便有冲天的怨气，也召不得一片雪来，可不胡说！我已听那锣鼓声，洒家这就前去。","这死罪必有冤枉，早两桩儿应验了，不知亢旱三年的说话，准也不准？且看后来如何。左右，也不必等待雪晴，便与我抬他尸首，还了那蔡婆婆去罢。我已听那锣鼓声，洒家这就前去。"}	
		


-- 任务奖励物品列表
x300563_g_RewardTable       = {
                                { minLevel = 40, maxLevel = 60,  items = { { id = 11000201, cnt = 8 }, { id = 11050002, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 60, maxLevel = 80,  items = { { id = 11000202, cnt = 8 }, { id = 11050003, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 80, maxLevel = 999, items = { { id = 11000203, cnt = 8 }, { id = 11050004, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
}



function x300563_GetMissionId( sceneId, selfId )
	return x300563_g_MissionId
end

function x300563_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	local level = GetLevel( sceneId,selfId )
    if level < x300563_g_LevelLess then
       return
    end

	local myMissionId = x300563_GetMissionId( sceneId, selfId )
	
	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		AddQuestNumText(sceneId, myMissionId, x300563_g_MissionName,8,1);
	else
		--local state = GetQuestStateNM(sceneId, selfId, targetId, myMissionId);

		
		--AddQuestNumText(sceneId, myMissionId, x300563_g_MissionName,state,state);

	end


	
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300563_ProcEventEntry( sceneId, selfId, targetId, MissionId, nExt )
	
	if GetGameOpenById(x300563_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300563_g_MissionId) == 0 then
		x300563_ShowTips(sceneId, selfId, "此活动今天不开放，详情请到大都包打处听查询每日新鲜事")
		return
	end

	local myMissionId = x300563_GetMissionId( sceneId, selfId )	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId )>0 then
		if nExt==30 then
			x300563_GiveQuestion(sceneId, selfId, targetId, MissionId,2)
			return
		end
	end

	
	
	if nExt>10 then --跟npc对话时
		if nExt>=20 then
			return
		end

		local iIndex = nExt-10

		if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
			return
		end

		x300563_DispatchNpcTalkInfo( sceneId, selfId, targetId,myMissionId,iIndex )

	
	else
		
		if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
			x300563_DispatchMissionInfo( sceneId, selfId, targetId, myMissionId, 0 )
		else
			if nExt==7 then -- 任务完成
				x300563_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
				
				
			else
				
				x300563_DispatchContinueInfo( sceneId, selfId, targetId,myMissionId )				
			end
		end
	end
	    	
end


function x300563_ProcAcceptCheck(sceneId, selfId, targetId, MissionId )
	
	if GetGameOpenById(x300563_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300563_g_MissionId) == 0 then
		
		return 0;
	end
	return 1;

end

function x300563_CheckRequest(sceneId, selfId)
	if GetGameOpenById(x300563_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300563_g_MissionId) == 0 then
		x300563_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0
	end
	local myMissionId = x300563_GetMissionId( sceneId, selfId )

	if GetLevel(sceneId, selfId) <x300563_g_LevelLess then
		x300563_ShowTips(sceneId, selfId, "你等级不足")
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) > 0 then
		x300563_ShowTips(sceneId, selfId, "你已经有这个任务，请先完成这个任务")
		return 0;
	end

    local day = GetDayOfYear()
    if day == GetQuestData( sceneId, selfId, MD_ZDOUXI_DATE[1], MD_ZDOUXI_DATE[2],MD_ZDOUXI_DATE[3] ) then
        Msg2Player( sceneId, selfId, "很抱歉，您今天已经做过此任务，不能再次领取", 8, 3)
        return 0
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

function x300563_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
	
	
	if GetGameOpenById(x300563_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300563_g_MissionId) == 0 then
		x300563_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	if x300563_CheckRequest(sceneId, selfId)<=0 then
		
		return 0;
	end

	local myMissionId = x300563_GetMissionId( sceneId, selfId )

	--------------------------- add for Mission full check --------------
	local bFullMission = IsQuestFullNM(sceneId,selfId)
	
	if bFullMission>0 then
		x300563_ShowTips(sceneId, selfId, "任务已满，无法接受任务")
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

    if GetQuestData( sceneId, selfId, MD_RICHANG_DAY[ 1], MD_RICHANG_DAY[ 2], MD_RICHANG_DAY[ 3] ) == GetDayOfYear() then
        if GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[ 1], MD_RICHANG_COUNT[ 2], MD_RICHANG_COUNT[ 3] ) >= 3 then
            Msg2Player( sceneId, selfId, "你不能再领取今天的日常任务了", 8, 3)
            return 0
        end
    end

	local ret = AddQuest( sceneId, selfId, myMissionId, x300563_g_ScriptId, 0, 0, 0,1)-- 给玩家添加任务		
		
	if ret > 0 then
		local str = "您接受了任务："..x300563_g_MissionName;
		x300563_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)
		
		local myMissionId = x300563_GetMissionId( sceneId, selfId )
		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
		SetQuestByIndex( sceneId, selfId, misIndex, 5, 0 )
        SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300563_g_BuffId, 0)
		GamePlayScriptLog(sceneId, selfId, 911)
		return 1
	else
		
		x300563_ShowTips(sceneId, selfId, "接受任务错误")
	
	end


end

function x300563_GiveQuestion(sceneId, selfId, targetId, MissionId, nExt)
	
	if GetGameOpenById(x300563_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300563_g_MissionId) == 0 then
		x300563_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end
	local myMissionId = x300563_GetMissionId( sceneId, selfId )

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 5, 1 )  --还没有答题
	SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 1, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 2, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 3, 0 )

	x300563_ShowQuestion( sceneId, selfId, targetId,MissionId )

	x300563_QuestLogRefresh( sceneId, selfId, myMissionId );
end

function x300563_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x300563_ProcQuestAbandon( sceneId, selfId, MissionId )

	local myMissionId = x300563_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	local ret = DelQuestNM( sceneId, selfId, myMissionId )

	if ret>0 then

		local str = "您放弃了任务："..x300563_g_MissionName;
	    x300563_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)

        local today = GetDayOfYear()
		SetQuestData( sceneId, selfId, MD_ZDOUXI_DATE[1], MD_ZDOUXI_DATE[2], MD_ZDOUXI_DATE[3], today)
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
		x300563_ShowTips(sceneId, selfId, "放弃任务失败")
	end

	
end



function x300563_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	
	if GetGameOpenById(x300563_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300563_g_MissionId) == 0 then
		x300563_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	local myMissionId = x300563_GetMissionId( sceneId, selfId )
	
	if x300563_CheckSubmit(sceneId, selfId )>0 then
		local today = GetDayOfYear()
        local count = GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3] )
        if today == GetQuestData(sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2],MD_RICHANG_DAY[3] ) and count >= 3 then
            Msg2Player( sceneId, selfId, "今天的日常任务已经不能再交了，请明天再来", 8, 3)
            return 0
        end

		local nRet,nRet2 = x300563_GiveRewardTest(sceneId,selfId)

		if nRet<=0 then
			return
		end
        x300563_GiveReward(sceneId,selfId,nRet, nRet2,selectId)

		local ret = DelQuestNM( sceneId, selfId, myMissionId )

		if ret>0 then
            CallScriptFunction( 270300, "OnSubmissionFinished", sceneId, selfId, x300563_g_MissionId)

			local str = "您完成了任务："..x300563_g_MissionName;
			x300563_ShowTips(sceneId, selfId, str)
			Msg2Player(sceneId,selfId,str,8,2)

            SetQuestData( sceneId, selfId, MD_ZDOUXI_DATE[1], MD_ZDOUXI_DATE[2], MD_ZDOUXI_DATE[3], GetDayOfYear() )

            if IsHaveSpecificImpact( sceneId, selfId, x300563_g_BuffId) == 1 then
                CancelSpecificImpact( sceneId, selfId, x300563_g_BuffId)
                if random( 1, 100) <= 20 then
                    BeginAddItem( sceneId)
                    AddItem( sceneId, x300563_g_ItemId, 1)
                    local ret = EndAddItem( sceneId, selfId)
                    if ret == 1 then
                        AddItemListToPlayer( sceneId, selfId)
                        LuaThisScenceM2Wrold( sceneId, format( "%s实在了得，赵王府斗戏开始前非常及时地找到了各位戏子，特奖励一个@item_%d。", 
                            GetName( sceneId, selfId), x300563_g_ItemId), 1, 1)
                    else
                        Msg2Player( sceneId, selfId, "物品栏已满，无法获得物品", 8, 3)
                    end
                end
            end

			GamePlayScriptLog(sceneId, selfId, 912)
			
		else
			x300563_ShowTips(sceneId, selfId, "交任务失败")
		end
		
	end
end

function x300563_GiveRewardTest(sceneId,selfId)
	if GetGameOpenById(x300563_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300563_g_MissionId) == 0 then
		x300563_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	
	
	
	local bGetRandom = 0;
	
	local nItemTypeCount = 2;
	local itemlist = {  11000201,11000201}
	local iIndex = 0
	
	BeginAddItem(sceneId)
		AddItem( sceneId, 11000201, 8 )
		if random(1,100)<=1 then  --1% 的概率
			iIndex = random(1,nItemTypeCount);
			AddItem( sceneId, itemlist[iIndex], 15 )
			bGetRandom = 1
			
		end
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		
		
		if bGetRandom>0 then

			return 2,iIndex ;
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

function x300563_GiveReward(sceneId,selfId, nExt, nExt2, selectRadioId)
	
	if GetGameOpenById(x300563_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300563_g_MissionId) == 0 then
		x300563_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

    -- 检查玩家选择的奖励是不是可判定非绑定的
	local level = GetLevel( sceneId, selfId)
    local canBind = 0
    local count = 0
    local id = 0
    for i, item in x300563_g_RewardTable do
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
        for i, item in x300563_g_RewardTable do
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



function x300563_CheckSubmit(sceneId, selfId )
	
	if GetGameOpenById(x300563_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300563_g_MissionId) == 0 then
		x300563_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	local myMissionId = x300563_GetMissionId( sceneId, selfId )
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
function x300563_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId, nExt )

	
	
	BeginQuestEvent(sceneId)

		
	
	AddQuestText(sceneId,"#Y"..x300563_g_MissionName)
	AddQuestText(sceneId,"\t赵王寿诞一天天临近，这事儿也就一天天多起来。赵王府的上上下下都忙的不可开交。\n\t我看你相貌端正，谈吐不俗，有没有兴趣来帮忙？放心，赵王府绝不会亏待你的。")
	AddQuestText( sceneId,"#Y任务目标:")
			
	AddQuestText( sceneId,x300563_g_MissionTarget)
	AddQuestText(sceneId," ")

	--1、经验
	local level = GetLevel(sceneId, selfId)
    for i, item in x300563_g_RewardTable do
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

	-- for i, item in x300563_g_BonusItem do
		-- AddQuestItemBonus(sceneId, item.item, item.n)
	-- end

	EndQuestEvent()
	
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300563_g_ScriptId, MissionId,0);
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300563_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	local myMissionId = x300563_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300563_g_MissionName)
		AddQuestText(sceneId,"你还没有找回这几个戏子吗？可真是急死我了。")
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300563_g_ScriptId, MissionId,0);
	


end







---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300563_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	local myMissionId = x300563_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300563_g_MissionName)
		AddQuestText(sceneId,"\t#Y@myname#W真是神速，偌大的大都，竟这么快就将这五个戏子找齐了，果然是英雄少年啊。\n\t这是一点小小的心意，还请您笑纳。")
	
	
	
	--1、经验
	local level = GetLevel(sceneId, selfId)
    for i, item in x300563_g_RewardTable do
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

	-- for i, item in x300563_g_BonusItem do
		-- AddQuestItemBonus(sceneId, item.item, item.n)
	-- end
		
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300563_g_ScriptId, MissionId);
	 CallScriptFunction( 256225, "Finishdouxi", sceneId, selfId)

end


---------------------------------------------------------------------------------------------------
--向客户端发送题目
---------------------------------------------------------------------------------------------------
function x300563_ShowQuestion( sceneId, selfId, NPCId,MissionId )


	
	local myMissionId = x300563_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	

	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300563_g_MissionName)
		AddQuestText(sceneId,"\t你来的正好！眼看这大戏就要开演了，这些戏子名角们，还在大都内游逛，可真是急煞我也！\n\t你快去找到那些戏子，让他们速速回来准备登台。\n\t#G(五位戏子都在大都内北部游逛，去通知他们回来准备登台。)")
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300563_g_ScriptId, MissionId,0);
	


end


function x300563_DispatchNpcTalkInfo( sceneId, selfId, NPCId,MissionId,iIndex )
	local myMissionId = x300563_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	SetQuestByIndex( sceneId, selfId, misIndex, iIndex-1, 1 )
	

	local strTalkText = ""
  if iIndex==1 then
  	strTalkText = x300563_g_NpcTalkList1[random(1,x300563_g_NpcTalkCount1)]
  elseif iIndex==2 then
  	strTalkText = x300563_g_NpcTalkList2[random(1,x300563_g_NpcTalkCount2)]
  elseif iIndex==3 then
  	strTalkText = x300563_g_NpcTalkList3[random(1,x300563_g_NpcTalkCount3)]
  elseif iIndex==4 then
  	strTalkText = x300563_g_NpcTalkList4[random(1,x300563_g_NpcTalkCount4)]
  elseif iIndex==5 then
  	strTalkText = x300563_g_NpcTalkList5[random(1,x300563_g_NpcTalkCount5)]
  end
	
	
	
	NpcTalk(sceneId, NPCId, strTalkText, selfId)

	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	local value3 = GetQuestParam( sceneId, selfId, misIndex, 2 )
	local value4 = GetQuestParam( sceneId, selfId, misIndex, 3 )
	local value5 = GetQuestParam( sceneId, selfId, misIndex, 4 )

	if value1*value2*value3*value4*value5>0 then
		SetQuestByIndex( sceneId, selfId, misIndex, 5, 2 ) --完成任务
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
	end
	
	x300563_QuestLogRefresh( sceneId, selfId, myMissionId );

	
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300563_g_MissionName)
		
		if iIndex==1 then
			AddQuestText(sceneId,"\t我虽是见宰相，似文王施礼；一头地离明妃，早宋玉悲秋。\n\t啊呀！戏要开演？老夫这就前往。")
		elseif iIndex==2 then
			AddQuestText(sceneId,"\t满腹闲愁，数年禁受，天知否？天若是知我情由，怕不待和天瘦。\n\t戏要开演？小生知晓了。")
		elseif iIndex==3 then
			AddQuestText(sceneId,"\t月色溶溶夜，花阴寂寂春；如何临皓魄，不见月中人？\n\t奴家知晓了，这就前往。")
		elseif iIndex==4 then
			AddQuestText(sceneId,"\t乌林之役，左将军身在行间，寝不脱介，戮力破魏，岂得徒劳，无一块壤，而足下来欲收地邪？\n\t勿需多言，关某自知前往。")
		elseif iIndex==5 then
			AddQuestText(sceneId,"\t这等三伏天道，你便有冲天的怨气，也召不得一片雪来，可不胡说！\n\t我已听那锣鼓声，洒家这就前去。")
		end
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300563_g_ScriptId, myMissionId,0);

	

end





---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300563_QuestLogRefresh( sceneId, selfId, MissionId)
	
	
		
	BeginQuestEvent(sceneId)	
			
		
	AddQuestLogCustomText( sceneId,
							"",						-- 标题
							x300563_GetMissionName(sceneId,selfId),        -- 任务名字
							x300563_GetMissionTask(sceneId,selfId),		--任务目标
							"@npc_"..x300563_GetReplyNpcId(sceneId,selfId),			--任务NPC
							x300563_GetMissionMethod(sceneId,selfId),               --任务攻略
							x300563_GetMissionText(sceneId,selfId),	--任务描述
							x300563_GetMissionHelp(sceneId,selfId)					--任务小提示
							)

	--1、经验
	local level = GetLevel(sceneId, selfId)
    for i, item in x300563_g_RewardTable do
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

	-- for i, item in x300563_g_BonusItem do
		-- AddQuestItemBonus(sceneId, item.item, item.n)
	-- end

	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	

end

function x300563_GetMissionName(sceneId,selfId)
	

	return x300563_g_MissionName;
end

function x300563_GetMissionTask(sceneId,selfId)
	local myMissionId = x300563_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

	if nStep==0 then
		
		return "  #Y任务回复:@npc_"..x300563_g_ReplyNpcId;
	end
	

	
	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	local value3 = GetQuestParam( sceneId, selfId, misIndex, 2 )
	local value4 = GetQuestParam( sceneId, selfId, misIndex, 3 )
	local value5 = GetQuestParam( sceneId, selfId, misIndex, 4 )

	local strTable = "  ";
	local str1 = strTable.."找到#G“铜锤”#W"..format("(%d/1)",value1)
	local str2 = "\n"..strTable.."找到#G“小生”#W"..format("(%d/1)",value2)
	local str3 = "\n"..strTable.."找到#G“花旦”#W"..format("(%d/1)",value3)
	local str4 = "\n"..strTable.."找到#G“关公”#W"..format("(%d/1)",value4)
	local str5 = "\n"..strTable.."找到#G“武丑”#W"..format("(%d/1)",value5)

	if value1>=1 then
		str1 = "#G"..str1
	else
		str1 = "#W"..str1
	end
	if value2>=1 then
		str2 = "#G"..str2
	else
		str2 = "#W"..str2
	end
	if value3>=1 then
		str3 = "#G"..str3
	else
		str3 = "#W"..str3
	end
	if value4>=1 then
		str4 = "#G"..str4
	else
		str4 = "#W"..str4
	end

	if value5>=1 then
		str5 = "#G"..str5
	else
		str5 = "#W"..str5
	end

	return str1..str2..str3..str4..str5
end

function x300563_GetReplyNpcId(sceneId,selfId)
	return x300563_g_ReplyNpcId;
end

function x300563_GetMissionMethod(sceneId,selfId)
	return "\t找到五位戏子“#G小生#W”，“#G花旦#W”，“#G武丑#W”，“#G关公#W”，“#G铜锤#W”。他们应该在#G大都内北方闲逛。"
end

function x300563_GetMissionText(sceneId,selfId)
	return "\t这可急死我了，你来的正好！这些戏子们，正在大都内北部游逛，眼看这大戏就要开演了，你快去找到那些戏子，让他们速速回来准备登台。"
end

function x300563_GetMissionHelp(sceneId,selfId)
	return "\t五位戏子一直都在大都内北部走动，要仔细寻找。\n\t#W“#G铜锤#W”对赵王府内很感兴趣。（赵王府内）\n\t“#G小生#W”对波斯舞女趋之若鹜。（大都美丽会附近）\n\t“#G花旦#W”总是对有宝石的地方流连忘返。（龙眼石商人附近）\n\t“#G关公#W”喜欢去有“龙”、“狮子”的地方。（皇宫大门外）\n\t“#G武丑#W”对武林高手非常仰慕。（大相国寺内）"
end



function x300563_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300563_QuestLogRefresh( sceneId, selfId, MissionId );
end

--// system function start
function x300563_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	
	local myMissionId = x300563_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	

	
	
	if npcGuid == x300563_g_ReplyNpcId then
		local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

		if nStep==0 then
			AddQuestNumText(sceneId, x300563_g_MissionId, x300563_g_MissionName,2,30);
		elseif nStep>0 then
			local state = GetQuestStateNM(sceneId, selfId, npcGuid, myMissionId);

		
			AddQuestNumText(sceneId, myMissionId, x300563_g_MissionName,state,state);
		end
	
	else
		local bFind =0;
		local iIndex=0
		for i,item in x300563_g_NpcList do
			iIndex = iIndex+1;
			if npcGuid==item then
				bFind=1;
				break;
			end
		end

		

		if bFind==0 then
			return
		end

		local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

		if nStep~=1 then
			return
		end



		
		local value = GetQuestParam( sceneId, selfId, misIndex, iIndex-1)

		if value==0 then


			AddQuestNumText(sceneId, x300563_g_MissionId, x300563_g_MissionName1,2,iIndex+10);
		end
	end
	

	
end


function x300563_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end



--// system end




