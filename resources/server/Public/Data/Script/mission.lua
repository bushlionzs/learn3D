
--任务系统全局函数的脚本文件

--脚本号
x888891_g_scriptId = 888891

x888891_g_AcceptMessage		= "#cffcf00您接受了任务：%s"
x888891_g_AbandonMessage	= "#cffcf00您放弃了任务：%s"
x888891_g_CompleteMessage	= "#cffcf00您完成了%s任务！"
x888891_g_AbandonErrorMessage	= "#cffcf00任务%s不能被放弃！"
x888891_g_BlueItemMissionList = {
									{misId = 9410, scriptId = 300783},
								}

function x888891_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, MissionId )
	if FrontMissiontId1 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
			return 0--如果前置任务没做直接返回
		end
	end
	if FrontMissiontId2 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
			return 0--如果前置任务没做直接返回
		end
	end
	if FrontMissiontId3 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
			return 0--如果前置任务没做直接返回
		end
	end
	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then
		return 0--如果任务完成，返回
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没有这个任务
		if QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId ) > 0 then	-- 如果可以接这个任务
			local  missionState = GetQuestStateNM(sceneId, selfId, targetId, MissionId)
			AddQuestTextNM( sceneId, selfId, targetId, MissionId, missionState, -1 ) -- 显示任务信息
			return 1
		end
	end

	return 0
end

--选中任务
function x888891_ProcEventEntry( sceneId, selfId, targetId, MissionId )

	--如果该任务已经完成直接退出(跑环任务例外)
	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then
		return
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没有这个任务

		if  IsNpcHaveQuestNM(sceneId, selfId, targetId, MissionId) == 1 then--这里判断npc身上是否有这个任务，否则会出bug

			local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )
			if ret > 0 then	-- 如果可以接这个任务
				AddDispatchQuestInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示接受任务信息
			else
				local strText = "#cffcf00未知错误，无法接新的任务"
				if ret == -1 then
					strText = "#cffcf00等级不足，无法接新的任务"
				elseif ret == -2 then
					strText = "#cffcf00等级过高，无法接新的任务"
				elseif ret == -3 then
					strText = "#cffcf00金钱不足，无法接新的任务"
				elseif ret == -4 then
					strText = "#cffcf00您不是本国玩家，无法接新的任务"
				elseif ret == -5 then
					strText = "#cffcf00职业类型不符，无法接新的任务"
				elseif ret == -6 then
					strText = "#cffcf00阵营不符，无法接新的任务"
				elseif ret == -7 then
					strText = "#cffcf00此人无此任务"
				end
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, strText);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end
		else
			local strText = "#cffcf00此人无此任务"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end

	else --如果有这个任务
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		if QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) > 0 then -- 如果任务可以完成
			QuestComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示完成信息
		else
			QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示任务未完成信息
		end
	end
end

--接受任务
function x888891_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	--如果该任务已经完成直接退出(跑环任务例外)
	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then	-- 如果有这个任务直接退出
		return 0
	end
	
	--检查前置任务
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, MissionId )
	if FrontMissiontId1 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
			return 0--如果前置任务没做直接返回
		end
	end
	if FrontMissiontId2 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
			return 0--如果前置任务没做直接返回
		end
	end
	if FrontMissiontId3 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
			return 0--如果前置任务没做直接返回
		end
	end

	local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId ) -- 获取接受任务检查信息
	if ret > 0 then -- 如果可以接这个任务
		local retAddMission = AddQuestNM( sceneId, selfId, MissionId ) -- 给玩家添加任务

		--SetPlayerAbilityLevel(sceneId, selfId, 26, 1)	--防止玩家不会采集的生活技能,playertemplate完善后，可以不需要此段

		for i = 0, 4 do
			local SceneID, PosX, PosZ, tips = GetAskWayPosNM(sceneId, selfId, MissionId, i)
			if SceneID ~= -1 then
				CallScriptFunction( UTILITY_SCRIPT, "AskTheWayPos", sceneId, selfId, SceneID, PosX, PosZ, tips )
			end
		end
		
		local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
		local message = format(x888891_g_AcceptMessage, MissionName);
		local strText = message
		if retAddMission == 0 then
			strText = "#cffcf00添加任务失败"

            BeginQuestEvent(sceneId)
		    AddQuestText(sceneId, strText);
		    EndQuestEvent(sceneId)
		    DispatchQuestTips(sceneId,selfId)
            
            return 1

		elseif retAddMission == -1 then
			
            strText = "#cffcf00背包已满,请整理后再来接任务"
            
            BeginQuestEvent(sceneId)
		    AddQuestText(sceneId, strText);
		    EndQuestEvent(sceneId)
		    DispatchQuestTips(sceneId,selfId)

            return 1

		elseif retAddMission == -2 then
            strText = "#cffcf00您的任务已满！"

            BeginQuestEvent(sceneId)
		    AddQuestText(sceneId, strText);
		    EndQuestEvent(sceneId)
		    DispatchQuestTips(sceneId,selfId)

            return 1
        end

        Msg2Player(sceneId, selfId, strText, 0, 2)
		Msg2Player(sceneId, selfId, strText, 0, 3)
		return 1
	end

	return 0
