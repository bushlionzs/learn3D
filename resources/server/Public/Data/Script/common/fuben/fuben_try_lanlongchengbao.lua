---------------------------------------------------
-- File: 700223_fuben_dawushi_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700223_CSP_FUBENTYPE				= 	0
x700223_CSP_SCRIPTID				=	1
x700223_CSP_TICKCOUNT				= 	2
x700223_CSP_FROMSCENEID				= 	3
x700223_CSP_ISCLOSING				= 	4
x700223_CSP_LEAVECOUNTDOWN			= 	5
x700223_CSP_TEAMID					=	6
x700223_CSP_BACKSCENEX       		=   7
x700223_CSP_BACKSCENEZ      		=   8
x700223_CSP_FUBENLEVEL			=	9
x700223_CSP_KILLCOUNT				=	20
x700223_CSP_FUBEN_SCENE_ID			=	21
x700223_CSP_BOSS1_ID				=	22
x700223_CSP_BOSS2_ID				=	23
x700223_CSP_BOSS1_FULL_HP			=	24
x700223_CSP_BOSS1_LOADMONSTER		=   25
x700223_CSP_BOSS3_ID				=	26
x700223_CSP_BOSS3_FLAG				=	27

x700223_CSP_CHILD_COUNT				=	40
x700223_CSP_CHILD_ID_START			=	41

x700223_CSP_PATROL_MONSTER_COUNT	=	70
x700223_CSP_PATROL_MONSTER_FULL_HP	=	71
x700223_CSP_PATROL_MONSTER_START	=	72

x700223_CSP_HUMAN_COUNT				=	240
x700223_CSP_OBJID_START				=	241
x700223_CSP_GUID_START              =   248



------------------------Scene System Setting -----------------------------------

x700223_g_ScriptId 					= 700223

------------------------- special for fuben-------------------
x700223_g_OneTime_Child_Count		=	2                       --龙蛋每次刷出小龙数量
x700223_g_Max_Child_Count			=	20                      --龙蛋刷出的小龙同时存在的最大个数
x700223_g_BuffId					=	13503                   --龙蛋被打破后，小龙boss获得的buffid

------------------------- list -----------------------------------------

x700223_g_SubmitNPC                 =   { type =25003,guid= 150545,x = 98, z=25, facedir =0, title = "" }

--BOSS类型
x700223_g_BossCreate				=	{

											{levelmin =20, levelmax=100, name ="成年龙",   type= 27732,  x=73,  z=58,  r=0,  ai=9, aiscript=579,  count=1,  facedir = 0, title = "", flag =0},
											
                                            {levelmin =20, levelmax=100, name ="蓝龙",   type= 27733,  x=98,  z=25,  r=0,  ai=18, aiscript=580,  count=1,  facedir = 0, title = "", flag =1},
											

                                           
										}
										
										
x700223_g_BossCreate2				=	{
                                            {levelmin =20, levelmax=100, name ="龙蛋",   type= 27731,   x=59, z=69,  r=0,  ai=7, aiscript=-1, count=1, facedir = 0, title = ""},
                                            

										}

x700223_g_Child_Dragon				=	{
                                            {levelmin =20, levelmax=100, name ="囚龙城堡小怪2",   type= 27730,   x=59, z=69,  r=1,  ai=9, aiscript=578, count=1, facedir = 0, title = ""},
											

										}


