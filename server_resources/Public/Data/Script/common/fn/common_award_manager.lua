
x561103_g_ScriptId = 561103
x561103_g_MissionName = "领取奖品"

--一次最多显示的奖品数
x561103_g_MaxOnceAwardNum = 5

--点击（NPC）
function x561103_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	return 0
	
end




--点击（按钮）点击该任务后执行此脚本
function x561103_ProcEventEntry( sceneId, selfId, targetId,state,index )	

	if  x561103_HaveBagSpace(sceneId, selfId,index,targetId) == 1 then
		x561103_DispatchMissionInfo( sceneId, selfId, targetId,index)
	end

end

function x561103_DispatchMissionInfo( sceneId, selfId, targetId,index)

	local dbIndex = GetPlayerRuntimeData( sceneId, selfId, index+x561103_g_MaxOnceAwardNum )
	SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_INDEX, dbIndex )

	local id = GetPlayerRuntimeData( sceneId, selfId, index )

	local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,id )--根据索引从表中得到奖励
	local str = format("%s \n  %s",title,text)

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,str)
	EndQuestEvent(sceneId)

	DispatchQuestEventList(sceneId,selfId,targetId)
	DispatchQuestInfo(sceneId, selfId, targetId, x561103_g_ScriptId, -1);

end


function x561103_HaveBagSpace(sceneId, selfId,index,targetId)

	local id = GetPlayerRuntimeData( sceneId, selfId, index )
	local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,id )

	local BagNum = BagNeedSpace

	if BagNeedSpace > 0 then
		local itemNum = GetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_AWARE_NUM1+index-RD_HUMAN_AWARE_INDEX1 ) 
		if MinSpliceNum == 0 then
			MinSpliceNum = 1
		end

		itemNum = itemNum * BagNeedSpace	
		BagNum = ceil(itemNum / MinSpliceNum )
		if BagNum < BagNeedSpace then
			BagNum = BagNeedSpace
		end		
	else 
		BagNum = BagNeedSpace
	end

	--判断背包是否有足够空间
	if GetBagSpace( sceneId, selfId ) <	BagNum then

		BeginQuestEvent(sceneId)
		local str = format("此次领奖背包中最少需要预留%d个空格，你当前背包空间不够。",BagNum)
		AddQuestText(sceneId,str)
		EndQuestEvent(sceneId)

		if targetId == -1 then
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,str,8,2)
		else
			DispatchQuestEventList(sceneId,selfId,targetId)
		end

		return 0
	end

	return 1

end


--领奖管理者
function x561103_OnAddAwardManager( sceneId, selfId, result,itemNum,index,dbIndex )
	
	if result == 0 then
		--领奖失败
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"领奖失败，没有查询到奖项记录或奖项己过期，请稍后重试")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 
	end

	if result == 2 then
		--该账户领奖功能暂时冻结
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"账户领奖功能暂时冻结，稍后重试")
		EndQuestEvent(sceneId)
		return 
	end

	--trophy.tab表中索引转换为全局变量(RuntimeData)的索引
	local runData = -1
	for tmpIndex=0, x561103_g_MaxOnceAwardNum-1 do

		local logicIndex = GetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_AWARE_INDEX1+tmpIndex )
		local tmpDbIndex = GetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_AWARE_DB_INDEX1+tmpIndex ) 
		
		if index == logicIndex and tmpDbIndex == dbIndex then
			runData = RD_HUMAN_AWARE_INDEX1 + tmpIndex  	
		end
	end

	if  runData ~=-1 and x561103_HaveBagSpace(sceneId, selfId,runData,-1) ~= 1 then
		return
	end

	local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,index )--根据索引从表中得到奖励信息
	CallScriptFunction( scriptId, "AddAward", sceneId, selfId ,itemNum,index,dbIndex ) 

	SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_INDEX, -1 )

	for i=0, x561103_g_MaxOnceAwardNum-1 do
		SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_AWARE_INDEX1+i, -1 )
		SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_AWARE_DB_INDEX1+i, -1 )
		SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_AWARE_NUM1+i, -1 )
	end

end

--**********************************
--接受
--**********************************
function x561103_ProcAccept( sceneId, selfId )

	local tabIndex = -1	--trophy.tab表中的索引
	local dbIndex = GetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_INDEX )
		
	--dbIndex转换为trophy.tab表中的索引
	for i=0, x561103_g_MaxOnceAwardNum-1 do

		if dbIndex ==  GetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_AWARE_DB_INDEX1+i ) then
			tabIndex = RD_HUMAN_AWARE_DB_INDEX1+i - x561103_g_MaxOnceAwardNum  
		end
	end

	if tabIndex ~= -1 and x561103_HaveBagSpace(sceneId, selfId,tabIndex,-1) ~= 1 then
		return		
	end

	local awardType = 0
	
	--1000以后的是CDKEY领奖
	if GetPlayerRuntimeData( sceneId, selfId, tabIndex )>=1000 then
	
		awardType = 1
		
	else 
	
		awardType = 0
		
	end

	--通知Balling领奖
	GetAward( sceneId, selfId, dbIndex, awardType )

end


function x561103_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end
--点击（确定）
function x561103_ProcQuestAccept( sceneId, selfId, NPCId )
end

--**********************************
--放弃
--**********************************
function x561103_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x561103_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x561103_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x561103_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x561103_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
