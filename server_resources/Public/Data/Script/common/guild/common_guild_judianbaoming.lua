
--领地争夺战申请

x300919_g_ScriptId              			= 300919
x300919_g_Leader_Index          			= 5
x300919_g_MissionName           			="【国家】领地争夺战报名"
x300919_g_MissionName1          			="【国家】领地争夺战查询"
x300919_g_NeedMoney             			= 50*1000
x300919_g_GuildLevel            			= 1
x300919_g_GuildMemberNum       				= 1
x300919_g_Laird_Signup                  	= 300     --报名
x300919_g_Laird_WaitBattle              	= 301     --报名结束，等待领地争夺战
x300919_g_Laird_BeginBattle             	= 302     --开始领地争夺战
x300919_g_Laird_EndBattle               	= 303     --结束领地争夺战
x300919_g_Leader_Index                      =  5


----------------------------------------------------------------------------------------------
--取得领地场景信息包装函数
----------------------------------------------------------------------------------------------
function x300919_GetLairdSceneCount(sceneId)
	return CallScriptFunction(300918,"GetLairdSceneCount",sceneId)
end

function x300919_GetLairdSceneInfo(sceneId,nIndex)
	return CallScriptFunction(300918,"GetLairdSceneInfo",sceneId,nIndex)
end

function x300919_GetLairdMapNameByID(sceneId,MapSignuped)

	if MapSignuped == nil then
		return "其他"
	end
	
	local nLairdSceneCount = x300919_GetLairdSceneCount(sceneId)
	for i=1,nLairdSceneCount do
		local nRetNpcGUID,nRetLairdScene,strRetLairdSceneName,nRetLevel,nRetFlag0,nRetFlag1 = x300919_GetLairdSceneInfo(sceneId,i)
		if nRetLairdScene == MapSignuped then
			return strRetLairdSceneName
		end
	end
	
	return "其他"	
end
											   
----------------------------------------------------------------------------------------------
--取得等级排行榜最后一名
----------------------------------------------------------------------------------------------
function x300919_GetLastLevelFromLevelTopList(sceneId, selfId)
	
	local nWorldID = GetWorldID(sceneId,selfId)
	local nLevelTopListType = LEVEL_TOP_LIST_BK - 1
	local nLevelCount = GetToplistCount(nWorldID,nLevelTopListType)
	if nLevelCount <= 0 then
		return 0
	else
		local _,nLastLevel = GetToplistInfo(nWorldID,nLevelTopListType,nLevelCount-1) 
		return nLastLevel
	end
end

----------------------------------------------------------------------------------------------
--检查领地场景级别是否达到开放要求
----------------------------------------------------------------------------------------------	
function x300919_CheckLairdSceneLevel(sceneId, selfId, nLevel )

	local nLastLevel = x300919_GetLastLevelFromLevelTopList(sceneId, selfId)
	if nLastLevel >= nLevel then
		return 1
	end
	
	return 0
	
end
											   
----------------------------------------------------------------------------------------------
--检查NPC是否是入口
----------------------------------------------------------------------------------------------										   
function x300919_IsNpcEntrance( sceneId,nNpcGUID )

	local nLairdSceneCount = x300919_GetLairdSceneCount(sceneId)
	for i=1,nLairdSceneCount do
		local nRetNpcGUID,nRetLairdScene,strRetLairdSceneName,nRetLevel,nRetFlag0,nRetFlag1 = x300919_GetLairdSceneInfo(sceneId,i)
		if nRetNpcGUID == nNpcGUID then
			return 1
		end
	end
	
	
	return 0	
end


