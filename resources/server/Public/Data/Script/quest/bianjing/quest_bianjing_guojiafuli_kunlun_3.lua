--国家福利
--MisDescBegin
--任务ID
x260012_g_MissionId = 3144
--脚本号
x260012_g_ScriptId = 260012

--上一个任务的ID
--g_MissionIdPre =

--任务文本描述


x260012_g_MissionName="【国家】为国效力<三>"

x260012_g_ReplyNpcId = 131502
x260012_g_LevelLess	= 50
x260012_g_NeedLevel = 50
x260012_g_NeedExploit = 14
x260012_g_BonusItem	=	{{item=11990110,n=3}}
x260012_g_MissionTarget ="   获得14点功勋"
x260012_g_MissionMethod = "功勋大于14"              --任务攻略
x260012_g_MissionText = "\t#G14点#W功勋值！对你应该不算很大的挑战。\n\t每天在发布出国令期间成功#G完成出国各项任务#W，会获得一定的功勋值。\n\t当你攒够#G14点#W功勋值的时候，再来找我吧。"					--任务描述
x260012_g_MissionCompleted = "\t你的功勋值不足！只有每天在发布出国令期间#G成功完成出国任务#W，才会获得功勋值。"
x260012_g_MissionEnd = "\t看来你获取功勋的速度是越来越快了！ \n\t在我看来，出国任务最重要的是#G团结一致#W和#G纪律严明#W。"
x260012_g_MissionHelp = "\t只有每天在发布#G出国令期间#W成功完成出国任务，才会获得功勋值。"					--任务小提示

function x260012_ShowTips(sceneId, selfId, tip)
	BeginQuestEvent(sceneId)
    AddQuestText(sceneId, tip)
    EndQuestEvent()
    DispatchQuestTips(sceneId, selfId)
end
--MisDescEnd

--**********************************
--任务入口函数
--**********************************
function x260012_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
		local MissionName = x260012_g_MissionName
	if MissionId ~= x260012_g_MissionId then
		if IsQuestHaveDone(sceneId, selfId, MissionId) > 0 then
			return 
		end
	else
		if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then
			return 
		end
	
	end	
		if GetQuestData(sceneId, selfId, MD_COUNTRY_FULI_3[1], MD_COUNTRY_FULI_3[2],MD_COUNTRY_FULI_3[3] ) == 1 then
			return
		end
		
		if GetLevel(sceneId, selfId) >= x260012_g_NeedLevel then
			local state = GetQuestStateNM(sceneId, selfId, targetId, x260012_g_MissionId);
			AddQuestNumText(sceneId, x260012_g_MissionId, MissionName,state,5);

		end
end

function x260012_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本
	if IsHaveQuestNM( sceneId, selfId, x260012_g_MissionId ) > 0 then	-- 如果有这个任务
			local bDone = x260012_CheckSubmit(sceneId, selfId,targetId, x260012_g_MissionId);
	        if (bDone > 0) then
				x260012_DispatchCompletedInfo( sceneId, selfId, targetId,x260012_g_MissionId) --完成任务显示
			else
			x260012_DispatchContinueInfo( sceneId, selfId, targetId,x260012_g_MissionId ) --未完成任务显示
			end
	else
			x260012_DispatchMissionInfo( sceneId, selfId, targetId,x260012_g_MissionId )		--任务信息显示
	end
end

--**********************************
--列举事件
--**********************************

--**********************************
--检测接受条件
--**********************************
function x260012_ProcAcceptCheck( sceneId, selfId, NPCId )
	local MissionId = x260012_g_MissionId
	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then
		x260012_ShowTips(sceneId, selfId, "您已经接取了该任务，请先完成当前任务")
		return 0;
	end 
	return 1
end

function x260012_ProcQuestAccept( sceneId, selfId, NPCId, MissionId)
    --local MissionId = x260012_g_MissionId
    local ScriptId = x260012_g_ScriptId
    local MissionName = x260012_g_MissionName
    
    if IsQuestHaveDone(sceneId, selfId, MissionId) > 0 then
		return 
    end
    if IsQuestFullNM(sceneId,selfId)==1 then
        x260012_ShowTips(sceneId, selfId, "可接任务数量已满")
        return 
    end
		
    if x260012_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
        local retmiss = AddQuest( sceneId, selfId, MissionId, ScriptId, 0, 0, 0,1)
    
        if retmiss  > 0 then
			Msg2Player(sceneId,selfId,"您接受了任务："..MissionName,8,2)
			if GetExploit(sceneId, selfId) >= x260012_g_NeedExploit then
					local misIndex = GetQuestIndexByID(sceneId,selfId,MissionId)                                                  
		            SetQuestByIndex(sceneId,selfId,misIndex,0,1)
		            SetQuestByIndex(sceneId,selfId,misIndex,7,1)
		           
			end
        else
			Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
		end
    end
