---------------------------------------------------
-- File: 700210_fuben_shizijing_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700210_CSP_FUBENTYPE				= 	0
x700210_CSP_SCRIPTID				=	1
x700210_CSP_TICKCOUNT				= 	2
x700210_CSP_FROMSCENEID				= 	3
x700210_CSP_ISCLOSING				= 	4
x700210_CSP_LEAVECOUNTDOWN			= 	5
x700210_CSP_TEAMID					=	6
x700210_CSP_BACKSCENEX       		=   7
x700210_CSP_BACKSCENEZ      		=   8
x700210_CSP_FUBENLEVEL			=	9
x700210_CSP_KILLCOUNT				=	20
x700210_CSP_FUBEN_SCENE_ID			=	21
x700210_CSP_BOSS1_ID				=	22
x700210_CSP_BOSS2_ID				=	23
x700210_CSP_BOSS3_ID				=   24
x700210_CSP_B_BOSS1_STATUS			=	25
x700210_CSP_BOSS1_TIME_COUNT		=	26
x700210_CSP_BOSS1_FULL_HP			=	27
x700210_CSP_B_BOSS2_STATUS			=	28
x700210_CSP_BOSS2_TIME_COUNT		=	29

x700210_CSP_HUMAN_COUNT				=	240
x700210_CSP_OBJID_START				=	241
x700210_CSP_GUID_START              =   248


------------------------Scene System Setting -----------------------------------

x700210_g_ScriptId 					= 700210

----------------------------- special for this Fuben --------------------
x700210_g_Buff1						=	13505                   --����buff
x700210_g_Buff2						=	13504                   --����buff
x700210_g_Boss1_Del_Time			=	6                       --����ʧ�������ʧʱ�䣨����ս����
x700210_g_Boss_Relive_Time			=	1*36                    --��buff�Ĺ�������ʱ��

x700210_g_nShengWang_Boss1			=	10                      --СͷĿ������buff������
x700210_g_nShengWang_Boss2			=	10                      --����֣�����buff������
x700210_g_nShengWang_Boss3			=	200                     --BOSS����
x700210_g_nShengWang_Monster		=   5                       --��ͨС������

------------------------- list -----------------------------------------




x700210_g_SubmitNPC                 =   { type =25023,guid= 150523,x = 49, z=52, facedir =0, title =""}

--BOSS����
x700210_g_BossCreate				=	{
											{levelmin =20, levelmax=100, name ="��ҹ����С��2",   type= 27817,  x=9,  z=27,  ai=18, aiscript=592,  facedir = 27, title = "", flag =1},
											
											{levelmin =20, levelmax=100, name ="��ҹ����С��3",   type= 27816,  x=16,  z=8,  ai=18, aiscript=593,  facedir = 9, title = "", flag =0},
											
											{levelmin =20, levelmax=100, name ="��ҹ����boss2",   type= 27818,  x=45,  z=73,  ai=18, aiscript=594,  facedir = 0, title = "", flag =2},
											
										}
-- Random ����



