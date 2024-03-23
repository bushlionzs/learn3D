--vip募集券

--MisDescBegin
x256298_g_ScriptId = 256298
x256298_g_MissionIdPre =2615
x256298_g_MissionId = 2638
x256298_g_LevelLess	= 	42 
x256298_g_MissionIdNext = -1
x256298_g_Name	={}
x256298_g_ExtTarget={{type=20,n=1,target="在金币商店贵宾区一星麒麟商店购买一个VIP募集券交给帮会管理员"}}
x256298_g_MissionName="【个人】第一次帮会募集"
x256298_g_MissionInfo="\t经验和帮贡有一个很重要也很简单的获得方式：帮会募集。我想，你首先应当熟悉一下帮会募集的流程。在#G金币商店贵宾区一星麒麟商店#W购买一个#GVIP募集券#W交给我吧"  --任务描述
x256298_g_MissionTarget=""		
x256298_g_MissionCompleted="\t很好，虽然这#GVIP募集券#W只能上交一次，但以后你每天都可以在普通的金币商店购买普通的#G募集券#W交给我。"					--完成任务npc说话的话
x256298_g_ContinueInfo="\t怎么？还没有拿来#GVIP募集券#W吗？"
x256298_g_MissionHelp =	"VIP募集券在金币商店贵宾区一星麒麟商店可以购买，但需要您的充值达到一定的金额，才能获得其中购买相应物品的权限。每个帮会每天最多接受50个VIP募集券。"
x256298_g_DemandItem =	{11990116}						
x256298_g_BonusMoney1 =0
x256298_g_BonusMoney2 =0
x256298_g_BonusMoney3 =0
x256298_g_BonusMoney4 =0
x256298_g_BonusMoney5 =0
x256298_g_BonusMoney6 =0
x256298_g_BonusItem	=	{}
x256298_g_BonusChoiceItem ={}
x256298_g_ExpBonus = 1200000
x256298_g_BonusMoney8 =300
x256298_g_GuildExpBonus =1
x256298_g_NpcGUID ={{ guid = 132022, name = "帮会管理员"} }
--MisDescEnd
-- 最大等级
x256298_g_MaxLevel      = 160

--**********************************

function x256298_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    local level = GetLevel(sceneId, selfId)
	if level < x256298_g_LevelLess or level >= x256298_g_MaxLevel then
		return
	end
	if GetGuildID( sceneId, selfId ) == -1 then
		--不在帮会中
		return
	end


	if IsQuestHaveDone(sceneId, selfId, x256298_g_MissionId) > 0 then --已完成过任务
		return 
	end
	
	if IsQuestHaveDone(sceneId, selfId, x256298_g_MissionIdPre)> 0 then 
	if IsHaveQuest(sceneId,selfId, x256298_g_MissionId) <= 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x256298_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x256298_g_MissionId, state, -1 )
	end
	end

end

function x256298_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x256298_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256298_g_ExpBonus )
		end
		if x256298_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256298_g_BonusMoney1 )
		end
		if x256298_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256298_g_BonusMoney2 )
		end
		if x256298_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256298_g_BonusMoney3 )
		end
		if x256298_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256298_g_BonusMoney4 )
		end
		if x256298_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256298_g_BonusMoney5 )
		end
		if x256298_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256298_g_BonusMoney6 )
		end
		if x256298_g_BonusMoney8 > 0 then
			AddQuestMoneyBonus8(sceneId, x256298_g_BonusMoney8 )
		end
		if x256298_g_GuildExpBonus>0 then
			AddQuestGuildExpBonus(sceneId,x256298_g_GuildExpBonus)
		end
		for i, item in x256298_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	 	end
		for i, item in x256298_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  	end
end
--**********************************

function x256298_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x256298_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256298_g_MissionId) > 0 then
			if x256298_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x256298_g_MissionName)
				AddQuestText(sceneId,x256298_g_ContinueInfo)
				EndQuestEvent()
				DispatchQuestEventList(sceneId, selfId, NPCId, x256298_g_ScriptId, x256298_g_MissionId);
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x256298_g_MissionName)
				AddQuestText(sceneId,x256298_g_MissionCompleted)
				AddQuestText(sceneId," ")
				x256298_DispatchMissionInfo( sceneId, selfId, NPCId )
				EndQuestEvent()
				DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256298_g_ScriptId, x256298_g_MissionId);
			end
  elseif x256298_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  		AddQuestText(sceneId,"#Y"..x256298_g_MissionName)
			AddQuestText(sceneId,x256298_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x256298_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x256298_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x256298_g_MissionHelp )
			end
			x256298_DispatchMissionInfo( sceneId, selfId, NPCId )
	  		EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256298_g_ScriptId, x256298_g_MissionId);
  end
	
