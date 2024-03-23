--***********************
--Const
--***********************
-------------------------

--MisDescBegin

x300807_g_MissionId 				= 	9418                    --任务ID
x300807_g_ScriptId 					= 	300807                  --脚本ID
x300807_g_MissionKind 				= 	1                       --任务类型
x300807_g_LevelLess					= 	75                      --场景开放等级  <=0 表示不限制


x300807_g_MissionName				= 	"【个人】军需武备"
x300807_g_MissionTarget				= 	""          --任务目标
x300807_g_MissionInfo				= 	"\t时下多事之秋，王国中有很多棘手的事情需要得力的人去做，我希望你能助上一臂之力。\n\t你是否要接受任务？"         
x300807_g_ContinueInfo				= 	"\t怎么？你连这些简单的任务都无法完成？看来我们要另外物色人选了。"  --任务继续信息
x300807_g_MissionCompleted			= 	"\t你的表现让我很欣慰，希望你以后能够继续为我们的王国多做贡献！"  --任务完成信息
x300807_g_MissionHelp				=	"\t军需武备任务每轮为#G30环#W子任务，环数越高，#G经验奖励#W也越高！\n\t军需武备中收集的物品，很多可以通过生活技能制作，或和其他玩家交易得来。"          --任务提示信息

--目标
x300807_g_ExtTarget					=	{ {type=20,n=1,target="【个人】军需武备"}}

--奖励

x300807_g_ExpBonus					= 	0;--x300807_AddExpAward               	--奖励：经验
x300807_g_BonusItem					=	{}	--奖励：物品

x300807_g_BonusMoney1               = 	0
x300807_g_BonusMoney2               =   0
x300807_g_BonusMoney3               =   0

x300807_g_BonusChoiceItem           =   {}


--MisDescEnd

x300807_g_GameId					=	1030
x300807_g_DayCountLimited			=	1
--x300807_g_nDaySpace					=	5    --多少天能做一次

x300807_g_EnterTime					=	{                       --接受任务的时间
											{min=0*60+0,  max=23*60+59},
										}

x300807_g_MaxStep					=	30
x300807_g_ReplyNpcId				=	132153
x300807_g_ReplyNpcObjId				=	3
----------------------------- common start ------------------------

x300807_g_BaseBonusRate = {50000,52000,54000,56000,58000,60000,62000,64000,66000,68000}  --基础奖励基数
x300807_g_ExtraBonusRate = {1,1.6,2.9}  --10环乘数

----------------------------- common end---------------------------

----------------------------- 收集 start ------------------------
x300807_g_MissionInfo2				= 	"\t现在世道纷乱，百姓处在水深火热之中，王国中的有识之士准备组织起来保境安民，但目前国中物资匮乏，急需补充。"
x300807_g_ContinueInfo2				= 	"\t这件物品着这么难以找到吗？"
x300807_g_MissionCompleted2			= 	"\t谢谢你的慷慨解囊。"
x300807_g_MissionHelp2					=	"\t军需武备任务每轮为#G30环#W子任务，环数越高，#G经验奖励#W也越高！\n\t军需武备中收集的物品，很多可以通过生活技能制作，或和其他玩家交易得来。"            --任务提示信息

