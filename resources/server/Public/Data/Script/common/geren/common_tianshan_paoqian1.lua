--MisDescBegin

x300863_g_ScriptId 					= 	300863                  --脚本ID

x300863_g_MissionKind 				= 	1                       --任务类型
x300863_g_LevelLess					= 	30                      --任务最小等级  <=0 表示不限制

x300863_g_MissionTarget				= 	"将货物安全运到@npc_137501"          --任务目标
x300863_g_MissionInfo				= 	"\t杀死@npc_72004的@npc_72005,找到@npc_137600"            --任务信息
x300863_g_ContinueInfo				= 	"怎么还没人送货过来啊？今天送货的人呢？"  --任务继续信息
x300863_g_MissionCompleted			= 	"一路辛苦了，这是给您的奖励，请收下！"  --任务完成信息
x300863_g_MissionHelp				=	""          --任务提示信息

--目标
x300863_g_ExtTarget					=	{ {type=20,n=1,target="@npc_72005"} }


--奖励
x300863_g_BonusItem					=	{}	--奖励：物品
x300863_g_BonusMoney6               =   0  --任务奖励荣誉

x300863_g_BonusChoiceItem           =   {}

x300863_g_Mis_Count   = 3				--每天可做的次数

--MisDescEnd

--任务目标顺序
x300863_MP_ISCOMPLETE				= 7	--代表完成 0未完成， 1完成

--任务物品
x300863_TARGET_ITEMID1				= -2

--x300863_SubmitNPCGUID				= 137501	--交任务NPC GUID

x300863_g_BusScriptId				= 300866

