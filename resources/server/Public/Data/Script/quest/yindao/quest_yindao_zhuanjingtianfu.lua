--询问状况

--MisDescBegin
x203829_g_ScriptId = 203829
x203829_g_MissionIdPre = -1
x203829_g_MissionId = 4082
x203829_g_LevelLess	= 	80 
x203829_g_MissionIdNext = -1
x203829_g_Name	={}
x203829_g_ExtTarget={{type=20,n=1,target="在@npc_141103处完成一次专攻训练"}}
x203829_g_MissionName="【引导】攻无不克"
x203829_g_MissionInfo="\t学习专精天赋之后可以提升你对其他玩家的伤害。现在你就将专攻点数分配到自身之上吧。\n \n#G小提示:#W\n\t1.学习专精天赋需要#R天赋等级达到50级以上#W。\n\t2.学习专精天赋方法：与大都专精天赋大师对话，选择【专攻训练】打开专攻分配界面，将自己的剩余点数分配到相应职业上。"  --任务描述
x203829_g_MissionTarget=""		
x203829_g_MissionCompleted="\t很好，这是一个好的开始。继续学习专精天赋的话，你对其他玩家的伤害会更高。"					--完成任务npc说话的话
x203829_g_ContinueInfo="\t你不想让自己更加强大起来吗？\n天赋等级到达50级后，可以找我进行专精天赋专攻训练，提高自己对某一特定职业的伤害。"
x203829_g_MissionHelp =	""
x203829_g_DemandItem ={}
x203829_g_ExpBonus = 500000
x203829_g_BonusMoney1 =800
x203829_g_BonusMoney2 =0
x203829_g_BonusMoney3 =0
x203829_g_BonusMoney4 =0
x203829_g_BonusMoney5 =90
x203829_g_BonusMoney6 =0
x203829_g_BonusItem	=	{}
x203829_g_BonusChoiceItem ={}
x203829_g_NpcGUID ={{ guid = 141103, name = "专精天赋大师"} }
--MisDescEnd
--**********************************
-- 最大等级
x203829_g_MaxLevel      = 120

function x203829_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
     local level = GetLevel(sceneId, selfId)
	   if level < x203829_g_LevelLess or level >= x203829_g_MaxLevel then
		return
	end


	if IsQuestHaveDone(sceneId, selfId, x203829_g_MissionId) > 0 then
		return 
	end

	if IsHaveQuest(sceneId,selfId, x203829_g_MissionId) <= 0 then
		--if IsQuestHaveDone(sceneId, selfId, x203829_g_MissionIdPre) > 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x203829_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x203829_g_MissionId, state, -1 )
		end
	--end

end

function x203829_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203829_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203829_g_ExpBonus )
		end
		if x203829_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203829_g_BonusMoney1 )
		end
		if x203829_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203829_g_BonusMoney2 )
		end
		if x203829_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203829_g_BonusMoney3 )
		end
		if x203829_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203829_g_BonusMoney4 )
		end
		if x203829_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203829_g_BonusMoney5 )
		end
		if x203829_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203829_g_BonusMoney6 )
		end
		for i, item in x203829_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	 	end
		for i, item in x203829_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  	end
end
--**********************************

function x203829_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x203829_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203829_g_MissionId) > 0 then
			if x203829_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x203829_g_MissionName)
				AddQuestText(sceneId,x203829_g_ContinueInfo)
				EndQuestEvent()
				DispatchQuestEventList(sceneId, selfId, NPCId, x203829_g_ScriptId, x203829_g_MissionId);
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x203829_g_MissionName)
				AddQuestText(sceneId,x203829_g_MissionCompleted)
				AddQuestText(sceneId," ")
				x203829_DispatchMissionInfo( sceneId, selfId, NPCId )
				EndQuestEvent()
				DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203829_g_ScriptId, x203829_g_MissionId);
			end
  elseif x203829_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  		AddQuestText(sceneId,"#Y"..x203829_g_MissionName)
			AddQuestText(sceneId,x203829_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x203829_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203829_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x203829_g_MissionHelp )
			end
			x203829_DispatchMissionInfo( sceneId, selfId, NPCId )
	  		EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203829_g_ScriptId, x203829_g_MissionId);
  end
	
end
--**********************************

function x203829_ProcAcceptCheck(sceneId, selfId, NPCId)
		
	return 1
		

end
--**********************************
function x203829_CheckSubmit( sceneId, selfId, NPCId)                                                 
	local misIndex = GetQuestIndexByID(sceneId,selfId,x203829_g_MissionId)
	if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
	    return 1
	else
	    return 0
	end
end

--**********************************
function x203829_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203829_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203829_g_MissionId  )
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
		
		if x203829_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203829_g_MissionId, x203829_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x203829_Msg2toplayer( sceneId, selfId,0)
					--判断如果已经分配过专攻系数 则任务置为完成
					local retComplete = GetQuestData( sceneId, selfId, MD_ZHUANGONG_COEFFICIENT[1], MD_ZHUANGONG_COEFFICIENT[2], MD_ZHUANGONG_COEFFICIENT[3] )
					if retComplete == 1 then
						local misidx = GetQuestIndexByID(sceneId,selfId,x203829_g_MissionId)
						SetQuestByIndex(sceneId,selfId,misidx,0,1)
						SetQuestByIndex(sceneId,selfId,misidx,7,1)
					end
				end
	 	end                                                                    
	     
end
--**********************************

function x203829_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203829_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203829_g_MissionId)
	  x203829_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x203829_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x203829_g_BonusItem do
		AddBindItem( sceneId, item.item, item.n )
  end
  for j, item in x203829_g_BonusChoiceItem do
        if item.item == selectRadioId then
            AddBindItem( sceneId, item.item, item.n )
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
function x203829_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203829_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203829_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203829_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"背包空间不足，请清理后再来！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203829_g_MissionId) > 0 then
				x203829_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203829_g_MissionId)
				x203829_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203829_g_BonusItem do
 						AddBindItem( sceneId, item.item, item.n )
				end
				for i, item in x203829_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203829_g_MissionIdNext )	
end

function x203829_GetBonus( sceneId, selfId,NpcID)
	  if x203829_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203829_g_ExpBonus);
  	end
		if x203829_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203829_g_BonusMoney1 )
	  end
		if x203829_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203829_g_BonusMoney2 )
	  end
		if x203829_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203829_g_BonusMoney3 )
		end
		if x203829_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203829_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203829_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203829_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203829_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203829_g_BonusMoney6)
		end
end

function x203829_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x203829_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x203829_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203829_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203829_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203829_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203829_g_MissionName.."！", 0, 3)
				if x203829_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x203829_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x203829_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x203829_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x203829_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x203829_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x203829_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x203829_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x203829_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x203829_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x203829_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x203829_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x203829_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x203829_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x203829_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203829_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203829_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203829_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203829_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203829_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x203829_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203829_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203829_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203829_g_MissionId, state, -1 )
		end
end

function x203829_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203829_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203829_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203829_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203829_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203829_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end