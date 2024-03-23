--【主线】真相

--MisDescBegin
x270006_g_ScriptId = 270006
x270006_g_MissionIdPre =3572
x270006_g_MissionId = 3573
x270006_g_LevelLess	= 	50 
x270006_g_MissionIdNext = 3574
x270006_g_Name	={}
x270006_g_ExtTarget={{type=20,n=1,target="弄清事情真相"}}
x270006_g_MissionName="【主线】真相"
x270006_g_MissionInfo="\t我郭破虏行得正，站得直，从不做那些伤天害理之事，你若硬说是我所为，我也没有什么好解释的。\n\t多言无益，你请回吧，武林大会之时，我自会对此事有所交代。"  --任务描述
x270006_g_MissionTarget=""		
x270006_g_MissionCompleted="\t苍天有眼！幸而智障大师及时出现，我丐帮才保住了我丐帮百年侠义之名。否则我就是丐帮的千古罪人。"					--完成任务npc说话的话
x270006_g_ContinueInfo="\t事情还没有弄清楚，大侠稍安勿躁！"
x270006_g_MissionHelp =	""
x270006_g_DemandItem ={}
x270006_g_BonusMoney1 =376
x270006_g_BonusMoney2 =0
x270006_g_BonusMoney3 =0
x270006_g_BonusMoney4 =0
x270006_g_BonusMoney5 =61
x270006_g_BonusMoney6 =0
x270006_g_BonusItem	=	{}
x270006_g_BonusChoiceItem ={}
x270006_g_ExpBonus = 145000
x270006_g_doing = 0
x270006_g_acceptid =-1
x270006_g_jiazhizhang = -1
x270006_g_guoponu = -1
x270006_g_heshang1 = -1
x270006_g_heshang2 =-1
x270006_g_heshang3 = -1
x270006_g_heshang4 = -1
x270006_g_zhangsanfeng = -1
x270006_g_fenglingshitai = -1
x270006_g_hezudao = -1
x270006_g_chenyouliang = -1
x270006_g_zhenzhizhang = -1
x270006_g_dingshangyi = -1
x270006_g_wangshisan = -1
x270006_g_lengxiaoqi = -1
x270006_g_lixuanyi = -1
x270006_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
--MisDescEnd
--**********************************

function x270006_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x270006_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x270006_g_MissionIdPre)> 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x270006_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x270006_g_MissionId, state, -1 )
	end
end

function x270006_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x270006_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x270006_g_ExpBonus )
		end
		if x270006_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x270006_g_BonusMoney1 )
		end
		if x270006_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x270006_g_BonusMoney2 )
		end
		if x270006_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x270006_g_BonusMoney3 )
		end
		if x270006_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x270006_g_BonusMoney4 )
		end
		if x270006_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x270006_g_BonusMoney5 )
		end
		if x270006_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x270006_g_BonusMoney6 )
		end
		for i, item in x270006_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x270006_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x270006_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x270006_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x270006_g_MissionId) > 0 then
			if x270006_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270006_g_MissionName)
						AddQuestText(sceneId,x270006_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x270006_g_ScriptId, x270006_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270006_g_MissionName)
						AddQuestText(sceneId,x270006_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x270006_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x270006_g_ScriptId, x270006_g_MissionId);
			end
  elseif x270006_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x270006_g_MissionName)
			AddQuestText(sceneId,x270006_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")
			for i, item in x270006_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x270006_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x270006_g_MissionHelp )
			end
			x270006_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x270006_g_ScriptId, x270006_g_MissionId);
  end
	
end
--**********************************

function x270006_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x270006_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x270006_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId, selfId, x270006_g_MissionId)
		if GetQuestParam(sceneId,selfId,misIndex,0) ==1 then 
	        return 1
	  end
	  return 0
	