end

--杀死怪物
function x888891_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
															--场景ID, 自己的ID, 怪物表位置号, 怪物objId, 任务ID
	local NeedKilledNum, InstIndex, ObjName = GetQuestNeedKillObjInfoNM( sceneId, selfId, MissionId, objdataId, objId )


	if NeedKilledNum == 0 then --杀怪得物品类型的任务
		local KilledNum = GetMonsterOwnerCount( sceneId, objId ) --取得这个怪物死后拥有分配权的人数
		for i = 0, KilledNum-1 do
			local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --取得拥有分配权的人的objId
            if humanObjId ~= -1 then
                if IsHaveQuestNM( sceneId, humanObjId, MissionId ) > 0 then	--如果这个人拥有任务
                    local ItemCount, ItemID, ItemRand, ItemDropNum = GetQuestItemNM( sceneId, humanObjId, MissionId, InstIndex )
                            --要收集的个数，物品ID，掉落率，一次最大掉落
                    if ItemCount > 0 then
                        local ItemNumOnPlayer = GetItemCount( sceneId, humanObjId, ItemID )
                        if ItemNumOnPlayer < ItemCount then
                            local droprand = random(100)
                            if droprand <= ItemRand then
                                local dropnum = random(ItemDropNum)
                                if dropnum == 0 then
                                    dropnum = 1
                                end
                                if dropnum > ItemID - ItemNumOnPlayer then
                                    dropnum = ItemID - ItemNumOnPlayer
                                end
                                BeginAddItem(sceneId)
                                AddItem( sceneId, ItemID, dropnum )
                                local ret = EndAddItem(sceneId,humanObjId)
                                if ret > 0 then
                                    AddItemListToPlayer(sceneId,humanObjId)
                                else
                                    BeginQuestEvent(sceneId)
                                    AddQuestText(sceneId,"#cffcf00物品栏已满，无法得到任务物品！")
                                    EndQuestEvent(sceneId)
                                    DispatchQuestTips(sceneId,humanObjId)
                                end
                            end
                        end
                    end
                end
            end
		end
	elseif NeedKilledNum > 0 then --单纯的杀怪任务
		local HumenNum = GetMonsterOwnerCount( sceneId, objId ) --取得这个怪物死后拥有分配权的人数
		for i = 0, HumenNum-1 do
				local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --取得拥有分配权的人的objId
                if humanObjId ~= -1 then
                    if IsHaveQuestNM( sceneId, humanObjId, MissionId ) > 0 then	--如果这个人拥有任务
                                local strText = "";
                                local misIndex = GetQuestIndexByID( sceneId, humanObjId, MissionId )
                                local KilledNum = GetQuestParam( sceneId, humanObjId, misIndex, InstIndex )

                            if KilledNum < NeedKilledNum then
                                    SetQuestByIndex( sceneId, humanObjId, misIndex, InstIndex, KilledNum+1 )
                                    if KilledNum == NeedKilledNum - 1 then
                                            --if IfQuestFinishdKillObjNM( sceneId, humanObjId, MissionId, InstIndex ) then
                                                --完成了～～
                                                BeginQuestEvent(sceneId)
                                                if ObjName == "" then
                                                    if NeedKilledNum > 1 then
                                                        strText = format( "#cffcf00您击毙了怪物(%d/%d)", KilledNum+1, NeedKilledNum )
                                                    else
                                                        strText = format( "#cffcf00您击毙了怪物(%d/%d)", KilledNum+1, NeedKilledNum )
                                                    end
                                                else
                                                    if NeedKilledNum > 1 then
                                                        strText = format( "#cffcf00您击毙了%s(%d/%d)", ObjName, KilledNum+1, NeedKilledNum )
                                                    else
                                                        strText = format( "#cffcf00您击毙了%s(%d/%d)", ObjName, KilledNum+1, NeedKilledNum )
                                                    end
                                                end
                                                AddQuestText( sceneId, strText )
                                                EndQuestEvent( sceneId )
                                                DispatchQuestTips( sceneId, humanObjId )
                                            --end

                                            local MisCareNPC = QuestCareNPCNM( sceneId, humanObjId, misIndex )
                                            if MisCareNPC == 0 then --任务自动完成
                                                local ret = QuestCheckSubmitNM( sceneId, humanObjId, humanObjId, MissionId, misIndex ) -- 获取完成任务检查信息
                                                if ret > 0 then -- 如果可以完成
                                                    return x888891_MissionComplate( sceneId, humanObjId, humanObjId, -1, MissionId )
                                                end
                                            end
                                    else
                                            BeginQuestEvent(sceneId)
                                            if ObjName == "" then
                                                strText = format( "#cffcf00您击毙了怪物(%d/%d)", KilledNum+1, NeedKilledNum )
                                            else
                                                strText = format( "#cffcf00您击毙了%s(%d/%d)", ObjName, KilledNum+1, NeedKilledNum )
                                            end
                                            AddQuestText( sceneId, strText )
                                            EndQuestEvent( sceneId )
                                            DispatchQuestTips( sceneId, humanObjId )
                                    end
                            end
                    end
                end
		end
	end
	return 0