x700223_g_MonsterCreate            =    {

											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=42,  z=108,  r=0,  ai=9, aiscript=577,  count=1,  facedir = 21 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=42,  z=118,  r=0,  ai=9, aiscript=577,  count=1,  facedir = 16 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=50,  z=108,  r=0,  ai=9, aiscript=577,  count=1,  facedir = 21 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=50,  z=118,  r=0,  ai=9, aiscript=577,  count=1,  facedir = 16 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=64,  z=103,  r=0,  ai=9, aiscript=577,  count=1,  facedir = 9  , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=62,  z=98,   r=0,  ai=9, aiscript=577,  count=1,  facedir = 31 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=66,  z=98,   r=0,  ai=9, aiscript=577,  count=1,  facedir = 23 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=63,  z=115,  r=0,  ai=9, aiscript=577,  count=1,  facedir = 27 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=61,  z=120,  r=0,  ai=9, aiscript=577,  count=1,  facedir = 7  , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=65,  z=120,  r=0,  ai=9, aiscript=577,  count=1,  facedir = 12 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=78,  z=104,  r=0,  ai=9, aiscript=577,  count=1,  facedir = 7  , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=76,  z=101,  r=0,  ai=9, aiscript=577,  count=1,  facedir = 7  , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=79,  z=98,   r=0,  ai=9, aiscript=577,  count=1,  facedir = 27 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=76,  z=115,  r=0,  ai=9, aiscript=577,  count=1,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=76,  z=120,  r=0,  ai=9, aiscript=577,  count=1,  facedir = 4  , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=79,  z=117,  r=0,  ai=9, aiscript=577,  count=1,  facedir = 15 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=97,  z=104,  r=0,  ai=9, aiscript=577,  count=1,  facedir = 12 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=94,  z=100,  r=0,  ai=9, aiscript=577,  count=1,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=96,  z=98,   r=0,  ai=9, aiscript=577,  count=1,  facedir = 23 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=94,  z=115,  r=0,  ai=9, aiscript=577,  count=1,  facedir = 27 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=92,  z=120,  r=0,  ai=9, aiscript=577,  count=1,  facedir = 6  , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=96,  z=120,  r=0,  ai=9, aiscript=577,  count=1,  facedir = 14 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=107, z=115,  r=0,  ai=9, aiscript=577,  count=1,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=111, z=114,  r=0,  ai=9, aiscript=577,  count=1,  facedir = 5  , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=110, z=120,  r=0,  ai=9, aiscript=577,  count=1,  facedir = 14 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=115, z=107,  r=0,  ai=9, aiscript=577,  count=1,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=115, z=111,  r=0,  ai=9, aiscript=577,  count=1,  facedir = 21 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=120, z=107,  r=0,  ai=9, aiscript=577,  count=1,  facedir = 21 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=120, z=111,  r=0,  ai=9, aiscript=577,  count=1,  facedir = 14 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=56,  z=38,   r=0,  ai=9, aiscript=577,  count=1,  facedir = 9  , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=60,  z=38,   r=0,  ai=9, aiscript=577,  count=1,  facedir = 9  , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=64,  z=38,   r=0,  ai=9, aiscript=577,  count=1,  facedir = 9  , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=68,  z=38,   r=0,  ai=9, aiscript=577,  count=1,  facedir = 9  , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=56,  z=11,   r=0,  ai=9, aiscript=577,  count=1,  facedir = 27 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=60,  z=11,   r=0,  ai=9, aiscript=577,  count=1,  facedir = 27 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=64,  z=11,   r=0,  ai=9, aiscript=577,  count=1,  facedir = 27 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=68,  z=11,   r=0,  ai=9, aiscript=577,  count=1,  facedir = 27 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=18,  z=33,   r=0,  ai=9, aiscript=577,  count=1,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=13,  z=31,   r=0,  ai=9, aiscript=577,  count=1,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=13,  z=35,   r=0,  ai=9, aiscript=577,  count=1,  facedir = 2  , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=34,  z=34,   r=0,  ai=9, aiscript=577,  count=1,  facedir = 21 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=39,  z=32,   r=0,  ai=9, aiscript=577,  count=1,  facedir = 23 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=36,  z=35,   r=0,  ai=9, aiscript=577,  count=1,  facedir = 9  , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=14,  z=10,   r=0,  ai=9, aiscript=577,  count=1,  facedir = 31 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=18,  z=10,   r=0,  ai=9, aiscript=577,  count=1,  facedir = 25 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=15,  z=15,   r=0,  ai=9, aiscript=577,  count=1,  facedir = 4  , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=20,  z=14,   r=0,  ai=9, aiscript=577,  count=1,  facedir = 16 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=40,  z=10,   r=0,  ai=9, aiscript=577,  count=1,  facedir = 23 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=41,  z=15,   r=0,  ai=9, aiscript=577,  count=1,  facedir = 16 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=38,  z=13,   r=0,  ai=9, aiscript=577,  count=1,  facedir = 27 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=34,  z=13,   r=0,  ai=9, aiscript=577,  count=1,  facedir = 0 , title=""},
											{levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=34,  z=13,   r=0,  ai=9, aiscript=577,  count=1,  facedir = 0 , title=""},
                                                                       
										

                                        }

