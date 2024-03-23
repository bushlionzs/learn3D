--功能：迎公测活动领奖脚本

x350000_g_ScriptId = 350000
x350000_g_MissionName = "领取迎公测礼包"
x350000_g_MissionDay = {	{ day=710,min = 1200,	max = 1320,	flag = 1},--12*60 14*60
													{ day=711,min = 1200,	max = 1320,	flag = 2},--20*60 22*60
													{ day=712,min = 1200,	max = 1320,	flag = 3},
													{ day=713,min = 1200,	max = 1320,	flag = 4},
													{ day=714,min = 1200,	max = 1320,	flag = 5},
													{ day=715,min = 1200,	max = 1320,	flag = 6},
													{ day=716,min = 1200,	max = 1320,	flag = 7},
													{ day=717,min = 1200,	max = 1320,	flag = 8}
												}
x350000_g_MissionReadme1 = "\t《成吉思汗》将于7月17日进入公开测试阶段，为了欢迎广大玩家进行游戏，并提出您宝贵的意见，在迎接公测倒计时一周的时间里，每天晚间8点至10点阶段都可以新手村和王国领奖大使处领取“迎公测礼包”。\n\t届时所有20级以上的玩家都可以获得一定数额的银卡奖励，同时也有机会获得商城道具！\n\t幸运多多，切莫错失良机！"
x350000_g_MissionReadme2 = "\t《成吉思汗》迎公测礼包在每天#G20:00#W至#G22:00#W间领取，每个时段您都可以领取到一只礼包，届时所有20级以上的玩家都可以获得一定数额的银卡奖励，同时也有机会获得商城道具！请您准时领取。"
x350000_g_MissionReadme3 = "\t您已经领取了今天的迎公测礼包！\n\t《成吉思汗》迎公测礼包在每天#G20:00#W至#G22:00#W间领取，每个时段您都可以领取到一只礼包，届时所有20级以上的玩家都可以获得一定数额的银卡奖励，同时也有机会获得商城道具！请您准时领取。"
x350000_g_ItemBonus1			=	{{zhiye=-1,id=12030326,num=1}}
x350000_g_ItemBonus2			=	{{zhiye=-1,id=12030326,num=1}}
x350000_g_LevelMin			= 20


function x350000_CheckDayValid( sceneId,selfId)

	local year,month,day = GetYearMonthDay()
	local nTime =GetMinOfDay()
	local nDay = month*100+day
	local nLevel = GetLevel(sceneId,selfId)

	if nLevel >= x350000_g_LevelMin then
		for i,item in x350000_g_MissionDay do
			if nDay == item.day and nTime >= item.min and nTime <= item.max then 
				return item.flag
			end
		end	
	end
	
	return 0
	
end

function x350000_CheckHaveGetBonus( sceneId,selfId,flag )

	local year,month,day = GetYearMonthDay()
	local nTime =GetMinOfDay()
	
	local nMD ={}
	for i,item in MD_GONGCE01_DATE do
		nMD[i] = GetQuestData(sceneId,selfId,item[1],item[2],item[3])
	end
	
	return nMD[flag]
	
end

--**********************************

--任务入口函数

--**********************************

function x350000_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本

	--check invalid
	local nIndex = x350000_CheckDayValid( sceneId,selfId )

	if nIndex >= 1 then
		
		if x350000_CheckHaveGetBonus( sceneId,selfId,nIndex) == 0 then
		
			-- not get bouns
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x350000_g_MissionName)
				AddQuestText(sceneId,x350000_g_MissionReadme1)
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, targetId, x350000_g_ScriptId, x350000_g_ScriptId)
			
			return
			 		
		else
				
			--have got 
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,x350000_g_MissionReadme3)
			EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, targetId)
			
			return
				
		end
		
	end


	--check valid
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,x350000_g_MissionReadme2)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, targetId)
	
end

--**********************************

--检测全局变量

--**********************************

function x350000_CheckMD( sceneId,selfId )

	local nIndex = x350000_CheckDayValid( sceneId,selfId )

	if nIndex < 1 then
		return		
	end

	local year,month,day = GetYearMonthDay()
	local nTime =GetMinOfDay()
	
	local nMD ={}
	for i,item in MD_GONGCE01_DATE do
		nMD[i] = GetQuestData(sceneId,selfId,item[1],item[2],item[3])
	end
	
	local nDay = month*100+day
	
	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= x350000_g_LevelMin then
		for i,item in x350000_g_MissionDay do
			if item.day == nDay and nTime >= item.min and nTime <= item.max and nMD[item.flag]==0 then
				if x350000_GiveBonus(sceneId,selfId,item.flag) == 1 then
					SetQuestData(sceneId,selfId,MD_GONGCE01_DATE[item.flag][1],MD_GONGCE01_DATE[item.flag][2],MD_GONGCE01_DATE[item.flag][3],1)
					return
				end
			end
		end
	end

end

--**********************************

--检测全局变量

--**********************************

function x350000_CheckDay( sceneId,selfId )

	local year,month,day = GetYearMonthDay()
	local nDay = month*100+day
	
	for i,item in x350000_g_MissionDay do
		if item.day == nDay then
			return 1
		end
	end
	
	return 0

end

--**********************************

--给予奖励

--**********************************

function x350000_GiveBonus( sceneId,selfId,flag)

	if flag == 1 or flag == 3 or flag == 5 or flag == 7 then
		
		BeginAddItem( sceneId )
			for i,itm in x350000_g_ItemBonus1 do
				AddBindItem( sceneId, itm.id, itm.num )	
			end
		local ret = EndAddItem( sceneId, selfId )
		if ret > 0 then
			AddItemListToPlayer(sceneId,selfId) 
			return 1
		else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x350000_g_MissionName)
				AddQuestText(sceneId,x350000_g_MissionReadme2)
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, selfId, x350000_g_ScriptId, -1)
			return 0
		end
		
	elseif flag == 2 or flag == 4 or flag == 6 or flag == 8 then
		
		BeginAddItem( sceneId )
			for i,itm in x350000_g_ItemBonus2 do
				AddBindItem( sceneId, itm.id, itm.num )	
			end
		local ret = EndAddItem( sceneId, selfId )
		if ret > 0 then
			AddItemListToPlayer(sceneId,selfId)
			return 1
		else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x350000_g_MissionName)
				AddQuestText(sceneId,x350000_g_MissionReadme2)
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, selfId, x350000_g_ScriptId, -1)
			return 0
		end
	end
	
	return 0
	
end

--**********************************

--列举事件

--**********************************

function x350000_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

		if x350000_CheckDay( sceneId,selfId ) == 1 then
			AddQuestNumText(sceneId, x350000_g_ScriptId, x350000_g_MissionName,3,1)
		else 
			return
		end

end



--**********************************

--检测接受条件

--**********************************

function x350000_ProcAcceptCheck(sceneId, selfId, targetId)
	return 1
end

--点击（确定）
function x350000_ProcAccept( sceneId, selfId, NPCId )

	x350000_CheckMD( sceneId,selfId )
	
end



--**********************************

--放弃

--**********************************

function x350000_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x350000_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x350000_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x350000_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x350000_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x350000_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end