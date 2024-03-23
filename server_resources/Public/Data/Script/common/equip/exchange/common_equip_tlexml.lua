--兑换30级帽子
--MisDescBegin
--脚本号
x570050_g_ScriptId = 570050

--以上是动态**************************************************************

--任务文本描述
x570050_g_MissionName = "【龙眼石】兑换冥之龙眼石"   --任务标题
x570050_g_EXCName = "兑换冥之龙眼石"		--兑换名称 将在任务提示和任务面板使用
x570050_g_EXCItemName = "天之龙眼石"		--兑换所需要的道具名称
x570050_g_CostitemId = 11050004	--所需道具ID
x570050_g_CostitemNum ={3,15,30,150,300} 				--所需数量
x570050_g_ItemId = 11050005	--获得道具ID
x570050_g_ItemNum = {1,5,10,50,100}				--获得数量
x570050_g_MissionError = format("\t您没有足够数量的%s，无法%s。",x570050_g_EXCItemName,x570050_g_EXCName)	--报错信息

--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x570050_ProcEventEntry( sceneId, selfId, NPCId, MissionId,nExt)	--点击该任务后执行此脚本

	if nExt==nil then
		return
	end

	if nExt==0 then

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570050_g_MissionName)
			AddQuestText(sceneId,"\t在我这里，你可以将天之龙眼石兑换为冥之龙眼石。3颗天之龙眼石可以兑换1颗冥之龙眼石。\n\t#R兑换的冥之龙眼石是绑定的！")
			
				AddQuestNumText(sceneId, MissionId, "我要兑换1颗",3,1);
				AddQuestNumText(sceneId, MissionId, "我要兑换5颗",3,2);
				AddQuestNumText(sceneId, MissionId, "我要兑换10颗",3,3);
				AddQuestNumText(sceneId, MissionId, "我要兑换50颗",3,4);
				AddQuestNumText(sceneId, MissionId, "我要兑换100颗",3,5);

		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId, NPCId, x570050_g_ScriptId, MissionId);


	end

	if nExt==1 or nExt==2 or nExt==3 or nExt==4 or nExt==5 then
		x570050_DispatchExchangeInfo( sceneId, selfId, NPCId,nExt )
	end
end



function x570050_DispatchExchangeInfo( sceneId, selfId, NPCId, nExt )
        
	--任务信息
	if nExt==1 then
		BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"#Y"..x570050_g_MissionName)
		AddQuestText(sceneId,format("\t你要用%d颗#G天之龙眼石#W换取%d颗#G冥之龙眼石#W吗？\n\t#R兑换的冥之龙眼石是绑定的！", 3,1))
		AddQuestItemBonus(sceneId, x570050_g_ItemId,1)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, NPCId, x570050_g_ScriptId, -1);
		x570050_SetSelected(sceneId, selfId, nExt)
	elseif nExt==2 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x570050_g_MissionName)
		AddQuestText(sceneId,format("\t你要用%d颗#G天之龙眼石#W换取%d颗#G冥之龙眼石#W吗？\n\t#R兑换的冥之龙眼石是绑定的！", 15,5))
		AddQuestItemBonus(sceneId, x570050_g_ItemId,5)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, NPCId, x570050_g_ScriptId, -1);
	    x570050_SetSelected(sceneId, selfId, nExt)
	elseif nExt==3 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x570050_g_MissionName)
		AddQuestText(sceneId,format("\t你要用%d颗#G天之龙眼石#W换取%d颗#G冥之龙眼石#W吗？\n\t#R兑换的冥之龙眼石是绑定的！", 30,10))
		AddQuestItemBonus(sceneId, x570050_g_ItemId,10)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, NPCId, x570050_g_ScriptId, -1);
	    x570050_SetSelected(sceneId, selfId, nExt)
	elseif nExt==4 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x570050_g_MissionName)
		AddQuestText(sceneId,format("\t你要用%d颗#G天之龙眼石#W换取%d颗#G冥之龙眼石#W吗？\n\t#R兑换的冥之龙眼石是绑定的！", 150,50))
		AddQuestItemBonus(sceneId, x570050_g_ItemId,50)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, NPCId, x570050_g_ScriptId, -1);
	    x570050_SetSelected(sceneId, selfId, nExt)
	elseif nExt==5 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x570050_g_MissionName)
		AddQuestText(sceneId,format("\t你要用%d颗#G天之龙眼石#W换取%d颗#G冥之龙眼石#W吗？\n\t#R兑换的冥之龙眼石是绑定的！", 300,100))
		AddQuestItemBonus(sceneId, x570050_g_ItemId,100)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, NPCId, x570050_g_ScriptId, -1);
	    x570050_SetSelected(sceneId, selfId, nExt)

	end	
end

--**********************************
--列举事件
--**********************************
function x570050_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x570050_g_ScriptId,x570050_g_MissionName,3);
	
end


--**********************************
--接受
--**********************************
function x570050_ProcAccept( sceneId, selfId ,nExt)

	local nExt = x570050_GetSelected(sceneId, selfId)
	if nExt==1 then
		nIndex = 1;
	elseif nExt==2 then
		nIndex = 2;
	elseif nExt==3 then
		nIndex = 3;
	elseif nExt==4 then
		nIndex = 4;
	elseif nExt==5 then
		nIndex = 5;

	else
		return
	end
	local Num = GetItemCount( sceneId, selfId, x570050_g_CostitemId )
    local weiyi = ItemIsUnique(sceneId,selfId, x570050_g_ItemId)
	local have  = HaveItem( sceneId,selfId,x570050_g_ItemId)
 
	if Num < x570050_g_CostitemNum[nIndex] then 
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x570050_g_MissionError)
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)
	end
	
	if Num >= x570050_g_CostitemNum[nIndex] then 
		
			BeginAddItem(sceneId)
			AddBindItem( sceneId,x570050_g_ItemId,x570050_g_ItemNum[nIndex])
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
				DelItem(sceneId,selfId,x570050_g_CostitemId,x570050_g_CostitemNum[nIndex])
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"兑换成功！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
                
			else
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"物品栏已满，无法获得物品！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end	
		elseif weiyi == 1 then
			if have < 1 then
				BeginAddItem(sceneId)
				AddBindItem( sceneId,x570050_g_ItemId,x570050_g_ItemNum[nIndex])
				local ret = EndAddItem(sceneId,selfId)
				if ret > 0 then
					AddItemListToPlayer(sceneId,selfId)
					DelItem(sceneId,selfId,x570050_g_CostitemId,x570050_g_CostitemNum[nIndex])
				else
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"物品栏已满，无法获得物品！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				end	
			else
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"您无法兑换更多的冥之龙眼石！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end	
		end
	end
		
function x570050_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1

end


--**********************************
--放弃
--**********************************
function x570050_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x570050_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x570050_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x570050_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x570050_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x570050_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x570050_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
---------------------------------------------------------------------------------------------------
--得到玩家刚才选择的界面选项
---------------------------------------------------------------------------------------------------
function x570050_GetSelected(sceneId, selfId)
	return GetPlayerRuntimeData(sceneId, selfId, RD_COMMON_NPCID )
end


---------------------------------------------------------------------------------------------------
--设置玩家刚才选择的界面选项
---------------------------------------------------------------------------------------------------
function x570050_SetSelected(sceneId, selfId, flag)
	SetPlayerRuntimeData(sceneId, selfId, RD_COMMON_NPCID, flag)
end
