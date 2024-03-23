--【主线】四海封王

--MisDescBegin
x203318_g_ScriptId = 203318
x203318_g_MissionIdPre = 770
x203318_g_MissionId = 771
x203318_g_LevelLess	= 	84
x203318_g_MissionIdNext = -1
x203318_g_Name	={}
x203318_g_ExtTarget={{type=20,n=1,target="向@npc_116000禀报战况"}}
x203318_g_MissionName="【剧场】四海封王"
x203318_g_MissionInfo="\t哈哈，如今不死魔君札兰丁也已经束手就擒，从此以后亚洲广阔的土地上，再也没人能够与我大蒙古帝国为敌，快将这个好消息禀报给大汗！"  --任务描述
x203318_g_MissionTarget=""		
x203318_g_MissionCompleted="\t#Y@myname#W，怎么？是大汗让你来的？是刚才封汗大典上大汗看出我神情异常了吧。"					--完成任务npc说话的话
x203318_g_ContinueInfo="\t庆功宴马上就要开始了！"
x203318_g_MissionHelp =	""
x203318_g_DemandItem ={}
x203318_g_ExpBonus = 626000
x203318_g_BonusMoney1 =840
x203318_g_BonusMoney2 =0
x203318_g_BonusMoney3 =0
x203318_g_BonusMoney4 =0
x203318_g_BonusMoney5 =96
x203318_g_BonusMoney6 =0
x203318_g_BonusItem	=	{}
x203318_g_BonusChoiceItem ={}
x203318_g_doing = 0
x203318_g_accid = -1
x203318_g_mengguwushi1 = -1
x203318_g_mengguwushi2 = -1
x203318_g_mengguwushi3 = -1
x203318_g_mengguwushi4 = -1
x203318_g_mengguwushi5 = -1
x203318_g_mengguwushi6 = -1
x203318_g_mengguwushi7 = -1
x203318_g_mengguwushi8 = -1
x203318_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
x203318_g_NpcGUID ={{ guid = 116000, name = "成吉思汗"}, {guid = 116003, name ="速不台"}}
--MisDescEnd
--**********************************

function x203318_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if IsQuestHaveDone(sceneId, selfId, x203318_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203318_g_MissionIdPre)> 0 then
		if IsHaveQuest(sceneId,selfId, x203318_g_MissionId) <= 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x203318_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x203318_g_MissionId, state, -1 )
		end
	end
end

