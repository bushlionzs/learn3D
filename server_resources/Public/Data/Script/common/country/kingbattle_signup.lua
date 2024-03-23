
--国王战场申请

--MisDescBegin
x300815_g_ScriptId              = 300815
x300815_g_Leader_Index          = 5
x300815_g_MissionName           ="【国家】挑战国王"
x300815_g_MissionName0          ="【国家】争夺国王"
x300815_g_MissionName1          ="【国家】国王战场查询"
x300815_g_NeedMoney             = 50*1000
x300815_g_GuildLevel            = 1
x300815_g_GuildMemberNum        = 1

x300815_g_Signup_None                       = -1         --没人报名
x300815_g_Signup_OK                         =  0         --报名成功
x300815_g_Signup_Failed                     =  1         --报名失败
x300815_g_Signup_Signed                     =  2         --已经报过名了
x300815_g_Signup_Other                      =  3         --已有他人报名
x300815_g_Signup_TimeNotMatch               =  4         --时间不对，不能报名
x300815_g_Signup_NoGuild                    =  5         --没有帮会
x300815_g_Signup_GuildNotMatchPlayer        =  6         --报名帮会与玩家帮会不匹配
x300815_g_Signup_NotGuildLeader             =  7         --报名玩家不是帮主
x300815_g_Signup_GuildLevelError            =  8         --帮会级别不够
x300815_g_Signup_GuildMemberCountError      =  9         --帮会不满15人
x300815_g_Signup_NoKing                     =  10        --国家没有国王
x300815_g_Signup_KingPlayerInSameGuild      =  11        --国王和帮主是在同一帮会
x300815_g_Signup_KingPlayerIsOnePlayer      =  12        --国王和帮主是同一人
x300815_g_Signup_PowerNotEnough             =  13        --实力不足
x300815_g_KingBattleNotPermitSignUp         =  14        --国家尚未开启
x300815_g_Signup_OtherError                 =  15        --其他错误
x300815_g_Leader_Index                      =  5
--MisDescEnd
----------------------------------------------------------------------------------------------
--枚举
----------------------------------------------------------------------------------------------
function x300815_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	--合服开关
    if GetMergeDBToggle() == 1 then
        return
    end
    
  --升级数据库开关
	local UpdateDBflag = GetUpdateDBBeforeToggle()
	if UpdateDBflag==1 then
		return
	end
    
    --测试服开关
    --if GetTestServerToggle() == 0 then
    --    return
    --end

    --战场自己的开关
    if GetBattleSceneToggle( BATTLESCENE_TYPE_KINGBATTLE ) == 0 then
        return
    end

    --是否有国王，申请者不得是国王
    local nGuildId = GetGuildID(sceneId,selfId )

    --无帮会
    if nGuildId < 0 then
        return
    end
    

    --非帮主
    local pos = GetGuildOfficial(sceneId, selfId)
	if pos ~= x300815_g_Leader_Index then
        return
    end

    local nHumanGUID = GetPlayerGUID( sceneId,selfId )
    
    --只要不是国王都能报名
    local nCountryId,nKingGUID,szKingName,nCountryGold = GetCountrySimpleData( sceneId,selfId )
    local nKingGuildID = GetCountryKingGuildId( sceneId,selfId )
    if nHumanGUID ~= nKingGUID then
    	if nKingGuildID < 0 then
        	AddQuestNumText(sceneId,x300815_g_ScriptId,x300815_g_MissionName0,3);
        else
        	AddQuestNumText(sceneId,x300815_g_ScriptId,x300815_g_MissionName0,3);
        end
        
        --在国王战场报名之后,开始之前,可以进行相关查询操作
        if GetKingBattleStatus( sceneId ) >= STATE_KING_BATTLE_SIGNUP and GetKingBattleStatus( sceneId ) < STATE_KING_BATTLE_BATTLE then
        	AddQuestNumText(sceneId,x300815_g_ScriptId,x300815_g_MissionName1,3,x300815_g_ScriptId);
        end
        
    end
    
end

----------------------------------------------------------------------------------------------
--默认事件
----------------------------------------------------------------------------------------------
function x300815_ProcEventEntry( sceneId, selfId, targetId,scriptId,idExt )

    if idExt == 0 then
    
    	--不在报名时间内
    	if GetKingBattleStatus( sceneId ) ~= STATE_KING_BATTLE_SIGNUP then
    		BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，很抱歉，现在不是报名时间。");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
    		return
    	end

        --查询结果
        local nGuildId = GetGuildID( sceneId,selfId )
        
         --检查是否是据点
