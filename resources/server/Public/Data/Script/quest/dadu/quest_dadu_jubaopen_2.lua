--【主线】照葫芦画瓢<三>

--MisDescBegin
x270015_g_ScriptId = 270015
x270015_g_MissionIdPre =3599
x270015_g_MissionId = 3600
x270015_g_LevelLess	= 	55 
x270015_g_MissionIdNext = 3601
x270015_g_Name	={}
x270015_g_noDemandItem ={{id=13020325,num=1},{id=13020326,num=1}}
x270015_g_ExtTarget ={{type=20,n=1,target="到@npc_143176把红焖田鸡倒入海中"}}
x270015_g_ExtTargetmul={{type=20,n=1,target="到@npc_143176把红焖田鸡倒入海中"},
												{type=20,n=1,target="到@npc_143176捞一网"},
												{type=20,n=1,target="到@npc_143177捞一网"},
												{type=20,n=1,target="到@npc_143178捞一网"},
												{type=20,n=1,target="到@npc_143179捞一网"},
												{type=20,n=1,target="打捞聚宝盆"}}
x270015_g_MissionName="【主线】照葫芦画瓢<三>"
x270015_g_MissionInfo="\t这是我刚命人在醉仙楼买回来的红焖田鸡，你带上网和这些田鸡，记得撒网之前先把田鸡丢进海里。"  --任务描述
x270015_g_MissionTarget=""		
x270015_g_MissionCompleted="\t什么？聚宝盆已经被老天爷收走了？！"					--完成任务npc说话的话
x270015_g_ContinueInfo="\t捞到了么？要是一次不行，那就多捞几次。"
x270015_g_MissionHelp =	""
x270015_g_DemandItem ={}
x270015_g_BonusMoney1 =376
x270015_g_BonusMoney2 =0
x270015_g_BonusMoney3 =0
x270015_g_BonusMoney4 =0
x270015_g_BonusMoney5 =66
x270015_g_BonusMoney6 =0
x270015_g_BonusItem	=	{}
x270015_g_BonusChoiceItem ={}
x270015_g_ExpBonus = 171000
--MisDescEnd
x270015_g_doing = 0
x270015_g_longwang =-1
x270015_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
--**********************************

function x270015_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x270015_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x270015_g_MissionIdPre)> 0 then
								local state = GetQuestStateNM(sceneId,selfId,NPCId,x270015_g_MissionId)
								AddQuestTextNM( sceneId, selfId, NPCId, x270015_g_MissionId, state, -1 )
	end
end

function x270015_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x270015_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x270015_g_ExpBonus )
		end
		if x270015_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x270015_g_BonusMoney1 )
		end
		if x270015_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x270015_g_BonusMoney2 )
		end
		if x270015_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x270015_g_BonusMoney3 )
		end
		if x270015_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x270015_g_BonusMoney4 )
		end
		if x270015_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x270015_g_BonusMoney5 )
		end
		if x270015_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x270015_g_BonusMoney6 )
		end
		for i, item in x270015_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x270015_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x270015_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x270015_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x270015_g_MissionId) > 0 then
			if x270015_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270015_g_MissionName)
						AddQuestText(sceneId,x270015_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x270015_g_ScriptId, x270015_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270015_g_MissionName)
						AddQuestText(sceneId,x270015_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x270015_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x270015_g_ScriptId, x270015_g_MissionId);
			end
  elseif x270015_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x270015_g_MissionName)
			AddQuestText(sceneId,x270015_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x270015_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x270015_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x270015_g_MissionHelp )
			end
			x270015_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x270015_g_ScriptId, x270015_g_MissionId);
  end
	
end
--**********************************

function x270015_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x270015_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x270015_g_MissionId)
	if GetQuestParam(sceneId,selfId,misIndex,0) == 1 then
			return 1
	end
	return 0
end
--**********************************
function x270015_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x270015_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x270015_g_MissionId  )
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
		
		if x270015_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
		  BeginAddItem(sceneId)                                                    
			AddItem( sceneId,x270015_g_noDemandItem[1].id, x270015_g_noDemandItem[1].num ) 
			AddItem( sceneId,x270015_g_noDemandItem[2].id, x270015_g_noDemandItem[2].num )              
			local ret = EndAddItem(sceneId,selfId)                                 
	  		if ret > 0 then
	  			local retmiss = AddQuest( sceneId, selfId, x270015_g_MissionId, x270015_g_ScriptId, 0, 0, 0)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x270015_Msg2toplayer( sceneId, selfId,0)
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

function x270015_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x270015_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x270015_g_MissionId)
	  x270015_Msg2toplayer( sceneId, selfId,1)
	  for i, item in x270015_g_noDemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
		end
			