function x203318_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203318_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203318_g_ExpBonus )
		end
		if x203318_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203318_g_BonusMoney1 )
		end
		if x203318_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203318_g_BonusMoney2 )
		end
		if x203318_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203318_g_BonusMoney3 )
		end
		if x203318_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203318_g_BonusMoney4 )
		end
		if x203318_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203318_g_BonusMoney5 )
		end
		if x203318_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203318_g_BonusMoney6 )
		end
		for i, item in x203318_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203318_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203318_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x203318_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203318_g_MissionId) > 0 then
		if which == -1 then   
			if x203318_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203318_g_MissionName)
						AddQuestText(sceneId,x203318_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203318_g_ScriptId, x203318_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203318_g_MissionName)
						AddQuestText(sceneId,x203318_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203318_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203318_g_ScriptId, x203318_g_MissionId);
			end
		elseif which == 1 then
			local misIndex = GetQuestIndexByID(sceneId,selfId,x203318_g_MissionId)                                                  
	    SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    BeginQuestEvent(sceneId)
			AddQuestText(sceneId,format("参观庆功宴   %d/1", GetQuestParam(sceneId,selfId,misIndex,0) ))
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"今天是我是最高兴的日子！")
			EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId, x203318_g_ScriptId, x203318_g_MissionId);
			x203318_g_chengjisihan =FindMonsterByGUID( sceneId,116000)
			x203318_g_guobaoyu =FindMonsterByGUID( sceneId,116009)
			x203318_g_hubilie=FindMonsterByGUID( sceneId,116007)
			x203318_g_badu =FindMonsterByGUID( sceneId,116019)
			x203318_g_mengge =FindMonsterByGUID( sceneId,116006)
			x203318_g_qiuchuji =FindMonsterByGUID( sceneId,116005)
			x203318_g_xuliewu =FindMonsterByGUID( sceneId,116004)
			x203318_g_subutai =FindMonsterByGUID( sceneId,116003)
			x203318_g_zhebie =FindMonsterByGUID( sceneId,116002)
	    --if x203318_g_doing == 0 then
	    		x203318_g_PROTECTINFO.StartTime = GetCurrentTime()
					x203318_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 203318, "OnScneneTimer", 1)
					if x203318_g_PROTECTINFO.ScneneTimerIndex >=0 then
							x203318_g_doing = 1
							x203318_g_accid = selfId
							x203318_g_mengguwushi1=CreateMonster(sceneId, 932,198,198,3,1,-1,-1,20,70000,0)
							x203318_g_mengguwushi2=CreateMonster(sceneId, 932,195,198,3,1,-1,-1,20,70000,0)
							x203318_g_mengguwushi3=CreateMonster(sceneId, 932,191,198,3,1,-1,-1,20,70000,0)
							x203318_g_mengguwushi4=CreateMonster(sceneId, 932,188,198,3,1,-1,-1,20,70000,0)
							x203318_g_mengguwushi5=CreateMonster(sceneId, 932,188,195,3,1,-1,-1,20,70000,0)
							x203318_g_mengguwushi6=CreateMonster(sceneId, 932,191,195,3,1,-1,-1,20,70000,0)
							x203318_g_mengguwushi7=CreateMonster(sceneId, 932,194,195,3,1,-1,-1,20,70000,0)
							x203318_g_mengguwushi8=CreateMonster(sceneId, 932,198,195,3,1,-1,-1,20,70000,0)
							--if IsObjValid (sceneId,x203318_g_guobaoyu) == 1 then
									--SetPatrolId(sceneId, x203318_g_guobaoyu, 7)
							--end
							if IsObjValid (sceneId,x203318_g_hubilie) == 1 then
									SetPatrolId(sceneId, x203318_g_hubilie, 9)
							end
							if IsObjValid (sceneId,x203318_g_badu) == 1 then
									SetPatrolId(sceneId, x203318_g_badu, 7)
							end
							if IsObjValid (sceneId,x203318_g_mengge) == 1 then
									SetPatrolId(sceneId, x203318_g_mengge, 10)
							end
							--if IsObjValid (sceneId,x203318_g_qiuchuji) == 1 then
									--SetPatrolId(sceneId, x203318_g_qiuchuji, 11)
							--end					
							if IsObjValid (sceneId,x203318_g_xuliewu) == 1 then
									SetPatrolId(sceneId, x203318_g_xuliewu, 8)
							end							
							--if IsObjValid (sceneId,x203318_g_subutai) == 1 then
									--SetPatrolId(sceneId, x203318_g_subutai, 8)
							--end	
							--if IsObjValid (sceneId,x203318_g_zhebie) == 1 then
									--SetPatrolId(sceneId, x203318_g_zhebie, 13)
							--end											
							x203318_g_chengjisihan =NPCId
							if IsObjValid (sceneId,x203318_g_chengjisihan) == 1 then
									NpcTalk(sceneId, x203318_g_chengjisihan, "勇士们，让我们举杯畅饮！", -1)
							end
          end
	   -- end
	  end
  elseif x203318_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203318_g_MissionName)
			AddQuestText(sceneId,x203318_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x203318_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203318_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x203318_g_MissionHelp )
			end
			x203318_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203318_g_ScriptId, x203318_g_MissionId);
  end
	
end
--**********************************

function x203318_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x203318_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x203318_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId,selfId,x203318_g_MissionId)
		if GetQuestParam(sceneId,selfId,misIndex,0) ==1 then 
	        return 1
	  end
	  return 0