--	    local nLairdM1,_,_,nLairdDate = GetGuildLairdSceneId(nGuildId) 
--	    if nLairdM1 > 0 then
--	    	BeginQuestEvent(sceneId)
--            AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，领主不能报名！");
--            EndQuestEvent(sceneId)
--            DispatchQuestEventList(sceneId,selfId,targetId)
--	    	return 
--	    end
	    
        QueryKingBattleSignupState( sceneId,selfId,nGuildId,targetId )

    elseif idExt == 1 then

        --是否是帮主
        local pos = GetGuildOfficial(sceneId, selfId)
        if pos ~= x300815_g_Leader_Index then
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，很抱歉，您还不是帮主无法申请国王。");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
            return
        end

        local nGuildId = GetGuildID(sceneId,selfId )
        local nLevel,nMemberNum,nExp = GetGuildSimpleData( nGuildId )

        --帮会等级是满足
        -- if nLevel < x300815_g_GuildLevel then
            -- BeginQuestEvent(sceneId)
            -- AddQuestText(sceneId, "申请失败，帮会等级不足２级！");
            -- EndQuestEvent(sceneId)
            -- DispatchQuestEventList(sceneId,selfId,targetId)
            -- return
        -- end

        --帮会会员数量是否满足
        if nMemberNum < x300815_g_GuildMemberNum then
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，帮会成员不足15人！");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
            return
        end
        
        
        --检查是否是据点
--	    local nLairdM1,_,_,nLairdDate = GetGuildLairdSceneId(nGuildId) 
--	    if nLairdM1 > 0 then
--	    	BeginQuestEvent(sceneId)
--            AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，领主不能报名！");
--            EndQuestEvent(sceneId)
--            DispatchQuestEventList(sceneId,selfId,targetId)
--	    	return 
--	    end

        --现银是否满足
--        local nMoney = GetMoney(sceneId,selfId,0)
--        if nMoney < x300815_g_NeedMoney then
--            BeginQuestEvent(sceneId)
--            AddQuestText(sceneId, "申请失败，很抱歉，您包裹中的现银不够50两，无法申请国王。");
--            EndQuestEvent(sceneId)
--            DispatchQuestEventList(sceneId,selfId,targetId)
--            return
--        end

        --是否是国王战场报名时间
        --if GetKingBattleStatus(sceneId) ~= STATE_KING_BATTLE_SIGNUP then
        --    BeginQuestEvent(sceneId)
        --    AddQuestText(sceneId, "申请失败，很抱歉，请在14：00~17：00之间申请国王。");
        --    EndQuestEvent(sceneId)
        --    DispatchQuestEventList(sceneId,selfId,targetId)
        --    return
        --end

        --先扣钱
        --CostMoney( sceneId,selfId,0,x300815_g_NeedMoney )

        --以上都通过，发送申请
        SignupKingBattle( sceneId,selfId,nGuildId )

    elseif idExt == x300815_g_ScriptId then
    	
    	KingBattleQueryCurrentGuild(sceneId,selfId,targetId)
    	
    end

    return 1

end

----------------------------------------------------------------------------------------------
--查询国王战场报名状态响应
----------------------------------------------------------------------------------------------
function x300815_OnQueryKingBattleSignupState( sceneId,selfId,nResult,targetId,nCurrentGuildA,nCurrentGuildB )
    
    if nResult == x300815_g_Signup_None then

        --未报名
        x300815_KingBattleSignup( sceneId,selfId,targetId,nCurrentGuildA,nCurrentGuildB )

    elseif nResult == x300815_g_Signup_Signed then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t很抱歉，已经受理了您挑战国王的请求，无法再次挑战国王。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    elseif nResult == x300815_g_Signup_Other then

        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，很抱歉，在您之前已经有帮会进行了申请国王。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    -- elseif nResult == x300815_g_Signup_TimeNotMatch then
        
        -- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，很抱歉，请在周日14：00~17：00之间申请国王。");
		-- EndQuestEvent(sceneId)
		-- DispatchQuestEventList(sceneId,selfId,targetId)
    
    elseif nResult == x300815_g_Signup_NoGuild then

        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，必须有帮会才能申请挑战！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    elseif nResult == x300815_g_Signup_GuildNotMatchPlayer then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，申请帮会信息与玩家所在帮会不匹配！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    elseif nResult == x300815_g_Signup_NotGuildLeader then

        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，必须是帮主才可以申请！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    -- elseif nResult == x300815_g_Signup_GuildLevelError then

        -- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, "申请失败，帮会等级不足2级！");
		-- EndQuestEvent(sceneId)
		-- DispatchQuestEventList(sceneId,selfId,targetId)

    elseif nResult == x300815_g_Signup_GuildMemberCountError then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，帮会成员不足15人！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    elseif nResult == x300815_g_Signup_NoKing then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，无法申请挑战，现在还没有国王！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    elseif nResult == x300815_g_Signup_KingPlayerInSameGuild then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，不能与国王在同一个帮会！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    elseif nResult == x300815_g_Signup_KingPlayerIsOnePlayer then

        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，国王不能申请国王战场！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
		
	elseif nResult == x300815_g_Signup_PowerNotEnough then
	
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，帮会实力必须大于已经申请的帮会实力！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
	elseif nResult == x300815_g_KingBattleNotPermitSignUp then
	
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败,你所在国家的国王争夺战尚未开启!");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		

    else
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，未知原因，可能国王战场申请数已达上线！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    end

    return 1

