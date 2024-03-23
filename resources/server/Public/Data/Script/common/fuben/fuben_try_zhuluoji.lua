---------------------------------------------------
-- File: 700227_fuben_huangjinkuangdong_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700227_CSP_FUBENTYPE				= 	0
x700227_CSP_SCRIPTID				=	1
x700227_CSP_TICKCOUNT				= 	2
x700227_CSP_FROMSCENEID				= 	3
x700227_CSP_ISCLOSING				= 	4
x700227_CSP_LEAVECOUNTDOWN			= 	5
x700227_CSP_TEAMID					=	6
x700227_CSP_BACKSCENEX       		=   7
x700227_CSP_BACKSCENEZ      		=   8
x700227_CSP_FUBENLEVEL			=	9
x700227_CSP_KILLCOUNT				=	20
x700227_CSP_FUBEN_SCENE_ID			=	21
x700227_CSP_BOSS1_ID				=	22

x700227_B_CREATE_RANDOMBOSS			=	230
x700227_CSP_RANDOM_BOSS_ID			=	231
x700227_RANDOMBOSS_FLAG				=	232

x700227_CSP_HUMAN_COUNT				=	240
x700227_CSP_OBJID_START				=	241
x700227_CSP_GUID_START              =   248




------------------------Scene System Setting -----------------------------------

x700227_g_ScriptId 					= 700227

----------------------------- special for this Fuben --------------------
x700227_g_RandomBossRate			=   1--0.5

x700227_g_RandomMonsterRate			=	0

------------------------- list -----------------------------------------

x700227_g_SubmitNPC                 =   { type =25041,guid= 150541,x = 23, z=68, facedir =0, title ="" }


-- Random ����

x700227_g_Monster_Random_Create		=	{
											{levelmin =20, levelmax=100, name ="����boss",   type= 27385,   x=30, z=84, r=0,  ai=18, aiscript=636,  facedir = 0, title = "",flag=0},
											                                                        
											{levelmin =20, levelmax=100, name ="����boss",   type= 27393,   x=30, z=84, r=0,  ai=18, aiscript=636,  facedir = 0, title = "",flag=1},
											                                          
											{levelmin =20, levelmax=100, name ="����boss",   type= 27401,   x=30, z=84, r=0,  ai=18, aiscript=636,  facedir = 0, title = "",flag=2},
											                                            
											{levelmin =20, levelmax=100, name ="����boss",   type= 27409,   x=30, z=84, r=0,  ai=18, aiscript=636,  facedir = 0, title = "",flag=3},
											

										}
--BOSS����
x700227_g_BossCreate				=	{

											{levelmin =40, levelmax=100, name ="����boss1",   type= 27771,  x=30,  z=84,  r=0,  ai=18, aiscript=607,  count=1,  facedir = 0, title = ""},
                                        

										}
-- Random ����

x700227_g_Boss_Random_Create		=	{

											{levelmin =40, levelmax=100, name ="����boss2",   type= 27772,  x=30,  z=84,  r=0,  ai=9, aiscript=606,  count=1,  facedir = 0, title = "",flag=0},    
                                          
                                        }

x700227_g_Boss_Random_Pos			={
										{x=75,z=110 },
										{x=106,z=106},
										{x=71,z=70  },
										{x=96,z=35  },
										{x=66,z=31  },
										{x=80,z=92  }
									 }