end

--**********************************
--接受
--**********************************
function x260012_ProcAccept( sceneId, selfId )
	return 1
end

--**********************************
--放弃
--**********************************
function x260012_ProcQuestAbandon( sceneId, selfId, MissionId )
	local MissionId = x260012_g_MissionId
    local MissionName = x260012_g_MissionName
    
	if IsHaveQuest(sceneId,selfId, MissionId) <= 0 then
		return 
	end
	DelQuest(sceneId, selfId, MissionId)
	Msg2Player(sceneId,selfId,"您放弃了任务："..MissionName.."！",8,2)
end

--**********************************
--继续
--**********************************
function x260012_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--检测是否可以提交
--**********************************
function x260012_CheckSubmit( sceneId, selfId, targetId,MissionId) 
	local misIndex = GetQuestIndexByID(sceneId, selfId, x260012_g_MissionId)
	local state = GetQuestStateNM(sceneId, selfId, targetId, x260012_g_MissionId)
	AddQuestNumText( sceneId, x260012_g_MissionId,x260012_g_MissionName, 7,state ) 
	return GetQuestParam(sceneId, selfId, misIndex, 7);
end

--**********************************
--提交
--**********************************
function x260012_DispatchCompletedInfo( sceneId, selfId, targetId,MissionId )

	
	BeginQuestEvent(sceneId)

		--任务完成信息
		AddQuestText(sceneId,"#Y"..x260012_g_MissionName)
		AddQuestText(sceneId,x260012_g_MissionEnd)
		AddQuestText(sceneId," ")
		
		AddQuestText( sceneId,"#Y完成情况：")
		AddQuestText(sceneId, "已完成");

		--1、经验
		for i, item in x260012_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	 	end
		--2 帮供
		-- if x260012_g_BonusMoney8>0 then
			-- AddQuestMoneyBonus8(sceneId,x260012_g_BonusMoney8)
		-- end
		--3 帮会经验
		-- if x260012_g_GuildExpBonus>0 then
			-- AddQuestGuildExpBonus(sceneId,x260012_g_GuildExpBonus)
		-- end
	EndQuestEvent(sceneId)
	DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x260012_g_ScriptId, MissionId);

end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x260012_DispatchContinueInfo( sceneId, selfId, targetId,MissionId )
	BeginQuestEvent(sceneId)
		--任务继续信息
		AddQuestText(sceneId,"#Y"..x260012_g_MissionName)
		AddQuestText(sceneId,format("%s", x260012_g_MissionCompleted))
		AddQuestText(sceneId," ")

		--任务目标
		AddQuestText( sceneId,"#Y完成情况：")
		AddQuestText(sceneId, "未完成#r");
		AddQuestText(sceneId, "需要功勋值：14点");

		-- for i, item in x260012_g_BonusItem do
		   	-- AddQuestItemBonus(sceneId, item.item, item.n)
	 	-- end

	--任务提示信息
	EndQuestEvent(sceneId)
	DispatchQuestDemandInfo(sceneId, selfId, targetId, x260012_g_ScriptId, MissionId,0);

end


---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x260012_DispatchMissionInfo( sceneId, selfId, NPCId,MissionId )

	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId,"#Y"..x260012_g_MissionName)
		AddQuestText(sceneId,format("%s", x260012_g_MissionText))
		AddQuestText(sceneId," ")

		--任务目标
		--AddQuestText( sceneId,x260012_g_MissionText)
		--AddQuestText( sceneId,format("%s", x260012_g_MissionTarget))
		--AddQuestText( sceneId," ")

		--提示信息
		if x260012_g_MissionHelp ~= "" then

			--AddQuestText(sceneId,x260012_g_MissionTarget)
			AddQuestText(sceneId,format("%s", x260012_g_MissionHelp))
			AddQuestText(sceneId," ")
		end

		--1、经验
		for i, item in x260012_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	 	end
		--2 帮供
		-- if x260012_g_BonusMoney8>0 then
			-- AddQuestMoneyBonus8(sceneId,x260012_g_BonusMoney8)
		-- end
		--3 帮会经验
		-- if x260012_g_GuildExpBonus>0 then
			-- AddQuestGuildExpBonus(sceneId,x260012_g_GuildExpBonus)
		-- end
	EndQuestEvent(sceneId)
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x260012_g_ScriptId, MissionId);
end

