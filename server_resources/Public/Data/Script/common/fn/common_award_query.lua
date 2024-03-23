
x561101_g_ScriptId = 561101
x561101_g_MissionName = "领取奖励补偿"

--一次最多显示的奖品数
x561101_g_MaxOnceAwardNum = 5	

--奖品最大索引
x561101_g_MaxAwardCount = 2000

x561101_g_GetAwardScript = 561103

--点击（NPC）
function x561101_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x561101_g_ScriptId,x561101_g_MissionName,3,-1)
	
end



--点击（按钮）点击该任务后执行此脚本
function x561101_ProcEventEntry( sceneId, selfId, targetId,state,index )	

	if index == -1 then
		
		for i=0, x561101_g_MaxOnceAwardNum-1 do
			SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_AWARE_INDEX1+i, -1 )
			SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_AWARE_DB_INDEX1+i, -1 )
			SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_AWARE_NUM1+i, -1 )
		end

		--查询奖品信息
		QueryAwardInfo( sceneId, selfId )
		--记录当前领奖NPCID，以便于返回定位
		SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_NPCID,targetId  )

	else
		CallScriptFunction( x561101_g_GetAwardScript, "ProcEventEntry", sceneId, selfId ,targetId,state,index) 
	end

end

--显示奖品信息
function x561101_OnShowAwardInfo( sceneId, selfId, awardNum, awardType )

	if GetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_NPCID ) ~= -1 then
			
		if awardNum < 1 then
			--没有奖励
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y奖品领取")
			AddQuestText(sceneId,"\t很抱歉，没有查询到您的奖励记录！请稍后再来！")
			EndQuestEvent(sceneId)
			DispatchQuestEventList( sceneId,selfId,GetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_NPCID ) )
			return 
		end

		BeginQuestEvent(sceneId)

        local bShow = 0
		for i=0, x561101_g_MaxOnceAwardNum-1 do
			--判断奖品索引是否有效
			local index = GetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_AWARE_INDEX1+i )

			if index >= 0 and index < x561101_g_MaxAwardCount then
			
				if awardType == 1 then
					--CDKEY领奖， 不需要玩家在次操作
					local haveSpace = CallScriptFunction( x561101_g_GetAwardScript, "HaveBagSpace", sceneId, selfId ,RD_HUMAN_AWARE_INDEX1+i, RD_HUMAN_CURR_AWARD_NPCID ) 
					if haveSpace == 1 then
						local dbIndex = GetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_AWARE_INDEX1+i+x561101_g_MaxOnceAwardNum )
						SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_INDEX, dbIndex )
	
						CallScriptFunction( x561101_g_GetAwardScript, "ProcAccept", sceneId, selfId )
					end
					
					return 
				end
				
				local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,index )--根据索引从表中得到奖励
				local ItemNum = GetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_AWARE_NUM1+i )

				if ItemNum > 1 then
					title = format("%s * %d",title,ItemNum)
				end
				if bShow == 0 then
    				AddQuestText(sceneId,"#Y奖品领取")
    				AddQuestText(sceneId,"\t您可以领取以下奖品：")
    				bShow = 1
				end
				AddQuestNumText(sceneId,x561101_g_ScriptId,title,0,RD_HUMAN_AWARE_INDEX1+i)
			end
		end

		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,GetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_NPCID ) )
	end

end

--点击（确定）
function x561101_ProcAcceptCheck( sceneId, selfId, NPCId )
	
	--BeginQuestEvent(sceneId);AddQuestText(sceneId,"按钮A对应的任务描述");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId)	
	--Msg2Player(sceneId,selfId,"按钮A对应的任务描述",8,2)

end



--**********************************
--接受
--**********************************
function x561101_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x561101_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x561101_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x561101_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x561101_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x561101_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x561101_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x561101_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end