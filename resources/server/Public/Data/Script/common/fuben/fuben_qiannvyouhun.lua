---------------------------------------------------
-- File: 700106_fuben_HUDI_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700106_CSP_FUBENTYPE				= 	0
x700106_CSP_SCRIPTID				=	1
x700106_CSP_TICKCOUNT				= 	2
x700106_CSP_FROMSCENEID				= 	3
x700106_CSP_ISCLOSING				= 	4
x700106_CSP_LEAVECOUNTDOWN			= 	5
x700106_CSP_TEAMID					=	6
x700106_CSP_BACKSCENEX       		=   7
x700106_CSP_BACKSCENEZ      		=   8
x700106_CSP_FUBENLEVEL				=	9

x700106_CSP_FUBEN_START				=   19
x700106_CSP_CURRENTSTEP				=   20

x700106_CSP_BOSS_ID					=   21
x700106_CSP_HEIWUCHANG_ID			=   22		--���޳�
x700106_CSP_BOSS1_ID				=   23
x700106_CSP_BOSS2_ID				=   24
x700106_CSP_BOSS3_ID				=   25

x700106_CSP_CURRENTSTEP_TICKCOUNT	=   27




x700106_CSP_MONSTER_COUNT			=	28
x700106_CSP_MONSTER_WAVE			=	29
x700106_CSP_NPCTALK_FLAG			=   30

x700106_CSP_NPCTALK_BOSS1_FLAG		=   31
x700106_CSP_NPCTALK_BOSS2_FLAG		=   32
x700106_CSP_NPCTALK_BOSS3_FLAG		=   33

x700106_CSP_NPCTALK_SHANGREN_FLAG	=   34

x700106_CSP_NIEXIAOQIAN_NPC_ID		=	100		--��СٻNPC ID
x700106_CSP_NIEXIAOQIAN_ID			=	101		--��СٻID
x700106_CSP_NINGCAICHEN_NPC_ID		=	102		--���ɳ�NPC ID
x700106_CSP_SHANREN_NPC_ID			=	103		--����NPC ID

x700106_CSP_XIANJINBOSS				=	239

x700106_CSP_HUMAN_COUNT				=	240
x700106_CSP_OBJID_START				=	241

x700106_CSP_GUID_START              =   248  --��6��
x700106_CSP_FUBEN_TYPE				=	254	--��������ͨ��Ӣ�ۣ���������
x700106_CSP_FUBEN_MODE				=   255 

x700106_g_nGrowpointType			=   547

------------------------Scene System Setting -----------------------------------

x700106_g_ScriptId 					= 	700106
x700106_g_MissionId					= 	6608

x700106_g_XiaoQianNPC               =   { type =50141,guid= 150588,x = 115, z=12, facedir =0, title="" }
x700106_g_ShanrenNPC                =   { type =50135,guid= 150590,x = 54, z=14, facedir =0, title="" }
x700106_g_EnterNPC                =   { type =50144,guid= 150591,x = 118, z=16, facedir =0, title="" }  --���NPC
--x700106_g_CaiChenGUID              =   150589  
										
x700106_g_NpcTalkTab				= 	{
											"ץסСٻ����������!",
											"�������������ģ�",
											"������Ļ��Ҹ��𣿣�",
										}
										
x700106_g_XiaoqianTalkTab			= 	{
											"�»�Ұ��׷�����ˣ����Ǹ��������ƽ�ħ�����ϣ������������ǣ�",
											"��˵��Ȫ·�����Ի�ƣ�ʹ��������ʱ�Ի���޳���ֹͣ�����ж���",
											"�������κ����ˣ�ֻ�л��������Ų���ͨ����",
											"���С�ģ�һ���ú��޳�׷�����ǵĻ�����Ҳ����ȥ�ظ��ˣ�",
											"���ھ���ǰ���ˣ�������ػ����ǵİ��޳��������ڴ�һƴ�ˣ�",
										}
										
x700106_g_ShangrenTalkTab			= 	{
											"�ٺ٣��þ�û���������ˡ������ʽ�����ô����������п�ʯ�Ļ���",
											"�ٺ٣��þ�û���������ˡ������ʽ�����ô����������п�ʯ�Ļ���",
											"�ٺ٣��þ�û���������ˡ������ʽ�����ô����������п�ʯ�Ļ���",
											"�ٺ٣��þ�û���������ˡ������ʽ�����ô����������п�ʯ�Ļ���",
											"�ٺ٣��þ�û���������ˡ������ʽ�����ô����������п�ʯ�Ļ���",
										}
																				
x700106_g_ShanrenInfoTab			= 	{			
											{title = "��һ�ضһ�[��ʯԭʯ]",itemId = 11990114,bonusItemId = 11990113,},
											{title = "�ڶ��ضһ�[��ʯԭʯ]",itemId = 11990114,bonusItemId = 11990113,},
											{title = "�����ضһ�[��ʯԭʯ]",itemId = 11990114,bonusItemId = 11990113,},
											{title = "���Ĺضһ�[��ʯԭʯ]",itemId = 11990115,bonusItemId = 11990113,},
											{title = "����ضһ�[��ʯԭʯ]",itemId = 11990115,bonusItemId = 11990113,},
										}	
x700106_g_MDInfoTab			= 			{			
											{MDdate = MD_EQUIP_EXCHANGE1_DAY, MDdateCount = MD_EQUIP_EXCHANGE1_DAYCOUNT},
											{MDdate = MD_EQUIP_EXCHANGE2_DAY, MDdateCount = MD_EQUIP_EXCHANGE2_DAYCOUNT},
											{MDdate = MD_EQUIP_EXCHANGE3_DAY, MDdateCount = MD_EQUIP_EXCHANGE3_DAYCOUNT},
											{MDdate = MD_EQUIP_EXCHANGE4_DAY, MDdateCount = MD_EQUIP_EXCHANGE4_DAYCOUNT},
											{MDdate = MD_EQUIP_EXCHANGE5_DAY, MDdateCount = MD_EQUIP_EXCHANGE5_DAYCOUNT},
										}											
										


x700106_g_BlockTab				= 	{
										{x1= 47, z1 = 8, x2=52, z2=18 , effectId = 68 },
										{x1= 16, z1 = 39, x2=30, z2=44 , effectId = 69},
										{x1= 65, z1 = 67, x2=71, z2=70 , effectId = 70},
										{x1= 75, z1 = 102, x2=80, z2=117 , effectId = 71},
										
									}


