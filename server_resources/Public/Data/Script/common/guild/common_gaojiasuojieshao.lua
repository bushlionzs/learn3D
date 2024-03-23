
x300747_g_ScriptId = 300747


--任务文本描述
x300747_g_MissionName="高加索之战"


--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x300747_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本

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

			BeginQuestEvent(sceneId);
		
			local localexp = (GetLevel( sceneId, selfId )) * 1000*0.3*5		
		
			local Readme_1 = "#Y【帮会战场】#W#r"
		
			local Readme_2 = "#G一，帮战报名：#W#r"
			
			local Readme_3 = "帮主可在每周二和周五的17：00-18：30之间报名，系统将在20：00自动开启帮战。#r"
			
			local Readme_4 = "#G二，胜负判定：#W#r"
			
			local Readme_5 = "  1，规定时间内，积分最先达到100分的一方获胜。#r"
			
			local Readme_6 = "  2，在规定时间内未分出胜负，则积分高的一方获胜。#r"

			local Readme_7 = "#G三，战场规则：#W#r"	
			
			local Readme_8 = "  1，战场中的4个粮仓可以占领，占领后每个粮仓将产出一点积分。#r"
			
			local Readme_9= "  2，占领全部4个粮仓将获得粮仓的双倍产出积分。#r"
			
			local Readme_10= "  3，在夺取军旗时不可使用技能，每提交一次记10分。#r"
			
			local Readme_11= "  4，军旗可以在本方仓库交付，也可在已经占领的2个临近粮仓中任意一个交付。"
			
			local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5..Readme_6..Readme_7..Readme_8..Readme_9..Readme_10..Readme_11
				
			AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId);DispatchQuestInfoNM( sceneId, selfId, targetId, -1, -1,2 );
	
	
end

--**********************************
--列举事件
--**********************************
function x300747_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

end


--********************
--检测接受条件
--**********************************
function x300747_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x300747_ProcAccept( sceneId, selfId )

	
end

--**********************************
--放弃
--**********************************
function x300747_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x300747_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x300747_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x300747_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x300747_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x300747_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x300747_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