--Monster����
x700210_g_MonsterCreate				=	{

											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=117, z=49 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 18 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=106, z=48 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 0  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=114, z=51 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 9  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=110, z=51 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 9  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=114, z=63 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 9  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=110, z=63 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 9  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=118, z=68 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 14 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=107, z=68 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 5  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=113, z=67 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 9  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=113, z=73 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 9  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=115, z=91 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 9  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=110, z=92 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 9  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=119, z=97 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 14 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=106, z=97 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 7  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=113, z=101,  r=0, count=1,  ai=9, aiscript=591,  facedir = 9  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=105, z=118,  r=0, count=1,  ai=9, aiscript=591,  facedir = 5  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=105, z=108,  r=0, count=1,  ai=9, aiscript=591,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=112, z=113,  r=0, count=1,  ai=9, aiscript=591,  facedir = 12 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=107, z=113,  r=0, count=1,  ai=9, aiscript=591,  facedir = 7  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=112, z=118,  r=0, count=1,  ai=9, aiscript=591,  facedir = 12 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=90 , z=110,  r=0, count=1,  ai=9, aiscript=591,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=91 , z=115,  r=0, count=1,  ai=9, aiscript=591,  facedir = 5  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=88 , z=119,  r=0, count=1,  ai=9, aiscript=591,  facedir = 7  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=88 , z=113,  r=0, count=1,  ai=9, aiscript=591,  facedir = 0  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=84 , z=116,  r=0, count=1,  ai=9, aiscript=591,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=80 , z=107,  r=0, count=1,  ai=9, aiscript=591,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=74 , z=106,  r=0, count=1,  ai=9, aiscript=591,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=85 , z=89 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=82 , z=88 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=77 , z=89 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=75 , z=90 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=89 , z=73 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=82 , z=73 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=89 , z=60 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=83 , z=59 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=89 , z=65 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=82 , z=65 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=89 , z=49 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=86 , z=45 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=86 , z=52 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=82 , z=49 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=89 , z=32 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=82 , z=32 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=88 , z=14 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=88 , z=27 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=75 , z=13 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 31 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=75 , z=27 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 0  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=63 , z=27 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 0  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=63 , z=13 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 0  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=49 , z=13 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 33 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=50 , z=27 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 0  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=16 , z=60 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 9  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=16 , z=54 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 9  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=11 , z=60 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 7  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=16 , z=67 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 12 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=23 , z=60 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 14 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=27 , z=60 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 18 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=18 , z=84 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 13 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=14 , z=84 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 7  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=16 , z=87 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 9  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=20 , z=90 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 14 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=11 , z=91 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 7  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=16 , z=91 ,  r=0, count=1,  ai=9, aiscript=591,  facedir = 12 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=12 , z=116,  r=0, count=1,  ai=9, aiscript=591,  facedir = 9  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=17 , z=118,  r=0, count=1,  ai=9, aiscript=591,  facedir = 12 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=20 , z=114,  r=0, count=1,  ai=9, aiscript=591,  facedir = 12 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=19 , z=108,  r=0, count=1,  ai=9, aiscript=591,  facedir = 16 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=16 , z=111,  r=0, count=1,  ai=9, aiscript=591,  facedir = 9  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=12 , z=109,  r=0, count=1,  ai=9, aiscript=591,  facedir = 9  , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=29 , z=109,  r=0, count=1,  ai=9, aiscript=591,  facedir = 21 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=29 , z=111,  r=0, count=1,  ai=9, aiscript=591,  facedir = 18 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=29 , z=114,  r=0, count=1,  ai=9, aiscript=591,  facedir = 18 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=29 , z=117,  r=0, count=1,  ai=9, aiscript=591,  facedir = 18 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=29 , z=119,  r=0, count=1,  ai=9, aiscript=591,  facedir = 18 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=53 , z=114,  r=0, count=1,  ai=9, aiscript=591,  facedir = 18 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=48 , z=107,  r=0, count=1,  ai=9, aiscript=591,  facedir = 23 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=48 , z=119,  r=0, count=1,  ai=9, aiscript=591,  facedir = 16 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=51 , z=109,  r=0, count=1,  ai=9, aiscript=591,  facedir = 21 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=59 , z=107,  r=0, count=1,  ai=9, aiscript=591,  facedir = 21 , title=""},
											{levelmin =20, levelmax=100, name ="��ҹ����С��1",   type= 27815,  x=56 , z=110,  r=0, count=1,  ai=9, aiscript=591,  facedir = 21 , title=""},
                                                                       
											

										}






-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700210_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)

end


-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  �����������ɹ�ʱ�� ��ʼˢ�ֺ�npc
--*********************************************************
-----------------------------------------------------------
function x700210_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  ��������id
	
	
	local humancount = GetFuben_PlayerCount(sceneId);
	SetFubenData_Param(sceneId, x700210_CSP_HUMAN_COUNT, humancount);
	
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		SetFubenData_Param(sceneId, x700210_CSP_OBJID_START+i, humanId);
	end

	

	x700210_CreateMonster( sceneId )
	x700210_CreateBoss( sceneId, 3 )
   
		
end