x700106_g_TimeDriverList		= 	{
										{2,12,12},
                                        {2,12,12,12},
                                        {2,12,12,12,12},
                                        {2,12,12,12,12,12},
                                        {2,12,12,12,12,12,12},
									}
--x700106_g_TimeDriverList		= 	{
--										{2,12},
--                                        {2,12},
--                                        {2,12},
--                                        {2,12},
--                                        {2,12},
--									}
x700106_g_XiaoqianPosList		= 	{
										{x = 54,z = 14},
										{x = 24,z = 36},
										{x = 68,z = 64},
										{x = 84,z = 107},
										{x = 25,z = 110},
										--{x = 21,z = 113},
									}
									
x700106_g_ChatList				= 	{		
										"����������֮ǰ�����Ҹ���Сٻ�����˿�ʼ�����ĵ�һ�̣��������ɳ��������Ѿ���ʧ�ˡ�",
										"ֻ���Ҹ�Сٻ����һ����������أ�Ҫ��ֻ���ң���ֻ��һ����į����ֹ����ج�Ρ�",			
										"����˵��������Ϊ���ط꣬���۷���֮���Ƕ�ô���������Σ����۷��ֺ������ǧɽ��ˮ���������Ͼ���", 					
										"ֻҪԵ�����֣������Ի��������š�",					
									}
x700106_g_BossInh				= 5		--boss�츳
x700106_g_MonsterInh			= 0.5		--monster�츳

x700106_g_DayCountUntil			= 1
x700106_g_NeedItemCount			= 1
-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------
---------------------------------------------------------------------------------------------------
--ȡ�õ�ǰ����
---------------------------------------------------------------------------------------------------
function x700106_GetDayCount(sceneId, humanId)
	local wave = GetFubenData_Param(sceneId, x700106_CSP_MONSTER_WAVE)		--���ﲨ��	
	local index = x700106_GetShanrenIndex(sceneId) 
	
	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, humanId, x700106_g_MDInfoTab[index].MDdate[1], x700106_g_MDInfoTab[index].MDdate[2],x700106_g_MDInfoTab[index].MDdate[3] );
	if lastday ~= today  and (lastday+1) ~= today then
		return 0
	end
	local daycount = GetQuestData(sceneId, humanId, x700106_g_MDInfoTab[index].MDdateCount[1], x700106_g_MDInfoTab[index].MDdateCount[2],x700106_g_MDInfoTab[index].MDdateCount[3] );

	return daycount;
end
---------------------------------------------------------------------------------------------------
--���õ������
---------------------------------------------------------------------------------------------------
function x700106_SetDayCount(sceneId, humanId)
	local wave = GetFubenData_Param(sceneId, x700106_CSP_MONSTER_WAVE)		--���ﲨ��	
	local index = x700106_GetShanrenIndex(sceneId) 
	
	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, humanId, x700106_g_MDInfoTab[index].MDdate[1], x700106_g_MDInfoTab[index].MDdate[2],x700106_g_MDInfoTab[index].MDdate[3] );

	if lastday ~= today  and (lastday+1) ~= today then
		SetQuestData(sceneId, humanId, x700106_g_MDInfoTab[index].MDdate[1], x700106_g_MDInfoTab[index].MDdate[2],x700106_g_MDInfoTab[index].MDdate[3], today)
		SetQuestData(sceneId, humanId, x700106_g_MDInfoTab[index].MDdateCount[1], x700106_g_MDInfoTab[index].MDdateCount[2],x700106_g_MDInfoTab[index].MDdateCount[3], 1)
	else
		local daycount = GetQuestData(sceneId, humanId, x700106_g_MDInfoTab[index].MDdateCount[1], x700106_g_MDInfoTab[index].MDdateCount[2],x700106_g_MDInfoTab[index].MDdateCount[3])
		SetQuestData(sceneId, humanId, x700106_g_MDInfoTab[index].MDdateCount[1], x700106_g_MDInfoTab[index].MDdateCount[2],x700106_g_MDInfoTab[index].MDdateCount[3], daycount+1)
	end
end

function x700106_CheckExchange(sceneId, humanId)
	local wave = GetFubenData_Param(sceneId, x700106_CSP_MONSTER_WAVE)		--���ﲨ��	
	local index = wave 
	
	if( x700106_g_DayCountUntil > 0 ) then
		
		if x700106_GetDayCount(sceneId, humanId) >= x700106_g_DayCountUntil then

			local str = format("���ֽ��ܶһ�%d��",x700106_g_DayCountUntil)

			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, humanId);
			return 0;
		end
	end

	local index = x700106_GetShanrenIndex(sceneId )
	local ItemCnt = GetItemCount( sceneId, humanId, x700106_g_ShanrenInfoTab[index].itemId)

	if ItemCnt<x700106_g_NeedItemCount then
		local str = format("����������߲���%d��",x700106_g_NeedItemCount)

		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent();

		DispatchQuestTips(sceneId, humanId);
		return 0;
	end

	return 1;
	
end

function x700106_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	local wave = GetFubenData_Param(sceneId, x700106_CSP_MONSTER_WAVE)		--���ﲨ��	
	local guid = GetMonsterGUID(sceneId, NPCId)
	--print("x700106_ProcEnumEvent",guid,wave)
	if guid == x700106_g_XiaoQianNPC.guid then	
		AddQuestNumText(sceneId,x700106_g_ScriptId,"�ðɣ������߰ɣ�", 0, 1)
		--AddQuestNumText(sceneId,x700106_g_ScriptId,"�������ʹ���޳����ٻ��ѷ���Ѫ��", 0,2)
	elseif guid == x700106_g_ShanrenNPC.guid then
		local index = x700106_GetShanrenIndex(sceneId)
		if index < 1 or index > getn(x700106_g_ShanrenInfoTab) then
			return
		end
		AddQuestNumText(sceneId,x700106_g_ScriptId,x700106_g_ShanrenInfoTab[index].title, 0, 10)
--	elseif guid == x700106_g_CaiChenGUID then
--		AddQuestNumText(sceneId,x700106_g_ScriptId,"��������", 0, 11)
	end
end

--��������
function x700106_TeleportDaguanyuan(sceneId, selfId)
		local selfcountry =GetCurCountry( sceneId, selfId)
        TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
        TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
		NewWorld( sceneId, selfId, 40, 203 + random( 0, 5), 55 + random( 0, 5), x700106_g_ScriptId)
