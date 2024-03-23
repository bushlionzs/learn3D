

--MisDescBegin
x310322_g_ScriptId = 310322
--x310322_g_MissionIdPre ={67,69,70,71}
x310322_g_MissionId = 9050 

x310322_g_MissionName="【个人】疯狂的宝箱"
x310322_g_MissionTarget				= "打开5个天上人间·麒麟内的#G宝箱#W"      --任务目标
x310322_g_MissionInfo				= "\t欢迎你，我亲爱的朋友。\n\t在这天上人间·麒麟中，常常会出现镶满宝石的黄金宝箱。据说每个宝箱里都藏着#G大量经验和稀有的宝贝#W，也有一些宝箱中封印着#G可怕的魔君#W。\n\t每天你可以在我这里接取5次任务，其中第一次免费领取，后4次每次接取需#Y花费1两现金或金卡#W。\n\t宝箱出现的时间是每周六、日的：\n#G12：35—12：50#W，#G13：35—13：50#W，\n#G14：35—14：50#W，#G15：35—15：50#W，\n#G16：35—16：50#W，#G17：35—17：50#W，\n#G18：35—18：50#W，#G19：35—19：50#W，\n#G20：35—20：50#W，#G21：35—21：50#W，\n#G22：35—22：50#W"            --任务信息x310322_g_ContinueInfo				= "\t难道你害怕面对照出来的魔王？"  --任务继续信息
x310322_g_ContinueInfo				= "\t打开宝箱之前，谁也不知道里面藏着的是什么。"
x310322_g_MissionCompleted			= "\t恭喜你完成了【个人】疯狂的宝箱任务，在开启黄金宝箱那一刻，你是不是充满了期待？"  --任务完成信息
x310322_g_MissionHelp				= ""          --任务提示信息
-- 任务放弃提示信息
x300320_g_strMissionAbandon         = "您放弃了任务：【个人】疯狂的宝箱"


--MisDescEnd
--**********************************

x310322_g_MinLevel	= 65
x310322_g_MaxLevel	= 84
x310322_g_strGongLue = "#G宝箱#W会在特定时间出现在天上人间·麒麟内#G暴龙任务区#W、#G海盗船区#W、#G旋转木马区#W、#G摩天轮区#W等地方。"




x310322_g_CostGold	= 1000 --1两现金

--MD_XIANGZI_DATE			--日期			9
--MD_XIANGZI_COUNT        	--次数			5


function x310322_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if IsHaveQuest(sceneId,selfId, x310322_g_MissionId) <= 0 then
		if GetLevel( sceneId, selfId) < x310322_g_MinLevel then 
	 		return 0
		end
	end	
	
	local state = GetQuestStateNM(sceneId,selfId,NPCId,x310322_g_MissionId)
	AddQuestTextNM( sceneId, selfId, NPCId, x310322_g_MissionId, state, 0 )

 	AddQuestNumText(sceneId,x310322_g_MissionId,"【疯狂的宝箱说明】" ,13,1)
	--AddQuestNumText(sceneId,x310322_g_MissionId,"领取奖励" ,3,2)
	

end
function x310322_ProcQuestAttach( sceneId, selfId, NPCId, npcGuid, misIndex, MissionId)
	--print("x310322_ProcQuestAttach")
end

function x310322_GetCount(sceneId ,selfId, npcId)
	local hour,minute,sec =GetHourMinSec();
	local nowtime = hour*60+minute
	
	local today = GetDayOfYear()
	local lastDay = GetQuestData(sceneId, selfId, MD_XIANGZI_DATE[1], MD_XIANGZI_DATE[2], MD_XIANGZI_DATE[3])
	if today ~= lastDay then
		return 0
	end
	
	local count = GetQuestData(sceneId, selfId, MD_XIANGZI_COUNT[1], MD_XIANGZI_COUNT[2], MD_XIANGZI_COUNT[3])
	
	return count
end

function x310322_CheckTime(sceneId ,selfId, npcId)
	local hour,minute,sec =GetHourMinSec();
	if hour >= 12 and hour <= 23 then
		return 1
	end
	return 0
end
function x310322_IncCountMD(sceneId ,selfId)
	local today = GetDayOfYear()
	local lastDay = GetQuestData(sceneId, selfId, MD_XIANGZI_DATE[1], MD_XIANGZI_DATE[2], MD_XIANGZI_DATE[3])
	if today == lastDay then
		local count = GetQuestData(sceneId, selfId, MD_XIANGZI_COUNT[1], MD_XIANGZI_COUNT[2], MD_XIANGZI_COUNT[3])
		count = count + 1
		SetQuestData(sceneId,selfId,MD_XIANGZI_COUNT[1],MD_XIANGZI_COUNT[2],MD_XIANGZI_COUNT[3], count)
		return count
	else
		SetQuestData(sceneId,selfId,MD_XIANGZI_DATE[1],MD_XIANGZI_DATE[2],MD_XIANGZI_DATE[3], today)
       	SetQuestData(sceneId,selfId,MD_XIANGZI_COUNT[1],MD_XIANGZI_COUNT[2],MD_XIANGZI_COUNT[3], 1)    
       	return 1
    end  
