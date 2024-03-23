
x580071_g_ScriptId = 580071
x580071_g_MissionName = "领取经验包"

--一次最多显示的奖品数
x580071_g_MaxOnceAwardNum = 5
x580071_g_5070Exp = 352800
x580071_g_7090Exp = 554400

--点击（NPC）
function x580071_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	return 0
	
end



--点击（按钮）点击该任务后执行此脚本
function x580071_ProcEventEntry( sceneId, selfId, targetId,state,index )	
	
	--未判断背包是否有足够空间

	x580071_DispatchMissionInfo( sceneId, selfId, targetId,index)

end

function x580071_DispatchMissionInfo( sceneId, selfId, targetId,index)

	SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_INDEX, index )

	local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,index )--根据索引从表中得到奖励
	local str = format("%s \n  %s",title,text)

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,str)
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	DispatchQuestInfo(sceneId, selfId, targetId, x580071_g_ScriptId, -1);

end

--领奖
function x580071_AddAward( sceneId, selfId,itemNum,index, dbIndex )

	local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,index )--根据索引从表中得到奖励
	local nLevel = GetLevel(sceneId,selfId)
	local nExp = 0

	if nLevel >= 60 and nLevel < 70 then
		nExp = nLevel*x580071_g_5070Exp*itemNum
		AddExpAutoLevelup(sceneId,selfId,nExp)
			--领奖成功
		BeginQuestEvent(sceneId)
		local DoneMSG = format("恭喜您，您获得了%d点经验值",nExp)
		AddQuestText(sceneId,DoneMSG)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		
		--写成功LOG
		local logFmtMsg         = "%u,%d,\"%s\",%d,%d,%d,%d,%d" --GUID，世界ID，姓名，等级，当前场景，DBIndex,ItemIndex,成功(1) / 失败(0)
		local logMsg = format(logFmtMsg,GetPlayerGUID( sceneId,selfId ),GetWorldId(sceneId,selfId),GetName( sceneId,selfId ),GetLevel(sceneId,selfId),sceneId,dbIndex,index,1)
		WriteLog(16,logMsg)

	elseif nLevel >= 70 and nLevel < 85 then
		nExp = nLevel*x580071_g_7090Exp*itemNum
		AddExpAutoLevelup(sceneId,selfId,nExp)
		
		BeginQuestEvent(sceneId)
		local DoneMSG = format("恭喜您，您获得了%d点经验值",nExp)
		AddQuestText(sceneId,DoneMSG)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	else
		BeginQuestEvent(sceneId)
		local DoneMSG = "对不起，您的等级已经超过了奖励范围，无法获得奖励！"
		AddQuestText(sceneId,DoneMSG)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end

end



--**********************************
--接受
--**********************************
function x580071_ProcAccept( sceneId, selfId )
end

function x580071_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end
--点击（确定）
function x580071_ProcQuestAccept( sceneId, selfId, NPCId )
end

--**********************************
--放弃
--**********************************
function x580071_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x580071_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x580071_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x580071_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x580071_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件