end
--**********************************
function x270006_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x270006_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x270006_g_MissionId  )
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
		if x270006_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
				if x270006_g_doing == 0 then
					local retmiss = AddQuest( sceneId, selfId, x270006_g_MissionId, x270006_g_ScriptId, 0, 0, 0)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x270006_Msg2toplayer( sceneId, selfId,0)
		  			x270006_g_PROTECTINFO.StartTime = GetCurrentTime()
						x270006_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 270006, "OnScneneTimer", 1)
						if x270006_g_PROTECTINFO.ScneneTimerIndex >= 0 then
								x270006_g_doing = 1
								x270006_g_acceptid = selfId
								x270006_g_jiazhizhang=CreateMonster(sceneId, 3800,205.7862,206.0416,3,1,-1,-1,20,78000,180,"智障禅师")
								x270006_g_heshang1=CreateMonster(sceneId, 3822,204.2096,205.2391,3,1,-1,-1,20,93000,180,"空寂")
								x270006_g_heshang2=CreateMonster(sceneId, 3822,204.1044,203.7996,3,1,-1,-1,20,93000,180,"空色")
								x270006_g_heshang3=CreateMonster(sceneId, 3822,204.2675,206.7597,3,1,-1,-1,20,93000,180,"空思")
								x270006_g_heshang4=CreateMonster(sceneId, 3822,204.3732,208.2915,3,1,-1,-1,20,93000,180,"空空")
								x270006_g_zhangsanfeng=CreateMonster(sceneId, 3802,214.1412,217.6203,3,1,-1,-1,20,93000,180,"张三丰")
								x270006_g_fenglingshitai=CreateMonster(sceneId, 3806,213.0141,217.4029,3,1,-1,-1,20,93000,180,"风陵师太")
								x270006_g_hezudao=CreateMonster(sceneId, 3804,215.0514,218.4295,3,1,-1,-1,20,93000,180,"何足道")
								if IsObjValid (sceneId,x270006_g_jiazhizhang) == 1 then
										SetPatrolId(sceneId, x270006_g_jiazhizhang, 1)
								end
								if IsObjValid (sceneId,x270006_g_heshang1) == 1 then
										SetPatrolId(sceneId, x270006_g_heshang1, 3)
								end
								if IsObjValid (sceneId,x270006_g_heshang2) == 1 then
										SetPatrolId(sceneId, x270006_g_heshang2, 2)
								end
								if IsObjValid (sceneId,x270006_g_heshang3) == 1 then
										SetPatrolId(sceneId, x270006_g_heshang3, 4)
								end
								if IsObjValid (sceneId,x270006_g_heshang4) == 1 then
										SetPatrolId(sceneId, x270006_g_heshang4, 5)
								end
								if IsObjValid (sceneId,x270006_g_zhangsanfeng) == 1 then
										SetPatrolId(sceneId, x270006_g_zhangsanfeng, 6)
								end
								if IsObjValid (sceneId,x270006_g_fenglingshitai) == 1 then
										SetPatrolId(sceneId, x270006_g_fenglingshitai, 7)
								end
								if IsObjValid (sceneId,x270006_g_hezudao) == 1 then
										SetPatrolId(sceneId, x270006_g_hezudao, 8)
								end
								x270006_g_guoponu =FindMonsterByGUID( sceneId,136264)
								x270006_g_dingshangyi =FindMonsterByGUID( sceneId,136266)
								x270006_g_wangshisan =FindMonsterByGUID( sceneId,136267)
								x270006_g_lengxiaoqi =FindMonsterByGUID( sceneId,136268)
								x270006_g_lixuanyi =FindMonsterByGUID( sceneId,136265)
						end
					end
				else
					Msg2Player(sceneId, selfId, "任务暂时无法接受！", 0, 3)
				end

	 	end                                                                    
	     
end
--**********************************

function x270006_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x270006_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x270006_g_MissionId)
	  x270006_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x270006_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x270006_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x270006_g_BonusChoiceItem do
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
function x270006_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x270006_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270006_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270006_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x270006_g_MissionId) > 0 then
				x270006_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x270006_g_MissionId)
				x270006_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x270006_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x270006_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x270006_g_MissionIdNext )	
end

