--幸运大礼包	
------------------------------------------------------------------------------------------
--一般物品的默认脚本

--脚本号

x418132_g_scriptId = 418132
x418132_g_MissionId = 10260
x418132_g_ItemId = 12030434
x418132_g_TimeOutMsg = "幸运大礼包只能在虎年正月使用，正月已过，礼包过期，已经销毁！"
x418132_g_NoTimes = "您的剩余次数不足！"

x418132_g_NormalItemNum		=   16	
x418132_g_NormalItemTab		=	{
									{	itemId = 12041101   , itemname = "修行草"		}, 
									{	itemId = 11000501  	, itemname = "紫檀木炭"		}, 
									{	itemId = 12030014  	, itemname = "轩尼诗理查"	}, 
									{	itemId = 12030013   , itemname = "芝华士"		}, 
									{	itemId = 12054300   , itemname = "还童书"		}, 
									{	itemId = 12041103   , itemname = "活力丹"		}, 
									{	itemId = 12030031   , itemname = "神行符"		}, 
									{	itemId = 12030016  	, itemname = "队伍召集令"	}, 	
									{	itemId = 12031019   , itemname = "烟花斩"		}, 
									{	itemId = 12031000  	, itemname = "爱情誓言"		}, 
									{	itemId = 12031001  	, itemname = "单凤求凰"		},
									{	itemId = 12031002  	, itemname = "五彩缤纷"		}, 
									{	itemId = 12031003  	, itemname = "芬芳四溢"		}, 
									{	itemId = 12031004  	, itemname = "火树银花"		}, 
									{	itemId = 12031005  	, itemname = "心心相印"		}, 
									{	itemId = 12031006  	, itemname = "一见钟情"		}
								}

x418132_g_YueBingItemTab	=	{
									{	itemId = 12030257	, level = 90, itemname = "九珍月饼"		},
									{	itemId = 12030256	, level = 80, itemname = "八宝月饼"		},
									{	itemId = 12030255	, level = 70, itemname = "七星月饼"		}, 
									{	itemId = 12030254	, level = 60, itemname = "六味月饼"		}, 
									{	itemId = 12030253	, level = 50, itemname = "五仁月饼"		}, 
									{	itemId = 12030252 	, level = 40, itemname = "四喜月饼"		}, 
									{	itemId = 12030251  	, level = 30, itemname = "三财月饼"		}, 
									{	itemId = 12030250   , level = 20, itemname = "双祥月饼"		}
								}


x418132_g_MainMenuTab	=	{
								{	itemname = 	"钻石原石"		,	itemId = 11990113,						times = 25		},  
								{	itemname = 	"洗石剂"	,	itemId = 11000904,						times = 25		},  
								{	itemname = 	"掌门牌"	,	itemId1 = 10310025,	itemId2 = 10310026,	times = 25		},  
								{	itemname = 	"经验装"	,	itemId = 10300141,						times = 25		},  
								{	itemname = 	"月饼"		,											times = 25		},  
								{	itemname = 	"帮贡"		,											times = 25		},  
								{	itemname = 	"荣誉"		,											times = 25		},  
								{	itemname = 	"声望"		,											times = 25		}, 	
								{	itemname = 	"战场积分"	,											times = 25		},  
								{	itemname = 	"现银"		,											times = 25		}
							}

x418132_g_BangGongTabNum	=	4
x418132_g_BangGongTab		=	{200, 300, 400, 500}
x418132_g_RongYuTabNum		=	6
x418132_g_RongYuTab			=	{700, 800, 900, 1050, 1150, 1250}
x418132_g_ShenWangTabNum	=	9
x418132_g_ShenWangTab		=	{7500, 8500, 9500, 10500, 11500, 12000, 13000, 14000, 15000}
x418132_g_ZhanChanTabNum	=	5
x418132_g_ZhanChanTab		=	{150, 175, 200, 225, 250}
x418132_g_XianYinTabNum		=	5
x418132_g_XianYinTab		=	{150000, 175000, 200000, 225000, 250000}

