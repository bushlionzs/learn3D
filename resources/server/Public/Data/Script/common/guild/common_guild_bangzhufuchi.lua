--desc  : "帮主扶持计划"

x300972_g_ScriptId 					= 	300972                  --脚本ID
x300972_g_Title						=  "【帮会】帮会发展基金" 
x300972_g_BONUS_TBL_IDX = 
{
1000000 ,
2000000,
3000000,
5000000,
7000000,
10000000,
15000000,
20000000,
25000000,
30000000,
35000000,
40000000,
50000000,
60000000,
70000000,
80000000,
90000000,
100000000
} 
x300972_g_BONUS_TBL = 
{
100000,
200000,
300000,
400000,
560000,
800000,
1000000,
1200000,
1500000,
1800000,
2100000,
2400000,
2800000,
3300000,
3800000,
4300000,
4800000,
5300000
}

x300972_g_Quest_Max_Count = 1 
x300972_g_GameId = 1057
 

function x300972_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	if GetGameOpenById(x300972_g_GameId) ~= 1 then
		return 0
	end

	if GetGuildID(sceneId, selfId) == -1 then
		--未加入帮会
		return 0
	end
	
	local pos = GetGuildOfficial(sceneId, selfId)
	if pos ~= 5 then
		return 0
	end
	AddQuestNumText(sceneId,x300972_g_ScriptId,x300972_g_Title, 3, -1)	
end


