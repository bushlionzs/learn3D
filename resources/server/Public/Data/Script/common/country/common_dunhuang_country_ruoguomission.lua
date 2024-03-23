--***********************
--Const
--***********************
-------------------------

--MisDescBegin


x310211_g_MissionId 				= 	7743                     --任务ID
x310211_g_ScriptId 					= 	310211                  --脚本ID
x310211_g_MissionKind 				= 	1                       --任务类型
x310211_g_LevelLess					= 	25                      --场景开放等级  <=0 表示不限制


x310211_g_MissionName				= 	"【个人】弱国任务"
x310211_g_MissionName1				= 	"这个......上算乾坤？"
x310211_g_MissionTarget				= 	"\t解决国家目前所遇到的麻烦，使国家早日强盛繁荣！"
x310211_g_MissionInfo				= 	""
x310211_g_ContinueInfo				= 	""
x310211_g_MissionCompleted			= 	""
x310211_g_MissionHelp				=	"根据情报，东瀛岛国的忍者们似乎在城外埋伏。\n\t（本任务每小时可以完成一次。）"          --任务提示信息

--目标
x310211_g_ExtTarget					=	{ {type=20,n=1,target="【个人】弱国任务"}}

--奖励

x310211_g_ExpBonus					= 	0;--x310211_AddExpAward               	--奖励：经验
x310211_g_BonusItem					=	{}	--奖励：物品

x310211_g_BonusMoney1               = 	0
x310211_g_BonusMoney2               =   0
x310211_g_BonusMoney3               =   0

x310211_g_BonusChoiceItem           =   {}


--MisDescEnd


x310211_g_DayCountLimited			=	3

x310211_g_EnterTime					=	{                       --接受任务的时间
											{min=1*60+0,  max=23*60+59},
										}


x310211_g_ReplyNpcId = 132021

x310211_g_GameId	= 1021






x310211_g_BonusChoiceItem2   = {}


-- 挖掘
x310211_g_ItemId_Caiji =	13011008
x310211_g_ItemCount_Caiji = 1

-- 收集
x310211_g_ShouJi_Count	= 17
x310211_g_ShouJi_list = {
							12010200,
							12020001,
							12020002,
							12020003,
							12020004,
							12020005,
							12020006,
							12010300,
							12052531,
							12052471,
							12052481,
							12052491,
							11000100,
							11000110,
							14030001,
							14030006,
							14030011

						}


x310211_g_NeedKillCount	= 20*4

x310211_g_GpTypeStart = 711



x310211_g_NpcId			= 4



function x310211_GetMissionId( sceneId, selfId )
	return x310211_g_MissionId
end

function x310211_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	if GetGameOpenById(x310211_g_GameId)<=0 then
		return
	end

	if IsPlayerStateNormal(sceneId,selfId ) <= 0 then
		return
	end

	local level = GetLevel( sceneId,selfId )
    if level < x310211_g_LevelLess then
       return
    end

	local myMissionId = x310211_GetMissionId( sceneId, selfId )
	
	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		local nCountry = GetCurCountry(sceneId, selfId)

		local nRank = GetCountryRank(nCountry)
		
		if nRank ==3 then
			AddQuestNumText(sceneId, myMissionId, x310211_g_MissionName,8,1);
		else
			return
		end
		
	else
		local state = GetQuestStateNM(sceneId, selfId, targetId, myMissionId);

		
		AddQuestNumText(sceneId, myMissionId, x310211_g_MissionName,state,state);

	end


	DispatchQuestEventList(sceneId, selfId, targetId)


	
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x310211_ProcEventEntry( sceneId, selfId, targetId, MissionId, nExt )
	
	if GetGameOpenById(x310211_g_GameId)<=0 then
		x310211_ShowTips(sceneId, selfId, "此活动未开启")
		return
	end

	local myMissionId = x310211_GetMissionId( sceneId, selfId )	
	
	

	
	
	
		
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		local nCountry = GetCurCountry(sceneId, selfId)

		local nRank = GetCountryRank(nCountry)
		
		if nRank ==3 then
			x310211_DispatchMissionInfo( sceneId, selfId, targetId, myMissionId, 0 )
		end
		
	else
		if nExt==7 then -- 任务完成
			x310211_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
			
			
		else
			
			x310211_DispatchContinueInfo( sceneId, selfId, targetId,myMissionId )
		end
	end
	
end


function x310211_ProcAcceptCheck(sceneId, selfId, targetId, MissionId )
	
	if GetGameOpenById(x310211_g_GameId)<=0 then
		
		return 0;
	end
	return 1;

end

function x310211_CheckRequest(sceneId, selfId)
	if GetGameOpenById(x310211_g_GameId)<=0 then
		x310211_ShowTips(sceneId, selfId, "此活动未开启")
		return 0
	end

	local myMissionId = x310211_GetMissionId( sceneId, selfId )

	if GetLevel(sceneId, selfId) <x310211_g_LevelLess then
		x310211_ShowTips(sceneId, selfId, "等级不足")
		return 0
	end

	local nCountry = GetCurCountry(sceneId, selfId)

	local nRank = GetCountryRank(nCountry)
	
	if nRank ~=3 then
		x310211_ShowTips(sceneId, selfId, "你所在国家不是弱国，不可以接此任务")
		return 0;
	end

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) > 0 then
		x310211_ShowTips(sceneId, selfId, "你已经有这个任务，请先完成这个任务")
		return 0;
	end
	
	--//检查进入时间
	local week = GetWeek()
	if week==1 then
		local bInTime = 0
		local hour,minute,sec =GetHourMinSec();
		local nowtime = hour*60+minute
		
		for i, item in x310211_g_EnterTime do
			if nowtime >= item.min and nowtime <= item.max then
				bInTime = 1
			end
		end

		if bInTime == 0 then
			x310211_ShowTips(sceneId, selfId, "很抱歉，排行榜更新期间不允许接弱国任务，请01:00后再来")
			return 0;
		end
	end
	--//检查进入时间end

	if x310211_g_DayCountLimited >0 then
		local nDayCount = x310211_GetDayCount(sceneId, selfId)
		if nDayCount>= x310211_g_DayCountLimited then
			x310211_ShowTips(sceneId, selfId, "很抱歉，您本周已经完成过三次【个人】弱国任务任务了，不能再来接取了！")
			return 0;
		end
	end

	

	return 1;