--子任务																	   
x300863_g_SubMissionID				=	{ { MissionId=7638, MissionName = "【个人】黑金押运", MissionTarget = "  将飞行器交给@npc_126129", MissionInfo = "\t一路小赚，押的少风险小啊。\n\t您可以通过王国押运官并抵押#G5两现银#W就可以领取一架#G飞行器#W，当您将飞行器安全护送到指定地点，系统将会#G返还押金#W并奖励您#G2两现银(银卡)#W工钱。\n\t您必须#R绑定密保卡后#W才能领取任务。\n\t有#G江湖请柬#W或#G朝廷请柬#W状态的玩家奖励为现银，否则奖励为银卡。\n",MissionHelp = "\t您必须#R绑定密保卡后#W才能领取任务，护送途中如果您离开飞行器过远，飞行器会意识到危险而#G停止前进#W。\n\t如果飞行器受到袭击并死亡，您的任务将失败，同时押金将被抢走。\n\t当您离开飞行器一段时间或掉线，飞行器将消失，此时#G任务失败#W，您的#G押金#W将丢失。", SubmitNPCGUID = 126129, iCostMoney =5000, BonusMoney = 2000, ExpBonus = 0,NPCName = "@npc_126129",Missionruse="将运金飞行器送到天山外城的@npc_128515处！",AcceptId = 281,SubmitId = 282,LevelLess	= 30,LevelMax = 40,BaoDanId=13080011 }, 
										  {	MissionId=7639, MissionName = "【个人】黑金押运", MissionTarget = "  将飞行器交给@npc_128515", MissionInfo = "\t略有风险，满足一点点小贪心。\n\t您可以通过王国押运官并抵押#G10两现银#W就可以领取一架#G飞行器#W，当您将飞行器安全护送到指定地点，系统将会#G返还押金#W并奖励您#G4两现银(银卡)#W工钱。\n\t您必须#R绑定密保卡后#W才能领取任务。\n\t有#G江湖请柬#W或#G朝廷请柬#W状态的玩家奖励为现银，否则奖励为银卡。\n",MissionHelp = "\t您必须#R绑定密保卡后#W才能领取任务，护送途中如果您离开飞行器过远，飞行器会意识到危险而#G停止前进#W。\n\t如果飞行器受到袭击并死亡，您的任务将失败，同时押金将被抢走。\n\t当您离开飞行器一段时间或掉线，飞行器将消失，此时#G任务失败#W，您的#G押金#W将丢失。",	SubmitNPCGUID = 128515, iCostMoney = 10000, BonusMoney = 4000, ExpBonus = 0,NPCName = "@npc_128515",Missionruse="将运金飞行器送到天山古道的@npc_128515处！",AcceptId = 291,SubmitId = 292,LevelLess = 40,LevelMax = 50,BaoDanId=13080012 },
										  {	MissionId=7640, MissionName = "【个人】黑金押运", MissionTarget = "  将飞行器交给@npc_128514", MissionInfo = "\t舍得，舍得，不舍哪会有得？下定决心才能大富大贵，风险大回报一定丰厚。\n\t您可以通过王国押运官并抵押#G15两现银#W就可以领取一架#G飞行器#W，当您将飞行器安全护送到指定地点，系统将会#G返还押金#W并奖励您#G6两现银(银卡)#W工钱。\n\t您必须#R绑定密保卡后#W才能领取任务。\n\t有#G江湖请柬#W或#G朝廷请柬#W状态的玩家奖励为现银，否则奖励为银卡。\n",MissionHelp = "\t您必须#R绑定密保卡后#W才能领取任务，护送途中如果您离开飞行器过远，飞行器会意识到危险而#G停止前进#W。\n\t如果飞行器受到袭击并死亡，您的任务将失败，同时押金将被抢走。\n\t当您离开飞行器一段时间或掉线，飞行器将消失，此时#G任务失败#W，您的#G押金#W将丢失。",SubmitNPCGUID = 128514, iCostMoney = 15000,BonusMoney = 6000,ExpBonus = 0,NPCName = "@npc_128514",Missionruse="将运金飞行器送到边塞的@npc_128514处！",AcceptId = 301,SubmitId = 302,LevelLess = 50,LevelMax = 60,BaoDanId=13080013 },
										  {	MissionId=7641, MissionName = "【个人】黑金押运", MissionTarget = "  将飞行器交给@npc_128514", MissionInfo = "\t舍得，舍得，不舍哪会有得？下定决心才能大富大贵，风险大回报一定丰厚。\n\t您可以通过王国押运官并抵押#G30两现银#W就可以领取一架#G飞行器#W，当您将飞行器安全护送到指定地点，系统将会#G返还押金#W并奖励您#G12两现银(银卡)#W工钱。\n\t您必须#R绑定密保卡后#W才能领取任务。\n\t有#G江湖请柬#W或#G朝廷请柬#W状态的玩家奖励为现银，否则奖励为银卡。\n",MissionHelp = "\t您必须#R绑定密保卡后#W才能领取任务，护送途中如果您离开飞行器过远，飞行器会意识到危险而#G停止前进#W。\n\t如果飞行器受到袭击并死亡，您的任务将失败，同时押金将被抢走。\n\t当您离开飞行器一段时间或掉线，飞行器将消失，此时#G任务失败#W，您的#G押金#W将丢失。",SubmitNPCGUID = 128514, iCostMoney = 30000,BonusMoney = 12000,ExpBonus = 0,NPCName = "@npc_128514",Missionruse="将运金飞行器送到边塞的@npc_128514处！",AcceptId = 761,SubmitId = 762,LevelLess = 60,LevelMax = 70,BaoDanId=13080014 },
										  { MissionId=7642, MissionName = "【个人】黑金押运", MissionTarget = "  将飞行器交给@npc_128514", MissionInfo = "\t舍得，舍得，不舍哪会有得？下定决心才能大富大贵，风险大回报一定丰厚。\n\t您可以通过王国押运官并抵押#G40两现银#W就可以领取一架#G飞行器#W，当您将飞行器安全护送到指定地点，系统将会#G返还押金#W并奖励您#G16两现银(银卡)#W工钱。\n\t您必须#R绑定密保卡后#W才能领取任务。\n\t有#G江湖请柬#W或#G朝廷请柬#W状态的玩家奖励为现银，否则奖励为银卡。\n",MissionHelp = "\t您必须#R绑定密保卡后#W才能领取任务，护送途中如果您离开飞行器过远，飞行器会意识到危险而#G停止前进#W。\n\t如果飞行器受到袭击并死亡，您的任务将失败，同时押金将被抢走。\n\t当您离开飞行器一段时间或掉线，飞行器将消失，此时#G任务失败#W，您的#G押金#W将丢失。",SubmitNPCGUID = 128514, iCostMoney = 40000,BonusMoney = 16000,ExpBonus = 0,NPCName = "@npc_128514",Missionruse="将运金飞行器送到边塞的@npc_128514处！",AcceptId = 771,SubmitId = 772,LevelLess = 70,LevelMax = 80,BaoDanId=13080015 },
										  { MissionId=7643, MissionName = "【个人】黑金押运", MissionTarget = "  将飞行器交给@npc_128514", MissionInfo = "\t舍得，舍得，不舍哪会有得？下定决心才能大富大贵，风险大回报一定丰厚。\n\t您可以通过王国押运官并抵押#G50两现银#W就可以领取一架#G飞行器#W，当您将飞行器安全护送到指定地点，系统将会#G返还押金#W并奖励您#G20两现银(银卡)#W工钱。\n\t您必须#R绑定密保卡后#W才能领取任务。\n\t有#G江湖请柬#W或#G朝廷请柬#W状态的玩家奖励为现银，否则奖励为银卡。\n",MissionHelp = "\t您必须#R绑定密保卡后#W才能领取任务，护送途中如果您离开飞行器过远，飞行器会意识到危险而#G停止前进#W。\n\t如果飞行器受到袭击并死亡，您的任务将失败，同时押金将被抢走。\n\t当您离开飞行器一段时间或掉线，飞行器将消失，此时#G任务失败#W，您的#G押金#W将丢失。",SubmitNPCGUID = 128514, iCostMoney = 50000,BonusMoney = 20000,ExpBonus = 0,NPCName = "@npc_128514",Missionruse="将运金飞行器送到边塞的@npc_128514处！",AcceptId = 781,SubmitId = 782,LevelLess = 80,LevelMax = 150,BaoDanId=13080016 },
										}
						