end
--**********************************

function x256298_ProcAcceptCheck(sceneId, selfId, NPCId)
		
	return 1
		

end
--**********************************
function x256298_CheckSubmit( sceneId, selfId, NPCId)  
                                                  
		if  IsHaveQuest(sceneId, selfId,x256298_g_MissionId) ~=1 then
			return 0
		end
		
	   	local 	misIndex = GetQuestIndexByID(sceneId, selfId,x256298_g_MissionId)                                                  
	   	if GetQuestParam(sceneId, selfId,misIndex,7,1) == 1 then
	   		return 1
	   	else 
	   		return 0
	   	end
	   	
	
end

--**********************************
function x256298_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256298_g_MissionId) > 0 then
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
--		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256298_g_MissionId  )
--		if FrontMissiontId1 ~= -1 then
--			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
--				return 0
--			end
--		end
--		if FrontMissiontId2 ~= -1 then
--			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
--				return 0
--			end
--		end
--		if FrontMissiontId3 ~= -1 then
--			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
--				return 0
--			end
--		end
		
		if x256298_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then

					local retmiss = AddQuest( sceneId, selfId, x256298_g_MissionId, x256298_g_ScriptId, 0, 0, 1,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x256298_Msg2toplayer( sceneId, selfId,0)
		  			CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 25,1 )
		  			--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 26,1 )
		  			CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 46,1 )
					for i, item in x256298_g_DemandItem do
						if GetItemCount(sceneId,selfId,item) >= 1 then		
							local misIndex = GetQuestIndexByID(sceneId,selfId,x256298_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 25,0 )
		  					--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 26,0 )
		  					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 46,0 )
						end
					end
					--x256298_ProcQuestItemChanged(sceneId, selfId, -1, MissionId)
					end
		  			
	 	end                                                                    
	     
end
--**********************************

function x256298_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256298_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x256298_g_MissionId)
	  x256298_Msg2toplayer( sceneId, selfId,1)
		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 25,0 )
		--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 26,0 )
		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 46,0 )	
end
--**********************************
function x256298_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x256298_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x256298_g_BonusChoiceItem do
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
function x256298_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256298_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256298_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256298_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"背包空间不足，请清理后再来！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif GetGuildID( sceneId, selfId ) == -1 then
		--不在帮会中
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"你需要先加入一个帮会！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
		
	else
				GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_VIP_COLLECT_COUNT, x256298_g_ScriptId, -1, "OnReturn1" );		
   	end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256298_g_MissionIdNext )	
end

function x256298_OnReturn1(sceneId, selfId,MissionData,MissionId,targetId)
		

	if MissionData >= 49 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"很抱歉，每个帮会每天只能接受50次VIP募集券，请明日再来")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	elseif DelQuest(sceneId, selfId, x256298_g_MissionId) > 0 then
				local guildid = GetGuildID(sceneId,selfId);
				SetGuildQuestData(sceneId, guildid, GD_GUILD_INDEX_VIP_COLLECT_COUNT, 1, 1 );	
				x256298_Msg2toplayer( sceneId, selfId,2)
				DelItem( sceneId,selfId,11990116,1 )
				QuestCom(sceneId, selfId, x256298_g_MissionId)
				
				x256298_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256298_g_BonusItem do
 						AddBindItem( sceneId, item.item, item.n )
				end
				for i, item in x256298_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256298_g_MissionIdNext )	
end

function x256298_GetBonus( sceneId, selfId,NpcID)
	  if x256298_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256298_g_ExpBonus);
  	end
		if x256298_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256298_g_BonusMoney1 )
	  end
		if x256298_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256298_g_BonusMoney2 )
	  end
		if x256298_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256298_g_BonusMoney3 )
		end
		if x256298_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256298_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256298_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256298_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256298_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256298_g_BonusMoney6)
		end

		if x256298_g_BonusMoney8 > 0 then
		AddGuildUserPoint(sceneId,selfId,x256298_g_BonusMoney8)	--增加帮贡
		local BonusMoney8 = x256298_g_BonusMoney8
		local pointText = "获得#R帮贡"..BonusMoney8.."点#o的奖励"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, pointText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)			
  		Msg2Player(sceneId,selfId,pointText,8,2)
		end
