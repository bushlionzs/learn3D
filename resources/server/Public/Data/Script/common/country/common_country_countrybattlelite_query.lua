x310152_g_scriptId                      = 310152


----------------------------------------------------------------------------------------------
--枚举
----------------------------------------------------------------------------------------------
function x310152_ProcEnumEvent( sceneId, selfId, targetId, MissionId )


    --合服开关
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --升级数据库开关
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end
    
    --测试服开关
    --if GetTestServerToggle() == 0 then
    --    return
    --end

    --战场自己的开关
    if GetBattleSceneToggle( BATTLESCENE_TYPE_COUNTRYBATTLELITE ) == 0 then
        return
    end
    
    if CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_CountryCamp", sceneId, selfId) < 0 then
        return
    end
    
    AddQuestNumText(sceneId,x310152_g_scriptId,"【屠城战】查询",3);
        
end

----------------------------------------------------------------------------------------------
--取得国家名字
----------------------------------------------------------------------------------------------
function x310152_GetCountryName( countryId )
    
    if countryId == 0 then
        return "楼兰王国"
    elseif countryId == 1 then
        return "天山王国"
    elseif countryId == 2 then
        return "昆仑王国"
    elseif countryId == 3 then
        return "敦煌王国"
    end
    
end

----------------------------------------------------------------------------------------------
--脚本默认事件
----------------------------------------------------------------------------------------------
function x310152_ProcEventEntry( sceneId ,selfId, npcId,idScript,idExt )

    --合服开关
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --升级数据库开关
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end
    
    --测试服开关
    --if GetTestServerToggle() == 0 then
    --    return
    --end

    --战场自己的开关
    if GetBattleSceneToggle( BATTLESCENE_TYPE_COUNTRYBATTLELITE ) == 0 then
        return
    end
    
    local camp = CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_CountryCamp", sceneId, selfId)
    if camp < 0 then
        return
    end
    
    local match = CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT,"GetCountryBattleLite_MatchCountry",sceneId ,selfId)
    if match < 0 then
        return
    end
    
    
    local strCountryName = x310152_GetCountryName( match )
    if strCountryName == nil then
        return
    end
    
    
    
    BeginQuestEvent(sceneId) 
    
    if camp == 0 then 
        local strMsg = format("#Y【屠城战】查询#r\t#G今天您处于防守方，您将要驱逐的侵略者是：#R%s",strCountryName )
        AddQuestText(sceneId, strMsg )
    else
        local strMsg = format("#Y【屠城战】查询#r\t#G今天您处于进攻方，您的敌人是：#R%s",strCountryName )
        AddQuestText(sceneId, strMsg )
    end
    
    EndQuestEvent(sceneId)
    DispatchQuestEventList(sceneId,selfId,npcId)
    
end


function x310152_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--接受
----------------------------------------------------------------------------------------------
function x310152_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--放弃
----------------------------------------------------------------------------------------------
function x310152_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--继续
----------------------------------------------------------------------------------------------
function x310152_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--检测是否可以提交
----------------------------------------------------------------------------------------------
function x310152_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--提交
----------------------------------------------------------------------------------------------
function x310152_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--杀死怪物或玩家
----------------------------------------------------------------------------------------------
function x310152_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--进入区域事件
----------------------------------------------------------------------------------------------
function x310152_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--道具改变
----------------------------------------------------------------------------------------------
function x310152_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end