function x260012_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- 如果没这个任务直接退出
		return 0
	end
    local MissionName = x260012_g_MissionName

    if GetExploit(sceneId, selfId) < x260012_g_NeedExploit then
        --x260012_ShowTips(sceneId,selfId,"你的功勋不够，需要"..x260012_g_NeedExploit)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "你的功勋不够，需要"..x260012_g_NeedExploit.."点才能领取奖励！ ");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
	  	Msg2Player(sceneId,selfId,"你的功勋不够，需要"..x260012_g_NeedExploit.."点才能领取奖励！ ",8,2)
    else
		BeginAddItem(sceneId)                                                    
        for i, item in x260012_g_BonusItem do
            AddBindItem( sceneId, item.item, item.n )
        end
        
        if EndAddItem(sceneId,selfId) > 0 then
			if DelQuest(sceneId, selfId, MissionId) > 0 then
				AddItemListToPlayer(sceneId,selfId) 
				QuestCom(sceneId, selfId, x260012_g_MissionId)
				Msg2Player(sceneId,selfId,"您完成了任务："..MissionName.."！",8,2)
				SetQuestData(sceneId, selfId, MD_COUNTRY_FULI_3[1], MD_COUNTRY_FULI_3[2],MD_COUNTRY_FULI_3[3], 1 ) 
			end
			if DelQuestNM( sceneId, selfId, MissionId) < 1 then
				return 
			end
        else
            BeginQuestEvent(sceneId)
            local strText = "背包空间不足，无法获得物品。"
            AddQuestText(sceneId,strText);
            EndQuestEvent(sceneId)
            DispatchQuestTips(sceneId,selfId)
        end
   end
end

-----------------------------------
function x260012_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	if IsHaveQuestNM( sceneId, selfId, x260012_g_MissionId) == 0 then	-- 如果没有这个任务
		return
	end
	local state = GetQuestStateNM(sceneId, selfId, npcId, x260012_g_MissionId);
	if npcGuid == x260012_g_ReplyNpcId then
		if GetExploit(sceneId, selfId) < x260012_g_NeedExploit then
			AddQuestNumText(sceneId, x260012_g_MissionId, x260012_g_MissionName,6,state);
			else
			 AddQuestNumText(sceneId, x260012_g_MissionId, x260012_g_MissionName,7,state);
		end
	end
end
--**********************************
--杀死怪物或玩家
--**********************************
function x260012_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

--**********************************
--进入区域事件
--**********************************
function x260012_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x260012_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x260012_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	--local myMissionId = x300797_GetMissionId( sceneId, selfId )
	local ScriptId = x260012_g_ScriptId
	local MissionName = x260012_g_MissionName
	local target =  x260012_g_MissionTarget

	if IsHaveQuestNM( sceneId, selfId, MissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	BeginQuestEvent(sceneId)	
			
		
	AddQuestLogCustomText( sceneId,
							"",						-- 标题
							MissionName,        -- 任务名字
							target,		--任务目标
							"@npc_"..x260012_g_ReplyNpcId,			--任务NPC
							x260012_g_MissionMethod,             --任务攻略
							x260012_g_MissionText,					--任务描述
							x260012_g_MissionHelp					--任务小提示
							)
	
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	

end

function x260012_OnExploitChanged(sceneId,selfId, exploit)
	local MissionId = x260012_g_MissionId
    
    
	if IsQuestHaveDone(sceneId, selfId, MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, MissionId) <= 0 then
		return
	end
	if GetQuestData(sceneId, selfId, MD_COUNTRY_FULI_3[1], MD_COUNTRY_FULI_3[2],MD_COUNTRY_FULI_3[3] ) == 1 then
		return
	end
	if GetExploit(sceneId, selfId) >= x260012_g_NeedExploit then
			local misIndex = GetQuestIndexByID(sceneId,selfId,MissionId)                                                  
            SetQuestByIndex(sceneId,selfId,misIndex,0,1)
            SetQuestByIndex(sceneId,selfId,misIndex,7,1)
    else
			local misIndex = GetQuestIndexByID(sceneId,selfId,MissionId)                                                  
            SetQuestByIndex(sceneId,selfId,misIndex,0,0)
            SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	end
end