end


--任务放弃
function x888891_ProcQuestAbandon( sceneId, selfId, MissionId )
	local ret = 0
	local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
	
	--检查任务是否可以主动放弃
	if IsQuestCanAbandonNM(MissionId) <= 0 then
		local message = format(x888891_g_AbandonErrorMessage, MissionName);

        Msg2Player(sceneId, selfId, message, 0, 2)
		Msg2Player(sceneId, selfId, message, 0, 3)
		return		
	end
	
	ret = DelQuestNM( sceneId, selfId, MissionId )
	if ret == 1 then
		local message = format(x888891_g_AbandonMessage, MissionName);

        Msg2Player(sceneId, selfId, message, 0, 2)
		Msg2Player(sceneId, selfId, message, 0, 3)

--		Msg2Player(sceneId, selfId, message, 4, 2);
	else
		--ret = -1
		--扣除任务物品失败处理
	end
end

function x888891_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没有这个任务
		return
	end

	local npcName = GetName( sceneId, npcId )
	if npcName == "" then	--NPC名字会是空的么
		return
	end

	local guid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex )
	local  missionState = GetQuestStateNM(sceneId, selfId, npcId, MissionId)
	if guid ~= -1 then --这个任务有完成的NPC
		if guid == npcGuid then	--点击的NPC的名字和任务中NPC的名字相同，场景也判断过了
			AddQuestTextNM( sceneId, selfId, npcId, MissionId, missionState, -1 ) -- 显示任务信息
		end
	else
		AddQuestTextNM( sceneId, selfId, npcId, MissionId, missionState, -1 ) -- 显示任务信息
	end
end


--完成任务
--返回1代表成功，0代表交任务失败
function x888891_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	--如果该任务已经完成直接退出(跑环任务例外)
	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --任务已经完成
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没这个任务直接退出
		local MissionName = GetQuestNameNM(sceneId, selfId, MissionId);
		local strText = "#cffcf00您没有接受相关任务！"
		if MissionName == nil or MissionName == "" then
			strText = "#cffcf00您没有接受相关任务！"
		else
			strText = format("#cffcf00您没有接受%s！", MissionName);
		end
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )

		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	local ret = QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) -- 获取完成任务检查信息
	if ret > 0 then -- 如果可以完成
		return x888891_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	end
	return 0
end

