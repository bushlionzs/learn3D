--20级学技能

--MisDescBegin
x203725_g_ScriptId = 203725
x203725_g_LevelLess	= 	20
x203725_g_MissionName="【主线】职业的进阶"
x203725_g_MissionInfo="\t虽然你已经具备相当的实力自保，但你还需要进一步提升自身的实力。\n\t去找王城的技能大师吧，他可以帮你快速地提升技能的威力。"  --任务描述
x203725_g_MissionTarget=""		
x203725_g_MissionCompleted="\t活到老学到老，等你觉得自己杀敌变得缓慢的时候记得去找技能大师学习新的技能。 "					--完成任务npc说话的话
x203725_g_ContinueInfo="\t不清楚如何提升技能等级？在技能大师那里就可以学习、提升自己的技能。\n\t点击#G技能学习#W按钮就能进入技能学习界面，里面#G明亮的技能#W表示你现在能掌握的技能，点击相应图标即可学习技能，当然你要有一定的经验和银子！\n\t最后记得学习完技能后，要将自己#G技能栏内技能的图标#W拖到下方#G快捷栏内#W，才能在需要的时候，方便快捷的使用。"
x203725_g_MissionHelp =	"#G您可以按下键盘上的#R2#G键，或者左键点击您下方技能快捷栏中的技能来使用。#W"
x203725_g_DemandItem ={}
x203725_g_ExpBonus = 1500
x203725_g_BonusMoney1 =258
x203725_g_BonusMoney2 =0
x203725_g_BonusMoney3 =0
x203725_g_BonusMoney4 =0
x203725_g_BonusMoney5 =37
x203725_g_BonusMoney6 =0

x203725_g_BonusChoiceItem ={}
--MisDescEnd
--**********************************
x203725_g_Name	={}
x203725_g_MissionIdPre =4262
x203725_g_MissionIdNext = 5963
x203725_g_MissionId = {4288,4289,4290,4291,4292,4293,4294,4295,4296,4297,4298,4299}
x203725_g_BonusItem	=	{
						 }
x203725_g_ExtTarget={{type=20,n=1,target="找到@npc_129044学习并#R使用#W3级#R勇冠三军#W"},
					 {type=20,n=1,target="找到@npc_129045学习并#R使用#W3级#R七星剑阵#W"},
					 {type=20,n=1,target="找到@npc_129047学习并#R使用#W3级#R自由之歌#W"},
					 {type=20,n=1,target="找到@npc_129046学习并#R使用#W3级#R散兵队形#W"},
					 {type=20,n=1,target="找到@npc_129049学习并#R使用#W3级#R神灯之光#W"},
					 {type=20,n=1,target="找到@npc_129048学习并#R使用#W3级#R冥神附体#W"},
					 {type=20,n=1,target="找到@npc_129050学习并#R使用#W3级#R光明圣战#W"},
					 {type=20,n=1,target="找到@npc_129051学习并#R使用#W3级#R无名业火#W"},
					 {type=20,n=1,target="找到@npc_129052学习并#R使用#W3级#R疾风烈火#W"},
					 {type=20,n=1,target="找到@npc_129053学习并#R使用#W3级#R临兵列阵#W"},
					 {type=20,n=1,target="找到@npc_129055学习并#R使用#W3级#R苦修祷言#W"},
					 {type=20,n=1,target="找到@npc_129054学习并#R使用#W3级#R浮屠咒#W"},
					 }
x203725_g_QuestTarget={"  找到@npc_129044学习并#R使用#W3级#R勇冠三军#W",
					 "  找到@npc_129045学习并#R使用#W3级#R七星剑阵#W",
					 "  找到@npc_129047学习并#R使用#W3级#R自由之歌#W",
					 "  找到@npc_129046学习并#R使用#W3级#R散兵队形#W",
					 "  找到@npc_129049学习并#R使用#W3级#R神灯之光#W",
					 "  找到@npc_129048学习并#R使用#W3级#R冥神附体#W",
					 "  找到@npc_129050学习并#R使用#W3级#R光明圣战#W",
					 "  找到@npc_129051学习并#R使用#W3级#R无名业火#W",
					 "  找到@npc_129052学习并#R使用#W3级#R疾风烈火#W",
					 "  找到@npc_129053学习并#R使用#W3级#R临兵列阵#W",
					 "  找到@npc_129055学习并#R使用#W3级#R苦修祷言#W",
					 "  找到@npc_129054学习并#R使用#W3级#R浮屠咒#W",
					   }
