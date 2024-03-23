--功能：中秋礼包大放送活动领奖脚本

x350004_g_ScriptId = 350004
x350004_g_MissionName = "领取中秋礼包"
x350004_g_MissionDay = {	{ day=1001,min = 1200,	max = 1320,	flag=1},--20*60 22*60
							{ day=1002,min = 1200,	max = 1320,	flag=2},--20*60 22*60
							{ day=1003,min = 1200,	max = 1320,	flag=3},
							{ day=1004,min = 1200,	max = 1320,	flag=4},
							{ day=1005,min = 1200,	max = 1320,	flag=5},
							{ day=1006,min = 1200,	max = 1320,	flag=6},
							{ day=1007,min = 1200,	max = 1320,	flag=7},
							{ day=1008,min = 1200,	max = 1320,	flag=8}
						}
x350004_g_MissionReadme1 = "\t八月十五月正南、瓜果石榴列满盘。中秋佳节是我国的传统节日，月饼作为中秋节美食之一，象征着合家团圆和美满幸福，为表达对广大玩家的感谢和祝福，中秋国庆期间【即10月1日至10月8日】每天晚间8点至10点阶段都可以新手村和王国领奖大使处领取“中秋礼包”。\n\t届时所有30级以上的玩家都可以获得一定数量的月饼，同时也有机会获得商城道具！请您准时领取。\n\t幸运多多，切莫错失良机！"
x350004_g_MissionReadme2 = "\t《成吉思汗》中秋礼包在每天#G20:00#W至#G22:00#W间领取，每个时段您都可以领取到一只礼包，届时所有30级以上的玩家都可以获得一定数量的月饼，同时也有机会获得商城道具！请您准时领取。"
x350004_g_MissionReadme3 = "\t您已经领取了今天的中秋礼包！\n\t《成吉思汗》中秋礼包在每天#G20:00#W至#G22:00#W间领取，每天您都可以领取到一只礼包，届时所有30级以上的玩家都可以获得一定数量的月饼，同时也有机会获得商城道具！请您准时领取。"

x350004_g_LevelMin				= 30
x350004_g_RandomItemBonus		=	{
										{id=12030201,rnd=10,num=1},
										{id=12041101,rnd=30,num=1},
										{id=11970021,rnd=20,num=1},
										{id=12054300,rnd=20,num=1},
										{id=12030209,rnd=5,num=1},
										{id=12010020,rnd=5,num=1},
										{id=12041103,rnd=5,num=1},
										{id=12030200,rnd=5,num=1},
									}


--唯一的全局变量
x350004_g_MD					= MD_ZHONGQIU


function x350004_CheckDayValid( sceneId,selfId)

	local year,month,day = GetYearMonthDay()
	local nTime =GetMinOfDay()
	local nDay = month*100+day
	local nLevel = GetLevel(sceneId,selfId)

	if nLevel >= x350004_g_LevelMin then			
		for i,item in x350004_g_MissionDay do
			if nDay == item.day and nTime >= item.min and nTime <= item.max then 
				return item.flag
			end
		end	
	end
		
	return 0
	
end

function x350004_CheckHaveGetBonus( sceneId,selfId,flag )

	local year,month,day = GetYearMonthDay()
	local nTime =GetMinOfDay()
	
	local nMD ={}
	for i,item in x350004_g_MD do
		nMD[i] = GetQuestData(sceneId,selfId,item[1],item[2],item[3])
	end
	
	return nMD[flag]
	
end

--**********************************

--给固定物品

--**********************************
function x350004_Yuebing(sceneId,selfId)
	
	local nLevel = GetLevel(sceneId,selfId)
	local yuebing = -1
	if nLevel < 40  then
		yuebing = 12030251
	elseif nLevel >=40 and nLevel < 50 then
		yuebing = 12030252
	elseif nLevel >=50 and nLevel < 60 then	
		yuebing = 12030253
	elseif nLevel >=60 and nLevel < 70 then
		yuebing = 12030254
	elseif nLevel >=70 and nLevel < 80 then
		yuebing = 12030255
	elseif nLevel >=80 and nLevel < 90 then
		yuebing = 12030256
	elseif nLevel >=90 and nLevel < 100 then
		yuebing = 12030257
	end
	
	return yuebing

end

--**********************************

--给随机物品

--**********************************
function x350004_GetRandomBonus()
	
	local nMaxRandom = -1
	local nCurIndex = -1
	for i,item in x350004_g_RandomItemBonus do
		
		local rnd = random(1,item.rnd)
		
		if rnd > nMaxRandom then
			nMaxRandom = rnd
			nCurIndex = i
		end
	end
	
	--随机失败的情况,宁愿玩家受损,不处理
	if nCurIndex == -1 then
		return -1
	end
	
	local n = getn(x350004_g_RandomItemBonus)
	if nCurIndex < 1 or nCurIndex > n then
		return -1
	end
	
	--随机正确的情况
	return x350004_g_RandomItemBonus[nCurIndex].id,x350004_g_RandomItemBonus[nCurIndex].num
	
