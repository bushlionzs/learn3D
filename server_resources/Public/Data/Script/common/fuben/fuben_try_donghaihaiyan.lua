---------------------------------------------------
-- File; 700204_fuben_dawushi_scene.lua
-- Author; ZP Wang
-- Created; 2008-12-19
-- Version; 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700204_CSP_FUBENTYPE				= 	0
x700204_CSP_SCRIPTID				=	1
x700204_CSP_TICKCOUNT				= 	2
x700204_CSP_FROMSCENEID				= 	3
x700204_CSP_ISCLOSING				= 	4
x700204_CSP_LEAVECOUNTDOWN			= 	5
x700204_CSP_TEAMID					=	6
x700204_CSP_BACKSCENEX       		=   7
x700204_CSP_BACKSCENEZ      		=   8
x700204_CSP_FUBENLEVEL			=	9
x700204_CSP_KILLCOUNT				=	20
x700204_CSP_FINALBOSS_OBJID			=   21
x700204_CSP_RELIVE_COUNT1			=   22
x700204_CSP_RELIVE_COUNT2			=   23
x700204_CSP_RELIVE_COUNT3			=   24
x700204_CSP_RELIVE_COUNT4			=   25
x700204_CSP_RELIVE_COUNT5			=   26
x700204_CSP_RELIVE_COUNT6			=   27

x700204_CSP_RELIVE_START1			=   40
x700204_CSP_RELIVE_START2			=   50
x700204_CSP_RELIVE_START3			=   60
x700204_CSP_RELIVE_START4			=   70
x700204_CSP_RELIVE_START5			=   80
x700204_CSP_RELIVE_START6			=   90

x700204_B_CREATE_RANDOMBOSS			=	230
x700204_CSP_RANDOM_BOSS_ID			=	231
x700204_RANDOMBOSS_FLAG				=	232
x700204_CSP_GUID_START              =   248


------------------------Scene System Setting -----------------------------------

x700204_g_ScriptId 					= 700204


x700204_RefreshTime					= 360		                --复生怪复生时间
x700204_g_RandomBossRate			= 0                         --隐藏boss出现几率
x700204_g_RandomMonsterRate			= 0                       --隐藏boss出现几率
x700204_g_EnterBuffId				= 14309                     --进入副本给予的buff

x700204_g_SubmitNPC                 =   { type =25005,guid= 150505,x = 27, z=100, facedir = 0, title = "" }

--BOSS类型
x700204_g_NpcType1                  =   25005                    --NPC ID
x700204_g_NpcGroup                  =   {
											{   hash = 1,type = x700204_g_NpcType1,x=23,z=22,ai=3,aiscript = 0, guid= 150002, facedir=0, title=""  },
										}


-- Random 怪物

x700204_g_Monster_Random_Create		=	{
											{levelmin =20, levelmax=29, name ="坐骑boss",   type= 27213,   x=27, z=103, r=0,  ai=18, aiscript=634,  facedir = 0, title = "",flag=0},
											
											{levelmin =20, levelmax=29, name ="坐骑boss",   type= 27221,   x=27, z=103, r=0,  ai=18, aiscript=634,  facedir = 0, title = "",flag=1},
											

                                            {levelmin =20, levelmax=29, name ="坐骑boss",   type= 27229,   x=27, z=103, r=0,  ai=18, aiscript=634,  facedir = 0, title = "",flag=2},
											
											{levelmin =20, levelmax=29, name ="坐骑boss",   type= 27237,   x=27, z=103, r=0,  ai=18, aiscript=634,  facedir = 0, title = "",flag=3},
											



										}

x700204_g_BossCreate				=	{
											{levelmin =20, levelmax=100, name ="三头龙",   type= 27738,   x=27, z=103, r=0,  ai=18, aiscript=611, facedir = 0, title = "", flag = 1},
											

											{levelmin =20, levelmax=100, name ="蝠鲼",   type= 27737,   x=79, z=44, r=0,  ai=9, aiscript=612, facedir = 0, title = "", flag = 0},
											

										}


