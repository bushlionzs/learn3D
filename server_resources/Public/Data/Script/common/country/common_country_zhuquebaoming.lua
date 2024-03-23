
--朱雀战场申请

x310114_g_ScriptId              			= 310114
x310114_g_Leader_Index          			= 5
x310114_g_MissionName           			="【国家】挑战朱雀之主"
x310114_g_MissionName1          			="【国家】朱雀战场查询"
x310114_g_NeedMoney             			= 50*1000
x310114_g_GuildLevel            			= 1
x310114_g_GuildMemberNum       				= 1


x310114_g_ZhuQue_Signup                  	= 100     --报名
x310114_g_ZhuQue_WaitBattle              	= 101     --报名结束，等待朱雀战场
x310114_g_ZhuQue_BeginBattle             	= 102     --开始朱雀战场
x310114_g_ZhuQue_EndBattle               	= 103     --结束朱雀战场

x310114_g_Leader_Index                      =  5


----------------------------------------------------------------------------------------------
--枚举
----------------------------------------------------------------------------------------------
function x310114_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_ZHUQUEBATTLELITE ) == 0 then
        return
    end

    --检查帮会
    local nGuildId = GetGuildID(sceneId,selfId )
    if nGuildId < 0 then
        return
    end
    
    --检查是否有国王
    local nHumanGUID = GetPlayerGUID( sceneId,selfId )
    local nCountryId,nKingGUID,szKingName,nCountryGold = GetCountrySimpleData( sceneId,selfId )
    if nKingGUID <= 0 or nHumanGUID == nKingGUID then
    	return    	
    end
    
    --弹出相关选项
    local nBattleStatus = CallScriptFunction(310113,"GetBattleState",sceneId)
	if nBattleStatus == x310114_g_ZhuQue_Signup then
		AddQuestNumText(sceneId,x310114_g_ScriptId,x310114_g_MissionName1,3,x310114_g_ScriptId);
	end

    --检查是否是帮主
    local pos = GetGuildOfficial(sceneId, selfId)
	if pos ~= x310114_g_Leader_Index then
        return
    end
    
    --检查是否是青龙
    if IsSpecialCountryOffical(sceneId,selfId,COUNTRY_POSITION_QINGLONG_LEADER) == 1 then
    	return
    end
    
    --检查是否是朱雀
    if IsSpecialCountryOffical(sceneId,selfId,COUNTRY_POSITION_ZHUQUE_LEADER) == 1 then
    	return
    end
    
    --检查是否是国王
    if IsSpecialCountryOffical(sceneId,selfId,COUNTRY_POSITION_KING) == 1 then
    	return
    end
    
    
	--弹出相关选项
	-- if nBattleStatus == x310114_g_ZhuQue_Signup then
    	AddQuestNumText(sceneId,x310114_g_ScriptId,x310114_g_MissionName,3);
    -- end
    
end

----------------------------------------------------------------------------------------------
--默认事件
----------------------------------------------------------------------------------------------
function x310114_ProcEventEntry( sceneId, selfId, targetId,scriptId,idExt )

    if idExt == 0 then
    
    	local nBattleStatus = CallScriptFunction(310113,"GetBattleState",sceneId)
    	if nBattleStatus ~= x310114_g_ZhuQue_Signup then
    		--活动没开启
    		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，很抱歉，请在每周日的20：25~20：40之间申请朱雀战场。");
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,targetId)
    		return
    	end

        --查询结果
        local nGuildId = GetGuildID( sceneId,selfId )
        GameBattleQuerySignupState( sceneId,selfId,0 )
        SetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID,targetId)

    elseif idExt == 1 then

        --是否是帮主
        local pos = GetGuildOfficial(sceneId, selfId)
        if pos ~= x310114_g_Leader_Index then
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，很抱歉，您还不是帮主无法申请成为朱雀之主。");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
            return
        end

        local nGuildId = GetGuildID(sceneId,selfId )
        local nLevel,nMemberNum,nExp = GetGuildSimpleData( nGuildId )

        --帮会等级是满足
        if nLevel < x310114_g_GuildLevel then
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，帮会等级不足２级！");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
            return
        end

        --帮会会员数量是否满足
        if nMemberNum < x310114_g_GuildMemberNum then
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，帮会成员不足30人！");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
            return
        end
        
        --检查是否是青龙
	    if IsSpecialCountryOffical(sceneId,selfId,COUNTRY_POSITION_QINGLONG_LEADER) == 1 then
	    	return
	    end
	    
	    --检查是否是朱雀
	    if IsSpecialCountryOffical(sceneId,selfId,COUNTRY_POSITION_ZHUQUE_LEADER) == 1 then
	    	return
	    end
	    
	    --检查是否是国王
	    if IsSpecialCountryOffical(sceneId,selfId,COUNTRY_POSITION_KING) == 1 then
	    	return
	    end
        
        --检查是否是据点
	    local nLairdM1,_,_,nLairdDate = GetGuildLairdSceneId(nGuildId) 
	    if nLairdM1 > 0 then
	    	BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，必须放弃领地才能申请！");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
	    	return 
	    end

        --以上都通过，发送申请
        GameBattleExecuteSignup( sceneId,selfId, 0 )
        SetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID,targetId)

    elseif idExt == x310114_g_ScriptId then    	
    	
    	--配对查询
    	GameBattleQueryMatchState(sceneId,selfId,0)
    	SetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID,targetId)
    	
    end

    return 1

