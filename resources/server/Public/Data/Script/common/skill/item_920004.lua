

--活动触发
function x920004_ProcEventEntry( sceneId, selfId, bufIndex,rorf )
	if rorf == 1 then --删除BUF
		-- 恢复为非PK模式
		SetCurPKMode( sceneId, selfId, 0, 1)
	end
end

