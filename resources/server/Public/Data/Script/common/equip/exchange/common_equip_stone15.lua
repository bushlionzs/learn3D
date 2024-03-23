----------------------------------------------------
-- 和氏璧3环内嵌任务
----------------------------------------------------

x570025_g_ScriptId 					= 570025

x570025_g_LevelMin					= 40
x570025_g_LevelMax					= 100
x570025_g_DayCountUntil				= 1

x570025_g_ItemId					= 11990114
x570025_g_NeedItemCount				= 1	
x570025_g_BonusItemId				= 11990112
x570025_CSP_CURRENT_STEP			= 22
x570025_G_STEP						= 7
x570025_g_md_date					= MD_EQUIP_EXCHANGE4_DAY
x570025_g_md_daycount				= MD_EQUIP_EXCHANGE4_DAYCOUNT

x570025_g_MissionName				= "第七轮兑换[国传钻石碎片]"
x570025_g_EnterInfo					= "\t1个#G国传钻石碎片劵#W兑换1个#G国传钻石碎片#W，\n\t#R每轮仅能兑换一次，请慎重选择兑换物品！"
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x570025_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	local level = GetLevel( sceneId,selfId )
    if level < x570025_g_LevelMin then
       return
    end

    if level > x570025_g_LevelMax then
		 return
    end

	local nCurrentGameStep = GetFubenData_Param(sceneId, x570025_CSP_CURRENT_STEP )
	
	if nCurrentGameStep==x570025_G_STEP then
		AddQuestNumText(sceneId, x570025_g_ScriptId, x570025_g_MissionName,3,1);
	end
	
end

---------------------------------------------------------------------------------------------------
--进入副本文字显示
---------------------------------------------------------------------------------------------------
function x570025_DispatchEnterInfo( sceneId, selfId, NPCId )

	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId,"#Y"..x570025_g_MissionName)
		AddQuestText(sceneId,x570025_g_EnterInfo)
        AddQuestItemBonus(sceneId, x570025_g_BonusItemId,1)
		--AddQuestText(sceneId," ")

		


	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, NPCId, x570025_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--申请进入副本
---------------------------------------------------------------------------------------------------
function x570025_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--点确定后
----------------------------------------------------------------------------------------------
function x570025_ProcAccept( sceneId, selfId )

	x570025_OnRequestSubmit(sceneId, selfId);
end


-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x570025_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)

	if nFlag== nil then
		return
	end

	x570025_DispatchEnterInfo( sceneId, selfId, NPCId )
	
end


function x570025_OnRequestSubmit(sceneId, selfId)

	local iRet = x570025_CheckRequest(sceneId, selfId)

	if iRet>0 then
		x570025_OnApproveRequest(sceneId, selfId)
	end
end

function x570025_CheckRequest(sceneId, selfId)

	if( x570025_g_DayCountUntil > 0 ) then
		
		if x570025_GetDayCount(sceneId, selfId) >= x570025_g_DayCountUntil then

			local str = format("本轮仅能兑换%d次",x570025_g_DayCountUntil)

			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			return 0;
		end
	end

	local nCurrentGameStep = GetFubenData_Param(sceneId, x570025_CSP_CURRENT_STEP )
	
	if nCurrentGameStep~=x570025_G_STEP then
		local str = format("当前波数不是第%d波",x570025_G_STEP)

		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		return 0;
	end

	local ItemCnt = GetItemCount( sceneId, selfId, x570025_g_ItemId )

	if ItemCnt<x570025_g_NeedItemCount then
		local str = format("所需任务道具不足%d个",x570025_g_NeedItemCount)

		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();

		DispatchQuestTips(sceneId, selfId);
		return 0;
	end

	return 1;
	
end

function x570025_OnApproveRequest(sceneId, selfId)

	if x570025_GetBonus(sceneId, selfId)>0 then	
		local iRet = DelItem(sceneId, selfId,x570025_g_ItemId,x570025_g_NeedItemCount)

	
		
		x570025_SetDayCount(sceneId, selfId);
	end
		
	
	
end


function x570025_GetBonus(sceneId, selfId)
	BeginAddItem(sceneId)
	AddBindItem( sceneId, x570025_g_BonusItemId, 1 )
	
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		AddItemListToPlayer(sceneId,selfId)
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"兑换成功！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 1;
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"物品栏已满，无法得到物品！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0;
	end
end


---------------------------------------------------------------------------------------------------
--取得当前次数
---------------------------------------------------------------------------------------------------
function x570025_GetDayCount(sceneId, selfId)



	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, x570025_g_md_date[1], x570025_g_md_date[2],x570025_g_md_date[3] );
	
	if lastday ~= today  and (lastday+1) ~= today then
		return 0
	end

	local daycount = GetQuestData(sceneId, selfId, x570025_g_md_daycount[1], x570025_g_md_daycount[2],x570025_g_md_daycount[3] );

	return daycount;

	

end

---------------------------------------------------------------------------------------------------
--设置当天次数
---------------------------------------------------------------------------------------------------
function x570025_SetDayCount(sceneId, selfId)

	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, x570025_g_md_date[1], x570025_g_md_date[2], x570025_g_md_date[3])

	if lastday ~= today  and (lastday+1) ~= today then
		SetQuestData(sceneId, selfId, x570025_g_md_date[1], x570025_g_md_date[2], x570025_g_md_date[3], today)
		SetQuestData(sceneId, selfId, x570025_g_md_daycount[1], x570025_g_md_daycount[2], x570025_g_md_daycount[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, x570025_g_md_daycount[1], x570025_g_md_daycount[2], x570025_g_md_daycount[3])
		SetQuestData(sceneId, selfId, x570025_g_md_daycount[1], x570025_g_md_daycount[2], x570025_g_md_daycount[3], daycount+1)
	end
	
	
	
end