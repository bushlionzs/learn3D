
x580000_g_ScriptId = 580000
x580000_g_MissionName = "领取奖品"

--一次最多显示的奖品数
x580000_g_MaxOnceAwardNum = 5

x580000_g_ItemBonus =	{
							{zhiye=-1,id=11000213,num=10},
							{zhiye=-1,id=11010003,num=10},
							{zhiye=-1,id=12010006,num=5},
							{zhiye=0, id=12020001,num=5},
							{zhiye=0, id=10010060,num=1},
							{zhiye=1, id=12020002,num=5},
							{zhiye=1, id=10020060,num=1},
							{zhiye=2, id=12020003,num=5},
							{zhiye=2, id=10030060,num=1},
							{zhiye=3, id=12020004,num=5},
							{zhiye=3, id=10040060,num=1},
							{zhiye=4, id=12020005,num=5},
							{zhiye=4, id=10050060,num=1},
							{zhiye=5, id=12020006,num=5},
							{zhiye=5, id=10060060,num=1},
							{zhiye=-1,id=12030202,num=1},
							{zhiye=-1,id=12030203,num=1}
						}

--点击（NPC）
function x580000_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	return 0
	
end



--点击（按钮）点击该任务后执行此脚本
function x580000_ProcEventEntry( sceneId, selfId, targetId,state,index )	
	
	--未判断背包是否有足够空间

	x580000_DispatchMissionInfo( sceneId, selfId, targetId,index)

end

function x580000_DispatchMissionInfo( sceneId, selfId, targetId,index)

	SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_INDEX, index )

	local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,index )--根据索引从表中得到奖励
	local str = format("%s \n  %s",title,text)

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,str)
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	DispatchQuestInfo(sceneId, selfId, targetId, x580000_g_ScriptId, -1);

end

--领奖
function x580000_AddAward( sceneId, selfId,itemNum,index, dbIndex )

	BeginAddItem( sceneId )

	local	zhiye = GetZhiye(sceneId, selfId)

	local IsHaveItem = 0
	for i,itm in x580000_g_ItemBonus do
		if itm.zhiye == -1 then
			IsHaveItem = 1
			AddItem( sceneId, itm.id, itm.num*itemNum )	
		elseif itm.zhiye == zhiye then 
			IsHaveItem = 1
			AddItem( sceneId, itm.id, itm.num*itemNum )	
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

	local exp = GetLevel(sceneId, selfId) * 2000*itemNum
	AddExp( sceneId, selfId,exp )
	AddMoney( sceneId, selfId, 1, 2000*itemNum,101 ) 
	AddMoney( sceneId, selfId, 3, 1000*itemNum,101 )	

	--领奖成功
	BeginQuestEvent(sceneId)
	--local title,text,scriptId = GetAwardInfo( sceneId, selfId,index )
	AddQuestText(sceneId,"恭喜你，你获得超级无敌大礼包一个！")
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
function x580000_ProcAccept( sceneId, selfId )
end

function x580000_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end
--点击（确定）
function x580000_ProcQuestAccept( sceneId, selfId, NPCId )
end

--**********************************
--放弃
--**********************************
function x580000_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x580000_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x580000_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x580000_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x580000_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件