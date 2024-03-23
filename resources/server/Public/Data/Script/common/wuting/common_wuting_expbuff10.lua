
x300181_g_ScriptId = 300181
x300181_g_FarScriptId = 300160
x300181_g_BuffId = 7667

--间隔发作时调用
function x300181_OnIntervalOverEvent( sceneId, selfId)
	if sceneId == 14 then
		CallScriptFunction(x300181_g_FarScriptId, "OnIntervalOverEvent", sceneId, selfId, x300181_g_BuffId)
	end
end

--生效时调用
function x300181_OnActiveEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300181_g_FarScriptId, "OnActiveEvent", sceneId, selfId)
	end
end

--效果消散时调用
function x300181_OnFadeOutEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300181_g_FarScriptId, "OnFadeOutEvent", sceneId, selfId, x300181_g_BuffId)
	end
end

--**********************************
--事件交互入口
--**********************************
function x300181_ProcEventEntry( sceneId, selfId, bagIndex)
end