--Monster����
x700227_g_MonsterCreate				=	{

											{levelmin =40, levelmax=100, name ="����1��",   type= 27767,  x=38,  z=35,  r=0,  ai=9, aiscript=599,  count=1,  facedir = 18 , title=""},
											{levelmin =40, levelmax=100, name ="����1��",   type= 27767,  x=38,  z=39,  r=0,  ai=9, aiscript=599,  count=1,  facedir = 18 , title=""},
											{levelmin =40, levelmax=100, name ="����1��",   type= 27767,  x=47,  z=34,  r=0,  ai=9, aiscript=599,  count=1,  facedir = 29 , title=""},
											{levelmin =40, levelmax=100, name ="����1��",   type= 27767,  x=54,  z=34,  r=0,  ai=9, aiscript=599,  count=1,  facedir = 12 , title=""},
											{levelmin =40, levelmax=100, name ="����1��",   type= 27767,  x=63,  z=30,  r=0,  ai=9, aiscript=599,  count=1,  facedir = 21 , title=""},
											{levelmin =40, levelmax=100, name ="����1��",   type= 27767,  x=63,  z=35,  r=0,  ai=9, aiscript=599,  count=1,  facedir = 21 , title=""},
											{levelmin =40, levelmax=100, name ="����1��",   type= 27767,  x=73,  z=29,  r=0,  ai=9, aiscript=599,  count=1,  facedir = 25 , title=""},
											{levelmin =40, levelmax=100, name ="����1��",   type= 27767,  x=78,  z=34,  r=0,  ai=9, aiscript=599,  count=1,  facedir = 4  , title=""},
											{levelmin =40, levelmax=100, name ="����1��",   type= 27767,  x=79,  z=27,  r=0,  ai=9, aiscript=599,  count=1,  facedir = 31 , title=""},
											{levelmin =40, levelmax=100, name ="����1��",   type= 27767,  x=86,  z=30,  r=0,  ai=9, aiscript=599,  count=1,  facedir = 21 , title=""},
											{levelmin =40, levelmax=100, name ="����1��",   type= 27767,  x=85,  z=34,  r=0,  ai=9, aiscript=599,  count=1,  facedir = 16 , title=""},
											{levelmin =40, levelmax=100, name ="����1��",   type= 27767,  x=90,  z=33,  r=0,  ai=9, aiscript=599,  count=1,  facedir = 18 , title=""},
											
											{levelmin =40, levelmax=100, name ="����2��",   type= 27768,  x=99 ,  z=42,  r=0,  ai=9, aiscript=600,  count=1,  facedir = 12 , title=""},
											{levelmin =40, levelmax=100, name ="����2��",   type= 27768,  x=102,  z=39,  r=0,  ai=9, aiscript=600,  count=1,  facedir = 16 , title=""},
											{levelmin =40, levelmax=100, name ="����2��",   type= 27768,  x=98 ,  z=47,  r=0,  ai=9, aiscript=600,  count=1,  facedir = 18 , title=""},
											{levelmin =40, levelmax=100, name ="����2��",   type= 27768,  x=104,  z=45,  r=0,  ai=9, aiscript=600,  count=1,  facedir = 0  , title=""},
											{levelmin =40, levelmax=100, name ="����2��",   type= 27768,  x=105,  z=53,  r=0,  ai=9, aiscript=600,  count=1,  facedir = 18 , title=""},
											{levelmin =40, levelmax=100, name ="����2��",   type= 27768,  x=99 ,  z=52,  r=0,  ai=9, aiscript=600,  count=1,  facedir = 3  , title=""},
											{levelmin =40, levelmax=100, name ="����2��",   type= 27768,  x=101,  z=58,  r=0,  ai=9, aiscript=600,  count=1,  facedir = 7  , title=""},
											{levelmin =40, levelmax=100, name ="����2��",   type= 27768,  x=97 ,  z=62,  r=0,  ai=9, aiscript=600,  count=1,  facedir = 21 , title=""},
											{levelmin =40, levelmax=100, name ="����2��",   type= 27768,  x=91 ,  z=65,  r=0,  ai=9, aiscript=600,  count=1,  facedir = 3  , title=""},
											{levelmin =40, levelmax=100, name ="����2��",   type= 27768,  x=86 ,  z=67,  r=0,  ai=9, aiscript=600,  count=1,  facedir = 3  , title=""},
											{levelmin =40, levelmax=100, name ="����2��",   type= 27768,  x=82 ,  z=67,  r=0,  ai=9, aiscript=600,  count=1,  facedir = 6  , title=""},
											{levelmin =40, levelmax=100, name ="����2��",   type= 27768,  x=78 ,  z=67,  r=0,  ai=9, aiscript=600,  count=1,  facedir = 12 , title=""},
											
											{levelmin =40, levelmax=100, name ="����3��",   type= 27769,  x=67 ,  z=78 ,  r=0,  ai=9, aiscript=601,  count=1,  facedir = 29 , title=""},
											{levelmin =40, levelmax=100, name ="����3��",   type= 27769,  x=64 ,  z=81 ,  r=0,  ai=9, aiscript=601,  count=1,  facedir = 5  , title=""},
											{levelmin =40, levelmax=100, name ="����3��",   type= 27769,  x=70 ,  z=81 ,  r=0,  ai=9, aiscript=601,  count=1,  facedir = 16 , title=""},
											{levelmin =40, levelmax=100, name ="����3��",   type= 27769,  x=71 ,  z=86 ,  r=0,  ai=9, aiscript=601,  count=1,  facedir = 31 , title=""},
											{levelmin =40, levelmax=100, name ="����3��",   type= 27769,  x=74 ,  z=88 ,  r=0,  ai=9, aiscript=601,  count=1,  facedir = 16 , title=""},
											{levelmin =40, levelmax=100, name ="����3��",   type= 27769,  x=78 ,  z=90 ,  r=0,  ai=9, aiscript=601,  count=1,  facedir = 14 , title=""},
											{levelmin =40, levelmax=100, name ="����3��",   type= 27769,  x=93 ,  z=92 ,  r=0,  ai=9, aiscript=601,  count=1,  facedir = 14 , title=""},
											{levelmin =40, levelmax=100, name ="����3��",   type= 27769,  x=87 ,  z=92 ,  r=0,  ai=9, aiscript=601,  count=1,  facedir = 12 , title=""},
											{levelmin =40, levelmax=100, name ="����3��",   type= 27769,  x=87 ,  z=98 ,  r=0,  ai=9, aiscript=601,  count=1,  facedir = 27 , title=""},
											{levelmin =40, levelmax=100, name ="����3��",   type= 27769,  x=94 ,  z=100,  r=0,  ai=9, aiscript=601,  count=1,  facedir = 27 , title=""},
											{levelmin =40, levelmax=100, name ="����3��",   type= 27769,  x=98 ,  z=95 ,  r=0,  ai=9, aiscript=601,  count=1,  facedir = 0  , title=""},
											{levelmin =40, levelmax=100, name ="����3��",   type= 27769,  x=105,  z=98 ,  r=0,  ai=9, aiscript=601,  count=1,  facedir = 16 , title=""},
											
											{levelmin =40, levelmax=100, name ="����4��",   type= 27770,  x=98,  z=109,  r=0,  ai=9, aiscript=602,  count=1,  facedir = 13 , title=""},
											{levelmin =40, levelmax=100, name ="����4��",   type= 27770,  x=97,  z=111,  r=0,  ai=9, aiscript=602,  count=1,  facedir = 27 , title=""},
											{levelmin =40, levelmax=100, name ="����4��",   type= 27770,  x=90,  z=109,  r=0,  ai=9, aiscript=602,  count=1,  facedir = 3  , title=""},
											{levelmin =40, levelmax=100, name ="����4��",   type= 27770,  x=90,  z=111,  r=0,  ai=9, aiscript=602,  count=1,  facedir = 4  , title=""},
											{levelmin =40, levelmax=100, name ="����4��",   type= 27770,  x=83,  z=108,  r=0,  ai=9, aiscript=602,  count=1,  facedir = 27 , title=""},
											{levelmin =40, levelmax=100, name ="����4��",   type= 27770,  x=83,  z=111,  r=0,  ai=9, aiscript=602,  count=1,  facedir = 11 , title=""},
											{levelmin =40, levelmax=100, name ="����4��",   type= 27770,  x=67,  z=106,  r=0,  ai=9, aiscript=602,  count=1,  facedir = 23 , title=""},
											{levelmin =40, levelmax=100, name ="����4��",   type= 27770,  x=63,  z=109,  r=0,  ai=9, aiscript=602,  count=1,  facedir = 6  , title=""},
											{levelmin =40, levelmax=100, name ="����4��",   type= 27770,  x=57,  z=105,  r=0,  ai=9, aiscript=602,  count=1,  facedir = 27 , title=""},
											{levelmin =40, levelmax=100, name ="����4��",   type= 27770,  x=47,  z=100,  r=0,  ai=9, aiscript=602,  count=1,  facedir = 33 , title=""},
											{levelmin =40, levelmax=100, name ="����4��",   type= 27770,  x=45,  z=104,  r=0,  ai=9, aiscript=602,  count=1,  facedir = 0  , title=""},
											{levelmin =40, levelmax=100, name ="����4��",   type= 27770,  x=55,  z=107,  r=0,  ai=9, aiscript=602,  count=1,  facedir = 9  , title=""},
											
										}