----------------------------------------------------------------------------------------------
--枚举
----------------------------------------------------------------------------------------------
function x300919_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_LAIRDGBATTLELITE ) == 0 then
        return
    end

    --检查帮会
    local nGuildId = GetGuildID(sceneId,selfId )
    if nGuildId < 0 then
        return
    end
    
    --弹出相关选项
    --local nBattleStatus = CallScriptFunction(300918,"GetBattleState",sceneId)
	--if nBattleStatus == x300919_g_Laird_Signup then
		--if x300919_IsNpcEntrance(sceneId,GetMonsterGUID(sceneId,targetId)) == 1  then
			AddQuestNumText(sceneId,x300919_g_ScriptId,x300919_g_MissionName1,3,x300919_g_ScriptId);
		--end
	--end

    --检查是否是帮主

    --检查是否有国王
    local nHumanGUID = GetPlayerGUID( sceneId,selfId )
    local nCountryId,nKingGUID,szKingName,nCountryGold = GetCountrySimpleData( sceneId,selfId )
    if nKingGUID <= 0 or nHumanGUID == nKingGUID then
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
	--if nBattleStatus == x300919_g_Laird_Signup then
		--if x300919_IsNpcEntrance(sceneId,GetMonsterGUID(sceneId,targetId)) == 1 then
    		AddQuestNumText(sceneId,x300919_g_ScriptId,x300919_g_MissionName,3);
    	--end
   -- end
    
end

