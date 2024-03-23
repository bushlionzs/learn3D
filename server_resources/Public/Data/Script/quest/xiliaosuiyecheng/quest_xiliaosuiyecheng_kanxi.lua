--【剧场】最强的劲敌

--MisDescBegin
x203312_g_ScriptId = 203312
x203312_g_MissionIdPre ={623,624}
x203312_g_MissionId = 625
x203312_g_LevelLess	= 	65 
x203312_g_MissionIdNext = 626
x203312_g_Name	={}
x203312_g_ExtTarget={{type=20,n=1,target="到@npc_113123处寻找逃亡的屈出律"}}
x203312_g_MissionName="【剧场】最强的劲敌"
x203312_g_MissionInfo="\t大营的一侧有条小路，屈出律一定是从那里跑了，想不到堂堂的太阳之子竟然不能像男子汉一样战死，反而苟且偷生。\n\t绝不能再让他逃走，快追！"  --任务描述
x203312_g_MissionTarget=""		
x203312_g_MissionCompleted="\t（成吉思汗沉吟半响，自言自语道）\n\t摩诃末？亚洲之王……？"					--完成任务npc说话的话
x203312_g_ContinueInfo="\t屈出律应该还没逃远，速度去追上他！"
x203312_g_MissionHelp =	""
x203312_g_DemandItem ={}
x203312_g_ExpBonus = 248000
x203312_g_BonusMoney1 =650
x203312_g_BonusMoney2 =0
x203312_g_BonusMoney3 =0
x203312_g_BonusMoney4 =0
x203312_g_BonusMoney5 =76
x203312_g_BonusMoney6 =0
x203312_g_BonusItem	=	{}
x203312_g_BonusChoiceItem ={}
x203312_g_doing = 0
x203312_g_mohemo = -1
x203312_g_zhalanding = -1
x203312_g_quchulv = -1
x203312_g_shibing1 = -1
x203312_g_shibing2 = -1
x203312_g_NpcGUID ={{ guid = 113001, name = "成吉思汗"}}
x203312_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
--MisDescEnd
--**********************************

function x203312_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x203312_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203312_g_MissionIdPre[1])> 0 and IsQuestHaveDone(sceneId, selfId, x203312_g_MissionIdPre[2])> 0 then
		if IsHaveQuest(sceneId,selfId, x203312_g_MissionId) <= 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x203312_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x203312_g_MissionId, state, -1 )
		end
	end
end

function x203312_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203312_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203312_g_ExpBonus )
		end
		if x203312_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203312_g_BonusMoney1 )
		end
		if x203312_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203312_g_BonusMoney2 )
		end
		if x203312_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203312_g_BonusMoney3 )
		end
		if x203312_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203312_g_BonusMoney4 )
		end
		if x203312_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203312_g_BonusMoney5 )
		end
		if x203312_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203312_g_BonusMoney6 )
		end
		for i, item in x203312_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203312_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203312_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x203312_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203312_g_MissionId) > 0 then
			if x203312_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203312_g_MissionName)
						AddQuestText(sceneId,x203312_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203312_g_ScriptId, x203312_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203312_g_MissionName)
						AddQuestText(sceneId,x203312_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203312_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203312_g_ScriptId, x203312_g_MissionId);
			end
  elseif x203312_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203312_g_MissionName)
			AddQuestText(sceneId,x203312_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x203312_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203312_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x203312_g_MissionHelp )
			end
			x203312_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203312_g_ScriptId, x203312_g_MissionId);
  end
	
end
--**********************************

function x203312_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x203312_g_MissionIdPre[1])> 0 and IsQuestHaveDone(sceneId, selfId, x203312_g_MissionIdPre[2])> 0 then
					return 1
		end
		return 0

end
--**********************************
function x203312_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId, selfId, x203312_g_MissionId)
		if GetQuestParam(sceneId,selfId,misIndex,0) ==1 then 
	        return 1
	  end
	  return 0
	
end
--**********************************
function x203312_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203312_g_MissionId) > 0 then
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
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203312_g_MissionId  )
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
		if x203312_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203312_g_MissionId, x203312_g_ScriptId, 1, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x203312_Msg2toplayer( sceneId, selfId,0)
		  		end
	 	end                                                                    
	     
end
--**********************************

function x203312_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203312_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203312_g_MissionId)
	  x203312_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x203312_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x203312_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203312_g_BonusChoiceItem do
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
function x203312_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203312_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203312_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203312_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203312_g_MissionId) > 0 then
				x203312_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203312_g_MissionId)
				x203312_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203312_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203312_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203312_g_MissionIdNext )	
end

function x203312_GetBonus( sceneId, selfId,NpcID)
	  if x203312_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203312_g_ExpBonus);
  	end
		if x203312_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203312_g_BonusMoney1 )
	  end
		if x203312_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203312_g_BonusMoney2 )
	  end
		if x203312_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203312_g_BonusMoney3 )
		end
		if x203312_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203312_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203312_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203312_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203312_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203312_g_BonusMoney6)
		end
end

function x203312_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x203312_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x203312_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203312_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203312_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203312_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203312_g_MissionName.."！", 0, 3)
				if x203312_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x203312_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x203312_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x203312_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x203312_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x203312_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x203312_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x203312_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x203312_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x203312_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x203312_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x203312_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x203312_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x203312_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x203312_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end


