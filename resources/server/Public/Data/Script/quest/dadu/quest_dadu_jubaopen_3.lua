--【主线】珍珠翡翠白玉汤<四>

--MisDescBegin
x270016_g_ScriptId = 270016
x270016_g_MissionIdPre =3603
x270016_g_MissionId = 3604
x270016_g_LevelLess	= 	55 
x270016_g_MissionIdNext = 3605
x270016_g_Name	={}
x270016_g_ExtTarget={{type=20,n=1,target="把@itemid_13020328带给@npc_143008"}}
x270016_g_MissionName="【主线】珍珠翡翠白玉汤<四>"
x270016_g_MissionInfo="\t这就是“珍珠翡翠白玉汤”？！这味道。。。\n\t这玩意儿能治病？还不把人臭晕了！算了，你赶紧把它端给沈阔吧，让他送进去，给帮主吧！"  --任务描述
x270016_g_MissionTarget=""		
x270016_g_MissionCompleted="\t（沈阔似乎恶心欲呕，一手捂住口鼻，一手将这碗“汤”远远地端着）\n\t这。。。这。。。"					--完成任务npc说话的话
x270016_g_ContinueInfo=""
x270016_g_MissionHelp =	""
x270016_g_DemandItem ={{item=13020328,num=1}}
x270016_g_BonusMoney1 =376
x270016_g_BonusMoney2 =0
x270016_g_BonusMoney3 =0
x270016_g_BonusMoney4 =0
x270016_g_BonusMoney5 =66
x270016_g_BonusMoney6 =0
x270016_g_BonusItem	=	{}
x270016_g_BonusChoiceItem ={}
x270016_g_ExpBonus = 171000
x270016_g_NpcGUID ={{ guid = 143172, name = "沈阔"} }
--MisDescEnd
x270016_g_shenwansan =-1
x270016_g_doing =0
x270016_g_jubaopen =-1
x270016_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
--**********************************

function x270016_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x270016_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x270016_g_MissionIdPre)> 0 then
	
						if IsHaveQuest(sceneId,selfId, x270016_g_MissionId) <= 0 then
								local state = GetQuestStateNM(sceneId,selfId,NPCId,x270016_g_MissionId)
								AddQuestTextNM( sceneId, selfId, NPCId, x270016_g_MissionId, state, -1 )
						end
			
	end
end

function x270016_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x270016_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x270016_g_ExpBonus )
		end
		if x270016_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x270016_g_BonusMoney1 )
		end
		if x270016_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x270016_g_BonusMoney2 )
		end
		if x270016_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x270016_g_BonusMoney3 )
		end
		if x270016_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x270016_g_BonusMoney4 )
		end
		if x270016_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x270016_g_BonusMoney5 )
		end
		if x270016_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x270016_g_BonusMoney6 )
		end
		for i, item in x270016_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x270016_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x270016_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x270016_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x270016_g_MissionId) > 0 then
			if x270016_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270016_g_MissionName)
						AddQuestText(sceneId,x270016_g_MissionCompleted)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x270016_g_ScriptId, x270016_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270016_g_MissionName)
						AddQuestText(sceneId,x270016_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x270016_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x270016_g_ScriptId, x270016_g_MissionId);
			end
  elseif x270016_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x270016_g_MissionName)
			AddQuestText(sceneId,x270016_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x270016_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x270016_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x270016_g_MissionHelp )
			end
			x270016_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x270016_g_ScriptId, x270016_g_MissionId);
  end
	
end
--**********************************

function x270016_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x270016_CheckSubmit( sceneId, selfId, NPCId)

	        return 1
	
end
--**********************************
function x270016_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x270016_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x270016_g_MissionId  )
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
		
		
		if x270016_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginAddItem(sceneId)                                                    
			AddItem( sceneId,x270016_g_DemandItem[1].item, x270016_g_DemandItem[1].num )             
			local ret = EndAddItem(sceneId,selfId)                                 
	  		if ret > 0 then
	  			local retmiss = AddQuest( sceneId, selfId, x270016_g_MissionId, x270016_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x270016_Msg2toplayer( sceneId, selfId,0)
		  			AddItemListToPlayer(sceneId,selfId) 
						local misIndex = GetQuestIndexByID(sceneId,selfId,x270016_g_MissionId)                                                  
	    			SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	   				SetQuestByIndex(sceneId,selfId,misIndex,7,1)
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

function x270016_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x270016_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x270016_g_MissionId)
	  x270016_Msg2toplayer( sceneId, selfId,1)
	  for i, item in x270016_g_DemandItem do
	  				DelItem( sceneId,selfId,item.item, item.num )
		end
			
end
--**********************************
function x270016_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x270016_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x270016_g_BonusChoiceItem do
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
function x270016_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x270016_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270016_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270016_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x270016_g_MissionId) > 0 then
				x270016_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x270016_g_MissionId)
				x270016_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x270016_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x270016_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		for i, item in x270016_g_DemandItem do
	  				DelItem( sceneId,selfId,item.item, item.num )
				end
    		EndAddItem(sceneId,selfId)
    		if x270016_g_doing==0 then      
    			      x270016_g_PROTECTINFO.StartTime = GetCurrentTime()
								x270016_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 270016, "OnScneneTimer", 1)
								if x270016_g_PROTECTINFO.ScneneTimerIndex >= 0 then
										x270016_g_doing = 1
										x270016_g_shenwansan =CreateMonster(sceneId, 75,152,95,3,1,-1,-1,20,24000,270,"沈万三")
								end
    		end
    			
	 	end