--选中任务
function x300972_ProcEventEntry( sceneId, selfId, NPCId, MissionId,nExtIdx )
	--PrintNum(nExtIdx)
	if nExtIdx == -1 then
						--是否为帮主
						local pos = GetGuildOfficial(sceneId, selfId)
						--PrintNum(pos)
						if pos ~= 5 then
												BeginQuestEvent(sceneId)
												AddQuestText(sceneId,"很抱歉，只有帮主才能领取帮会发展基金")
												EndQuestEvent(sceneId)
												--DispatchQuestEventList(sceneId, selfId, NPCId)       
												DispatchQuestInfo(sceneId, selfId, NPCId, x300972_g_ScriptId, -1,  0)
												Msg2Player(sceneId,selfId,"很抱歉，只有帮主才能领取帮会发展基金",8,2)	
												return
						end
						
						local nGuildID = GetGuildID(sceneId,selfId)
						
						local year, curMonth,  day = GetYearMonthDay()
						curMonth = year*100 + curMonth
						local sysCurMonth = GetGuildParam(nGuildID, GD_GUILD_CURMONTH)
						if curMonth ~= sysCurMonth then --跨月了,数据平移
						
									local nCurMonth = GetGuildParam(nGuildID, GD_GUILD_CURMONTH)
									local nCurMoney = GetGuildParam(nGuildID, GD_GUILD_CURMONTH_GUILD_MEMBER_MONEY)
									
									SetGuildParam(nGuildID,GD_GUILD_CURMONTH,curMonth)
									SetGuildParam(nGuildID,GD_GUILD_CURMONTH_GUILD_MEMBER_MONEY,0)					--本月重新开始计算
									
									
									SetGuildParam(nGuildID,GD_GUILD_LASTMONTH,nCurMonth)
									SetGuildParam(nGuildID,GD_GUILD_LASTMONTH_GUILD_MEMBER_MONEY,nCurMoney )			        --设置上月的总金额						
						end
						
				

						
						--上月本帮会成员消费总额
						local nTotalLast = GetGuildParam(nGuildID,GD_GUILD_LASTMONTH_GUILD_MEMBER_MONEY) 
						
						--当月本帮会成员充值总额
						local nTotalNow = GetGuildParam(nGuildID,GD_GUILD_CURMONTH_GUILD_MEMBER_MONEY)  
						--PrintNum(nTotalNow)
						
						local nTotal   = GetGuildParam(nGuildID,GD_GUILD_LASTMONTH_GUILD_MEMBER_MONEY)  --获取上月月帮会成员的总的消费金额
						--PrintNum(nTotal)
						
						--显示领奖界面以及说明文字
						local nCur ,nIdx  =  x300972_GetBonus(sceneId, selfId,nTotalNow)
						local nNext =  x300972_GetBonus_NextMonth(sceneId, selfId,nIdx)
						local nNext2 = 0
						if nIdx < 18 then
												nNext2 =  x300972_g_BONUS_TBL[nIdx+1]
										
												local str_last = x300972_GetMoney_Liang(sceneId,nTotalLast)
												local str_now  = x300972_GetMoney_Liang(sceneId,nTotalNow)
												local str_cur = x300972_GetMoney_Liang(sceneId,nCur)
												local str_next = x300972_GetMoney_Liang(sceneId,nNext)
												local str_next2 = x300972_GetMoney_Liang(sceneId,nNext2)
												
												local nBindGold ,nIdx = x300972_GetBonus(sceneId, selfId,nTotal)
												local str_bind = x300972_GetMoney_Liang(sceneId,nBindGold)



												BeginQuestEvent(sceneId)
												AddQuestText(sceneId,"#Y"..x300972_g_Title)
												AddQuestText(sceneId,"\t帮会的发展，需要众人一心，和充足的资金。而常用的帮会召集令，天赋研发等等，都需要付出不菲的资金。\n\t帮会发展基金的目的正是为了帮会的持续发展，它来源于各位帮众每月的现金消费之和，每月底结算，帮主在本月结算之前都可以领取上月的基金。\n#B（此功能仅帮主可见）#W\n \n#Y本月领取：\n#W您#G本月#W可以领取到金卡#R"..str_bind.."#W\n \n#Y下月领取：#W\n您#G下月#W可以领取到金卡#R"..str_cur.."#W,如果#G本月#W帮众再消费现金#G"..str_next.."#W，您#G下月#W就可以领取#R"..str_next2.."#W金卡了。")
												--AddQuestNumText(sceneId,x300972_g_ScriptId,"领取帮主奖励",13,1)
												EndQuestEvent()
												--DispatchQuestEventList(sceneId, selfId, NPCId)			
												DispatchQuestInfo(sceneId, selfId, NPCId, x300972_g_ScriptId, -1,  0)
							
							
						else
												nNext2 =  x300972_g_BONUS_TBL[nIdx]
									
																			
												local str_last = x300972_GetMoney_Liang(sceneId,nTotalLast)
												local str_now  = x300972_GetMoney_Liang(sceneId,nTotalNow)

												local str_cur = x300972_GetMoney_Liang(sceneId,nCur)
												local str_next = x300972_GetMoney_Liang(sceneId,nNext)
												local str_next2 = x300972_GetMoney_Liang(sceneId,nNext2)
												
												local nBindGold ,nIdx = x300972_GetBonus(sceneId, selfId,nTotal)
												local str_bind = x300972_GetMoney_Liang(sceneId,nBindGold)



												BeginQuestEvent(sceneId)
												AddQuestText(sceneId,"#Y"..x300972_g_Title)
												AddQuestText(sceneId,"\t帮会的发展，需要众人一心，和充足的资金。而常用的帮会召集令，天赋研发等等，都需要付出不菲的资金。\n\t帮会发展基金的目的正是为了帮会的持续发展，它来源于各位帮众每月的现金消费之和，每月底结算，帮主在本月结算之前都可以领取上月的基金。\n#B（此功能仅帮主可见）#W\n \n#Y本月领取：\n#W您#G本月#W可以领取到金卡#R"..str_bind.."#W\n \n#Y下月领取：#W\n您#G下月#W可以领取到金卡#R"..str_cur.."")
												--AddQuestNumText(sceneId,x300972_g_ScriptId,"领取帮主奖励",13,1)
												EndQuestEvent()
												--DispatchQuestEventList(sceneId, selfId, NPCId)			
												DispatchQuestInfo(sceneId, selfId, NPCId, x300972_g_ScriptId, -1,  0)
												--DispatchQuestTips(sceneId,selfId)     
							
						end

	 end
	
end


function x300972_GetMoney_Liang(sceneId,nMoney)
			if nMoney <= 0 then
				local str = "0文"
				return str
			end
				
				
			local ding = floor(nMoney/(1000*1000))
			local liang = floor((nMoney-ding*1000*1000)/1000)
			local wen = nMoney-(ding*1000*1000+liang*1000)
			local str=""
			if ding>0 then
				str = str..format("%d锭",ding)
			end

			if liang>0 then
				str = str..format("%d两",liang)
			end

			if wen>0 then
				str = str..format("%d文",wen)
			end

			return str;
end


function x300972_GetBonus_NextMonth(sceneId, selfId,nIdx)
		local nGuildID = GetGuildID(sceneId,selfId)
		if nIdx < 18 then
			--PrintNum(GetGuildParam(nGuildID,GD_GUILD_CURMONTH_GUILD_MEMBER_MONEY))
			return x300972_g_BONUS_TBL_IDX[nIdx + 1] - GetGuildParam(nGuildID,GD_GUILD_CURMONTH_GUILD_MEMBER_MONEY)			
		else
			return x300972_g_BONUS_TBL_IDX[nIdx]
		end
		return 0
