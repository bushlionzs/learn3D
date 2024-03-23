
x800100_g_ScriptId = 800100
x800100_g_MissionName = "加密算法管理模块"



--点击（NPC）
function x800100_ProcEnumEvent( sceneId, selfId, targetId, MissionId )	
end



--点击（按钮）点击该任务后执行此脚本
function x800100_ProcEventEntry( sceneId, selfId, targetId,state,index )	
end


--加密管理模块：
--功能：1。生成并发送新的加密算法		
function x800100_OnEncryptManager( sceneId, selfId, enctyptId )	
	
	local answer = x800100_CheckLoginAnswer( sceneId, selfId )	

	if answer == 0 then		--登陆答案错误	
		
		local bValid,nErrorCount,nOPMode = GetCheatActTableInfo( sceneId, selfId,9 )
		
		if bValid == 0 then
			--功能关闭
			return 1
		end
		
		if nOPMode == 2 then		--踢掉
			x800100_MakeKickTime( sceneId, selfId )				
		elseif nOPMode == 3 then	--答题
			x800100_DoLoginAnswer( sceneId, selfId )	
		end

		SetLoginAnswer(sceneId, selfId,3)		--避免重复处理
		return 1
	elseif answer == 1 or answer == 2 then
		--解码结果错误或超时
		local bValid,nErrorCount,nOPMode = GetCheatActTableInfo( sceneId, selfId,0 )
		
		if bValid == 0 then
			--功能关闭
			return 1
		end
				
		if nOPMode == 2 then		--踢掉
			x800100_MakeKickTime( sceneId, selfId )				
		elseif nOPMode == 3 then	--答题
			x800100_DoLoginAnswer( sceneId, selfId )	
		end
		return 1
	end

	local encryptCount = GetPlayerRuntimeData( sceneId, selfId, RD_CURR_ENCRYPT_COUNT )

	if encryptCount == 0 then
		SetPlayerRuntimeData( sceneId, selfId, RD_LAST_ENCRYPT_INDEX, -1 )
	end

	if encryptCount == 0 or encryptCount >= 5 then

		--每5分钟产生一个新索引
		SetPlayerRuntimeData( sceneId, selfId, RD_CURR_ENCRYPT_COUNT, 0 )
		local currIndex = GetPlayerRuntimeData( sceneId, selfId, RD_CURR_ENCRYPT_INDEX )
		SetPlayerRuntimeData( sceneId, selfId, RD_LAST_ENCRYPT_INDEX, currIndex )
		SetPlayerRuntimeData( sceneId, selfId, RD_CURR_ENCRYPT_INDEX, enctyptId )
		encryptCount = 0

	end

	SetPlayerRuntimeData( sceneId, selfId, RD_CURR_ENCRYPT_COUNT, encryptCount+1 )
	
	--计算客户端未响应时间，如果未响应超过5分钟，则踢掉该玩家
	local unrespondCount = GetPlayerRuntimeData( sceneId, selfId, RD_ENCRYPT_UNRESPOND_TIME )
	if unrespondCount >= 5 then
		--返回踢人
		return 0
	end

	SetPlayerRuntimeData( sceneId, selfId, RD_ENCRYPT_UNRESPOND_TIME, unrespondCount+1 )

	--根据Id得到当前加密信息
	local currIndex = GetPlayerRuntimeData( sceneId, selfId, RD_CURR_ENCRYPT_INDEX )
	local scriptId,result,fnName = GetEncryptInfo( sceneId, selfId ,currIndex )

	--每分钟发送一次加密算法
	CallScriptFunction( scriptId, fnName, sceneId, selfId ,currIndex )

	return 1
	
end


--检查登陆时的验证结果
--返回值：	0。登陆答案错误	，继续答题（仍然错误则踢掉）
--			1。解码结果错误，踢掉	
--			2。解码超时，可能是外挂在反调试。踢掉
--			3。成功
function x800100_CheckLoginAnswer( sceneId, selfId )	
	
	local answer = GetLoginAnswer(sceneId, selfId)
	return answer

end


--登陆时答题错误，进入游戏后再次答题
function x800100_DoLoginAnswer( sceneId, selfId )	
	
	if GetGameOpenById(1020)>0 then

		if CallScriptFunction(300824, "StartDati", sceneId, selfId, 1020)>0 then
		end
		
	end

end

function x800100_OnDatiSuccess(sceneId,selfId)
end

function x800100_OnDatiFail(sceneId,selfId)
end


--检查客户端加密结果
--先检查当前加密算法，如果失败并且在容错时间内则检查与上次加密算法是否匹配
function x800100_OnCheckEncrypt( sceneId, selfId, result )	
	
	local currIndex = GetPlayerRuntimeData( sceneId, selfId, RD_CURR_ENCRYPT_INDEX )
	local scriptId,tabResult,fnName = GetEncryptInfo( sceneId, selfId ,currIndex )

	if result == tabResult then

		--验证通过，重计客户端响应时间
		SetPlayerRuntimeData( sceneId, selfId, RD_ENCRYPT_UNRESPOND_TIME, 0 )
		return 1

	else

		local lastIndex = GetPlayerRuntimeData( sceneId, selfId, RD_LAST_ENCRYPT_INDEX )	
		if lastIndex ~= -1 then
			local scriptId2,tabResult2,fnName2 = GetEncryptInfo( sceneId, selfId ,lastIndex )
			if result == tabResult2 then
				--验证通过，重计客户端响应时间
				SetPlayerRuntimeData( sceneId, selfId, RD_ENCRYPT_UNRESPOND_TIME, 0 )
				return 1
			end
		end

	end

	--加密验证失败，踢人
	return 0

end


--产生踢人时间
function x800100_MakeKickTime( sceneId, selfId )	
	
	local kickTime = GetEncryptKickTime(sceneId, selfId)

	if kickTime ~= NumberCastIntToUInt(-1) then
		--已处于被踢状态
		return 
	end

	--倒计时为30--120秒
	kickTime = mod(600,2400)
	SetEncryptKickTime(sceneId, selfId,kickTime)

end
