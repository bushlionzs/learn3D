--询问状况

--MisDescBegin
x256056_g_ScriptId = 256056
x256056_g_MissionIdPre =1615
x256056_g_MissionId = 1616
x256056_g_LevelLess	= 	10 
x256056_g_MissionIdNext = 1617
x256056_g_Name	={}
x256056_g_ExtTarget={{type=20,n=1,target="找到@npc_138050"}}
x256056_g_MissionName="【主线】蒙古秘史<六>"
x256056_g_MissionInfo="\t用了美容秘方，我忽然间觉得皮肤好了很多，记忆也……恢复过来了，嘻嘻，哈喇图老爷子是寄放了一件羊皮袄在这，我拿给你。"  --任务描述
x256056_g_MissionTarget=""		
x256056_g_MissionCompleted="\t（哈喇图轻轻撕开羊皮袄的内衬，取出几页纸。）\n\t其实，他们所有人想要的秘密就在这件破旧的羊皮袄之中。 "					--完成任务npc说话的话
x256056_g_ContinueInfo=""
x256056_g_MissionHelp =	""
--x256056_g_DemandItem ={{item=13010030,num=1}}
x256056_g_BonusMoney1 =253
x256056_g_BonusMoney2 =0
x256056_g_BonusMoney3 =0
x256056_g_BonusMoney4 =0
x256056_g_BonusMoney5 =26
x256056_g_BonusMoney6 =0
x256056_g_BonusItem	=	{}
x256056_g_BonusChoiceItem ={}
x256056_g_ExpBonus = 2932
x256056_g_NpcGUID ={{ guid = 138050, name = "哈喇图"} }

--MisDescEnd
x256056_g_zhubaoshangren =0
x256056_g_doing =0
x256056_g_huhelu =-1
x256056_g_huwei1 =-1
x256056_g_huwei2 =-1
x256056_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
x256056_g_acceptid =-1
--**********************************

function x256056_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x256056_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x256056_g_MissionIdPre)> 0 then
	
						if IsHaveQuest(sceneId,selfId, x256056_g_MissionId) <= 0 then
								local state = GetQuestStateNM(sceneId,selfId,NPCId,x256056_g_MissionId)
								AddQuestTextNM( sceneId, selfId, NPCId, x256056_g_MissionId, state, -1 )
						end
			
	end
end

function x256056_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x256056_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256056_g_ExpBonus )
		end
		if x256056_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256056_g_BonusMoney1 )
		end
		if x256056_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256056_g_BonusMoney2 )
		end
		if x256056_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256056_g_BonusMoney3 )
		end
		if x256056_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256056_g_BonusMoney4 )
		end
		if x256056_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256056_g_BonusMoney5 )
		end
		if x256056_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256056_g_BonusMoney6 )
		end
		for i, item in x256056_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x256056_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x256056_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x256056_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256056_g_MissionId) > 0 then
			if x256056_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256056_g_MissionName)
						AddQuestText(sceneId,x256056_g_MissionCompleted)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x256056_g_ScriptId, x256056_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256056_g_MissionName)
						AddQuestText(sceneId,x256056_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x256056_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256056_g_ScriptId, x256056_g_MissionId);
			end
  elseif x256056_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x256056_g_MissionName)
			AddQuestText(sceneId,x256056_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x256056_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x256056_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x256056_g_MissionHelp )
			end
			x256056_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256056_g_ScriptId, x256056_g_MissionId);
  end
	
end
--**********************************

function x256056_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x256056_CheckSubmit( sceneId, selfId, NPCId)

	        return 1
	
