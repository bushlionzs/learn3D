----------------------------------------------------
-- 和氏璧3环内嵌任务
----------------------------------------------------

x570012_g_ScriptId 					= 570012

x570012_g_LevelMin					= 40
x570012_g_LevelMax					= 100


x570012_g_ItemId					= 11990112
x570012_g_NeedItemCount				= 4	
x570012_g_ExtraType					=	2 --1: 荣誉， 2： 声望
x570012_g_ExtraCount				=	2000 -- 所需荣誉/声望值
x570012_g_BonusItemId				= 11000216



x570012_g_MissionName				= "【兑换】国传晕光钻石"
x570012_g_EnterInfo					= "\t4个#G国传钻石碎片#W和2000#G声望#W\n\t兑换1个#G国传晕光钻石#W。"
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x570012_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	AddQuestNumText(sceneId, x570012_g_ScriptId, x570012_g_MissionName,3,1);
	
end

---------------------------------------------------------------------------------------------------
--进入副本文字显示
---------------------------------------------------------------------------------------------------
function x570012_DispatchEnterInfo( sceneId, selfId, NPCId )

	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId,"#Y"..x570012_g_MissionName)
		AddQuestText(sceneId,x570012_g_EnterInfo)
        AddQuestItemBonus(sceneId, x570012_g_BonusItemId,1)
		--AddQuestText(sceneId," ")

		


	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, NPCId, x570012_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--申请进入副本
---------------------------------------------------------------------------------------------------
function x570012_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--点确定后
----------------------------------------------------------------------------------------------
function x570012_ProcAccept( sceneId, selfId )

	x570012_OnRequestSubmit(sceneId, selfId);
end


-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x570012_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)

	if nFlag== nil then
		return
	end

	x570012_DispatchEnterInfo( sceneId, selfId, NPCId )
	
end


function x570012_OnRequestSubmit(sceneId, selfId)

	local iRet = x570012_CheckRequest(sceneId, selfId)

	if iRet>0 then
		x570012_OnApproveRequest(sceneId, selfId)
	end
end

function x570012_CheckRequest(sceneId, selfId)

	

	local ItemCnt = GetItemCount( sceneId, selfId, x570012_g_ItemId )

	if ItemCnt<x570012_g_NeedItemCount then
		local str =  format("碎片不足%d个！",x570012_g_NeedItemCount)

		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();

		DispatchQuestTips(sceneId, selfId);
		return 0;
	end

	local nExtraCount = 0

	if x570012_g_ExtraType==1 then		--荣誉
		nExtraCount = GetHonor(sceneId, selfId)
	elseif x570012_g_ExtraType==2 then	--声望
		nExtraCount = GetShengWang( sceneId, selfId )
	else
		return 0;
	end

	if nExtraCount<x570012_g_ExtraCount then
		local str = ""

		if x570012_g_ExtraType==1 then		--荣誉
			str = format("您荣誉不足%d！",x570012_g_ExtraCount)
		elseif x570012_g_ExtraType==2 then	--声望
			str = format("您声望不足%d！",x570012_g_ExtraCount)
		else
			return 0;
		end

		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();

		DispatchQuestTips(sceneId, selfId);
		return 0;
	end

	

	return 1;
	
end

function x570012_OnApproveRequest(sceneId, selfId)

	if x570012_GetBonus(sceneId, selfId)>0 then
		local iRet = DelItem(sceneId, selfId,x570012_g_ItemId,x570012_g_NeedItemCount)

		local nExtraCount;
		local iRet=-1;
		if x570012_g_ExtraType==1 then		--荣誉
			nExtraCount = GetHonor(sceneId, selfId)
			iRet = SubHonor(sceneId, selfId,x570012_g_ExtraCount)
		elseif x570012_g_ExtraType==2 then	--声望
			nExtraCount = GetShengWang( sceneId, selfId )
			iRet = SetShengWang(sceneId, selfId, nExtraCount-x570012_g_ExtraCount)
		else
			return 0;
		end

		
		--if iRet>0 then

			
		--end
	end
		
	
	
end


function x570012_GetBonus(sceneId, selfId)
	BeginAddItem(sceneId)
	AddBindItem( sceneId, x570012_g_BonusItemId, 1 )
	
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