end

----------------------------------------------------------------------------------------------
--查询朱雀战场报名状态响应
----------------------------------------------------------------------------------------------
function x310114_OnQueryZhuQueBattleSignupState( sceneId,selfId,nResult,nGuildA,nGuildB )
    
    local targetId = GetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID)
    if nResult == 0 then
    	--OK,查询状态不处理这种情况
    	
    elseif nResult == 100 then
    	
    	--活动没开启
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，很抱歉，请在每周日的20：25~20：40之间申请朱雀战场。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
    elseif nResult == 101 then
    
    	--帮会没有报名
        x310114_ZhuQueBattleSignup( sceneId,selfId,targetId,nGuildA,nGuildB )
        
    elseif nResult == 102 then
    	
    	--已经报名
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t很抱歉，已经受理了您挑战朱雀之主的请求，无法再次挑战朱雀之主。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
    elseif nResult == 103 then
    	
    	--没有帮会
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，必须有帮会才能申请挑战！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 104 then
    
    	--帮会等级不够
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，帮会等级不足2级！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 105 then
    
    	--不是帮主
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，必须是帮主才可以申请！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 106 then
    	
    	--帮会人数不足
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，帮会成员不足30人！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 107 then
    
    	--青龙帮错误,不能是青龙帮
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，不能是青龙帮！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 108 then
    
    	--国王帮错误,不能是国王帮
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，不能是国王帮！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 109 then
    	
    	--帮会实力不足
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，帮会实力必须大于已经审请的帮会实力！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
	elseif nResult == 110 then
    	
    	--报名结束
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，报名已经结束");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
	elseif nResult == 111 then
		
		--报过青龙报了
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，报过青龙守护了");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
    else
    
    	--未知错误
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，未知原因，可能朱雀战场申请数已达上线！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    end

    return 1

end

