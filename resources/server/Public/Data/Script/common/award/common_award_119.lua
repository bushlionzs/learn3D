
x580118_g_ScriptId = 580118
x580118_g_MissionName = "领取称号补偿"

--一次最多显示的奖品数
x580118_g_MaxOnceAwardNum = 1

--点击（NPC）
function x580118_OnEnumerate( sceneId, selfId, targetId, MissionId )
	return 0
	
end



--点击（按钮）点击该任务后执行此脚本
function x580118_OnDefaultEvent( sceneId, selfId, targetId,state,index )	
	
	--未判断背包是否有足够空间

	x580118_DispatchMissionInfo( sceneId, selfId, targetId,index)

end

function x580118_DispatchMissionInfo( sceneId, selfId, targetId,index)

	SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_INDEX, index )

	local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,index )--根据索引从表中得到奖励
	local str = format("%s \n  %s",title,text)

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,str)
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	DispatchQuestInfo(sceneId, selfId, targetId, x580118_g_ScriptId, -1);

end

--领奖
function x580118_AddAward( sceneId, selfId,itemNum,index, dbIndex )

	local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,index )--根据索引从表中得到奖励
     local level = GetLevel(sceneId, selfId)
     local exp = level * 240000
     AddExp(sceneId, selfId, exp)  
		AwardTitle(sceneId, selfId, 37)
		--领奖成功
		BeginQuestEvent(sceneId)
		local sex = GetSex(sceneId,selfId)
		local TitleName = GetTitleNameByTitleID(37, sex)
        local level1 = GetLevel(sceneId, selfId)
        local exp1 = level1 * 240000
		local DoneMSG = format("恭喜您，您获得了%s称号",TitleName)
		local MSG     = format("您获得了%d点经验",exp1)
		AddQuestText(sceneId,DoneMSG)
		AddQuestText(sceneId,MSG)
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
function x580118_OnAccept( sceneId, selfId )
end

function x580118_CheckAccept( sceneId, selfId, NPCId )
	return 1
end
--点击（确定）
function x580118_CheckAndAccept( sceneId, selfId, NPCId )
end

--**********************************
--放弃
--**********************************
function x580118_OnAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x580118_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x580118_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x580118_OnSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x580118_OnKillObject( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件