--寻找红绳任务脚本
x300617_g_ScritpId = 300617
x300617_g_MissionId = 7019
x300617_g_NeedLevel = 40
x300617_g_NeedGold = 10000
x300617_g_KillMissionId =  7012
x300617_g_Material_Thread = 13011010 
x300617_g_Material_Color =  13011011

x300617_g_AwardItemId = 13011012 --奖励物品id


function x300617_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	if GetLevel(sceneId, selfId) < 40 then
		return
	end

	local haveAccept = IsHaveQuestNM( sceneId, selfId, MissionId ) 
	if  haveAccept== 0 then	-- 如果没有这个任务
		 AddQuestTextNM( sceneId, selfId, targetId, MissionId, 8, -1 ) -- 显示任务信息
	end
end


function x300617_ProcEventEntry( sceneId, selfId, targetId, MissionId )
    if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没有这个任务    

		AddDispatchQuestInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示接受任务信息
	  
    else--检查是不是可以提交    
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		if QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) > 0 then -- 如果任务可以完成
			QuestComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示完成信息
		else
			QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示任务未完成信息
		end
    end
end


function x300617_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
    if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没有这个任务
		local ItemNumOnPlayer = GetItemCount( sceneId, selfId, x300617_g_AwardItemId )
		if ItemNumOnPlayer > 0 then
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, " 很抱歉，您身上有红绳了，不能再接任务了！");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"很抱歉，您身上有红绳了，不能再接任务了！",8,2)
			return
		end

		if GetSex(sceneId, selfId) ~= 1 then
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "请让你心仪的男士来接取此任务！");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"请让你心仪的男士来接取此任务！",8,2)
			return
		end

        if  IsMarried(sceneId, selfId) == 0  then --是否已婚
            if GetLevel(sceneId, selfId) >= x300617_g_NeedLevel then			
				local money = GetMoney( sceneId, selfId, 0 )				
				if money >= x300617_g_NeedGold then
                    x300617_Accept( sceneId, selfId, MissionId )
				else-- 金钱不够
					BeginQuestEvent(sceneId);
					AddQuestText(sceneId, "很抱歉，您包裹中的现银不足10两，无法领取任务！");
					EndQuestEvent(sceneId);
					DispatchQuestTips(sceneId,selfId);
					Msg2Player(sceneId,selfId,"很抱歉，您包裹中的现银不足10两，无法领取任务！",8,2)
				end
            else
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "很抱歉，您的等级不到40级，无法接取此任务！");
				EndQuestEvent(sceneId);
				DispatchQuestTips(sceneId,selfId);Msg2Player(sceneId,selfId,"很抱歉，您的等级不到40级，无法接取此任务！",8,2)
				--AddDispatchQuestInfoNM( sceneId, selfId, targetId, MissionId ) -- 显示接受任务信息
            end
        else--已经结婚           
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "您已经结婚了,无法接取任务！");
				EndQuestEvent(sceneId);
				DispatchQuestTips(sceneId,selfId);
				Msg2Player(sceneId,selfId,"很抱歉，您已是已婚人物，无法接取此任务！",8,2)
        end
    end
end


function x300617_Accept( sceneId, selfId, MissionId )

	--检查前置任务
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, MissionId )
	if FrontMissiontId1 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
			return -1
		end
	end
	if FrontMissiontId2 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
			return -1
		end
	end
	if FrontMissiontId3 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
			return -1
		end
	end

	local	ret = AddQuestNM( sceneId, selfId, MissionId ) -- 给玩家添加任务
	local strText = GetQuestNameNM( sceneId, selfId, MissionId )
	
	strText = "您接受了任务：" .. strText
	if ret == 0 then
		strText = "添加任务失败"
	elseif ret == -1 then
		strText = "背包已满,请整理后再来接任务"
	elseif ret == -2 then
		strText = "任务已达到上限，无法接新的任务"
	elseif ret == -3 then
		strText = "很抱歉，您包裹中的金钱不够，无法领取任务"
	else
		strText = "您接受了任务：【婚姻】寻找红绳。"
	end

	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, strText);
	EndQuestEvent(sceneId);
	DispatchQuestTips(sceneId,selfId);
	Msg2Player(sceneId,selfId,strText,4,2)

	return -1
end


