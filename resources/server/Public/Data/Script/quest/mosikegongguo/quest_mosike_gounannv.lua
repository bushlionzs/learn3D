--策反喀山大公

--MisDescBegin
x203327_g_ScriptId = 203327
x203327_g_MissionIdPre = 808
x203327_g_MissionId = 809
x203327_g_LevelLess	= 	88
x203327_g_MissionIdNext = 810
x203327_g_Name	={}
x203327_g_ExtTarget={{type=20,n=1,target="找到@npc_117005"}}
x203327_g_MissionName="【剧场】策反喀山大公<二>"
x203327_g_MissionInfo="\t好，我这就去见艾尔莎，真不知道她突然找我到底有什么事，我，我有点激动……\n\t这样吧，你先去告诉她，我马上就到，我，我得准备一下！"  --任务描述
x203327_g_MissionTarget=""		
x203327_g_MissionCompleted="\t好，我就在这里等他过来吧。 "					--完成任务npc说话的话
x203327_g_ContinueInfo=""
x203327_g_MissionHelp =	""
x203327_g_DemandItem ={}
x203327_g_ExpBonus = 684000
x203327_g_BonusMoney1 =880
x203327_g_BonusMoney2 =0
x203327_g_BonusMoney3 =0
x203327_g_BonusMoney4 =0
x203327_g_BonusMoney5 =106
x203327_g_BonusMoney6 =0
x203327_g_BonusItem	=	{}
x203327_g_BonusChoiceItem ={}
x203327_g_NpcGUID ={{ guid = 117005, name = "立陶宛大公"} }

--MisDescEnd
x203327_g_litaowandagong =-1
x203327_g_doing =0
x203327_g_kashandagong =-1
--x203327_g_kashandagong =-1
--x203327_g_litaowandagong =-1
--x203327_g_mengguwushi2 =-1
--x203327_g_mengguwushi3 =-1
--x203327_g_mengguwushi4 =-1
x203327_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0} --定义时钟控件
x203327_g_acceptid =-1
--**********************************

function x203327_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if IsQuestHaveDone(sceneId, selfId, x203327_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203327_g_MissionIdPre)> 0 then
			if IsHaveQuest(sceneId,selfId, x203327_g_MissionId) <= 0 then
						local state = GetQuestStateNM(sceneId,selfId,NPCId,x203327_g_MissionId)
						AddQuestTextNM( sceneId, selfId, NPCId, x203327_g_MissionId, state, -1 )
			end		
	end
end

function x203327_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203327_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203327_g_ExpBonus )
		end
		if x203327_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203327_g_BonusMoney1 )
		end
		if x203327_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203327_g_BonusMoney2 )
		end
		if x203327_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203327_g_BonusMoney3 )
		end
		if x203327_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203327_g_BonusMoney4 )
		end
		if x203327_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203327_g_BonusMoney5 )
		end
		if x203327_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203327_g_BonusMoney6 )
		end
		for i, item in x203327_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203327_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203327_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x203327_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203327_g_MissionId) > 0 then
			if x203327_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203327_g_MissionName)
						AddQuestText(sceneId,x203327_g_MissionCompleted)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203327_g_ScriptId, x203327_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203327_g_MissionName)
						AddQuestText(sceneId,x203327_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203327_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203327_g_ScriptId, x203327_g_MissionId);
			end
  elseif x203327_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203327_g_MissionName)
			AddQuestText(sceneId,x203327_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x203327_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203327_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x203327_g_MissionHelp )
			end
			x203327_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203327_g_ScriptId, x203327_g_MissionId);
  end
	
end
--**********************************

function x203327_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x203327_CheckSubmit( sceneId, selfId, NPCId)

	        return 1
	
