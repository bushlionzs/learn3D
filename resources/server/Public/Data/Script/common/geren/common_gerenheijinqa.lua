
x300824_g_ScriptId	= 300824

x300824_g_DatiGameIdList = {1016,1018,1020}
x300824_g_DatiMDList = {
							{ MD_FUBEN_ENTERTICK,MD_FUBEN_DATISTEP},
							{ MD_HEIJIN_ENTERTICK,MD_HEIJIN_DATISTEP},
							{ MD_LOGIN_ANSWER_ENTERTICK,MD_LOGIN_ANSWER_DATISTEP}
						}

function x300824_GetDatiMDByGameId(nGameId)

	local nIndex =0;
	
	for i,item in x300824_g_DatiGameIdList do
		nIndex = nIndex +1
		if nGameId==item then
			return x300824_g_DatiMDList[nIndex][1],x300824_g_DatiMDList[nIndex][2]
		end
	end

	return -1,-1,-1
end

------------------------------------------------
-- buff start 
-------------------------------------------------
--间隔发作时调用
function x300824_OnIntervalOverEvent( sceneId, selfId )
	
		
	
	local nActiveGameId = GetQuestData(sceneId, selfId, MD_DATI_ACTIVE_ID[1], MD_DATI_ACTIVE_ID[2], MD_DATI_ACTIVE_ID[3])

	if nActiveGameId==0 then
		return
	end

	if GetGameOpenById(nActiveGameId)<=0 then
		return
	end
	
	
	local bJishi = GetQuestData(sceneId, selfId, MD_DATI_JISHI_KAIGUAN[1], MD_DATI_JISHI_KAIGUAN[2], MD_DATI_JISHI_KAIGUAN[3])
	
	if bJishi<=0 then
		return
	end


	local md_entertick,md_step = x300824_GetDatiMDByGameId(nActiveGameId)

	


		
	local nHumanEnterTick = GetQuestData(sceneId, selfId, md_entertick[1], md_entertick[2], md_entertick[3])+1
	
	

	SetQuestData(sceneId, selfId, md_entertick[1], md_entertick[2], md_entertick[3], nHumanEnterTick)

	if nHumanEnterTick>=40 then  --200秒
		OnFubenDatiNoAnswer(sceneId, selfId,nActiveGameId)
	end
	
	
		
	
end

--生效时调用
function x300824_OnActiveEvent( sceneId, selfId )

end

--效果消散时调用
function x300824_OnFadeOutEvent( sceneId, selfId )

	
end

function x300824_ProcEventEntry()
end

------------------------------------------------
-- buff end 
-------------------------------------------------





----------------------------------------------------------------------------------------------------------------------------
----防外挂答题开始
----------------------------------------------------------------------------------------------------------------------------

function x300824_StartDati(sceneId, selfId, nGameId)
	if GetGameOpenById(nGameId)<=0 then
		return 0
	end

	
    if IsPlayerStateNormal(sceneId,selfId ) <= 0 then
        return 0
    end

    
    if IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_DIE )> 0 then
    		BeginQuestEvent(sceneId);
					AddQuestText(sceneId,"死亡状态不能答题");
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
        return 0
    end

	local bCanJump =  x300824_IsJumpWaiguaDati(sceneId, selfId, nGameId)

	if bCanJump>0 then
		return 1
	end

	
	local md_entertick,md_step = x300824_GetDatiMDByGameId(nGameId)

	
	
	local nCurrentTick = GetQuestData(sceneId, selfId, md_entertick[1], md_entertick[2], md_entertick[3])

			
	StartFubenDati(sceneId, selfId, (200-nCurrentTick*5), nGameId,1,0)  --告诉客户端答题

	SetQuestData(sceneId, selfId, MD_DATI_ACTIVE_ID[1], MD_DATI_ACTIVE_ID[2], MD_DATI_ACTIVE_ID[3], nGameId)
			
	SetQuestData(sceneId, selfId, MD_DATI_JISHI_KAIGUAN[1], MD_DATI_JISHI_KAIGUAN[2], MD_DATI_JISHI_KAIGUAN[3], 0)
	SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId, 8713,0 )  --给玩家加buff计时

	return 2	
	
end

function x300824_CloseDatiOnServer(sceneId, selfId, nGameId)
	
	SetQuestData(sceneId, selfId, MD_DATI_ACTIVE_ID[1], MD_DATI_ACTIVE_ID[2], MD_DATI_ACTIVE_ID[3], 0)
	SetQuestData(sceneId, selfId, MD_DATI_JISHI_KAIGUAN[1], MD_DATI_JISHI_KAIGUAN[2], MD_DATI_JISHI_KAIGUAN[3],0)
	CancelSpecificImpact(sceneId, selfId, 8713);

    -- 清除答题互斥状态
    SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_BLACKGOLD, 0)

	local md_entertick,md_step = x300824_GetDatiMDByGameId(nGameId)

	SetQuestData(sceneId, selfId, md_entertick[1], md_entertick[2], md_entertick[3], 0)
	SetQuestData(sceneId, selfId, md_step[1], md_step[2], md_step[3], 0)

	CancelSpecificImpact(sceneId, selfId, 9825);