x203725_g_NpcGUID ={ guid = 129056, name = "刀"}
--**********************************

function x203725_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

	local zhiye= GetZhiye( sceneId, selfId)
	if IsQuestHaveDone(sceneId, selfId, x203725_g_MissionId[zhiye+1]) > 0 then
		return 
	end
	
	if MissionId ~= x203725_g_MissionId[zhiye+1] then
		return
	end

	if IsQuestHaveDone(sceneId, selfId, x203725_g_MissionIdPre)> 0 then
		if IsHaveQuest(sceneId,selfId, x203725_g_MissionId[zhiye+1]) <= 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x203725_g_MissionId[zhiye+1])
			AddQuestTextNM( sceneId, selfId, NPCId, x203725_g_MissionId[zhiye+1], state, -1 )
		end
	end
end

function x203725_DispatchMissionInfo( sceneId, selfId, NPCId )
		local zhiye= GetZhiye( sceneId, selfId)
		if x203725_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203725_g_ExpBonus )
		end
		if x203725_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203725_g_BonusMoney1 )
		end
		if x203725_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203725_g_BonusMoney2 )
		end
		if x203725_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203725_g_BonusMoney3 )
		end
		if x203725_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203725_g_BonusMoney4 )
		end
		if x203725_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203725_g_BonusMoney5 )
		end
		if x203725_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203725_g_BonusMoney6 )
		end
		
		--AddQuestItemBonus(sceneId, x203725_g_BonusItem[zhiye+1].item, x203725_g_BonusItem[zhiye+1].n)

		for i, item in x203725_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203725_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	 local zhiye= GetZhiye( sceneId, selfId)
	if IsQuestHaveDone(sceneId, selfId, x203725_g_MissionId[zhiye+1]) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203725_g_MissionId[zhiye+1]) > 0 then
			if x203725_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203725_g_MissionName)
						AddQuestText(sceneId,x203725_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203725_g_ScriptId, x203725_g_MissionId[zhiye+1]);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203725_g_MissionName)
						AddQuestText(sceneId,x203725_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203725_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203725_g_ScriptId, x203725_g_MissionId[zhiye+1]);
			end
  elseif x203725_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203725_g_MissionName)
			AddQuestText(sceneId,x203725_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			
			AddQuestText( sceneId,x203725_g_ExtTarget[zhiye+1].target)

			if x203725_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x203725_g_MissionHelp )
			end
			x203725_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203725_g_ScriptId, x203725_g_MissionId[zhiye+1]);
  end
	
end
--**********************************

function x203725_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x203725_CheckSubmit( sceneId, selfId, NPCId)
	local zhiye= GetZhiye( sceneId, selfId)
	local misIndex = GetQuestIndexByID( sceneId, selfId, x203725_g_MissionId[zhiye+1] )
	if GetQuestParam(sceneId,selfId,misIndex,0) ==1 then 
		
		--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 23,0 ) 
	    return 1
	end
	return 0
	
end
--**********************************
function x203725_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		local zhiye= GetZhiye( sceneId, selfId)
		if IsQuestHaveDone(sceneId, selfId, x203725_g_MissionId[zhiye+1]) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203725_g_MissionId[zhiye+1]  )
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
		
		if x203725_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203725_g_MissionId[zhiye+1], x203725_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x203725_Msg2toplayer( sceneId, selfId,0)
		  			 --CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 23,1 )
		  				if x203725_CheckSubmit(sceneId, selfId, NPCId) > 0 then
							local misIndex = GetQuestIndexByID(sceneId,selfId,x203725_g_MissionId[zhiye+1])                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    					
	    				end
	    			x203725_ProcQuestLogRefresh( sceneId, selfId, x203725_g_MissionId[zhiye+1])
		  			end
	 	end                                                                    
	     
end
--**********************************

