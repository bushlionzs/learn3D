--询问状况

--MisDescBegin
x256207_g_ScriptId = 256207
x256207_g_MissionId = 1482
x256207_g_LevelLess	= 	40 
x256207_g_MissionIdNext = -1
x256207_g_Name	={}
x256207_g_ExtTarget={{type=20,n=50,target="获得50条@item_13015012"}}
x256207_g_MissionName="【队伍】美味佳肴"
x256207_g_MissionInfo="\t吃过鲨鱼肉么？现在已经风靡全城，你何不趁机也捞上一笔？进入@npcsp_和氏璧_138513，帮我带来50条@item_13015012#W吧！\n\t此外，参加#G益者三友#W或者#G天坛灯谜会#W都有可能获得@item_13015012#W。"  --任务描述
x256207_g_MissionTarget="获得50条@item_13015012#W"		
x256207_g_MissionCompleted="\t呵呵，相信这美味佳肴会继续流行下去吧。"					--完成任务npc说话的话
x256207_g_ContinueInfo="\t你还没有完成任务吗？赶快去帮我带来50条@item_13015012#W吧！"
x256207_g_MissionHelp =	""
x256207_g_DemandItem ={}
x256207_g_BonusMoney1 =0
x256207_g_BonusMoney2 =0
x256207_g_BonusMoney3 =0
x256207_g_BonusMoney4 =0
x256207_g_BonusMoney5 =0
x256207_g_BonusMoney6 =0
x256207_g_BonusItem	=	{}
x256207_g_BonusChoiceItem ={{item=12050228,n=1},{item=12050229,n=1},{item=12050230,n=1}}
x256207_g_ExpBonus = 200000

x256207_g_ReplyNpc = 140417

x256207_g_ItemId  = 13015012
x256207_g_NeedItemCount	= 50
x256207_g_MonsterName	=	"幼鲨"


--MisDescEnd
--**********************************

function x256207_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

	local nLevel = GetLevel(sceneId, selfId)
	
	if nLevel<x256207_g_LevelLess then
		return
	end
	if IsQuestHaveDone(sceneId, selfId, x256207_g_MissionId) > 0 then
		return 
	end
	
	if IsHaveQuest(sceneId,selfId, x256207_g_MissionId) <= 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x256207_g_MissionId)

			AddQuestTextNM( sceneId, selfId, NPCId, x256207_g_MissionId, state, -1 )
	end
end

function x256207_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x256207_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256207_g_ExpBonus )
		end
		if x256207_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256207_g_BonusMoney1 )
		end
		if x256207_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256207_g_BonusMoney2 )
		end
		if x256207_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256207_g_BonusMoney3 )
		end
		if x256207_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256207_g_BonusMoney4 )
		end
		if x256207_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256207_g_BonusMoney5 )
		end
		if x256207_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256207_g_BonusMoney6 )
		end
		for i, item in x256207_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x256207_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x256207_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x256207_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256207_g_MissionId) > 0 then
		if x256207_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"#Y"..x256207_g_MissionName)
					AddQuestText(sceneId,x256207_g_ContinueInfo)
					EndQuestEvent()
					DispatchQuestEventList(sceneId, selfId, NPCId, x256207_g_ScriptId, x256207_g_MissionId);
		else
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"#Y"..x256207_g_MissionName)
					AddQuestText(sceneId,x256207_g_MissionCompleted)
					AddQuestText(sceneId," ")
					x256207_DispatchMissionInfo( sceneId, selfId, NPCId )
					EndQuestEvent()
					DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256207_g_ScriptId, x256207_g_MissionId);
		end
  elseif x256207_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
		BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x256207_g_MissionName)
			AddQuestText(sceneId,x256207_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")

			AddQuestText( sceneId,x256207_g_MissionTarget)
			
			if x256207_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x256207_g_MissionHelp )
			end
			x256207_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
		DispatchQuestInfoNM(sceneId, selfId, NPCId, x256207_g_ScriptId, x256207_g_MissionId);
  end
	
end
--**********************************

function x256207_ProcAcceptCheck(sceneId, selfId, NPCId)
	local nLevel = GetLevel(sceneId, selfId)
	
	if nLevel<x256207_g_LevelLess then
		return 0
	end
	return 1
		

