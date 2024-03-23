----------------------------------------------------
-- 收集神石
----------------------------------------------------

x310016_g_ScriptId 					= 310016

x310016_g_LevelMin					= 20
x310016_g_LevelMax					= 100
x310016_g_DayCountUntil				= 1

x310016_g_ItemIdList				= {12030328,12030329,12030330,12030331,12030332}

x310016_g_NeedItemCount				= 1	

x310016_g_MissionName				= "【个人】收集神石"
x310016_g_EnterInfo					= "\t听说了吗？从七月十四日开始，每天收集齐全#Y“成”，“吉”，“思”，“汗”，“China Joy”#W字样的神石交给我，每天可以完成一次，如果是第#R888#W次完成这个任务的幸运儿，你就有可能获得#Y显卡#W或#Y笔记本#W的超值大奖！\n\t当你接受了“#G天降宝箱#W”任务后，在就有可能从那些箱子中获得这些石头，在每天#Y12：30-24：00#W中，请带给我五块神石#Y\n“成”字神石 * 1\n“吉”字神石 * 1\n“思”字神石 * 1\n“汗”字神石 * 1\n“ChinaJoy”字神石 * 1#W"

x310016_g_BonusItem1 = 12030209
x310016_g_BonusItem2 = 11000300
x310016_g_BonusItem3 = 12010020
x310016_g_BonusItem4 = 12030200
x310016_g_BonusItem5 = 12041101

x310016_GameId = 1017


x310016_g_EnterTime					=	{                       --可进入时间段
											{min=12*60+30,  max=24*60+0},
											--{min=19*60+30,  max=20*60+0},
										}
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x310016_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	if GetGameOpenById(x310016_GameId)<=0 then
		return
	end

	local level = GetLevel( sceneId,selfId )
    if level < x310016_g_LevelMin then
       return
    end

    if level > x310016_g_LevelMax then
		 return
    end
	
	AddQuestNumText(sceneId, x310016_g_ScriptId, x310016_g_MissionName,5,1);
	
end

---------------------------------------------------------------------------------------------------
--进入副本文字显示
---------------------------------------------------------------------------------------------------
function x310016_DispatchEnterInfo( sceneId, selfId, NPCId )

	if GetGameOpenById(x310016_GameId)<=0 then
		x310016_ShowTips(sceneId, selfId,"此活动已关闭");
		return
	end

	local level = GetLevel(sceneId, selfId)
	local nYinkaBonus = level*600;
	local str1 = format("#Y%d银卡#W\n",nYinkaBonus)
 	local nExpBonus = level*4500;
	local str2 = format("#Y%d点的经验#W\n",nExpBonus) 
	local nShengWangBonus = 1000
	
	local str3 = format("#Y%d点声望#W\n", nShengWangBonus) 
	
	local str4 = "#Y@itemid_"..x310016_g_BonusItem1.."\n#W"
	local str5 = "#Y@itemid_"..x310016_g_BonusItem2.."\n#W"
	local str6 = "#Y@itemid_"..x310016_g_BonusItem3.."\n#W"
	local str7 = "#Y@itemid_"..x310016_g_BonusItem4.."\n#W"
	local str8 = "#Y@itemid_"..x310016_g_BonusItem5.."\n#W"
  local str9 ="\n你还可能获得以下奖励中的一种：\n"
	local str = "\n你会获得固定奖励：\n"..str2..str9..str1..str3..str4..str5..str6..str7..str8


	BeginQuestEvent(sceneId)
	
  
  	
		--任务信息
		AddQuestText(sceneId,"#Y"..x310016_g_MissionName)
		AddQuestText(sceneId,x310016_g_EnterInfo..str)
		--AddQuestText(sceneId,str)
		


	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, NPCId, x310016_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--申请进入副本
---------------------------------------------------------------------------------------------------
function x310016_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--点确定后
----------------------------------------------------------------------------------------------
function x310016_ProcAccept( sceneId, selfId )
	if GetGameOpenById(x310016_GameId)<=0 then
		x310016_ShowTips(sceneId, selfId,"此活动已关闭");
		return
	end

	x310016_OnRequestSubmit(sceneId, selfId);
end


-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x310016_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)
	if GetGameOpenById(x310016_GameId)<=0 then
		x310016_ShowTips(sceneId, selfId,"此活动已关闭");
		return
	end

	if nFlag== nil then
		return
	end

	x310016_DispatchEnterInfo( sceneId, selfId, NPCId )
	
end


function x310016_OnRequestSubmit(sceneId, selfId)

	local iRet = x310016_CheckRequest(sceneId, selfId)

	if iRet>0 then
		x310016_OnApproveRequest(sceneId, selfId)
	end