--任务完成
function x888891_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
    
    if MissionId == nil or MissionId < 0 then
        return 0
    end
    
    if IsHaveQuestNM( sceneId,selfId,MissionId )<= 0 then
        return 0
    end
    
	local ret = QuestComplateNM( sceneId, selfId, targetId, MissionId,selectId ) -- 获取完成任务信息
	if ret == 1 then -- 如果成功完成
		--提示玩家任务完成
		local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
		local message = format(x888891_g_CompleteMessage, MissionName);

        Msg2Player(sceneId, selfId, message, 0, 2)
		Msg2Player(sceneId, selfId, message, 0, 3)

        --非道具奖励
        QuestBonusNotItemNM(sceneId, selfId, MissionId )
		x888891_DisplayAwardInfo(sceneId, selfId, targetId, MissionId, selectId)

        --道具奖励
        QuestBonusItemNM(sceneId, selfId, MissionId ,selectId)

		local AfterMissionType, AfterMissionScript = GetAfterQuestIdNM( sceneId, selfId, MissionId )
		if AfterMissionScript ~= -1 then
			if AfterMissionType == 0 then
				--呼叫下一个任务的界面
				x888891_ProcEventEntry( sceneId, selfId, targetId, AfterMissionScript )
			else
				--直接PUSH下一个任务
				PushAfterQuestNM( sceneId, selfId, targetId, AfterMissionScript )
			end
		end
		return 1 -- 返回成功
	else -- 如果未成功完成
		BeginQuestEvent(sceneId)
		local strText = "#cffcf00未知错误，无法完成任务"
		if ret == -2 then
			strText = "#cffcf00请选择奖励物品"
		elseif ret == -3 then
			strText = "#cffcf00背包已满,请整理后再来交任务"
		elseif ret == -4 then
			strText = "#cffcf00扣除任务物品失败"
		end
		AddQuestText(sceneId,strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end
	return 0
end

function x888891_DisplayAwardInfo(sceneId, selfId, targetId, selectId, MissionId, moneyType, money, expAward, honorType, honor, vigorType,vigor, guildRewardType,guildReward)--提示玩家金钱经验声望的奖励信息
	if MissionId >= 0 then
		moneyType, money, expAward, honorType, honor, vigorType,vigor, guildRewardType,guildReward = AwardMoneyExpHonorNM(sceneId, selfId, targetId, selectId, MissionId)
	end

	if expAward > 0 then
		Msg2Player(sceneId,selfId,format("#cffcf00获得#G%d点#cffcf00经验值的奖励。", expAward),4,2)
	end

    if money > 0 then
		if moneyType == 0 then --银
			Msg2Player(sceneId,selfId,format("#cffcf00获得#G#{_MONEY%d}#cffcf00银币的奖励。", money),4,2)
		elseif moneyType == 1 then -- 绑定银
			Msg2Player(sceneId,selfId,format("#cffcf00获得#G#{_MONEY%d}#cffcf00银卡的奖励。", money),4,2)
		elseif moneyType == 2 then --金
			Msg2Player(sceneId,selfId,format("#cffcf00获得#G#{_MONEY%d}#cffcf00金币的奖励。", money),4,2)
		elseif moneyType == 3 then -- 绑定金
			Msg2Player(sceneId,selfId,format("#cffcf00获得#G#{_MONEY%d}#cffcf00金卡的奖励。", money),4,2)
		else--表添错了
		end
	end

	if honor > 0 then
		if honorType == 0 then --朝廷声望
			Msg2Player(sceneId,selfId,format("#cffcf00获得#G%d点#cffcf00声望值的奖励。", honor),4,2)
		elseif honorType == 1 then	--江湖声望
			Msg2Player(sceneId,selfId,format("#cffcf00获得#G%d点#cffcf00声望值的奖励。", honor),4,2)
		elseif honorType == 2 then --PK
			Msg2Player(sceneId,selfId,format("#cffcf00获得#G%d点#cffcf00PK值的奖励。", honor),4,2)
		elseif honorType == 3 then --荣誉
			Msg2Player(sceneId,selfId,format("#cffcf00获得#G%d点#cffcf00荣誉值的奖励。", honor),4,2)
		elseif honorType == 4 then -- 帮贡
			Msg2Player(sceneId,selfId,format("#cffcf00获得#G%d点#cffcf00帮贡值的奖励。", honor),4,2)
		elseif honorType == 5 then -- 文采
			Msg2Player(sceneId,selfId,format("#cffcf00获得#G%d点#cffcf00文采值的奖励。", honor),4,2)
		elseif honorType == 6 then -- 威望
			Msg2Player(sceneId,selfId,format("#cffcf00获得#G%d点#cffcf00威望值的奖励。", honor),4,2)
		elseif honorType == 7 then -- 天赋值
			Msg2Player(sceneId,selfId,format("#cffcf00获得#G%d点#cffcf00天赋值的奖励。", honor),4,2)
		end
	end

    if vigorType >= 0 and vigor > 0 then
        
        if vigorType == 0 then              --活力
            Msg2Player(sceneId,selfId,format("#cffcf00获得#G%d点#cffcf00活力值的奖励。", vigor),4,2)
        elseif vigorType == 1 then          --魅力
            Msg2Player(sceneId,selfId,format("#cffcf00获得#G%d点#cffcf00魅力值的奖励。", vigor),4,2)
        elseif vigorType == 2 then          --天赋
            Msg2Player(sceneId,selfId,format("#cffcf00获得#G%d点#cffcf00天赋值的奖励。", vigor),4,2)
        end
    end

    if guildRewardType ~= nil and  guildRewardType >= 0 and guildReward > 0 then
        
        if guildRewardType == 0 then
            Msg2Player(sceneId,selfId,format("#cffcf00获得#G%d点#cffcf00帮会经验值的奖励。", guildReward),4,2)
        elseif guildRewardType == 1 then
            Msg2Player(sceneId,selfId,format("#cffcf00获得#G%d袋#cffcf00国家资源-食物的奖励。", guildReward),4,2)
        elseif guildRewardType == 2 then
            Msg2Player(sceneId,selfId,format("#cffcf00获得#G%d两#cffcf00国家资源-金钱的奖励。", guildReward),4,2)
        elseif guildRewardType == 3 then
            Msg2Player(sceneId,selfId,format("#cffcf00获得#G%d根#cffcf00国家资源-木材的奖励。", guildReward),4,2)
        elseif guildRewardType == 4 then
            Msg2Player(sceneId,selfId,format("#cffcf00获得#G%d块#cffcf00国家资源-金属的奖励。", guildReward),4,2)
        end
    end

end

--物品改变
function x888891_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId, nChangeType)

    if MissionId == nil or MissionId < 0 then
        return
    end
    
    if IsHaveQuestNM(sceneId,selfId,MissionId) <= 0 then
        return
    end    
    
	local NeedNum, ObjIndex = GetQuestNeedItemNumNM( sceneId, selfId, MissionId, itemdataId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )

	if NeedNum > 0 then
		local Num = GetItemCount( sceneId, selfId, itemdataId )
		if Num < NeedNum then --还没有完成任务

            if nChangeType == 0 then --删除物品，不提示
                BeginQuestEvent(sceneId)
                local strText = format("#cffcf00您获得了物品#G#{_ITEM%d}#cffcf00(%d/%d)", itemdataId, Num, NeedNum )
                if strText == nil then
                    strText = "";
                end
                AddQuestText( sceneId, strText )
                EndQuestEvent( sceneId )
                DispatchQuestTips( sceneId, selfId )
            end
			SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, Num )         --by zheng
		elseif Num >= NeedNum then
			
			--修正数量
			local ShowNum = Num 
			if ShowNum > NeedNum then
				ShowNum = NeedNum
			end
			
			--已经完成任务
            if nChangeType == 0 then --删除物品，不提示
                BeginQuestEvent(sceneId)
                local strText = format( "#cffcf00您获得了物品#G#{_ITEM%d}#cffcf00(%d/%d)", itemdataId, ShowNum, NeedNum )
                if strText == nil then
                    strText = "";
                end
                AddQuestText( sceneId, strText )
                EndQuestEvent( sceneId )
                DispatchQuestTips( sceneId, selfId )
            end
			SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, ShowNum )         --by zheng
			--local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			local MisCareNPC = QuestCareNPCNM( sceneId, selfId, misIndex )
			if MisCareNPC == 0 then --任务自动完成
				local ret = QuestCheckSubmitNM( sceneId, selfId, selfId, MissionId, misIndex ) -- 获取完成任务检查信息
				if ret > 0 then -- 如果可以完成
					return x888891_MissionComplate( sceneId, selfId, selfId, -1, MissionId )
				end
			end
		end
	else
        if ObjIndex >= 0 then
            SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, 0 )         --by czg
        end

    end
