--询问状况

--MisDescBegin
x256219_g_ScriptId = 256219
x256219_g_MissionIdPre = 3052
x256219_g_MissionId = 3094
x256219_g_LevelLess	= 	25 
x256219_g_MissionIdNext = 3095
x256219_g_Name	={}
x256219_g_ExtTarget={{type=20,n=1,target="用#G赤铜钻或青铜钻#W在一件#G世传君主装#W上完成一次@npc_82067"}}
x256219_g_MissionName="【个人】第一次打孔"
x256219_g_MissionInfo="\t亲爱的朋友，在你的背包中有#G赤铜钻和青铜钻#W各一颗，可以让你在一件#G世传君主装备#W上打一个孔。\n\t首先鼠标左键点击装备镶嵌大师，再用鼠标左键点击#G装备打孔#W的选项，会打开打孔的功能栏，同时背包也会自动打开。\n\t 右键点击所要#G打孔的装备#W，该装备会自动放入打孔功能栏中，此时您的赤铜钻或青铜钻会自动出现在下方的打孔道具栏中，点击#G打孔按钮#W，就可以为你的装备打出第一个孔了。\n\t打孔完成后点击关闭功能栏，打孔就此结束，已打孔的装备也会自动回到您的背包中。\n\t #G注：不同部位的装备所需要的打孔道具也是有不同的。#W"
x256219_g_MissionTarget=""		
x256219_g_MissionCompleted="\t我想你已经仔细看过那件被打过孔声望装备，被打过孔的装备可以镶嵌宝石提高装备属性。"					--完成任务npc说话的话
x256219_g_ContinueInfo="\t你不愿意为你的那件声望装备打上一个孔吗？"
x256219_g_MissionHelp =	""
x256219_g_DemandItem =	   {10014001,10024001,10034001,10044001,10054001,10064001,10074001,10084001,10094001,10104001,10114001,10124001,10234001,10234011,10234021,10234031,10234041,10234051,10254001,10254011,10254021,10254031,10254041,10254051,10274001,10274011,10274021,10274031,10274041,10274051,10244001, 10244011, 10244021,	10244031,	10244041,	10244051,	10264001,	10264011,	10264021,	10264031,	10264041,	10264051,	10204001, 10204011,	10204021,	10204031,	10204041,	10204051}						
x256219_g_BonusMoney1 =0
x256219_g_BonusMoney2 =0
x256219_g_BonusMoney3 =0
x256219_g_BonusMoney4 =0
x256219_g_BonusMoney5 =0
x256219_g_BonusMoney6 =0
x256219_g_BonusItem	=	{}
x256219_g_BonusChoiceItem ={}
x256219_g_ExpBonus = 10200
x256219_g_NpcGUID ={{ guid = 138554, name = "哈森尔"} }
--MisDescEnd
--**********************************
x256219_g_MaxLevel   = 40

function x256219_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    local level = GetLevel(sceneId, selfId)
	if level < x256219_g_LevelLess or level >= x256219_g_MaxLevel then
		return
	end


	if IsQuestHaveDone(sceneId, selfId, x256219_g_MissionId) > 0 then
		return 
	end
	
	if IsQuestHaveDone(sceneId, selfId, x256219_g_MissionIdPre)> 0 then 
	if IsHaveQuest(sceneId,selfId, x256219_g_MissionId) <= 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x256219_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x256219_g_MissionId, state, -1 )
	end
	end

end

function x256219_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x256219_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256219_g_ExpBonus )
		end
		if x256219_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256219_g_BonusMoney1 )
		end
		if x256219_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256219_g_BonusMoney2 )
		end
		if x256219_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256219_g_BonusMoney3 )
		end
		if x256219_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256219_g_BonusMoney4 )
		end
		if x256219_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256219_g_BonusMoney5 )
		end
		if x256219_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256219_g_BonusMoney6 )
		end
		for i, item in x256219_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	 	end
		for i, item in x256219_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  	end
end
--**********************************