end

function x700106_GetShanrenIndex(sceneId)
	local shanrenId = GetFubenData_Param(sceneId, x700106_CSP_SHANREN_NPC_ID)
	if shanrenId < 0 then
		return 0
	end
	local x,z = GetWorldPos(sceneId, shanrenId)
	local nlen = getn(x700106_g_XiaoqianPosList)
	--local index = 0
	for i = 1,nlen do
		if x700106_g_XiaoqianPosList[i].x == x and x700106_g_XiaoqianPosList[i].z == z then
			return i
		end
	end
	return 0
end

function x700106_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)

	local wave = GetFubenData_Param(sceneId, x700106_CSP_MONSTER_WAVE)		--���ﲨ��
        	
	local guid = GetMonsterGUID(sceneId, NPCId)
	if guid == x700106_g_XiaoQianNPC.guid then		--��Сٻ
		if nFlag == 1 then
			 x700106_OnFubenStart( sceneId )
		end
	elseif guid == x700106_g_ShanrenNPC.guid then		--����
		BeginQuestEvent(sceneId)

		--������Ϣ
		local index = x700106_GetShanrenIndex(sceneId)
		
		AddQuestText(sceneId,"#Y"..x700106_g_ShanrenInfoTab[index].title)
		
		if index == 1 then
			AddQuestText(sceneId,"1��������ʯ��#W�һ�1��#G��ʯԭʯ")
		elseif index == 2 then
			AddQuestText(sceneId,"1��������ʯ��#W�һ�1��#G��ʯԭʯ")	
		elseif index == 3 then
			AddQuestText(sceneId,"1��������ʯ��#W�һ�1��#G��ʯԭʯ")	
		elseif index == 4 then
			AddQuestText(sceneId,"1��ԭ����ʯ��#W�һ�1��#G��ʯԭʯ")		
		elseif index == 5 then
			AddQuestText(sceneId,"1��ԭ����ʯ��#W�һ�1��#G��ʯԭʯ")	
		end	
        AddQuestItemBonus(sceneId, x700106_g_ShanrenInfoTab[index].bonusItemId,1)
		EndQuestEvent()
		DispatchQuestInfo(sceneId, selfId, NPCId, x700106_g_ScriptId, -1);
--	elseif guid == x700106_g_CaiChenGUID then
--		x700106_TeleportDaguanyuan(sceneId, selfId)
	end
	--EnterAreaEventListHideNM(sceneId, selfId) 
    
end

function x700106_GetBonus(sceneId, selfId)

	--local wave = GetFubenData_Param(sceneId, x700106_CSP_MONSTER_WAVE)		--���ﲨ��
	local index = x700106_GetShanrenIndex(sceneId)	
	
	BeginAddItem(sceneId)
	AddBindItem( sceneId, x700106_g_ShanrenInfoTab[index].bonusItemId, 1 )
	
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		AddItemListToPlayer(sceneId,selfId)
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"�һ��ɹ���")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 1;
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"��Ʒ���������޷��õ���Ʒ��")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0;
	end
end

function x700106_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end
----------------------------------------------------------------------------------------------
--��ȷ����
----------------------------------------------------------------------------------------------
function x700106_ProcAccept( sceneId, selfId )
	--local wave = GetFubenData_Param(sceneId, x700106_CSP_MONSTER_WAVE)		--���ﲨ��
	local index = x700106_GetShanrenIndex( sceneId )
	local iRet = x700106_CheckExchange(sceneId, selfId)

	if iRet>0 then
		if x700106_GetBonus(sceneId, selfId)>0 then
			local iRet = DelItem(sceneId, selfId,x700106_g_ShanrenInfoTab[index].itemId,1)
			x700106_SetDayCount(sceneId, selfId);
		end
	end
end

function x700106_CreateShanrenNpc(sceneId, wave)
	local nRet = 0
	local x= x700106_g_XiaoqianPosList[wave].x
	local z= x700106_g_XiaoqianPosList[wave].z
	
	if x700106_g_ShanrenNPC.title~= "" then
		 nRet = CreateMonster(sceneId, x700106_g_ShanrenNPC.type, x, z, 3, 0, -1, x700106_g_ShanrenNPC.guid, -1,-1,x700106_g_ShanrenNPC.facedir, "", x700106_g_ShanrenNPC.title)
		 		
	else
		 nRet = CreateMonster(sceneId, x700106_g_ShanrenNPC.type, x, z, 3, 0, -1, x700106_g_ShanrenNPC.guid, -1,-1,x700106_g_ShanrenNPC.facedir)
		
	end
    
    SetFubenData_Param(sceneId, x700106_CSP_SHANREN_NPC_ID, nRet )
    
    SetFubenData_Param(sceneId, x700106_CSP_NPCTALK_SHANGREN_FLAG, 0 )
end


function x700106_CreateEnterNpc(sceneId)

	
	if x700106_g_EnterNPC.title~= "" then
		 CreateMonster(sceneId, x700106_g_EnterNPC.type, x700106_g_EnterNPC.x, x700106_g_EnterNPC.z, 3, 0, -1, x700106_g_EnterNPC.guid, -1,-1,x700106_g_EnterNPC.facedir, "", x700106_g_EnterNPC.title)
		 		
	else
		 CreateMonster(sceneId, x700106_g_EnterNPC.type, x700106_g_EnterNPC.x, x700106_g_EnterNPC.z, 3, 0, -1, x700106_g_EnterNPC.guid, -1,-1,x700106_g_EnterNPC.facedir)
		
	end

end


---------------------------------------------------------------------------------------------------
--����ʱ��
---------------------------------------------------------------------------------------------------
function x700106_ProcTiming( sceneId, selfId, ScriptId, MissionId )

end
--//add end
function x700106_CreateNingcaichenNpc( sceneId)    --�������ɳ�NPC
	--print("x700106_CreateNingcaichenNpc")
	local fubenlevel = GetFubenData_Param(sceneId, x700106_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700106_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700106_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700106_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700106_g_ScriptId,nIndexFrom,i)
		if idScript == x700106_g_ScriptId and monsterFlag == 12 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
		    local nRet = 0
		    
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, 3, 0, -1, guid, -1,-1,facedir,  "",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, 3, 0, -1, guid, -1,-1,facedir)
			
			end
			SetFubenData_Param(sceneId, x700106_CSP_NINGCAICHEN_NPC_ID, nRet )
			--SetPatrolId(sceneId, nRet, 0)
			return
	    end
	end
