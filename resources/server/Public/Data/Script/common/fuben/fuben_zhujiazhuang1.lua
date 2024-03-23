---------------------------------------------------
-- File: 700030_fuben_ZHUJIAZHUANG1_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700030_CSP_FUBENTYPE				= 	0
x700030_CSP_SCRIPTID				=	1
x700030_CSP_TICKCOUNT				= 	2
x700030_CSP_FROMSCENEID				= 	3
x700030_CSP_ISCLOSING				= 	4
x700030_CSP_LEAVECOUNTDOWN			= 	5
x700030_CSP_TEAMID					=	6
x700030_CSP_BACKSCENEX       		=   7
x700030_CSP_BACKSCENEZ      		=   8
x700030_CSP_FUBENLEVEL			=	9

x700030_CSP_KILLCOUNT				=	20
x700030_CSP_FUBEN_SCENE_ID			=	21

x700030_CSP_NPC1_ID					=	22
x700030_CSP_NPC2_ID					=	23
x700030_CSP_BOSS1_ID				=	24
x700030_CSP_BOSS2_ID				=	25
x700030_CSP_RUN_FLAG				=	26
x700030_CSP_GAME_STEP				=	27
x700030_CSP_TALK_STEP				=	28



x700030_CSP_SHUAGUAI_AREA_START		=	90
x700030_CSP_OBJID_AREA				=	110
x700030_CSP_FAIL_FLAG				=	111

x700030_CSP_XIANJINBOSS				=	239
x700030_CSP_HUMAN_COUNT				=	240
x700030_CSP_OBJID_START				=	241

x700030_CSP_GUID_START              =   248  --空6个
x700030_CSP_FUBEN_TYPE				=	254	--试练，普通，英雄，三种类型

x700030_CSP_FUBEN_MODE				=   255 
------------------------Scene System Setting -----------------------------------

x700030_g_ScriptId 					= 700030

x700030_g_FubenType				= 	FUBEN_ZHUJIAZHUANG1		    --副本类型



x700030_g_SubmitNPC                 =   { type =25077,guid= 150551,x = 142, z=214, facedir =0, title ="拼命三郎" }
x700030_g_LeaveNPC					=   { type =25077,guid= 150029,x = 142, z=214, facedir =0, title ="拼命三郎" }

x700030_g_Run_Count						= 12

x700030_g_NpcTalkCount =5
--不说话为空
x700030_g_NpcTalk1 = {"哎呦，祝家没人了不成？怎么还出来一个女的？",	"",	"啊，我怎么动弹不得？有妖法？",	"",	"兄弟们救我……"}
x700030_g_NpcTalk2 = {"",	"贼人休要胡言，今天就让你看看姑奶奶的手段！","","哼哼，你这等草寇怎么识得我的天网阵法。",""	}



-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700030_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)

	
end

function x700030_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x700030_ShowTipsToAll(sceneId, str)

	local humancount = GetFuben_PlayerCount(sceneId);

	--通知玩家
	for i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId,str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, humanId);
	end
end

-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  当副本创建成功时， 开始刷怪和npc
--*********************************************************
-----------------------------------------------------------
function x700030_OnFubenSceneCreated( sceneId )

	for i=20,239 do
		SetFubenData_Param(sceneId, i, -1 )
	end
	SetFubenData_Param(sceneId, x700030_CSP_XIANJINBOSS, -1 )
	SetFubenData_Param(sceneId, x700030_CSP_GAME_STEP, 0 )
	SetFubenData_Param(sceneId, x700030_CSP_TALK_STEP, 0 )
	
	SetFubenData_Param(sceneId, x700030_CSP_FAIL_FLAG, 0 )


	
	
	x700030_CreateBoss( sceneId )

    x700030_CreateMonster( sceneId )
		
end