end

function x310016_CheckRequest(sceneId, selfId)

	if( x310016_g_DayCountUntil > 0 ) then
		
		if x310016_GetDayCount(sceneId, selfId) >= x310016_g_DayCountUntil then

			local str = format("每天只能完成%d次本任务，明天再来吧。",x310016_g_DayCountUntil)

			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			return 0;
		end
	end

	for i,item in x310016_g_ItemIdList do
		local ItemCnt = GetItemCount( sceneId, selfId, item )

		if ItemCnt<x310016_g_NeedItemCount then
			local str = format("你身上似乎没有@itemid_%d。",item)

			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, str);
			EndQuestEvent();

			DispatchQuestTips(sceneId, selfId);
			return 0;
		end
	end

	local hour,minute,sec =GetHourMinSec();

	local nowtime = hour*60+minute
	

	
	for i, item in x310016_g_EnterTime do
		if nowtime >= item.min and nowtime <= item.max then
			
			
			return 1;
			
		end
	end
	x310016_ShowTips(sceneId, selfId,"活动还没开始呢，请留意公告，耐心等待。");
	return 0;

end

function x310016_OnApproveRequest(sceneId, selfId)
	
	if GetGameOpenById(x310016_GameId)<=0 then
		x310016_ShowTips(sceneId, selfId,"此活动已关闭");
		return
	end

	local nRet1, iRandom = x310016_GetBonusTest(sceneId, selfId)

	if nRet1==0 then
		x310016_ShowTips(sceneId, selfId,"背包空间不足，无法获得奖励物品,请先整理背包");
	end
	
	local iRet=0;
	for i,item in x310016_g_ItemIdList do
		iRet = DelItem(sceneId, selfId,item,x310016_g_NeedItemCount)
	end



	if iRet>0 then
		x310016_GetBonus(sceneId, selfId,iRandom)
		x310016_SetDayCount(sceneId, selfId);

		
		local myGuid = GetPlayerGUID( sceneId,selfId )

		GetCountryQuestDataNM(sceneId,myGuid,0, CD_INDEX_CHINAJOY_DATE, x310016_g_ScriptId,-1,"OnGetChinaJoyDate",1)
	end
		
	
	
end


function x310016_OnGetChinaJoyDate(sceneId, selfId,MissionData,MissionId)

	
	
	local today = GetDayOfYear()

	

	if today~=MissionData then
		SetCountryQuestData(sceneId, 0, CD_INDEX_CHINAJOY_DATE,today)
		SetCountryQuestData(sceneId, 0, CD_INDEX_CHINAJOY_TIMES,0)
		
		local myGuid = GetPlayerGUID( sceneId,selfId )
		GetCountryQuestDataNM(sceneId,myGuid,0, CD_INDEX_CHINAJOY_TIMES, x310016_g_ScriptId,-1,"OnGetChinaJoyTimes",1)
		
	else
		local myGuid = GetPlayerGUID( sceneId,selfId )
		GetCountryQuestDataNM(sceneId,myGuid,0, CD_INDEX_CHINAJOY_TIMES, x310016_g_ScriptId,-1,"OnGetChinaJoyTimes",1)
	end

	
end

function x310016_OnGetChinaJoyTimes(sceneId, selfId,MissionData,MissionId)

	
	SetCountryQuestData(sceneId, 0, CD_INDEX_CHINAJOY_TIMES,MissionData+1)
	x310016_OnCompleteTimes(sceneId, selfId, MissionData+1)


	
end


function x310016_OnCompleteTimes(sceneId, selfId, nTimes)
	
	
	local guid = GetPlayerGUID( sceneId,selfId )	

	if nTimes==nil then
		return
	end

	
	if nTimes==888 then
		--写完成日志
		
		--local msg = "ChinaJoy Bonus: guid="..guid..",name="..GetName(sceneId,selfId)..",country="..GetCurCountry(sceneId,selfId)..",times="..nTimes

		--WriteLog(23,msg)
		GamePlayScriptLog(sceneId, selfId, 892)

		local str = GetName(sceneId,selfId).."恭喜！你是第"..nTimes.."个完成了收集神石任务的玩家，你很有可能获得显卡或笔记本的奖励哦！"

		LuaAllScenceM2Wrold (sceneId,str, 0, 1)

		x310016_ShowTips(sceneId, selfId,"恭喜你，你很有可能获得显卡或笔记本的奖励哦！");
	end

	--local msg = "ChinaJoy:"..guid..","..GetName(sceneId,selfId)..","..GetCurCountry(sceneId,selfId)..",times="..nTimes  -- 

	--WriteLog(1,msg)
	GamePlayScriptLog(sceneId, selfId, 882)

	
