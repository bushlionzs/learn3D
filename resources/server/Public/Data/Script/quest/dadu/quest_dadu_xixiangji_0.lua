--【主线】天赐姻缘<二>

--MisDescBegin
x270010_g_ScriptId = 270010
x270010_g_MissionIdPre =3500
x270010_g_MissionId = 3501
x270010_g_LevelLess	= 	45 
x270010_g_MissionIdNext = 3502
x270010_g_Name	={}
x270010_g_noDemandItem ={{id=13020314,num=1}}
x270010_g_ExtTarget={{type=20,n=1,target="到@npc_141010放下酒坛询问红娘的爷爷"}}
x270010_g_MissionName="【主线】天赐姻缘<二>"
x270010_g_MissionInfo="\t我看那张生也是一表人才，莺莺美貌贤淑，二人若能喜结良缘也不失为是一件美事，不过我还有些事情要向我爷爷问清楚。\n\t你现在去买一坛美酒，把它放在城边的大树下，请那里一个手拿红线和书的老头喝酒，等他喝到高兴时，再问他我说的这件事，他一定会告诉你。"  --任务描述
x270010_g_MissionTarget=""		
x270010_g_MissionCompleted="\t（红娘欣喜地说道）\n\t爷爷真的这么说么？哎呀，那可真是太好了，我今日若是成人之美，从中撮合他们，也不失为功德一件。"					--完成任务npc说话的话
x270010_g_ContinueInfo="\t见过我爷爷了吗？"
x270010_g_MissionHelp =	""
x270010_g_DemandItem ={}
x270010_g_BonusMoney1 =376
x270010_g_BonusMoney2 =0
x270010_g_BonusMoney3 =0
x270010_g_BonusMoney4 =0
x270010_g_BonusMoney5 =56
x270010_g_BonusMoney6 =0
x270010_g_BonusItem	=	{}
x270010_g_BonusChoiceItem ={}
x270010_g_ExpBonus = 112000
--MisDescEnd
x270010_g_doing = 0
x270010_g_yuelao =-1
x270010_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
--**********************************

function x270010_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x270010_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x270010_g_MissionIdPre)> 0 then
								local state = GetQuestStateNM(sceneId,selfId,NPCId,x270010_g_MissionId)
								AddQuestTextNM( sceneId, selfId, NPCId, x270010_g_MissionId, state, -1 )
	end
end

function x270010_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x270010_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x270010_g_ExpBonus )
		end
		if x270010_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x270010_g_BonusMoney1 )
		end
		if x270010_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x270010_g_BonusMoney2 )
		end
		if x270010_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x270010_g_BonusMoney3 )
		end
		if x270010_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x270010_g_BonusMoney4 )
		end
		if x270010_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x270010_g_BonusMoney5 )
		end
		if x270010_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x270010_g_BonusMoney6 )
		end
		for i, item in x270010_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x270010_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x270010_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x270010_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x270010_g_MissionId) > 0 then
			if x270010_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270010_g_MissionName)
						AddQuestText(sceneId,x270010_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x270010_g_ScriptId, x270010_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270010_g_MissionName)
						AddQuestText(sceneId,x270010_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x270010_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x270010_g_ScriptId, x270010_g_MissionId);
			end
  elseif x270010_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x270010_g_MissionName)
			AddQuestText(sceneId,x270010_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x270010_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x270010_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x270010_g_MissionHelp )
			end
			x270010_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x270010_g_ScriptId, x270010_g_MissionId);
  end
	
end
--**********************************

function x270010_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x270010_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x270010_g_MissionId)
	if GetQuestParam(sceneId,selfId,misIndex,0) == 1 then
			return 1
	end
	return 0
end
--**********************************
function x270010_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x270010_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x270010_g_MissionId  )
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
		if x270010_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
		  BeginAddItem(sceneId)                                                    
			AddItem( sceneId,x270010_g_noDemandItem[1].id, x270010_g_noDemandItem[1].num )             
			local ret = EndAddItem(sceneId,selfId)                                 
	  		if ret > 0 then
	  			local retmiss = AddQuest( sceneId, selfId, x270010_g_MissionId, x270010_g_ScriptId, 0, 0, 0)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x270010_Msg2toplayer( sceneId, selfId,0)
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

function x270010_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x270010_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x270010_g_MissionId)
	  x270010_Msg2toplayer( sceneId, selfId,1)
	  for i, item in x270010_g_noDemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
		end
			
end
--**********************************
function x270010_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x270010_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x270010_g_BonusChoiceItem do
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
function x270010_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x270010_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270010_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270010_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x270010_g_MissionId) > 0 then
				x270010_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x270010_g_MissionId)
				x270010_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x270010_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x270010_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x270010_g_MissionIdNext )	
