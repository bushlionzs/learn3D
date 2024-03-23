---------------------------------------------------
-- File: 700209_fuben_dawushi_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700209_CSP_FUBENTYPE				= 	0
x700209_CSP_SCRIPTID				=	1
x700209_CSP_TICKCOUNT				= 	2
x700209_CSP_FROMSCENEID				= 	3
x700209_CSP_ISCLOSING				= 	4
x700209_CSP_LEAVECOUNTDOWN			= 	5
x700209_CSP_TEAMID					=	6
x700209_CSP_BACKSCENEX       		=   7
x700209_CSP_BACKSCENEZ      		=   8
x700209_CSP_FUBENLEVEL			=	9
x700209_CSP_KILLCOUNT				=	20
x700209_CSP_FUBEN_SCENE_ID			=	21
x700209_CSP_BOSSINDEX				=   22
x700209_CSP_BOSSCREATETIME			=	23
x700209_CSP_FORCE					=	24
x700209_CSP_GAME_STARTED            =   25
x700209_CSP_CURRENTBOSS_INDEX		=	26
x700209_CSP_CURRENTBOSS_TICK		=   27
x700209_CSP_STARTNPC_ID				=	28
x700209_CSP_B_FUBEN_STATUS			=	29

x700209_CSP_CURRENTBOSS_TIME_START	=   50
x700209_CSP_CURRENTBOSS_ID_START	=	60
x700209_CSP_MONSTER_COUNT			=	70
x700209_CSP_MONSTER_START			=	71

x700209_B_CREATE_RANDOMBOSS			=	230
x700209_CSP_RANDOM_BOSS_ID			=	231
x700209_RANDOMBOSS_FLAG				=	232

x700209_CSP_HUMAN_COUNT				=	240
x700209_CSP_OBJID_START				=	241
x700209_CSP_GUID_START              =   248



------------------------Scene System Setting -----------------------------------

x700209_g_ScriptId 					= 700209

------------------------- special for fuben----------------------
x700209_g_Boss_Interval = {2*12,2*12,2*12,2*12,2*12,2*12,2*12,2*12}  --bossˢ�¼��
x700209_g_SuccessBossInex			=	8	                         --�ɹ�����

x700209_g_MaxForce					=	50                           --ʧ������

x700209_g_NpcTalkText			=  { "�������죬����������","�ɼ�˼���Ļƽ�ʱ���ؽ���Ϊ��ʷ��"}
x700209_g_nTextCount			=	2


x700209_g_RandomBossRate		=	0

------------------------- list -----------------------------------------

x700209_g_SubmitNPC                 =   { type =25011,guid= 150511,x = 69, z=20,facedir=0, title="" }
x700209_g_LeaveNPC					=   { type =25011,guid= 150511,x = 69, z=20,facedir=0, title="" }	


-- Random ����

x700209_g_Monster_Random_Create		=	{
											{levelmin =20, levelmax=100, name ="����boss",   type= 27353,   x=65, z=31, r=0,  ai=18, aiscript=635,  facedir = 0, title = "",flag=0},
											                                          
											{levelmin =20, levelmax=100, name ="����boss",   type= 27361,   x=65, z=31, r=0,  ai=18, aiscript=635,  facedir = 0, title = "",flag=1},
											                                      
											{levelmin =20, levelmax=100, name ="����boss",   type= 27369,   x=65, z=31, r=0,  ai=18, aiscript=635,  facedir = 0, title = "",flag=2},
											                      
											{levelmin =20, levelmax=100, name ="����boss",   type= 27377,   x=65, z=31, r=0,  ai=18, aiscript=635,  facedir = 0, title = "",flag=3},
											

										}

