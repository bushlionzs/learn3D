--脚本号
x302500_g_ScriptId = 302500						
x302500_g_DayInfo1 = {
						{m = 12,d = 24},
						{m = 12,d = 25},
					}
----------------------------------------------------------------------
--播放特效
----------------------------------------------------------------------
function x302500_PlayEffect1(sceneId,selfId )

    --场景判断
    if sceneId ~= 0 and sceneId ~= 50 and sceneId ~= 150 and sceneId ~= 250 and sceneId ~= 350 and sceneId ~= 15  then 
	  return
	end

	--日期判断
	local year,month,day = GetYearMonthDay()
	local find1 = 0
	for i,item in x302500_g_DayInfo1 do
		if item.m == month and item.d == day then
			find1 = 1
			break
		end
	end

    --播放特效
	if find1 == 1 then

		CallScriptFunction( 888894, "PlayClientCameraEffect", sceneId, selfId,29,1)
	end

end

----------------------------------------------------------------------
--停止特效
----------------------------------------------------------------------
function x302500_StopEffect1(sceneId)
    --场景判断
	if sceneId ~= 0 and sceneId ~= 50 and sceneId ~= 150 and sceneId ~= 250 and sceneId ~= 350 and sceneId ~= 15  then 
	  return
	end
	local year,month,day = GetYearMonthDay()
	local find1 = 0
	for i,item in x302500_g_DayInfo1 do
		if item.m == month and item.d == day then
			find1 = 1
			break
		end
	end

	if find1 == 0 then
		local humancount = GetScenePlayerCount(sceneId);
		for	i = 0, humancount - 1 do
			local humanId = GetScenePlayerObjId(sceneId, i);
			if IsPlayerStateNormal( sceneId,humanId ) == 1 then
				CallScriptFunction( 888894, "PlayClientCameraEffect", sceneId, humanId,29,0)
			end
		end
	end	
end

----------------------------------------------------------------------
--封装起来,供外部调用
----------------------------------------------------------------------
function x302500_PlayEffect(sceneId,selfId )
	x302500_PlayEffect1(sceneId,selfId )
end

----------------------------------------------------------------------
--封装起来,配对
----------------------------------------------------------------------
function x302500_StopEffect(sceneId)
	x302500_StopEffect1(sceneId)
end


----------------------------------------------------------------------
--根据场景播放特效
----------------------------------------------------------------------
function x302500_PlayEffectBySceneId(sceneId )
	
	--场景判断
    if sceneId ~= 0 and sceneId ~= 50 and sceneId ~= 150 and sceneId ~= 250 and sceneId ~= 350 and sceneId ~= 15  then 
	  return 0
	end

	--日期判断
	local year,month,day = GetYearMonthDay()
	local item = x302500_g_DayInfo1[1]
	if item.m ~= month or item.d ~= day then
		return 0
	end
	
	--10分钟以内
	local md = GetMinOfDay()
	if md < 0 or md >= 10*60*1000 then
		return 0
	end
	
	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			CallScriptFunction( 888894, "PlayClientCameraEffect", sceneId, humanId,29,1)
		end
	end
	
	return 1
end

----------------------------------------------------------------------
--根据场景停止特效
----------------------------------------------------------------------
function x302500_StopEffectBySceneId(sceneId)
	x302500_StopEffect1(sceneId)
end

----------------------------------------------------------------------
--定时器事件
----------------------------------------------------------------------
function x302500_OnTimerDoingStart( SceneId, actId, Param1, Param2, Param3, Param4, Param5 )

	--先检查是否是播放特效
	if x302500_PlayEffectBySceneId( SceneId) == 1 then
		return
	end

	--结束特效
	x302500_StopEffectBySceneId(SceneId)
	
end