function x700030_EnterTick(sceneId,nowTickCount)

	if nowTickCount == 2 then
			
		x700030_CreateNpc( sceneId, 0 )
		return 
	end

	if nowTickCount>24 then
		local nCurrentFlag = GetFubenData_Param(sceneId,x700030_CSP_RUN_FLAG)

		if nCurrentFlag<x700030_g_Run_Count then
	
			if random(1,100)<=15 then				
				x700030_CreateRunMonster(sceneId, nCurrentFlag)
			end
		end
	end

	local nNpcId1 = GetFubenData_Param(sceneId, x700030_CSP_NPC1_ID )
	local nNpcId2 = GetFubenData_Param(sceneId, x700030_CSP_NPC2_ID )

	local nStep = GetFubenData_Param(sceneId, x700030_CSP_GAME_STEP )

	if nStep==0 then   --谈话之前

		if nNpcId1>=0 then
			local x,z =GetWorldPos(sceneId,nNpcId1)
			--x700030_ShowTipsToAll( sceneId, format("x=%d,z=%d",x,z))	
			local area = {121,180,157,218}  
			if x>=area[1] and x<=area[3] then
				if z>=area[2] and z<=area[4] then
					x700030_OnNpcInArea(sceneId)
				end
			end
		end
	elseif nStep==1 then --谈话
		local nTalkStep = GetFubenData_Param(sceneId, x700030_CSP_TALK_STEP )
		
		if nTalkStep<=x700030_g_NpcTalkCount then
			if x700030_g_NpcTalk1[nTalkStep]~="" then
				NpcTalk(sceneId, nNpcId1, x700030_g_NpcTalk1[nTalkStep],  -1)
			end
			if x700030_g_NpcTalk2[nTalkStep]~="" then
				NpcTalk(sceneId, nNpcId2, x700030_g_NpcTalk2[nTalkStep],  -1)
			end
		else
			SetFubenData_Param(sceneId, x700030_CSP_GAME_STEP, 2 )
		end

		SetFubenData_Param(sceneId, x700030_CSP_TALK_STEP, nTalkStep+1 )
		
		
	elseif nStep ==2 then --谈话结束
		DeleteMonster( sceneId,nNpcId1 )
		DeleteMonster( sceneId,nNpcId2 )
		SetFubenData_Param(sceneId, x700030_CSP_NPC1_ID, -2 )
		SetFubenData_Param(sceneId, x700030_CSP_NPC2_ID, -2 )
		SetFubenData_Param(sceneId, x700030_CSP_GAME_STEP, 3 ) --副本逻辑结束
		
		x700030_ShowTipsToAll( sceneId, "时迁又被抓走了！")
		x700030_CreateSubmitNpc( sceneId)
		
		x700030_ShowTipsToAll( sceneId, "副本完成")
	end

end



function x700030_OnNpcInArea(sceneId)

--	x700030_ShowTipsToAll( sceneId, "x700030_OnNpcInArea")	
	local nNpcId1 = GetFubenData_Param(sceneId, x700030_CSP_NPC1_ID )
	local boss1 = GetFubenData_Param(sceneId, x700030_CSP_BOSS1_ID )
	local boss2 = GetFubenData_Param(sceneId, x700030_CSP_BOSS2_ID )

	if nNpcId1<0 then
		return
	end
	
	if boss1<0 and boss2<0 then
		x700030_EnterNextScene(sceneId)
	end
end

function x700030_EnterNextScene(sceneId)
	local nStep = GetFubenData_Param(sceneId, x700030_CSP_GAME_STEP )

	if nStep~=0 then
		return
	end


	SetFubenData_Param(sceneId, x700030_CSP_GAME_STEP, 1 )
	SetFubenData_Param(sceneId, x700030_CSP_TALK_STEP, 1 )

	x700030_CreateNpc( sceneId, 1 )
	
end