--BOSS����
x700209_g_BossCreate                =   {

                                            {levelmin =20, levelmax=100, name ="�ΰ�ͷĿ1",   type= 27802,   x=29, z=48, r=0,  ai=9, aiscript=563, count=1, facedir = 0, title = "",patrolid=0,flag=0 },
                                           
                                            {levelmin =20, levelmax=100, name ="�ΰ�ͷĿ2",   type= 27803,   x=29, z=63, r=0,  ai=9, aiscript=564, count=1, facedir = 0, title = "",patrolid=1,flag=1 },
                                           
                                            {levelmin =20, levelmax=100, name ="�ΰ�ͷĿ3",   type= 27804,   x=29, z=79, r=0,  ai=9, aiscript=565, count=1, facedir = 0, title = "",patrolid=2,flag=2 },
                                           
                                            {levelmin =20, levelmax=100, name ="ؤ��ͷĿ1",   type= 27805,   x=99, z=48, r=0,  ai=9, aiscript=566, count=1, facedir = 0, title = "",patrolid=4,flag=4 },
                                           
                                            {levelmin =20, levelmax=100, name ="ؤ��ͷĿ2",   type= 27806,   x=99, z=63, r=0,  ai=9, aiscript=567, count=1, facedir = 0, title = "",patrolid=5,flag=5 },
                                            
                                            {levelmin =20, levelmax=100, name ="ؤ��ͷĿ3",   type= 27807,   x=99, z=79, r=0,  ai=9, aiscript=568, count=1, facedir = 0, title = "",patrolid=6,flag=6 },
                                            
                                            {levelmin =20, levelmax=100, name ="��ʿ��",   type= 27808,   x=29, z=95, r=0,  ai=9, aiscript=569, count=1, facedir = 0, title = "",patrolid=3,flag=3 },
                                            
                                            {levelmin =20, levelmax=100, name ="������",   type= 27809,   x=99, z=95, r=0,  ai=9, aiscript=570, count=1, facedir = 0, title = "",patrolid=7,flag=7 },
                                            

                                        }


x700209_g_MonsterCreate_Random_Count = {2,2,2,2,2,2,2,2}

x700209_g_MonsterCreate             =   {

                                            {levelmin =20, levelmax=100, name ="�ΰ����1",   type= 27794,   x=29, z=48, r=0,  ai=9, aiscript=555, count=1, facedir = 0, title = "",patrolid=0,flag=0 },
                                            
                                            {levelmin =20, levelmax=100, name ="�ΰ����2",   type= 27795,   x=29, z=63, r=0,  ai=9, aiscript=556, count=1, facedir = 0, title = "",patrolid=1,flag=1 },
												
                                            {levelmin =20, levelmax=100, name ="�ΰ����3",   type= 27796,   x=29, z=79, r=0,  ai=9, aiscript=557, count=1, facedir = 0, title = "",patrolid=2,flag=2 },
                                            
                                            {levelmin =20, levelmax=100, name ="�ΰ����4",   type= 27797,   x=29, z=95, r=0,  ai=9, aiscript=558, count=1, facedir = 0, title = "",patrolid=3,flag=3 },
                                            
                                            {levelmin =20, levelmax=100, name ="ؤ�����1",   type= 27798,   x=99, z=48, r=0,  ai=9, aiscript=559, count=1, facedir = 0, title = "",patrolid=4,flag=4 },
												
                                            {levelmin =20, levelmax=100, name ="ؤ�����2",   type= 27799,   x=99, z=63, r=0,  ai=9, aiscript=560, count=1, facedir = 0, title = "",patrolid=5,flag=5 },
												
                                            {levelmin =20, levelmax=100, name ="ؤ�����3",   type= 27800,   x=99, z=79, r=0,  ai=9, aiscript=561, count=1, facedir = 0, title = "",patrolid=6,flag=6 },
                                            
                                            {levelmin =20, levelmax=100, name ="ؤ�����4",   type= 27801,   x=99, z=95, r=0,  ai=9, aiscript=562, count=1, facedir = 0, title = "",patrolid=7,flag=7 },
                                            
											{levelmin =20, levelmax=100, name ="�ΰ����12",  type= 27794,   x=29, z=63, r=0,  ai=9, aiscript=555, count=1, facedir = 0, title = "",patrolid=1,flag=11 },
                                            														     
                                            {levelmin =20, levelmax=100, name ="�ΰ����2",   type= 27795,   x=29, z=48, r=0,  ai=9, aiscript=556, count=1, facedir = 0, title = "",patrolid=0,flag=10 },
																									     
                                            {levelmin =20, levelmax=100, name ="�ΰ����3",   type= 27796,   x=29, z=95, r=0,  ai=9, aiscript=557, count=1, facedir = 0, title = "",patrolid=3,flag=13 },
                                            														     
                                            {levelmin =20, levelmax=100, name ="�ΰ����4",   type= 27797,   x=29, z=79, r=0,  ai=9, aiscript=558, count=1, facedir = 0, title = "",patrolid=2,flag=12 },
																									     
                                            {levelmin =20, levelmax=100, name ="ؤ�����1",   type= 27798,   x=99, z=63, r=0,  ai=9, aiscript=559, count=1, facedir = 0, title = "",patrolid=5,flag=15 },
																									     
                                            {levelmin =20, levelmax=100, name ="ؤ�����2",   type= 27799,   x=99, z=48, r=0,  ai=9, aiscript=560, count=1, facedir = 0, title = "",patrolid=4,flag=14 },
                                            														     
                                            {levelmin =20, levelmax=100, name ="ؤ�����3",   type= 27800,   x=99, z=95, r=0,  ai=9, aiscript=561, count=1, facedir = 0, title = "",patrolid=7,flag=17 },
                                            														     
                                            {levelmin =20, levelmax=100, name ="ؤ�����4",   type= 27801,   x=99, z=79, r=0,  ai=9, aiscript=562, count=1, facedir = 0, title = "",patrolid=6,flag=16 },
                                           

                                        }




