--【新手】小试身手

--MisDescBegin
x256240_g_ScriptId = 256240
x256240_g_MissionIdPre = 3046
x256240_g_MissionId = 3005
x256240_g_LevelLess	= 	1 
x256240_g_MissionIdNext = 3006
x256240_g_Name	={}
x256240_g_ExtTarget={{type=20,n=5,target="消灭5只@npc_80000"}}
x256240_g_MissionName="【新手】小试身手"
x256240_g_MissionInfo="\t村口最近不知为什么多了很多可恶的狐狸，虽然它们并不会拿羊儿们当作食物，可是它们身上的骚味却令那些可怜的羔羊寝食难安。\n\t想办法赶走它们，如果它们能够懂得什么叫做“杀一儆百”这个道理，事情就会好办得多。"  --任务描述
x256240_g_MissionTarget=""		
x256240_g_MissionCompleted="\t真没想到你这么快就回来了！怎么？你没有顺手带点狐皮回来么？那真可惜了，它们的皮可是上等的御寒材料。\n\t不过，我们的那些羊群今晚上看来能睡个好觉了，哈哈哈。"					--完成任务npc说话的话
x256240_g_ContinueInfo="\t赶走那些狐狸了吗？"
x256240_g_MissionHelp =	""
x256240_g_DemandItem ={}
x256240_g_BonusMoney1 =55
x256240_g_BonusMoney2 =0
x256240_g_BonusMoney3 =0
x256240_g_BonusMoney4 =0
x256240_g_BonusMoney5 =12
x256240_g_BonusMoney6 =0
x256240_g_BonusItem	=	{{item=10261001,n=1}}
x256240_g_BonusChoiceItem ={}
x256240_g_ExpBonus = 163
--x256240_g_doing = 0
--x256240_g_sunfeihu = -1
--x256240_g_zhangsheng = -1
--x256240_g_huwei1 = -1
--x256240_g_huwei2 = -1
x256240_g_NpcGUID ={{ guid = 138004, name = "苍狼长老"}}
--x256240_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
--MisDescEnd
--**********************************

function x256240_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 11,0 ) 
	if IsQuestHaveDone(sceneId, selfId, x256240_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x256240_g_MissionIdPre)> 0 then
		if IsHaveQuest(sceneId,selfId, x256240_g_MissionId) <= 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x256240_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x256240_g_MissionId, state, -1 )
		end
	end
end

function x256240_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x256240_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256240_g_ExpBonus )
		end
		if x256240_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256240_g_BonusMoney1 )
		end
		if x256240_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256240_g_BonusMoney2 )
		end
		if x256240_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256240_g_BonusMoney3 )
		end
		if x256240_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256240_g_BonusMoney4 )
		end
		if x256240_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256240_g_BonusMoney5 )
		end
		if x256240_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256240_g_BonusMoney6 )
		end
		for i, item in x256240_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x256240_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x256240_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x256240_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256240_g_MissionId) > 0 then
			if x256240_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256240_g_MissionName)
						AddQuestText(sceneId,x256240_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x256240_g_ScriptId, x256240_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256240_g_MissionName)
						AddQuestText(sceneId,x256240_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x256240_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256240_g_ScriptId, x256240_g_MissionId);
			end
  elseif x256240_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x256240_g_MissionName)
			AddQuestText(sceneId,x256240_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")  
			for i, item in x256240_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x256240_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x256240_g_MissionHelp )
			end
			x256240_DispatchMissionInfo( sceneId, selfId, NPCId )
		  CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,0 ) 	
			CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 21,1 ) 
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256240_g_ScriptId, x256240_g_MissionId);
  end
	
end
--**********************************

function x256240_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x256240_g_MissionIdPre)> 0 then
			return 1
	end
		return 0

end
--**********************************
function x256240_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId, selfId, x256240_g_MissionId)
		if GetQuestParam(sceneId,selfId,misIndex,0) ==5 then 
				
	        return 1
	  end
	  return 0
	
end
--**********************************
function x256240_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256240_g_MissionId) > 0 then
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
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256240_g_MissionId  )
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
   	if x256240_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
   				local retmiss = AddQuest( sceneId, selfId, x256240_g_MissionId, x256240_g_ScriptId, 1, 0, 0,1)
   				if retmiss ==0 then
   					Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
   					return 0
   				else
   	  			x256240_Msg2toplayer( sceneId, selfId,0)
   	  		end
    	end                                                                    
	     
