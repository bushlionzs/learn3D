---------------------------------------------------
-- File: 700031_fuben_ZHUJIAZHUANG2_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700031_CSP_FUBENTYPE				= 	0
x700031_CSP_SCRIPTID				=	1
x700031_CSP_TICKCOUNT				= 	2
x700031_CSP_FROMSCENEID				= 	3
x700031_CSP_ISCLOSING				= 	4
x700031_CSP_LEAVECOUNTDOWN			= 	5
x700031_CSP_TEAMID					=	6
x700031_CSP_BACKSCENEX       		=   7
x700031_CSP_BACKSCENEZ      		=   8
x700031_CSP_FUBENLEVEL			=	9

x700031_CSP_TICKCOUNT_ADD			=	12
x700031_CSP_TICKCOUNT_SUB			=	13

x700031_CSP_KILLCOUNT				=	20
x700031_CSP_FUBEN_SCENE_ID			=	21

x700031_CSP_NPC1_ID					=	22
x700031_CSP_NPC2_ID					=	23
x700031_CSP_NPC3_ID					=	24
x700031_CSP_NPC4_ID					=	25
x700031_CSP_NPC5_ID					=	26
x700031_CSP_NPC6_ID					=	27
x700031_CSP_BOSS1_ID				=	28
x700031_CSP_BOSS2_ID				=	29
x700031_CSP_BOSS3_ID				=	30
x700031_CSP_BOSS4_ID				=	31
x700031_CSP_BOSS5_ID				=	32


x700031_CSP_GAME_STEP				=	34

x700031_CSP_B_BOSS1					=	35
x700031_CSP_B_BOSS2					=	36
x700031_CSP_B_BOSS3					=	37
x700031_CSP_B_BOSS4					=	38
x700031_CSP_B_BOSS5					=	39
x700031_CSP_B_MONSTER2				=	40
x700031_CSP_FINAL_BOSS_ID			=	41
x700031_CSP_B_FINALBOSS				=	42


x700031_CSP_TALK_NPC1_ID			=	43
x700031_CSP_TALK_NPC1_STEP			=	44
x700031_CSP_TALK_NPC2_ID			=	45
x700031_CSP_TALK_NPC2_STEP			=	46

x700031_CSP_B_KILL_WUXING			=	47



x700031_CSP_SHUAGUAI_AREA_START		=	90
x700031_CSP_OBJID_AREA				=	110


x700031_CSP_XIANJINBOSS				=	239
x700031_CSP_HUMAN_COUNT				=	240
x700031_CSP_OBJID_START				=	241

x700031_CSP_GUID_START              =   248  --空6个
x700031_CSP_FUBEN_TYPE				=	254	--试练，普通，英雄，三种类型
x700031_CSP_FUBEN_MODE				=   255 

------------------------Scene System Setting -----------------------------------

x700031_g_ScriptId 					= 700031
x700031_g_FubenType				= 	FUBEN_ZHUJIAZHUANG2		    --副本类型
x700031_g_LimitTotalHoldTime		= 	540						--副本可以存活的时间（单位：次数）,如果此时间到了，则任务将会失败
x700031_g_TaopaoTime				=   30*12


x700031_g_SubmitNPC                 =   { type =25079,guid= 150553,x = 138, z=203, facedir =0, title ="神行太保" }
x700031_g_LeaveNPC					=   { type =25079,guid= 150553,x = 138, z=203, facedir =0, title ="神行太保" }
--时迁变身后
x700031_g_ShiqianNPC					=   { type =25088,x = 130, z=110.5, facedir =178, title ="" }

x700031_g_TalkNPCList					= {
											{ type =25089,x = 135, z=202,	facedir =178, flag =0, title ="花和尚" },
											{ type =25090,x = 0,	z=0,	facedir =178, flag =1, title ="矮脚虎" },
										  }
-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700031_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)

	
end


