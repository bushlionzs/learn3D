--功能：年底分红领奖脚本：12月15日刺陵活动 12月25日活动 1月1日元旦活动

x350012_g_ScriptId = 350012
x350012_g_MissionName = "领取年底分红"
x350012_g_MissionDay = {	{ day=1218,min = 1200,	max = 1320,	flag=1},--20*60 22*60
													{ day=1225,min = 1200,	max = 1320,	flag=2},--20*60 22*60
													{ day=0101,min = 1200,	max = 1320,	flag=3}
												}
x350012_g_MissionDayTest = {	{ day=1218,min = 1200,	max = 1320,	flag=1},--20*60 22*60
													{ day=1225,min = 1200,	max = 1320,	flag=2},--20*60 22*60
													{ day=0101,min = 1200,	max = 1320,	flag=3}
												}
x350012_g_MissionReadme = "\t《成吉思汗：刺陵》资料片于2009年12月18日公开测试，感谢您能够长久如一日地支持《成吉思汗》，您的忠诚让我们感动，值此新资料片公测之际，带有10元金卡的刺陵大红包仅代表我们的一点心意，为您的游戏之旅带来更多好运！\n\t12月18日晚间8点至10点阶段您可以在新手村和王国领奖大使处领取“#R年底分红#W”。\n\t届时所有#R60级#W以上的玩家都可以获得年底分红金卡红包！请您准时领取。"
x350012_g_MissionReadme1 = "\t《成吉思汗：刺陵》资料片于2009年12月18日公开测试，感谢您能够长久如一日地支持《成吉思汗》，您的忠诚让我们感动，值此新资料片公测之际，带有10元金卡的刺陵大红包仅代表我们的一点心意，为您的游戏之旅带来更多好运！\n\t12月18日晚间8点至10点阶段您可以在新手村和王国领奖大使处领取“#R年底分红#W”。\n\t届时所有WR60级#W以上的玩家都可以获得年底分红金卡红包！请您准时领取。"
x350012_g_MissionReadme2 = "\t晚间8点至10点阶段您可以在新手村和王国领奖大使处领取“#R年底分红#W”。\n\t届时所有#R60级#W以上的玩家都可以获得年底分红金卡红包！请您准时领取。"
x350012_g_MissionReadme3 = "\t您已经领取了今天的年底分红大红包！\n\t年底分红在当天#G20:00#W至#G22:00#W间领取，您将直接获得#R红包内的金卡分红#W！请您准时领取。"
x350012_g_LevelMin				= 60
--x350012_g_RandomItemBonus		=	 12030421


--唯一的全局变量
x350012_g_MD					= MD_FENHONG


function x350012_CheckDayValid( sceneId,selfId)

	local year,month,day = GetYearMonthDay()
	local nTime =GetMinOfDay()
	local nDay = month*100+day
	local nLevel = GetLevel(sceneId,selfId)

	if GetTestServerToggle() == 1 then	--体服
		if nLevel >= x350012_g_LevelMin then			
			for i,item in x350012_g_MissionDayTest do
				if nDay == item.day and nTime >= item.min and nTime <= item.max then 
					return item.flag
				end
			end	
		end
	else	--公服
		if nLevel >= x350012_g_LevelMin then			
			for i,item in x350012_g_MissionDay do
				if nDay == item.day and nTime >= item.min and nTime <= item.max then 
					return item.flag
				end
			end	
		end
	end

--	if nLevel >= x350012_g_LevelMin then			
--		for i,item in x350012_g_MissionDay do
--			if nDay == item.day and nTime >= item.min and nTime <= item.max then 
--				return item.flag
--			end
--		end	
--	end
		
	return 0
	
end

function x350012_CheckHaveGetBonus( sceneId,selfId,flag )

	local year,month,day = GetYearMonthDay()
	local nTime =GetMinOfDay()
	
	local nMD ={}
	for i,item in x350012_g_MD do
		nMD[i] = GetQuestData(sceneId,selfId,item[1],item[2],item[3])
	end
	
	return nMD[flag]
	
