--初入世界

--MisDescBegin
x203550_g_ScriptId = 203550
--x203550_g_MissionIdPre =2704
x203550_g_MissionId = 3400
x203550_g_LevelLess	= 	1 
x203550_g_MissionIdNext = {3417,3418,3419,3420,3421,3422,3423,3424,3425,3426,3427,3428}
x203550_g_Name	={}
x203550_g_ExtTarget={{type=20,n=1,target="找到@npc_131000"}}
x203550_g_MissionName="【新手】征兵令"
x203550_g_MissionInfo="\t欢迎来到成吉思汗的世界！请耐心阅读一下：#r　#r\t通过您的鼠标#G左键#W点击地面可以#G行走#W，点击游戏中的人物可以和他#G交谈#W。#r\t#W若您看到的NPC头顶有#Y金色的问号#W“#Y？#W”，您可以使用鼠标左键点击他#G完成任务#W。#r　#r\t现在，看到身旁的#G雄鹰长老#W头顶的金色问号“#Y？#W”了吗？他已经等候你许久了，和他谈谈吧。"  --任务描述
x203550_g_MissionTarget=""		
x203550_g_MissionCompleted="\t#Y@myname#W,欢迎你！\n\t随着海都大王叛乱的愈演愈烈，战火已经蔓延到了一向安宁祥和的昆仑王国。\n\t近日，大元皇帝忽必烈陛下下旨，昆仑王国开始征兵！\n\t所有昆仑王国的勇士，都可以加入昆仑军，跃马扬鞭，建功立业！"					--完成任务npc说话的话
x203550_g_ContinueInfo=""
x203550_g_MissionHelp =	"您可以用鼠标#R左键#G点击雄鹰长老，和他对话。您可以点击键盘上的#RQ#G键，打开任务列表，选中你要完成的任务，点击#R任务目标#G中的蓝色字体来进行自动寻路。"
x203550_g_DemandItem ={}
x203550_g_ExpBonus = 23
x203550_g_BonusMoney1 =99999999
x203550_g_BonusMoney2 =99999999
x203550_g_BonusMoney3 =99999999
x203550_g_BonusMoney4 =99999999
x203550_g_BonusMoney5 =99999999
x203550_g_BonusMoney6 =99999999
x203550_g_BonusItem	=	{}
x203550_g_BonusChoiceItem ={}
x203550_g_NpcGUID = {}
x203550_g_ScriptIdNext ={203565,203566,203567,203568,203569,203570,203571,203572,203573,203574,203575,203576}
--MisDescEnd
--**********************************

function x203550_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	local level = GetLevel( sceneId, selfId)
  CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,0 )
	if IsQuestHaveDone(sceneId, selfId, x203550_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203550_g_MissionId) <= 0 then
		if level >20 then
			return 
		end		
	end
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x203550_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x203550_g_MissionId, state, -1 )
	  CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 2,1 ) -- 第二个 1 打开界面 0 关闭界面 ? 
end

function x203550_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203550_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203550_g_ExpBonus )
		end
		if x203550_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203550_g_BonusMoney1 )
		end
		if x203550_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203550_g_BonusMoney2 )
		end
		if x203550_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203550_g_BonusMoney3 )
		end
		if x203550_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203550_g_BonusMoney4 )
		end
		if x203550_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203550_g_BonusMoney5 )
		end
		if x203550_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203550_g_BonusMoney6 )
		end
		for i, item in x203550_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203550_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203550_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--点击该任务后执行此脚本
	if IsQuestHaveDone(sceneId, selfId, x203550_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203550_g_MissionId) > 0 then
			if x203550_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203550_g_MissionName)
						AddQuestText(sceneId,x203550_g_MissionCompleted)
						EndQuestEvent()
						
						DispatchQuestEventList(sceneId, selfId, NPCId, x203550_g_ScriptId, x203550_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203550_g_MissionName)
						AddQuestText(sceneId,x203550_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203550_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 2,0 ) -- 第二个 1 打开界面 0 关闭界面  
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 3,1 ) -- 第二个 1 打开界面 0 关闭界面  
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203550_g_ScriptId, x203550_g_MissionId);
			end
  elseif x203550_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203550_g_MissionName)
			AddQuestText(sceneId,x203550_g_MissionInfo)
			AddQuestText( sceneId,"#Y任务目标：")  
			for i, item in x203550_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203550_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#G小提示:#W")
				AddQuestText(sceneId,x203550_g_MissionHelp )
			end
			x203550_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203550_g_ScriptId, x203550_g_MissionId);
  end
	
