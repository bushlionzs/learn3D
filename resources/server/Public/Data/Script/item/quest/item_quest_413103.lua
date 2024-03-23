--药物

--MisDescBegin
x413103_g_ScriptId = 413103
x413103_g_MissionId = 1005
x413103_g_MissionKind = 13
x413103_g_LevelLess	= 	15 
x413103_g_Name	="金国俘虏" 
x413103_g_DemandItem ={{id=11990008,num=6}}
x413103_g_ExtTarget={{type=20,n=1,target="得到一封红螺堂密信"}}
x413103_g_MissionHelp =	""
x413103_g_MissionName="【支线】塔塔尔宝石"
x413103_g_MissionInfo="    不要杀我，如果你给我带来6颗塔塔尔宝石我会报答你的。"  --任务描述
x413103_g_MissionCompleted="\t多谢你了，这个宝贝就送给你吧。"					--完成任务npc说话的话
x413103_g_ContinueInfo=""
x413103_g_BonusMoney1 =40
x413103_g_BonusMoney2 =0
x413103_g_BonusMoney3 =0
x413103_g_BonusItem	=	{}
x413103_g_BonusChoiceItem ={10206004,10206005,10206006,10206007,10206008,10206009,10206013,10206014,10206015,10206016,10206017,10206018}
x413103_g_ExpBonus = 0

--MisDescEnd

--**********************************

--任务入口函数

--**********************************

function x413103_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本

	if GetItemCount(sceneId,selfId,x413103_g_DemandItem[1].id) > 5 then
				BeginQuestEvent(sceneId)
				 	AddQuestText(sceneId,"#Y"..x413103_g_MissionName.."\n")
        			AddQuestText(sceneId,x413103_g_MissionCompleted)
		    if x413103_g_BonusMoney1 > 0 then
							AddQuestMoneyBonus1(sceneId, x413103_g_BonusMoney1 )
				end
				for i=0, 11 do
						if GetZhiye( sceneId, selfId)==i then
						local ii =i+1
					    		AddQuestItemBonus(sceneId, x413103_g_BonusChoiceItem[ii], 1)
					  end
				end
		    EndQuestEvent()
        DispatchQuestContinueInfo(sceneId, selfId, targetId, x413103_g_ScriptId, x413103_g_MissionId)
  elseif GetItemCount(sceneId,selfId,x413103_g_DemandItem[1].id) < 6 then
  			BeginQuestEvent(sceneId)
        AddQuestText(sceneId,x413103_g_MissionInfo)
		    EndQuestEvent()
        DispatchQuestEventList(sceneId, selfId, targetId)
  
  end
end



--**********************************

--列举事件

--**********************************

function x413103_ProcEnumEvent(sceneId, selfId, targetId, MissionId)


	if  x413103_CheckPushList(sceneId, selfId, targetId) > 0 then
		AddQuestNumText(sceneId, x413103_g_ScriptId, x413103_g_MissionName,8)
	end
	
end



--**********************************

--检测接受条件

--**********************************

function x413103_ProcAcceptCheck(sceneId, selfId, targetId)

					return 1

end


--**********************************

--检测查看条件

--**********************************

function x413103_CheckPushList(sceneId, selfId, targetId)
        		if IsQuestHaveDone(sceneId, selfId, x413103_g_MissionId) == 0 then
        		           		return 1
        		 end
        return 0
	
end

--**********************************

--接受

--**********************************

function x413103_ProcAccept(sceneId, selfId)

	                                                  
     	                                    
	     
end



--**********************************

--放弃

--**********************************

function x413103_ProcQuestAbandon(sceneId, selfId, MissionId)

	

end



--**********************************

--检测是否可以提交

--**********************************

function x413103_CheckSubmit( sceneId, selfId, targetId)
	

end



--**********************************

--提交

--**********************************

function x413103_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)

		--AddExp(sceneId, selfId, x413103_g_ExpBonus)
		
		for i=0, 11 do
						if GetZhiye( sceneId, selfId)==i then
								local ii =i+1
					    		BeginAddItem(sceneId)
								AddItem( sceneId, x413103_g_BonusChoiceItem[ii], 1 )
								local ret = EndAddItem(sceneId,selfId)
								if ret > 0 then
										AddItemListToPlayer(sceneId,selfId)
										AddMoney( sceneId, selfId, 1, x413103_g_BonusMoney1 )
										DelItem(sceneId, selfId, x413103_g_DemandItem[1].id, x413103_g_DemandItem[1].num)
										QuestCom(sceneId, selfId, x413103_g_MissionId)
								else
										BeginQuestEvent(sceneId)
										AddQuestText(sceneId,"物品栏已满，无法得到任务物品！")
										EndQuestEvent(sceneId)
										DispatchQuestTips(sceneId,selfId)
								end
					  end
		end
	
	

	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x413103_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	 

end



--**********************************

--进入区域事件

--**********************************

function x413103_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x413103_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end