x300807_g_MissionTable2 =	{ --needvalue:帮会功德
							
 { id=1, ncount=6,needitem={{itemid=11020080,count=5},{itemid=11020070,count=5},{itemid=11020050,count=5},{itemid=11020060,count=5},{itemid=11020030,count=5},{itemid=11020040,count=5}}},
 { id=2, ncount=6,needitem={{itemid=11041010,count=5},{itemid=11041000,count=5},{itemid=11041020,count=5},{itemid=11041030,count=5},{itemid=11041040,count=5},{itemid=11041050,count=5}}},
 { id=3, ncount=10,needitem={{itemid=12240003,count=1},{itemid=12240004,count=1},{itemid=12240005,count=1},{itemid=12240007,count=1},{itemid=12240008,count=1},{itemid=12240009,count=1},{itemid=12240010,count=1},{itemid=12240011,count=1},{itemid=12240012,count=1},{itemid=12240012,count=1}}},
 { id=4, ncount=6,needitem={{itemid=11020080,count=5},{itemid=11020070,count=5},{itemid=11020050,count=5},{itemid=11020060,count=5},{itemid=11020030,count=5},{itemid=11020040,count=5}}},
 { id=5, ncount=8,needitem={{itemid=12200600,count=1},{itemid=12200601,count=1},{itemid=12200602,count=1},{itemid=12200603,count=1},{itemid=12200604,count=1},{itemid=12200605,count=1},{itemid=12200606,count=1},{itemid=12200607,count=1}}},
 { id=6, ncount=4,needitem={{itemid=11020071,count=5},{itemid=11020081,count=5},{itemid=11020051,count=5},{itemid=11020061,count=5}}},
 { id=7, ncount=9,needitem={{itemid=12240003,count=1},{itemid=12240004,count=1},{itemid=12240005,count=1},{itemid=12240007,count=1},{itemid=12240008,count=1},{itemid=12240009,count=1},{itemid=12240010,count=1},{itemid=12240011,count=1},{itemid=12240012,count=1}}},
 { id=8, ncount=5,needitem={{itemid=12052013,count=1},{itemid=12052023,count=1},{itemid=12052033,count=1},{itemid=12052043,count=1},{itemid=12052053,count=1}}},
 { id=9, ncount=7,needitem={{itemid=11041032,count=2},{itemid=11041051,count=4},{itemid=11041052,count=2},{itemid=11041021,count=4},{itemid=11041022,count=4},{itemid=11041041,count=4},{itemid=11041042,count=2}}},
 { id=10, ncount=9,needitem={{itemid=12240003,count=1},{itemid=12240004,count=1},{itemid=12240005,count=1},{itemid=12240007,count=1},{itemid=12240008,count=1},{itemid=12240009,count=1},{itemid=12240010,count=1},{itemid=12240011,count=1},{itemid=12240012,count=1}}},
 { id=11, ncount=6,needitem={{itemid=11020071,count=12},{itemid=11020081,count=12},{itemid=11020051,count=12},{itemid=11020061,count=12},{itemid=11020031,count=12},{itemid=11020041,count=12}}},
 { id=12, ncount=5,needitem={{itemid=12240002,count=2},{itemid=11000902,count=1},{itemid=12050091,count=2},{itemid=12050092,count=1},{itemid=12054300,count=1}}},
 { id=13, ncount=7,needitem={{itemid=12200705,count=1},{itemid=12200704,count=1},{itemid=12200706,count=1},{itemid=12221812,count=1},{itemid=12223802,count=1},{itemid=12223800,count=1},{itemid=12223801,count=1}}},
 { id=14, ncount=9,needitem={{itemid=12240003,count=5},{itemid=12240004,count=5},{itemid=12240005,count=5},{itemid=12240007,count=5},{itemid=12240008,count=5},{itemid=12240009,count=5},{itemid=12240010,count=5},{itemid=12240011,count=5},{itemid=12240012,count=5}}},
 { id=15, ncount=11,needitem={{itemid=12221800,count=1},{itemid=12221801,count=1},{itemid=12221802,count=1},{itemid=12221803,count=1},{itemid=12221804,count=1},{itemid=12221805,count=1},{itemid=12222800,count=1},{itemid=12222801,count=1},{itemid=12222802,count=1},{itemid=12222803,count=1},{itemid=12222804,count=1}}},
 { id=16, ncount=6,needitem={{itemid=11020082,count=20},{itemid=11020072,count=20},{itemid=11020052,count=20},{itemid=11020062,count=20},{itemid=11020032,count=20},{itemid=11020042,count=20}}},
 { id=17, ncount=7,needitem={{itemid=14040003,count=1},{itemid=14010008,count=1},{itemid=14010003,count=1},{itemid=14010013,count=1},{itemid=14020003,count=1},{itemid=14020008,count=1},{itemid=14020013,count=1}}},
 { id=18, ncount=6,needitem={{itemid=11041012,count=10},{itemid=11041002,count=10},{itemid=11041022,count=10},{itemid=11041032,count=10},{itemid=11041042,count=10},{itemid=11041052,count=10}}},
 { id=19, ncount=7,needitem={{itemid=12200800,count=1},{itemid=12200808,count=1},{itemid=12200809,count=1},{itemid=12200810,count=1},{itemid=12210805,count=1},{itemid=12221816,count=1},{itemid=12223804,count=1}}},
 { id=20, ncount=9,needitem={{itemid=12240003,count=5},{itemid=12240004,count=5},{itemid=12240005,count=5},{itemid=12240007,count=5},{itemid=12240008,count=5},{itemid=12240009,count=5},{itemid=12240010,count=5},{itemid=12240011,count=5},{itemid=12240012,count=5}}},
 { id=21, ncount=7,needitem={{itemid=12200800,count=1},{itemid=12200808,count=1},{itemid=12200809,count=1},{itemid=12200810,count=1},{itemid=12210805,count=1},{itemid=12221816,count=1},{itemid=12223804,count=1}}},
 { id=22, ncount=9,needitem={{itemid=12240007,count=7},{itemid=12240008,count=7},{itemid=12240009,count=7},{itemid=12240010,count=7},{itemid=12240011,count=7},{itemid=12240003,count=7},{itemid=12240004,count=7},{itemid=12240005,count=7},{itemid=12240010,count=7}}},
 { id=23, ncount=8,needitem={{itemid=12240003,count=7},{itemid=12240004,count=7},{itemid=12240005,count=7},{itemid=12240007,count=7},{itemid=12240008,count=7},{itemid=12240009,count=7},{itemid=12240010,count=7},{itemid=12240011,count=7}}},
 { id=24, ncount=6,needitem={{itemid=11020073,count=20},{itemid=11020083,count=20},{itemid=11020053,count=20},{itemid=11020063,count=20},{itemid=11020032,count=20},{itemid=11020042,count=20}}},
 { id=25, ncount=3,needitem={{itemid=12041110,count=5},{itemid=12041111,count=5},{itemid=12041112,count=5}}},
 { id=26, ncount=6,needitem={{itemid=11041003,count=10},{itemid=11041043,count=10},{itemid=11041013,count=10},{itemid=11041033,count=10},{itemid=11041023,count=10},{itemid=11041053,count=10}}},
 { id=27, ncount=6,needitem={{itemid=11020073,count=20},{itemid=11020083,count=20},{itemid=11020053,count=20},{itemid=11020063,count=20},{itemid=11020032,count=20},{itemid=11020042,count=20}}},
 { id=28, ncount=7,needitem={{itemid=14040003,count=1},{itemid=14010008,count=1},{itemid=14010003,count=1},{itemid=14010013,count=1},{itemid=14020003,count=1},{itemid=14020008,count=1},{itemid=14020013,count=1}}},
 { id=29, ncount=8,needitem={{itemid=12240003,count=7},{itemid=12240004,count=7},{itemid=12240005,count=7},{itemid=12240007,count=7},{itemid=12240008,count=7},{itemid=12240009,count=7},{itemid=12240010,count=7},{itemid=12240011,count=7}}},
 { id=30, ncount=4,needitem={{itemid=11020073,count=20},{itemid=11020083,count=20},{itemid=11020053,count=20},{itemid=11020063,count=20}}},
							}