end

----------------------------------------------------------------------------------------------
--帮战报名
----------------------------------------------------------------------------------------------
function x300815_KingBattleSignup( sceneId,selfId,targetId ,nCurrentGuildA,nCurrentGuildB)
    
    --是否是帮主
    local pos = GetGuildOfficial(sceneId, selfId)
	if pos ~= x300815_g_Leader_Index then
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t很抱歉，您还不是帮主无法申请国王。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		return 0
	end

    local nGuildId = GetGuildID(sceneId,selfId )
    local nLevel,nMemberNum,nExp = GetGuildSimpleData( nGuildId )

    --帮会等级是满足
    -- if nLevel < x300815_g_GuildLevel then
        -- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, "申请失败，帮会等级不足2级！");
		-- EndQuestEvent(sceneId)
		-- DispatchQuestEventList(sceneId,selfId,targetId)
		-- return 0
    -- end

    --帮会会员数量是否满足
    if nMemberNum < x300815_g_GuildMemberNum then
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，帮会成员不足15人！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		return 0
    end
    
    --检查是否是据点
--    local nLairdM1,_,_,nLairdDate = GetGuildLairdSceneId(nGuildId) 
--    if nLairdM1 > 0 then
--    	return 
--    end

    --现银是否满足
--    local nMoney = GetMoney(sceneId,selfId,0)
--    if nMoney < x300815_g_NeedMoney then
--        BeginQuestEvent(sceneId)
--		AddQuestText(sceneId, "申请失败，很抱歉，您包裹中的现银不够50两，无法申请国王。");
--		EndQuestEvent(sceneId)
--		DispatchQuestEventList(sceneId,selfId,targetId)
--		return 0
--    end


    --是否是国王战场报名时间
	if GetKingBattleStatus(sceneId) ~= STATE_KING_BATTLE_SIGNUP then
 		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，很抱歉，请在周日14：00~17：00之间申请国王。");
		EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,targetId)
		return 0
	end


	
	local nCountryId,nKingGUID,szKingName,nCountryGold = GetCountrySimpleData( sceneId,selfId )
	local nKingGuildID = GetCountryKingGuildId( sceneId,selfId )
	
	local msg = ""
	if nKingGuildID >= 0 then
		if nCurrentGuildA >= 0 then
			local strCurrentGuildName = GetGuildName( nCurrentGuildA )
			msg = format("#R已经有国王，您确定发起对现任国王的挑战吗？\n#G当前已发起对国王挑战并且实力最强帮会为:#c0000FF%s",strCurrentGuildName)
		else
			msg = "#R已经有国王，您确定发起对现任国王的挑战吗？\n#G当前没有帮会发起对国王的争夺!"
		end
	else
		if nCurrentGuildA < 0 and nCurrentGuildB < 0 then
			msg = "#R目前没有国王，您确定要争夺国王吗？\n#G当前没有帮会发起对国王的争夺!"
		elseif nCurrentGuildA <0 and nCurrentGuildB >= 0 then
			local strGuildBName = GetGuildName( nCurrentGuildB )
			msg = format("#R目前没有国王，您确定要争夺国王吗？\n#G当前已发起对国王挑战并且实力最强帮会为:#c0000FF%s!",strGuildBName)
		elseif nCurrentGuildA >= 0 and nCurrentGuildB >= 0 then
			local strGuildBNameA = GetGuildName( nCurrentGuildA )
			local strGuildBNameB = GetGuildName( nCurrentGuildB )
			msg = format("#R目前没有国王，您确定要争夺国王吗？\n#G当前已发起对国王挑战并且实力最强帮会为:#c0000FF%s,%s!",strGuildBNameA,strGuildBNameB)
		end
	end 
	
    BeginQuestEvent(sceneId)
	local msg1 ="#Y【国家】争夺国王#W#r #r 1、您必须在#G周日14：00-17：00#W之间申请#W。#r #r2、当您申请后，如果有在#G帮会实力榜#W上排名高于您所在帮会排名的帮会报名，您的报名申请将会被#G顶替#W。#W#r #r 3、如果到达报名截止时间，#G只有一个#W帮会报名，则该帮会#G自动成为王者卫队#W，帮主#G自动成为国王#W。#W#r #r 4、如果到达报名截止时间，申请报名的帮会有2个，则会在#G周日19：30-19：50#W开启国王战场，胜者帮会成为王者卫队，帮主成为国王。#W#r #r5、您必须是某个帮会的#G帮主#W。#r #r6、您的帮会#G人数#W必须#G大于15人#W。#r #r"
	AddQuestText(sceneId, msg1);
    AddQuestText(sceneId, msg);
    AddQuestNumText(sceneId,x300815_g_ScriptId,"确定..",3,1);
    EndQuestEvent(sceneId)
    DispatchQuestEventList(sceneId,selfId,targetId)

    return 1
