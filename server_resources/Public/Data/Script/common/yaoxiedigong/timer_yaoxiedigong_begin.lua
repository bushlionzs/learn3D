x310030_g_ScriptId = 310030
x310030_str_end = "圣山地宫将在%d分钟后关闭，请各位勇士加紧杀怪"

x310030_str_pre = "圣山地宫的怪物将在%d分钟后出现，请大家做好准备"

x310030_str_shuaguai1 = "圣山地宫的怪物出现了，请大家努力消灭这些怪物吧"
x310030_str_shuaguai2 = "各位勇者请小心，新的怪物出现了"
x310030_str_shuaguai3 = "强者出现了，请大家全力以赴"

x310030_RespwanTime1 = 1000
x310030_RespwanTime2 = 10000
x310030_RespwanTime3 = 100000000

x310030_g_PreBroadCastNum = 2
x310030_g_CreateMonsterInterval = 60*1000*6
x310030_g_AfterBroadCastNum = 6


function x310030_ShowMessage1(sceneId, msg)
	
	LuaThisScenceM2Wrold( sceneId, msg, CHAT_PLANE_SCROLL, 1 )
	LuaThisScenceM2Wrold( sceneId, msg, CHAT_LEFTDOWN, 1 )
	LuaThisScenceM2Wrold( sceneId, msg, CHAT_PLUMB_SCROLL, 1 )
end


function x310030_AddObj(sceneId, objId)
	if sceneId == YX_LOULAN_SCENE_ID1 then
		YX_LOULAN_MONSTER_OBJ_NUM1 = YX_LOULAN_MONSTER_OBJ_NUM1 + 1
		YX_LOULAN_MONSTER_OBJ_ID1[YX_LOULAN_MONSTER_OBJ_NUM1] = objId
	elseif sceneId == YX_LOULAN_SCENE_ID2 then
		YX_LOULAN_MONSTER_OBJ_NUM2 = YX_LOULAN_MONSTER_OBJ_NUM2 + 1
		YX_LOULAN_MONSTER_OBJ_ID2[YX_LOULAN_MONSTER_OBJ_NUM2] = objId
	elseif sceneId == YX_LOULAN_SCENE_ID3 then
		YX_LOULAN_MONSTER_OBJ_NUM3 = YX_LOULAN_MONSTER_OBJ_NUM3 + 1
		YX_LOULAN_MONSTER_OBJ_ID3[YX_LOULAN_MONSTER_OBJ_NUM3] = objId
	elseif sceneId == YX_LOULAN_SCENE_ID4 then
		YX_LOULAN_MONSTER_OBJ_NUM4 = YX_LOULAN_MONSTER_OBJ_NUM4 + 1
		YX_LOULAN_MONSTER_OBJ_ID4[YX_LOULAN_MONSTER_OBJ_NUM4] = objId
	elseif sceneId == YX_LOULAN_SCENE_ID5 then
		YX_LOULAN_MONSTER_OBJ_NUM5 = YX_LOULAN_MONSTER_OBJ_NUM5 + 1
		YX_LOULAN_MONSTER_OBJ_ID5[YX_LOULAN_MONSTER_OBJ_NUM5] = objId
	elseif sceneId == YX_LOULAN_SCENE_ID6 then
		YX_LOULAN_MONSTER_OBJ_NUM6 = YX_LOULAN_MONSTER_OBJ_NUM6 + 1
		YX_LOULAN_MONSTER_OBJ_ID6[YX_LOULAN_MONSTER_OBJ_NUM6] = objId
	elseif sceneId == YX_LOULAN_SCENE_ID7 then
		YX_LOULAN_MONSTER_OBJ_NUM7 = YX_LOULAN_MONSTER_OBJ_NUM7 + 1
		YX_LOULAN_MONSTER_OBJ_ID7[YX_LOULAN_MONSTER_OBJ_NUM7] = objId
	elseif sceneId == YX_LOULAN_SCENE_ID8 then
		YX_LOULAN_MONSTER_OBJ_NUM8 = YX_LOULAN_MONSTER_OBJ_NUM8 + 1
		YX_LOULAN_MONSTER_OBJ_ID8[YX_LOULAN_MONSTER_OBJ_NUM8] = objId
	elseif sceneId == YX_LOULAN_SCENE_ID9 then
		YX_LOULAN_MONSTER_OBJ_NUM9 = YX_LOULAN_MONSTER_OBJ_NUM9 + 1
		YX_LOULAN_MONSTER_OBJ_ID9[YX_LOULAN_MONSTER_OBJ_NUM9] = objId				
			
	elseif sceneId == YX_LAIYIN_SCENE_ID1 then
		YX_LAIYIN_MONSTER_OBJ_NUM1 = YX_LAIYIN_MONSTER_OBJ_NUM1 + 1
		YX_LAIYIN_MONSTER_OBJ_ID1[YX_LAIYIN_MONSTER_OBJ_NUM1] = objId
	elseif sceneId == YX_LAIYIN_SCENE_ID2 then
		YX_LAIYIN_MONSTER_OBJ_NUM2 = YX_LAIYIN_MONSTER_OBJ_NUM2 + 1
		YX_LAIYIN_MONSTER_OBJ_ID2[YX_LAIYIN_MONSTER_OBJ_NUM2] = objId
	elseif sceneId == YX_LAIYIN_SCENE_ID3 then
		YX_LAIYIN_MONSTER_OBJ_NUM3 = YX_LAIYIN_MONSTER_OBJ_NUM3 + 1
		YX_LAIYIN_MONSTER_OBJ_ID3[YX_LAIYIN_MONSTER_OBJ_NUM3] = objId
	elseif sceneId == YX_LAIYIN_SCENE_ID4 then
		YX_LAIYIN_MONSTER_OBJ_NUM4 = YX_LAIYIN_MONSTER_OBJ_NUM4 + 1
		YX_LAIYIN_MONSTER_OBJ_ID4[YX_LAIYIN_MONSTER_OBJ_NUM4] = objId
	elseif sceneId == YX_LAIYIN_SCENE_ID5 then
		YX_LAIYIN_MONSTER_OBJ_NUM5 = YX_LAIYIN_MONSTER_OBJ_NUM5 + 1
		YX_LAIYIN_MONSTER_OBJ_ID5[YX_LAIYIN_MONSTER_OBJ_NUM5] = objId
	elseif sceneId == YX_LAIYIN_SCENE_ID6 then
		YX_LAIYIN_MONSTER_OBJ_NUM6 = YX_LAIYIN_MONSTER_OBJ_NUM6 + 1
		YX_LAIYIN_MONSTER_OBJ_ID6[YX_LAIYIN_MONSTER_OBJ_NUM6] = objId
	elseif sceneId == YX_LAIYIN_SCENE_ID7 then
		YX_LAIYIN_MONSTER_OBJ_NUM7 = YX_LAIYIN_MONSTER_OBJ_NUM7 + 1
		YX_LAIYIN_MONSTER_OBJ_ID7[YX_LAIYIN_MONSTER_OBJ_NUM7] = objId
	elseif sceneId == YX_LAIYIN_SCENE_ID8 then
		YX_LAIYIN_MONSTER_OBJ_NUM8 = YX_LAIYIN_MONSTER_OBJ_NUM8 + 1
		YX_LAIYIN_MONSTER_OBJ_ID8[YX_LAIYIN_MONSTER_OBJ_NUM8] = objId
	elseif sceneId == YX_LAIYIN_SCENE_ID9 then
		YX_LAIYIN_MONSTER_OBJ_NUM9 = YX_LAIYIN_MONSTER_OBJ_NUM9 + 1
		YX_LAIYIN_MONSTER_OBJ_ID9[YX_LAIYIN_MONSTER_OBJ_NUM9] = objId
			
	elseif sceneId == YX_KUNLUN_SCENE_ID1 then
		YX_KUNLUN_MONSTER_OBJ_NUM1 = YX_KUNLUN_MONSTER_OBJ_NUM1 + 1
		YX_KUNLUN_MONSTER_OBJ_ID1[YX_KUNLUN_MONSTER_OBJ_NUM1] = objId
	elseif sceneId == YX_KUNLUN_SCENE_ID2 then
		YX_KUNLUN_MONSTER_OBJ_NUM2 = YX_KUNLUN_MONSTER_OBJ_NUM2 + 1
		YX_KUNLUN_MONSTER_OBJ_ID2[YX_KUNLUN_MONSTER_OBJ_NUM2] = objId
	elseif sceneId == YX_KUNLUN_SCENE_ID3 then
		YX_KUNLUN_MONSTER_OBJ_NUM3 = YX_KUNLUN_MONSTER_OBJ_NUM3 + 1
		YX_KUNLUN_MONSTER_OBJ_ID3[YX_KUNLUN_MONSTER_OBJ_NUM3] = objId
	elseif sceneId == YX_KUNLUN_SCENE_ID4 then
		YX_KUNLUN_MONSTER_OBJ_NUM4 = YX_KUNLUN_MONSTER_OBJ_NUM4 + 1
		YX_KUNLUN_MONSTER_OBJ_ID4[YX_KUNLUN_MONSTER_OBJ_NUM4] = objId
	elseif sceneId == YX_KUNLUN_SCENE_ID5 then
		YX_KUNLUN_MONSTER_OBJ_NUM5 = YX_KUNLUN_MONSTER_OBJ_NUM5 + 1
		YX_KUNLUN_MONSTER_OBJ_ID5[YX_KUNLUN_MONSTER_OBJ_NUM5] = objId
	elseif sceneId == YX_KUNLUN_SCENE_ID6 then
		YX_KUNLUN_MONSTER_OBJ_NUM6 = YX_KUNLUN_MONSTER_OBJ_NUM6 + 1
		YX_KUNLUN_MONSTER_OBJ_ID6[YX_KUNLUN_MONSTER_OBJ_NUM6] = objId
	elseif sceneId == YX_KUNLUN_SCENE_ID7 then
		YX_KUNLUN_MONSTER_OBJ_NUM7 = YX_KUNLUN_MONSTER_OBJ_NUM7 + 1
		YX_KUNLUN_MONSTER_OBJ_ID7[YX_KUNLUN_MONSTER_OBJ_NUM7] = objId
	elseif sceneId == YX_KUNLUN_SCENE_ID8 then
		YX_KUNLUN_MONSTER_OBJ_NUM8 = YX_KUNLUN_MONSTER_OBJ_NUM8 + 1
		YX_KUNLUN_MONSTER_OBJ_ID8[YX_KUNLUN_MONSTER_OBJ_NUM8] = objId	
	elseif sceneId == YX_KUNLUN_SCENE_ID9 then
		YX_KUNLUN_MONSTER_OBJ_NUM9 = YX_KUNLUN_MONSTER_OBJ_NUM9 + 1
		YX_KUNLUN_MONSTER_OBJ_ID9[YX_KUNLUN_MONSTER_OBJ_NUM9] = objId			

	elseif sceneId == YX_DUNHUANG_SCENE_ID1 then
		YX_DUNHUANG_MONSTER_OBJ_NUM1 = YX_DUNHUANG_MONSTER_OBJ_NUM1 + 1
		YX_DUNHUANG_MONSTER_OBJ_ID1[YX_DUNHUANG_MONSTER_OBJ_NUM1] = objId
	elseif sceneId == YX_DUNHUANG_SCENE_ID2 then
		YX_DUNHUANG_MONSTER_OBJ_NUM2 = YX_DUNHUANG_MONSTER_OBJ_NUM2 + 1
		YX_DUNHUANG_MONSTER_OBJ_ID2[YX_DUNHUANG_MONSTER_OBJ_NUM2] = objId
	elseif sceneId == YX_DUNHUANG_SCENE_ID3 then
		YX_DUNHUANG_MONSTER_OBJ_NUM3 = YX_DUNHUANG_MONSTER_OBJ_NUM3 + 1
		YX_DUNHUANG_MONSTER_OBJ_ID3[YX_DUNHUANG_MONSTER_OBJ_NUM3] = objId
	elseif sceneId == YX_DUNHUANG_SCENE_ID4 then
		YX_DUNHUANG_MONSTER_OBJ_NUM4 = YX_DUNHUANG_MONSTER_OBJ_NUM4 + 1
		YX_DUNHUANG_MONSTER_OBJ_ID4[YX_DUNHUANG_MONSTER_OBJ_NUM4] = objId
	elseif sceneId == YX_DUNHUANG_SCENE_ID5 then
		YX_DUNHUANG_MONSTER_OBJ_NUM5 = YX_DUNHUANG_MONSTER_OBJ_NUM5 + 1
		YX_DUNHUANG_MONSTER_OBJ_ID5[YX_DUNHUANG_MONSTER_OBJ_NUM5] = objId
	elseif sceneId == YX_DUNHUANG_SCENE_ID6 then
		YX_DUNHUANG_MONSTER_OBJ_NUM6 = YX_DUNHUANG_MONSTER_OBJ_NUM6 + 1
		YX_DUNHUANG_MONSTER_OBJ_ID6[YX_DUNHUANG_MONSTER_OBJ_NUM6] = objId
	elseif sceneId == YX_DUNHUANG_SCENE_ID7 then
		YX_DUNHUANG_MONSTER_OBJ_NUM7 = YX_DUNHUANG_MONSTER_OBJ_NUM7 + 1
		YX_DUNHUANG_MONSTER_OBJ_ID7[YX_DUNHUANG_MONSTER_OBJ_NUM7] = objId
	elseif sceneId == YX_DUNHUANG_SCENE_ID8 then
		YX_DUNHUANG_MONSTER_OBJ_NUM8 = YX_DUNHUANG_MONSTER_OBJ_NUM8 + 1
		YX_DUNHUANG_MONSTER_OBJ_ID8[YX_DUNHUANG_MONSTER_OBJ_NUM8] = objId	
	elseif sceneId == YX_DUNHUANG_SCENE_ID9 then
		YX_DUNHUANG_MONSTER_OBJ_NUM9 = YX_DUNHUANG_MONSTER_OBJ_NUM9 + 1
		YX_DUNHUANG_MONSTER_OBJ_ID9[YX_DUNHUANG_MONSTER_OBJ_NUM9] = objId			
	end