function x700031_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x700031_ShowTipsToAll(sceneId, str)

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
function x700031_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  副本场景id
	
	SetFubenData_Param(sceneId, x700031_CSP_B_KILL_WUXING,0)
	local index = x700031_CSP_OBJID_AREA
	for i=index,index+11 do

		SetFubenData_Param(sceneId, i, -1 )
	end

	SetFubenData_Param(sceneId, x700031_CSP_GAME_STEP, 0 )

	SetFubenData_Param(sceneId, x700031_CSP_BOSS1_ID,-2)
	SetFubenData_Param(sceneId, x700031_CSP_BOSS2_ID,-2)
	SetFubenData_Param(sceneId, x700031_CSP_BOSS3_ID,-2)
	SetFubenData_Param(sceneId, x700031_CSP_BOSS4_ID,-2)
	SetFubenData_Param(sceneId, x700031_CSP_BOSS5_ID,-2)
	SetFubenData_Param(sceneId, x700031_CSP_FINAL_BOSS_ID,-2)
	SetFubenData_Param(sceneId, x700031_CSP_XIANJINBOSS, -1 )

	x700031_CreateTalkNpc( sceneId, 0 )

	x700031_CreateNpc( sceneId )
	
	--x700031_CreateBoss( sceneId )

    x700031_CreateMonster( sceneId )
		
end

function x700031_EnterTick(sceneId,nowTickCount)
	local nStep = GetFubenData_Param(sceneId, x700031_CSP_GAME_STEP )
	if nStep==1 then
		local nNpcId1 = GetFubenData_Param(sceneId, x700031_CSP_NPC1_ID )
		--NpcTalk(sceneId, nNpcId1, "这是个圈套！时间无多，大家快跑！",  -1)
		DeleteMonster( sceneId,nNpcId1 )
		SetFubenData_Param(sceneId, x700031_CSP_GAME_STEP, 2 )
	end
	
	local nTalkStep1 = GetFubenData_Param(sceneId, x700031_CSP_TALK_NPC1_STEP )
	local nTalkStep2 = GetFubenData_Param(sceneId, x700031_CSP_TALK_NPC2_STEP )

	if nTalkStep1>0 then
		local nTalkNpc1 = GetFubenData_Param(sceneId, x700031_CSP_TALK_NPC1_ID )
			
		local talklen =2
		local talklist = {"洒家一路杀过来，未见时迁，只见几个怪异的东西立在院内。倒是刚刚看见一个小女子手提一布袋向庄院最里边走去，莫非那袋中的便是时迁不成？","众家兄弟，杀进庄去，救出时迁！"};

		if nTalkStep1<= talklen then
			NpcTalk(sceneId, nTalkNpc1, talklist[nTalkStep1],  -1)
			SetFubenData_Param(sceneId, x700031_CSP_TALK_NPC1_STEP, nTalkStep1+1 )
		else
			if nTalkNpc1>=0 then
				DeleteMonster( sceneId,nTalkNpc1 )
				SetFubenData_Param(sceneId, x700031_CSP_TALK_NPC1_ID, -1 )
			end
			SetFubenData_Param(sceneId, x700031_CSP_TALK_NPC1_STEP, -1 )
		end
	end

	if nTalkStep2>0 then
		local nTalkNpc2 = GetFubenData_Param(sceneId, x700031_CSP_TALK_NPC2_ID )
		local talklen =1
		local talklist = {"兄弟慢动手，似这等小娘子死了岂不可惜，待我禀明宋公明哥哥，讨她做老婆，嘿嘿……"};

		if nTalkStep2<= talklen then
			NpcTalk(sceneId, nTalkNpc2, talklist[nTalkStep2],  -1)
			SetFubenData_Param(sceneId, x700031_CSP_TALK_NPC2_STEP, nTalkStep2+1 )
		else
			if nTalkNpc2>=0 then
				DeleteMonster( sceneId,nTalkNpc2 )
				SetFubenData_Param(sceneId, x700031_CSP_TALK_NPC2_ID, -1 )
			end
			SetFubenData_Param(sceneId, x700031_CSP_TALK_NPC2_STEP, -1 )
		end
	end
	
	
	
end


