--功能：中心传送
--NPC：中心传送使者

x211022_g_ScriptId = 211022
x211022_g_MissionName="蔑里乞部"
--**********************************

--任务入口函数

--**********************************

function x211022_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferFunc",sceneId, selfId, 1,86,130)
end

--用户通过UI请求切换场景
--在CGMapInfoHandler中被呼叫
function x211022_OnChangeSceneEvent(sceneId, selfId, index, Backhaul)	
				
	--得到进入该场景需要的最小等级、场景ID，位置信息
	local MinUserLevel, targetSceneId, PosX,PosZ = GetNewSceneInfoByIndex(sceneId,index)
	
	local level = GetLevel(sceneId, selfId)
	
	if level >= MinUserLevel then
		if IsInStall(sceneId, selfId) == 0 then
			NewWorld(sceneId,selfId,targetSceneId,PosX,PosZ,211022)	
		end
	end

end

--**********************************

--列举事件

--**********************************

function x211022_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x211022_g_ScriptId, x211022_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x211022_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x211022_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x211022_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x211022_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x211022_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x211022_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x211022_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x211022_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end