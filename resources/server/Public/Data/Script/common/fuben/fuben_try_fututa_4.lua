---------------------------------------------------
-- File: 700222_fuben_dawushi_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700222_CSP_FUBENTYPE				= 	0
x700222_CSP_SCRIPTID				=	1
x700222_CSP_TICKCOUNT				= 	2
x700222_CSP_FROMSCENEID				= 	3
x700222_CSP_ISCLOSING				= 	4
x700222_CSP_LEAVECOUNTDOWN			= 	5
x700222_CSP_TEAMID					=	6
x700222_CSP_BACKSCENEX       		=   7
x700222_CSP_BACKSCENEZ      		=   8
x700222_CSP_FUBENLEVEL			=	9

x700222_CSP_KILLCOUNT				=	20
x700222_CSP_FUBEN_SCENE_ID			=	21

x700222_CSP_NPC_ID					=	22
x700222_CSP_CURRENTSTEP				=	23
x700222_CSP_CURRENTSTEP_TICKCOUNT	=	24
x700222_CSP_MONSTER_COUNT			=	25
x700222_CSP_BOSS_ID					=	26
x700222_CSP_FUBENLEVEL_DUP		=	27

x700222_CSP_TWO_TYPE_START			=	30
x700222_CSP_THREE_TYPE_START		=	35

x700222_CSP_HUMAN_TALKPARAM_START	=	230
x700222_CSP_HUMAN_COUNT				=	240
x700222_CSP_OBJID_START				=	241
x700222_CSP_NEXT_SCENE				=   248
x700222_CSP_GUID_START              =   248


------------------------Scene System Setting -----------------------------------

x700222_g_ScriptId 					= 700222                    --脚本号


---------------------------- special for fuben -----------------------------
x700222_g_nTextCount				= 4
x700222_g_NpcTalkText				= { "它们会从四面八方涌来","出现的怪物要及时杀掉","不要手软，勇士！","它们的出现威胁到王国的安危！"}

x700222_g_TimeDriverList			= {2,3,3,3,10,3,3,3,10,3,3,3,10,3,3,3,10,5,5,5,16,5,5,5,16,5,5,5,16,5,5,5,16,1,12,1,30,1,12,1,30,1,12,1,30,1,12,1,30,1,12,1,30,1,12,1,30,1,12,1,30,1,12,1,30}


------------------------- list -----------------------------------------

x700222_g_SubmitNPC                 =   { type =25024,guid= 150525,x = 65, z=60, facedir =0, title="" }

x700222_g_GameNPC                 =   { type =25024,guid= 150525,x = 54, z=48, facedir=0, title="" }

--BOSS类型
x700222_g_BossCreate				=	{
                                            {levelmin =20, levelmax=100, name ="巨掌玄冰",   type= 27743,  x=65,  z=21,  r=0,  ai=9, aiscript=511, flag = 0, count=1, facedir = 0, patrolid = 0, title = ""},
                                           

                                            
										}
										



--x700222_g_MonsterCreate            =    {
--                                            {levelmin = 40, levelmax=100, name ="狂热信徒",   type= 26064,  x=15.77 , z=66.24 ,   r=0,  ai=9, aiscript=571,count=1, facedir = 0, title = ""},
--                                            
--
--
--                                        }

--12个坐标点和对应路径id
x700222_g_PointList	=		{
								{flag=1,	x=65, 	z= 21 ,	patrolid = 0},
								{flag=2,	x=58, 	z= 21 ,	patrolid = 1},
								{flag=3,	x=71, 	z= 21 ,	patrolid = 2},
								{flag=4,	x=25, 	z= 59 ,	patrolid = 3},
								{flag=5,	x=25, 	z= 53 ,	patrolid = 4},
								{flag=6,	x=25, 	z= 66 ,	patrolid = 5},
								{flag=7,	x=65, 	z= 102,	patrolid = 0},
								{flag=8,	x=58, 	z= 102,	patrolid = 1},
								{flag=9,	x=71, 	z= 102,	patrolid = 2},
								{flag=10,	x=108, 	z= 59 ,	patrolid = 3},
								{flag=11,	x=108, 	z= 53 ,	patrolid = 4},
								{flag=12,	x=108, 	z= 66 ,	patrolid = 5},
							}

--4个中随机2种可能的组合
x700222_g_C42 = {{1,2},{1,3},{1,4},{2,3},{2,4},{3,4}}
--4各种随机3种可能的组合
x700222_g_C43 = {{1,2,3},{2,3,4},{1,3,4},{1,2,4}};	

