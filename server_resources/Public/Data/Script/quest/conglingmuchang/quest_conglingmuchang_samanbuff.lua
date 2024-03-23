--【敦煌】继续修炼  萨满

--MisDescBegin
x203705_g_ScriptId = 203705
x203705_g_MissionIdPre =3295
x203705_g_MissionId = 3274
x203705_g_LevelLess	= 	1 
x203705_g_MissionIdNext = 3286
x203705_g_Name	={}
x203705_g_ExtTarget={{type=20,n=1,target="找到@npc_123751学习并使用2级冥神附体技能"}}
x203705_g_MissionName="【新手】职业的进阶"
x203705_g_MissionInfo="\t你已经熟悉了生存的必要条件和王城周围的环境，现在你需要加强的就是你的自身实力了，王城的技能大师可以帮你快速地提升自身的能力。\n\t现在，你可以去找他了。"  --任务描述
x203705_g_MissionTarget=""		
x203705_g_MissionCompleted="\t我就是这里的技能大师，如果你愿意，我将是你终生的导师。\n\t活到老学到老，等你觉得自己杀敌变得缓慢的时候记得来找我学习新的技能。"					--完成任务npc说话的话
x203705_g_ContinueInfo="\t不清楚如何提升技能等级？在我这里就可以学习、提升萨满的技能。\n\t点击#G萨满技能学习#W按钮就能进入技能学习界面，里面#G明亮的技能#W表示你现在能掌握的技能，点击相应图标即可学习技能，当然你要有一定的经验和银子！\n\t最后记得学习完技能后，要将自己#G技能栏内技能的图标#W拖到下方#G快捷栏内#W，才能在需要的时候，方便快捷的使用。"
x203705_g_MissionHelp =	"#G您可以按下键盘上的#R2#G键，或者左键点击您下方技能快捷栏中的#R冥神附体#G技能。#W"
x203705_g_DemandItem ={}
x203705_g_ExpBonus = 855
x203705_g_BonusMoney1 =132
x203705_g_BonusMoney2 =0
x203705_g_BonusMoney3 =0
x203705_g_BonusMoney4 =0
x203705_g_BonusMoney5 =20
x203705_g_BonusMoney6 =0
x203705_g_BonusItem	=	{}
x203705_g_BonusChoiceItem ={}
x203705_g_NpcGUID ={{ guid = 123751, name = "萨满技能大师"} } --人物回复人
--MisDescEnd
--**********************************

function x203705_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x203705_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203705_g_MissionIdPre)> 0 then
		if GetZhiye( sceneId, selfId)==5 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x203705_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x203705_g_MissionId, state, -1 )
		end
	end
end

function x203705_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203705_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203705_g_ExpBonus )
		end
		if x203705_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203705_g_BonusMoney1 )
		end
		if x203705_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203705_g_BonusMoney2 )
		end
		if x203705_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203705_g_BonusMoney3 )
		end
		if x203705_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203705_g_BonusMoney4 )
		end
		if x203705_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203705_g_BonusMoney5 )
		end
		if x203705_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203705_g_BonusMoney6 )
		end
		for i, item in x203705_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203705_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203705_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x203705_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203705_g_MissionId) > 0 then
			if x203705_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203705_g_MissionName)
						AddQuestText(sceneId,x203705_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203705_g_ScriptId, x203705_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203705_g_MissionName)
						AddQuestText(sceneId,x203705_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203705_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203705_g_ScriptId, x203705_g_MissionId);
			end
  elseif x203705_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203705_g_MissionName)
			AddQuestText(sceneId,x203705_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x203705_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203705_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x203705_g_MissionHelp )
			end
			x203705_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203705_g_ScriptId, x203705_g_MissionId);
  end
	
end
--**********************************

function x203705_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x203705_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x203705_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID( sceneId, selfId, x203705_g_MissionId )
	if GetQuestParam(sceneId,selfId,misIndex,0) ==1 then 
					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 23,0 ) 
	        return 1
	end
	return 0
	
end
--**********************************
function x203705_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203705_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203705_g_MissionId  )
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
		if x203705_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203705_g_MissionId, x203705_g_ScriptId, 0, 0, 0, 1)  -- 参数 第四位1 是自问别人答 例如学习并使用技能；杀怪时第三位改为1
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x203705_Msg2toplayer( sceneId, selfId,0)
		  			  CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 23,1 )
		  			if x203705_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x203705_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x203705_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203705_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203705_g_MissionId)
	  x203705_Msg2toplayer( sceneId, selfId,1)
		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 23,0 )
			
end
--**********************************
function x203705_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x203705_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203705_g_BonusChoiceItem do
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
function x203705_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203705_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203705_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203705_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203705_g_MissionId) > 0 then
				x203705_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203705_g_MissionId)
				--QuestCom(sceneId, selfId, 3098)
				x203705_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203705_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203705_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203705_g_MissionIdNext )	
end

function x203705_GetBonus( sceneId, selfId,NpcID)
	  if x203705_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203705_g_ExpBonus);
  	end
		if x203705_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203705_g_BonusMoney1 )
	  end
		if x203705_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203705_g_BonusMoney2 )
	  end
		if x203705_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203705_g_BonusMoney3 )
		end
		if x203705_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203705_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203705_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203705_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203705_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203705_g_BonusMoney6)
		end
end

function x203705_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x203705_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x203705_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203705_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203705_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203705_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203705_g_MissionName.."！", 0, 3)
				if x203705_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G经验"..x203705_g_ExpBonus.."#cffcf00的奖励", 0, 2)
  			end
				if x203705_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G银卡"..x203705_g_BonusMoney1.."文#cffcf00的奖励", 0, 2)
	  		end
				if x203705_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G现银"..x203705_g_BonusMoney2.."文#cffcf00的奖励", 0, 2)
	  		end
				if x203705_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G金卡"..x203705_g_BonusMoney3.."文#cffcf00的奖励", 0, 2)
				end
				if x203705_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G朝廷声望值"..x203705_g_BonusMoney4.."#cffcf00的奖励", 0, 2)
				end
				if x203705_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G声望"..x203705_g_BonusMoney5.."#cffcf00的奖励", 0, 2)
				end
				if x203705_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G荣誉"..x203705_g_BonusMoney6.."#cffcf00的奖励", 0, 2)
				end
		end
end

function x203705_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203705_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203705_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203705_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203705_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203705_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )          --点击 npc 触发事件
local bFind  = 0
    for i ,item in x203705_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203705_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203705_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203705_g_MissionId, state, -1 )
		end
end

function x203705_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203705_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203705_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203705_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203705_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203705_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end