--Npc����
x700209_g_NpcCreate				=	{                                          
                                            {levelmin =20, levelmax=100, name ="��Ԫ�",   type= 25010,  x=65, z=19, r=0,  ai=7, aiscript=0,   facedir = 0, title = "",camp = 24},
									}

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700209_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)
	
end

-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  �����������ɹ�ʱ�� ��ʼˢ�ֺ�npc
--*********************************************************
-----------------------------------------------------------
function x700209_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  ��������id
	
	x700209_CreateNpc( sceneId)
	SetFubenData_Param(sceneId, x700209_CSP_B_FUBEN_STATUS,0 ) ;   


	local humancount = GetFuben_PlayerCount(sceneId);
	SetFubenData_Param(sceneId, x700209_CSP_HUMAN_COUNT, humancount);
	
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		SetFubenData_Param(sceneId, x700209_CSP_OBJID_START+i, humanId);
	end
end

-----------------------------------------------------------
--*********************************************************
--EnterTick  :  ��������
--*********************************************************
-----------------------------------------------------------
function x700209_EnterTick(sceneId, nowTickCount)
		
	if nowTickCount >= 2 and  nowTickCount<= x700209_g_nTextCount+1 then
		local nNpcId = GetFubenData_Param(sceneId, x700209_CSP_STARTNPC_ID)
		
		
		NpcTalk(sceneId, nNpcId, x700209_g_NpcTalkText[nowTickCount-1],  -1)
	end

        if nowTickCount == (x700209_g_nTextCount+2) then
		SetFubenData_Param( sceneId ,x700209_CSP_GAME_STARTED, 1)
		x700209_CreateBoss(sceneId,0)
        end
	local humancount = GetFuben_PlayerCount(sceneId);
	local nStarted = GetFubenData_Param( sceneId ,x700209_CSP_GAME_STARTED)
	
	if nStarted>0 then
		
		if humancount>0 then
			x700209_CheckMonsterRefresh(sceneId,nowTickCount)
		end
	end
end