end



function x300972_GetBonus(sceneId, selfId,nTotal)
	if nTotal <= 0 then
		return 0,0
	end
	
	if nTotal < x300972_g_BONUS_TBL_IDX[1] then
		return 0 , 0
	end
	
	if nTotal >= x300972_g_BONUS_TBL_IDX[1] and nTotal < x300972_g_BONUS_TBL_IDX[2] then
		return x300972_g_BONUS_TBL[1] , 1
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[2] and nTotal < x300972_g_BONUS_TBL_IDX[3] then
		return x300972_g_BONUS_TBL[2] , 2
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[3] and nTotal < x300972_g_BONUS_TBL_IDX[4] then
		return x300972_g_BONUS_TBL[3] ,  3
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[4] and nTotal < x300972_g_BONUS_TBL_IDX[5] then
		return x300972_g_BONUS_TBL[4],  4
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[5] and nTotal < x300972_g_BONUS_TBL_IDX[6] then
		return x300972_g_BONUS_TBL[5], 5
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[6] and nTotal < x300972_g_BONUS_TBL_IDX[7] then
		return x300972_g_BONUS_TBL[6], 6
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[7] and nTotal < x300972_g_BONUS_TBL_IDX[8] then
		return x300972_g_BONUS_TBL[7], 7
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[8] and nTotal < x300972_g_BONUS_TBL_IDX[9] then
		return x300972_g_BONUS_TBL[8], 8
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[9] and nTotal < x300972_g_BONUS_TBL_IDX[10] then
		return x300972_g_BONUS_TBL[9], 9
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[10] and nTotal < x300972_g_BONUS_TBL_IDX[11] then
		return x300972_g_BONUS_TBL[10], 10
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[11] and nTotal < x300972_g_BONUS_TBL_IDX[12] then
		return x300972_g_BONUS_TBL[11], 11
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[12] and nTotal < x300972_g_BONUS_TBL_IDX[13] then
		return x300972_g_BONUS_TBL[12], 12
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[13] and nTotal < x300972_g_BONUS_TBL_IDX[14] then
		return x300972_g_BONUS_TBL[13], 13
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[14] and nTotal < x300972_g_BONUS_TBL_IDX[15] then
		return x300972_g_BONUS_TBL[14], 14
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[15] and nTotal < x300972_g_BONUS_TBL_IDX[16] then
		return x300972_g_BONUS_TBL[15], 15
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[16] and nTotal < x300972_g_BONUS_TBL_IDX[17] then
		return x300972_g_BONUS_TBL[16], 16
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[17] and nTotal < x300972_g_BONUS_TBL_IDX[18] then
		return x300972_g_BONUS_TBL[17], 17
	end
	if nTotal >= x300972_g_BONUS_TBL_IDX[18] then
		return x300972_g_BONUS_TBL[18], 18
	end	
	
	return  0, 0
end


--------------------------------------------------------------------------------------------------------------
-------------更新当本月领取奖励的次数
-------------from common_loulan_fangyuzhilu.lua
--------------------------------------------------------------------------------------------------------------
-----------function x300972_GetMonthCount(sceneId, selfId)
-----------	--PrintStr("x300980_GetDayCount")
-----------	if x300972_g_Quest_Max_Count > 0 then
-----------		local year, curMonth,  day = GetYearMonthDay()
-----------		local lastMonth			   = GetQuestData(sceneId, selfId, MD_LOULAN_GUILD_BANGZHUFUZHI_MONTH[1], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTH[2], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTH[3])
-----------		if curMonth ~= lastMonth then
-----------			return 0
-----------		end
-----------
-----------		local monthcount =  GetQuestData(sceneId, selfId, MD_LOULAN_GUILD_BANGZHUFUZHI_MONTHCOUNT[1], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTHCOUNT[2], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTHCOUNT[3])
-----------		return monthcount
-----------
-----------	end
-----------	return 0
-----------end



