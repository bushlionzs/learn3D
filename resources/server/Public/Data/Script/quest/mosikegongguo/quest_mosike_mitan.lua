--莫斯科公国 立陶宛大公杀怪

--MisDescBegin
x203325_g_ScriptId = 203325
x203325_g_MissionIdPre = 805
x203325_g_MissionId = 806
x203325_g_LevelLess	= 88
x203325_g_MissionIdNext = 807
x203325_g_DemandKill ={{id=2137,num=1}}
x203325_g_Name	={"莫斯科密探"}
x203325_g_ExtTarget={{type=20,n=1,target="击败@npc_117014"}}
x203325_g_MissionName="【剧场】立陶宛女大公<二>"
x203325_g_MissionInfo="\t从刚才我们谈话的时候，我就发现那里有一个卫兵一直探头探脑，似乎是在偷听我们的谈话，他不是我的人，肯定是莫斯科大公派来监视我的，千万不能让他泄露了我们的密约！"  --任务描述
x203325_g_MissionTarget="击败@npc_117014"		
x203325_g_MissionCompleted="\t真不愧是大蒙古国的勇士，三两下就收拾了这个狗腿子，剩下的事情交给我好了。"
x203325_g_ContinueInfo="\t怎么？那家伙不是莫斯科大公的眼线么？"
x203325_g_MissionHelp =	""
--x203325_g_DemandItem ={{id=13030081,num=1}}
x203325_g_ExpBonus =684000
x203325_g_BonusMoney1 =880
x203325_g_BonusMoney2 =0
x203325_g_BonusMoney3 =0
x203325_g_BonusMoney4 =0
x203325_g_BonusMoney5 =106
x203325_g_BonusMoney6 =0
x203325_g_BonusItem	={}
x203325_g_BonusChoiceItem ={}
x203325_g_NpcGUID = 117014
--x203325_g_Impact1 = 2092
x203325_g_npcid = 0
x203325_g_chaerke =0
x203325_g_dog =0
x203325_g_pangxie = 0
x203325_g_acceptid =0
--MisDescEnd
--**********************************

function x203325_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    --DelQuest(sceneId, selfId, x203325_g_MissionId)
	if IsQuestHaveDone(sceneId, selfId, x203325_g_MissionId) > 0 then
		return 
	else
	if IsQuestHaveDone(sceneId, selfId, x203325_g_MissionIdPre)> 0 then 
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x203325_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x203325_g_MissionId, state, -1 )
	end
	end
end

function x203325_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203325_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203325_g_ExpBonus )
		end
		if x203325_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203325_g_BonusMoney1 )
		end
		if x203325_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203325_g_BonusMoney2 )
		end
		if x203325_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203325_g_BonusMoney3 )
		end
		if x203325_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203325_g_BonusMoney4 )
		end
		if x203325_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203325_g_BonusMoney5 )
		end
		if x203325_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203325_g_BonusMoney6 )
		end
		for i, item in x203325_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203325_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

--任务入口函数

--**********************************
function x203325_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
    x203325_g_npcid =   NPCId
	if IsQuestHaveDone(sceneId, selfId, x203325_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203325_g_MissionId) > 0 then
			if x203325_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
            
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203325_g_MissionName)
						AddQuestText(sceneId,x203325_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203325_g_ScriptId, x203325_g_MissionId);
			else
          
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203325_g_MissionName)
						AddQuestText(sceneId,x203325_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203325_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203325_g_ScriptId, x203325_g_MissionId);
			end
  elseif x203325_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203325_g_MissionName)
			AddQuestText(sceneId,x203325_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x203325_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203325_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x203325_g_MissionHelp )
			end
			x203325_DispatchMissionInfo( sceneId, selfId, NPCId )
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203325_g_ScriptId, x203325_g_MissionId);
  end
end
--**********************************
function x203325_ProcAcceptCheck(sceneId, selfId, NPCId)
	if IsQuestHaveDone(sceneId, selfId, x203325_g_MissionId) > 0 then
		return 0
	elseif GetLevel(sceneId, selfId)< x203325_g_LevelLess then
		return 0
	end
	return 1