----------------------------------------------------------------------------------------------
--帮战报名
----------------------------------------------------------------------------------------------
function x310114_ZhuQueBattleSignup( sceneId,selfId,targetId ,nGuildA, nGuildB)

	
	SetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID,targetId)
    
    --是否是帮主
    local pos = GetGuildOfficial(sceneId, selfId)
	if pos ~= x310114_g_Leader_Index then
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t很抱歉，您还不是帮主无法申请挑战朱雀之主。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		return 0
	end

    local nGuildId = GetGuildID(sceneId,selfId )
    local nLevel,nMemberNum,nExp = GetGuildSimpleData( nGuildId )

    --帮会等级是满足
    if nLevel < x310114_g_GuildLevel then
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，帮会等级不足2级！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		return 0
    end

    --帮会会员数量是否满足
    if nMemberNum < x310114_g_GuildMemberNum then
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，帮会成员不足30人！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		return 0
    end
    
    
    --检查是否是青龙
    if IsSpecialCountryOffical(sceneId,selfId,COUNTRY_POSITION_QINGLONG_LEADER) == 1 then
    	return
    end
    
    --检查是否是朱雀
    if IsSpecialCountryOffical(sceneId,selfId,COUNTRY_POSITION_ZHUQUE_LEADER) == 1 then
    	return
    end
    
    --检查是否是国王
    if IsSpecialCountryOffical(sceneId,selfId,COUNTRY_POSITION_KING) == 1 then
    	return
    end
    
    --检查是否是据点
    local nLairdM1,_,_,nLairdDate = GetGuildLairdSceneId(nGuildId) 
    if nLairdM1 > 0 then
    	BeginQuestEvent(sceneId)
        AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，必须放弃领地才能申请！");
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,targetId)
    	return 
    end

    --是否是朱雀战场报名时间
    local nBattleStatus = CallScriptFunction(310113,"GetBattleState",sceneId)
	if nBattleStatus ~= x310114_g_ZhuQue_Signup then
 		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，很抱歉，请在每周日的20：25~20：40之间申请朱雀战场。");
		EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,targetId)
		return 0
	end
	
	--分各种情况对朱雀帮会进行处理
	local msg = ""
	local nCountryGuildId = CountryGetOfficerGUID(GetCurCountry(sceneId,selfId),1)
	if nCountryGuildId <= 0 then

		
		--没有朱雀守护的情况
		if nGuildA >= 0 and nGuildB >= 0 then
			
			--如果已经有人挑战了
			local strGuildA = GetGuildName( nGuildA )
			local strGuildB = GetGuildName( nGuildB )
			msg = format("#Y【国家】挑战朱雀之主#W\n \n#G当前没有朱雀守护帮会\n申请帮会：#R%s\n#G申请帮会：#R%s\n \n您确定要发起挑战吗？",strGuildA,strGuildB)
			
		elseif nGuildA >= 0 and nGuildB < 0 then
			--如果只有一方挑战
			local strGuildA = GetGuildName( nGuildA )
			msg = format("#Y【国家】挑战朱雀之主#W\n \n#G当前没有朱雀守护帮会\n申请帮会：#R%s\n#G申请帮会：#W待申请\n \n您确定要发起挑战吗？",strGuildA)
		else
			--如果没有人挑战
			msg = "#Y【国家】挑战朱雀之主#W\n \n#G当前没有朱雀守护帮会\n申请帮会：#W待申请\n#G申请帮会：#W待申请\n \n您确定要发起挑战吗？"
		end
		
	else
		--有清龙守护的情况
		if nGuildB >= 0 then
			--如果已经有人挑战了
			
			local strGuildA = GetGuildName( nGuildA )
			local strGuildB = GetGuildName( nGuildB )
			msg = format("#Y【国家】挑战朱雀之主#W\n \n#G朱雀守护帮会:#R%s#r#G申请帮会:#R%s\n \n您确定要发起挑战吗？",strGuildA,strGuildB)
			
		else
			--如果没有人挑战
			local strGuildA = GetGuildName( nGuildA )
			msg = format("#Y【国家】挑战朱雀之主#W\n \n#G朱雀守护帮会:#R%s#r#G申请帮会：#W待申请\n \n您确定要发起挑战吗？",strGuildA)
		end
	end

    BeginQuestEvent(sceneId)
    AddQuestText(sceneId, msg);
    AddQuestNumText(sceneId,x310114_g_ScriptId,"确定..",3,1);
    EndQuestEvent(sceneId)
    DispatchQuestEventList(sceneId,selfId,targetId)

    return 1
end

function x310114_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--接受
----------------------------------------------------------------------------------------------
function x310114_ProcAccept( sceneId, selfId )
end


----------------------------------------------------------------------------------------------
--申请结果
----------------------------------------------------------------------------------------------
function x310114_OnZhuQueBattleSignupResult( sceneId,selfId,nResult,nGuildA, nGuildB,nSignupCount)

	local targetId = GetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID)
	
	if nResult == 0 then

		local strMsg = ""
		local strMsg1= ""
		if nSignupCount > 0 then
        	strMsg = format("#Y【国家】挑战朱雀之主#W#r\t恭喜本帮会成功报名朱雀战场，目前为止已有%d个帮会报名参加。",nSignupCount)
        	strMsg1= format("恭喜本帮会成功报名朱雀战场，目前为止已有%d个帮会报名参加。",nSignupCount)
        else
        	strMsg = "#Y【国家】挑战朱雀之主#W#r\t恭喜本帮会成功报名朱雀战场，目前除了本帮会还没有其他帮会报名参加。"
			strMsg1= "恭喜本帮会成功报名朱雀战场，目前除了本帮会还没有其他帮会报名参加。"
        end
	
    	local nGuildId = GetGuildID(sceneId,selfId )        
       
        LuaAllScenceM2Guild(sceneId,strMsg1,nGuildId,3,1)
        LuaAllScenceM2Guild(sceneId,strMsg1,nGuildId,2,1)

        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strMsg);
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 100 then
    	
    	--活动没开启
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，很抱歉，请在每周日的20：25~20：40之间申请朱雀战场。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
    elseif nResult == 101 then
    
    	--帮会没有报名
        x310114_ZhuQueBattleSignup( sceneId,selfId,targetId,nGuildA,nGuildB )
        
    elseif nResult == 102 then
    	
    	--已经报名
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t很抱歉，已经受理了您挑战朱雀之主的请求，无法再次挑战朱雀之主。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
    elseif nResult == 103 then
    	
    	--没有帮会
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，必须有帮会才能申请挑战朱雀之主！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 104 then
    
    	--帮会等级不够
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，帮会等级不足2级！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 105 then
    
    	--不是帮主
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，必须是帮主才可以申请！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 106 then
    	
    	--帮会人数不足
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，帮会成员不足30人！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 107 then
    
    	--青龙帮错误,不能是青龙帮
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，不能是青龙帮！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 108 then
    
    	--国王帮错误,不能是国王帮
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，不能是国王帮！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 109 then
    	
    	--帮会实力不足
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，帮会实力必须大于已经申请的帮会实力！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
	elseif nResult == 110 then
    	
    	--报名结束
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，报名已经结束");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
	elseif nResult == 111 then
		
		--报过青龙报了
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，报过青龙守护了");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
    elseif nResult == -1 then
    
    	--未知错误
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】挑战朱雀之主#W#r\t申请失败，未知原因，可能朱雀战场申请数已达上线！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    end

    return 1

