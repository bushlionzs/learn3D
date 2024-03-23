
--点击（NPC）
function x300315_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	--合服开关
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --升级数据库开关
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end
    
    --测试服开关
    --if GetTestServerToggle() == 0 then
    --    return
    --end

    --战场自己的开关
    if GetBattleSceneToggle( BATTLESCENE_TYPE_KINGBATTLE ) == 0 then
        return
    end

	AddQuestNumText(sceneId,300315,"【介绍】国王战场",0,1)--增加按钮:领取测试费	
end

--点击（按钮）点击该任务后执行此脚本
function x300315_ProcEventEntry( sceneId, selfId, targetId,state,index)

	--合服开关
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --升级数据库开关
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end
    
    --测试服开关
    --if GetTestServerToggle() == 0 then
    --    return
    --end

    --战场自己的开关
    if GetBattleSceneToggle( BATTLESCENE_TYPE_KINGBATTLE ) == 0 then
        return
    end

	local Readme_1   = "#Y【介绍】国王战场#W#r"
	local Readme_2   = "#G一，挑战条件：#W#r"
	local Readme_3   = "  1，每周日#G14：00-17：00#W间可以挑战报名。#r  2，当等级排行榜第一名大于等于50级时，若某一国家没有国王时，则每天都会开启国王战场直到产生国王为止。#r"
	local Readme_4   = "  3，您必须是帮主。#r"
	local Readme_6   = "  4，帮会人数不少于#G15人#W。#r"
	local Readme_7   = "在报名时间内，帮会实力高的帮会会顶替帮会实力低的帮会，并会始终显示。到达17：00，帮会实力最高的帮会成功报名，参加当天的国王战场。国王战场将在当天20：00~20：20之间开启。#r"
	local Readme_8   = "#G二，胜负判定：#W#r"
	local Readme_9  = "  1，战场开启#G2分钟#W后才可#G判定胜负#W。#r"
	local Readme_10  = "  2，20分钟内将对方全部清出战场方获胜。#r"
	local Readme_11  = "  3，20分钟内未分出胜负，则判定有帮主方获胜。#r"
	local Readme_12  = "  4，双方帮主均在战场或均死亡，则判定人数多的一方获胜。#r"
	local Readme_13  = "  5，双方人数相等，则判定帮主死亡次数少的一方获胜。#r"
	local Readme_14  = "  6，双方帮主死亡次数相等，则判定国王方获胜。#r"
	local Readme_15  = "  7，双方都无帮主且人数相等时，判定国王方获胜。#r"	
	local Readme_16  = "#G三，战场规则：#W#r"
	local Readme_17  = "  1，进入战场时间只开放#G2分钟#W，请在开战后抓紧时间进入战场。#r"
	local Readme_18 = "  2，每人只有#G一次#W进入战场的机会，在战场中离线或通过NPC主动离开战场，则不能再次进入。#r"
	local Readme_19  = "  3，在战场中每人有#G5次#W复活机会，#G第6次#W死亡后会被系统强制离开战场。#r"	
	local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_6..Readme_7..Readme_8..Readme_9..Readme_10..Readme_11..Readme_12..Readme_13..Readme_14..Readme_15..Readme_16..Readme_17..Readme_18..Readme_19
	BeginQuestEvent(sceneId);AddQuestText(sceneId,Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId)
end

--点击（确定）
function x300315_ProcAcceptCheck( sceneId, selfId, NPCId )

end




--**********************************
--接受
--**********************************
function x300315_ProcAccept( sceneId, selfId )
end

--**********************************
--放弃
--**********************************
function x300315_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x300315_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x300315_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x300315_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x300315_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x300315_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x300315_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end