function x700030_CreateNpc( sceneId, nFlag )
	local fubenlevel = GetFubenData_Param(sceneId, x700030_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700030_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700030_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700030_g_ScriptId )
	
	for i = 0,nDataCount-1 do		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700030_g_ScriptId,nIndexFrom,i)
		if idScript == x700030_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 and flag == nFlag then

			if 	flag == 0 then
				camp = 24
			elseif flag == 1 then
				camp = 20
			end

			local nObjId  = -1  
			if title~="" then
				nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700030_g_ScriptId, -1, camp,-1,facedir, "",title)
			else
				nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700030_g_ScriptId, -1, camp,-1,facedir)
				
			end
			if nObjId >= 0 then

				if flag==0 then
					SetFubenData_Param(sceneId, x700030_CSP_NPC1_ID, nObjId )
					SetPatrolId(sceneId, nObjId, 0)
					x700030_ShowTipsToAll( sceneId, "保护时迁逃到河边，有船接应！")	
				elseif flag==1 then
					SetFubenData_Param(sceneId, x700030_CSP_NPC2_ID, nObjId )
	--					x700030_ShowTipsToAll( sceneId, "一丈青出现")	
				end

			end
			break
		end
	end

end



function x700030_CreateBoss(sceneId)


	local fubenlevel = GetFubenData_Param(sceneId, x700030_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700030_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700030_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700030_g_ScriptId )
	
	for i = 0,nDataCount-1 do		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700030_g_ScriptId,nIndexFrom,i)
		if idScript == x700030_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then

			local nObjId  = -1  
			if title~="" then
				nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700030_g_ScriptId, -1, 21,-1,facedir, "",title)
			else
				nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700030_g_ScriptId, -1, 21,-1,facedir)
				
			end

			if nObjId >= 0 then					
				if flag == 0 then
					SetFubenData_Param(sceneId, x700030_CSP_BOSS1_ID, nObjId )
					SetPatrolId(sceneId, nObjId, 1)
				elseif flag == 1 then
					SetFubenData_Param(sceneId, x700030_CSP_BOSS2_ID, nObjId )
				end
			end
        end
	end

end







---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700030_CreateMonster(sceneId)

	local fubenlevel = GetFubenData_Param(sceneId, x700030_CSP_FUBENLEVEL ) ;
	local nFubenType = GetFubenData_Param(sceneId, x700030_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700030_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700030_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700030_g_ScriptId,nIndexFrom,i)
		if idScript == x700030_g_ScriptId and monsterFlag == 3 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x + rx
                local rz = random(-r,r)
                local z = z + rz
				if title~="" then
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir,  "",title)
				else
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
				
				end
			end
        end
	end
	

end

function x700030_CreateRunMonster(sceneId, nFlag)
	
	local nCurrentFlag = GetFubenData_Param(sceneId,x700030_CSP_RUN_FLAG)

	if nCurrentFlag>=x700030_g_Run_Count then
		return
	end

	SetFubenData_Param(sceneId,x700030_CSP_RUN_FLAG, nCurrentFlag+1)

	local fubenlevel = GetFubenData_Param(sceneId, x700030_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700030_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700030_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700030_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700030_g_ScriptId,nIndexFrom,i)
		if idScript == x700030_g_ScriptId and monsterFlag == 4 and levelmin <= fubenlevel and levelmax >= fubenlevel and flag == nFlag and nFubenType == flag3 then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x + rx
                local rz = random(-r,r)
                local z = z + rz

				local nObjId = -1

				if title~="" then
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir,  "",title)
				else
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
				
				end
				if nObjId >= 0 and patrolid >=0 then
					SetPatrolId(sceneId, nObjId, 0)
				end
			end
        end
	end

--	x700030_ShowTipsToAll( sceneId, format("创建追踪怪%d",nFlag))

end




function x700030_CreateAreaMonster(sceneId, areaId)



	local bCreated = GetFubenData_Param(sceneId,x700030_CSP_SHUAGUAI_AREA_START+areaId)

	if bCreated>0 then
		return
	end

	SetFubenData_Param(sceneId,x700030_CSP_SHUAGUAI_AREA_START+areaId, 1)

	local fubenlevel = GetFubenData_Param(sceneId, x700030_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700030_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700030_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700030_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700030_g_ScriptId,nIndexFrom,i)
		if idScript == x700030_g_ScriptId and monsterFlag == 5 and levelmin <= fubenlevel and levelmax >= fubenlevel and flag == areaId and nFubenType == flag3 then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x + rx
                local rz = random(-r,r)
                local z = z + rz

				if title~="" then
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir, "",title)
				else
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
					
				end
			end
        end
	end

	--x700030_ShowTipsToAll( sceneId, format("创建区域怪%d",areaId))