end
--**********************************
function x203318_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203318_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203318_g_MissionId  )
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
		if x203318_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203318_g_MissionId, x203318_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x203318_Msg2toplayer( sceneId, selfId,0)
						if x203318_CheckSubmit(sceneId, selfId, NPCId) > 0 then
							local misIndex = GetQuestIndexByID(sceneId,selfId,x203318_g_MissionId)                                                  
	    				SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    				SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x203318_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203318_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203318_g_MissionId)
	  x203318_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x203318_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x203318_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203318_g_BonusChoiceItem do
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
function x203318_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203318_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203318_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203318_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203318_g_MissionId) > 0 then
				x203318_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203318_g_MissionId)
				x203318_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203318_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203318_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203318_g_MissionIdNext )	
end

function x203318_GetBonus( sceneId, selfId,NpcID)
	  if x203318_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203318_g_ExpBonus);
  	end
		if x203318_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203318_g_BonusMoney1 )
	  end
		if x203318_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203318_g_BonusMoney2 )
	  end
		if x203318_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203318_g_BonusMoney3 )
		end
		if x203318_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203318_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203318_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203318_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203318_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203318_g_BonusMoney6)
		end
end

function x203318_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x203318_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x203318_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203318_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203318_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203318_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203318_g_MissionName.."！", 0, 3)
				if x203318_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x203318_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x203318_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x203318_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x203318_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x203318_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x203318_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x203318_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x203318_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x203318_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x203318_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x203318_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x203318_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x203318_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x203318_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203318_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203318_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203318_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203318_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203318_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	
		if IsHaveQuest(sceneId,selfId, x203318_g_MissionId) > 0 then
			
				if npcGuid == x203318_g_NpcGUID[1].guid then	
					local misIndex = GetQuestIndexByID(sceneId,selfId,x203318_g_MissionId)
					if GetQuestParam(sceneId,selfId,misIndex,0) ==0 then 
						AddQuestNumText(sceneId, x203318_g_MissionId, "请列位功臣举起手中金杯",0,1)
					end
				elseif npcGuid == x203318_g_NpcGUID[2].guid then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203318_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203318_g_MissionId, state, -1 )
				end
		end
end

