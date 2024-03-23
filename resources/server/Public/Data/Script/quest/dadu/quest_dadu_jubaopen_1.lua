--【主线】聚宝盆<三>

--MisDescBegin
x270014_g_ScriptId = 270014
x270014_g_MissionIdPre =3595
x270014_g_MissionId = 3596
x270014_g_LevelLess	= 	55 
x270014_g_MissionIdNext = 3597
x270014_g_Name	={}
x270014_g_ExtTarget={{type=20,n=1,target="从@npc_140039处得到答案"}}
x270014_g_MissionName="【主线】聚宝盆<三>"
x270014_g_MissionInfo="\t你是第9100个来找我问这件事的人了，我有一个规矩，就是我说你猜，你要是够聪明，很快就能知道捞出这聚宝盆的关键是什么。当然了，每问一个问题，我都要收取一定费用。怎么样，准备好了么？"  --任务描述
x270014_g_MissionTarget=""		
x270014_g_MissionCompleted="\t你还真有两下子！没错，当年沈万三得到聚宝盆的关键，正是因为放了一盆田鸡！"					--完成任务npc说话的话
x270014_g_ContinueInfo=""
x270014_g_MissionHelp =	"此任务回答错误或者寻求乞丐提示会分别扣除银卡10文和5文！"
x270014_g_DemandItem ={}
x270014_g_BonusMoney1 =376
x270014_g_BonusMoney2 =0
x270014_g_BonusMoney3 =0
x270014_g_BonusMoney4 =0
x270014_g_BonusMoney5 =66
x270014_g_BonusMoney6 =0
x270014_g_BonusItem	=	{}
x270014_g_BonusChoiceItem ={}
x270014_g_ExpBonus = 171000
x270014_g_NpcGUID ={}
x270014_g_answer1 ={"田鸡","蛇","鳄鱼","再给我点提示"}
x270014_g_answer2 ={"田鸡","蛇","鳄鱼","再给我点提示"}
x270014_g_answer3 ={"田鸡","蛇","鳄鱼","再给我点提示"}
x270014_g_answer4 ={"田鸡","蛇","鳄鱼"}
x270014_g_question1 ={"\t这种东西你可以在水里面找到。"}
x270014_g_question2 ={"\t这东西不仅在水里能找到，在岸上也能找到！"}
x270014_g_question3 ={"\t这东西不仅在水里能找到，在岸上也能找到，而且有四条腿！"}
x270014_g_question4 ={"\t这东西不仅在水里能找到，在岸上也能找到，而且有四条腿，并且跳的还很高！"}
--MisDescEnd
--**********************************

function x270014_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x270014_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x270014_g_MissionIdPre)> 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x270014_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x270014_g_MissionId, state, -1 )
	end
end