-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700227_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)
	
end


-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  �����������ɹ�ʱ�� ��ʼˢ�ֺ�npc
--*********************************************************
-----------------------------------------------------------
function x700227_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  ��������id
	
	
	local humancount = GetFuben_PlayerCount(sceneId);
	SetFubenData_Param(sceneId, x700227_CSP_HUMAN_COUNT, humancount);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		SetFubenData_Param(sceneId, x700227_CSP_OBJID_START+i, humanId);
	end
	
	x700227_CreateBoss( sceneId )
	x700227_CreateRandomBoss( sceneId )
    x700227_CreateMonster( sceneId )
		
end

-----------------------------------------------------------
--*********************************************************
--EnterTick  :  ��������
--*********************************************************
-----------------------------------------------------------
function x700227_EnterTick(sceneId, nowTickCount)

end	


function x700227_CreateBoss(sceneId)


	local copyscenelevel = GetFubenData_Param(sceneId, x700227_CSP_FUBENLEVEL ) ;

	
	for i, item in x700227_g_BossCreate do

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
		    local nRet = 0
			if item.title ~="" then
				nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700227_g_ScriptId, -1, 21,-1, item.facedir,  "",item.title)
			else
				nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700227_g_ScriptId, -1, 21,-1, item.facedir)
			
			end
			
			SetFubenData_Param(sceneId, x700227_CSP_BOSS1_ID, nRet )
			break;
				
        end
	end