end

function x700106_CreateNiexiaoqianNpc( sceneId)    --������СٻNPC

	local nRet = 0
	if x700106_g_XiaoQianNPC.title~= "" then
		 nRet = CreateMonster(sceneId, x700106_g_XiaoQianNPC.type, x700106_g_XiaoQianNPC.x, x700106_g_XiaoQianNPC.z, 3, 0, -1, x700106_g_XiaoQianNPC.guid, -1,-1,x700106_g_XiaoQianNPC.facedir, "", x700106_g_XiaoQianNPC.title)
		 		
	else
		 nRet = CreateMonster(sceneId, x700106_g_XiaoQianNPC.type, x700106_g_XiaoQianNPC.x, x700106_g_XiaoQianNPC.z, 3, 0, -1, x700106_g_XiaoQianNPC.guid, -1,-1,x700106_g_XiaoQianNPC.facedir)
		
	end

	SetFubenData_Param(sceneId, x700106_CSP_NIEXIAOQIAN_NPC_ID, nRet )
end
function x700106_CreateNiexiaoqian( sceneId)    --������Сٻ

	local fubenlevel = GetFubenData_Param(sceneId, x700106_CSP_FUBENLEVEL )

	local nFubenType = GetFubenData_Param(sceneId, x700106_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700106_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700106_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700106_g_ScriptId,nIndexFrom,i)
		if idScript == x700106_g_ScriptId and monsterFlag == 13 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
		    local nRet = 0
		    
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, 7, aiscript, x700106_g_ScriptId, -1, 7,-1,facedir,  "",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, 7, aiscript, x700106_g_ScriptId, -1, 7,-1,facedir)
			
			end
			SetFubenData_Param(sceneId, x700106_CSP_NIEXIAOQIAN_ID, nRet ) ;
			SetPatrolId(sceneId, nRet, 0)
        end
	end

end

function x700106_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x700106_ShowTipsToAll(sceneId, str)

	local humancount = GetFuben_PlayerCount(sceneId);

	--֪ͨ���
	for i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId,str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, humanId);
		Msg2Player(sceneId, humanId, str, 0, 2)
	end
end


function x700106_AddGateBlocks( sceneId )
	
	local blocknum = getn(x700106_g_BlockTab)
	for i = 1,blocknum do
		AddSceneTempImpassable(sceneId,x700106_g_BlockTab[i].x1,x700106_g_BlockTab[i].z1,x700106_g_BlockTab[i].x2,x700106_g_BlockTab[i].z2)
		
		local humancount = GetFuben_PlayerCount(sceneId);
		for j = 0, humancount - 1 do
			local humanId = GetFuben_PlayerObjId(sceneId, j);

			CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,humanId,x700106_g_BlockTab[i].effectId )

		end
		
	end
end
function x700106_DelGateBlocks( sceneId )
	
	local blocknum = getn(x700106_g_BlockTab)
	for i = 1,blocknum do
		DelSceneTempImpassable(sceneId,x700106_g_BlockTab[i].x1,x700106_g_BlockTab[i].z1,x700106_g_BlockTab[i].x2,x700106_g_BlockTab[i].z2)
		local humancount = GetFuben_PlayerCount(sceneId);
		for j = 0, humancount - 1 do
			local humanId = GetFuben_PlayerObjId(sceneId, j);
			CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,humanId,x700106_g_BlockTab[i].effectId )
		end
	end
end

function x700106_DeleteGateBlock( sceneId, index )
	if index < 1 or index > getn(x700106_g_BlockTab) then
		return
	end
	local i = index
	DelSceneTempImpassable(sceneId,x700106_g_BlockTab[i].x1,x700106_g_BlockTab[i].z1,x700106_g_BlockTab[i].x2,x700106_g_BlockTab[i].z2)
	local humancount = GetFuben_PlayerCount(sceneId);
		for j = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, j);
		CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,humanId,x700106_g_BlockTab[i].effectId )
	end
	
	
end


function x700106_OnFubenStart( sceneId )

	SetFubenData_Param(sceneId, x700106_CSP_FUBEN_START, 1 ) 
	SetFubenData_Param(sceneId, x700106_CSP_CURRENTSTEP, 0)
	
	SetFubenData_Param(sceneId, x700106_CSP_HEIWUCHANG_ID, -1)
	
	x700106_AddGateBlocks(sceneId)
	
	local xiaoqianNPC = GetFubenData_Param(sceneId, x700106_CSP_NIEXIAOQIAN_NPC_ID )
	DeleteMonster(sceneId,xiaoqianNPC) --ɾ��СٻNPC
	x700106_CreateNiexiaoqian( sceneId)
	x700106_CreateHeiwuchang(sceneId)	

end

function x700106_OnFubenFail(sceneId)
	SetFubenData_Param(sceneId, x700106_CSP_FUBEN_START, 0)
	
	local heiwuchangId = GetFubenData_Param(sceneId, x700106_CSP_HEIWUCHANG_ID)
	if heiwuchangId >= 0 then
		DeleteMonster(sceneId,heiwuchangId)	--ɾ�����޳�
	end
	local shanrenId = GetFubenData_Param(sceneId, x700106_CSP_SHANREN_NPC_ID)
	if shanrenId >= 0 then
		DeleteMonster(sceneId,shanrenId)	--ɾ������
	end
	x700106_ShowTipsToAll(sceneId, "����ʧ�ܣ����뿪������")
