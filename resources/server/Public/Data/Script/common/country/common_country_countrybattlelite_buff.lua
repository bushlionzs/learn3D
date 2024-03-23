
x310156_g_ScriptId = 310156
x310156_g_BufId  = {8719,8720,8721,8722,8723,8724,8725,8726,8727}


----------------------------------------------------------
--删除BUF
----------------------------------------------------------
function x310156_CancelBuf( sceneId,selfId )
	
	for i,item in x310156_g_BufId do
		if IsHaveSpecificImpact(sceneId,selfId,item) == 1 then
			CancelSpecificImpact(sceneId,selfId,item)
		end
	end
end

----------------------------------------------------------
--间隔发作时调用
----------------------------------------------------------
function x310156_OnIntervalOverEvent( sceneId, selfId)
	
	
	
	--场景无效
	if sceneId ~= 50 and sceneId ~= 150 and sceneId ~= 250 and sceneId ~= 350 and
	   sceneId ~= 51 and sceneId ~= 151 and sceneId ~= 251 and sceneId ~= 351 and
	   sceneId ~= 58 and sceneId ~= 158 and sceneId ~= 258 and sceneId ~= 358 and
	   sceneId ~= 68 and sceneId ~= 168 and sceneId ~= 268 and sceneId ~= 368 and
	   sceneId ~= 76 and sceneId ~= 176 and sceneId ~= 276 and sceneId ~= 376 and 
	   sceneId ~= 86 and sceneId ~= 186 and sceneId ~= 286 and sceneId ~= 386 and 
	   sceneId ~= 104 and sceneId ~= 204 and sceneId ~= 304 and sceneId ~= 404 and 
	   sceneId ~= 105 and sceneId ~= 205 and sceneId ~= 305 and sceneId ~= 405 and 
	   sceneId ~= 106 and sceneId ~= 206 and sceneId ~= 306 and sceneId ~= 406 and 
	   sceneId ~= 107 and sceneId ~= 207 and sceneId ~= 307 and sceneId ~= 407 and 
	   sceneId ~= 108 and sceneId ~= 208 and sceneId ~= 308 and sceneId ~= 408 and 
	   sceneId ~= 109 and sceneId ~= 209 and sceneId ~= 309 and sceneId ~= 409 and 
	   sceneId ~= 110 and sceneId ~= 210 and sceneId ~= 310 and sceneId ~= 410 and 
	   sceneId ~= 111 and sceneId ~= 211 and sceneId ~= 311 and sceneId ~= 411 and 
	   sceneId ~= 91 and sceneId ~= 191 and sceneId ~= 291 and sceneId ~= 391 and sceneId ~= 3 then
	   
	   x310156_CancelBuf( sceneId,selfId )
	   return
		
	end
	
	--已经结束
	if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"IsBattleFinished",sceneId,selfId) == 1 then
		
		x310156_CancelBuf( sceneId,selfId )
	   	return
	end	
end


----------------------------------------------------------
--生效时调用
----------------------------------------------------------
function x310156_OnActiveEvent( sceneId, selfId )
end

----------------------------------------------------------
--效果消散时调用
----------------------------------------------------------
function x310156_OnFadeOutEvent( sceneId, selfId )
end

----------------------------------------------------------
--事件交互入口
----------------------------------------------------------
function x310156_ProcEventEntry( sceneId, selfId, bagIndex)
end