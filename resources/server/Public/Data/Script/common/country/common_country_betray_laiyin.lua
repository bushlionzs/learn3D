x300821_g_ScriptId	= 300821
x300821_g_curCountryID = 1
x300821_g_CountryTransPos = {
							[0] = {sceneid=50,posX=128,posZ=30},
							[1] = {sceneid=150,posX=128,posZ=30},
							[2] = {sceneid=250,posX=128,posZ=30},
							[3] = {sceneid=350,posX=128,posZ=30},
							}

function x300821_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
end

--点击（按钮）点击该任务后执行此脚本
function x300821_ProcEventEntry( sceneId, selfId, targetId)		

	BeginQuestEvent(sceneId)

		local Readme_1 = "#Y【国家】前往天山#r#W #r"	
		local Readme_2 = "   您确实想放弃现有的国籍，前往天山王国发展么？#r"
		local Readme_3 ="#G提示，您必须等以下情况消失或解除后，才可以进行国籍改变：#r"
		local Readme_4 ="#G1.保护时间内上线，或转换地图保护时间未消失。#r2.处于护送状态时。#r3.处于变身状态中。#r4.您身上有国家官职。#r5.您必须退出帮会。#r"
		local Readme_5 ="#G6.您在组队状态下。#r7.您必须完成或放弃身上的所有任务。#r8.您必须解除夫妻或师徒关系。#r9.距离上次改变国籍时间小于一周。"
		--local Readme_3 = "\t 确认放弃国籍，背叛到昆仑吗？策划加字....#r"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
		AddQuestText( sceneId,Readme)

	EndQuestEvent(sceneId)

	DispatchQuestEventList(sceneId,selfId,targetId);
	DispatchQuestInfo( sceneId, selfId, targetId, 300821, -1 );

end



--点击（确定）
function x300821_ProcAcceptCheck( sceneId, selfId, NPCId )

	-- 只能到弱国
	-- if GetCountryRank(x300821_g_curCountryID) ~= 3 then
		-- BeginQuestEvent(sceneId)
		-- local strText = "很抱歉，您目前只能前往弱国！"
		-- AddQuestText( sceneId, strText )
		-- EndQuestEvent( sceneId )
		-- DispatchQuestTips( sceneId, selfId )
		-- return			
	-- end

	--1.保护状态
	if IsPlayerMutexState(sceneId, selfId,PLAYER_STATE_PROTECTTIME) == 1 then
		BeginQuestEvent(sceneId)
		local strText = "很抱歉，您现在处于保护状态，请等状态消失后才能放弃国籍！"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return		
	end
	
	--2.密保卡锁定
	
	--3.护送状态
	if IsPlayerMutexState(sceneId, selfId,PLAYER_STATE_CRASHBOX) == 1 then
		BeginQuestEvent(sceneId)
		local strText = "很抱歉，您正处于护送状态，不能放弃国籍！"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return		
	end	
	
	--4.变身
	if IsPlayerMutexState(sceneId, selfId,PLAYER_STATE_TIESAN) == 1 		--铁人三项
		or IsHaveSpecificImpact(sceneId, selfId,7702) == 1				--夺旗任务有BUFF
		or IsPlayerMutexState(sceneId, selfId,PLAYER_STATE_TONGQUBUFF) == 1	--童趣任务有BUFF
		then
		BeginQuestEvent(sceneId)
		local strText = "很抱歉，您正处于变身状态，不能放弃国籍！"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return			
	end
	
	--5.有国家官职
	if CountryGetOfficial(sceneId, selfId) ~= 0 then
		BeginQuestEvent(sceneId)
		local strText = "很抱歉，您必须先辞去国家相关职务，才可以放弃国籍！"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return			
	end
	
	--6.有帮会
	if GetGuildID(sceneId, selfId) ~= -1 then
		BeginQuestEvent(sceneId)
		local strText = "很抱歉，您必须先脱离帮会，才可以放弃国籍！"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return			
	end
	
	--7.有任务
	if GetQuestCount(sceneId, selfId) > 0 then
		BeginQuestEvent(sceneId)
		local strText = "很抱歉，您必须先将您身上的任务完成或放弃，才可以放弃国籍！"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return			
	end
	
	--8.有夫妻关系
	if IsMarried(sceneId, selfId) == 1 then
		BeginQuestEvent(sceneId)
		local strText = "很抱歉，您必须先解除夫妻关系，才可以放弃国籍！"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return		
	end
	
	--9.有师徒关系
	if IsHaveMaster(sceneId, selfId) == 1 
		or IsHavePrentice(sceneId, selfId) == 1  then
		BeginQuestEvent(sceneId)
		local strText = "很抱歉，您必须先解除师徒关系，才可以放弃国籍！"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return		
	end
	
	--10.有队伍
	if HasTeam(sceneId, selfId) == 1 then
		BeginQuestEvent(sceneId)
		local strText = "很抱歉，您必须先退出队伍，才可以放弃国籍！"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return	
	end
	
	--11.上次叛国7天内，不能再次叛国
	local lastDay = GetQuestData(sceneId,selfId,MD_COUNTRY_BETRAY_LASTDAY[1], MD_COUNTRY_BETRAY_LASTDAY[2],MD_COUNTRY_BETRAY_LASTDAY[3])
	local curDay = GetDayTime()
	local diffDay = x300821_GetDiffDay(lastDay,curDay)
	if diffDay < 7 then
		BeginQuestEvent(sceneId)
		local strText = "很抱歉，放弃国籍7天内不能再次放弃国籍"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return
	end
	
	--所有检查均通过
	return 1
	
