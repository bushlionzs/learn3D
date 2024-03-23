--武士修习技能

--MisDescBegin
x203527_g_ScriptId = 203527
x203527_g_MissionIdPre =3210
x203527_g_MissionId = 3211
x203527_g_LevelLess	= 	1 
x203527_g_MissionIdNext = 3243
x203527_g_DemandKill ={{id=11971,num=5}}
--x203527_g_Name	={"穆林","斡鲁斯" }
x203527_g_ExtTarget={{type=20,n=1,target="在@npc_125026处学习技能"}}
x203527_g_MissionName="【新手】新兵的技能"
--x203527_g_MissionTalk={"武士的特点","技能的特色","如何能成为宗师"}
x203527_g_MissionInfo="\t虽然你是三位长老推荐而来，但是你的技能似乎有所欠缺。\n\t每一位来应征的新兵，都可以从教官铁力那里学到两个新的技能，快去找他吧。"  --任务描述
x203527_g_MissionTarget=""		
x203527_g_MissionCompleted="\t这两个最初级的技能就传授给你了，但是要牢记：只有勤加修炼才能学会更高级的技能。"
x203527_g_ContinueInfo={""}
x203527_g_MissionHelp =	""
x203527_g_DemandItem ={}
x203527_g_ExpBonus = 1600
x203527_g_BonusMoney1 =5
x203527_g_BonusMoney2 =0
x203527_g_BonusMoney3 =0
x203527_g_BonusMoney4 =0
x203527_g_BonusMoney5 =12
x203527_g_BonusMoney6 =0
x203527_g_BonusChoiceItem ={}

x203527_g_NpcGUID = {{ guid = 125026, name = "雄鹰长老"} }

--MisDescEnd
x203527_g_Skill	= {{id=123, level=1, pos=4},{id=132, level=1, pos=3},
				   {id=204, level=1, pos=4},{id=208, level=1, pos=3},
				   {id=306, level=1, pos=4},{id=309, level=1, pos=3},
				   {id=406, level=1, pos=4},{id=409, level=1, pos=3},
				   {id=502, level=1, pos=4},{id=508, level=1, pos=3},
				   {id=601, level=1, pos=4},{id=610, level=1, pos=3},
				   {id=1104, level=1, pos=4},{id=1102, level=1, pos=3},
				   {id=1207, level=1, pos=4},{id=1206, level=1, pos=3},
				   {id=1307, level=1, pos=4},{id=1306, level=1, pos=3},
				   {id=1406, level=1, pos=3},{id=1407, level=1, pos=4},
				   {id=1506, level=1, pos=3},{id=1507, level=1, pos=4},
				   {id=1600, level=1, pos=4},{id=1605, level=1, pos=3}
				   }
x203527_g_BonusItem	=	{{id=13030003,num=1},{id=13030004,num=1},
						 {id=13030005,num=1},{id=13030006,num=1},
						 {id=13030007,num=1},{id=13030008,num=1},
						 {id=13030009,num=1},{id=13030010,num=1},
						 {id=13030011,num=1},{id=13030012,num=1},
						 {id=13030013,num=1},{id=13030014,num=1},
						 {id=13030129,num=1},{id=13030130,num=1},
						 {id=13030131,num=1},{id=13030132,num=1},
						 {id=13030133,num=1},{id=13030134,num=1},
						 {id=13030135,num=1},{id=13030136,num=1},
						 {id=13030137,num=1},{id=13030138,num=1},
						 {id=13030140,num=1},{id=13030139,num=1}
						 }
--**********************************

function x203527_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

   CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,0 ) 
	if IsQuestHaveDone(sceneId, selfId, x203527_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203527_g_MissionIdPre) > 0 then
	
				if IsHaveQuest(sceneId,selfId, x203527_g_MissionId) <= 0 then
						local state = GetQuestStateNM(sceneId,selfId,NPCId,x203527_g_MissionId)
						AddQuestTextNM( sceneId, selfId, NPCId, x203527_g_MissionId, state, -1 )
				end

	end
