--【剧场】三头妖龙

--MisDescBegin
x203311_g_ScriptId = 203311
x203311_g_MissionIdPre ={613,614,615}
x203311_g_MissionId = 619
x203311_g_LevelLess	= 	65 
x203311_g_MissionIdNext = 621
x203311_g_Name	={}
x203311_g_ExtTarget={{type=20,n=1,target="到@npc_113120处招出并消灭@npc_113115"}}
x203311_g_MissionName="【剧场】三头魔龙"
x203311_g_MissionInfo="\t太好了，金火水三龙之魂都已经拿到了，只要把它们放在一起就会自动融合成龙之精华，带着龙之精华到东南面开阔地带召唤出那条魔龙，在他还没有完全恢复妖力之前，除掉他，快！"  --任务描述
x203311_g_MissionTarget=""		
x203311_g_MissionCompleted="\t太好了，终于除掉了这头魔龙，希望长生天保佑旭烈兀安答平安无事。"					--完成任务npc说话的话
x203311_g_ContinueInfo="\t除掉那条三头魔龙！"
x203311_g_MissionHelp =	""
x203311_g_DemandItem ={{id=13020433,num=1}}
x203311_g_ExpBonus = 248000
x203311_g_BonusMoney1 =650
x203311_g_BonusMoney2 =0
x203311_g_BonusMoney3 =0
x203311_g_BonusMoney4 =0
x203311_g_BonusMoney5 =76
x203311_g_BonusMoney6 =0
x203311_g_BonusItem	=	{}
x203311_g_BonusChoiceItem ={}

x203311_g_NpcGUID ={ }
x203311_g_long = -1
--MisDescEnd
--**********************************

function x203311_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x203311_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203311_g_MissionIdPre[1])> 0  and IsQuestHaveDone(sceneId, selfId, x203311_g_MissionIdPre[2])> 0  and IsQuestHaveDone(sceneId, selfId, x203311_g_MissionIdPre[3])> 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x203311_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x203311_g_MissionId, state, -1 )
	end
end

function x203311_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203311_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203311_g_ExpBonus )
		end
		if x203311_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203311_g_BonusMoney1 )
		end
		if x203311_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203311_g_BonusMoney2 )
		end
		if x203311_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203311_g_BonusMoney3 )
		end
		if x203311_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203311_g_BonusMoney4 )
		end
		if x203311_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203311_g_BonusMoney5 )
		end
		if x203311_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203311_g_BonusMoney6 )
		end
		for i, item in x203311_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203311_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203311_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x203311_g_MissionId) > 0 then
		return 
	end
	if which == -1 then
		if IsHaveQuest(sceneId,selfId, x203311_g_MissionId) > 0 then
			if x203311_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203311_g_MissionName)
						AddQuestText(sceneId,x203311_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203311_g_ScriptId, x203311_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203311_g_MissionName)
						AddQuestText(sceneId,x203311_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203311_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203311_g_ScriptId, x203311_g_MissionId);
			end
		elseif x203311_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203311_g_MissionName)
			AddQuestText(sceneId,x203311_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x203311_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203311_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x203311_g_MissionHelp )
			end
			x203311_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203311_g_ScriptId, x203311_g_MissionId);
  	end
  end
  
end
--**********************************

function x203311_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x203311_g_MissionIdPre[1])> 0 then
			if IsQuestHaveDone(sceneId, selfId, x203311_g_MissionIdPre[2])> 0 then
			if IsQuestHaveDone(sceneId, selfId, x203311_g_MissionIdPre[3])> 0 then
					return 1
			end
		end
		end
		return 0

end
--**********************************
function x203311_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId,selfId,x203311_g_MissionId)
			if GetQuestParam(sceneId,selfId,misIndex,0) >= 1 then
					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    		return 1
	    end
	 		return 0
end
--**********************************
function x203311_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203311_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203311_g_MissionId  )
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
		if x203311_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginAddItem(sceneId)                                                    
			AddItem( sceneId,x203311_g_DemandItem[1].id, x203311_g_DemandItem[1].num )             
			local ret = EndAddItem(sceneId,selfId)                                 
	  		if ret > 0 then
	  			local retmiss = AddQuest( sceneId, selfId, x203311_g_MissionId, x203311_g_ScriptId, 1, 0, 0)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x203311_Msg2toplayer( sceneId, selfId,0)
						AddItemListToPlayer(sceneId,selfId) 
		  		end
	  		else                                                             
		  		BeginQuestEvent(sceneId)                                      
		  		AddQuestText(sceneId,"物品栏已满，请整理下再来！")                    
		  		EndQuestEvent(sceneId)                                        
		  		DispatchQuestTips(sceneId,selfId)                      
	   		end        
	 	end                                                                    
	     