--**********************************
--事件交互入口
--**********************************
function x418132_SetLeaveTimes( sceneId, selfId, MdIndex, MdData )
	if MdIndex == 1 then
		SetQuestData(sceneId, selfId, MD_XINGYUN_ZUANSHI[1], MD_XINGYUN_ZUANSHI[2],MD_XINGYUN_ZUANSHI[3], MdData ) 
	elseif MdIndex == 2 then
		SetQuestData(sceneId, selfId, MD_XINGYUN_XISHIJI[1], MD_XINGYUN_XISHIJI[2],MD_XINGYUN_XISHIJI[3], MdData ) 
	elseif MdIndex == 3 then
		SetQuestData(sceneId, selfId, MD_XINGYUN_ZHANGMENPAI[1], MD_XINGYUN_ZHANGMENPAI[2],MD_XINGYUN_ZHANGMENPAI[3], MdData ) 
	elseif MdIndex == 4 then
		SetQuestData(sceneId, selfId, MD_XINGYUN_JINYANZHUANG[1], MD_XINGYUN_JINYANZHUANG[2],MD_XINGYUN_JINYANZHUANG[3], MdData ) 
	elseif MdIndex == 5 then
		SetQuestData(sceneId, selfId, MD_XINGYUN_YUEBING[1], MD_XINGYUN_YUEBING[2],MD_XINGYUN_YUEBING[3], MdData ) 
	elseif MdIndex == 6 then
		SetQuestData(sceneId, selfId, MD_XINGYUN_BANGGONG[1], MD_XINGYUN_BANGGONG[2],MD_XINGYUN_BANGGONG[3], MdData ) 
	elseif MdIndex == 7 then
		SetQuestData(sceneId, selfId, MD_XINGYUN_RONGYU[1], MD_XINGYUN_RONGYU[2],MD_XINGYUN_RONGYU[3], MdData ) 
	elseif MdIndex == 8 then
		SetQuestData(sceneId, selfId, MD_XINGYUN_SHENGWANG[1], MD_XINGYUN_SHENGWANG[2],MD_XINGYUN_SHENGWANG[3], MdData ) 
	elseif MdIndex == 9 then
		SetQuestData(sceneId, selfId, MD_XINGYUN_ZHANCHANG[1], MD_XINGYUN_ZHANCHANG[2],MD_XINGYUN_ZHANCHANG[3], MdData ) 
	elseif MdIndex == 10 then
		SetQuestData(sceneId, selfId, MD_XINGYUN_XIANYIN[1], MD_XINGYUN_XIANYIN[2],MD_XINGYUN_XIANYIN[3], MdData ) 
	end
end
function x418132_GetLeaveTimes( sceneId, selfId, MdIndex )
	if MdIndex == 1 then
		return GetQuestData(sceneId, selfId, MD_XINGYUN_ZUANSHI[1], MD_XINGYUN_ZUANSHI[2],MD_XINGYUN_ZUANSHI[3]) 
	elseif MdIndex == 2 then
		return GetQuestData(sceneId, selfId, MD_XINGYUN_XISHIJI[1], MD_XINGYUN_XISHIJI[2],MD_XINGYUN_XISHIJI[3]) 
	elseif MdIndex == 3 then
		return GetQuestData(sceneId, selfId, MD_XINGYUN_ZHANGMENPAI[1], MD_XINGYUN_ZHANGMENPAI[2],MD_XINGYUN_ZHANGMENPAI[3]) 
	elseif MdIndex == 4 then
		return GetQuestData(sceneId, selfId, MD_XINGYUN_JINYANZHUANG[1], MD_XINGYUN_JINYANZHUANG[2],MD_XINGYUN_JINYANZHUANG[3]) 
	elseif MdIndex == 5 then
		return GetQuestData(sceneId, selfId, MD_XINGYUN_YUEBING[1], MD_XINGYUN_YUEBING[2],MD_XINGYUN_YUEBING[3]) 
	elseif MdIndex == 6 then
		return GetQuestData(sceneId, selfId, MD_XINGYUN_BANGGONG[1], MD_XINGYUN_BANGGONG[2],MD_XINGYUN_BANGGONG[3]) 
	elseif MdIndex == 7 then
		return GetQuestData(sceneId, selfId, MD_XINGYUN_RONGYU[1], MD_XINGYUN_RONGYU[2],MD_XINGYUN_RONGYU[3]) 
	elseif MdIndex == 8 then
		return GetQuestData(sceneId, selfId, MD_XINGYUN_SHENGWANG[1], MD_XINGYUN_SHENGWANG[2],MD_XINGYUN_SHENGWANG[3]) 
	elseif MdIndex == 9 then
		return GetQuestData(sceneId, selfId, MD_XINGYUN_ZHANCHANG[1], MD_XINGYUN_ZHANCHANG[2],MD_XINGYUN_ZHANCHANG[3]) 
	elseif MdIndex == 10 then
		return GetQuestData(sceneId, selfId, MD_XINGYUN_XIANYIN[1], MD_XINGYUN_XIANYIN[2],MD_XINGYUN_XIANYIN[3]) 
	end
	return 0
end
function x418132_IsSkillLikeScript( sceneId, selfId)
	return 1; --这个脚本需要动作支持