end
--**********************************
function x203327_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203327_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203327_g_MissionId  )
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
		
		if x203327_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203327_g_MissionId, x203327_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x203327_Msg2toplayer( sceneId, selfId,0)
		  			--BeginAddItem(sceneId)																																----添加送信物品
						--	for i, item in x203327_g_DemandItem do
 						--		AddItem( sceneId, item.item, item.num )
						--	end
    				--EndAddItem(sceneId,selfId)                                                          ----添加送信物品
    				--AddItemListToPlayer(sceneId,selfId)	
						--if x203327_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x203327_g_MissionId)								                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x203327_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203327_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203327_g_MissionId)
	  x203327_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x203327_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x203327_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203327_g_BonusChoiceItem do
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
function x203327_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203327_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203327_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203327_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203327_g_MissionId) > 0 then
				x203327_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203327_g_MissionId)
				--DelItem( sceneId,selfId,13010030,1 )                                                --删除送信的物品
				x203327_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203327_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203327_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		
    		x203327_g_litaowandagong =FindMonsterByGUID( sceneId,117005)
    			if x203327_g_doing==0 then
						if x203327_g_kashandagong==-1 then
								if IsObjValid (sceneId,x203327_g_litaowandagong) == 1 then
    			    			NpcTalk(sceneId, x203327_g_litaowandagong, "他来了！请你们帮我注意四周，不要被他们的爪牙听见！", -1)
    			    	end
    			    			x203327_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
										x203327_g_doing =1
										x203327_g_kashandagong=CreateMonster(sceneId, 2106,140,48,3,1,-1,-1,20,52500,180)      
    			          x203327_g_PROTECTINFO.StartTime = GetCurrentTime()
										x203327_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 203327, "OnScneneTimer", 1)
    			  end
					end
	 	end        
									
    		--AddItemListToPlayer(sceneId,selfId)

   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203327_g_MissionIdNext )	
end


function x203327_OnScneneTimer(sceneId)
	if x203327_g_doing==1   then				
	   if GetCurrentTime() - x203327_g_PROTECTINFO.StartTime >= 4   then
			  x203327_g_doing = 3
			 
				if IsObjValid (sceneId,x203327_g_litaowandagong) == 1 then
				
						NpcTalk(sceneId, x203327_g_litaowandagong, "山德鲁，你身为喀山大公真的想一辈子被人欺凌，被人看不起么？你，和他们一样，是个大公！", -1)
				end
     end
	 elseif x203327_g_doing == 3   then
			if GetCurrentTime() - x203327_g_PROTECTINFO.StartTime >= 9   then
						x203327_g_doing =5
						if IsObjValid (sceneId,x203327_g_kashandagong) == 1 then
								NpcTalk(sceneId, x203327_g_kashandagong, "我，我不想，可是我打不过他们，我怕……", -1)
						end
			end
	 elseif x203327_g_doing == 5   then
			if GetCurrentTime() - x203327_g_PROTECTINFO.StartTime >= 13  then
						x203327_g_doing =6
						if IsObjValid (sceneId,x203327_g_litaowandagong) == 1 then
								NpcTalk(sceneId, x203327_g_litaowandagong, "怕？你怕什么？作为一个男人，统治喀山的大公，你竟然和一个女人说害怕！", -1)
						end
			end
	 elseif x203327_g_doing == 6   then
			if GetCurrentTime() - x203327_g_PROTECTINFO.StartTime >= 18   then
						x203327_g_doing =7
						if IsObjValid (sceneId,x203327_g_kashandagong) == 1 then
								NpcTalk(sceneId, x203327_g_kashandagong, "不，不，我不是怕他们，我是怕，怕，我怕失败了，你会看不起我，怕会牵连你！", -1)
						end
			end
	 elseif x203327_g_doing == 7   then
			--if GetCurrentTime() - x203327_g_PROTECTINFO.StartTime >= 11   then
						--x203327_g_doing =8
						--if IsObjValid (sceneId,x203327_g_kashandagong) == 1 then
								--NpcTalk(sceneId, x203327_g_kashandagong, "住手！我就是你要找的刺客，你堂堂乞颜部大汗，难为一个小孩子算什么本事？", -1)
						--end
	    --end
	---elseif x203327_g_doing == 8   then
			if GetCurrentTime() - x203327_g_PROTECTINFO.StartTime >= 23   then
						x203327_g_doing =9
						if IsObjValid (sceneId,x203327_g_litaowandagong) == 1 then
								NpcTalk(sceneId, x203327_g_litaowandagong, "他们几个狼狈为奸，早已惹起众怒，今天的形势，蒙古大军一统斯拉夫地区已经是必然之势！", -1)
						end
			end
	 elseif x203327_g_doing == 9  then   
			if GetCurrentTime() - x203327_g_PROTECTINFO.StartTime >= 28   then 	
						x203327_g_doing =10			
						if IsObjValid (sceneId,x203327_g_litaowandagong) == 1 then
								NpcTalk(sceneId, x203327_g_litaowandagong, "我，艾尔莎，不仅是立陶宛的统治者，也是一个女人，我只想嫁给一个英雄，而不是一个委曲求全的狗熊！", -1)
						end
			end
	 elseif x203327_g_doing == 10   then	
			if GetCurrentTime() - x203327_g_PROTECTINFO.StartTime >= 32   then 
				x203327_g_doing =11		                                     				
						if IsObjValid (sceneId,x203327_g_kashandagong) == 1 then
								NpcTalk(sceneId, x203327_g_kashandagong, "好，既然你这么说，我也要让你看看，我山德鲁，喀山大公，也是一个男子汉！", -1)
						end
			end
	 elseif x203327_g_doing == 11   then
			if GetCurrentTime() - x203327_g_PROTECTINFO.StartTime >= 37   then      
				x203327_g_doing =12	
				if IsObjValid (sceneId,x203327_g_litaowandagong) == 1 then 
					NpcTalk(sceneId, x203327_g_litaowandagong, "好，等蒙古大军发出信号，我们就里应外合。事不成，我和你一起去上帝那里控诉他们！", -1)                                          
						---x203327_g_doing =10
				end		
						---if IsObjValid (sceneId,x203327_g_kashandagong) == 1 then
								---NpcTalk(sceneId, x203327_g_kashandagong, "想不到......铁木真竟然如此大度，我愿为大汗出力，深水可使横断，坚石可使粉碎！", -1)
						---end
			end
	 elseif x203327_g_doing == 12   then 
	     if GetCurrentTime() - x203327_g_PROTECTINFO.StartTime >= 42  then 
				x203327_g_doing =13		                                     				
						if IsObjValid (sceneId,x203327_g_kashandagong) == 1 then
	  				NpcTalk(sceneId, x203327_g_kashandagong, "好，我宁愿体无完肤的去见上帝，也不愿在恶魔爪下完整的生活！等着我，我要请大主教来替我们主持婚礼！", -1)
	---elseif x203327_g_doing == 10   then
			--if GetCurrentTime() - x203327_g_PROTECTINFO.StartTime >= 15   then
						--x203327_g_doing =11
						--if IsObjValid (sceneId,x203327_g_litaowandagong) == 1 then
								--NpcTalk(sceneId, x203327_g_litaowandagong, "好！从今以后，你就是我的---哲别神射手！", -1)
						end
			end
    elseif x203327_g_doing==13 then
			 if GetCurrentTime() - x203327_g_PROTECTINFO.StartTime >= 45  then
			  x203327_g_doing=13
			   x203327_CloseTimer(sceneId, x203327_g_PROTECTINFO.ScneneTimerIndex)
			 end
	 end
