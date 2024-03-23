--MisDescBegin

x300850_g_ScriptId 	  = 300850
x300850_g_MissionKind 				= 	1                       --任务类型
x300850_g_Mis_Count   = 1--每天可做的次数
x300850_g_ExtTarget					=	{ {type=20,n=1,target="马车"} }
x300850_g_MissionName = "托运官府马车"

--MisDescEnd

x300850_CostGold		= 1000

x300850_g_SubMissionID		=	{ {	MisID=7614,DestPosX = 94,DestPosZ = 91 },
								  {	MisID=7615,DestPosX = 163,DestPosZ = 127 },
								  {	MisID=7616,DestPosX = 55,DestPosZ = 42 	 },
								  {	MisID=7617,DestPosX = 55,DestPosZ = 42   },
								  {	MisID=7618,DestPosX = 55,DestPosZ = 42   },	
								  {	MisID=7619,DestPosX = 55,DestPosZ = 42   },											  
								}																		

function x300850_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
	AddQuestNumText(sceneId,x300850_g_ScriptId,x300850_g_MissionName,3,-1)

end



--点击（按钮）点击该任务后执行此脚本
function x300850_ProcEventEntry( sceneId, selfId, targetId, MissionId,nExtIdx )

	-- local bRet = x300850_IsCanAccept( sceneId, selfId )

	-- if bRet == 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t当您领取官府押运后，并花费#Y1两金卡（现金）#W我们就能将官府马车传送到距离目的地很近的地方。#r\t选择现金消费，您可以按B键打开包裹界面，在#G优先使用#W#Y现金/金卡#W处打上对勾即可。");
		EndQuestEvent(sceneId)
		DispatchQuestInfo(sceneId, selfId, targetId, x300850_g_ScriptId,  -1);
		return
	-- end
	-- if GetGoldMode( sceneId, selfId ) == 1 then
				-- 现金模式
				-- if GetMoney(sceneId, selfId,2) < x300850_CostGold then
					-- BeginQuestEvent(sceneId)
					-- AddQuestText(sceneId, "很抱歉，您身上携带的现金不够支付本次托运费用。");
					-- EndQuestEvent(sceneId)
					-- DispatchQuestTips(sceneId,selfId)
					-- Msg2Player(sceneId,selfId,"很抱歉，您身上携带的现金不够支付本次托运费用。",8,2)	
					-- return -2
				-- end
			-- else 
				-- 金卡模式
				-- if GetMoney(sceneId, selfId,3) < x300850_CostGold then
					-- BeginQuestEvent(sceneId)
					-- AddQuestText(sceneId, "很抱歉，您身上携带的金卡不够支付本次托运费用。");
					-- EndQuestEvent(sceneId)
					-- DispatchQuestTips(sceneId,selfId)
					-- Msg2Player(sceneId,selfId,"很抱歉，您身上携带的金卡不够支付本次托运费用。",8,2)	
					-- return -2
				-- end
			-- end

end

