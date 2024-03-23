
x300180_g_ScriptId = 300180
x300180_g_FarScriptId = 300160
x300180_g_BuffId = 8401
x300180_g_PosTable              = {
                                    { x =94 , z =67}, 
                                    { x =157 , z =73}, 
                                    { x = 50, z = 95}, 
                                    { x = 127, z =58 }, 
									{ x = 206, z =77 },
}                                

--间隔发作时调用
function x300180_OnIntervalOverEvent( sceneId, selfId)
end

--生效时调用
function x300180_OnActiveEvent( sceneId, selfId )
end

--效果消散时调用
function x300180_OnFadeOutEvent( sceneId, selfId )
    if sceneId == 14 and GetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID) == 1 then
        SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, 0)

        x300160_ChangeBody( sceneId, selfId, 0, 0)
        SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_DANCERY, 0)
        local index = random( 1, getn( x300180_g_PosTable) )
        NewWorld( sceneId, selfId, 0, x300180_g_PosTable[ index].x, x300180_g_PosTable[ index].z, 300160)
    end

end

--**********************************
--事件交互入口
--**********************************
function x300180_ProcEventEntry( sceneId, selfId, bagIndex)
end