end

function x310030_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4, Param5 )
	

	if sceneId == YX_LOULAN_SCENE_ID1 then
	
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LOULAN_BROADCAST_NUM1 )
		x310030_ShowMessage1(sceneId,message)
		YX_LOULAN_BROADCAST_NUM1 = YX_LOULAN_BROADCAST_NUM1 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
		
	elseif sceneId == YX_LOULAN_SCENE_ID2 then
	
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LOULAN_BROADCAST_NUM2 )
		x310030_ShowMessage1(sceneId,message)
		YX_LOULAN_BROADCAST_NUM2 = YX_LOULAN_BROADCAST_NUM2 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
		
	elseif sceneId == YX_LOULAN_SCENE_ID3 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LOULAN_BROADCAST_NUM3 )
		x310030_ShowMessage1(sceneId,message)
		YX_LOULAN_BROADCAST_NUM3 = YX_LOULAN_BROADCAST_NUM3 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始

	elseif sceneId == YX_LOULAN_SCENE_ID4 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LOULAN_BROADCAST_NUM4 )
		x310030_ShowMessage1(sceneId,message)
		YX_LOULAN_BROADCAST_NUM4 = YX_LOULAN_BROADCAST_NUM4 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_LOULAN_SCENE_ID5 then
	
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LOULAN_BROADCAST_NUM5 )
		x310030_ShowMessage1(sceneId,message)
		YX_LOULAN_BROADCAST_NUM5 = YX_LOULAN_BROADCAST_NUM5 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始

	elseif sceneId == YX_LOULAN_SCENE_ID6 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LOULAN_BROADCAST_NUM6 )
		x310030_ShowMessage1(sceneId,message)
		YX_LOULAN_BROADCAST_NUM6 = YX_LOULAN_BROADCAST_NUM6 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
		
	elseif sceneId == YX_LOULAN_SCENE_ID7 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LOULAN_BROADCAST_NUM7 )
		x310030_ShowMessage1(sceneId,message)
		YX_LOULAN_BROADCAST_NUM7 = YX_LOULAN_BROADCAST_NUM7 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
		
	elseif sceneId == YX_LOULAN_SCENE_ID8 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LOULAN_BROADCAST_NUM8 )
		x310030_ShowMessage1(sceneId,message)
		YX_LOULAN_BROADCAST_NUM8 = YX_LOULAN_BROADCAST_NUM8 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始

	elseif sceneId == YX_LOULAN_SCENE_ID9 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LOULAN_BROADCAST_NUM9 )
		x310030_ShowMessage1(sceneId,message)
		YX_LOULAN_BROADCAST_NUM9 = YX_LOULAN_BROADCAST_NUM9 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
				
	elseif sceneId == YX_LAIYIN_SCENE_ID1 then
	
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LAIYIN_BROADCAST_NUM1 )
		x310030_ShowMessage1(sceneId,message)
		YX_LAIYIN_BROADCAST_NUM1 = YX_LAIYIN_BROADCAST_NUM1 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
		
	elseif sceneId == YX_LAIYIN_SCENE_ID2 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LAIYIN_BROADCAST_NUM2 )
		x310030_ShowMessage1(sceneId,message)
		YX_LAIYIN_BROADCAST_NUM2 = YX_LAIYIN_BROADCAST_NUM2 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
		
	elseif sceneId == YX_LAIYIN_SCENE_ID3 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LAIYIN_BROADCAST_NUM3 )
		x310030_ShowMessage1(sceneId,message)
		YX_LAIYIN_BROADCAST_NUM3 = YX_LAIYIN_BROADCAST_NUM3 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	
	elseif sceneId == YX_LAIYIN_SCENE_ID4 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LAIYIN_BROADCAST_NUM4 )
		x310030_ShowMessage1(sceneId,message)
		YX_LAIYIN_BROADCAST_NUM4 = YX_LAIYIN_BROADCAST_NUM4 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始

	elseif sceneId == YX_LAIYIN_SCENE_ID5 then

		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LAIYIN_BROADCAST_NUM5 )
		x310030_ShowMessage1(sceneId,message)
		YX_LAIYIN_BROADCAST_NUM5 = YX_LAIYIN_BROADCAST_NUM5 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	
	elseif sceneId == YX_LAIYIN_SCENE_ID6 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LAIYIN_BROADCAST_NUM6 )
		x310030_ShowMessage1(sceneId,message)
		YX_LAIYIN_BROADCAST_NUM6 = YX_LAIYIN_BROADCAST_NUM6 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
		
	elseif sceneId == YX_LAIYIN_SCENE_ID7 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LAIYIN_BROADCAST_NUM7 )
		x310030_ShowMessage1(sceneId,message)
		YX_LAIYIN_BROADCAST_NUM7 = YX_LAIYIN_BROADCAST_NUM7 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
		
	elseif sceneId == YX_LAIYIN_SCENE_ID8 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LAIYIN_BROADCAST_NUM8 )
		x310030_ShowMessage1(sceneId,message)
		YX_LAIYIN_BROADCAST_NUM8 = YX_LAIYIN_BROADCAST_NUM8 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	
	elseif sceneId == YX_LAIYIN_SCENE_ID9 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LAIYIN_BROADCAST_NUM9 )
		x310030_ShowMessage1(sceneId,message)
		YX_LAIYIN_BROADCAST_NUM9 = YX_LAIYIN_BROADCAST_NUM9 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始		
				
	elseif sceneId == YX_KUNLUN_SCENE_ID1 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_KUNLUN_BROADCAST_NUM1 )
		x310030_ShowMessage1(sceneId,message)
		YX_KUNLUN_BROADCAST_NUM1 = YX_KUNLUN_BROADCAST_NUM1 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
		
	elseif sceneId == YX_KUNLUN_SCENE_ID2 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_KUNLUN_BROADCAST_NUM2 )
		x310030_ShowMessage1(sceneId,message)
		YX_KUNLUN_BROADCAST_NUM2 = YX_KUNLUN_BROADCAST_NUM2 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
		
	elseif sceneId == YX_KUNLUN_SCENE_ID3 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_KUNLUN_BROADCAST_NUM3 )
		x310030_ShowMessage1(sceneId,message)
		YX_KUNLUN_BROADCAST_NUM3 = YX_KUNLUN_BROADCAST_NUM3 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	
	elseif sceneId == YX_KUNLUN_SCENE_ID4 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_KUNLUN_BROADCAST_NUM4 )
		x310030_ShowMessage1(sceneId,message)
		YX_KUNLUN_BROADCAST_NUM4 = YX_KUNLUN_BROADCAST_NUM4 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
		
	elseif sceneId == YX_KUNLUN_SCENE_ID5 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_KUNLUN_BROADCAST_NUM5 )
		x310030_ShowMessage1(sceneId,message)
		YX_KUNLUN_BROADCAST_NUM5 = YX_KUNLUN_BROADCAST_NUM5 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	
	elseif sceneId == YX_KUNLUN_SCENE_ID6 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_KUNLUN_BROADCAST_NUM6 )
		x310030_ShowMessage1(sceneId,message)
		YX_KUNLUN_BROADCAST_NUM6 = YX_KUNLUN_BROADCAST_NUM6 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
		
	elseif sceneId == YX_KUNLUN_SCENE_ID7 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_KUNLUN_BROADCAST_NUM7 )
		x310030_ShowMessage1(sceneId,message)
		YX_KUNLUN_BROADCAST_NUM7 = YX_KUNLUN_BROADCAST_NUM7 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
		
	elseif sceneId == YX_KUNLUN_SCENE_ID8 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_KUNLUN_BROADCAST_NUM8 )
		x310030_ShowMessage1(sceneId,message)
		YX_KUNLUN_BROADCAST_NUM8 = YX_KUNLUN_BROADCAST_NUM8 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
		
	elseif sceneId == YX_KUNLUN_SCENE_ID9 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_KUNLUN_BROADCAST_NUM9 )
		x310030_ShowMessage1(sceneId,message)
		YX_KUNLUN_BROADCAST_NUM9 = YX_KUNLUN_BROADCAST_NUM9 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始		
				
	elseif sceneId == YX_DUNHUANG_SCENE_ID1 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_DUNHUANG_BROADCAST_NUM1 )
		x310030_ShowMessage1(sceneId,message)
		YX_DUNHUANG_BROADCAST_NUM1 = YX_DUNHUANG_BROADCAST_NUM1 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
		
	elseif sceneId == YX_DUNHUANG_SCENE_ID2 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_DUNHUANG_BROADCAST_NUM2 )
		x310030_ShowMessage1(sceneId,message)
		YX_DUNHUANG_BROADCAST_NUM2 = YX_DUNHUANG_BROADCAST_NUM2 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
		
	elseif sceneId == YX_DUNHUANG_SCENE_ID3 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_DUNHUANG_BROADCAST_NUM3 )
		x310030_ShowMessage1(sceneId,message)
		YX_DUNHUANG_BROADCAST_NUM3 = YX_DUNHUANG_BROADCAST_NUM3 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_DUNHUANG_SCENE_ID4 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_DUNHUANG_BROADCAST_NUM4 )
		x310030_ShowMessage1(sceneId,message)
		YX_DUNHUANG_BROADCAST_NUM4 = YX_DUNHUANG_BROADCAST_NUM4 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始

	elseif sceneId == YX_DUNHUANG_SCENE_ID5 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_DUNHUANG_BROADCAST_NUM5 )
		x310030_ShowMessage1(sceneId,message)
		YX_DUNHUANG_BROADCAST_NUM5 = YX_DUNHUANG_BROADCAST_NUM5 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
		
	elseif sceneId == YX_DUNHUANG_SCENE_ID6 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_DUNHUANG_BROADCAST_NUM6 )
		x310030_ShowMessage1(sceneId,message)
		YX_DUNHUANG_BROADCAST_NUM6 = YX_DUNHUANG_BROADCAST_NUM6 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始

	elseif sceneId == YX_DUNHUANG_SCENE_ID7 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_DUNHUANG_BROADCAST_NUM7 )
		x310030_ShowMessage1(sceneId,message)
		YX_DUNHUANG_BROADCAST_NUM7 = YX_DUNHUANG_BROADCAST_NUM7 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始	

    elseif sceneId == YX_DUNHUANG_SCENE_ID8 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_DUNHUANG_BROADCAST_NUM8 )
		x310030_ShowMessage1(sceneId,message)
		YX_DUNHUANG_BROADCAST_NUM8 = YX_DUNHUANG_BROADCAST_NUM8 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
		
    elseif sceneId == YX_DUNHUANG_SCENE_ID9 then
		
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_DUNHUANG_BROADCAST_NUM9 )
		x310030_ShowMessage1(sceneId,message)
		YX_DUNHUANG_BROADCAST_NUM9 = YX_DUNHUANG_BROADCAST_NUM9 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始			

	end
	