--四种怪物ObjId 表
x700222_g_Monster_ObjList = {

                                {flag=1, levelmin =20, levelmax=100, type= 27739, ai=9, aiscript=504},
                               
                                {flag=2, levelmin =20, levelmax=100, type= 27740, ai=9, aiscript=505},
                                
                                {flag=3, levelmin =20, levelmax=100, type= 27741, ai=9, aiscript=506},
                                

                                {flag=4, levelmin =20, levelmax=100, type= 27742, ai=9, aiscript=510},
                                

							}

	
--创建怪物的信息
x700222_g_MonsterCreate =	{
								--第1波
								{timeflag=1, pointlist = {1},	objflag = 1},
								{timeflag=2, pointlist = {4},	objflag = 1},
								{timeflag=3, pointlist = {7},	objflag = 1},
								{timeflag=4, pointlist = {10},	objflag = 1},

								--第2波
								{timeflag=5, pointlist = {1},	objflag = 2},
								{timeflag=6, pointlist = {4},	objflag = 2},
								{timeflag=7, pointlist = {7},	objflag = 2},
								{timeflag=8, pointlist = {10},	objflag = 2},

								--第3波
								{timeflag=9,  pointlist = {1},	objflag = 3},
								{timeflag=10, pointlist = {4},	objflag = 3},
								{timeflag=11, pointlist = {7},	objflag = 3},
								{timeflag=12, pointlist = {10},	objflag = 3},

								--第4波
								{timeflag=13, pointlist = {1},	objflag = 4},
								{timeflag=14, pointlist = {4},	objflag = 4},
								{timeflag=15, pointlist = {7},	objflag = 4},
								{timeflag=16, pointlist = {10},	objflag = 4},

								--第5波
								{timeflag=17, pointlist = {2,3},	objflag = 5},
								{timeflag=18, pointlist = {5,6},	objflag = 5},
								{timeflag=19, pointlist = {8,9},	objflag = 5},
								{timeflag=20, pointlist = {11,12},	objflag = 5},

								--第6波
								{timeflag=21, pointlist = {2,3},	objflag = 6},
								{timeflag=22, pointlist = {5,6},	objflag = 6},
								{timeflag=23, pointlist = {8,9},	objflag = 6},
								{timeflag=24, pointlist = {11,12},	objflag = 6},

								--第7波
								{timeflag=25, pointlist = {2,3},	objflag = 7},
								{timeflag=26, pointlist = {5,6},	objflag = 7},
								{timeflag=27, pointlist = {8,9},	objflag = 7},
								{timeflag=28, pointlist = {11,12},	objflag = 7},

								--第8波
								{timeflag=29, pointlist = {2,3},	objflag = 8},
								{timeflag=30, pointlist = {5,6},	objflag = 8},
								{timeflag=31, pointlist = {8,9},	objflag = 8},
								{timeflag=32, pointlist = {11,12},	objflag = 8},

								--第9波
								{timeflag=33, pointlist = {1,2,3},		objflag = 9},
								{timeflag=34, pointlist = {4,5,6},		objflag = 9},
								{timeflag=35, pointlist = {7,8,9},		objflag = 9},
								{timeflag=36, pointlist = {10,11,12},	objflag = 9},

								--第10波
								{timeflag=37, pointlist = {1,2,3},		objflag = 10},
								{timeflag=38, pointlist = {4,5,6},		objflag = 10},
								{timeflag=39, pointlist = {7,8,9},		objflag = 10},
								{timeflag=40, pointlist = {10,11,12},	objflag = 10},

								--第11波
								{timeflag=41, pointlist = {1,2,3},		objflag = 11},
								{timeflag=42, pointlist = {4,5,6},		objflag = 11},
								{timeflag=43, pointlist = {7,8,9},		objflag = 11},
								{timeflag=44, pointlist = {10,11,12},	objflag = 11},

								--第12波
								{timeflag=45, pointlist = {1,2,3},		objflag = 12},
								{timeflag=46, pointlist = {4,5,6},		objflag = 12},
								{timeflag=47, pointlist = {7,8,9},		objflag = 12},
								{timeflag=48, pointlist = {10,11,12},	objflag = 12},

								--第13波
								{timeflag=49, pointlist = {1,2,3},		objflag = 13},
								{timeflag=50, pointlist = {4,5,6},		objflag = 13},
								{timeflag=51, pointlist = {7,8,9},		objflag = 13},
								{timeflag=52, pointlist = {10,11,12},	objflag = 13},
								
								--第14波
								{timeflag=53, pointlist = {1,2,3},		objflag = 14},
								{timeflag=54, pointlist = {4,5,6},		objflag = 14},
								{timeflag=55, pointlist = {7,8,9},		objflag = 14},
								{timeflag=56, pointlist = {10,11,12},	objflag = 14},
								
								--第15波
								{timeflag=57, pointlist = {1,2,3},		objflag = 15},
								{timeflag=58, pointlist = {4,5,6},		objflag = 15},
								{timeflag=59, pointlist = {7,8,9},		objflag = 15},
								{timeflag=60, pointlist = {10,11,12},	objflag = 15},
								
								--第16波
								{timeflag=61, pointlist = {1,2,3},		objflag = 16},
								{timeflag=62, pointlist = {4,5,6},		objflag = 16},
								{timeflag=63, pointlist = {7,8,9},		objflag = 16},
								{timeflag=64, pointlist = {10,11,12},	objflag = 16},
								
						    }

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700222_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)

