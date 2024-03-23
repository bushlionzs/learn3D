x413306_g_scriptId  = 413306 --召唤白骆驼
x413306_g_Impact1   = -1--效果ID，先无视好了
x413306_g_MissionId = 672
x413306_g_doing =0
x413306_g_bailuotuo =0
x413306_g_luotuo1 =0
x413306_g_luotuo2 =0
x413306_g_tujueqibing =0
--**********************************
--事件交互入口
--**********************************
function x413306_ProcEventEntry( sceneId, selfId, bagIndex )
    local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x413306_g_Impact1 )
  
    if bCplay == 1 then
    
        x413306_g_bailuotuo=CreateMonster(sceneId, 849,161,113,1,1,-1,-1,20,9000)
        x413306_g_luotuo1=CreateMonster(sceneId, 861,157,111,1,1,-1,-1,20,9000)
        x413306_g_luotuo2=CreateMonster(sceneId, 861,163,115,1,1,-1,-1,20,9000)
        x413306_g_tujueqibing=CreateMonster(sceneId, 841,159,119,1,1,-1,-1,20,2000)
        SetPatrolId(sceneId, x413306_g_bailuotuo, 3)
        SetPatrolId(sceneId, x413306_g_luotuo1, 4)
        SetPatrolId(sceneId, x413306_g_luotuo2, 5)
        NpcTalk(sceneId, x413306_g_tujueqibing, "啊！快看，白骆驼！神的使者出现了！", -1)
    end

    return bCplay


-- 不需要这个接口，但要保留空函数
end


function x413306_IsSkillLikeScript( sceneId, selfId)
 
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x413306_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x413306_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413306_OnDeplete( sceneId, selfId )

	return 1
end

function x413306_OnActivateOnce( sceneId, selfId )
end

function x413306_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