end
--**********************************
function x203325_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x203325_g_MissionId)
	if GetQuestParam(sceneId,selfId,misIndex,0) == x203325_g_DemandKill[1].num then
             
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	        return 1
	end
	return 0
end
--**********************************
function x203325_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203325_g_MissionId) > 0 then
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
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203325_g_MissionId  )
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
		
		if x203325_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
		x203325_g_mitan =FindMonsterByGUID( sceneId,117014)
					local retmiss = AddQuest( sceneId, selfId, x203325_g_MissionId, x203325_g_ScriptId, 1, 0, 0)  --添加一个任务返回结果   --杀怪 ，
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)                                         -- 3 显示在哪里；0是？
						return 0
					else
						if IsObjValid (sceneId,x203325_g_mitan) == 1 then                                                       -- npc有效（存在）
							--local x203325_g_liliang =FindMonsterByGUID( sceneId,117014)
			  			SetMonsterCamp(sceneId,x203325_g_mitan,21)
			  		end
            --CreateMonster(sceneId, 811,132,70,5,1,-1,-1,21,120000)
						x203325_Msg2toplayer( sceneId, selfId,0)
						--if x203325_CheckSubmit(sceneId, selfId, NPCId) > 0 then
						local misIndex = GetQuestIndexByID(sceneId,selfId,x203325_g_MissionId)                                                  
	    			SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************
function x203325_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203325_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203325_g_MissionId)
	  x203325_Msg2toplayer( sceneId, selfId,1)
end
--**********************************
function x203325_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x203325_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203325_g_BonusChoiceItem do
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
function x203325_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId)
	if IsHaveQuest(sceneId,selfId, x203325_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203325_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203325_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203325_g_MissionId) > 0 then
				x203325_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203325_g_MissionId)
                x203325_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203325_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203325_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		    end
    		    EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
				CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203325_g_MissionIdNext )	
   end
end

function x203325_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
   
end

function x203325_GetBonus( sceneId, selfId,NpcID)
	  if x203325_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203325_g_ExpBonus);
  	end
		if x203325_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203325_g_BonusMoney1 )
	  end
		if x203325_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203325_g_BonusMoney2 )
	  end
		if x203325_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203325_g_BonusMoney3 )
		end
		if x203325_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203325_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203325_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203325_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203325_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203325_g_BonusMoney6)
		end
end

function x203325_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x203325_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x203325_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203325_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203325_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203325_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203325_g_MissionName.."！", 0, 3)
				if x203325_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x203325_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x203325_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x203325_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x203325_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x203325_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x203325_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x203325_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x203325_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x203325_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x203325_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x203325_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x203325_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x203325_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

--**********************************

function x203325_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
   if	objdataId ==x203325_g_DemandKill[1].id then
	 local KilledNum = GetMonsterOwnerCount( sceneId, objId ) --取得这个怪物死后拥有分配权的人数
		for i = 0, KilledNum-1 do
			local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --取得拥有分配权的人的objId
            if humanObjId ~= -1 then
                 if IsHaveQuest(sceneId,selfId, x203325_g_MissionId) > 0 then
                    local misIndex = GetQuestIndexByID(sceneId,selfId,x203325_g_MissionId)
										if GetQuestParam(sceneId,selfId,misIndex,0) < 1 then
												SetQuestByIndex(sceneId,selfId,misIndex,0,GetQuestParam(sceneId,selfId,misIndex,0)+1)
												SetQuestByIndex(sceneId,selfId,misIndex,7,1)
												Msg2Player(sceneId, selfId, format("击败莫斯科密探  %d/1", GetQuestParam(sceneId,selfId,misIndex,0)), 0, 3)
												x203325_CheckSubmit( sceneId, selfId)
										end
                end
            end
		end
	end 
end
--**********************************
function x203325_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203325_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203325_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203325_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203325_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203325_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203325_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203325_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203325_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203325_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end





