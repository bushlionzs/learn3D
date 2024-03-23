--药物

--MisDescBegin
x413102_g_ScriptId = 413102
x413102_g_MissionId = 1004
x413102_g_MissionKind = 13
x413102_g_LevelLess	= 	15 
x413102_g_Name	="豁儿赤" 
x413102_g_DemandItem ={{id=11990007,num=4}}
x413102_g_ExtTarget={{type=20,n=1,target="得到4个神秘蜘蛛牙"}}
x413102_g_MissionHelp =	""
x413102_g_MissionName="神秘的蜘蛛牙"
x413102_g_MissionInfo="    如果你能带来四个神秘的蜘蛛牙，我不会亏待你的。"  --任务描述
x413102_g_MissionCompleted="    很好的施法材料，这是你的奖励。"					--完成任务npc说话的话
x413102_g_ContinueInfo=""
x413102_g_BonusMoney1 =40
x413102_g_BonusMoney2 =0
x413102_g_BonusMoney3 =0
x413102_g_BonusItem	=	{}
x413102_g_BonusChoiceItem ={10016002,10026002,10036002,10046002,10056002,10066002,10352002,10362002,10372002,10382002,10392002,10402002}
x413102_g_ExpBonus = 0

--MisDescEnd

--**********************************

--任务入口函数

--**********************************

function x413102_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本

	if GetItemCount(sceneId,selfId,x413102_g_DemandItem[1].id) > 3 then
		BeginQuestEvent(sceneId)
        AddQuestText(sceneId,x413102_g_MissionCompleted)
		    if x413102_g_BonusMoney1 > 0 then
					AddQuestMoneyBonus1(sceneId, x413102_g_BonusMoney1 )
			end
			for i=0, 11 do
				if GetZhiye( sceneId, selfId)==i then
						local ii =i+1
					    AddQuestItemBonus(sceneId, x413102_g_BonusChoiceItem[ii], 1)
				end
			end
		EndQuestEvent()
        DispatchQuestContinueInfo(sceneId, selfId, targetId, x413102_g_ScriptId, x413102_g_MissionId)
 	elseif GetItemCount(sceneId,selfId,x413102_g_DemandItem[1].id) < 4 then
  		BeginQuestEvent(sceneId)
        AddQuestText(sceneId,x413102_g_MissionInfo)
		EndQuestEvent()
        DispatchQuestEventList(sceneId, selfId, targetId)
  
  end
end



--**********************************

--列举事件

--**********************************

function x413102_ProcEnumEvent(sceneId, selfId, targetId, MissionId)


	if  x413102_CheckPushList(sceneId, selfId, targetId) > 0 then
		AddQuestNumText(sceneId, x413102_g_ScriptId, x413102_g_MissionName,8)
	end
	
end



--**********************************

--检测接受条件

--**********************************

function x413102_ProcAcceptCheck(sceneId, selfId, targetId)

					return 1

end


--**********************************

--检测查看条件

--**********************************

function x413102_CheckPushList(sceneId, selfId, targetId)
        		if IsQuestHaveDone(sceneId, selfId, x413102_g_MissionId) == 0 then
        		           		return 1
       	end
       return 0
	
end

--**********************************

--接受

--**********************************

function x413102_ProcAccept(sceneId, selfId)

	                                                  
     	                                    
	     
end



--**********************************

--放弃

--**********************************

function x413102_ProcQuestAbandon(sceneId, selfId, MissionId)

	

end



--**********************************

--检测是否可以提交

--**********************************

function x413102_CheckSubmit( sceneId, selfId, targetId)
	

end



--**********************************

--提交

--**********************************

function x413102_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)

		--AddExp(sceneId, selfId, x413102_g_ExpBonus)
		
		for i=0, 11 do
			if GetZhiye( sceneId, selfId)==i then
					local ii =i+1
					
					BeginAddItem(sceneId)
					AddItem( sceneId, x413102_g_BonusChoiceItem[ii], 1 )
					local ret = EndAddItem(sceneId,selfId)
					if ret > 0 then
						
						AddItemListToPlayer(sceneId,selfId)
						AddMoney( sceneId, selfId, 1, x413102_g_BonusMoney1 )
						DelItem(sceneId, selfId, x413102_g_DemandItem[1].id, x413102_g_DemandItem[1].num)
						QuestCom(sceneId, selfId, x413102_g_MissionId)
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

function x413102_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	 

end



--**********************************

--进入区域事件

--**********************************

function x413102_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x413102_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end

