--个人帮贡补偿

x580058_g_ScriptId = 580058
x580058_g_MissionName = "领取奖品"

--一次最多显示的奖品数
x580058_g_MaxOnceAwardNum = 5

x580058_g_ItemBonus =	{
						}

--点击（NPC）
function x580058_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	return 0
	
end



--点击（按钮）点击该任务后执行此脚本
function x580058_ProcEventEntry( sceneId, selfId, targetId,state,index )	
	
	--未判断背包是否有足够空间

	x580058_DispatchMissionInfo( sceneId, selfId, targetId,index)

end

function x580058_DispatchMissionInfo( sceneId, selfId, targetId,index)

	SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_INDEX, index )

	local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,index )--根据索引从表中得到奖励
	local str = format("%s \n  %s",title,text)

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,str)
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	DispatchQuestInfo(sceneId, selfId, targetId, x580058_g_ScriptId, -1);

end

--领奖
function x580058_AddAward( sceneId, selfId,itemNum,index, dbIndex )

	if GetGuildID(sceneId, selfId) < 0 then
		
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"对不起，你目前没有帮会, 领取失败！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		--失败写LOG
		local logFmtMsg         = "%u,%d,\"%s\",%d,%d,%d,%d,%d" --GUID，世界ID，姓名，等级，当前场景，DBIndex,ItemIndex,成功(1) / 失败(0)
		local logMsg = format(logFmtMsg,GetPlayerGUID( sceneId,selfId ),GetWorldId(sceneId,selfId),GetName( sceneId,selfId ),GetLevel(sceneId,selfId),sceneId,dbIndex,index,0)
		WriteLog(16,logMsg)
		return
	end
	
	local nValue = 1*itemNum
	AddGuildUserPoint(sceneId, selfId, nValue)	--增加帮贡
	
	--领奖成功
	BeginQuestEvent(sceneId)
	--local title,text,scriptId = GetAwardInfo( sceneId, selfId,index )
	AddQuestText(sceneId,format("恭喜你，你获得了%d点帮贡", nValue))
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)

	--写成功LOG
	local logFmtMsg         = "%u,%d,\"%s\",%d,%d,%d,%d,%d" --GUID，世界ID，姓名，等级，当前场景，DBIndex,ItemIndex,成功(1) / 失败(0)
	local logMsg = format(logFmtMsg,GetPlayerGUID( sceneId,selfId ),GetWorldId(sceneId,selfId),GetName( sceneId,selfId ),GetLevel(sceneId,selfId),sceneId,dbIndex,index,1)
	WriteLog(16,logMsg)

end



--**********************************
--接受
--**********************************
function x580058_ProcAccept( sceneId, selfId )
end

function x580058_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end
--点击（确定）
function x580058_ProcQuestAccept( sceneId, selfId, NPCId )
end

--**********************************
--放弃
--**********************************
function x580058_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x580058_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x580058_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x580058_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x580058_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件