function x700210_EnterTick(sceneId,nowTickCount)
	local nBoss1TimeCount = GetFubenData_Param(sceneId, x700210_CSP_BOSS1_TIME_COUNT) + 1;
	SetFubenData_Param(sceneId, x700210_CSP_BOSS1_TIME_COUNT, nBoss1TimeCount);

	local nBoss2TimeCount = GetFubenData_Param(sceneId, x700210_CSP_BOSS2_TIME_COUNT) + 1;
	SetFubenData_Param(sceneId, x700210_CSP_BOSS2_TIME_COUNT, nBoss2TimeCount);

	local nBoss1Status = GetFubenData_Param(sceneId, x700210_CSP_B_BOSS1_STATUS)
	local nBoss2Status = GetFubenData_Param(sceneId, x700210_CSP_B_BOSS2_STATUS)


	
	
	if nBoss1Status==1 then
		local nBoss1Id = GetFubenData_Param(sceneId, x700210_CSP_BOSS1_ID)

		local currentHp = GetHp( sceneId, nBoss1Id )
		local nFullHp = GetFubenData_Param(sceneId, x700210_CSP_BOSS1_FULL_HP)
		
		if currentHp>=nFullHp then
			
			nBoss1TimeCount = nBoss1TimeCount-1
			SetFubenData_Param(sceneId, x700210_CSP_BOSS1_TIME_COUNT, nBoss1TimeCount);
		else
			
			if nBoss1TimeCount==x700210_g_Boss1_Del_Time then
			
				if nBoss1Id>=0 then
					DeleteMonster( sceneId,nBoss1Id )
					SetFubenData_Param(sceneId, x700210_CSP_B_BOSS1_STATUS,2)
					SetFubenData_Param(sceneId, x700210_CSP_BOSS1_ID,-1)
					SetFubenData_Param(sceneId, x700210_CSP_BOSS1_TIME_COUNT,0)
					--x700210_ShowTipsToAll(sceneId, format("������ʧ�� %d���Ӻ����³���",x700210_g_Boss_Relive_Time/12))
				end
			end
		end

		
	elseif nBoss1Status==2 then
		if nBoss1TimeCount==x700210_g_Boss_Relive_Time then
			x700210_CreateBoss(sceneId, 0)
			
		end
	end

	if nBoss2Status==2 then
		if nBoss2TimeCount==x700210_g_Boss_Relive_Time then
			x700210_CreateBoss(sceneId, 1)
		end
	end
	
end


function x700210_ShowTipsToAll(sceneId, str)
	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);

		DispatchQuestTips(sceneId, humanId);
	end
end



function x700210_CreateBoss(sceneId, nFlag)


	local copyscenelevel = GetFubenData_Param(sceneId, x700210_CSP_FUBENLEVEL ) ;

	
	for i, item in x700210_g_BossCreate do  --����3��boss

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
			if nFlag== item.flag or nFlag>=3 then
				local nRet = 0
				if item.title ~="" then
					nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700210_g_ScriptId, -1, 21,-1, item.facedir,  "",item.title)
				else
					nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700210_g_ScriptId, -1, 21,-1, item.facedir)
				
				end
				if item.flag == 0 then
					SetFubenData_Param(sceneId, x700210_CSP_BOSS1_ID, nRet )
					SetFubenData_Param(sceneId, x700210_CSP_B_BOSS1_STATUS, 1 )
					SetFubenData_Param(sceneId, x700210_CSP_BOSS1_TIME_COUNT, 0 )

					local nFullHp = GetHp( sceneId, nRet )
					SetFubenData_Param(sceneId, x700210_CSP_BOSS1_FULL_HP,nFullHp )
					
					--SetPatrolId(sceneId, nRet, 0)
				elseif item.flag == 1 then
					
					SetFubenData_Param(sceneId, x700210_CSP_BOSS2_ID, nRet )
					SetFubenData_Param(sceneId, x700210_CSP_B_BOSS2_STATUS, 1 )
					SetFubenData_Param(sceneId, x700210_CSP_BOSS2_TIME_COUNT, 0 )
				elseif item.flag == 2 then
					
					SetFubenData_Param(sceneId, x700210_CSP_BOSS3_ID, nRet )
					
				end
			end
		
        end
	end


--	if nFlag<3 then
--
--		local humancount = GetFuben_PlayerCount(sceneId);
--
--			for i = 0, humancount - 1 do
--
--
--				local humanId = GetFuben_PlayerObjId(sceneId, i);	--ȡ�õ�ǰ�������˵�objId
--				local str = format(" ",nFlag+1);
--				BeginQuestEvent(sceneId);
--				AddQuestText(sceneId, str);
--				EndQuestEvent(sceneId);
--
--				DispatchQuestTips(sceneId, humanId);
--			end
--	end

end




---------------------------------------------------------------------------------------------------
--����Monster
---------------------------------------------------------------------------------------------------
function x700210_CreateMonster(sceneId)


    local copyscenelevel = GetFubenData_Param(sceneId, x700210_CSP_FUBENLEVEL ) ;

	for i, item in x700210_g_MonsterCreate do --������ͨ��

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
            for j=0,item.count -1 do

                local rx = random(-item.r,item.r)
                local x = item.x + rx
                local rz = random(-item.r,item.r)
                local z = item.z + rz

				if item.title ~= "" then
					CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700210_g_ScriptId, -1, 21,-1,item.facedir,  "",item.title)
				else
					CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700210_g_ScriptId, -1, 21,-1,item.facedir)
				
				end
			end
        end
	end


	