end

function x310030_ProcTiming( sceneId, actId, uTime )

end


function x310030_BroadCastPre(sceneId, actId, uTime)

	if sceneId == YX_LOULAN_SCENE_ID1 then
		if YX_LOULAN_BROADCAST_NUM1 == x310030_g_PreBroadCastNum then
			YX_LOULAN_BROADCAST_NUM1 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LOULAN_BROADCAST_NUM1 )
		x310030_ShowMessage1(sceneId,message)
		YX_LOULAN_BROADCAST_NUM1 = YX_LOULAN_BROADCAST_NUM1 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_LOULAN_SCENE_ID2 then
		if YX_LOULAN_BROADCAST_NUM2 == x310030_g_PreBroadCastNum then
			YX_LOULAN_BROADCAST_NUM2 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LOULAN_BROADCAST_NUM2 )
		x310030_ShowMessage1(sceneId,message)
		YX_LOULAN_BROADCAST_NUM2 = YX_LOULAN_BROADCAST_NUM2 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_LOULAN_SCENE_ID3 then
		if YX_LOULAN_BROADCAST_NUM3 == x310030_g_PreBroadCastNum then
			YX_LOULAN_BROADCAST_NUM3 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LOULAN_BROADCAST_NUM3 )
		x310030_ShowMessage1(sceneId,message)
		YX_LOULAN_BROADCAST_NUM3 = YX_LOULAN_BROADCAST_NUM3 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_LOULAN_SCENE_ID4 then
		if YX_LOULAN_BROADCAST_NUM4 == x310030_g_PreBroadCastNum then
			YX_LOULAN_BROADCAST_NUM4 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LOULAN_BROADCAST_NUM4 )
		x310030_ShowMessage1(sceneId,message)
		YX_LOULAN_BROADCAST_NUM4 = YX_LOULAN_BROADCAST_NUM4 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
		
	elseif sceneId == YX_LOULAN_SCENE_ID5 then
		if YX_LOULAN_BROADCAST_NUM5 == x310030_g_PreBroadCastNum then
			YX_LOULAN_BROADCAST_NUM5 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LOULAN_BROADCAST_NUM5 )
		x310030_ShowMessage1(sceneId,message)
		YX_LOULAN_BROADCAST_NUM5 = YX_LOULAN_BROADCAST_NUM5 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_LOULAN_SCENE_ID6 then
		if YX_LOULAN_BROADCAST_NUM6 == x310030_g_PreBroadCastNum then
			YX_LOULAN_BROADCAST_NUM6 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LOULAN_BROADCAST_NUM6 )
		x310030_ShowMessage1(sceneId,message)
		YX_LOULAN_BROADCAST_NUM6 = YX_LOULAN_BROADCAST_NUM6 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_LOULAN_SCENE_ID7 then
		if YX_LOULAN_BROADCAST_NUM7 == x310030_g_PreBroadCastNum then
			YX_LOULAN_BROADCAST_NUM7 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LOULAN_BROADCAST_NUM7 )
		x310030_ShowMessage1(sceneId,message)
		YX_LOULAN_BROADCAST_NUM7 = YX_LOULAN_BROADCAST_NUM7 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
    elseif sceneId == YX_LOULAN_SCENE_ID8 then
		if YX_LOULAN_BROADCAST_NUM8 == x310030_g_PreBroadCastNum then
			YX_LOULAN_BROADCAST_NUM8= 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LOULAN_BROADCAST_NUM8 )
		x310030_ShowMessage1(sceneId,message)
		YX_LOULAN_BROADCAST_NUM8 = YX_LOULAN_BROADCAST_NUM8 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
    elseif sceneId == YX_LOULAN_SCENE_ID9 then
		if YX_LOULAN_BROADCAST_NUM9 == x310030_g_PreBroadCastNum then
			YX_LOULAN_BROADCAST_NUM9= 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LOULAN_BROADCAST_NUM9 )
		x310030_ShowMessage1(sceneId,message)
		YX_LOULAN_BROADCAST_NUM9 = YX_LOULAN_BROADCAST_NUM9 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始		
			
	elseif sceneId == YX_LAIYIN_SCENE_ID1 then
		if YX_LAIYIN_BROADCAST_NUM1 == x310030_g_PreBroadCastNum then
			YX_LAIYIN_BROADCAST_NUM1 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LAIYIN_BROADCAST_NUM1 )
		x310030_ShowMessage1(sceneId,message)
		YX_LAIYIN_BROADCAST_NUM1 = YX_LAIYIN_BROADCAST_NUM1 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_LAIYIN_SCENE_ID2 then
		if YX_LAIYIN_BROADCAST_NUM2 == x310030_g_PreBroadCastNum then
			YX_LAIYIN_BROADCAST_NUM2 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LAIYIN_BROADCAST_NUM2 )
		x310030_ShowMessage1(sceneId,message)
		YX_LAIYIN_BROADCAST_NUM2 = YX_LAIYIN_BROADCAST_NUM2 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_LAIYIN_SCENE_ID3 then
		if YX_LAIYIN_BROADCAST_NUM3 == x310030_g_PreBroadCastNum then
			YX_LAIYIN_BROADCAST_NUM3 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LAIYIN_BROADCAST_NUM3 )
		x310030_ShowMessage1(sceneId,message)
		YX_LAIYIN_BROADCAST_NUM3 = YX_LAIYIN_BROADCAST_NUM3 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_LAIYIN_SCENE_ID4 then
		if YX_LAIYIN_BROADCAST_NUM4 == x310030_g_PreBroadCastNum then
			YX_LAIYIN_BROADCAST_NUM4 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LAIYIN_BROADCAST_NUM4 )
		x310030_ShowMessage1(sceneId,message)
		YX_LAIYIN_BROADCAST_NUM4 = YX_LAIYIN_BROADCAST_NUM4 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
		
	elseif sceneId == YX_LAIYIN_SCENE_ID5 then
		if YX_LAIYIN_BROADCAST_NUM5 == x310030_g_PreBroadCastNum then
			YX_LAIYIN_BROADCAST_NUM5 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LAIYIN_BROADCAST_NUM5 )
		x310030_ShowMessage1(sceneId,message)
		YX_LAIYIN_BROADCAST_NUM5 = YX_LAIYIN_BROADCAST_NUM5 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_LAIYIN_SCENE_ID6 then
		if YX_LAIYIN_BROADCAST_NUM6 == x310030_g_PreBroadCastNum then
			YX_LAIYIN_BROADCAST_NUM6 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LAIYIN_BROADCAST_NUM6 )
		x310030_ShowMessage1(sceneId,message)
		YX_LAIYIN_BROADCAST_NUM6 = YX_LAIYIN_BROADCAST_NUM6 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_LAIYIN_SCENE_ID7 then
		if YX_LAIYIN_BROADCAST_NUM7 == x310030_g_PreBroadCastNum then
			YX_LAIYIN_BROADCAST_NUM7 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LAIYIN_BROADCAST_NUM7 )
		x310030_ShowMessage1(sceneId,message)
		YX_LAIYIN_BROADCAST_NUM7 = YX_LAIYIN_BROADCAST_NUM7 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_LAIYIN_SCENE_ID8 then
		if YX_LAIYIN_BROADCAST_NUM8 == x310030_g_PreBroadCastNum then
			YX_LAIYIN_BROADCAST_NUM8 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LAIYIN_BROADCAST_NUM8 )
		x310030_ShowMessage1(sceneId,message)
		YX_LAIYIN_BROADCAST_NUM8 = YX_LAIYIN_BROADCAST_NUM8 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_LAIYIN_SCENE_ID9 then
		if YX_LAIYIN_BROADCAST_NUM9 == x310030_g_PreBroadCastNum then
			YX_LAIYIN_BROADCAST_NUM9 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_LAIYIN_BROADCAST_NUM9 )
		x310030_ShowMessage1(sceneId,message)
		YX_LAIYIN_BROADCAST_NUM9 = YX_LAIYIN_BROADCAST_NUM9 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始		
		
	elseif sceneId == YX_KUNLUN_SCENE_ID1 then
		if YX_KUNLUN_BROADCAST_NUM1 == x310030_g_PreBroadCastNum then
			YX_KUNLUN_BROADCAST_NUM1 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_KUNLUN_BROADCAST_NUM1 )
		x310030_ShowMessage1(sceneId,message)
		YX_KUNLUN_BROADCAST_NUM1 = YX_KUNLUN_BROADCAST_NUM1 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_KUNLUN_SCENE_ID2 then
		if YX_KUNLUN_BROADCAST_NUM2 == x310030_g_PreBroadCastNum then
			YX_KUNLUN_BROADCAST_NUM2 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_KUNLUN_BROADCAST_NUM2 )
		x310030_ShowMessage1(sceneId,message)
		YX_KUNLUN_BROADCAST_NUM2 = YX_KUNLUN_BROADCAST_NUM2 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_KUNLUN_SCENE_ID3 then
		if YX_KUNLUN_BROADCAST_NUM3 == x310030_g_PreBroadCastNum then
			YX_KUNLUN_BROADCAST_NUM3 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_KUNLUN_BROADCAST_NUM3 )
		x310030_ShowMessage1(sceneId,message)
		YX_KUNLUN_BROADCAST_NUM3 = YX_KUNLUN_BROADCAST_NUM3 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_KUNLUN_SCENE_ID4 then
		if YX_KUNLUN_BROADCAST_NUM4 == x310030_g_PreBroadCastNum then
			YX_KUNLUN_BROADCAST_NUM4 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_KUNLUN_BROADCAST_NUM4 )
		x310030_ShowMessage1(sceneId,message)
		YX_KUNLUN_BROADCAST_NUM4 = YX_KUNLUN_BROADCAST_NUM4 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始

	elseif sceneId == YX_KUNLUN_SCENE_ID5 then
		if YX_KUNLUN_BROADCAST_NUM5 == x310030_g_PreBroadCastNum then
			YX_KUNLUN_BROADCAST_NUM5 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_KUNLUN_BROADCAST_NUM5 )
		x310030_ShowMessage1(sceneId,message)
		YX_KUNLUN_BROADCAST_NUM5 = YX_KUNLUN_BROADCAST_NUM5 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
		
	elseif sceneId == YX_KUNLUN_SCENE_ID6 then
		if YX_KUNLUN_BROADCAST_NUM6 == x310030_g_PreBroadCastNum then
			YX_KUNLUN_BROADCAST_NUM6 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_KUNLUN_BROADCAST_NUM6 )
		x310030_ShowMessage1(sceneId,message)
		YX_KUNLUN_BROADCAST_NUM6 = YX_KUNLUN_BROADCAST_NUM6 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
		
	elseif sceneId == YX_KUNLUN_SCENE_ID7 then
		if YX_KUNLUN_BROADCAST_NUM7 == x310030_g_PreBroadCastNum then
			YX_KUNLUN_BROADCAST_NUM7 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_KUNLUN_BROADCAST_NUM7 )
		x310030_ShowMessage1(sceneId,message)
		YX_KUNLUN_BROADCAST_NUM7 = YX_KUNLUN_BROADCAST_NUM7 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_KUNLUN_SCENE_ID8 then
		if YX_KUNLUN_BROADCAST_NUM8 == x310030_g_PreBroadCastNum then
			YX_KUNLUN_BROADCAST_NUM8 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_KUNLUN_BROADCAST_NUM8 )
		x310030_ShowMessage1(sceneId,message)
		YX_KUNLUN_BROADCAST_NUM8 = YX_KUNLUN_BROADCAST_NUM8 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_KUNLUN_SCENE_ID9 then
		if YX_KUNLUN_BROADCAST_NUM9 == x310030_g_PreBroadCastNum then
			YX_KUNLUN_BROADCAST_NUM9 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_KUNLUN_BROADCAST_NUM9 )
		x310030_ShowMessage1(sceneId,message)
		YX_KUNLUN_BROADCAST_NUM9 = YX_KUNLUN_BROADCAST_NUM9 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始		

	elseif sceneId == YX_DUNHUANG_SCENE_ID1 then
		if YX_DUNHUANG_BROADCAST_NUM1 == x310030_g_PreBroadCastNum then
			YX_DUNHUANG_BROADCAST_NUM1 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_DUNHUANG_BROADCAST_NUM1 )
		x310030_ShowMessage1(sceneId,message)
		YX_DUNHUANG_BROADCAST_NUM1 = YX_DUNHUANG_BROADCAST_NUM1 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_DUNHUANG_SCENE_ID2 then
		if YX_DUNHUANG_BROADCAST_NUM2 == x310030_g_PreBroadCastNum then
			YX_DUNHUANG_BROADCAST_NUM2 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_DUNHUANG_BROADCAST_NUM2 )
		x310030_ShowMessage1(sceneId,message)
		YX_DUNHUANG_BROADCAST_NUM2 = YX_DUNHUANG_BROADCAST_NUM2 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_DUNHUANG_SCENE_ID3 then
		if YX_DUNHUANG_BROADCAST_NUM3 == x310030_g_PreBroadCastNum then
			YX_DUNHUANG_BROADCAST_NUM3 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_DUNHUANG_BROADCAST_NUM3 )
		x310030_ShowMessage1(sceneId,message)
		YX_DUNHUANG_BROADCAST_NUM3 = YX_DUNHUANG_BROADCAST_NUM3 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_DUNHUANG_SCENE_ID4 then
		if YX_DUNHUANG_BROADCAST_NUM4 == x310030_g_PreBroadCastNum then
			YX_DUNHUANG_BROADCAST_NUM4 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_DUNHUANG_BROADCAST_NUM4 )
		x310030_ShowMessage1(sceneId,message)
		YX_DUNHUANG_BROADCAST_NUM4 = YX_DUNHUANG_BROADCAST_NUM4 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
		
	elseif sceneId == YX_DUNHUANG_SCENE_ID5 then
		if YX_DUNHUANG_BROADCAST_NUM5 == x310030_g_PreBroadCastNum then
			YX_DUNHUANG_BROADCAST_NUM5 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_DUNHUANG_BROADCAST_NUM5 )
		x310030_ShowMessage1(sceneId,message)
		YX_DUNHUANG_BROADCAST_NUM5 = YX_DUNHUANG_BROADCAST_NUM5 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_DUNHUANG_SCENE_ID6 then
		if YX_DUNHUANG_BROADCAST_NUM6 == x310030_g_PreBroadCastNum then
			YX_DUNHUANG_BROADCAST_NUM6 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_DUNHUANG_BROADCAST_NUM6 )
		x310030_ShowMessage1(sceneId,message)
		YX_DUNHUANG_BROADCAST_NUM6 = YX_DUNHUANG_BROADCAST_NUM6 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_DUNHUANG_SCENE_ID7 then
		if YX_DUNHUANG_BROADCAST_NUM7 == x310030_g_PreBroadCastNum then
			YX_DUNHUANG_BROADCAST_NUM7 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_DUNHUANG_BROADCAST_NUM7 )
		x310030_ShowMessage1(sceneId,message)
		YX_DUNHUANG_BROADCAST_NUM7 = YX_DUNHUANG_BROADCAST_NUM7 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_DUNHUANG_SCENE_ID8 then
		if YX_DUNHUANG_BROADCAST_NUM8 == x310030_g_PreBroadCastNum then
			YX_DUNHUANG_BROADCAST_NUM8 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_DUNHUANG_BROADCAST_NUM8 )
		x310030_ShowMessage1(sceneId,message)
		YX_DUNHUANG_BROADCAST_NUM8 = YX_DUNHUANG_BROADCAST_NUM8 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_DUNHUANG_SCENE_ID9 then
		if YX_DUNHUANG_BROADCAST_NUM9 == x310030_g_PreBroadCastNum then
			YX_DUNHUANG_BROADCAST_NUM9 = 0
			x310030_CreateMonster(sceneId, actId, uTime)
			return
		end
		local message = format( x310030_str_pre, x310030_g_PreBroadCastNum-YX_DUNHUANG_BROADCAST_NUM9 )
		x310030_ShowMessage1(sceneId,message)
		YX_DUNHUANG_BROADCAST_NUM9 = YX_DUNHUANG_BROADCAST_NUM9 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastPre", actId, 60*1000  ) --1分钟后开始		
		
	end
	
