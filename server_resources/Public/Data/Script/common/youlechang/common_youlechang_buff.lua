
x310329_g_ScriptId = 310329
x310329_g_BuffId = 8400
x310329_g_Pos              = {x = 127, z = 79}

--间隔发作时调用
function x310329_OnIntervalOverEvent( sceneId, selfId)
end

--生效时调用
function x310329_OnActiveEvent( sceneId, selfId )
end

--效果消散时调用
function x310329_OnFadeOutEvent( sceneId, selfId )
    if sceneId == 39 or sceneId == 40 then
        NewWorld( sceneId, selfId, 36, x310329_g_Pos.x, x310329_g_Pos.z, 310320)
    end

end

--**********************************
--事件交互入口
--**********************************
function x310329_ProcEventEntry( sceneId, selfId, bagIndex)
end