end
--**********************************
function x256207_CheckSubmit( sceneId, selfId, NPCId)
	if IsHaveQuestNM(sceneId,selfId,x256207_g_MissionId) <= 0 then
		
		return 0
    end
	
	local misIndex = GetQuestIndexByID( sceneId, selfId, x256207_g_MissionId )

	local Num = GetItemCount( sceneId, selfId, x256207_g_ItemId )
	
	if Num < x256207_g_NeedItemCount then --还没有完成任务
		
		return 0;
	end

	return 1;
	
end
--**********************************
function x256207_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256207_g_MissionId) > 0 then
				return 
		end
		if IsQuestFullNM(sceneId,selfId)==1 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"可接任务数量已满")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 
		end
		
		--检查前置任务
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256207_g_MissionId  )
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
		
		
		if x256207_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
				local retmiss = AddQuest( sceneId, selfId, x256207_g_MissionId, x256207_g_ScriptId, 1, 0, 1,1)
				if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
				else
		  			x256207_Msg2toplayer( sceneId, selfId,0)
						
					local misIndex = GetQuestIndexByID(sceneId,selfId,x256207_g_MissionId)                                                  
	    			SetQuestByIndex(sceneId,selfId,misIndex,0,0)
	    			SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	    			
		  		end
	 	end                                                                    
	     
end
--**********************************

function x256207_ProcQuestAbandon(sceneId, selfId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256207_g_MissionId) <= 0 then
		return 
	end
	local n = GetItemCount( sceneId, selfId, x256207_g_ItemId );

	
	if n > 0 then
		DelItem(sceneId, selfId,x256207_g_ItemId,n)
		
	end




	DelQuest(sceneId, selfId, x256207_g_MissionId)
	x256207_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x256207_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x256207_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x256207_g_BonusChoiceItem do
        if item.item == selectRadioId then
            AddItem( sceneId, item.item, item.n )
            break
        end
  end
  local ret = EndAddItem(sceneId,selfId)
    if ret <= 0 then
        if result == 1 then
            result = 0
        end
    end
	return result
end
--**********************************
function x256207_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256207_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256207_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				x256207_ShowTips(sceneId, selfId, format("所需任务物品不足%d",x256207_g_NeedItemCount))
				return 0
	elseif x256207_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256207_g_MissionId) > 0 then
				x256207_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x256207_g_MissionId)
				--CallScriptFunction( UTILITY_SCRIPT, "PlaySound", sceneId, selfId, 6 )
				x256207_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256207_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x256207_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		AddItemListToPlayer(sceneId,selfId)
				local n = GetItemCount( sceneId, selfId, x256207_g_ItemId );
				if n > 0 then
					DelItem(sceneId, selfId,x256207_g_ItemId,n)
					
				end

   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256207_g_MissionIdNext )	
end

function x256207_GetBonus( sceneId, selfId,NpcID)
	  if x256207_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256207_g_ExpBonus);
  	end
		if x256207_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256207_g_BonusMoney1 )
	  end
		if x256207_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256207_g_BonusMoney2 )
	  end
		if x256207_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256207_g_BonusMoney3 )
		end
		if x256207_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256207_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256207_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256207_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256207_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256207_g_BonusMoney6)
		end
end

function x256207_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x256207_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x256207_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x256207_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x256207_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x256207_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x256207_g_MissionName.."！", 0, 3)
				if x256207_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x256207_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x256207_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x256207_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x256207_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x256207_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x256207_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x256207_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x256207_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x256207_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x256207_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x256207_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x256207_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x256207_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x256207_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	
	
	
	if GetName(sceneId, objId) ~= x256207_g_MonsterName then
		return
	end
	
	x256207_AddLootItem(sceneId, selfId)

	local bHasTeam = HasTeam(sceneId, selfId)

	

	if bHasTeam>0 then
	
		local nearteamnum = GetNearTeamCount(sceneId, selfId);
		

		for i=0, nearteamnum-1 do
			local memberId = GetNearTeamMember(sceneId, selfId, i)

			if memberId~=selfId then
				x256207_AddLootItem(sceneId, memberId)
			end
			
		end
	end
end

function x256207_AddLootItem(sceneId, selfId)
	if IsHaveQuest(sceneId,selfId, x256207_g_MissionId) <= 0 then
		return
	end

	if HaveItem( sceneId, selfId, x256207_g_ItemId ) <  x256207_g_NeedItemCount then
		
		
		BeginAddItem(sceneId)
		AddBindItem( sceneId, x256207_g_ItemId, 1 )
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
			--AddItemListToPlayer(sceneId,selfId)
			AddItemListToPlayer(sceneId,selfId)
			
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"物品栏已满，无法得到任务物品！")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end
	end