end
--**********************************
function x256056_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256056_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256056_g_MissionId  )
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
		
		if x256056_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x256056_g_MissionId, x256056_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x256056_Msg2toplayer( sceneId, selfId,0)
						--if x256056_CheckSubmit(sceneId, selfId, NPCId) > 0 then
						local misIndex = GetQuestIndexByID(sceneId,selfId,x256056_g_MissionId)                                                  
	    			SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			x256056_g_zhubaoshangren =FindMonsterByGUID( sceneId,138500)
    				if x256056_g_doing==0 then
								if x256056_g_huhelu==-1 then
										x256056_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 256056, "OnScneneTimer", 1)
										if x256056_g_PROTECTINFO.ScneneTimerIndex >= 0 then
											if IsObjValid (sceneId,x256056_g_zhubaoshangren) == 1 then
    			    					NpcTalk(sceneId, x256056_g_zhubaoshangren, "哎呀，不好，有人找上门了。", -1)
    			    				end
    			    					x256056_g_doing =2
												x256056_g_huhelu=CreateMonster(sceneId, 139,285,126,3,1,-1,-1,20,-1,90,"胡和鲁","窝阔台汗国")
    			          		x256056_g_huwei1=CreateMonster(sceneId, 141,282,128,3,1,-1,-1,20,-1,90,"胡和鲁护卫")
    			          		x256056_g_huwei2=CreateMonster(sceneId, 141,282,124,3,1,-1,-1,20,-1,90,"胡和鲁护卫")		      
												-- SetPatrolId(sceneId, x256056_g_guojing, 3)	
    			    					--x256056_g_PROTECTINFO.PlayerNum = 1                    
												--x256056_g_PROTECTINFO.PlayerId[1] = selfId             
    			          		x256056_g_PROTECTINFO.StartTime = GetCurrentTime()
    			          end
    			  		end
    						--elseif x256056_g_doing<=5 then
    								--if x256056_g_PROTECTINFO.PlayerNum > 5  then
												--return
										--end
									--	x256056_g_PROTECTINFO.PlayerNum = x256056_g_PROTECTINFO.PlayerNum + 1
										--x256056_g_PROTECTINFO.PlayerId[x256056_g_PROTECTINFO.PlayerNum] = selfId
						  		--	AddQuest( sceneId, selfId, x256056_g_MissionId, x256056_g_ScriptId, 1, 0, 0)
					  			--	x256056_Msg2toplayer( sceneId, selfId,0)
							--else
								--BeginQuestEvent(sceneId)
								--strText = "#Y现在不能接这个任务"
								--AddQuestText(sceneId,strText)
								--EndQuestEvent(sceneId)
								--DispatchQuestTips(sceneId,selfId)
						end
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x256056_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256056_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x256056_g_MissionId)
	  x256056_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x256056_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x256056_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x256056_g_BonusChoiceItem do
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
function x256056_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256056_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256056_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256056_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256056_g_MissionId) > 0 then
				x256056_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x256056_g_MissionId)
				x256056_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256056_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x256056_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		
    		
	 	end        
									
    		--AddItemListToPlayer(sceneId,selfId)

   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256056_g_MissionIdNext )	
end


function x256056_OnScneneTimer(sceneId)
	--if x256056_g_doing == 1   then
		--local nTeamCount = GetNearTeamCount(sceneId, x256056_g_acceptid)
		--for i=0, nTeamCount-1 do
			--local PlayerId = GetNearTeamMember(sceneId, x256056_g_acceptid, i)
			--if PlayerId ~= x256056_g_acceptid  then
				--if x256056_ProcAcceptCheck(sceneId, PlayerId, NPCId) > 0 then
					--local nPlayerX, nPlayerZ = GetWorldPos(sceneId, PlayerId)
					--local distance1 = floor(sqrt((78-nPlayerX)*(78-nPlayerX)+(174-nPlayerZ)*(174-nPlayerZ)))
					--print(distance1)
					--if distance1 < 5   then
						--CallScriptFunction((256056), "ProcEventEntry", sceneId, PlayerId, x256056_g_zhubaoshangren,x256056_g_MissionId )
					--end
				--end
			--end
		--end
		--x256056_g_doing =2
	--end
	if x256056_g_doing==2   then
		if GetCurrentTime() - x256056_g_PROTECTINFO.StartTime >= 1   then
						x256056_g_doing = 3
		end