end
function x418132_CancelImpacts( sceneId, selfId)
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end
function x418132_OnConditionCheck( sceneId, selfId)
	--校验使用的物品
	if( 1~=VerifyUsedItem( sceneId, selfId) ) then
		return 0
	end

	return 1; --不需要任何条件，并且始终返回1。
end

--**********************************
--消耗检测及处理入口：
--系统会在技能消耗的时间点调用这个接口，并根据这个函数的返回值确定以后的流程是否执行。
--返回1：消耗处理通过，可以继续执行；返回0：消耗检测失败，中断后续执行。
--注意：这不光负责消耗的检测也负责消耗的执行。
--**********************************
function x418132_OnDeplete( sceneId, selfId)
    -- if DepletingUsedItem( sceneId, selfId) == 1 then
        -- return 1;
    -- end

    return 1
end
function x418132_OnActivateOnce( sceneId, selfId, impactId)
	CallScriptFunction( 418132, "ProcEnumEvent", sceneId, selfId, selfId, 0)
end

--**********************************
--引导心跳处理入口：
--引导技能会在每次心跳结束时调用这个接口。
--返回：1继续下次心跳；0：中断引导。
--注：这里是技能生效一次的入口
--**********************************
function x418132_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end


function x418132_ProcEventEntry( sceneId, selfId, targetId, scriptid, extid)


		--print("1   ----------------------------      extid=  "..extid)
		local Times = x418132_GetLeaveTimes(sceneId, selfId, extid)
		Times = 25 - Times
		--print("\n------------------Times2="..Times)
		if Times <= 0 then
			Msg2Player( sceneId, selfId, x418132_g_NoTimes, 8, 2)
			--BeginQuestEvent( sceneId)
			--AddQuestText( sceneId, x418132_g_NoTimes )	
			--EndQuestEvent()
			--SetPlayerRuntimeData( sceneId, selfId, RD_VIP_BOX, extid)
			--DispatchQuestInfoNM( sceneId, selfId, targetId,x418132_g_scriptId,x418132_g_MissionId)
			return
		end
		--print("1    Times=      "..Times)
		BeginQuestEvent( sceneId)
		AddQuestText( sceneId, format( "\t您将进行#Y%s#W的幸运抽奖，您有可能获得目标道具，但也有可能获得其他道具，祝您中奖！\n\t您确定要开始幸运抽奖了吗？", x418132_g_MainMenuTab[ extid].itemname) )
		--AddQuestNumText(sceneId, x418132_g_MissionId, "#W确定",3,extid+10)
		if(extid == 3) then
			--print("!!!!!!!!!!!!!!!!")
			AddQuestRadioItemBonus( sceneId, x418132_g_MainMenuTab[ extid].itemId2, 1)
			AddQuestRadioItemBonus( sceneId, x418132_g_MainMenuTab[ extid].itemId1, 1)
		elseif(extid <= 4) then
			--print("2!!!!!!!!!!!!!!!!")
			AddQuestRadioItemBonus( sceneId, x418132_g_MainMenuTab[ extid].itemId, 1)
		end
		--print("!!!!!!!!!!!!!!!!extid="..extid)
		SetPlayerRuntimeData( sceneId, selfId, RD_VIP_BOX, extid)
		EndQuestEvent()
		DispatchQuestInfoNM( sceneId, selfId, targetId,x418132_g_scriptId,x418132_g_MissionId)


	
	--DispatchQuestInfoNM( sceneId, selfId, selfId, x418132_g_scriptId,)
	
end

function x418132_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)

	local dayTime = GetDayTime()
	--print(dayTime)
	if(dayTime > 10073) then  --2010.03.15
		if DepletingUsedItem( sceneId, selfId) == 1 then
			AddQuestText(sceneId,x418132_g_TimeOutMsg)
			Msg2Player(sceneId,selfId,x418132_g_TimeOutMsg,8,2)
			local i = 1
			while i <= 10 do 
				x418132_SetLeaveTimes( sceneId, selfId, i, 0)
				i = i + 1 
			end
		end
		return
    end	

	local Times = 0
	BeginQuestEvent(sceneId)
	AddQuestText( sceneId, "\t可以给你带来幸运的礼包。" )
	--AddQuestNumText(sceneId, x418132_g_scriptId, "fsafsd次", 3, 1)

	for i, s in x418132_g_MainMenuTab do
		
		
		--x418132_SetLeaveTimes(sceneId, selfId, i, 0)
		Times = x418132_GetLeaveTimes(sceneId, selfId, i)
		--print("Times = "..Times)
		Times = 25 - Times
		--Times = 10
		if(Times > 0) then
			AddQuestNumText(sceneId, x418132_g_MissionId, "#W我要"..x418132_g_MainMenuTab[i].itemname.."(剩余"..Times.."次)",3,i)
			--AddQuestNumText(sceneId, tonumber(x418132_g_scriptId), "fsafsd次", 3, i)
		else
			AddQuestNumText(sceneId, x418132_g_MissionId, "#cb4b4b4我要"..x418132_g_MainMenuTab[i].itemname.."(剩余0次)",3,i)
			--AddQuestText(sceneId,"\t#G"..s.itemname.."(0次)")
		end
	end

	EndQuestEvent( sceneId)

                                           
    DispatchQuestEventList( sceneId, selfId, selfId)
