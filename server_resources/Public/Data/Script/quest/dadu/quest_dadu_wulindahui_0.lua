--【主线】智取药材

--MisDescBegin
x270003_g_ScriptId = 270003
x270003_g_MissionIdPre =3565
x270003_g_MissionId = 3566
x270003_g_LevelLess	= 	50 
x270003_g_MissionIdNext = 3567
x270003_g_Name	={}
x270003_g_ExtTarget={{type=20,n=1,target="从@npc_136255处要一坛杜康，到@npc_136499处使用诱走丐帮弟子后到@npc_141008处得到@itemid_13020310"}}
x270003_g_MissionName="【主线】智取药材"
x270003_g_MissionInfo="\t没有时间去等药铺的药材了，我的徒弟不能等了。既然药材都被丐帮买走了，那么就去他们那里碰碰运气吧，或许能找到药。在事情还没有弄清楚之前先不要和丐帮动手，悄悄的给我带回一个鹿茸就行。如果有看守的话，一坛酒或许能解决问题。去跟我的徒弟俞岱岩要一坛杜康，我知道他有这东西。"  --任务描述
x270003_g_MissionTarget=""		
x270003_g_MissionCompleted="\t真及时，如果再晚些时候，我的两个徒儿怕是救不回来了！"					--完成任务npc说话的话
x270003_g_ContinueInfo="\t你去过丐帮了吗？"
x270003_g_MissionHelp =	""
x270003_g_DemandItem ={{id=13020309,num=1},{id=13020310,num=1}}
x270003_g_BonusMoney1 =376
x270003_g_BonusMoney2 =0
x270003_g_BonusMoney3 =0
x270003_g_BonusMoney4 =0
x270003_g_BonusMoney5 =61
x270003_g_BonusMoney6 =0
x270003_g_BonusItem	=	{}
x270003_g_BonusChoiceItem ={}
x270003_g_ExpBonus = 145000
x270003_g_doing = 0
x270003_g_gaibangkanshou = -1
x270003_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
x270003_g_NpcGUID ={{ guid = 136255, name = "俞岱岩"} }
x270003_g_GroupPoint	={ {type=10,id =14,target = "药材堆"} }
--MisDescEnd
--**********************************

function x270003_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x270003_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x270003_g_MissionIdPre)> 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x270003_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x270003_g_MissionId, state, -1 )
	end
end

function x270003_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x270003_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x270003_g_ExpBonus )
		end
		if x270003_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x270003_g_BonusMoney1 )
		end
		if x270003_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x270003_g_BonusMoney2 )
		end
		if x270003_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x270003_g_BonusMoney3 )
		end
		if x270003_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x270003_g_BonusMoney4 )
		end
		if x270003_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x270003_g_BonusMoney5 )
		end
		if x270003_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x270003_g_BonusMoney6 )
		end
		for i, item in x270003_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x270003_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x270003_ProcEventEntry(sceneId, selfId, NPCId, MissionId, which)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x270003_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x270003_g_MissionId) > 0 then
		if which == -1 then
			if x270003_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270003_g_MissionName)
						AddQuestText(sceneId,x270003_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x270003_g_ScriptId, x270003_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270003_g_MissionName)
						AddQuestText(sceneId,x270003_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x270003_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x270003_g_ScriptId, x270003_g_MissionId);
			end
		elseif which == 1 then
				if GetItemCount(sceneId,selfId,x270003_g_DemandItem[1].id) < x270003_g_DemandItem[1].num then
						BeginAddItem(sceneId)
						AddItem( sceneId, x270003_g_DemandItem[1].id, x270003_g_DemandItem[1].num )
  					local ret = EndAddItem(sceneId,selfId)
    				if ret > 0 then
    					AddItemListToPlayer(sceneId,selfId)
    					BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"\t原来师父他老人家一直都知道我偷着喝酒，下次我不敢了！")
							EndQuestEvent()
							DispatchQuestEventList(sceneId, selfId, NPCId, x270003_g_ScriptId, x270003_g_MissionId);
							Msg2Player(sceneId, selfId, "得到一坛#G杜康酒#Y   1/1", 0, 3)
    				else
    					Msg2Player(sceneId, selfId, "包裹已满", 0, 3)
    				end
    		end
    end
  elseif x270003_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x270003_g_MissionName)
			AddQuestText(sceneId,x270003_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x270003_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x270003_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x270003_g_MissionHelp )
			end
			x270003_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x270003_g_ScriptId, x270003_g_MissionId);
  end
	