end



--**********************************
--关闭计时器
--**********************************
function x203327_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x203327_g_doing =0
	x203327_g_litaowandagong =-1
  x203327_g_doing =0
  x203327_g_kashandagong =-1
  --x203327_g_kashandagong =-1
  --x203327_g_litaowandagong =-1
  --x203327_g_mengguwushi2 =-1
  --x203327_g_mengguwushi3 =-1
  --x203327_g_mengguwushi4 =-1
	x203327_g_acceptid =-1
	x203327_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
end


function x203327_GetBonus( sceneId, selfId,NpcID)
	  if x203327_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203327_g_ExpBonus);
  	end
		if x203327_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203327_g_BonusMoney1 )
	  end
		if x203327_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203327_g_BonusMoney2 )
	  end
		if x203327_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203327_g_BonusMoney3 )
		end
		if x203327_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203327_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203327_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203327_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203327_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203327_g_BonusMoney6)
		end
end

function x203327_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x203327_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x203327_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203327_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203327_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203327_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203327_g_MissionName.."！", 0, 3)
				if x203327_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x203327_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x203327_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x203327_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x203327_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x203327_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x203327_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x203327_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x203327_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x203327_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x203327_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x203327_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x203327_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x203327_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x203327_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203327_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203327_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203327_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203327_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203327_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x203327_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203327_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203327_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203327_g_MissionId, state, -1 )
		end
end

function x203327_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203327_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203327_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203327_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203327_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203327_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end