end


function x310030_OnCreateMonster(sceneId,nCreateFlag )

	
	local checkMonsterFlag = 0
	local nRespwanTimer = x310030_RespwanTime1
	
	if nCreateFlag == 1 then
	
		checkMonsterFlag = nCreateFlag-1
		nRespwanTimer = x310030_RespwanTime1
		
	elseif nCreateFlag == 2 then
		
		checkMonsterFlag = nCreateFlag-1
		nRespwanTimer = x310030_RespwanTime2
		
	elseif nCreateFlag == 3 then
	
		checkMonsterFlag = nCreateFlag-1
		nRespwanTimer = x310030_RespwanTime3
	end

	--优化的创建怪数据
	local nIndexFrom = GetFubenDataPosByScriptID(x310030_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x310030_g_ScriptId )
	for i = 0,nDataCount-1 do
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x310030_g_ScriptId,nIndexFrom,i)
		if idScript == x310030_g_ScriptId and monsterFlag == checkMonsterFlag and sceneId == flag then
			for j=0,count -1 do
				
				local rx = random(-3,3)
				x = x + rx
				local rz = random(-3,3)
				z = z + rz
				
				local objId, objGuid = CreateMonster(sceneId, type, x, z, 0, -1, -1, -1, 21, -1, 0, "", "", nRespwanTimer)
				if objId ~= -1 then
					x310030_AddObj(sceneId, objId)
				end
			end
		end
	end
end