--检查是否能接受此任务
--返回值：-2--现金不够  -1--没有相关任务 0--镖车不在有效距离	1--可以接受任务
function x300850_IsCanAccept( sceneId, selfId )
	
	local bHaveMission = 0
	for i,itm in x300850_g_SubMissionID do

		bHaveMission = IsHaveQuestNM(sceneId, selfId,itm.MisID )
		if bHaveMission > 0 then
			local valid = IsValidMyselfBus(sceneId, selfId,itm.MisID)
			if valid == 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "很抱歉，您的马车没在附近，无法托运,请找到马车再来。");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				Msg2Player(sceneId,selfId,"很抱歉，您的马车没在附近，无法托运,请找到马车再来。",8,2)
				return 0
			end
		
			--得到玩家现金消费模式
			if GetGoldMode( sceneId, selfId ) == 1 then
				-- 现金模式
				if GetMoney(sceneId, selfId,2) < x300850_CostGold then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "很抱歉，您身上携带的现金不够支付本次托运费用。");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					Msg2Player(sceneId,selfId,"很抱歉，您身上携带的现金不够支付本次托运费用。",8,2)	
					return -2
				end
			else 
				-- 金卡模式
				if GetMoney(sceneId, selfId,3) < x300850_CostGold then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "很抱歉，您身上携带的金卡不够支付本次托运费用。");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					Msg2Player(sceneId,selfId,"很抱歉，您身上携带的金卡不够支付本次托运费用。",8,2)	
					return -2
				end
			end

			return 1
						
		end

	end

	-- if IsHaveQuestNM(sceneId, selfId,7001 ) > 0 then
		-- 有7001
		-- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, "很抱歉，我们只接受跨越到边境的官府马车托运生意。");
		-- EndQuestEvent(sceneId)
		-- DispatchQuestTips(sceneId,selfId)
		-- Msg2Player(sceneId,selfId,"很抱歉，我们只接受到达#G中转商#W和#G大掌柜处#W托运生意。",8,2)
	-- else
		--没有任何官府押运
		 BeginQuestEvent(sceneId)
		 AddQuestText(sceneId, "很抱歉，您必须先领取官府马车，才能进行托运！");
		 EndQuestEvent(sceneId)
		 DispatchQuestTips(sceneId,selfId)
		 Msg2Player(sceneId,selfId,"很抱歉，您必须先领取官府马车，才能进行托运！",8,2)
	-- end

	return -1;

end


--**********************************
--接受
--**********************************
function x300850_ProcAcceptCheck( sceneId, selfId, targetId, MissionId )
				
	local bRet = x300850_IsCanAccept( sceneId, selfId )

	if bRet ~= 1 then
		return
	end

	--得到玩家现金消费模式
	if GetGoldMode( sceneId, selfId ) == 1 then
		--现金模式
		if CostMoney( sceneId, selfId, 2,x300850_CostGold,301 ) == -1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "很抱歉，您身上携带的现金不够支付本次托运费用。");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,"很抱歉，您身上携带的现金不够支付本次托运费用。",8,2)	
			return
		end
	else 
		--金卡模式
		if CostMoney( sceneId, selfId, 3,x300850_CostGold,301 ) == -1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "很抱歉，您身上携带的金卡不够支付本次托运费用。");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,"很抱歉，您身上携带的金卡不够支付本次托运费用。",8,2)	
			return
		end
	end

	local InBus = IsBusMember(sceneId, selfId)

	if InBus ~= 1 then
		return
	end

	local BusId = GetBusId(sceneId, selfId)

	for i,itm in x300850_g_SubMissionID do

		local bHaveMission = IsHaveQuestNM(sceneId, selfId,itm.MisID )
		if bHaveMission > 0 then
			if i == 1 then
				if BusId ~=-1 then
					ReadyBusChangeScene(sceneId, 258,BusId)
					NewWorld(sceneId, selfId, 258, itm.DestPosX, itm.DestPosZ, x300850_g_ScriptId)	
					DeleteBus(sceneId, BusId,0)		
				end
			elseif i == 2 then
				if BusId ~=-1 then
					ReadyBusChangeScene(sceneId, 286,BusId)
					NewWorld(sceneId, selfId, 286, itm.DestPosX, itm.DestPosZ, x300850_g_ScriptId)	
					DeleteBus(sceneId, BusId,0)		
				end
			else
				if BusId ~=-1 then
					ReadyBusChangeScene(sceneId, 251,BusId)
					NewWorld(sceneId, selfId, 251, itm.DestPosX, itm.DestPosZ, x300850_g_ScriptId)	
					DeleteBus(sceneId, BusId,0)			
				end
			end
		end
	end

end


--**********************************
--接受
--**********************************
function x300850_ProcAccept( sceneId, selfId )	
end

--完成任务
--返回1代表成功，0代表交任务失败
function x300850_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
end


--********************************************************************
--放弃
--********************************************************************
function x300850_ProcQuestAbandon( sceneId, selfId,MissionId )  	
end


function x300850_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
end

---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300850_QuestLogRefresh( sceneId, selfId, MissionId)
end

function x300850_ProcQuestLogRefresh( sceneId, selfId, MissionId)

end