end

function x300815_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--接受
----------------------------------------------------------------------------------------------
function x300815_ProcAccept( sceneId, selfId )
end


----------------------------------------------------------------------------------------------
--申请结果
----------------------------------------------------------------------------------------------
function x300815_OnKingBattleSignupResult( sceneId,selfId,nResult,targetId ,nSignupCount)
    

    --以下除了申请成功，其他的都需要将扣除的钱还给玩家
    if nResult == x300815_g_Signup_OK then

        local nGuildId = GetGuildID(sceneId,selfId )
        local nCountryId,nKingGUID,szKingName,nCountryGold = GetCountrySimpleData( sceneId,selfId )

        local strGuildA = GetGuildName( nGuildId )
        local strGuildB = GetGuildName( GetCountryKingGuildId( sceneId,selfId ) )

        local strMsg = ""
        
        if nSignupCount > 0 then
        	strMsg = format("恭喜本帮会成功报名国王战场，目前为止已有%d个帮会报名参加。",nSignupCount)
        else
        	strMsg = "恭喜本帮会成功报名国王战场，目前除了本帮会还没有其他帮会报名参加。"
        end
        
        LuaAllScenceM2Guild(sceneId,strMsg,nGuildId,3,1)
        LuaAllScenceM2Guild(sceneId,strMsg,nGuildId,2,1)

        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strMsg);
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    elseif nResult == x300815_g_Signup_Signed then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t很抱歉，已经受理了您挑战国王的请求，无法再次挑战国王。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        --还钱
        --AddMoney( sceneId,selfId, 0, x300815_g_NeedMoney )

    elseif nResult == x300815_g_Signup_Other then

        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "##Y【国家】争夺国王#W#r\t申请失败，很抱歉，在您之前已经有帮会进行了申请国王。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        --还钱
        --AddMoney( sceneId,selfId, 0, x300815_g_NeedMoney )

    -- elseif nResult == x300815_g_Signup_TimeNotMatch then
        
        -- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，很抱歉，请在周日14：00~17：00之间申请国王。");
		-- EndQuestEvent(sceneId)
		-- DispatchQuestEventList(sceneId,selfId,targetId)

        --还钱
        --AddMoney( sceneId,selfId, 0, x300815_g_NeedMoney )
    
    elseif nResult == x300815_g_Signup_NoGuild then

        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，必须有帮会才能申请挑战！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        --还钱
        --AddMoney( sceneId,selfId, 0, x300815_g_NeedMoney )

    elseif nResult == x300815_g_Signup_GuildNotMatchPlayer then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，申请帮会信息与玩家所在帮会不匹配！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        --还钱
        --AddMoney( sceneId,selfId, 0, x300815_g_NeedMoney )

    elseif nResult == x300815_g_Signup_NotGuildLeader then

        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，必须是帮主才可以申请！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        --还钱
        --AddMoney( sceneId,selfId, 0, x300815_g_NeedMoney )

    -- elseif nResult == x300815_g_Signup_GuildLevelError then

        -- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, "申请失败，帮会等级不足2级！");
		-- EndQuestEvent(sceneId)
		-- DispatchQuestEventList(sceneId,selfId,targetId)

        --还钱
        --AddMoney( sceneId,selfId, 0, x300815_g_NeedMoney )

    elseif nResult == x300815_g_Signup_GuildMemberCountError then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，帮会成员不足15人！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        --还钱
        --AddMoney( sceneId,selfId, 0, x300815_g_NeedMoney )

    elseif nResult == x300815_g_Signup_NoKing then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，无法申请挑战，现在还没有国王！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        --还钱
        --AddMoney( sceneId,selfId, 0, x300815_g_NeedMoney )

    elseif nResult == x300815_g_Signup_KingPlayerInSameGuild then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，不能与国王在同一个帮会！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        --还钱
        --AddMoney( sceneId,selfId, 0, x300815_g_NeedMoney )

    elseif nResult == x300815_g_Signup_KingPlayerIsOnePlayer then

        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，国王不能申请国王战场！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        --还钱
        --AddMoney( sceneId,selfId, 0, x300815_g_NeedMoney )

	elseif nResult == x300815_g_Signup_PowerNotEnough then
	
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，帮会实力必须大于已经申请的帮会实力！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

		--还钱
        --AddMoney( sceneId,selfId, 0, x300815_g_NeedMoney )
		
	elseif nResult == x300815_g_KingBattleNotPermitSignUp then
	
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败,你所在国家的国王争夺战尚未开启!");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId) 
		
    else
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】争夺国王#W#r\t申请失败，未知原因，可能国王战场申请数已达上线！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        --还钱
        --AddMoney( sceneId,selfId, 0, x300815_g_NeedMoney )
    end

    return 1

