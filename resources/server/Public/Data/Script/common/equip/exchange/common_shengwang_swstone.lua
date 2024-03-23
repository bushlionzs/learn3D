--声望兑换冥界声望石

x570042_g_ScriptId 					= 570042

x570042_g_LevelMin					= 1
x570042_g_LevelMax					= 100


x570042_g_ItemId					= 11000203
x570042_g_NeedItemCount				= 1	
x570042_g_ExtraType					=	2 --1: 荣誉， 2： 声望， 3：威望， 4：帮贡
x570042_g_ExtraCount				=	5000 -- 所需荣誉/声望值
x570042_g_BonusItemId				= 11000508



x570042_g_MissionName				= "【兑换】冥界声望石"
x570042_g_EnterInfo					= "\n\t#G1#W个#G天传水晶#W和#G5000声望#W兑换1颗#G冥界声望石#W。"
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x570042_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	AddQuestNumText(sceneId, x570042_g_ScriptId, x570042_g_MissionName,3,1);
	
end

---------------------------------------------------------------------------------------------------
--进入副本文字显示
---------------------------------------------------------------------------------------------------
function x570042_DispatchEnterInfo( sceneId, selfId, NPCId )

	BeginQuestEvent(sceneId)

		--任务信息
    local suipiannum = GetItemCount(sceneId, selfId, x570042_g_ItemId)         
    local shengwangnum = GetShengWang( sceneId, selfId )                               		
    local strText1 = format("\n\t您现在有#R%d#W个#G天传水晶#W！",suipiannum)   		
    local strText2 = format("\n\t您现在有#R%d#W点#G声望#W！",shengwangnum)        		
		
		AddQuestText(sceneId,"#Y"..x570042_g_MissionName)
		AddQuestText(sceneId,x570042_g_EnterInfo)
		  AddQuestText(sceneId,strText1)
      AddQuestText(sceneId,strText2)   
       AddQuestItemBonus(sceneId, x570042_g_BonusItemId,1)
		--AddQuestText(sceneId," ")

		


	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, NPCId, x570042_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--申请进入副本
---------------------------------------------------------------------------------------------------
function x570042_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--点确定后
----------------------------------------------------------------------------------------------
function x570042_ProcAccept( sceneId, selfId )

	x570042_OnRequestSubmit(sceneId, selfId);
end


-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x570042_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)

	if nFlag== nil then
		return
	end

	x570042_DispatchEnterInfo( sceneId, selfId, NPCId )
	
end


function x570042_OnRequestSubmit(sceneId, selfId)

	local iRet = x570042_CheckRequest(sceneId, selfId)

	if iRet>0 then
		x570042_OnApproveRequest(sceneId, selfId)
	end
end

function x570042_CheckRequest(sceneId, selfId)

	

	local ItemCnt = GetItemCount( sceneId, selfId, x570042_g_ItemId )

	if ItemCnt<x570042_g_NeedItemCount then
		local str =  format("天传水晶不足%d个！",x570042_g_NeedItemCount)

		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();

		DispatchQuestTips(sceneId, selfId);
		return 0;
	end

	local nExtraCount = 0

	if x570042_g_ExtraType==1 then		--荣誉
		nExtraCount = GetHonor(sceneId, selfId)
	elseif x570042_g_ExtraType==2 then	--声望
		nExtraCount = GetShengWang( sceneId, selfId )
    elseif x570042_g_ExtraType==3 then  --威望
        nExtraCount = GetPlayerGoodBadValue( sceneId, selfId )
    elseif x570042_g_ExtraType==4 then  --帮贡
        nExtraCount = GetGuildUserPoint( sceneId, selfId )
	else
		return 0;
	end

	if nExtraCount<x570042_g_ExtraCount then
		local str = ""

		if x570042_g_ExtraType==1 then		--荣誉
			str = format("您荣誉不足%d！",x570042_g_ExtraCount)
		elseif x570042_g_ExtraType==2 then	--声望
			str = format("您声望不足%d！",x570042_g_ExtraCount)
		elseif x570042_g_ExtraType==3 then  --威望
			str = format("您威望不足%d！",x570042_g_ExtraCount)
        elseif x570042_g_ExtraType==4 then  --帮贡
   			str = format("您帮贡不足%d！",x570042_g_ExtraCount)
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

function x570042_OnApproveRequest(sceneId, selfId)

	if x570042_GetBonus(sceneId, selfId)>0 then
		local iRet = DelItem(sceneId, selfId,x570042_g_ItemId,x570042_g_NeedItemCount)

	
		local nExtraCount;
		local iRet=-1;
		if x570042_g_ExtraType==1 then		--荣誉
			nExtraCount = GetHonor(sceneId, selfId)
			iRet = SubHonor(sceneId, selfId,x570042_g_ExtraCount)
		elseif x570042_g_ExtraType==2 then	--声望
			nExtraCount = GetShengWang( sceneId, selfId )
			iRet = SetShengWang(sceneId, selfId, nExtraCount-x570042_g_ExtraCount)
		elseif x570042_g_ExtraType==3 then  --威望
            nExtraCount = GetPlayerGoodBadValue(sceneId, selfId)
            SetPlayerGoodBadValue(sceneId, selfId, nExtraCount-x570042_g_ExtraCount)            
        elseif x570042_g_ExtraType==4 then  --帮贡
            nExtraCount = GetGuildUserPoint( sceneId, selfId )
            SubGuildUserPoint(sceneId,selfId,x570042_g_ExtraCount)
		else
			return 0;
		end

		
		--if iRet>0 then

			
		--end
	end
		
	
	
end


function x570042_GetBonus(sceneId, selfId)
	BeginAddItem(sceneId)
	AddBindItem( sceneId, x570042_g_BonusItemId, 1 )
	
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