----------------------------------------------------------------------------------------------
--默认事件
----------------------------------------------------------------------------------------------
function x300919_ProcEventEntry( sceneId, selfId, targetId,scriptId,idExt )

	 local pos = GetGuildOfficial(sceneId, selfId)
	if pos ~= x300919_g_Leader_Index then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "申请失败，很抱歉，只有帮主才有权查询或申请。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
        return
    end

	local nNpcGUID = GetMonsterGUID(sceneId,targetId)

    if idExt == 0 then
    
    
    	--状态检查
    	local nBattleStatus = CallScriptFunction(300918,"GetBattleState",sceneId)
    	if nBattleStatus ~= x300919_g_Laird_Signup then
    		--活动没开启
    		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "申请失败，很抱歉，请在每周六的13：00~15：00之间申请领地争夺战。");
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,targetId)
    		return
    	end
    	
    	--做NPC检查
    	if x300919_IsNpcEntrance(sceneId, nNpcGUID ) == 0 then
    		return
    	end
		
    	--显示领地列表
    	local nLairdSceneCount = x300919_GetLairdSceneCount(sceneId)
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r \n#G您可以发起对以下领地的争夺:#W");
    	for i=1,nLairdSceneCount do
			local nRetNpcGUID,nRetLairdScene,strRetLairdSceneName,nRetLevel,nRetFlag0,nRetFlag1 = x300919_GetLairdSceneInfo(sceneId,i)
			if nRetNpcGUID == nNpcGUID and x300919_CheckLairdSceneLevel( sceneId, selfId,nRetLevel ) == 1 then	
				AddQuestNumText(sceneId,x300919_g_ScriptId,"【领地】"..strRetLairdSceneName,3,nRetFlag0);
			end
		end
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    elseif idExt == x300919_g_ScriptId then
    
    
    	--做NPC检查
    	if x300919_IsNpcEntrance( sceneId,nNpcGUID ) == 0 then
    		return
    	end
    	
    	--显示领地列表
    	local nLairdSceneCount = x300919_GetLairdSceneCount(sceneId)
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战查询#W#r#G请选择下列按钮查询相应领地报名情况:#W");
    	for i=1,nLairdSceneCount do
			local nRetNpcGUID,nRetLairdScene,strRetLairdSceneName,nRetLevel,nRetFlag0,nRetFlag1 = x300919_GetLairdSceneInfo(sceneId,i)
			if nRetNpcGUID == nNpcGUID and x300919_CheckLairdSceneLevel(sceneId, selfId, nRetLevel ) == 1 then	
				AddQuestNumText(sceneId,x300919_g_ScriptId,"【领地】"..strRetLairdSceneName,3,nRetFlag1);
	
			end
		end
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    else
    	
    	--处理结果
    	local nLairdSceneCount = x300919_GetLairdSceneCount(sceneId)
    	for i=1,nLairdSceneCount do
    	
			local nRetNpcGUID,nRetLairdScene,strRetLairdSceneName,nRetLevel,nRetFlag0,nRetFlag1 = x300919_GetLairdSceneInfo(sceneId,i)
    		
    		if nRetFlag0 == idExt then
    		
    			 --战场没有开放
		        if x300919_CheckLairdSceneLevel(sceneId, selfId, nRetLevel ) ~= 1 then
		        	
		        	BeginQuestEvent(sceneId)
		            AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，领地争夺战目前没有开放！");
		            EndQuestEvent(sceneId)
		            DispatchQuestEventList(sceneId,selfId,targetId)
		            return
		        	
		        end
    			
    			--查询结果
		        GameBattleQuerySignupState( sceneId,selfId,2,nRetLairdScene )
		        SetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID,targetId)   
		        
		        break	
    			
    		elseif nRetFlag1 == idExt then
    		
    			 --战场没有开放
		        if x300919_CheckLairdSceneLevel(sceneId, selfId, nRetLevel ) ~= 1 then
		        	
		        	BeginQuestEvent(sceneId)
		            AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，领地争夺战目前没有开放！");
		            EndQuestEvent(sceneId)
		            DispatchQuestEventList(sceneId,selfId,targetId)
		            return
		        	
		        end
    			
    			--配对查询
    			GameBattleQueryMatchState(sceneId,selfId,2,nRetLairdScene)
    			SetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID,targetId)
    			break
    			
    		elseif nRetLairdScene == idExt then
    			
    			--是否是帮主
		        local pos = GetGuildOfficial(sceneId, selfId)
		        if pos ~= x300919_g_Leader_Index then
		            BeginQuestEvent(sceneId)
		            AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，很抱歉，您还不是帮主无法申请成为领地之主。");
		            EndQuestEvent(sceneId)
		            DispatchQuestEventList(sceneId,selfId,targetId)
		            return
		        end
		
		        local nGuildId = GetGuildID(sceneId,selfId )
		        local nLevel,nMemberNum,nExp = GetGuildSimpleData( nGuildId )
		
		        --帮会等级是满足
		        if nLevel < x300919_g_GuildLevel then
		            BeginQuestEvent(sceneId)
		            AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，帮会等级不足２级！");
		            EndQuestEvent(sceneId)
		            DispatchQuestEventList(sceneId,selfId,targetId)
		            return
		        end
		
		        --帮会会员数量是否满足
		        if nMemberNum < x300919_g_GuildMemberNum then
		            BeginQuestEvent(sceneId)
		            AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，帮会成员不足30人！");
		            EndQuestEvent(sceneId)
		            DispatchQuestEventList(sceneId,selfId,targetId)
		            return
		        end
		        
		        --战场没有开放
		        if x300919_CheckLairdSceneLevel(sceneId, selfId, nRetLevel ) ~= 1 then
		        	
		        	BeginQuestEvent(sceneId)
		            AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，领地争夺战目前没有开放！");
		            EndQuestEvent(sceneId)
		            DispatchQuestEventList(sceneId,selfId,targetId)
		            return
		        	
		        end
		        
		        --是否是领主
		        local nLairdMap1,nLairdMap2,nLairdMap3,nLairdMap4 = GetGuildLairdSceneId(nGuildId)
		        if nLairdMap1 > 0 then
		        	
		        	BeginQuestEvent(sceneId)
		            AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，已经是领主了，无法再次申请！");
		            EndQuestEvent(sceneId)
		            DispatchQuestEventList(sceneId,selfId,targetId)
		            return
		        	
		        end
		
		        --以上都通过，发送申请
		        GameBattleExecuteSignup( sceneId,selfId, 2, idExt )
		        SetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID,targetId)
		        break
    		end
    	end
    	
    end

    return 1

end