end



function x310211_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
	local day, week = GetWeek()
	if day == 0 then
        Msg2Player( sceneId, selfId, "很抱歉，周日不能接受【个人】弱国任务任务", 8, 3)
        return 0
    end

	if GetGameOpenById(x310211_g_GameId)<=0 then
		x310211_ShowTips(sceneId, selfId, "此活动未开启")
		return 0;
	end

	if x310211_CheckRequest(sceneId, selfId)<=0 then
		
		return 0;
	end

	local myMissionId = x310211_GetMissionId( sceneId, selfId )

	local missionType = x310211_GetMissionType(sceneId, selfId)


	if missionType==2 then
		local myGuid = GetPlayerGUID( sceneId,selfId )
		GetCountryQuestDataNM(sceneId,myGuid,0, CD_INDEX_RUOGUO_SHOUJI_DATE, x310211_g_ScriptId,-1,"OnGetRuoguoDate",1)
		return 1
	end

	--------------------------- add for Mission full check --------------
	local bFullMission = IsQuestFullNM(sceneId,selfId)
	
	if bFullMission>0 then
		x310211_ShowTips(sceneId, selfId, "任务已满，无法接受任务")
		return 0
	end
	---------------------------- add end -------------------------------


	


	

	local ret = AddQuest( sceneId, selfId, myMissionId, x310211_g_ScriptId, 1, 0, 1,0)-- 给玩家添加任务		
		
	if ret > 0 then
		local str = "您接受了任务："..x310211_g_MissionName;
		x310211_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)
		
		local myMissionId = x310211_GetMissionId( sceneId, selfId )
		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
		SetQuestByIndex( sceneId, selfId, misIndex, 5, 0 )

		x310211_GiveSubMission(sceneId, selfId, targetId, myMissionId,missionType,-1)
		GamePlayScriptLog(sceneId, selfId, 1271)
		return 1
	else
		
		x310211_ShowTips(sceneId, selfId, "接受任务错误")
	
	end


end

function x310211_GetMissionType(sceneId, selfId)

	local nLastFlag = GetQuestData(sceneId, selfId, MD_RUOGUO_NEW_TASK_FLAG[1], MD_RUOGUO_NEW_TASK_FLAG[2], MD_RUOGUO_NEW_TASK_FLAG[3])

	if nLastFlag==0 then
		
		return 1
	elseif nLastFlag==1 then
		return 2
	elseif nLastFlag==2 then
		return 3
	else
		
	end
	
	
  
end

function x310211_SaveMissionType(sceneId, selfId)

	local nLastFlag = GetQuestData(sceneId, selfId, MD_RUOGUO_NEW_TASK_FLAG[1], MD_RUOGUO_NEW_TASK_FLAG[2], MD_RUOGUO_NEW_TASK_FLAG[3])

	if nLastFlag<2 then
		
		SetQuestData(sceneId, selfId, MD_RUOGUO_NEW_TASK_FLAG[1], MD_RUOGUO_NEW_TASK_FLAG[2], MD_RUOGUO_NEW_TASK_FLAG[3],nLastFlag+1)
	else
		SetQuestData(sceneId, selfId, MD_RUOGUO_NEW_TASK_FLAG[1], MD_RUOGUO_NEW_TASK_FLAG[2], MD_RUOGUO_NEW_TASK_FLAG[3],0)
	end
	
	
  
end




function x310211_GiveSubMission(sceneId, selfId, targetId, MissionId, missionType,nItemIndex)
	
	if GetGameOpenById(x310211_g_GameId)<=0 then
		x310211_ShowTips(sceneId, selfId, "此活动未开启")
		return 0;
	end
	local myMissionId = x310211_GetMissionId( sceneId, selfId )

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 5, 1 )  --还没有答题
	SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )

	
	SetQuestByIndex( sceneId, selfId, misIndex, 1, missionType )
	SetQuestByIndex( sceneId, selfId, misIndex, 2, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 3, 0 )

	x310211_SaveMissionType(sceneId, selfId)

	
	if missionType==1 then
		local nLevel = GetLevel(sceneId, selfId)
		
		local nGpIndex =0
		if nLevel<30 then
			nGpIndex = 1
		elseif nLevel<40 then
			nGpIndex = 2
		elseif nLevel<50 then
			nGpIndex = 3
		elseif nLevel<60 then
			nGpIndex = 4
		elseif nLevel<70 then
			nGpIndex = 5
		else
			nGpIndex = 6
		end

		SetQuestByIndex( sceneId, selfId, misIndex, 3, nGpIndex )

		
	elseif missionType==2 then

		
		SetQuestByIndex( sceneId, selfId, misIndex, 4, nItemIndex )

		local nCount = 1

		if nItemIndex<=8 then
			nCount =3
		end

		nCount = nCount*4

		SetQuestByIndex( sceneId, selfId, misIndex, 3, nCount )
			



		x310211_ProcQuestItemChanged( sceneId, selfId, x310211_g_ShouJi_list[nItemIndex], myMissionId, -1, nCount)



		
		
	end

	if targetId~=nil  then

		if targetId>0 then
	
			x310211_ShowSubMission( sceneId, selfId, targetId,MissionId, nItemIndex )
		end
	end

	x310211_QuestLogRefresh( sceneId, selfId, myMissionId );