end


function x700030_OnEnterShuaguaiArea(sceneId,  areaId)
	


	
	local bCreated = GetFubenData_Param(sceneId,x700030_CSP_SHUAGUAI_AREA_START+areaId)

--	x700030_ShowTipsToAll( sceneId, format("bCreated = %d",bCreated))	
	if bCreated>0 then
		return
	end

	x700030_CreateAreaMonster(sceneId, areaId)
end



function x700030_OnDie(sceneId, selfId, killerId)
	
	local nDieCount = GetFubenData_Param(sceneId, x700030_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700030_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	local objId1 = GetFubenData_Param(sceneId, x700030_CSP_NPC1_ID)
	local objId2 = GetFubenData_Param(sceneId, x700030_CSP_BOSS1_ID)
	local objId3 = GetFubenData_Param(sceneId, x700030_CSP_BOSS2_ID)
	
	local xianjinboss = GetFubenData_Param(sceneId, x700030_CSP_XIANJINBOSS)
	
	if xianjinboss == selfId then
		CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnXianjinBossDie", sceneId)
	end
	
	if objId1 == selfId then
		SetFubenData_Param(sceneId, x700030_CSP_NPC1_ID, -1)
		
		x700030_OnFubenFailed(sceneId, selfId)
		
	elseif objId2 == selfId then
		SetFubenData_Param(sceneId, x700030_CSP_BOSS1_ID, -1)
		
	elseif objId3 == selfId then
		SetFubenData_Param(sceneId, x700030_CSP_BOSS2_ID, -1)
		
	end
end

function x700030_OnAllMonsterDead( sceneId)
	--x700030_CreateSubmitNpc( sceneId)
end

function x700030_DelAllMonster( sceneId)
	local nMonsterCount = GetMonsterCount(sceneId)
	for i=1,nMonsterCount do
    	local objid = GetMonsterObjID(sceneId,i-1)
    	if objid >= 0 and IsObjValid(sceneId,objid) then
    		DeleteMonster(sceneId,objid)
    	end
	end
end		
		
function x700030_OnFubenFailed(sceneId,selfId)
	x700030_ShowTipsToAll( sceneId, "时迁被抓走,速去河边与石秀会合,再谋对策！")
	--x700030_DelAllMonster( sceneId)
	x700030_CreateSubmitNpc( sceneId)
	SetFubenData_Param(sceneId, x700030_CSP_FAIL_FLAG, 1)
end

function x700030_CreateLeaveNpc( sceneId)
	
	if x700030_g_LeaveNPC.title~= "" then
		CreateMonster(sceneId, x700030_g_LeaveNPC.type, x700030_g_LeaveNPC.x, x700030_g_LeaveNPC.z, 3, 0, -1, x700030_g_LeaveNPC.guid, -1,-1,x700030_g_LeaveNPC.facedir, "", x700030_g_LeaveNPC.title)
	else
		CreateMonster(sceneId, x700030_g_LeaveNPC.type, x700030_g_LeaveNPC.x, x700030_g_LeaveNPC.z, 3, 0, -1, x700030_g_LeaveNPC.guid, -1,-1,x700030_g_LeaveNPC.facedir)
		
	end

	--// add for 现金副本
	 x700030_CreateXianJinBoss(sceneId)
	 --// add end
end

function x700030_CreateSubmitNpc( sceneId)
	if x700030_g_SubmitNPC.title~= "" then
		CreateMonster(sceneId, x700030_g_SubmitNPC.type, x700030_g_SubmitNPC.x, x700030_g_SubmitNPC.z, 3, 0, -1, x700030_g_SubmitNPC.guid, -1,-1,x700030_g_SubmitNPC.facedir, "", x700030_g_SubmitNPC.title)
	else
		CreateMonster(sceneId, x700030_g_SubmitNPC.type, x700030_g_SubmitNPC.x, x700030_g_SubmitNPC.z, 3, 0, -1, x700030_g_SubmitNPC.guid, -1,-1,x700030_g_SubmitNPC.facedir)
		
	end

	--// add for 现金副本
	 x700030_CreateXianJinBoss(sceneId)
	 --// add end

	 CallScriptFunction( 701119, "OnSceneBossDie", sceneId, 0)
end

----------------------------------------------------------
--创建现金boss
----------------------------------------------------------

function x700030_CreateXianJinBoss(sceneId)

	local nFubenType = GetFubenData_Param(sceneId, x700030_CSP_FUBEN_TYPE)

	if nFubenType ~= 0 then
		return
	end
	
	local nFubenMode = GetFubenData_Param(sceneId, x700030_CSP_FUBEN_MODE)
	
	if nFubenMode == 0  then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700030_CSP_FUBENLEVEL ) ;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700030_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700030_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700030_g_ScriptId,nIndexFrom,i)
		if idScript == x700030_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700030_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700030_g_ScriptId, -1, 21,-1,facedir)
			end
			SetFubenData_Param(sceneId, x700030_CSP_XIANJINBOSS, nRet )
		end
	end

	x700030_ShowTipsToAll(sceneId, "翻番宝箱出现！")