end

function x888891_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )

    if MissionId < 0 then
        return 0
    end

	--如果该任务已经完成直接退出
	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --任务已经完成
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没这个任务直接退出
		return 0
	end

	local MissionIdx = GetQuestEnterAreaIndexNM( sceneId, selfId, MissionId, zoneId )
	if MissionIdx == -1 then
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	if GetQuestParam( sceneId, selfId, misIndex, MissionIdx ) == 0 then
		SetQuestByIndex( sceneId, selfId, misIndex, MissionIdx, 1 )
		SendQuestEnterAreaTipsNM( sceneId, selfId, selfId, MissionId, MissionIdx )
	end

	--任务自动完成
	local MisCareNPC = QuestCareNPCNM( sceneId, selfId, misIndex )
	if MisCareNPC == 0 then --任务自动完成
		local ret = QuestCheckSubmitNM( sceneId, selfId, selfId, MissionId, misIndex ) -- 获取完成任务检查信息
		if ret > 0 then -- 如果可以完成
			return x888891_MissionComplate( sceneId, selfId, selfId, -1, MissionId )
		end
	end

	return 1
end

--离开区域
function x888891_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
	EnterAreaEventListHideNM(sceneId, selfId)
end

--区域定时器
function x888891_ProcTiming( sceneId, selfId, ScriptId, MissionId )
end