function x700031_CreateTalkNpc( sceneId, nFlag, x1,z1 )
	for i, item in x700031_g_TalkNPCList do

		if item.flag == nFlag then

			local nRet = 0
			
				


			if item.flag==0 then
				if item.title ~="" then
					nRet = CreateMonster(sceneId, item.type, item.x, item.z, 7, -1, -1, -1, -1,-1, item.facedir,  "",item.title)
					
				else
					nRet = CreateMonster(sceneId, item.type, item.x, item.z, 7, -1, -1, item.guid, -1,-1, item.facedir)
				
				end
				SetFubenData_Param(sceneId, x700031_CSP_TALK_NPC1_ID, nRet )
				SetFubenData_Param(sceneId, x700031_CSP_TALK_NPC1_STEP, 1 )
					
			elseif item.flag==1 then
				local nRandom1 = random(-2,2)
				local nRandom2 = random(-2,2)
				if item.title ~="" then
					nRet = CreateMonster(sceneId, item.type, x1+nRandom1, z1+nRandom2, 7, -1, -1, -1, -1,-1, item.facedir,  "",item.title)
					
				else
					nRet = CreateMonster(sceneId, item.type, x1+nRandom1, z1+nRandom2, 7, -1, -1, item.guid, -1,-1, item.facedir)
				
				end
				SetFubenData_Param(sceneId, x700031_CSP_TALK_NPC2_ID, nRet )
				SetFubenData_Param(sceneId, x700031_CSP_TALK_NPC2_STEP, 1 )
			
			end
		end
	end
end



function x700031_CreateNpc( sceneId )

	local fubenlevel = GetFubenData_Param(sceneId, x700031_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700031_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700031_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700031_g_ScriptId )

	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700031_g_ScriptId,nIndexFrom,i)
		if idScript == x700031_g_ScriptId and monsterFlag == 3 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then

			local nObjId = 0
			if title ~="" then
				nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, guid, -1,-1, facedir,  "",title)
			else
				nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, guid, -1,-1, facedir)
			
			end

			if nObjId >= 0 then
				if flag==0 then
					SetFubenData_Param(sceneId, x700031_CSP_NPC1_ID, nObjId )					
				elseif flag==1 then
					SetFubenData_Param(sceneId, x700031_CSP_NPC2_ID, nObjId )
				elseif flag==2 then
					SetFubenData_Param(sceneId, x700031_CSP_NPC3_ID, nObjId )
				elseif flag==3 then
					SetFubenData_Param(sceneId, x700031_CSP_NPC4_ID, nObjId )
				elseif flag==4 then
					SetFubenData_Param(sceneId, x700031_CSP_NPC5_ID, nObjId )
				elseif flag==5 then
					SetFubenData_Param(sceneId, x700031_CSP_NPC6_ID, nObjId )
				end
			end
		end

	end			
		
end