end
--**********************************                  

function x256240_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256240_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x256240_g_MissionId)
	  x256240_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x256240_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x256240_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x256240_g_BonusChoiceItem do
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
function x256240_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256240_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256240_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256240_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256240_g_MissionId) > 0 then
				x256240_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x256240_g_MissionId)
				x256240_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256240_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x256240_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end  
    		 AddItemListToPlayer(sceneId,selfId)
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end 
  -- CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 19,1 )    
   CallScriptFunction( 203434, "ProcEventEntry", sceneId, selfId, NPCId, x256240_g_MissionIdNext )	
end

function x256240_GetBonus( sceneId, selfId,NpcID)
	  if x256240_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256240_g_ExpBonus);
  	end
		if x256240_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256240_g_BonusMoney1 )
	  end
		if x256240_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256240_g_BonusMoney2 )
	  end
		if x256240_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256240_g_BonusMoney3 )
		end
		if x256240_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256240_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256240_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256240_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256240_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256240_g_BonusMoney6)
		end
end

function x256240_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x256240_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x256240_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x256240_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x256240_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x256240_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x256240_g_MissionName.."！", 0, 3)
				if x256240_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x256240_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x256240_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x256240_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x256240_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x256240_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x256240_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x256240_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x256240_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x256240_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x256240_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x256240_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x256240_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x256240_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x256240_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	if	objdataId ==1830 then
	 local KilledNum = GetMonsterOwnerCount( sceneId, objId ) --取得这个怪物死后拥有分配权的人数
		for i = 0, KilledNum-1 do
			local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --取得拥有分配权的人的objId
            if humanObjId ~= -1 then
                 if IsHaveQuest(sceneId,humanObjId, x256240_g_MissionId) > 0 then
                    local misIndex = GetQuestIndexByID(sceneId,humanObjId,x256240_g_MissionId)
										if GetQuestParam(sceneId,humanObjId,misIndex,0) < 5 then
												SetQuestByIndex(sceneId,humanObjId,misIndex,0,GetQuestParam(sceneId,humanObjId,misIndex,0)+1)	
												CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, humanObjId, 21,0 ) 
												CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, humanObjId, 17,1 ) 
												Msg2Player(sceneId, humanObjId, format("消灭狐狸   %d/5", GetQuestParam(sceneId,humanObjId,misIndex,0)), 0, 3)
												x256240_CheckSubmit( sceneId, humanObjId)
										end
										if GetQuestParam(sceneId,humanObjId,misIndex,0) == 5 then
															SetQuestByIndex(sceneId,humanObjId,misIndex,7,1)
															SetQuestByIndex(sceneId,humanObjId,misIndex,0,5)	
										CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, humanObjId, 17,0 ) 												
										CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, humanObjId, 1,1 ) 						
										end
                end
            end
		end
	end
end


function x256240_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	--if IsHaveQuest(sceneId,selfId, x256240_g_MissionId) > 0 then
	--	if x256240_g_doing == 0 then
	--		if x256240_CheckSubmit(sceneId, selfId) <= 0 then
	--			--if GetName(sceneId,x256240_g_sunfeihu)~="孙飞虎" then
	--					x256240_g_PROTECTINFO.StartTime = GetCurrentTime()
	--					x256240_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 256240, "OnScneneTimer", 1)
	--					if x256240_g_PROTECTINFO.ScneneTimerIndex >= 0 then
	--							x256240_g_doing = 1
	--							x256240_g_sunfeihu=CreateMonster(sceneId, 1617,155,475,5,1,-1,-1,20,80000,180,"孙飞虎")
	--							x256240_g_huwei1=CreateMonster(sceneId, 1618,151,477,3,1,-1,-1,20,80000,180,"护卫")
	--							x256240_g_huwei2=CreateMonster(sceneId, 1618,151,473,3,1,-1,-1,20,80000,180,"护卫")
	--							if IsObjValid (sceneId,x256240_g_sunfeihu) == 1 then
	--									SetPatrolId(sceneId, x256240_g_sunfeihu, 49)
	--							end
	--							if IsObjValid (sceneId,x256240_g_huwei1) == 1 then
	--									SetPatrolId(sceneId, x256240_g_huwei1, 50)
	--							end
	--							if IsObjValid (sceneId,x256240_g_huwei2) == 1 then
	--									SetPatrolId(sceneId, x256240_g_huwei2, 51)
	--							end
	--					end
	--			--end
	--		end
	--	end
	--end