function x203725_ProcQuestAbandon(sceneId, selfId, MissionId)
		local zhiye= GetZhiye( sceneId, selfId)
		if IsHaveQuest(sceneId,selfId, x203725_g_MissionId[zhiye+1]) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203725_g_MissionId[zhiye+1])
	  x203725_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x203725_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local zhiye= GetZhiye( sceneId, selfId)
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)	
		--AddItem( sceneId, x203725_g_BonusItem[zhiye+1].item, x203725_g_BonusItem[zhiye+1].n )
  for j, item in x203725_g_BonusChoiceItem do
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
function x203725_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	local zhiye= GetZhiye( sceneId, selfId)
	if IsHaveQuest(sceneId,selfId, x203725_g_MissionId[zhiye+1]) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203725_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203725_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203725_g_MissionId[zhiye+1]) > 0 then
				x203725_Msg2toplayer( sceneId, selfId,2)
				--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,13,0)
				QuestCom(sceneId, selfId, x203725_g_MissionId[zhiye+1])
				QuestCom(sceneId, selfId, 6001)
				x203725_GetBonus( sceneId, selfId,NPCId)
				
				BeginAddItem(sceneId)
 				--AddItem( sceneId, x203725_g_BonusItem[zhiye+1].item, x203725_g_BonusItem[zhiye+1].n )
				for i, item in x203725_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203725_g_MissionIdNext )	
end

function x203725_GetBonus( sceneId, selfId,NpcID)

	 	if x203725_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203725_g_ExpBonus);
  		end
		if x203725_g_BonusMoney1 > 0 then
	    	AddMoney( sceneId, selfId, 1, x203725_g_BonusMoney1 )
	 	end
		if x203725_g_BonusMoney2 > 0 then
	    	AddMoney( sceneId, selfId, 0, x203725_g_BonusMoney2 )
	 	end
		if x203725_g_BonusMoney3 > 0 then
	    	AddMoney( sceneId, selfId, 3, x203725_g_BonusMoney3 )
		end
		if x203725_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203725_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203725_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203725_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203725_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203725_g_BonusMoney6)
		end
end

function x203725_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x203725_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x203725_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203725_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203725_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203725_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203725_g_MissionName.."！", 0, 3)
				if x203725_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G经验"..x203725_g_ExpBonus.."#cffcf00的奖励", 0, 2)
  			end
				if x203725_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G银卡"..x203725_g_BonusMoney1.."文#cffcf00的奖励", 0, 2)
	  		end
				if x203725_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G现银"..x203725_g_BonusMoney2.."文#cffcf00的奖励", 0, 2)
	  		end
				if x203725_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G金卡"..x203725_g_BonusMoney3.."文#cffcf00的奖励", 0, 2)
				end
				if x203725_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G朝廷声望值"..x203725_g_BonusMoney4.."#cffcf00的奖励", 0, 2)
				end
				if x203725_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G声望"..x203725_g_BonusMoney5.."#cffcf00的奖励", 0, 2)
				end
				if x203725_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G荣誉"..x203725_g_BonusMoney6.."#cffcf00的奖励", 0, 2)
				end
		end
end

function x203725_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203725_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203725_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203725_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203725_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203725_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	local zhiye= GetZhiye( sceneId, selfId)
	local bFind  = 0
	  
	if x203725_g_NpcGUID.guid ~= npcGuid then
		return
	end
	
	if IsHaveQuest(sceneId,selfId, x203725_g_MissionId[zhiye+1]) > 0 then
			local state = GetQuestStateNM(sceneId,selfId,npcId,x203725_g_MissionId[zhiye+1])
			AddQuestTextNM( sceneId, selfId, npcId, x203725_g_MissionId[zhiye+1], state, -1 )
	end
end

function x203725_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
    local zhiye= GetZhiye( sceneId, selfId)
    local strTarget = format( "任务已经完成，请回报")
    local Npcid = 0
	if zhiye < 0 or zhiye > 11 then
		return
	else
    strTarget = x203725_g_QuestTarget[zhiye+1] 
    end   	
	Npcid = x203725_g_NpcGUID.guid

	BeginQuestEvent( sceneId)
		x203725_DispatchMissionInfo( sceneId, selfId, -1 )
        AddQuestLogCustomText( sceneId,
                                "",                             -- 标题
                                x203725_g_MissionName,          -- 任务名字
                                strTarget,
                                "@npc_"..Npcid,                             --任务NPC
                                x203725_g_QuestTarget[zhiye+1],
                                "\t虽然你已经具备相当的实力自保，但你还需要进一步提升自身的实力。\n\t去找王城的技能大师吧，他可以帮你快速地提升技能的威力。",
                                ""
                                )

	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

function x203725_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203725_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203725_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203725_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203725_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203725_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end