--**********************************************************************
--定点使用物品任务
function x888891_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	--如果该任务已经完成直接退出

	local ItemID = GetItemTableIndexByIndex( sceneId, selfId, BagIndex ) --得到物品ID
	local MissionId = GetQuestIDByItemIDNM( sceneId, selfId, ItemID )

	if MissionId == -1 then 	--没有找到这个任务
		return 0
	end

	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --任务已经完成
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没这个任务直接退出
		return 0
	end

	local scene, posx, posz, radii, MissionIdx, dispStr, bDispOther, otherStr, errorStr = GetQuestUseItemInfoNM( sceneId, selfId, MissionId, ItemID )
	if scene == -1 or sceneId ~= scene then --没有找到这个任务信息
		local strText = errorStr
        if errorStr == nil or errorStr == "" then
            strText = "#cffcf00无法在这里使用这个物品，请查看任务描述！"
        end
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		return 0
	end

	if posx > 0 then --需要检查地点
		local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )

		local distanceRet = radii * radii - (posx - PlayerPosX) * (posx - PlayerPosX) - (posz - PlayerPosZ) * (posz - PlayerPosZ)
		if distanceRet <= 0 then
            local strText = errorStr
            if errorStr == nil or errorStr == "" then
			    --strText = format("您应该在@sceneid_%d[%d,%d]使用此物品！", scene, posx, posz )
                strText = "#cffcf00无法在这里使用这个物品，请查看任务描述！"
            end
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText)
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			return 0
		end
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	if GetQuestParam( sceneId, selfId, misIndex, MissionIdx ) == 1 then
		return 0
	end

	--删除物品
	EraseItem(sceneId, selfId, BagIndex)

	--发送提示
	SetQuestByIndex( sceneId, selfId, misIndex, MissionIdx, 1 )
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, dispStr)
	DispatchQuestTips(sceneId,selfId) 
	EndQuestEvent(sceneId)

	--播放效果
	if impactId ~= -1 then
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, impactId, 0);
	end

	--任务自动完成
	local MisCareNPC = QuestCareNPCNM( sceneId, selfId, misIndex )
	if MisCareNPC == 0 then --任务自动完成
		local ret = QuestCheckSubmitNM( sceneId, selfId, selfId, MissionId, misIndex ) -- 获取完成任务检查信息
		if ret > 0 then -- 如果可以完成
			return x888891_MissionComplate( sceneId, selfId, selfId, -1, MissionId )
		end
	end

	return 1
end


--**********************************************************************
--采集任务
--打开ItemBox
function x888891_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )

	local MissionId, needItemCount, collNum = GetItemIdInItemBoxNM( sceneId, selfId, targetId, gpType, needItemID )
	if MissionId == -1 then
		return 1 --没有这个任务
	end

	--如果该任务已经完成直接退出
	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --任务已经完成
		return 1
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没这个任务直接退出
		local MissionName = GetQuestNameNM(sceneId, selfId, MissionId)
		local str = "#cffcf00您没有接受相关任务！"
		if MissionName == nil or MissionName == "" then
			str = "#cffcf00您没有接受相关任务！"
		else
			str = format("#cffcf00您没有接受%s！", MissionName);
		end
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,str)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 1
	end

	local itemCountNow = GetItemCount( sceneId, selfId, needItemID )
	if itemCountNow >= needItemCount then
		local str = "#cffcf00物品已经收集齐全！"
		if needItemCount > 0 then	
			str = "#cffcf00物品已经收集齐全！";
		else
			str = "#cffcf00您不需要这个物品！";
		end
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,str)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 1
	end

	return 0
end

--回收
function x888891_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	local MissionId, needItemCount, collNum = GetItemIdInItemBoxNM( sceneId, selfId, targetId, gpType, needItemID )
	if MissionId == -1 then
		return 1 --没有这个任务
	end

	--如果该任务已经完成直接退出
	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --任务已经完成
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没这个任务直接退出
		return 0
	end

	local itemCountNow = GetItemCount( sceneId, selfId, needItemID )
	if itemCountNow >= needItemCount then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#cffcf00物品已经收集齐全")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end

	--决定一次采集多少
	local itemAdd = needItemCount - itemCountNow
	if collNum == -1 then
		itemAdd = 1
	else
		if itemAdd > collNum then
			itemAdd = collNum
		end
	end
	if itemAdd > 1 then
		itemAdd = random(itemAdd)
		if itemAdd == 0 then
			itemAdd = 1
		end
	end

	BeginAddItem( sceneId )
	AddItem( sceneId, needItemID, itemAdd )
	local ret = EndAddItem( sceneId, selfId )
	if ret > 0 then
		AddItemListToPlayer(sceneId,selfId)
		return 1
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#cffcf00无法得到采集物品，请整理道具栏！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end
end

--打开
function x888891_OnProcOver( sceneId, selfId, targetId )
end

--打开后检查
function x888891_OpenCheck( sceneId, selfId, targetId )
end


--**********************************************************************

