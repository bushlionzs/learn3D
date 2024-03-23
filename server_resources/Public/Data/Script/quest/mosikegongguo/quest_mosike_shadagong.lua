--【主线】击败莫斯科大公

--MisDescBegin
x203330_g_ScriptId = 203330
x203330_g_MissionIdPre = {825,826}
x203330_g_MissionId = 827
x203330_g_LevelLess	= 	88 
x203330_g_MissionIdNext = 828
x203330_g_Name	={}
x203330_g_ExtTarget={{type=20,n=1,target="击败@npc_117006"}}
x203330_g_MissionName="【剧场】罪魁祸首的覆灭"
x203330_g_MissionInfo="\t我们现在已经尽数消灭了莫斯科大公的党羽和部队，现在正是我们动手收拾这个阴谋家的时候了。"  --任务描述
x203330_g_MissionTarget=""		
x203330_g_MissionCompleted="\t哈哈哈，我们的西征之路的第一步竟然能够兵不血刃，真是没有想到。"					--完成任务npc说话的话
x203330_g_ContinueInfo="\t别让那个阴险的家伙逃走。"
x203330_g_MissionHelp =	""
x203330_g_DemandItem ={}
x203330_g_ExpBonus = 684000
x203330_g_BonusMoney1 =880
x203330_g_BonusMoney2 =0
x203330_g_BonusMoney3 =0
x203330_g_BonusMoney4 =0
x203330_g_BonusMoney5 =106
x203330_g_BonusMoney6 =0
x203330_g_BonusItem	=	{}
x203330_g_BonusChoiceItem ={}
x203330_g_NpcGUID ={{guid=117006,name ="莫斯科大公"}}
--MisDescEnd
--**********************************

function x203330_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if IsQuestHaveDone(sceneId, selfId, x203330_g_MissionId) > 0 then
		return 
	else
	if IsQuestHaveDone(sceneId, selfId, x203330_g_MissionIdPre[1])> 0 then
	  if IsQuestHaveDone(sceneId, selfId, x203330_g_MissionIdPre[2])> 0 then
	   local state = GetQuestStateNM(sceneId,selfId,NPCId,x203330_g_MissionId)
	   AddQuestTextNM( sceneId, selfId, NPCId, x203330_g_MissionId, state, -1 )
	  end
	end
 end
end

function x203330_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203330_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203330_g_ExpBonus )
		end
		if x203330_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203330_g_BonusMoney1 )
		end
		if x203330_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203330_g_BonusMoney2 )
		end
		if x203330_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203330_g_BonusMoney3 )
		end
		if x203330_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203330_g_BonusMoney4 )
		end
		if x203330_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203330_g_BonusMoney5 )
		end
		if x203330_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203330_g_BonusMoney6 )
		end
		for i, item in x203330_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203330_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203330_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本

	if IsQuestHaveDone(sceneId, selfId, x203330_g_MissionId) > 0 then
		return 
	end
	if which == -1 then
		if IsHaveQuest(sceneId,selfId, x203330_g_MissionId) > 0 then
			if x203330_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203330_g_MissionName)
						AddQuestText(sceneId,x203330_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203330_g_ScriptId, x203330_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203330_g_MissionName)
						AddQuestText(sceneId,x203330_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203330_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203330_g_ScriptId, x203330_g_MissionId);
			end
		elseif x203330_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203330_g_MissionName)
			AddQuestText(sceneId,x203330_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x203330_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203330_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x203330_g_MissionHelp )
			end
			x203330_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203330_g_ScriptId, x203330_g_MissionId);
  	end
	elseif which == 1 then
			SetMonsterCamp(sceneId,NPCId,21)
			NpcTalk(sceneId, NPCId, "既然事已败漏，只好和你拼个鱼死网破！", -1)
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t莫斯科大公突然露出一副凶恶的嘴脸，向你冲来！")
			EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId, x203330_g_ScriptId, x203330_g_MissionId);
	--elseif which == 2 then
	--		BeginQuestEvent(sceneId)
	--		AddQuestText(sceneId,"\t回施主下句是“空即是色”")
	--		EndQuestEvent()
	--		DispatchQuestEventList(sceneId, selfId, NPCId, x203330_g_ScriptId, x203330_g_MissionId);
	end
  
end
--**********************************

function x203330_ProcAcceptCheck(sceneId, selfId, NPCId)
		--if IsQuestHaveDone(sceneId, selfId, x203330_g_MissionIdPre)> 0 then
					return 1
		--end
		--return 0