function x203318_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203318_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203318_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203318_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203318_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203318_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x203318_OnScneneTimer(sceneId)
	if x203318_g_doing==1   then
		if GetCurrentTime() - x203318_g_PROTECTINFO.StartTime >= 8   then
				x203318_g_doing = 2
				if IsObjValid (sceneId,x203318_g_chengjisihan) == 1 then
						NpcTalk(sceneId, x203318_g_chengjisihan, "我黄金家族的子子孙孙都已经长大成材，今天，我要将我所有的土地分给这些子孙们。", -1)
						SetMonsterDir(sceneId,x203318_g_badu,180)
				end
		end
	elseif x203318_g_doing==2   then
		if GetCurrentTime() - x203318_g_PROTECTINFO.StartTime >= 11   then
						x203318_g_doing = 3
						if IsObjValid (sceneId,x203318_g_subutai) == 1 then
								NpcTalk(sceneId, x203318_g_subutai, "但凭大汗吩咐。", -1)
						end
		end
	elseif x203318_g_doing==3   then
		if GetCurrentTime() - x203318_g_PROTECTINFO.StartTime >= 16   then
						x203318_g_doing = 4
						if IsObjValid (sceneId,x203318_g_chengjisihan) == 1 then
								NpcTalk(sceneId, x203318_g_chengjisihan, "旭烈兀！大战之中屡立奇功，虽处逆境而不惊，战功卓著，我今册封其为西亚之王，掌管我大蒙古帝国西边辽阔的疆土。", -1)
						end
            if IsObjValid (sceneId,x203318_g_xuliewu) == 1 then
								NpcTalk(sceneId, x203318_g_xuliewu, "多谢大汗，旭烈兀定不负大汗所望！", -1)
						end
						if IsObjValid (sceneId,x203318_g_mengguwushi3) == 1 then
								NpcTalk(sceneId, x203318_g_mengguwushi3, "成吉思汗！成吉思汗！", -1)
						end
						if IsObjValid (sceneId,x203318_g_mengguwushi1) == 1 then
								NpcTalk(sceneId, x203318_g_mengguwushi1, "成吉思汗！成吉思汗！", -1)
						end
            --if IsObjValid (sceneId,x203318_g_mingjiaodizi) == 1 then
            
            		--SetPatrolId(sceneId, x203318_g_mingjiaodizi, 22)
            --end
            --if IsObjValid (sceneId,x203318_g_mingjiaodizi2) == 1 then
            		--SetPatrolId(sceneId, x203318_g_mingjiaodizi2, 23)
            --end
            --if IsObjValid (sceneId,x203318_g_mingjiaodizi3) == 1 then
            		--SetPatrolId(sceneId, x203318_g_mingjiaodizi3, 24)
            --end
            --if IsObjValid (sceneId,x203318_g_mingjiaodizi4) == 1 then
            		--SetPatrolId(sceneId, x203318_g_mingjiaodizi4, 25)
            --end
            --if IsObjValid (sceneId,x203318_g_mingjiaodizi5) == 1 then
            	--	SetPatrolId(sceneId, x203318_g_mingjiaodizi5, 26)
            --end
            --if IsObjValid (sceneId,x203318_g_mingjiaodizi6) == 1 then
            		--SetPatrolId(sceneId, x203318_g_mingjiaodizi6, 27)
            --end
		end
	elseif x203318_g_doing==4   then
		if GetCurrentTime() - x203318_g_PROTECTINFO.StartTime >= 25  then
						x203318_g_doing = 5
						if IsObjValid (sceneId,x203318_g_chengjisihan) == 1 then
								NpcTalk(sceneId, x203318_g_chengjisihan, "蒙哥，勇而有谋，数次妙计破敌，居功甚伟！今封蒙哥为东亚之王！", -1)								
						end
						 if IsObjValid (sceneId,x203318_g_mengge) == 1 then
								NpcTalk(sceneId, x203318_g_mengge, "谢大汗，蒙哥一定永守蒙古疆土！", -1)
						end
						if IsObjValid (sceneId,x203318_g_mengguwushi6) == 1 then
								NpcTalk(sceneId, x203318_g_mengguwushi6, "成吉思汗！成吉思汗！", -1)
						end
            if IsObjValid (sceneId,x203318_g_mengguwushi4) == 1 then
								NpcTalk(sceneId, x203318_g_mengguwushi4, "成吉思汗！成吉思汗！", -1)
						end						
		end
	elseif x203318_g_doing==5   then
	 if GetCurrentTime() - x203318_g_PROTECTINFO.StartTime >= 35  then
						x203318_g_doing = 6
						if IsObjValid (sceneId,x203318_g_chengjisihan) == 1 then
								NpcTalk(sceneId, x203318_g_chengjisihan, "拔都，勇猛无比，军纪严明，作战之时身先士卒！今，封拔都为欧洲之王！", -1)								
						end
						if IsObjValid (sceneId,x203318_g_badu) == 1 then
								NpcTalk(sceneId, x203318_g_badu, "拔都，多谢大汗！", -1)
						end
						if IsObjValid (sceneId,x203318_g_mengguwushi6) == 1 then
								NpcTalk(sceneId, x203318_g_mengguwushi6, "……？……？", -1)
						end
						if IsObjValid (sceneId,x203318_g_subutai) == 1 then
								NpcTalk(sceneId, x203318_g_subutai, "欧洲？！什么？！", -1)
						end
						if IsObjValid (sceneId,x203318_g_mengguwushi3) == 1 then
								NpcTalk(sceneId, x203318_g_mengguwushi3, "……？……？", -1)
						end
	 end
	elseif x203318_g_doing==6  then
		if GetCurrentTime() - x203318_g_PROTECTINFO.StartTime >= 45   then
						x203318_g_doing = 7
						if IsObjValid (sceneId,x203318_g_chengjisihan) == 1 then
								NpcTalk(sceneId, x203318_g_chengjisihan, "我希望黄金家族的子孙们牢牢记住，一个民族，只有吸收更多的文化，更多的人民，才能更加强大。亡诸国者并非是我成吉思汗，成就庞大蒙古汗国的也并非是我，而是各国、各民族，千千万万渴望和平与安定的人民。", -1)
						end
						if IsObjValid (sceneId,x203318_g_mengguwushi1) == 1 then
								NpcTalk(sceneId, x203318_g_mengguwushi1, "成吉思汗！成吉思汗！", -1)
						end
						if IsObjValid (sceneId,x203318_g_mengguwushi4) == 1 then
								NpcTalk(sceneId, x203318_g_mengguwushi4, "成吉思汗！成吉思汗！", -1)
						end
		end
	elseif x203318_g_doing==7 then
	  if GetCurrentTime() - x203318_g_PROTECTINFO.StartTime >= 55  then
						x203318_g_doing = 8
						if IsObjValid (sceneId,x203318_g_chengjisihan) == 1 then
								NpcTalk(sceneId, x203318_g_chengjisihan, "昨天我做了一个梦，梦见了我的安答札木合，梦见了屈出律，还，梦见了很多很多人。如今，他们都不在了，我，要感谢这些曾经与我为敌的人，是他们，造就了我，今天的成吉思汗！在这里，我向天，敬他们一杯！", -1)
						end
						if IsObjValid (sceneId,x203318_g_mengge) == 1 then
								NpcTalk(sceneId, x203318_g_mengge, "大汗！", -1)
						end
						if IsObjValid (sceneId,x203318_g_xuliewu) == 1 then
								NpcTalk(sceneId, x203318_g_xuliewu, "大汗……？", -1)
						end
						if IsObjValid (sceneId,x203318_g_hubilie) == 1 then
								NpcTalk(sceneId, x203318_g_hubilie, "大汗……", -1)
						end
						if IsObjValid (sceneId,x203318_g_badu) == 1 then
								NpcTalk(sceneId, x203318_g_badu, "……！", -1)
						end
			end
	elseif x203318_g_doing==8 then
			if GetCurrentTime() - x203318_g_PROTECTINFO.StartTime >= 70  then
				x203318_g_doing=9
				if x203318_g_doing ==9 then
				x203318_CloseTimer(sceneId, x203318_g_PROTECTINFO.ScneneTimerIndex)
				end
			end
	  end
 end