--请求创建BUS
function x888891_CreateBus( sceneId, selfId, targetId, MissionId )
	--取得玩家所在位置
	local PosX,PosZ = GetWorldPos(sceneId, selfId)
	
	--初始化一些测试数据,以后脚本接口有了后,删除该行,并将后面的行打开
	--local	CarType, BaseAI, AIScript, EventScript, Impact,ShapeType, Name, Title = 1 , 3 , -1, MISSION_SCRIPT, 1210, -1, "无敌运镖车", "威武镖局"
	--local	WaitTime,  LifeTime = 5, 120
	--local	PatrolID = 0
	
	--通过脚本接口【 GetQuestBusInfoNM(sceneId, selfId, misIndex)】取到护送的BUS的一些信息
	--      BUS类型、基础AI、扩展AI、  绑定事件脚本、上车BUFF			
	local  CarType, BaseAI, AIScript, EventScript, Impact, Name, Title, WaitTime,  LifeTime, PatrolID = GetQuestBusInfoNM(sceneId, selfId, MissionId)
	
	--正式创建BUS
	local ObjID = CreateBus(sceneId, CarType, PosX, PosZ, BaseAI, AIScript, EventScript, selfId, Impact, MissionId,targetId)
end

--**********************************************************************
--bus创建成功
function x888891_OnCreateBusOK(sceneId, selfId, busId,targetId,MissionId)

	--修改BUS的外形,还没制作BUS的变身BUFF,暂时不开放
	--SendSpecificImpactToUnit(sceneId, selfId, selfId, ObjID, nImpactDataIndex, nDelayTime)

	--修改BUS的title
	local  CarType, BaseAI, AIScript, EventScript, Impact, Name, Title, WaitTime,  LifeTime, PatrolID = GetQuestBusInfoNM(sceneId, selfId, MissionId)	
	local BusTitle = GetName( sceneId, selfId ).."的"..Title
	SetBusTitle(sceneId , busId, BusTitle)
	
	--修改BUS的名字,目前该接口还没有
	--SetBusName(sceneId , busId, Name)
	
	--设置BUS的空车时间/生命时间
	SetBusTimerTick(sceneId , busId, 1000)
	SetBusTimerOpen(sceneId, busId, 1)
	if WaitTime>0 then
		SetBusWaitTime(sceneId , busId, WaitTime)
	end
	if LifeTime>0 then
		SetBusLifeTime(sceneId , busId, LifeTime)
	end
	
	--取得BUS的类型,0--镖车，1--BUS，2--变身为BUS的镖车,2不使用
	local BusType  = GetBusType(sceneId, busId)
	local MessageStr = ""
	if BusType == 0 then
		MessageStr = "你开始运镖了"
	elseif BusType == 1 then
		--护送的话,开启自动巡逻路径
		if PatrolID == -1 then
			BeginQuestEvent(sceneId)
			  AddQuestText(sceneId,"数据填写补全,护送没有绑巡逻路径");
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)	
			return
		end
		SetBusPatrolId(sceneId , busId, PatrolID)
		MessageStr = "你开始护送了,不要离开BUS超过5米"
	else
		MessageStr = "-_!!数据填写有误,检查下"	
	end
		
	BeginQuestEvent(sceneId)
	  AddQuestText(sceneId,MessageStr);
	EndQuestEvent()
	DispatchQuestTips(sceneId,selfId)	
end




function x888891_DeleteBus(sceneId, ObjId)		
	DeleteBus(sceneId, ObjId,1)
end


--玩家请求进入BUS
--selfId：玩家ID
--targetId：BUSID
function x888891_OnIntoBusEvent(sceneId, selfId,targetId)
	local InBus = IsBusMember(sceneId, selfId)
	if InBus == 1 then
		BeginQuestEvent(sceneId)
		  	AddQuestText(sceneId,"你已经在车里了");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		return 
	end
			
	local BusSize = GetBusSize(sceneId,targetId) 
	local MemberNum = GetBusMemberCount(sceneId,targetId)
	
	if BusSize<=MemberNum  then
		BeginQuestEvent(sceneId)
		  	AddQuestText(sceneId,"这辆车已经人满了");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		return
	end
	

	local IsOwner = IsTheBusOwner(sceneId, selfId, targetId )	
	if IsOwner == 1 then
		--进入BUS
		AddBusMember(sceneId, selfId,targetId)
	end
end

--玩家离开BUS
--selfId：玩家ID
function x888891_OnLeaveBusEvent(sceneId, selfId,BusId)
	local BusType  = GetBusType(sceneId, BusId)
	if BusType == 0 then	
		BeginQuestEvent(sceneId)
		  AddQuestText(sceneId,"你正在运镖，无法离开");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
	elseif  BusType == 1 then	
		DelBusMember(sceneId, selfId,BusId)
	end
end