end
--**********************************
function x270015_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x270015_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x270015_g_BonusChoiceItem do
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
function x270015_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x270015_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270015_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270015_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x270015_g_MissionId) > 0 then
				x270015_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x270015_g_MissionId)
				x270015_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x270015_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x270015_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		for i, item in x270015_g_noDemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
				end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x270015_g_MissionIdNext )	
end

function x270015_GetBonus( sceneId, selfId,NpcID)
	  if x270015_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x270015_g_ExpBonus);
  	end
		if x270015_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x270015_g_BonusMoney1 )
	  end
		if x270015_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x270015_g_BonusMoney2 )
	  end
		if x270015_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x270015_g_BonusMoney3 )
		end
		if x270015_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x270015_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x270015_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x270015_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x270015_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x270015_g_BonusMoney6)
		end
end

function x270015_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x270015_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x270015_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x270015_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x270015_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x270015_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x270015_g_MissionName.."！", 0, 3)
				if x270015_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x270015_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x270015_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x270015_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x270015_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x270015_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x270015_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x270015_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x270015_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x270015_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x270015_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x270015_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x270015_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x270015_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x270015_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x270015_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
end

function x270015_ProcTiming(ssceneId, selfId, ScriptId, MissionId)
	
end

function x270015_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
end

function x270015_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x270015_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end

function x270015_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x270015_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x270015_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x270015_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x270015_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x270015_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x270015_OnScneneTimer(sceneId, selfId)
	if x270015_g_longwang < 0 then
			x270015_CloseTimer(sceneId, x270015_g_PROTECTINFO.ScneneTimerIndex)
			return
	end
	if x270015_g_doing==1   then
		if GetCurrentTime() - x270015_g_PROTECTINFO.StartTime >= 1   then
			if IsObjValid (sceneId,x270015_g_longwang) == 1 then
				NpcTalk(sceneId, x270015_g_longwang, "英雄！收了你的神通吧！", -1)
			end
      x270015_g_doing = 2
		end
	elseif x270015_g_doing == 2   then
			if GetCurrentTime() - x270015_g_PROTECTINFO.StartTime >= 5   then
				if IsObjValid (sceneId,x270015_g_longwang) == 1 then
						NpcTalk(sceneId, x270015_g_longwang, "我是威海的龙王，你要知道你的网不是普通的网。", -1)
				end
        x270015_g_doing =3
			end
	elseif x270015_g_doing == 3   then
			if GetCurrentTime() - x270015_g_PROTECTINFO.StartTime >= 8   then
				if IsObjValid (sceneId,x270015_g_longwang) == 1 then
						NpcTalk(sceneId, x270015_g_longwang, "你的网刚刚已经把龙宫搅得一团糟，龟丞相被你网上去之后一直躲在壳里不肯出来！", -1)
				end
						x270015_g_doing =4
			end
	elseif x270015_g_doing == 4   then
			if GetCurrentTime() - x270015_g_PROTECTINFO.StartTime >= 12   then
				if IsObjValid (sceneId,x270015_g_longwang) == 1 then
						NpcTalk(sceneId, x270015_g_longwang, "聚宝盆乃是神物，怎么会在此海里面停留呢？它早就已经回到天上去了！", -1)
				end
						x270015_g_doing =5
			end
	elseif x270015_g_doing == 5   then
			if GetCurrentTime() - x270015_g_PROTECTINFO.StartTime >= 16   then
				if IsObjValid (sceneId,x270015_g_longwang) == 1 then
						NpcTalk(sceneId, x270015_g_longwang, "这个网我就留下了，免得再危害龙宫！", -1)
				end
						x270015_g_doing =6
						x270015_CloseTimer(sceneId, x270015_g_PROTECTINFO.ScneneTimerIndex)
			end
	end
end

function x270015_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x270015_g_doing = 0
	x270015_g_longwang =-1
	x270015_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
	
end

function x270015_ProcQuestLogRefresh( sceneId,selfId,missionId)
				local misIndex = GetQuestIndexByID(sceneId,selfId,x270015_g_MissionId)
				local exttarget =GetQuestParam(sceneId,selfId,misIndex,1)+1
				BeginQuestEvent(sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                    -- 标题
                                "",                 -- 任务名字
                                x270015_g_ExtTargetmul[exttarget].target,               --任务目标
                                "",                         --任务NPC
                                "",                   --任务攻略
                                "",                --任务描述
                                ""        --任务小提示
                                )

				EndQuestEvent()
				DispatchQuestLogUpdate(sceneId, selfId, x270015_g_MissionId);

end