x700223_g_PatrolMonster				=   {
                                             {levelmin =20, levelmax=100, name ="囚龙城堡小怪1",   type= 27729,  x=60,  z=108,  r=6,  ai=9, aiscript=577,  count=3,  facedir = 21 , title=""},
                                            
                                          
										}

x700223_g_ChangeMonster				=   {
                                            {levelmin =20, levelmax=100, name ="囚龙城堡小怪2",   type= 27730, ai=9, aiscript=578, facedir = 0, title = ""},
										
										}

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700223_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)

end


-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  当副本创建成功时， 开始刷怪和npc
--*********************************************************
-----------------------------------------------------------
function x700223_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  副本场景id
	
	local humancount = GetFuben_PlayerCount(sceneId);
	SetFubenData_Param(sceneId, x700223_CSP_HUMAN_COUNT, humancount);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		SetFubenData_Param(sceneId, x700223_CSP_OBJID_START+i, humanId);
	end

	SetFubenData_Param(sceneId, x700223_CSP_BOSS3_FLAG,-1) 

	x700223_CreateMonster( sceneId )
	x700223_CreateBoss( sceneId )
    x700223_CreatePatrolMonster( sceneId )
		
end



function x700223_EnterTick(sceneId,nowTickCount)

	local nBoss1 = GetFubenData_Param(sceneId, x700223_CSP_BOSS1_ID )
	
	if nBoss1>=0 then
		local humancount = GetFuben_PlayerCount(sceneId);
		if humancount>0 then
			local nCurrentHp = GetHp( sceneId, nBoss1 )
			local nFullHp = GetFubenData_Param(sceneId, x700223_CSP_BOSS1_FULL_HP )
			
			local bCreatedSubMonster = GetFubenData_Param(sceneId, x700223_CSP_BOSS1_LOADMONSTER )
			
			if nFullHp>0 then
				if nCurrentHp/nFullHp <0.9 then
					if bCreatedSubMonster<=0 then
						x700223_CreateBoss2(sceneId)
					end
				end
			end
		end
	end

	local nBoss3Flag = GetFubenData_Param(sceneId, x700223_CSP_BOSS3_FLAG) ;
	if nBoss3Flag>0 then
		if mod(nowTickCount,6) ==0 then  --每30秒
			x700223_CreateChildDragon(sceneId, x700223_g_OneTime_Child_Count)
		end
	end

	local nCount = GetFubenData_Param(sceneId, x700223_CSP_PATROL_MONSTER_COUNT)
	local nCount_dup = nCount;
	local nFullHp = GetFubenData_Param(sceneId, x700223_CSP_PATROL_MONSTER_FULL_HP)
	for i=0, nCount-1 do
		local nObjId = GetFubenData_Param(sceneId, x700223_CSP_PATROL_MONSTER_START+i)
		if nObjId>=0 then
			local nCurrentHp = GetHp( sceneId, nObjId )
			if nCurrentHp/nFullHp<=0.2 then
				SetFubenData_Param(sceneId, x700223_CSP_PATROL_MONSTER_START+i,-1)
				
				local x,z =GetWorldPos(sceneId,nObjId)
				DeleteMonster( sceneId,nObjId )
				x700223_CreateChangeMonster(sceneId,x,z)
				
			end
		end
	end

	for i=0, nCount-1 do
		local nObjId = GetFubenData_Param(sceneId, x700223_CSP_PATROL_MONSTER_START+i)
		
		if nObjId ==-1 then
		
			x700223_ArrayDeleteByIndex(sceneId,x700223_CSP_PATROL_MONSTER_START,nCount,i)
			nCount_dup = nCount_dup -1;
			
		end
	end

	SetFubenData_Param(sceneId, x700223_CSP_PATROL_MONSTER_COUNT,nCount_dup )

	