end

function x310016_GetBonusTest(sceneId, selfId)

	if GetGameOpenById(x310016_GameId)<=0 then
		x310016_ShowTips(sceneId, selfId,"此活动已关闭");
		return 0
	end

	local level = GetLevel(sceneId, selfId)



	local iRandom = random(1,1000)
	local nRet1 = 1;

	if iRandom<=370 then
		
	elseif iRandom<=780 then
		
	elseif iRandom<=820 then
		
		BeginAddItem(sceneId)
			AddBindItem( sceneId, x310016_g_BonusItem1, 1 )
		
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
		
		else
			nRet1 = 0
		end
	elseif iRandom<=821 then
		
		BeginAddItem(sceneId)
			AddBindItem( sceneId, x310016_g_BonusItem2, 1 )
		
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
		
		else
			nRet1 = 0
		end
	elseif iRandom<=850 then
		
		BeginAddItem(sceneId)
			AddItem( sceneId, x310016_g_BonusItem3, 1 )
		
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
		
		else
			nRet1 = 0
		end
	elseif iRandom<=900 then
		
		BeginAddItem(sceneId)
			AddItem( sceneId, x310016_g_BonusItem4, 1 )
		
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
		
		else
			nRet1 = 0
		end
	elseif iRandom<=1000 then
		
		BeginAddItem(sceneId)
			AddItem( sceneId, x310016_g_BonusItem5, 1 )
		
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
		
		else
			nRet1 = 0
		end

	
	end
	
	return nRet1,iRandom
end

function x310016_GetBonus(sceneId, selfId, iRandom)

	if GetGameOpenById(x310016_GameId)<=0 then
		x310016_ShowTips(sceneId, selfId,"此活动已关闭");
		return
	end

	local level = GetLevel(sceneId, selfId)

