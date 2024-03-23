--【主线】光荣之箭

--MisDescBegin
x256108_g_ScriptId = 256108
x256108_g_MissionIdPre =427
x256108_g_MissionId = 434
x256108_g_LevelLess	= 	55
x256108_g_Name	={}
x256108_g_ExtTarget={{type=20,n=1,target="将光荣神箭交给@npc_109021，回到王城。"}}
x256108_g_MissionName="【剧场】光荣神箭"
x256108_g_MissionInfo="\t如今我们灭亡了金朝，为了便于统治中原，我们要实行汉化统治，四处网罗人才，并减轻赋税，使国家和军队有充足的物资供应。"  --任务描述
x256108_g_MissionTarget=""		
x256108_g_MissionCompleted="\t世间从不少以弱胜强的实例，而从作为金朝藩属到亲手埋葬金朝，成吉思汗再一次证明，唯有人可以与天争。能正确运用各种战术，并对敌人分化瓦解，这是成吉思汗灭亡金朝的原因。"					--完成任务npc说话的话
x256108_g_ContinueInfo="\t风烛残年的金帝国，只剩最后一口气苟延残喘，现在，终结这个王朝吧！"
x256108_g_MissionHelp =	""
x256108_g_DemandItem ={{id=13020019,num=1}}
x256108_g_ExpBonus = 1200000
x256108_g_BonusMoney1 =1000
x256108_g_BonusMoney2 =0
x256108_g_BonusMoney3 =0
x256108_g_BonusMoney4 =0
x256108_g_BonusMoney5 =66
x256108_g_BonusMoney6 =0
x256108_g_BonusItem	=	{{item=11050002,n=20}}
x256108_g_BonusChoiceItem ={}
x256108_g_NpcGUID ={{ guid = 109021, name = "钥匙老人"}}
--MisDescEnd
--**********************************

function x256108_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if IsQuestHaveDone(sceneId, selfId, x256108_g_MissionId) > 0 then
		return 
	end
		if IsHaveQuest(sceneId,selfId, x256108_g_MissionId) > 0 then
	return 
	end	
	if GetLevel(sceneId, selfId) >= x256108_g_LevelLess then
		if IsQuestHaveDone(sceneId, selfId, x256108_g_MissionIdPre)> 0 then
	   	if IsHaveQuest(sceneId,selfId, x256108_g_MissionId) <= 0 then
				local state = GetQuestStateNM(sceneId,selfId,NPCId,x256108_g_MissionId)
				AddQuestTextNM( sceneId, selfId, NPCId, x256108_g_MissionId, state, -1 )
			end
		end
	end
end

function x256108_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x256108_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256108_g_ExpBonus )
		end
		if x256108_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256108_g_BonusMoney1 )
		end
		if x256108_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256108_g_BonusMoney2 )
		end
		if x256108_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256108_g_BonusMoney3 )
		end
		if x256108_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256108_g_BonusMoney4 )
		end
		if x256108_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256108_g_BonusMoney5 )
		end
		if x256108_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256108_g_BonusMoney6 )
		end
		for i, item in x256108_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x256108_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x256108_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x256108_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256108_g_MissionId) > 0 then
			if x256108_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256108_g_MissionName)
						AddQuestText(sceneId,x256108_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x256108_g_ScriptId, x256108_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256108_g_MissionName)
						AddQuestText(sceneId,x256108_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x256108_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256108_g_ScriptId, x256108_g_MissionId);
			end
  elseif x256108_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x256108_g_MissionName)
			AddQuestText(sceneId,x256108_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x256108_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x256108_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x256108_g_MissionHelp )
			end
			x256108_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256108_g_ScriptId, x256108_g_MissionId);
  end
	
end
--**********************************

function x256108_ProcAcceptCheck(sceneId, selfId, NPCId)
		--if IsQuestHaveDone(sceneId, selfId, x256108_g_MissionIdPre)> 0 then
					return 1
		--end
		--return 0

end
--**********************************
function x256108_CheckSubmit( sceneId, selfId, NPCId)
		if GetItemCount(sceneId,selfId,x256108_g_DemandItem[1].id) >= x256108_g_DemandItem[1].num then
					local misIndex = GetQuestIndexByID(sceneId,selfId,x256108_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    		return 1
	  else
	  			local misIndex = GetQuestIndexByID(sceneId,selfId,x256108_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,0)
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	  end
	  return 0
	
end
--**********************************
function x256108_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256108_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256108_g_MissionId  )
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
		
		
		if x256108_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x256108_g_MissionId, x256108_g_ScriptId, 1, 0, 0, 1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x256108_Msg2toplayer( sceneId, selfId,0)
		  			x256108_ProcQuestItemChanged(sceneId, selfId, -1, MissionId)
						if x256108_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x256108_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x256108_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256108_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x256108_g_MissionId)
	  x256108_Msg2toplayer( sceneId, selfId,1)
end
--**********************************
function x256108_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x256108_g_BonusItem do
		AddBindItem( sceneId, item.item, item.n )
  end
  for j, item in x256108_g_BonusChoiceItem do
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
function x256108_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256108_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256108_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256108_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256108_g_MissionId) > 0 then
				x256108_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x256108_g_MissionId)
				x256108_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256108_g_BonusItem do
 						AddBindItem( sceneId, item.item, item.n )
				end
				for i, item in x256108_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddBindItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		for i, item in x256108_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
				end
    		AddItemListToPlayer(sceneId,selfId)
   end
end

function x256108_GetBonus( sceneId, selfId,NpcID)
	  if x256108_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256108_g_ExpBonus);
  	end
		if x256108_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256108_g_BonusMoney1 )
	  end
		if x256108_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256108_g_BonusMoney2 )
	  end
		if x256108_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256108_g_BonusMoney3 )
		end
		if x256108_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256108_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256108_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256108_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256108_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256108_g_BonusMoney6)
		end
end

function x256108_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x256108_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x256108_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x256108_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x256108_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x256108_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x256108_g_MissionName.."！", 0, 3)
				if x256108_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x256108_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x256108_g_BonusMoney1 > 0 then
					local money =x256108_g_BonusMoney1
	  		  Msg2Player( sceneId, selfId, format( "#Y获得#R银卡#{_MONEY%d}#cffcf00#Y的奖励", money).."。", 8, 2)
	  		end
				if x256108_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x256108_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x256108_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x256108_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x256108_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x256108_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x256108_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x256108_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x256108_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x256108_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x256108_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x256108_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256108_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x256108_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256108_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
		if GetItemCount(sceneId,selfId,x256108_g_DemandItem[1].id) >= x256108_g_DemandItem[1].num then
					local misIndex = GetQuestIndexByID(sceneId,selfId,x256108_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,GetItemCount(sceneId,selfId,x256108_g_DemandItem[1].id))
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	  else
	  			local misIndex = GetQuestIndexByID(sceneId,selfId,x256108_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,GetItemCount(sceneId,selfId,x256108_g_DemandItem[1].id))
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	  end
end


function x256108_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
local bFind  = 0
    for i ,item in x256108_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x256108_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x256108_g_MissionId)        ---取得任务状态 ，根据状态添加按钮 AddQuestTextNM
				AddQuestTextNM( sceneId, selfId, npcId, x256108_g_MissionId, state, -1 )
		end
end

function x256108_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256108_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256108_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256108_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256108_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256108_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end