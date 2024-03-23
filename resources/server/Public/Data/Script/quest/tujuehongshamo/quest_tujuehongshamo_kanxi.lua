--【剧情】逃出生天

--MisDescBegin
x203313_g_ScriptId = 203313
x203313_g_MissionIdPre =676
x203313_g_MissionId = 671
x203313_g_LevelLess	= 	75
x203313_g_MissionIdNext = -1
x203313_g_Name	={}
x203313_g_ExtTarget={{type=20,n=1,target="找到@npc_114033，保护两位公主一起逃出红沙漠"}}
x203313_g_MissionName="【剧情】逃出生天"
x203313_g_MissionInfo="\t趁他们的主力还没有到，快赶到东边的山脚下，那里有一条小路，马匹可以顺利通过，忽必烈和贵由正在那里等着我们。"  --任务描述
x203313_g_MissionTarget=""		
x203313_g_MissionCompleted="\t太好了，这里一切都已经准备好了，公主正在车上等待你们。趁他们还没有追上来，快保护两位公主从小路走！"					--完成任务npc说话的话
x203313_g_ContinueInfo=	""
x203313_g_MissionHelp =	""
x203313_g_DemandItem ={}
x203313_g_BonusMoney1 =750
x203313_g_BonusMoney2 =0
x203313_g_BonusMoney3 =0
x203313_g_BonusMoney4 =0
x203313_g_BonusMoney5 =86
x203313_g_BonusMoney6 =0
x203313_g_BonusItem	=	{}
x203313_g_BonusChoiceItem ={}
x203313_g_ExpBonus = 440000
x203313_g_NpcGUID ={{ guid = 114033, name = "贵由"}}

--MisDescEnd
x203313_g_doing = 0
x203313_g_mohemo = -1
x203313_g_zhalanding = -1
x203313_g_quchulv = -1
x203313_g_shibing1 = -1
x203313_g_shibing2 = -1
x203313_g_hedan = -1
x203313_g_xuliewu = -1
x203313_g_alibuge = -1
x203313_g_baierda = -1
x203313_g_mengguyongshi1 = -1
x203313_g_mengguyongshi2 = -1
x203313_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
--**********************************


----------------------------------------------------------------------------------------------
--向周围玩家放特效，不可频繁使用
----------------------------------------------------------------------------------------------
function x203313_PlayeffectToNearPlayer(sceneId,npcID,nEffect)

	if IsObjValid(sceneId,npcID) ~= 1 then
		return
	end
	
	local nHumanCount = GetScenePlayerCount( sceneId )
	for i=0,nHumanCount do

		local objId = GetScenePlayerObjId(sceneId,i)
		if IsPlayerStateNormal(sceneId,objId) == 1 then
			
			if GetDist(sceneId,objId,npcID,25 ) <= 25 then
				CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,objId,nEffect)
			end
		end
	end

end

function x203313_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if GetLevel( sceneId, selfId) < x203313_g_LevelLess then
		return
   end

	if IsQuestHaveDone(sceneId, selfId, x203313_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203313_g_MissionIdPre)> 0 then
	
						if IsHaveQuest(sceneId,selfId, x203313_g_MissionId) <= 0 then
								local state = GetQuestStateNM(sceneId,selfId,NPCId,x203313_g_MissionId)
								AddQuestTextNM( sceneId, selfId, NPCId, x203313_g_MissionId, state, -1 )
						end
			
	end
end

function x203313_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203313_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203313_g_ExpBonus )
		end
		if x203313_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203313_g_BonusMoney1 )
		end
		if x203313_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203313_g_BonusMoney2 )
		end
		if x203313_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203313_g_BonusMoney3 )
		end
		if x203313_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203313_g_BonusMoney4 )
		end
		if x203313_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203313_g_BonusMoney5 )
		end
		if x203313_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203313_g_BonusMoney6 )
		end
		for i, item in x203313_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203313_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203313_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x203313_g_MissionId) > 0 then
		return 
	end
	if GetLevel( sceneId, selfId) < x203313_g_LevelLess then
		return
   end
	if IsHaveQuest(sceneId,selfId, x203313_g_MissionId) > 0 then
			if x203313_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203313_g_MissionName)
						AddQuestText(sceneId,x203313_g_MissionCompleted)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203313_g_ScriptId, x203313_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203313_g_MissionName)
						AddQuestText(sceneId,x203313_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203313_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203313_g_ScriptId, x203313_g_MissionId);
			end
  elseif x203313_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203313_g_MissionName)
			AddQuestText(sceneId,x203313_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x203313_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203313_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x203313_g_MissionHelp )
			end
			x203313_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203313_g_ScriptId, x203313_g_MissionId);
  end
	