--	a、LV*600的银卡；      25%几率
--b、LV*4500的经验；     25%几率
--c、1000点声望；        25%几率
--d、1个江湖请柬（绑定）  4%几率   全服公告
--e、1个灵魂印记（绑定）  1%几率   全服公告
--f、1个小生命清露        5%几率   全服公告
--g、1个小喇叭            5%几率   全服公告
--h、1个修行草            10%几率  全服公告


	--local iRandom = 100

	if iRandom<=370 then

		local nYinkaBonus = level*600;
		if nYinkaBonus > 0 then
			AddMoney(sceneId, selfId, 1, nYinkaBonus)
			
			--local str = format("你获得%d的银卡",nYinkaBonus)
			--Msg2Player(sceneId,selfId,str,4,2)
		local nExpBonus = level*4500;
			AddExp(sceneId, selfId, nExpBonus);
			
			local str = format("你获得%d点的经验奖励",nExpBonus)
			Msg2Player(sceneId,selfId,str,4,2)			
		end
	elseif iRandom<=780 then
		local nShengWangBonus = 1000
		local nShengWang = GetShengWang( sceneId, selfId )
		nShengWang = nShengWang + nShengWangBonus
		SetShengWang( sceneId, selfId, nShengWang )
		
		local str = format("您获得了%d点声望值的奖励。", nShengWangBonus)
		Msg2Player(sceneId,selfId,str,4,2)
		Msg2Player(sceneId,selfId,str,4,3)
		local nExpBonus = level*4500;
			AddExp(sceneId, selfId, nExpBonus);
			
			local str = format("你获得%d点的经验奖励",nExpBonus)
			Msg2Player(sceneId,selfId,str,4,2)	
	elseif iRandom<=820 then
		
		BeginAddItem(sceneId)
			AddBindItem( sceneId, x310016_g_BonusItem1, 1 )
		
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
		
			AddItemListToPlayer(sceneId,selfId)
		

			x310016_ShowTips(sceneId, selfId, "获得奖励物品@itemid_"..x310016_g_BonusItem1)

			local str = "恭喜玩家"..GetName(sceneId, selfId).."在收集神石的活动中获得奖励物品@itemid_"..x310016_g_BonusItem1

			LuaAllScenceM2Wrold (sceneId,str, 0, 1)
					local nExpBonus = level*4500;
			AddExp(sceneId, selfId, nExpBonus);
			
			local str = format("你获得%d点的经验奖励",nExpBonus)
			Msg2Player(sceneId,selfId,str,4,2)	
		end
	elseif iRandom<=821 then
		
		BeginAddItem(sceneId)
			AddBindItem( sceneId, x310016_g_BonusItem2, 1 )
		
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
		
			AddItemListToPlayer(sceneId,selfId)
		

			x310016_ShowTips(sceneId, selfId, "获得奖励物品@itemid_"..x310016_g_BonusItem2)

			local str = "恭喜玩家"..GetName(sceneId, selfId).."在收集神石的活动中获得奖励物品@itemid_"..x310016_g_BonusItem2

			LuaAllScenceM2Wrold (sceneId,str, 0, 1)
					local nExpBonus = level*4500;
			AddExp(sceneId, selfId, nExpBonus);
			
			local str = format("你获得%d点的经验奖励",nExpBonus)
			Msg2Player(sceneId,selfId,str,4,2)	
		end
	elseif iRandom<=850 then
		
		BeginAddItem(sceneId)
			AddItem( sceneId, x310016_g_BonusItem3, 1 )
		
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
		
			AddItemListToPlayer(sceneId,selfId)
		

			x310016_ShowTips(sceneId, selfId, "获得奖励物品@itemid_"..x310016_g_BonusItem3)

			local str = "恭喜玩家"..GetName(sceneId, selfId).."在收集神石的活动中获得奖励物品@itemid_"..x310016_g_BonusItem3

			LuaAllScenceM2Wrold (sceneId,str, 0, 1)
					local nExpBonus = level*4500;
			AddExp(sceneId, selfId, nExpBonus);
			
			local str = format("你获得%d点的经验奖励",nExpBonus)
			Msg2Player(sceneId,selfId,str,4,2)	
		end
	elseif iRandom<=900 then
		
		BeginAddItem(sceneId)
			AddItem( sceneId, x310016_g_BonusItem4, 1 )
		
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
		
			AddItemListToPlayer(sceneId,selfId)
		

			x310016_ShowTips(sceneId, selfId, "获得奖励物品@itemid_"..x310016_g_BonusItem4)

			local str = "恭喜玩家"..GetName(sceneId, selfId).."在收集神石的活动中获得奖励物品@itemid_"..x310016_g_BonusItem4

			LuaAllScenceM2Wrold (sceneId,str, 0, 1)
					local nExpBonus = level*4500;
			AddExp(sceneId, selfId, nExpBonus);
			
			local str = format("你获得%d点的经验奖励",nExpBonus)
			Msg2Player(sceneId,selfId,str,4,2)	
		end
	elseif iRandom<=1000 then
		
		BeginAddItem(sceneId)
			AddItem( sceneId, x310016_g_BonusItem5, 1 )
		
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
		
			AddItemListToPlayer(sceneId,selfId)
		

			x310016_ShowTips(sceneId, selfId, "获得奖励物品@itemid_"..x310016_g_BonusItem5)

			local str = "恭喜玩家"..GetName(sceneId, selfId).."在收集神石的活动中获得奖励物品@itemid_"..x310016_g_BonusItem5

			LuaAllScenceM2Wrold (sceneId,str, 0, 1)
					local nExpBonus = level*4500;
			AddExp(sceneId, selfId, nExpBonus);
			
			local str = format("你获得%d点的经验奖励",nExpBonus)
			Msg2Player(sceneId,selfId,str,4,2)	
		end

	end
	
end

function x310016_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end


---------------------------------------------------------------------------------------------------
--取得当前次数
---------------------------------------------------------------------------------------------------
function x310016_GetDayCount(sceneId, selfId)



	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, MD_CHINAJOY_DATE[1], MD_CHINAJOY_DATE[2],MD_CHINAJOY_DATE[3] );
	
	if lastday ~= today then
		return 0
	end

	local daycount = GetQuestData(sceneId, selfId, MD_CHINAJOY_DAYCOUNT[1], MD_CHINAJOY_DAYCOUNT[2],MD_CHINAJOY_DAYCOUNT[3] );

	return daycount;

	

end

---------------------------------------------------------------------------------------------------
--设置当天次数
---------------------------------------------------------------------------------------------------
function x310016_SetDayCount(sceneId, selfId)

	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, MD_CHINAJOY_DATE[1], MD_CHINAJOY_DATE[2], MD_CHINAJOY_DATE[3])

	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_CHINAJOY_DATE[1], MD_CHINAJOY_DATE[2], MD_CHINAJOY_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_CHINAJOY_DAYCOUNT[1], MD_CHINAJOY_DAYCOUNT[2], MD_CHINAJOY_DAYCOUNT[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, MD_CHINAJOY_DAYCOUNT[1], MD_CHINAJOY_DAYCOUNT[2], MD_CHINAJOY_DAYCOUNT[3])
		SetQuestData(sceneId, selfId, MD_CHINAJOY_DAYCOUNT[1], MD_CHINAJOY_DAYCOUNT[2], MD_CHINAJOY_DAYCOUNT[3], daycount+1)
	end
	
	
	
end