--**********************************
--列举事件
--**********************************
function x300863_ProcEnumEvent( sceneId, selfId, NPCId, MissionId )
	return 0;
end

--**********************************
--任务入口函数
--**********************************
function x300863_ProcEventEntry(sceneId, selfId, NPCId, MissionId,nExtIdx)	--点击该任务后执行此脚本
		
	local index = 1
	for i,itm in x300863_g_SubMissionID do
		if i == nExtIdx then
			MissionId = itm.MissionId
			index = i
			break
		end
	end

	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, MissionId);
	if(bHaveMission > 0) then
		local bDone = x300863_CheckSubmit(sceneId, selfId, NPCId, index);
		if(bDone > 0) then
			if nExtIdx ~= -1 then
				x300863_DispatchCompletedInfo( sceneId, selfId, NPCId,index) --完成任务显示
			end
		else
			if nExtIdx ~= -1 then
				x300863_DispatchContinueInfo( sceneId, selfId, NPCId,index ) --未完成任务显示
			end
		end
	else
		local npcGuid = GetMonsterGUID(sceneId,NPCId)
		if x300863_g_SubMissionID[index].SubmitNPCGUID ~= npcGuid then
			x300863_DispatchMissionInfo( sceneId, selfId, NPCId,index )	--任务信息显示
		else
			BeginQuestEvent(sceneId)

			--任务继续信息
			AddQuestText(sceneId,"你没有此任务！")
			EndQuestEvent()
			DispatchQuestEventList(sceneId,selfId,NPCId);
		end
	end
end

---------------------------------------------------------------------------------------------------
--检测接受条件
---------------------------------------------------------------------------------------------------
function x300863_ProcAcceptCheck( sceneId, selfId,MissionID )
	
	local bindCard = IsBindPWCard(sceneId, selfId)
	local bindPhone = IsBindPhone(sceneId, selfId)
	local PWCardEnable = PWCardEnable(sceneId, selfId)
		
	if PWCardEnable == 1 and bindCard == 0 and bindPhone == 0 then
		local Readme = "帐号绑定卡片密保或电话密保后您才能接受该任务,详细信息请参见官方网站帐号中心"	
		
		--BeginQuestEvent(sceneId)
		--AddQuestText(sceneId,Readme)
		--EndQuestEvent(sceneId)
		--DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,Readme,8,2)	

		ShowMsgBoxMibaoka(sceneId,selfId,0)
		return 0
	end
	if IsHideName(sceneId, selfId) > 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"抱歉，蒙面状态不能接此任务。")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 
	end
	
	for BaoDanId,BaoDanItm in x300863_g_SubMissionID do
		if HaveItem(sceneId, selfId, BaoDanItm.BaoDanId) > 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"有保单时不能在接此任务")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return 0
		end
	end

	if IsQuestFullNM( sceneId, selfId )==1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"可接任务数量已满")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end

	local money = GetMoney(sceneId, selfId,0)	
	local iCostMoney = 10000
	local LevelLess = x300863_g_SubMissionID[1].LevelLess
	local LevelMax = x300863_g_SubMissionID[1].LevelMax
	for i,itm in x300863_g_SubMissionID do
		if itm.MissionId == MissionID then
			iCostMoney = itm.iCostMoney
			LevelLess = itm.LevelLess
			LevelMax = itm.LevelMax
			break
		end
	end
	
	if money < iCostMoney then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "您身上的现银不足以支付押金，不能领取任务！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "您身上的现银不足以支付押金，不能领取任务！"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0;		
	end

	local level = GetLevel(sceneId,selfId);
	if ( level < LevelLess or level >= LevelMax ) then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "您的等级不能领取此任务！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "您的等级不能领取此任务！" 
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0;
	end
	
	if IsTeamFollow(sceneId, selfId) == 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "组队跟随状态下不可以接跑钱任务!");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "组队跟随状态下不可以接跑钱任务！" 
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end

	if IsBusMember(sceneId,selfId) == 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "您已处于护送/押运状态，无法领取新的押运任务！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "您已处于护送/押运状态，无法领取新的押运任务！" 
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end
	
	if x300863_GetDayCount(sceneId, selfId) >= x300863_g_Mis_Count then
	  	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您今天任务次数已满，请明天再来做吧！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "很抱歉，您今天任务次数已满，请明天再来做吧！" 
		Msg2Player(sceneId,selfId,Readme,8,2)
		return
	end

	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, MissionID);
	if(bHaveMission > 0) then
		return 0;
	else
				-- BeginQuestEvent(sceneId)
				-- AddQuestText(sceneId,"成功领取【个人】黑金押运任务！");
				-- EndQuestEvent(sceneId)
				-- DispatchQuestTips(sceneId,selfId)
		return 1;
	end
