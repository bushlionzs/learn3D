

x310223_g_LevelMax					= 40

x310223_g_GameId					= 1023
x310223_g_NeedMoney					= 2000

--MisDescBegin

x310223_g_ScriptId 					= 	310223                  --脚本ID

x310223_g_LevelLess					= 	25                      --场景开放等级  <=0 表示不限制


x310223_g_MissionName				= 	"新兵速成"

x310223_g_MaxKillNum				= 20

x310223_g_MaxCount					= 5


--MisDescEnd


function x310223_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	-- local maxlevel = GetTopListInfo_MaxLevel(GetWorldID(sceneId, selfId))
	-- if maxlevel < 60 then
		-- return
	-- end
	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then
		local  missionState = GetQuestStateNM(sceneId, selfId, targetId, MissionId)
	AddQuestTextNM(sceneId, selfId, targetId, MissionId, missionState);
	end
	
end

--选中任务
function x310223_ProcEventEntry( sceneId, selfId, targetId, MissionId )

	if GetGameOpenById(x310223_g_GameId) ~= 1 then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "服务器等级第一名达到65级，才可开启新兵速成任务");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"服务器等级第一名达到65级，才可开启新兵速成任务",8,2)	
		return
	end
	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没有这个任务

		x310223_DispatchMissionInfo( sceneId, selfId, targetId, MissionId )
		--AddDispatchQuestInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示接受任务信息
	
	else --如果有这个任务
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		local killcount = GetQuestParam(sceneId, selfId, misIndex, 0)
		if killcount == x310223_g_MaxKillNum then
			x310223_DispatchCompletedInfo( sceneId, selfId, targetId,MissionId )
			--QuestComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示完成信息
		else
			x310223_DispatchContinueInfo( sceneId, selfId, targetId,MissionId )
			--QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示任务未完成信息
		end
	end
end


--接受任务
function x310223_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then	-- 如果有这个任务直接退出
		return 0
	end
	local  WorldID = GetWorldID(sceneId,selfId)
	local  toplevel = GetToplistCount(WorldID,0)
	local  guid,LevelMax = GetToplistInfo(WorldID,0,toplevel-1)
	if GetLevel(sceneId, selfId) < x310223_g_LevelLess then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "你等级过低，不能领取任务");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"你等级过低，不能领取任务",8,2)
		return 0
	end

	if GetLevel(sceneId, selfId) > ( LevelMax-10) then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "你等级过高，不能领取任务");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"你等级过高，不能领取任务",8,2)
		return 0
	end 

	local daycount = x310223_GetDayCount(sceneId, selfId)
	if daycount >= x310223_g_MaxCount then
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "每日只能接取五次此任务，请明日再来");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		return 0
	end
	
	--local daycount = x310223_GetDayCount(sceneId, selfId)	
	if daycount > 0 then
		if IsEnoughGold(sceneId, selfId,x310223_g_NeedMoney) < 1 then
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "你的金钱不足，无法领取任务");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,"你的金钱不足，无法领取任务",8,2)
			return 0
		end
	end

	local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId ) -- 获取接受任务检查信息
	if ret > 0 then -- 如果可以接这个任务
		ret = AddQuestNM( sceneId, selfId, MissionId ) -- 给玩家添加任务
		if ret > 0 then
			x310223_ProcQuestLogRefresh( sceneId, selfId, MissionId)
			if daycount > 0 then
				
				local goldMode = GetGoldMode(sceneId, selfId)
				
				if goldMode == 1 then
					local cash = GetMoney(sceneId, selfId,2)
					if cash >= x310223_g_NeedMoney then
						CostMoney(sceneId, selfId, 2, x310223_g_NeedMoney,322)
					end
				else
					local cash = GetMoney(sceneId, selfId,2)
					local bind = GetMoney(sceneId, selfId,3)
					if bind >= x310223_g_NeedMoney then
						CostMoney(sceneId, selfId, 3, x310223_g_NeedMoney)
					elseif cash >= x310223_g_NeedMoney then
						CostMoney(sceneId, selfId, 2, x310223_g_NeedMoney,322)
					end
				end
			end

			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "您接受了任务:【个人】新兵速成");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,"您接受了任务:【个人】新兵速成",8,2)
                        GamePlayScriptLog(sceneId, selfId, 1301)
			return 1
		elseif ret == -2 then
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "任务已满，无法接受任务");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			return 0
		else
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "接受任务错误");
			EndQuestEvent();		
			DispatchQuestTips(sceneId, selfId);
			return 0
		end
	elseif ret ==-1 then  --等级不够
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "你等级过低，不能接收任务");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
	elseif ret ==-2 then
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "超过最大等级限制");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
	end

	return 0