end


function x256207_ProcQuestLogRefresh( sceneId, selfId, MissionId)

	x256207_QuestLogRefresh( sceneId, selfId, MissionId );
end

---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x256207_QuestLogRefresh( sceneId, selfId, MissionId)
	
			
	BeginQuestEvent(sceneId)	
		
	AddQuestLogCustomText( sceneId,
							"",						-- 标题
							"",
							x256207_GetMissionTask(sceneId,selfId),
							"@npc_"..x256207_g_ReplyNpc,
							"",
							"",
							""
--							x256207_g_MissionName,        -- 任务名字
--							x256207_GetMissionTask(sceneId,selfId),		--任务目标
--							"@npc_"..x256207_g_ReplyNpc,			--任务NPC
--							x256207_GetMissionMethod(sceneId,selfId),               --任务攻略
--							x256207_GetMissionText(sceneId,selfId),	--任务描述
--							x256207_GetMissionHelp(sceneId,selfId)					--任务小提示
							)

	--1、经验
	
	
	if x256207_g_ExpBonus > 0 then
		AddQuestExpBonus( sceneId, x256207_g_ExpBonus)
	end

	for i, item in x256207_g_BonusItem do
		AddQuestItemBonus(sceneId, item.item, item.n)
	end

	for i, item in x256207_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end

	

	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	

end

function x256207_GetMissionTask(sceneId,selfId)
	local misIndex = GetQuestIndexByID( sceneId, selfId, x256207_g_MissionId )
	local nNum = GetQuestParam( sceneId, selfId, misIndex, 0 )
	return format("  获得@item_13015012#W(%d/%d)",nNum,x256207_g_NeedItemCount)
end

function x256207_GetMissionMethod(sceneId,selfId)
	return "攻略"
end

function x256207_GetMissionText(sceneId,selfId)
	return "描述"
end

function x256207_GetMissionHelp(sceneId,selfId)	
	return "任务提示"
end

function x256207_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	
end

function x256207_ProcTiming(sceneId, selfId, ScriptId, MissionId)
		
end

function x256207_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
end

function x256207_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
	if IsPlayerStateNormal(sceneId, selfId) == 0 then
		
		return 
	end

	if GetHp(sceneId, selfId) <= 0 then
		return
	end

	if MissionId==nil then
		return
	end

	
	if itemdataId~=x256207_g_ItemId then
		return
	end
    
    if IsHaveQuestNM(sceneId,selfId,x256207_g_MissionId) <= 0 then
      
		return 
    end
	
	local misIndex = GetQuestIndexByID( sceneId, selfId, x256207_g_MissionId )

	if x256207_g_NeedItemCount > 0 then
		local Num = GetItemCount( sceneId, selfId, x256207_g_ItemId )
		
		if Num < x256207_g_NeedItemCount then --还没有完成任务
			
			
			
			
			if(MissionId==0)then
				local strText = format("您获得了@item_13015012: %d/%d", Num, x256207_g_NeedItemCount);
				BeginQuestEvent(sceneId);
					AddQuestText(sceneId,strText);
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
			end

			

			
   			SetQuestByIndex( sceneId, selfId, misIndex, 0, Num ) 
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
			
			x256207_QuestLogRefresh( sceneId, selfId, x256207_g_MissionId)
		elseif Num >= x256207_g_NeedItemCount then
			--已经完成任务
			local strText = format( "您获得了@item_13015012: %d/%d", Num, x256207_g_NeedItemCount )
			if strText == nil then
				strText = "";
			end
			BeginQuestEvent(sceneId)
			
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			
			SetQuestByIndex( sceneId, selfId, misIndex, 0, Num )     

			SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
			x256207_QuestLogRefresh( sceneId, selfId, x256207_g_MissionId)
		end
	end
end


function x256207_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	
    if x256207_g_ReplyNpc ~= npcGuid then
        return
    end
		if IsHaveQuest(sceneId,selfId, x256207_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x256207_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x256207_g_MissionId, state, -1 )
		end
end

function x256207_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	
end

function x256207_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	
end

function x256207_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	
end

function x256207_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	
end

function x256207_OnProcOver( sceneId, selfId, targetId )
	
end

function x256207_OpenCheck( sceneId, selfId, targetId )
	
end

function x256207_ShowTips(sceneId, selfId, str)

	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	
end