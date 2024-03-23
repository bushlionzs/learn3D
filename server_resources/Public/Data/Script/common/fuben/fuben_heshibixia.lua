---------------------------------------------------
-- File: 700009_fuben_dawushi_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700009_CSP_FUBENTYPE				= 	0
x700009_CSP_SCRIPTID				=	1
x700009_CSP_TICKCOUNT				= 	2
x700009_CSP_FROMSCENEID				= 	3
x700009_CSP_ISCLOSING				= 	4
x700009_CSP_LEAVECOUNTDOWN			= 	5
x700009_CSP_TEAMID					=	6
x700009_CSP_BACKSCENEX       		=   7
x700009_CSP_BACKSCENEZ      		=   8
x700009_CSP_FUBENLEVEL			=	9

x700009_CSP_KILLCOUNT				=	20
x700009_CSP_FUBEN_SCENE_ID			=	21
x700009_CSP_BOSSINDEX				=   22
x700009_CSP_BOSSCREATETIME			=	23
x700009_CSP_FORCE					=	24
x700009_CSP_GAME_STARTED            =   25
x700009_CSP_CURRENTBOSS_INDEX		=	26
x700009_CSP_CURRENTBOSS_TICK		=   27
x700009_CSP_STARTNPC_ID				=	28
x700009_CSP_B_FUBEN_STATUS			=	29

x700009_CSP_CURRENTBOSS_TIME_START	=   50
x700009_CSP_CURRENTBOSS_ID_START	=	60
x700009_CSP_MONSTER_COUNT			=	70
x700009_CSP_MONSTER_START			=	71

x700009_B_CREATE_RANDOMBOSS			=	230
x700009_CSP_RANDOM_BOSS_ID			=	231
x700009_RANDOMBOSS_FLAG				=	232

x700009_CSP_XIANJINBOSS				=	239

x700009_CSP_HUMAN_COUNT				=	240
x700009_CSP_OBJID_START				=	241

x700009_CSP_GUID_START              =   248  --��6��
x700009_CSP_FUBEN_TYPE				=	254	--��������ͨ��Ӣ�ۣ���������
x700009_CSP_FUBEN_MODE				=   255 
------------------------Scene System Setting -----------------------------------

x700009_g_ScriptId 					= 700009
------------------------- special for fuben----------------------
x700009_g_Boss_Interval = {2*12,2*12,2*12,2*12,2*12,2*12,2*12,2*12}  --bossˢ�¼��
x700009_g_SuccessBossInex			=	8	                         --�ɹ�����

x700009_g_MaxForce					=	50                           --ʧ������

x700009_g_NpcTalkText			=  { "�������죬����������","�ɼ�˼���Ļƽ�ʱ���ؽ���Ϊ��ʷ��"}
x700009_g_nTextCount			=	2


x700009_g_RandomBossRate		=	0.1


x700009_g_SubmitNPC                 =   { type =25011,guid= 150511,x = 69, z=20,facedir=0, title="" }
x700009_g_LeaveNPC					=   { type =25011,guid= 150511,x = 69, z=20,facedir=0, title="" }	





x700009_g_MonsterCreate_Random_Count = {2,2,2,2,2,2,2,2}



--Npc����
x700009_g_NpcCreate				=	{                                          
                                            {levelmin =20, levelmax=100, name ="��Ԫ�",   type= 25010,  x=65, z=19, r=0,  ai=7, aiscript=0,   facedir = 0, title = "",camp = 24},
									}



-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700009_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)

end

function x700009_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x700009_ShowTipsToAll(sceneId, str)

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

-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  �����������ɹ�ʱ�� ��ʼˢ�ֺ�npc
--*********************************************************
-----------------------------------------------------------
function x700009_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  ��������id
	
	x700009_CreateNpc( sceneId)
	SetFubenData_Param(sceneId, x700009_CSP_B_FUBEN_STATUS,0 ) ;   

end