end


--判断是否需要防外挂答题
function x300824_IsJumpWaiguaDati(sceneId, selfId, nGameId)
	if GetGameOpenById(nGameId)<=0 then
		return -1
	end

	local sceneType = GetSceneType(sceneId) ;
	if nGameId==1016 then
		if sceneType~=1 then
			return -1
		end
	end

	
	local bufflist = {9011,9012,9013}

	for i,item in bufflist do
		local bHaveImpact = IsHaveSpecificImpact( sceneId, selfId, item )

		if bHaveImpact>0 then
			return 1;
		end
	end

	
	return 0
end

--防外挂中途使用物品解除答题状态

function x300824_CancelWaiguaDati(sceneId, selfId)
	
	if IsPlayerStateNormal(sceneId,selfId ) <= 0 then
		return
	end

	local nActiveGameId = GetQuestData(sceneId, selfId, MD_DATI_ACTIVE_ID[1], MD_DATI_ACTIVE_ID[2], MD_DATI_ACTIVE_ID[3])

	if nActiveGameId==0 then
		return
	end

	if GetGameOpenById(nActiveGameId)<=0 then
		return
	end

	local sceneType = GetSceneType(sceneId) ;
	if nActiveGameId==1016 then
		if sceneType~=1 then
			return
		end
	end

	
	CancelSpecificImpact(sceneId, selfId, 8713);
	
	x300824_CloseDatiOnServer(sceneId, selfId, nActiveGameId)

	--StartFubenDati(sceneId, selfId, 0, 0,2)  --告诉客户端关闭答题状态

	
			
	
	
end


--回答副本答题
function x300824_OnAnswerFubenDati(sceneId, selfId, nGameId)
	
	

	

	if IsPlayerStateNormal(sceneId,selfId ) <= 0 then
		return
	end

	local nActiveGameId = GetQuestData(sceneId, selfId, MD_DATI_ACTIVE_ID[1], MD_DATI_ACTIVE_ID[2], MD_DATI_ACTIVE_ID[3])

	if nActiveGameId==0 then
		return
	end

	if GetGameOpenById(nActiveGameId)<=0 then
		return
	end

	if nGameId~=nActiveGameId then
		return
	end

	local sceneType = GetSceneType(sceneId) ;
	if nGameId==1016 then
		if sceneType~=1 then
			return
		end
	end

	
	
	local countryId = GetCurCountry( sceneId, selfId)
	if nActiveGameId == 1016 then --场景类型必须是副本
		
		
		SetQuestData(sceneId, selfId, MD_FUBEN_DATI[1], MD_FUBEN_DATI[2], MD_FUBEN_DATI[3],0)
		AddExp(sceneId, selfId,500)  --奖励

		
		
	elseif nActiveGameId == 1018 then

		
		if countryId == 0 then
			CallScriptFunction(300757, "OnHeiJinDatiSuccess", sceneId, selfId);
		end
		
		if countryId == 1 then
			CallScriptFunction(300863, "OnHeiJinDatiSuccess", sceneId, selfId);
		end
		
		if countryId == 2 then
			CallScriptFunction(300862, "OnHeiJinDatiSuccess", sceneId, selfId);
		end
		
		if countryId == 3 then
			CallScriptFunction(300861, "OnHeiJinDatiSuccess", sceneId, selfId);
		end

		
	elseif nActiveGameId == 1020 then
		CallScriptFunction(800100, "OnDatiSuccess", sceneId, selfId);
	end
	
	x300824_CloseDatiOnServer(sceneId, selfId, nGameId)
			
	

end

--根据副本答题规则将答题错误者投入监狱 
function x300824_FubenEnterPrison(sceneId, selfId, nGameId, nMode)
	
	
	if IsPlayerStateNormal(sceneId,selfId ) <= 0 then
		return
	end

	local nActiveGameId = GetQuestData(sceneId, selfId, MD_DATI_ACTIVE_ID[1], MD_DATI_ACTIVE_ID[2], MD_DATI_ACTIVE_ID[3])

	if nActiveGameId==0 then
		return
	end

	if GetGameOpenById(nActiveGameId)<=0 then
		return
	end

	if nGameId~=nActiveGameId then
		return
	end

	local sceneType = GetSceneType(sceneId) ;
	if nGameId==1016 then
		if sceneType~=1 then
			return
		end
	end

	if nMode ==1 then  --如果是答错引起


		local md_entertick,md_step = x300824_GetDatiMDByGameId(nGameId)
		

		
		local nStep = GetQuestData(sceneId, selfId, md_step[1], md_step[2], md_step[3])+1
		SetQuestData(sceneId, selfId, md_step[1], md_step[2], md_step[3],nStep)
		if nStep<5 then
			local nCurrentTick = GetQuestData(sceneId, selfId, md_entertick[1], md_entertick[2], md_entertick[3])
			StartFubenDati(sceneId, selfId, 200-nCurrentTick*5, nActiveGameId,0,nStep)
			
			return
		end
		
	end

	
	

	x300824_CloseDatiOnServer(sceneId, selfId, nGameId)
	
	local countryId = GetCurCountry( sceneId, selfId)
	if nGameId == 1016 then
		CallScriptFunction(700012, "OnDatiFail", sceneId, selfId)
	elseif nActiveGameId == 1018 then
		if countryId == 0 then
			CallScriptFunction(300757, "OnDatiFail", sceneId, selfId);
		end
		if countryId == 1 then
			CallScriptFunction(300863, "OnDatiFail", sceneId, selfId);
		end
		if countryId == 2 then
			CallScriptFunction(300862, "OnDatiFail", sceneId, selfId);
		end
		if countryId == 3 then
			CallScriptFunction(300861, "OnDatiFail", sceneId, selfId);
		end
	elseif 	nActiveGameId == 1020 then
		CallScriptFunction(800100, "OnDatiFail", sceneId, selfId);
	end
	
	

	--写日志
	
	local msg = "Dati failed:"..GetName(sceneId, selfId)..","..GetPlayerGUID( sceneId,selfId )..","..nGameId
	WriteLog(1,msg)
	