----------------------------- 收集 end---------------------------

function x300807_GetMissionId( sceneId, selfId )
	return x300807_g_MissionId
end

function x300807_GetMissionStep(sceneId, selfId)

---调步骤
    --return 1
	local nLastFlag = GetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_CURRENT_ID[1], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[2], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[3])
	if nLastFlag>=x300807_GetMaxStep(sceneId,selfId) then
		nLastFlag = 0
	end
	return nLastFlag+1
	
end

function x300807_SaveMissionStep(sceneId, selfId)

	local nLastFlag = GetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_CURRENT_ID[1], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[2], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[3])



	if nLastFlag<(x300807_GetMaxStep(sceneId,selfId)-1) then
		
		SetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_CURRENT_ID[1], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[2], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[3],nLastFlag+1)
		local myMissionId = x300807_GetMissionId( sceneId, selfId )	
		x300807_DispatchMissionInfo( sceneId, selfId, x300807_g_ReplyNpcObjId, myMissionId, 0 )
	else
		SetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_CURRENT_ID[1], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[2], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[3],0)
		x300807_SetDayCount(sceneId, selfId)
		
		if random( 1, 1000000) <= 25 then
            BeginAddItem( sceneId)
            AddItem( sceneId, 10310003, 1)
            local ret = EndAddItem( sceneId, selfId)
            if ret > 0 then
                AddItemListToPlayer( sceneId, selfId)
				local msg = format( "恭喜#R%s#cffcc00完成军需武备任务，幸运的获得了一个#G掌门牌：大三元(永不磨损)！", GetName( sceneId, selfId) )
                LuaAllScenceM2Wrold (sceneId, msg, 5, 1)
                Msg2Player( sceneId, selfId, msg, 2, 0)
            else
                Msg2Player( sceneId, selfId, "物品栏已满，无法得到物品", 8, 3)
            end
        end
		
	end
	
  
end

function x300807_ResetMissionStep(sceneId, selfId)
	SetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_CURRENT_ID[1], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[2], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[3],0)
end

function x300807_GetMissionTypeById(nStep)
	
	local nIndex =0
	for i,item in x300807_g_MissionTable2 do
		nIndex = nIndex+1;
		if item.id == nStep then
			return nIndex
		end
	end
end

