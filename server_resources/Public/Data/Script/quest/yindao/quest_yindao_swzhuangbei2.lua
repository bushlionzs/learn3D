--询问状况

--MisDescBegin
x203760_g_ScriptId = 203760
x203760_g_MissionIdPre = 4214
x203760_g_MissionId = 4218
x203760_g_LevelLess	= 	20 
x203760_g_MissionIdNext = 2697
x203760_g_Name	={}
x203760_g_ExtTarget={{type=20,n=1,target="在@npc_129024处兑处换一件声望装"}}
x203760_g_MissionName="【个人】第一件声望装"
x203760_g_MissionInfo="\t亲爱的朋友，在我的手中有很多声望套装，换上这些套装你的能力会有明显的提升。\n\t点击声望商店后，左键点击#G换取世传君主套装#c000000的选项，会打开世传君主装备商店。其中有#G五件套装#c000000，选取你喜欢的一件#G右键点击该套装#c000000，在声望足够的情况下便兑换成功。\n\t这里我推荐你首先兑换世传君主套装中的兵器，如果你不小心将套装卖出，可点击商店中的#G回购#c000000再将套装买回。"  --任务描述
x203760_g_MissionTarget=""		
x203760_g_MissionCompleted="\t这件装备必然对你日后成长和能力提高起到不可低估的作用。\n\t一定要记住，日后在获得足够的声望还可以来我这里兑换装备。"					--完成任务npc说话的话
x203760_g_ContinueInfo="\t你不想兑换一件声望套装吗？"
x203760_g_MissionHelp =	""
x203760_g_DemandItem = {10014001,10024001,10034001,10044001,10054001,10064001,10074001,10084001,10094001,10104001,10114001,10124001,10234001,10234011,10234021,10234031,10234041,10234051,10254001,10254011,10254021,10254031,10254041,10254051,10274001,10274011,10274021,10274031,10274041,10274051,10354001,10414001,10204061,10239218,10259218,10269218,10279218,10249218,10364001,10424001,10204071,10239222,10259222,10269222,10279222,10249222,10374001,10434001,10204081,10239226,10259226,10269226,10279226,10249226,10384001,10444001,10204091,10239230,10259230,10269230,10279230,10249230,10394001,10455001,10204101,10239234,10259234,10269234,10279234,10249234,10404001,10464001,10204111,10239238,10259238,10269238,10279238,10249238,10354001,10414001,10239218,10259218,10279218,10364001,10424001,10239222,10259222,10279222,10374001,10434001,10239226,10259226,10279226,10384001,10444001,10239230,10259230,10279230,10394001,10454001,10239234,10259234,10279234,10404001,10464001,10239238,10259238,10279238}
x203760_g_ExpBonus = 10200
x203760_g_BonusMoney1 =0
x203760_g_BonusMoney2 =0
x203760_g_BonusMoney3 =0
x203760_g_BonusMoney4 =0
x203760_g_BonusMoney5 =0
x203760_g_BonusMoney6 =0
x203760_g_BonusItem	=	{{item=11000200,n=5}}
x203760_g_BonusChoiceItem ={}
x203760_g_NpcGUID ={{ guid = 129024, name = "声望商店"} }
--MisDescEnd
--**********************************
x203760_g_MaxLevel   = 40

function x203760_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    local level = GetLevel(sceneId, selfId)
	if level < x203760_g_LevelLess or level >= x203760_g_MaxLevel then
		return

	end



	if IsQuestHaveDone(sceneId, selfId, x203760_g_MissionId) > 0 then
		return 
			
	end

	if IsQuestHaveDone(sceneId, selfId, x203760_g_MissionIdPre)> 0 then 
		
	if IsHaveQuest(sceneId,selfId, x203760_g_MissionId) <= 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x203760_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x203760_g_MissionId, state, -1 )
	end
	end

end

function x203760_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203760_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203760_g_ExpBonus )
		end
		if x203760_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203760_g_BonusMoney1 )
		end
		if x203760_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203760_g_BonusMoney2 )
		end
		if x203760_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203760_g_BonusMoney3 )
		end
		if x203760_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203760_g_BonusMoney4 )
		end
		if x203760_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203760_g_BonusMoney5 )
		end
		if x203760_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203760_g_BonusMoney6 )
		end
		for i, item in x203760_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	 	end
		for i, item in x203760_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  	end
end
--**********************************

