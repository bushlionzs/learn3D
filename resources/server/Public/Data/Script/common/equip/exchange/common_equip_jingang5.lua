----------------------------------------------------
-- 兑换碧海金刚
----------------------------------------------------

x570069_g_ScriptId 					= 570069

x570069_g_LevelMin					= 75
x570069_g_LevelMax					= 100


x570069_g_ItemId1					= 11000218
x570069_g_NeedItemCount1				= 1	
x570069_g_ItemId2					= 11010014
x570069_g_NeedItemCount2				= 1	
x570069_g_BonusItemId				= 11000226



x570069_g_MissionName				= "【兑换】碧海金刚"
x570069_g_EnterInfo					= "\n\t1颗#G海蓝钻石#W和1个#G夜明珠#W兑换1颗#G碧海金刚#W。"
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x570069_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	AddQuestNumText(sceneId, x570069_g_ScriptId, x570069_g_MissionName,3,1);
	
end

---------------------------------------------------------------------------------------------------
--进入副本文字显示
---------------------------------------------------------------------------------------------------
function x570069_DispatchEnterInfo( sceneId, selfId, NPCId )

	BeginQuestEvent(sceneId)

		--任务信息
		local suipiannum = GetItemCount(sceneId, selfId, x570069_g_ItemId1)       
		local yemingzhu = GetItemCount(sceneId, selfId, x570069_g_ItemId2)              
		local strText1 = format("\n\t您现在有#R%d颗#W#G海蓝钻石#W！",suipiannum) 
		local strText2 = format("\n\t您现在有#R%d颗#W#G夜明珠#W！",yemingzhu)     
		
		AddQuestText(sceneId,"#Y"..x570069_g_MissionName)
		AddQuestText(sceneId,x570069_g_EnterInfo)
		
		AddQuestText(sceneId,strText1)
		AddQuestText(sceneId,strText2) 
		
        AddQuestItemBonus(sceneId, x570069_g_BonusItemId,1)
		--AddQuestText(sceneId," ")

		


	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, NPCId, x570069_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--申请进入副本
---------------------------------------------------------------------------------------------------
function x570069_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--点确定后
----------------------------------------------------------------------------------------------
function x570069_ProcAccept( sceneId, selfId )

	x570069_OnRequestSubmit(sceneId, selfId);
end


-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x570069_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)

	if nFlag== nil then
		return
	end

	x570069_DispatchEnterInfo( sceneId, selfId, NPCId )
	
end


function x570069_OnRequestSubmit(sceneId, selfId)

	local iRet = x570069_CheckRequest(sceneId, selfId)

	if iRet>0 then
		x570069_OnApproveRequest(sceneId, selfId)
	end
end

function x570069_CheckRequest(sceneId, selfId)

	

	local ItemCnt = GetItemCount( sceneId, selfId, x570069_g_ItemId1 )

	if ItemCnt<x570069_g_NeedItemCount1 then
		local str =  format("海蓝钻石不足%d个！",x570069_g_NeedItemCount1)

		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();

		DispatchQuestTips(sceneId, selfId);
		return 0;
	end

	local ItemCnt = GetItemCount( sceneId, selfId, x570069_g_ItemId2 )

	if ItemCnt<x570069_g_NeedItemCount2 then
		local str =  format("夜明珠不足%d个！",x570069_g_NeedItemCount2)

		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();

		DispatchQuestTips(sceneId, selfId);
		return 0;
	end

	

	return 1;
	
end

function x570069_OnApproveRequest(sceneId, selfId)

	if x570069_GetBonus(sceneId, selfId)>0 then
		local iRet = DelItem(sceneId, selfId,x570069_g_ItemId1,x570069_g_NeedItemCount1)
    local iRet = DelItem(sceneId, selfId,x570069_g_ItemId2,x570069_g_NeedItemCount2)

	end
		
	
	
end


function x570069_GetBonus(sceneId, selfId)
	BeginAddItem(sceneId)
	AddBindItem( sceneId, x570069_g_BonusItemId, 1 )
	
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