end



function x310211_OnGetRuoguoDate(sceneId, selfId,MissionData,MissionId)

	
	
	local thisweek = x310211_GetWeekOfYear()

	

	if thisweek~=MissionData then
		SetCountryQuestData(sceneId, 0, CD_INDEX_RUOGUO_SHOUJI_DATE,thisweek)

		local nItemIndex =random(1, x310211_g_ShouJi_Count)

		SetCountryQuestData(sceneId, 0, CD_INDEX_RUOGUO_SHOUJI_FLAG,nItemIndex)

		x310211_OnCompleteFlag(sceneId, selfId, nItemIndex)
		
	else
		local myGuid = GetPlayerGUID( sceneId,selfId )
		GetCountryQuestDataNM(sceneId,myGuid,0, CD_INDEX_RUOGUO_SHOUJI_FLAG, x310211_g_ScriptId,-1,"OnGetRuoguoShoujiFlag",1)
	end

	
end

function x310211_OnGetRuoguoShoujiFlag(sceneId, selfId,MissionData,MissionId)

	

	x310211_OnCompleteFlag(sceneId, selfId, MissionData)
	
end


function x310211_OnCompleteFlag(sceneId, selfId, nItemIndex)

	
	
	if nItemIndex<0 or nItemIndex>x310211_g_ShouJi_Count then
		return
	end

	if GetGameOpenById(x310211_g_GameId)<=0 then
		x310211_ShowTips(sceneId, selfId, "【个人】弱国任务未开启")
		return 0;
	end


	local missionType = x310211_GetMissionType(sceneId, selfId)

	if missionType~=2 then
		return
	end

	if x310211_CheckRequest(sceneId, selfId)<=0 then
		
		return 0;
	end

	local myMissionId = x310211_GetMissionId( sceneId, selfId )

	


	if IsHaveQuestNM( sceneId, selfId, myMissionId ) > 0 then
		return
	end

	--------------------------- add for Mission full check --------------
	local bFullMission = IsQuestFullNM(sceneId,selfId)
	
	if bFullMission>0 then
		x310211_ShowTips(sceneId, selfId, "任务已满，无法接受任务")
		return 0
	end
	---------------------------- add end -------------------------------

	
	

	

	local ret = AddQuest( sceneId, selfId, myMissionId, x310211_g_ScriptId, 1, 0, 1,0)-- 给玩家添加任务		
		
	if ret > 0 then
		local str = "您接受了任务："..x310211_g_MissionName;
		x310211_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)
		
		local myMissionId = x310211_GetMissionId( sceneId, selfId )
		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
		SetQuestByIndex( sceneId, selfId, misIndex, 5, 0 )

		x310211_GiveSubMission(sceneId, selfId, -1, myMissionId,missionType,nItemIndex)
		GamePlayScriptLog(sceneId, selfId, 1271)
		return 1
	else
		
		x310211_ShowTips(sceneId, selfId, "接受任务错误")
	
	end



end

function x310211_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x310211_ProcQuestAbandon( sceneId, selfId, MissionId )

	local myMissionId = x310211_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )


	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )


	

	local ret = DelQuestNM( sceneId, selfId, myMissionId )

	if ret>0 then

		local str = "您放弃了任务:"..x310211_g_MissionName;
	    x310211_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)

		if value2==1 then
		
			local Num = GetItemCount( sceneId, selfId, x310211_g_ItemId_Caiji )

			if Num>0 then
				DelItem(sceneId, selfId, x310211_g_ItemId_Caiji, Num);
			end	
		elseif value2==2 then
			--local nItemIndex =GetQuestParam( sceneId, selfId, misIndex, 4 )
			--local Num = GetItemCount( sceneId, selfId, x310211_g_ShouJi_list[nItemIndex] )
			
			--local nCount =GetQuestParam( sceneId, selfId, misIndex, 3 )

			--if Num>0 then
			--	DelItem(sceneId, selfId,  x310211_g_ShouJi_list[nItemIndex] , nCount);
			--end
			
		end

		x310211_SetDayCount(sceneId, selfId)

		
		
	else
		x310211_ShowTips(sceneId, selfId, "放弃任务失败")
	end

	
end



function x310211_ProcQuestSubmit( sceneId, selfId, targetId, selectRadioId, MissionId )
	
	
	
	if GetGameOpenById(x310211_g_GameId)<=0 then
		x310211_ShowTips(sceneId, selfId, "此活动未开启")
		return 0;
	end

	local day, week = GetWeek()
	if day == 0 then
        Msg2Player( sceneId, selfId, "很抱歉，周日不能交付【个人】弱国任务任务", 8, 3)
        return
    end

	local myMissionId = x310211_GetMissionId( sceneId, selfId )

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )


	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )

	local nItemIndex=-1
	local nCount = 0
	if value2==2 then
		nItemIndex =GetQuestParam( sceneId, selfId, misIndex, 4 )
		nCount =GetQuestParam( sceneId, selfId, misIndex, 3 )
	end
	
	if x310211_CheckSubmit(sceneId, selfId )>0 then
		
		local ret = DelQuestNM( sceneId, selfId, myMissionId )

		if ret>0 then

			local str = "您完成了任务:"..x310211_g_MissionName;
			x310211_ShowTips(sceneId, selfId, str)
			Msg2Player(sceneId,selfId,str,8,2)

			
			
			x310211_GiveReward(sceneId,selfId, value2,nItemIndex,nCount)


			x310211_SetDayCount(sceneId, selfId)
			x310211_SetDaySuccessCount(sceneId, selfId)


			GamePlayScriptLog(sceneId, selfId, 1272)
			
		else
			x310211_ShowTips(sceneId, selfId, "交任务失败")
		end
		
	end