end




function x700210_OnDie(sceneId, selfId, killerId)
	local nDieCount = GetFubenData_Param(sceneId, x700210_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700210_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	
	
	local objId1 = GetFubenData_Param(sceneId, x700210_CSP_BOSS1_ID)
	local objId2 = GetFubenData_Param(sceneId, x700210_CSP_BOSS2_ID)
	local objId3 = GetFubenData_Param(sceneId, x700210_CSP_BOSS3_ID)

	local nShengWangBonus = 0;
	if objId1 == selfId then
		SetFubenData_Param(sceneId, x700210_CSP_BOSS1_ID, -1)
		SetFubenData_Param(sceneId, x700210_CSP_B_BOSS1_STATUS, 2)
		SetFubenData_Param(sceneId, x700210_CSP_BOSS1_TIME_COUNT, 0)
		nShengWangBonus	= x700210_g_nShengWang_Boss1;
		local humancount = GetFuben_PlayerCount(sceneId);

		for i = 0, humancount - 1 do


			local humanId = GetFuben_PlayerObjId(sceneId, i);	--ȡ�õ�ǰ�������˵�objId
			SendSpecificImpactToUnit(sceneId, humanId,humanId,humanId, x700210_g_Buff1,0 )
--			local str = "";
--			BeginQuestEvent(sceneId);
--			AddQuestText(sceneId, str);
--			EndQuestEvent(sceneId);
--
--			DispatchQuestTips(sceneId, humanId);
		end
	
		--x700210_ShowTipsToAll(sceneId, format("���������� %d���Ӻ����³���",x700210_g_Boss_Relive_Time/12))
	elseif objId2 == selfId then

		SetFubenData_Param(sceneId, x700210_CSP_BOSS2_ID, -1)
		SetFubenData_Param(sceneId, x700210_CSP_B_BOSS2_STATUS, 2)
		SetFubenData_Param(sceneId, x700210_CSP_BOSS2_TIME_COUNT, 0)
		nShengWangBonus	= x700210_g_nShengWang_Boss2;

		local humancount = GetFuben_PlayerCount(sceneId);

		for i = 0, humancount - 1 do


			local humanId = GetFuben_PlayerObjId(sceneId, i);	--ȡ�õ�ǰ�������˵�objId
			SendSpecificImpactToUnit(sceneId, humanId,humanId,humanId, x700210_g_Buff2,0 )
--			local str = "";
--			BeginQuestEvent(sceneId);
--			AddQuestText(sceneId, str);
--			EndQuestEvent(sceneId);

--			DispatchQuestTips(sceneId, humanId);
		end
		
		--x700210_ShowTipsToAll(sceneId, format("���������� %d���Ӻ����³���",x700210_g_Boss_Relive_Time/12))
	elseif objId3 == selfId then

		nShengWangBonus	= x700210_g_nShengWang_Boss3;
		SetFubenData_Param(sceneId, x700210_CSP_BOSS3_ID, -1)
		x700210_CreateSubmitNpc( sceneId)
		
--		--//--------------------------- ���纰�� Start--------------------
--			--ɱ��boss1
--			local nowTickCount = GetFubenData_Param(sceneId, x700210_CSP_TICKCOUNT)
--
--			local nowTime = x700210_g_TickTime* nowTickCount;
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
--			--LuaAllScenceM2Wrold (sceneId,"#R���ɼ�˼�����궼����ʹ���������ο�������Щ���ϣ���һ�Σ��Ҿ������ص����ޣ�����#G"..strPlayerName.."#R�������ҵĹ����£�����������֧����#G"..strKillTime.."#R����ŭ������һ�ν����˳�˯��", 0, 1)
--			
--			
--			--//--------------------------- ���纰�� end----------------------

	else
		nShengWangBonus	= x700210_g_nShengWang_Monster;
		
	end


	local nShengWangBonus_dup = nShengWangBonus
	
	--��͢����
	if nShengWangBonus > 0 then
		local humancount = GetFuben_PlayerCount(sceneId);

		for i = 0, humancount - 1 do


			local humanId = GetFuben_PlayerObjId(sceneId, i);	--ȡ�õ�ǰ�������˵�objId

			--//add in 2009-3-26
			nShengWangBonus = nShengWangBonus_dup
			local nLevel1 = GetLevel(sceneId, selfId)	--��ɱ�������level
			local nLevel2 = GetLevel(sceneId, humanId)	--��ҵ�level
			local copyscenelevel = GetFubenData_Param(sceneId, x700210_CSP_FUBENLEVEL ) ; --�����ȼ�
			
			if nLevel2-copyscenelevel>10 then
				nShengWangBonus = floor(nShengWangBonus*nLevel1/nLevel2)
			end
			--//add end


			local nShengWang = GetShengWang( sceneId, humanId )
			nShengWang = nShengWang + nShengWangBonus
			SetShengWang( sceneId, humanId, nShengWang )
            
            local str = format("�������%d������ֵ�Ľ�����", nShengWangBonus)
			Msg2Player(sceneId,humanId,str,4,2)
			Msg2Player(sceneId,humanId,str,4,3)

		end
		

		----------------------------------- �ܿ� ----------------------------------

		local buffId1 =9011
		local buffId1_1 = 9013
		local buffId2 =9012

		local humancount = GetFuben_PlayerCount(sceneId);

		--֪ͨ���
		for i = 0, humancount - 1 do
			local humanId = GetFuben_PlayerObjId(sceneId, i);
			
			local bHaveImpact1 = IsHaveSpecificImpact( sceneId, humanId, buffId1 )
			local bHaveImpact1_1 = IsHaveSpecificImpact( sceneId, humanId, buffId1_1 )
			local bHaveImpact2 = IsHaveSpecificImpact( sceneId, humanId, buffId2 )

			--//add in 2009-3-26
			nShengWangBonus = nShengWangBonus_dup
			local nLevel1 = GetLevel(sceneId, selfId)	--��ɱ�������level
			local nLevel2 = GetLevel(sceneId, humanId)	--��ҵ�level
			local copyscenelevel = GetFubenData_Param(sceneId, x700210_CSP_FUBENLEVEL ) ; --�����ȼ�
			
			if nLevel2-copyscenelevel>10 then
				nShengWangBonus = floor(nShengWangBonus*nLevel1/nLevel2)
			end
			--//add end
				
			local nLevel = GetLevel(sceneId, humanId)
			if bHaveImpact1>0 or bHaveImpact1_1 > 0 then
				
				local nShengWang = GetShengWang( sceneId, humanId )
				nShengWang = nShengWang + nShengWangBonus*1
				SetShengWang( sceneId, humanId, nShengWang )

				local str = format("������������%d������ֵ�Ľ���",nShengWangBonus*1)
				Msg2Player(sceneId,humanId,str,4,2)
                Msg2Player(sceneId,humanId,str,4,3)
				
				
				BeginQuestEvent(sceneId);
					AddQuestText(sceneId,str);
				EndQuestEvent();
				DispatchQuestTips(sceneId, humanId);

			
				
			end

			if bHaveImpact2>0 then
				
				local nShengWang = GetShengWang( sceneId, humanId )
				nShengWang = nShengWang + nShengWangBonus*2
				SetShengWang( sceneId, humanId, nShengWang )

				local str = format("��͢��������%d������ֵ�Ľ���",nShengWangBonus*2)
				Msg2Player(sceneId,humanId,str,4,2)
                Msg2Player(sceneId,humanId,str,4,3)
				
				
				BeginQuestEvent(sceneId);
					AddQuestText(sceneId,str);
				EndQuestEvent();
				DispatchQuestTips(sceneId, humanId);
			end
			
		end

	----------------------------------- �ܿ�end ----------------------------------
	end
end

function x700210_OnAllMonsterDead( sceneId)
	x700210_CreateSubmitNpc( sceneId)
end

function x700210_CreateSubmitNpc( sceneId)
	if x700210_g_SubmitNPC.title ~="" then
		CreateMonster(sceneId, x700210_g_SubmitNPC.type, x700210_g_SubmitNPC.x, x700210_g_SubmitNPC.z, 3, 0, -1, x700210_g_SubmitNPC.guid, -1,-1,x700210_g_SubmitNPC.facedir,  "",x700210_g_SubmitNPC.title)
	else
		CreateMonster(sceneId, x700210_g_SubmitNPC.type, x700210_g_SubmitNPC.x, x700210_g_SubmitNPC.z, 3, 0, -1, x700210_g_SubmitNPC.guid, -1,-1,x700210_g_SubmitNPC.facedir)
	
	end
end


--//added in 2009-3-17
---------------------------------------------------------------------------------------------------
--��������
---------------------------------------------------------------------------------------------------
function x700210_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

---------------------------------------------------------------------------------------------------
--�뿪����
---------------------------------------------------------------------------------------------------
function x700210_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
end
--//add end