---------  随机boss 
x700204_g_Random_Boss_Type_Count = 4
x700204_g_Random_Boss			=	{  	--随机Boss
											{levelmin =20, levelmax=29, name ="隐藏boss3",   type= 27213, ai=18, aiscript=639, facedir = 0, title = "", flag=0},
											

											{levelmin =20, levelmax=29, name ="隐藏boss3",   type= 27221, ai=18, aiscript=639, facedir = 0, title = "", flag=1},
											

											{levelmin =20, levelmax=29, name ="隐藏boss3",   type= 27229, ai=18, aiscript=639, facedir = 0, title = "", flag=2},
											

                                            {levelmin =20, levelmax=29, name ="隐藏boss3",   type= 27237, ai=18, aiscript=639, facedir = 0, title = "", flag=3},
                                            

										}
-- 巡逻怪1
x700204_g_MonsterCreate1			=   {
											{levelmin =20, levelmax=100, name ="龙穴巡逻怪",   type= 27735,  x=61,  z=36,   r=0,  ai=9, aiscript=609, count=1, facedir = 0, title = ""},
											
                                            
                                            {levelmin =20, levelmax=100, name ="龙穴巡逻怪",   type= 27735,  x=60,  z=36,   r=0,  ai=9, aiscript=609, count=1, facedir = 0, title = ""},
											

                                            {levelmin =20, levelmax=100, name ="龙穴巡逻怪",   type= 27735,  x=59,  z=36,   r=0,  ai=9, aiscript=609, count=1, facedir = 0, title = ""},
											

										}   
									
-- 巡逻怪2									 
x700204_g_MonsterCreate2			=   {
											{levelmin =20, levelmax=100, name ="龙穴巡逻怪",   type= 27735,  x=61,  z=58,   r=0,  ai=9, aiscript=609, count=1, facedir = 0, title = ""},
											
									}

-- 巡逻怪3									 
x700204_g_MonsterCreate3			=   {
											{levelmin =20, levelmax=100, name ="龙穴巡逻怪",   type= 27735,  x=80,  z=84,   r=0,  ai=9, aiscript=609, count=1, facedir = 0, title = ""},
											
										}


--重生怪
x700204_g_MonsterCreate4  	=	{
										  {levelmin =20, levelmax=100, name ="龙穴复生怪",   type= 27736,  x=52, z=99, r=2,  ai=14, aiscript=610, count=7, facedir = 0, title = "", flag = 0},
										  

										  {levelmin =20, levelmax=100, name ="龙穴复生怪",   type= 27736,  x=75, z=92,r=2,   ai=14, aiscript=610, count=7, facedir = 0, title = "", flag = 1},
										 

                                          {levelmin =20, levelmax=100, name ="龙穴复生怪",   type= 27736,  x=70, z=79, r=2,   ai=14, aiscript=610, count=7, facedir = 0, title = "", flag = 2},
										  

										  {levelmin =20, levelmax=100, name ="龙穴复生怪",   type= 27736,  x=48, z=75, r=2,   ai=14, aiscript=610, count=7, facedir = 0, title = "", flag = 3},
										  

										  {levelmin =20, levelmax=100, name ="龙穴复生怪",   type= 27736,  x=40, z=60, r=2,   ai=14, aiscript=610, count=7, facedir = 0, title = "", flag = 4},
										  

										  {levelmin =20, levelmax=100, name ="龙穴复生怪",   type= 27736,  x=66, z=56, r=2,   ai=14, aiscript=610, count=7, facedir = 0, title = "", flag = 5},
										 

										}

x700204_g_MonsterCreate_Normal	= {

											{levelmin =20, levelmax=100, name ="龙穴小怪",   type= 27734,  x=43, z=29,    ai=9, aiscript=608,  facedir = 0, title = "" },
											
                                            {levelmin =20, levelmax=100, name ="龙穴小怪",   type= 27734,  x=44, z=37,    ai=9, aiscript=608,  facedir = 0, title = "" },
											

                                            {levelmin =20, levelmax=100, name ="龙穴小怪",   type= 27734,  x=53, z=39,    ai=9, aiscript=608,  facedir = 0, title = "" },
											

                                            {levelmin =20, levelmax=100, name ="龙穴小怪",   type= 27734,  x=62, z=39,    ai=9, aiscript=608,  facedir = 0, title = "" },
											
                                            {levelmin =20, levelmax=100, name ="龙穴小怪",   type= 27734,  x=68, z=34,    ai=9, aiscript=608,  facedir = 0, title = "" },
											




										}


-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700204_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)
	
end



