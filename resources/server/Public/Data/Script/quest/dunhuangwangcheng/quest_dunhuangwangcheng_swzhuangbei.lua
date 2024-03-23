--询问状况

--MisDescBegin
x256226_g_ScriptId = 256226
x256226_g_MissionIdPre =3050
x256226_g_MissionId = 3092
x256226_g_LevelLess	= 	25 
x256226_g_MissionIdNext = 3051
x256226_g_Name	={}
x256226_g_ExtTarget={{type=20,n=1,target="在#G声望商店#W答剌速处兑处换一件@npc_82066"}}
x256226_g_MissionName="【个人】第一件声望装"
x256226_g_MissionInfo="\t亲爱的朋友，在我的手中有很多声望套装，换上这些套装你的能力会有明显的提升。\n\t点击声望商店后，左键点击#G换取世传君主套装#W的选项，会打开世传君主装备商店。其中有#G五件套装#W，选取你喜欢的一件#G右键点击该套装#W，在声望足够的情况下便兑换成功。\n\t这里我推荐你首先兑换世传君主套装中的兵器，如果你不小心将套装卖出，可点击商店中的#G回购#W再将套装买回。"  --任务描述
x256226_g_MissionTarget=""		
x256226_g_MissionCompleted="\t这件装备必然对你日后成长和能力提高起到不可低估的作用。\n\t一定要记住，日后在获得足够的声望还可以来我这里兑换装备。"					--完成任务npc说话的话
x256226_g_ContinueInfo="\t你不想兑换一件声望套装吗？"
x256226_g_MissionHelp =	""
x256226_g_DemandItem =	   {10014001,10024001,10034001,10044001,10054001,10064001,10074001,10084001,10094001,10104001,10114001,10124001,10234001,10234011,10234021,10234031,10234041,10234051,10254001,10254011,10254021,10254031,10254041,10254051,10274001,10274011,10274021,10274031,10274041,10274051}						
x256226_g_BonusMoney1 =0
x256226_g_BonusMoney2 =0
x256226_g_BonusMoney3 =0
x256226_g_BonusMoney4 =0
x256226_g_BonusMoney5 =0
x256226_g_BonusMoney6 =0
x256226_g_BonusItem	=	{}
x256226_g_BonusChoiceItem ={}
x256226_g_ExpBonus = 10200
x256226_g_NpcGUID ={{ guid = 138538, name = "声望商店"} }
--MisDescEnd
--**********************************
x256226_g_MaxLevel   = 40

function x256226_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    local level = GetLevel(sceneId, selfId)
	if level < x256226_g_LevelLess or level >= x256226_g_MaxLevel then
		return
	end



	if IsQuestHaveDone(sceneId, selfId, x256226_g_MissionId) > 0 then
		return 
	end
	
	if IsQuestHaveDone(sceneId, selfId, x256226_g_MissionIdPre)> 0 then 
	if IsHaveQuest(sceneId,selfId, x256226_g_MissionId) <= 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x256226_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x256226_g_MissionId, state, -1 )
	end
	end

end

function x256226_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x256226_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256226_g_ExpBonus )
		end
		if x256226_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256226_g_BonusMoney1 )
		end
		if x256226_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256226_g_BonusMoney2 )
		end
		if x256226_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256226_g_BonusMoney3 )
		end
		if x256226_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256226_g_BonusMoney4 )
		end
		if x256226_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256226_g_BonusMoney5 )
		end
		if x256226_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256226_g_BonusMoney6 )
		end
		for i, item in x256226_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	 	end
		for i, item in x256226_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  	end
end
--**********************************

function x256226_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x256226_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256226_g_MissionId) > 0 then
			if x256226_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x256226_g_MissionName)
				AddQuestText(sceneId,x256226_g_ContinueInfo)
				EndQuestEvent()
				DispatchQuestEventList(sceneId, selfId, NPCId, x256226_g_ScriptId, x256226_g_MissionId);
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x256226_g_MissionName)
				AddQuestText(sceneId,x256226_g_MissionCompleted)
				AddQuestText(sceneId," ")
				x256226_DispatchMissionInfo( sceneId, selfId, NPCId )
				EndQuestEvent()
				DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256226_g_ScriptId, x256226_g_MissionId);
			end
  elseif x256226_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  		AddQuestText(sceneId,"#Y"..x256226_g_MissionName)
			AddQuestText(sceneId,x256226_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x256226_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x256226_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x256226_g_MissionHelp )
			end
			x256226_DispatchMissionInfo( sceneId, selfId, NPCId )
	  		EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256226_g_ScriptId, x256226_g_MissionId);
  end
	
