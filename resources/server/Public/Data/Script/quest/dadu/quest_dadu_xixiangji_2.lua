--【主线】破镜重圆<一>

--MisDescBegin
x270012_g_ScriptId = 270012
x270012_g_MissionIdPre =3510
x270012_g_MissionId = 3513
x270012_g_LevelLess	= 	45 
x270012_g_MissionIdNext = 3514
x270012_g_Name	={}
x270012_g_noDemandItem ={{id=13020324,num=1}}
x270012_g_ExtTarget={{type=20,n=1,target="到@npc_141012处使用@itemid_13020324之后按照道士的指示去做完成仪式"}}
x270012_g_MissionName="【主线】破镜重圆<一>"
x270012_g_MissionInfo="\t据我所知，这附近有一种叫做饕餮的异兽，生性贪吃法力却不小，你可以用我给你的水玉加上柳叶来喂它，等它缩小到一定的程度就可以擒住它来拼合破碎的镜子。\n\t至于能不能将它成功地引诱出来复原镜子，贫道也没有把握。"  --任务描述
x270012_g_MissionTarget=""		
x270012_g_MissionCompleted="\t这破镜重圆也是世间一桩逆天奇事，你居然能成功！看来这就是天意使然啊。"					--完成任务npc说话的话
x270012_g_ContinueInfo="\t这件事能否成功就看缘分了！"
x270012_g_MissionHelp =	""
x270012_g_DemandItem ={}
x270012_g_BonusMoney1 =376
x270012_g_BonusMoney2 =0
x270012_g_BonusMoney3 =0
x270012_g_BonusMoney4 =0
x270012_g_BonusMoney5 =56
x270012_g_BonusMoney6 =0
x270012_g_BonusItem	=	{}
x270012_g_BonusChoiceItem ={}
x270012_g_ExpBonus = 112000
x270012_g_GroupPoint	={ {type=10,id =16,target = "火腿"} }
--MisDescEnd
x270012_g_daotong =-1
x270012_g_taotie =-1
x270012_g_doing=0
x270012_g_doing2=0
x270012_g_accid =-1
x270012_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0,StartTime2 = 0}
--**********************************

function x270012_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x270012_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x270012_g_MissionIdPre)> 0 then
								local state = GetQuestStateNM(sceneId,selfId,NPCId,x270012_g_MissionId)
								AddQuestTextNM( sceneId, selfId, NPCId, x270012_g_MissionId, state, -1 )
	end
end

function x270012_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x270012_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x270012_g_ExpBonus )
		end
		if x270012_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x270012_g_BonusMoney1 )
		end
		if x270012_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x270012_g_BonusMoney2 )
		end
		if x270012_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x270012_g_BonusMoney3 )
		end
		if x270012_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x270012_g_BonusMoney4 )
		end
		if x270012_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x270012_g_BonusMoney5 )
		end
		if x270012_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x270012_g_BonusMoney6 )
		end
		for i, item in x270012_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x270012_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x270012_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x270012_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x270012_g_MissionId) > 0 then
			if x270012_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270012_g_MissionName)
						AddQuestText(sceneId,x270012_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x270012_g_ScriptId, x270012_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270012_g_MissionName)
						AddQuestText(sceneId,x270012_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x270012_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x270012_g_ScriptId, x270012_g_MissionId);
			end
  elseif x270012_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x270012_g_MissionName)
			AddQuestText(sceneId,x270012_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x270012_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x270012_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x270012_g_MissionHelp )
			end
			x270012_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x270012_g_ScriptId, x270012_g_MissionId);
  end
	
end
--**********************************

function x270012_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x270012_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x270012_g_MissionId)
	if GetQuestParam(sceneId,selfId,misIndex,0) == 1 then
			return 1
	end
	return 0