function x300807_GetMaxStep(sceneId,selfId)
	return x300807_g_MaxStep
end

function x300807_GetData(sceneId, selfId)
	local nStep = x300807_GetMissionStep(sceneId, selfId)
	local nIndex = x300807_GetMissionTypeById(nStep)
	local n1 = mod(nStep,10)

	

	local n2 = (nStep - mod(nStep,10))/10+1
	if n1==0 then
		n1 = 10
		
		n2 = (nStep - mod(nStep,10))/10
	end
	
	local nBaseBonusRate = x300807_g_BaseBonusRate[n1]  --基础奖励基数
	local nExtraBonusRate = x300807_g_ExtraBonusRate[n2] --还数奖励基数
	local nLevel = GetLevel(sceneId, selfId)
	local nExpBonus = nLevel*nBaseBonusRate*nExtraBonusRate
	
	nExpBonus = tonumber(format("%d",nExpBonus))
	if nLevel >= 80 and nLevel < 90 then
		nExpBonus = nExpBonus*2
	elseif nLevel >= 90 and nLevel < 160 then 
	 	nExpBonus = nExpBonus*2.6
	end
	return nStep,nIndex,nExpBonus
end

function x300807_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	if GetGameOpenById(x300807_g_GameId)<=0 then
		return
	end

	if IsPlayerStateNormal(sceneId,selfId ) <= 0 then
		return
	end

	local level = GetLevel( sceneId,selfId )
    if level < x300807_g_LevelLess then
       return
    end

	local myMissionId = x300807_GetMissionId( sceneId, selfId )
	
	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		AddQuestNumText(sceneId, myMissionId, x300807_g_MissionName,8,1);
		
	else
		local state = GetQuestStateNM(sceneId, selfId, targetId, myMissionId);

		AddQuestNumText(sceneId, myMissionId, x300807_g_MissionName,state,state);

	end


	DispatchQuestEventList(sceneId, selfId, targetId)


	
end





---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300807_ProcEventEntry( sceneId, selfId, targetId, MissionId, nExt )
	
	
	
	if GetGameOpenById(x300807_g_GameId)<=0 then
		x300807_ShowTips(sceneId, selfId, "此活动未开启")
		return
	end

	local myMissionId = x300807_GetMissionId( sceneId, selfId )	
	
	

	
	
	
		
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		if nExt~=30 then
		
		x300807_DispatchMissionInfo( sceneId, selfId, targetId, myMissionId, 0 )
		else
			x300807_ShowTips(sceneId, selfId, "你没有任务"..x300807_g_MissionName)
			return
		end
		
		
	else
		if nExt==7 then -- 任务完成
			x300807_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
			
		elseif nExt==30 then
			x300807_DispatchSongxinInfo( sceneId, selfId, targetId,myMissionId )
		else
			
			x300807_DispatchContinueInfo( sceneId, selfId, targetId,myMissionId )
		end
	end
	
end



function x300807_DispatchSongxinInfo( sceneId, selfId, NPCId,MissionId )

end

---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x300807_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId, nExt )
	

	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300807_g_MissionName)
		
			
		AddQuestText(sceneId,x300807_g_MissionInfo)
		AddQuestText(sceneId," ")
			
		--AddQuestText( sceneId,"#Y任务目标:")
					
		AddQuestText( sceneId,x300807_g_MissionTarget)
		--AddQuestText(sceneId," ")

		
		if nExpBonus > 0 then
			AddQuestExpBonus( sceneId, nExpBonus)
		end

		AddQuestText( sceneId,"#G小提示：#W\n\t军需武备任务每轮为#G30环#W子任务，环数越高，#G经验奖励#W也越高！\n\t军需武备中收集的物品，很多可以通过生活技能制作，或和其他玩家交易得来。")
	

	EndQuestEvent()
	
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300807_g_ScriptId, MissionId,0);
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300807_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	local myMissionId = x300807_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300807_g_MissionName)
		AddQuestText(sceneId," ")
		AddQuestText(sceneId,"\t您还没有完成本次任务，请赶快去完成吧！")
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300807_g_ScriptId, MissionId,0);
	


end







---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300807_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	local myMissionId = x300807_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)
	

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300807_g_MissionName)
		AddQuestText(sceneId,"\t#Y@myname#W，感谢你所做出的贡献，相信在大家的共同努力下，我们的王国一定会更加强盛。")
	

	
	if nExpBonus > 0 then
		AddQuestExpBonus( sceneId, nExpBonus)
	end

	
		
	EndQuestEvent()
	
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300807_g_ScriptId, MissionId);

end


