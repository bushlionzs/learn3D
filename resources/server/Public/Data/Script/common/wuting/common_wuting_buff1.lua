
x300165_g_ScriptId = 300165
x300165_g_FarScriptId = 300160
x300165_g_BuffId = 7650

--间隔发作时调用
function x300165_OnIntervalOverEvent( sceneId, selfId)
	if sceneId == 14 then
		CallScriptFunction(x300165_g_FarScriptId, "OnIntervalOverEvent", sceneId, selfId, x300165_g_BuffId)
	end
end

--生效时调用
function x300165_OnActiveEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300165_g_FarScriptId, "OnActiveEvent", sceneId, selfId)
	end
end

--效果消散时调用
function x300165_OnFadeOutEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300165_g_FarScriptId, "OnFadeOutEvent", sceneId, selfId, x300165_g_BuffId)
	end
end

--**********************************
--事件交互入口
--**********************************
function x300165_ProcEventEntry( sceneId, selfId, bagIndex)
end


