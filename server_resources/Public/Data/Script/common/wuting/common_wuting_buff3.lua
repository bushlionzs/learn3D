
x300167_g_ScriptId = 300167
x300167_g_FarScriptId = 300160
x300167_g_BuffId = 7648

--间隔发作时调用
function x300167_OnIntervalOverEvent( sceneId, selfId)
	if sceneId == 14 then
		CallScriptFunction(x300167_g_FarScriptId, "OnIntervalOverEvent", sceneId, selfId, x300167_g_BuffId)
	end
end

--生效时调用
function x300167_OnActiveEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300167_g_FarScriptId, "OnActiveEvent", sceneId, selfId)
	end
end

--效果消散时调用
function x300167_OnFadeOutEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300167_g_FarScriptId, "OnFadeOutEvent", sceneId, selfId, x300167_g_BuffId)
	end
end

--**********************************
--事件交互入口
--**********************************
function x300167_ProcEventEntry( sceneId, selfId, bagIndex)
end