end

---------------------------------------------------------------------------------------------------
--接受条件
---------------------------------------------------------------------------------------------------
function x300863_ProcQuestAccept( sceneId, selfId,targetID,MissionID )
	if ( x300863_ProcAcceptCheck( sceneId, selfId,MissionID ) ~= 1 ) then
		
		return 0;
	end

	--//黑金任务答题Start
	if GetGameOpenById(1018)>0 then
		local nRet = CallScriptFunction(300824, "StartDati", sceneId, selfId, 1018);

		if nRet~=1 then
			return 0;
		end
	end
	--//黑金任务答题end
	
	for i,itm in x300863_g_SubMissionID do
		if MissionID == itm.MissionId then
			CallScriptFunction( x300863_g_BusScriptId, "OnCreateBus", sceneId, selfId ,MissionID,i)
			break
		end
	end

	
    
end

function  x300863_OnDatiFail(sceneId, selfId)

	if GetGameOpenById(1018)>0 then
		local Readme = "答题失败，记次一次"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)

		x300863_SetDayCount(sceneId, selfId)
	end
end

function x300863_OnHeiJinDatiSuccess(sceneId, selfId)
	local nLevel = GetLevel(sceneId, selfId)
	local index = 1
	local nMissionId=0;

	
	for i,itm in x300863_g_SubMissionID do
		if nLevel >= itm.LevelLess and nLevel<itm.LevelMax then
			nMissionId = itm.MissionId
			index = i
			break
		end
	end

	if nMissionId==0 then
		return
	end


	local PosX,PosZ = GetWorldPos(sceneId, selfId)
	local x=64
	local z=170

	local dis = (PosX-x)*(PosX-x)+(PosZ-z)*(PosZ-z)

	if dis>18 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "距离太远，不能接任务");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end

	

	if ( x300863_ProcAcceptCheck( sceneId, selfId,nMissionId ) ~= 1 ) then
		
		return 0;
	end

	for i,itm in x300863_g_SubMissionID do
		if nMissionId == itm.MissionId then
			CallScriptFunction( x300863_g_BusScriptId, "OnCreateBus", sceneId, selfId ,nMissionId,i)
			break
		end
	end

	AddExp(sceneId, selfId,500)  --答对给奖励

end

---------------------------------------------------------------------------------------------------
--检查任务是否可提交
---------------------------------------------------------------------------------------------------
function x300863_CheckSubmit(sceneId, selfId, NPCId, index)

	local npcGuid = GetMonsterGUID(sceneId,NPCId)

	if x300863_g_SubMissionID[index].SubmitNPCGUID ~= npcGuid then
		return 0
	end

	return 1;

end

---------------------------------------------------------------------------------------------------
--放弃任务
---------------------------------------------------------------------------------------------------
function x300863_ProcQuestAbandon(sceneId, selfId, MissionId)

	for i,itm in x300863_g_SubMissionID do
		local bHaveMission = IsHaveQuestNM(sceneId, selfId,itm.MissionId );
		if bHaveMission > 0 then

			if IsBusMember(sceneId, selfId) == 1 then
				local BusID  =  GetBusId(sceneId, selfId)
				if BusID ~= -1 and IsObjValid (sceneId,BusID) == 1 then
					--如果BUS还活着
					if GetBusQuestID(sceneId, BusID) == itm.MissionId then
						DeleteBus(sceneId, BusID,1)
					end
				else
					local Readme = "很抱歉，您与您的护送目标在同一场景才能放弃任务，请先找到您的护送目标再选择放弃！"
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "现在不能放弃任务！");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					Msg2Player(sceneId,selfId,Readme,8,2)
					return
				end				
			end
			
			--删除保单
			local ItemCnt = GetItemCount( sceneId, selfId, itm.BaoDanId )
			if ItemCnt > 0 then 
				DelItem(sceneId, selfId,itm.BaoDanId,1)
			end

			local misIndex = GetQuestIndexByID(sceneId, selfId, itm.MissionId); 
			DelQuest(sceneId, selfId, itm.MissionId);
							
			--放弃任务写日志
			GamePlayScriptLog(sceneId,selfId,itm.SubmitId+1)

			local Readme = "您放弃了任务：【个人】黑金押运"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, Readme);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,Readme,8,2)

			x300863_SetDayCount(sceneId, selfId)

			break
		end
	end

end

