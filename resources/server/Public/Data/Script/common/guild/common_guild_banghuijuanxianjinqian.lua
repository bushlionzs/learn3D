
x300634_g_ScriptId = 300634


--任务文本描述
x300634_g_MissionName="【帮会】帮会募集"




--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x300634_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本

	if GetGuildOfficial(sceneId, selfId) ~= -1 then--判断是否加入帮会
	
		local level = GetLevel( sceneId, selfId )	
		local localexp = 0
			if  level < 70 then
				 localexp = level * 20000
			elseif level >= 70 and level < 80 then
				 localexp = level * 36000
			elseif level >= 80 and level < 90 then
				 localexp = level * 36000*2
			elseif level >= 90 and level < 200 then
				 localexp = level * 36000*2.6
			end
		local Readme_1 = "#Y【帮会】帮会募集#W#r"
		
		local Readme_2 = "\t您可以通过捐助一个".."#G募集券".."#W".."来提升".."#G2点帮会经验，20两帮会金钱".."#W同时您也将会获得".."#G"..localexp.."点经验#W，#G100点帮贡#W，#G1点使命点#W。当帮主发布#G募集令#W时2小时内捐助募集券可获得翻倍奖励！"
		
		local Readme_3 = "#r#Y您是否要参与帮会募集?"
		
		local Readme = Readme_1 .. Readme_2..Readme_3
				
		BeginQuestEvent(sceneId);AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId);DispatchQuestInfo( sceneId, selfId, targetId, x300634_g_ScriptId, -1 );
	
	end

end

--**********************************
--列举事件
--**********************************
function x300634_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

end


--********************
--检测接受条件
--**********************************
function x300634_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x300634_ProcAccept( sceneId, selfId )

	if GetGuildOfficial(sceneId, selfId) == -1 then
		BeginQuestEvent(sceneId);AddQuestText(sceneId, "帮会募集失败。");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"很抱歉，您不是帮会成员，无法进行帮会募集。",8,2)
		return
	end
	
	if  GetItemCount( sceneId, selfId, 11990110 ) < 1 then
		BeginQuestEvent(sceneId);AddQuestText(sceneId, "帮会募集失败。");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"很抱歉，您包裹中没有募集券，帮会募集失败！",8,2)		
		return
	end
	
	if x300634_CanCashBuild(sceneId,selfId)==0 then
		BeginQuestEvent(sceneId);AddQuestText(sceneId, "帮会募集失败。");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"很抱歉，您每天只能进行1次帮会募集，请明日再来！",8,2)			
		return
	end
		
	-- 通过验证，开始逻辑处理
	DelItem( sceneId, selfId, 11990110 ,1)			--扣现金
	Msg2Player(sceneId,selfId,"【帮会】帮会募集:扣除一个募集券",8,2)
	GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_MULTI_MISSION_MUJI, x300634_g_ScriptId,-1,"OnReturn1",-1)

    -- 增加活跃度
    local id = GetGuildID( sceneId, selfId)
    if id ~= -1 then
        AddGuildActivity( sceneId, selfId, GetGuildCacheFreeParam( id, GD_GUILD_ACTIVITY_PARAM4) )
    end
end
-- 检测是否多倍
function x300634_OnReturn1(sceneId, selfId,MissionData,MissionId,targetId)
	local curTime = GetCurrentTime()
	local isMultiple = 0
	if curTime - MissionData < 2*60*60 then
		isMultiple = 1
	end
	x300634_GetBonus( sceneId,selfId, isMultiple )
