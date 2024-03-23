--兑换天传项链
--MisDescBegin
--脚本号
x570030_g_ScriptId = 570030

--以上是动态**************************************************************

--任务文本描述
x570030_g_MissionName = "【龙眼石】兑换天传项链"
x570030_g_EXCName = "兑换天传项链"		--兑换名称 将在任务提示和任务面板使用
x570030_g_EXCItemName = "天之龙眼石"		--兑换所需要的道具名称
x570030_g_ItemId = 11050004    --所需道具ID
x570030_g_ItemNum = 200          --所需数量  
x570030_g_ItemBonus =	{{id=10244004,num=1},{id=10244014,num=1},{id=10244024,num=1},{id=10244034,num=1},{id=10244044,num=1},{id=10244054,num=1},{id=10249221,num=1},{id=10249225,num=1},{id=10249229,num=1},{id=10249233,num=1},{id=10249237,num=1},{id=10249241,num=1}}
x570030_g_MissionInfo = format("\t您确定要使用#G%s#W%s吗？\n\t将需要#R%d颗#W#G%s#W。",x570030_g_EXCItemName,x570030_g_EXCName,x570030_g_ItemNum,x570030_g_EXCItemName)	--任务说明文字
x570030_g_MissionError = format("\t您没有足够数量的%s，无法%s。",x570030_g_EXCItemName,x570030_g_EXCName)	--报错信息

--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x570030_ProcEventEntry( sceneId, selfId, targetId ,scriptId,seleteId)	--点击该任务后执行此脚本

	local zhiye = GetZhiye(sceneId, selfId)
	local longyannum = GetItemCount(sceneId, selfId, x570030_g_ItemId)
	local strText = format("\t您现在有#R%d颗#W#G%s#W！",longyannum,x570030_g_EXCItemName)
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570030_g_MissionName)
			AddQuestText(sceneId,x570030_g_MissionInfo)
			AddQuestText(sceneId,strText)
			AddQuestItemBonus(sceneId, x570030_g_ItemBonus[zhiye+1].id,x570030_g_ItemBonus[1].num)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, targetId, x570030_g_ScriptId,-1)

end

--**********************************
--列举事件
--**********************************
function x570030_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x570030_g_ScriptId,x570030_g_MissionName,3);
	
end



--**********************************
--接受
--**********************************
function x570030_ProcAccept( sceneId, selfId )
	
	local Num = GetItemCount( sceneId, selfId, x570030_g_ItemId )

	if Num < x570030_g_ItemNum then 
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x570030_g_MissionError)
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)
	end
	
	if Num >= x570030_g_ItemNum then 

		local zhiye = GetZhiye(sceneId, selfId)
		local weiyi = ItemIsUnique(sceneId,selfId, x570030_g_ItemBonus[zhiye+1].id)
		local have  = HaveItem( sceneId,selfId,x570030_g_ItemBonus[zhiye+1].id)
		
		if weiyi ~= 1  then
			BeginAddItem(sceneId)
				AddItem( sceneId,x570030_g_ItemBonus[zhiye+1].id,x570030_g_ItemBonus[1].num)
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				DelItem(sceneId,selfId,x570030_g_ItemId,x570030_g_ItemNum)
			else
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"物品栏已满，无法获得物品！")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			end	
		elseif weiyi == 1 then
			if have < 1 then
				BeginAddItem(sceneId)
					AddItem( sceneId,x570030_g_ItemBonus[zhiye+1].id,x570030_g_ItemBonus[1].num)
				local ret = EndAddItem(sceneId,selfId)
				if ret > 0 then
					AddItemListToPlayer(sceneId,selfId)
					DelItem(sceneId,selfId,x570030_g_ItemId,x570030_g_ItemNum)
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
		
function x570030_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1

end


--**********************************
--放弃
--**********************************
function x570030_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x570030_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x570030_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x570030_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x570030_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x570030_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x570030_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