function x700009_CheckMonsterRefresh(sceneId,nowTickCount)

	local nFubenStatus = GetFubenData_Param(sceneId, x700009_CSP_B_FUBEN_STATUS ) 

	if nFubenStatus~= 0 then
		return
	end

	local nCurrentStep = GetFubenData_Param(sceneId, x700009_CSP_CURRENTBOSS_INDEX)

	if nCurrentStep>8 then
		return 0;
	end

	local nTargetTick = x700009_g_Boss_Interval[nCurrentStep];

	local nCurrentTick = GetFubenData_Param(sceneId, x700009_CSP_CURRENTBOSS_TICK) + 1;

	SetFubenData_Param(sceneId, x700009_CSP_CURRENTBOSS_TICK,nCurrentTick)

	if nTargetTick ==nCurrentTick then
		if nCurrentStep<8 then
			x700009_CreateBoss(sceneId,nCurrentStep)
		end
	end

	for i = 0, nCurrentStep - 1 do
		local nBossId = GetFubenData_Param(sceneId, x700009_CSP_CURRENTBOSS_ID_START + i);
		local nBossTime = GetFubenData_Param(sceneId, x700009_CSP_CURRENTBOSS_TIME_START + i)+1;
		SetFubenData_Param(sceneId, x700009_CSP_CURRENTBOSS_TIME_START + i, nBossTime);

		if nBossId>=0 then
			if nBossTime>0 then
				if mod( nBossTime, 2 ) == 0 then
					x700009_g_CreateMonster(sceneId,i)
				end
			end
		end
	end
	
				
end

function x700009_EnterTick(sceneId, nowTickCount)
	if nowTickCount >= 2 and  nowTickCount<= x700009_g_nTextCount+1 then
		local nNpcId = GetFubenData_Param(sceneId, x700009_CSP_STARTNPC_ID)
		
		
		NpcTalk(sceneId, nNpcId, x700009_g_NpcTalkText[nowTickCount-1],  -1)
	end

	if nowTickCount == (x700009_g_nTextCount+2) then
		SetFubenData_Param( sceneId ,x700009_CSP_GAME_STARTED, 1)
		x700009_CreateBoss(sceneId,0)
	end

	local nStarted = GetFubenData_Param( sceneId ,x700009_CSP_GAME_STARTED)
	
	if nStarted>0 then
		

		x700009_CheckMonsterRefresh(sceneId,nowTickCount)
		
	end
end

function x700009_CreateBoss(sceneId,index)

	local fubenlevel = GetFubenData_Param(sceneId, x700009_CSP_FUBENLEVEL )
	local nIndexFrom = GetFubenDataPosByScriptID(x700009_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700009_g_ScriptId )
	local nFubenType = GetFubenData_Param(sceneId, x700009_CSP_FUBEN_TYPE)
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700009_g_ScriptId,nIndexFrom,i)
		if idScript == x700009_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then

            if flag == index   then

				local nForce = GetFubenData_Param(sceneId, x700009_CSP_FORCE )
				if nForce>x700009_g_MaxForce then
					--x700009_OnFubenFailed(sceneId,0)
					return
				end


                local nRet = 0
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700009_g_ScriptId,-1,21,-1, facedir,  "",title);
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700009_g_ScriptId,-1,21,-1, facedir);
				
				end
				if patrolid>=0 then
					SetPatrolId(sceneId, nRet, patrolid)
				end

				SetFubenData_Param(sceneId, x700009_CSP_CURRENTBOSS_ID_START + index, nRet)
				SetFubenData_Param(sceneId, x700009_CSP_CURRENTBOSS_INDEX, index+1)
				SetFubenData_Param(sceneId, x700009_CSP_CURRENTBOSS_TICK, 0)
				SetFubenData_Param(sceneId, x700009_CSP_CURRENTBOSS_TIME_START + index, 0)

                --������10
                nForce = GetFubenData_Param(sceneId, x700009_CSP_FORCE ) + 10
                SetFubenData_Param(sceneId,x700009_CSP_FORCE,nForce )
                SetFubenData_Param(sceneId, x700009_CSP_BOSSINDEX,index +1 )


                --����BOSS����ʱ��
                local nTickCount = GetFubenData_Param( sceneId ,x700009_CSP_TICKCOUNT );
                SetFubenData_Param(sceneId, x700009_CSP_BOSSCREATETIME,nTickCount )

                --֪ͨ���
                local humancount = GetFuben_PlayerCount(sceneId);

                for i = 0, humancount - 1 do
                    local humanId = GetFuben_PlayerObjId(sceneId, i);

                    BeginQuestEvent(sceneId);
                        AddQuestText(sceneId,"�ж���������10, ������������"..nForce);
                    EndQuestEvent();
                    DispatchQuestTips(sceneId, humanId);
                end


				if nForce>x700009_g_MaxForce then
					x700009_OnFubenFailed(sceneId,0)
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
function x700009_g_CreateMonster(sceneId,index)

	local nFubenType = GetFubenData_Param(sceneId, x700009_CSP_FUBEN_TYPE)
    local fubenlevel = GetFubenData_Param(sceneId, x700009_CSP_FUBENLEVEL ) ;

	local nMonsterCount = GetFubenData_Param(sceneId, x700009_CSP_MONSTER_COUNT ) ;
	local nCount =nMonsterCount;

	local nTypeCount = x700009_g_MonsterCreate_Random_Count[index+1];
	local nTypeFlag = random(0,nTypeCount-1)
	nTypeFlag = index+nTypeFlag*10

	local nIndexFrom = GetFubenDataPosByScriptID(x700009_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700009_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700009_g_ScriptId,nIndexFrom,i)
		if idScript == x700009_g_ScriptId and monsterFlag == 3 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then

            if flag == nTypeFlag  then

				local nForce = GetFubenData_Param(sceneId, x700009_CSP_FORCE )
				if nForce>x700009_g_MaxForce then
					--x700009_OnFubenFailed(sceneId,0)
					return
				end

                local monsterid = 0
				if title~="" then
					monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700009_g_ScriptId,-1,21,-1,facedir,  "",title);
                else
					monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700009_g_ScriptId,-1,21,-1,facedir);
                
				end
				if patrolid>=0 then
					SetPatrolId(sceneId, monsterid, patrolid)
				end

				SetFubenData_Param(sceneId, x700009_CSP_MONSTER_START+nCount, monsterid ) ;
				nCount = nCount +1


                --������1
                nForce = GetFubenData_Param(sceneId, x700009_CSP_FORCE ) + 1
                SetFubenData_Param(sceneId,x700009_CSP_FORCE,nForce )

                local humancount = GetFuben_PlayerCount(sceneId);

                --֪ͨ���
                for i = 0, humancount - 1 do
                    local humanId = GetFuben_PlayerObjId(sceneId, i);

                    BeginQuestEvent(sceneId);
                        AddQuestText(sceneId,"�ж���������1, ������������"..nForce);
                    EndQuestEvent();
                    DispatchQuestTips(sceneId, humanId);
                end

				if nForce>x700009_g_MaxForce then
					SetFubenData_Param(sceneId, x700009_CSP_MONSTER_COUNT, nCount ) ;
					x700009_OnFubenFailed(sceneId,0)
					return
				end

                break

            end
        end
    end


	SetFubenData_Param(sceneId, x700009_CSP_MONSTER_COUNT, nCount ) ;

