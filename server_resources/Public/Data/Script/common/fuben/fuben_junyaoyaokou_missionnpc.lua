x700040_CSP_CURRENT_STEP			=	22--x700001_CSP_CURRENT_STEP
x700040_CSP_B_FIGTHING				=	24--x700001_CSP_B_FIGTHING
x700040_MAX_TOTAL_STEP				=	10--x700001_MAX_TOTAL_STEP
x700040_CSP_HUMAN_TALKPARAM_START	=	230--x700001_CSP_HUMAN_TALKPARAM_START
x700040_CSP_HUMAN_COUNT				=	240--x700001_CSP_HUMAN_COUNT
x700040_CSP_OBJID_START             =   241--x700001_CSP_OBJID_START
x700040_CSP_B_GETBONUS_START		=	220--x700001_CSP_B_GETBONUS_START
x700040_CSP_B_MISSION_FAILED		=	27--x700001_CSP_B_MISSION_FAILED

x700040_CSP_LAST_TICKOUNT			=	247
x700040_CSP_GUID_START              =   248  --空6个

x700040_g_ScriptId = 700040


x700040_Fuben_ScriptId = 700001

function x700040_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
	
	if which>=0 then	
		x700040_DispatchPlayInfo( sceneId, selfId, NPCId,which )
	--else
		--x700040_DispatchGetBonusInfo( sceneId, selfId, NPCId,which )
	end
	
end


--**********************************

--列举事件

--**********************************

function x700040_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

	local nCurrentGameStep = GetFubenData_Param(sceneId, x700040_CSP_CURRENT_STEP )
	local bFighting = GetFubenData_Param(sceneId, x700040_CSP_B_FIGTHING )
	local bFailed = GetFubenData_Param(sceneId, x700040_CSP_B_MISSION_FAILED )



	if bFighting>0 then
		return
	end

	if bFailed>0 then
		return
	end


	local myGuid = GetPlayerGUID( sceneId,selfId )
	myGuid = format("%u", myGuid)

	local bFind = 0;
	for i=0, 5 do
        local paramidx = x700040_CSP_GUID_START + i
        local nGUID = GetFubenData_Param(sceneId, paramidx  )
				nGUID = format("%u", nGUID)
        if nGUID == myGuid then

			local bGetBonus = GetFubenData_Param(sceneId,x700040_CSP_B_GETBONUS_START+i)
			
			if bGetBonus>0 then
				return
			end

            bFind = 1
            break
        end
    end


	if bFind<=0 then
		return
	end

	 
	if nCurrentGameStep<=0 then
		AddQuestNumText(sceneId, x700040_g_ScriptId, "抵挡妖魔的袭击",0,nCurrentGameStep)
	elseif nCurrentGameStep>0 then
		if nCurrentGameStep<x700040_MAX_TOTAL_STEP then
			AddQuestNumText(sceneId, x700040_g_ScriptId, "对抗更强大的妖魔",0,nCurrentGameStep)
			--AddQuestNumText(sceneId, x700040_g_ScriptId, "领取奖励",0,-1)
		--else
			--AddQuestNumText(sceneId, x700040_g_ScriptId, "领取奖励",0,-1)
		end
	end
end


---------------------------------------------------------------------------------------------------
--进入副本文字显示
---------------------------------------------------------------------------------------------------
function x700040_DispatchPlayInfo( sceneId, selfId, NPCId, nParam )

	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId,"#Y".."\t帮助我抵抗这些妖魔，保护炼妖炉不被破坏，我会给你们丰厚的奖励！")
		AddQuestText(sceneId,"\n\t开始抵挡妖魔的袭击！")
		--AddQuestText(sceneId," ")

		


	EndQuestEvent()


	
	local myGuid = GetPlayerGUID( sceneId,selfId )
	myGuid = format("%u", myGuid)

	for i=0, 5 do
        local paramidx = x700040_CSP_GUID_START + i
        local nGUID = GetFubenData_Param(sceneId, paramidx  )
				nGUID = format("%u", nGUID)
        if nGUID == myGuid then

			SetFubenData_Param(sceneId,x700040_CSP_HUMAN_TALKPARAM_START+i, nParam)
            break
        end
    end

	


	DispatchQuestInfo(sceneId, selfId, NPCId, x700040_g_ScriptId, -1);
end