end
--**********************************
function x270012_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x270012_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x270012_g_MissionId  )
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
		if x270012_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
		  BeginAddItem(sceneId)                                                    
			AddItem( sceneId,x270012_g_noDemandItem[1].id, x270012_g_noDemandItem[1].num )             
			local ret = EndAddItem(sceneId,selfId)                                 
	  		if ret > 0 then
	  			local retmiss = AddQuest( sceneId, selfId, x270012_g_MissionId, x270012_g_ScriptId, 0, 0, 0)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x270012_Msg2toplayer( sceneId, selfId,0)
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

function x270012_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x270012_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x270012_g_MissionId)
	  x270012_Msg2toplayer( sceneId, selfId,1)
	  for i, item in x270012_g_noDemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
		end
			
end
--**********************************
function x270012_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x270012_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x270012_g_BonusChoiceItem do
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
function x270012_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x270012_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270012_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270012_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x270012_g_MissionId) > 0 then
				x270012_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x270012_g_MissionId)
				x270012_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x270012_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x270012_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		for i, item in x270012_g_noDemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
				end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x270012_g_MissionIdNext )	
end

function x270012_GetBonus( sceneId, selfId,NpcID)
	  if x270012_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x270012_g_ExpBonus);
  	end
		if x270012_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x270012_g_BonusMoney1 )
	  end
		if x270012_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x270012_g_BonusMoney2 )
	  end
		if x270012_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x270012_g_BonusMoney3 )
		end
		if x270012_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x270012_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x270012_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x270012_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x270012_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x270012_g_BonusMoney6)
		end
end

function x270012_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x270012_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x270012_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x270012_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x270012_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x270012_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x270012_g_MissionName.."！", 0, 3)
				if x270012_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x270012_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x270012_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x270012_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x270012_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x270012_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x270012_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x270012_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x270012_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x270012_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x270012_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x270012_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x270012_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x270012_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x270012_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x270012_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
end

function x270012_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	
end

function x270012_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
end

function x270012_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x270012_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end

function x270012_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x270012_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x270012_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x270012_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x270012_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x270012_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x270012_useitem(sceneId,selfId)
		local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )
		local distanceRet = 25 - (412 - PlayerPosX) * (412 - PlayerPosX) - (430 - PlayerPosZ) * (430 - PlayerPosZ)
		if distanceRet >= 0 then
			local misIndex = GetQuestIndexByID(sceneId, selfId, x270012_g_MissionId)
			if GetQuestParam(sceneId,selfId,misIndex,0) == 0 then
				if x270012_g_doing==0   then
						x270012_g_PROTECTINFO.StartTime = GetCurrentTime()
						x270012_g_PROTECTINFO.StartTime2 = GetCurrentTime()
						x270012_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 270012, "OnScneneTimer", 1)
						if x270012_g_PROTECTINFO.ScneneTimerIndex >= 0 then
								x270012_g_doing = 1
								x270012_g_daotong=CreateMonster(sceneId, 1619,412,430,3,1,-1,-1,20,98000,0,"巫山道人")
								x270012_g_accid =selfId
								return 0
						end
				else
						Msg2Player(sceneId, selfId, "你暂时无法这样做", 0, 3)
				end
			end
		else
				Msg2Player(sceneId, selfId, "这里无法使用这个物品", 0, 3)
				return 0
		end
end