end

function x203527_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203527_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203527_g_ExpBonus )
		end
		if x203527_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203527_g_BonusMoney1 )
		end
		if x203527_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203527_g_BonusMoney2 )
		end
		if x203527_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203527_g_BonusMoney3 )
		end
		if x203527_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203527_g_BonusMoney4 )
		end
		if x203527_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203527_g_BonusMoney5 )
		end
		if x203527_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203527_g_BonusMoney6 )
		end
		local zhiye = GetZhiye( sceneId, selfId)+1
			--	if zhiye == 1 then 
					AddQuestItemBonus(sceneId, x203527_g_BonusItem[zhiye+zhiye-1].id,  x203527_g_BonusItem[zhiye+zhiye-1].num)
					AddQuestItemBonus(sceneId, x203527_g_BonusItem[zhiye+zhiye].id,  x203527_g_BonusItem[zhiye+zhiye].num)
			--  	elseif zhiye ==2 then 
			--  		AddQuestItemBonus(sceneId, x203527_g_BonusItem[zhiye+1].id,  x203527_g_BonusItem[zhiye].num)
			--  		AddQuestItemBonus(sceneId, x203527_g_BonusItem[zhiye+2].id,  x203527_g_BonusItem[zhiye+1].num)
			--	elseif zhiye ==3 then
			--		AddQuestItemBonus(sceneId, x203527_g_BonusItem[zhiye+2].id,  x203527_g_BonusItem[zhiye].num)
			--		AddQuestItemBonus(sceneId, x203527_g_BonusItem[zhiye+3].id,  x203527_g_BonusItem[zhiye+1].num)
			--	elseif zhiye ==4 then
			--		AddQuestItemBonus(sceneId, x203527_g_BonusItem[zhiye+3].id,  x203527_g_BonusItem[zhiye].num)
			--		AddQuestItemBonus(sceneId, x203527_g_BonusItem[zhiye+4].id,  x203527_g_BonusItem[zhiye+1].num)
			--	elseif zhiye ==5 then
			--		AddQuestItemBonus(sceneId, x203527_g_BonusItem[zhiye+4].id,  x203527_g_BonusItem[zhiye].num)
			--		AddQuestItemBonus(sceneId, x203527_g_BonusItem[zhiye+5].id,  x203527_g_BonusItem[zhiye+1].num)
			--	elseif zhiye ==6 then
			--		AddQuestItemBonus(sceneId, x203527_g_BonusItem[zhiye+5].id,  x203527_g_BonusItem[zhiye].num)
			--		AddQuestItemBonus(sceneId, x203527_g_BonusItem[zhiye+6].id,  x203527_g_BonusItem[zhiye+1].num)
			--	elseif zhiye ==7 then
			--		AddQuestItemBonus(sceneId, x203527_g_BonusItem[zhiye+6].id,  x203527_g_BonusItem[zhiye].num)
			--		AddQuestItemBonus(sceneId, x203527_g_BonusItem[zhiye+7].id,  x203527_g_BonusItem[zhiye+1].num)
			--	elseif zhiye ==8 then
			--		AddQuestItemBonus(sceneId, x203527_g_BonusItem[zhiye+7].id,  x203527_g_BonusItem[zhiye].num)
			--		AddQuestItemBonus(sceneId, x203527_g_BonusItem[zhiye+8].id,  x203527_g_BonusItem[zhiye+1].num)
			--	elseif zhiye ==9 then
			--		AddQuestItemBonus(sceneId, x203527_g_BonusItem[zhiye+8].id,  x203527_g_BonusItem[zhiye].num)
			--		AddQuestItemBonus(sceneId, x203527_g_BonusItem[zhiye+9].id,  x203527_g_BonusItem[zhiye+1].num)
			--	elseif zhiye ==10 then
			--		AddQuestItemBonus(sceneId, x203527_g_BonusItem[zhiye+9].id,  x203527_g_BonusItem[zhiye].num)
			--		AddQuestItemBonus(sceneId, x203527_g_BonusItem[zhiye+10].id,  x203527_g_BonusItem[zhiye+1].num)
			--	elseif zhiye ==11 then
			--		AddQuestItemBonus(sceneId, x203527_g_BonusItem[zhiye+10].id,  x203527_g_BonusItem[zhiye].num)
			--		AddQuestItemBonus(sceneId, x203527_g_BonusItem[zhiye+11].id,  x203527_g_BonusItem[zhiye+1].num)
			--	elseif zhiye ==12 then
			--		AddQuestItemBonus(sceneId, x203527_g_BonusItem[zhiye+11].id,  x203527_g_BonusItem[zhiye].num)
			--		AddQuestItemBonus(sceneId, x203527_g_BonusItem[zhiye+12].id,  x203527_g_BonusItem[zhiye+1].num)
			--	end



		for i, item in pairs(x203527_g_BonusChoiceItem) do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

