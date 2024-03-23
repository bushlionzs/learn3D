
x580031_g_ScriptId = 580031
x580031_g_MissionName = "开启扩展仓库"

--一次最多显示的奖品数
x580031_g_MaxOnceAwardNum = 5

x580031_g_ItemBonus =	{
							{zhiye=-1,id=12030302,num=1}
						}

--点击（NPC）
function x580031_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	return 0
	
end



--点击（按钮）点击该任务后执行此脚本
function x580031_ProcEventEntry( sceneId, selfId, targetId,state,index )	
	
	--未判断背包是否有足够空间

	x580031_DispatchMissionInfo( sceneId, selfId, targetId,index)

end

function x580031_DispatchMissionInfo( sceneId, selfId, targetId,index)

	SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_INDEX, index )

	local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,index )--根据索引从表中得到奖励
	local str = format("%s \n  %s",title,text)

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,str)
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	DispatchQuestInfo(sceneId, selfId, targetId, x580031_g_ScriptId, -1);

end

--领奖
function x580031_AddAward( sceneId, selfId,itemNum,index, dbIndex )

	local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,index )--根据索引从表中得到奖励
	local storesize = GetBankSize(sceneId,selfId)
	if storesize == 36 then
		ExpandBankSize(sceneId,selfId,36)
		if storesize == 72 then
			--领奖成功
			BeginQuestEvent(sceneId)
			local DoneMSG = "恭喜您，您成功开启了扩展仓库！"
			AddQuestText(sceneId,DoneMSG)
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		
			--写成功LOG
			local logFmtMsg         = "%u,%d,\"%s\",%d,%d,%d,%d,%d" --GUID，世界ID，姓名，等级，当前场景，DBIndex,ItemIndex,成功(1) / 失败(0)
			local logMsg = format(logFmtMsg,GetPlayerGUID( sceneId,selfId ),GetWorldId(sceneId,selfId),GetName( sceneId,selfId ),GetLevel(sceneId,selfId),sceneId,dbIndex,index,1)
			WriteLog(16,logMsg)
		else
			--失败写LOG
			local logFmtMsg         = "%u,%d,\"%s\",%d,%d,%d,%d,%d" --GUID，世界ID，姓名，等级，当前场景，DBIndex,ItemIndex,成功(1) / 失败(0)
			local logMsg = format(logFmtMsg,GetPlayerGUID( sceneId,selfId ),GetWorldId(sceneId,selfId),GetName( sceneId,selfId ),GetLevel(sceneId,selfId),sceneId,dbIndex,index,0)
			WriteLog(16,logMsg)
			return
		end
	elseif storesize > 36 then
--		AddMoney(sceneId,selfId,1,200000,101)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"您已经开启了扩展仓库，无法获得本次开启扩展仓库的奖励！")
--		AddQuestText(sceneId,"您获得了200两银卡的奖励！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		
		--失败写LOG
			local logFmtMsg         = "%u,%d,\"%s\",%d,%d,%d,%d,%d" --GUID，世界ID，姓名，等级，当前场景，DBIndex,ItemIndex,成功(1) / 失败(0)
			local logMsg = format(logFmtMsg,GetPlayerGUID( sceneId,selfId ),GetWorldId(sceneId,selfId),GetName( sceneId,selfId ),GetLevel(sceneId,selfId),sceneId,dbIndex,index,0)
			WriteLog(16,logMsg)
			
		return
		
	end

end



--**********************************
--接受
--**********************************
function x580031_ProcAccept( sceneId, selfId )
end

function x580031_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end
--点击（确定）
function x580031_ProcQuestAccept( sceneId, selfId, NPCId )
end

--**********************************
--放弃
--**********************************
function x580031_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x580031_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x580031_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x580031_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x580031_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件