end
-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  �����������ɹ�ʱ�� ��ʼˢ�ֺ�npc
--*********************************************************
-----------------------------------------------------------
function x700106_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  ��������id
	--print("x700106_OnFubenSceneCreated")

	x700106_CreateNiexiaoqianNpc( sceneId)
	x700106_AddGateBlocks(sceneId)
	SetFubenData_Param(sceneId, x700106_CSP_XIANJINBOSS, -1 )
	SetFubenData_Param(sceneId, x700106_CSP_NIEXIAOQIAN_ID, -1 )
	
	SetFubenData_Param(sceneId, x700106_CSP_FUBEN_START, 0 )
	
	SetFubenData_Param(sceneId, x700106_CSP_MONSTER_WAVE, 0 )
	
	SetFubenData_Param(sceneId, x700106_CSP_NPCTALK_FLAG, 0 )
	
	SetFubenData_Param(sceneId, x700106_CSP_NPCTALK_BOSS1_FLAG, 0 )
	SetFubenData_Param(sceneId, x700106_CSP_NPCTALK_BOSS2_FLAG, 0 )
	SetFubenData_Param(sceneId, x700106_CSP_NPCTALK_BOSS3_FLAG, 0 )
	
	SetFubenData_Param(sceneId, x700106_CSP_NPCTALK_SHANGREN_FLAG, 1 )
	
	SetFubenData_Param(sceneId, x700106_CSP_BOSS1_ID, -1 )
	SetFubenData_Param(sceneId, x700106_CSP_BOSS2_ID, -1 )
	SetFubenData_Param(sceneId, x700106_CSP_BOSS3_ID, -1 )	

	x700106_CreateEnterNpc(sceneId)
	
	local weekIndex = GetWeekIndex()
	local nHumanCount = GetScenePlayerCount( sceneId)
	if nHumanCount > 0 then
	    for i = 0, nHumanCount do
	        local objId = GetScenePlayerObjId( sceneId,i)
	        if objId >= 0 then
	        	local week = GetQuestData(sceneId, objId, MD_FUBEN_XIAOQIAN_DATE[1], MD_FUBEN_XIAOQIAN_DATE[2], MD_FUBEN_XIAOQIAN_DATE[3])
	        	SetQuestData(sceneId, objId, MD_FUBEN_XIAOQIAN_DATE[1], MD_FUBEN_XIAOQIAN_DATE[2], MD_FUBEN_XIAOQIAN_DATE[3], weekIndex)
	        	if week ~= weekIndex then
	        		SetQuestData(sceneId, objId, MD_FUBEN_XIAOQIAN_FLAG[1], MD_FUBEN_XIAOQIAN_FLAG[2], MD_FUBEN_XIAOQIAN_FLAG[3], 0)
	        	end
	        end
		end
	end
	    
	
	
	--x700106_OnFubenStart( sceneId )
   	--x700106_CreateMonster( sceneId )

end

function x700106_EnterTick(sceneId, nowTickCount)
	local start = GetFubenData_Param(sceneId, x700106_CSP_FUBEN_START ) 
	if start == 0 then
		return
	end
	local xiaoqianId = GetFubenData_Param(sceneId, x700106_CSP_NIEXIAOQIAN_ID )
	if xiaoqianId < 0 then
		return
	end  
	
	
	local shangrenId = GetFubenData_Param(sceneId, x700106_CSP_SHANREN_NPC_ID )
	local shangrenFlag = GetFubenData_Param(sceneId, x700106_CSP_NPCTALK_SHANGREN_FLAG )
	if shangrenId >= 0 and shangrenFlag == 0 then
		local shangrenIndex = x700106_GetShanrenIndex(sceneId)
		if shangrenIndex > 0 then
			NpcTalk(sceneId, shangrenId, x700106_g_ShangrenTalkTab[shangrenIndex],  -1)	 
			SetFubenData_Param(sceneId, x700106_CSP_NPCTALK_SHANGREN_FLAG, 1 )
		end
	end
	
	
	local boss1 = GetFubenData_Param(sceneId, x700106_CSP_BOSS1_ID )
	local boss2 = GetFubenData_Param(sceneId, x700106_CSP_BOSS2_ID )
	local boss3 = GetFubenData_Param(sceneId, x700106_CSP_BOSS3_ID )
	local flag1 = GetFubenData_Param(sceneId, x700106_CSP_NPCTALK_BOSS1_FLAG )
	local flag2 = GetFubenData_Param(sceneId, x700106_CSP_NPCTALK_BOSS2_FLAG )
	local flag3 = GetFubenData_Param(sceneId, x700106_CSP_NPCTALK_BOSS3_FLAG )
	if boss1 >= 0 and flag1 == 0 then
		NpcTalk(sceneId, boss1, "���������ҵ�������ȴ������˿��~��",  -1)	 
		SetFubenData_Param(sceneId, x700106_CSP_NPCTALK_BOSS1_FLAG, 1 )
	end
	if boss2 >= 0 and flag2 == 0 then
		SetFubenData_Param(sceneId, x700106_CSP_NPCTALK_BOSS2_FLAG, 1 )
	end
	if boss3 >= 0 and flag3 == 0 then
		SetFubenData_Param(sceneId, x700106_CSP_NPCTALK_BOSS3_FLAG, 1 )
	end
	
	
	
	local hewuchangId = GetFubenData_Param(sceneId, x700106_CSP_HEIWUCHANG_ID )
	if hewuchangId == -1 then
    	--x700106_CreateHeiwuchang(sceneId)	--���޳�         TEST
    end
    
    local caichenNpc = GetFubenData_Param(sceneId, x700106_CSP_NINGCAICHEN_NPC_ID)
	local talkFlag = GetFubenData_Param(sceneId, x700106_CSP_NPCTALK_FLAG)
    if caichenNpc >= 0 and xiaoqianId >= 0 and talkFlag == 1 then
		NpcTalk(sceneId, caichenNpc, x700106_g_ChatList[1],  -1)	 
		NpcTalk(sceneId, caichenNpc, x700106_g_ChatList[2],  -1)	 
		NpcTalk(sceneId, xiaoqianId, x700106_g_ChatList[3],  -1)	 
		NpcTalk(sceneId, xiaoqianId, x700106_g_ChatList[4],  -1)	
		SetFubenData_Param(sceneId, x700106_CSP_NPCTALK_FLAG, 2) 
		x700106_OnFubenEnd(sceneId)
		return
	end
		
		
    heiwuchangId = GetFubenData_Param(sceneId, x700106_CSP_HEIWUCHANG_ID )
    if heiwuchangId >= 0 then
    	local ran = random(1,3)
    	NpcTalk(sceneId, hewuchangId, x700106_g_NpcTalkTab[ran],  -1)	 
    	
    	--local dis = GetDist(xiaoqianId,hewuchangId)
    	--if dis <= 5 then
    		--x700106_OnFubenFail(sceneId)
    		--return
    	--end
    end
    
   
    local wave = GetFubenData_Param(sceneId, x700106_CSP_MONSTER_WAVE)		--���ﲨ��	
    
    local x,z = GetWorldPos(sceneId, xiaoqianId)
    
    local listlen = getn(x700106_g_XiaoqianPosList)
   	if (wave+1) <= listlen then
	    if x700106_g_XiaoqianPosList[wave+1].x == x and x700106_g_XiaoqianPosList[wave+1].z == z then
	    	wave = wave + 1
	    	--print("x700106_EnterTick in pos wave=",wave)
	    	NpcTalk(sceneId, xiaoqianId, x700106_g_XiaoqianTalkTab[wave],  -1)	 
    		SetFubenData_Param(sceneId, x700106_CSP_MONSTER_WAVE, wave)
	    	SetFubenData_Param(sceneId, x700106_CSP_CURRENTSTEP, 1)
			--print("x700106_EnterTick wave",wave)
		else
			--return
		end
	else
		
    end
    ------------------------------------------------------------------
    wave = GetFubenData_Param(sceneId, x700106_CSP_MONSTER_WAVE)		--���ﲨ��	
    local nCurrentStep = GetFubenData_Param(sceneId, x700106_CSP_CURRENTSTEP);
    

    if nCurrentStep<=0 then
		return
	end
	local nLen = getn(x700106_g_TimeDriverList[wave])
	if nCurrentStep> nLen then
		return
	end
	
	local nCurrentStepTickCount = GetFubenData_Param(sceneId, x700106_CSP_CURRENTSTEP_TICKCOUNT)+1;
	SetFubenData_Param(sceneId, x700106_CSP_CURRENTSTEP_TICKCOUNT, nCurrentStepTickCount)
	local nNextStepTime = x700106_g_TimeDriverList[wave][nCurrentStep];
	if nCurrentStepTickCount>=nNextStepTime then
		
		SetFubenData_Param(sceneId, x700106_CSP_CURRENTSTEP_TICKCOUNT, 0)
		SetFubenData_Param(sceneId, x700106_CSP_CURRENTSTEP,nCurrentStep+1 )
		if wave >= 3 then   --�ӵ�3����ʼ����BOSS
			if nCurrentStep < nLen  then   
				x700106_CreateMonster( sceneId, nCurrentStep )
			else
				x700106_CreateBoss(sceneId, wave)
			end
    	else    
    		x700106_CreateMonster( sceneId, nCurrentStep )
    	end
	end