end



function x300824_SaveEncryptArith(sceneId, selfId, nIndex,nValue)
	if nIndex== nil then
		return
	end

	if nIndex==0 then
		SetQuestData(sceneId, selfId, MD_ENCRYPT_ARITH1[1], MD_ENCRYPT_ARITH1[2], MD_ENCRYPT_ARITH1[3],nValue) 
	elseif nIndex==1 then
		SetQuestData(sceneId, selfId, MD_ENCRYPT_ARITH2[1], MD_ENCRYPT_ARITH2[2], MD_ENCRYPT_ARITH2[3],nValue) 
	elseif nIndex==2 then
		SetQuestData(sceneId, selfId, MD_ENCRYPT_ARITH3[1], MD_ENCRYPT_ARITH3[2], MD_ENCRYPT_ARITH3[3],nValue) 
	end
end

function x300824_SaveDatiResult(sceneId, selfId, nResult)

	if nResult==nil then
		return
	end

	if nResult<0 or nResult>5 then
		return
	end

	SetQuestData(sceneId, selfId, MD_DATI_RESULT[1], MD_DATI_RESULT[2], MD_DATI_RESULT[3],nResult) 
end


function x300824_GetEncryptArith(sceneId, selfId, nIndex)
	if nIndex== nil then
		return -1;
	end

	if IsPlayerStateNormal(sceneId,selfId ) <= 0 then
		return -1;
	end
	
	if nIndex==0 then
		return GetQuestData(sceneId, selfId, MD_ENCRYPT_ARITH1[1], MD_ENCRYPT_ARITH1[2], MD_ENCRYPT_ARITH1[3]) 
	elseif nIndex==1 then
		return GetQuestData(sceneId, selfId, MD_ENCRYPT_ARITH2[1], MD_ENCRYPT_ARITH2[2], MD_ENCRYPT_ARITH2[3]) 
	elseif nIndex==2 then
		return GetQuestData(sceneId, selfId, MD_ENCRYPT_ARITH3[1], MD_ENCRYPT_ARITH3[2], MD_ENCRYPT_ARITH3[3]) 
	else
		return -1;
	end

end

function x300824_GetDatiResult(sceneId, selfId)

	if IsPlayerStateNormal(sceneId,selfId ) <= 0 then
		return -1;
	end

	return GetQuestData(sceneId, selfId, MD_DATI_RESULT[1], MD_DATI_RESULT[2], MD_DATI_RESULT[3]) 
end

function x300824_OnClientGetDati(sceneId, selfId, nGameId)

	local nActiveGameId = GetQuestData(sceneId, selfId, MD_DATI_ACTIVE_ID[1], MD_DATI_ACTIVE_ID[2], MD_DATI_ACTIVE_ID[3])

	if nActiveGameId==0 then
		return
	end

	

	if GetGameOpenById(nActiveGameId)<=0 then
		return
	end

	if nActiveGameId~=nGameId then
		return
	end

	local bJishi = GetQuestData(sceneId, selfId, MD_DATI_JISHI_KAIGUAN[1], MD_DATI_JISHI_KAIGUAN[2], MD_DATI_JISHI_KAIGUAN[3])
	
	if bJishi>0 then
		return
	end


	SetQuestData(sceneId, selfId, MD_DATI_JISHI_KAIGUAN[1], MD_DATI_JISHI_KAIGUAN[2], MD_DATI_JISHI_KAIGUAN[3], 1)  --服务器开始计时

    SetPlayerMutexState( sceneId, selfId, PLAYER_STATE_BLACKGOLD, 1)

	SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId, 9825,0 ) --加定身无敌buff

end







----------------------------------------------------------------------------------------------------------------------------
----防外挂答题结束
----------------------------------------------------------------------------------------------------------------------------