function x700031_CreateBoss(sceneId, nFlag)


	if nFlag==0 then
		local bCreated = GetFubenData_Param(sceneId, x700031_CSP_B_BOSS1 )
		if bCreated>0 then
			return
		end
	elseif nFlag==1 then
		local bCreated = GetFubenData_Param(sceneId, x700031_CSP_B_BOSS2 )
		if bCreated>0 then
			return
		end
	elseif nFlag==2 then
		local bCreated = GetFubenData_Param(sceneId, x700031_CSP_B_BOSS3 )
		if bCreated>0 then
			return
		end
	elseif nFlag==3 then
		local bCreated = GetFubenData_Param(sceneId, x700031_CSP_B_BOSS4 )
		if bCreated>0 then
			return
		end
	elseif nFlag==4 then
		local bCreated = GetFubenData_Param(sceneId, x700031_CSP_B_BOSS5 )
		if bCreated>0 then
			return
		end
	else
		return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700031_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700031_CSP_FUBEN_TYPE)

	local nIndexFrom = GetFubenDataPosByScriptID(x700031_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700031_g_ScriptId )

	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700031_g_ScriptId,nIndexFrom,i)
		if idScript == x700031_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then

			if nFlag==flag then
				local nObjId = -1
				if title ~="" then
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700031_g_ScriptId, -1, 21,-1, facedir,  "",title)
				else
					nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700031_g_ScriptId, -1, 21,-1, facedir)
				
				end

				if nObjId >= 0 then 
					if nFlag==0 then
						SetFubenData_Param(sceneId, x700031_CSP_BOSS1_ID, nObjId )
						SetFubenData_Param(sceneId, x700031_CSP_B_BOSS1, 1 )
					elseif nFlag==1 then
						SetFubenData_Param(sceneId, x700031_CSP_BOSS2_ID, nObjId )
						SetFubenData_Param(sceneId, x700031_CSP_B_BOSS2, 1 )
					elseif nFlag==2 then
						SetFubenData_Param(sceneId, x700031_CSP_BOSS3_ID, nObjId )
						SetFubenData_Param(sceneId, x700031_CSP_B_BOSS3, 1 )
					elseif nFlag==3 then
						SetFubenData_Param(sceneId, x700031_CSP_BOSS4_ID, nObjId )
						SetFubenData_Param(sceneId, x700031_CSP_B_BOSS4, 1 )
					elseif nFlag==4 then
						SetFubenData_Param(sceneId, x700031_CSP_BOSS5_ID, nObjId )
						SetFubenData_Param(sceneId, x700031_CSP_B_BOSS5, 1 )
					end
					break
				end
			end													
        end

	end

end


function x700031_CreateBoss2(sceneId)  --创建一丈青

	local bCreated = GetFubenData_Param(sceneId, x700031_CSP_B_FINALBOSS )

	if bCreated>0 then
		return
	end


	local bosslist ={x700031_CSP_BOSS1_ID,x700031_CSP_BOSS2_ID,x700031_CSP_BOSS3_ID,x700031_CSP_BOSS4_ID,x700031_CSP_BOSS5_ID}
	
	local nDieCount = 0
	for i,item in bosslist do
		local nValue = GetFubenData_Param(sceneId, item ) ;
		if nValue==-1 then
			nDieCount = nDieCount+1;
		end
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700031_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700031_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700031_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700031_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700031_g_ScriptId,nIndexFrom,i)
		if idScript == x700031_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 and nDieCount == flag then

				local nRet = 0
				if title ~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700031_g_ScriptId, -1, 21,-1, facedir,  "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700031_g_ScriptId, -1, 21,-1, facedir)
				
				end


				
				SetFubenData_Param(sceneId, x700031_CSP_FINAL_BOSS_ID, nRet )
				SetFubenData_Param(sceneId, x700031_CSP_B_FINALBOSS, 1 )

--				x700031_ShowTipsToAll( sceneId, "一丈青出现")
				
				break
			
	    end
	end

	SetFubenData_Param(sceneId, x700031_CSP_GAME_STEP,3 )

end




---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700031_CreateMonster2(sceneId)  --点击时迁后创建的怪


    local fubenlevel = GetFubenData_Param(sceneId, x700031_CSP_FUBENLEVEL ) ;
	local bCreatMonster2 = GetFubenData_Param(sceneId, x700031_CSP_B_MONSTER2 ) ;

	if bCreatMonster2>0 then
		return
	end

	local nFubenType = GetFubenData_Param(sceneId, x700031_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700031_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700031_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700031_g_ScriptId,nIndexFrom,i)
		if idScript == x700031_g_ScriptId and monsterFlag == 5 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x + rx
                local rz = random(-r,r)
                local z = z + rz
				if title ~="" then
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir, "", title)
				else
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
				
				end
			end
        end
	end

	SetFubenData_Param(sceneId, x700031_CSP_B_MONSTER2, 1 ) 


	

end