end
--**********************************
function x203330_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId,selfId,x203330_g_MissionId)
			if GetQuestParam(sceneId,selfId,misIndex,0) >= 1 then
					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    		return 1
	    end
	 		return 0
end
--**********************************
function x203330_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203330_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203330_g_MissionId  )
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
		if x203330_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203330_g_MissionId, x203330_g_ScriptId, 1, 0, 0, 1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x203330_Msg2toplayer( sceneId, selfId,0)
		  		end
	 	end                                                                    
	     
end
--**********************************

function x203330_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203330_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203330_g_MissionId)
	  x203330_Msg2toplayer( sceneId, selfId,1)
	  for i, item in x203330_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
		end
end
--**********************************
function x203330_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x203330_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203330_g_BonusChoiceItem do
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
function x203330_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203330_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203330_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203330_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203330_g_MissionId) > 0 then
				x203330_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203330_g_MissionId)		--完成任务的判断
				x203330_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203330_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203330_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		for i, item in x203330_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
				end
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203330_g_MissionIdNext )	
end

function x203330_GetBonus( sceneId, selfId,NpcID)
	  if x203330_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203330_g_ExpBonus);
  	end
		if x203330_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203330_g_BonusMoney1 )
	  end
		if x203330_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203330_g_BonusMoney2 )
	  end
		if x203330_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203330_g_BonusMoney3 )
		end
		if x203330_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203330_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203330_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203330_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203330_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203330_g_BonusMoney6)
		end
end

function x203330_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x203330_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x203330_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203330_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203330_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203330_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203330_g_MissionName.."！", 0, 3)
				if x203330_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x203330_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x203330_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x203330_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x203330_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x203330_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x203330_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x203330_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x203330_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x203330_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x203330_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x203330_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x203330_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x203330_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x203330_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	if	objdataId ==2107 then
	 local KilledNum = GetMonsterOwnerCount( sceneId, objId ) --取得这个怪物死后拥有分配权的人数
		for i = 0, KilledNum-1 do
			local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --取得拥有分配权的人的objId
            if humanObjId ~= -1 then
                 if IsHaveQuest(sceneId,humanObjId, x203330_g_MissionId) > 0 then
                    local misIndex = GetQuestIndexByID(sceneId,humanObjId,x203330_g_MissionId)
										if GetQuestParam(sceneId,humanObjId,misIndex,0) < 1 then
												SetQuestByIndex(sceneId,humanObjId,misIndex,0,GetQuestParam(sceneId,humanObjId,misIndex,0)+1)
												Msg2Player(sceneId, humanObjId, format("击败莫斯科大公   %d/1", GetQuestParam(sceneId,humanObjId,misIndex,0)), 0, 3)
												x203330_CheckSubmit( sceneId, humanObjId)
										end
                end
            end
		end
	end
end


function x203330_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203330_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203330_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203330_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203330_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
		--if IsHaveQuest(sceneId,selfId, x203330_g_MissionId) > 0 then
		--	
		--		if npcGuid == x203330_g_NpcGUID.guid then	
		--			local misIndex = GetQuestIndexByID(sceneId,selfId,x203330_g_MissionId)
					--if GetQuestParam(sceneId,selfId,misIndex,0) ==0 then 
				--   AddQuestNumText(sceneId, x203330_g_MissionId, "请列位功臣举起手中金杯",0,1)
					
			--	elseif npcGuid == x203330_g_NpcGUID[2].guid then
			--	local state = GetQuestStateNM(sceneId,selfId,npcId,x203330_g_MissionId)
			--	AddQuestTextNM( sceneId, selfId, npcId, x203330_g_MissionId, state, -1 )                    --get任务的状态作出显示的判断
	--		end
	--	end
   local bFind  = 0
  for i ,item in x203330_g_NpcGUID do
     if item.guid == npcGuid then
    		if IsHaveQuest(sceneId,selfId, x203330_g_MissionId) > 0 then 
    		AddQuestTextNM( sceneId, selfId, npcId, x200502_g_MissionId, state, -1 )
  				--AddQuestNumText(sceneId, x203330_g_MissionId, "你的阴谋已经败露了，束手就擒吧！",0, 1)   
  			 end
         bFind = 1
         break
     end
  end
    if bFind == 0 then   
     return
    end
		
		
end

function x203330_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203330_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203330_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203330_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203330_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203330_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