end


--任务完成
function x310223_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
    
    if MissionId == nil or MissionId < 0 then
        return 0
    end
    
    if IsHaveQuestNM( sceneId,selfId,MissionId )<= 0 then
        return 0
    end
    
	local ret = QuestComplateNM( sceneId, selfId, targetId, MissionId, selectId ) -- 获取完成任务信息
	if ret == 1 then -- 如果成功完成
		x310223_SetDayCount(sceneId, selfId)
		
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "您完成了任务:【个人】新兵速成");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"您完成了任务:【个人】新兵速成",8,2)

		x310223_GiveReward(sceneId,selfId)
		
		x310223_SetFirst(sceneId, selfId)
		
        GamePlayScriptLog(sceneId, selfId, 1302)
		--DelQuestNM( sceneId, selfId, MissionId )
		return 1 -- 返回成功
	else -- 如果未成功完成
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "完成任务错误");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		return 0
	end
	return 0
end

function x310223_GiveReward(sceneId,selfId)

	local nExpBonus = x310223_GetExp( sceneId, selfId )
	
	AddExp(sceneId, selfId, nExpBonus)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o获得#R经验"..nExpBonus.."点#o的奖励");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId,selfId,"#o获得#R经验"..nExpBonus.."点#o的奖励",4,2)
end


function x310223_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- 如果没有这个任务
		return
	end
		
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	local submitGuid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex )
	if npcGuid == submitGuid then	--点击的NPC的名字和任务中NPC的名字相同，场景也判断过了
		local missionState = GetQuestStateNM(sceneId, selfId, npcId, MissionId)
		AddQuestTextNM( sceneId, selfId, npcId, MissionId, missionState, -1 ) -- 显示任务信息
	end
end

 

--********************************************************************
--放弃
--********************************************************************
function x310223_ProcQuestAbandon( sceneId, selfId,MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) <= 0 then
		return -1;
	end

	local ret = 0
	ret = DelQuestNM( sceneId, selfId, MissionId )
	if ret == 1 then
		x310223_SetFirst(sceneId, selfId)
		x310223_SetDayCount(sceneId, selfId)
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "您放弃了任务:【个人】新兵速成");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"您放弃了任务:【个人】新兵速成",8,2)
	end
end

--杀死怪物
function x310223_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
	local ObjName = GetName(sceneId, objId)

	local HumenNum = GetMonsterOwnerCount( sceneId, objId ) --取得这个怪物死后拥有分配权的人数
		for i = 0, HumenNum-1 do
				local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --取得拥有分配权的人的objId
				
				if humanObjId ~= -1 then
					if  GetLevel(sceneId, humanObjId) - GetLevel(sceneId, objId) <= 5 then
					if  GetHp(sceneId, humanObjId) > 0 then
				    if IsHaveQuestNM( sceneId, humanObjId, MissionId ) > 0 then	--如果这个人拥有任务
						local strText = "";
						local misIndex = GetQuestIndexByID( sceneId, humanObjId, MissionId )
						local KilledNum = GetQuestParam( sceneId, humanObjId, misIndex, 0 )
										
					    if KilledNum == x310223_g_MaxKillNum-1 then
						    SetQuestByIndex( sceneId, humanObjId, misIndex, 0, KilledNum+1 )
											SetQuestByIndex( sceneId, humanObjId, misIndex, 7, 1 )
											BeginQuestEvent(sceneId)
											if ObjName == "" then
												strText = format( "#cffcf00【个人】新兵速成：您击毙了怪物(%d/%d)", KilledNum+1, x310223_g_MaxKillNum )
											else
												strText = format( "#cffcf00【个人】新兵速成：您击毙了%s(%d/%d)", ObjName, KilledNum+1, x310223_g_MaxKillNum )
											end
											AddQuestText( sceneId, strText )
											EndQuestEvent( sceneId )
											DispatchQuestTips( sceneId, humanObjId )
											x310223_ProcQuestLogRefresh( sceneId, humanObjId, MissionId)
									elseif KilledNum < x310223_g_MaxKillNum-1 then
											SetQuestByIndex( sceneId, humanObjId, misIndex, 0, KilledNum+1 )
											BeginQuestEvent(sceneId)
											if ObjName == "" then
												strText = format( "#cffcf00【个人】新兵速成：您击毙了怪物(%d/%d)", KilledNum+1, x310223_g_MaxKillNum )
											else
												strText = format( "#cffcf00【个人】新兵速成：您击毙了%s(%d/%d)", ObjName, KilledNum+1, x310223_g_MaxKillNum )
											end
											AddQuestText( sceneId, strText )
											EndQuestEvent( sceneId )
											DispatchQuestTips( sceneId, humanObjId )
											x310223_ProcQuestLogRefresh( sceneId, humanObjId, MissionId)
					    end
				    end
				    end
				    end
				end
				
				
		end

	
