
x310153_g_ScriptId 					= 	310153  
 
function x310153_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_COUNTRYBATTLELITE ) == 0 then
        return
    end

	AddQuestNumText(sceneId,310153,"【介绍】屠城战",1)
end



--点击（按钮）点击该任务后执行此脚本
function x310153_ProcEventEntry( sceneId, selfId, targetId)

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_COUNTRYBATTLELITE ) == 0 then
        return
    end
    		
		-- local MissionName = x300767_g_MissionName;
		BeginQuestEvent(sceneId)
			local Readme_1 = "#Y【介绍】屠城战#r#W #r"			
			
			local Readme_2 = "\t当等级排行榜第一名大于70级时，屠城战会每两周开启一次，开启时间为周六晚20：00-21：00 时会进行四国之间的战争，您的国家将处于#G进攻#W或#G防守#W之间的任意一方。#r"
			
			local Readme_3 = "\t屠城战开始时，会在防守方的外城，古道和边境出现10个象征#R国家军力#W的NPC。#r"
			
			local Readme_4 ="\t#G40级以上#W且身处#R王城#W，#R外城#W，#R古道#W，#R边境#W，#R迷宫#W或#R中兴府#W的国民会收到#R系统提示#W，#G点击确定#W，将#R成功参加屠城战#W。#R选择放弃#W，则不会#G获得屠城战奖励#W。您还可以在20:00-20:20之间，来我这里点击按钮#Y【国家】屠城战#W来参加屠城战。#r"
			
			local Readme_5="\t在王城#G国家管理员#W和边境#G拓道#W选择#Y【屠城战】查询#W，可进行查询。#r"
			
			local Readme_6="\t屠城战中，如果国家#G处于进攻方#W，需要尽可能的摧毁更多敌国的国家军力。#r"
			
			local Readme_7= "\t如果国家#G处于防守方#W需要全力保卫自己国家的国家军力的安全。#r"
			
			local Readme_8 ="\t屠城战结束后#G21：00-21:20#W之间，您可以在我这领取#G丰厚奖励#W，奖励的多少取决于您所在国家#G摧毁或#G防守住#K国家军力的数量。#r"
			
			local Readme_9 ="\t参加屠城战后，您只能在#R四国的王城，外城，古道，边境和中兴府#K等场景活动，如果您前往#R其它场景#K您的任务将被#R清除#K，将不能再次参加屠城战活动。"
			
			local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5..Readme_6..Readme_7..Readme_8..Readme_9
		AddQuestText( sceneId,Readme)
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
		
		
end



--点击（确定）
function x310153_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x310153_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x310153_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x310153_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x310153_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x310153_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x310153_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x310153_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x310153_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end