--**********************************
--关闭计时器
--**********************************
function x203318_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x203318_g_doing =0
	x203318_g_accid = -1
	x203318_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}   --初试时间置为零
	SetPos(sceneId,x203318_g_badu,186,200)
	SetPos(sceneId,x203318_g_xuliewu,186,194)
	SetPos(sceneId,x203318_g_mengge,201,200)
	SetPos(sceneId,x203318_g_hubilie,201,194)
	SetPatrolId(sceneId, x203318_g_hubilie, -1)
	SetPatrolId(sceneId, x203318_g_badu, -1)
  SetPatrolId(sceneId, x203318_g_mengge, -1)
	SetPatrolId(sceneId, x203318_g_xuliewu, -1)
	SetMonsterDir(sceneId,x203318_g_badu,180)
	SetMonsterDir(sceneId,x203318_g_xuliewu,180)
	SetMonsterDir(sceneId,x203318_g_mengge,180)
	SetMonsterDir(sceneId,x203318_g_hubilie,180)
	x203318_g_mengguwushi1 = -1
  x203318_g_mengguwushi2 = -1
  x203318_g_mengguwushi3 = -1
  x203318_g_mengguwushi4 = -1
  x203318_g_mengguwushi5 = -1
  x203318_g_mengguwushi6 = -1
end