function x700209_CheckMonsterRefresh(sceneId,nowTickCount)

	local nFubenStatus = GetFubenData_Param(sceneId, x700209_CSP_B_FUBEN_STATUS ) 

	if nFubenStatus~= 0 then
		return
	end

	local nCurrentStep = GetFubenData_Param(sceneId, x700209_CSP_CURRENTBOSS_INDEX)

	if nCurrentStep>8 then
		return 0;
	end

	local nTargetTick = x700209_g_Boss_Interval[nCurrentStep];

	local nCurrentTick = GetFubenData_Param(sceneId, x700209_CSP_CURRENTBOSS_TICK) + 1;

	SetFubenData_Param(sceneId, x700209_CSP_CURRENTBOSS_TICK,nCurrentTick)

	if nTargetTick ==nCurrentTick then
		if nCurrentStep<8 then
			x700209_CreateBoss(sceneId,nCurrentStep)
		end
	end

	for i = 0, nCurrentStep - 1 do
		local nBossId = GetFubenData_Param(sceneId, x700209_CSP_CURRENTBOSS_ID_START + i);
		local nBossTime = GetFubenData_Param(sceneId, x700209_CSP_CURRENTBOSS_TIME_START + i)+1;
		SetFubenData_Param(sceneId, x700209_CSP_CURRENTBOSS_TIME_START + i, nBossTime);

		if nBossId>=0 then
			if nBossTime>0 then
				if mod( nBossTime, 2 ) == 0 then
					x700209_g_CreateMonster(sceneId,i)
				end
			end
		end
	end
	
				
end


function x700209_CreateBoss(sceneId,index)

	local copyscenelevel = GetFubenData_Param(sceneId, x700209_CSP_FUBENLEVEL ) ;
	for i, item in x700209_g_BossCreate do

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then

            if item.flag == index   then

				local nForce = GetFubenData_Param(sceneId, x700209_CSP_FORCE )
				if nForce>x700209_g_MaxForce then
					--x700209_OnFubenFailed(sceneId,0)
					return
				end


                local nRet = 0
				if item.title~="" then
					nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700209_g_ScriptId,-1,21,-1, item.facedir,  "",item.title);
				else
					nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700209_g_ScriptId,-1,21,-1, item.facedir);
				
				end
				if item.patrolid>=0 then
					SetPatrolId(sceneId, nRet, item.patrolid)
				end

				SetFubenData_Param(sceneId, x700209_CSP_CURRENTBOSS_ID_START + index, nRet)
				SetFubenData_Param(sceneId, x700209_CSP_CURRENTBOSS_INDEX, index+1)
				SetFubenData_Param(sceneId, x700209_CSP_CURRENTBOSS_TICK, 0)
				SetFubenData_Param(sceneId, x700209_CSP_CURRENTBOSS_TIME_START + index, 0)

                --������10
                nForce = GetFubenData_Param(sceneId, x700209_CSP_FORCE ) + 10
                SetFubenData_Param(sceneId,x700209_CSP_FORCE,nForce )
                SetFubenData_Param(sceneId, x700209_CSP_BOSSINDEX,index +1 )


                --����BOSS����ʱ��
                local nTickCount = GetFubenData_Param( sceneId ,x700209_CSP_TICKCOUNT );
                SetFubenData_Param(sceneId, x700209_CSP_BOSSCREATETIME,nTickCount )

                --֪ͨ���
                local humancount = GetFuben_PlayerCount(sceneId);

                for i = 0, humancount - 1 do
                    local humanId = GetFuben_PlayerObjId(sceneId, i);

                    BeginQuestEvent(sceneId);
                        AddQuestText(sceneId,"�ж���������10, ������������"..nForce);
                    EndQuestEvent();
                    DispatchQuestTips(sceneId, humanId);
                end


				if nForce>x700209_g_MaxForce then
					x700209_OnFubenFailed(sceneId,0)
					return
				end

				
               
                break
            end
        end
    end

end





