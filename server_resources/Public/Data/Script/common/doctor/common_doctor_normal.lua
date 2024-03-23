--功能：普通医生


x300411_g_ScriptId = 300411
x300411_g_MissionName="免费治疗"
--**********************************

--任务入口函数

--**********************************

function x300411_ProcEventEntry(sceneId, selfId, targetId)	--点击该任务后执行此脚本
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "好了，以后再去冒险的时候，记得要时刻注意自己的安危。")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	BeginQuestEvent(sceneId)
		local strText = "你全身恢复了健康"
		AddQuestText(sceneId,strText);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	
	RestoreHp(sceneId, selfId,100)
	local ZhiYe= GetZhiye( sceneId, selfId)
	if ZhiYe~=0 then
		RestoreRage(sceneId, selfId,100)
	end
end



--**********************************

--列举事件

--**********************************

function x300411_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
		AddQuestNumText(sceneId, x300411_g_ScriptId, x300411_g_MissionName)
end



--**********************************

--检测接受条件

--**********************************

function x300411_ProcAcceptCheck(sceneId, selfId, targetId)

end

--**********************************

--接受

--**********************************

function x300411_ProcAccept(sceneId, selfId)
                                                                   
	     
end



--**********************************

--放弃

--**********************************

function x300411_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x300411_CheckSubmit( sceneId, selfId, targetId)

end



--**********************************

--提交

--**********************************

function x300411_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)
	
end



--**********************************

--杀死怪物或玩家

--**********************************

function x300411_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x300411_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--道具改变

--**********************************

function x300411_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end