function x300807_ProcAcceptCheck(sceneId, selfId, targetId, MissionId )
	
	if GetGameOpenById(x300807_g_GameId)<=0 then
		
		return 0;
	end
	return 1;

end

function x300807_CheckRequest(sceneId, selfId)
	if GetGameOpenById(x300807_g_GameId)<=0 then
		x300807_ShowTips(sceneId, selfId, "此活动未开启")
		return 0
	end


	local myMissionId = x300807_GetMissionId( sceneId, selfId )

	if GetLevel(sceneId, selfId) <x300807_g_LevelLess then
		x300807_ShowTips(sceneId, selfId, "您的等级不足，无法接取此任务")
		return 0
	end

	--if GetGuildID( sceneId, selfId ) == -1 then
	--  x300807_ShowTips(sceneId, selfId, "您还没有加入帮会，无法接取此任务")
	--  return 0
	--end

	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) > 0 then
		x300807_ShowTips(sceneId, selfId, "您已经接取了该任务，请先完成当前任务")
		return 0;
	end


	if x300807_g_DayCountLimited >0 then
		--local nDayCount, nLastDay = x300807_GetDayCount(sceneId, selfId)

		
		--if nDayCount>= x300807_g_DayCountLimited then
		--	local today = GetDayOfYear() 

		--	local nNeedDay = x300807_g_nDaySpace-(today-nLastDay)

		--	x300807_ShowTips(sceneId, selfId, format("很抱歉，【个人】军需武备任务，请%d天后来接任务！",nNeedDay))
		--	return 0;
		--end
		if x300807_GetDayCount(sceneId, selfId) > 0 then
			x300807_ShowTips(sceneId, selfId, "很抱歉，请下周再来接取本任务！")
			x300807_ResetMissionStep(sceneId, selfId)
			return 0
		end
	end

	

	return 1;

end



function x300807_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
	
	if x300807_CheckRequest(sceneId, selfId)<=0 then
		
		return 0;
	end

	local myMissionId = x300807_GetMissionId( sceneId, selfId )
	--------------------------- add for Mission full check --------------
	local bFullMission = IsQuestFullNM(sceneId,selfId)
	
	if bFullMission>0 then
		x300807_ShowTips(sceneId, selfId, "任务已满，无法接受任务")
		return 0
	end
	---------------------------- add end -------------------------------
	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)

	local ret = AddQuest( sceneId, selfId, myMissionId, x300807_g_ScriptId, 1, 0, 1,1)-- 给玩家添加任务		
		
	if ret > 0 then
		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

---调步骤
		local nRandom = random(1,x300807_g_MissionTable2[nIndex].ncount)
		if nRandom < 1 then
			nRandom = 1
		elseif nRandom > x300807_g_MissionTable2[nIndex].ncount then
			nRandom = x300807_g_MissionTable2[nIndex].ncount
		end
		
		local str = "您接受了任务："..x300807_g_MissionName;
		x300807_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)
		
		SetQuestByIndex( sceneId, selfId, misIndex, 6, nRandom )
		

		x300807_ShowSubMission( sceneId, selfId, targetId,MissionId,nRandom )

		x300807_CheckShoujiHaveAll(sceneId, selfId, nRandom)

		GamePlayScriptLog(sceneId, selfId, 1271)
		return 1
	else
		
		x300807_ShowTips(sceneId, selfId, "接受任务错误")
	
	end


end


function x300807_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x300807_ProcQuestAbandon( sceneId, selfId, MissionId )

	local myMissionId = x300807_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )


	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )

    local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)
	local nRandom = GetQuestParam( sceneId, selfId, misIndex, 6 )
	

	local ret = DelQuestNM( sceneId, selfId, myMissionId )
	if ret>0 then

		local str = "您放弃了任务:"..x300807_g_MissionName;
	    x300807_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)

		x300807_SetDayCount(sceneId, selfId)
		x300807_ResetMissionStep(sceneId, selfId)
	else
		x300807_ShowTips(sceneId, selfId, "放弃任务失败")
	end
end