-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  ;  当副本创建成功时， 开始刷怪和npc
--*********************************************************
-----------------------------------------------------------
function x700204_OnFubenSceneCreated( sceneId )
	-- @Param sceneId;  副本场景id

	SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START1,0);
	SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START2,0);
	SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START3,0);
	SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START4,0);
	SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START5,0);
	SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START6,0);
	

	x700204_CreateBoss( sceneId )
	x700204_CreateRandomBoss( sceneId )
    x700204_CreateMonster( sceneId )

	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		 x700204_AddPlayerBuff(sceneId, humanId,1)
	end
		
end



function x700204_AddPlayerBuff(sceneId, selfId, nFlag)
	local haveImpact = IsHaveSpecificImpact( sceneId, selfId, x700204_g_EnterBuffId )
	if haveImpact == 1 then
		
		if nFlag == 1 then
			return
		end
		CancelSpecificImpact(sceneId, selfId, x700204_g_EnterBuffId);
		
	end

	

	SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId, x700204_g_EnterBuffId,0 )
end

function x700204_RemovePlayerBuff(sceneId, selfId)
	local haveImpact = IsHaveSpecificImpact( sceneId, selfId, x700204_g_EnterBuffId )
	if haveImpact == 1 then

		CancelSpecificImpact(sceneId, selfId, x700204_g_EnterBuffId);
	end
end


-----------------------------------------------------------
--*********************************************************
--EnterTick  :  副本心跳
--*********************************************************
-----------------------------------------------------------
function x700204_EnterTick(sceneId, nowTickCount)
    if nowTickCount > 6 then
       if mod(nowTickCount, x700204_RefreshTime) == 0 then
			x700204_CheckReliveMonster(sceneId)
	   end
    end
end



function x700204_CreateBoss(sceneId)


	local copyscenelevel = GetFubenData_Param(sceneId, x700204_CSP_FUBENLEVEL ) ;

	
	for i, item in x700204_g_BossCreate do --创建Boss

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
		    local nRet = 0
			if item.title~="" then
				nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700204_g_ScriptId, -1, 21,-1,item.facedir,  "",item.title)
			else
				nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700204_g_ScriptId, -1, 21,-1,item.facedir)
			end

			if item.flag ==1 then
				SetFubenData_Param(sceneId, x700204_CSP_FINALBOSS_OBJID, nRet ) ;
			end
        end
	end

end

function x700204_CreateRandomBoss(sceneId)


	local rate = random(0,100)/100;
	if rate>= x700204_g_RandomBossRate then
		return 0;
	end

	local nFlag = random(0,3)

	local nType = random(0,x700204_g_Random_Boss_Type_Count-1)

	local copyscenelevel = GetFubenData_Param(sceneId, x700204_CSP_FUBENLEVEL ) ;


	
	
	for i, item in x700204_g_Random_Boss do  --创建随机Boss
		if nType == item.flag then
			if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
				local x,z;
				if nFlag==0 then
					x = 32
					z = 68
				else
					x = 91
					z = 80
				end
				if item.title~="" then
					CreateMonster(sceneId, item.type, x,z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir,  "",item.title)
				else
					CreateMonster(sceneId, item.type, x,z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir)
				end
			end
		end
		
	end

end




