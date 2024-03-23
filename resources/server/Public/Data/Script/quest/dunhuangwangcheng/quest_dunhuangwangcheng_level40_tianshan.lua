--询问状况

--MisDescBegin
x256257_g_ScriptId = 256257
--x256257_g_MissionIdPre ={67,69,70,71}
x256257_g_MissionId = 1574
x256257_g_LevelLess	= 	37 
x256257_g_MissionIdNext = -1
x256257_g_Name	={}
x256257_g_ExtTarget={{type=20,n=1,target="按任务攻略的指引升级到40级"}}
x256257_g_MissionName="【个人】四十而明"
x256257_g_MissionInfo="\t又见面了，亲爱的朋友，是否在升级的途中感到有些疲惫？那么，请暂时的停下来，听我说说：\n\t和你的朋友一起每天@npcsp_前往轮回台_126011一次，是升级的最佳选择，@npc_126063会发布国家押运任务，边塞的大将军@npc_128510会发布国家守边任务。\n\t也别忘记了那些老朋友@npc_126041，@npc_126132，@npc_126058，或者继续和你的朋友们@npcsp_前往三环副本_126040，当然，在@npc_126028领取双倍经验也是必不可少的。"  --任务描述
x256257_g_MissionTarget=""		
x256257_g_MissionCompleted="\t四十级的你，已经具备在《成吉思汗2》中立足的资本。\n\t我这里为你准备了一些小礼物，希望能对你今后的历程有所帮助。"					--完成任务npc说话的话
x256257_g_ContinueInfo="别太心急，我为你的四十级准备了不少礼物，但是......你应该先到四十级再来。"
x256257_g_MissionHelp =	""
x256257_g_DemandItem ={}
x256257_g_ExpBonus = 1800000
x256257_g_BonusMoney1 =120000
x256257_g_BonusMoney2 =0
x256257_g_BonusMoney3 =0
x256257_g_BonusMoney4 =0
x256257_g_BonusMoney5 =2000
x256257_g_BonusMoney6 =0
x256257_g_BonusItem	=	{{item=11010002,n=1},{item=12030252,n=1},{item=11060002,n=1}}
x256257_g_BonusChoiceItem ={}
x256257_g_NpcGUID ={{ guid = 126002, name = "万事通"} }
--MisDescEnd
--**********************************
-- 最大等级
x256257_g_MaxLevel      = 70

function x256257_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
		local level = GetLevel(sceneId, selfId)
	  if level < x256257_g_LevelLess or level >= x256257_g_MaxLevel then
		return
	end


	if IsQuestHaveDone(sceneId, selfId, x256257_g_MissionId) > 0 then
		return 
	end

	if IsHaveQuest(sceneId,selfId, x256257_g_MissionId) <= 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x256257_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x256257_g_MissionId, state, -1 )
	end

end

function x256257_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x256257_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256257_g_ExpBonus )
		end
		if x256257_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256257_g_BonusMoney1 )
		end
		if x256257_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256257_g_BonusMoney2 )
		end
		if x256257_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256257_g_BonusMoney3 )
		end
		if x256257_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256257_g_BonusMoney4 )
		end
		if x256257_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256257_g_BonusMoney5 )
		end
		if x256257_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256257_g_BonusMoney6 )
		end
		for i, item in x256257_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	 	end
		for i, item in x256257_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  	end
end
--**********************************

function x256257_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x256257_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256257_g_MissionId) > 0 then
			if x256257_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x256257_g_MissionName)
				AddQuestText(sceneId,x256257_g_ContinueInfo)
				EndQuestEvent()
				DispatchQuestEventList(sceneId, selfId, NPCId, x256257_g_ScriptId, x256257_g_MissionId);
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x256257_g_MissionName)
				AddQuestText(sceneId,x256257_g_MissionCompleted)
				AddQuestText(sceneId," ")
				x256257_DispatchMissionInfo( sceneId, selfId, NPCId )
				EndQuestEvent()
				DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256257_g_ScriptId, x256257_g_MissionId);
			end
  elseif x256257_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  		AddQuestText(sceneId,"#Y"..x256257_g_MissionName)
			AddQuestText(sceneId,x256257_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x256257_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x256257_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x256257_g_MissionHelp )
			end
			x256257_DispatchMissionInfo( sceneId, selfId, NPCId )
	  		EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256257_g_ScriptId, x256257_g_MissionId);
  end
	
end
--**********************************

function x256257_ProcAcceptCheck(sceneId, selfId, NPCId)
		
	return 1
		

end
--**********************************
function x256257_CheckSubmit( sceneId, selfId, NPCId)                                                 
	if GetLevel(sceneId, selfId)>= 40 then
	   return 1
	end
	 
	return 0
	
end

--**********************************
function x256257_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256257_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256257_g_MissionId  )
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
		
		if x256257_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x256257_g_MissionId, x256257_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x256257_Msg2toplayer( sceneId, selfId,0)
					if GetLevel(sceneId, selfId) >= 40 then
						local misIndex = GetQuestIndexByID(sceneId,selfId,x256257_g_MissionId)                                                  
	    				SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    				SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x256257_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256257_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x256257_g_MissionId)
	  x256257_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x256257_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x256257_g_BonusItem do
		AddBindItem( sceneId, item.item, item.n )
  end
  for j, item in x256257_g_BonusChoiceItem do
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
function x256257_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256257_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256257_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256257_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"背包空间不足，请清理后再来！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256257_g_MissionId) > 0 then
				x256257_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x256257_g_MissionId)
				x256257_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256257_g_BonusItem do
 						AddBindItem( sceneId, item.item, item.n )
				end
				for i, item in x256257_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256257_g_MissionIdNext )	
end

function x256257_GetBonus( sceneId, selfId,NpcID)
	  if x256257_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256257_g_ExpBonus);
  	end
		if x256257_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256257_g_BonusMoney1 )
	  end
		if x256257_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256257_g_BonusMoney2 )
	  end
		if x256257_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256257_g_BonusMoney3 )
		end
		if x256257_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256257_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256257_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256257_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256257_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256257_g_BonusMoney6)
		end
end

function x256257_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x256257_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x256257_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x256257_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x256257_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x256257_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x256257_g_MissionName.."！", 0, 3)
				if x256257_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x256257_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x256257_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x256257_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x256257_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x256257_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x256257_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x256257_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x256257_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x256257_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x256257_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x256257_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x256257_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x256257_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x256257_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x256257_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256257_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x256257_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256257_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x256257_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x256257_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x256257_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x256257_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x256257_g_MissionId, state, -1 )
		end
end

function x256257_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256257_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256257_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256257_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256257_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256257_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end