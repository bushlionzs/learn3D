----------------------------------------------------
-- 和氏璧3环内嵌任务
----------------------------------------------------

x700014_g_ScriptId 					= 700014

x700014_g_LevelMin					= 1
x700014_g_LevelMax					= 100
x700014_g_DayCountUntil				= 1

x700014_g_ItemId					= 11990101
x700014_g_NeedItemCount				= 1	

x700014_g_MissionName				= "【队伍】定鼎天下"
x700014_g_EnterInfo					= "\t真不简单，我记得前一个在我这里看过天机的人是一百多年前一个叫做赵普的人，听说他后来做了宰相。\n\t这传国玉玺你现在不能带走，待天机显示的真龙天子出现之时，也正是此宝再现人间之日。"
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x700014_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	local level = GetLevel( sceneId,selfId )
    if level < x700014_g_LevelMin then
       return
    end

    if level > x700014_g_LevelMax then
		 return
    end
	
	AddQuestNumText(sceneId, x700014_g_ScriptId, x700014_g_MissionName,5,1);
	
end

---------------------------------------------------------------------------------------------------
--进入副本文字显示
---------------------------------------------------------------------------------------------------
function x700014_DispatchEnterInfo( sceneId, selfId, NPCId )

	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId,"#Y"..x700014_g_MissionName)
		AddQuestText(sceneId,x700014_g_EnterInfo)
		--AddQuestText(sceneId," ")

		


	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, NPCId, x700014_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--申请进入副本
---------------------------------------------------------------------------------------------------
function x700014_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--点确定后
----------------------------------------------------------------------------------------------
function x700014_ProcAccept( sceneId, selfId )

	x700014_OnRequestSubmit(sceneId, selfId);
end


-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700014_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)

	if nFlag== nil then
		return
	end

	x700014_DispatchEnterInfo( sceneId, selfId, NPCId )
	
end


function x700014_OnRequestSubmit(sceneId, selfId)

	local iRet = x700014_CheckRequest(sceneId, selfId)

	if iRet>0 then
		x700014_OnApproveRequest(sceneId, selfId)
	end
end

function x700014_CheckRequest(sceneId, selfId)

	if( x700014_g_DayCountUntil > 0 ) then
		
		if x700014_GetDayCount(sceneId, selfId) >= x700014_g_DayCountUntil then

			local str = format("此任务次数每天不能超过%d次",x700014_g_DayCountUntil)

			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			return 0;
		end
	end

	local ItemCnt = GetItemCount( sceneId, selfId, x700014_g_ItemId )

	if ItemCnt<x700014_g_NeedItemCount then
		local str = format("所需任务道具不足",x700014_g_NeedItemCount)

		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();

		DispatchQuestTips(sceneId, selfId);
		return 0;
	end

	return 1;
	
end

function x700014_OnApproveRequest(sceneId, selfId)

	
	local iRet = DelItem(sceneId, selfId,x700014_g_ItemId,x700014_g_NeedItemCount)

	if iRet>0 then
		x700014_GetBonus(sceneId, selfId)
		x700014_SetDayCount(sceneId, selfId);
	end
		
	
	
end


function x700014_GetBonus(sceneId, selfId)
	local level = GetLevel(sceneId, selfId)
	local nExpBonus = level*8000;
    if nExpBonus > 0 then
		AddExp(sceneId, selfId, nExpBonus);
		
		local str = format("你获得%d点的经验奖励",nExpBonus)
  		Msg2Player(sceneId,selfId,str,4,2)
		
	end
end


---------------------------------------------------------------------------------------------------
--取得当前次数
---------------------------------------------------------------------------------------------------
function x700014_GetDayCount(sceneId, selfId)



	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, MD_HESHIBI_INTER_DATE[1], MD_HESHIBI_INTER_DATE[2],MD_HESHIBI_INTER_DATE[3] );
	
	if lastday ~= today then
		return 0
	end

	local daycount = GetQuestData(sceneId, selfId, MD_HESHIBI_INTER_DAYCOUNT[1], MD_HESHIBI_INTER_DAYCOUNT[2],MD_HESHIBI_INTER_DAYCOUNT[3] );

	return daycount;

	

end

---------------------------------------------------------------------------------------------------
--设置当天次数
---------------------------------------------------------------------------------------------------
function x700014_SetDayCount(sceneId, selfId)

	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, MD_HESHIBI_INTER_DATE[1], MD_HESHIBI_INTER_DATE[2], MD_HESHIBI_INTER_DATE[3])

	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_HESHIBI_INTER_DATE[1], MD_HESHIBI_INTER_DATE[2], MD_HESHIBI_INTER_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_HESHIBI_INTER_DAYCOUNT[1], MD_HESHIBI_INTER_DAYCOUNT[2], MD_HESHIBI_INTER_DAYCOUNT[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, MD_HESHIBI_INTER_DAYCOUNT[1], MD_HESHIBI_INTER_DAYCOUNT[2], MD_HESHIBI_INTER_DAYCOUNT[3])
		SetQuestData(sceneId, selfId, MD_HESHIBI_INTER_DAYCOUNT[1], MD_HESHIBI_INTER_DAYCOUNT[2], MD_HESHIBI_INTER_DAYCOUNT[3], daycount+1)
	end
	
	
	
end