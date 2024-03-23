--五番令兑换藏宝令
--MisDescBegin
--脚本号
x414028_g_ScriptId = 414028

--以上是动态**************************************************************

--任务文本描述
x414028_g_MissionName = "五番令兑换藏宝令"   --任务标题
x414028_g_EXCName = "五番令兑换藏宝令"		--兑换名称 将在任务提示和任务面板使用
x414028_g_EXCItemName = "五番令"		--兑换所需要的道具名称
x414028_g_ItemId = 11990012	--所需道具ID
x414028_g_ItemNum = 1				--所需数量
x414028_g_ItemBonus = {{id=11990015,num=4},{id=11990015,num=4},{id=11990015,num=4},{id=11990015,num=4},{id=11990015,num=4},{id=11990015,num=4},{id=11990015,num=4},{id=11990015,num=4},{id=11990015,num=4},{id=11990015,num=4},{id=11990015,num=4},{id=11990015,num=4}}		--奖励物品
x414028_g_MissionInfo = format("\n\t您那里有多余的#G五番令#W吗？在我这里可以将#R%d个#W#G五番令#W兑换为#R4个#W#G藏宝令#W。",x414028_g_ItemNum)	--任务说明文字
x414028_g_MissionError = format("\t您没有%s，无法用%s。",x414028_g_EXCItemName,x414028_g_EXCName)	--报错信息

--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x414028_ProcEventEntry( sceneId, selfId, targetId ,scriptId,seleteId)	--点击该任务后执行此脚本

	local zhiye = GetZhiye(sceneId, selfId)
	local longyannum = GetItemCount(sceneId, selfId, x414028_g_ItemId)
	local strText = format("\n\t您确定要使用#G五番令#W兑换#G藏宝令#W吗？")
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x414028_g_MissionName)
			AddQuestText(sceneId,x414028_g_MissionInfo)
			AddQuestText(sceneId,strText)
			AddQuestItemBonus(sceneId, x414028_g_ItemBonus[zhiye+1].id,x414028_g_ItemBonus[1].num)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, targetId, x414028_g_ScriptId,-1)

end

--**********************************
--列举事件
--**********************************
function x414028_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x414028_g_ScriptId,x414028_g_MissionName,3);
	
end



--**********************************
--接受
--**********************************
function x414028_ProcAccept( sceneId, selfId )
	
	local Num = GetItemCount( sceneId, selfId, x414028_g_ItemId )

	if Num < x414028_g_ItemNum then 
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x414028_g_MissionError)
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)
	end
	
	if Num >= x414028_g_ItemNum then 

		local zhiye = GetZhiye(sceneId, selfId)
		local weiyi = ItemIsUnique(sceneId,selfId, x414028_g_ItemBonus[zhiye+1].id)
		local have  = HaveItem( sceneId,selfId,x414028_g_ItemBonus[zhiye+1].id)
		
		if weiyi ~= 1  then
			BeginAddItem(sceneId)
				AddItem( sceneId,x414028_g_ItemBonus[zhiye+1].id,x414028_g_ItemBonus[1].num)
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				DelItem(sceneId,selfId,x414028_g_ItemId,x414028_g_ItemNum)
			else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"物品栏已满，无法获得物品！")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			end	
		elseif weiyi == 1 then
			if have < 1 then
				BeginAddItem(sceneId)
					AddItem( sceneId,x414028_g_ItemBonus[zhiye+1].id,x414028_g_ItemBonus[1].num)
				local ret = EndAddItem(sceneId,selfId)
				if ret > 0 then
					AddItemListToPlayer(sceneId,selfId)
					DelItem(sceneId,selfId,x414028_g_ItemId,x414028_g_ItemNum)
				else
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"物品栏已满，无法获得物品！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				end	
			else
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"您无法兑换更多的藏宝令！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end	
		end
	end
end
		
function x414028_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1

end


--**********************************
--放弃
--**********************************
function x414028_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x414028_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x414028_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x414028_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x414028_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x414028_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x414028_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