-- 奖励帮会经验
	local bangExp = x256298_g_GuildExpBonus 
	if bangExp > 0 then
		AddGuildExp(sceneId,selfId,bangExp)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "获得#R帮会经验"..bangExp.."点#o的奖励");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)			
  		Msg2Player(sceneId,selfId,"获得#R帮会经验"..bangExp.."点#o的奖励",8,2)
	end
end

function x256298_Msg2toplayer( sceneId, selfId,type)
			if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x256298_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x256298_g_MissionName.."！", 0, 3)
			elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x256298_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x256298_g_MissionName.."！", 0, 3)
			elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x256298_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x256298_g_MissionName.."！", 0, 3)
			if x256298_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x256298_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
			if x256298_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x256298_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
			if x256298_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x256298_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
			if x256298_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x256298_g_BonusMoney3.."文#Y的奖励", 0, 2)
			end
			if x256298_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x256298_g_BonusMoney4.."#Y的奖励", 0, 2)
			end
			if x256298_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x256298_g_BonusMoney5.."#Y的奖励", 0, 2)
			end
			if x256298_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x256298_g_BonusMoney6.."#Y的奖励", 0, 2)
			end
		end
end

function x256298_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x256298_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256298_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x256298_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256298_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId,optype)
	if	optype	==	0	then
		return
	end
	
	for i, item in x256298_g_DemandItem do
	
		if itemdataId == item then

			if GetItemCount(sceneId,selfId,item) >= 1 then
					local misIndex = GetQuestIndexByID(sceneId,selfId,x256298_g_MissionId)                                                  
		    		SetQuestByIndex(sceneId,selfId,misIndex,0,1)
		    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
		    		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 25,0 )
		  			--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 26,0 )
		  			CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 46,0 )
		  	else
		  			local misIndex = GetQuestIndexByID(sceneId,selfId,x256298_g_MissionId)                                                  
		    		SetQuestByIndex(sceneId,selfId,misIndex,0,0)
		    		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
		  	end
		  	
		  	break
	  	
	  	end
	  	
	end

end


function x256298_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x256298_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x256298_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x256298_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x256298_g_MissionId, state, -1 )
		end
end

function x256298_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256298_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256298_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256298_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256298_OnProcOver( sceneId, selfId, targetId )
	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256298_OpenCheck( sceneId, selfId, targetId )
	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x256298_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	if IsHaveQuest(sceneId,selfId, x256298_g_MissionId) ~= 1 then
		return 
	end
	
	BeginQuestEvent(sceneId)	
	if x256298_g_ExpBonus> 0 then
		AddQuestExpBonus(sceneId, x256298_g_ExpBonus )
	end
	if x256298_g_BonusMoney1 > 0 then
		AddQuestMoneyBonus1(sceneId, x256298_g_BonusMoney1 )
	end
	if x256298_g_BonusMoney2 > 0 then
		AddQuestMoneyBonus2(sceneId, x256298_g_BonusMoney2 )
	end
	if x256298_g_BonusMoney3 > 0 then
		AddQuestMoneyBonus3(sceneId, x256298_g_BonusMoney3 )
	end
	if x256298_g_BonusMoney4 > 0 then
		AddQuestMoneyBonus4(sceneId, x256298_g_BonusMoney4 )
	end
	if x256298_g_BonusMoney5 > 0 then
		AddQuestMoneyBonus5(sceneId, x256298_g_BonusMoney5 )
	end
	if x256298_g_BonusMoney6 > 0 then
		AddQuestMoneyBonus6(sceneId, x256298_g_BonusMoney6 )
	end
	if x256298_g_BonusMoney8 > 0 then
		AddQuestMoneyBonus8(sceneId, x256298_g_BonusMoney8 )
	end
	if x256298_g_GuildExpBonus>0 then
		AddQuestGuildExpBonus(sceneId,x256298_g_GuildExpBonus)
	end
	for i, item in x256298_g_BonusItem do
	   	AddQuestItemBonus(sceneId, item.item, item.n)
 	end
	for i, item in x256298_g_BonusChoiceItem do
    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
  	end
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, x256298_g_MissionId);
end