end

--**********************************

--任务入口函数

--**********************************

function x350012_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本

	--check invalid
	local nIndex = x350012_CheckDayValid( sceneId,selfId )

	if nIndex >= 1 then
			
		local	strInfo1 = x350012_g_MissionReadme
		local	strInfo2 = "\t逢圣诞之际，大家与亲朋好友共享节日的快乐，与兄弟姐妹一起尽情享受《成吉思汗：刺陵》给我们带来的无限欢乐！\n\t回首过去，您为《成吉思汗》付出了许多许多，也为属国建立了无数功勋。这些点点滴滴都被我们牢记于心，带有20元金卡的圣诞大红包送给您，感谢您对我们的支持和鼓励！\n\t#G12月25日晚间8点至10点阶段#W您可以在新手村和王国领奖大使处领取“#R年底分红#W”。\n\t届时所有#R60级#W以上的玩家都可以获得年底分红金卡红包！请您准时领取。"
		local strInfo3 = "\t元旦历来是中国的传统节日，在爆竹与烟花、恭喜与贺喜的喜庆气氛中，我们共同迎接《成吉思汗》创造的更大辉煌！\n\t光阴茬苒，我们迎来新的一年！在您伴随《成吉思汗》共同成长的数百个日夜里，我们感受到了您对她深切的爱意，这个满怀感激的带有30元金卡的元旦大红包助您在来年继续加油，勇攀巅峰！\n\t1月1日晚间8点至10点阶段您可以在新手村和王国领奖大使处领取“#R年底分红#W”。\n\t届时所有#R60级#W以上的玩家都可以获得年底分红金卡红包！请您准时领取。"
		
		if x350012_CheckHaveGetBonus( sceneId,selfId,nIndex) == 0 then
			if GetTestServerToggle() == 1 then
				-- not get bouns
				if nIndex == 1 then
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x350012_g_MissionName)
						AddQuestText(sceneId,x350012_g_MissionReadme)
					EndQuestEvent()
					DispatchQuestInfoNM(sceneId, selfId, targetId, x350012_g_ScriptId, x350012_g_ScriptId)				
				elseif nIndex == 2 then
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x350012_g_MissionName)
						AddQuestText(sceneId,strInfo2)
					EndQuestEvent()
					DispatchQuestInfoNM(sceneId, selfId, targetId, x350012_g_ScriptId, x350012_g_ScriptId)					
				elseif nIndex == 3 then
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x350012_g_MissionName)
						AddQuestText(sceneId,strInfo3)
					EndQuestEvent()
					DispatchQuestInfoNM(sceneId, selfId, targetId, x350012_g_ScriptId, x350012_g_ScriptId)					
				end
			
			else
				-- not get bouns
				if nIndex == 1 then
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"#Y"..x350012_g_MissionName)
					AddQuestText(sceneId,x350012_g_MissionReadme)
				EndQuestEvent()
				DispatchQuestInfoNM(sceneId, selfId, targetId, x350012_g_ScriptId, x350012_g_ScriptId)						
				elseif nIndex == 2 then
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"#Y"..x350012_g_MissionName)
					AddQuestText(sceneId,strInfo2)
				EndQuestEvent()
				DispatchQuestInfoNM(sceneId, selfId, targetId, x350012_g_ScriptId, x350012_g_ScriptId)						
				elseif nIndex == 3 then
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"#Y"..x350012_g_MissionName)
					AddQuestText(sceneId,strInfo3)
				EndQuestEvent()
				DispatchQuestInfoNM(sceneId, selfId, targetId, x350012_g_ScriptId, x350012_g_ScriptId)						
				end
				
	
			end
			
			return
			 		
		else
				
			--have got 
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,x350012_g_MissionReadme3)
			EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, targetId)
			
			return
				
		end
		
	end


	--check valid
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x350012_g_MissionName)
		AddQuestText(sceneId,x350012_g_MissionReadme2)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, targetId)
	
end

--**********************************

--检测全局变量

--**********************************

