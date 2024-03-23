--##############################################
--##跨服报名场景离开场景脚本 by rj 2010-10-29 ##
--##############################################

x303103_g_ScriptId          		= 303103
x303103_g_MissionName       		= "回到大都"
x303100_g_LeaveToSceneIdAry		    = {0, 0, 0, 0}								--四国从报名场景离开时退回场景 id
x303100_g_LeaveToPosAry		     	= {{168, 68}, {168, 68}, {168, 68}, {168, 68}}		--四国从报名场景离开时退回场景坐标

----------------------------------------------------------------------------------------------
--枚举
----------------------------------------------------------------------------------------------
function x303103_ProcEnumEvent(sceneId, selfId, targetId, missionId)

    AddQuestNumText(sceneId, x303103_g_ScriptId, x303103_g_MissionName, 3)
end

----------------------------------------------------------------------------------------------
--默认事件
----------------------------------------------------------------------------------------------
function x303103_ProcEventEntry(sceneId, selfId, targetId, scriptId, idExt)

	--合服开关
    if GetMergeDBToggle() == 1 then
        return
    end
    
  	--升级数据库开关
	if GetUpdateDBBeforeToggle() == 1 then
		return
	end

   	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, "\t如果您已报名，离开跨服报名场景将无法收到进入战场通知，是否离开跨服报名场景？")
 	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, targetId, x303103_g_ScriptId, -1)
    return
end

----------------------------------------------------------------------------------------------
--检测接受条件
----------------------------------------------------------------------------------------------
function x303103_ProcAcceptCheck(sceneId, selfId, npcId)

	--根据不同国家导向到不同的自身服地图
	local nCountry = GetCurCountry(sceneId, selfId)
	NewWorld
		(
		sceneId, 
		selfId, 
		x303100_g_LeaveToSceneIdAry[nCountry + 1], 
		x303100_g_LeaveToPosAry[nCountry + 1][1],
		x303100_g_LeaveToPosAry[nCountry + 1][2], 
 		x303103_g_ScriptId
 		)
end