function x270006_GetBonus( sceneId, selfId,NpcID)
	  if x270006_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x270006_g_ExpBonus);
  	end
		if x270006_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x270006_g_BonusMoney1 )
	  end
		if x270006_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x270006_g_BonusMoney2 )
	  end
		if x270006_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x270006_g_BonusMoney3 )
		end
		if x270006_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x270006_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x270006_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x270006_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x270006_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x270006_g_BonusMoney6)
		end
end

function x270006_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x270006_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x270006_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x270006_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x270006_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x270006_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x270006_g_MissionName.."！", 0, 3)
				if x270006_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R经验"..x270006_g_ExpBonus.."#Y的奖励", 0, 2)
  			end
				if x270006_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R银卡"..x270006_g_BonusMoney1.."文#Y的奖励", 0, 2)
	  		end
				if x270006_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R现银"..x270006_g_BonusMoney2.."文#Y的奖励", 0, 2)
	  		end
				if x270006_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y获得#R金卡"..x270006_g_BonusMoney3.."文#Y的奖励", 0, 2)
				end
				if x270006_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R朝廷声望值"..x270006_g_BonusMoney4.."#Y的奖励", 0, 2)
				end
				if x270006_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R声望"..x270006_g_BonusMoney5.."#Y的奖励", 0, 2)
				end
				if x270006_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y获得#R荣誉"..x270006_g_BonusMoney6.."#Y的奖励", 0, 2)
				end
		end
end

function x270006_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x270006_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x270006_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x270006_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x270006_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x270006_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  
end