function x700040_DispatchGetBonusInfo( sceneId, selfId, NPCId, nParam )

	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId,"#Y".." 领取奖励")
		AddQuestText(sceneId,"确定领取奖励吗？")
		--AddQuestText(sceneId," ")

		


	EndQuestEvent()


	local myGuid = GetPlayerGUID( sceneId,selfId )
	myGuid = format("%u", myGuid)

	for i=0, 5 do
        local paramidx = x700040_CSP_GUID_START + i
        local nGUID = GetFubenData_Param(sceneId, paramidx  )
				nGUID = format("%u", nGUID)
        if nGUID == myGuid then

			SetFubenData_Param(sceneId,x700040_CSP_HUMAN_TALKPARAM_START+i, nParam)
            break
        end
    end
	
	


	DispatchQuestInfo(sceneId, selfId, NPCId, x700040_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--申请进入副本
---------------------------------------------------------------------------------------------------
function x700040_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--点确定后
----------------------------------------------------------------------------------------------
function x700040_ProcAccept( sceneId, selfId )

	local nParam = -2;
	
	local myGuid = GetPlayerGUID( sceneId,selfId )
	myGuid = format("%u", myGuid)

	for i=0, 5 do
        local paramidx = x700040_CSP_GUID_START + i
        local nGUID = GetFubenData_Param(sceneId, paramidx  )
				nGUID = format("%u", nGUID)
        if nGUID == myGuid then

			nParam = GetFubenData_Param(sceneId,x700040_CSP_HUMAN_TALKPARAM_START+i)
            break
        end
    end

	
	if nParam>=0 then
		CallScriptFunction( x700040_Fuben_ScriptId, "OnNpcTalk", sceneId, selfId,nParam ) ;
	--elseif nParam==-1 then
		--x700040_OnRequestGetBonus(sceneId, selfId )
	end
end

function x700040_OnRequestGetBonus(sceneId, selfId )
	local nCurrentGameStep = GetFubenData_Param(sceneId, x700040_CSP_CURRENT_STEP )
	local bFighting = GetFubenData_Param(sceneId, x700040_CSP_B_FIGTHING )
	local bFailed = GetFubenData_Param(sceneId, x700040_CSP_B_MISSION_FAILED )

	if bFailed>0 then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "很可惜，你没能成功的保护炼妖炉");
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, selfId);
		return
	end

	if bFighting>0 then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "还有妖魔在肆虐，你还不能领取奖励");
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, selfId);
		return
	end

	
		
	local myGuid = GetPlayerGUID( sceneId,selfId )
	myGuid = format("%u", myGuid)
	local bFind = 0;
	for i=0, 5 do
        local paramidx = x700040_CSP_GUID_START + i
        local nGUID = GetFubenData_Param(sceneId, paramidx  )
				nGUID = format("%u", nGUID)	
        if nGUID == myGuid then

			local bGetBonus = GetFubenData_Param(sceneId,x700040_CSP_B_GETBONUS_START+i)
			if bGetBonus>0 then
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "你已经领取过奖励");
				EndQuestEvent(sceneId);
				DispatchQuestTips(sceneId, selfId);
				return
			end

			SetFubenData_Param(sceneId,x700040_CSP_B_GETBONUS_START+i, 1)

			bFind = 1;
			break;
        end
    end
	
	

	if bFind<=0 then
		return
	end

	x700040_GiveBonusToHuman(sceneId, selfId )
end

function x700040_GiveBonusToHuman(sceneId, selfId )
	local nCurrentGameStep = GetFubenData_Param(sceneId, x700040_CSP_CURRENT_STEP )
	local nLevel = GetLevel(sceneId, selfId)
	
	local nCount = 0;

	local itemId = 0;
	
	if nLevel>=20 and nLevel <=39 then
		itemId = 11000200
	elseif nLevel>=40 and nLevel <=59 then
		itemId = 11000201
	elseif nLevel>=60 and nLevel <=79 then
		itemId = 11000202
	elseif nLevel>=80  then
		itemId = 11000203
	else
		return
	end

	if nCurrentGameStep==1 then
		nCount = 1
	elseif nCurrentGameStep>=2 and nCurrentGameStep<10 then
		nCount =1*(nCurrentGameStep-1)
	elseif nCurrentGameStep>=10 then
		nCount = 10
	end
	

	local nSuccess = 0;

	for i=1, nCount do
		BeginAddItem(sceneId)
		AddItem( sceneId, itemId, 1 )
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
			AddItemListToPlayer(sceneId,selfId)
			nSuccess = nSuccess+1
		end
	end

	local str = format("你获得了%d个星尘的奖励！",nCount,nSuccess)

	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end