function x270014_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x270014_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x270014_g_ExpBonus )
		end
		if x270014_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x270014_g_BonusMoney1 )
		end
		if x270014_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x270014_g_BonusMoney2 )
		end
		if x270014_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x270014_g_BonusMoney3 )
		end
		if x270014_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x270014_g_BonusMoney4 )
		end
		if x270014_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x270014_g_BonusMoney5 )
		end
		if x270014_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x270014_g_BonusMoney6 )
		end
		for i, item in x270014_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x270014_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x270014_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x270014_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x270014_g_MissionId) > 0 then
	local misIndex = GetQuestIndexByID(sceneId,selfId,x270014_g_MissionId)
	local daan =0
			if x270014_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
					if which ==-1 then
						daan =4
						if GetQuestParam(sceneId,selfId,misIndex,1) ==0 then 
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"#Y"..x270014_g_MissionName)
							AddQuestText(sceneId,x270014_g_question1[1])
							for i, item in x270014_g_answer1 do
								AddQuestNumText(sceneId, MissionId, x270014_g_answer1[i],3,i)
							end 
							EndQuestEvent()
							DispatchQuestEventList(sceneId, selfId, NPCId, x270014_g_ScriptId, x270014_g_MissionId);
					  elseif GetQuestParam(sceneId,selfId,misIndex,1) ==1 then 
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"#Y"..x270014_g_MissionName)
							AddQuestText(sceneId,x270014_g_question2[1])
							for i, item in x270014_g_answer2 do
								AddQuestNumText(sceneId, MissionId, x270014_g_answer2[i],3,i)
							end 
							EndQuestEvent()
							DispatchQuestEventList(sceneId, selfId, NPCId, x270014_g_ScriptId, x270014_g_MissionId);
						elseif GetQuestParam(sceneId,selfId,misIndex,1) ==2 then 
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"#Y"..x270014_g_MissionName)
							AddQuestText(sceneId,x270014_g_question3[1])
							for i, item in x270014_g_answer3 do
								AddQuestNumText(sceneId, MissionId, x270014_g_answer3[i],3,i)
							end 
							EndQuestEvent()
							DispatchQuestEventList(sceneId, selfId, NPCId, x270014_g_ScriptId, x270014_g_MissionId);
						elseif GetQuestParam(sceneId,selfId,misIndex,1) ==3 then 
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"#Y"..x270014_g_MissionName)
							AddQuestText(sceneId,x270014_g_question4[1])
							for i, item in x270014_g_answer4 do
								AddQuestNumText(sceneId, MissionId, x270014_g_answer4[i],3,i)
							end 
							EndQuestEvent()
							DispatchQuestEventList(sceneId, selfId, NPCId, x270014_g_ScriptId, x270014_g_MissionId);
					  end
					elseif GetMoney(sceneId, selfId, 1) < 10 then
									daan =3
					elseif which == 1 then
									daan =1
					elseif which == 2 then
									daan =0
					elseif which == 3 then
									daan =0
					elseif which == 4 then
									daan =2
					end
					if daan ==0 then
						CostMoney( sceneId , selfId, 1 , 10 )
						Msg2Player(sceneId, selfId, "猜错了，你损失了10文钱！", 0, 3)
					elseif daan ==1 then
						Msg2Player(sceneId, selfId, "恭喜你猜对了！", 0, 3)
						SetQuestByIndex(sceneId,selfId,misIndex,0,GetQuestParam(sceneId,selfId,misIndex,0)+1)
						x270014_ProcEventEntry(sceneId, selfId, NPCId, MissionId,-1)
					elseif daan ==2 then
						CostMoney( sceneId , selfId, 1 , 5 )
						Msg2Player(sceneId, selfId, "你给了乞丐5文钱！", 0, 3)
						SetQuestByIndex(sceneId,selfId,misIndex,1,GetQuestParam(sceneId,selfId,misIndex,1)+1)
						x270014_ProcEventEntry(sceneId, selfId, NPCId, MissionId,-1)
					elseif daan ==3 then
						Msg2Player(sceneId, selfId, "您的银卡不足10文", 0, 3)
					end
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270014_g_MissionName)
						AddQuestText(sceneId,x270014_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x270014_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x270014_g_ScriptId, x270014_g_MissionId);
			end
  elseif x270014_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x270014_g_MissionName)
			AddQuestText(sceneId,x270014_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x270014_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x270014_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x270014_g_MissionHelp )
			end
			x270014_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x270014_g_ScriptId, x270014_g_MissionId);
  end
	
end
--**********************************

function x270014_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x270014_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x270014_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId,selfId,x270014_g_MissionId)
		if GetQuestParam(sceneId,selfId,misIndex,0) ==1 then
	        return 1
	  end
	  return 0
	
end
--**********************************
function x270014_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x270014_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x270014_g_MissionId  )
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
		if x270014_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			local retmiss = AddQuest( sceneId, selfId, x270014_g_MissionId, x270014_g_ScriptId, 0, 0, 0)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x270014_Msg2toplayer( sceneId, selfId,0)
		  			local misIndex = GetQuestIndexByID(sceneId,selfId,x270014_g_MissionId)                                                  
	    			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			if x270014_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    			end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x270014_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x270014_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x270014_g_MissionId)
	  x270014_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x270014_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x270014_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x270014_g_BonusChoiceItem do
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
function x270014_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId)
	if IsHaveQuest(sceneId,selfId, x270014_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270014_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270014_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x270014_g_MissionId) > 0 then
				x270014_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x270014_g_MissionId)
				x270014_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x270014_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x270014_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x270014_g_MissionIdNext )	
end

function x270014_GetBonus( sceneId, selfId,NpcID)
	  if x270014_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x270014_g_ExpBonus);
  	end
		if x270014_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x270014_g_BonusMoney1 )
	  end
		if x270014_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x270014_g_BonusMoney2 )
	  end
		if x270014_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x270014_g_BonusMoney3 )
		end
		if x270014_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x270014_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x270014_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x270014_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x270014_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x270014_g_BonusMoney6)
		end
end

function x270014_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x270014_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x270014_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x270014_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x270014_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x270014_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x270014_g_MissionName.."！", 0, 3)
				if x270014_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x270014_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x270014_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x270014_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x270014_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x270014_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x270014_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x270014_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x270014_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x270014_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x270014_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x270014_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x270014_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x270014_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x270014_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x270014_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x270014_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x270014_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x270014_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x270014_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	 
end

function x270014_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x270014_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x270014_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x270014_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x270014_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x270014_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end