end

function x700223_ArrayDeleteByIndex(sceneId,arrayId,arrayLen, index)
	if arrayLen< index+1 then
		return
	end

	if arrayLen<=0 or index<0 then
		return
	end

	for i=index, arrayLen-2 do
		local nNextValue = GetFubenData_Param(sceneId, arrayId+i+1)
		SetFubenData_Param(sceneId, arrayId+i,nNextValue)
	end
	
end


function x700223_CreateBoss(sceneId)


	local copyscenelevel = GetFubenData_Param(sceneId, x700223_CSP_FUBENLEVEL ) ;

	
	for i, item in x700223_g_BossCreate do

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
		    local nRet = 0
			if item.title~="" then
				nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700223_g_ScriptId, -1, 21,-1,item.facedir,  "",item.title)
			else
				nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700223_g_ScriptId, -1, 21,-1,item.facedir)
				
			end
			if item.flag ==0 then
				SetFubenData_Param(sceneId, x700223_CSP_BOSS1_ID, nRet ) ;
				local nFullHp = GetHp( sceneId, nRet )
				SetFubenData_Param(sceneId, x700223_CSP_BOSS1_FULL_HP, nFullHp )
				SetFubenData_Param(sceneId, x700223_CSP_BOSS1_LOADMONSTER, 0 )
			elseif item.flag ==1 then
				SetFubenData_Param(sceneId, x700223_CSP_BOSS2_ID, nRet ) ;
			end
        end
	end

end
---------------------------------------------------------------------------------------------------
--创建BOSS2
---------------------------------------------------------------------------------------------------
function x700223_CreateBoss2(sceneId)

	local bCreatedSubMonster = GetFubenData_Param(sceneId, x700223_CSP_BOSS1_LOADMONSTER )

	if bCreatedSubMonster>0 then
		return 0;
	end

	

	local copyscenelevel = GetFubenData_Param(sceneId, x700223_CSP_FUBENLEVEL ) ;

	for i, item in x700223_g_BossCreate2 do

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
		    local nRet = 0
			if item.title~="" then
				nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700223_g_ScriptId, -1, 21,-1,item.facedir,  "",item.title)
			else
				nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700223_g_ScriptId, -1, 21,-1,item.facedir)
			
			end
			SetFubenData_Param(sceneId, x700223_CSP_BOSS3_ID, nRet ) ;
			SetFubenData_Param(sceneId, x700223_CSP_BOSS3_FLAG, 1 ) ;
			break;
        end
	end

	SetFubenData_Param(sceneId, x700223_CSP_BOSS1_LOADMONSTER, 1 )

	local humancount = GetFuben_PlayerCount(sceneId);
	
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		local str = "龙蛋出现";
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, humanId);
	end
end


---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700223_CreateChildDragon(sceneId, nCount)  --龙蛋创建小怪

	local nCurrentChildCount = GetFubenData_Param(sceneId, x700223_CSP_CHILD_COUNT ) ;
	if (nCurrentChildCount+nCount)>x700223_g_Max_Child_Count then
		return
	end

	

    local copyscenelevel = GetFubenData_Param(sceneId, x700223_CSP_FUBENLEVEL ) ;

	local iFlag =0

	for i, item in x700223_g_Child_Dragon do

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
            for j=0,nCount -1 do

                local rx = random(-item.r,item.r)
                local x = item.x + rx
                local rz = random(-item.r,item.r)
                local z = item.z + rz
		        local nRet = 0
				if item.title~="" then
					nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700223_g_ScriptId, -1, 21,-1,item.facedir,  "",item.title)
				else
					nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700223_g_ScriptId, -1, 21,-1,item.facedir)
				
				end
				SetFubenData_Param(sceneId, x700223_CSP_CHILD_ID_START+nCurrentChildCount+iFlag, nRet)
				iFlag = iFlag+1
				SetPatrolId(sceneId, nRet, 2)
            end
			break;
        end
	end

	SetFubenData_Param(sceneId, x700223_CSP_CHILD_COUNT, nCurrentChildCount+nCount)

	local humancount = GetFuben_PlayerCount(sceneId);
	
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		local str = format("%d怪物出现， 地图上总%d 只",nCount,nCurrentChildCount+nCount);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, humanId);
	end