end

function x700227_CreateRandomBoss(sceneId)


	local rate = random(0,100)/100;
	if rate>= x700227_g_RandomBossRate then
		return 0;
	end

	local nFlag = random(0,0)

	

	local copyscenelevel = GetFubenData_Param(sceneId, x700227_CSP_FUBENLEVEL ) ;


	local nLen =0;
	for i, item in x700227_g_Boss_Random_Pos do
		nLen = nLen+1
	end

	local n = random(1,nLen)
	
	local x=x700227_g_Boss_Random_Pos[n].x;
	local z=x700227_g_Boss_Random_Pos[n].z;
	
	for i, item in x700227_g_Boss_Random_Create do  --�������boss
		if item.flag == nFlag then
			if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
				if item.title ~="" then
					CreateMonster(sceneId, item.type, x,z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir,  "",item.title)
				else
					CreateMonster(sceneId, item.type, x,z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir)
				
				end
			end
		end
	end

	--x700227_ShowTipsToAll( sceneId, format("����boss�����ˣ���λ��x=%d,z=%d",x,z))

end





---------------------------------------------------------------------------------------------------
--����Monster
---------------------------------------------------------------------------------------------------
function x700227_CreateMonster(sceneId)


    local copyscenelevel = GetFubenData_Param(sceneId, x700227_CSP_FUBENLEVEL ) ;

	for i, item in x700227_g_MonsterCreate do  --������ͨС��

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
            for j=0,item.count -1 do

                local rx = random(-item.r,item.r)
                local x = item.x + rx
                local rz = random(-item.r,item.r)
                local z = item.z + rz
				if item.title ~="" then
					CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir, "", item.title)
				else
					CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir)
				
				end
			end
        end
	end


	

end

function x700227_CreateRandomMonster(sceneId)


	local rate = random(0,100)/100;
	if rate>= x700227_g_RandomMonsterRate then
		return 0;
	end

	local nFlag = random(0,3)

	

	local copyscenelevel = GetFubenData_Param(sceneId, x700227_CSP_FUBENLEVEL ) ;


	
	
	for i, item in x700227_g_Monster_Random_Create do --�������monster
		if item.flag == nFlag then
			if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
				local nBossID =0;
				if item.title~="" then
					nBossID = CreateMonster(sceneId, item.type, item.x,item.z, item.ai, item.aiscript, x700227_g_ScriptId, -1, 21,-1,item.facedir,  "",item.title)
				else
					nBossID = CreateMonster(sceneId, item.type, item.x,item.z, item.ai, item.aiscript, x700227_g_ScriptId, -1, 21,-1,item.facedir)
				
				end

				SetFubenData_Param(sceneId, x700227_B_CREATE_RANDOMBOSS, 1)
				SetFubenData_Param(sceneId, x700227_RANDOMBOSS_FLAG, nFlag)

				SetFubenData_Param(sceneId, x700227_CSP_RANDOM_BOSS_ID, nBossID)


			end
		end
	end

	x700227_ShowTipsToAll(sceneId, "ս�����֣�")

end