---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700031_CreateMonster(sceneId)


    local fubenlevel = GetFubenData_Param(sceneId, x700031_CSP_FUBENLEVEL ) 
	local nFubenType = GetFubenData_Param(sceneId, x700031_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700031_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700031_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700031_g_ScriptId,nIndexFrom,i)
		if idScript == x700031_g_ScriptId and monsterFlag == 4 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x + rx
                local rz = random(-r,r)
                local z = z + rz
				if title ~="" then
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir, "", title)
				else
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
				
				end
			end
        end
	end

	

end







function x700031_OnDie(sceneId, selfId, killerId)
	
	local nDieCount = GetFubenData_Param(sceneId, x700031_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700031_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	
	local objId1 = GetFubenData_Param(sceneId, x700031_CSP_BOSS1_ID)
	local objId2 = GetFubenData_Param(sceneId, x700031_CSP_BOSS2_ID)
	local objId3 = GetFubenData_Param(sceneId, x700031_CSP_BOSS3_ID)
	local objId4 = GetFubenData_Param(sceneId, x700031_CSP_BOSS4_ID)
	local objId5 = GetFubenData_Param(sceneId, x700031_CSP_BOSS5_ID)
	local finalbossid = GetFubenData_Param(sceneId, x700031_CSP_FINAL_BOSS_ID)

	
	local xianjinboss = GetFubenData_Param(sceneId, x700031_CSP_XIANJINBOSS)
	
	if xianjinboss == selfId then
		CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnXianjinBossDie", sceneId)
	end
	
	if objId1 == selfId then
		SetFubenData_Param(sceneId, x700031_CSP_BOSS1_ID, -1)
		
		SetFubenData_Param(sceneId, x700031_CSP_B_KILL_WUXING, 1)
	elseif objId2 == selfId then
		SetFubenData_Param(sceneId, x700031_CSP_BOSS2_ID, -1)
		SetFubenData_Param(sceneId, x700031_CSP_B_KILL_WUXING, 1)
	elseif objId3 == selfId then
		SetFubenData_Param(sceneId, x700031_CSP_BOSS3_ID, -1)
		SetFubenData_Param(sceneId, x700031_CSP_B_KILL_WUXING, 1)
	elseif objId4 == selfId then
		SetFubenData_Param(sceneId, x700031_CSP_BOSS4_ID, -1)
		SetFubenData_Param(sceneId, x700031_CSP_B_KILL_WUXING, 1)
	elseif objId5 == selfId then
		SetFubenData_Param(sceneId, x700031_CSP_BOSS5_ID, -1)
		SetFubenData_Param(sceneId, x700031_CSP_B_KILL_WUXING, 1)
	elseif finalbossid == selfId then

		local x,z = GetWorldPos(sceneId,finalbossid)
		
		x700031_CreateTalkNpc( sceneId, 1,x,z )

		SetFubenData_Param(sceneId, x700031_CSP_FINAL_BOSS_ID, -1)

		x700031_CreateSubmitNpc( sceneId)
		
		x700031_ShowTipsToAll( sceneId, "成功击杀扈三娘，副本完成。")
	end
end

function x700031_OnAllMonsterDead( sceneId)
	--x700031_CreateSubmitNpc( sceneId)
end

function x700031_OnFubenFailed(sceneId,selfId)
--	x700031_ShowTipsToAll( sceneId, "时迁挂了，副本失败")
	x700031_CreateLeaveNpc( sceneId)
end

function x700031_CreateLeaveNpc( sceneId)
	
	if x700031_g_LeaveNPC.title~= "" then
		CreateMonster(sceneId, x700031_g_LeaveNPC.type, x700031_g_LeaveNPC.x, x700031_g_LeaveNPC.z, 3, 0, -1, x700031_g_LeaveNPC.guid, -1,-1,x700031_g_LeaveNPC.facedir, "", x700031_g_LeaveNPC.title)
	else
		CreateMonster(sceneId, x700031_g_LeaveNPC.type, x700031_g_LeaveNPC.x, x700031_g_LeaveNPC.z, 3, 0, -1, x700031_g_LeaveNPC.guid, -1,-1,x700031_g_LeaveNPC.facedir)
		
	end

	--// add for 现金副本
	 x700031_CreateXianJinBoss(sceneId)
	 --// add end

end



function x700031_CreateSubmitNpc( sceneId)
	
	if x700031_g_SubmitNPC.title~= "" then
		CreateMonster(sceneId, x700031_g_SubmitNPC.type, x700031_g_SubmitNPC.x, x700031_g_SubmitNPC.z, 3, 0, -1, x700031_g_SubmitNPC.guid, -1,-1,x700031_g_SubmitNPC.facedir, "", x700031_g_SubmitNPC.title)
	else
		CreateMonster(sceneId, x700031_g_SubmitNPC.type, x700031_g_SubmitNPC.x, x700031_g_SubmitNPC.z, 3, 0, -1, x700031_g_SubmitNPC.guid, -1,-1,x700031_g_SubmitNPC.facedir)
		
	end

	--// add for 现金副本
	 x700031_CreateXianJinBoss(sceneId)
	 --// add end

	local bKillWuxing = GetFubenData_Param(sceneId, x700031_CSP_B_KILL_WUXING)

	if bKillWuxing<=0 then
		CallScriptFunction( 701120, "OnSceneBossDie", sceneId, 0)
	end
end

----------------------------------------------------------
--创建现金boss
----------------------------------------------------------

function x700031_CreateXianJinBoss(sceneId)
	local nFubenType = GetFubenData_Param(sceneId, x700031_CSP_FUBEN_TYPE)
	if nFubenType ~= 0 then
		return
	end
	
	local nFubenMode = GetFubenData_Param(sceneId, x700031_CSP_FUBEN_MODE)

	if nFubenMode == 0 then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700031_CSP_FUBENLEVEL )
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700031_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700031_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700031_g_ScriptId,nIndexFrom,i)
		if idScript == x700031_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700031_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700031_g_ScriptId, -1, 21,-1,facedir)
			end
			SetFubenData_Param(sceneId, x700031_CSP_XIANJINBOSS, nRet )
		end
	end

	x700031_ShowTipsToAll(sceneId, "翻番宝箱出现！")