end
---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700223_CreatePatrolMonster(sceneId)
	local copyscenelevel = GetFubenData_Param(sceneId, x700223_CSP_FUBENLEVEL ) ;

	local nCount =0;

	for i, item in x700223_g_PatrolMonster do --创建巡逻怪

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
            for j=0,item.count -1 do

                local rx = random(-item.r,item.r)
                local x = item.x + rx
                local rz = random(-item.r,item.r)
                local z = item.z + rz
		        local nRet = 0
				if item.title~="" then
					nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700223_g_ScriptId, -1, 21,-1,item.facedir,  "",item.title)
				else
					nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700223_g_ScriptId, -1, 21,-1,item.facedir)
				
				end
				SetPatrolId(sceneId, nRet, 0)
				SetFubenData_Param(sceneId, x700223_CSP_PATROL_MONSTER_START + nCount, nRet ) 
				if nCount ==0 then
					local nFullHp = GetHp( sceneId, nRet )
					SetFubenData_Param(sceneId,x700223_CSP_PATROL_MONSTER_FULL_HP, nFullHp ) 
				end
				nCount = nCount +1;
            end
        end
	end
	
	SetFubenData_Param(sceneId, x700223_CSP_PATROL_MONSTER_COUNT, nCount ) 

end

function x700223_CreateChangeMonster(sceneId, x, z)
	 local copyscenelevel = GetFubenData_Param(sceneId, x700223_CSP_FUBENLEVEL ) ;

	for i, item in x700223_g_ChangeMonster do --创建变身怪

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
			if item.title~="" then
				CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir,  "",item.title)
			else
				CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir)
				
			end
			break
            
        end
	end

	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		local str = "一个小怪变身"
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, humanId);
	end
end

function x700223_CreateMonster(sceneId)


    local copyscenelevel = GetFubenData_Param(sceneId, x700223_CSP_FUBENLEVEL ) ;

	for i, item in x700223_g_MonsterCreate do  --创建普通怪

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
            for j=0,item.count -1 do

                local rx = random(-item.r,item.r)
                local x = item.x + rx
                local rz = random(-item.r,item.r)
                local z = item.z + rz
				if item.title~="" then
					CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir,  "",item.title)
				else
					CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir)
									
				end
			end
        end
	end

end