---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700204_CreateMonster(sceneId)


    local copyscenelevel = GetFubenData_Param(sceneId, x700204_CSP_FUBENLEVEL ) ;

	for i, item in x700204_g_MonsterCreate1 do --创建巡逻怪0

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
            for j=0,item.count -1 do

                local rx = random(-item.r,item.r)
                local x = item.x + rx
                local rz = random(-item.r,item.r)
                local z = item.z + rz
		        local monsterid = 0
				if item.title~="" then
					monsterid = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir,  "",item.title)
				else
					monsterid = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir)
				end

				SetPatrolId(sceneId, monsterid, 0)
            end
        end
	end

	for i, item in x700204_g_MonsterCreate2 do --创建巡逻怪1

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
            for j=0,item.count -1 do

                local rx = random(-item.r,item.r)
                local x = item.x + rx
                local rz = random(-item.r,item.r)
                local z = item.z + rz
		        local monsterid = 0;
				if item.title ~="" then
					monsterid = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir, "", item.title)
				else
					monsterid = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir)
				end

				SetPatrolId(sceneId, monsterid, 1)
            end
        end
	end

	for i, item in x700204_g_MonsterCreate3 do --创建巡逻怪2

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
            for j=0,item.count -1 do

                local rx = random(-item.r,item.r)
                local x = item.x + rx
                local rz = random(-item.r,item.r)
                local z = item.z + rz
		        local monsterid = 0
				if item.title~="" then
					monsterid = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir, "", item.title)
				else
					monsterid = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir)
				end
				SetPatrolId(sceneId, monsterid, 2)
            end
        end
	end

	for i, item in x700204_g_MonsterCreate_Normal do ---创建普通怪

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
           
			if item.title~="" then
				CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir, "", item.title)
			else
				CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir)
			end
        end
	end

	for i, item in x700204_g_MonsterCreate4 do  --创建复生怪

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
            for j=0,item.count -1 do

                local rx = random(-item.r,item.r)
                local x = item.x + rx
                local rz = random(-item.r,item.r)
                local z = item.z + rz

		        local nRet = 0;
				if item.title~="" then
					nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700204_g_ScriptId, -1, 21,-1,item.facedir, "", item.title);
				else
					nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700204_g_ScriptId, -1, 21,-1,item.facedir);
				end

				if item.flag == 0 then
					local nCount = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START1);
		
					SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START1,nCount+1);
					SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START1+nCount+1, nRet);
				elseif item.flag ==1 then
					local nCount = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START2);
		
					SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START2,nCount+1);
					SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START2+nCount+1, nRet);
				elseif item.flag==2 then
					local nCount = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START3);
		
					SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START3,nCount+1);
					SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START3+nCount+1, nRet);
				elseif item.flag==3 then
					local nCount = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START4);
		
					SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START4,nCount+1);
					SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START4+nCount+1, nRet);
				elseif item.flag==4 then
					local nCount = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START5);
		
					SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START5,nCount+1);
					SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START5+nCount+1, nRet);
				elseif item.flag==5 then
					local nCount = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START6);
		
					SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START6,nCount+1);
					SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START6+nCount+1, nRet);
				end
				
				
            end
        end
	end

end

function x700204_ReliveMonster( sceneId, index, index2)  --复生怪复生

	
	 local copyscenelevel = GetFubenData_Param(sceneId, x700204_CSP_FUBENLEVEL ) ;

	for i, item in x700204_g_MonsterCreate4 do

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
			if index == item.flag then
				 local rx = random(-item.r,item.r)
				 local x = item.x + rx
				 local rz = random(-item.r,item.r)
				 local z = item.z + rz	

				 local nRet = 0
				 if item.title~="" then
					nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700204_g_ScriptId, -1, 21,  "",item.title)
				 else
				 	nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700204_g_ScriptId, -1, 21)
				 end

				 if index ==0 then
					SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START1+index2, nRet);
				 elseif index==1 then
					SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START2+index2, nRet);
				 elseif index==2 then
					SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START3+index2, nRet);
				 elseif index==3 then
					SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START4+index2, nRet);
				 elseif index==4 then
					SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START5+index2, nRet);
				 elseif index==5 then
					SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START6+index2, nRet);
				 end
				 
				 return 1;
			end
		end
	end
end

function x700204_CheckReliveMonster(sceneId)
	local n1 = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START1);
	local n2 = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START2);
	local n3 = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START3);
	local n4 = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START4);
	local n5 = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START5);
	local n6 = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START6);

	

	for i=1, n1 do
		local nObjId = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START1+i);
		
		if nObjId == -1 then
			
			x700204_ReliveMonster( sceneId, 0, i);
			
		end
	end

	for i=1, n2 do
		local nObjId = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START2+i);
		
		if nObjId == -1 then
			
			x700204_ReliveMonster( sceneId, 1,i);
			
		end
	end

	for i=1, n3 do
		local nObjId = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START3+i);
		if nObjId == -1 then
			x700204_ReliveMonster( sceneId, 2,i);
			
		end
	end

	for i=1, n4 do
		local nObjId = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START4+i);
		if nObjId == -1 then
			x700204_ReliveMonster( sceneId, 3,i);
			
		end
	end

	for i=1, n5 do
		local nObjId = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START5+i);
		if nObjId == -1 then
			x700204_ReliveMonster( sceneId, 4,i);
			
		end
	end

	for i=1, n6 do
		local nObjId = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START6+i);
		
		if nObjId == -1 then
			x700204_ReliveMonster( sceneId, 5,i);
			
		end
	end