end

function x418132_GetGift( sceneId, selfId, index)

	--print("index="..index)
	if index == 1 then
		local rand = random( 1, 5)
		if(rand == 1) then
			return x418132_g_MainMenuTab[index].itemId,1
		else
			rand = random( 1, x418132_g_NormalItemNum)
			--print("rand="..rand)
			return x418132_g_NormalItemTab[rand].itemId,0
		end
	elseif index == 2 then
		local rand = random( 1, 5)
		if(rand == 1) then
			return x418132_g_MainMenuTab[index].itemId,1
		else
			
			rand = random( 1, x418132_g_NormalItemNum)
			--print("rand="..rand)
			return x418132_g_NormalItemTab[rand].itemId,0
		end
	elseif index == 3 then
		local rand = random( 1, 20)
		if rand == 1 then
			return x418132_g_MainMenuTab[index].itemId2,1
		elseif rand <= 5 then
			return x418132_g_MainMenuTab[index].itemId1,1
		else
			rand = random( 1, x418132_g_NormalItemNum)
			--print("rand="..rand)
			return x418132_g_NormalItemTab[rand].itemId,0
		end
	elseif index == 4 then
		local rand = random( 1, 4)
		if(rand == 1) then
			return x418132_g_MainMenuTab[index].itemId,1
		else
			rand = random( 1, x418132_g_NormalItemNum)
			return x418132_g_NormalItemTab[rand].itemId,0
		end
	elseif index == 5 then							--月饼
		local level = GetLevel(sceneId, selfId)
		for i, s in x418132_g_YueBingItemTab do
			if level >= s.level then
				return s.itemId,0
				--break
			end
		end
		return nil,0
	elseif index == 6 then							--帮贡
		local rand = random( 1, x418132_g_BangGongTabNum)
		return x418132_g_BangGongTab[rand],0
	elseif index == 7 then
		local rand = random( 1, x418132_g_RongYuTabNum)
		return x418132_g_RongYuTab[rand],0
	elseif index == 8 then
		local rand = random( 1, x418132_g_ShenWangTabNum)
		return x418132_g_ShenWangTab[rand],0
	elseif index == 9 then
		local rand = random( 1, x418132_g_ZhanChanTabNum)
		return x418132_g_ZhanChanTab[rand],0
	elseif index == 10 then
		local rand = random( 1, x418132_g_XianYinTabNum)
		return x418132_g_XianYinTab[rand],0
	end

end



