

--囚禁BUFF对应的事件
function x300777_ProcEventEntry( sceneId, selfId, bufIndex,rorf )

	if rorf == 0 then --Active
		MarkMutexState( sceneId, selfId, 25 )
	else -- FadeOut
		ClearMutexState( sceneId, selfId, 25 )
	end

end