----------------------------------------------------------------------------------------------
--查询领地争夺战报名状态响应
----------------------------------------------------------------------------------------------
function x300919_OnQueryLairdBattleSignupState( sceneId,selfId,nResult,nLairdMapId,nGuildA,nGuildB,nHasLaird,nMapSignuped )
    
    local targetId = GetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID)
    if nResult == 0 then
    	--OK,查询状态不处理这种情况
    	
    elseif nResult == 300 then
    	
    	--活动没开启
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，很抱歉，请在每周六的13：00~15：00之间申请领地争夺战。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
    elseif nResult == 301 then
    
    	--帮会没有报名
        x300919_LairdBattleSignup( sceneId,selfId,targetId,nLairdMapId,nGuildA,nGuildB,nHasLaird )
        
    elseif nResult == 302 then
    	
    	--已经报名
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t很抱歉，您已经成功申请了一块领地的争夺，目前正在受理中，无法再次申请对其它领地的争夺。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
    elseif nResult == 303 then
    	
    	--没有帮会
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，必须有帮会才能申请挑战！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 304 then
    
    	--帮会等级不够
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，帮会等级不足2级！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 305 then
    
    	--不是帮主
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，必须是帮主才可以申请！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 306 then
    	
    	--帮会人数不足
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，帮会成员不足30人！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 307 then
    
    	--朱雀帮错误,不能是朱雀帮
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，朱雀不能申请占领领地！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 308 then
    
    	--青龙帮错误,不能是青龙帮
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，青龙不能申请占领领地！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 309 then
    	
    	--国王帮错误,不能是国王帮
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，国王不能申请占领领地！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
	elseif nResult == 310 then
    	
    	--帮会实力不足
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，帮会实力不足！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
	
	elseif nResult == 311 then
		
		--报名已经结束
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，报名已经结束！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
	elseif nResult == 312 then
	
		--已经报名了其他领地的争夺
    	BeginQuestEvent(sceneId)
		local strMapSignedup = x300919_GetLairdMapNameByID(sceneId,nMapSignuped)
		AddQuestText(sceneId, format("#Y【国家】领地争夺战报名#W#r\t申请失败，已经报名了%s领地的争夺",strMapSignedup));
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
	elseif nResult == 313 then
	
		--取得帮会信息
		local nGuidID = GetGuildID(sceneId,selfId)
		if nGuidID < 0 then
			return
		end
		
		--取得帮会领地信息

		local nGuildLairdMapId = GetGuildLairdSceneId(nGuidID)
		
		local nLairdSceneCount = x300919_GetLairdSceneCount(sceneId)
    	BeginQuestEvent(sceneId)
    	for i=1,nLairdSceneCount do
			local nRetNpcGUID,nRetLairdScene,strRetLairdSceneName,nRetLevel,nRetFlag0,nRetFlag1 = x300919_GetLairdSceneInfo(sceneId,i)
			if nGuildLairdMapId == nRetLairdScene then	
				--已经是领地帮会
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, format("#Y【国家】领地争夺战报名#W#r\t已是%s领主，无法报名参加领地争夺战",strRetLairdSceneName));
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,targetId)
				break
			end
		end

		
    else
    
    	--未知错误
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，未知原因，可能领地争夺战申请数已达上限！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    end

    return 1

end