---------------------------------------------------------------------------------------------------
--����Monster
---------------------------------------------------------------------------------------------------
function x700209_g_CreateMonster(sceneId,index)


    local copyscenelevel = GetFubenData_Param(sceneId, x700209_CSP_FUBENLEVEL ) ;

	local nMonsterCount = GetFubenData_Param(sceneId, x700209_CSP_MONSTER_COUNT ) ;
	local nCount =nMonsterCount;

	local nTypeCount = x700209_g_MonsterCreate_Random_Count[index+1];
	local nTypeFlag = random(0,nTypeCount-1)
	nTypeFlag = index+nTypeFlag*10

	for i, item in x700209_g_MonsterCreate do

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then

            if item.flag == nTypeFlag  then

				local nForce = GetFubenData_Param(sceneId, x700209_CSP_FORCE )
				if nForce>x700209_g_MaxForce then
					--x700209_OnFubenFailed(sceneId,0)
					return
				end

                local monsterid = 0
				if item.title~="" then
					monsterid = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700209_g_ScriptId,-1,21,-1,item.facedir,  "",item.title);
                else
					monsterid = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700209_g_ScriptId,-1,21,-1,item.facedir);
                
				end
				if item.patrolid>=0 then
					SetPatrolId(sceneId, monsterid, item.patrolid)
				end

				SetFubenData_Param(sceneId, x700209_CSP_MONSTER_START+nCount, monsterid ) ;
				nCount = nCount +1


                --������1
                nForce = GetFubenData_Param(sceneId, x700209_CSP_FORCE ) + 1
                SetFubenData_Param(sceneId,x700209_CSP_FORCE,nForce )

                local humancount = GetFuben_PlayerCount(sceneId);

                --֪ͨ���
                for i = 0, humancount - 1 do
                    local humanId = GetFuben_PlayerObjId(sceneId, i);

                    BeginQuestEvent(sceneId);
                        AddQuestText(sceneId,"�ж���������1, ������������"..nForce);
                    EndQuestEvent();
                    DispatchQuestTips(sceneId, humanId);
                end

				if nForce>x700209_g_MaxForce then
					SetFubenData_Param(sceneId, x700209_CSP_MONSTER_COUNT, nCount ) ;
					x700209_OnFubenFailed(sceneId,0)
					return
				end

                break

            end
        end
    end


	SetFubenData_Param(sceneId, x700209_CSP_MONSTER_COUNT, nCount ) ;

end




function x700209_CreateNpc( sceneId )

	local copyscenelevel = GetFubenData_Param(sceneId, x700209_CSP_FUBENLEVEL ) ;

	for i, item in x700209_g_NpcCreate do

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
			local nRet = 0
			if item.title~="" then
				nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, -1,-1,item.camp,-1,item.facedir, "", item.title);
			else
				nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, -1,-1,item.camp,-1,item.facedir);
			
			end
			SetFubenData_Param(sceneId, x700209_CSP_STARTNPC_ID, nRet)
			break;
		end
	end

    
end


function x700209_OnFubenFailed(sceneId, nParam)
	SetFubenData_Param(sceneId, x700209_CSP_B_FUBEN_STATUS,2 ) ;   -- Failed

	if nParam==0 then
		x700209_ShowTipsToAll(sceneId, format("�ж���������%d, ����ʧ��",x700209_g_MaxForce))
	elseif nParam==1 then
		x700209_ShowTipsToAll(sceneId, "�����ļ��Ʋ���,��Ķ���, ����ʧ��")
	end


	local nCurrentStep = GetFubenData_Param(sceneId, x700209_CSP_CURRENTBOSS_INDEX)

	

	for i = 0, nCurrentStep - 1 do
		local nBossID = GetFubenData_Param(sceneId, x700209_CSP_CURRENTBOSS_ID_START + i)
		if nBossID>= 0 then
			DeleteMonster( sceneId,nBossID )
		end
	end

	local nMonsterCount = GetFubenData_Param(sceneId, x700209_CSP_MONSTER_COUNT)	

	for i=0, nMonsterCount-1 do
		local nMonsterId = GetFubenData_Param(sceneId, x700209_CSP_MONSTER_START+i)
		if nMonsterId>=0 then
		DeleteMonster( sceneId,nMonsterId )
	end
	end

	local nNpcObjId = GetFubenData_Param(sceneId, x700209_CSP_STARTNPC_ID)

	if nNpcObjId>=0 then
		DeleteMonster( sceneId,nNpcObjId )
	end

	x700209_ShowTipsToAll(sceneId, "���й�����ʧ")

	x700209_CreateLeaveNpc( sceneId)