function x270012_Growpoint(sceneId,selfId,which)
		if IsHaveQuest(sceneId,selfId, x270012_g_MissionId) <= 0 then
				return 1
		end
		if which ==0 then
							return 0
		elseif which == 1 then
				if x270012_g_doing == 5   then
					if IsObjValid (sceneId,x270012_g_daotong) == 1 then
						SetPatrolId(sceneId, x270012_g_daotong, 55)
					end
					if IsObjValid (sceneId,x270012_g_taotie) == 1 then
						SetPatrolId(sceneId, x270012_g_taotie, 54)
					end
					if IsObjValid (sceneId,x270012_g_daotong) == 1 then
						NpcTalk(sceneId, x270012_g_daotong, "好的，我们继续！", -1)
					end
						CreateMonster(sceneId, 1622,411, 448,3,1,-1,-1,20,8000,0," ")
						x270012_g_PROTECTINFO.StartTime2 = GetCurrentTime()
						x270012_g_doing2= 0
    				return 1
    		elseif x270012_g_doing == 6   then
    			if IsObjValid (sceneId,x270012_g_daotong) == 1 then
						SetPatrolId(sceneId, x270012_g_daotong, 56)
						NpcTalk(sceneId, x270012_g_daotong, "好的，我们继续！", -1)
					end
					if IsObjValid (sceneId,x270012_g_taotie) == 1 then
						SetPatrolId(sceneId, x270012_g_taotie, 55)
					end
						CreateMonster(sceneId, 1622,396, 453,3,1,-1,-1,20,8000,0," ")
						x270012_g_PROTECTINFO.StartTime2 = GetCurrentTime()
						x270012_g_doing2= 0
    				return 1
    		elseif x270012_g_doing == 7   then
    			if IsObjValid (sceneId,x270012_g_daotong) == 1 then
						SetPatrolId(sceneId, x270012_g_daotong, 57)
						NpcTalk(sceneId, x270012_g_daotong, "好的，我们继续！", -1)
					end
					if IsObjValid (sceneId,x270012_g_taotie) == 1 then
						SetPatrolId(sceneId, x270012_g_taotie, 56)
					end
						CreateMonster(sceneId, 1622,385, 441,3,1,-1,-1,20,8000,0," ")
						x270012_g_PROTECTINFO.StartTime2 = GetCurrentTime()
						x270012_g_doing2= 0
    				return 1
    		elseif x270012_g_doing == 8   then
    			if IsObjValid (sceneId,x270012_g_daotong) == 1 then
						SetPatrolId(sceneId, x270012_g_daotong, 58)
						NpcTalk(sceneId, x270012_g_daotong, "好了等它来就好了！", -1)
					end
					if IsObjValid (sceneId,x270012_g_taotie) == 1 then
						SetPatrolId(sceneId, x270012_g_taotie, 57)
					end
						CreateMonster(sceneId, 1622,371, 441,3,1,-1,-1,20,8000,0," ")
						x270012_g_PROTECTINFO.StartTime2 = GetCurrentTime()
						x270012_g_doing2= 0
    				return 1
    		end
    end
		
end