end



function x310211_GiveReward(sceneId,selfId,value2, nExt, nExt2)
	
	if GetGameOpenById(x310211_g_GameId)<=0 then
		x310211_ShowTips(sceneId, selfId, "此活动未开启")
		return 0;
	end


	
	

	if value2==1 then
	
		local Num = GetItemCount( sceneId, selfId, x310211_g_ItemId_Caiji )

		if Num>0 then
			DelItem(sceneId, selfId, x310211_g_ItemId_Caiji, Num);
		end
	elseif value2==2 then
		
		local Num = GetItemCount( sceneId, selfId, x310211_g_ShouJi_list[nExt] )
		
		

		if Num>=nExt2 then

			DelItem(sceneId, selfId, x310211_g_ShouJi_list[nExt] , nExt2);
		end
		
	end
	

	local daySuccessCount = x310211_GetDaySuccessCount(sceneId, selfId)+1
	local level = GetLevel(sceneId, selfId)
	local exp1 = level * 10000*4
	local exp2 = level * 20000*4
	local exp3 = level * 30000*4
	if daySuccessCount==1 then
		AddExp(sceneId,selfId,exp1)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o您获得了#R经验"..exp1.."点#o的奖励");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
  		Msg2Player(sceneId,selfId,"#o您完成了【个人】弱国任务 任务，获得了#R经验"..exp1.."点#o的奖励",4,2)
	elseif daySuccessCount==2 then
		AddExp(sceneId,selfId,exp2)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o您获得了#R经验"..exp2.."点#o的奖励");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
  		Msg2Player(sceneId,selfId,"#o您完成了【个人】弱国任务 ，获得了#R经验"..exp2.."点#o的奖励",4,2)
	elseif daySuccessCount==3 then
		AddExp(sceneId,selfId,exp3)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o您获得了#R经验"..exp3.."点#o的奖励");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
  		Msg2Player(sceneId,selfId,"#o您完成了【个人】弱国任务任务，获得了#R经验"..exp3.."点#o的奖励",4,2)
		--AddExp(sceneId,selfId,500)  --额外获得的经验

	else
		return
	end

	
	

	
	
	
	
end



function x310211_CheckSubmit(sceneId, selfId )
	
	if GetGameOpenById(x310211_g_GameId)<=0 then
		x310211_ShowTips(sceneId, selfId, "此活动未开启")
		return 0;
	end

	local myMissionId = x310211_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )


	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	

	if (bCompleted)<=0 then
		return 0
	end

	if value2==1 then
		local Num = GetItemCount( sceneId, selfId, x310211_g_ItemId_Caiji )
			
		if Num>=x310211_g_ItemCount_Caiji then
			return 1
		
		end

	elseif value2==2 then
		
		local nItemIndex = GetQuestParam( sceneId, selfId, misIndex, 4 )
		local Num = GetItemCount( sceneId, selfId, x310211_g_ShouJi_list[nItemIndex] )

		local nCount = GetQuestParam( sceneId, selfId, misIndex, 3 )
		
		if  Num>=nCount then
			return 1
		end
		
		
	elseif value2==3 then
		local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )
		if value1>=x310211_g_NeedKillCount then
			return 1
		end
	end

	return 0;
end



---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x310211_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId, nExt )

	
	
	BeginQuestEvent(sceneId)

		
	
	AddQuestText(sceneId,"#Y"..x310211_g_MissionName)
	AddQuestText(sceneId,"\n\t#Y@myname#W我们的国家目前正在遭受内忧外患的折磨，这严重影响了国家的发展，使得国家的实力每况愈下，在四大王国中，我们目前的实力排在最后。\n\t当等级排行榜第一名达到#R70级#W时，会开启弱国任务，只有每个国民都行动起来，积极为国家做出自己的贡献，才是摆脱这种局面，将我国变为强国！\n\t为此，我这里有一些任务需要你去完成。\n\t#G（本任务一周可领取三次，周日不可领取或交付本任务。）")
	AddQuestText(sceneId," ")
	AddQuestText( sceneId,"#Y任务目标:")
			
	AddQuestText( sceneId,x310211_g_MissionTarget)
	AddQuestText(sceneId," ")

	--1、经验
	local level = GetLevel(sceneId, selfId)
	local nExpBonus = level*0;
	local daySuccessCount = x310211_GetDaySuccessCount(sceneId, selfId)+1
	--local level = GetLevel(sceneId, selfId)
	if daySuccessCount==1 then
		nExpBonus = level * 10000
	elseif daySuccessCount==2 then
		nExpBonus = level * 20000
	elseif daySuccessCount==3 then
		nExpBonus = level * 30000
	else
		--return
	end

	nExpBonus = nExpBonus*4
	
	if nExpBonus > 0 then
		AddQuestExpBonus( sceneId, nExpBonus)
	end

	

	EndQuestEvent()
	
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x310211_g_ScriptId, MissionId,0);
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x310211_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	local myMissionId = x310211_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x310211_g_MissionName)
		AddQuestText(sceneId," ")
		AddQuestText(sceneId,"\t您还没有完成本次任务，请赶快去完成吧！")
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x310211_g_ScriptId, MissionId,0);
	