----------------------------------------------------------------------------------------------
--帮战报名
----------------------------------------------------------------------------------------------
function x300919_LairdBattleSignup( sceneId,selfId,targetId ,nLairdMapId,nGuildA, nGuildB,nHasLaird,nMapSignuped)

	
	SetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID,targetId)
    
    --是否是帮主
    local pos = GetGuildOfficial(sceneId, selfId)
	if pos ~= x300919_g_Leader_Index then
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t很抱歉，您还不是帮主无法申请挑战领地之主。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		return 0
	end

    local nGuildId = GetGuildID(sceneId,selfId )
    local nLevel,nMemberNum,nExp = GetGuildSimpleData( nGuildId )

    --帮会等级是满足
    if nLevel < x300919_g_GuildLevel then
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，帮会等级不足2级！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		return 0
    end

    --帮会会员数量是否满足
    if nMemberNum < x300919_g_GuildMemberNum then
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，帮会成员不足30人！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		return 0
    end

    --是否是领地争夺战报名时间
    local nBattleStatus = CallScriptFunction(300918,"GetBattleState",sceneId)
	if nBattleStatus ~= x300919_g_Laird_Signup then
 		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，很抱歉，请在每周六的13：00~15：00之间申请领地争夺战。");
		EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,targetId)
		return 0
	end
	
	--分各种情况对领地帮会进行处理
	local msg = ""
	local nCountryGuildId = CountryGetOfficerGUID(GetCurCountry(sceneId,selfId),1)
	if nHasLaird ~= 1 then

		
		--没有领地帮会的情况
		if nGuildA >= 0 and nGuildB >= 0 then
			
			--如果已经有人挑战了
			local strGuildA = GetGuildName( nGuildA )
			local strGuildB = GetGuildName( nGuildB )
			msg = format("#Y【国家】领地争夺战报名#W#r#R\t已经有帮会对该领地发起了争夺申请，您确定对该帮会进行挑战吗？\n\t#G当前已发起对该领地的争夺申请并且实力最强帮会分别为:#r#c0000FF%s#r%s",strGuildA,strGuildB)
			
		elseif nGuildA >= 0 and nGuildB < 0 then
			--如果只有一方挑战
			local strGuildA = GetGuildName( nGuildA )
			msg = format("#Y【国家】领地争夺战报名#W#r#R\t已经有帮会对该领地发起了争夺申请，您确定对该帮会进行挑战吗？\n\t#G当前已发起对该领地的争夺并且实力最强帮会为:#r#c0000FF%s",strGuildA)
		else
			--如果没有人挑战
			msg = "#Y【国家】领地争夺战报名#W#r\t#G当前没有其他帮会发起对该领地的争夺!"
		end
		
	else
		--有领地帮会的情况
		if nGuildB >= 0 then
			--如果已经有人挑战了
			
			local strGuildA = GetGuildName( nGuildA )
			local strGuildB = GetGuildName( nGuildB )
			msg = format("#Y【国家】领地争夺战报名#W#r#R\t目前占据该领地的帮会是:%s，您确定对其进行挑战吗？\n\t#G当前已发起对该领地的争夺并且实力最强帮会为:#r#c0000FF%s",strGuildA,strGuildB)
			
		else
			--如果没有人挑战
			msg = "#Y【国家】领地争夺战报名#W#r#R\t已经有帮会拥有对该领地的占领，您确定要发起对该领地的挑战吗？\n\t#G当前没有任何帮会发起对该领地的挑战!"
		end
	end

    BeginQuestEvent(sceneId)
    AddQuestText(sceneId, msg);
    AddQuestNumText(sceneId,x300919_g_ScriptId,"确定..",3,nLairdMapId);
    EndQuestEvent(sceneId)
    DispatchQuestEventList(sceneId,selfId,targetId)

    return 1
end

