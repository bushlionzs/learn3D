--帮贡测试用
--添加帮贡

--************************************************************************
--MisDescBegin

--脚本号
x300306_g_ScriptId = 300306


--任务文本描述
x300306_g_MissionName="神啊，请赐我帮贡吧！"
x300306_g_MissionInfo="就赏你这100帮贡吧！"

function x300306_ProcEventEntry( sceneId, selfId, targetId )
--AddGuildUserPoint(sceneId,selfId,100)
	BeginQuestEvent(sceneId)
		
		AddQuestText(sceneId,x300306_g_MissionInfo)
	
	EndQuestEvent(sceneId)
	DispatchQuestInfo(sceneId,selfId,targetId,x300306_g_ScriptId,-1)
	
end

--**********************************
function x300306_ProcAcceptCheck( sceneId, selfId, NPCId )

	return	1

end

--**********************************
function x300306_ProcAccept( sceneId, selfId )

	AddGuildUserPoint(sceneId,selfId,100)

end

--**********************************

function x300306_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
--	AddGuildUserPoint(sceneId,selfId,100)
	AddQuestNumText(sceneId, x300306_g_ScriptId, x300306_g_MissionName)
end