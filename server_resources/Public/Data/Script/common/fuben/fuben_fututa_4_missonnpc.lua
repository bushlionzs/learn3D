-------------------------------------------------
-- fututa_4: 
-------------------------------------------------
x700044_CSP_CURRENTSTEP		=	23--x700022_CSP_CURRENTSTEP	
x700044_CSP_FUBENLEVEL	=	9--x700022_CSP_FUBENLEVEL
x700044_CSP_FUBENLEVEL_DUP	=	27--x700044_CSP_FUBENLEVEL_DUP


x700044_CSP_HUMAN_TALKPARAM_START	=	230--x700022_CSP_HUMAN_TALKPARAM_START
x700044_CSP_GUID_START              =   248


x700044_g_LevelMin					=   20                      --进入最低等级
x700044_g_LevelMax					=   100                     --进入最高等级

x700044_g_ScriptId = 700044


x700044_Fuben_ScriptId = 700022

function x700044_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
	
	if which==1 then	
		x700044_DispatchUpgrade( sceneId, selfId, NPCId,which ) --增加难度
	elseif which==2 then
		x700044_DispatchDegrade( sceneId, selfId, NPCId,which )	--降低难度
	end
	
end


--**********************************

--列举事件

--**********************************

function x700044_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

	local nCurrentLevel = GetFubenData_Param(sceneId,x700044_CSP_FUBENLEVEL)
	local nStdLevel = GetFubenData_Param(sceneId,x700044_CSP_FUBENLEVEL_DUP)

	
	if nCurrentLevel< (nStdLevel+5) then
		AddQuestNumText(sceneId, x700044_g_ScriptId, "增加难度",0,1)
	end

	if nCurrentLevel> (nStdLevel-5) then
		AddQuestNumText(sceneId, x700044_g_ScriptId, "降低难度",0,2)
	end


	
	
	
		
end


---------------------------------------------------------------------------------------------------
--进入副本文字显示
---------------------------------------------------------------------------------------------------
function x700044_DispatchUpgrade( sceneId, selfId, NPCId, nParam )

	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId,"#Y增加难度")
		AddQuestText(sceneId,"怪物等级增加5")
		--AddQuestText(sceneId," ")

		


	EndQuestEvent()


	
	local myGuid = GetPlayerGUID( sceneId,selfId )
	myGuid = format("%u", myGuid)

	for i=0, 5 do
        local paramidx = x700044_CSP_GUID_START + i
        local nGUID = GetFubenData_Param(sceneId, paramidx  )
				nGUID = format("%u", nGUID)
        if nGUID == myGuid then

			SetFubenData_Param(sceneId,x700044_CSP_HUMAN_TALKPARAM_START+i, nParam)
            break
        end
    end

	


	DispatchQuestInfo(sceneId, selfId, NPCId, x700044_g_ScriptId, -1);
end



function x700044_DispatchDegrade( sceneId, selfId, NPCId, nParam )

	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId,"#Y降低难度")
		AddQuestText(sceneId,"怪物等级减少5")
		--AddQuestText(sceneId," ")

		


	EndQuestEvent()


	local myGuid = GetPlayerGUID( sceneId,selfId )
	myGuid = format("%u", myGuid)

	for i=0, 5 do
        local paramidx = x700044_CSP_GUID_START + i
        local nGUID = GetFubenData_Param(sceneId, paramidx  )
				nGUID = format("%u", nGUID)
        if nGUID == myGuid then

			SetFubenData_Param(sceneId,x700044_CSP_HUMAN_TALKPARAM_START+i, nParam)
            break
        end
    end
	
	


	DispatchQuestInfo(sceneId, selfId, NPCId, x700044_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--申请进入副本
---------------------------------------------------------------------------------------------------
function x700044_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--点确定后
----------------------------------------------------------------------------------------------
function x700044_ProcAccept( sceneId, selfId )

	local nParam = 0;
	
	local myGuid = GetPlayerGUID( sceneId,selfId )
	myGuid = format("%u", myGuid)

	for i=0, 5 do
        local paramidx = x700044_CSP_GUID_START + i
        local nGUID = GetFubenData_Param(sceneId, paramidx  )
				nGUID = format("%u", nGUID)
        if nGUID == myGuid then

			nParam = GetFubenData_Param(sceneId,x700044_CSP_HUMAN_TALKPARAM_START+i)
            break
        end
    end
	
	
	
	if nParam==1 then
		x700044_OnRequestUpgrade(sceneId,selfId)
	elseif nParam==2 then
		x700044_OnRequestDegrade(sceneId,selfId)
	end
end

function x700044_OnRequestUpgrade(sceneId,selfId)
	local nCurrentLevel = GetFubenData_Param(sceneId,x700044_CSP_FUBENLEVEL)
	local nStdLevel = GetFubenData_Param(sceneId,x700044_CSP_FUBENLEVEL_DUP)

	if nCurrentLevel< (nStdLevel+5) then
		if x700044_g_LevelMax >= (nCurrentLevel+5) then
			SetFubenData_Param(sceneId,x700044_CSP_FUBENLEVEL, nCurrentLevel+5)

			x700044_ShowTipsToAll(sceneId, format("怪物等级增加5", nCurrentLevel+5))
		else
			
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "超过最大等级限制，增加难度失败");
			EndQuestEvent(sceneId);

			DispatchQuestTips(sceneId, selfId);
			
		end
	else
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "难度已经最高了，增加难度失败");
		EndQuestEvent(sceneId);

		DispatchQuestTips(sceneId, selfId);
	end

	
end

function x700044_OnRequestDegrade(sceneId,selfId)
	local nCurrentLevel = GetFubenData_Param(sceneId,x700044_CSP_FUBENLEVEL)
	local nStdLevel = GetFubenData_Param(sceneId,x700044_CSP_FUBENLEVEL_DUP)

	
	if nCurrentLevel> (nStdLevel-5) then
		if x700044_g_LevelMin <= (nCurrentLevel-5) then
			SetFubenData_Param(sceneId,x700044_CSP_FUBENLEVEL, nCurrentLevel-5)

			x700044_ShowTipsToAll(sceneId, format("怪物等级降低5", nCurrentLevel-5))
		else
			
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "超过最小等级限制，降低难度失败");
			EndQuestEvent(sceneId);

			DispatchQuestTips(sceneId, selfId);
			
		end
	else
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "难度已经最低了，减少难度失败");
		EndQuestEvent(sceneId);

		DispatchQuestTips(sceneId, selfId);
	end
end


function x700044_ShowTipsToAll(sceneId, str)
	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);

		DispatchQuestTips(sceneId, humanId);
	end
end