end







---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x310211_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	local myMissionId = x310211_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x310211_g_MissionName)
		AddQuestText(sceneId,"\t#Y@myname#W，感谢你所做出的贡献，相信在大家的共同努力下，我们的国家一定会很快强盛起来。")
	
	
	
	--1、经验
	local level = GetLevel(sceneId, selfId)
	local nExpBonus = level*0;

	nExpBonus = nExpBonus*4
	
	if nExpBonus > 0 then
		AddQuestExpBonus( sceneId, nExpBonus)
	end

	
		
	EndQuestEvent()
	
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x310211_g_ScriptId, MissionId);

end


---------------------------------------------------------------------------------------------------
--向客户端发送题目
---------------------------------------------------------------------------------------------------
function x310211_ShowSubMission( sceneId, selfId, NPCId,MissionId, nExt )


	
	local myMissionId = x310211_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )


	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x310211_g_MissionName)
		
		if value2==1 then
			local str1 = " "

			local nGpIndex = GetQuestParam( sceneId, selfId, misIndex, 3)

			if nGpIndex==1 then
				str1 = "请到gp1寻找找寻这种珍贵药材"
			elseif nGpIndex==2 then
				str1 = "请到gp2寻找找寻这种珍贵药材" 
			elseif nGpIndex==3 then
				str1 = "请到gp3寻找找寻这种珍贵药材" 
			elseif nGpIndex==4 then
				str1 = "请到gp4寻找找寻这种珍贵药材" 
			elseif nGpIndex==5 then
				str1 = "请到gp5寻找找寻这种珍贵药材" 
			elseif nGpIndex==6 then
				str1 = "请到gp6寻找找寻这种珍贵药材" 
			else
				
			end
			AddQuestText(sceneId,str1)
		elseif value2==2 then
			local nItemIndex = GetQuestParam( sceneId, selfId, misIndex, 4 )
	

			
			local str = format("收集4个@itemid_%d",x310211_g_ShouJi_list[nItemIndex])

			
			AddQuestText(sceneId,str)
		elseif value2==3 then
			local str = "杀怪...."
			AddQuestText(sceneId,str)
		else
			return 0
		end
		
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x310211_g_ScriptId, myMissionId,0);
	


end







---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x310211_QuestLogRefresh( sceneId, selfId, MissionId)
	
	
		
	BeginQuestEvent(sceneId)	
			
		
	AddQuestLogCustomText( sceneId,
							"",						-- 标题
							x310211_GetMissionName(sceneId,selfId),        -- 任务名字
							x310211_GetMissionTask(sceneId,selfId),		--任务目标
							"@npc_"..x310211_GetReplyNpcId(sceneId,selfId),			--任务NPC
							x310211_GetMissionMethod(sceneId,selfId),               --任务攻略
							x310211_GetMissionText(sceneId,selfId),	--任务描述
							x310211_GetMissionHelp(sceneId,selfId)					--任务小提示
							)

	--1、经验
	local level = GetLevel(sceneId, selfId)
	local nExpBonus = level*0;
	local daySuccessCount = x310211_GetDaySuccessCount(sceneId, selfId)+1
	--local level = GetLevel(sceneId, selfId)
	if daySuccessCount==1 then
		nExpBonus = level * 10000
	elseif daySuccessCount==2 then
		nExpBonus = level * 20000
	elseif daySuccessCount==3 then
		nExpBonus = level * 30000
	else
		return
	end
	
	nExpBonus = nExpBonus*4

	if nExpBonus > 0 then
		AddQuestExpBonus( sceneId, nExpBonus)
	end

	
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	

end

function x310211_GetMissionName(sceneId,selfId)
	

	return x310211_g_MissionName;
end

function x310211_GetMissionTask(sceneId,selfId)
	local myMissionId = x310211_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	
	
	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )

	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )

	

	local strTable = "  ";
	local str1 = ""

	if value2==1 then
		local nGpIndex = GetQuestParam( sceneId, selfId, misIndex, 3)

		if nGpIndex==1 then
			str1 = "  请到外城寻找@npc_81010(%d/%d)"
		elseif nGpIndex==2 then
			str1 = "  请到外城寻找@npc_81011(%d/%d)" 
		elseif nGpIndex==3 then
			str1 = "  请到边塞寻找@npc_81012(%d/%d)" 
		elseif nGpIndex==4 then
			str1 = "  请到大都寻找@npc_81013(%d/%d)" 
		elseif nGpIndex==5 then
			str1 = "  请到威海港寻找@npc_85058(%d/%d)" 
		elseif nGpIndex==6 then
			str1 = "  请到威海港寻找@npc_85059(%d/%d)" 
		else
			
		end

		str1 = format(str1,value1,x310211_g_ItemCount_Caiji)

		
	elseif value2==2 then
		local nItemIndex = GetQuestParam( sceneId, selfId, misIndex, 4 )
		
		local nCount = GetQuestParam( sceneId, selfId, misIndex, 3 )
	
		if value1>=nCount then
			value1 = nCount
		else
			
		end
			
		str1 = format("  收集@itemid_%d(%d/%d)",x310211_g_ShouJi_list[nItemIndex],value1,nCount)
	elseif value2==3 then
		str1 = format("  杀死不低于自己等级的怪物(%d/%d)", value1, x310211_g_NeedKillCount)
	end

	if value1>=1 then
		str1 = "#G"..str1
	else
		str1 = "#W"..str1
	end

	return str1