function x418132_ProcQuestAccept( sceneId, selfId, targetId, missionId)
    -- 检查背包空间
	
    local index = GetPlayerRuntimeData( sceneId, selfId, RD_VIP_BOX)
	local value,broadcast = x418132_GetGift( sceneId, selfId, index)

	local Times = x418132_GetLeaveTimes(sceneId, selfId, index)
	--print("\n~~~~~~~~~~~~~~~~~Times="..Times)
	--	print("\n~~~~~~~~~~~~~~~~~index="..index)
	Times = 25 - Times
	--print("\n!!!!!!!!!!!!!Times="..Times)
	if Times <= 0 then
		return
	end
	local msg
	--print("accept!!!!!!!!!!!!!!!!! Times = "..Times)
	--print("accept!!!!!!!!!!!!!!!!! boardcast = "..broadcast.."         value="..value)
	if index <= 5 then
		if(value == nil) then
			Msg2Player( sceneId, selfId, "您级别不够，无法得到物品!", 8, 2)
			return
		end

	    
		local num = 1
		if index == 5 then
			num = random(8, 12)
		end
			
		
		if GetBagSpace(sceneId, selfId) <= 0 then
			--print(GetBagSpace(sceneId, selfId))
			Msg2Player( sceneId, selfId, "无法得到物品，请整理背包", 8, 2)
			--print("dddddd")
			return
		else
			--print("sssssss")
			--local del = DelItem(sceneId,selfId,x418132_g_ItemId,1)
			--print(del)
			--if del ~= 1 then
			--	return
			--end

			if DepletingUsedItem( sceneId, selfId) ~= 1 then
				return
			end

			BeginAddItem( sceneId)		
			AddBindItem( sceneId, value, num)
			if EndAddItem( sceneId, selfId) <= 0 then
				return
			end
			AddItemListToPlayer( sceneId, selfId)
		end
		

		
		if broadcast == 1 then
			local CounID = GetCurCountry(sceneId, selfId)
			local CountryName = GetCountryName(CounID)
			local Name =  GetName(sceneId, selfId)
			
			msg = format( "恭喜%s的%s在幸运大礼包抽奖中获得了#{_ITEM%d}!", CountryName, Name, value )
			LuaAllScenceM2Wrold( sceneId, msg, 5, 1)
			Msg2Player( sceneId, selfId, format( "恭喜你在幸运大礼包抽奖中获得了#{_ITEM%d}!", value), 8, 2)
		else
			if index == 5 then
				msg = format( "恭喜你在幸运大礼包抽奖中获得了%d个#{_ITEM%d}!", num, value)
			else
				msg = format( "恭喜你在幸运大礼包抽奖中获得了#{_ITEM%d}!", value)
			end
			Msg2Player( sceneId, selfId, msg, 8, 2)
		end
	elseif index == 6 then
		local guildId = GetGuildID(sceneId,selfId)
		if guildId < 0 then
			msg = format( "您没有帮会，无法获得帮贡!")
			Msg2Player( sceneId, selfId, msg, 8, 2)
			return
		end
		--local del = DelItem(sceneId,selfId,x418132_g_ItemId,1)
		--if del ~= 1 then
		--	return
		--end
		if DepletingUsedItem( sceneId, selfId) ~= 1 then
				return
		end
		AddGuildUserPoint(sceneId, selfId, value)
		msg = format( "恭喜你在幸运大礼包抽奖中获得了%d点帮贡!", value)
		Msg2Player( sceneId, selfId, msg, 8, 2)

	elseif index == 7 then
		--local rongyu = GetRongYu(sceneId, selfId)
		--print(rongyu)
		--print(value)
		--SetRongYu(sceneId, selfId, rongyu+value)
		--print(GetHonor(sceneId, selfId))
		
		if DepletingUsedItem( sceneId, selfId) ~= 1 then
			return
		end
		--local del = DelItem(sceneId,selfId,x418132_g_ItemId,1)
		--if del ~= 1 then
		--	return
		--end
		AddHonor(sceneId, selfId, value)
		msg = format( "恭喜你在幸运大礼包抽奖中获得了%d点荣誉!", value)
		Msg2Player( sceneId, selfId, msg, 8, 2)

	elseif index == 8 then
		--print("shenwang1")
		--local del = DelItem(sceneId,selfId,x418132_g_ItemId,1)
		--if del ~= 1 then
		--	return
		--end
		if DepletingUsedItem( sceneId, selfId) ~= 1 then
				return
		end
		local shenwang = GetShengWang(sceneId, selfId)
		--print("shenwang2")
		SetShengWang(sceneId, selfId, shenwang+value)
		--print("shenwang")
		msg = format( "恭喜你在幸运大礼包抽奖中获得了%d点声望!", value)
		Msg2Player( sceneId, selfId, msg, 8, 2)
		
	elseif index == 9 then
		--local del = DelItem(sceneId,selfId,x418132_g_ItemId,1)
		--if del ~= 1 then
		--	return
		--end
		if DepletingUsedItem( sceneId, selfId) ~= 1 then
				return
		end
		AddPVP2V2Mark(sceneId, selfId, value)
		msg = format( "恭喜你在幸运大礼包抽奖中获得了%d点战场积分!", value)
		Msg2Player( sceneId, selfId, msg, 8, 2)
	elseif index == 10 then
		--local del = DelItem(sceneId,selfId,x418132_g_ItemId,1)
		--if del ~= 1 then
		--	return
		--end
		if DepletingUsedItem( sceneId, selfId) ~= 1 then
				return
		end
		AddMoney(sceneId, selfId, 0, value)
		msg = format( "恭喜你在幸运大礼包抽奖中获得了%d文现银!", value)
		Msg2Player( sceneId, selfId, msg, 8, 2)
	end
	
	if broadcast ~= 1 then 
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,msg)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	end

	Times = Times -	1
	Times = 25 - Times
	x418132_SetLeaveTimes(sceneId, selfId, index, Times)


	GamePlayScriptLog( sceneId, selfId, 1412)

	--local del = DelItem(sceneId,selfId,x418132_g_ItemId,1)
    
end