function x300919_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--接受
----------------------------------------------------------------------------------------------
function x300919_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--申请结果
----------------------------------------------------------------------------------------------
function x300919_OnLairdBattleSignupResult( sceneId,selfId,nResult,nLiardMapId,nGuildA, nGuildB,nSignupCount,nHasLaird,nMapSignuped)

	local targetId = GetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID)
	
	if nResult == 0 then

		local strMsg = ""
		if nSignupCount > 0 then
        	strMsg = format("#Y【国家】领地争夺战报名#W#r\t恭喜本帮会成功报名【国家】领地争夺战，目前为止已有%d个帮会报名参加。",nSignupCount)
        	strMsg1= format("恭喜本帮会成功报名领地争夺战，目前为止已有%d个帮会报名参加。",nSignupCount)
        else
        	strMsg = "#Y【国家】领地争夺战报名#W#r\t恭喜本帮会成功报名【国家】领地争夺战，目前除了本帮会还没有其他帮会报名参加。"
        	strMsg1= "恭喜本帮会成功报名领地争夺战，目前除了本帮会还没有其他帮会报名参加。"
        end
	
    	local nGuildId = GetGuildID(sceneId,selfId )        
       
        LuaAllScenceM2Guild(sceneId,strMsg1,nGuildId,3,1)
        LuaAllScenceM2Guild(sceneId,strMsg1,nGuildId,2,1)
		LuaAllScenceM2Guild(sceneId,strMsg1,nGuildId,6,1)

        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strMsg);
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 300 then
    	
    	--活动没开启
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，很抱歉，请在每周六的13：00~15：00之间申请领地争夺战。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
    elseif nResult == 301 then
    
    	--帮会没有报名
        --x300919_LairdBattleSignup( sceneId,selfId,targetId,nLiardMapId,nGuildA,nGuildB,nHasLaird)
        
    elseif nResult == 302 then
    	
    	--已经报名
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t很抱歉，您已经成功申请了一块领地的争夺，目前正在受理中，无法再次申请对其它领地的争夺。");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
    elseif nResult == 303 then
    	
    	--没有帮会
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，必须有帮会才能申请挑战领地之主！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 304 then
    
    	--帮会等级不够
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，帮会等级不足2级！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 305 then
    
    	--不是帮主
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，必须是帮主才可以申请！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 306 then
    	
    	--帮会人数不足
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，帮会成员不足30人！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 307 then
    
    	--朱雀帮错误,不能是朱雀帮
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，不能是朱雀帮！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 308 then
    
    	--青龙帮错误,不能是青龙帮
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，不能是青龙帮！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	
    elseif nResult == 309 then
    	
    	--国王帮错误,不能是国王帮
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，不能是国王帮！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
	elseif nResult == 310 then
	
		
		local nCountryId = GetSceneLairdCountryId(nLiardMapId)
		local nSelfCountryId = GetCurCountry(sceneId,selfId)
		if nCountryId >= 0 and nCountryId <= 3 then
			if nCountryId == nSelfCountryId then
				--国王帮错误,不能是国王帮
		    	BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，您报名的领地已经被本国占领！");
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,targetId)
				return
			end
		end

		--帮会实力不足
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，帮会实力不足！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
			
	
	elseif nResult == 311 then
		
		--报名已经结束
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，报名已经结束！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
	elseif nResult == 312 then
	
		--已经报名了其他领地的争夺
    	BeginQuestEvent(sceneId)
    	local strMapSignedup = x300919_GetLairdMapNameByID(sceneId,nMapSignuped)
		AddQuestText(sceneId, format("#Y【国家】领地争夺战报名#W#r\t申请失败，已经报名了%s领地的争夺",strMapSignedup));
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
	elseif nResult == 313 then
	
		--取得帮会信息
		local nGuidID = GetGuildID(sceneId,selfId)
		if nGuidID < 0 then
			return
		end
		
		--取得帮会领地信息
		local nGuildLairdMapId = GetGuildLairdSceneId(nGuidID)		
		local nLairdSceneCount = x300919_GetLairdSceneCount(sceneId)
    	BeginQuestEvent(sceneId)
    	for i=1,nLairdSceneCount do
			local nRetNpcGUID,nRetLairdScene,strRetLairdSceneName,nRetLevel,nRetFlag0,nRetFlag1 = x300919_GetLairdSceneInfo(sceneId,i)
			if nGuildLairdMapId == nRetLairdScene then	
				--已经是领地帮会
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, format("#Y【国家】领地争夺战报名#W#r\t已是%s领主，无法报名参加领地争夺战",strRetLairdSceneName));
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,targetId)
				break
			end
		end
		
    else
    
    	--未知错误
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【国家】领地争夺战报名#W#r\t申请失败，未知原因，可能领地争夺战申请数已达上限！");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    end

    return 1

end