end


-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  当副本创建成功时， 开始刷怪和npc
--*********************************************************
-----------------------------------------------------------
function x700222_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  副本场景id

	local humancount = GetFuben_PlayerCount(sceneId);
	SetFubenData_Param(sceneId, x700222_CSP_HUMAN_COUNT, humancount);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		SetFubenData_Param(sceneId, x700222_CSP_OBJID_START+i, humanId);
	end

	SetFubenData_Param(sceneId, x700222_CSP_CURRENTSTEP, 1)
	SetFubenData_Param( sceneId, x700222_CSP_BOSS_ID, -1)

	local copyscenelevel = GetFubenData_Param(sceneId, x700222_CSP_FUBENLEVEL ) ;
	SetFubenData_Param( sceneId, x700222_CSP_FUBENLEVEL_DUP, copyscenelevel)
	
	
	x700222_InitRandomType(sceneId)

    x700222_CreateNpc(sceneId)
	
		
end

function x700222_InitRandomType(sceneId)
	local objList={random(1,6)};

	for i=2, 4 do
		local j = random(1,6)

		while j== objList[i-1] do
			j = random(1,6)
		end
		
		objList[i] = j
	end

	for i=1, 4 do
		SetFubenData_Param(sceneId, x700222_CSP_TWO_TYPE_START+i, objList[i]);
	end

	objList={random(1,4)};

	for i=2, 4 do
		local j = random(1,4)

		while j== objList[i-1] do
			j = random(1,4)
		end
		
		objList[i] = j
	end

	for i=1, 4 do
		SetFubenData_Param(sceneId, x700222_CSP_THREE_TYPE_START+i, objList[i]);
	end

end

function x700222_CreateNpc( sceneId)
	
	 local nRet = 0;
	 if x700222_g_GameNPC.title~="" then
		nRet = CreateMonster(sceneId, x700222_g_GameNPC.type, x700222_g_GameNPC.x, x700222_g_GameNPC.z, 3, 0, -1, x700222_g_GameNPC.guid, -1,-1,x700222_g_GameNPC.facedir,  "",x700222_g_GameNPC.title)
	 else
		nRet = CreateMonster(sceneId, x700222_g_GameNPC.type, x700222_g_GameNPC.x, x700222_g_GameNPC.z, 3, 0, -1, x700222_g_GameNPC.guid, -1,-1,x700222_g_GameNPC.facedir)
	 end

	 SetFubenData_Param(sceneId, x700222_CSP_NPC_ID, nRet )
end