end
function x700106_CreateHeiwuchang(sceneId)	--���޳�

	local fubenlevel = GetFubenData_Param(sceneId, x700106_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700106_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700106_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700106_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700106_g_ScriptId,nIndexFrom,i)
		if idScript == x700106_g_ScriptId and monsterFlag == 7 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
		    local nRet = 0
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700106_g_ScriptId, -1, 25,-1,facedir,  "",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700106_g_ScriptId, -1, 25,-1,facedir)
			
			end
			
			SetPatrolId(sceneId, nRet, 5)
			SetFubenData_Param(sceneId, x700106_CSP_HEIWUCHANG_ID, nRet)		
			
		end
	end       
end
function x700106_CreateBoss(sceneId,wave)
	local nFlag = 0
	if wave == 3 then
		nFlag = 9
	elseif wave == 4 then
		nFlag = 10
	elseif wave == 5 then
		nFlag = 8
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700106_CSP_FUBENLEVEL )

	local nFubenType = GetFubenData_Param(sceneId, x700106_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700106_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700106_g_ScriptId )
	local nRemainCount = GetFubenData_Param(sceneId, x700106_CSP_MONSTER_COUNT ) 
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700106_g_ScriptId,nIndexFrom,i)
		if idScript == x700106_g_ScriptId and monsterFlag == nFlag and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
		    local nRet = 0
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700106_g_ScriptId, -1, 21,-1,facedir,  "",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700106_g_ScriptId, -1, 21,-1,facedir)
			
			end
			
			if nFlag == 8 then
				SetFubenData_Param(sceneId, x700106_CSP_BOSS3_ID, nRet )		--���޳� ���BOSS
			elseif nFlag == 9 then
				SetFubenData_Param(sceneId, x700106_CSP_BOSS1_ID, nRet )
			elseif nFlag == 10 then
				SetFubenData_Param(sceneId, x700106_CSP_BOSS2_ID, nRet )
			end
			nRemainCount = nRemainCount + 1
			--SetFubenData_Param(sceneId, x700106_CSP_MONSTER_WAVE, wave+1)		--���ﲨ��
			SetPatrolId(sceneId, nRet, patrolid)
		end
	end
	SetFubenData_Param(sceneId, x700106_CSP_MONSTER_COUNT, nRemainCount ) 
end

---------------------------------------------------------------------------------------------------
--����Monster
---------------------------------------------------------------------------------------------------
function x700106_CreateMonster(sceneId, nStep) --����С��
	--print("x700106_CreateMonster")

    local fubenlevel = GetFubenData_Param(sceneId, x700106_CSP_FUBENLEVEL ) ;
	local wave = GetFubenData_Param(sceneId, x700106_CSP_MONSTER_WAVE ) ;
	local nCount = 0
	local nFubenType = GetFubenData_Param(sceneId, x700106_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700106_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700106_g_ScriptId )
	local nRemainCount = GetFubenData_Param(sceneId, x700106_CSP_MONSTER_COUNT ) 
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700106_g_ScriptId,nIndexFrom,i)
		if idScript == x700106_g_ScriptId and monsterFlag == wave and levelmin <= fubenlevel and levelmax >= fubenlevel and flag == nStep and nFubenType == flag3 then
            
                local rx = random(-r,r)
                local x = x + rx
                local rz = random(-r,r)
                local z = z + rz
		        local nRet = 0
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700106_g_ScriptId, -1, 21,-1, facedir,  "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700106_g_ScriptId, -1, 21,-1, facedir)
				
				end
				nRemainCount = nRemainCount + 1
				
				SetPatrolId(sceneId, nRet, patrolid)
            
        end
	end
	--print("x700106_CreateMonster nRemainCount",nRemainCount)
	SetFubenData_Param(sceneId, x700106_CSP_MONSTER_COUNT, nRemainCount ) 
end


function x700106_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	--print("x700106_ProcAreaEntered",zoneId)

	--@param sceneId: ����Id
	--@param selfId: ���ObjId (�������EnterAreaҲ�ᴥ�����ʱ��)
	--@param zoneId: ����Id
	--@param MissionId: ����id\
	if zoneId == 0 then  --����
		--local BossId = GetFubenData_Param(sceneId, x700106_CSP_BOSS_ID)
		--if BossId ~= -2 then
			--return --TEST
		--end
		
		--print("BossId",BossId)
		--CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700106_g_MissionId, x700106_g_ScriptId)

	elseif zoneId == 1 then
		--CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700106_g_MissionId, x700106_g_ScriptId)
	
	end