function x700227_OnDie(sceneId, selfId, killerId)
	local nDieCount = GetFubenData_Param(sceneId, x700227_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700227_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	local objId1 = GetFubenData_Param(sceneId, x700227_CSP_BOSS1_ID)

	--// add for random boss event, add in 2009-5-20
	local bCreateRandomboss = GetFubenData_Param(sceneId, x700227_B_CREATE_RANDOMBOSS)

	if bCreateRandomboss>0 then
		local nRandomBossId = GetFubenData_Param(sceneId, x700227_CSP_RANDOM_BOSS_ID)
		if nRandomBossId==selfId then
			--//--------------------------- ���纰�� Start--------------------
			--ɱ��Random boss
			
			
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
				strCountryName = "¥��"
			elseif nCountry==1 then
				strCountryName = "��ɽ"
			elseif nCountry==2 then
				strCountryName = "����"
			elseif nCountry==3 then
				strCountryName = "�ػ�"
			end

			local strHorseName = ""

			local nHorseFlag = GetFubenData_Param(sceneId, x700227_RANDOMBOSS_FLAG);

			if nHorseFlag==0 then
				strHorseName = "���ݻ�"
			elseif nHorseFlag==1 then
				strHorseName = "��ţ"
			elseif nHorseFlag==2 then
				strHorseName = "���"
			elseif nHorseFlag==3 then
				strHorseName = "����"
			end


			local strMapName = "٪�޼�"
			
			--LuaAllScenceM2Wrold (sceneId,strCountryName.."��"..strPlayerName.."�����"..strMapName.."�ľ��ս�񣬾�츶���"..strHorseName.."��Ķ��ӣ�", 5, 1)
			
			
			--//--------------------------- ���纰�� end----------------------
		end
	end
	--//add end
	
	if objId1 == selfId then
		SetFubenData_Param(sceneId, x700227_CSP_BOSS1_ID, -1)
		
		x700227_CreateSubmitNpc( sceneId)

		x700227_CreateRandomMonster(sceneId)

--		--//--------------------------- ���纰�� Start--------------------
--			--ɱ��boss1
--			local nowTickCount = GetFubenData_Param(sceneId, x700227_CSP_TICKCOUNT)
--
--			local nowTime = x700227_g_TickTime* nowTickCount;
--
--			local nMinute = floor(nowTime/60)
--			local nSec = mod(nowTime,60)
--
--				
--			local strPlayerName = GetName(sceneId, killerId)     -- ɱ��������������
--			-------- if killed by pet -----------------
--			local nKillerType = GetObjType(sceneId, killerId)
--			--PrintStr(nKillerType)
--			if nKillerType== 3 then
--				local nOwnerId = GetOwnerID(sceneId, killerId)
--				strPlayerName = GetName(sceneId, nOwnerId)
--			end
--			--------- end -------------------------------
--
--			local strBossName = GetName(sceneId, selfId)		 -- Boss name	
--			local strKillTime = format("%d��%d��", nMinute, nSec) -- ɱ��������¼�
--
--			
--			
--			--LuaAllScenceM2Wrold (sceneId,"#R��ʿ����#G"..strPlayerName.."#R�Ĵ����½�����#G"..strKillTime.."#R���òб���"..strBossName.."��Ȼ���£�������������һ��˽�ɽ���񺣡�", 0, 1)
--			
--			
--			--//--------------------------- ���纰�� end----------------------
	end
end

function x700227_OnAllMonsterDead( sceneId)
	--x700227_CreateSubmitNpc( sceneId)
end

function x700227_CreateSubmitNpc( sceneId)
	 x700227_ShowTipsToAll( sceneId, "�������")
	if x700227_g_SubmitNPC.title~= "" then
		CreateMonster(sceneId, x700227_g_SubmitNPC.type, x700227_g_SubmitNPC.x, x700227_g_SubmitNPC.z, 3, 0, -1, x700227_g_SubmitNPC.guid, -1,-1,x700227_g_SubmitNPC.facedir, "", x700227_g_SubmitNPC.title)
	else
		CreateMonster(sceneId, x700227_g_SubmitNPC.type, x700227_g_SubmitNPC.x, x700227_g_SubmitNPC.z, 3, 0, -1, x700227_g_SubmitNPC.guid, -1,-1,x700227_g_SubmitNPC.facedir)
		
	end
end

function x700227_ShowTipsToAll( sceneId, str)
	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, humanId);
	end
end



--//added in 2009-3-17
---------------------------------------------------------------------------------------------------
--��������
---------------------------------------------------------------------------------------------------
function x700227_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

---------------------------------------------------------------------------------------------------
--�뿪����
---------------------------------------------------------------------------------------------------
function x700227_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
end
--//add end