end

function x310211_GetReplyNpcId(sceneId,selfId)
	return x310211_g_ReplyNpcId;
end

function x310211_GetMissionMethod(sceneId,selfId)
	local myMissionId = x310211_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )


	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )

	

	local strTable = "  ";
	local str1 = ""

	if value2==1 then

		local nGpIndex = GetQuestParam( sceneId, selfId, misIndex, 3)

		if nGpIndex==1 then
			str1 = "请到外城寻找@npc_81010"
		elseif nGpIndex==2 then
			str1 = "请到外城寻找@npc_81011" 
		elseif nGpIndex==3 then
			str1 = "请到边塞寻找@npc_81012" 
		elseif nGpIndex==4 then
			str1 = "请到大都寻找@npc_81013" 
		elseif nGpIndex==5 then
			str1 = "请到威海港寻找@npc_85058" 
		elseif nGpIndex==6 then
			str1 = "请到威海港寻找@npc_85059" 
		else
			
		end
		
	elseif value2==2 then
		local nItemIndex = GetQuestParam( sceneId, selfId, misIndex, 4 )
		
		local nCount = GetQuestParam( sceneId, selfId, misIndex, 3 )

			
		str1 = format("收集%d个@itemid_%d。",nCount,x310211_g_ShouJi_list[nItemIndex])
		--str1 = ""
		
	elseif value2==3 then
		str1 = "杀死不低于自己等级的怪物80只。"
	end

	return str1
end

function x310211_GetMissionText(sceneId,selfId)
	
	local myMissionId = x310211_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )


	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )

	

	local strTable = "  ";
	local str1 = ""

	if value2==1 then
		str1 = "\t国家现在急需一些珍贵的药材来配置良药，以治疗正在国内蔓延的一种疾病，我想这么有侠义心肠的你一定愿意帮我去寻找这些急需的药材吧。"
	elseif value2==2 then
		local nItemIndex = GetQuestParam( sceneId, selfId, misIndex, 4 )
	

			
		str1 = format("\t为了对抗外来的侵犯，国家急需一些补给物资来加强国防能力，请快去找些@itemid_%d捐献给国库。",x310211_g_ShouJi_list[nItemIndex])
		
	elseif value2==3 then
		str1 = "国家总是被一些怪人和怪兽骚扰，使国民生活在恐慌之中，请去好好教训下这些怪物，为民除害。"
	end
	
	return str1	
end

function x310211_GetMissionHelp(sceneId,selfId)
	local myMissionId = x310211_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )


	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )

	

	local strTable = "  ";
	local str1 = ""

	if value2==1 then
		
		local nGpIndex = GetQuestParam( sceneId, selfId, misIndex, 3)

		if nGpIndex==1 then
			str1 = "请在外城内找到国家所需要的药材"
		elseif nGpIndex==2 then
			str1 = "请在外城内找到国家所需要的药材" 
		elseif nGpIndex==3 then
			str1 = "请在边塞找到国家所需要的药材" 
		elseif nGpIndex==4 then
			str1 = "请在大都找到国家所需要的药材" 
		elseif nGpIndex==5 then
			str1 = "请在威海港找到国家所需要的药材" 
		elseif nGpIndex==6 then
			str1 = "请在威海港找到国家所需要的药材" 
		else
			
		end
	elseif value2==2 then
		local nItemIndex = GetQuestParam( sceneId, selfId, misIndex, 4 )
	

			
		str1 = format("@itemid_%d可以通过生活技能产出或从其他玩家那里购买获得。",x310211_g_ShouJi_list[nItemIndex])
	elseif value2==3 then
		str1 = "杀死大于等于自己等级的怪物即可。"
	end
	
	return str1
end



function x310211_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x310211_QuestLogRefresh( sceneId, selfId, MissionId );
end

--// system function start
function x310211_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	
	
	
	
	

	
end



---------------------------------------------------------------------------------------------------
--取得当前次数
---------------------------------------------------------------------------------------------------
function x310211_GetDayCount(sceneId, selfId)



	local thisweek = x310211_GetWeekOfYear()

	
	local lastweek = GetQuestData(sceneId, selfId, MD_RUOGUO_NEW_DATE[1], MD_RUOGUO_NEW_DATE[2],MD_RUOGUO_NEW_DATE[3] );
	

	if lastweek ~= thisweek then
		return 0
	end

	local weekcount = GetQuestData(sceneId, selfId, MD_RUOGUO_NEW_DAYCOUNT[1], MD_RUOGUO_NEW_DAYCOUNT[2],MD_RUOGUO_NEW_DAYCOUNT[3] );

	
	return weekcount;



	

end