function x300807_ProcQuestSubmit( sceneId, selfId, targetId, selectRadioId, MissionId )
	
	
	if GetGameOpenById(x300807_g_GameId)<=0 then
		x300807_ShowTips(sceneId, selfId, "此活动未开启")
		return 0;
	end

	
	local myMissionId = x300807_GetMissionId( sceneId, selfId )

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end
	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )


	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)
	
	if x300807_CheckSubmit(sceneId, selfId )>0 then
		if x300807_SubmitShouji(sceneId, selfId,targetId)<=0 then
				return 0
			end
		
		local ret = DelQuestNM( sceneId, selfId, myMissionId )

		if ret>0 then

			local str = "您完成了任务:"..x300807_g_MissionName;
			x300807_ShowTips(sceneId, selfId, str)
			Msg2Player(sceneId,selfId,str,8,2)

			
			
			x300807_GiveReward(sceneId,selfId)

			x300807_SaveMissionStep(sceneId, selfId)

			CallScriptFunction( 300807, "ProcEventEntry", sceneId, selfId, targetId, x300807_g_MissionId )	
			GamePlayScriptLog(sceneId, selfId, 1272)
			
		else
			x300807_ShowTips(sceneId, selfId, "交任务失败")
		end
		
	end
end


function x300807_SubmitShouji(sceneId, selfId,targetId)
	
	
	local myMissionId = x300807_GetMissionId( sceneId, selfId )

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	local nRandom = GetQuestParam( sceneId, selfId, misIndex, 6 )



	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)
	
	
	local itemid_t = x300807_g_MissionTable2[nIndex].needitem[nRandom].itemid
	local count_t = x300807_g_MissionTable2[nIndex].needitem[nRandom].count

	
	if GetItemClass(itemid_t)~=10 then

		local nRet = DelItem(sceneId, selfId,itemid_t,count_t)
		
		if nRet<=0 then
			x300807_ShowTips(sceneId, selfId, "删除物品失败")
			
			return 0
		else
		
		end
	
	else
		--如果是装备
		
		
		local nItemCount = GetItemCount( sceneId, selfId, itemid_t )
		
		BeginUICommand( sceneId)
			UICommand_AddInt( sceneId, x300807_g_ScriptId)
			UICommand_AddInt( sceneId, myMissionId)
			UICommand_AddInt( sceneId, targetId)
			UICommand_AddInt( sceneId, itemid_t)
			
			
			DispatchUICommand( sceneId, selfId, 106)  --104
		EndUICommand( sceneId)

		BeginQuestEvent( sceneId)
		AddQuestText( sceneId, "#Y"..x300807_g_MissionName)
			AddQuestText( sceneId, "\t你需要选择上交一件完成本轮任务的所需物品" )
		EndQuestEvent( sceneId)
		DispatchQuestEventList( sceneId, selfId, targetId)

		--AskDeleteWhichEquip(sceneId, selfId,itemid_t,count_t)  --发送给客户端删除哪个装备

		return 0
	end

	return 1
end

function x300807_OnComitSubmitItem(sceneId, selfId,bagIndex)

	local myMissionId = x300807_GetMissionId( sceneId, selfId )

	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)
	
	if x300807_CheckSubmit(sceneId, selfId )>0 then
		
		if EraseItem(sceneId, selfId,bagIndex)>0 then
			local ret = DelQuestNM( sceneId, selfId, myMissionId )

			if ret>0 then

				local str = "您完成了任务:"..x300807_g_MissionName;
				x300807_ShowTips(sceneId, selfId, str)
				Msg2Player(sceneId,selfId,str,8,2)

				
				
				x300807_GiveReward(sceneId,selfId)

				x300807_SaveMissionStep(sceneId, selfId)


				GamePlayScriptLog(sceneId, selfId, 1272)
				
			else
				x300807_ShowTips(sceneId, selfId, "交任务失败")
			end
		else
			x300807_ShowTips(sceneId, selfId, "删除物品失败")
		end
		
	end
end



function x300807_GiveReward(sceneId,selfId)
	
	if GetGameOpenById(x300807_g_GameId)<=0 then
		x300807_ShowTips(sceneId, selfId, "此活动未开启")
		return 0;
	end

	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)
	
	AddExp(sceneId,selfId,nExpBonus)
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, "#o您获得了#R经验"..nExpBonus.."点#o的奖励");
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId,selfId,"#o您完成了【个人】军需武备任务，获得了#R经验"..nExpBonus.."点#o的奖励",4,2)
	
	
end



function x300807_CheckSubmit(sceneId, selfId )
	
	if GetGameOpenById(x300807_g_GameId)<=0 then
		x300807_ShowTips(sceneId, selfId, "此活动未开启")
		return 0;
	end

	local myMissionId = x300807_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )
	local nRandom = GetQuestParam( sceneId, selfId, misIndex, 6 )


	

	if (bCompleted)<=0 then
		return 0
	end

	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)

		local itemid_t = x300807_g_MissionTable2[nIndex].needitem[nRandom].itemid
		local count_t = x300807_g_MissionTable2[nIndex].needitem[nRandom].count
		local nItemCount = GetItemCount( sceneId, selfId, itemid_t )
		if nItemCount<count_t then
			return 0
		end
		

	return 1;
