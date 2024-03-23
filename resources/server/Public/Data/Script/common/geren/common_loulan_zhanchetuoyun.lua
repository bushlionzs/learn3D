--MisDescBegin

x300762_g_ScriptId 	  = 300762
x300762_g_MissionKind 				= 	1                       --任务类型
x300762_g_Mis_Count   = 1--每天可做的次数
x300762_g_ExtTarget					=	{ {type=20,n=1,target="战车"} }
x300762_g_MissionName = "托运战车"

--MisDescEnd

x300762_CostGold		= 1000

x300762_g_MissionId = 7031
x300762_g_DestPosX = 162
x300762_g_DestPosZ = 165
				

function x300762_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x300762_g_ScriptId,x300762_g_MissionName,3,-1)

end




--点击（按钮）点击该任务后执行此脚本
function x300762_ProcEventEntry( sceneId, selfId, targetId, MissionId,nExtIdx )

	-- local bRet = x300762_IsCanAccept( sceneId, selfId )

	-- if bRet == 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t当您领取战车护送后，并花费#Y1两金卡（现金）#W我们就能将战车传送到距离目的地很近的地方。#r\t选择现金消费，您可以按B键打开包裹界面，在#G优先使用#W#Y现金/金卡#W处打上对勾即可。");
		EndQuestEvent(sceneId)
		DispatchQuestInfo(sceneId, selfId, targetId, x300762_g_ScriptId,  -1);
		return
	-- end
	-- if GetGoldMode( sceneId, selfId ) == 1 then
				-- 现金模式
				-- if GetMoney(sceneId, selfId,2) < x300762_CostGold then
					-- BeginQuestEvent(sceneId)
					-- AddQuestText(sceneId, "很抱歉，您身上携带的现金不够支付本次托运费用。");
					-- EndQuestEvent(sceneId)
					-- DispatchQuestTips(sceneId,selfId)
					-- Msg2Player(sceneId,selfId,"很抱歉，您身上携带的现金不够支付本次托运费用。",8,2)
					-- return -2
				-- end
			-- else
				-- 金卡模式
				-- if GetMoney(sceneId, selfId,3) < x300762_CostGold then
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
function x300762_IsCanAccept( sceneId, selfId )
	
	local bHaveMission = 0
	bHaveMission = IsHaveQuestNM(sceneId, selfId,x300762_g_MissionId )
	if bHaveMission > 0 then
		local valid = IsValidMyselfBus(sceneId, selfId,x300762_g_MissionId)
		if valid == 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "很抱歉，您的战车没在附近，无法托运,请找到战车再来。");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,"很抱歉，您的战车没在附近，无法托运,请找到战车再来。",8,2)
			return 0
		end
	


		--得到玩家现金消费模式
		if GetGoldMode( sceneId, selfId ) == 1 then
			-- 现金模式
			if GetMoney(sceneId, selfId,2) < x300762_CostGold then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "很抱歉，您身上携带的现金不够支付本次托运费用。");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				Msg2Player(sceneId,selfId,"很抱歉，您身上携带的现金不够支付本次托运费用。",8,2)	
				return -2
			end
		else 
			-- 金卡模式
			if GetMoney(sceneId, selfId,3) < x300762_CostGold then
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

	-- if IsHaveQuestNM(sceneId, selfId,7001 ) > 0 then
		-- 有7001
		-- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, "很抱歉，我们只接受跨越到边境的战车托运生意。");
		-- EndQuestEvent(sceneId)
		-- DispatchQuestTips(sceneId,selfId)
		-- Msg2Player(sceneId,selfId,"很抱歉，我们只接受到达#G中转商#W和#G大掌柜处#W托运生意。",8,2)
	-- else
		--没有任何官府押运
		 BeginQuestEvent(sceneId)
		 AddQuestText(sceneId, "很抱歉，您必须先领取战车，才能进行托运！");
		 EndQuestEvent(sceneId)
		 DispatchQuestTips(sceneId,selfId)
		 Msg2Player(sceneId,selfId,"很抱歉，您必须先领取战车，才能进行托运！",8,2)
	-- end

	return -1;

end


--**********************************
--接受
--**********************************
function x300762_ProcAcceptCheck( sceneId, selfId, targetId, MissionId )
				
	local bRet = x300762_IsCanAccept( sceneId, selfId )

	if bRet ~= 1 then
		return
	end

	--得到玩家现金消费模式
	if GetGoldMode( sceneId, selfId ) == 1 then
		--现金模式
		if CostMoney( sceneId, selfId, 2,x300762_CostGold,301 ) == -1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "很抱歉，您身上携带的现金不够支付本次托运费用。");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,"很抱歉，您身上携带的现金不够支付本次托运费用。",8,2)	
			return
		end
	else 
		--金卡模式
		if CostMoney( sceneId, selfId, 3,x300762_CostGold,301 ) == -1 then
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

	local bHaveMission = IsHaveQuestNM(sceneId, selfId,x300762_g_MissionId )
	if bHaveMission > 0 then

		if BusId ~=-1 then
			ReadyBusChangeScene(sceneId, 58,BusId)
			NewWorld(sceneId, selfId, 58, x300762_g_DestPosX, x300762_g_DestPosZ, x300762_g_ScriptId)	
			DeleteBus(sceneId, BusId,0)			
		end

		-- if BusId ~=-1 then
			-- SetBusPos(sceneId,BusId,x300762_g_DestPosX, x300762_g_DestPosZ)
			-- SetPos(sceneId,selfId,x300762_g_DestPosX, x300762_g_DestPosZ)		
		-- end
	end

end


--**********************************
--接受
--**********************************
function x300762_ProcAccept( sceneId, selfId )	
end

--完成任务
--返回1代表成功，0代表交任务失败
function x300762_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
end


--********************************************************************
--放弃
--********************************************************************
function x300762_ProcQuestAbandon( sceneId, selfId,MissionId )  	
end


function x300762_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
end

---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300762_QuestLogRefresh( sceneId, selfId, MissionId)
end

function x300762_ProcQuestLogRefresh( sceneId, selfId, MissionId)

end