----------------------------------------------------------------------------------------------
--查询结果
----------------------------------------------------------------------------------------------
function x300919_OnQueryCurrentGuild(sceneId,selfId,nLairdMapId,nGuildA,nGuildB,nCount,nHasLaird,nMapSignuped)


	--查找名称
	local targetId = GetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID)
	local nNpcGUID = GetMonsterGUID(sceneId,targetId)
	local strLairdSceneName = ""
	local bFind = 0
	local nLairdSceneCount = x300919_GetLairdSceneCount(sceneId)
	for i=1,nLairdSceneCount do
		local nRetNpcGUID,nRetLairdScene,strRetLairdSceneName,nRetLevel,nRetFlag0,nRetFlag1 = x300919_GetLairdSceneInfo(sceneId,i)
		if nRetNpcGUID == nNpcGUID and nRetLairdScene == nLairdMapId then
			strLairdSceneName = strRetLairdSceneName
			bFind = 1
			break
		end
	end
	
	--没有找到
	if bFind == 0 then
		return
	end
	
	--分各种情况对领地帮会进行处理
	local msg = ""
	if nHasLaird ~= 1 then
		
		--没有领地帮会的情况
		if nGuildA >= 0 and nGuildB >= 0 then
			
			--如果已经有人挑战了
			local strGuildA = GetGuildName( nGuildA )
			local strGuildB = GetGuildName( nGuildB )
			msg = format("#Y【国家】领地争夺战查询#W#r#R\t#G当前已发起对【领地】%s的争夺并且实力最强帮会分别为:#r#c0000FF%s#r%s",strLairdSceneName,strGuildA,strGuildB)
			
		elseif nGuildA >= 0 and nGuildB < 0 then
			--如果只有一方挑战
			local strGuildA = GetGuildName( nGuildA )
			msg = format("#Y【国家】领地争夺战查询#W#r#R\t#G当前已发起对【领地】%s的争夺并且实力最强帮会为:#r#c0000FF%s",strLairdSceneName,strGuildA)
		else
			--如果没有人挑战
			msg = format("#Y【国家】领地争夺战查询#W#r\t#G目前没有任何帮会发起对【领地】%s的争夺!",strLairdSceneName)
		end
		
	else
		--有领地帮会的情况
		if nGuildB >= 0 then
			--如果已经有人挑战了
			
			local strGuildA = GetGuildName( nGuildA )
			local strGuildB = GetGuildName( nGuildB )
			msg = format("#Y【国家】领地争夺战查询#W#r#R\t目前占据该领地的帮会是:%s,#G当前已发起对该领地的挑战并且实力最强帮会为:#r#c0000FF%s",strGuildA,strGuildB)
			
		else
			local strGuildA = GetGuildName( nGuildA )
			--如果没有人挑战
			msg = format("#Y【国家】领地争夺战查询#W#r#R\t目前占据该领地的帮会是:%s,没有其他帮会发起对该领地的挑战!",strGuildA)
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
function x300919_OnSignupInstead(sceneId,nLairdMapId,nGuildA,nGuildB)
	
	local strGuildB = GetGuildName(nGuildB)
	local msg = format("#R本帮对领地争夺战的报名被%s帮会顶掉了",strGuildB)  
            	
	LuaThisScenceM2Guild(sceneId,msg,nGuildA,3,1)
	LuaThisScenceM2Guild(sceneId,msg,nGuildA,2,1)
end