end
--**********************************

function x203313_ProcAcceptCheck(sceneId, selfId, NPCId)

		
						return 1
		

end
--**********************************
function x203313_CheckSubmit( sceneId, selfId, NPCId)


	        return 1
	
end
--**********************************
function x203313_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203313_g_MissionId) > 0 then
				return 
		end
			if GetLevel( sceneId, selfId) < x203313_g_LevelLess then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203313_g_MissionId  )
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
	
		if x203313_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203313_g_MissionId, x203313_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
				
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x203313_Msg2toplayer( sceneId, selfId,0)
		  			BeginAddItem(sceneId)
							for i, item in x203313_g_DemandItem do
 								AddItem( sceneId, item.item, item.num )
							end
    				EndAddItem(sceneId,selfId)
    				--AddItemListToPlayer(sceneId,selfId)	
						--if x203313_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x203313_g_MissionId)								                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x203313_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203313_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203313_g_MissionId)
	  x203313_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x203313_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x203313_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203313_g_BonusChoiceItem do
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
function x203313_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203313_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203313_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203313_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203313_g_MissionId) > 0 then
				x203313_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203313_g_MissionId)
				x203313_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203313_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203313_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		
    		
    			if x203313_g_doing==0 then
						if x203313_g_mohemo==-1 then
    			    			x203313_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
										x203313_g_doing =1
										x203313_g_mohemo=CreateMonster(sceneId, 851,207,137,3,1,-1,-1,20,30000,180,"摩诃末")
									  x203313_g_zhalanding=CreateMonster(sceneId, 852,203,136,3,1,-1,-1,20,30000,180,"扎兰丁")
									  x203313_g_quchulv=CreateMonster(sceneId, 854,208,140,3,1,-1,-1,20,30000,180,"屈出律")
									  x203313_g_shibing1=CreateMonster(sceneId, 843,207,145,3,1,-1,-1,20,30000,180,"突厥士兵")
										x203313_g_shibing2=CreateMonster(sceneId, 843,197,141,3,1,-1,-1,20,30000,180,"突厥士兵")
										x203313_g_shibing2=CreateMonster(sceneId, 843,103,143,3,1,-1,-1,20,30000,180,"突厥士兵")
										x203313_g_hedan=CreateMonster(sceneId, 859,209,130,3,1,-1,-1,20,30000,0,"合丹")
										x203313_g_xuliewu=CreateMonster(sceneId, 859,203,126,3,1,-1,-1,20,30000,0,"旭烈兀")
										x203313_g_alibuge=CreateMonster(sceneId, 859,214,119,3,1,-1,-1,20,30000,0,"阿里不哥")
										x203313_g_baierda=CreateMonster(sceneId, 859,207,118,3,1,-1,-1,20,30000,0,"拜尔答")
    			          x203313_g_PROTECTINFO.StartTime = GetCurrentTime()
										x203313_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 203313, "OnScneneTimer", 1)
    			  end
    			--elseif x203313_g_doing<=5 then
    								--if x203313_g_PROTECTINFO.PlayerNum > 5  then
												--return
										--end
									--	x203313_g_PROTECTINFO.PlayerNum = x203313_g_PROTECTINFO.PlayerNum + 1
										--x203313_g_PROTECTINFO.PlayerId[x203313_g_PROTECTINFO.PlayerNum] = selfId
						  		--	AddQuest( sceneId, selfId, x203313_g_MissionId, x203313_g_ScriptId, 1, 0, 0)
					  			--	x203313_Msg2toplayer( sceneId, selfId,0)
					--else
								--BeginQuestEvent(sceneId)
								--strText = "#Y现在不能接这个任务"
								--AddQuestText(sceneId,strText)
								--EndQuestEvent(sceneId)
								--DispatchQuestTips(sceneId,selfId)
					end
	 	end        
									
    		--AddItemListToPlayer(sceneId,selfId)

   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203313_g_MissionIdNext )	
end