function x203760_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x203760_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203760_g_MissionId) > 0 then
			if x203760_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x203760_g_MissionName)
				AddQuestText(sceneId,x203760_g_ContinueInfo)
				EndQuestEvent()
				DispatchQuestEventList(sceneId, selfId, NPCId, x203760_g_ScriptId, x203760_g_MissionId);
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x203760_g_MissionName)
				AddQuestText(sceneId,x203760_g_MissionCompleted)
				AddQuestText(sceneId," ")
				x203760_DispatchMissionInfo( sceneId, selfId, NPCId )
				EndQuestEvent()
				DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203760_g_ScriptId, x203760_g_MissionId);
			end
  elseif x203760_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  		AddQuestText(sceneId,"#Y"..x203760_g_MissionName)
			AddQuestText(sceneId,x203760_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x203760_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203760_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#c000000")
				AddQuestText(sceneId,x203760_g_MissionHelp )
			end
			x203760_DispatchMissionInfo( sceneId, selfId, NPCId )
	  		EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203760_g_ScriptId, x203760_g_MissionId);
  end
	
end
--**********************************

function x203760_ProcAcceptCheck(sceneId, selfId, NPCId)
		
	return 1
		

end
--**********************************
function x203760_CheckSubmit( sceneId, selfId, NPCId)  
                                                  
		if  IsHaveQuest(sceneId, selfId,x203760_g_MissionId) ~=1 then
			return 0
		end
		
	   	local 	misIndex = GetQuestIndexByID(sceneId, selfId,x203760_g_MissionId)                                                  
	   	if GetQuestParam(sceneId, selfId,misIndex,7,1) == 1 then
	   		return 1
	   	else 
	   		return 0
	   	end
	   	
	
end

--**********************************
function x203760_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203760_g_MissionId) > 0 then
				return 
		end
		if IsQuestFullNM(sceneId,selfId)==1 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"可接任务数量已满")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 
		end
		
--		检查前置任务
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203760_g_MissionId  )
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
		
		if x203760_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then

					local retmiss = AddQuest( sceneId, selfId, x203760_g_MissionId, x203760_g_ScriptId, 0, 0, 1,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x203760_Msg2toplayer( sceneId, selfId,0)
		  			
					for i, item in x203760_g_DemandItem do
						if GetItemCount(sceneId,selfId,x203760_g_DemandItem[i]) >= 1 then		
							local misIndex = GetQuestIndexByID(sceneId,selfId,x203760_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 32,0 )
								--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 33,0 )
						end
					end
					--x203760_ProcQuestItemChanged(sceneId, selfId, -1, MissionId)
					end
		  			
	 	end                                                                    
	     
end
--**********************************

function x203760_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203760_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203760_g_MissionId)
	  x203760_Msg2toplayer( sceneId, selfId,1)
		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 32,0 )
		--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 33,0 )	
end
--**********************************
function x203760_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x203760_g_BonusItem do
		AddBindItem( sceneId, item.item, item.n )
  end
  for j, item in x203760_g_BonusChoiceItem do
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
function x203760_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203760_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203760_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203760_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"背包空间不足，请清理后再来！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203760_g_MissionId) > 0 then
				x203760_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203760_g_MissionId)
				x203760_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203760_g_BonusItem do
 						AddBindItem( sceneId, item.item, item.n )
				end
				for i, item in x203760_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203760_g_MissionIdNext )	
end

function x203760_GetBonus( sceneId, selfId,NpcID)
	  if x203760_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203760_g_ExpBonus);
  	end
		if x203760_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203760_g_BonusMoney1 )
	  end
		if x203760_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203760_g_BonusMoney2 )
	  end
		if x203760_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203760_g_BonusMoney3 )
		end
		if x203760_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203760_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203760_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203760_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203760_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203760_g_BonusMoney6)
		end
end

function x203760_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务："..x203760_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务："..x203760_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务："..x203760_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务："..x203760_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203760_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203760_g_MissionName.."！", 0, 3)
				if x203760_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x203760_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x203760_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x203760_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x203760_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x203760_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x203760_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x203760_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x203760_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x203760_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x203760_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x203760_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x203760_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x203760_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x203760_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203760_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203760_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203760_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203760_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId,optype)
	if	optype	==	0	then
		return
	end
	
	for i, item in x203760_g_DemandItem do
	
		if itemdataId == item then

			if GetItemCount(sceneId,selfId,item) >= 1 then
					local misIndex = GetQuestIndexByID(sceneId,selfId,x203760_g_MissionId)                                                  
		    		SetQuestByIndex(sceneId,selfId,misIndex,0,1)
		    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
		    		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 32,0 )
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 33,0 )
		  	else
		  			local misIndex = GetQuestIndexByID(sceneId,selfId,x203760_g_MissionId)                                                  
		    		SetQuestByIndex(sceneId,selfId,misIndex,0,0)
		    		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
		  	end
		  	
		  	break
	  	
	  	end
	  	
	end

end


function x203760_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x203760_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203760_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203760_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203760_g_MissionId, state, -1 )
				if x203760_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 32,1 )
					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 33,0 )
				end	
		end
end

function x203760_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203760_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203760_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203760_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203760_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203760_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end