---------------------------------------------------------------------------------------------------
--设置当天次数
---------------------------------------------------------------------------------------------------
function x310211_SetDayCount(sceneId, selfId)

	local thisweek = x310211_GetWeekOfYear()

	local lastweek = GetQuestData(sceneId, selfId, MD_RUOGUO_NEW_DATE[1], MD_RUOGUO_NEW_DATE[2], MD_RUOGUO_NEW_DATE[3])

	
	if lastweek ~= thisweek then
		SetQuestData(sceneId, selfId, MD_RUOGUO_NEW_DATE[1], MD_RUOGUO_NEW_DATE[2], MD_RUOGUO_NEW_DATE[3], thisweek)
		SetQuestData(sceneId, selfId, MD_RUOGUO_NEW_DAYCOUNT[1], MD_RUOGUO_NEW_DAYCOUNT[2], MD_RUOGUO_NEW_DAYCOUNT[3], 1)
		SetQuestData(sceneId, selfId, MD_RUOGUO_NEW_DAY_SUCCESS_COUNT[1], MD_RUOGUO_NEW_DAY_SUCCESS_COUNT[2], MD_RUOGUO_NEW_DAY_SUCCESS_COUNT[3], 0)
	else
		local weekcount = GetQuestData(sceneId, selfId, MD_RUOGUO_NEW_DAYCOUNT[1], MD_RUOGUO_NEW_DAYCOUNT[2], MD_RUOGUO_NEW_DAYCOUNT[3])
		SetQuestData(sceneId, selfId, MD_RUOGUO_NEW_DAYCOUNT[1], MD_RUOGUO_NEW_DAYCOUNT[2], MD_RUOGUO_NEW_DAYCOUNT[3], weekcount+1)
	end
	
	
	
end

---------------------------------------------------------------------------------------------------
--取得当前成功次数
---------------------------------------------------------------------------------------------------
function x310211_GetDaySuccessCount(sceneId, selfId)



	local thisweek = x310211_GetWeekOfYear()
	local lastweek = GetQuestData(sceneId, selfId, MD_RUOGUO_NEW_DATE[1], MD_RUOGUO_NEW_DATE[2],MD_RUOGUO_NEW_DATE[3] );
	
	if lastweek ~= thisweek then
		return 0
	end

	local weekcount = GetQuestData(sceneId, selfId, MD_RUOGUO_NEW_DAY_SUCCESS_COUNT[1], MD_RUOGUO_NEW_DAY_SUCCESS_COUNT[2],MD_RUOGUO_NEW_DAY_SUCCESS_COUNT[3] );
	return weekcount;



	

end

---------------------------------------------------------------------------------------------------
--设置当天成功次数
---------------------------------------------------------------------------------------------------
function x310211_SetDaySuccessCount(sceneId, selfId)

	local thisweek = x310211_GetWeekOfYear()

	local lastweek = GetQuestData(sceneId, selfId, MD_RUOGUO_NEW_DATE[1], MD_RUOGUO_NEW_DATE[2], MD_RUOGUO_NEW_DATE[3])

	if lastweek ~= thisweek then
		--SetQuestData(sceneId, selfId, MD_RUOGUO_NEW_DATE[1], MD_RUOGUO_NEW_DATE[2], MD_RUOGUO_NEW_DATE[3], thisweek)
		SetQuestData(sceneId, selfId, MD_RUOGUO_NEW_DAY_SUCCESS_COUNT[1], MD_RUOGUO_NEW_DAY_SUCCESS_COUNT[2], MD_RUOGUO_NEW_DAY_SUCCESS_COUNT[3], 1)
	else
		local weekcount = GetQuestData(sceneId, selfId, MD_RUOGUO_NEW_DAY_SUCCESS_COUNT[1], MD_RUOGUO_NEW_DAY_SUCCESS_COUNT[2], MD_RUOGUO_NEW_DAY_SUCCESS_COUNT[3])
		SetQuestData(sceneId, selfId, MD_RUOGUO_NEW_DAY_SUCCESS_COUNT[1], MD_RUOGUO_NEW_DAY_SUCCESS_COUNT[2], MD_RUOGUO_NEW_DAY_SUCCESS_COUNT[3], weekcount+1)
	end
	
	
	
end

function x310211_CheckSceneOnKill(sceneId, selfId)
	return 1
end


-------------------------------------------------------------------------------
-- Kill
-------------------------------------------------------------------------------

function x310211_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
	
	local myMissionId = x310211_GetMissionId( sceneId, selfId )

	

	
	

	local HumenNum = GetMonsterOwnerCount( sceneId, objId ) --取得这个怪物死后拥有分配权的人数
	for i = 0, HumenNum-1 do
		local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --取得拥有分配权的人的objId
		if humanObjId ~= -1 then
			if IsHaveQuestNM( sceneId, humanObjId, myMissionId ) > 0 then	--如果这个人拥有任务
				x310211_OnValidKillObject( sceneId, humanObjId, objdataId, objId, myMissionId )
			end
		end
	end
	
end

function x310211_OnValidKillObject( sceneId, selfId, objdataId, objId, MissionId )

	if x310211_CheckSceneOnKill(sceneId, selfId)<=0 then
		return 0;
	end



	local myMissionId = x310211_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	
	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )

	if bCompleted>0 then
		return
	end

	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )


	
	if value2~=3 then
		return
	end

	
	local level1 = GetLevel(sceneId,objId)
	local level2 = GetLevel(sceneId,selfId)

	if level1<level2 then
		return 
	end
	
	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )

	

	SetQuestByIndex( sceneId, selfId, misIndex, 0, value1+1 )

	if (value1+1)>=x310211_g_NeedKillCount then
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
	end

	x310211_ShowTips(sceneId, selfId, format("【个人】弱国任务杀怪(%d/%d)",value1+1,x310211_g_NeedKillCount))

	x310211_QuestLogRefresh( sceneId, selfId, myMissionId );
	
end


--// system end


--------------------------------------------------------------------------------------
-- 生长点脚本
--------------------------------------------------------------------------------------