end	

------------------------------------------------------------------------------------------
--�뿪����
---------------------------------------------------------------------------------------------------
function x700106_ProcAreaLeaved( sceneId, selfId, zoneId, MissionId )
	EnterAreaEventListHideNM(sceneId, selfId)
end


function x700106_OnFubenEnd(sceneId)
	x700106_DelGateBlocks( sceneId )
	SetFubenData_Param(sceneId, x700106_CSP_FUBEN_START, 0 ) 
	local heiwuchangId = GetFubenData_Param(sceneId, x700106_CSP_HEIWUCHANG_ID)
	if heiwuchangId >= 0 then
		DeleteMonster(sceneId,heiwuchangId)	--ɾ�����޳�
		SetFubenData_Param(sceneId, x700106_CSP_HEIWUCHANG_ID, -2)	
	end
	x700106_ShowTipsToAll(sceneId, "�ɹ���ɱ���޳���������ɣ����˳�������")
end

function x700106_AddPlayerInh(sceneId, objId, multi)  
	local level =GetLevel( sceneId, objId)
	local inh =  floor(level*multi)
	local refixInh = AddInherenceExp(sceneId, objId, inh)
	local msg = format("������%d���츳ֵ��",refixInh)
	Msg2Player(sceneId, objId, msg, 0, 2)
	Msg2Player(sceneId, objId, msg, 0, 3)
end

function x700106_OnDie(sceneId, selfId, killerId)

	local boss3 = GetFubenData_Param(sceneId, x700106_CSP_BOSS3_ID )		--���޳� ���BOSS
	local boss1 = GetFubenData_Param(sceneId, x700106_CSP_BOSS1_ID)
	local boss2 = GetFubenData_Param(sceneId, x700106_CSP_BOSS2_ID)
	if boss3 == selfId then
		local nHumanCount = GetScenePlayerCount( sceneId)
	    if nHumanCount > 0 then
	        for i = 0, nHumanCount do
	            local objId = GetScenePlayerObjId( sceneId,i)
	            if objId >= 0 then
	            	local multi = 1
	            	if IsHaveSpecificImpact( sceneId, objId, 7510) == 1 or IsHaveSpecificImpact( sceneId, objId, 7511) == 1  or IsHaveSpecificImpact( sceneId, objId, 9007) == 1 then --˫������
		            	multi = multi + 1
	        		end
	        		if IsHaveSpecificImpact( sceneId, objId, 9015) == 1 then --�츳��
		            	multi = multi + 1
	        		end
	        		if IsHaveSpecificImpact( sceneId, objId, 9012) == 1 then --��ނ���
						multi =  multi + 0.20
					end
					multi = multi * x700106_g_BossInh
	        		x700106_AddPlayerInh(sceneId, objId, multi) 
	    		end
	    	end
	    end
	    --SetFubenData_Param(sceneId, x700106_CSP_BOSS3_ID, -2 )
	elseif boss1 == selfId then
		local nHumanCount = GetScenePlayerCount( sceneId)
	    if nHumanCount > 0 then
	        for i = 0, nHumanCount do
	            local objId = GetScenePlayerObjId( sceneId,i)
	            if objId >= 0 then
	            	local multi = 1
	            	if IsHaveSpecificImpact( sceneId, objId, 7510) == 1 or IsHaveSpecificImpact( sceneId, objId, 7511) == 1  or IsHaveSpecificImpact( sceneId, objId, 9007) == 1 then --˫������
		            	multi = multi + 1
	        		end
	        		if IsHaveSpecificImpact( sceneId, objId, 9015) == 1 then --�츳��
		            	multi = multi + 1
	        		end
	        		if IsHaveSpecificImpact( sceneId, objId, 9012) == 1 then --��ނ���
						multi =  multi + 0.20
					end
	        		multi = multi * x700106_g_BossInh
	        		x700106_AddPlayerInh(sceneId, objId, multi) 
	    		end
	    	end
	    end
	    SetFubenData_Param(sceneId, x700106_CSP_BOSS1_ID, -2 )
	elseif boss2 == selfId then
		local nHumanCount = GetScenePlayerCount( sceneId)
	    if nHumanCount > 0 then
	        for i = 0, nHumanCount do
	            local objId = GetScenePlayerObjId( sceneId,i)
	            if objId >= 0 then
	            	local multi = 1
	            	if IsHaveSpecificImpact( sceneId, objId, 7510) == 1 or IsHaveSpecificImpact( sceneId, objId, 7511) == 1  or IsHaveSpecificImpact( sceneId, objId, 9007) == 1 then --˫������
		            	multi = multi + 1
	        		end
	        		if IsHaveSpecificImpact( sceneId, objId, 9015) == 1 then --�츳��
		            	multi = multi + 1
	        		end
	        		if IsHaveSpecificImpact( sceneId, objId, 9012) == 1 then --��ނ���
						multi =  multi + 0.20
					end
					multi = multi * x700106_g_BossInh
	        		x700106_AddPlayerInh(sceneId, objId, multi) 
	    		end
	    	end
	    end
	    SetFubenData_Param(sceneId, x700106_CSP_BOSS2_ID, -2 )
	else
		local nHumanCount = GetScenePlayerCount( sceneId)
	    if nHumanCount > 0 then
	        for i = 0, nHumanCount do
	            local objId = GetScenePlayerObjId( sceneId,i)
	            if objId >= 0 then
	            	local multi = 1
	            	if IsHaveSpecificImpact( sceneId, objId, 7510) == 1 or IsHaveSpecificImpact( sceneId, objId, 7511) == 1  or IsHaveSpecificImpact( sceneId, objId, 9007) == 1 then --˫������
		            	multi = multi + 1
	        		end
	        		if IsHaveSpecificImpact( sceneId, objId, 9015) == 1 then --�츳��
		            	multi = multi + 1
	        		end
	        		if IsHaveSpecificImpact( sceneId, objId, 9012) == 1 then --��ނ���
						multi =  multi + 0.20
					end
					multi = multi * x700106_g_MonsterInh
	        		x700106_AddPlayerInh(sceneId, objId, multi) 
	        	end
	    	end
	    end
	end		
				
				
	local xiaoqianId = GetFubenData_Param(sceneId, x700106_CSP_NIEXIAOQIAN_ID )
	if selfId == xiaoqianId then
		 SetFubenData_Param(sceneId, x700106_CSP_NIEXIAOQIAN_ID, -2 )
		 x700106_OnFubenFail(sceneId)
		 return
	end
	
	local bossId3 = GetFubenData_Param(sceneId, x700106_CSP_BOSS3_ID)
	if bossId3 == selfId then
		x700106_CreateNingcaichenNpc( sceneId)    --�������ɳ�NPC
		
		local caichenNpc = GetFubenData_Param(sceneId, x700106_CSP_NINGCAICHEN_NPC_ID)
		xiaoqianId = GetFubenData_Param(sceneId, x700106_CSP_NIEXIAOQIAN_ID )
		local talkFlag = GetFubenData_Param(sceneId, x700106_CSP_NPCTALK_FLAG)
		if caichenNpc >= 0 and xiaoqianId >= 0 and talkFlag == 1 then
			--NpcTalk(sceneId, caichenNpc, x700106_g_ChatList[1],  -1)	 
			--NpcTalk(sceneId, xiaoqianId, x700106_g_ChatList[2],  -1)	 
			--NpcTalk(sceneId, caichenNpc, x700106_g_ChatList[3],  -1)	 
			--NpcTalk(sceneId, xiaoqianId, x700106_g_ChatList[4],  -1)	
			--SetFubenData_Param(sceneId, x700106_CSP_NPCTALK_FLAG, 2) 
			--x700106_OnFubenEnd(sceneId)
		end
		if caichenNpc >= 0 and xiaoqianId >= 0 then
			SetFubenData_Param(sceneId, x700106_CSP_NPCTALK_FLAG, 1)
		end
		
	end
	
	local nCurMonsterCount = GetFubenData_Param(sceneId, x700106_CSP_MONSTER_COUNT)-1 
	SetFubenData_Param(sceneId, x700106_CSP_MONSTER_COUNT, nCurMonsterCount)
	if nCurMonsterCount <= 0 then
		x700106_OnAllMonsterDead( sceneId)
	end