----------------------------------------------------------------------------------------------
--外援邀请反馈
----------------------------------------------------------------------------------------------
function x300919_OnPlayerAidSignupQuery(sceneId,selfId,nRet)
	
	local msg = "未知错误,外援邀请失败"
	if nRet == 0 then
		--OK
		msg = "已经成功发送邀请."
	elseif nRet == 1 then
		--邀请的外援不在线或是没找到
		msg = "您邀请的外援不在线或不存在."
	elseif nRet == 2 then
		--邀请的外援不是同国
		msg = "您邀请的外援必须是本国玩家"
	elseif nRet == 3 then
		--邀请的外援等级不够
		msg = "您邀请的外援等级不够"
	elseif nRet == 4 then
		--邀请的外援没有帮会
		msg = "您邀请的外援没有帮会"
	elseif nRet == 5 then
		--邀请的外援所在帮会与邀请者帮会相同
		msg = "很抱歉，不能邀请本帮会成员"
	elseif nRet == 6 then
		--邀请的外援只能是国王帮或是守护帮
		msg = "您只能邀请国王帮或是守护帮成员参加领地争夺战"
	elseif nRet == 7 then
		--邀请的外援已邀请
		msg = "您邀请的目标玩家已经成功接受您的邀请"
	elseif nRet == 8 then
		--邀请的外援已被别的帮会邀请
		msg = "您邀请的外援已被其它的帮会邀请"
	elseif nRet == 9 then
		--外援名额已满
		msg = "外援名额已满，不能继续邀请"
	elseif nRet == 10 then
		--外援所在帮会也报名了据点战场
		msg = "您邀请的外援所在帮会已报名参加领地争夺战"
	elseif nRet == 11 then
		--邀请者没有帮会
		msg = "很抱歉，您没有帮会，不能进行邀请"
	elseif nRet == 12 then
		--邀请者不是帮主
		msg = "很抱歉，您不是帮主，不能进行邀请操作"
	elseif nRet == 13 then
		--邀请者所在帮会没有报名据点战
		msg = "很抱歉，您的帮会尚未报名参加领地争夺战"
	end
	
	
	Msg2Player(sceneId, selfId, msg, 8, 2)
	Msg2Player(sceneId, selfId, msg, 8, 3)
	
end


----------------------------------------------------------------------------------------------
--外援邀请反馈
----------------------------------------------------------------------------------------------
function x300919_OnPlayerAidSignupExecute(sceneId,selfId,nRet)
	
	local msg = "未知错误,外援邀请失败"
	if nRet == 0 then
		--OK
		msg = "接受成功."
	elseif nRet == 1 then
		--邀请的外援不在线或是没找到
		msg = "加入失败,邀请的外援不在线或是没找到."
	elseif nRet == 2 then
		--邀请的外援不是同国
		msg = "加入失败,必须邀请同国玩家"
	elseif nRet == 3 then
		--邀请的外援等级不够
		msg = "加入失败,等级不够"
	elseif nRet == 4 then
		--邀请的外援没有帮会
		msg = "加入失败,没有帮会"
	elseif nRet == 5 then
		--邀请的外援所在帮会与邀请者帮会相同
		msg = "加入失败,外援为本帮会成员"
	elseif nRet == 6 then
		--邀请的外援只能是国王帮或是守护帮
		msg = "加入失败,只有国王帮或是守护帮的成员才可以成为外援"
	elseif nRet == 7 then
		--邀请的外援已邀请
		msg = "加入失败,您已经接受该帮会的邀请"
	elseif nRet == 8 then
		--邀请的外援已被别的帮会邀请
		msg = "加入失败,您已经加入其它帮会的外援邀请，请放弃再继续接受邀请"
	elseif nRet == 9 then
		--外援名额已满
		msg = "加入失败,邀请您的帮会外援邀请名额已满"
	elseif nRet == 13 then
		--邀请者所在帮会没有报名据点战
		msg = "加入失败,邀请您的帮会没有参加领地争夺战"
	end
	
	
	Msg2Player(sceneId, selfId, msg, 8, 2)
	Msg2Player(sceneId, selfId, msg, 8, 3)
	
end

----------------------------------------------------------------------------------------------
--检测接受条件
----------------------------------------------------------------------------------------------
function x300919_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--接受
----------------------------------------------------------------------------------------------
function x300919_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--放弃
----------------------------------------------------------------------------------------------
function x300919_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--继续
----------------------------------------------------------------------------------------------
function x300919_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--检测是否可以提交
----------------------------------------------------------------------------------------------
function x300919_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--提交
----------------------------------------------------------------------------------------------
function x300919_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--杀死怪物或玩家
----------------------------------------------------------------------------------------------
function x300919_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--进入区域事件
----------------------------------------------------------------------------------------------
function x300919_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--道具改变
----------------------------------------------------------------------------------------------
function x300919_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end