function x700223_OnDie(sceneId, selfId, killerId)
	local nDieCount = GetFubenData_Param(sceneId, x700223_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700223_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;

	local objId1 = GetFubenData_Param(sceneId, x700223_CSP_BOSS1_ID )
	local objId2 = GetFubenData_Param(sceneId, x700223_CSP_BOSS2_ID ) ;
	if selfId ==objId1 then
		SetFubenData_Param(sceneId, x700223_CSP_BOSS1_ID,-1 )
	elseif selfId ==objId2 then
		SetFubenData_Param(sceneId, x700223_CSP_BOSS2_ID,-1 )
		x700223_CreateSubmitNpc( sceneId)

		--//--------------------------- 世界喊话 Start--------------------
			--杀死最终boss
--			local nowTickCount = GetFubenData_Param(sceneId, x700223_CSP_TICKCOUNT)

--			local nowTime = x700223_g_TickTime* nowTickCount;

--			local nMinute = floor(nowTime/60)
--			local nSec = mod(nowTime,60)

				
--			local strPlayerName = GetName(sceneId, killerId)     -- 杀死怪物的玩家名字
--			-------- if killed by pet -----------------
--			local nKillerType = GetObjType(sceneId, killerId)
--			--PrintStr(nKillerType)
--			if nKillerType== 3 then
--				local nOwnerId = GetOwnerID(sceneId, killerId)
--				strPlayerName = GetName(sceneId, nOwnerId)
--			end
--			--------- end -------------------------------
--			local strBossName = GetName(sceneId, selfId)		 -- Boss name	
--			local strKillTime = format("%d分%d秒", nMinute, nSec) -- 杀死关务的事件

			
			
--			--LuaAllScenceM2Wrold (sceneId,x700223_g_FubenName.."玩家"..strPlayerName.."在"..strKillTime.."杀死"..strBossName, 0, 1)
			
			
			--//--------------------------- 世界喊话 end----------------------
	end

	local objId3 = GetFubenData_Param(sceneId, x700223_CSP_BOSS3_ID ) ;
	
	local nBoss3Flag = GetFubenData_Param(sceneId, x700223_CSP_BOSS3_FLAG) ;
	if nBoss3Flag>0 then

		if objId3== selfId then
			SetFubenData_Param(sceneId, x700223_CSP_BOSS3_ID, -1 ) ;
			SetFubenData_Param(sceneId, x700223_CSP_BOSS3_FLAG, 0) ;
			if objId1>=0 then
				SendSpecificImpactToUnit(sceneId, objId1,objId1,objId1, x700223_g_BuffId,0 )
			end
		end
	end
	
	
	local nCurrentChildCount = GetFubenData_Param(sceneId, x700223_CSP_CHILD_COUNT ) ;
	

	for i=0, nCurrentChildCount-1 do
		local nChildObjId = GetFubenData_Param(sceneId, x700223_CSP_CHILD_ID_START+i )
		if nChildObjId==selfId then
			SetFubenData_Param(sceneId, x700223_CSP_CHILD_COUNT, nCurrentChildCount-1 ) ;
			for j=i,nCurrentChildCount-2 do
				local nNextObjId = GetFubenData_Param(sceneId, x700223_CSP_CHILD_ID_START+j+1 )
				SetFubenData_Param(sceneId, x700223_CSP_CHILD_ID_START+j,nNextObjId )
			end
			SetFubenData_Param(sceneId, x700223_CSP_CHILD_ID_START+nCurrentChildCount-1,-1 )
			break;
		end
	end


	local nCount = GetFubenData_Param(sceneId, x700223_CSP_PATROL_MONSTER_COUNT)
	

	for i=0, nCount-1 do
		local nObjId = GetFubenData_Param(sceneId, x700223_CSP_PATROL_MONSTER_START+i)
		
		if nObjId ==selfId then
			SetFubenData_Param(sceneId, x700223_CSP_PATROL_MONSTER_START+i,-1)
			x700223_ArrayDeleteByIndex(sceneId,x700223_CSP_PATROL_MONSTER_START,nCount,i)
			SetFubenData_Param(sceneId, x700223_CSP_PATROL_MONSTER_COUNT,nCount-1 )
		end
	end

	
	
	
end

function x700223_OnAllMonsterDead( sceneId)
	--x700223_CreateSubmitNpc( sceneId)
end

function x700223_CreateSubmitNpc( sceneId)

	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		local str = "副本完成，可以进入下一环了"
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, humanId);
	end

	if x700223_g_SubmitNPC.title~="" then

		CreateMonster(sceneId, x700223_g_SubmitNPC.type, x700223_g_SubmitNPC.x, x700223_g_SubmitNPC.z, 3, 0, -1, x700223_g_SubmitNPC.guid, -1,-1,x700223_g_SubmitNPC.facedir,  "",x700223_g_SubmitNPC.title)
	else
		CreateMonster(sceneId, x700223_g_SubmitNPC.type, x700223_g_SubmitNPC.x, x700223_g_SubmitNPC.z, 3, 0, -1, x700223_g_SubmitNPC.guid, -1,-1,x700223_g_SubmitNPC.facedir)
	
	end
end

--//added in 2009-3-17
---------------------------------------------------------------------------------------------------
--进入区域
---------------------------------------------------------------------------------------------------
function x700223_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x700223_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
end
--//add end