end
-- 给奖励
function x300634_GetBonus( sceneId, selfId, isMultiple )
		local level =  GetLevel ( sceneId , selfId )
		local localexp = 0
			if  level < 70 then
				 localexp = level * 20000
			elseif level >= 70 and level < 80 then
				 localexp = level * 36000
			elseif level >= 80 and level < 90 then
				 localexp = level * 36000*2
			elseif level >= 90 and level < 200 then
				 localexp = level * 36000*2.6
			end
			AddExp ( sceneId , selfId , localexp )			--加个人经验
			AddGuildExp(sceneId, selfId, 2)			--加帮会经验
			AddGuildUserPoint(sceneId, selfId, 100 )		--增加个人帮贡
			AddGuildShiMing(sceneId, selfId, 1 ) --加使命点
			--AddGuildMerit (sceneId, selfId, 4 )  --加帮会功德
			AddGuildMoney (sceneId, selfId, 20000 ) --加帮会金钱
			Msg2Player(sceneId,selfId,"【帮会】帮会募集:获得#R经验"..localexp.."点#o的奖励",8,2)
			Msg2Player(sceneId,selfId,"【帮会】帮会募集:获得#R帮贡100点#o的奖励",8,2)
			Msg2Player(sceneId,selfId,"获得#R经验"..localexp.."点#o的奖励",8,3)
			Msg2Player(sceneId,selfId,"获得#R帮贡100点#o的奖励",8,3)				
			--Msg2Player(sceneId,selfId,"【帮会】帮会募集:获得帮会功德4点",8,2)	
			Msg2Player( sceneId, selfId, (GetName(sceneId, selfId)).."慷慨捐助了一个募集券，使帮会经验提高了2点，帮会使命点提高了1点，帮会金钱增加20两。", 6 )		--帮会广播
	if isMultiple == 1 then
	    local level = GetLevel ( sceneId , selfId )
		local pos = GetGuildOfficial(sceneId, selfId)
		local localexp1 = localexp*3
		local exp = localexp*2
		local exp1 = localexp*1
		local guildid =GetGuildID(sceneId, selfId)
		if pos ==5 then
			if  GetGuildCacheFreeParam(guildid,GD_GUILD_INDEX_CHIEF_MULTIMISSION_DAY) == GetDayOfYear() then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "帮主职位只能领取一次募集令奖励");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				Msg2Player(sceneId,selfId,"帮主职位只能领取一次募集令奖励",8,2)
				return
			end		
			
			AddExp ( sceneId , selfId , localexp1 )
			AddGuildUserPoint(sceneId, selfId, 300 )
			Msg2Player(sceneId,selfId,"【帮会】帮会募集:帮会多倍额外获得#R经验"..localexp1.."点#o#r【帮会】帮会募集:帮会多倍额外获得#R帮贡300点#o",8,2)
			SetGuildQuestData(sceneId,GetGuildID(sceneId,selfId),GD_GUILD_INDEX_CHIEF_MULTIMISSION_DAY,GetDayOfYear(),0)
		
		elseif pos ==4 then
			if  GetGuildCacheFreeParam(guildid,GD_GUILD_INDEX_ASSCHIEF_MULTIMISSION_DAY) == GetDayOfYear() then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "副帮主职位只能领取一次募集令奖励");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				Msg2Player(sceneId,selfId,"副帮主职位只能领取一次募集令奖励",8,2)
				return
			end		
			
			AddExp ( sceneId , selfId , exp )
			AddGuildUserPoint(sceneId, selfId, 200 )
			Msg2Player(sceneId,selfId,"【帮会】帮会募集:帮会多倍额外获得#R经验"..exp.."#o点#r【帮会】帮会募集:帮会多倍额外获得#R帮贡200点#o",8,2)
			SetGuildQuestData(sceneId,GetGuildID(sceneId,selfId),GD_GUILD_INDEX_ASSCHIEF_MULTIMISSION_DAY,GetDayOfYear(),0)
		
		else
		AddExp ( sceneId , selfId , exp1 )
		AddGuildUserPoint(sceneId, selfId, 100 )
		Msg2Player(sceneId,selfId,"【帮会】帮会募集:帮会多倍额外获得#R经验"..exp1.."点#o#r【帮会】帮会募集:帮会多倍额外获得#R帮贡100点#o",8,2)
		end
	end
end

--**********************************
--放弃
--**********************************
function x300634_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x300634_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x300634_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x300634_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x300634_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x300634_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x300634_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end


--**********************************
--判断是否能够进行现金建设
--**********************************
function x300634_CanCashBuild( sceneId, selfId )
	
	local bSuc = 0
	local day_human
	local count_human
	local day_cur = GetDayTime()

	-- 取数据
	day_human,count_human = GuildGetCashBuildTimes(sceneId, selfId)
	
	if day_cur ~= day_human then
		count_human = 1
		bSuc = 1
	elseif count_human < 1 then
		count_human = count_human + 1
		bSuc = 1
	else
		bSuc = 0
	end
	
	-- 数据刷回去
	if bSuc==1 then
		GuildSetCashBuildTimes(sceneId, selfId, day_cur, count_human )
	end
	
	return bSuc
	
end