function x310211_OnOpenItemBox(sceneId, selfId, targetId,growpointId, itemId)
	
	if GetGameOpenById( x310211_g_GameId) <= 0 then
        x310211_ShowTips(sceneId, selfId, "此活动未开启")
		return 1
    end

	local myMissionId = x310211_GetMissionId( sceneId, selfId )

	

	if myMissionId ~= 7600 and myMissionId ~=7743 and myMissionId ~=7744 and myMissionId ~= 7745 then
		x310211_ShowTips(sceneId, selfId, "您没有接取【个人】弱国任务，不能采集！")
		return 1
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )


	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )


	if value2~=1 then
		x310211_ShowTips(sceneId, selfId, "你没有弱国任务中的采集任务，无法采集")
		return 1
	end

   
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId)
	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7)

	if bCompleted==1 then
		x310211_ShowTips(sceneId, selfId, "你已完成任务:"..x310211_g_MissionName)
		return 1;
	end

	local nGpIndex = GetQuestParam( sceneId, selfId, misIndex, 3)

	if nGpIndex~=(growpointId-x310211_g_GpTypeStart+1) then
		--x310211_ShowTips(sceneId, selfId, "请您去与您等级相应的地点")
		return 1;
	end

	return 0;
	
end

function x310211_OnRecycle(sceneId, selfId, targetId,growpointId, itemId)
	
	if GetGameOpenById( x310211_g_GameId) <= 0 then
        x310211_ShowTips(sceneId, selfId, "此活动未开启")
		return 0
    end

	

	local myMissionId = x310211_GetMissionId( sceneId, selfId )

	

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then	-- 如果没这个任务直接退出
		x310211_ShowTips(sceneId, selfId, "你没有任务:"..x310211_g_MissionName)
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )


	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )


	if value2~=1 then
		x310211_ShowTips(sceneId, selfId, "你没有弱国任务中的采集任务，无法采集")
		return 1
	end


   
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId)
	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7)

	if bCompleted==1 then
		x310211_ShowTips(sceneId, selfId, "你已完成任务:"..x310211_g_MissionName)
		return 0;
	end


	local nGpIndex = GetQuestParam( sceneId, selfId, misIndex, 3)

	if nGpIndex~=(growpointId-x310211_g_GpTypeStart+1) then
		x310211_ShowTips(sceneId, selfId, "你应该去采集你相应等级的采集点")
		return 0;
	end


	

	BeginAddItem(sceneId)
		AddItem( sceneId, x310211_g_ItemId_Caiji, 1 )
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		
		AddItemListToPlayer(sceneId,selfId)
		
		
		
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"物品栏已满，无法得到任务物品！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

		
	end

	return 1;
	--return CallScriptFunction( MISSION_SCRIPT, "OnRecycle", sceneId, selfId, targetId, x310211_g_GrowpointId, x310211_g_ItemIndex )
end




function x310211_OnProcOver(sceneId, selfId, targetId)
	-- 采集完毕
	
	

	return 0;
end

function x310211_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

	
end





-------------------------------------------------------------------
-- OnItemChange
-------------------------------------------------------------------
--物品改变
function x310211_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId, nChangeType, nCount)

    if MissionId == nil or MissionId < 0 then
        return
    end

	local MissionId_dup = MissionId

	

	local myMissionId = x310211_GetMissionId( sceneId, selfId )

	MissionId = myMissionId;
    
    if IsHaveQuestNM(sceneId,selfId,MissionId) <= 0 then
        return
    end
	

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )


	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )


	if value2==1 then
		if x310211_g_ItemId_Caiji==itemdataId then
			local Num = GetItemCount( sceneId, selfId, itemdataId )
			if Num<=x310211_g_ItemCount_Caiji then
			SetQuestByIndex( sceneId, selfId, misIndex, 0, Num )
			else
				SetQuestByIndex( sceneId, selfId, misIndex, 0, x310211_g_ItemCount_Caiji )
			end
			
			if nChangeType~=nil then
				if nChangeType<=0 then
				else
					local str = format("已获得@itemid_%d(%d/%d)",x310211_g_ItemId_Caiji,Num,x310211_g_ItemCount_Caiji)
					--x310211_ShowTips(sceneId, selfId, str)
				end
			else
				local str = format("已获得@itemid_%d(%d/%d)",x310211_g_ItemId_Caiji,Num,x310211_g_ItemCount_Caiji)
				--x310211_ShowTips(sceneId, selfId, str)
				
			end

			if Num>=x310211_g_ItemCount_Caiji then

				local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )

				if bCompleted<=0 then
				
					SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )

					if MissionId_dup~=1 then
						x310211_ShowTips(sceneId, selfId, "已完成任务:"..x310211_g_MissionName)
					end
				end
			elseif Num<x310211_g_ItemCount_Caiji then
				SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
			end
		end
		
	elseif value2==2 then
		local nItemIndex = GetQuestParam( sceneId, selfId, misIndex, 4 )
		

		if nCount==nil then
		
			nCount = GetQuestParam( sceneId, selfId, misIndex, 3 )
		end

		if x310211_g_ShouJi_list[nItemIndex]==itemdataId then
			local Num = GetItemCount( sceneId, selfId, itemdataId )

			if Num<=nCount then
			SetQuestByIndex( sceneId, selfId, misIndex, 0, Num )
			else
				SetQuestByIndex( sceneId, selfId, misIndex, 0, nCount )
			end
			
			

			if Num>=nCount then

				local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )

				if bCompleted<=0 then
					SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
					if MissionId_dup~=1 then
						x310211_ShowTips(sceneId, selfId, "已完成任务:"..x310211_g_MissionName)
					end
				end
			elseif Num<nCount then
				SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
			end
		end
		
	end

	x310211_QuestLogRefresh( sceneId, selfId, MissionId );

    
	
end


function x310211_GetWeekOfYear()
	return GetWeekIndex()
end