function x270006_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x270006_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x270006_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x270006_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x270006_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x270006_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x270006_OnScneneTimer(sceneId)
	if x270006_g_doing==1   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 9   then
						x270006_g_doing = 2
						if IsObjValid (sceneId,x270006_g_jiazhizhang) == 1 then
								NpcTalk(sceneId, x270006_g_jiazhizhang, "郭帮主，贫僧有礼了", -1)
						end
		end
	elseif x270006_g_doing==2   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 12   then
						x270006_g_doing = 3
						if IsObjValid (sceneId,x270006_g_guoponu) == 1 then
								NpcTalk(sceneId, x270006_g_guoponu, "就算禅师不来，郭某也要去拜访。", -1)
						end
		end
	elseif x270006_g_doing==3   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 15   then
						x270006_g_doing = 4
						if IsObjValid (sceneId,x270006_g_guoponu) == 1 then
								NpcTalk(sceneId, x270006_g_guoponu, "近来发生的种种事情确不是丐帮所为。", -1)
						end
		end
	elseif x270006_g_doing==4   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 18   then
						x270006_g_doing = 5
						if IsObjValid (sceneId,x270006_g_jiazhizhang) == 1 then
								NpcTalk(sceneId, x270006_g_jiazhizhang, "但是总总证据都指向丐帮，希望郭帮主给一个合理的说法。", -1)
						end
		end
	elseif x270006_g_doing==5   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 22   then
						x270006_g_doing = 6
						if IsObjValid (sceneId,x270006_g_fenglingshitai) == 1 then
								NpcTalk(sceneId, x270006_g_fenglingshitai, "什么说法，铁证如山，还我徒儿命来！", -1)
						end
		end
	elseif x270006_g_doing==6   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 25   then
						x270006_g_doing = 7
						if IsObjValid (sceneId,x270006_g_dingshangyi) == 1 then
								NpcTalk(sceneId, x270006_g_dingshangyi, "什么你徒儿的命，说事来的还是来找事来的？", -1)
						end
		end
	elseif x270006_g_doing==7   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 28   then
						x270006_g_doing = 8
						if IsObjValid (sceneId,x270006_g_zhangsanfeng) == 1 then
								NpcTalk(sceneId, x270006_g_zhangsanfeng, "师太冷静，贫道也相信事有蹊跷，让郭帮主把事情说明白吧。", -1)
						end
            x270006_g_chenyouliang=CreateMonster(sceneId, 28,219.5403,195.8635,3,1,-1,-1,20,50000,180,"陈友谅")
            if IsObjValid (sceneId,x270006_g_chenyouliang) == 1 then
            		SetPatrolId(sceneId, x270006_g_chenyouliang, 9)
            end
		end
	elseif x270006_g_doing==8   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 31   then
						x270006_g_doing = 9
						if IsObjValid (sceneId,x270006_g_chenyouliang) == 1 then
								NpcTalk(sceneId, x270006_g_chenyouliang, "禀教主，我丐帮几个分舵遭到武当，峨眉，昆仑等派的袭击！", -1)
						end
		end
	elseif x270006_g_doing==9   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 33   then
						x270006_g_doing = 10
						if IsObjValid (sceneId,x270006_g_guoponu) == 1 then
								NpcTalk(sceneId, x270006_g_guoponu, "！！", -1)
						end
						if IsObjValid (sceneId,x270006_g_zhangsanfeng) == 1 then
								NpcTalk(sceneId, x270006_g_zhangsanfeng, "！！", -1)
						end
						if IsObjValid (sceneId,x270006_g_fenglingshitai) == 1 then
								NpcTalk(sceneId, x270006_g_fenglingshitai, "！！", -1)
						end
						if IsObjValid (sceneId,x270006_g_hezudao) == 1 then
								NpcTalk(sceneId, x270006_g_hezudao, "！！", -1)
						end
						if IsObjValid (sceneId,x270006_g_dingshangyi) == 1 then
								NpcTalk(sceneId, x270006_g_dingshangyi, "！！", -1)
						end
						if IsObjValid (sceneId,x270006_g_wangshisan) == 1 then
								NpcTalk(sceneId, x270006_g_wangshisan, "！！", -1)
						end
						if IsObjValid (sceneId,x270006_g_lengxiaoqi) == 1 then
								NpcTalk(sceneId, x270006_g_lengxiaoqi, "！！", -1)
						end
						if IsObjValid (sceneId,x270006_g_lixuanyi) == 1 then
								NpcTalk(sceneId, x270006_g_lixuanyi, "！！", -1)
						end
		end
	elseif x270006_g_doing==10   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 35   then
						x270006_g_doing = 11
						if IsObjValid (sceneId,x270006_g_lixuanyi) == 1 then
								NpcTalk(sceneId, x270006_g_lixuanyi, "原来你们就是意图消灭我丐帮，好，那就来吧！", -1)
						end
		end
	elseif x270006_g_doing==11   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 36   then
						x270006_g_doing = 12
						if IsObjValid (sceneId,x270006_g_guoponu) == 1 then
								NpcTalk(sceneId, x270006_g_guoponu, "陈友谅，此事可当真？", -1)
						end
		end
	elseif x270006_g_doing==12   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 37   then
						x270006_g_doing = 13
						if IsObjValid (sceneId,x270006_g_fenglingshitai) == 1 then
								NpcTalk(sceneId, x270006_g_fenglingshitai, "你们别转移视线，快把事情说清楚。", -1)
						end
		end
	elseif x270006_g_doing==13   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 40   then
						x270006_g_doing = 14
						if IsObjValid (sceneId,x270006_g_lixuanyi) == 1 then
								NpcTalk(sceneId, x270006_g_lixuanyi, "说什么说？都欺负到家门口了！", -1)
						end
		end
	elseif x270006_g_doing==14   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 43   then
						x270006_g_doing = 15
						if IsObjValid (sceneId,x270006_g_jiazhizhang) == 1 then
								NpcTalk(sceneId, x270006_g_jiazhizhang, "既然丐帮如此不配合，我们只能认为这些事情是丐帮所为了！", -1)
						end
            x270006_g_zhenzhizhang=CreateMonster(sceneId, 31,216,202,3,1,-1,-1,20,44000,90,"智障禅师")
		end
	elseif x270006_g_doing==15   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 47   then
						x270006_g_doing = 16
						if IsObjValid (sceneId,x270006_g_zhenzhizhang) == 1 then
								NpcTalk(sceneId, x270006_g_zhenzhizhang, "善哉善哉！施主放下屠刀立地成佛！", -1)
						end
						if IsObjValid (sceneId,x270006_g_jiazhizhang) == 1 then
            		SetMonsterDir(sceneId,x270006_g_jiazhizhang,270)
            end
		end
	elseif x270006_g_doing==16   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 50   then
						x270006_g_doing = 17
						if IsObjValid (sceneId,x270006_g_jiazhizhang) == 1 then
								NpcTalk(sceneId, x270006_g_jiazhizhang, "你居然出来了！你想清楚了！？", -1)
						end
		end
	elseif x270006_g_doing==17   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 53   then
						x270006_g_doing = 18
						if IsObjValid (sceneId,x270006_g_zhenzhizhang) == 1 then
								NpcTalk(sceneId, x270006_g_zhenzhizhang, "贫僧不能因为一己之私而让丐帮蒙此大辱！徒儿们，对不起！", -1)
						end
		end
	elseif x270006_g_doing==18   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 56   then
						x270006_g_doing = 19
						if IsObjValid (sceneId,x270006_g_heshang1) == 1 then
								NpcTalk(sceneId, x270006_g_heshang1, "阿弥陀佛！", -1)
						end
						if IsObjValid (sceneId,x270006_g_heshang2) == 1 then
								NpcTalk(sceneId, x270006_g_heshang2, "阿弥陀佛！", -1)
						end
						if IsObjValid (sceneId,x270006_g_heshang3) == 1 then
								NpcTalk(sceneId, x270006_g_heshang3, "阿弥陀佛！", -1)
						end
						if IsObjValid (sceneId,x270006_g_heshang4) == 1 then
								NpcTalk(sceneId, x270006_g_heshang4, "阿弥陀佛！", -1)
						end
		end
	elseif x270006_g_doing==19   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 60   then
						x270006_g_doing = 20
						if IsObjValid (sceneId,x270006_g_zhenzhizhang) == 1 then
								NpcTalk(sceneId, x270006_g_zhenzhizhang, "站在你们面前的不是智障禅师，而是天魔教的教主！", -1)
						end
						if IsObjValid (sceneId,x270006_g_heshang1) == 1 then
            		SendSpecificImpactToUnit(sceneId, x270006_g_heshang1, x270006_g_heshang1, x270006_g_heshang1, 3060, 0);
            end
		end
	elseif x270006_g_doing==20   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 64   then
						x270006_g_doing = 21
						if IsObjValid (sceneId,x270006_g_zhenzhizhang) == 1 then
								NpcTalk(sceneId, x270006_g_zhenzhizhang, "一个月前他给我寺僧人都下了毒，控制了整个寺院，以我的名义召开了武林大会。", -1)
						end
						if IsObjValid (sceneId,x270006_g_heshang2) == 1 then
            		SendSpecificImpactToUnit(sceneId, x270006_g_heshang2, x270006_g_heshang2, x270006_g_heshang2, 3060, 0);
            end
		end
	elseif x270006_g_doing==21   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 68   then
						x270006_g_doing = 22
						if IsObjValid (sceneId,x270006_g_zhenzhizhang) == 1 then
								NpcTalk(sceneId, x270006_g_zhenzhizhang, "他的目的就是成为武林盟主，所以他嫁祸丐帮挑起武林纷争！", -1)
						end
						if IsObjValid (sceneId,x270006_g_heshang3) == 1 then
            		SendSpecificImpactToUnit(sceneId, x270006_g_heshang3, x270006_g_heshang3, x270006_g_heshang3, 3060, 0);
            end
		end
	elseif x270006_g_doing==22   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 72   then
						x270006_g_doing = 23
						if IsObjValid (sceneId,x270006_g_zhenzhizhang) == 1 then
								NpcTalk(sceneId, x270006_g_zhenzhizhang, "贫僧因世俗杂念，记挂着弟子所以一直不能出来揭破他的谎言。", -1)
						end
						if IsObjValid (sceneId,x270006_g_heshang4) == 1 then
            		SendSpecificImpactToUnit(sceneId, x270006_g_heshang4, x270006_g_heshang4, x270006_g_heshang4, 3060, 0);
            end
		end
	elseif x270006_g_doing==23   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 75   then
						x270006_g_doing = 24
						if IsObjValid (sceneId,x270006_g_jiazhizhang) == 1 then
								NpcTalk(sceneId, x270006_g_jiazhizhang, "看见弟子死在面前感觉如何？智障！我要让你付出代价！", -1)
						end
		end
	elseif x270006_g_doing==24   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 78   then
						x270006_g_doing = 25
						if IsObjValid (sceneId,x270006_g_zhenzhizhang) == 1 then
								NpcTalk(sceneId, x270006_g_zhenzhizhang, "郭帮主，贫僧向你赔罪了！", -1)
						end
		end
	elseif x270006_g_doing==25   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 81   then
						x270006_g_doing = 26
						if IsObjValid (sceneId,x270006_g_guoponu) == 1 then
								NpcTalk(sceneId, x270006_g_guoponu, "禅师的气度令郭某佩服万分，您去料理徒弟的事情吧，此间事交给郭某处理！", -1)
						end
		end
	elseif x270006_g_doing==26   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 84   then
						x270006_g_doing = 27
						if IsObjValid (sceneId,x270006_g_zhenzhizhang) == 1 then
								NpcTalk(sceneId, x270006_g_zhenzhizhang, "多谢郭帮主，贫僧先告辞了！", -1)
						end
		end
	elseif x270006_g_doing==27   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 87   then
						x270006_g_doing = 28
						if IsObjValid (sceneId,x270006_g_zhangsanfeng) == 1 then
								NpcTalk(sceneId, x270006_g_zhangsanfeng, "这次误会由我等引起，请见谅！他日如有差遣我等必赴汤蹈火，告辞！", -1)
						end
		end
	elseif x270006_g_doing==28   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 90   then
						x270006_g_doing = 29
						if IsObjValid (sceneId,x270006_g_fenglingshitai) == 1 then
								NpcTalk(sceneId, x270006_g_fenglingshitai, "告辞！", -1)
						end
						if IsObjValid (sceneId,x270006_g_hezudao) == 1 then
								NpcTalk(sceneId, x270006_g_hezudao, "告辞！", -1)
						end
		end
	elseif x270006_g_doing==29 then
			if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 92   then
				if IsPlayerStateNormal(sceneId,x270006_g_acceptid) ==1 then
					if IsHaveQuest(sceneId,x270006_g_acceptid, x270006_g_MissionId) > 0 then
						local nPlayerX, nPlayerZ = GetWorldPos(sceneId, x270006_g_acceptid)
						local distance1 = floor(sqrt((216-nPlayerX)*(216-nPlayerX)+(206-nPlayerZ)*(206-nPlayerZ)))
						if distance1 <= 20 then
									local misIndex = GetQuestIndexByID(sceneId, x270006_g_acceptid, x270006_g_MissionId)
									SetQuestByIndex(sceneId,x270006_g_acceptid,misIndex,0,1)
									SetQuestByIndex(sceneId,x270006_g_acceptid,misIndex,7,1)
									BeginQuestEvent(sceneId)
									AddQuestText(sceneId,format("弄清事情真相   %d/1", GetQuestParam(sceneId,x270006_g_acceptid,misIndex,0) ))
									EndQuestEvent(sceneId)
									DispatchQuestTips(sceneId,x270006_g_acceptid)
						end
					end
				end
				x270006_g_doing=30
				x270006_CloseTimer(sceneId, x270006_g_PROTECTINFO.ScneneTimerIndex)
			end
	end
end


--**********************************
--关闭计时器
--**********************************
function x270006_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x270006_g_doing =0
	x270006_g_acceptid =-1
	x270006_g_jiazhizhang = -1
	x270006_g_guoponu = -1
	x270006_g_heshang1 = -1
	x270006_g_heshang2 =-1
	x270006_g_heshang3 = -1
	x270006_g_heshang4 = -1
	x270006_g_zhangsanfeng = -1
	x270006_g_fenglingshitai = -1
	x270006_g_hezudao = -1
	x270006_g_chenyouliang = -1
	x270006_g_zhenzhizhang = -1
	x270006_g_dingshangyi = -1
	x270006_g_wangshisan = -1
	x270006_g_lengxiaoqi = -1
	x270006_g_lixuanyi = -1
	x270006_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
	
end