end

----------------------------------------------------------------------------------------------
--设置运行期状态
----------------------------------------------------------------------------------------------
function OnKingBattleAskPlayerEnterScene( sceneId, selfId )

    --通知玩家进入场景
    KingBattleAskEnterScene( sceneId, selfId )
    
end


----------------------------------------------------------------------------------------------
--查询结果
----------------------------------------------------------------------------------------------
function OnQueryCurrentGuild(sceneId,selfId,targetId,nCurrentGuildA,nCurrentGuildB,nCount)
	
	
	local nCountryId,nKingGUID,szKingName,nCountryGold = GetCountrySimpleData( sceneId,selfId )
	local nKingGuildID = GetCountryKingGuildId( sceneId,selfId )
	
	local msg = ""
	if nKingGuildID >= 0 then
		if nCurrentGuildA >= 0 then
			local strCurrentGuildName = GetGuildName( nCurrentGuildA )
			msg = format("#Y【国家】国王战场查询#W#r #r #R已经有国王，您确定对其进行挑战吗？\n#G当前已发起对国王的挑战并且实力最强帮会为:#c0000FF%s",strCurrentGuildName)
		else
			msg = "#Y【国家】国王战场查询#W#r #r #R已经有国王，您确定对其进行挑战吗？\n#G当前没有帮会发起对国王的争夺!"
		end
	else
		if nCurrentGuildA < 0 and nCurrentGuildB < 0 then	
			msg = "#Y【国家】国王战场查询#W#r #r #R目前没有国王!\n\t#G当前没有帮会发起到国王的争夺!"
		elseif nCurrentGuildA <0 and nCurrentGuildB >= 0 then
			local strGuildBName = GetGuildName( nCurrentGuildB )
			msg = format("#Y【国家】国王战场查询#W#r #r #R目前没有国王!\n#G当前已发起对国王的挑战并且实力最强帮会为:#c0000FF%s!",strGuildBName)
		elseif nCurrentGuildA >= 0 and nCurrentGuildB >= 0 then
			local strGuildBNameA = GetGuildName( nCurrentGuildA )
			local strGuildBNameB = GetGuildName( nCurrentGuildB )
			msg = format("#Y【国家】国王战场查询#W#r #r #R目前没有国王!\n#G当前已发起对国王的挑战并且实力最强帮会为:#c0000FF%s,%s!",strGuildBNameA,strGuildBNameB)
		end
	end 

    BeginQuestEvent(sceneId)
    AddQuestText(sceneId, msg);
    EndQuestEvent(sceneId)
    DispatchQuestEventList(sceneId,selfId,targetId)

    return 1
    	
end


----------------------------------------------------------------------------------------------
--检测接受条件
----------------------------------------------------------------------------------------------
function x300815_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--接受
----------------------------------------------------------------------------------------------
function x300815_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--放弃
----------------------------------------------------------------------------------------------
function x300815_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--继续
----------------------------------------------------------------------------------------------
function x300815_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--检测是否可以提交
----------------------------------------------------------------------------------------------
function x300815_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--提交
----------------------------------------------------------------------------------------------
function x300815_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--杀死怪物或玩家
----------------------------------------------------------------------------------------------
function x300815_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--进入区域事件
----------------------------------------------------------------------------------------------
function x300815_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--道具改变
----------------------------------------------------------------------------------------------
function x300815_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end