end


----------------------------------------------------------------------------------------------
--查询结果
----------------------------------------------------------------------------------------------
function x310114_OnQueryCurrentGuild(sceneId,selfId,nGuildA,nGuildB,nCount)
	
	local targetId = GetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID)
	
	--分各种情况对朱雀帮会进行处理
	local msg = ""
	local nCountryGuildId = CountryGetOfficerGUID(GetCurCountry(sceneId,selfId),1)
	if nCountryGuildId <= 0 then
		
		--没有朱雀守护的情况
		if nGuildA >= 0 and nGuildB >= 0 then
			
			--如果已经有人挑战了
			local strGuildA = GetGuildName( nGuildA )
			local strGuildB = GetGuildName( nGuildB )
			msg = format("#Y【国家】朱雀战场查询#W\n \n#G当前没有朱雀守护帮会\n#G申请帮会：#R%s\n#G申请帮会：#R%s",strGuildA,strGuildB)
			
		elseif nGuildA >= 0 and nGuildB < 0 then
			--如果只有一方挑战
			local strGuildA = GetGuildName( nGuildA )
			msg = format("#Y【国家】朱雀战场查询#W\n \n#G当前没有朱雀守护帮会\n#G申请帮会：#R%s\n#G申请帮会：#W待申请",strGuildA)
		else
			--如果没有人挑战
			msg = "#Y【国家】朱雀战场查询#W\n \n#G当前没有朱雀守护帮会\n#G申请帮会：#W待申请\n#G申请帮会：#W待申请"
		end
		
	else
		--有朱雀守护的情况
		if nGuildB >= 0 then
			--如果已经有人挑战了
			
			local strGuildA = GetGuildName( nGuildA )
			local strGuildB = GetGuildName( nGuildB )
			msg = format("#Y【国家】朱雀战场查询#W\n \n#G朱雀守护帮会:#R%s\n#G申请帮会:#R%s",strGuildA,strGuildB)
			
		else
			local strGuildA = GetGuildName( nGuildA )
			--如果没有人挑战
			msg = format("#Y【国家】朱雀战场查询#W\n \n#G朱雀守护帮会:#R%s\n#G申请帮会：#W待申请",strGuildA)
		end
	end

    BeginQuestEvent(sceneId)
    AddQuestText(sceneId, msg);
    EndQuestEvent(sceneId)
    DispatchQuestEventList(sceneId,selfId,targetId)

    return 1
    	
end

----------------------------------------------------------------------------------------------
--报名被顶替处理
----------------------------------------------------------------------------------------------
function x310114_OnSignupInstead(sceneId,nCountryId,nGuildA,nGuildB)
	
	local strGuildB = GetGuildName(nGuildB)
	local msg = format("#R很抱歉，朱雀战场的报名名额已被帮会实力更高的%s帮会顶替",strGuildB)  
	
	local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 and IsPlayerStateNormal(sceneId,objId) == 1 then
        
            local nGuildId = GetGuildID( sceneId,objId )
            if nGuildId == nGuildA then
            	
            	
            	LuaScenceM2Player(sceneId,objId,msg,GetName(sceneId,objId),3,1)          	
            	LuaScenceM2Player(sceneId,objId,msg,GetName(sceneId,objId),2,1)
            end
        end
    end
	
end


----------------------------------------------------------------------------------------------
--检测接受条件
----------------------------------------------------------------------------------------------
function x310114_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--接受
----------------------------------------------------------------------------------------------
function x310114_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--放弃
----------------------------------------------------------------------------------------------
function x310114_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--继续
----------------------------------------------------------------------------------------------
function x310114_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--检测是否可以提交
----------------------------------------------------------------------------------------------
function x310114_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--提交
----------------------------------------------------------------------------------------------
function x310114_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--杀死怪物或玩家
----------------------------------------------------------------------------------------------
function x310114_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--进入区域事件
----------------------------------------------------------------------------------------------
function x310114_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--道具改变
----------------------------------------------------------------------------------------------
function x310114_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end