function x203313_OnScneneTimer(sceneId)
	if x203313_g_doing==1   then
		if GetCurrentTime() - x203313_g_PROTECTINFO.StartTime >= 3   then
						x203313_g_doing = 2
						if IsObjValid (sceneId,x203313_g_zhalanding) == 1 then
								NpcTalk(sceneId, x203313_g_zhalanding, "嘿嘿，想走？哪有那么容易！", -1)
						end
		end
	elseif x203313_g_doing==2   then
		if GetCurrentTime() - x203313_g_PROTECTINFO.StartTime >= 6   then
						x203313_g_doing = 3
						if IsObjValid (sceneId,x203313_g_mohemo) == 1 then
								NpcTalk(sceneId, x203313_g_mohemo, "留下两位公主，我或许可以考虑放你们一条生路！", -1)
						end
		end
	elseif x203313_g_doing==3   then
		if GetCurrentTime() - x203313_g_PROTECTINFO.StartTime >= 10   then
						x203313_g_doing = 4
						if IsObjValid (sceneId,x203313_g_zhalanding) == 1 then
								NpcTalk(sceneId, x203313_g_zhalanding, "我们才是真正的亚洲之王，成吉思汗算什么东西！", -1)
						end
		end
	elseif x203313_g_doing==4   then
		if GetCurrentTime() - x203313_g_PROTECTINFO.StartTime >= 15   then
						x203313_g_doing = 5
						if IsObjValid (sceneId,x203313_g_hedan) == 1 then
								NpcTalk(sceneId, x203313_g_hedan, "旭烈兀，你们快走！", -1)
						end
		end
	elseif x203313_g_doing==5   then
		if GetCurrentTime() - x203313_g_PROTECTINFO.StartTime >= 20   then
						x203313_g_doing = 6
						if IsObjValid (sceneId,x203313_g_hedan) == 1 then
								NpcTalk(sceneId, x203313_g_hedan, "勇士们，猎狗终须山上死，大将难免阵前亡！为了我们大蒙古国的荣誉，和他们拼了！", -1)
								--CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 14)
								--播放周围玩家
								x203313_PlayeffectToNearPlayer(sceneId,x203313_g_hedan,14)
						end
		end
	elseif x203313_g_doing==6   then
		if GetCurrentTime() - x203313_g_PROTECTINFO.StartTime >= 25   then
						x203313_g_doing = 7
						if IsObjValid (sceneId,x203313_g_xuliewu) == 1 then
								NpcTalk(sceneId, x203313_g_xuliewu, "合丹，合丹！", -1)	
						end
		end
	elseif x203313_g_doing==7   then
		if GetCurrentTime() - x203313_g_PROTECTINFO.StartTime >= 31   then
						x203313_g_doing = 8
						if IsObjValid (sceneId,x203313_g_hedan) == 1 then							
									NpcTalk(sceneId, x203313_g_hedan, "旭烈兀，我像英雄一样的死去没有怨恨，只求你帮我照顾好贵由！", -1)
						end	
		end
	elseif x203313_g_doing==8   then
		if GetCurrentTime() - x203313_g_PROTECTINFO.StartTime >= 35   then
						x203313_g_doing = 9
						x203313_CloseTimer(sceneId, x203313_g_PROTECTINFO.ScneneTimerIndex)
					end
	end
end


--**********************************
--关闭计时器
--**********************************
function x203313_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x203313_g_doing = 0
	x203313_g_mohemo = -1
	x203313_g_zhalanding = -1
	x203313_g_quchulv = -1
	x203313_g_shibing1 = -1
	x203313_g_shibing2 = -1
	x203313_g_hedan = -1
	x203313_g_xuliewu = -1
	x203313_g_mengguyongshi1 = -1
	x203313_g_mengguyongshi2 = -1
	x203313_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
end


function x203313_GetBonus( sceneId, selfId,NpcID)
	  if x203313_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203313_g_ExpBonus);
  	end
		if x203313_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203313_g_BonusMoney1 )
	  end
		if x203313_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203313_g_BonusMoney2 )
	  end
		if x203313_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203313_g_BonusMoney3 )
		end
		if x203313_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203313_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203313_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203313_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203313_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203313_g_BonusMoney6)
		end
end

function x203313_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x203313_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x203313_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203313_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203313_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203313_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203313_g_MissionName.."！", 0, 3)
				if x203313_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x203313_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x203313_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x203313_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x203313_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x203313_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x203313_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x203313_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x203313_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x203313_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x203313_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x203313_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x203313_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x203313_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x203313_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203313_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203313_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203313_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203313_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203313_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x203313_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203313_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203313_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203313_g_MissionId, state, -1 )
		end
end

function x203313_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203313_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203313_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203313_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203313_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203313_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end