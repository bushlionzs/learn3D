
x300746_g_ScriptId = 300746

--上一个任务的ID
--g_MissionIdPre =

--后续任务ID
--x300746_g_MessionIdAfter0	= 300747
--x300746_g_MessionIdAfter1	= 300748
--x300746_g_MessionIdAfter2	= 300749

--任务文本描述
x300746_g_MissionName="【帮会战场介绍】"
x300746_g_MissionName0="【帮会战场】"
--x300746_g_MissionName1="十三翼之战"
--x300746_g_MissionName2="八鲁湾之战"

--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x300746_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_GUILDBATTLE ) == 0 then
        return
    end

	local Readme_1 = "#Y【帮会战场介绍】#W#r"
	
	local Readme_2 = "#G一、帮战报名：#W#r帮主可在每周二和周五的17：00-18：30之间报名，系统将在20：00自动开启帮会战场。#r"
	
	local Readme_3 = "#G二、胜负判定：#W#r1、规定时间内，积分最先达到100分的一方获胜。#r2、在规定时间内未分出胜负，则积分高的一方获胜。#r3、在战场结束前，击倒敌方战旗，可提前获得胜利。#r"
	
	local Readme_4 = "#G三、战场规则：#W#r1、战场中的4个粮仓可以占领，占领后每个粮仓每10秒将产出1点积分和1点战场资源。#r2、占领全部4个粮仓将获得双倍产出。#r3、在夺取军旗时不可使用技能，每提交一次获得10积分。#r4、军旗可以在本方仓库交付，也可在已占领的2个临近粮仓中任意一个交付。#r"	
	
	local Readme_5 = "5、在战场中，帮主可以消耗60战场资源为本方成员购买持续20分钟的增加10暴击或增加10韧性的Buff，也可以消耗20战场资源为本方战旗补充10%的生命值。"
	
	local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
	
	BeginQuestEvent(sceneId);AddQuestText(sceneId,Readme)
	
	--AddQuestNumText(sceneId,x300746_g_MessionIdAfter0,x300746_g_MissionName0,1)
	
	--AddQuestNumText(sceneId,x300746_g_MessionIdAfter1,x300746_g_MissionName1,1)
	
	--AddQuestNumText(sceneId,x300746_g_MessionIdAfter2,x300746_g_MissionName2,1)
	
	EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId)
	
end

--**********************************
--列举事件
--**********************************
function x300746_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_GUILDBATTLE ) == 0 then
        return
    end
    
	local pos = GetLevel(sceneId, selfId)--判断是否大于45级
	if pos >= 20 then
		AddQuestNumText(sceneId,x300746_g_ScriptId,x300746_g_MissionName,1);
	end
	
end


--********************
--检测接受条件
--**********************************
function x300746_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x300746_ProcAccept( sceneId, selfId )

end

--**********************************
--放弃
--**********************************
function x300746_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x300746_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x300746_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x300746_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x300746_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x300746_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x300746_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