end
--**********************************

function x256226_ProcAcceptCheck(sceneId, selfId, NPCId)
		
	return 1
		

end
--**********************************
function x256226_CheckSubmit( sceneId, selfId, NPCId)  
                                                  
		if  IsHaveQuest(sceneId, selfId,x256226_g_MissionId) ~=1 then
			return 0
		end
		
	   	local 	misIndex = GetQuestIndexByID(sceneId, selfId,x256226_g_MissionId)                                                  
	   	if GetQuestParam(sceneId, selfId,misIndex,7,1) == 1 then
	   		return 1
	   	else 
	   		return 0
	   	end
	   	
	
end

--**********************************
function x256226_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256226_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256226_g_MissionId  )
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
		
		if x256226_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then

					local retmiss = AddQuest( sceneId, selfId, x256226_g_MissionId, x256226_g_ScriptId, 0, 0, 1,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x256226_Msg2toplayer( sceneId, selfId,0)
		  			
					for i, item in x256226_g_DemandItem do
						if GetItemCount(sceneId,selfId,x256226_g_DemandItem[i]) >= 1 then		
							local misIndex = GetQuestIndexByID(sceneId,selfId,x256226_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 32,0 )
								--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 33,0 )
						end
					end
					--x256226_ProcQuestItemChanged(sceneId, selfId, -1, MissionId)
					end
		  			
	 	end                                                                    
	     
end
--**********************************

function x256226_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256226_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x256226_g_MissionId)
	  x256226_Msg2toplayer( sceneId, selfId,1)
		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 32,0 )
		--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 33,0 )	
end
--**********************************
function x256226_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x256226_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x256226_g_BonusChoiceItem do
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
function x256226_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256226_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256226_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256226_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"背包空间不足，请清理后再来！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256226_g_MissionId) > 0 then
				x256226_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x256226_g_MissionId)
				x256226_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256226_g_BonusItem do
 						AddBindItem( sceneId, item.item, item.n )
				end
				for i, item in x256226_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256226_g_MissionIdNext )	
end

function x256226_GetBonus( sceneId, selfId,NpcID)
	  if x256226_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256226_g_ExpBonus);
  	end
		if x256226_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256226_g_BonusMoney1 )
	  end
		if x256226_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256226_g_BonusMoney2 )
	  end
		if x256226_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256226_g_BonusMoney3 )
		end
		if x256226_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256226_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256226_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256226_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256226_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256226_g_BonusMoney6)
		end
end

function x256226_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务："..x256226_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务："..x256226_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务："..x256226_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务："..x256226_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x256226_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x256226_g_MissionName.."！", 0, 3)
				if x256226_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x256226_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x256226_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x256226_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x256226_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x256226_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x256226_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x256226_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x256226_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x256226_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x256226_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x256226_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x256226_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x256226_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x256226_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x256226_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256226_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x256226_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256226_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId,optype)
	if	optype	==	0	then
		return
	end
	
	for i, item in x256226_g_DemandItem do
	
		if itemdataId == item then

			if GetItemCount(sceneId,selfId,item) >= 1 then
					local misIndex = GetQuestIndexByID(sceneId,selfId,x256226_g_MissionId)                                                  
		    		SetQuestByIndex(sceneId,selfId,misIndex,0,1)
		    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
		    		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 32,0 )
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 33,0 )
		  	else
		  			local misIndex = GetQuestIndexByID(sceneId,selfId,x256226_g_MissionId)                                                  
		    		SetQuestByIndex(sceneId,selfId,misIndex,0,0)
		    		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
		  	end
		  	
		  	break
	  	
	  	end
	  	
	end

end


function x256226_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x256226_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x256226_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x256226_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x256226_g_MissionId, state, -1 )
				if x256226_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 32,1 )
					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 33,0 )
				end	
		end
end

function x256226_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256226_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256226_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256226_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256226_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256226_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end