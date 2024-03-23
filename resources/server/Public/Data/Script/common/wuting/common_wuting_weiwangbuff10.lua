
x300185_g_ScriptId = 300185
x300185_g_FarScriptId = 300160
x300185_g_BuffId = 7665

--间隔发作时调用
function x300185_OnIntervalOverEvent( sceneId, selfId)
	if sceneId == 14 then
		CallScriptFunction(x300185_g_FarScriptId, "OnIntervalOverEvent", sceneId, selfId, x300185_g_BuffId)
	end
end

--生效时调用
function x300185_OnActiveEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300185_g_FarScriptId, "OnActiveEvent", sceneId, selfId)
	end
end

--效果消散时调用
function x300185_OnFadeOutEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300185_g_FarScriptId, "OnFadeOutEvent", sceneId, selfId, x300185_g_BuffId)
	end
end

--**********************************
--事件交互入口
--**********************************
function x300185_ProcEventEntry( sceneId, selfId, bagIndex)
end