function x256219_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x256219_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256219_g_MissionId) > 0 then
			if x256219_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x256219_g_MissionName)
				AddQuestText(sceneId,x256219_g_ContinueInfo)
				EndQuestEvent()
				DispatchQuestEventList(sceneId, selfId, NPCId, x256219_g_ScriptId, x256219_g_MissionId);
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x256219_g_MissionName)
				AddQuestText(sceneId,x256219_g_MissionCompleted)
				AddQuestText(sceneId," ")
				x256219_DispatchMissionInfo( sceneId, selfId, NPCId )
				EndQuestEvent()
				DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256219_g_ScriptId, x256219_g_MissionId);
			end
  elseif x256219_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  		AddQuestText(sceneId,"#Y"..x256219_g_MissionName)
			AddQuestText(sceneId,x256219_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x256219_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x256219_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x256219_g_MissionHelp )
			end
			x256219_DispatchMissionInfo( sceneId, selfId, NPCId )
	  		EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256219_g_ScriptId, x256219_g_MissionId);
  end
	
end
--**********************************

function x256219_ProcAcceptCheck(sceneId, selfId, NPCId)
		
	return 1
		

end
--**********************************
function x256219_CheckSubmit( sceneId, selfId, NPCId)  
                                                  
		if  IsHaveQuest(sceneId, selfId,x256219_g_MissionId) ~=1 then
			return 0
		end
		
	   	local 	misIndex = GetQuestIndexByID(sceneId, selfId,x256219_g_MissionId)                                                  
	   	if GetQuestParam(sceneId, selfId,misIndex,7,1) == 1 then
	   		return 1
	   	else 
	   		return 0
	   	end
	   	
	
end

--**********************************
function x256219_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256219_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256219_g_MissionId  )
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
		
		if x256219_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x256219_g_MissionId, x256219_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x256219_Msg2toplayer( sceneId, selfId,0)
						for i, item in x256219_g_DemandItem do
							local equip	=	GetEquipItemCountByLess(sceneId, selfId, 1,1,item)
							local bag	=	GetBagItemCountByLess(sceneId, selfId, 1,1,item)  --0--升星 1--打孔 2--宝石
							if equip >= 1 or bag >=1 then
								
								local misIndex = GetQuestIndexByID(sceneId,selfId,x256219_g_MissionId)                                                  
			    				SetQuestByIndex(sceneId,selfId,misIndex,0,1)
			    				SetQuestByIndex(sceneId,selfId,misIndex,7,1)
			    				CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 34,0 )
									CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 47,0 )
									CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 35,0 )
			    				break
							end
						end
					end
		  			
	 	end                                                                    
	     
end
--**********************************

function x256219_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256219_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x256219_g_MissionId)
	  x256219_Msg2toplayer( sceneId, selfId,1)
		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 34,0 )
		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 47,0 )
		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 35,0 )	
end
--**********************************
function x256219_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x256219_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x256219_g_BonusChoiceItem do
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
function x256219_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256219_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256219_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256219_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"背包空间不足，请清理后再来！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256219_g_MissionId) > 0 then
				x256219_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x256219_g_MissionId)
				x256219_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256219_g_BonusItem do
 						AddBindItem( sceneId, item.item, item.n )
				end
				for i, item in x256219_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256219_g_MissionIdNext )	
end

function x256219_GetBonus( sceneId, selfId,NpcID)
	  if x256219_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256219_g_ExpBonus);
  	end
		if x256219_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256219_g_BonusMoney1 )
	  end
		if x256219_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256219_g_BonusMoney2 )
	  end
		if x256219_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256219_g_BonusMoney3 )
		end
		if x256219_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256219_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256219_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256219_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256219_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256219_g_BonusMoney6)
		end
end

function x256219_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务："..x256219_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务："..x256219_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务："..x256219_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务："..x256219_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x256219_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x256219_g_MissionName.."！", 0, 3)
				if x256219_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x256219_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x256219_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x256219_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x256219_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x256219_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x256219_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x256219_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x256219_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x256219_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x256219_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x256219_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x256219_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x256219_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x256219_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x256219_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256219_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x256219_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256219_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x256219_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x256219_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x256219_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x256219_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x256219_g_MissionId, state, -1 )
				if x256219_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 34,1 )
					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 47,1 )
					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 35,1 )
				end
		end
end

function x256219_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256219_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256219_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256219_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256219_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256219_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end