end

function x256240_ProcTiming(sceneId, selfId, ScriptId, MissionId)

end

function x256240_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)

end

function x256240_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x256240_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x256240_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x256240_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x256240_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x256240_g_MissionId, state, -1 )
		end
end

function x256240_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256240_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256240_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256240_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256240_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256240_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x256240_OnScneneTimer(sceneId)
--if x256240_g_doing==1   then
--	if GetCurrentTime() - x256240_g_PROTECTINFO.StartTime >= 3   then
--					x256240_g_doing = 2
--					if IsObjValid (sceneId,x256240_g_sunfeihu) == 1 then
--							NpcTalk(sceneId, x256240_g_sunfeihu, "你说刚才那姑娘来了没？", -1)
--					end
--	end
--elseif x256240_g_doing==2   then
--	if GetCurrentTime() - x256240_g_PROTECTINFO.StartTime >= 6   then
--					x256240_g_doing = 3
--					if IsObjValid (sceneId,x256240_g_huwei1) == 1 then
--							NpcTalk(sceneId, x256240_g_huwei1, "看她刚才是吓傻了，没准跑了吧！", -1)
--					end
--	end
--elseif x256240_g_doing==3   then
--	if GetCurrentTime() - x256240_g_PROTECTINFO.StartTime >= 9   then
--					x256240_g_doing = 4
--					if IsObjValid (sceneId,x256240_g_sunfeihu) == 1 then
--							NpcTalk(sceneId, x256240_g_sunfeihu, "往哪里跑？跑到天边我也能抓回来！", -1)
--					end
--	end
--elseif x256240_g_doing==4   then
--	if GetCurrentTime() - x256240_g_PROTECTINFO.StartTime >= 12   then
--					x256240_g_doing = 5
--					if IsObjValid (sceneId,x256240_g_huwei2) == 1 then
--							NpcTalk(sceneId, x256240_g_huwei2, "没准看上孙将军英明神武自己颠颠过来了！", -1)
--					end
--	end
--elseif x256240_g_doing==5   then
--	if GetCurrentTime() - x256240_g_PROTECTINFO.StartTime >= 14   then
--					x256240_g_doing = 6
--					if IsObjValid (sceneId,x256240_g_sunfeihu) == 1 then
--							NpcTalk(sceneId, x256240_g_sunfeihu, "哈哈哈哈", -1)
--					end
--					if IsObjValid (sceneId,x256240_g_huwei1) == 1 then
--							NpcTalk(sceneId, x256240_g_huwei1, "哈哈哈哈", -1)
--					end
--					x256240_g_zhangsheng=CreateMonster(sceneId, 1621,166,458,3,1,-1,-1,20,30000,0,"崔莺莺","张生扮")
--	end
--elseif x256240_g_doing==6   then
--	if GetCurrentTime() - x256240_g_PROTECTINFO.StartTime >= 16   then
--					x256240_g_doing = 7
--					if IsObjValid (sceneId,x256240_g_huwei1) == 1 then
--							NpcTalk(sceneId, x256240_g_huwei1, "诶，这不是来了？", -1)
--					end
--					if IsObjValid (sceneId,x256240_g_huwei1) == 1 then
--							SetMonsterDir(sceneId,x256240_g_huwei1,180)
--					end
--	end
--elseif x256240_g_doing==7   then
--	if GetCurrentTime() - x256240_g_PROTECTINFO.StartTime >= 18   then
--					x256240_g_doing = 8
--					if IsObjValid (sceneId,x256240_g_sunfeihu) == 1 then
--							NpcTalk(sceneId, x256240_g_sunfeihu, "哈哈，来了！省了我不少麻烦！", -1)
--					end
--					if IsObjValid (sceneId,x256240_g_sunfeihu) == 1 then
--							SetMonsterDir(sceneId,x256240_g_sunfeihu,180)
--					end
--					if IsObjValid (sceneId,x256240_g_huwei2) == 1 then
--							SetMonsterDir(sceneId,x256240_g_huwei2,180)
--					end
--	end
--elseif x256240_g_doing==8   then
--	if GetCurrentTime() - x256240_g_PROTECTINFO.StartTime >= 21   then
--					x256240_g_doing = 9
--					if IsObjValid (sceneId,x256240_g_huwei2) == 1 then
--							NpcTalk(sceneId, x256240_g_huwei2, "呀！她怎么掉头走了！", -1)
--					end
--					if IsObjValid (sceneId,x256240_g_zhangsheng) == 1 then
--							SetPatrolId(sceneId, x256240_g_zhangsheng, 52)
--					end
--	end
--elseif x256240_g_doing==9   then
--	if GetCurrentTime() - x256240_g_PROTECTINFO.StartTime >= 24   then
--					x256240_g_doing = 10
--					if IsObjValid (sceneId,x256240_g_sunfeihu) == 1 then
--							NpcTalk(sceneId, x256240_g_sunfeihu, "害羞了，这种我喜欢！", -1)
--							SetPatrolId(sceneId, x256240_g_sunfeihu, 53)
--					end
--	end
--elseif x256240_g_doing==10   then
--	if GetCurrentTime() - x256240_g_PROTECTINFO.StartTime >= 26   then
--					x256240_g_doing = 11
--					if IsObjValid (sceneId,x256240_g_huwei2) == 1 then
--							NpcTalk(sceneId, x256240_g_huwei2, "我们俩在这等着吧！", -1)
--					end
--	end
--elseif x256240_g_doing==11   then
--	if GetCurrentTime() - x256240_g_PROTECTINFO.StartTime >= 28   then
--					x256240_g_doing = 12
--					if IsObjValid (sceneId,x256240_g_huwei1) == 1 then
--							NpcTalk(sceneId, x256240_g_huwei1, "恩，我打赌一炷香时间他就能回来！", -1)
--							SetMonsterDir(sceneId,x256240_g_huwei1,90)
--					end
--					if IsObjValid (sceneId,x256240_g_huwei2) == 1 then
--							SetMonsterDir(sceneId,x256240_g_huwei2,90)
--					end
--	end
--elseif x256240_g_doing==12   then
--	if GetCurrentTime() - x256240_g_PROTECTINFO.StartTime >= 32   then
--					x256240_g_doing = 13
--					if IsObjValid (sceneId,x256240_g_sunfeihu) == 1 then
--							NpcTalk(sceneId, x256240_g_sunfeihu, "我看你要跑到哪里！", -1)
--					end
--	end
--elseif x256240_g_doing==13   then
--	if GetCurrentTime() - x256240_g_PROTECTINFO.StartTime >= 36   then
--					x256240_g_doing = 14
--					if IsObjValid (sceneId,x256240_g_zhangsheng) == 1 then
--							SetMonsterDir(sceneId,x256240_g_zhangsheng,50)
--					end
--	end
--elseif x256240_g_doing==14   then
--	if GetCurrentTime() - x256240_g_PROTECTINFO.StartTime >= 38   then
--					x256240_g_doing = 15
--					if IsObjValid (sceneId,x256240_g_sunfeihu) == 1 then
--							NpcTalk(sceneId, x256240_g_sunfeihu, "什么你居然是男的！你到底是谁？", -1)
--							SetMonsterCamp(sceneId,x256240_g_sunfeihu,21)
--					end
--	end
--elseif x256240_g_doing==15   then
--	if GetCurrentTime() - x256240_g_PROTECTINFO.StartTime >= 40   then
--					x256240_g_doing = 16
--					if IsObjValid (sceneId,x256240_g_zhangsheng) == 1 then
--							NpcTalk(sceneId, x256240_g_zhangsheng, "壮士，剩下的拜托你了！", -1)
--					end
--	end
--elseif x256240_g_doing==16   then
--	if GetCurrentTime() - x256240_g_PROTECTINFO.StartTime >= 43   then
--					x256240_g_doing = 17
--	end
--elseif x256240_g_doing==17 then
--		if GetCurrentTime() - x256240_g_PROTECTINFO.StartTime >= 81   then
--			x256240_g_doing=30
--			x256240_CloseTimer(sceneId, x256240_g_PROTECTINFO.ScneneTimerIndex)
--		end
--end
end


--**********************************
--关闭计时器
--**********************************
function x256240_CloseTimer( sceneId, TimerIndex )
--	StopTimer(sceneId, TimerIndex)
--	x256240_g_doing =0
--	x256240_g_sunfeihu = -1
--	x256240_g_huwei1 = -1
--	x256240_g_huwei2 = -1
--	x256240_g_zhangsheng = -1
--	x256240_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
end