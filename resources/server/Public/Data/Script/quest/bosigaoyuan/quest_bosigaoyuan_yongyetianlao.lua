--永夜天牢

--MisDescBegin
x203320_g_ScriptId = 203320
x203320_g_MissionIdPre =753
x203320_g_MissionId = 754
x203320_g_LevelLess	= 	84
x203320_g_MissionIdNext = -1
x203320_g_Name	={}
x203320_g_ExtTarget={{type=20,n=1,target="找到@npc_116000"}}
x203320_g_MissionName="【剧场】永夜天牢<五>"
x203320_g_MissionInfo="\t我已用定天罗盘测量好了封印这几个魔头的位置，就在离这里不远处的山脚下，我这就去准备，请你通知大汗。"  --任务描述
x203320_g_MissionTarget=""		
x203320_g_MissionCompleted="\t好，今天就要将这魔头永远封印在永夜天牢之中！ "					--完成任务npc说话的话
x203320_g_ContinueInfo=""
x203320_g_MissionHelp =	""
x203320_g_DemandItem ={}
x203320_g_ExpBonus = 626000
x203320_g_BonusMoney1 =840
x203320_g_BonusMoney2 =0
x203320_g_BonusMoney3 =0
x203320_g_BonusMoney4 =0
x203320_g_BonusMoney5 =96
x203320_g_BonusMoney6 =0
x203320_g_BonusItem	=	{}
x203320_g_BonusChoiceItem ={}
x203320_g_NpcGUID ={{ guid = 116000, name = "成吉思汗"} }

--MisDescEnd
x203320_g_chengjisihan =-1
x203320_g_doing =0
x203320_g_mohemo =-1
x203320_g_wosilahei =-1
x203320_g_mengguwushi1 =-1
x203320_g_mengguwushi2 =-1
x203320_g_mengguwushi3 =-1
x203320_g_mengguwushi4 =-1
x203320_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
x203320_g_acceptid =-1
--**********************************

function x203320_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if IsQuestHaveDone(sceneId, selfId, x203320_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203320_g_MissionIdPre)> 0 then
	
						if IsHaveQuest(sceneId,selfId, x203320_g_MissionId) <= 0 then
								local state = GetQuestStateNM(sceneId,selfId,NPCId,x203320_g_MissionId)
								AddQuestTextNM( sceneId, selfId, NPCId, x203320_g_MissionId, state, -1 )
						end
			
	end
end

function x203320_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203320_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203320_g_ExpBonus )
		end
		if x203320_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203320_g_BonusMoney1 )
		end
		if x203320_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203320_g_BonusMoney2 )
		end
		if x203320_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203320_g_BonusMoney3 )
		end
		if x203320_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203320_g_BonusMoney4 )
		end
		if x203320_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203320_g_BonusMoney5 )
		end
		if x203320_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203320_g_BonusMoney6 )
		end
		for i, item in x203320_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203320_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203320_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x203320_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203320_g_MissionId) > 0 then
			if x203320_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203320_g_MissionName)
						AddQuestText(sceneId,x203320_g_MissionCompleted)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203320_g_ScriptId, x203320_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203320_g_MissionName)
						AddQuestText(sceneId,x203320_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203320_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203320_g_ScriptId, x203320_g_MissionId);
			end
  elseif x203320_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203320_g_MissionName)
			AddQuestText(sceneId,x203320_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x203320_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203320_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x203320_g_MissionHelp )
			end
			x203320_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203320_g_ScriptId, x203320_g_MissionId);
  end
	
end
--**********************************

function x203320_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x203320_CheckSubmit( sceneId, selfId, NPCId)

	        return 1
	