-----------------------------------------------`--------------------------------------------------------------
------------更新当本月领取上月奖励的次数
------------from common_loulan_fangyuzhilu.lua
-------------------------------------------------------------------------------------------------------------
----------function x300972_SetMonthCount(sceneId, selfId)
----------	local year, curMonth,  day = GetYearMonthDay()
----------	local lastMonth = GetQuestData(sceneId, selfId, MD_LOULAN_GUILD_BANGZHUFUZHI_MONTH[1], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTH[2], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTH[3])
----------	if curMonth ~= lastMonth then
----------		SetQuestData(sceneId, selfId, MD_LOULAN_GUILD_BANGZHUFUZHI_MONTH[1], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTH[2], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTH[3], curMonth)
----------		SetQuestData(sceneId, selfId, MD_LOULAN_GUILD_BANGZHUFUZHI_MONTHCOUNT[1], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTHCOUNT[2], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTHCOUNT[3], 1)		
----------	else
----------				
----------		local monthcount = GetQuestData(sceneId, selfId, MD_LOULAN_GUILD_BANGZHUFUZHI_MONTHCOUNT[1], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTHCOUNT[2], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTHCOUNT[3])
----------		SetQuestData(sceneId, selfId, MD_LOULAN_GUILD_BANGZHUFUZHI_MONTHCOUNT[1], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTHCOUNT[2], MD_LOULAN_GUILD_BANGZHUFUZHI_MONTHCOUNT[3], monthcount+1)		
----------	end
----------end


--**********************************
--接受
--**********************************
function x300972_ProcAccept( sceneId, selfId )
	--在此处检测条件
	--PrintStr("x300972_ProcAccept")

	--是否为帮主
	local pos = GetGuildOfficial(sceneId, selfId)
	--PrintNum(pos)
	if pos ~= 5 then
							return -1
	end

					
	--当月本帮会成员充值总额
	local nGuildID = GetGuildID(sceneId,selfId)
	--PrintNum(nGuildID)
	local nTotal    = GetGuildParam(nGuildID,GD_GUILD_LASTMONTH_GUILD_MEMBER_MONEY)  --获取上月月帮会成员的总的消费金额
	if nTotal <= 0 then
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"上月您的帮会成员的现金消费不足或者本帮帮主本月已经领取过一次，无法领取帮会发展基金")
							--DispatchQuestEventList(sceneId, selfId, NPCId)       
							EndQuestEvent(sceneId)
							DispatchQuestTips(sceneId, selfId)
							Msg2Player(sceneId,selfId,"上月您的帮会成员的现金消费不足或者本帮帮主本月已经领取过一次，无法领取帮会发展基金",8,2)
							return
	end

	
	--根据公式计算返还金卡
	--to be fixed!!!
	--不知道公式!!!	
	local nBindGold ,nIdx = x300972_GetBonus(sceneId, selfId,nTotal)
	if nBindGold == 0 then
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"#Y"..x300972_g_Title)
							AddQuestText(sceneId,"上月您的帮会成员的现金消费不足或者本帮帮主本月已经领取过一次，无法领取帮会发展基金")
							EndQuestEvent()
							--DispatchQuestInfo(sceneId, selfId, -1,x300972_g_ScriptId,-1,0) 
							DispatchQuestEventList(sceneId, selfId, -1) 
							
							Msg2Player(sceneId,selfId,"上月您的帮会成员的现金消费不足或者本帮帮主本月已经领取过一次，无法领取帮会发展基金",8,2)							
							return -1
	end

	--上个月清0
	--清0动作置于奖励金卡前面防止多次领取
	local year, curMonth,  day = GetYearMonthDay()
	curMonth = year*100 + curMonth
	SetGuildParam(nGuildID,GD_GUILD_LASTMONTH_GUILD_MEMBER_MONEY,0)
	SetGuildParam(nGuildID,GD_GUILD_LASTMONTH,curMonth)
	SetGuildParam(nGuildID,GD_GUILD_CURMONTH, curMonth)
	
				
	local moneymes = "返还金卡"
	--返还金卡
	local ret = AddMoney( sceneId, selfId, 3, nBindGold )
	if ret <= 0 then
							GamePlayScriptLog(sceneId, selfId, 1732) --领取失败
	else
							local nBindStr = x300972_GetMoney_Liang(sceneId,nBindGold)
							Msg2Player(sceneId, selfId,"成功领取帮会发展基金#R"..nBindStr.."金卡奖励", 8, 2);
							Msg2Player(sceneId, selfId,"成功领取帮会发展基金#R"..nBindStr.."金卡奖励", 8, 3)
							GamePlayScriptLog(sceneId, selfId, 1731) --领取成功
	end
	

	
end

function x300972_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end
--点击（确定）
function x300972_ProcQuestAccept( sceneId, selfId, NPCId )
	--PrintStr("x300972_ProcQuestAccept")
end


