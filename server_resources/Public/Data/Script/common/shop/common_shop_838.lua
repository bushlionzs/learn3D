--功能：罗马铸甲术护手类防具配方店

x560838_g_ScriptId = 560838
x560838_g_MissionName="罗马铸甲术护手类防具配方店"
x560838_g_ShopList={838}
--**********************************

--任务入口函数

--**********************************

function x560838_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x560838_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x560838_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	

	local nLevel = GetLevel(sceneId,selfId)
	if nLevel >= 0 then
		AddQuestNumText(sceneId, x560838_g_ScriptId, x560838_g_MissionName,10)
	else
		return
	end
	
end



--**********************************

--检测接受条件

--**********************************

function x560838_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x560838_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x560838_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x560838_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x560838_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x560838_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x560838_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x560838_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end