end


--**********************************
--接受
--**********************************
function x300821_ProcAccept( sceneId, selfId )

	-- 开始更改国籍流程
	-- 1.扣除金钱
	local nCost = x300821_GetBetrayCost()
	if x300821_CostMoney(sceneId, selfId, nCost ) == 0 then
		BeginQuestEvent(sceneId)
		local strText = "很抱歉，您身上的现金不足以支付放弃国籍的费用！"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return	
	end
	
	-- 2.向GLServer发消息，GL收到后，更改用户的国家ID，刷新国家内部数据，刷新用户相关排行榜
	SendCountryBetrayMsg( sceneId, selfId, x300821_g_curCountryID, x300821_g_ScriptId )

end

--**********************************
--GLServer返回结果时，调用的回调函数
--**********************************
function x300821_OnCountryBetrayResult( sceneId, selfId, result )

	-- 失败！
	if result == 0 then
		
		BeginQuestEvent(sceneId)
		local strText = "很抱歉，服务器内部错误，改变国籍失败！"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
		-- 将已经扣除的金钱还给用户
		local nCost = x300821_GetBetrayCost()
		AddMoney( sceneId, selfId, 3, nCost )
		
		return
	end
	
	-- 成功！
	--1.通知客户端
	BeginQuestEvent(sceneId)
	local strText = "恭喜，您已成功改变国籍为"..GetCountryName(x300821_g_curCountryID)
	AddQuestText( sceneId, strText )
	EndQuestEvent( sceneId )
	DispatchQuestTips( sceneId, selfId )	
	
	--2.更新叛国时间
	local curDay = GetDayTime()
	SetQuestData(sceneId,selfId,MD_COUNTRY_BETRAY_LASTDAY[1], MD_COUNTRY_BETRAY_LASTDAY[2],MD_COUNTRY_BETRAY_LASTDAY[3], curDay )
	
	--3.拉人到新国家的王城，同时设置NextScene的场景，以防传送过程中掉线。
	local newSceneId 	= x300821_g_CountryTransPos[x300821_g_curCountryID].sceneid
	local newPosX		= x300821_g_CountryTransPos[x300821_g_curCountryID].posX
	local newPosZ		= x300821_g_CountryTransPos[x300821_g_curCountryID].posZ
	SetPlayerNextSceneInfo(sceneId, selfId, newSceneId, newPosX, newPosZ)
	NewWorld(sceneId, selfId, newSceneId, newPosX, newPosZ, x300821_g_ScriptId)
	
end

--**********************************
--放弃
--**********************************
function x300821_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300821_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300821_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300821_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300821_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300821_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300821_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end


-- 取得叛国需要的金卡钱数，单位文
function x300821_GetBetrayCost( )

	local nRank = GetCountryRank(x300821_g_curCountryID)
	local nCost = 0
	
	if nRank == 0 then 
		nCost = 50000		--强国
	elseif nRank == 1 or nRank == 2 then 
		nCost = 50000		--中等国
	elseif nRank == 3 then 
		nCost = 50000		--弱国
	end	
	
	return nCost
	
end

--扣除玩家金卡或现金
function x300821_CostMoney( sceneId, selfId, value )
	local nGoldMode = GetGoldMode( sceneId, selfId )
	
	--if nGoldMode == 1 then		--优先现金结算
		if CostMoney(sceneId, selfId, 2, value,303) == -1 then
			return 0
		end
	
	-- elseif nGoldMode == 0 then	--优先金卡结算
		-- if CostMoney(sceneId, selfId, 3, value,303) == -1 then
			-- if CostMoney(sceneId, selfId, 2, value,303) == -1 then
				-- return 0
			-- end
		-- end
	
	-- else						--未知的结算模式
		-- return 0
	-- end

	return 1
end

--计算时间差
function x300821_GetDiffDay( lastDay, curDay )
	local diffDay = 0;
	local lastYear = floor(lastDay/1000);
	local curYear = floor(curDay/1000);
	local lastDayofYear = mod(lastDay,1000);
	local curDayOfYear = mod(curDay,1000);
	local DayCount = 365;

	if mod(lastYear,4)==0 then
		DayCount = 366;
	end
	
	if curDay<lastDay then
		diffDay = 0
	elseif curYear == lastYear then
		diffDay = curDay - lastDay
	elseif curYear < lastYear then
		diffDay = 0
	elseif curYear > lastYear then
		diffDay = (curYear-lastYear)*DayCount + curDayOfYear - lastDayofYear;
	end
	
	return diffDay
end