end


function x700209_OnFubenSuccess(sceneId)
	SetFubenData_Param(sceneId, x700209_CSP_B_FUBEN_STATUS,1 ) ;   -- successed
	x700209_ShowTipsToAll(sceneId, "��ɫ������˸���")

	local nCurrentStep = GetFubenData_Param(sceneId, x700209_CSP_CURRENTBOSS_INDEX)
	for i = 0, nCurrentStep - 1 do
		local nBossID = GetFubenData_Param(sceneId, x700209_CSP_CURRENTBOSS_ID_START + i)
		if nBossID>= 0 then
		DeleteMonster( sceneId,nBossID )
	end
	end

	local nMonsterCount = GetFubenData_Param(sceneId, x700209_CSP_MONSTER_COUNT)	

	for i=0, nMonsterCount-1 do
		local nMonsterId = GetFubenData_Param(sceneId, x700209_CSP_MONSTER_START+i)
		if nMonsterId>=0 then
		DeleteMonster( sceneId,nMonsterId )
		end
	end

	x700209_ShowTipsToAll(sceneId, "���й�����ʧ")


	x700209_CreateSubmitNpc( sceneId)


	x700209_CreateRandomMonster(sceneId)
	
	
	
end



function x700209_CreateRandomMonster(sceneId)


	local rate = random(0,100)/100;
	if rate>= x700209_g_RandomBossRate then
		return 0;
	end

	local nFlag = random(0,3)

	

	local copyscenelevel = GetFubenData_Param(sceneId, x700209_CSP_FUBENLEVEL ) ;


	
	
	for i, item in x700209_g_Monster_Random_Create do --�������monster
		if item.flag == nFlag then
			if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
				local nBossID =0;
				if item.title~="" then
					nBossID = CreateMonster(sceneId, item.type, item.x,item.z, item.ai, item.aiscript, x700209_g_ScriptId, -1, 21,-1,item.facedir,  "",item.title)
				else
					nBossID = CreateMonster(sceneId, item.type, item.x,item.z, item.ai, item.aiscript, x700209_g_ScriptId, -1, 21,-1,item.facedir)
				
				end

				SetFubenData_Param(sceneId, x700209_B_CREATE_RANDOMBOSS, 1)
				SetFubenData_Param(sceneId, x700209_RANDOMBOSS_FLAG, nFlag)

				SetFubenData_Param(sceneId, x700209_CSP_RANDOM_BOSS_ID, nBossID)
			end

				
		end
	end

	x700209_ShowTipsToAll(sceneId, "ս�����֣�")

end


function x700209_ShowTipsToAll(sceneId, str)

	local humancount = GetFuben_PlayerCount(sceneId);

	--֪ͨ���
	for i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId,str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, humanId);
	end
end


