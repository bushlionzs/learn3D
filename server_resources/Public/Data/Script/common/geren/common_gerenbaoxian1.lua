--MisDescBegin

x300610_g_ScriptId 	  = 300610
x300610_g_MissionKind 				= 	1                       --任务类型
x300610_g_ExtTarget					=	{ {type=20,n=1,target="马车"} }
x300610_MissionName = "【黑金】保险"

--MisDescEnd	  
						
--子任务																	   
x300610_g_SubMissionID				=	{ { MissionId=7556,BaoDanId=13080011,iCostMoney=250 }, 
										  {	MissionId=7557,BaoDanId=13080012,iCostMoney=500 },
										  {	MissionId=7558,BaoDanId=13080013,iCostMoney=750 },
										  {	MissionId=7546,BaoDanId=13080014,iCostMoney=1500 },
										  { MissionId=7547,BaoDanId=13080015,iCostMoney=2000 },
										  { MissionId=7548,BaoDanId=13080016,iCostMoney=2500 },
										}

function x300610_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	if x300610_IsHaveCashbox(sceneId, selfId) == 1 then
		AddQuestNumText(sceneId,x300610_g_ScriptId,x300610_MissionName,3);
	end

end



--点击（按钮）点击该任务后执行此脚本
function x300610_ProcEventEntry( sceneId, selfId, targetId )

	BeginQuestEvent(sceneId)
	local Readme_1 ="\t世上没有白吃的午餐，如果您对您押运的黑金进行投保的话，您需要付给我#G押金的5%#W做为保金。#r"
	local Readme_2 ="\t无论您押运黑金成功与否，您缴付的保金都不会退还给您。#r"
	local Readme_3 ="\t如果您押运黑金时。您的飞行器被敌人劫走，或因异常情况飞行器丢失。您都可以在黑金押运的任务回复人那里提交您的#G保单#W，换取#G理赔单#W。#r"
	local Readme_4 ="\t您领取了#G理赔单#W后，可以回到我这里#G提交理赔单#W，如果您提交的#G理赔单#W没有问题，我们将对您进行#G赔付#W，赔付的金额为您领取黑金押运任务时的#G押金的一半#W。#r"
	local Readme_5 ="\t少侠，您现在需要马上进行投保吗？"
	
	local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
	AddQuestText(sceneId,Readme)
	EndQuestEvent(sceneId)
	DispatchQuestInfo(sceneId, selfId, targetId, x300610_g_ScriptId, -1);

end

--判断玩家是否有镖车
function x300610_IsHaveCashbox( sceneId, selfId )

	local BusObjId = GetBusId(sceneId,selfId)
	if BusObjId ~= -1 then
		if GetBusType(sceneId,BusObjId) == 0 then --普通镖车
			return 1
		end
	end

	return 0

end

--**********************************
--接受
--**********************************
function x300610_ProcAcceptCheck( sceneId, selfId, targetId )

	if x300610_IsHaveCashbox(sceneId, selfId) == 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"很抱歉，您不在护送状态不能参加投保！")
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
		Msg2Player(sceneId,selfId,"很抱歉，您不在护送状态不能参加投保！",8,2)
		return
	end

	local SubIndex = 0
	for i,itm in x300610_g_SubMissionID do
		if IsHaveQuest(sceneId, selfId, itm.MissionId) > 0 then
			SubIndex = i
			break;
		end
	end

	if SubIndex == 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"很抱歉，只有领取了黑金押运任务才能参加投保！")
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
		Msg2Player(sceneId,selfId,"很抱歉，只有领取了黑金押运任务才能参加投保！",8,2)
		return		
	end

	local IsHaveBaoDan = 0
	for i,itm in x300610_g_SubMissionID do
		if HaveItem(sceneId, selfId, itm.BaoDanId) > 0 then
			IsHaveBaoDan = 1
			break;
		end
	end

	if IsHaveBaoDan == 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"很抱歉，您的身上已经有保单了，请先兑换理赔单赔付后才能再次申请投保！")
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
		Msg2Player(sceneId,selfId,"很抱歉，您的身上已经有保单了，请先兑换理赔单赔付后才能再次申请投保！",8,2)
		return		
	end

	local money = GetMoney(sceneId, selfId,0)	
	if money < x300610_g_SubMissionID[SubIndex].iCostMoney then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"很抱歉，您身上的现银不足以支付保险！")
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
		Msg2Player(sceneId,selfId,"很抱歉，您身上的现银不足以支付保险！",8,2)
		return
	end

	BeginAddItem( sceneId )
	AddItem( sceneId, x300610_g_SubMissionID[SubIndex].BaoDanId, 1 )
	local ret = EndAddItem( sceneId, selfId )
	if ret > 0 then
		AddItemListToPlayer(sceneId,selfId)
		local num = CostMoney( sceneId , selfId ,0, x300610_g_SubMissionID[SubIndex].iCostMoney,301)	--成功返回1 失败返回-1
		if num == -1 then
			--不应该出现这种情况
			return
		end

		local Readme = "投保成功,扣除保费现银#R#{_MONEY"..x300610_g_SubMissionID[SubIndex].iCostMoney.."}" 
		Msg2Player(sceneId,selfId,Readme,8,2)

		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"投保成功！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId);
		--Msg2Player(sceneId,selfId, "扣除保费现银#{_MONEY"..x300610_g_SubMissionID[SubIndex].iCostMoney.."}",8,2)
		return 1
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"很抱歉，您的背包空间不足，请整理背包！")
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
		Msg2Player(sceneId,selfId, "很抱歉，您的背包空间不足，请整理背包！",8,2)
		return 0
	end

end

--**********************************
--接受
--**********************************
function x300610_ProcAccept( sceneId, selfId )
end

--完成任务
--返回1代表成功，0代表交任务失败
function x300610_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
end


--********************************************************************
--放弃
--********************************************************************
function x300610_ProcQuestAbandon( sceneId, selfId,MissionId )
end