--杀死怪物
function x300617_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
--场景ID, 自己的ID, 怪物表位置号, 怪物objId, 任务ID

	local ItemCount=0;
	local ItemID=0;
	local ItemRand=0;
	local ItemDropNum=0;
	--场景ID, 自己的ID, 怪物表位置号, 怪物objId, 任务ID
	local NeedKilledNum, InstIndex, ObjName = GetQuestNeedKillObjInfoNM( sceneId, selfId, MissionId, objdataId, objId )
		if NeedKilledNum >= 0 then
			local KilledNum = GetMonsterOwnerCount( sceneId, objId ) --取得这个怪物死后拥有分配权的人数
			for i = 0, KilledNum-1 do
				local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --取得拥有分配权的人的objId
				if humanObjId ~= -1 then
					if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
						if GetHp(sceneId, humanObjId) > 0 then
							if IsHaveQuestNM( sceneId, humanObjId, MissionId ) > 0 then	--如果这个人拥有任务
								if InstIndex >= 0 then
									
									ItemCount, ItemID, ItemRand, ItemDropNum = GetQuestItemNM( sceneId, humanObjId, MissionId, InstIndex )
							
											--要收集的个数，物品ID，掉落率，一次最大掉落
									if HaveItem( sceneId, humanObjId, ItemID ) ~= 1 then --如果没有这个物品 
										BeginAddItem(sceneId)
										AddItem( sceneId, ItemID, ItemDropNum )
										local ret = EndAddItem(sceneId,humanObjId)
										if ret > 0 then
											--AddItemListToPlayer(sceneId,selfId)
											AddItemListToPlayer(sceneId,humanObjId)
										else
											BeginQuestEvent(sceneId)
											AddQuestText(sceneId,"物品栏已满，无法得到任务物品！")
											EndQuestEvent(sceneId)
											DispatchQuestTips(sceneId,humanObjId)
										end
											--end
									  end
										
									
								end
							end

						end--end
					end
				end
			end
		end


end



--物品改变
function x300617_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )--寻找材料的任务完成后再添加合成任务
	
	
	if MissionId == nil or MissionId < 0 then
        return
    end
    
	if IsHaveQuestNM( sceneId, selfId, MissionId ) <= 0 then
		return
	end

	if IsPlayerStateNormal(sceneId, selfId) == 0 then
		return 
	end

	if GetHp(sceneId, selfId) <= 0 then
		return
	end

	local NeedNum, ObjIndex = GetQuestNeedItemNumNM( sceneId, selfId, MissionId, itemdataId )
	--
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )

	if NeedNum > 0 then
		local Num = GetItemCount( sceneId, selfId, itemdataId )
		if Num < NeedNum then --还没有完成任务
			BeginQuestEvent(sceneId)
			local strText = format("已得到了@itemid_%d: %d/%d", itemdataId, Num, NeedNum )
			if strText == nil then
				strText = "";
			end
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
   			SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, Num )         --by zheng
		elseif Num == NeedNum then
			--已经完成任务
			BeginQuestEvent(sceneId)
			local strText = format( "已得到了@itemid_%d: %d/%d", itemdataId, Num, NeedNum )
			if strText == nil then
				strText = "";
			end
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, Num )         --by zheng
			--local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			--if QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) > 0 then
				--local MisCareNPC = QuestCareNPCNM( sceneId, selfId, misIndex )
				--if MisCareNPC == 0 then --任务自动完成
				    --if  IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then
	                    --x300617_MissionComplate( sceneId, selfId, MissionId )
					--end

				--end
			--end
		end
	end
	return 0
end


function x300617_MissionComplate( sceneId, selfId, MissionId )
	local ret = DelQuest( sceneId, selfId, MissionId )

	if ret > 0 then
		local strText = GetQuestNameNM( sceneId, selfId, MissionId )
		strText = "您完成了任务：" .. strText
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, strText);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId);
		Msg2Player( sceneId, selfId, strText, 4,2 )
	end
end



function x300617_ProcQuestAbandon( sceneId, selfId, MissionId )
	local ret = 0
	local MissionName = GetQuestNameNM( sceneId, selfId, MissionId )
	ret = DelQuest( sceneId, selfId, MissionId )
	if ret == 1 then
	--删掉原材料 
		   if HaveItem(sceneId, selfId, x300617_g_Material_Thread) > 0 then
		   		DelItem(sceneId, selfId, x300617_g_Material_Thread, 1);	
		   end
		   
		   if HaveItem(sceneId, selfId, x300617_g_Material_Color) > 0 then
		   		DelItem(sceneId, selfId, x300617_g_Material_Color, 1);	
		   end

		local strText = GetQuestNameNM( sceneId, selfId, MissionId )
		strText = "您放弃了任务：" .. strText
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, strText);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId);
		Msg2Player( sceneId, selfId, strText, 4,2 )
	else
		--ret = -1
		--扣除任务物品失败处理
	end
end

function x300617_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then	-- 如果没这个任务直接退出
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "请去找我的助理杜成双去制作红绳吧！");
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId);
		Msg2Player( sceneId, selfId, "请去找我的助理杜成双去制作红绳吧！", 4,2 )
	end
end

function x300617_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
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
