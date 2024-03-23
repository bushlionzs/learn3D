--功能：节庆礼包大放送活动领奖脚本：感恩节 09 1125-1127

x350006_g_ScriptId = 350006
x350006_g_MissionName = "领取节庆礼包"
x350006_g_MissionDay = {	{ day=1125,min = 1200,	max = 1320,	flag=1},--20*60 22*60
													{ day=1126,min = 1200,	max = 1320,	flag=2},--20*60 22*60
													{ day=1127,min = 1200,	max = 1320,	flag=3}
												}
x350006_g_MissionDayTest = {	{ day=1121,min = 1200,	max = 1320,	flag=1},--20*60 22*60
													{ day=1122,min = 1200,	max = 1320,	flag=2},--20*60 22*60
													{ day=1123,min = 1200,	max = 1320,	flag=3}
												}
x350006_g_MissionReadme = "\t在感恩节期间，为表达对广大玩家的感谢和祝福，感恩节期间【即11月21日至11月23日】每天晚间8点至10点阶段都可以新手村和王国领奖大使处领取“节庆礼包”。\n\t届时所有30级以上的玩家都可以获得节庆礼包1个！请您准时领取。\n\t幸运多多，切莫错失良机！"
x350006_g_MissionReadme1 = "\t在感恩节期间，为表达对广大玩家的感谢和祝福，感恩节期间【即11月25日至11月27日】每天晚间8点至10点阶段都可以新手村和王国领奖大使处领取“节庆礼包”。\n\t届时所有30级以上的玩家都可以获得节庆礼包1个！请您准时领取。\n\t幸运多多，切莫错失良机！"
x350006_g_MissionReadme2 = "\t节庆礼包在每天#G20:00#W至#G22:00#W间领取，每个时段您都可以领取到1个节庆礼包！请您准时领取。"
x350006_g_MissionReadme3 = "\t您已经领取了今天的节庆礼包！\n\t节庆礼包在每天#G20:00#W至#G22:00#W间领取，每个时段您都可以领取到1个节庆礼包！请您准时领取。"
x350006_g_LevelMin				= 30
x350006_g_RandomItemBonus		=	 12030421


--唯一的全局变量
x350006_g_MD					= MD_GANEN


function x350006_CheckDayValid( sceneId,selfId)

	local year,month,day = GetYearMonthDay()
	local nTime =GetMinOfDay()
	local nDay = month*100+day
	local nLevel = GetLevel(sceneId,selfId)

	if GetTestServerToggle() == 1 then	--体服
		if nLevel >= x350006_g_LevelMin then			
			for i,item in x350006_g_MissionDayTest do
				if nDay == item.day and nTime >= item.min and nTime <= item.max then 
					return item.flag
				end
			end	
		end
	else	--公服
		if nLevel >= x350006_g_LevelMin then			
			for i,item in x350006_g_MissionDay do
				if nDay == item.day and nTime >= item.min and nTime <= item.max then 
					return item.flag
				end
			end	
		end
	end

--	if nLevel >= x350006_g_LevelMin then			
--		for i,item in x350006_g_MissionDay do
--			if nDay == item.day and nTime >= item.min and nTime <= item.max then 
--				return item.flag
--			end
--		end	
--	end
		
	return 0
	
end

function x350006_CheckHaveGetBonus( sceneId,selfId,flag )

	local year,month,day = GetYearMonthDay()
	local nTime =GetMinOfDay()
	
	local nMD ={}
	for i,item in x350006_g_MD do
		nMD[i] = GetQuestData(sceneId,selfId,item[1],item[2],item[3])
	end
	
	return nMD[flag]
	
end

--**********************************

--任务入口函数

--**********************************

function x350006_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本

	--check invalid
	local nIndex = x350006_CheckDayValid( sceneId,selfId )

	if nIndex >= 1 then
		
		if x350006_CheckHaveGetBonus( sceneId,selfId,nIndex) == 0 then
			if GetTestServerToggle() == 1 then
				-- not get bouns
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"#Y"..x350006_g_MissionName)
					AddQuestText(sceneId,x350006_g_MissionReadme)
				EndQuestEvent()
				DispatchQuestInfoNM(sceneId, selfId, targetId, x350006_g_ScriptId, x350006_g_ScriptId)			
			else
				-- not get bouns
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"#Y"..x350006_g_MissionName)
					AddQuestText(sceneId,x350006_g_MissionReadme1)
				EndQuestEvent()
				DispatchQuestInfoNM(sceneId, selfId, targetId, x350006_g_ScriptId, x350006_g_ScriptId)			
			end
			
			return
			 		
		else
				
			--have got 
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,x350006_g_MissionReadme3)
			EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, targetId)
			
			return
				
		end
		
	end


	--check valid
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,x350006_g_MissionReadme2)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, targetId)
	