end

function x310322_DecCountMD(sceneId ,selfId)
	local count = GetQuestData(sceneId, selfId, MD_XIANGZI_COUNT[1], MD_XIANGZI_COUNT[2], MD_XIANGZI_COUNT[3])
	count = count - 1
	if count <= 0 then
		count = 0
	end
	SetQuestData(sceneId,selfId,MD_XIANGZI_COUNT[1],MD_XIANGZI_COUNT[2],MD_XIANGZI_COUNT[3], count)
	return count
end


---------------------------------------------------------------------------------------------------
--检查任务是否可提交
---------------------------------------------------------------------------------------------------
function x310322_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID( sceneId, selfId, x310322_g_MissionId)

    if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
        return 1
    else
        return 0
    end
end


function x310322_ProcEventEntry(sceneId ,selfId, NPCId,idScript,idExt )	--点击该任务后执行此脚本
	--print("x310322_ProcEventEntry")
	if idExt == 0 then
		if IsQuestHaveDone(sceneId, selfId, x310322_g_MissionId) > 0 then
			BeginQuestEvent(sceneId)
        	AddQuestText(sceneId,"你已完成此任务")
        	EndQuestEvent(sceneId)
        	DispatchQuestEventList(sceneId,selfId,NPCId)
			return
		end
		
		if IsHaveQuest(sceneId,selfId, x310322_g_MissionId) > 0 then
			local bDone = x310322_CheckSubmit( sceneId, selfId, NPCId)
            if bDone > 0 then
                x310322_DispatchCompletedInfo( sceneId, selfId, NPCId) --完成任务显示
            else
                x310322_DispatchContinueInfo( sceneId, selfId, NPCId) --未完成任务显示
            end
            
            
--			BeginQuestEvent(sceneId)
--        	AddQuestText(sceneId,"你已有此任务")
--        	EndQuestEvent(sceneId)
--        	DispatchQuestEventList(sceneId,selfId,NPCId)
			return
		end
		
		
		
		
		BeginQuestEvent(sceneId)
		local level =GetLevel( sceneId, selfId)
		local exp =  level *64800
		AddQuestText(sceneId,"#Y"..x310322_g_MissionName)
        AddQuestText(sceneId,x310322_g_MissionInfo)
        AddQuestText( sceneId,"#Y任务目标:")
        AddQuestText( sceneId,x310322_g_MissionTarget)        
        AddQuestExpBonus(sceneId, exp )
        EndQuestEvent(sceneId)
        --DispatchQuestEventList(sceneId,selfId,NPCId)
        DispatchQuestInfoNM(sceneId, selfId, NPCId, x310322_g_ScriptId, x310322_g_MissionId)
        

	elseif idExt == 1 then
		BeginQuestEvent(sceneId)
				local Readme_1 = "#Y【疯狂的宝箱说明】#r#W"
				AddQuestText(sceneId,"#Y接取任务：\n\t#W65级以上的玩家，每周六、日12：30-22：50可以接取任务。\n\t每个玩家每天最多可以接取五次任务。第一次接取任务免费，其后的四次均要花费#R1两现金/金卡#W。")
        AddQuestText(sceneId,"#Y玩法过程：\n\t#W接取任务后，你需要在#G特定时间#W内,找到散落在天上人间·麒麟各处的#G宝箱#W。\n\t采集宝箱后有可能会获得以下几种奖励：\n\t1.完成任务获得超大量经验。\n\t2.获得道具天上人间·麒麟藏宝图碎片（凑齐后可找彩湘子合成天上人间·麒麟藏宝图）。\n\t3.获得道具魔君部将召唤符。\n\t4.原地释放出一个十八魔君。\n \n#Y宝箱出现的时间:#W\n#G12：35—12：50#W，#G13：35—13：50#W，\n#G14：35—14：50#W，#G15：35—15：50#W，\n#G16：35—16：50#W，#G17：35—17：50#W，\n#G18：35—18：50#W，#G19：35—19：50#W，\n#G20：35—20：50#W，#G21：35—21：50#W，\n#G22：35—22：50#W。")
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,NPCId)
    elseif idExt == 2 then
    	
	end
	

