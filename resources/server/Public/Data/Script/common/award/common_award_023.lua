--暑假清凉包

x580022_g_ScriptId = 580022
x580022_g_MissionName = "领取暑假回归礼包"

--一次最多显示的奖品数
x580022_g_MaxOnceAwardNum = 1

x580022_g_ItemBonus =	{	}

--点击（NPC）
function x580022_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	return 0
	
end



--点击（按钮）点击该任务后执行此脚本
function x580022_ProcEventEntry( sceneId, selfId, targetId,state,index )	
	
	--未判断背包是否有足够空间

	x580022_DispatchMissionInfo( sceneId, selfId, targetId,index)

end

function x580022_DispatchMissionInfo( sceneId, selfId, targetId,index)

	SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_INDEX, index )

	local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,index )--根据索引从表中得到奖励
	local str = format("%s \n  %s",title,text)

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,str)
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	DispatchQuestInfo(sceneId, selfId, targetId, x580022_g_ScriptId, -1);

end

--领奖
function x580022_AddAward( sceneId, selfId,itemNum,index, dbIndex )

	BeginAddItem( sceneId )

	local	nLevel = GetLevel(sceneId, selfId)
	local nExp = nLevel * 180000 * itemNum
	local nMoney = nLevel * 1000 * itemNum
	
	AddExpAutoLevelup(sceneId,selfId,nExp) --自动升级经验
	AddMoney(sceneId,selfId,1,nMoney,101)	--银卡奖励

--	AddMoney( sceneId, selfId, 0, 1000*itemNum,101 ) 
--
--	--领奖成功
--	BeginQuestEvent(sceneId)
--	local DoneMSG = format("恭喜您，您获得了现银%d文！",1000*itemNum)
--	AddQuestText(sceneId,DoneMSG)
--	EndQuestEvent(sceneId)
--	DispatchQuestTips(sceneId,selfId)

	--写成功LOG
	local logFmtMsg         = "%u,%d,\"%s\",%d,%d,%d,%d,%d" --GUID，世界ID，姓名，等级，当前场景，DBIndex,ItemIndex,成功(1) / 失败(0)
	local logMsg = format(logFmtMsg,GetPlayerGUID( sceneId,selfId ),GetWorldId(sceneId,selfId),GetName( sceneId,selfId ),GetLevel(sceneId,selfId),sceneId,dbIndex,index,1)
	WriteLog(16,logMsg)

end



--**********************************
--接受
--**********************************
function x580022_ProcAccept( sceneId, selfId )
end

function x580022_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end
--点击（确定）
function x580022_ProcQuestAccept( sceneId, selfId, NPCId )
end

--**********************************
--放弃
--**********************************
function x580022_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x580022_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x580022_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x580022_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x580022_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件