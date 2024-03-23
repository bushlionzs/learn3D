--进入地窖

--MisDescBegin
x550401_g_ScriptId = 550401
x550401_g_MissionName1 = "前往楼兰边塞"
x550401_g_MissionName2 = "前往天山边塞"
x550401_g_MissionName3 = "前往昆仑边塞"
x550401_g_MissionName4 = "前往敦煌边塞"   
x550401_g_SceneID1 =51								--楼兰边境场景ID
x550401_g_SceneID2 =151	  						 --天山边境场景ID
x550401_g_SceneID3 =251								--昆仑边境场景ID
x550401_g_SceneID4 =351								--敦煌边境场景ID
x550401_g_MissionInfo=" "  --任务描述
x550401_g_MissionInfo2=""
x550401_g_MissionQuestID	=	-1
x550401_g_MissionComplete="  "					--完成任务npc说话的话
x550401_g_ContinueInfo="    "
x550401_g_Notice = "您的等级还不足#R40级#Y，无法前往其他国家！"
--任务奖励
x550401_g_MoneyBonus = 10000
--固定物品奖励，最多8种
x550401_g_ItemBonus={}

--可选物品奖励，最多8种
x550401_g_RadioItemBonus={}

--MisDescEnd
x550401_g_ExpBonus = 1000
--**********************************

--任务入口函数

--**********************************

function x550401_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本

	local selfType = GetObjType(sceneId, selfId)
	if selfType == 1 then 
		------------------------------------------------------
		if IsHaveQuestNM( sceneId, selfId, 7537) ~= 0 or  IsHaveQuestNM( sceneId, selfId, 7538) ~= 0 or IsHaveQuestNM( sceneId, selfId, 7539) ~= 0 then
			Msg2Player(sceneId,selfId,"很抱歉，未完成铁人三项任务时无法通往其他场景！",8,2)
			return
		end
		--以上用于铁人三项禁止传送的处理
		------------------------------------------------------
	end
	
	if selfType == 9 then	--Bus进入区域 把bus和bus里的人跨场景
		local busType = GetBusType(sceneId, selfId)
		if busType == 1 then --BUS_TYPE_NORMAL
			local memberCount = GetBusMemberCount(sceneId, selfId)
			local daduSceneId = 0
			ReadyBusChangeScene(sceneId, daduSceneId,selfId)--注意：此步骤是必需的.BUS切换场景，要先做些准备工作,
			for	i = 0, memberCount - 1 do
				local ObjID = GetBusMemberObjId(sceneId, selfId, i)
				NewWorld(sceneId,ObjID,x550401_g_SceneID2,126.5,198, 550401)
			end
			--删除BUS,但乘员仍在车上
			DeleteBus(sceneId, selfId,0)
			return
		end
	elseif selfType == 1 then	--玩家
--		local isBusMember = IsBusMember(sceneId, selfId)
--		if isBusMember == 1 then
--			Msg2Player(sceneId,selfId,"很抱歉，未完成镖车护送时无法通往其他场景！",8,2)		
--			return
--		end
	end
	
	local strText = ""
	local CanTrans = IsCashboxState(sceneId,selfId)	
	if CanTrans == 1 then
		BeginQuestEvent(sceneId)
			strText = "#Y运镖或者护送状态中，不允许传送"
			AddQuestText(sceneId,strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end

	local nLevel = GetLevel(sceneId, selfId)
	if nLevel < 40 then 
		Msg2Player(sceneId,selfId,"#Y"..x550401_g_Notice.."#W",4,3)
	else
		NewWorld(sceneId,selfId,x550401_g_SceneID2,126.6,197, 550401)
	end
	
end



--**********************************

--列举事件

--**********************************

function x550401_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	if sceneId ~= x550401_g_SceneID2 then	
		AddQuestNumText(sceneId, x550401_g_ScriptId, x550401_g_MissionName2)
	end		
end



--**********************************

--检测接受条件

--**********************************

function x550401_ProcAcceptCheck(sceneId, selfId, targetId)
	return 1
end


--**********************************

--检测查看条件

--**********************************

function x550401_CheckPushList(sceneId, selfId, targetId)
	
end

--**********************************

--接受

--**********************************

function x550401_ProcAccept(sceneId, selfId)

    
end



--**********************************

--放弃

--**********************************

function x550401_ProcQuestAbandon(sceneId, selfId, MissionId)


end



--**********************************

--检测是否可以提交

--**********************************

function x550401_CheckSubmit( sceneId, selfId, targetId)


end



--**********************************

--提交

--**********************************

function x550401_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)

	
end


--进入区域事件

--**********************************

function x550401_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x550401_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end

