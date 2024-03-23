--兑换60级帽子
--MisDescBegin
--脚本号
x570004_g_ScriptId = 570004

--以上是动态**************************************************************

--任务文本描述
x570004_g_MissionName = "【龙眼石】兑换国传帽子"
x570004_g_EXCName = "兑换国传帽子"		--兑换名称 将在任务提示和任务面板使用
x570004_g_EXCItemName = "中级龙眼石"		--兑换所需要的道具名称
x570004_g_ItemId = 11050002      --所需道具ID
x570004_g_ItemNum = 130            --所需数量  
x570004_g_ItemBonus = {{id=10204002,num=1},{id=10204012,num=1},{id=10204022,num=1},{id=10204032,num=1},{id=10204042,num=1},{id=10204052,num=1},{id=10204062,num=1},{id=10204072,num=1},{id=10204082,num=1},{id=10204092,num=1},{id=10204102,num=1},{id=10204112,num=1}}
x570004_g_MissionInfo = format("\t您确定要使用#G%s#W%s吗？\n\t将需要#R%d颗#W#G%s#W。",x570004_g_EXCItemName,x570004_g_EXCName,x570004_g_ItemNum,x570004_g_EXCItemName)	--任务说明文字
x570004_g_MissionError = format("\t您没有足够数量的%s，无法%s。",x570004_g_EXCItemName,x570004_g_EXCName)	--报错信息

--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x570004_ProcEventEntry( sceneId, selfId, targetId ,scriptId,seleteId)	--点击该任务后执行此脚本

	local zhiye = GetZhiye(sceneId, selfId)
	local longyannum = GetItemCount(sceneId, selfId, x570004_g_ItemId)
	local strText = format("\t您现在有#R%d颗#W#G%s#W！",longyannum,x570004_g_EXCItemName)
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570004_g_MissionName)
			AddQuestText(sceneId,x570004_g_MissionInfo)
			AddQuestText(sceneId,strText)
			AddQuestItemBonus(sceneId, x570004_g_ItemBonus[zhiye+1].id,x570004_g_ItemBonus[1].num)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, targetId, x570004_g_ScriptId,-1)

end

--**********************************
--列举事件
--**********************************
function x570004_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x570004_g_ScriptId,x570004_g_MissionName,3);
	
end



--**********************************
--接受
--**********************************
function x570004_ProcAccept( sceneId, selfId )
	
	local Num = GetItemCount( sceneId, selfId, x570004_g_ItemId )

	if Num < x570004_g_ItemNum then 
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x570004_g_MissionError)
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)
	end
	
	if Num >= x570004_g_ItemNum then 

		local zhiye = GetZhiye(sceneId, selfId)
		local weiyi = ItemIsUnique(sceneId,selfId, x570004_g_ItemBonus[zhiye+1].id)
		local have  = HaveItem( sceneId,selfId,x570004_g_ItemBonus[zhiye+1].id)
		
		if weiyi ~= 1  then
			BeginAddItem(sceneId)
				AddItem( sceneId,x570004_g_ItemBonus[zhiye+1].id,x570004_g_ItemBonus[1].num)
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				DelItem(sceneId,selfId,x570004_g_ItemId,x570004_g_ItemNum)
			else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"物品栏已满，无法获得物品！")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			end	
		elseif weiyi == 1 then
			if have < 1 then
				BeginAddItem(sceneId)
					AddItem( sceneId,x570004_g_ItemBonus[zhiye+1].id,x570004_g_ItemBonus[1].num)
				local ret = EndAddItem(sceneId,selfId)
				if ret > 0 then
					AddItemListToPlayer(sceneId,selfId)
					DelItem(sceneId,selfId,x570004_g_ItemId,x570004_g_ItemNum)
				else
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"物品栏已满，无法获得物品！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				end	
			else
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"您无法兑换更多的装备！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end	
		end
	end
end
		
function x570004_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1

end


--**********************************
--放弃
--**********************************
function x570004_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x570004_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x570004_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x570004_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x570004_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x570004_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x570004_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