function x203312_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
		if IsHaveQuest(sceneId,selfId, x203312_g_MissionId) > 0 then
			if x203312_g_doing == 0 then
				if x203312_CheckSubmit(sceneId, selfId) <= 0 then
					--if GetName(sceneId,x203312_g_sunfeihu)~="孙飞虎" then
							local misIndex = GetQuestIndexByID(sceneId, selfId, x203312_g_MissionId)
							SetQuestByIndex(sceneId,selfId,misIndex,0,1)
							SetQuestByIndex(sceneId,selfId,misIndex,7,1)
							x203312_CheckSubmit( sceneId, selfId)
								x203312_g_PROTECTINFO.StartTime = GetCurrentTime()
							x203312_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 203312, "OnScneneTimer", 1)
							if x203312_g_PROTECTINFO.ScneneTimerIndex >= 0 then
									x203312_g_doing = 1
									x203312_g_mohemo=CreateMonster(sceneId, 1715,60,178,3,1,-1,-1,20,30000,180,"摩诃末")
									x203312_g_zhalanding=CreateMonster(sceneId, 1716,56,176,3,1,-1,-1,20,30000,180,"扎兰丁")
									x203312_g_quchulv=CreateMonster(sceneId, 1717,64,179,3,1,-1,-1,20,30000,180,"屈出律")
									x203312_g_shibing1=CreateMonster(sceneId, 1718,61,181,3,1,-1,-1,20,30000,220,"突厥士兵")
									x203312_g_shibing2=CreateMonster(sceneId, 1718,58,180,3,1,-1,-1,20,30000,220,"突厥士兵")
							end
					--end
				end
			
			end
		end

end

function x203312_ProcTiming(sceneId, selfId, ScriptId, MissionId)
end

function x203312_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
end

function x203312_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203312_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x203312_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203312_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203312_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203312_g_MissionId, state, -1 )
		end
end

function x203312_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203312_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203312_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203312_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203312_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203312_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x203312_OnScneneTimer(sceneId)
	if x203312_g_doing==1   then
		if GetCurrentTime() - x203312_g_PROTECTINFO.StartTime >= 3   then
						x203312_g_doing = 2
						if IsObjValid (sceneId,x203312_g_zhalanding) == 1 then
								NpcTalk(sceneId, x203312_g_zhalanding, "哈哈，又来了一个！", -1)
						end
		end
	elseif x203312_g_doing==2   then
		if GetCurrentTime() - x203312_g_PROTECTINFO.StartTime >= 6   then
						x203312_g_doing = 3
						if IsObjValid (sceneId,x203312_g_mohemo) == 1 then
								NpcTalk(sceneId, x203312_g_mohemo, "你很幸运！", -1)
						end
		end
	elseif x203312_g_doing==3   then
		if GetCurrentTime() - x203312_g_PROTECTINFO.StartTime >= 10   then
						x203312_g_doing = 4
						if IsObjValid (sceneId,x203312_g_zhalanding) == 1 then
								NpcTalk(sceneId, x203312_g_zhalanding, "我们需要一个活口去给铁木真带口信，所以你可以不死了！", -1)
						end
		end
	elseif x203312_g_doing==4   then
		if GetCurrentTime() - x203312_g_PROTECTINFO.StartTime >= 15   then
						x203312_g_doing = 5
						if IsObjValid (sceneId,x203312_g_quchulv) == 1 then
								NpcTalk(sceneId, x203312_g_quchulv, "不行，放了谁也不能放了这个！每次都是这个人出现坏了我的事！", -1)
						end
		end
	elseif x203312_g_doing==5   then
		if GetCurrentTime() - x203312_g_PROTECTINFO.StartTime >= 20   then
						x203312_g_doing = 6
						if IsObjValid (sceneId,x203312_g_zhalanding) == 1 then
								NpcTalk(sceneId, x203312_g_zhalanding, "放轻松些！在我眼里，他，还有这些尸体，都一样！", -1)
						end
		end
	elseif x203312_g_doing==6   then
		if GetCurrentTime() - x203312_g_PROTECTINFO.StartTime >= 25   then
						x203312_g_doing = 7
						if IsObjValid (sceneId,x203312_g_mohemo) == 1 then
								NpcTalk(sceneId, x203312_g_mohemo, "我一直在思考，怎样才能成为真正的亚洲之王。现在看来，机会终于来了，回去告诉铁木真，我们在花剌子模等着他，到时候，神会给我明示！", -1)
						end
		end
	elseif x203312_g_doing==7   then
		if GetCurrentTime() - x203312_g_PROTECTINFO.StartTime >= 31   then
						x203312_g_doing = 8
						x203312_CloseTimer(sceneId, x203312_g_PROTECTINFO.ScneneTimerIndex)
		end
	end
end


--**********************************
--关闭计时器
--**********************************
function x203312_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x203312_g_doing = 0
	x203312_g_mohemo = -1
	x203312_g_zhalanding = -1
	x203312_g_quchulv = -1
	x203312_g_shibing1 = -1
	x203312_g_shibing2 = -1
	x203312_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
end