end

--物品改变
function x310223_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
	return 0
end
---------------------------------------------------------------------------------------------------
--检查任务接受结果
---------------------------------------------------------------------------------------------------
function x310223_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end

function x310223_GetCost(sceneId, selfId)
	local daycount =x310223_GetDayCount(sceneId,selfId)
	if daycount > 0 then
		return 2000
	end
	return 0
end
---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x310223_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId)
	local awardexp = x310223_GetExp( sceneId, selfId )
	
	BeginQuestEvent(sceneId)

	AddQuestText(sceneId,"#Y【个人】新兵速成")
	--任务信息
	
	AddQuestText(sceneId,"   当等级排行榜第一名达到#R65级#W时，会开启新兵速成任务。最近，四国之间的矛盾渐渐加深了，我需要更多的士兵来保卫我们的国家。不过，训练新兵需要花费一些金钱，如果你愿意自负费用的话，我可以帮助你迅速变成一个训练有素的士兵。\n\t消灭等级不比你低5级以上的20只怪物，你就可以完成新兵的训练。")
	AddQuestText(sceneId," ")

	--任务目标
	AddQuestText( sceneId,"#Y任务目标：")
	AddQuestText( sceneId,"   消灭等级不比你低5级以上的20只怪物，你就可以完成新兵的训练。")
	 AddQuestText( sceneId, "\n#Y任务花费：" )
        local cost = x310223_GetCost(sceneId, selfId)
        AddQuestText( sceneId, format( "金卡:#{_MONEY%d}", cost) )
	AddQuestText( sceneId,"   \n#G小提示：\n每天可以领取五次新兵速成任务，如果世界中玩家等级越高，获得的经验也会越多。现在可以领取该任务的等级下限为25级，等级上限为低于等级排行榜上最低等级10级。每天第一次领取该任务免费。")
	AddQuestText( sceneId," ")
	--AddQuestText(sceneId,"#Y任务奖励：")
	--AddQuestText(sceneId,"  经验值："..awardexp)
	--AddQuestText(sceneId," ")
	AddQuestExpBonus(sceneId,  awardexp);
			
	EndQuestEvent()
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x310223_g_ScriptId, MissionId,0);
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x310223_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	--local maxlevel = GetTopListInfo_MaxLevel(GetWorldID(sceneId, selfId))
	--local awardexp = 0
	--if maxlevel > 0 then
		--awardexp = maxlevel*16000
	--end
	
	BeginQuestEvent(sceneId)

	AddQuestText(sceneId,"#Y【个人】新兵速成")
	--任务信息
	
	AddQuestText(sceneId,"   时间紧迫，你还是快去杀怪吧。")
	AddQuestText(sceneId," ")

	--AddQuestText(sceneId,"#Y任务奖励：")
	--AddQuestText(sceneId,"  经验值："..awardexp)
	--AddQuestText(sceneId," ")
	--AddQuestExpBonus(sceneId,  awardexp);
			
	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x310223_g_ScriptId, MissionId,0);
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x310223_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	local awardexp = x310223_GetExp( sceneId, selfId )
	
	BeginQuestEvent(sceneId)

	AddQuestText(sceneId,"#Y【个人】新兵速成")
	--任务信息
	
	AddQuestText(sceneId,"   很好，你被证明是一个合格的新兵。")
	AddQuestText(sceneId," ")

	--AddQuestText(sceneId,"  经验值："..awardexp)
	--AddQuestText(sceneId," ")
	AddQuestExpBonus(sceneId,  awardexp);
			
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x310223_g_ScriptId, MissionId);