---------------------------------------------------------------------------------------------------
--获得奖励
---------------------------------------------------------------------------------------------------
function x300863_GetBonus( sceneId, selfId,NpcID, SelectId,MissionId )

	local BonusMoney = 0
	local ExpBonus = 0
	local iCostMoney = 0
	for i,itm in x300863_g_SubMissionID do
		if MissionId == itm.MissionId then
			BonusMoney = itm.BonusMoney
			ExpBonus = itm.ExpBonus
			iCostMoney = itm.iCostMoney
			break
		end
	end

	--奖励经验
    if ExpBonus > 0 then
		local level = GetLevel(sceneId, selfId)
		ExpBonus = ExpBonus * level
		AddExp(sceneId, selfId, ExpBonus);
		-- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, "您出色的完成了增值押运任务！");
		-- EndQuestEvent(sceneId)
		-- DispatchQuestTips(sceneId,selfId)
  		-- Msg2Player(sceneId,selfId,format("获得经验%d的奖励！", ExpBonus),8,2)
	end
--奖励金钱1
	if BonusMoney > 0 then

	local buffId1 = 9011
	local buffId2 = 9013
	local buffId3 = 9012
	local bHaveImpact1 = IsHaveSpecificImpact( sceneId, selfId, buffId1 )
	local bHaveImpact2 = IsHaveSpecificImpact( sceneId, selfId, buffId2 )
	local bHaveImpact3 = IsHaveSpecificImpact( sceneId, selfId, buffId3 )


	if bHaveImpact1==1 or bHaveImpact2 == 1 or bHaveImpact3 == 1 then
		BeginQuestEvent(sceneId)
		local  Money = floor(BonusMoney/1000)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"您完成了任务了：【个人】黑金押运");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"获得#R现银"..Money.."两#o的奖励");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"您完成了任务了：【个人】黑金押运#r获得#R现银"..Money.."两#o的奖励",8,2)

		local ret = CountryIsFortuneTime(sceneId,selfId,0)
		if ret == 1  then   -- 国运期间
			BonusMoney = BonusMoney * 2
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"国运期间额外获得#R现银"..Money.."两#o的奖励");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,"国运期间额外#r获得#R现银"..Money.."两#o的奖励",8,2)
		end

	    AddMoney( sceneId, selfId, 0, BonusMoney )


   else
       	BeginQuestEvent(sceneId)
		local  Money = floor(BonusMoney/1000)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"您完成了任务了：【个人】黑金押运");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"获得#R银卡"..Money.."两#o的奖励");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,"您完成了任务了：【个人】黑金押运#r获得#R银卡"..Money.."两#o的奖励",8,2)

		local ret = CountryIsFortuneTime(sceneId,selfId,0)
		if ret == 1  then   -- 国运期间
			BonusMoney = BonusMoney * 2
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"国运期间额外获得#R银卡"..Money.."两#o的奖励");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,"国运期间额外#r获得#R银卡"..Money.."两#o的奖励",8,2)
		end

	    AddMoney( sceneId, selfId, 1, BonusMoney )

		end
		
	end

	--返回押金
	if iCostMoney > 0 then
		AddMoney( sceneId, selfId, 0, iCostMoney )
		local  Money = floor(iCostMoney/1000)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"返还押金#R现银"..Money.."两");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,format("返还押金#R现银"..Money.."两"),8,2)
	end
		
 	--奖励固定物品
	for i, item in x300863_g_BonusItem do
 		BeginAddItem(sceneId)
		AddItem( sceneId, item.item, item.n )
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
			AddItemListToPlayer(sceneId,selfId)
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"物品栏已满，无法得到任务物品！")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end
    end

	--奖励可选物品
	for i, item in x300863_g_BonusChoiceItem do
	    if item.item == SelectId then
	        BeginAddItem(sceneId)
			AddItem( sceneId, item.item, item.n )
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"物品栏已满，无法得到任务物品！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end

			--获取完必，请返回，防止重复添加
			return
		end
    end

end

