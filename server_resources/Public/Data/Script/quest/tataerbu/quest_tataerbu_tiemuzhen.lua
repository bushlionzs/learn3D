--兄弟与爱人6/8

--MisDescBegin
x223001_g_ScriptId = 223001
x223001_g_MissionIdPre =-1
x223001_g_MissionId = 100
x223001_g_LevelLess	= 	20 
x223001_g_MaxLevel  =   50
x223001_g_MissionIdNext = 101
x223001_g_Name	={"铁木真"}
x223001_g_ExtTarget={{type=20,n=1,target="和@npc_103001交谈"}}
x223001_g_MissionName="【剧场】大战在即"
x223001_g_MissionTalk={"正是！","小小差距并不算什么。","的确如此。"}
x223001_g_MissionInfo="\t#Y@myname#W，很高兴再次见到你。目前我们正和塔塔尔人对峙着，这次又能得到你的帮助了。"  --任务描述
x223001_g_MissionTarget=""		
x223001_g_MissionCompleted="\t高级的技能能让你更轻松的解决掉你的敌人，所以记得当你的等级提高以后经常回来学习新的技能。\n\t人不能一口吃成胖子，但胖子却是一口一口吃出来的。持之以恒的练习，才能成为一代宗师。"
x223001_g_ContinueInfo={"\t此次和塔塔尔部交战，我们有了一个强力的盟友—金国。金国六王爷完颜洪烈亲帅大军来帮助我们。\n\t曾几何时，我们草原人在金国的眼里不过是一群未开化的蛮子，如今金国竟然肯主动和我们结盟，不能不说这是我们这些年一个巨大的收获。 ",
												"\t金国军队衣甲鲜明，刀枪锐利，尤其是六王爷完颜洪烈的亲卫队，个个都是面带杀气的勇士，我们乞颜部的普通士兵一比之下确实差了很多。",
												"\t我们的兵器盔甲都不如金国人，但是我们不能在金国人面前堕了我们乞颜部健儿的威风！#Y@myname#W,#R我#W和#R木华黎#W将军有一些重要的事情要交给你。"}
x223001_g_MissionHelp =	""
x223001_g_DemandItem ={}
x223001_g_ExpBonus = 8977
x223001_g_BonusMoney1 =255
x223001_g_BonusMoney2 =0
x223001_g_BonusMoney3 =0
x223001_g_BonusMoney4 =0
x223001_g_BonusMoney5 =37
x223001_g_BonusMoney6 =0
x223001_g_BonusItem	=	{}
x223001_g_BonusChoiceItem ={}
x223001_g_NpcGUID = { }
--MisDescEnd
--**********************************
function x223001_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    local level = GetLevel(sceneId, selfId)
	if level < x223001_g_LevelLess or level > x223001_g_MaxLevel then
		return
	end
	if IsQuestHaveDone(sceneId, selfId, x223001_g_MissionId) > 0 then
		return 
	end
	if GetLevel(sceneId, selfId)>= x223001_g_LevelLess then
			--if IsQuestHaveDone(sceneId, selfId, x223001_g_MissionIdPre) > 0 then
						local state = GetQuestStateNM(sceneId,selfId,NPCId,x223001_g_MissionId)
						AddQuestTextNM( sceneId, selfId, NPCId, x223001_g_MissionId, state, -1 )
		--	end			
	end
end

function x223001_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x223001_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x223001_g_ExpBonus )
		end
		if x223001_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x223001_g_BonusMoney1 )
		end
		if x223001_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x223001_g_BonusMoney2 )
		end
		if x223001_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x223001_g_BonusMoney3 )
		end
		if x223001_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x223001_g_BonusMoney4 )
		end
		if x223001_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x223001_g_BonusMoney5 )
		end
		if x223001_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x223001_g_BonusMoney6 )
		end
		for i, item in x223001_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.id, item.num)
	  end
		for i, item in x223001_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

--任务入口函数

--**********************************

function x223001_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x223001_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x223001_g_MissionId) > 0 then
			if x223001_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
					if which == -1 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x223001_g_MissionName)
						AddQuestText(sceneId,x223001_g_ContinueInfo[1])
						AddQuestNumText(sceneId, MissionId, x223001_g_MissionTalk[1],0,0)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x223001_g_ScriptId, x223001_g_MissionId);
					elseif which ==0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x223001_g_MissionName)
						AddQuestText(sceneId,x223001_g_ContinueInfo[2])
						AddQuestNumText(sceneId, MissionId, x223001_g_MissionTalk[2],1,1)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x223001_g_ScriptId, x223001_g_MissionId);
						local misIndex = GetQuestIndexByID(sceneId,selfId,x223001_g_MissionId)  
						SetQuestByIndex(sceneId,selfId,misIndex,1,1)                                                
	    			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
					end
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x223001_g_MissionName)
						AddQuestText(sceneId,x223001_g_ContinueInfo[3])
						AddQuestText(sceneId," ")
						x223001_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x223001_g_ScriptId, x223001_g_MissionId);
			end
  elseif x223001_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x223001_g_MissionName)
			AddQuestText(sceneId,x223001_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x223001_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x223001_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x223001_g_MissionHelp )
			end
			x223001_DispatchMissionInfo( sceneId, selfId, NPCId )
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x223001_g_ScriptId, x223001_g_MissionId);
  end
end
--**********************************
function x223001_ProcAcceptCheck(sceneId, selfId, NPCId)
	if IsQuestHaveDone(sceneId, selfId, x223001_g_MissionId) > 0 then
		return 0
	elseif GetLevel(sceneId, selfId)< x223001_g_LevelLess then
		return 0
	end
	return 1
end
--**********************************
function x223001_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x223001_g_MissionId)
	if GetQuestParam(sceneId,selfId,misIndex,1) == 1 then
	        return 1
	end
	return 0
end
--**********************************
function x223001_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x223001_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x223001_g_MissionId  )
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
		
		if x223001_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x223001_g_MissionId, x223001_g_ScriptId, 0, 0, 0)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x223001_Msg2toplayer( sceneId, selfId,0)
						--if x223001_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x223001_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************
function x223001_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x223001_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x223001_g_MissionId)
	  x223001_Msg2toplayer( sceneId, selfId,1)
end
--**********************************
function x223001_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x223001_g_BonusItem do
		AddItem( sceneId, item.id, item.num )
  end
  for j, item in x223001_g_BonusChoiceItem do
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
function x223001_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x223001_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x223001_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x223001_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x223001_g_MissionId) > 0 then
				x223001_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x223001_g_MissionId)
				x223001_GetBonus( sceneId, selfId,NPCId)
				CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x223001_g_MissionIdNext )	
   end
end

function x223001_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
   
end

function x223001_GetBonus( sceneId, selfId,NpcID)
	  if x223001_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x223001_g_ExpBonus);
  	end
		if x223001_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x223001_g_BonusMoney1 )
	  end
		if x223001_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x223001_g_BonusMoney2 )
	  end
		if x223001_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x223001_g_BonusMoney3 )
		end
		if x223001_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x223001_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x223001_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x223001_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x223001_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x223001_g_BonusMoney6)
		end
end

function x223001_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x223001_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x223001_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x223001_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x223001_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x223001_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x223001_g_MissionName.."！", 0, 3)
				if x223001_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x223001_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x223001_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x223001_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x223001_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x223001_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x223001_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x223001_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x223001_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x223001_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x223001_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x223001_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x223001_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x223001_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

--**********************************

function x223001_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end
--**********************************
function x223001_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x223001_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x223001_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x223001_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x223001_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x223001_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x223001_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x223001_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x223001_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x223001_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end