end

---------------------------------------------------------------------------------------------------
--创建NPC
---------------------------------------------------------------------------------------------------
function x700204_CreateNpc(sceneId )

  	for i, item in x700204_g_NpcGroup do
  		if item.title~="" then
			CreateMonster( sceneId,item.type,item.x,item.z,item.ai,item.aiscript,-1,item.guid,-1,-1, item.facedir, "", item.title)
		else
			CreateMonster( sceneId,item.type,item.x,item.z,item.ai,item.aiscript,-1,item.guid,-1,-1, itme.facedir)
		end
	end
end



function x700204_CreateRandomMonster(sceneId)


	local rate = random(0,100)/100;
	if rate>= x700204_g_RandomMonsterRate then
		return 0;
	end

	local nFlag = random(0,3)

	

	local copyscenelevel = GetFubenData_Param(sceneId, x700204_CSP_FUBENLEVEL ) ;


	
	
	for i, item in x700204_g_Monster_Random_Create do --创建随机monster
		if item.flag == nFlag then
			if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
				local nBossID =0;
				if item.title~="" then
					nBossID = CreateMonster(sceneId, item.type, item.x,item.z, item.ai, item.aiscript, x700204_g_ScriptId, -1, 21,-1,item.facedir,  "",item.title)
				else
					nBossID = CreateMonster(sceneId, item.type, item.x,item.z, item.ai, item.aiscript, x700204_g_ScriptId, -1, 21,-1,item.facedir)
				
				end

				SetFubenData_Param(sceneId, x700204_B_CREATE_RANDOMBOSS, 1)
				SetFubenData_Param(sceneId, x700204_RANDOMBOSS_FLAG, nFlag)

				SetFubenData_Param(sceneId, x700204_CSP_RANDOM_BOSS_ID, nBossID)
			end
		end
	end

	x700204_ShowTipsToAll(sceneId, "战神再现！")

end