---------------------------------------------------------------------------------------------------
--提交任务，不管任务是否完成或是任务，显示任务继续信息或是任务完成信息
---------------------------------------------------------------------------------------------------
function x300863_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId,MissionId)

	if x300863_GetDayCount(sceneId, selfId) >= x300863_g_Mis_Count then
		return
	end

	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, MissionId);
	if(bHaveMission <= 0) then
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "你没有这个任务，不能提交！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "你没有这个任务，不能提交！" 
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0		
	end
	
	--镖车是否在有效距离
	local valid = IsValidMyselfBus(sceneId, selfId,MissionId)
	if valid == 0 then
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "飞行器离你太远了，不能提交！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "飞行器离你太远了，不能提交！" 
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end

	--判断是否有任务
	local bHaveMission = IsHaveQuestNM(sceneId, selfId, MissionId);
	if bHaveMission > 0 then

		local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId)

		local result = x300863_CheckPlayerBagFull(sceneId,selfId,selectRadioId)
		if result == 1 then
			if DelQuest(sceneId, selfId, MissionId) ~= 1 then
				return
			end

			for i,itm in x300863_g_SubMissionID do
				if MissionId == itm.MissionId then
					--交任务写日志
					GamePlayScriptLog(sceneId,selfId,itm.SubmitId)
					local ItemCnt = GetItemCount( sceneId, selfId, itm.BaoDanId )
					if ItemCnt > 0 then 
						DelItem(sceneId, selfId,itm.BaoDanId,1)
					end
					
					--增加国家资源
					local ret = CountryIsFortuneTime(sceneId,selfId,0)
					if ret == 1  then   -- 国运期间
						local addMoney = itm.iCostMoney * 0.4
						local addMoney1 =itm.iCostMoney * 0.4/1000
						 BeginQuestEvent(sceneId)
						AddQuestText(sceneId, "国运期间您为国家资源贡献了#R"..addMoney1.."两#O金钱");
						EndQuestEvent(sceneId)
						DispatchQuestTips(sceneId,selfId)
						local Readme = "国运期间您为国家资源贡献了#R"..addMoney1.."两#O金钱" 
						Msg2Player(sceneId,selfId,Readme,8,2)
						AddCountryResource( sceneId,selfId,2,addMoney,0 )
						
					end

					break;			
				end
			end
			
			x300863_GetBonus( sceneId,selfId,NPCId,selectRadioId,MissionId )

			x300863_SetDayCount(sceneId, selfId)
						
			local BusID  =  GetBusId(sceneId, selfId)
		  	if BusID ~= -1 and IsObjValid (sceneId,BusID) == 1 then
		     	--如果BUS还活着
				if GetBusQuestID(sceneId, BusID) == MissionId then
		  			DeleteBus(sceneId, BusID,1)
				end
		  	end 
		else
			BeginQuestEvent( sceneId )
			AddQuestText( sceneId,"包裹已满！")
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId);
		end

	else

		BeginQuestEvent( sceneId )
			AddQuestText( sceneId,"任务不存在，获取任务信息失败！")
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId);

		return
	end

end

---------------------------------------------------------------------------------------------------
--检查玩家包裹已满
---------------------------------------------------------------------------------------------------
function x300863_CheckPlayerBagFull( sceneId ,selfId,selectRadio )

	local result = 1

	local j = 0

	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满

	--普通的奖励检查
	BeginAddItem(sceneId)
	for j, item in x300863_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
    end

	for j, item in x300863_g_BonusChoiceItem do
		if item.item == selectRadio then
			AddItem( sceneId, item.item, item.n )
			break
		end
	end

	local ret = EndAddItem(sceneId,selfId)
	if ret <= 0 then
		result = 0
	end

	return result
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x300863_DispatchMissionInfo( sceneId, selfId, NPCId,index )

	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId,"#Y"..x300863_g_SubMissionID[index].MissionName)
		AddQuestText(sceneId,format("%s", x300863_g_SubMissionID[index].MissionInfo))
		AddQuestText(sceneId," ")

		--任务目标
		AddQuestText( sceneId,"#Y任务目标：")
		AddQuestText( sceneId,format("%s", x300863_g_SubMissionID[index].MissionTarget))
		AddQuestText( sceneId," ")

		--提示信息
		if x300863_g_MissionHelp ~= "" then

			AddQuestText(sceneId,"#Y任务提示：")
			AddQuestText(sceneId,format("%s", x300863_g_SubMissionID[index].MissionHelp))
			AddQuestText(sceneId," ")
		end

		--任务奖励信息

		--1、经验
		local ExpBonus = x300863_g_SubMissionID[index].ExpBonus
		if ExpBonus > 0 then
			local level = GetLevel(sceneId, selfId)
			ExpBonus = x300863_g_SubMissionID[index].ExpBonus * level
			AddQuestExpBonus(sceneId, ExpBonus )
		end

		--2、金钱1

		if x300863_g_SubMissionID[index].BonusMoney > 0 then
    		local buffId1 = 9011
	        local buffId2 = 9013
	        local buffId3 = 9012
	        local bHaveImpact1 = IsHaveSpecificImpact( sceneId, selfId, buffId1 )
	        local bHaveImpact2 = IsHaveSpecificImpact( sceneId, selfId, buffId2 )
	        local bHaveImpact3 = IsHaveSpecificImpact( sceneId, selfId, buffId3 )

	        if bHaveImpact1==1 or bHaveImpact2 == 1 or bHaveImpact3 == 1 then

			AddQuestMoneyBonus2(sceneId, x300863_g_SubMissionID[index].BonusMoney )
		    else 
		    AddQuestMoneyBonus1(sceneId, x300863_g_SubMissionID[index].BonusMoney )
		end
		end

		--荣誉值
		if x300863_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x300863_g_BonusMoney6 )
		end


		--5、固定物品
		for i, item in x300863_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	    end

		--6、可选物品
		for i, item in x300863_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	    end

	EndQuestEvent(sceneId)
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300863_g_ScriptId, x300863_g_SubMissionID[index].MissionId);
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300863_DispatchContinueInfo( sceneId, selfId, NPCId,index )
	
	BeginQuestEvent(sceneId)

		--任务继续信息
		AddQuestText(sceneId,"#Y"..x300863_g_SubMissionID[index].MissionName)
		AddQuestText(sceneId,format("%s", x300863_g_SubMissionID[index].MissionInfo))
		AddQuestText(sceneId," ")

		--任务目标
		AddQuestText( sceneId,"#Y完成情况：")
		AddQuestText(sceneId, "未完成");

  		--任务奖励信息

		--1、经验
		local ExpBonus = 0
		if ExpBonus> 0 then
			local level = GetLevel(sceneId, selfId)
			ExpBonus = x300863_g_SubMissionID[index].ExpBonus * level
			AddQuestExpBonus(sceneId, ExpBonus )
		end

		--2、金钱1
		if x300863_g_SubMissionID[index].BonusMoney > 0 then
		    local buffId1 = 9011
	        local buffId2 = 9013
	        local buffId3 = 9012
	        local bHaveImpact1 = IsHaveSpecificImpact( sceneId, selfId, buffId1 )
	        local bHaveImpact2 = IsHaveSpecificImpact( sceneId, selfId, buffId2 )
	        local bHaveImpact3 = IsHaveSpecificImpact( sceneId, selfId, buffId3 )

	        if bHaveImpact1==1 or bHaveImpact2 == 1 or bHaveImpact3 == 1 then
			AddQuestMoneyBonus2(sceneId, x300863_g_SubMissionID[index].BonusMoney )
			else
			AddQuestMoneyBonus(sceneId, x300863_g_SubMissionID[index].BonusMoney )

		end
		end

		--荣誉值
		if x300863_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x300863_g_BonusMoney6 )
		end


		--5、固定物品
		for i, item in x300863_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	    end

		--6、可选物品
		for i, item in x300863_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	    end

	    --任务提示信息
	EndQuestEvent()
	--DispatchQuestEventList(sceneId,selfId,NPCId);
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300863_g_ScriptId, x300863_g_SubMissionID[index].MissionId,0);

