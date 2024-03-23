--功能：罗马铸甲配方店

x560151_g_ScriptId = 560151
x560151_g_MissionName="罗马铸甲配方店"
x560151_g_ShopList={151}
--**********************************

--任务入口函数

--**********************************

function x560151_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	DispatchShopItem( sceneId, selfId, targetId, x560151_g_ShopList[1] )
end



--**********************************

--列举事件

--**********************************

function x560151_ProcEnumEvent(sceneId, selfId, targetId, MissionId)	
                AddQuestNumText(sceneId, x560151_g_ScriptId, x560151_g_MissionName,10)

--	local nLevel = GetLevel(sceneId,selfId)
--	if nLevel >= 60 then
--		AddQuestNumText(sceneId, x560151_g_ScriptId, x560151_g_MissionName,10)
--	else
--		return
--	end
	
end



--**********************************

--检测接受条件

--**********************************

function x560151_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x560151_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x560151_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x560151_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x560151_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x560151_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x560151_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x560151_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end