end






---------------------------------------------------------------------------------------------------
--向客户端发送题目
---------------------------------------------------------------------------------------------------
function x300807_ShowSubMission( sceneId, selfId, NPCId,MissionId, nRandom )


	
	local myMissionId = x300807_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)

	

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"#Y"..x300807_g_MissionName)
	
		local str1 = "  收集"..x300807_g_MissionTable2[nIndex].needitem[nRandom].count.."个#G@itemid_"..x300807_g_MissionTable2[nIndex].needitem[nRandom].itemid.."\n"
		
		AddQuestText(sceneId,x300807_g_MissionInfo2)
		AddQuestText( sceneId,"\n#Y任务目标:")
		AddQuestText(sceneId,"#W"..str1)
	

	
	if nExpBonus > 0 then
		AddQuestExpBonus( sceneId, nExpBonus)
	end

	

	EndQuestEvent()

	DispatchQuestEventList( sceneId, selfId, NPCId)
end







---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300807_QuestLogRefresh( sceneId, selfId, MissionId)
	
	local myMissionId = x300807_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end
		
	BeginQuestEvent(sceneId)	
			
		
	AddQuestLogCustomText( sceneId,
							"",						-- 标题
							x300807_GetMissionName(sceneId,selfId),        -- 任务名字
							x300807_GetMissionTask(sceneId,selfId),		--任务目标
							"@npc_"..x300807_GetReplyNpcId(sceneId,selfId),			--任务NPC
							x300807_GetMissionMethod(sceneId,selfId),               --任务攻略
							x300807_GetMissionText(sceneId,selfId),	--任务描述
							x300807_GetMissionHelp(sceneId,selfId)					--任务小提示
							)

	--1、经验
	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)

	if nExpBonus > 0 then
		AddQuestExpBonus( sceneId, nExpBonus)
	end

	
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	

end

function x300807_GetMissionName(sceneId,selfId)
	
	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)

	return x300807_g_MissionName..format("(%d/%d)",nStep,x300807_GetMaxStep(sceneId,selfId));
end

function x300807_GetMissionTask(sceneId,selfId)
	local myMissionId = x300807_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	
	local value0 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	local value7 = GetQuestParam( sceneId, selfId, misIndex, 7 )
	local nRandom = GetQuestParam( sceneId, selfId, misIndex, 6 )
	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)

	local str1=""

	

		local id = x300807_g_MissionTable2[nIndex].needitem[nRandom].itemid
		local count_t = x300807_g_MissionTable2[nIndex].needitem[nRandom].count
		
		local strTail = format("(%d/%d)",value0,count_t)
		if value0>=count_t then
			strTail = "#G"..strTail
		else
			strTail = "#W"..strTail
		end
		str1 = str1.."  #W收集"..count_t.."个#G@itemid_"..id..strTail
		

		return str1
	

	

	
end

function x300807_GetReplyNpcId(sceneId,selfId)
	return x300807_g_ReplyNpcId;
end

function x300807_GetMissionMethod(sceneId,selfId)
	

	local myMissionId = x300807_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)
	local nRandom = GetQuestParam( sceneId, selfId, misIndex, 6 )

	local str1=""

		
		local id = x300807_g_MissionTable2[nIndex].needitem[nRandom].itemid
		local count_t = x300807_g_MissionTable2[nIndex].needitem[nRandom].count
		
		str1 = str1.."  #W收集"..count_t.."个#G@itemid_"..id
		

	return str1
end

function x300807_GetMissionText(sceneId,selfId)
	
	

	return x300807_g_MissionInfo
end

function x300807_GetMissionHelp(sceneId,selfId)
	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)
	
		return x300807_g_MissionHelp2
	
end



function x300807_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300807_QuestLogRefresh( sceneId, selfId, MissionId );
end

--// system function start
function x300807_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	
	local myMissionId = x300807_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	local nRandom = GetQuestParam( sceneId, selfId, misIndex, 6 )

	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)
	
end

---------------------------------------------------------------------------------------------------
--取得当前次数
---------------------------------------------------------------------------------------------------
function x300807_GetDayCount(sceneId, selfId)

	local today = GetWeekIndex()
	local lastday = GetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_DATE_NV[1], MD_GUILD_CIRCLE_MISSION_DATE_NV[2],MD_GUILD_CIRCLE_MISSION_DATE_NV[3] )
	local daycount = GetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_DAYCOUNT[1], MD_GUILD_CIRCLE_MISSION_DAYCOUNT[2],MD_GUILD_CIRCLE_MISSION_DAYCOUNT[3] );

	if today == lastday then
		return daycount 
	end
	
	return 0