function x310030_CreateMonster(sceneId, actId, uTime)

	if sceneId == YX_LOULAN_SCENE_ID1 then
		if YX_LOULAN_CREATE_ROUNDS1 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)			
			x310030_OnCreateMonster(sceneId,1)

			YX_LOULAN_CREATE_ROUNDS1 = YX_LOULAN_CREATE_ROUNDS1 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
			
		elseif YX_LOULAN_CREATE_ROUNDS1 == 1 then
		
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_LOULAN_CREATE_ROUNDS1 = YX_LOULAN_CREATE_ROUNDS1 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
			
		elseif YX_LOULAN_CREATE_ROUNDS1 == 2 then
		
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)	

			YX_LOULAN_CREATE_ROUNDS1 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LOULAN_BROADCAST_NUM1 )
			x310030_ShowMessage1(sceneId,message)
			
			YX_LOULAN_BROADCAST_NUM1 = YX_LOULAN_BROADCAST_NUM1 + 1
		end
		
	elseif sceneId == YX_LOULAN_SCENE_ID2 then
	
		if YX_LOULAN_CREATE_ROUNDS2 == 0 then
		
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)

			YX_LOULAN_CREATE_ROUNDS2 = YX_LOULAN_CREATE_ROUNDS2 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LOULAN_CREATE_ROUNDS2 == 1 then

			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_LOULAN_CREATE_ROUNDS2 = YX_LOULAN_CREATE_ROUNDS2 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval ) --1分钟后开始
		elseif YX_LOULAN_CREATE_ROUNDS2 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_LOULAN_CREATE_ROUNDS2 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LOULAN_BROADCAST_NUM2 )
			x310030_ShowMessage1(sceneId,message)
			YX_LOULAN_BROADCAST_NUM2 = YX_LOULAN_BROADCAST_NUM2 + 1
		end
		
	elseif sceneId == YX_LOULAN_SCENE_ID3 then
		if YX_LOULAN_CREATE_ROUNDS3 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)
			

			YX_LOULAN_CREATE_ROUNDS3 = YX_LOULAN_CREATE_ROUNDS3 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LOULAN_CREATE_ROUNDS3 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_LOULAN_CREATE_ROUNDS3 = YX_LOULAN_CREATE_ROUNDS3 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LOULAN_CREATE_ROUNDS3 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_LOULAN_CREATE_ROUNDS3 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LOULAN_BROADCAST_NUM3 )
			x310030_ShowMessage1(sceneId,message)
			YX_LOULAN_BROADCAST_NUM3 = YX_LOULAN_BROADCAST_NUM3 + 1
		end
	elseif sceneId == YX_LOULAN_SCENE_ID4 then
		if YX_LOULAN_CREATE_ROUNDS4 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)
			

			YX_LOULAN_CREATE_ROUNDS4 = YX_LOULAN_CREATE_ROUNDS4 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LOULAN_CREATE_ROUNDS4 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_LOULAN_CREATE_ROUNDS4 = YX_LOULAN_CREATE_ROUNDS4 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LOULAN_CREATE_ROUNDS4 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_LOULAN_CREATE_ROUNDS4 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LOULAN_BROADCAST_NUM4 )
			x310030_ShowMessage1(sceneId,message)
			YX_LOULAN_BROADCAST_NUM4 = YX_LOULAN_BROADCAST_NUM4 + 1
		end

	elseif sceneId == YX_LOULAN_SCENE_ID5 then
		
		if YX_LOULAN_CREATE_ROUNDS5 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)
			

			YX_LOULAN_CREATE_ROUNDS5 = YX_LOULAN_CREATE_ROUNDS5 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LOULAN_CREATE_ROUNDS5 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_LOULAN_CREATE_ROUNDS5 = YX_LOULAN_CREATE_ROUNDS5 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LOULAN_CREATE_ROUNDS5 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_LOULAN_CREATE_ROUNDS5 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LOULAN_BROADCAST_NUM5 )
			x310030_ShowMessage1(sceneId,message)
			YX_LOULAN_BROADCAST_NUM5 = YX_LOULAN_BROADCAST_NUM5 + 1
		end
	
	elseif sceneId == YX_LOULAN_SCENE_ID6 then
		if YX_LOULAN_CREATE_ROUNDS6 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)
			

			YX_LOULAN_CREATE_ROUNDS6 = YX_LOULAN_CREATE_ROUNDS6 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LOULAN_CREATE_ROUNDS6 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_LOULAN_CREATE_ROUNDS6 = YX_LOULAN_CREATE_ROUNDS6 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LOULAN_CREATE_ROUNDS6 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_LOULAN_CREATE_ROUNDS6 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LOULAN_BROADCAST_NUM6 )
			x310030_ShowMessage1(sceneId,message)
			YX_LOULAN_BROADCAST_NUM6 = YX_LOULAN_BROADCAST_NUM6 + 1
		end
	elseif sceneId == YX_LOULAN_SCENE_ID7 then
		if YX_LOULAN_CREATE_ROUNDS7 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)
			

			YX_LOULAN_CREATE_ROUNDS7 = YX_LOULAN_CREATE_ROUNDS7 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LOULAN_CREATE_ROUNDS7 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_LOULAN_CREATE_ROUNDS7 = YX_LOULAN_CREATE_ROUNDS7 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LOULAN_CREATE_ROUNDS7 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_LOULAN_CREATE_ROUNDS7 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LOULAN_BROADCAST_NUM7 )
			x310030_ShowMessage1(sceneId,message)
			YX_LOULAN_BROADCAST_NUM7 = YX_LOULAN_BROADCAST_NUM7 + 1
		end
	elseif sceneId == YX_LOULAN_SCENE_ID8 then
		if YX_LOULAN_CREATE_ROUNDS8 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)
			

			YX_LOULAN_CREATE_ROUNDS8 = YX_LOULAN_CREATE_ROUNDS8 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LOULAN_CREATE_ROUNDS8 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_LOULAN_CREATE_ROUNDS8 = YX_LOULAN_CREATE_ROUNDS8 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LOULAN_CREATE_ROUNDS8 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_LOULAN_CREATE_ROUNDS8 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LOULAN_BROADCAST_NUM8 )
			x310030_ShowMessage1(sceneId,message)
			YX_LOULAN_BROADCAST_NUM8 = YX_LOULAN_BROADCAST_NUM8 + 1
		end
	elseif sceneId == YX_LOULAN_SCENE_ID9 then
		if YX_LOULAN_CREATE_ROUNDS9 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)
			

			YX_LOULAN_CREATE_ROUNDS9 = YX_LOULAN_CREATE_ROUNDS9 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LOULAN_CREATE_ROUNDS9 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_LOULAN_CREATE_ROUNDS9 = YX_LOULAN_CREATE_ROUNDS9 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LOULAN_CREATE_ROUNDS9 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_LOULAN_CREATE_ROUNDS9 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LOULAN_BROADCAST_NUM9 )
			x310030_ShowMessage1(sceneId,message)
			YX_LOULAN_BROADCAST_NUM9 = YX_LOULAN_BROADCAST_NUM9 + 1
		end		
		
	elseif sceneId == YX_LAIYIN_SCENE_ID1 then
		if YX_LAIYIN_CREATE_ROUNDS1 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)

			YX_LAIYIN_CREATE_ROUNDS1 = YX_LAIYIN_CREATE_ROUNDS1 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LAIYIN_CREATE_ROUNDS1 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_LAIYIN_CREATE_ROUNDS1 = YX_LAIYIN_CREATE_ROUNDS1 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LAIYIN_CREATE_ROUNDS1 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)
			
			YX_LAIYIN_CREATE_ROUNDS1 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LAIYIN_BROADCAST_NUM1 )
			x310030_ShowMessage1(sceneId,message)
			YX_LAIYIN_BROADCAST_NUM1 = YX_LAIYIN_BROADCAST_NUM1 + 1
		end
	elseif sceneId == YX_LAIYIN_SCENE_ID2 then
		if YX_LAIYIN_CREATE_ROUNDS2 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)

			YX_LAIYIN_CREATE_ROUNDS2 = YX_LAIYIN_CREATE_ROUNDS2 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LAIYIN_CREATE_ROUNDS2 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_LAIYIN_CREATE_ROUNDS2 = YX_LAIYIN_CREATE_ROUNDS2 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LAIYIN_CREATE_ROUNDS2 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_LAIYIN_CREATE_ROUNDS2 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LAIYIN_BROADCAST_NUM2 )
			x310030_ShowMessage1(sceneId,message)
			YX_LAIYIN_BROADCAST_NUM2 = YX_LAIYIN_BROADCAST_NUM2 + 1
		end
	elseif sceneId == YX_LAIYIN_SCENE_ID3 then
		if YX_LAIYIN_CREATE_ROUNDS3 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)

			YX_LAIYIN_CREATE_ROUNDS3 = YX_LAIYIN_CREATE_ROUNDS3 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LAIYIN_CREATE_ROUNDS3 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_LAIYIN_CREATE_ROUNDS3 = YX_LAIYIN_CREATE_ROUNDS3 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LAIYIN_CREATE_ROUNDS3 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_LAIYIN_CREATE_ROUNDS3 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LAIYIN_BROADCAST_NUM3 )
			x310030_ShowMessage1(sceneId,message)
			YX_LAIYIN_BROADCAST_NUM3 = YX_LAIYIN_BROADCAST_NUM3 + 1
		end
	elseif sceneId == YX_LAIYIN_SCENE_ID4 then
		if YX_LAIYIN_CREATE_ROUNDS4 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)

			YX_LAIYIN_CREATE_ROUNDS4 = YX_LAIYIN_CREATE_ROUNDS4 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LAIYIN_CREATE_ROUNDS4 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_LAIYIN_CREATE_ROUNDS4 = YX_LAIYIN_CREATE_ROUNDS4 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LAIYIN_CREATE_ROUNDS4 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_LAIYIN_CREATE_ROUNDS4 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LAIYIN_BROADCAST_NUM4 )
			x310030_ShowMessage1(sceneId,message)
			YX_LAIYIN_BROADCAST_NUM4 = YX_LAIYIN_BROADCAST_NUM4 + 1
		end


	elseif sceneId == YX_LAIYIN_SCENE_ID5 then
		if YX_LAIYIN_CREATE_ROUNDS5 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)
			

			YX_LAIYIN_CREATE_ROUNDS5 = YX_LAIYIN_CREATE_ROUNDS5 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LAIYIN_CREATE_ROUNDS5 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_LAIYIN_CREATE_ROUNDS5 = YX_LAIYIN_CREATE_ROUNDS5 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LAIYIN_CREATE_ROUNDS5 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_LAIYIN_CREATE_ROUNDS5 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LAIYIN_BROADCAST_NUM5 )
			x310030_ShowMessage1(sceneId,message)
			YX_LAIYIN_BROADCAST_NUM5 = YX_LAIYIN_BROADCAST_NUM5 + 1
		end
	
	elseif sceneId == YX_LAIYIN_SCENE_ID6 then
		if YX_LAIYIN_CREATE_ROUNDS6 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)
			

			YX_LAIYIN_CREATE_ROUNDS6 = YX_LAIYIN_CREATE_ROUNDS6 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LAIYIN_CREATE_ROUNDS6 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_LAIYIN_CREATE_ROUNDS6 = YX_LAIYIN_CREATE_ROUNDS6 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LAIYIN_CREATE_ROUNDS6 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_LAIYIN_CREATE_ROUNDS6 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LAIYIN_BROADCAST_NUM6 )
			x310030_ShowMessage1(sceneId,message)
			YX_LAIYIN_BROADCAST_NUM6 = YX_LAIYIN_BROADCAST_NUM6 + 1
		end
	elseif sceneId == YX_LAIYIN_SCENE_ID7 then
		if YX_LAIYIN_CREATE_ROUNDS7 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)
			

			YX_LAIYIN_CREATE_ROUNDS7 = YX_LAIYIN_CREATE_ROUNDS7 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LAIYIN_CREATE_ROUNDS7 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_LAIYIN_CREATE_ROUNDS7 = YX_LAIYIN_CREATE_ROUNDS7 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LAIYIN_CREATE_ROUNDS7 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_LAIYIN_CREATE_ROUNDS7 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LAIYIN_BROADCAST_NUM7 )
			x310030_ShowMessage1(sceneId,message)
			YX_LAIYIN_BROADCAST_NUM7 = YX_LAIYIN_BROADCAST_NUM7 + 1
		end
	elseif sceneId == YX_LAIYIN_SCENE_ID8 then
		if YX_LAIYIN_CREATE_ROUNDS8 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)
			

			YX_LAIYIN_CREATE_ROUNDS8 = YX_LAIYIN_CREATE_ROUNDS8 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LAIYIN_CREATE_ROUNDS8 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_LAIYIN_CREATE_ROUNDS8 = YX_LAIYIN_CREATE_ROUNDS8 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LAIYIN_CREATE_ROUNDS8 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_LAIYIN_CREATE_ROUNDS8 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LAIYIN_BROADCAST_NUM8 )
			x310030_ShowMessage1(sceneId,message)
			YX_LAIYIN_BROADCAST_NUM8 = YX_LAIYIN_BROADCAST_NUM8 + 1
		end
	elseif sceneId == YX_LAIYIN_SCENE_ID9 then
		if YX_LAIYIN_CREATE_ROUNDS9 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)
			

			YX_LAIYIN_CREATE_ROUNDS9 = YX_LAIYIN_CREATE_ROUNDS9 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LAIYIN_CREATE_ROUNDS9 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_LAIYIN_CREATE_ROUNDS9 = YX_LAIYIN_CREATE_ROUNDS9 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_LAIYIN_CREATE_ROUNDS9 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_LAIYIN_CREATE_ROUNDS9 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LAIYIN_BROADCAST_NUM9 )
			x310030_ShowMessage1(sceneId,message)
			YX_LAIYIN_BROADCAST_NUM9 = YX_LAIYIN_BROADCAST_NUM9 + 1
		end		

	elseif sceneId == YX_KUNLUN_SCENE_ID1 then
		if YX_KUNLUN_CREATE_ROUNDS1 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)

			YX_KUNLUN_CREATE_ROUNDS1 = YX_KUNLUN_CREATE_ROUNDS1 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_KUNLUN_CREATE_ROUNDS1 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_KUNLUN_CREATE_ROUNDS1 = YX_KUNLUN_CREATE_ROUNDS1 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_KUNLUN_CREATE_ROUNDS1 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_KUNLUN_CREATE_ROUNDS1 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_KUNLUN_BROADCAST_NUM1 )
			x310030_ShowMessage1(sceneId,message)
			YX_KUNLUN_BROADCAST_NUM1 = YX_KUNLUN_BROADCAST_NUM1 + 1
		end
	elseif sceneId == YX_KUNLUN_SCENE_ID2 then
		if YX_KUNLUN_CREATE_ROUNDS2 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)

			YX_KUNLUN_CREATE_ROUNDS2 = YX_KUNLUN_CREATE_ROUNDS2 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_KUNLUN_CREATE_ROUNDS2 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_KUNLUN_CREATE_ROUNDS2 = YX_KUNLUN_CREATE_ROUNDS2 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_KUNLUN_CREATE_ROUNDS2 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)
			
			YX_KUNLUN_CREATE_ROUNDS2 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_KUNLUN_BROADCAST_NUM2 )
			x310030_ShowMessage1(sceneId,message)
			YX_KUNLUN_BROADCAST_NUM2 = YX_KUNLUN_BROADCAST_NUM2 + 1
		end
	elseif sceneId == YX_KUNLUN_SCENE_ID3 then
		if YX_KUNLUN_CREATE_ROUNDS3 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)

			YX_KUNLUN_CREATE_ROUNDS3 = YX_KUNLUN_CREATE_ROUNDS3 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_KUNLUN_CREATE_ROUNDS3 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_KUNLUN_CREATE_ROUNDS3 = YX_KUNLUN_CREATE_ROUNDS3 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_KUNLUN_CREATE_ROUNDS3 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_KUNLUN_CREATE_ROUNDS3 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_KUNLUN_BROADCAST_NUM3 )
			x310030_ShowMessage1(sceneId,message)
			YX_KUNLUN_BROADCAST_NUM3 = YX_KUNLUN_BROADCAST_NUM3 + 1
		end
	elseif sceneId == YX_KUNLUN_SCENE_ID4 then
		if YX_KUNLUN_CREATE_ROUNDS4 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)

			YX_KUNLUN_CREATE_ROUNDS4 = YX_KUNLUN_CREATE_ROUNDS4 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_KUNLUN_CREATE_ROUNDS4 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_KUNLUN_CREATE_ROUNDS4 = YX_KUNLUN_CREATE_ROUNDS4 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_KUNLUN_CREATE_ROUNDS4 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_KUNLUN_CREATE_ROUNDS4 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_KUNLUN_BROADCAST_NUM4 )
			x310030_ShowMessage1(sceneId,message)
			YX_KUNLUN_BROADCAST_NUM4 = YX_KUNLUN_BROADCAST_NUM4 + 1
		end


	elseif sceneId == YX_KUNLUN_SCENE_ID5 then
		if YX_KUNLUN_CREATE_ROUNDS5 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)
			

			YX_KUNLUN_CREATE_ROUNDS5 = YX_KUNLUN_CREATE_ROUNDS5 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_KUNLUN_CREATE_ROUNDS5 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_KUNLUN_CREATE_ROUNDS5 = YX_KUNLUN_CREATE_ROUNDS5 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_KUNLUN_CREATE_ROUNDS5 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_KUNLUN_CREATE_ROUNDS5 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_KUNLUN_BROADCAST_NUM5 )
			x310030_ShowMessage1(sceneId,message)
			YX_KUNLUN_BROADCAST_NUM5 = YX_KUNLUN_BROADCAST_NUM5 + 1
		end
	
	elseif sceneId == YX_KUNLUN_SCENE_ID6 then
		if YX_KUNLUN_CREATE_ROUNDS6 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)
			

			YX_KUNLUN_CREATE_ROUNDS6 = YX_KUNLUN_CREATE_ROUNDS6 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_KUNLUN_CREATE_ROUNDS6 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_KUNLUN_CREATE_ROUNDS6 = YX_KUNLUN_CREATE_ROUNDS6 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_KUNLUN_CREATE_ROUNDS6 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_KUNLUN_CREATE_ROUNDS6 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_KUNLUN_BROADCAST_NUM6 )
			x310030_ShowMessage1(sceneId,message)
			YX_KUNLUN_BROADCAST_NUM6 = YX_KUNLUN_BROADCAST_NUM6 + 1
		end
		
	elseif sceneId == YX_KUNLUN_SCENE_ID7 then
		if YX_KUNLUN_CREATE_ROUNDS7 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)
			

			YX_KUNLUN_CREATE_ROUNDS7 = YX_KUNLUN_CREATE_ROUNDS7 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_KUNLUN_CREATE_ROUNDS7 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_KUNLUN_CREATE_ROUNDS7 = YX_KUNLUN_CREATE_ROUNDS7 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_KUNLUN_CREATE_ROUNDS7 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_KUNLUN_CREATE_ROUNDS7 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_KUNLUN_BROADCAST_NUM7 )
			x310030_ShowMessage1(sceneId,message)
			YX_KUNLUN_BROADCAST_NUM7 = YX_KUNLUN_BROADCAST_NUM7 + 1
		end
	elseif sceneId == YX_KUNLUN_SCENE_ID8 then
		if YX_KUNLUN_CREATE_ROUNDS8 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)
			

			YX_KUNLUN_CREATE_ROUNDS8 = YX_KUNLUN_CREATE_ROUNDS8 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_KUNLUN_CREATE_ROUNDS8 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_KUNLUN_CREATE_ROUNDS8 = YX_KUNLUN_CREATE_ROUNDS8 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_KUNLUN_CREATE_ROUNDS8 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_KUNLUN_CREATE_ROUNDS8 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_KUNLUN_BROADCAST_NUM8 )
			x310030_ShowMessage1(sceneId,message)
			YX_KUNLUN_BROADCAST_NUM8 = YX_KUNLUN_BROADCAST_NUM8 + 1
		end
	elseif sceneId == YX_KUNLUN_SCENE_ID9 then
		if YX_KUNLUN_CREATE_ROUNDS9 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)
			

			YX_KUNLUN_CREATE_ROUNDS9 = YX_KUNLUN_CREATE_ROUNDS9 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_KUNLUN_CREATE_ROUNDS9 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_KUNLUN_CREATE_ROUNDS9 = YX_KUNLUN_CREATE_ROUNDS9 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_KUNLUN_CREATE_ROUNDS9 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_KUNLUN_CREATE_ROUNDS9 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_KUNLUN_BROADCAST_NUM9 )
			x310030_ShowMessage1(sceneId,message)
			YX_KUNLUN_BROADCAST_NUM9 = YX_KUNLUN_BROADCAST_NUM9 + 1
		end		
	
	elseif sceneId == YX_DUNHUANG_SCENE_ID1 then
		if YX_DUNHUANG_CREATE_ROUNDS1 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)

			YX_DUNHUANG_CREATE_ROUNDS1 = YX_DUNHUANG_CREATE_ROUNDS1 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_DUNHUANG_CREATE_ROUNDS1 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_DUNHUANG_CREATE_ROUNDS1 = YX_DUNHUANG_CREATE_ROUNDS1 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_DUNHUANG_CREATE_ROUNDS1 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_DUNHUANG_CREATE_ROUNDS1 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_DUNHUANG_BROADCAST_NUM1 )
			x310030_ShowMessage1(sceneId,message)
			YX_DUNHUANG_BROADCAST_NUM1 = YX_DUNHUANG_BROADCAST_NUM1 + 1
		end
	elseif sceneId == YX_DUNHUANG_SCENE_ID2 then
		if YX_DUNHUANG_CREATE_ROUNDS2 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)

			YX_DUNHUANG_CREATE_ROUNDS2 = YX_DUNHUANG_CREATE_ROUNDS2 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_DUNHUANG_CREATE_ROUNDS2 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_DUNHUANG_CREATE_ROUNDS2 = YX_DUNHUANG_CREATE_ROUNDS2 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_DUNHUANG_CREATE_ROUNDS2 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_DUNHUANG_CREATE_ROUNDS2 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_DUNHUANG_BROADCAST_NUM2 )
			x310030_ShowMessage1(sceneId,message)
			YX_DUNHUANG_BROADCAST_NUM2 = YX_DUNHUANG_BROADCAST_NUM2 + 1
		end
	elseif sceneId == YX_DUNHUANG_SCENE_ID3 then
		if YX_DUNHUANG_CREATE_ROUNDS3 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)

			YX_DUNHUANG_CREATE_ROUNDS3 = YX_DUNHUANG_CREATE_ROUNDS3 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_DUNHUANG_CREATE_ROUNDS3 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_DUNHUANG_CREATE_ROUNDS3 = YX_DUNHUANG_CREATE_ROUNDS3 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_DUNHUANG_CREATE_ROUNDS3 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_DUNHUANG_CREATE_ROUNDS3 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_DUNHUANG_BROADCAST_NUM3 )
			x310030_ShowMessage1(sceneId,message)
			YX_DUNHUANG_BROADCAST_NUM3 = YX_DUNHUANG_BROADCAST_NUM3 + 1
		end
	elseif sceneId == YX_DUNHUANG_SCENE_ID4 then
		if YX_DUNHUANG_CREATE_ROUNDS4 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)

			YX_DUNHUANG_CREATE_ROUNDS4 = YX_DUNHUANG_CREATE_ROUNDS4 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_DUNHUANG_CREATE_ROUNDS4 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_DUNHUANG_CREATE_ROUNDS4 = YX_DUNHUANG_CREATE_ROUNDS4 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_DUNHUANG_CREATE_ROUNDS4 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_DUNHUANG_CREATE_ROUNDS4 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_DUNHUANG_BROADCAST_NUM4 )
			x310030_ShowMessage1(sceneId,message)
			YX_DUNHUANG_BROADCAST_NUM4 = YX_DUNHUANG_BROADCAST_NUM4 + 1
		end


	elseif sceneId == YX_DUNHUANG_SCENE_ID5 then
		if YX_DUNHUANG_CREATE_ROUNDS5 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)
			

			YX_DUNHUANG_CREATE_ROUNDS5 = YX_DUNHUANG_CREATE_ROUNDS5 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_DUNHUANG_CREATE_ROUNDS5 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_DUNHUANG_CREATE_ROUNDS5 = YX_DUNHUANG_CREATE_ROUNDS5 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_DUNHUANG_CREATE_ROUNDS5 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_DUNHUANG_CREATE_ROUNDS5 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_DUNHUANG_BROADCAST_NUM5 )
			x310030_ShowMessage1(sceneId,message)
			YX_DUNHUANG_BROADCAST_NUM5 = YX_DUNHUANG_BROADCAST_NUM5 + 1
		end
	
	elseif sceneId == YX_DUNHUANG_SCENE_ID6 then
		if YX_DUNHUANG_CREATE_ROUNDS6 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)
			

			YX_DUNHUANG_CREATE_ROUNDS6 = YX_DUNHUANG_CREATE_ROUNDS6 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_DUNHUANG_CREATE_ROUNDS6 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_DUNHUANG_CREATE_ROUNDS6 = YX_DUNHUANG_CREATE_ROUNDS6 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_DUNHUANG_CREATE_ROUNDS6 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_DUNHUANG_CREATE_ROUNDS6 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_DUNHUANG_BROADCAST_NUM6 )
			x310030_ShowMessage1(sceneId,message)
			YX_DUNHUANG_BROADCAST_NUM6 = YX_DUNHUANG_BROADCAST_NUM6 + 1
		end
	elseif sceneId == YX_DUNHUANG_SCENE_ID7 then
		if YX_DUNHUANG_CREATE_ROUNDS7 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)
			

			YX_DUNHUANG_CREATE_ROUNDS7 = YX_DUNHUANG_CREATE_ROUNDS7 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_DUNHUANG_CREATE_ROUNDS7 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_DUNHUANG_CREATE_ROUNDS7 = YX_DUNHUANG_CREATE_ROUNDS7 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_DUNHUANG_CREATE_ROUNDS7 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_DUNHUANG_CREATE_ROUNDS7 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_DUNHUANG_BROADCAST_NUM7 )
			x310030_ShowMessage1(sceneId,message)
			YX_DUNHUANG_BROADCAST_NUM7 = YX_DUNHUANG_BROADCAST_NUM7 + 1
		end
	elseif sceneId == YX_DUNHUANG_SCENE_ID8 then
		if YX_DUNHUANG_CREATE_ROUNDS8 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)
			

			YX_DUNHUANG_CREATE_ROUNDS8 = YX_DUNHUANG_CREATE_ROUNDS8 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_DUNHUANG_CREATE_ROUNDS8 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_DUNHUANG_CREATE_ROUNDS8 = YX_DUNHUANG_CREATE_ROUNDS8 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_DUNHUANG_CREATE_ROUNDS8 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_DUNHUANG_CREATE_ROUNDS8 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_DUNHUANG_BROADCAST_NUM8 )
			x310030_ShowMessage1(sceneId,message)
			YX_DUNHUANG_BROADCAST_NUM8 = YX_DUNHUANG_BROADCAST_NUM8 + 1
		end
	elseif sceneId == YX_DUNHUANG_SCENE_ID9 then
		if YX_DUNHUANG_CREATE_ROUNDS9 == 0 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai1)
			x310030_OnCreateMonster(sceneId,1)
			

			YX_DUNHUANG_CREATE_ROUNDS9 = YX_DUNHUANG_CREATE_ROUNDS9 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_DUNHUANG_CREATE_ROUNDS9 == 1 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai2)
			x310030_OnCreateMonster(sceneId,2)

			YX_DUNHUANG_CREATE_ROUNDS9 = YX_DUNHUANG_CREATE_ROUNDS9 + 1
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "CreateMonster", actId, x310030_g_CreateMonsterInterval  ) --1分钟后开始
		elseif YX_DUNHUANG_CREATE_ROUNDS9 == 2 then
			
			x310030_ShowMessage1(sceneId,x310030_str_shuaguai3)
			x310030_OnCreateMonster(sceneId,3)

			YX_DUNHUANG_CREATE_ROUNDS9 = 0
			SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
			local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_DUNHUANG_BROADCAST_NUM9 )
			x310030_ShowMessage1(sceneId,message)
			YX_DUNHUANG_BROADCAST_NUM9 = YX_DUNHUANG_BROADCAST_NUM9 + 1
		end		

	end