function x270015_useitem(sceneId,selfId,which)
		local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )
		local misIndex = GetQuestIndexByID(sceneId,selfId,x270015_g_MissionId)
		if GetQuestParam(sceneId,selfId,misIndex,1) == 0 then
			if which == 1 then 
				local distanceRet = 25 - (185 - PlayerPosX) * (185 - PlayerPosX) - (201 - PlayerPosZ) * (201 - PlayerPosZ)
				if distanceRet >= 0 then
						DelItem( sceneId,selfId,x270015_g_noDemandItem[1].id, x270015_g_noDemandItem[1].num )
						Msg2Player(sceneId, selfId, "任务目标改变", 0, 3)
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"\t你把田鸡倒入到水中，没有任何反应。接下来应该用网去捞一下了！")
						SetQuestByIndex(sceneId,selfId,misIndex,1,1)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, selfId, x270015_g_ScriptId, x270015_g_MissionId);
						x270015_ProcQuestLogRefresh( sceneId,selfId,x270015_g_MissionId)
						return 1
				else
						Msg2Player(sceneId, selfId, "这里无法使用这个物品", 0, 3)
						return 0
				end
			else
						Msg2Player(sceneId, selfId, "这里无法使用这个物品", 0, 3)
						return 0
			end
		elseif GetQuestParam(sceneId,selfId,misIndex,1) == 1 then
				local distanceRet = 25 - (185 - PlayerPosX) * (185 - PlayerPosX) - (201 - PlayerPosZ) * (201 - PlayerPosZ)
				if distanceRet >= 0 then
						Msg2Player(sceneId, selfId, "任务目标改变", 0, 3)
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"\t一网下去捞上来一个破破烂烂的铁盆，怎么看也不像是聚宝盆，应该换个地方捞捞了。")
						SetQuestByIndex(sceneId,selfId,misIndex,1,2)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, selfId, x270015_g_ScriptId, x270015_g_MissionId);
						x270015_ProcQuestLogRefresh( sceneId,selfId,x270015_g_MissionId)
						return 1
				else
						Msg2Player(sceneId, selfId, "这里无法使用这个物品", 0, 3)
						return 0
				end
		elseif GetQuestParam(sceneId,selfId,misIndex,1) == 2 then
				local distanceRet = 25 - (185 - PlayerPosX) * (185 - PlayerPosX) - (190 - PlayerPosZ) * (190 - PlayerPosZ)
				if distanceRet >= 0 then
						Msg2Player(sceneId, selfId, "任务目标改变", 0, 3)
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"\t一网下去又捞上来一个石盆，看起来年代久远，但与张士诚描述的聚宝盆还是有一定差别，再换一个地方吧。")
						SetQuestByIndex(sceneId,selfId,misIndex,1,3)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, selfId, x270015_g_ScriptId, x270015_g_MissionId);
						x270015_ProcQuestLogRefresh( sceneId,selfId,x270015_g_MissionId)
						return 1
				else
						Msg2Player(sceneId, selfId, "这里无法使用这个物品", 0, 3)
						return 0
				end
		elseif GetQuestParam(sceneId,selfId,misIndex,1) == 3 then
				local distanceRet = 25 - (200 - PlayerPosX) * (200 - PlayerPosX) - (185 - PlayerPosZ) * (185 - PlayerPosZ)
				if distanceRet >= 0 then
						Msg2Player(sceneId, selfId, "任务目标改变", 0, 3)
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"\t一网下去这次不是盆了，而是一只大乌龟，看起来它的年龄不比刚才的石盆小。它的头脚都已经缩到了壳里，无奈之下你把它又扔到了海里！")
						SetQuestByIndex(sceneId,selfId,misIndex,1,4)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, selfId, x270015_g_ScriptId, x270015_g_MissionId);
						x270015_ProcQuestLogRefresh( sceneId,selfId,x270015_g_MissionId)
						return 1
				else
						Msg2Player(sceneId, selfId, "这里无法使用这个物品", 0, 3)
						return 0
				end
		elseif GetQuestParam(sceneId,selfId,misIndex,1) == 4 then
				local distanceRet = 25 - (174 - PlayerPosX) * (174 - PlayerPosX) - (206 - PlayerPosZ) * (206 - PlayerPosZ)
				if distanceRet >= 0 then
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,1,5)
						Msg2Player(sceneId, selfId, "任务目标完成", 0, 3)
						DelItem( sceneId,selfId,x270015_g_noDemandItem[2].id, x270015_g_noDemandItem[2].num )
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"\t这次的网很沉，当你费劲拉上来时，看见网上挂着一个人！而且戴着王冠！")
						SetQuestByIndex(sceneId,selfId,misIndex,1,5)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, selfId, x270015_g_ScriptId, x270015_g_MissionId);
						if x270015_g_doing==0   then
								x270015_g_PROTECTINFO.StartTime = GetCurrentTime()
								x270015_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 270015, "OnScneneTimer", 1)
								if x270015_g_PROTECTINFO.ScneneTimerIndex >= 0 then
										x270015_g_doing = 1
										x270015_g_longwang =CreateMonster(sceneId, 3902,170,203,3,1,-1,-1,20,20000,90,"龙王")
								end
						end
						return 1
				else
						Msg2Player(sceneId, selfId, "这里无法使用这个物品", 0, 3)
						return 0
				end
		end
end
