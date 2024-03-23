--龙眼石送信

--MisDescBegin
x256253_g_ScriptId = 256253
x256253_g_MissionIdPre = 3178
x256253_g_MissionId = 3068
x256253_g_LevelLess	= 	35
x256253_g_MissionIdNext = 2602
x256253_g_Name	={}
x256253_g_ExtTarget={{type=20,n=1,target="询问@npc_129043"}}
x256253_g_MissionName="【个人】珍宝龙眼石"
x256253_g_MissionInfo="\t前几天我击败了盗墓贼之后缴获了几颗龙眼石，我还不知有何作用，请你帮我去请教一下@npc_129043，她对这些东西很有研究，问问这些龙眼石有什么作用。"  --任务描述
x256253_g_MissionTarget=""		
x256253_g_MissionCompleted="\t龙眼石本是炼金的极品材料，如今可是取之不易啊！你如果对此物感兴趣我倒是可以赠与你几颗 。"					--完成任务npc说话的话
x256253_g_ContinueInfo=""
x256253_g_MissionHelp =	""
x256253_g_DemandItem ={}
x256253_g_ExpBonus = 24000
x256253_g_BonusMoney1 =176
x256253_g_BonusMoney2 =0
x256253_g_BonusMoney3 =0
x256253_g_BonusMoney4 =0
x256253_g_BonusMoney5 =21
x256253_g_BonusMoney6 =0
x256253_g_BonusItem	=	{{item=11050001,n=65}}
x256253_g_BonusChoiceItem ={}
x256253_g_NpcGUID ={{ guid = 129043, name = "龙眼石兑换"} }
--MisDescEnd
--**********************************
x256253_g_MaxLevel   = 50

function x256253_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
  local level = GetLevel(sceneId, selfId)
	if level < x256253_g_LevelLess or level >= x256253_g_MaxLevel then
	return 
	end
	
	


	if IsQuestHaveDone(sceneId, selfId, x256253_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x256253_g_MissionIdPre)> 0 then

						if IsHaveQuest(sceneId,selfId, x256253_g_MissionId) <= 0 then
								local state = GetQuestStateNM(sceneId,selfId,NPCId,x256253_g_MissionId)
								AddQuestTextNM( sceneId, selfId, NPCId, x256253_g_MissionId, state, -1 )
						end
		
	end
end

function x256253_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x256253_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256253_g_ExpBonus )
		end
		if x256253_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256253_g_BonusMoney1 )
		end
		if x256253_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256253_g_BonusMoney2 )
		end
		if x256253_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256253_g_BonusMoney3 )
		end
		if x256253_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256253_g_BonusMoney4 )
		end
		if x256253_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256253_g_BonusMoney5 )
		end
		if x256253_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256253_g_BonusMoney6 )
		end
		for i, item in x256253_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x256253_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x256253_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x256253_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256253_g_MissionId) > 0 then
			if x256253_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256253_g_MissionName)
						AddQuestText(sceneId,x256253_g_MissionCompleted)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x256253_g_ScriptId, x256253_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256253_g_MissionName)
						AddQuestText(sceneId,x256253_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x256253_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256253_g_ScriptId, x256253_g_MissionId);
			end
  elseif x256253_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x256253_g_MissionName)
			AddQuestText(sceneId,x256253_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x256253_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x256253_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x256253_g_MissionHelp )
			end
			x256253_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256253_g_ScriptId, x256253_g_MissionId);
  end
	
end
--**********************************

function x256253_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x256253_CheckSubmit( sceneId, selfId, NPCId)

	        return 1
	
end
--**********************************
function x256253_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256253_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256253_g_MissionId  )
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
		
		if x256253_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x256253_g_MissionId, x256253_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x256253_Msg2toplayer( sceneId, selfId,0)
						--if x256253_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x256253_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x256253_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256253_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x256253_g_MissionId)
	  x256253_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x256253_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x256253_g_BonusItem do
		AddBindItem( sceneId, item.item, item.n )
  end
  for j, item in x256253_g_BonusChoiceItem do
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
function x256253_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256253_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256253_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256253_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256253_g_MissionId) > 0 then
				x256253_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x256253_g_MissionId)
				x256253_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256253_g_BonusItem do
 						AddBindItem( sceneId, item.item, item.n )
				end
				for i, item in x256253_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256253_g_MissionIdNext )	
end

function x256253_GetBonus( sceneId, selfId,NpcID)
	  if x256253_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256253_g_ExpBonus);
  	end
		if x256253_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256253_g_BonusMoney1 )
	  end
		if x256253_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256253_g_BonusMoney2 )
	  end
		if x256253_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256253_g_BonusMoney3 )
		end
		if x256253_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256253_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256253_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256253_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256253_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256253_g_BonusMoney6)
		end
end

function x256253_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务："..x256253_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务："..x256253_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务："..x256253_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务："..x256253_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x256253_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x256253_g_MissionName.."！", 0, 3)
				if x256253_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x256253_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x256253_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x256253_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x256253_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x256253_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x256253_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x256253_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x256253_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x256253_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x256253_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x256253_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x256253_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x256253_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x256253_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x256253_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	--return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256253_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	-- CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x256253_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	--CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256253_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	--CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x256253_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x256253_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x256253_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x256253_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x256253_g_MissionId, state, -1 )
		end
end

function x256253_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	--return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256253_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	--return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256253_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	--return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256253_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	--return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256253_OnProcOver( sceneId, selfId, targetId )
	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256253_OpenCheck( sceneId, selfId, targetId )
	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end