end

function x270010_GetBonus( sceneId, selfId,NpcID)
	  if x270010_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x270010_g_ExpBonus);
  	end
		if x270010_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x270010_g_BonusMoney1 )
	  end
		if x270010_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x270010_g_BonusMoney2 )
	  end
		if x270010_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x270010_g_BonusMoney3 )
		end
		if x270010_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x270010_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x270010_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x270010_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x270010_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x270010_g_BonusMoney6)
		end
end

function x270010_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x270010_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x270010_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x270010_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x270010_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x270010_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x270010_g_MissionName.."！", 0, 3)
				if x270010_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x270010_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x270010_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x270010_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x270010_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x270010_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x270010_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x270010_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x270010_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x270010_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x270010_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x270010_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x270010_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x270010_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x270010_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x270010_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
end

function x270010_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	
end

function x270010_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
end

function x270010_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x270010_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end

function x270010_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x270010_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x270010_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x270010_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x270010_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x270010_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x270010_OnScneneTimer(sceneId, selfId)
	if x270010_g_yuelao < 0 then
			x270010_CloseTimer(sceneId, x270010_g_PROTECTINFO.ScneneTimerIndex)
			return
	end
	if x270010_g_doing==1   then
		if GetCurrentTime() - x270010_g_PROTECTINFO.StartTime >= 1   then
		  x270010_g_doing = 2
			if IsObjValid (sceneId,x270010_g_yuelao) == 1 then
				NpcTalk(sceneId, x270010_g_yuelao, "是我孙女让你来的吧！", -1)
			end
    end
	elseif x270010_g_doing == 2   then
			if GetCurrentTime() - x270010_g_PROTECTINFO.StartTime >= 5   then
			  	x270010_g_doing =3
					if IsObjValid (sceneId,x270010_g_yuelao) == 1 then
						NpcTalk(sceneId, x270010_g_yuelao, "你不用说我知道她要问什么。", -1)
					end
      end
	elseif x270010_g_doing == 3   then
			if GetCurrentTime() - x270010_g_PROTECTINFO.StartTime >= 8   then
					x270010_g_doing =4
					if IsObjValid (sceneId,x270010_g_yuelao) == 1 then
						NpcTalk(sceneId, x270010_g_yuelao, "你就告诉她这件事能成，是个很不错的事情。", -1)
					end
			end
	
	elseif x270010_g_doing == 4   then
			if GetCurrentTime() - x270010_g_PROTECTINFO.StartTime >= 12   then
					x270010_g_doing =5
					if IsObjValid (sceneId,x270010_g_yuelao) == 1 then
						NpcTalk(sceneId, x270010_g_yuelao, "好了我去喝酒了，你回去告诉她吧！", -1)
					end
						x270010_CloseTimer(sceneId, x270010_g_PROTECTINFO.ScneneTimerIndex)
			end
	end
end

function x270010_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x270010_g_doing = 0
	x270010_g_yuelao =-1
	x270010_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
	
end

function x270010_useitem(sceneId,selfId)
		local x,z = GetWorldPos(sceneId,selfId)
		local distanceRet = 100 - (181 - x) * (181 - x) - (445 - z) * (445 - z)
		local misIndex = GetQuestIndexByID(sceneId,selfId,x270010_g_MissionId)
		if sceneId == 0 then
  		if distanceRet >= 0 then
          SetQuestByIndex(sceneId,selfId,misIndex,0,1)
		 			if x270010_g_doing==0 then
		 					BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"询问红娘的爷爷  1/1")
							DispatchQuestTips(sceneId,selfId) 
							EndQuestEvent(sceneId)
							SetQuestByIndex(sceneId,selfId,misIndex,7,1)
				 			x270010_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 270010, "OnScneneTimer", 1)
				 			if x270010_g_PROTECTINFO.ScneneTimerIndex >= 0 then
									x270010_g_yuelao=CreateMonster(sceneId, 445,181,444,3,1,-1,-1,20,15000,0,"老人")
        					x270010_g_doing =1
									x270010_g_PROTECTINFO.StartTime = GetCurrentTime()
									DelItem(sceneId, selfId, 13020314, 1)
							end
					else
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"询问红娘的爷爷  1/1")
							DispatchQuestTips(sceneId,selfId) 
							EndQuestEvent(sceneId)
							DelItem(sceneId, selfId, 13020314, 1)
							SetQuestByIndex(sceneId,selfId,misIndex,7,1)
					end
     			  	return 1
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"这里不能使用")
				DispatchQuestTips(sceneId,selfId) 
				EndQuestEvent(sceneId)
			end
		end
           
			return 0
end