end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x310322_DispatchContinueInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x310322_g_MissionName)
    AddQuestText( sceneId, x310322_g_ContinueInfo)
    AddQuestText( sceneId, " ")
 
    DispatchQuestEventList( sceneId, selfId, NPCId)
	
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x310322_DispatchCompletedInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x310322_g_MissionName)
    AddQuestText( sceneId, x310322_g_MissionCompleted)
    AddQuestText( sceneId, " ")
    local level = GetLevel( sceneId, selfId)
    
	EndQuestEvent( sceneId)
    DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x310322_g_ScriptId, x310322_g_MissionId)
end

function x310322DispatchMissionInfo( sceneId, selfId, NPCId)
	
	BeginQuestEvent( sceneId)

    --任务信息
    AddQuestText( sceneId, "#Y"..x310322_g_MissionName)
    AddQuestText( sceneId, x310322_g_MissionInfo)
    AddQuestText( sceneId, " ")
           
    --任务目标
    AddQuestText( sceneId, "#Y任务目标：")
    AddQuestText( sceneId, x310322_g_MissionTarget)
    AddQuestText( sceneId, " ")

    --提示信息
    if x310322_g_MissionHelp ~= "" then
        AddQuestText( sceneId, "#Y任务提示：")
        AddQuestText( sceneId, x310322_g_MissionHelp)
        AddQuestText( sceneId, " ")
    end                 

	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, NPCId, x310322_g_ScriptId, x310322_g_MissionId)
end

function x310322_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	BeginQuestEvent( sceneId)
	local level =GetLevel( sceneId, selfId)
	local exp =  level *64800
	local misIndex = GetQuestIndexByID(sceneId,selfId,x310322_g_MissionId)
	local num = GetQuestParam( sceneId,selfId,misIndex,1)
	local strTarget = " 开启天上人间·麒麟内的#G宝箱#W："..num.."/".."#W"..5
	AddQuestLogCustomText( sceneId,
                                   x310322_g_MissionName,               -- 标题
                                   x310322_g_MissionName,               -- 任务名字
                                   strTarget,                   				 -- 任务目标
                                   "",              -- 任务NPC
                                   x310322_g_strGongLue,               -- 任务攻略
                                   x310322_g_MissionInfo,    -- 任务描述
                                   x310322_g_MissionHelp) 
                                                -- 任务提示
                                                
    AddQuestExpBonus( sceneId, exp)                                            
    EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, x310322_g_MissionId)
end


function x310322_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end



function x310322_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
	--print("x310322_ProcQuestAccept")
	
	local count = GetQuestData(sceneId,selfId,MD_XIANGZI_COUNT[1],MD_XIANGZI_COUNT[2],MD_XIANGZI_COUNT[3])    
		

	if IsQuestHaveDone(sceneId, selfId, x310322_g_MissionId) > 0 then
		BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"你已经有此任务")
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,NPCId)
        return 
    end
    
    local level = GetLevel(sceneId, selfId)
	if  GetLevel( sceneId, selfId) > x310322_g_MaxLevel then
    	Msg2Player(sceneId, selfId, "只有低于85级的玩家才能接受本任务", 0, 2)
   		Msg2Player(sceneId, selfId, "只有低于85级的玩家才能接受本任务", 0, 3)   
   		return
	end
		
		
    if IsQuestFullNM(sceneId,selfId)==1 then
 		Msg2Player(sceneId, selfId, "任务已满，添加任务失败", 0, 2)
   		Msg2Player(sceneId, selfId, "任务已满，添加任务失败", 0, 3)          
        return 
    end
	local level = GetLevel(sceneId, selfId)
		if GetLevel( sceneId, selfId) < x310322_g_MinLevel or GetLevel( sceneId, selfId) > x310322_g_MaxLevel then
			BeginQuestEvent(sceneId)
        	AddQuestText(sceneId,"等级不属于65级至84级之间，无法领取任务")
        	EndQuestEvent(sceneId)
        	DispatchQuestEventList(sceneId,selfId,NPCId)
			return
		end
		
		local weekDay = GetWeek()
		if weekDay ~= 0 and weekDay ~= 6 then
		BeginQuestEvent(sceneId)
        	AddQuestText(sceneId,"\t很抱歉，本活动尚未开放，请于周六、日12：30以后再来领取")
        	EndQuestEvent(sceneId)
        	DispatchQuestEventList(sceneId,selfId,NPCId)       	       	
        Msg2Player(sceneId, selfId, "很抱歉，本活动尚未开放，请于周六、日12：30以后再来领取", 0, 2)
   			Msg2Player(sceneId, selfId, "很抱歉，本活动尚未开放，请于周六、日12：30以后再来领取", 0, 3)   
			return --TEST
		end
		if x310322_CheckTime(sceneId ,selfId, npcId) < 1 then       	
       Msg2Player(sceneId, selfId, "很抱歉，本活动开放时间为12：30-22：50", 0, 2)
   		 Msg2Player(sceneId, selfId, "很抱歉，本活动开放时间为12：30-22：50", 0, 3) 
			return --TEST
		end
		
		local count = x310322_GetCount(sceneId ,selfId, npcId)
		if count >= 5 then
       Msg2Player(sceneId, selfId, "你今天已完成5次【个人】疯狂的宝箱，请改天再来", 0, 2)
   		 Msg2Player(sceneId, selfId, "你今天已完成5次【个人】疯狂的宝箱，请改天再来", 0, 3)         	      	
			return
		end
		
		
		
   if count >= 1 then  --不是第一次则要扣钱
		if CostMoney(sceneId,selfId,3,x310322_g_CostGold) ~= -1 then
			Msg2Player(sceneId, selfId, "领取任务成功，扣除1两金卡！", 0, 3)
			Msg2Player(sceneId, selfId, "领取任务成功，扣除1两金卡！", 0, 2)
		else
			if CostMoney(sceneId,selfId,2,x310322_g_CostGold,318) ~= -1 then
				Msg2Player(sceneId, selfId, "领取任务成功，扣除1两现金！", 0, 3)
				Msg2Player(sceneId, selfId, "领取任务成功，扣除1两现金！", 0, 2)
			else
	    	Msg2Player(sceneId, selfId, "很遗憾，你的现金/金卡不足1两", 0, 3)
				Msg2Player(sceneId, selfId, "很遗憾，你的现金/金卡不足1两", 0, 2)
	    		return
			end
		end
	end
   local retmiss = AddQuest( sceneId, selfId, x310322_g_MissionId, x310322_g_ScriptId, 0, 0, 0, 1)
   if retmiss ==0 then
       Msg2Player(sceneId, selfId, "接受任务失败！", 0, 3)
       return 0
   end
   	x310322_IncCountMD(sceneId ,selfId)     	
   	x310322_ProcQuestLogRefresh( sceneId, selfId, x310322_g_MissionId)	
    --BeginQuestEvent(sceneId)
   	--AddQuestText(sceneId,"成功接任务")
   	--EndQuestEvent(sceneId)
   	--DispatchQuestEventList(sceneId,selfId,NPCId)
   	GamePlayScriptLog(sceneId, selfId, 1641)
	
