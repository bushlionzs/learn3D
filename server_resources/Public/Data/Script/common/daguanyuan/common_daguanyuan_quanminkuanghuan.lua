-- 脚本号
x310363_g_ScriptId              = 310363
-- npc list
x310363_g_NPCList               = {}
-- pos list
x310363_g_PosList               = {
                                    { x = 104, z =  97, index = 1  }, 
                                    { x = 104, z = 104, index = 2  }, 
                                    { x = 120, z = 103, index = 3  }, 
                                    { x = 120, z =  97, index = 4  }, 
                                    { x = 134, z =  97, index = 5  }, 
                                    { x = 133, z = 105, index = 6  }, 
                                    { x = 151, z = 106, index = 7  }, 
                                    { x = 151, z = 98 , index = 8  }, 
                                    { x = 132, z = 101, index = 9  }, 
                                    { x = 125, z = 100, index = 10 }, 
}
-- 已经创建的
x310363_g_Created               = {}
-- 可用点
x310363_g_Available             = {}
-- open flag
x310363_g_IsEnableId            = 1044

function x310363_OnMapInit( sceneId)
    if sceneId ~= 40 then
        return
    end

    --SetSystemTimerTick( sceneId, x310363_g_ScriptId, "DaguanyunTimer", x310363_g_TimerID, 10000)
end

function x310363_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4, Param5)
	SetSystemTimerTick( sceneId, x310363_g_ScriptId, "DaguanyunTimer", actId, 10000)

    local strLog = format( "Timer %d active script %d. ", actId, x310363_g_ScriptId)
    WriteLog( 1, strLog)
end

function x310363_DaguanyunTimer( sceneId, actId, uTime)
    if GetGameOpenById( x310363_g_IsEnableId) <= 0 then
        return
    end

    local day, week = GetWeek()
    if day == 6 or day == 0 then
        if getn( x310363_g_NPCList) == 0 then
            -- 从x310363_g_PosList随机选择5个不重复的索引
            x310363_g_Available = x310363_g_PosList
            local empty = {}
            local index = 1
            for i = 1, 5 do
                index = x310363_g_Available[ random( 1, getn( x310363_g_Available) ) ].index
                x310363_g_NPCList[ getn( x310363_g_NPCList) + 1] = { p = index, objId = -1, guid = -1, count = 0 }
                for j, item in x310363_g_Available do
                    if index ~= item.index then
                        empty[ getn( empty) + 1] = item
                    end
                end
                x310363_g_Created[ getn( x310363_g_Created) + 1] = index
                x310363_g_Available = empty
                empty = {}
            end
            -- 创建NPC
            for i, item in x310363_g_NPCList do
                local pos = x310363_g_PosList[ item.p]
                x310363_g_NPCList[ i].objId, x310363_g_NPCList[ i].guid = CreateMonster( sceneId, 4804, pos.x, pos.z, 3, -1, -1, 145142, 5)
            end
            local strLog = format( "Script %d create 5 NPC. ", x310363_g_ScriptId)
            WriteLog( 1, strLog)
        else
            for i, item in x310363_g_NPCList do
                if item.objId == -1 then
                    if item.count == 5 then
                        -- 从可用数组中随机选一个NPC创建
                        local index = x310363_g_Available[ random( 1, getn( x310363_g_Available) ) ].index
                        item.objId, item.guid = CreateMonster( sceneId, 4804, x310363_g_PosList[ index].x, x310363_g_PosList[ index].z, 3, -1, -1, 145142, 5)
                        item.p = index
                        item.count = 0
                        x310363_g_Created[ getn( x310363_g_Created) + 1] = index
                        local strLog = format( "Script %d create a NPC. ", x310363_g_ScriptId)
                        WriteLog( 1, strLog)
                        -- 把选出来的从可用数组众剔除
                        local tblTemp = {}
                        for j, iter in x310363_g_Available do
                            if index ~= iter.index then
                                tblTemp[ getn( tblTemp) + 1] = iter
                            end
                        end
                        x310363_g_Available = tblTemp
                    else
                        item.count = item.count + 1
                    end
                end
            end
        end

        if GetMinOfDay() < 1370 then
            SetSystemTimerTick( sceneId, x310363_g_ScriptId, "DaguanyunTimer", actId, 10000)
        end
    end
end

function x310363_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
    if GetGameOpenById( x310363_g_IsEnableId) <= 0 then
        return
    end

    -- print( "*-*-*-*-*-*" )
    local day, week = GetWeek()
    local minute = GetMinOfDay()
      if day == 0 or day == 6 then
          if minute >= 540 and minute <= 1439 then
              BeginQuestEvent( sceneId)
                  AddQuestText( sceneId, "#Y福神赐福" )
                  AddQuestText( sceneId, "\t相见既有缘，有缘再相见。" )
                  AddQuestNumText( sceneId, x310363_g_ScriptId, "我找到你了", 3, 1)
              EndQuestEvent()
              DispatchQuestEventList( sceneId, selfId, NPCId)
          end  
      end
end

function x310363_ProcEventEntry( sceneId, selfId, NPCId, idScript, idExt)
    if GetGameOpenById( x310363_g_IsEnableId) <= 0 then
        return
    end

    local day, week = GetWeek()
    local minute = GetMinOfDay()

    if day == 0 or day == 6 then
        if minute >= 540 and minute <= 1439 then
            for i, item in x310363_g_NPCList do
                if item.objId == NPCId then
                    DeleteMonster( sceneId, NPCId)
                    item.objId = -1
                    item.guid = -1
                    -- 把删除的NPC索引从x310363_g_Created移动到x310363_g_Available
                    local tblTemp = {}
                    for j, iter in x310363_g_Created do
                        if iter ~= item.p then
                            tblTemp[ getn( tblTemp) + 1] = iter
                        else
                            x310363_g_Available[ getn( x310363_g_Available) + 1] = x310363_g_PosList[ iter]
                        end
                    end
                    x310363_g_Created = tblTemp
                    GamePlayScriptLog(sceneId, selfId, 1661)  
                    local xp = GetLevel( sceneId, selfId) * 900

                    AddExp( sceneId, selfId, xp)
                    Msg2Player(sceneId, selfId, format("有缘与福神相见，获得%d点经验奖励",xp), 0, 2)
                    Msg2Player(sceneId, selfId, format("有缘与福神相见，获得%d点经验奖励",xp), 0, 3)

                    local nHumanCount = GetScenePlayerCount( sceneId)
                    for i = 0, nHumanCount - 1 do
                        local objId = GetScenePlayerObjId( sceneId, i)
                        if objId ~= selfId then
                            local xp1 = GetLevel( sceneId, objId) * 180
                            AddExp( sceneId, objId, xp1)
                            Msg2Player(sceneId, objId, format("福神赐福，获得%d点经验奖励",xp1), 0, 2)
                            Msg2Player(sceneId, objId, format("福神赐福，获得%d点经验奖励",xp1), 0, 3)
                        end	
                    end
                end
            end
        end
    end
end




























