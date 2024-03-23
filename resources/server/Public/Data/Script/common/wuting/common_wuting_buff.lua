
x300162_g_ScriptId = 300162
x300162_g_FarScriptId = 300160
x300162_g_BuffId = 7646

--间隔发作时调用
function x300162_OnIntervalOverEvent( sceneId, selfId)
	if sceneId == 14 then
		CallScriptFunction(x300162_g_FarScriptId, "OnIntervalOverEvent", sceneId, selfId, x300162_g_BuffId)
	end
end

--生效时调用
function x300162_OnActiveEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300162_g_FarScriptId, "OnActiveEvent", sceneId, selfId)
	end
end

--效果消散时调用
function x300162_OnFadeOutEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300162_g_FarScriptId, "OnFadeOutEvent", sceneId, selfId, x300162_g_BuffId)
	end
end

--**********************************
--事件交互入口
--**********************************
function x300162_ProcEventEntry( sceneId, selfId, bagIndex)
end