end
--**********************************

function x203311_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203311_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203311_g_MissionId)
	  x203311_Msg2toplayer( sceneId, selfId,1)
	  for i, item in x203311_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
		end
end
--**********************************
function x203311_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x203311_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203311_g_BonusChoiceItem do
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
function x203311_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203311_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203311_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203311_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203311_g_MissionId) > 0 then
				x203311_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203311_g_MissionId)
				x203311_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203311_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203311_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		for i, item in x203311_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
				end
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203311_g_MissionIdNext )	
end

function x203311_GetBonus( sceneId, selfId,NpcID)
	  if x203311_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203311_g_ExpBonus);
  	end
		if x203311_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203311_g_BonusMoney1 )
	  end
		if x203311_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203311_g_BonusMoney2 )
	  end
		if x203311_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203311_g_BonusMoney3 )
		end
		if x203311_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203311_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203311_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203311_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203311_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203311_g_BonusMoney6)
		end
end

function x203311_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x203311_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x203311_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203311_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203311_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203311_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203311_g_MissionName.."！", 0, 3)
				if x203311_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x203311_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x203311_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x203311_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x203311_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x203311_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x203311_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x203311_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x203311_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x203311_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x203311_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x203311_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x203311_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x203311_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x203311_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	if	objdataId ==1714 then
	 local KilledNum = GetMonsterOwnerCount( sceneId, objId ) --取得这个怪物死后拥有分配权的人数
		for i = 0, KilledNum-1 do
			local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --取得拥有分配权的人的objId
            if humanObjId ~= -1 then
                 if IsHaveQuest(sceneId,humanObjId, x203311_g_MissionId) > 0 then
                    local misIndex = GetQuestIndexByID(sceneId,humanObjId,x203311_g_MissionId)
										if GetQuestParam(sceneId,humanObjId,misIndex,0) < 1 then
												SetQuestByIndex(sceneId,humanObjId,misIndex,0,GetQuestParam(sceneId,humanObjId,misIndex,0)+1)
												Msg2Player(sceneId, humanObjId, format("您击毙三头魔龙   %d/1", GetQuestParam(sceneId,humanObjId,misIndex,0)), 0, 3)
												x203311_CheckSubmit( sceneId, humanObjId)
										end
                end
            end
		end
	end
end

function x203311_useitem(sceneId,selfId)
		local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )
		local misIndex = GetQuestIndexByID(sceneId,selfId,x203311_g_MissionId)
		if GetQuestParam(sceneId,selfId,misIndex,1) == 0 then
				local distanceRet = 25 - (169 - PlayerPosX) * (169 - PlayerPosX) - (221 - PlayerPosZ) * (221 - PlayerPosZ)
				if distanceRet >= 0 then
					if IsObjValid (sceneId,x203311_g_long) == 0 then
							DelItem( sceneId,selfId,x203311_g_DemandItem[1].id, x203311_g_DemandItem[1].num )
							x203311_g_long=CreateMonster(sceneId, 1714,169,221,5,1,-1,-1,21,180000,45,"三头魔龙")
							return 1
					elseif IsObjValid (sceneId,x203311_g_long) == 1 then
							if GetName(sceneId,x203311_g_long)~="三头魔龙" then
									DelItem( sceneId,selfId,x203311_g_DemandItem[1].id, x203311_g_DemandItem[1].num )
									x203311_g_long=CreateMonster(sceneId, 1714,169,221,5,1,-1,-1,21,180000,45,"三头魔龙")
									return 1
							end
					else
							Msg2Player(sceneId, selfId, "你暂时无法这样做！", 0, 3)
					end
				else
						Msg2Player(sceneId, selfId, "这里无法使用这个物品", 0, 3)
						return 0
				end
		end
end


function x203311_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203311_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203311_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203311_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203311_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	 
end

function x203311_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203311_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203311_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203311_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203311_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203311_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