elseif x256056_g_doing == 3   then
			if GetCurrentTime() - x256056_g_PROTECTINFO.StartTime >= 2   then
					if IsObjValid (sceneId,x256056_g_zhubaoshangren) == 1 then
						NpcTalk(sceneId, x256056_g_zhubaoshangren, "哎呀，几位将军大驾光临，要买点珠宝玉器么？", -1)
					end
                       
        		x256056_g_doing =4
			end
	elseif x256056_g_doing == 4   then
			if GetCurrentTime() - x256056_g_PROTECTINFO.StartTime >= 5   then
					if IsObjValid (sceneId,x256056_g_huhelu) == 1 then
						NpcTalk(sceneId, x256056_g_huhelu, "少废话！听说哈喇图那老家伙在你这放了点东西？", -1)
          end        
						x256056_g_doing =5
			end
	elseif x256056_g_doing == 5   then
			if GetCurrentTime() - x256056_g_PROTECTINFO.StartTime >= 8   then
					if IsObjValid (sceneId,x256056_g_zhubaoshangren) == 1 then
						NpcTalk(sceneId, x256056_g_zhubaoshangren, "......哈喇图？小女子不认识这人。", -1)
          end    
						x256056_g_doing =6
			end
	elseif x256056_g_doing == 6   then
			if GetCurrentTime() - x256056_g_PROTECTINFO.StartTime >= 11   then
					if IsObjValid (sceneId,x256056_g_huhelu) == 1 then
						NpcTalk(sceneId, x256056_g_huhelu, "敢骗我？信不信老子当场把你给......", -1)
          end           
						x256056_g_doing =7
			end
	elseif x256056_g_doing == 7   then
			if GetCurrentTime() - x256056_g_PROTECTINFO.StartTime >= 14   then
					if IsObjValid (sceneId,x256056_g_huwei1) == 1 then
						NpcTalk(sceneId, x256056_g_huwei1, "头！头！我看见那个刚才给我们送饭的......", -1)
					end
					if IsObjValid (sceneId,x256056_g_huhelu) == 1 then
             SetMonsterDir(sceneId,x256056_g_huhelu,330)
          end
						x256056_g_doing =8
			end
	elseif x256056_g_doing == 8   then
			if GetCurrentTime() - x256056_g_PROTECTINFO.StartTime >= 16   then
					if IsObjValid (sceneId,x256056_g_huhelu) == 1 then
						NpcTalk(sceneId, x256056_g_huhelu, "饭什么饭！你这个蠢货就知道吃！找不到秘史，霍博大人怪罪下来，小心老子扒了你的皮！", -1)
          end
						x256056_g_doing =9
			end
	
	elseif x256056_g_doing == 9   then
			if GetCurrentTime() - x256056_g_PROTECTINFO.StartTime >= 18   then
					if IsObjValid (sceneId,x256056_g_huwei2) == 1 then
						NpcTalk(sceneId, x256056_g_huwei2, "头！不好了，巡逻的军官过来了！", -1)
          end
						x256056_g_doing =10
			end
	elseif x256056_g_doing == 10   then
			if GetCurrentTime() - x256056_g_PROTECTINFO.StartTime >= 19   then
					if IsObjValid (sceneId,x256056_g_huhelu) == 1 then
						NpcTalk(sceneId, x256056_g_huhelu, "什么?......走！", -1)
          end
						x256056_g_doing =11
			end
	elseif x256056_g_doing==11 then
			if GetCurrentTime() - x256056_g_PROTECTINFO.StartTime >= 23   then
				--for i=1, x256056_g_PROTECTINFO.PlayerNum  do
					--if x256056_g_PROTECTINFO.PlayerId[i]~=0   then
						--if IsHaveQuest(sceneId,x256056_g_PROTECTINFO.PlayerId[i],x256056_g_MissionId) > 0 then
							--local nPlayerX, nPlayerZ = GetWorldPos(sceneId, x256056_g_PROTECTINFO.PlayerId[i])
							--local distance1 = floor(sqrt((78-nPlayerX)*(78-nPlayerX)+(174-nPlayerZ)*(174-nPlayerZ)))
						--if distance1 < 20   then
								--local misIndex = GetQuestIndexByID(sceneId, x256056_g_PROTECTINFO.PlayerId[i], x256056_g_MissionId)
								--SetQuestByIndex(sceneId,x256056_g_PROTECTINFO.PlayerId[i],misIndex,0,1)
								--SetQuestByIndex(sceneId,x256056_g_PROTECTINFO.PlayerId[i],misIndex,7,1)
								--BeginQuestEvent(sceneId)
								--AddQuestText(sceneId,format("    看铁木真抓住刺客的过程   %d/1", GetQuestParam(sceneId,x256056_g_PROTECTINFO.PlayerId[i],misIndex,0) ))
								--EndQuestEvent(sceneId)
								--DispatchQuestTips(sceneId,x256056_g_PROTECTINFO.PlayerId[i])
						--end
					--end
				--end
			--end
			x256056_g_doing=12
			x256056_CloseTimer(sceneId, x256056_g_PROTECTINFO.ScneneTimerIndex)
			end
	end
end


--**********************************
--关闭计时器
--**********************************
function x256056_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	DeleteMonster (sceneId,x256056_g_huhelu )
	DeleteMonster (sceneId,x256056_g_huwei1 )
	DeleteMonster (sceneId,x256056_g_huwei2 )
	x256056_g_doing =0
	x256056_g_huhelu =-1
	x256056_g_huwei1 =-1
	x256056_g_huwei2 =-1
	x256056_g_acceptid =-1
	x256056_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
end


function x256056_GetBonus( sceneId, selfId,NpcID)
	  if x256056_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256056_g_ExpBonus);
  	end
		if x256056_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256056_g_BonusMoney1 )
	  end
		if x256056_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256056_g_BonusMoney2 )
	  end
		if x256056_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256056_g_BonusMoney3 )
		end
		if x256056_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256056_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256056_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256056_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256056_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256056_g_BonusMoney6)
		end
end

function x256056_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x256056_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x256056_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x256056_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x256056_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x256056_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x256056_g_MissionName.."！", 0, 3)
				if x256056_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x256056_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x256056_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x256056_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x256056_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x256056_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x256056_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x256056_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x256056_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x256056_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x256056_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x256056_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x256056_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x256056_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x256056_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x256056_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256056_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x256056_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256056_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x256056_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x256056_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x256056_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x256056_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x256056_g_MissionId, state, -1 )
		end
end

function x256056_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256056_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256056_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256056_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256056_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256056_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end