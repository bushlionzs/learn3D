---------------------------------- enter day and time --------------------------

x700015_g_EnterDay					=	{0,1,2,3,4,5,6};

---------------------------------- enter day and time end --------------------------
--脚本号
x700015_g_ScriptId = 700015
x700015_g_SceneNpcCount = 1
x700015_g_SceneNpcGuid = 137715



function x700015_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4,Param5 )

	if x700015_CheckDay(sceneId)<=0 then
		return
	end

    if sceneId == 50 or sceneId == 150 or sceneId == 250 or sceneId == 350 then

        -- 做x700015_g_SceneNpcCount次循环以删除创建的NPC
        for i=1,x700015_g_SceneNpcCount do

            local objid = FindMonsterByGUID( sceneId,x700015_g_SceneNpcGuid)
            
			if objid>=0 then
				DeleteMonster( sceneId,objid )
			end

        end

		local strFmt = "探宝任务结束了"
		local msg = strFmt
		--LuaAllScenceM2Wrold (sceneId, msg, 4, 1)
		x700015_MsgToCountry(sceneId, msg, 4, 1)
    end
end


--活动的Tick
function x700015_ProcTiming( sceneId, actId, uTime )

end


function x700015_CheckDay(sceneId)
	local weekDay = GetWeek()
	for i, item in x700015_g_EnterDay do
		if weekDay==item then
			
			
			return 1;
			
		end
	end

	return 0;
end


function x700015_MsgToCountry(sceneId, msg, nParam1, nParam2)
	if sceneId==50 then
		LuaAllScenceM2Country(sceneId, msg, 0, nParam1, nParam2)
	elseif sceneId==150 then
		LuaAllScenceM2Country(sceneId, msg, 1, nParam1, nParam2)
	elseif sceneId==250 then
		LuaAllScenceM2Country(sceneId, msg, 2, nParam1, nParam2)
	elseif sceneId==350 then
		LuaAllScenceM2Country(sceneId, msg, 3, nParam1, nParam2)
	end

end