end

function x700106_OnAllMonsterDead( sceneId)
	local wave = GetFubenData_Param(sceneId, x700106_CSP_MONSTER_WAVE)		--���ﲨ��
	
	local nCurrentStep = GetFubenData_Param(sceneId, x700106_CSP_CURRENTSTEP)
	if nCurrentStep<=0 then
		return
	end
	local nLen = getn(x700106_g_TimeDriverList[wave])
	if nCurrentStep > nLen then
		x700106_DeleteGateBlock( sceneId, wave )
		--SetFubenData_Param(sceneId, x700106_CSP_MONSTER_WAVE, wave + 1)		--���ﲨ��
		SetFubenData_Param(sceneId, x700106_CSP_CURRENTSTEP, 0)
		local xiaoqianId = GetFubenData_Param(sceneId, x700106_CSP_NIEXIAOQIAN_ID) 
		if xiaoqianId >= 0 then
			if wave >= 5 then
				SetPatrolId(sceneId, xiaoqianId, 21)
			else
				SetPatrolId(sceneId, xiaoqianId, wave)
			end
			
			--SetFubenData_Param(sceneId, x700106_CSP_SHANREN_NPC_ID, nRet )
			local shanrenId = GetFubenData_Param(sceneId, x700106_CSP_SHANREN_NPC_ID) 
			if shanrenId >= 0 then
				DeleteMonster(sceneId,shanrenId) --ɾ������NPC
				SetFubenData_Param(sceneId, x700106_CSP_SHANREN_NPC_ID, -1) 
			end
			x700106_CreateShanrenNpc(sceneId,  wave)
		end
		return
	end
	
	local listlen = getn(x700106_g_XiaoqianPosList)
	--if wave == listlen then
		--x700106_CreateNingcaichenNpc(sceneId)
	--end
	local nNextStepTime = x700106_g_TimeDriverList[wave][nCurrentStep]
	SetFubenData_Param(sceneId, x700106_CSP_CURRENTSTEP_TICKCOUNT, nNextStepTime-1)
	
	local niexiaoqianId = GetFubenData_Param(sceneId, x700106_CSP_NIEXIAOQIAN_ID)
	if niexiaoqianId >= 0 then
		--SetPatrolId(sceneId, niexiaoqianId, wave-1)
	end
end


function x700106_CreateSubmitNpc( sceneId)
	if x700106_g_SubmitNPC.title~="" then
		CreateMonster(sceneId, x700106_g_SubmitNPC.type, x700106_g_SubmitNPC.x, x700106_g_SubmitNPC.z, 3, 0, -1, x700106_g_SubmitNPC.guid, -1,-1,x700106_g_SubmitNPC.facedir,  "",x700106_g_SubmitNPC.title)
	else
		CreateMonster(sceneId, x700106_g_SubmitNPC.type, x700106_g_SubmitNPC.x, x700106_g_SubmitNPC.z, 3, 0, -1, x700106_g_SubmitNPC.guid, -1,-1,x700106_g_SubmitNPC.facedir)
	
	end
	 --// add end

--	 CallScriptFunction( 701107, "OnSceneBossDie", sceneId, 0)
--
--	 local bKillShark = GetFubenData_Param(sceneId, x700106_CSP_B_KILL_SHARK);
--
--	 if bKillShark<=0 then
--		CallScriptFunction( 701108, "OnSceneBossDie", sceneId, 0)
--	 end
end

----------------------------------------------------------
--�����ֽ�boss
----------------------------------------------------------

function x700106_CreateXianJinBoss(sceneId)
	local nFubenType = GetFubenData_Param(sceneId, x700106_CSP_FUBEN_TYPE)
	if nFubenType ~= 0 then
		return
	end
	
	local nFubenMode = GetFubenData_Param(sceneId, x700106_CSP_FUBEN_MODE)

	if nFubenMode ==0 then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700106_CSP_FUBENLEVEL ) ;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700106_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700106_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700106_g_ScriptId,nIndexFrom,i)
		if idScript == x700106_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700106_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700106_g_ScriptId, -1, 21,-1,facedir)
			end
			SetFubenData_Param(sceneId, x700106_CSP_XIANJINBOSS, nRet )
		end
	end

	x700106_ShowTipsToAll(sceneId, "����������֣�")
end