function x270012_OnScneneTimer(sceneId, selfId)
	if x270012_g_doing==1   then
		if GetCurrentTime() - x270012_g_PROTECTINFO.StartTime >= 1   then
			if IsObjValid (sceneId,x270012_g_daotong) == 1 then
				NpcTalk(sceneId, x270012_g_daotong, "饕餮马上出来了，记得跟在我的后面，当我放下诱饵之后立刻将水玉涂抹在上面！", -1)
			end
        x270012_g_doing = 2
		end
	elseif x270012_g_doing == 2   then
			if GetCurrentTime() - x270012_g_PROTECTINFO.StartTime >= 5   then
				if IsObjValid (sceneId,x270012_g_daotong) == 1 then
						NpcTalk(sceneId, x270012_g_daotong, "他出来了，跟着我！", -1)
						SetPatrolId(sceneId, x270012_g_daotong, 54)
				end
        x270012_g_doing =3
			end
	elseif x270012_g_doing == 3   then
			if GetCurrentTime() - x270012_g_PROTECTINFO.StartTime >= 6   then
						x270012_g_taotie=CreateMonster(sceneId, 1620,412,430,3,1,-1,-1,20,96000,0,"饕餮")
						x270012_g_PROTECTINFO.StartTime2 = GetCurrentTime()
        x270012_g_doing =4
			end
	elseif GetCurrentTime() - x270012_g_PROTECTINFO.StartTime >= 95   then
			if IsObjValid (sceneId,x270012_g_daotong) == 1 then
						NpcTalk(sceneId, x270012_g_daotong, "没有时间了，看来要重新试一次了！", -1)
			end
						x270012_CloseTimer(sceneId, x270012_g_PROTECTINFO.ScneneTimerIndex)
  end
	if x270012_g_doing2== 0 then
		if GetCurrentTime() - x270012_g_PROTECTINFO.StartTime2 >= 8   then
			if x270012_g_doing == 4   then
						ItemBoxEnterScene(411, 448, 16, sceneId, 0, 13020324,90000)
						if IsObjValid (sceneId,x270012_g_daotong) == 1 then
								NpcTalk(sceneId, x270012_g_daotong, "快来把水玉涂在上面！", -1)
						end
						--SendSpecificImpactToUnit(sceneId, x270012_g_taotie, x270012_g_taotie, x270012_g_taotie, 8705, 0);
						x270012_g_doing =5
        		x270012_g_doing2= 1
      elseif x270012_g_doing == 5   then
						ItemBoxEnterScene(396, 453, 16, sceneId, 0, 13020324,80000)
						if IsObjValid (sceneId,x270012_g_daotong) == 1 then
								NpcTalk(sceneId, x270012_g_daotong, "快来把水玉涂在上面！", -1)
						end
						if IsObjValid (sceneId,x270012_g_taotie) == 1 then
						NpcTalk(sceneId, x270012_g_taotie, "呼噜呼噜！", -1)
						end
						--SendSpecificImpactToUnit(sceneId, x270012_g_taotie, x270012_g_taotie, x270012_g_taotie, 8706, 0);
        		x270012_g_doing =6
        		x270012_g_doing2= 1
     elseif x270012_g_doing == 6   then
						ItemBoxEnterScene(385, 441, 16, sceneId, 0, 13020324,70000)
						if IsObjValid (sceneId,x270012_g_daotong) == 1 then
								NpcTalk(sceneId, x270012_g_daotong, "快来把水玉涂在上面！", -1)
						end
						if IsObjValid (sceneId,x270012_g_taotie) == 1 then
								NpcTalk(sceneId, x270012_g_taotie, "呼噜呼噜！", -1)
						end
						--SendSpecificImpactToUnit(sceneId, x270012_g_taotie, x270012_g_taotie, x270012_g_taotie, 8707, 0);
        		x270012_g_doing =7
        		x270012_g_doing2= 1
     elseif x270012_g_doing == 7   then
						ItemBoxEnterScene(371, 441, 16, sceneId, 0, 13020324,60000)
						if IsObjValid (sceneId,x270012_g_daotong) == 1 then
								NpcTalk(sceneId, x270012_g_daotong, "快来把水玉涂在上面！", -1)
						end
						if IsObjValid (sceneId,x270012_g_taotie) == 1 then
								NpcTalk(sceneId, x270012_g_taotie, "呼噜呼噜！", -1)
						end
						--SendSpecificImpactToUnit(sceneId, x270012_g_taotie, x270012_g_taotie, x270012_g_taotie, 8708, 0);
        		x270012_g_doing =8
        		x270012_g_doing2= 1
     elseif x270012_g_doing == 8   then
     				if IsObjValid (sceneId,x270012_g_daotong) == 1 then
     						SetMonsterDir(sceneId,x270012_g_daotong,60)
     						NpcTalk(sceneId, x270012_g_daotong, "成功了，拿到想要的东西了，稍后真人会帮你修好镜子。", -1)
     				end
     				if IsPlayerStateNormal(sceneId,x270012_g_accid) ==1 then
     						local misIndex = GetQuestIndexByID(sceneId, x270012_g_accid, x270012_g_MissionId)
								SetQuestByIndex(sceneId,x270012_g_accid,misIndex,0,1)
								SetQuestByIndex(sceneId,x270012_g_accid,misIndex,7,1)
								DeleteMonster (sceneId,x270012_g_daotong )
								DeleteMonster (sceneId,x270012_g_taotie )
						end
     				x270012_g_doing =9
     end
  	end
  end
end

function x270012_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x270012_g_doing = 0
	x270012_g_doing2= 0
	x270012_g_daotong =-1
	x270012_g_taotie =-1
	x270012_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0,StartTime2 = 0}
end