function x700204_OnDie(sceneId, selfId, killerId)
	local nDieCount = GetFubenData_Param(sceneId, x700204_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700204_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	
	--// add for random boss event, add in 2009-5-20
	local bCreateRandomboss = GetFubenData_Param(sceneId, x700204_B_CREATE_RANDOMBOSS)

	if bCreateRandomboss>0 then
		local nRandomBossId = GetFubenData_Param(sceneId, x700204_CSP_RANDOM_BOSS_ID)
		if nRandomBossId==selfId then
			--//--------------------------- 世界喊话 Start--------------------
			--杀死Random boss
			
			
			-------- if killed by pet -----------------
			local nKillerType = GetObjType(sceneId, killerId)
			local nOwnerId = killerId
			if nKillerType== 3 then
				nOwnerId = GetOwnerID(sceneId, killerId)
				
			end
			--------- end -------------------------------
			local strPlayerName = GetName(sceneId, nOwnerId)
			
			local nCountry = GetCurCountry( sceneId, nOwnerId )
			local strCountryName = "";
			if nCountry==0 then
				strCountryName = "楼兰"
			elseif nCountry==1 then
				strCountryName = "天山"
			elseif nCountry==2 then
				strCountryName = "昆仑"
			elseif nCountry==3 then
				strCountryName = "敦煌"
			end

			local strHorseName = ""

			local nHorseFlag = GetFubenData_Param(sceneId, x700204_RANDOMBOSS_FLAG);

			if nHorseFlag==0 then
				strHorseName = "凶豹"
			elseif nHorseFlag==1 then
				strHorseName = "奔羚"
			elseif nHorseFlag==2 then
				strHorseName = "天鹅"
			elseif nHorseFlag==3 then
				strHorseName = "河马"
			end


			local strMapName = "龙穴"
			
			----LuaAllScenceM2Wrold (sceneId,strCountryName.."的"..strPlayerName.."打败了"..strMapName.."的九旄战神，九旄丢下"..strHorseName.."落荒而逃！", 5, 1)
			
			
			--//--------------------------- 世界喊话 end----------------------
		end
	end
	--//add end

	local objId1 = GetFubenData_Param(sceneId, x700204_CSP_FINALBOSS_OBJID ) ;

--	--//--------------------------- 世界喊话 Start--------------------
--	
--	local nowTickCount = GetFubenData_Param(sceneId, x700204_CSP_TICKCOUNT)
--
--	local nowTime = x700204_g_TickTime* nowTickCount;
--
--	local nMinute = floor(nowTime/60)
--	local nSec = mod(nowTime,60)
--
--		
--	local strPlayerName = GetName(sceneId, killerId)     -- 杀死怪物的玩家名字
--	-------- if killed by pet -----------------
--	local nKillerType = GetObjType(sceneId, killerId)
--	--PrintStr(nKillerType)
--	if nKillerType== 3 then
--		local nOwnerId = GetOwnerID(sceneId, killerId)
--		strPlayerName = GetName(sceneId, nOwnerId)
--	end
--	--------- end -------------------------------
--	
--	local strBossName = GetName(sceneId, selfId)		 -- Boss name	
--	local strKillTime = format("%d分%d秒", nMinute, nSec) -- 杀死关务的事件
--	
--	
--	if selfId == objId1 then -- boss flag=0
--		----LuaAllScenceM2Wrold (sceneId,"#R三头凶蛟无力地喷出了最后一口恶毒的火焰，绝望地闭上了眼睛，它怎么也想不到曾经击败了蒙古精锐部队的它，被#G"..strPlayerName.."#R带领的队伍仅用了#G"..strKillTime.."#R就彻底地打败了。", 0, 1)
--	end
--
--	
--	
--	--//--------------------------- 世界喊话 end----------------------

	if objId1>=0 then
		if objId1== selfId then
			SetFubenData_Param(sceneId, x700204_CSP_FINALBOSS_OBJID,-1 )
			x700204_CreateSubmitNpc( sceneId)

			x700204_CreateRandomMonster(sceneId)
		end
	end

	local n1 = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START1);
	local n2 = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START2);
	local n3 = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START3);
	local n4 = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START4);
	local n5 = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START5);
	local n6 = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START6);

	

	for i=1, n1 do
		local nObjId = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START1+i);
		if nObjId == selfId then
			SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START1+i, -1);
			return 1;
		end
	end

	for i=1, n2 do
		local nObjId = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START2+i);
		if nObjId == selfId then
			SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START2+i, -1);
			return 1;
		end
	end

	for i=1, n3 do
		local nObjId = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START3+i);
		if nObjId == selfId then
			SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START3+i, -1);
			return 1;
		end
	end

	for i=1, n4 do
		local nObjId = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START4+i);
		if nObjId == selfId then
			SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START4+i, -1);
			return 1;
		end
	end

	

	for i=1, n5 do
		local nObjId = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START5+i);
		
		if nObjId == selfId then
			SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START5+i, -1);
			return 1;
		end
	end

	for i=1, n6 do
		local nObjId = GetFubenData_Param(sceneId, x700204_CSP_RELIVE_START6+i);
		if nObjId == selfId then
			SetFubenData_Param(sceneId, x700204_CSP_RELIVE_START6+i, -1);
			return 1;
		end
	end
	
				
end

function x700204_OnAllMonsterDead( sceneId)
	
	--x700204_CreateMonster3( sceneId )
	--x700204_CreateNpc( sceneId )
	x700204_CreateSubmitNpc( sceneId)
end

function x700204_CreateSubmitNpc( sceneId)
	if x700204_g_SubmitNPC.title~="" then
		CreateMonster(sceneId, x700204_g_SubmitNPC.type, x700204_g_SubmitNPC.x, x700204_g_SubmitNPC.z, 3, 0, -1, x700204_g_SubmitNPC.guid, -1,-1,x700204_g_SubmitNPC.facedir, "", x700204_g_SubmitNPC.title)
	else
		CreateMonster(sceneId, x700204_g_SubmitNPC.type, x700204_g_SubmitNPC.x, x700204_g_SubmitNPC.z, 3, 0, -1, x700204_g_SubmitNPC.guid, -1,-1,x700204_g_SubmitNPC.facedir)
		
	end
end


---------------------------------------------------------------------------------------------------
--玩家死亡
---------------------------------------------------------------------------------------------------
function x700204_OnPlayerDie(sceneId, selfId, killerId)
end



--//added in 2009-3-17
---------------------------------------------------------------------------------------------------
--进入区域
---------------------------------------------------------------------------------------------------
function x700204_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x700204_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
end
--//add end


function x700204_ShowTipsToAll(sceneId, str)

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





