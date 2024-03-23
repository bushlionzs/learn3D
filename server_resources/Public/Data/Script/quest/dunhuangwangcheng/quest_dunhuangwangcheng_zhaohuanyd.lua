--消灭轮回台boss

--MisDescBegin
x256233_g_ScriptId = 256233
--x256233_g_MissionIdPre =455
x256233_g_MissionId = 3125
x256233_g_LevelLess	= 	30
--x256233_g_MissionIdNext = 457
x256233_g_DemandKill ={{id=2533,num=1}}
x256233_g_Name	={"boss"}
x256233_g_ExtTarget={{type=20,n=1,target="前往#G轮回台#W使用“#G巨兽魂石#W”召唤并消灭其中隐藏的巨兽"}}
x256233_g_MissionName="【副本】轮回台的巨兽"
x256233_g_MissionInfo="\t你可曾听说过轮回台中隐藏巨兽的传说？\n\t听说只要拥有那巨兽魂石，就可以在轮回台内召唤出这可怕的怪兽。"  --任务描述
x256233_g_MissionTarget=""		
x256233_g_MissionCompleted="\t你们真不简单！这是你们应得的奖励！"
x256233_g_ContinueInfo="“还没发现那可怕的巨兽吗？你可以在金币商店贵宾区一星麒麟商店购买#G巨兽魂石”#W来召唤它。"
x256233_g_MissionHelp =	"#G“巨兽魂石”#W可以在金币商店贵宾区一星麒麟商店购买，但需要您的充值达到一定的金额，才能获得其中购买相应物品的权限。"
x256233_g_DemandItem ={}
x256233_g_BonusMoney1 =0
x256233_g_BonusMoney2 =0
x256233_g_BonusMoney3 =0
x256233_g_BonusMoney4 =0
x256233_g_BonusMoney5 =0
x256233_g_BonusMoney6 =0
x256233_g_BonusItem	={}
x256233_g_BonusChoiceItem ={}
x256233_g_ExpBonus = 450000

x256233_g_NpcGUID ={{ guid = 150525, name = "轮回台出口"} }
x256233_g_Impact1 = 2092
x256233_g_npcid = 0
--MisDescEnd
x256233_g_ExpBonus1 = 100000
--**********************************

function x256233_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    --DelQuest(sceneId, selfId, x256233_g_MissionId)
    
	if IsQuestHaveDone(sceneId, selfId, x256233_g_MissionId) > 0 then
		return 
	end
	--if IsQuestHaveDone(sceneId, selfId, x256233_g_MissionIdPre)> 0 then 
						local state = GetQuestStateNM(sceneId,selfId,NPCId,x256233_g_MissionId)
						AddQuestTextNM( sceneId, selfId, NPCId, x256233_g_MissionId, state, -1 )
	--end
end

function x256233_DispatchMissionInfo( sceneId, selfId, NPCId )

		if x256233_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256233_g_ExpBonus )
		end
		if x256233_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256233_g_BonusMoney1 )
		end
		if x256233_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256233_g_BonusMoney2 )
		end
		if x256233_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256233_g_BonusMoney3 )
		end
		if x256233_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256233_g_BonusMoney4 )
		end
		if x256233_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256233_g_BonusMoney5 )
		end
		if x256233_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256233_g_BonusMoney6 )
		end
		for i, item in x256233_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.id, item.num)
	  end
		for i, item in x256233_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

--任务入口函数

--**********************************
function x256233_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
    x256233_g_npcid =   NPCId
	if IsQuestHaveDone(sceneId, selfId, x256233_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256233_g_MissionId) > 0 then
			if x256233_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
            
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256233_g_MissionName)
						AddQuestText(sceneId,x256233_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x256233_g_ScriptId, x256233_g_MissionId);
			else
          
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256233_g_MissionName)
						AddQuestText(sceneId,x256233_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x256233_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256233_g_ScriptId, x256233_g_MissionId);
			end
  elseif x256233_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x256233_g_MissionName)
			AddQuestText(sceneId,x256233_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x256233_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x256233_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x256233_g_MissionHelp )
			end
			x256233_DispatchMissionInfo( sceneId, selfId, NPCId )
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256233_g_ScriptId, x256233_g_MissionId);
  end
end
--**********************************
function x256233_ProcAcceptCheck(sceneId, selfId, NPCId)
	if IsQuestHaveDone(sceneId, selfId, x256233_g_MissionId) > 0 then
		return 0
	elseif GetLevel(sceneId, selfId)< x256233_g_LevelLess then
		return 0
	end
	return 1
end
--**********************************
function x256233_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x256233_g_MissionId)
	if GetQuestParam(sceneId,selfId,misIndex,0) == x256233_g_DemandKill[1].num then
             
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	        return 1
	end
	return 0
end
--**********************************
function x256233_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256233_g_MissionId) > 0 then
				return 
		end
		
		--检查前置任务
--		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256233_g_MissionId  )
--		if FrontMissiontId1 ~= -1 then
--			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
--				return 0
--			end
--		end
--		if FrontMissiontId2 ~= -1 then
--			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
--				return 0
--			end
--		end
--		if FrontMissiontId3 ~= -1 then
--			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
--				return 0
--			end
--		end
		
		if x256233_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x256233_g_MissionId, x256233_g_ScriptId, 1, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			
           
						x256233_Msg2toplayer( sceneId, selfId,0)
						--if x256233_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x256233_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************