end

---------------------------------------------------------------------------------------------------
--设置当天次数
---------------------------------------------------------------------------------------------------
function x300807_SetDayCount(sceneId, selfId)

	local today = GetWeekIndex()
	local lastday = GetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_DATE_NV[1], MD_GUILD_CIRCLE_MISSION_DATE_NV[2],MD_GUILD_CIRCLE_MISSION_DATE_NV[3] );
	
	if today == lastday then
			local daycount = GetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_DAYCOUNT[1], MD_GUILD_CIRCLE_MISSION_DAYCOUNT[2], MD_GUILD_CIRCLE_MISSION_DAYCOUNT[3])
			SetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_DAYCOUNT[1], MD_GUILD_CIRCLE_MISSION_DAYCOUNT[2], MD_GUILD_CIRCLE_MISSION_DAYCOUNT[3], daycount+1)
		else
		SetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_DATE_NV[1], MD_GUILD_CIRCLE_MISSION_DATE_NV[2], MD_GUILD_CIRCLE_MISSION_DATE_NV[3], today)
		SetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_DAYCOUNT[1], MD_GUILD_CIRCLE_MISSION_DAYCOUNT[2], MD_GUILD_CIRCLE_MISSION_DAYCOUNT[3], 1)
		end
end

--function x300807_CheckSceneOnKill(sceneId, selfId)
	--return 1
--end

--定点使用物品任务
function x300807_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return 1
end


--// system end


-------------------------------------------------------------------
-- OnItemChange
-------------------------------------------------------------------
--物品改变
function x300807_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId, nChangeType, nCount)

    local myMissionId = x300807_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)


	local nRandom = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	local itemid_t	= x300807_g_MissionTable2[nIndex].needitem[nRandom].itemid
	local count_t	= x300807_g_MissionTable2[nIndex].needitem[nRandom].count
	if itemid_t==itemdataId then
		local Num = GetItemCount( sceneId, selfId, itemdataId )

		if Num<count_t then
			SetQuestByIndex( sceneId, selfId, misIndex, 0, Num )
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
		else
			SetQuestByIndex( sceneId, selfId, misIndex, 0, count_t )
			
			local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )

			if bCompleted<=0 then
				SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
				
				--x300807_ShowTips(sceneId, selfId, "已完成任务:"..x300807_g_MissionName)
				
			end
		end
		
	end


	x300807_QuestLogRefresh( sceneId, selfId, myMissionId );

    
	
end

function x300807_CheckShoujiHaveAll(sceneId, selfId, nRandom)
	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)


	local itemid_t = x300807_g_MissionTable2[nIndex].needitem[nRandom].itemid
	x300807_ProcQuestItemChanged( sceneId, selfId,itemid_t, -1, -1, -1)
	
end

function x300807_OnSelectSubmitItem( sceneId, selfId , bagIndex, nGuid_Serial, nGuid_Server, nGuid_World)

	if x300807_CheckSubmit(sceneId, selfId )<=0 then
		return 0
	end

	local myMissionId = x300807_GetMissionId( sceneId, selfId )
	
	if IsHaveQuest( sceneId, selfId, myMissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId)

	local nStep,nIndex,nExpBonus = x300807_GetData(sceneId, selfId)
	


	--x300807_ShowTips(sceneId, selfId, format("bagIndex=%d,itemGuid1=%d, itemGuild2=%d, itemGuid3=%d",bagIndex , nGuid_Serial, nGuid_Server, nGuid_World))

	local nRandom = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	local itemid_t = x300807_g_MissionTable2[nIndex].needitem[nRandom].itemid
	local count_t = x300807_g_MissionTable2[nIndex].needitem[nRandom].count

	if (CheckItemMatchInBag( sceneId, selfId , bagIndex, itemid_t,nGuid_Serial, nGuid_Server, nGuid_World))>0 then  --如果物品检查正确
		x300807_OnComitSubmitItem(sceneId, selfId,bagIndex)
	end
end


-- 离开帮会
function x300807_OnLeaveGuild(sceneId, selfId, MissionId)

	--DelQuestNM( sceneId, selfId, MissionId)
	--local message = format("您已经不在帮会中了，删除了任务：%s", x300807_g_MissionName);
	--BeginQuestEvent(sceneId);
	--AddQuestText(sceneId, message);
	--EndQuestEvent();
	--DispatchQuestTips(sceneId, selfId);
	--Msg2Player(sceneId, selfId, message, 8, 2);	
	
end

function x300807_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end