-----------------------------------------------------------
--*********************************************************
--EnterTick  :  副本心跳
--*********************************************************
-----------------------------------------------------------
function x700222_EnterTick(sceneId, nowTickCount)

	if nowTickCount >= 2 and  nowTickCount<= x700222_g_nTextCount+1 then
		local nNpcId = GetFubenData_Param(sceneId, x700222_CSP_NPC_ID )
		
		
		NpcTalk(sceneId, nNpcId, x700222_g_NpcTalkText[nowTickCount-1],  -1)
	end

	local nCurrentStep = GetFubenData_Param(sceneId, x700222_CSP_CURRENTSTEP);

	
	if nCurrentStep<=0 then
		return
	end



	local nLen = 0;
	for i,item in x700222_g_TimeDriverList do
		nLen = nLen+1
	end

	if nCurrentStep> nLen then
		return
	end

	local nCurrentStepTickCount = GetFubenData_Param(sceneId, x700222_CSP_CURRENTSTEP_TICKCOUNT)+1;
	SetFubenData_Param(sceneId, x700222_CSP_CURRENTSTEP_TICKCOUNT, nCurrentStepTickCount)
	
	local nNextStepTime = x700222_g_TimeDriverList[nCurrentStep];

	if nCurrentStepTickCount>=nNextStepTime then
		SetFubenData_Param(sceneId, x700222_CSP_CURRENTSTEP_TICKCOUNT, 0)
		SetFubenData_Param(sceneId, x700222_CSP_CURRENTSTEP,nCurrentStep+1 );
		
		if nCurrentStep< nLen then
			x700222_CreateMonster( sceneId, nCurrentStep )
		else
			x700222_CreateBoss(sceneId)
		end
    
	end
end


---------------------------------------------------------------------------------------------------
--创建一小波怪物
---------------------------------------------------------------------------------------------------
function x700222_CreateMonster(sceneId, nStep)

	
	local nCount = GetFubenData_Param(sceneId, x700222_CSP_MONSTER_COUNT ) 
    
	local nCreateCount = 0;

	for i, item in x700222_g_MonsterCreate do

		if item.timeflag == nStep then
			
			

			local tpointlist = item.pointlist;
			local j=0
			for k,pointIndex in tpointlist do
				j = j+1;

				
				local x,z,patrolid = x700222_GetPointInfo(sceneId, pointIndex)
				local nType, ai,aiscript = x700222_GetMonsterInfo(sceneId, item.objflag, j); --每一小波出的怪物一样
				
				local nRet = CreateMonster(sceneId, nType, x, z, ai, aiscript, x700222_g_ScriptId, -1, 21,-1,0)

				if patrolid>=0 then
					SetPatrolId(sceneId, nRet, patrolid)
				end
				
				nCreateCount = nCreateCount+1
				nCount = nCount+1
				
			end
		end

       
	end

	
	if mod(nStep,4) ==1 then
		local str = ""
		if nStep==1 then
			str = "#G第一批怪兽出现了！"
		else
			local strList = {	"#G又一批怪兽蜂拥而出……",
								"#G四周同时出现了怪物的身影……",
								"#G四面都传来沉重的脚步声……"}

			str = strList[random(1,3)]

		end

		--x700222_ShowTipsToAll(sceneId,format("创建第%d波怪物,总共创建%d个",nStep,nCreateCount));
		x700222_ShowTipsToAll(sceneId,str);
	end

	SetFubenData_Param(sceneId, x700222_CSP_MONSTER_COUNT, nCount ) 

end


---------------------------------------------------------------------------------------------------
--得到怪物的位置和patrol
---------------------------------------------------------------------------------------------------
function x700222_GetPointInfo(sceneId, pointIndex)
	for i,item in x700222_g_PointList do
		if item.flag == pointIndex then
			return item.x, item.z, item.patrolid;
		end
	end

	return -1;
end

---------------------------------------------------------------------------------------------------
--得到怪物的obj和ai
---------------------------------------------------------------------------------------------------
function x700222_GetMonsterInfo(sceneId, objflag, nExt)

	local copyscenelevel = GetFubenData_Param(sceneId, x700222_CSP_FUBENLEVEL ) ;

	
	--// get type
	local nIndex;

	if objflag<=4 then --出现四只
		nIndex = objflag
	elseif objflag<=8 then
		local twoType = GetFubenData_Param(sceneId, x700222_CSP_TWO_TYPE_START+objflag-4);
		local tempList = x700222_g_C42[twoType]
		nIndex = tempList[nExt];
	elseif objflag<=12 then
		local threeType = GetFubenData_Param(sceneId, x700222_CSP_THREE_TYPE_START+objflag-8);
		local tempList = x700222_g_C43[threeType]
		nIndex = tempList[nExt];
	elseif objflag<=16 then
		nIndex = random(1,4);
	else
		return -1;
	end

	for i,item in x700222_g_Monster_ObjList do
		if item.flag == nIndex then
			if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
				return item.type, item.ai, item.aiscript;
			end
		end
	end

	
	--// get end
end



