----------------------------------------------------
-- 兑换钻石任务
----------------------------------------------------

x570017_g_ScriptId 					= 570017

x570017_g_LevelMin					= 60
x570017_g_LevelMax					= 100


x570017_g_ItemId					= 11990113
x570017_g_NeedItemCount				= 2	
x570017_g_ExtraType					=	3      --1: 荣誉， 2： 声望， 3：现银， 4：帮贡
x570017_g_ExtraCount				=	200000 -- 单位“文”
x570017_g_BonusItemId				= 11000221



x570017_g_MissionName				= "【兑换】炫彩钻石"
x570017_g_EnterInfo					= "\n\t2颗#G钻石原石#W和200两#G现银#W兑换1颗#G炫彩钻石#W。"
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x570017_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	AddQuestNumText(sceneId, x570017_g_ScriptId, x570017_g_MissionName,3,1);
	
end

---------------------------------------------------------------------------------------------------
--进入副本文字显示
---------------------------------------------------------------------------------------------------
function x570017_DispatchEnterInfo( sceneId, selfId, NPCId )

	BeginQuestEvent(sceneId)

		--任务信息
		
		local suipiannum = GetItemCount(sceneId, selfId, x570017_g_ItemId)         
		local xianyin  = GetMoney( sceneId, selfId , 0 )                      
		local strText1 = format("\n\t您现在有#R%d颗#W#G钻石原石#W！",suipiannum)   
		local strText2 = format("\n\t您现在有#R%d#W两#G现银#W！",xianyin/1000)     
		                                                                           
		AddQuestText(sceneId,"#Y"..x570017_g_MissionName)
		AddQuestText(sceneId,x570017_g_EnterInfo)
		
	  AddQuestText(sceneId,strText1)  
		AddQuestText(sceneId,strText2)  
		
   AddQuestItemBonus(sceneId, x570017_g_BonusItemId,1)
		--AddQuestText(sceneId," ")

		


	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, NPCId, x570017_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--申请进入副本
---------------------------------------------------------------------------------------------------
function x570017_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--点确定后
----------------------------------------------------------------------------------------------
function x570017_ProcAccept( sceneId, selfId )

	x570017_OnRequestSubmit(sceneId, selfId);
end


-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x570017_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)

	if nFlag== nil then
		return
	end

	x570017_DispatchEnterInfo( sceneId, selfId, NPCId )
	
end


function x570017_OnRequestSubmit(sceneId, selfId)

	local iRet = x570017_CheckRequest(sceneId, selfId)

	if iRet>0 then
		x570017_OnApproveRequest(sceneId, selfId)
	end
end

function x570017_CheckRequest(sceneId, selfId)

	

	local ItemCnt = GetItemCount( sceneId, selfId, x570017_g_ItemId )

	if ItemCnt<x570017_g_NeedItemCount then
		local str =  format("原石不足%d个！",x570017_g_NeedItemCount)

		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();

		DispatchQuestTips(sceneId, selfId);
		return 0;
	end

	local nExtraCount = 0

	if x570017_g_ExtraType==1 then		--荣誉
		nExtraCount = GetHonor(sceneId, selfId)
	elseif x570017_g_ExtraType==2 then	--声望
		nExtraCount = GetShengWang( sceneId, selfId )
    elseif x570017_g_ExtraType==3 then  --现银
        nExtraCount = GetMoney( sceneId, selfId ,0 )
    elseif x570017_g_ExtraType==4 then  --帮贡
        nExtraCount = GetGuildUserPoint( sceneId, selfId )
	else
		return 0;
	end

	if nExtraCount<x570017_g_ExtraCount then
		local str = ""

		if x570017_g_ExtraType==1 then		--荣誉
			str = format("您荣誉不足%d！",x570017_g_ExtraCount)
		elseif x570017_g_ExtraType==2 then	--声望
			str = format("您声望不足%d！",x570017_g_ExtraCount)
		elseif x570017_g_ExtraType==3 then  --现银
			str = format("您现银不足%d两！",x570017_g_ExtraCount/1000)
        elseif x570017_g_ExtraType==4 then  --帮贡
   			str = format("您帮贡不足%d！",x570017_g_ExtraCount)
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

function x570017_OnApproveRequest(sceneId, selfId)

	if x570017_GetBonus(sceneId, selfId)>0 then	
		local iRet = DelItem(sceneId, selfId,x570017_g_ItemId,x570017_g_NeedItemCount)


		local nExtraCount;
		local iRet=-1;
		if x570017_g_ExtraType==1 then		--荣誉
			nExtraCount = GetHonor(sceneId, selfId)
			iRet = SubHonor(sceneId, selfId,x570017_g_ExtraCount)
		elseif x570017_g_ExtraType==2 then	--声望
			nExtraCount = GetShengWang( sceneId, selfId )
			iRet = SetShengWang(sceneId, selfId, nExtraCount-x570017_g_ExtraCount)
		elseif x570017_g_ExtraType==3 then  --现银
            nExtraCount = GetMoney(sceneId, selfId, 0)
            CostMoney(sceneId, selfId, 0, x570017_g_ExtraCount)            
        elseif x570017_g_ExtraType==4 then  --帮贡
            nExtraCount = GetGuildUserPoint( sceneId, selfId )
            SubGuildUserPoint(sceneId,selfId,x570017_g_ExtraCount)
		else
			return 0;
		end

		
		--if iRet>0 then

			
		--end
	end
		
	
	
end


function x570017_GetBonus(sceneId, selfId)
	BeginAddItem(sceneId)
	AddBindItem( sceneId, x570017_g_BonusItemId, 1 )
	
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

