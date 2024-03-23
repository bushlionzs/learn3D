--领取王者锦囊	12030483

x580162_g_ScriptId = 580162
x580162_g_MissionName = "王者锦囊"

--一次最多显示的奖品数
x580162_g_MaxOnceAwardNum = 1
x580162_g_ItemBonus =	{	{zhiye=-1,id=12030483,num=1}	--王者锦囊
						}


--点击（NPC）
function x580162_OnEnumerate( sceneId, selfId, targetId, MissionId )
	return 0
	
end



--点击（按钮）点击该任务后执行此脚本
function x580162_OnDefaultEvent( sceneId, selfId, targetId,state,index )	
	
	--未判断背包是否有足够空间

	x580162_DispatchMissionInfo( sceneId, selfId, targetId,index)

end

function x580162_DispatchMissionInfo( sceneId, selfId, targetId,index)

	SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_INDEX, index )

	local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,index )--根据索引从表中得到奖励
	local str = format("%s \n  %s",title,text)

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,str)
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	DispatchQuestInfo(sceneId, selfId, targetId, x580162_g_ScriptId, -1);

end

--领奖
function x580162_AddAward( sceneId, selfId,itemNum,index, dbIndex )

	BeginAddItem( sceneId )

	local	zhiye = GetZhiye(sceneId, selfId)

	local IsHaveItem = 0
	for i,itm in x580162_g_ItemBonus do
		if itm.zhiye == -1 then
			IsHaveItem = 1
			AddBindItem( sceneId, itm.id, itm.num*itemNum )	
		elseif itm.zhiye == zhiye then 
			IsHaveItem = 1
			AddBindItem( sceneId, itm.id, itm.num*itemNum )	
		end
	end

	local ret = EndAddItem( sceneId, selfId )
	if ret > 0 then
		if IsHaveItem == 1 then
			AddItemListToPlayer(sceneId,selfId) 
		end
	else
		--失败写LOG
		local logFmtMsg         = "%u,%d,\"%s\",%d,%d,%d,%d,%d" --GUID，世界ID，姓名，等级，当前场景，DBIndex,ItemIndex,成功(1) / 失败(0)
		local logMsg = format(logFmtMsg,GetPlayerGUID( sceneId,selfId ),GetWorldId(sceneId,selfId),GetName( sceneId,selfId ),GetLevel(sceneId,selfId),sceneId,dbIndex,index,0)
		WriteLog(16,logMsg)
		return
	end

--	AddMoney( sceneId, selfId, 3, 12000000*itemNum,101 ) 

	local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,index )--根据索引从表中得到奖励

	--领奖成功
	BeginQuestEvent(sceneId)
	local DoneMSG =  format("恭喜您，您获得了"..title..itemNum.."个")
	AddQuestText(sceneId,DoneMSG)
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
function x580162_OnAccept( sceneId, selfId )
end

function x580162_CheckAccept( sceneId, selfId, NPCId )
	return 1
end
--点击（确定）
function x580162_CheckAndAccept( sceneId, selfId, NPCId )
end

--**********************************
--放弃
--**********************************
function x580162_OnAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x580162_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x580162_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x580162_OnSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x580162_OnKillObject( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