end




function x700009_CreateNpc( sceneId )

	local fubenlevel = GetFubenData_Param(sceneId, x700009_CSP_FUBENLEVEL ) ;

	for i, item in x700009_g_NpcCreate do

        if item.levelmin <= fubenlevel and item.levelmax >= fubenlevel then
			local nRet = 0
			if item.title~="" then
				nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, -1,-1,item.camp,-1,item.facedir, "", item.title);
			else
				nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, -1,-1,item.camp,-1,item.facedir);
			
			end
			SetFubenData_Param(sceneId, x700009_CSP_STARTNPC_ID, nRet)
			break;
		end
	end

    
end


function x700009_OnFubenFailed(sceneId, nParam)
	SetFubenData_Param(sceneId, x700009_CSP_XIANJINBOSS, -1 )

	SetFubenData_Param(sceneId, x700009_CSP_B_FUBEN_STATUS,2 ) ;   -- Failed

	if nParam==0 then
		x700009_ShowTipsToAll(sceneId, format("�ж���������%d, ����ʧ��",x700009_g_MaxForce))
	elseif nParam==1 then
		x700009_ShowTipsToAll(sceneId, "�����ļ��Ʋ���,��Ķ���, ����ʧ��")
	end


	local nCurrentStep = GetFubenData_Param(sceneId, x700009_CSP_CURRENTBOSS_INDEX)

	

	for i = 0, nCurrentStep - 1 do
		local nBossID = GetFubenData_Param(sceneId, x700009_CSP_CURRENTBOSS_ID_START + i)
		if nBossID>= 0 then
			DeleteMonster( sceneId,nBossID )
		end
	end

	local nMonsterCount = GetFubenData_Param(sceneId, x700009_CSP_MONSTER_COUNT)	

	for i=0, nMonsterCount-1 do
		local nMonsterId = GetFubenData_Param(sceneId, x700009_CSP_MONSTER_START+i)
		if nMonsterId>=0 then
		DeleteMonster( sceneId,nMonsterId )
	end
	end

	local nNpcObjId = GetFubenData_Param(sceneId, x700009_CSP_STARTNPC_ID)

	if nNpcObjId>=0 then
		DeleteMonster( sceneId,nNpcObjId )
	end

	x700009_ShowTipsToAll(sceneId, "���й�����ʧ")

	x700009_CreateLeaveNpc( sceneId)
