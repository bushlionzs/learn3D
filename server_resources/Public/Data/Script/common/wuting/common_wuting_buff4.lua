
x300168_g_ScriptId = 300168
x300168_g_FarScriptId = 300160
x300168_g_BuffId = 7649

--间隔发作时调用
function x300168_OnIntervalOverEvent( sceneId, selfId)
	if sceneId == 14 then
		CallScriptFunction(x300168_g_FarScriptId, "OnIntervalOverEvent", sceneId, selfId, x300168_g_BuffId)
	end
end

--生效时调用
function x300168_OnActiveEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300168_g_FarScriptId, "OnActiveEvent", sceneId, selfId)
	end
end

--效果消散时调用
function x300168_OnFadeOutEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300168_g_FarScriptId, "OnFadeOutEvent", sceneId, selfId, x300168_g_BuffId)
	end
end

--**********************************
--事件交互入口
--**********************************
function x300168_ProcEventEntry( sceneId, selfId, bagIndex)
end


