--药物

--MisDescBegin
x413101_g_ScriptId = 413101
x413101_g_MissionId = 1003
x413101_g_MissionKind = 13
x413101_g_LevelLess	= 	15 
x413101_g_Name	="窑口守门人" 
x413101_g_DemandItem ={{id=13010082,num=1}}
x413101_g_ExtTarget={{type=20,n=1,target="得到一封红螺堂密信"}}
x413101_g_MissionHelp =	""
x413101_g_MissionName="赤蛇鞭"
x413101_g_MissionInfo="\t我的赤蛇鞭本来放在雕像上的，结果被阿兰人抢走了，到窑口里面可以找到他们，帮我夺回赤蛇鞭吧。"  --任务描述
x413101_g_MissionCompleted="\t好的谢谢你了！"					--完成任务npc说话的话
x413101_g_ContinueInfo=""
x413101_g_BonusMoney1 =1000
x413101_g_BonusMoney2 =0
x413101_g_BonusMoney3 =0
x413101_g_BonusItem	=	{}
x413101_g_BonusChoiceItem ={}
x413101_g_ExpBonus = 0

--MisDescEnd

--**********************************

--任务入口函数

--**********************************

function x413101_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本

	if GetItemCount(sceneId,selfId,x413101_g_DemandItem[1].id) > 0 then
				BeginQuestEvent(sceneId)
        AddQuestText(sceneId,x413101_g_MissionCompleted)
		    if x413101_g_BonusMoney1 > 0 then
		    local addmoney =x413101_g_BonusMoney1*GetLevel(sceneId, selfId)
							AddQuestMoneyBonus1(sceneId, addmoney )
				end
		    EndQuestEvent()
        DispatchQuestContinueInfo(sceneId, selfId, targetId, x413101_g_ScriptId, x413101_g_MissionId)
  elseif GetItemCount(sceneId,selfId,x413101_g_DemandItem[1].id) == 0 then
  			BeginQuestEvent(sceneId)
        AddQuestText(sceneId,x413101_g_MissionInfo)
		    EndQuestEvent()
        DispatchQuestEventList(sceneId, selfId, targetId)
  
  end
end



--**********************************

--列举事件

--**********************************

function x413101_ProcEnumEvent(sceneId, selfId, targetId, MissionId)


	if  x413101_CheckPushList(sceneId, selfId, targetId) > 0 then
		AddQuestNumText(sceneId, x413101_g_ScriptId, x413101_g_MissionName,8)
	end
	
end



--**********************************

--检测接受条件

--**********************************

function x413101_ProcAcceptCheck(sceneId, selfId, targetId)

					return 1

end


--**********************************

--检测查看条件

--**********************************

function x413101_CheckPushList(sceneId, selfId, targetId)
        		           		return 1
      
	
end

--**********************************

--接受

--**********************************

function x413101_ProcAccept(sceneId, selfId)

	                                                  
     	                                    
	     
end



--**********************************

--放弃

--**********************************

function x413101_ProcQuestAbandon(sceneId, selfId, MissionId)

	

end



--**********************************

--检测是否可以提交

--**********************************

function x413101_CheckSubmit( sceneId, selfId, targetId)
	

end



--**********************************

--提交

--**********************************

function x413101_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
		local addmoney =x413101_g_BonusMoney1*GetLevel(sceneId, selfId)
		--AddExp(sceneId, selfId, x413101_g_ExpBonus)
		AddMoney( sceneId, selfId, 0, addmoney )
		DelItem(sceneId, selfId, x413101_g_DemandItem[1].id, x413101_g_DemandItem[1].num)
	
	

	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x413101_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	 

end



--**********************************

--进入区域事件

--**********************************

function x413101_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x413101_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end