end

function x310322_ProcQuestAbandon(sceneId, selfId, MissionId)
    if IsHaveQuest(sceneId,selfId, x310322_g_MissionId) <= 0 then
        return 
    end
    DelQuest( sceneId, selfId, x310322_g_MissionId)
    Msg2Player(sceneId, selfId, format("您放弃了任务:%s",x310322_g_MissionName), 0, 2)
    Msg2Player(sceneId, selfId, format("您放弃了任务:%s",x310322_g_MissionName), 0, 3) 
   	--x310322_DecCountMD(sceneId ,selfId)   --放弃也计次
    
end


function x310322_GiveBonus(sceneId, selfId, NPCId)
end

function x310322_GiveExp( sceneId, selfId)
	local rate = random(1,100)
	if rate == 100 then
		local level = GetLevel(sceneId,selfId)
		local bonusExp = 64800 * level * 3
		AddExp(sceneId,selfId,bonusExp)
		local name = GetName(sceneId,selfId)
		if name == nil then
			name = "ErrorName"
		end

		Msg2Player( sceneId, selfId, "您非常幸运的获得3倍经验奖励"..bonusExp.."点。", 8, 2)
		return 1
	elseif rate >= 75 then
		local level = GetLevel(sceneId,selfId)
		local bonusExp = 64800 * level * 1.5
		AddExp(sceneId,selfId,bonusExp)
		Msg2Player( sceneId, selfId, "您幸运的获得1.5倍经验奖励"..bonusExp.."点。", 8, 2)
		return 1
	else
		local level = GetLevel(sceneId,selfId)
		local bonusExp = 64800 * level
		AddExp(sceneId,selfId,bonusExp)
		Msg2Player( sceneId, selfId, "您获得经验奖励"..bonusExp.."点。", 8, 2)
		return 1
	end
	return 0
end
function x310322_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x310322_g_MissionId) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"您没有这个任务！")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif DelQuest(sceneId, selfId, x310322_g_MissionId) > 0 then
		x310322_GiveExp( sceneId, selfId)
    Msg2Player(sceneId, selfId, format("您完成了任务:%s",x310322_g_MissionName), 0, 2)
    Msg2Player(sceneId, selfId, format("您完成了任务:%s",x310322_g_MissionName), 0, 3) 
    	
    GamePlayScriptLog( sceneId, selfId, 1642)   
	
       -- AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x310322_g_MissionIdNext )	
end

 