end


function x700009_OnFubenSuccess(sceneId)
	SetFubenData_Param(sceneId, x700009_CSP_B_FUBEN_STATUS,1 ) ;   -- successed
	x700009_ShowTipsToAll(sceneId, "��ɫ������˸���")

	local nCurrentStep = GetFubenData_Param(sceneId, x700009_CSP_CURRENTBOSS_INDEX)
	for i = 0, nCurrentStep - 1 do
		local nBossID = GetFubenData_Param(sceneId, x700009_CSP_CURRENTBOSS_ID_START + i)
		if nBossID>= 0 then
		DeleteMonster( sceneId,nBossID )
	end
	end

	local nMonsterCount = GetFubenData_Param(sceneId, x700009_CSP_MONSTER_COUNT)	

	for i=0, nMonsterCount-1 do
		local nMonsterId = GetFubenData_Param(sceneId, x700009_CSP_MONSTER_START+i)
		if nMonsterId>=0 then
		DeleteMonster( sceneId,nMonsterId )
		end
	end

	x700009_ShowTipsToAll(sceneId, "���й�����ʧ")


	x700009_CreateSubmitNpc( sceneId)


	--x700009_CreateRandomMonster(sceneId)
	
	CallScriptFunction( 701107, "OnSceneBossDie", sceneId, 2)
	CallScriptFunction( 701108, "OnSceneBossDie", sceneId, 2)
	
	
end



function x700009_CreateRandomMonster(sceneId)

	local nFubenType = GetFubenData_Param(sceneId, x700009_CSP_FUBEN_TYPE)
	if nFubenType ~= 0 then
		return
	end
	
	local rate = random(0,100)/100;
	local nStdRate = x700009_g_RandomBossRate
	local nFubenMode = GetFubenData_Param(sceneId, x700009_CSP_FUBEN_MODE)
	if nFubenMode ==1 then
		nStdRate = nStdRate*3
	end
	
	if rate>= nStdRate then
		return 0;
	end

	local nFlag = random(0,3)

	

	local fubenlevel = GetFubenData_Param(sceneId, x700009_CSP_FUBENLEVEL ) ;


	
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700009_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700009_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700009_g_ScriptId,nIndexFrom,i)
		if idScript == x700009_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel then
			if flag == nFlag then
			
				local nBossID =0;
				if title~="" then
					nBossID = CreateMonster(sceneId, type, x,z, ai, aiscript, x700009_g_ScriptId, -1, 21,-1,facedir,  "",title)
				else
					nBossID = CreateMonster(sceneId, type, x,z, ai, aiscript, x700009_g_ScriptId, -1, 21,-1,facedir)
				
				end

				SetFubenData_Param(sceneId, x700009_B_CREATE_RANDOMBOSS, 1)
				SetFubenData_Param(sceneId, x700009_RANDOMBOSS_FLAG, nFlag)

				SetFubenData_Param(sceneId, x700009_CSP_RANDOM_BOSS_ID, nBossID)
			end

				
		end
	end

	x700009_ShowTipsToAll(sceneId, "ս�����֣�")

end