end


function x270016_OnScneneTimer(sceneId)
	if x270016_g_shenwansan < 0 then
			x270016_CloseTimer(sceneId, x270016_g_PROTECTINFO.ScneneTimerIndex)
			return
	end
	if x270016_g_doing==1   then
		if GetCurrentTime() - x270016_g_PROTECTINFO.StartTime >= 2   then
			if IsObjValid (sceneId,x270016_g_shenwansan) == 1 then
						NpcTalk(sceneId, x270016_g_shenwansan, "真是一副良药！", -1)
			end
						x270016_g_doing = 2
		end
	elseif x270016_g_doing == 2   then
			if GetCurrentTime() - x270016_g_PROTECTINFO.StartTime >= 5   then
				if IsObjValid (sceneId,x270016_g_shenwansan) == 1 then
						NpcTalk(sceneId, x270016_g_shenwansan, "近些年已经完全忘了穷苦的日子了！", -1)
				end
            x270016_g_doing =3
			end
	elseif x270016_g_doing == 3   then
			if GetCurrentTime() - x270016_g_PROTECTINFO.StartTime >= 8   then
				if IsObjValid (sceneId,x270016_g_shenwansan) == 1 then
						NpcTalk(sceneId, x270016_g_shenwansan, "有了这么多钱又有什么用呢！", -1)
				end
        		x270016_g_doing =4
			end
	elseif x270016_g_doing == 4   then
			if GetCurrentTime() - x270016_g_PROTECTINFO.StartTime >= 11   then
				if IsObjValid (sceneId,x270016_g_shenwansan) == 1 then
						NpcTalk(sceneId, x270016_g_shenwansan, "钱够买一碗饭就行了，从今天起我要散尽家财来行善！", -1)
				end
						x270016_g_jubaopen =CreateMonster(sceneId, 3903,752,95,3,1,-1,-1,20,13000,270," ")
        		x270016_g_doing =5
			end
	elseif x270016_g_doing == 5   then
			if GetCurrentTime() - x270016_g_PROTECTINFO.StartTime >= 14   then
				if IsObjValid (sceneId,x270016_g_shenwansan) == 1 then
						NpcTalk(sceneId, x270016_g_shenwansan, "恩？这不是聚宝盆吗？", -1)
				end
        		x270016_g_doing =6
			end
	elseif x270016_g_doing == 6   then
			if GetCurrentTime() - x270016_g_PROTECTINFO.StartTime >= 17   then
				if IsObjValid (sceneId,x270016_g_shenwansan) == 1 then
						NpcTalk(sceneId, x270016_g_shenwansan, "我懂得上天的意思，聚宝盆是用来行善的！", -1)
				end
        		x270016_g_doing =7
			end
	elseif x270016_g_doing == 7   then
			if GetCurrentTime() - x270016_g_PROTECTINFO.StartTime >= 20   then
				if IsObjValid (sceneId,x270016_g_shenwansan) == 1 then
						NpcTalk(sceneId, x270016_g_shenwansan, "了解这些之后，有没有聚宝盆已经无所谓了，我会收好它，避免他被坏人利用！", -1)
				end
        		x270016_g_doing =8
			end
	elseif x270016_g_doing==8 then
			if GetCurrentTime() - x270016_g_PROTECTINFO.StartTime >= 23   then
					x270016_g_doing=9
					x270016_CloseTimer(sceneId, x270016_g_PROTECTINFO.ScneneTimerIndex)
			end
	end
end


--**********************************
--关闭计时器
--**********************************
function x270016_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x270016_g_doing =0
	x270016_g_shenwansan =-1
	x270016_g_jubaopen =-1
	x270016_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
end


function x270016_GetBonus( sceneId, selfId,NpcID)
	  if x270016_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x270016_g_ExpBonus);
  	end
		if x270016_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x270016_g_BonusMoney1 )
	  end
		if x270016_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x270016_g_BonusMoney2 )
	  end
		if x270016_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x270016_g_BonusMoney3 )
		end
		if x270016_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x270016_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x270016_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x270016_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x270016_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x270016_g_BonusMoney6)
		end
end

function x270016_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x270016_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x270016_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x270016_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x270016_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x270016_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x270016_g_MissionName.."！", 0, 3)
				if x270016_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x270016_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x270016_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x270016_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x270016_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x270016_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x270016_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x270016_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x270016_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x270016_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x270016_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x270016_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x270016_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x270016_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x270016_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x270016_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x270016_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x270016_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x270016_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x270016_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x270016_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x270016_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x270016_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x270016_g_MissionId, state, -1 )
		end
end

function x270016_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x270016_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x270016_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x270016_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x270016_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x270016_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end