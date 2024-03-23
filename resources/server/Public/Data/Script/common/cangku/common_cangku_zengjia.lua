--增加仓库空间
--MisDescBegin
--脚本号
x561001_g_ScriptId = 561001

--**************************************************************

--任务文本描述
x561001_g_MainName="增加仓库扩展空间说明"
x561001_g_MissionName="增加仓库扩展空间"
x561001_g_Readme = "\t增加仓库扩展空间需要花费一定的金额，增加第一页扩展空间需要花费#G200两#W银子，增加第二页扩展空间需要花费#G2锭#W银子！"
x561001_g_Notice1 = "\t您确定要扩展第一页扩展仓库吗？需要花费#G200两#W银子！"
x561001_g_Notice2 = "\t您确定要扩展第二页扩展仓库吗？需要花费#G2锭#W银子！"
x561001_g_Notice3 = "\t您的扩展仓库已经全部开启！"
x561001_g_Notice4 = "\t您的银子不足！无法完成增加扩展仓库操作！"
x561001_g_Notice5 = "\t操作成功！已增加了仓库的扩展空间！"

x561001_g_NeedMoney1 = 200000			--开启第一页花费 200两
x561001_g_NeedMoney2 = 2000000		--开启第二页花费 2锭
x561001_g_BasicSize = 36


--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x561001_ProcEventEntry( sceneId, selfId, targetId,scriptid,extid )	--点击该任务后执行此脚本

	if extid == 1 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x561001_g_MainName)
			AddQuestText(sceneId,x561001_g_Readme);
			AddQuestText(sceneId,x561001_g_Notice1);
		EndQuestEvent(sceneId)	
		DispatchQuestInfo(sceneId, selfId, targetId, scriptid, -1)
	elseif extid == 2 then
		BeginQuestEvent(sceneId)	
			AddQuestText(sceneId,"#Y"..x561001_g_MainName)
			AddQuestText(sceneId,x561001_g_Readme);
			AddQuestText(sceneId,x561001_g_Notice2);
		EndQuestEvent(sceneId)	
		DispatchQuestInfo(sceneId, selfId, targetId, scriptid, -1)
	elseif extid == 3 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x561001_g_MainName)
			AddQuestText(sceneId,x561001_g_Readme);
			AddQuestText(sceneId,x561001_g_Notice3);
		EndQuestEvent(sceneId)	
		DispatchQuestInfo(sceneId, selfId, targetId, scriptid, -1)
	end
	x561001_SetSelected(sceneId, selfId,extid)
		
end

--**********************************
--列举事件
--**********************************
function x561001_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	local storesize = GetBankSize(sceneId,selfId)
	
	if storesize == x561001_g_BasicSize then
		AddQuestNumText(sceneId, x561001_g_ScriptId, x561001_g_MissionName,3,1)
	elseif storesize == x561001_g_BasicSize*2 then
		AddQuestNumText(sceneId, x561001_g_ScriptId, x561001_g_MissionName,3,2)
	elseif storesize == x561001_g_BasicSize*3 then
		AddQuestNumText(sceneId, x561001_g_ScriptId, x561001_g_MissionName,3,3)
	else
		return
	end

end

--**********************************
--检测接受条件
--**********************************
function x561001_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end

---------------------------------------------------------------------------------------------------
--得到玩家刚才选择的界面选项
---------------------------------------------------------------------------------------------------

function x561001_GetSelected(sceneId, selfId)
	return GetPlayerRuntimeData(sceneId,selfId,RD_CANGKU_EXT)
end

---------------------------------------------------------------------------------------------------
--设置玩家刚才选择的界面选项
---------------------------------------------------------------------------------------------------
function x561001_SetSelected(sceneId, selfId, flag)
	SetPlayerRuntimeData(sceneId,selfId,RD_CANGKU_EXT,flag)
end

--**********************************
--接受
--**********************************
function x561001_ProcAccept( sceneId, selfId )

	local flag = x561001_GetSelected(sceneId,selfId)

	if flag == 1 then 
		if IsEnoughMoney( sceneId, selfId, x561001_g_NeedMoney1 ) == 0  then
			BeginQuestEvent(sceneId,selfId)
				AddQuestText(sceneId,x561001_g_Notice4)
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		else 
			SpendMoney( sceneId, selfId, x561001_g_NeedMoney1 )
			--CostMoney( sceneId , selfId , 1 , x561001_g_NeedMoney1 )
			ExpandBankSize(sceneId,selfId,36)
			BeginQuestEvent(sceneId,selfId)
				AddQuestText(sceneId,x561001_g_Notice5)
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		end
	elseif flag == 2 then 
		if IsEnoughMoney( sceneId, selfId, x561001_g_NeedMoney2 ) == 0  then
			BeginQuestEvent(sceneId,selfId)
				AddQuestText(sceneId,x561001_g_Notice4)
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		else 
			SpendMoney( sceneId,selfId,x561001_g_NeedMoney2 )
			ExpandBankSize(sceneId,selfId,36)
			BeginQuestEvent(sceneId,selfId)
				AddQuestText(sceneId,x561001_g_Notice5)
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		end
	elseif flag == 3 then 
		return
	end


end

--**********************************
--放弃
--**********************************
function x561001_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x561001_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x561001_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x561001_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x561001_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x561001_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x561001_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