function x700222_OnDie(sceneId, selfId, killerId)
	local nDieCount = GetFubenData_Param(sceneId, x700222_CSP_KILLCOUNT)
	local country = GetCurCountry(sceneId, selfId)
	SetFubenData_Param(sceneId, x700222_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	


	local bossid = GetFubenData_Param(sceneId, x700222_CSP_BOSS_ID)
	
	if bossid== selfId then
		x700222_ShowTipsToAll(sceneId, "随着巨兽的倒下，轮回台渐渐恢复了平静。")
	if  country == 0 then
    	CallScriptFunction( 203782, "FinishLunhuitai", sceneId, killerId)
    elseif country == 1 then 
   		CallScriptFunction( 203783, "FinishLunhuitai", sceneId, killerId)
    elseif country == 2 then 
    	CallScriptFunction( 203784, "FinishLunhuitai", sceneId, killerId)
    elseif country == 3 then 
    	CallScriptFunction( 203785, "FinishLunhuitai", sceneId, killerId)
    end
    
    	
		local nNpcId = GetFubenData_Param(sceneId, x700222_CSP_NPC_ID )
		NpcTalk(sceneId, nNpcId, "来我这里，我帮你们回到王城！",  -1)

		
--		--//--------------------------- 世界喊话 Start--------------------
--		--杀死所有 boss
--		local nowTickCount = GetFubenData_Param(sceneId, x700222_CSP_TICKCOUNT)
--
--		local nowTime = x700222_g_TickTime* nowTickCount;
--
--		local nMinute = floor(nowTime/60)
--		local nSec = mod(nowTime,60)
--
--			
--		local strPlayerName = GetName(sceneId, killerId)     -- 杀死怪物的玩家名字
--		-------- if killed by pet -----------------
--		local nKillerType = GetObjType(sceneId, killerId)
--		--PrintStr(nKillerType)
--		if nKillerType== 3 then
--			local nOwnerId = GetOwnerID(sceneId, killerId)
--			strPlayerName = GetName(sceneId, nOwnerId)
--		end
--		--------- end -------------------------------
--
--		local strBossName = GetName(sceneId, selfId)		 -- Boss name	
--		local strKillTime = format("%d分%d秒", nMinute, nSec) -- 杀死关务的事件
--
--		
--		
--		----LuaAllScenceM2Wrold (sceneId,"#G"..strPlayerName.."#R和他的队友用了#G"..strKillTime.."#R击败了巨掌玄冰！轮回台，又恢复了以往的平静……", 0, 1)
--		
--
--		
--		
--		--//--------------------------- 世界喊话 end----------------------

	else
		local nCurMonsterCount = GetFubenData_Param(sceneId, x700222_CSP_MONSTER_COUNT)-1 
		
		SetFubenData_Param(sceneId, x700222_CSP_MONSTER_COUNT, nCurMonsterCount)
		if nCurMonsterCount==0 then
			x700222_OnAllMonsterDead( sceneId)
		end
	end

	

	
end

function x700222_OnAllMonsterDead( sceneId)
	local nCurrentStep = GetFubenData_Param(sceneId, x700222_CSP_CURRENTSTEP);

	
	if nCurrentStep<=0 then
		return
	end



	local nLen = 0;
	for i,item in x700222_g_TimeDriverList do
		nLen = nLen+1
	end

	if nCurrentStep> nLen then
		return
	end
	
	local nNextStepTime = x700222_g_TimeDriverList[nCurrentStep];
	
	SetFubenData_Param(sceneId, x700222_CSP_CURRENTSTEP_TICKCOUNT, nNextStepTime-1)
	
	


end

function x700222_CreateSubmitNpc( sceneId)
	 if x700222_g_SubmitNPC.title~="" then
		CreateMonster(sceneId, x700222_g_SubmitNPC.type, x700222_g_SubmitNPC.x, x700222_g_SubmitNPC.z, 3, 0, -1, x700222_g_SubmitNPC.guid, -1,-1,x700222_g_SubmitNPC.facedir,  "", x700222_g_SubmitNPC.title)
	 else
		CreateMonster(sceneId, x700222_g_SubmitNPC.type, x700222_g_SubmitNPC.x, x700222_g_SubmitNPC.z, 3, 0, -1, x700222_g_SubmitNPC.guid, -1,-1,x700222_g_SubmitNPC.facedir)
	 end
	 
end




--//added in 2009-3-17
---------------------------------------------------------------------------------------------------
--进入区域
---------------------------------------------------------------------------------------------------
function x700222_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x700222_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
end
--//add end


function x700222_ShowTipsToAll(sceneId, str)
	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);

		DispatchQuestTips(sceneId, humanId);
	end
end
