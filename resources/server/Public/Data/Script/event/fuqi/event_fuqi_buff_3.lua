
x300382_g_ScriptId = 300382

--间隔发作时调用
function x300382_OnIntervalOverEvent( sceneId, selfId )
	if sceneId == 0 then
		local level = GetLevel(sceneId, selfId)
		local exp = level * level
		AddExp ( sceneId , selfId , exp )
	end
end

--生效时调用
function x300382_OnActiveEvent( sceneId, selfId )
end

--效果消散时调用
function x300382_OnFadeOutEvent( sceneId, selfId )
end

function x300382_ProcEventEntry()
end