--任务入口函数

--**********************************

function x203527_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
   CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,0 )
	if IsQuestHaveDone(sceneId, selfId, x203527_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203527_g_MissionId) > 0 then
			if x203527_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
					if which == -1 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203527_g_MissionName) 
						AddQuestText(sceneId,x203527_g_ContinueInfo[1])
						--AddQuestNumText(sceneId, MissionId, x203527_g_MissionTalk[1],0,0)
						EndQuestEvent()	
						--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 16,1 )		
						DispatchQuestEventList(sceneId, selfId, NPCId, x203527_g_ScriptId, x203527_g_MissionId); 
						
					elseif which ==0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203527_g_MissionName)
						AddQuestText(sceneId,x203527_g_ContinueInfo[2])
						--AddQuestNumText(sceneId, MissionId, x203527_g_MissionTalk[2],1,1)
						EndQuestEvent()
						--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 16,0)
						DispatchQuestEventList(sceneId, selfId, NPCId, x203527_g_ScriptId, x203527_g_MissionId);
					elseif which ==1 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203527_g_MissionName)
						AddQuestText(sceneId,x203527_g_ContinueInfo[3])
						--AddQuestNumText(sceneId, MissionId, x203527_g_MissionTalk[3],0,2)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203527_g_ScriptId, x203527_g_MissionId);
						local misIndex = GetQuestIndexByID(sceneId,selfId,x203527_g_MissionId)  
						SetQuestByIndex(sceneId,selfId,misIndex,1,1)                                                
	    			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
					end
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203527_g_MissionName)
						AddQuestText(sceneId,x203527_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203527_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203527_g_ScriptId, x203527_g_MissionId);
			end
  elseif x203527_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
    CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 5,0 )
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203527_g_MissionName)
			AddQuestText(sceneId,x203527_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：") 
			for i, item in pairs(x203527_g_ExtTarget) do
					AddQuestText( sceneId,item.target)
			end 
			if x203527_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x203527_g_MissionHelp )
			end
			x203527_DispatchMissionInfo( sceneId, selfId, NPCId )
			EndQuestEvent()
		
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203527_g_ScriptId, x203527_g_MissionId);
  end
end
--*************************************************

--************************************************* 
function x203527_ProcAcceptCheck(sceneId, selfId, NPCId)
	if IsQuestHaveDone(sceneId, selfId, x203527_g_MissionId) > 0 then
		return 0
	elseif IsQuestHaveDone(sceneId, selfId, x203527_g_MissionIdPre) <= 0 then
		return 0
	end
	return 1
end
--**********************************杀怪
function x203527_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x203527_g_MissionId)
	--if GetQuestParam(sceneId,selfId,misIndex,0) == x203527_g_DemandKill[1].num then
             
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    		--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 21,0 )
	        return 1
	--end
	--return 0