function x350012_CheckMD( sceneId,selfId )

	local nIndex = x350012_CheckDayValid( sceneId,selfId )

	if nIndex < 1 then
		return		
	end

	local year,month,day = GetYearMonthDay()
	local nTime =GetMinOfDay()
	
	local nMD ={}
	for i,item in x350012_g_MD do
		nMD[i] = GetQuestData(sceneId,selfId,item[1],item[2],item[3])
	end
	
	local nDay = month*100+day
	
	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= x350012_g_LevelMin then

	if GetTestServerToggle() == 1 then
		for i,item in x350012_g_MissionDayTest do
			if item.day == nDay and nTime >= item.min and nTime <= item.max and nMD[item.flag]==0 then
				if x350012_GiveBonus(sceneId,selfId,item.flag) == 1 then
					SetQuestData(sceneId,selfId,x350012_g_MD[item.flag][1],x350012_g_MD[item.flag][2],x350012_g_MD[item.flag][3],1)
					return
				end
			end
		end
	else
		for i,item in x350012_g_MissionDay do
			if item.day == nDay and nTime >= item.min and nTime <= item.max and nMD[item.flag]==0 then
				if x350012_GiveBonus(sceneId,selfId,item.flag) == 1 then
					SetQuestData(sceneId,selfId,x350012_g_MD[item.flag][1],x350012_g_MD[item.flag][2],x350012_g_MD[item.flag][3],1)
					return
				end
			end
		end
	end
	
	
--		for i,item in x350012_g_MissionDay do
--			if item.day == nDay and nTime >= item.min and nTime <= item.max and nMD[item.flag]==0 then
--				if x350012_GiveBonus(sceneId,selfId,item.flag) == 1 then
--					SetQuestData(sceneId,selfId,x350012_g_MD[item.flag][1],x350012_g_MD[item.flag][2],x350012_g_MD[item.flag][3],1)
--					return
--				end
--			end
--		end
	end
	
end

--**********************************

--检测全局变量

--**********************************

function x350012_CheckDay( sceneId,selfId )

	local year,month,day = GetYearMonthDay()
	local nDay = month*100+day

	if GetTestServerToggle() == 1 then
		for i,item in x350012_g_MissionDayTest do
			if item.day == nDay then
				return 1
			end
		end
	else
		for i,item in x350012_g_MissionDay do
			if item.day == nDay then
				return 1
			end
		end
	end
	
--	for i,item in x350012_g_MissionDay do
--		if item.day == nDay then
--			return 1
--		end
--	end
	
	return 0

end

--**********************************

--给予奖励

--**********************************

function x350012_GiveBonus( sceneId,selfId,flag)

	if flag == 1 then
		--固定物品的添加	
		AddMoney( sceneId, selfId, 3, 10000,101)	
		Msg2Player( sceneId, selfId, "恭喜您获得刺陵资料片大红包金卡10两！", 8, 3)
		return 1
				
	elseif flag == 2 then
		
		AddMoney( sceneId, selfId, 3, 20000,101)	
		Msg2Player( sceneId, selfId, "恭喜您获得圣诞大红包金卡20两！", 8, 3)
		return 1
	elseif flag == 3 then
		
		AddMoney( sceneId, selfId, 3, 30000,101)	
		Msg2Player( sceneId, selfId, "恭喜您获得元旦大红包金卡30两！", 8, 3)
		return 1			

	end
	
	return 0
	
end

--**********************************

--列举事件

--**********************************

function x350012_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		if x350012_CheckDay( sceneId,selfId ) == 1 then
			AddQuestNumText(sceneId, x350012_g_ScriptId, x350012_g_MissionName,3,1)
		else 
			return
		end

end



--**********************************

--检测接受条件

--**********************************

function x350012_ProcAcceptCheck(sceneId, selfId, targetId)
	return 1
end

--点击（确定）
function x350012_ProcAccept( sceneId, selfId, NPCId )

	x350012_CheckMD( sceneId,selfId )
	
end



--**********************************

--放弃

--**********************************

function x350012_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x350012_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x350012_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x350012_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x350012_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x350012_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end