end
--**********************************
function x203320_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203320_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203320_g_MissionId  )
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
		
		if x203320_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203320_g_MissionId, x203320_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x203320_Msg2toplayer( sceneId, selfId,0)
		  			--BeginAddItem(sceneId)																																----添加送信物品
						--	for i, item in x203320_g_DemandItem do
 						--		AddItem( sceneId, item.item, item.num )
						--	end
    				--EndAddItem(sceneId,selfId)                                                          ----添加送信物品
    				--AddItemListToPlayer(sceneId,selfId)	
						--if x203320_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x203320_g_MissionId)								                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x203320_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203320_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203320_g_MissionId)
	  x203320_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x203320_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x203320_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203320_g_BonusChoiceItem do
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
function x203320_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203320_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203320_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203320_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203320_g_MissionId) > 0 then
				x203320_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203320_g_MissionId)
				--DelItem( sceneId,selfId,13010030,1 )                                                --删除送信的物品
				x203320_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203320_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203320_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		
    		x203320_g_chengjisihan =FindMonsterByGUID( sceneId,116000)
    			if x203320_g_doing==0 then
						if x203320_g_mohemo==-1 then
								if IsObjValid (sceneId,x203320_g_chengjisihan) == 1 then
    			    			NpcTalk(sceneId, x203320_g_chengjisihan, "把暴君摩诃末带上来！", -1)
    			    	end
    			    			x203320_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
										x203320_g_doing =2
										x203320_g_mengguwushi1=CreateMonster(sceneId, 932,126,35,3,1,-1,-1,20,23000,180)
    			          x203320_g_mengguwushi2=CreateMonster(sceneId, 932,126,37,3,1,-1,-1,20,23000,180)
    			          x203320_g_mengguwushi3=CreateMonster(sceneId, 932,130,37,3,1,-1,-1,20,23000,180)
    			          x203320_g_mengguwushi4=CreateMonster(sceneId, 932,130,35,3,1,-1,-1,20,23000,180)
    			          x203320_g_wosilahei=CreateMonster(sceneId, 934,127,34,3,1,-1,-1,20,23000,180)
										x203320_g_mohemo=CreateMonster(sceneId, 919,129,34,3,1,-1,-1,20,23000,180)
										-- SetPatrolId(sceneId, x203320_g_guojing, 3)	
    			    			--x203320_g_PROTECTINFO.PlayerNum = 1                    
										--x203320_g_PROTECTINFO.PlayerId[1] = selfId             
    			          x203320_g_PROTECTINFO.StartTime = GetCurrentTime()
										x203320_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 203320, "OnScneneTimer", 1)
    			  end
    			--elseif x203320_g_doing<=5 then
    								--if x203320_g_PROTECTINFO.PlayerNum > 5  then
												--return
										--end
									--	x203320_g_PROTECTINFO.PlayerNum = x203320_g_PROTECTINFO.PlayerNum + 1
										--x203320_g_PROTECTINFO.PlayerId[x203320_g_PROTECTINFO.PlayerNum] = selfId
						  		--	AddQuest( sceneId, selfId, x203320_g_MissionId, x203320_g_ScriptId, 1, 0, 0)
					  			--	x203320_Msg2toplayer( sceneId, selfId,0)
					--else
								--BeginQuestEvent(sceneId)
								--strText = "#Y现在不能接这个任务"
								--AddQuestText(sceneId,strText)
								--EndQuestEvent(sceneId)
								--DispatchQuestTips(sceneId,selfId)
					end
	 	end        
									
    		--AddItemListToPlayer(sceneId,selfId)

   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203320_g_MissionIdNext )	
end


