--凤翔府到大都南

x550501_g_ScriptId = 550501
x550501_g_TransPos0	=	"loulanmachang2wangcheng"  
x550501_g_TransPos1	=	"laiyinmachang2wangcheng"  
x550501_g_TransPos2	=	"kunlunmachang2wangcheng"  
x550501_g_TransPos3	=	"dunhuangmachang2wangcheng"
x550501_g_Notice = "您的等级还不足#R40级#Y，无法进入大都！"

--玩家进入一个 area 时触发
function x550501_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	------------------------------------------------------
	if IsHaveSpecificImpact( sceneId, selfId, 7610) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7607) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7608) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7605) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7616) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7613) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7614) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7611) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7622) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7619) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7620) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7617) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7628) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7625) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7626) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7623) == 1 then
		Msg2Player(sceneId,selfId,"很抱歉，未完成铁人三项任务时无法通往其他场景！",8,2)
		return
	end
	--以上用于铁人三项禁止传送的处理
  local nLevel = GetLevel(sceneId, selfId)                          
  if nLevel < 40 then                                                
  		Msg2Player(sceneId,selfId,"#Y"..x550501_g_Notice.."#W",4,3)    
  		return                                                         
  end  
 	--以上用于等级判断  
	local selfType = GetObjType(sceneId, selfId)
	
	if selfType == 9 then	--Bus进入区域 把bus和bus里的人跨场景
		local busType = GetBusType(sceneId, selfId)
		if busType == 1 then --BUS_TYPE_NORMAL
			local memberCount = GetBusMemberCount(sceneId, selfId)
			ReadyBusChangeScene(sceneId, sceneId - 1,selfId)--注意：此步骤是必需的.BUS切换场景，要先做些准备工作,
			for	i = 0, memberCount - 1 do
				local ObjID = GetBusMemberObjId(sceneId, selfId, i)
				x550501_TransToPosition(sceneId, ObjID)
			end
			--删除BUS,但乘员仍在车上
			DeleteBus(sceneId, selfId,0)
			return
		end
	elseif selfType == 1 then	--玩家
			
		local busId = GetBusId(sceneId, selfId)
		if busId ~= -1 then
			local busType = GetObjType(sceneId, busId)
			if busType == 3 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "很抱歉，护送目标感到危险，拒绝进入该场景！");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return	
			end

			if busType == 0 or busType == 2 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "很抱歉，护送目标感到危险，拒绝进入该场景！");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return	
			end
			
			local IsInDist = 0
			local busType = GetBusType(sceneId, busId)
			if busType == 0 then		--个人镖车
				--判断距离	
				IsInDist = IsValidMyselfBus(sceneId,selfId)
			elseif busType == 2 then	--帮会镖车
				IsInDist = IsValidGuildBus(sceneId,selfId)		
			elseif busType == 3 then	--护送任务
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "你正在护送，不能这么做！");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return			
			end
			
			if IsInDist == 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "你的护送目标离你太远了，不能这么做！");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return
			end
				
			local memberCount = GetBusMemberCount(sceneId, busId)
			ReadyBusChangeScene(sceneId, sceneId + 1, busId)--注意：此步骤是必需的.BUS切换场景，要先做些准备工作,
			for	i = 0, memberCount - 1 do
				local ObjID = GetBusMemberObjId(sceneId, busId, i)
				x550501_TransToPosition(sceneId, ObjID)
			end
			--删除BUS,但乘员仍在车上
			DeleteBus(sceneId, busId,0)
			return
		end

--		local isBusMember = IsBusMember(sceneId, selfId)
--		if isBusMember == 1 then
--			return
--		end
	end
	
	x550501_TransToPosition(sceneId, selfId)

end

function x550501_TransToPosition(sceneId, selfId)

	local guo = GetCurCountry(sceneId,selfId)
	
	if guo == 0 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550501_g_TransPos0)
		
		elseif guo == 1 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550501_g_TransPos1)
		
		elseif guo == 2 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550501_g_TransPos2)
		
		elseif guo == 3 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550501_g_TransPos3)
	
	end
	
end

--玩家在一个 area 呆了一段时间没走则定时触发
function x550501_ProcTiming( sceneId, monsterobjid )

end

--玩家离开一个 area 时触发
function x550501_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550501_ProcEventEntry( sceneId, monsterobjid )

end