end
--**********************************杀怪
function x203527_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203527_g_MissionId) > 0 then
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
	--	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203527_g_MissionId  )
	--	if FrontMissiontId1 ~= -1 then
	--		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
	--			return 0
	--		end
	--	end
	--	if FrontMissiontId2 ~= -1 then
	--		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
	--			return 0
	--		end
	--	end
	--	if FrontMissiontId3 ~= -1 then
	--		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
	--			return 0
	--		end
	--	end
		if x203527_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203527_g_MissionId, x203527_g_ScriptId, 1, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x203527_Msg2toplayer( sceneId, selfId,0)
						--if x203527_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x203527_g_MissionId) 
								SetQuestByIndex(sceneId,selfId,misIndex,7,1)
								CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,1 )                                                 
								  --CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 21,1 )
                                           
	    					--SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			--end
		  		end
	 	end                                                                    
	     
end

--**********************************
function x203527_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203527_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203527_g_MissionId)
	  x203527_Msg2toplayer( sceneId, selfId,1)
	  
end
--**********************************
function x203527_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	--for j, item in x203527_g_BonusItem do
		--AddItem( sceneId, item.id, item.num )
 -- end
  for j, item in pairs(x203527_g_BonusChoiceItem) do
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
function x203527_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203527_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203527_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203527_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203527_g_MissionId) > 0 then
				x203527_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203527_g_MissionId)
				--QuestCom(sceneId, selfId, 3264)
				x203527_GetBonus( sceneId, selfId,NPCId)
				local zhiye = GetZhiye( sceneId, selfId)+1
				--if zhiye == 1 then 
					if HaveSkill(sceneId, selfId,x203527_g_Skill[zhiye+zhiye-1].id)<=0 then
						AddSkillToPlayer(sceneId, selfId, x203527_g_Skill[zhiye+zhiye-1].id, x203527_g_Skill[zhiye+zhiye-1].level, x203527_g_Skill[zhiye+zhiye-1].pos)
					end
					if HaveSkill(sceneId, selfId,x203527_g_Skill[zhiye+zhiye].id)<=0 then
						AddSkillToPlayer(sceneId, selfId, x203527_g_Skill[zhiye+zhiye].id, x203527_g_Skill[zhiye+zhiye].level, x203527_g_Skill[zhiye+zhiye].pos)
					end       
			  	--elseif zhiye ==2 then 
			  	--	if HaveSkill(sceneId, selfId,x203527_g_Skill[1].id)<=0 then
				--		AddSkillToPlayer(sceneId, selfId, x203527_g_Skill[3].id, x203527_g_Skill[3].level, x203527_g_Skill[3].pos)
				--	end
				--	if HaveSkill(sceneId, selfId,x203527_g_Skill[2].id)<=0 then
				--		AddSkillToPlayer(sceneId, selfId, x203527_g_Skill[4].id, x203527_g_Skill[4].level, x203527_g_Skill[4].pos)
				--	end  
				--elseif zhiye ==3 then
				--	if HaveSkill(sceneId, selfId,x203527_g_Skill[1].id)<=0 then
				--		AddSkillToPlayer(sceneId, selfId, x203527_g_Skill[5].id, x203527_g_Skill[5].level, x203527_g_Skill[5].pos)
				--	end
				--	if HaveSkill(sceneId, selfId,x203527_g_Skill[2].id)<=0 then
				--		AddSkillToPlayer(sceneId, selfId, x203527_g_Skill[6].id, x203527_g_Skill[6].level, x203527_g_Skill[6].pos)
				--	end 
				--elseif zhiye ==4 then
				--	if HaveSkill(sceneId, selfId,x203527_g_Skill[1].id)<=0 then
				--		AddSkillToPlayer(sceneId, selfId, x203527_g_Skill[7].id, x203527_g_Skill[7].level, x203527_g_Skill[7].pos)
				--	end
				--	if HaveSkill(sceneId, selfId,x203527_g_Skill[2].id)<=0 then
				--		AddSkillToPlayer(sceneId, selfId, x203527_g_Skill[8].id, x203527_g_Skill[8].level, x203527_g_Skill[8].pos)
				--	end 
				--elseif zhiye ==5 then
				--	if HaveSkill(sceneId, selfId,x203527_g_Skill[1].id)<=0 then
				--		AddSkillToPlayer(sceneId, selfId, x203527_g_Skill[9].id, x203527_g_Skill[9].level, x203527_g_Skill[9].pos)
				--	end
				--	if HaveSkill(sceneId, selfId,x203527_g_Skill[2].id)<=0 then
				--		AddSkillToPlayer(sceneId, selfId, x203527_g_Skill[10].id, x203527_g_Skill[10].level, x203527_g_Skill[10].pos)
				--	end 
				--elseif zhiye ==6 then
				--	if HaveSkill(sceneId, selfId,x203527_g_Skill[1].id)<=0 then
				--		AddSkillToPlayer(sceneId, selfId, x203527_g_Skill[11].id, x203527_g_Skill[11].level, x203527_g_Skill[11].pos)
				--	end
				--	if HaveSkill(sceneId, selfId,x203527_g_Skill[2].id)<=0 then
				--		AddSkillToPlayer(sceneId, selfId, x203527_g_Skill[12].id, x203527_g_Skill[12].level, x203527_g_Skill[12].pos)
				--	end 
				--elseif zhiye ==7 then
				--	if HaveSkill(sceneId, selfId,x203527_g_Skill[1].id)<=0 then
				--		AddSkillToPlayer(sceneId, selfId, x203527_g_Skill[13].id, x203527_g_Skill[13].level, x203527_g_Skill[13].pos)
				--	end
				--	if HaveSkill(sceneId, selfId,x203527_g_Skill[2].id)<=0 then
				--		AddSkillToPlayer(sceneId, selfId, x203527_g_Skill[14].id, x203527_g_Skill[14].level, x203527_g_Skill[14].pos)
				--	end 
				--elseif zhiye ==8 then
				--	if HaveSkill(sceneId, selfId,x203527_g_Skill[1].id)<=0 then
				--		AddSkillToPlayer(sceneId, selfId, x203527_g_Skill[15].id, x203527_g_Skill[15].level, x203527_g_Skill[15].pos)
				--	end
				--	if HaveSkill(sceneId, selfId,x203527_g_Skill[2].id)<=0 then
				--		AddSkillToPlayer(sceneId, selfId, x203527_g_Skill[16].id, x203527_g_Skill[16].level, x203527_g_Skill[16].pos)
				--	end 
				--elseif zhiye ==9 then
				--	if HaveSkill(sceneId, selfId,x203527_g_Skill[1].id)<=0 then
				--		AddSkillToPlayer(sceneId, selfId, x203527_g_Skill[17].id, x203527_g_Skill[17].level, x203527_g_Skill[17].pos)
				--	end
				--	if HaveSkill(sceneId, selfId,x203527_g_Skill[2].id)<=0 then
				--		AddSkillToPlayer(sceneId, selfId, x203527_g_Skill[18].id, x203527_g_Skill[18].level, x203527_g_Skill[18].pos)
				--	end 
				--elseif zhiye ==10 then
				--	if HaveSkill(sceneId, selfId,x203527_g_Skill[1].id)<=0 then
				--		AddSkillToPlayer(sceneId, selfId, x203527_g_Skill[19].id, x203527_g_Skill[19].level, x203527_g_Skill[19].pos)
				--	end
				--	if HaveSkill(sceneId, selfId,x203527_g_Skill[2].id)<=0 then
				--		AddSkillToPlayer(sceneId, selfId, x203527_g_Skill[20].id, x203527_g_Skill[20].level, x203527_g_Skill[20].pos)
				--	end 
				--elseif zhiye ==11 then
				--	if HaveSkill(sceneId, selfId,x203527_g_Skill[1].id)<=0 then
				--		AddSkillToPlayer(sceneId, selfId, x203527_g_Skill[21].id, x203527_g_Skill[21].level, x203527_g_Skill[21].pos)
				--	end
				--	if HaveSkill(sceneId, selfId,x203527_g_Skill[2].id)<=0 then
				--		AddSkillToPlayer(sceneId, selfId, x203527_g_Skill[22].id, x203527_g_Skill[22].level, x203527_g_Skill[22].pos)
				--	end 
				--elseif zhiye ==12 then
				--	if HaveSkill(sceneId, selfId,x203527_g_Skill[1].id)<=0 then
				--		AddSkillToPlayer(sceneId, selfId, x203527_g_Skill[23].id, x203527_g_Skill[23].level, x203527_g_Skill[23].pos)
				--	end
				--	if HaveSkill(sceneId, selfId,x203527_g_Skill[2].id)<=0 then
				--		AddSkillToPlayer(sceneId, selfId, x203527_g_Skill[24].id, x203527_g_Skill[24].level, x203527_g_Skill[24].pos)
				--	end 
				--end
				CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203527_g_MissionIdNext )	
				--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 17,1 ) 
   end