function x203320_OnScneneTimer(sceneId)
	if x203320_g_doing==2   then
		--if GetCurrentTime() - x203320_g_PROTECTINFO.StartTime >= 2   then
					x203320_g_doing = 3
					--if IsObjValid (sceneId,x203320_g_tuolei) == 1 then
						--SetPatrolId(sceneId, x203320_g_tuolei, 5)	
					--end
					--if IsObjValid (sceneId,x203320_g_mohemo) == 1 then
        		--SetPatrolId(sceneId, x203320_g_mohemo, 4)
        	--end
		--end
	--elseif x203320_g_doing == 3   then
	if GetCurrentTime() - x203320_g_PROTECTINFO.StartTime >= 2   then
			  x203320_g_doing =3
				if IsObjValid (sceneId,x203320_g_chengjisihan) == 1 then
						NpcTalk(sceneId, x203320_g_chengjisihan, "摩诃末，你暴虐成性，今天就是你的末日", -1)
				end
  end
	elseif x203320_g_doing == 3   then
			if GetCurrentTime() - x203320_g_PROTECTINFO.StartTime >= 4   then
						x203320_g_doing =5
						if IsObjValid (sceneId,x203320_g_wosilahei) == 1 then
								NpcTalk(sceneId, x203320_g_wosilahei, "哼！", -1)
						end
			end
	elseif x203320_g_doing == 5   then
			if GetCurrentTime() - x203320_g_PROTECTINFO.StartTime >= 6  then
						x203320_g_doing =6
						if IsObjValid (sceneId,x203320_g_chengjisihan) == 1 then
								NpcTalk(sceneId, x203320_g_chengjisihan, "我知道你们都是不死之身，我会在此处为你们建一间永远沉没于黑暗之中的天牢，你们也将永生永世被囚禁！", -1)
						end
			end
	elseif x203320_g_doing == 6   then
			if GetCurrentTime() - x203320_g_PROTECTINFO.StartTime >= 9   then
						x203320_g_doing =7
						if IsObjValid (sceneId,x203320_g_mohemo) == 1 then
								NpcTalk(sceneId, x203320_g_mohemo, "成吉思汗，我们不会屈服，我相信，总有一天，我的儿子札兰丁会冲破这永远黑夜的天牢，让我们的王朝重现光辉！", -1)
						end
			end
	elseif x203320_g_doing == 7   then
			--if GetCurrentTime() - x203320_g_PROTECTINFO.StartTime >= 11   then
						--x203320_g_doing =8
						--if IsObjValid (sceneId,x203320_g_mohemo) == 1 then
								--NpcTalk(sceneId, x203320_g_mohemo, "住手！我就是你要找的刺客，你堂堂乞颜部大汗，难为一个小孩子算什么本事？", -1)
						--end
	    --end
	---elseif x203320_g_doing == 8   then
			if GetCurrentTime() - x203320_g_PROTECTINFO.StartTime >= 13   then
						x203320_g_doing =9
						if IsObjValid (sceneId,x203320_g_chengjisihan) == 1 then
								NpcTalk(sceneId, x203320_g_chengjisihan, "把他们拉下去，封印在永远是黑夜的天牢里。", -1)
						end
						if IsObjValid (sceneId,x203320_g_mengguwushi1) == 1 then
								NpcTalk(sceneId, x203320_g_mengguwushi1, "是！", -1)
						end
						if IsObjValid (sceneId,x203320_g_mengguwushi4) == 1 then
								NpcTalk(sceneId, x203320_g_mengguwushi4, "是！", -1)
						end
			end
	
	elseif x203320_g_doing == 9   then
			--if GetCurrentTime() - x203320_g_PROTECTINFO.StartTime >= 17   then
						---x203320_g_doing =10
						---if IsObjValid (sceneId,x203320_g_mohemo) == 1 then
								---NpcTalk(sceneId, x203320_g_mohemo, "想不到......铁木真竟然如此大度，我愿为大汗出力，深水可使横断，坚石可使粉碎！", -1)
						---end
			--end
	---elseif x203320_g_doing == 10   then
			--if GetCurrentTime() - x203320_g_PROTECTINFO.StartTime >= 15   then
						--x203320_g_doing =11
						--if IsObjValid (sceneId,x203320_g_chengjisihan) == 1 then
								--NpcTalk(sceneId, x203320_g_chengjisihan, "好！从今以后，你就是我的---哲别神射手！", -1)
						--end
			--end
  ---elseif x203320_g_doing==11 then
			if GetCurrentTime() - x203320_g_PROTECTINFO.StartTime >= 20   then
			x203320_g_doing=12
			x203320_CloseTimer(sceneId, x203320_g_PROTECTINFO.ScneneTimerIndex)
			end
	end
	end



--**********************************
--关闭计时器
--**********************************
function x203320_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x203320_g_doing =0
	x203320_g_chengjisihan =-1
  x203320_g_doing =0
  x203320_g_mohemo =-1
  x203320_g_wosilahei =-1
  x203320_g_mengguwushi1 =-1
  x203320_g_mengguwushi2 =-1
  x203320_g_mengguwushi3 =-1
  x203320_g_mengguwushi4 =-1
	x203320_g_acceptid =-1
	x203320_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
end


function x203320_GetBonus( sceneId, selfId,NpcID)
	  if x203320_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203320_g_ExpBonus);
  	end
		if x203320_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203320_g_BonusMoney1 )
	  end
		if x203320_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203320_g_BonusMoney2 )
	  end
		if x203320_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203320_g_BonusMoney3 )
		end
		if x203320_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203320_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203320_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203320_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203320_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203320_g_BonusMoney6)
		end
end

function x203320_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x203320_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x203320_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203320_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203320_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203320_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203320_g_MissionName.."！", 0, 3)
				if x203320_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x203320_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x203320_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x203320_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x203320_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x203320_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x203320_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x203320_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x203320_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x203320_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x203320_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x203320_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x203320_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x203320_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x203320_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203320_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203320_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203320_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203320_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203320_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x203320_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203320_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203320_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203320_g_MissionId, state, -1 )
		end
end

function x203320_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203320_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203320_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203320_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203320_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203320_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end