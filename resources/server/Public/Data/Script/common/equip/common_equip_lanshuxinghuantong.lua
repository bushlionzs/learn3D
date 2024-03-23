
--MisDescBegin
--脚本号
x800089_g_ScriptId = 800089

--任务文本描述
x800089_g_MissionName="装备回炉（洗蓝）"

--MisDescEnd

--**********************************
--任务入口函数
--**********************************
function x800089_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本
end

--********************
--检测接受条件
--**********************************
function x800089_ProcAcceptCheck( sceneId, selfId, NPCId )

		return 1
		
end

function x800089_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x800089_g_ScriptId,x800089_g_MissionName,3);

end
