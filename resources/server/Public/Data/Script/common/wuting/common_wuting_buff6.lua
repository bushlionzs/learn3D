
x300176_g_ScriptId = 300176
x300176_g_FarScriptId = 300160
x300176_g_BuffId = 7644

--间隔发作时调用
function x300176_OnIntervalOverEvent( sceneId, selfId)
	if sceneId == 14 then
		CallScriptFunction(x300176_g_FarScriptId, "OnIntervalOverEvent", sceneId, selfId, x300176_g_BuffId)
	end
end

--生效时调用
function x300176_OnActiveEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300176_g_FarScriptId, "OnActiveEvent", sceneId, selfId)
	end
end

--效果消散时调用
function x300176_OnFadeOutEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300176_g_FarScriptId, "OnFadeOutEvent", sceneId, selfId, x300176_g_BuffId)
	end
end

--**********************************
--事件交互入口
--**********************************
function x300176_ProcEventEntry( sceneId, selfId, bagIndex)
end