function x888891_OnTime(sceneId, BusId, MissionId)
    
    --检查ID是否有效
    if( IsObjValid(sceneId,BusId) ~= 1 )then
        return
    end
    
	local BusPosX, BusPosZ = GetWorldPos(sceneId, BusId)
	--测试数据
	local EndSceneID = -1
	local EndPosX = 0
	local EndPosZ = 0
	
	--取得任务要送到的地方的自动寻路索引(Mission_List.tab里面的),通过这个索引查到终点的坐标,
	local roadId = GetQuestXunLuIndexNM( MissionId )
	if roadId > 0 then
		EndSceneID,EndPosX,EndPosZ = GetQuestEndPosNM( roadId )
	else
        --此处没人认领，目前陈治国修改，有问题请找陈治国 2009-02-10
		--BeginQuestEvent(sceneId)
		--  AddQuestText(sceneId,"终点坐标没有填写正确,请检查");
		--EndQuestEvent()
		--DispatchQuestTips(sceneId,selfId)
		return
	end

	if sceneId == EndSceneID then
		local distance = floor((BusPosX-EndPosX)*(BusPosX-EndPosX)+(BusPosZ-EndPosZ)*(BusPosZ-EndPosZ))
		if distance<100 then
			
			--这里做任务完成处理,还有后续处理需要 唐鹏 添加
			local  PlayerId = GetBusMemberObjId(sceneId,BusId,0)
			BeginQuestEvent(sceneId)
			  AddQuestText(sceneId,"任务完成");
			EndQuestEvent()
			DispatchQuestTips(sceneId,PlayerId)
			x888891_DeleteBus(sceneId, BusId)	
			
			local misIndex = GetQuestIndexByID( sceneId, PlayerId, MissionId )	--得到玩家身上的任务索引
			local MissionIdx = GetQuestHuSongIndexNM( sceneId, PlayerId, MissionId )	--得到护送任务在Mission_List表中的索引 0-4
			if MissionIdx > 0 and misIndex > 0 then
				if GetQuestParam( sceneId, PlayerId, misIndex, MissionIdx ) == 0 then
					SetQuestByIndex( sceneId, PlayerId, misIndex, MissionIdx, 1 )	--设置护送任务完成
				end
			end
		end
	end
end

function x888891_OnLifeTimeOut(sceneId, BusId, MissionId)
	
	--这里做任务失败处理,还有后续处理需要 唐鹏 添加
	
	local  PlayerId = GetBusMemberObjId(sceneId,BusId,0)
	BeginQuestEvent(sceneId)
	  AddQuestText(sceneId,"任务失败");
	EndQuestEvent()
	DispatchQuestTips(sceneId,PlayerId)
	x888891_DeleteBus(sceneId, BusId)
	
	local MissionName = GetQuestNameNM( sceneId, PlayerId, MissionId )
	local ret = DelQuestNM( sceneId, PlayerId, MissionId )
	if ret == 1 then
		Msg2Player( sceneId, PlayerId, "#R护送任务["..MissionName.."]失败！", MSG2PLAYER_PARA )
	end
end

function x888891_OnWaitTimeOut(sceneId, BusId, MissionId)
	
	--这里做任务失败处理,还有后续处理需要 唐鹏 添加
	local  PlayerId = GetBusMemberObjId(sceneId,BusId,0)
	BeginQuestEvent(sceneId)
	  AddQuestText(sceneId,"任务失败");
	EndQuestEvent()
	DispatchQuestTips(sceneId,PlayerId)
	x888891_DeleteBus(sceneId, BusId)

	local MissionName = GetQuestNameNM( sceneId, PlayerId, MissionId )
	local ret = DelQuestNM( sceneId, PlayerId, MissionId )
	if ret == 1 then
		Msg2Player( sceneId, PlayerId, "#R护送任务["..MissionName.."]失败！", MSG2PLAYER_PARA )
	end
end

function x888891_OnBusStopWhenOwnerFarAway(sceneId, ownerId)
end

function x888891_OnDie( sceneId, killerId , BusId, MissionId)
	--这里做任务失败处理,还有后续处理需要 唐鹏 添加
	local  PlayerId = GetBusMemberObjId(sceneId,BusId,0)
	BeginQuestEvent(sceneId)
	  AddQuestText(sceneId,"任务失败");
	EndQuestEvent()
	DispatchQuestTips(sceneId,PlayerId)

	local MissionName = GetQuestNameNM( sceneId, PlayerId, MissionId )
	local ret = DelQuestNM( sceneId, PlayerId, MissionId )
	if ret == 1 then
		Msg2Player( sceneId, PlayerId, "#R护送任务["..MissionName.."]失败！", MSG2PLAYER_PARA )
	end
end

function x888891_OnSelectSubmitItem( sceneId, selfId , bagIndex,nGuid_Serial, nGuid_Server, nGuid_World)
	
	for i,item in x888891_g_BlueItemMissionList do
		if IsHaveQuestNM( sceneId, selfId, item.misId )>0 then
			CallScriptFunction(item.scriptId,"OnSelectSubmitItem", sceneId,selfId,bagIndex,nGuid_Serial, nGuid_Server, nGuid_World)
		end
	end
	return 1
end