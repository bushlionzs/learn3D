
x300740_g_ScriptId_ = 300740
x300740_g_MissionName = "离开监狱"
x300740_g_MissionInfo = "想要离开监狱吗"

--点击（NPC）
function x300740_ProcEnumEvent( sceneId, selfId, targetId )

	AddQuestNumText(sceneId,x300740_g_ScriptId_,x300740_g_MissionName)
	
end



--点击（按钮）点击该任务后执行此脚本
function x300740_ProcEventEntry( sceneId, selfId, targetId,state,index)	


	
		BeginQuestEvent(sceneId);AddQuestText(sceneId,x300740_g_MissionInfo);EndQuestEvent(sceneId);
		DispatchQuestInfo(sceneId, selfId, targetId, 300740, -1)
		

	
end



--点击（确定）
function x300740_ProcAcceptCheck( sceneId, selfId )


	local IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId,PK_PUNISH_PRISON_TIME_BUF_ID )

	if IsHaveFlag > 0 then
		BeginQuestEvent(sceneId);AddQuestText(sceneId,"时间没到，继续在监狱里享受生活吧");EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,"时间没到，继续在监狱里享受生活吧",8,2)
		return
	end

	SetPKValue(sceneId, selfId, 0)
	SetCurPKMode(sceneId, selfId, 0, 1)		--强制PK模式为国家模式

	BeginQuestEvent(sceneId);AddQuestText(sceneId,"出狱了，记得出去以后一定要低调呀");EndQuestEvent(sceneId);
	DispatchQuestTips(sceneId,selfId)

	Msg2Player(sceneId,selfId,"出狱了，记得出去以后一定要低调呀",8,2)
	SetPlayerMutexState( sceneId, selfId,PLAYER_STATE_READYFUBEN,0 )
	SetPlayerMutexState( sceneId,selfId ,PLAYER_STATE_PRISON ,0)

	if GetLevel(sceneId, selfId) >= 10 then
		local PosX,PosY = 128,82
		if GetCurCountry( sceneId, selfId ) == 0 then--楼兰
			NewWorld( sceneId, selfId ,50,PosX,PosY,300740)
		elseif GetCurCountry( sceneId, selfId ) == 1 then--天山
			NewWorld( sceneId, selfId ,150,PosX,PosY,300740)
		elseif GetCurCountry( sceneId, selfId ) == 2 then--昆仑
			NewWorld( sceneId, selfId ,250,PosX,PosY,300740)
		elseif GetCurCountry( sceneId, selfId ) == 3 then--敦煌
			NewWorld( sceneId, selfId ,350,PosX,PosY,300740)
		end
	else
		local PosX,PosY = 76,62
		if GetCurCountry( sceneId, selfId ) == 0 then--楼兰
			NewWorld( sceneId, selfId ,87,PosX,PosY,300740)
		elseif GetCurCountry( sceneId, selfId ) == 1 then--天山
			NewWorld( sceneId, selfId ,187,PosX,PosY,300740)
		elseif GetCurCountry( sceneId, selfId ) == 2 then--昆仑
			NewWorld( sceneId, selfId ,287,PosX,PosY,300740)
		elseif GetCurCountry( sceneId, selfId ) == 3 then--敦煌
			NewWorld( sceneId, selfId ,387,PosX,PosY,300740)
		end		
	end

end

--**********************************
--接受
--**********************************
function x300740_ProcAccept( sceneId, selfId )

end
--**********************************
--放弃
--**********************************
function x300740_ProcQuestAbandon( sceneId, selfId )
end
--**********************************
--继续
--**********************************
function x300740_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300740_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300740_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300740_ProcQuestObjectKilled( sceneId, selfId, objdataId )
end
--**********************************
--进入区域事件
--**********************************
function x300740_ProcAreaEntered( sceneId, selfId, zoneId )
end
--**********************************
--道具改变
--**********************************
function x300740_ProcQuestItemChanged( sceneId, selfId, itemdataId )
end