end
--**********************************

function x203550_ProcAcceptCheck(sceneId, selfId, NPCId)

					return 1

end
--**********************************
function x203550_CheckSubmit( sceneId, selfId, NPCId)

	        return 1
	
end
--**********************************
function x203550_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203550_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203550_g_MissionId  )
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
		
		
		if x203550_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203550_g_MissionId, x203550_g_ScriptId, 0, 0, 0)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
						return 0
					else
		  			x203550_Msg2toplayer( sceneId, selfId,0)
						if x203550_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x203550_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x203550_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203550_g_MissionId) > 0 then
				return 
		end
	  	BeginQuestEvent(sceneId)
		  AddQuestText(sceneId,"您无法放弃此任务！") 
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId)
			
end
--**********************************
function x203550_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满
	BeginAddItem(sceneId)
	for j, item in x203550_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203550_g_BonusChoiceItem do
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
function x203550_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203550_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有这个任务！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203550_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您没有达到完成条件！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203550_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"包裹已满！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203550_g_MissionId) > 0 then
				x203550_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203550_g_MissionId)
				x203550_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203550_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203550_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
   end
  local zhiye =GetZhiye( sceneId, selfId)+1
   CallScriptFunction( x203550_g_ScriptIdNext[zhiye], "ProcEventEntry", sceneId, selfId, NPCId, x203550_g_MissionIdNext[zhiye] )	
end

function x203550_GetBonus( sceneId, selfId,NpcID)
	  if x203550_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203550_g_ExpBonus);
  	end
		if x203550_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203550_g_BonusMoney1 )
	  end
		if x203550_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203550_g_BonusMoney2 )
	  end
		if x203550_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203550_g_BonusMoney3 )
		end
		if x203550_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203550_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203550_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203550_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203550_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203550_g_BonusMoney6)
		end
end

function x203550_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "您接受了任务"..x203550_g_MissionName.."！", 0, 2)
		  	Msg2Player(sceneId, selfId, "您接受了任务"..x203550_g_MissionName.."！", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203550_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您放弃了任务"..x203550_g_MissionName.."！", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "您完成了任务"..x203550_g_MissionName.."！", 0, 2)
				Msg2Player(sceneId, selfId, "您完成了任务"..x203550_g_MissionName.."！", 0, 3)
				if x203550_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G经验"..x203550_g_ExpBonus.."#cffcf00的奖励", 0, 2)
  			end
				if x203550_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G银卡"..x203550_g_BonusMoney1.."文#cffcf00的奖励", 0, 2)
	  		end
				if x203550_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G现银"..x203550_g_BonusMoney2.."文#cffcf00的奖励", 0, 2)
	  		end
				if x203550_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00获得#G金卡"..x203550_g_BonusMoney3.."文#cffcf00的奖励", 0, 2)
				end
				if x203550_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G朝廷声望值"..x203550_g_BonusMoney4.."#cffcf00的奖励", 0, 2)
				end
				if x203550_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G声望"..x203550_g_BonusMoney5.."#cffcf00的奖励", 0, 2)
				end
				if x203550_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00获得#G荣誉"..x203550_g_BonusMoney6.."#cffcf00的奖励", 0, 2)
				end
		end
end

function x203550_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203550_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203550_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203550_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203550_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203550_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x203550_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203550_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203550_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203550_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203550_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203550_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end