function x700209_OnDie(sceneId, selfId, killerId)
	
	

	local nDieCount = GetFubenData_Param(sceneId, x700209_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700209_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	
	--// add for random boss event, add in 2009-5-20
	local bCreateRandomboss = GetFubenData_Param(sceneId, x700209_B_CREATE_RANDOMBOSS)

	if bCreateRandomboss>0 then
		local nRandomBossId = GetFubenData_Param(sceneId, x700209_CSP_RANDOM_BOSS_ID)
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

			local nHorseFlag = GetFubenData_Param(sceneId, x700209_RANDOMBOSS_FLAG);

			if nHorseFlag==0 then
				strHorseName = "��ʨ"
			elseif nHorseFlag==1 then
				strHorseName = "ѱ¹"
			elseif nHorseFlag==2 then
				strHorseName = "���"
			elseif nHorseFlag==3 then
				strHorseName = "��Ϭ"
			end


			local strMapName = "���ǵ�"
			
			----LuaAllScenceM2Wrold (sceneId,strCountryName.."��"..strPlayerName.."�����"..strMapName.."�ľ��ս�񣬾�츶���"..strHorseName.."��Ķ��ӣ�", 5, 1)
			
			
			--//--------------------------- ���纰�� end----------------------
		end
	end
	--//add end
	
	local nNpcObjId = GetFubenData_Param(sceneId, x700209_CSP_STARTNPC_ID)

	if nNpcObjId==selfId then
		SetFubenData_Param(sceneId, x700209_CSP_STARTNPC_ID,-1)
		x700209_OnFubenFailed(sceneId, 1)
		return
	end

	local bBoss  = 0;


	local nCurrentStep = GetFubenData_Param(sceneId, x700209_CSP_CURRENTBOSS_INDEX)

	

	for i = 0, nCurrentStep - 1 do
		local nBossID = GetFubenData_Param(sceneId, x700209_CSP_CURRENTBOSS_ID_START + i)
		if nBossID>=0 then
			if nBossID== selfId then
				SetFubenData_Param(sceneId, x700209_CSP_CURRENTBOSS_ID_START + i, -1)
				local nForce = GetFubenData_Param(sceneId, x700209_CSP_FORCE ) - 10;
				SetFubenData_Param(sceneId,x700209_CSP_FORCE,nForce )

				local humancount = GetFuben_PlayerCount(sceneId);

				--֪ͨ���
				for i = 0, humancount - 1 do
					local humanId = GetFuben_PlayerObjId(sceneId, i);

					BeginQuestEvent(sceneId);
						AddQuestText(sceneId,"�ж���������10, �������½���"..nForce);
					EndQuestEvent();
					DispatchQuestTips(sceneId, humanId);
				end

				--//add in 2009-3-5
				if nForce==0 then
					x700209_OnAllForceDie(sceneId)
				end
				--//add end

				bBoss = i+1;
				break;
			end
		end
	end

	if bBoss==x700209_g_SuccessBossInex then

--		--//--------------------------- ���纰�� Start--------------------
--		--ɱ������ boss
--		local nowTickCount = GetFubenData_Param(sceneId, x700209_CSP_TICKCOUNT)
--
--		local nowTime = x700209_g_TickTime* nowTickCount;
--
--		local nMinute = floor(nowTime/60)
--		local nSec = mod(nowTime,60)
--
--			
--		local strPlayerName = GetName(sceneId, killerId)     -- ɱ��������������
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
--		local strKillTime = format("%d��%d��", nMinute, nSec) -- ɱ��������¼�
--
--		
--		
--		----LuaAllScenceM2Wrold (sceneId,"#R���й¶����#G"..strPlayerName.."#R�Ĵ����£����ǵĶ�����ڽ��ǵ�������#G"..strKillTime.."#R�ͳ��������ص��谭��ͨ�����֮������赿����������", 0, 1)
--		
--
--		
		
		--//--------------------------- ���纰�� end----------------------

		x700209_OnFubenSuccess(sceneId)
		return
	end


	local nMonsterCount = GetFubenData_Param(sceneId, x700209_CSP_MONSTER_COUNT)	

	for i=0, nMonsterCount-1 do
		local nMonsterId = GetFubenData_Param(sceneId, x700209_CSP_MONSTER_START+i)
		if nMonsterId== selfId then
			for j=i, nMonsterCount-2 do
				local nNextId = GetFubenData_Param(sceneId, x700209_CSP_MONSTER_START+j+1)
				SetFubenData_Param(sceneId, x700209_CSP_MONSTER_START+j, nNextId)
				
			end
			SetFubenData_Param(sceneId, x700209_CSP_MONSTER_START+nMonsterCount-1,0)

			SetFubenData_Param(sceneId, x700209_CSP_MONSTER_COUNT,nMonsterCount-1)

			local nForce = GetFubenData_Param(sceneId, x700209_CSP_FORCE ) - 1;
			SetFubenData_Param(sceneId,x700209_CSP_FORCE,nForce )

			local humancount = GetFuben_PlayerCount(sceneId);

			--֪ͨ���
			for i = 0, humancount - 1 do
				local humanId = GetFuben_PlayerObjId(sceneId, i);

				BeginQuestEvent(sceneId);
					AddQuestText(sceneId,"�ж���������1, �������½���"..nForce);
				EndQuestEvent();
				DispatchQuestTips(sceneId, humanId);
			end

			--//add in 2009-3-5
			if nForce==0 then
				x700209_OnAllForceDie(sceneId)
			end
			--//add end

			break
		end
	end
	


	
end


--//add in 2009-3-5
function x700209_OnAllForceDie(sceneId)
	local nCurrentStep = GetFubenData_Param(sceneId, x700209_CSP_CURRENTBOSS_INDEX)

	if nCurrentStep>8 then
		return 0;
	end

	local nTargetTick = x700209_g_Boss_Interval[nCurrentStep];


	SetFubenData_Param(sceneId, x700209_CSP_CURRENTBOSS_TICK,nTargetTick-1)

	local humancount = GetFuben_PlayerCount(sceneId);

	--֪ͨ���
--	for i = 0, humancount - 1 do
--		local humanId = GetFuben_PlayerObjId(sceneId, i);
--
--		BeginQuestEvent(sceneId);
--			AddQuestText(sceneId,"�ɵ�Ư������һ��boss����Ҫ���ˡ���ʿ�ǣ���������ţ��");
--		EndQuestEvent();
--		DispatchQuestTips(sceneId, humanId);
--	end

end
--//add end

function x700209_OnAllMonsterDead( sceneId)
	--x700209_CreateSubmitNpc( sceneId)
end

function x700209_CreateSubmitNpc( sceneId)

	if x700209_g_SubmitNPC.title~="" then
		CreateMonster(sceneId, x700209_g_SubmitNPC.type, x700209_g_SubmitNPC.x, x700209_g_SubmitNPC.z, 3, 0, -1, x700209_g_SubmitNPC.guid, -1, -1,x700209_g_SubmitNPC.facedir, "", x700209_g_SubmitNPC.title )
	else
		CreateMonster(sceneId, x700209_g_SubmitNPC.type, x700209_g_SubmitNPC.x, x700209_g_SubmitNPC.z, 3, 0, -1, x700209_g_SubmitNPC.guid, -1, -1,x700209_g_SubmitNPC.facedir )
	
	end
end

function x700209_CreateLeaveNpc( sceneId)
	if x700209_g_LeaveNPC.title ~="" then
		CreateMonster(sceneId, x700209_g_LeaveNPC.type, x700209_g_LeaveNPC.x, x700209_g_LeaveNPC.z, 3, 0, -1, x700209_g_LeaveNPC.guid, -1, -1,x700209_g_LeaveNPC.facedir,  "",x700209_g_LeaveNPC.title )
	else
		CreateMonster(sceneId, x700209_g_LeaveNPC.type, x700209_g_LeaveNPC.x, x700209_g_LeaveNPC.z, 3, 0, -1, x700209_g_LeaveNPC.guid, -1, -1,x700209_g_LeaveNPC.facedir )
	end

end


--//added in 2009-3-17
---------------------------------------------------------------------------------------------------
--��������
---------------------------------------------------------------------------------------------------
function x700209_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

---------------------------------------------------------------------------------------------------
--�뿪����
---------------------------------------------------------------------------------------------------
function x700209_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
end
--//add end