end
--//added in 2009-3-17
---------------------------------------------------------------------------------------------------
--进入区域
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
--区域定时器
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
function x700030_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	if GetFubenData_Param(sceneId, x700030_CSP_FAIL_FLAG) == 1 then
		return
	end
	
	
	local nFubenType = GetFubenData_Param(sceneId, x700030_CSP_FUBENTYPE);

	if nFubenType~=x700030_g_FubenType then
		return
	end

	
	
	local humancount = GetFuben_PlayerCount(sceneId);
	--for	i = 0, humancount - 1 do
		--local humanId = GetFuben_PlayerObjId(sceneId, i);
		--local str = format(" 进入%d",zoneId);
		--BeginQuestEvent(sceneId);
		--AddQuestText(sceneId, str);
		--EndQuestEvent(sceneId);
		--DispatchQuestTips(sceneId, humanId);
	--end

	 --检查玩家GUID
    local nFind = 1
    local guid = GetPlayerGUID( sceneId,selfId )


	
    --not player
    if nFind == 0 then
		return
    end

	local index = x700030_CSP_OBJID_AREA
	for i=0, 5 do
		local idx = index+i*2
	    local objid = GetFubenData_Param(sceneId, idx )
	    if objid == selfId then

	    	SetFubenData_Param(sceneId, idx, selfId )
			SetFubenData_Param(sceneId, idx+1, zoneId )

	    	break
	    elseif objid == -1 then

	        SetFubenData_Param(sceneId, idx, selfId )
	        SetFubenData_Param(sceneId, idx+1, zoneId )
	        break
		end
	end

	


	x700030_OnEnterShuaguaiArea(sceneId, zoneId)
	

end

---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x700030_ProcAreaLeaved( sceneId, selfId, zoneId, MissionId )

	local nFubenType = GetFubenData_Param(sceneId, x700030_CSP_FUBENTYPE);

	if nFubenType~=x700030_g_FubenType then
		return
	end

    local humancount = GetFuben_PlayerCount(sceneId);
	--for	i = 0, humancount - 1 do
		--local humanId = GetFuben_PlayerObjId(sceneId, i);
		--local str = format(" 离开%d",zoneId);
		--BeginQuestEvent(sceneId);
		--AddQuestText(sceneId, str);
		--EndQuestEvent(sceneId);
		--DispatchQuestTips(sceneId, humanId);
	--end

	local index = x700030_CSP_OBJID_AREA
	for i=0, 5 do
		local idx = index+i*2
	    local objid = GetFubenData_Param(sceneId, idx )
	    local zoneId = GetFubenData_Param(sceneId, idx + 1 )
	    if objid == selfId then
	        SetFubenData_Param(sceneId, idx, -1 )
	        SetFubenData_Param(sceneId, idx+1, -1 )
	    end
	end
end

---------------------------------------------------------------------------------------------------
--区域定时器
---------------------------------------------------------------------------------------------------
function x700030_ProcTiming( sceneId, selfId, ScriptId, MissionId )
	
end


