--威望之星兑换三番令
--MisDescBegin
--脚本号
x300359_g_ScriptId = 300359

--以上是动态**************************************************************

--任务文本描述
x300359_g_MissionName = "威望之星兑换三番令"   --任务标题
x300359_g_EXCName = "兑换三番令"		--兑换名称 将在任务提示和任务面板使用
x300359_g_EXCItemName = "威望之星"		--兑换所需要的道具名称
x300359_g_ItemId = 12030210	--所需道具ID
x300359_g_ItemNum = 1				--所需数量
x300359_g_ItemBonus = {id=11990011,num=1}		--奖励物品
x300359_g_MissionInfo = format("\t如果您有从成吉思汗1中保留而来的威望之星，您可以在我这里将其兑换成三番令。\n\t您确定要使用#G%s#W%s吗？\n\t将需要#R%d颗#W#G%s#W。",x300359_g_EXCItemName,x300359_g_EXCName,x300359_g_ItemNum,x300359_g_EXCItemName)	--任务说明文字
x300359_g_MissionError = format("\t您没有足够数量的%s，无法%s。",x300359_g_EXCItemName,x300359_g_EXCName)	--报错信息

--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x300359_ProcEventEntry( sceneId, selfId, targetId ,scriptId,seleteId)	--点击该任务后执行此脚本

	local zhiye = GetZhiye(sceneId, selfId)
	local longyannum = GetItemCount(sceneId, selfId, x300359_g_ItemId)
	local strText = format("\t您现在有#R%d个#W#G%s#W！",longyannum,x300359_g_EXCItemName)
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x300359_g_MissionName)
			AddQuestText(sceneId,x300359_g_MissionInfo)
			AddQuestText(sceneId,strText)
			AddQuestItemBonus(sceneId, x300359_g_ItemBonus.id,x300359_g_ItemBonus.num)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, targetId, x300359_g_ScriptId,-1)

end

--**********************************
--列举事件
--**********************************
function x300359_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x300359_g_ScriptId,x300359_g_MissionName,3);
	
end



--**********************************
--接受
--**********************************
function x300359_ProcAccept( sceneId, selfId )
	
	local Num = GetItemCount( sceneId, selfId, x300359_g_ItemId )

	if Num < x300359_g_ItemNum then 
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x300359_g_MissionError)
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)
	end
	
	if Num >= x300359_g_ItemNum then 

		--local zhiye = GetZhiye(sceneId, selfId)
		--local weiyi = ItemIsUnique(sceneId,selfId, x300359_g_ItemBonus.id)
		--local have  = HaveItem( sceneId,selfId,x300359_g_ItemBonus.id)
		
		
			BeginAddItem(sceneId)
				AddBindItem( sceneId,x300359_g_ItemBonus.id,x300359_g_ItemBonus.num)
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				DelItem(sceneId,selfId,x300359_g_ItemId,x300359_g_ItemNum)
			else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"物品栏已满，无法获得物品！")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			end	
		
	end
end
		
function x300359_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1

end


--**********************************
--放弃
--**********************************
function x300359_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x300359_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x300359_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x300359_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x300359_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x300359_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x300359_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