end



---------------------------------------------------------------------------------------------------
--进入区域
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
--区域定时器
---------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------
function x700031_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	
	local nFubenType = GetFubenData_Param(sceneId, x700031_CSP_FUBENTYPE);

	if nFubenType~=x700031_g_FubenType then
		return
	end

	local humancount = GetFuben_PlayerCount(sceneId);
--	for	i = 0, humancount - 1 do
--		local humanId = GetFuben_PlayerObjId(sceneId, i);
--		local str = format(" 进入%d",zoneId);
--		BeginQuestEvent(sceneId);
--		AddQuestText(sceneId, str);
--		EndQuestEvent(sceneId);
--		DispatchQuestTips(sceneId, humanId);
--	end

	 --检查玩家GUID
    local nFind = 1
    local guid = GetPlayerGUID( sceneId,selfId )


	
    --not player
    if nFind == 0 then
		return
    end

	local index = x700031_CSP_OBJID_AREA
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


	local nStep = GetFubenData_Param(sceneId, x700031_CSP_GAME_STEP )


	if nStep==2 then --进入区域，开始创建boss
		x700031_CreateBoss2(sceneId)
	end

	
	

end

---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x700031_ProcAreaLeaved( sceneId, selfId, zoneId, MissionId )

	local nFubenType = GetFubenData_Param(sceneId, x700031_CSP_FUBENTYPE);

	if nFubenType~=x700031_g_FubenType then
		return
	end

    local humancount = GetFuben_PlayerCount(sceneId);
--	for	i = 0, humancount - 1 do
--		local humanId = GetFuben_PlayerObjId(sceneId, i);
--		local str = format(" 离开%d",zoneId);
--		BeginQuestEvent(sceneId);
--		AddQuestText(sceneId, str);
--		EndQuestEvent(sceneId);
--		DispatchQuestTips(sceneId, humanId);
--	end

	local index = x700031_CSP_OBJID_AREA
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
function x700031_ProcTiming( sceneId, selfId, ScriptId, MissionId )
	
