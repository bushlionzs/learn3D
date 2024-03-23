--MisDescBegin

x300611_g_ScriptId 	  = 300611
x300611_g_MissionKind 				= 	1                       --任务类型
x300611_g_ExtTarget					=	{ {type=20,n=1,target="马车"} }
x300611_MissionName = "【黑金】兑换理赔单"

--MisDescEnd	  
						
--子任务																	   
x300611_g_SubMissionID				=	{ { MissionId=7556,BaoDanId=13080011,LiPeiDanId=13080017 }, 
										  {	MissionId=7557,BaoDanId=13080012,LiPeiDanId=13080018 },
										  {	MissionId=7558,BaoDanId=13080013,LiPeiDanId=13080019 },
										  {	MissionId=7546,BaoDanId=13080014,LiPeiDanId=13080020 },
										  { MissionId=7547,BaoDanId=13080015,LiPeiDanId=13080021 },
										  { MissionId=7548,BaoDanId=13080016,LiPeiDanId=13080022 },
										}

function x300611_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	if x300611_GetBaoDanId(sceneId, selfId) > 0 then
		AddQuestNumText(sceneId,x300611_g_ScriptId,x300611_MissionName,3);
	end

end



--点击（按钮）点击该任务后执行此脚本
function x300611_ProcEventEntry( sceneId, selfId, targetId )

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"\t您可以在我这里把#G保险单#W兑换成#G理赔单#W，然后您就可以去找#G押运保险麦宝#W理赔了！")
	EndQuestEvent(sceneId)
	DispatchQuestInfo(sceneId, selfId, targetId, x300611_g_ScriptId, -1);

end

--判断玩家是否有镖车
function x300611_GetBaoDanId( sceneId, selfId )

	local BaoDanId = 0
	for i,itm in x300611_g_SubMissionID do
		if HaveItem(sceneId, selfId, itm.BaoDanId) > 0 then
			BaoDanId = i
			break
		end
	end

	return BaoDanId

end

--**********************************
--接受
--**********************************
function x300611_ProcAcceptCheck( sceneId, selfId, targetId )
	
	local BaoDanId = x300611_GetBaoDanId(sceneId, selfId)
	if BaoDanId == 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"很抱歉，你必需出示保单，才能进行理赔！")
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
		return	
	end

	local SubIndex = 0
	for i,itm in x300611_g_SubMissionID do
		if IsHaveQuest(sceneId, selfId, itm.MissionId) > 0 then
			SubIndex = i
			break;
		end
	end

	if SubIndex > 0 and SubIndex == BaoDanId then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"你可以直接回复黑金押运任务,不需要领取理赔单！")
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
		return				
	end

	--删除保单
	local ItemCnt = GetItemCount( sceneId, selfId, x300611_g_SubMissionID[BaoDanId].BaoDanId )
	if ItemCnt > 0 then 
		DelItem(sceneId, selfId,x300611_g_SubMissionID[BaoDanId].BaoDanId,ItemCnt)
	end

	--增加理赔单
	BeginAddItem( sceneId )
	AddItem( sceneId, x300611_g_SubMissionID[BaoDanId].LiPeiDanId, 1 )
	local ret = EndAddItem( sceneId, selfId )
	if ret > 0 then
		AddItemListToPlayer(sceneId,selfId)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"理赔单兑换成功，一路顺风呀！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

		local Readme = "理赔单兑换成功，一路顺风呀！" 
		Msg2Player(sceneId,selfId,Readme,8,2)

		return 1
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"背包空间不足，请整理背包！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end
	
end

--**********************************
--接受
--**********************************
function x300611_ProcAccept( sceneId, selfId )
end

--完成任务
--返回1代表成功，0代表交任务失败
function x300611_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
end


--********************************************************************
--放弃
--********************************************************************
function x300611_ProcQuestAbandon( sceneId, selfId,MissionId )
end