end

---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300863_DispatchCompletedInfo( sceneId, selfId, NPCId,index )
	
	BeginQuestEvent(sceneId)

		--任务完成信息
		AddQuestText(sceneId,"#Y"..x300863_g_SubMissionID[index].MissionName)
		AddQuestText(sceneId,x300863_g_MissionCompleted)
		AddQuestText(sceneId," ")

  		--任务奖励信息

		--1、经验
		local ExpBonus = x300863_g_SubMissionID[index].ExpBonus
		if ExpBonus> 0 then
			local level = GetLevel(sceneId, selfId)
			ExpBonus = (1000*0.1*level*15)
			AddQuestExpBonus(sceneId, ExpBonus )
		end

		--2、金钱1
		if x300863_g_SubMissionID[index].BonusMoney > 0 then
			local buffId1 = 9011
	        local buffId2 = 9013
	        local buffId3 = 9012
	        local bHaveImpact1 = IsHaveSpecificImpact( sceneId, selfId, buffId1 )
	        local bHaveImpact2 = IsHaveSpecificImpact( sceneId, selfId, buffId2 )
	        local bHaveImpact3 = IsHaveSpecificImpact( sceneId, selfId, buffId3 )

	        if bHaveImpact1==1 or bHaveImpact2 == 1 or bHaveImpact3 == 1 then

			AddQuestMoneyBonus2(sceneId, x300863_g_SubMissionID[index].BonusMoney )
			else
			AddQuestMoneyBonus1(sceneId, x300863_g_SubMissionID[index].BonusMoney )
        end
		end

		--荣誉值
		if x300863_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x300863_g_BonusMoney6 )
		end


		--5、固定物品
		for i, item in x300863_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	    end

		--6、可选物品
		for i, item in x300863_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	    end
	EndQuestEvent(sceneId)
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300863_g_ScriptId, x300863_g_SubMissionID[index].MissionId);

end


---------------------------------------------------------------------------------------------------
--单击NPC事件
---------------------------------------------------------------------------------------------------
function x300863_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	for i,itm in x300863_g_SubMissionID do
		local bHaveMission = IsHaveQuestNM(sceneId, selfId,itm.MissionId );

		if bHaveMission > 0 then
			if npcGuid == itm.SubmitNPCGUID then
				local state = GetQuestStateNM(sceneId,selfId,npcId,itm.MissionId)
				AddQuestNumText(sceneId, itm.MissionId, itm.MissionName,7,i);
				break;
			end
		end
	end
end