end

--**********************************

--检测全局变量

--**********************************

function x350006_CheckMD( sceneId,selfId )

	local nIndex = x350006_CheckDayValid( sceneId,selfId )

	if nIndex < 1 then
		return		
	end

	local year,month,day = GetYearMonthDay()
	local nTime =GetMinOfDay()
	
	local nMD ={}
	for i,item in x350006_g_MD do
		nMD[i] = GetQuestData(sceneId,selfId,item[1],item[2],item[3])
	end
	
	local nDay = month*100+day
	
	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= x350006_g_LevelMin then

	if GetTestServerToggle() == 1 then
		for i,item in x350006_g_MissionDayTest do
			if item.day == nDay and nTime >= item.min and nTime <= item.max and nMD[item.flag]==0 then
				if x350006_GiveBonus(sceneId,selfId,item.flag) == 1 then
					SetQuestData(sceneId,selfId,x350006_g_MD[item.flag][1],x350006_g_MD[item.flag][2],x350006_g_MD[item.flag][3],1)
					return
				end
			end
		end
	else
		for i,item in x350006_g_MissionDay do
			if item.day == nDay and nTime >= item.min and nTime <= item.max and nMD[item.flag]==0 then
				if x350006_GiveBonus(sceneId,selfId,item.flag) == 1 then
					SetQuestData(sceneId,selfId,x350006_g_MD[item.flag][1],x350006_g_MD[item.flag][2],x350006_g_MD[item.flag][3],1)
					return
				end
			end
		end
	end
	
	
--		for i,item in x350006_g_MissionDay do
--			if item.day == nDay and nTime >= item.min and nTime <= item.max and nMD[item.flag]==0 then
--				if x350006_GiveBonus(sceneId,selfId,item.flag) == 1 then
--					SetQuestData(sceneId,selfId,x350006_g_MD[item.flag][1],x350006_g_MD[item.flag][2],x350006_g_MD[item.flag][3],1)
--					return
--				end
--			end
--		end
	end
	
end

--**********************************

--检测全局变量

--**********************************

function x350006_CheckDay( sceneId,selfId )

	local year,month,day = GetYearMonthDay()
	local nDay = month*100+day

	if GetTestServerToggle() == 1 then
		for i,item in x350006_g_MissionDayTest do
			if item.day == nDay then
				return 1
			end
		end
	else
		for i,item in x350006_g_MissionDay do
			if item.day == nDay then
				return 1
			end
		end
	end
	
--	for i,item in x350006_g_MissionDay do
--		if item.day == nDay then
--			return 1
--		end
--	end
	
	return 0

end

--**********************************

--给予奖励

--**********************************

function x350006_GiveBonus( sceneId,selfId,flag)

	if flag == 1 or flag == 3 or flag == 5 or flag == 7 then
		--固定物品的添加		
		BeginAddItem( sceneId )
			AddBindItem( sceneId,x350006_g_RandomItemBonus, 1 )	
			
		local ret = EndAddItem( sceneId, selfId )
		if ret > 0 then
			AddItemListToPlayer(sceneId,selfId) 
			return 1
		else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x350006_g_MissionName)
				AddQuestText(sceneId,x350006_g_MissionReadme2)
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, selfId, x350006_g_ScriptId, -1)
			return 0
		end
		
	elseif flag == 2 or flag == 4 or flag == 6 or flag == 8 then
		
		BeginAddItem( sceneId )
		--固定物品的添加		
			AddBindItem( sceneId,x350006_g_RandomItemBonus, 1 )	

		local ret = EndAddItem( sceneId, selfId )
		if ret > 0 then
			AddItemListToPlayer(sceneId,selfId)
			return 1
		else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x350006_g_MissionName)
				AddQuestText(sceneId,x350006_g_MissionReadme2)
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, selfId, x350006_g_ScriptId, -1)
			return 0
		end
	end
	
	return 0
	
end

--**********************************

--列举事件

--**********************************

function x350006_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		if x350006_CheckDay( sceneId,selfId ) == 1 then
			AddQuestNumText(sceneId, x350006_g_ScriptId, x350006_g_MissionName,3,1)
		else 
			return
		end

end



--**********************************

--检测接受条件

--**********************************

function x350006_ProcAcceptCheck(sceneId, selfId, targetId)
	return 1
end

--点击（确定）
function x350006_ProcAccept( sceneId, selfId, NPCId )

	x350006_CheckMD( sceneId,selfId )
	
end



--**********************************

--放弃

--**********************************

function x350006_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x350006_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x350006_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x350006_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x350006_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x350006_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end