end

function x203527_GetBonus( sceneId, selfId,NpcID)
	  if x203527_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203527_g_ExpBonus);
  	end
		if x203527_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203527_g_BonusMoney1 )
	  end
		if x203527_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203527_g_BonusMoney2 )
	  end
		if x203527_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203527_g_BonusMoney3 )
		end
		if x203527_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203527_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203527_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203527_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203527_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203527_g_BonusMoney6)
		end
end

function x203527_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x203527_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x203527_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203527_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203527_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203527_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203527_g_MissionName.."！", 0, 3)
				if x203527_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G经验"..x203527_g_ExpBonus.."#cffcf00的奖励", 0, 2)
  			end
				if x203527_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G银卡"..x203527_g_BonusMoney1.."文#cffcf00的奖励", 0, 2)
	  		end
				if x203527_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G现银"..x203527_g_BonusMoney2.."文#cffcf00的奖励", 0, 2)
	  		end
				if x203527_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G金卡"..x203527_g_BonusMoney3.."文#cffcf00的奖励", 0, 2)
				end
				if x203527_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G朝廷声望值"..x203527_g_BonusMoney4.."#cffcf00的奖励", 0, 2)
				end
				if x203527_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G声望"..x203527_g_BonusMoney5.."#cffcf00的奖励", 0, 2)
				end
				if x203527_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G荣誉"..x203527_g_BonusMoney6.."#cffcf00的奖励", 0, 2)
				end
		end
