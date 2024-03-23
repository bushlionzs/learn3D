--酒后误事

--MisDescBegin
x203000_g_ScriptId = 203000
x203000_g_MissionIdPre =310
x203000_g_MissionId = 311
x203000_g_LevelLess	= 	40 
x203000_g_MissionIdNext = 312
x203000_g_DemandKill ={{id=1018,num=1}}
x203000_g_Name	={"耶律楚材"}
x203000_g_ExtTarget={{type=20,n=1,target="击败@npc_19021"}}
x203000_g_MissionName="【剧场】治国良材<二>"
x203000_g_MissionInfo="\t（耶律楚材只稍微看了看你的鞋子，冷笑道）钦差远从中都而来，为何衣衫却如此整洁？来人，抓刺客！"  --任务描述
x203000_g_MissionTarget=""		
x203000_g_MissionCompleted="\t你究竟何人？胆敢假冒天朝使者！"
x203000_g_ContinueInfo="你那小小伎俩也想瞒的过我？"
x203000_g_MissionHelp =	"#G如果您过久没有击败怪物，怪物会自行消失，您可以放弃并重新接取本任务。"
x203000_g_DemandItem ={}
x203000_g_ExpBonus = 93000
x203000_g_BonusMoney1 =295
x203000_g_BonusMoney2 =0
x203000_g_BonusMoney3 =0
x203000_g_BonusMoney4 =0
x203000_g_BonusMoney5 =51
x203000_g_BonusMoney6 =0
x203000_g_BonusItem	={}
x203000_g_BonusChoiceItem ={}
x203000_g_NpcGUID = 107008
x203000_g_Impact1 = 2092
x203000_g_npcid = 0
--MisDescEnd
--**********************************

function x203000_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    --DelQuest(sceneId, selfId, x203000_g_MissionId)
	if IsQuestHaveDone(sceneId, selfId, x203000_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203000_g_MissionIdPre)> 0 then 
						local state = GetQuestStateNM(sceneId,selfId,NPCId,x203000_g_MissionId)
						AddQuestTextNM( sceneId, selfId, NPCId, x203000_g_MissionId, state, -1 )
	end
end

function x203000_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203000_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203000_g_ExpBonus )
		end
		if x203000_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203000_g_BonusMoney1 )
		end
		if x203000_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203000_g_BonusMoney2 )
		end
		if x203000_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203000_g_BonusMoney3 )
		end
		if x203000_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203000_g_BonusMoney4 )
		end
		if x203000_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203000_g_BonusMoney5 )
		end
		if x203000_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203000_g_BonusMoney6 )
		end
		for i, item in x203000_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.id, item.num)
	  end
		for i, item in x203000_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

--任务入口函数

--**********************************
function x203000_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
    x203000_g_npcid =   NPCId
	if IsQuestHaveDone(sceneId, selfId, x203000_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203000_g_MissionId) > 0 then
			if x203000_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
            
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203000_g_MissionName)
						AddQuestText(sceneId,x203000_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203000_g_ScriptId, x203000_g_MissionId);
			else
          
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203000_g_MissionName)
						AddQuestText(sceneId,x203000_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203000_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203000_g_ScriptId, x203000_g_MissionId);
			end
  elseif x203000_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203000_g_MissionName)
			AddQuestText(sceneId,x203000_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x203000_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203000_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:")
				AddQuestText(sceneId,x203000_g_MissionHelp )
			end
			x203000_DispatchMissionInfo( sceneId, selfId, NPCId )
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203000_g_ScriptId, x203000_g_MissionId);
  end
end
--**********************************
function x203000_ProcAcceptCheck(sceneId, selfId, NPCId)
	if IsQuestHaveDone(sceneId, selfId, x203000_g_MissionId) > 0 then
		return 0
	elseif GetLevel(sceneId, selfId)< x203000_g_LevelLess then
		return 0
	end
	return 1
end
--**********************************
function x203000_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x203000_g_MissionId)
	if GetQuestParam(sceneId,selfId,misIndex,0) == x203000_g_DemandKill[1].num then
             
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	        return 1
	end
	return 0
end
--**********************************
function x203000_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203000_g_MissionId) > 0 then
				return 
		end
		--检查前置任务
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203000_g_MissionId  )
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
		if x203000_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203000_g_MissionId, x203000_g_ScriptId, 1, 0, 0)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			-- SendSpecificImpactToUnit(sceneId, selfId, selfId, NPCId, x203000_g_Impact1, 0)
            CreateMonster(sceneId, 1018,53,60,5,1,-1,-1,21,60000)
						x203000_Msg2toplayer( sceneId, selfId,0)
						local misIndex = GetQuestIndexByID(sceneId,selfId,x203000_g_MissionId)                                                  
	    			SetQuestByIndex(sceneId,selfId,misIndex,7,0)
		  		end
		  
          
	  end                                                                  
	     
end
--**********************************
function x203000_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203000_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203000_g_MissionId)
	  x203000_Msg2toplayer( sceneId, selfId,1)
end
--**********************************
function x203000_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x203000_g_BonusItem do
		AddItem( sceneId, item.id, item.num )
  end
  for j, item in x203000_g_BonusChoiceItem do
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
function x203000_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId)
	if IsHaveQuest(sceneId,selfId, x203000_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203000_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203000_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203000_g_MissionId) > 0 then
				x203000_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203000_g_MissionId)
                x203000_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203000_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203000_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		    end
    		    EndAddItem(sceneId,selfId)
				CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203000_g_MissionIdNext )	
   end
end

function x203000_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
   
end

function x203000_GetBonus( sceneId, selfId,NpcID)
	  if x203000_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203000_g_ExpBonus);
  	end
		if x203000_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203000_g_BonusMoney1 )
	  end
		if x203000_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203000_g_BonusMoney2 )
	  end
		if x203000_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203000_g_BonusMoney3 )
		end
		if x203000_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203000_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203000_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203000_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203000_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203000_g_BonusMoney6)
		end
end

function x203000_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x203000_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x203000_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203000_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203000_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203000_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203000_g_MissionName.."！", 0, 3)
				if x203000_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x203000_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x203000_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x203000_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x203000_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x203000_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x203000_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x203000_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x203000_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x203000_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x203000_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x203000_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x203000_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x203000_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

--**********************************

function x203000_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	if	objdataId ==x203000_g_DemandKill[1].id then
			local MissionId = x203000_g_MissionId
			local guid = GetMonsterGUID(sceneId, selfId)
			local x,z = GetWorldPos(sceneId,selfId)
			local Num =  GetNearPlayerCount(sceneId, selfId,x,z,5)  
			for i = 0, Num-1 do
				local humanObjId = GetNearPlayerMember(sceneId, selfId,i);
				if humanObjId >= 0 then
					if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
						if IsHaveQuestNM(sceneId, humanObjId, x203000_g_MissionId) == 1 then
	    	        local misIndex = GetQuestIndexByID( sceneId, humanObjId, MissionId)
		            SetQuestByIndex( sceneId, humanObjId, misIndex, 0, 1)
				        SetQuestByIndex( sceneId, humanObjId, misIndex, 7, 1)
				        Msg2Player( sceneId, humanObjId, format("击败虎刀侍卫   %d/1", GetQuestParam(sceneId,humanObjId,misIndex,0)), 8, 3)
				        Msg2Player( sceneId, humanObjId, format("击败虎刀侍卫   %d/1", GetQuestParam(sceneId,humanObjId,misIndex,0)), 8, 2)
				 		end
			    end
				end
			end
	end 
end
--**********************************
function x203000_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203000_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203000_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203000_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203000_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203000_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203000_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203000_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203000_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203000_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end





