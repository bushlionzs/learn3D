
x300189_g_ScriptId = 300189
x300189_g_FarScriptId = 300160
x300189_g_BuffId = 7669

--间隔发作时调用
function x300189_OnIntervalOverEvent( sceneId, selfId)
	if sceneId == 14 then
		CallScriptFunction(x300189_g_FarScriptId, "OnIntervalOverEvent", sceneId, selfId, x300189_g_BuffId)
	end
end

--生效时调用
function x300189_OnActiveEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300189_g_FarScriptId, "OnActiveEvent", sceneId, selfId)
	end
end

--效果消散时调用
function x300189_OnFadeOutEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300189_g_FarScriptId, "OnFadeOutEvent", sceneId, selfId, x300189_g_BuffId)
	end
end

--**********************************
--事件交互入口
--**********************************
function x300189_ProcEventEntry( sceneId, selfId, bagIndex)
end