end

function x203527_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
    local bFind  = 0
    for i ,item in pairs(x203527_g_NpcGUID) do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203527_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203527_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203527_g_MissionId, state, -1 )
		end
end

--**********************************杀怪

function x203527_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
--	if	objdataId ==x203527_g_DemandKill[1].id then
--	 local KilledNum = GetMonsterOwnerCount( sceneId, objId ) --取得这个怪物死后拥有分配权的人数
--		for i = 0, KilledNum-1 do
--			local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --取得拥有分配权的人的objId
--            if humanObjId ~= -1 then
--                 if IsHaveQuest(sceneId,humanObjId, x203527_g_MissionId) > 0 then
--                    local misIndex = GetQuestIndexByID(sceneId,humanObjId,x203527_g_MissionId)
--										if GetQuestParam(sceneId,humanObjId,misIndex,0) < 5 then
--												SetQuestByIndex(sceneId,humanObjId,misIndex,0,GetQuestParam(sceneId,humanObjId,misIndex,0)+1)
--												Msg2Player(sceneId, humanObjId, format("你击毙了草原狼   %d/5", GetQuestParam(sceneId,humanObjId,misIndex,0)), 0, 3)
--												x203527_CheckSubmit( sceneId, humanObjId)
--										end
--                end
--            end
--		end
--	end
end

--**********************************杀怪
function x203527_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203527_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203527_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203527_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203527_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203527_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203527_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203527_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203527_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203527_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end