end

--**********************************

--任务入口函数

--**********************************

function x350004_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本

	--check invalid
	local nIndex = x350004_CheckDayValid( sceneId,selfId )

	if nIndex >= 1 then
		
		if x350004_CheckHaveGetBonus( sceneId,selfId,nIndex) == 0 then

			-- not get bouns
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x350004_g_MissionName)
				AddQuestText(sceneId,x350004_g_MissionReadme1)
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, targetId, x350004_g_ScriptId, x350004_g_ScriptId)
			
			return
			 		
		else
				
			--have got 
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,x350004_g_MissionReadme3)
			EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, targetId)
			
			return
				
		end
		
	end


	--check valid
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,x350004_g_MissionReadme2)
	EndQuestEvent()
	DispatchQuestEventList(sceneId, selfId, targetId)
	
end

--**********************************

--检测全局变量

--**********************************

function x350004_CheckMD( sceneId,selfId )

	local nIndex = x350004_CheckDayValid( sceneId,selfId )

	if nIndex < 1 then
		return		
	end

	local year,month,day = GetYearMonthDay()
	local nTime =GetMinOfDay()
	
	local nMD ={}
	for i,item in x350004_g_MD do
		nMD[i] = GetQuestData(sceneId,selfId,item[1],item[2],item[3])
	end
	
	local nDay = month*100+day
	
	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= x350004_g_LevelMin then
		for i,item in x350004_g_MissionDay do
			if item.day == nDay and nTime >= item.min and nTime <= item.max and nMD[item.flag]==0 then
				if x350004_GiveBonus(sceneId,selfId,item.flag) == 1 then
					SetQuestData(sceneId,selfId,x350004_g_MD[item.flag][1],x350004_g_MD[item.flag][2],x350004_g_MD[item.flag][3],1)
					return
				end
			end
		end
	end
	
end

--**********************************

--检测全局变量

--**********************************

function x350004_CheckDay( sceneId,selfId )

	local year,month,day = GetYearMonthDay()
	local nDay = month*100+day
	
	for i,item in x350004_g_MissionDay do
		if item.day == nDay then
			return 1
		end
	end
	
	return 0

end

--**********************************

--给予奖励

--**********************************

function x350004_GiveBonus( sceneId,selfId,flag)

	if flag == 1 or flag == 3 or flag == 5 or flag == 7 then
		
		BeginAddItem( sceneId )
		
		--随机物品的添加
		local nRandItem,nRandItemNum = x350004_GetRandomBonus()
		if nRandItem ~= -1 then
			AddBindItem( sceneId,nRandItem, nRandItemNum )	
		end
		
		--固定物品的添加
		local yuebing = x350004_Yuebing(sceneId,selfId)	
		if yuebing ~= -1 then
			AddBindItem( sceneId,yuebing, random(2,4) )	
		end		
				
		local ret = EndAddItem( sceneId, selfId )
		if ret > 0 then
			AddItemListToPlayer(sceneId,selfId) 
			return 1
		else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x350004_g_MissionName)
				AddQuestText(sceneId,x350004_g_MissionReadme2)
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, selfId, x350004_g_ScriptId, -1)
			return 0
		end
		
	elseif flag == 2 or flag == 4 or flag == 6 or flag == 8 then
		
		BeginAddItem( sceneId )

		--随机物品的添加
		local nRandItem,nRandItemNum = x350004_GetRandomBonus()
		if nRandItem ~= -1 then
			AddBindItem( sceneId,nRandItem, nRandItemNum )	
		end
		
		--固定物品的添加
		local yuebing = x350004_Yuebing(sceneId,selfId)	
		if yuebing ~= -1 then
			AddBindItem( sceneId,yuebing, random(2,4) )	
		end		
		
		local ret = EndAddItem( sceneId, selfId )
		if ret > 0 then
			AddItemListToPlayer(sceneId,selfId)
			return 1
		else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x350004_g_MissionName)
				AddQuestText(sceneId,x350004_g_MissionReadme2)
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, selfId, x350004_g_ScriptId, -1)
			return 0
		end
	end
	
	return 0
	
end

--**********************************

--列举事件

--**********************************

function x350004_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		if x350004_CheckDay( sceneId,selfId ) == 1 then
			AddQuestNumText(sceneId, x350004_g_ScriptId, x350004_g_MissionName,3,1)
		else 
			return
		end

end



--**********************************

--检测接受条件

--**********************************

function x350004_ProcAcceptCheck(sceneId, selfId, targetId)
	return 1
end

--点击（确定）
function x350004_ProcAccept( sceneId, selfId, NPCId )

	x350004_CheckMD( sceneId,selfId )
	
end



--**********************************

--放弃

--**********************************

function x350004_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x350004_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x350004_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x350004_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x350004_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x350004_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end
