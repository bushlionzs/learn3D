--功能：帮会相关
--NPC：祖兰德

--MisDescBegin
x211000_g_ScriptId = 211000
x211000_g_MissionName = "【帮会】创建帮会"

--MisDescEnd
--**********************************

--任务入口函数

--**********************************

function x211000_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本

	BeginQuestEvent(sceneId)
	
	local Readme_1 = "#Y【帮会】创建帮会#W#r #r"
	
	local Readme_2 = "创建帮会您要满足二个条件：#r #r"
	
	local Readme_3 = " 第一个条件：您的等级必须大于或等于30级。#r #r"
	
	local Readme_4 = " 第二个条件：您所拥有的现银大于或等于50两。#r #r"
	
	local Readme_5 = "您是否要创建帮会？"
	
	-- local Readme_6 = "  3，创建帮会所需#G帮会令#W至少#G一个#W。#r #r"
	
	-- local Readme_7=  "#G帮会令：#W打败王城434,373的令火鸟以及它的随从，就有一定几率获得帮会令。"
	
	local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5--..Readme_6..Readme_7
	
	AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId);DispatchQuestInfo( sceneId, selfId, targetId, x211000_g_ScriptId, -1 );
	
end



--**********************************

--列举事件

--**********************************

function x211000_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

  --合服开关
	local flag = GetMergeDBToggle()
	if flag==1 then
		return
	end
	
	--升级数据库开关
	local UpdateDBflag = GetUpdateDBBeforeToggle()
	if UpdateDBflag==1 then
		return
	end

 	local pos = GetGuildOfficial(sceneId, selfId)--判断是否加入帮会了
	if pos ~= -1 then
		return
	end
		AddQuestNumText(sceneId, x211000_g_ScriptId, x211000_g_MissionName,3)
end



--**********************************

--检测接受条件

--**********************************

function x211000_ProcAcceptCheck(sceneId, selfId, targetId)
	--1.级别
	local nLevel = GetLevel(sceneId, selfId)
	if nLevel < 30 then
        BeginQuestEvent(sceneId);
        AddQuestText(sceneId, "很抱歉，您的等级低于30级，无法创建帮会。");
		Msg2Player(sceneId, selfId,"很抱歉，您的等级低于30级，无法创建帮会。",8,2)
        EndQuestEvent();
        DispatchQuestTips(sceneId, selfId);	
		return 0
	end
	--2.钱
	local nMoney = GetMoney(sceneId, selfId, 0)
	if nMoney < 50000 then
        BeginQuestEvent(sceneId);
        AddQuestText(sceneId, "很抱歉，您包裹中的现银不足50两，无法创建帮会。");
		Msg2Player(sceneId, selfId,"很抱歉，您包裹中的现银不足50两，无法创建帮会。",8,2)
        EndQuestEvent();
        DispatchQuestTips(sceneId, selfId);		
		return 0
	end
	--3.帮会令
	-- if HaveItem(sceneId, selfId,11990001) < 1 then
        -- BeginQuestEvent(sceneId);
        -- AddQuestText(sceneId, "很抱歉，您包裹中没有帮会令，无法创建帮会。");
		-- Msg2Player(sceneId, selfId,"很抱歉，您包裹中没有帮会令，无法创建帮会。",8,2)
        -- EndQuestEvent();
        -- DispatchQuestTips(sceneId, selfId);		
		-- return 0
	-- end
	
	return 1
end
--**********************************

--接受

--**********************************

function x211000_ProcAccept(sceneId, selfId)
	GuildCreate(sceneId, selfId, 0)
end



--**********************************

--放弃

--**********************************

function x211000_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211000_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211000_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)

end



--**********************************

--杀死怪物或玩家

--**********************************

function x211000_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211000_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211000_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end