end

function x310030_BroadCastAfter(sceneId, actId, uTime)
	if sceneId == YX_LOULAN_SCENE_ID1 then
		if YX_LOULAN_BROADCAST_NUM1 == x310030_g_AfterBroadCastNum then
			YX_LOULAN_BROADCAST_NUM1 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LOULAN_BROADCAST_NUM1 )
		x310030_ShowMessage1(sceneId,message)
		YX_LOULAN_BROADCAST_NUM1 = YX_LOULAN_BROADCAST_NUM1 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_LOULAN_SCENE_ID2 then
		if YX_LOULAN_BROADCAST_NUM2 == x310030_g_AfterBroadCastNum then
			YX_LOULAN_BROADCAST_NUM2 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LOULAN_BROADCAST_NUM2 )
		x310030_ShowMessage1(sceneId,message)
		YX_LOULAN_BROADCAST_NUM2 = YX_LOULAN_BROADCAST_NUM2 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_LOULAN_SCENE_ID3 then
		if YX_LOULAN_BROADCAST_NUM3 == x310030_g_AfterBroadCastNum then
			YX_LOULAN_BROADCAST_NUM3 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LOULAN_BROADCAST_NUM3 )
		x310030_ShowMessage1(sceneId,message)
		YX_LOULAN_BROADCAST_NUM3 = YX_LOULAN_BROADCAST_NUM3 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_LOULAN_SCENE_ID4 then
		if YX_LOULAN_BROADCAST_NUM4 == x310030_g_AfterBroadCastNum then
			YX_LOULAN_BROADCAST_NUM4 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LOULAN_BROADCAST_NUM4 )
		x310030_ShowMessage1(sceneId,message)
		YX_LOULAN_BROADCAST_NUM4 = YX_LOULAN_BROADCAST_NUM4 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始

	elseif sceneId == YX_LOULAN_SCENE_ID5 then
		if YX_LOULAN_BROADCAST_NUM5 == x310030_g_AfterBroadCastNum then
			YX_LOULAN_BROADCAST_NUM5 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LOULAN_BROADCAST_NUM5 )
		x310030_ShowMessage1(sceneId,message)
		YX_LOULAN_BROADCAST_NUM5 = YX_LOULAN_BROADCAST_NUM5 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_LOULAN_SCENE_ID6 then
		if YX_LOULAN_BROADCAST_NUM6 == x310030_g_AfterBroadCastNum then
			YX_LOULAN_BROADCAST_NUM6 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LOULAN_BROADCAST_NUM6 )
		x310030_ShowMessage1(sceneId,message)
		YX_LOULAN_BROADCAST_NUM6 = YX_LOULAN_BROADCAST_NUM6 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_LOULAN_SCENE_ID7 then
		if YX_LOULAN_BROADCAST_NUM7 == x310030_g_AfterBroadCastNum then
			YX_LOULAN_BROADCAST_NUM7 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LOULAN_BROADCAST_NUM7 )
		x310030_ShowMessage1(sceneId,message)
		YX_LOULAN_BROADCAST_NUM7 = YX_LOULAN_BROADCAST_NUM7 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
    elseif sceneId == YX_LOULAN_SCENE_ID8 then
		if YX_LOULAN_BROADCAST_NUM8 == x310030_g_AfterBroadCastNum then
			YX_LOULAN_BROADCAST_NUM8 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LOULAN_BROADCAST_NUM8 )
		x310030_ShowMessage1(sceneId,message)
		YX_LOULAN_BROADCAST_NUM8 = YX_LOULAN_BROADCAST_NUM8 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
    elseif sceneId == YX_LOULAN_SCENE_ID9 then
		if YX_LOULAN_BROADCAST_NUM9 == x310030_g_AfterBroadCastNum then
			YX_LOULAN_BROADCAST_NUM9 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LOULAN_BROADCAST_NUM9 )
		x310030_ShowMessage1(sceneId,message)
		YX_LOULAN_BROADCAST_NUM9 = YX_LOULAN_BROADCAST_NUM9 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始		

	elseif sceneId == YX_LAIYIN_SCENE_ID1 then
		if YX_LAIYIN_BROADCAST_NUM1 == x310030_g_AfterBroadCastNum then
			YX_LAIYIN_BROADCAST_NUM1 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LAIYIN_BROADCAST_NUM1 )
		x310030_ShowMessage1(sceneId,message)
		YX_LAIYIN_BROADCAST_NUM1 = YX_LAIYIN_BROADCAST_NUM1 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_LAIYIN_SCENE_ID2 then
		if YX_LAIYIN_BROADCAST_NUM2 == x310030_g_AfterBroadCastNum then
			YX_LAIYIN_BROADCAST_NUM2 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LAIYIN_BROADCAST_NUM2 )
		x310030_ShowMessage1(sceneId,message)
		YX_LAIYIN_BROADCAST_NUM2 = YX_LAIYIN_BROADCAST_NUM2 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_LAIYIN_SCENE_ID3 then
		if YX_LAIYIN_BROADCAST_NUM3 == x310030_g_AfterBroadCastNum then
			YX_LAIYIN_BROADCAST_NUM3 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LAIYIN_BROADCAST_NUM3 )
		x310030_ShowMessage1(sceneId,message)
		YX_LAIYIN_BROADCAST_NUM3 = YX_LAIYIN_BROADCAST_NUM3 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_LAIYIN_SCENE_ID4 then
		if YX_LAIYIN_BROADCAST_NUM4 == x310030_g_AfterBroadCastNum then
			YX_LAIYIN_BROADCAST_NUM4 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LAIYIN_BROADCAST_NUM4 )
		x310030_ShowMessage1(sceneId,message)
		YX_LAIYIN_BROADCAST_NUM4 = YX_LAIYIN_BROADCAST_NUM4 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始

	elseif sceneId == YX_LAIYIN_SCENE_ID5 then
		if YX_LAIYIN_BROADCAST_NUM5 == x310030_g_AfterBroadCastNum then
			YX_LAIYIN_BROADCAST_NUM5 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LAIYIN_BROADCAST_NUM5 )
		x310030_ShowMessage1(sceneId,message)
		YX_LAIYIN_BROADCAST_NUM5 = YX_LAIYIN_BROADCAST_NUM5 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_LAIYIN_SCENE_ID6 then
		if YX_LAIYIN_BROADCAST_NUM6 == x310030_g_AfterBroadCastNum then
			YX_LAIYIN_BROADCAST_NUM6 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LAIYIN_BROADCAST_NUM6 )
		x310030_ShowMessage1(sceneId,message)
		YX_LAIYIN_BROADCAST_NUM6 = YX_LAIYIN_BROADCAST_NUM6 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_LAIYIN_SCENE_ID7 then
		if YX_LAIYIN_BROADCAST_NUM7 == x310030_g_AfterBroadCastNum then
			YX_LAIYIN_BROADCAST_NUM7 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LAIYIN_BROADCAST_NUM7 )
		x310030_ShowMessage1(sceneId,message)
		YX_LAIYIN_BROADCAST_NUM7 = YX_LAIYIN_BROADCAST_NUM7 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_LAIYIN_SCENE_ID8 then
		if YX_LAIYIN_BROADCAST_NUM8 == x310030_g_AfterBroadCastNum then
			YX_LAIYIN_BROADCAST_NUM8 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LAIYIN_BROADCAST_NUM8 )
		x310030_ShowMessage1(sceneId,message)
		YX_LAIYIN_BROADCAST_NUM8 = YX_LAIYIN_BROADCAST_NUM8 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_LAIYIN_SCENE_ID9 then
		if YX_LAIYIN_BROADCAST_NUM9 == x310030_g_AfterBroadCastNum then
			YX_LAIYIN_BROADCAST_NUM9 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_LAIYIN_BROADCAST_NUM9 )
		x310030_ShowMessage1(sceneId,message)
		YX_LAIYIN_BROADCAST_NUM9 = YX_LAIYIN_BROADCAST_NUM9 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始		

	elseif sceneId == YX_KUNLUN_SCENE_ID1 then
		if YX_KUNLUN_BROADCAST_NUM1 == x310030_g_AfterBroadCastNum then
			YX_KUNLUN_BROADCAST_NUM1 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_KUNLUN_BROADCAST_NUM1 )
		x310030_ShowMessage1(sceneId,message)
		YX_KUNLUN_BROADCAST_NUM1 = YX_KUNLUN_BROADCAST_NUM1 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_KUNLUN_SCENE_ID2 then
		if YX_KUNLUN_BROADCAST_NUM2 == x310030_g_AfterBroadCastNum then
			YX_KUNLUN_BROADCAST_NUM2 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_KUNLUN_BROADCAST_NUM2 )
		x310030_ShowMessage1(sceneId,message)
		YX_KUNLUN_BROADCAST_NUM2 = YX_KUNLUN_BROADCAST_NUM2 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_KUNLUN_SCENE_ID3 then
		if YX_KUNLUN_BROADCAST_NUM3 == x310030_g_AfterBroadCastNum then
			YX_KUNLUN_BROADCAST_NUM3 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_KUNLUN_BROADCAST_NUM3 )
		x310030_ShowMessage1(sceneId,message)
		YX_KUNLUN_BROADCAST_NUM3 = YX_KUNLUN_BROADCAST_NUM3 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_KUNLUN_SCENE_ID4 then
		if YX_KUNLUN_BROADCAST_NUM4 == x310030_g_AfterBroadCastNum then
			YX_KUNLUN_BROADCAST_NUM4 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_KUNLUN_BROADCAST_NUM4 )
		x310030_ShowMessage1(sceneId,message)
		YX_KUNLUN_BROADCAST_NUM4 = YX_KUNLUN_BROADCAST_NUM4 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始

	elseif sceneId == YX_KUNLUN_SCENE_ID5 then
		if YX_KUNLUN_BROADCAST_NUM5 == x310030_g_AfterBroadCastNum then
			YX_KUNLUN_BROADCAST_NUM5 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_KUNLUN_BROADCAST_NUM5 )
		x310030_ShowMessage1(sceneId,message)
		YX_KUNLUN_BROADCAST_NUM5 = YX_KUNLUN_BROADCAST_NUM5 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_KUNLUN_SCENE_ID6 then
		if YX_KUNLUN_BROADCAST_NUM6 == x310030_g_AfterBroadCastNum then
			YX_KUNLUN_BROADCAST_NUM6 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_KUNLUN_BROADCAST_NUM6 )
		x310030_ShowMessage1(sceneId,message)
		YX_KUNLUN_BROADCAST_NUM6 = YX_KUNLUN_BROADCAST_NUM6 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_KUNLUN_SCENE_ID7 then
		if YX_KUNLUN_BROADCAST_NUM7 == x310030_g_AfterBroadCastNum then
			YX_KUNLUN_BROADCAST_NUM7 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_KUNLUN_BROADCAST_NUM7 )
		x310030_ShowMessage1(sceneId,message)
		YX_KUNLUN_BROADCAST_NUM7 = YX_KUNLUN_BROADCAST_NUM7 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_KUNLUN_SCENE_ID8 then
		if YX_KUNLUN_BROADCAST_NUM8 == x310030_g_AfterBroadCastNum then
			YX_KUNLUN_BROADCAST_NUM8 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_KUNLUN_BROADCAST_NUM8 )
		x310030_ShowMessage1(sceneId,message)
		YX_KUNLUN_BROADCAST_NUM8 = YX_KUNLUN_BROADCAST_NUM8 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_KUNLUN_SCENE_ID9 then
		if YX_KUNLUN_BROADCAST_NUM9 == x310030_g_AfterBroadCastNum then
			YX_KUNLUN_BROADCAST_NUM9 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_KUNLUN_BROADCAST_NUM9 )
		x310030_ShowMessage1(sceneId,message)
		YX_KUNLUN_BROADCAST_NUM9 = YX_KUNLUN_BROADCAST_NUM9 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始		

	elseif sceneId == YX_DUNHUANG_SCENE_ID1 then
		if YX_DUNHUANG_BROADCAST_NUM1 == x310030_g_AfterBroadCastNum then
			YX_DUNHUANG_BROADCAST_NUM1 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_DUNHUANG_BROADCAST_NUM1 )
		x310030_ShowMessage1(sceneId,message)
		YX_DUNHUANG_BROADCAST_NUM1 = YX_DUNHUANG_BROADCAST_NUM1 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_DUNHUANG_SCENE_ID2 then
		if YX_DUNHUANG_BROADCAST_NUM2 == x310030_g_AfterBroadCastNum then
			YX_DUNHUANG_BROADCAST_NUM2 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_DUNHUANG_BROADCAST_NUM2 )
		x310030_ShowMessage1(sceneId,message)
		YX_DUNHUANG_BROADCAST_NUM2 = YX_DUNHUANG_BROADCAST_NUM2 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_DUNHUANG_SCENE_ID3 then
		if YX_DUNHUANG_BROADCAST_NUM3 == x310030_g_AfterBroadCastNum then
			YX_DUNHUANG_BROADCAST_NUM3 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_DUNHUANG_BROADCAST_NUM3 )
		x310030_ShowMessage1(sceneId,message)
		YX_DUNHUANG_BROADCAST_NUM3 = YX_DUNHUANG_BROADCAST_NUM3 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_DUNHUANG_SCENE_ID4 then
		if YX_DUNHUANG_BROADCAST_NUM4 == x310030_g_AfterBroadCastNum then
			YX_DUNHUANG_BROADCAST_NUM4 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_DUNHUANG_BROADCAST_NUM4 )
		x310030_ShowMessage1(sceneId,message)
		YX_DUNHUANG_BROADCAST_NUM4 = YX_DUNHUANG_BROADCAST_NUM4 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始

	elseif sceneId == YX_DUNHUANG_SCENE_ID5 then
		if YX_DUNHUANG_BROADCAST_NUM5 == x310030_g_AfterBroadCastNum then
			YX_DUNHUANG_BROADCAST_NUM5 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_DUNHUANG_BROADCAST_NUM5 )
		x310030_ShowMessage1(sceneId,message)
		YX_DUNHUANG_BROADCAST_NUM5 = YX_DUNHUANG_BROADCAST_NUM5 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_DUNHUANG_SCENE_ID6 then
		if YX_DUNHUANG_BROADCAST_NUM6 == x310030_g_AfterBroadCastNum then
			YX_DUNHUANG_BROADCAST_NUM6 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_DUNHUANG_BROADCAST_NUM6 )
		x310030_ShowMessage1(sceneId,message)
		YX_DUNHUANG_BROADCAST_NUM6 = YX_DUNHUANG_BROADCAST_NUM6 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_DUNHUANG_SCENE_ID7 then
		if YX_DUNHUANG_BROADCAST_NUM7 == x310030_g_AfterBroadCastNum then
			YX_DUNHUANG_BROADCAST_NUM7 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_DUNHUANG_BROADCAST_NUM7 )
		x310030_ShowMessage1(sceneId,message)
		YX_DUNHUANG_BROADCAST_NUM7 = YX_DUNHUANG_BROADCAST_NUM7 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_DUNHUANG_SCENE_ID8 then
		if YX_DUNHUANG_BROADCAST_NUM8 == x310030_g_AfterBroadCastNum then
			YX_DUNHUANG_BROADCAST_NUM8 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_DUNHUANG_BROADCAST_NUM8 )
		x310030_ShowMessage1(sceneId,message)
		YX_DUNHUANG_BROADCAST_NUM8 = YX_DUNHUANG_BROADCAST_NUM8 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始
	elseif sceneId == YX_DUNHUANG_SCENE_ID9 then
		if YX_DUNHUANG_BROADCAST_NUM9 == x310030_g_AfterBroadCastNum then
			YX_DUNHUANG_BROADCAST_NUM9 = 0
			CallScriptFunction( 310032, "KickHuman", sceneId, actId, uTime)
			return 
		end
		local message = format( x310030_str_end, x310030_g_AfterBroadCastNum-YX_DUNHUANG_BROADCAST_NUM9 )
		x310030_ShowMessage1(sceneId,message)
		YX_DUNHUANG_BROADCAST_NUM9 = YX_DUNHUANG_BROADCAST_NUM9 + 1
		SetSystemTimerTick( sceneId, x310030_g_ScriptId, "BroadCastAfter", actId, 60*1000  ) --1分钟后开始		
		
	end
end