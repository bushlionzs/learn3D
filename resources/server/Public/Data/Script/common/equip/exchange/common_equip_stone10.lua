----------------------------------------------------
-- 和氏璧3环内嵌任务
----------------------------------------------------

x570019_g_ScriptId 					= 570019

x570019_g_LevelMin					= 60
x570019_g_LevelMax					= 160
x570019_g_DayCountUntil				= 1

x570019_g_ItemId					= 11990114
x570019_g_NeedItemCount				= 1	
x570019_g_BonusItemId				= 11990113
x570019_CSP_CURRENT_STEP			= 22
x570019_G_STEP						= 6
x570019_g_md_date					= MD_EQUIP_EXCHANGE1_DAY
x570019_g_md_daycount				= MD_EQUIP_EXCHANGE1_DAYCOUNT

x570019_g_MissionName				= "第六轮兑换[钻石原石]"
x570019_g_EnterInfo					= "\t1个#G次生钻石矿#W兑换1个#G钻石原石#W，\n\t#R每轮仅能兑换一次，请慎重选择兑换物品！"
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x570019_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	local level = GetLevel( sceneId,selfId )
    if level < x570019_g_LevelMin then
       return
    end

    if level > x570019_g_LevelMax then
		 return
    end

	local nCurrentGameStep = GetFubenData_Param(sceneId, x570019_CSP_CURRENT_STEP )
	if x570019_IsExchanged(sceneId, selfId) == 0  and x570019_G_STEP <= nCurrentGameStep then
		AddQuestNumText(sceneId, x570019_g_ScriptId, x570019_g_MissionName,3,1);
	end
	
end

function x570019_IsExchanged(sceneId, selfId)

	if( x570019_g_DayCountUntil > 0 ) then
		
		if x570019_GetDayCount(sceneId, selfId) >= x570019_g_DayCountUntil then

			return 1;
		end
	end
	return 0
	
end

---------------------------------------------------------------------------------------------------
--进入副本文字显示
---------------------------------------------------------------------------------------------------
function x570019_DispatchEnterInfo( sceneId, selfId, NPCId )

	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId,"#Y"..x570019_g_MissionName)
		AddQuestText(sceneId,x570019_g_EnterInfo)
        AddQuestItemBonus(sceneId, x570019_g_BonusItemId,1)
		--AddQuestText(sceneId," ")

		


	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, NPCId, x570019_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--申请进入副本
---------------------------------------------------------------------------------------------------
function x570019_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--点确定后
----------------------------------------------------------------------------------------------
function x570019_ProcAccept( sceneId, selfId )

	x570019_OnRequestSubmit(sceneId, selfId);
end


-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x570019_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)

	if nFlag== nil then
		return
	end

	x570019_DispatchEnterInfo( sceneId, selfId, NPCId )
	
end


function x570019_OnRequestSubmit(sceneId, selfId)

	local iRet = x570019_CheckRequest(sceneId, selfId)

	if iRet>0 then
		x570019_OnApproveRequest(sceneId, selfId)
	end
end

function x570019_CheckRequest(sceneId, selfId)

	if( x570019_g_DayCountUntil > 0 ) then
		
		if x570019_GetDayCount(sceneId, selfId) >= x570019_g_DayCountUntil then

			local str = format("本轮仅能兑换%d次",x570019_g_DayCountUntil)

			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			return 0;
		end
	end

--	local nCurrentGameStep = GetFubenData_Param(sceneId, x570019_CSP_CURRENT_STEP )
	
--	if nCurrentGameStep~=x570019_G_STEP then
--		local str = format("当前波数不是第%d波",x570019_G_STEP)
--
--		BeginQuestEvent(sceneId);
--			AddQuestText(sceneId, str);
--		EndQuestEvent();
--		DispatchQuestTips(sceneId, selfId);
--		return 0;
--	end

	local ItemCnt = GetItemCount( sceneId, selfId, x570019_g_ItemId )

	if ItemCnt<x570019_g_NeedItemCount then
		local str = format("所需任务道具不足%d个",x570019_g_NeedItemCount)

		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();

		DispatchQuestTips(sceneId, selfId);
		return 0;
	end

	return 1;
	
end

function x570019_OnApproveRequest(sceneId, selfId)

	if x570019_GetBonus(sceneId, selfId)>0 then
		local iRet = DelItem(sceneId, selfId,x570019_g_ItemId,x570019_g_NeedItemCount)

	
		
		x570019_SetDayCount(sceneId, selfId);
	end
		
	
	
end


function x570019_GetBonus(sceneId, selfId)
	BeginAddItem(sceneId)
	AddBindItem( sceneId, x570019_g_BonusItemId, 1 )
	
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
function x570019_GetDayCount(sceneId, selfId)



	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, x570019_g_md_date[1], x570019_g_md_date[2],x570019_g_md_date[3] );
	
	if lastday ~= today  and (lastday+1) ~= today then
		return 0
	end

	local daycount = GetQuestData(sceneId, selfId, x570019_g_md_daycount[1], x570019_g_md_daycount[2],x570019_g_md_daycount[3] );

	return daycount;

	

end

---------------------------------------------------------------------------------------------------
--设置当天次数
---------------------------------------------------------------------------------------------------
function x570019_SetDayCount(sceneId, selfId)

	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, x570019_g_md_date[1], x570019_g_md_date[2], x570019_g_md_date[3])

	if lastday ~= today  and (lastday+1) ~= today then
		SetQuestData(sceneId, selfId, x570019_g_md_date[1], x570019_g_md_date[2], x570019_g_md_date[3], today)
		SetQuestData(sceneId, selfId, x570019_g_md_daycount[1], x570019_g_md_daycount[2], x570019_g_md_daycount[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, x570019_g_md_daycount[1], x570019_g_md_daycount[2], x570019_g_md_daycount[3])
		SetQuestData(sceneId, selfId, x570019_g_md_daycount[1], x570019_g_md_daycount[2], x570019_g_md_daycount[3], daycount+1)
	end
	
	
	
end