
x300166_g_ScriptId = 300166
x300166_g_FarScriptId = 300160
x300166_g_BuffId = 7647

--间隔发作时调用
function x300166_OnIntervalOverEvent( sceneId, selfId)
	if sceneId == 14 then
		CallScriptFunction(x300166_g_FarScriptId, "OnIntervalOverEvent", sceneId, selfId, x300166_g_BuffId)
	end
end

--生效时调用
function x300166_OnActiveEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300166_g_FarScriptId, "OnActiveEvent", sceneId, selfId)
	end
end

--效果消散时调用
function x300166_OnFadeOutEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300166_g_FarScriptId, "OnFadeOutEvent", sceneId, selfId, x300166_g_BuffId)
	end
end

--**********************************
--事件交互入口
--**********************************
function x300166_ProcEventEntry( sceneId, selfId, bagIndex)
end