function x256233_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256233_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x256233_g_MissionId)
		
	  x256233_Msg2toplayer( sceneId, selfId,1)
end
--**********************************
function x256233_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x256233_g_BonusItem do
		AddItem( sceneId, item.id, item.num )
  end
  for j, item in x256233_g_BonusChoiceItem do
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
function x256233_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId)
	if IsHaveQuest(sceneId,selfId, x256233_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256233_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256233_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256233_g_MissionId) > 0 then
				x256233_Msg2toplayer( sceneId, selfId,2)
				
				QuestCom(sceneId, selfId, x256233_g_MissionId)
                x256233_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256233_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x256233_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		    end
    		    EndAddItem(sceneId,selfId)
    		    local nCount = GetNearTeamCount(sceneId, selfId)
    			if nCount > 0 then
	    			for i = 0,nCount - 1 do
	    				
	    				local objId = GetNearTeamMember(sceneId, selfId, i)
		    			if IsPlayerStateNormal(sceneId,objId ) == 1 and objId ~= selfId then --是否存在
		    				AddExp(sceneId, objId, x256233_g_ExpBonus1);
		    			end
	    				
	    			end
    			end
				--CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256233_g_MissionIdNext )	
   end
end

function x256233_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
   	  local bFind  = 0
    for i ,item in x256233_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x256233_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x256233_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x256233_g_MissionId, state, -1 )
		end
end

function x256233_GetBonus( sceneId, selfId,NpcID)
	  if x256233_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256233_g_ExpBonus);
  	end
		if x256233_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256233_g_BonusMoney1 )
	  end
		if x256233_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256233_g_BonusMoney2 )
	  end
		if x256233_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256233_g_BonusMoney3 )
		end
		if x256233_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256233_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256233_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256233_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256233_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256233_g_BonusMoney6)
		end
end

function x256233_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务："..x256233_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务："..x256233_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务："..x256233_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务："..x256233_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务："..x256233_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务："..x256233_g_MissionName.."！", 0, 3)
				if x256233_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x256233_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x256233_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x256233_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x256233_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x256233_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x256233_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x256233_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x256233_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x256233_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x256233_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x256233_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x256233_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x256233_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

--**********************************

function x256233_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	if	objdataId ==x256233_g_DemandKill[1].id then
	 local KilledNum = GetMonsterOwnerCount( sceneId, objId ) --取得这个怪物死后拥有分配权的人数
		for i = 0, KilledNum-1 do
			local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --取得拥有分配权的人的objId
            if humanObjId ~= -1 then
                 if IsHaveQuest(sceneId,humanObjId, x256233_g_MissionId) > 0 then
                    local misIndex = GetQuestIndexByID(sceneId,humanObjId,x256233_g_MissionId)
										if GetQuestParam(sceneId,humanObjId,misIndex,0) < 1 then
												SetQuestByIndex(sceneId,humanObjId,misIndex,0,GetQuestParam(sceneId,humanObjId,misIndex,0)+1)
												Msg2Player(sceneId, humanObjId, format("消灭轮回台的隐藏巨兽   %d/1", GetQuestParam(sceneId,humanObjId,misIndex,0)), 0, 3)
												x256233_CheckSubmit( sceneId, humanObjId)
										end
                end
            end
		end
	end
end
--**********************************

function x256233_OnUseItem( sceneId, selfId, BagIndex, impactId )
	local sceneType = GetSceneType(sceneId) ;
	if sceneType == 1 then 	
	
		local fubentype = GetFubenData_Param(sceneId,0) ;		--取得副本号
		local fubenscript = GetFubenData_Param(sceneId,1) ; 	--取得脚本号
		local level =GetLevel(sceneId, selfId)
		if IsQuestHaveDone(sceneId, selfId, x256233_g_MissionId) > 0 then
				Msg2Player(sceneId, selfId, "你已经完成过本任务了。", 0, 3)
				return 
		end
		if IsHaveQuest(sceneId,selfId, x256233_g_MissionId) > 0 then
				Msg2Player(sceneId, selfId, "你已经接受了这个任务", 0, 3)
				return
		end
		if 	fubentype==FUBEN_FUTUTA4  then      	--在轮回台场景
			if level	>=	x256233_g_LevelLess	 then
				
			   		AddQuest( sceneId, selfId, x256233_g_MissionId, x256233_g_ScriptId, 1, 0, 0,1)
			   		Msg2Player(sceneId, selfId, "你接受了任务：【副本】轮回台的巨兽", 0, 3)
     		   		CreateMonster(sceneId, 2533,62,58,5,1,-1,-1,21,1200000)
     		   		DelItem( sceneId,selfId,12030033,1 )	
     		
     		else
    		   Msg2Player(sceneId, selfId, "你的等级不足", 0, 3)	
    		end
    	end
    else 
    		Msg2Player(sceneId, selfId, "只有在轮回台副本内才能召唤巨兽", 0, 3)	
    	
	end
end
--**********************************
function x256233_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256233_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x256233_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256233_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x256233_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256233_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256233_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256233_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256233_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256233_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end