---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300863_QuestLogRefresh( sceneId, selfId, MissionId)

	for i,itm in x300863_g_SubMissionID do 
		local bHaveMission = IsHaveQuestNM(sceneId, selfId,itm.MissionId );
		if bHaveMission > 0 then
		
			BeginQuestEvent(sceneId)	
			local BonusMoney = itm.BonusMoney
			local ExpBonus = itm.ExpBonus
			local buffId1 = 9011
	        local buffId2 = 9013
	        local buffId3 = 9012
	        local bHaveImpact1 = IsHaveSpecificImpact( sceneId, selfId, buffId1 )
	        local bHaveImpact2 = IsHaveSpecificImpact( sceneId, selfId, buffId2 )
	        local bHaveImpact3 = IsHaveSpecificImpact( sceneId, selfId, buffId3 )

	        if bHaveImpact1==1 or bHaveImpact2 == 1 or bHaveImpact3 == 1 then

			AddQuestMoneyBonus2(sceneId,BonusMoney)
			else
			AddQuestMoneyBonus1(sceneId,BonusMoney)
            end

			AddQuestLogCustomText( sceneId,
									"",						-- 标题
									itm.MissionName,        -- 任务名字
									itm.MissionTarget,		--任务目标
									itm.NPCName,			--任务NPC
									itm.Missionruse,               --任务攻略
									itm.MissionInfo,	--任务描述
									""					--任务小提示
									)
			EndQuestEvent()
			DispatchQuestLogUpdate(sceneId, selfId, itm.MissionId);
			break
		end
	end

end

function x300863_ProcQuestLogRefresh( sceneId, selfId, MissionId)

	x300863_QuestLogRefresh( sceneId, selfId, MissionId );
end

function x300863_CostMoney( sceneId, selfId,MissionID )
	for i,itm in x300863_g_SubMissionID do
		if MissionID == itm.MissionId  then

			local cost = CostMoney( sceneId , selfId ,0, itm.iCostMoney,301 ) 
			if cost == -1 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "很抱歉，您包裹中的现银不够支付押金，无法接取任务!");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				local Readme = "很抱歉，您包裹中的现银不够支付押金，无法接取任务！" 
				Msg2Player(sceneId,selfId,Readme,8,2)
				return 0
			else
				local playerCountry =GetCurCountry(sceneId,selfId)
				local Country = "楼兰王国"
				if playerCountry == 0 then
					Country = "楼兰王国"
					elseif playerCountry == 1 then
					Country = "天山王国"
					elseif playerCountry == 2 then
					Country = "昆仑王国"
					elseif playerCountry == 3 then
					Country = "敦煌王国"
				end
--				local name = GetName(sceneId, selfId);
--				if i >2then
--					local  Money = floor(itm.iCostMoney/1000)
--					LuaAllScenceM2Wrold(sceneId,"#o"..Country.."的"..name.."花费了#R"..Money.."#W#o两现银领取了【个人】黑金黑金押运",2,1)	
--				elseif i >1 then
--					local  Money = floor(itm.iCostMoney/1000)
--					LuaAllScenceM2Wrold(sceneId,"#o"..Country.."的"..name.."花费了#R"..Money.."#W#o两现银领取了【个人】黑金黑金押运",2,1)	
--				end
				
				local str = "您接受了任务：【个人】黑金押运"
				
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"您接受了任务：【个人】黑金押运");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				local  Money = floor(itm.iCostMoney/1000)
				local Readme = "您接受了任务：【个人】黑金押运#r扣除押金#R"..Money.."两#o现银"
				Msg2Player(sceneId,selfId,Readme,8,2)
				return 1
			end	
			break
		end
	end
end


function x300863_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end


---------------------------------------------------------------------------------------------------
--取得此任务当天当前已完成次数
---------------------------------------------------------------------------------------------------
function x300863_GetDayCount(sceneId, selfId)

	if x300863_g_Mis_Count > 0 then

		local today = GetDayOfYear()

		local lastday = GetQuestData(sceneId, selfId, MD_PAO_QIAN_DATE[1], MD_PAO_QIAN_DATE[2], MD_PAO_QIAN_DATE[3])

		if lastday ~= today then
			return 0
		end

		local daycount =  GetQuestData(sceneId, selfId, MD_PAO_QIAN_COUNT[1], MD_PAO_QIAN_COUNT[2], MD_PAO_QIAN_COUNT[3])
		return daycount

	end

	return 0
end

---------------------------------------------------------------------------------------------------
--更新当天接任务次数
---------------------------------------------------------------------------------------------------
function x300863_SetDayCount(sceneId, selfId)
	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, MD_PAO_QIAN_DATE[1], MD_PAO_QIAN_DATE[2], MD_PAO_QIAN_DATE[3])

	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_PAO_QIAN_DATE[1], MD_PAO_QIAN_DATE[2], MD_PAO_QIAN_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_PAO_QIAN_COUNT[1], MD_PAO_QIAN_COUNT[2], MD_PAO_QIAN_COUNT[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, MD_PAO_QIAN_COUNT[1], MD_PAO_QIAN_COUNT[2], MD_PAO_QIAN_COUNT[3])
		SetQuestData(sceneId, selfId, MD_PAO_QIAN_COUNT[1], MD_PAO_QIAN_COUNT[2], MD_PAO_QIAN_COUNT[3], daycount+1)
	end
end