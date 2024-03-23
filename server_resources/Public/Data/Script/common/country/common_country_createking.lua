--申请当国王
--MisDescBegin
--脚本号
x800024_g_ScriptId = 800024

--上一个任务的ID
--g_MissionIdPre =



--任务文本描述
x800024_g_MissionName="【国家】申请国王"

--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x800024_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本

	BeginQuestEvent(sceneId)
	
	local Readme_1 = "#Y【国家】申请国王#W#r #r"
	
	local Readme_2 = "\t成吉思汗中，想要成为国王必须要满足四个条件：#r #r"
	
	local Readme_3 = "  1，您包裹中的现银必须#G大于50两#W。#r #r"
	
	local Readme_4 = "  2，您必须是某个#G帮会#W的#G帮主#W。#r #r"
	
	local Readme_5 = "  3，您的#G帮会等级#W必须大于#G2级#W。#r #r"
	
	local Readme_6 = "  4，您的#G帮会人数#W必须大于#G15人#W。#r #r"
	
	local Readme_7 = "您是否决定要申请国王？"
	
	local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5..Readme_6..Readme_7
	
	AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId);DispatchQuestInfo( sceneId, selfId, targetId, x800024_g_ScriptId, -1 )
	
end

--**********************************
--列举事件
--**********************************
function x800024_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	local nCountry = GetCurCountry(sceneId, selfId)
	if CountryGetKingGUID(nCountry) == -1 then
		AddQuestNumText(sceneId,x800024_g_ScriptId,x800024_g_MissionName,3)
	end
end


--********************
--检测接受条件
--**********************************
function x800024_ProcAcceptCheck( sceneId, selfId, NPCId )
	--1. 钱
	if GetMoney(sceneId, selfId, 0) < 50000 then
        BeginQuestEvent(sceneId);
        AddQuestText(sceneId, "现银不足50两，不能申请国王");
        EndQuestEvent();
        DispatchQuestTips(sceneId, selfId);	
		return 0		
	end
	
	--2. 是否帮主
	if GetGuildOfficial(sceneId, selfId) ~= 5 then
        BeginQuestEvent(sceneId);
        AddQuestText(sceneId, "不是帮主，不能申请国王");
        EndQuestEvent();
        DispatchQuestTips(sceneId, selfId);	
		return 0		
	end
	
	local guildID = GetGuildID(sceneId, selfId)
	if guildID == -1 then
		return 0
	end
	
	local nLevel, nCount, nExp = GetGuildSimpleData(guildID)
	--3. 帮会级别
	if nLevel<2 then
        BeginQuestEvent(sceneId);
        AddQuestText(sceneId, "帮会等级小于2级，不能申请国王");
        EndQuestEvent();
        DispatchQuestTips(sceneId, selfId);	
		return 0		
	end
	
	--4. 帮会人数
	if nCount<15 then
        BeginQuestEvent(sceneId);
        AddQuestText(sceneId, "帮会成员不足15人，不能申请国王");
        EndQuestEvent();
        DispatchQuestTips(sceneId, selfId);	
		return 0		
	end
	
	return 1
end

--**********************************
--接受
--**********************************
function x800024_ProcAccept( sceneId, selfId )
	ApplyKing(sceneId, selfId)
end

--**********************************
--放弃
--**********************************
function x800024_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x800024_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x800024_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x800024_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x800024_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x800024_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x800024_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