end

---------------------------------------------------------------------------------------------------
--5个npc对话
---------------------------------------------------------------------------------------------------
--时迁
function x700031_OnNpcTalk1( sceneId, selfId)
	local nStep = GetFubenData_Param(sceneId, x700031_CSP_GAME_STEP )
	if nStep~=0 then
		return
	end

	local bCloseing = GetFubenData_Param(sceneId, x700031_CSP_ISCLOSING);

	if bCloseing==1 then
		return
	end

	SetFubenData_Param(sceneId, x700031_CSP_GAME_STEP, 1 )
	local nNpcId1 = GetFubenData_Param(sceneId, x700031_CSP_NPC1_ID )

	
	NpcTalk(sceneId, nNpcId1, "这是个圈套！时间无多，大家快撤！",  -1)
		
	

	local nRet = 0
	if x700031_g_ShiqianNPC.title~= "" then
		nRet = CreateMonster(sceneId, x700031_g_ShiqianNPC.type, x700031_g_ShiqianNPC.x, x700031_g_ShiqianNPC.z, 3, 0, -1, -1, -1,-1,x700031_g_ShiqianNPC.facedir, "", x700031_g_LeaveNPC.title)
	else
		nRet = CreateMonster(sceneId, x700031_g_ShiqianNPC.type, x700031_g_ShiqianNPC.x, x700031_g_ShiqianNPC.z, 3, 0, -1, -1, -1,-1,x700031_g_ShiqianNPC.facedir)
		
	end
	
	--SetFubenData_Param(sceneId, x700031_CSP_NPC1_ID, nRet )

	
	x700031_CreateMonster2(sceneId)

	local nowTickCount = GetFubenData_Param(sceneId, x700031_CSP_TICKCOUNT)

	
	local nAdd = x700031_g_LimitTotalHoldTime-x700031_g_TaopaoTime-nowTickCount
	if nAdd>0 then
		SetFubenData_Param(sceneId, x700031_CSP_TICKCOUNT_ADD, nAdd)
	elseif nAdd<0 then
		nAdd = -1*nAdd
		SetFubenData_Param(sceneId, x700031_CSP_TICKCOUNT_SUB, nAdd)
	end

	SetFubenData_Param(sceneId, x700031_CSP_TICKCOUNT, x700031_g_LimitTotalHoldTime-x700031_g_TaopaoTime);  
	x700031_SetTempImpassable(sceneId)
end

--金
function x700031_OnNpcTalk2( sceneId, selfId)
	x700031_CreateBoss(sceneId, 0)
end

--木
function x700031_OnNpcTalk3( sceneId, selfId)
	x700031_CreateBoss(sceneId, 1)
end

--水
function x700031_OnNpcTalk4( sceneId, selfId)
	x700031_CreateBoss(sceneId, 2)
end

--火
function x700031_OnNpcTalk5( sceneId, selfId)
	x700031_CreateBoss(sceneId, 3)
end

--土
function x700031_OnNpcTalk6( sceneId, selfId)
	x700031_CreateBoss(sceneId, 4)
end


----------------------------------------------------------------------------------------------
--生成动态阻挡
----------------------------------------------------------------------------------------------
function x700031_SetTempImpassable(sceneId)
	
	
	local arrArea = {Left = 125,Top = 107,Right =  135,Bottom = 114}


	AddSceneTempImpassable(sceneId,arrArea.Left,arrArea.Top,arrArea.Right,arrArea.Bottom)
		
	
end

----------------------------------------------------------------------------------------------
--删除动态阻挡
----------------------------------------------------------------------------------------------
function x700031_ClearTempImpassable(sceneId)
	
	LuaThisScenceM2Wrold( sceneId,"战斗开始",5,1)
	
	local nIndex = x700031_GetBattleSceneType(sceneId)
	
	for i,itm in x700031_g_TempImpassable do
		if itm.Flag == nIndex then
			DelSceneTempImpassable(sceneId,itm.Left,itm.Top,itm.Right,itm.Bottom)
		end
	end
end