end
--**********************************

function x270003_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x270003_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x270003_CheckSubmit( sceneId, selfId, NPCId)
		if GetItemCount(sceneId,selfId,x270003_g_DemandItem[2].id) >= x270003_g_DemandItem[2].num then
				local misIndex = GetQuestIndexByID(sceneId,selfId,x270003_g_MissionId)
				SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    	SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	      return 1
	  else
	  		local misIndex = GetQuestIndexByID(sceneId,selfId,x270003_g_MissionId)
				SetQuestByIndex(sceneId,selfId,misIndex,0,0)
	    	SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	  end
	  return 0
	
end
--**********************************
function x270003_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x270003_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x270003_g_MissionId  )
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
		if x270003_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x270003_g_MissionId, x270003_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x270003_Msg2toplayer( sceneId, selfId,0)
		  		end
	 	end                                                                    
	     
end
--**********************************

function x270003_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x270003_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x270003_g_MissionId)
	  x270003_Msg2toplayer( sceneId, selfId,1)
	  for i, item in x270003_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
		end
			
end
--**********************************
function x270003_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x270003_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x270003_g_BonusChoiceItem do
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
function x270003_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x270003_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270003_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270003_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x270003_g_MissionId) > 0 then
				x270003_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x270003_g_MissionId)
				x270003_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x270003_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x270003_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		for i, item in x270003_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
				end
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x270003_g_MissionIdNext )	
end

function x270003_GetBonus( sceneId, selfId,NpcID)
	  if x270003_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x270003_g_ExpBonus);
  	end
		if x270003_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x270003_g_BonusMoney1 )
	  end
		if x270003_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x270003_g_BonusMoney2 )
	  end
		if x270003_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x270003_g_BonusMoney3 )
		end
		if x270003_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x270003_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x270003_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x270003_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x270003_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x270003_g_BonusMoney6)
		end
end

function x270003_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x270003_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x270003_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x270003_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x270003_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x270003_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x270003_g_MissionName.."！", 0, 3)
				if x270003_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x270003_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x270003_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x270003_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x270003_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x270003_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x270003_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x270003_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x270003_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x270003_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x270003_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x270003_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x270003_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x270003_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x270003_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x270003_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x270003_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x270003_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x270003_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x270003_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x270003_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x270003_g_MissionId) > 0 then
			if GetItemCount(sceneId,selfId,x270003_g_DemandItem[1].id) < x270003_g_DemandItem[1].num then
				AddQuestNumText(sceneId, x270003_g_MissionId, "给我一坛杜康",0, 1)
			end
		end
end

function x270003_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x270003_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x270003_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x270003_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x270003_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x270003_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x270003_useitem(sceneId,selfId)
		local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )
		local distanceRet = 25 - (95 - PlayerPosX) * (95 - PlayerPosX) - (214 - PlayerPosZ) * (214 - PlayerPosZ)
		if distanceRet >= 0 then
				if x270003_g_doing==0   then
						x270003_g_PROTECTINFO.StartTime = GetCurrentTime()
						x270003_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 270003, "OnScneneTimer", 1)
						if x270003_g_PROTECTINFO.ScneneTimerIndex >= 0 then
								x270003_g_doing = 1
								x270003_g_gaibangkanshou =FindMonsterByGUID( sceneId,136269)
								if IsObjValid (sceneId,x270003_g_gaibangkanshou) == 1 then
										SetPatrolId(sceneId, x270003_g_gaibangkanshou, 0)
								end
						end
				end
				DelItem( sceneId,selfId,x270003_g_DemandItem[1].id, x270003_g_DemandItem[1].num )
				return 1
		else
				Msg2Player(sceneId, selfId, "这里无法使用这个物品", 0, 3)
				return 0
		end
end