end

function x310223_ProcQuestLogRefresh( sceneId, selfId, MissionId)

	if IsHaveQuestNM( sceneId, selfId, MissionId ) <= 0 then
		return
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	local killcount = GetQuestParam(sceneId, selfId, misIndex, 0);

	local str = "  消灭20只等级适当的怪物("..killcount.."/"..tostring(x310223_g_MaxKillNum)..")";	
	BeginQuestEvent(sceneId)	
		local awardexp = x310223_GetExp( sceneId, selfId )

		AddQuestExpBonus(sceneId,  awardexp);
			
	AddQuestLogCustomText( sceneId,
							"",						-- 标题
							"【个人】新兵速成",        -- 任务名字
							str,		--任务目标
							"@npc_132164",			--任务NPC
							"和其他玩家配合可以更快地完成任务。",               --任务攻略
							"最近，四国之间的矛盾渐渐加深了，我需要更多的士兵来保卫我们的国家。不过，训练新兵需要花费一些金钱，如果你愿意自负费用的话，我可以帮助你迅速变成一个训练有素的士兵。消灭等级不比你低5级以上的20只怪物，你就可以完成新兵的训练。",	--任务描述
							"每天可以领取五次新兵速成任务，如果世界中玩家等级越高，获得的经验也会越多。现在可以领取该任务的等级下限为25级，等级上限为低于等级排行榜上最低等级10级。每天第一次领取该任务免费。"					--任务小提示
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
		
	
end

---------------------------------------------------------------------------------------------------
--取得此任务当天当前已完成次数
---------------------------------------------------------------------------------------------------
function x310223_GetDayCount(sceneId, selfId)
	if x310223_g_MaxCount > 0 then
		local today = GetDayOfYear()
		local lastday = GetQuestData(sceneId, selfId, MD_XINBINGSUCHENG_DATE[1], MD_XINBINGSUCHENG_DATE[2], MD_XINBINGSUCHENG_DATE[3])
		if lastday ~= today then
			return 0
		end

		local daycount =  GetQuestData(sceneId, selfId, MD_XINBINGSUCHENG_DATECOUNT[1], MD_XINBINGSUCHENG_DATECOUNT[2], MD_XINBINGSUCHENG_DATECOUNT[3])
		return daycount

	end
	return 0
end

---------------------------------------------------------------------------------------------------
--更新当天接任务次数
---------------------------------------------------------------------------------------------------
function x310223_SetDayCount(sceneId, selfId)
	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_XINBINGSUCHENG_DATE[1], MD_XINBINGSUCHENG_DATE[2], MD_XINBINGSUCHENG_DATE[3])
	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_XINBINGSUCHENG_DATE[1], MD_XINBINGSUCHENG_DATE[2], MD_XINBINGSUCHENG_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_XINBINGSUCHENG_DATECOUNT[1], MD_XINBINGSUCHENG_DATECOUNT[2], MD_XINBINGSUCHENG_DATECOUNT[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, MD_XINBINGSUCHENG_DATECOUNT[1], MD_XINBINGSUCHENG_DATECOUNT[2], MD_XINBINGSUCHENG_DATECOUNT[3])
		SetQuestData(sceneId, selfId, MD_XINBINGSUCHENG_DATECOUNT[1], MD_XINBINGSUCHENG_DATECOUNT[2], MD_XINBINGSUCHENG_DATECOUNT[3], daycount+1)
	end
end

function x310223_GetFirst(sceneId, selfId)
	return GetQuestData(sceneId, selfId, MD_XINBINGSUCHENG_FIRST[1], MD_XINBINGSUCHENG_FIRST[2], MD_XINBINGSUCHENG_FIRST[3])
end

function x310223_SetFirst(sceneId, selfId)
	SetQuestData(sceneId, selfId, MD_XINBINGSUCHENG_FIRST[1], MD_XINBINGSUCHENG_FIRST[2], MD_XINBINGSUCHENG_FIRST[3], 1)
end

function x310223_GetExp( sceneId, selfId )
	local level = GetLevel(sceneId, selfId)
	local maxlevel = GetTopListInfo_MaxLevel(GetWorldID(sceneId, selfId))
	local awardexp = 0
	if maxlevel > 0 then
		awardexp = maxlevel*129600
	end
	return awardexp
end