function x700009_OnDie(sceneId, selfId, killerId)
	
	local xianjinboss = GetFubenData_Param(sceneId, x700009_CSP_XIANJINBOSS)
	if xianjinboss == selfId then
		local humancount = GetFuben_PlayerCount(sceneId);

	--֪ͨ���
		for i = 0, humancount - 1 do
			local humanId = GetFuben_PlayerObjId(sceneId, i);
			if GetLevel(sceneId, humanId) >= 80 then
				local refixInhExp = AddInherenceExp(sceneId, humanId, 600)
				local str = format("������%d���츳ֵ", refixInhExp)
				BeginQuestEvent(sceneId);
					AddQuestText(sceneId,str);
				EndQuestEvent();
				DispatchQuestTips(sceneId, humanId)
			end
		end
	end

	local nDieCount = GetFubenData_Param(sceneId, x700009_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700009_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	
	--// add for random boss event, add in 2009-5-20
	local bCreateRandomboss = GetFubenData_Param(sceneId, x700009_B_CREATE_RANDOMBOSS)

	if bCreateRandomboss>0 then
		local nRandomBossId = GetFubenData_Param(sceneId, x700009_CSP_RANDOM_BOSS_ID)
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

			local nHorseFlag = GetFubenData_Param(sceneId, x700009_RANDOMBOSS_FLAG);
			local fubenlevel = GetFubenData_Param(sceneId, x700009_CSP_FUBENLEVEL )
			
			if fubenlevel < 50 then
				if nHorseFlag==0 then
					strHorseName = "�ױ�"
				elseif nHorseFlag==1 then
					strHorseName = "����"
				elseif nHorseFlag==2 then
					strHorseName = "���"
				elseif nHorseFlag==3 then
					strHorseName = "����"
				end
			elseif fubenlevel < 70 then
				if nHorseFlag==0 then
					strHorseName = "��ʨ"
				elseif nHorseFlag==1 then
					strHorseName = "ѱ¹"
				elseif nHorseFlag==2 then
					strHorseName = "���"
				elseif nHorseFlag==3 then
					strHorseName = "��Ϭ"
				end
			elseif fubenlevel < 80 then
				if nHorseFlag==0 then
					strHorseName = "���ݻ�"
				elseif nHorseFlag==1 then
					strHorseName = "��ţ"
				elseif nHorseFlag==2 then
					strHorseName = "���"
				elseif nHorseFlag==3 then
					strHorseName = "����"
				end
			elseif fubenlevel < 110 then
				if nHorseFlag==0 then
					strHorseName = "���"
				elseif nHorseFlag==1 then
					strHorseName = "Ӧ��"
				elseif nHorseFlag==2 then
					strHorseName = "����"
				elseif nHorseFlag==3 then
				strHorseName = "����"
				end
			elseif fubenlevel < 130 then
				if nHorseFlag==0 then
					strHorseName = "���"
				elseif nHorseFlag==1 then
					strHorseName = "Ӧ��"
				elseif nHorseFlag==2 then
					strHorseName = "����"
				elseif nHorseFlag==3 then
					strHorseName = "����"
				end
			else
				if nHorseFlag==0 then
					strHorseName = "���"
				elseif nHorseFlag==1 then
					strHorseName = "Ӧ��"
				elseif nHorseFlag==2 then
					strHorseName = "����"
				elseif nHorseFlag==3 then
					strHorseName = "����"
				end
			end



			local strMapName = "���ǵ�"
			
			LuaAllScenceM2Wrold (sceneId,strCountryName.."��"..strPlayerName.."�����"..strMapName.."�ľ��ս�񣬾�츶���"..strHorseName.."��Ķ��ӣ�", 5, 1)
			
			
			--//--------------------------- ���纰�� end----------------------
		end
	end
	--//add end
	
	local nNpcObjId = GetFubenData_Param(sceneId, x700009_CSP_STARTNPC_ID)

	if nNpcObjId==selfId then
		SetFubenData_Param(sceneId, x700009_CSP_STARTNPC_ID,-1)
		x700009_OnFubenFailed(sceneId, 1)
		return
	end

	local bBoss  = 0;


	local nCurrentStep = GetFubenData_Param(sceneId, x700009_CSP_CURRENTBOSS_INDEX)

	

	for i = 0, nCurrentStep - 1 do
		local nBossID = GetFubenData_Param(sceneId, x700009_CSP_CURRENTBOSS_ID_START + i)
		if nBossID>=0 then
			if nBossID== selfId then
				SetFubenData_Param(sceneId, x700009_CSP_CURRENTBOSS_ID_START + i, -1)
				local nForce = GetFubenData_Param(sceneId, x700009_CSP_FORCE ) - 10;
				SetFubenData_Param(sceneId,x700009_CSP_FORCE,nForce )

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
					x700009_OnAllForceDie(sceneId)
				end
				--//add end

				bBoss = i+1;
				break;
			end
		end
	end

	if bBoss==x700009_g_SuccessBossInex then

--		--//--------------------------- ���纰�� Start--------------------
--		--ɱ������ boss
--		local nowTickCount = GetFubenData_Param(sceneId, x700009_CSP_TICKCOUNT)
--
--		local nowTime = x700009_g_TickTime* nowTickCount;
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
--		LuaAllScenceM2Wrold (sceneId,"#R���й¶����#G"..strPlayerName.."#R�Ĵ����£����ǵĶ�����ڽ��ǵ�������#G"..strKillTime.."#R�ͳ��������ص��谭��ͨ�����֮������赿����������", 0, 1)
--		
--
--		
		
		--//--------------------------- ���纰�� end----------------------

		x700009_OnFubenSuccess(sceneId)
		return
	end


	local nMonsterCount = GetFubenData_Param(sceneId, x700009_CSP_MONSTER_COUNT)	

	for i=0, nMonsterCount-1 do
		local nMonsterId = GetFubenData_Param(sceneId, x700009_CSP_MONSTER_START+i)
		if nMonsterId== selfId then
			for j=i, nMonsterCount-2 do
				local nNextId = GetFubenData_Param(sceneId, x700009_CSP_MONSTER_START+j+1)
				SetFubenData_Param(sceneId, x700009_CSP_MONSTER_START+j, nNextId)
				
			end
			SetFubenData_Param(sceneId, x700009_CSP_MONSTER_START+nMonsterCount-1,0)

			SetFubenData_Param(sceneId, x700009_CSP_MONSTER_COUNT,nMonsterCount-1)

			local nForce = GetFubenData_Param(sceneId, x700009_CSP_FORCE ) - 1;
			SetFubenData_Param(sceneId,x700009_CSP_FORCE,nForce )

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
				x700009_OnAllForceDie(sceneId)
			end
			--//add end

			break
		end
	end
	


	
end


--//add in 2009-3-5
function x700009_OnAllForceDie(sceneId)
	local nCurrentStep = GetFubenData_Param(sceneId, x700009_CSP_CURRENTBOSS_INDEX)

	if nCurrentStep>8 then
		return 0;
	end

	local nTargetTick = x700009_g_Boss_Interval[nCurrentStep];


	SetFubenData_Param(sceneId, x700009_CSP_CURRENTBOSS_TICK,nTargetTick-1)

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

function x700009_OnAllMonsterDead( sceneId)
	--x700009_CreateSubmitNpc( sceneId)
end

function x700009_CreateSubmitNpc( sceneId)

	if x700009_g_SubmitNPC.title~="" then
		CreateMonster(sceneId, x700009_g_SubmitNPC.type, x700009_g_SubmitNPC.x, x700009_g_SubmitNPC.z, 3, 0, -1, x700009_g_SubmitNPC.guid, -1, -1,x700009_g_SubmitNPC.facedir, "", x700009_g_SubmitNPC.title )
	else
		CreateMonster(sceneId, x700009_g_SubmitNPC.type, x700009_g_SubmitNPC.x, x700009_g_SubmitNPC.z, 3, 0, -1, x700009_g_SubmitNPC.guid, -1, -1,x700009_g_SubmitNPC.facedir )
	
	end

	CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnFubuenCompleted", sceneId)

	--// add for �ֽ𸱱�
	 x700009_CreateXianJinBoss(sceneId)
	 --// add end

	
end

function x700009_CreateLeaveNpc( sceneId)
	if x700009_g_LeaveNPC.title ~="" then
		CreateMonster(sceneId, x700009_g_LeaveNPC.type, x700009_g_LeaveNPC.x, x700009_g_LeaveNPC.z, 3, 0, -1, x700009_g_LeaveNPC.guid, -1, -1,x700009_g_LeaveNPC.facedir,  "",x700009_g_LeaveNPC.title )
	else
		CreateMonster(sceneId, x700009_g_LeaveNPC.type, x700009_g_LeaveNPC.x, x700009_g_LeaveNPC.z, 3, 0, -1, x700009_g_LeaveNPC.guid, -1, -1,x700009_g_LeaveNPC.facedir )
	end

	--// add for �ֽ𸱱�
	 x700009_CreateXianJinBoss(sceneId)
	 --// add end

end

----------------------------------------------------------
--�����ֽ�boss
----------------------------------------------------------

function x700009_CreateXianJinBoss(sceneId)

	local nFubenType = GetFubenData_Param(sceneId, x700009_CSP_FUBEN_TYPE)
	if nFubenType ~= 0 then
		return
	end
	
	local nFubenMode = GetFubenData_Param(sceneId, x700009_CSP_FUBEN_MODE)

	if nFubenMode == 0 then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700009_CSP_FUBENLEVEL ) ;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700009_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700009_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700009_g_ScriptId,nIndexFrom,i)
		if idScript == x700009_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700009_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700009_g_ScriptId, -1, 21,-1,facedir)
			end
			SetFubenData_Param(sceneId, x700009_CSP_XIANJINBOSS, nRet )
		end
	end

	x700009_ShowTipsToAll(sceneId, "����������֣�")
end
