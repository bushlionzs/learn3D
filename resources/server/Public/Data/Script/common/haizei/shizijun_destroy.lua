--广播海贼信息

--脚本号
x300562_g_ScriptId = 300562
x300562_g_KillScriptId = 300561
x300562_money = 500000
x300562_g_SceneMonsterCount = 30
x300562_g_MsgFightFail = ""
x300562_g_MsgFightBossFail = ""

function x300562_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4,Param5 )
	
	local nCount = getn( HZ_MONSTER_OBJ )
    
    if nCount == 0 then
  	    return
    end
    
    if sceneId == 19 then
        
  	    if HZ_KILL_MONSTERBOSS < 1 then
			
			local IsHavecommonMonster = 0
			
			for i=1,nCount do
    			if HZ_MONSTER_OBJ[i] >= 0 then
    				DeleteMonster(sceneId, HZ_MONSTER_OBJ[i])
					HZ_MONSTER_OBJ[i] = -1
					IsHavecommonMonster = 1
    			end
            end
            
    	    if HZ_MONSTER_BOSSOBJ >= 0 then
    	    		DeleteMonster(sceneId, HZ_MONSTER_BOSSOBJ)
    				HZ_MONSTER_BOSSOBJ = -1
    	    end
    	    
    	    if IsHavecommonMonster > 0 then
				--LuaAllScenceM2Country(sceneId, x300562_g_MsgFightFail, 0, 4, 1)
				--LuaAllScenceM2Country(sceneId, x300562_g_MsgFightFail, 0, 1, 1)
    		else
				--LuaAllScenceM2Country(sceneId, x300562_g_MsgFightBossFail, 0, 4, 1)
				--LuaAllScenceM2Country(sceneId, x300562_g_MsgFightBossFail, 0, 1, 1)
    	    end
    	    
		end
		
    end
end


--活动的Tick
function x300562_ProcTiming( sceneId, actId, uTime )
end