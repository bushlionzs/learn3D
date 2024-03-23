--回城技能



-----------------------------------------------------------------------


function x417001_ProcEventEntry( sceneId, selfId, bufIndex,rorf )
	
	if IsBusMember(sceneId, selfId) == 1 and rorf == 0 then
		local msg = "运镖、乘坐公交车或者护送状态时不能使用回城卷轴！"
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,msg,8,2)
		return
	end

    -- 如果在世界杯战场传出前检查是否有幽谷玄冰，有就删除
    local iCount = GetItemCountInBag( sceneId, selfId, 13080024)
    if iCount > 0 then
        DelItem( sceneId, selfId, 13080024, iCount)
    end
	
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

	if rorf == 0 then
	
		-- 在舞厅里先清除禁止骑马标记
    	if sceneId == 14 then
        	SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_DANCERY, 0)
            -- 恢复变身
            if IsHaveSpecificImpact( sceneId, selfId, 7651) == 1 then
                CancelSpecificImpact( sceneId, selfId, 7651)
            elseif IsHaveSpecificImpact( sceneId, selfId, 7652) == 1 then
                CancelSpecificImpact( sceneId, selfId, 7652)
            elseif IsHaveSpecificImpact( sceneId, selfId, 7653) == 1 then
                CancelSpecificImpact( sceneId, selfId, 7653)
            elseif IsHaveSpecificImpact( sceneId, selfId, 7654) == 1 then
                CancelSpecificImpact( sceneId, selfId, 7654)
            elseif IsHaveSpecificImpact( sceneId, selfId, 7655) == 1 then
                CancelSpecificImpact( sceneId, selfId, 7655)
            elseif IsHaveSpecificImpact( sceneId, selfId, 7656) == 1 then
                CancelSpecificImpact( sceneId, selfId, 7656)
            end
	    end
	    
		local selfcountry =GetCurCountry( sceneId, selfId)
		local nLevel = GetLevel(sceneId, selfId)

				if selfcountry ==0 then
					if nLevel < 10 then
						if sceneId == 87 then
							SetPos(sceneId,selfId,193,77)
						else
							TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
							NewWorld(sceneId,selfId,87,77,65, 417001)
						end
					elseif nLevel >=10 then
						if sceneId ==50 then
							SetPos(sceneId,selfId,121,115)
						else
							TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
							NewWorld(sceneId,selfId,50,122,115, 417001)
						end							
					end	
				
				elseif selfcountry ==1 then
					if nLevel < 10 then
						if sceneId == 187 then
							SetPos(sceneId,selfId,58,78)
						else
							TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
							NewWorld(sceneId,selfId,187,58,78, 417001)
						end
					elseif nLevel >=10 then
						if sceneId ==150 then
							SetPos(sceneId,selfId,124,118)
						else
							TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
							NewWorld(sceneId,selfId,150,124,118, 417001)
						end							
					end					

				elseif selfcountry ==2 then
					if nLevel < 10 then
						if sceneId == 287 then
							SetPos(sceneId,selfId,49,209)
						else
							TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
							NewWorld(sceneId,selfId,287,49,209, 417001)
						end
					elseif nLevel >=10 then
						if sceneId ==250 then
							SetPos(sceneId,selfId,124,137)
						else
							TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
							NewWorld(sceneId,selfId,250,124,137, 417001)
						end							
					end						

				elseif selfcountry ==3 then
					if nLevel < 10 then
						if sceneId == 387 then
							SetPos(sceneId,selfId,211,199)
						else
							TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
							NewWorld(sceneId,selfId,387,211,199, 417001)
						end
					elseif nLevel >=10 then
						if sceneId ==350 then
							SetPos(sceneId,selfId,124,137)
						else
							TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
							NewWorld(sceneId,selfId,350,124,137, 417001)
						end							
					end
		end
	end
end