function x270003_Growpoint(sceneId,selfId,which)
		if IsHaveQuest(sceneId,selfId, x270003_g_MissionId) <= 0 then
				return 1
		end
		if which ==0 then
				if x270003_g_doing > 0 then
					if GetItemCount(sceneId,selfId,x270003_g_DemandItem[2].id) < x270003_g_DemandItem[2].num then
							return 0
					else
							Msg2Player(sceneId, selfId, "你已经拿到了药材", 0, 3)
							return 1
					end
				else
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"\t当你走进这堆药材，旁边看守的丐帮弟子一直在看着你。你想起了张真人的话，先不与丐帮发生冲突，还是想个办法把他引走吧。")
					EndQuestEvent()
					DispatchQuestEventList(sceneId, selfId, selfId, x270003_g_ScriptId, x270003_g_MissionId);
					return 1
				end
		elseif which == 1 then
				if GetItemCount(sceneId,selfId,x270003_g_DemandItem[2].id) < x270003_g_DemandItem[2].num then
						BeginAddItem(sceneId)
						AddItem( sceneId, x270003_g_DemandItem[2].id, x270003_g_DemandItem[2].num )
  					local ret = EndAddItem(sceneId,selfId)
    				if ret > 0 then
    					AddItemListToPlayer(sceneId,selfId)
    					Msg2Player(sceneId, selfId, "得到了#G鹿茸#Y   1/1", 0, 3)
    					x270003_CheckSubmit( sceneId, selfId)
    				else
    					Msg2Player(sceneId, selfId, "包裹已满", 0, 3)
    				end
    		end
    		return 0
    end
		
end

function x270003_OnScneneTimer(sceneId)
	if x270003_g_gaibangkanshou < 0 then
			x270003_CloseTimer(sceneId, x270003_g_PROTECTINFO.ScneneTimerIndex)
			return
	end
	if x270003_g_doing==1   then
		if GetCurrentTime() - x270003_g_PROTECTINFO.StartTime >= 1   then
						x270003_g_doing = 2
						if IsObjValid (sceneId,x270003_g_gaibangkanshou) == 1 then
								NpcTalk(sceneId, x270003_g_gaibangkanshou, "好香的酒味啊！", -1)
						end
		end
	elseif x270003_g_doing==2   then
		if GetCurrentTime() - x270003_g_PROTECTINFO.StartTime >= 5   then
						x270003_g_doing = 3
						if IsObjValid (sceneId,x270003_g_gaibangkanshou) == 1 then
								NpcTalk(sceneId, x270003_g_gaibangkanshou, "一定是什么人不小心把酒忘在这里了！", -1)
						end
		end
	elseif x270003_g_doing==3   then
		if GetCurrentTime() - x270003_g_PROTECTINFO.StartTime >= 9   then
						x270003_g_doing = 4
						if IsObjValid (sceneId,x270003_g_gaibangkanshou) == 1 then
								NpcTalk(sceneId, x270003_g_gaibangkanshou, "真的有一坛杜康！如此美酒不喝它就是罪过了。", -1)
						end
		end
	elseif x270003_g_doing==4   then
		if GetCurrentTime() - x270003_g_PROTECTINFO.StartTime >= 13   then
						x270003_g_doing = 5
						if IsObjValid (sceneId,x270003_g_gaibangkanshou) == 1 then
								NpcTalk(sceneId, x270003_g_gaibangkanshou, "对酒当歌，人生几何？", -1)
						end
		end
	elseif x270003_g_doing==5   then
		if GetCurrentTime() - x270003_g_PROTECTINFO.StartTime >= 17   then
						x270003_g_doing = 6
						if IsObjValid (sceneId,x270003_g_gaibangkanshou) == 1 then
								NpcTalk(sceneId, x270003_g_gaibangkanshou, "譬如朝露，去日苦多。", -1)
						end
		end
	elseif x270003_g_doing==6   then
		if GetCurrentTime() - x270003_g_PROTECTINFO.StartTime >= 21   then
						x270003_g_doing = 7
						if IsObjValid (sceneId,x270003_g_gaibangkanshou) == 1 then
								NpcTalk(sceneId, x270003_g_gaibangkanshou, "慨当以慷，忧思难忘。", -1)
						end
		end
	elseif x270003_g_doing==7   then
		if GetCurrentTime() - x270003_g_PROTECTINFO.StartTime >= 25   then
						x270003_g_doing = 8
						if IsObjValid (sceneId,x270003_g_gaibangkanshou) == 1 then
								NpcTalk(sceneId, x270003_g_gaibangkanshou, "何以解忧，唯有杜康。", -1)
						end
		end
	elseif x270003_g_doing==8 then
			if GetCurrentTime() - x270003_g_PROTECTINFO.StartTime >= 42   then
				x270003_g_doing=9
				x270003_CloseTimer(sceneId, x270003_g_PROTECTINFO.ScneneTimerIndex)
			end
	end
end


--**********************************
--关闭计时器
--**********************************
function x270003_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x270003_g_doing =0
	if IsObjValid (sceneId,x270003_g_gaibangkanshou) == 1 then
			SetPatrolId(sceneId, x270003_g_gaibangkanshou, -1)
	end
	x270003_g_gaibangkanshou =-1
end