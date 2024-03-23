---------------------------------------------------
-- File: 700013_fuben_dawushi_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700013_CSP_FUBENTYPE				= 	0
x700013_CSP_SCRIPTID				=	1
x700013_CSP_TICKCOUNT				= 	2
x700013_CSP_FROMSCENEID				= 	3
x700013_CSP_ISCLOSING				= 	4
x700013_CSP_LEAVECOUNTDOWN			= 	5
x700013_CSP_TEAMID					=	6
x700013_CSP_BACKSCENEX       		=   7
x700013_CSP_BACKSCENEZ      		=   8
x700013_CSP_FUBENLEVEL			=	9


x700013_CSP_ARRAYID					=   21
x700013_CSP_COUNT					=	23
x700013_CSP_TOTALCOUNT				=	24	
x700013_CSP_TIME_COUNT				=	25
x700013_CSP_TIME_DOWN				=	26
x700013_CSP_TIME_BACKUP				=	27
x700013_CSP_TIME_BISHEN				=	28
x700013_CSP_COUNTDOWN				=	29
x700013_CSP_NPCID					=   30

x700013_CSP_MONSTER_COUNT			=	31
x700013_CSP_MONSTERCONVCOUNT		=	32
x700013_CSP_NKILLMONSTER			=	33
x700013_CSP_MONSTERCOUNT            =   34      --当前组别ID
x700013_CSP_TOTALBIAN				=	35
x700013_CSP_TOTALDISAPEAR			=	36
x700013_CSP_BOSSLOGIC				=	37
x700013_CSP_BONUSLOGIC				=	38
x700013_CSP_BOSSID					=	39
x700013_CSP_GROUP					=	40
x700013_CSP_KILLCOUNT				=	41
x700013_CSP_START					=	51

x700013_CSP_B_BIANSHEN				=	238
x700013_CSP_XIANJINBOSS				=	239


x700013_CSP_GUID_START              =   248  --空6个
x700013_CSP_FUBEN_TYPE				=	254	--试练，普通，英雄，三种类型
x700013_CSP_FUBEN_MODE				=   255 



------------------------Scene System Setting -----------------------------------

x700013_g_ScriptId 					= 700013

--------------------------- special for this fuben ---------------------
--NPC引领时说话的内容
x700013_g_NpcText					=	{
											"冰之灵，多疑之灵，让人失去信念！", 
											"巨之灵，慢之根，自大让人迷失！", 
											"地之灵，痴之源泉，蒙蔽人的慧心！", 
											"聚之灵，是嗔念之灵，一念地狱，一念天堂！", 
											"不要被你的欲望所困！", 
											"炎之灵，是贪欲之火！三大戒之首！", 
											"坚持住，不能倒下！", 
											"战胜最后的心魔，小心了！", 
										}

x700013_g_NeedKillMonster			=  65	

x700013_g_SubmitNPC                 =   { type =25033,guid= 150533,x = 32, z=34, facedir = 0, title = "" }


--创建时间
x700013_g_Timer0                    = 1
x700013_g_Timer1                    = 2
x700013_g_Timer2                    = 3 --boss
x700013_g_Timer3                    = 4
x700013_g_Timer4                    = 4
x700013_g_Timer5                    = 3 --boss
x700013_g_Timer6                    = 4
x700013_g_Timer7                    = 0

--变身时间
x700013_g_Timer0_r                  = 4
x700013_g_Timer1_r                  = 4
x700013_g_Timer2_r                  = 12    --boss
x700013_g_Timer3_r                  = 6
x700013_g_Timer4_r                  = 6
x700013_g_Timer5_r                  = 18    --boss
x700013_g_Timer6_r                  = 6
x700013_g_Timer7_r                  = 12

--每个刷怪点的倒计时计数
x700013_g_CountDown					= 2



x700013_g_NPCType					= 	25033

x700013_g_NpcGUID                   =   {
                                            {guid = 150000, name = "指灵禅师"},
                                        }

x700013_g_NpcCreate					=	{
											{	hash=1, type=x700013_g_NPCType,	x=15,	z=15,	ai=3, aiscript=-1,facedir = 0, title = "",objid = 150000,campid = -1 },
										}
	

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700013_ProcEventEntry(sceneId, selfId, NPCId)
	
end



function x700013_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x700013_ShowTipsToAll(sceneId, str)

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
function x700013_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  副本场景id
	SetFubenData_Param(sceneId, x700013_CSP_XIANJINBOSS, -1 )
	SetFubenData_Param( sceneId, x700013_CSP_B_BIANSHEN, 0);
	SetFubenData_Param(sceneId, x700013_CSP_ARRAYID, -1);	

	x700013_CreateNPC( sceneId);


end

function x700013_EnterTick(sceneId, nowTickCount)
	if nowTickCount >= 2 then
		x700013_UpdateMonsterParam( sceneId )
	end

	local nTotalCount = GetFubenData_Param( sceneId, 24 )

	local TotalDisapear = GetFubenData_Param( sceneId, 36 )

	local nArray = GetFubenData_Param( sceneId, 21 )

	local nMonsterCount = GetFubenData_Param(sceneId, x700013_CSP_MONSTER_COUNT,     31);--总数3
	local nDieCount = GetFubenData_Param(sceneId, x700013_CSP_KILLCOUNT)

	--x700013_ShowTipsToAll(sceneId, format("nTotalCount=%d, nMonsterCount=%d, nDieCount=%d",nTotalCount,nMonsterCount,nDieCount))
end
---------------------------------------------------------------------------------------------------
--创建BOSS
---------------------------------------------------------------------------------------------------
function x700013_CreateBoss(sceneId)

	local fubenlevel = GetFubenData_Param(sceneId, x700013_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700013_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700013_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700013_g_ScriptId )

	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700013_g_ScriptId,nIndexFrom,i)
		if idScript == x700013_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
		    local bossid = 0;
			if title~="" then
				bossid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700013_g_ScriptId, -1, 21, -1, facedir, "", title)
			else
				bossid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700013_g_ScriptId, -1, 21, -1, facedir)
			end
			SetFubenData_Param( sceneId, x700013_CSP_BOSSID, bossid )
			
		end
	end
end



function x700013_CreateNPC( sceneId)
	for i, item in x700013_g_NpcCreate do
		local NPCID, NPCGUID;
		
		if item.title~="" then
			NPCID, NPCGUID = CreateMonster( sceneId, item.type, item.x, item.z, item.ai, item.aiscript, -1, item.objid, -1, -1, item.facedir,  "",item.title);
		else
			NPCID, NPCGUID = CreateMonster( sceneId, item.type, item.x, item.z, item.ai, item.aiscript, -1, item.objid, -1, -1, item.facedir);
		end

		SetFubenData_Param( sceneId, x700013_CSP_NPCID, NPCID);
	end
end



---------------------------------------------------------------------------------------------------
--设置怪物数据
---------------------------------------------------------------------------------------------------
function x700013_SetMonsterParam( sceneId, arrayId)
	local patrolId = arrayId - 1
    if arrayId == 0 then
        SetFubenData_Param(sceneId, x700013_CSP_ARRAYID,           arrayId             );
        SetFubenData_Param(sceneId, x700013_CSP_COUNT,             1                   );
	    SetFubenData_Param(sceneId, x700013_CSP_TOTALCOUNT,        0                   );
	    SetFubenData_Param(sceneId, x700013_CSP_TIME_COUNT,        0                   );
		SetFubenData_Param(sceneId, x700013_CSP_GROUP,        		0                   );
        SetFubenData_Param(sceneId, x700013_CSP_TIME_DOWN,         x700013_g_Timer0    );
        SetFubenData_Param(sceneId, x700013_CSP_TIME_BACKUP,       x700013_g_Timer0    );
        SetFubenData_Param(sceneId, x700013_CSP_TIME_BISHEN,       x700013_g_Timer0_r  );
		SetFubenData_Param(sceneId, x700013_CSP_COUNTDOWN,         x700013_g_CountDown );

		SetFubenData_Param(sceneId, x700013_CSP_MONSTER_COUNT,     3                   );--总数3
    elseif arrayId == 1 then
        SetFubenData_Param(sceneId, x700013_CSP_ARRAYID,           arrayId             );
        SetFubenData_Param(sceneId, x700013_CSP_COUNT,             2                   );
	    SetFubenData_Param(sceneId, x700013_CSP_TOTALCOUNT,        0                   );
	    SetFubenData_Param(sceneId, x700013_CSP_TIME_COUNT,        0                   );
		SetFubenData_Param(sceneId, x700013_CSP_GROUP,        		0                   );
        SetFubenData_Param(sceneId, x700013_CSP_TIME_DOWN,         x700013_g_Timer1    );
        SetFubenData_Param(sceneId, x700013_CSP_TIME_BACKUP,       x700013_g_Timer1    );
        SetFubenData_Param(sceneId, x700013_CSP_TIME_BISHEN,       x700013_g_Timer1_r  );
        SetFubenData_Param(sceneId, x700013_CSP_COUNTDOWN,         x700013_g_CountDown );
		SetFubenData_Param(sceneId, x700013_CSP_MONSTER_COUNT,     6                   );--总数6
		--npc talk
		local id = GetFubenData_Param( sceneId, x700013_CSP_NPCID);
		NpcTalk( sceneId, id, x700013_g_NpcText[ arrayId], -1);
		--npc move to target
		SetPatrolId( sceneId, id, patrolId);
	elseif arrayId == 2 then
        SetFubenData_Param(sceneId, x700013_CSP_ARRAYID,           arrayId             );
        SetFubenData_Param(sceneId, x700013_CSP_COUNT,             1                   );
	    SetFubenData_Param(sceneId, x700013_CSP_TOTALCOUNT,        0                   );
	    SetFubenData_Param(sceneId, x700013_CSP_TIME_COUNT,        0                   );
		SetFubenData_Param(sceneId, x700013_CSP_GROUP,        		0                   );
        SetFubenData_Param(sceneId, x700013_CSP_TIME_DOWN,         x700013_g_Timer2    );
        SetFubenData_Param(sceneId, x700013_CSP_TIME_BACKUP,       x700013_g_Timer2    );
        SetFubenData_Param(sceneId, x700013_CSP_TIME_BISHEN,       x700013_g_Timer2_r  );
        SetFubenData_Param(sceneId, x700013_CSP_COUNTDOWN,         x700013_g_CountDown );
		SetFubenData_Param(sceneId, x700013_CSP_MONSTER_COUNT,     1                   );--总数1
		--npc talk
		local id = GetFubenData_Param( sceneId, x700013_CSP_NPCID);
		NpcTalk( sceneId, id, x700013_g_NpcText[ arrayId], -1);
		--npc move to target
		SetPatrolId( sceneId, id, patrolId);
	elseif arrayId == 3 then
        SetFubenData_Param(sceneId, x700013_CSP_ARRAYID,           arrayId             );
        SetFubenData_Param(sceneId, x700013_CSP_COUNT,             4                   );
	    SetFubenData_Param(sceneId, x700013_CSP_TOTALCOUNT,        0                   );
	    SetFubenData_Param(sceneId, x700013_CSP_TIME_COUNT,        0                   );
		SetFubenData_Param(sceneId, x700013_CSP_GROUP,        		0                   );
        SetFubenData_Param(sceneId, x700013_CSP_TIME_DOWN,         x700013_g_Timer3    );
        SetFubenData_Param(sceneId, x700013_CSP_TIME_BACKUP,       x700013_g_Timer3    );
        SetFubenData_Param(sceneId, x700013_CSP_TIME_BISHEN,       x700013_g_Timer3_r  );
        SetFubenData_Param(sceneId, x700013_CSP_COUNTDOWN,         x700013_g_CountDown );
		SetFubenData_Param(sceneId, x700013_CSP_MONSTER_COUNT,     12                  );--总数12
		--npc talk
		local id = GetFubenData_Param( sceneId, x700013_CSP_NPCID);
		NpcTalk( sceneId, id, x700013_g_NpcText[ arrayId], -1);
		--npc move to target
		SetPatrolId( sceneId, id, patrolId);
    elseif arrayId == 4 then
        SetFubenData_Param(sceneId, x700013_CSP_ARRAYID,           arrayId             );
        SetFubenData_Param(sceneId, x700013_CSP_COUNT,             6                   );
	    SetFubenData_Param(sceneId, x700013_CSP_TOTALCOUNT,        0                   );
	    SetFubenData_Param(sceneId, x700013_CSP_TIME_COUNT,        0                   );
		SetFubenData_Param(sceneId, x700013_CSP_GROUP,        		0                   );
        SetFubenData_Param(sceneId, x700013_CSP_TIME_DOWN,         x700013_g_Timer4    );
        SetFubenData_Param(sceneId, x700013_CSP_TIME_BACKUP,       x700013_g_Timer4    );
        SetFubenData_Param(sceneId, x700013_CSP_TIME_BISHEN,       x700013_g_Timer4_r  );
        SetFubenData_Param(sceneId, x700013_CSP_COUNTDOWN,         x700013_g_CountDown );
		SetFubenData_Param(sceneId, x700013_CSP_MONSTER_COUNT,     18                  );--总数18
		--npc talk
		local id = GetFubenData_Param( sceneId, x700013_CSP_NPCID);
		NpcTalk( sceneId, id, x700013_g_NpcText[ arrayId], -1);
		--npc move to target
		SetPatrolId( sceneId, id, patrolId);
    elseif arrayId == 5 then
        SetFubenData_Param(sceneId, x700013_CSP_ARRAYID,           arrayId             );
        SetFubenData_Param(sceneId, x700013_CSP_COUNT,             1                   );
	    SetFubenData_Param(sceneId, x700013_CSP_TOTALCOUNT,        0                   );
	    SetFubenData_Param(sceneId, x700013_CSP_TIME_COUNT,        0                   );
		SetFubenData_Param(sceneId, x700013_CSP_GROUP,        		0                   );
        SetFubenData_Param(sceneId, x700013_CSP_TIME_DOWN,         x700013_g_Timer5    );
        SetFubenData_Param(sceneId, x700013_CSP_TIME_BACKUP,       x700013_g_Timer5    );
        SetFubenData_Param(sceneId, x700013_CSP_TIME_BISHEN,       x700013_g_Timer5_r  );
        SetFubenData_Param(sceneId, x700013_CSP_COUNTDOWN,         x700013_g_CountDown );
		SetFubenData_Param(sceneId, x700013_CSP_MONSTER_COUNT,     1                   );--总数1
		--npc talk
		local id = GetFubenData_Param( sceneId, x700013_CSP_NPCID);
		NpcTalk( sceneId, id, x700013_g_NpcText[ arrayId], -1);
		--npc move to target
		SetPatrolId( sceneId, id, patrolId);
    elseif arrayId == 6 then
        SetFubenData_Param(sceneId, x700013_CSP_ARRAYID,           arrayId             );
        SetFubenData_Param(sceneId, x700013_CSP_COUNT,             8                   );
	    SetFubenData_Param(sceneId, x700013_CSP_TOTALCOUNT,        0                   );
	    SetFubenData_Param(sceneId, x700013_CSP_TIME_COUNT,        0                   );
		SetFubenData_Param(sceneId, x700013_CSP_GROUP,        		0                   );
        SetFubenData_Param(sceneId, x700013_CSP_TIME_DOWN,         x700013_g_Timer6    );
        SetFubenData_Param(sceneId, x700013_CSP_TIME_BACKUP,       x700013_g_Timer6    );
        SetFubenData_Param(sceneId, x700013_CSP_TIME_BISHEN,       x700013_g_Timer6_r  );
        SetFubenData_Param(sceneId, x700013_CSP_COUNTDOWN,         x700013_g_CountDown );
		SetFubenData_Param(sceneId, x700013_CSP_MONSTER_COUNT,     24                  );--总数24
		--npc talk
		local id = GetFubenData_Param( sceneId, x700013_CSP_NPCID);
		NpcTalk( sceneId, id, x700013_g_NpcText[ arrayId], -1);
		--npc move to target
		SetPatrolId( sceneId, id, patrolId);

	elseif arrayId == 8 then
        SetFubenData_Param(sceneId, x700013_CSP_ARRAYID,           arrayId             );
        SetFubenData_Param(sceneId, x700013_CSP_COUNT,             1                   );
	    SetFubenData_Param(sceneId, x700013_CSP_TOTALCOUNT,        0                   );
	    SetFubenData_Param(sceneId, x700013_CSP_TIME_COUNT,        0                   );
		SetFubenData_Param(sceneId, x700013_CSP_GROUP,        		0                   );
        SetFubenData_Param(sceneId, x700013_CSP_TIME_DOWN,         0                   );
        SetFubenData_Param(sceneId, x700013_CSP_TIME_BACKUP,       0                   );
        SetFubenData_Param(sceneId, x700013_CSP_TIME_BISHEN,       0                   );
        SetFubenData_Param(sceneId, x700013_CSP_COUNTDOWN,         x700013_g_CountDown );
		SetFubenData_Param(sceneId, x700013_CSP_MONSTER_COUNT,     1                   );--总数24
		--npc talk
		local id = GetFubenData_Param( sceneId, x700013_CSP_NPCID);
		NpcTalk( sceneId, id, x700013_g_NpcText[ arrayId], -1);
		--npc move to target
		SetPatrolId( sceneId, id, 7);
	elseif arrayId == 9 then
        SetFubenData_Param(sceneId, x700013_CSP_ARRAYID,           arrayId             );
        SetFubenData_Param(sceneId, x700013_CSP_COUNT,             6                   );
	    SetFubenData_Param(sceneId, x700013_CSP_TOTALCOUNT,        0                   );
	    SetFubenData_Param(sceneId, x700013_CSP_TIME_COUNT,        0                   );
		SetFubenData_Param(sceneId, x700013_CSP_GROUP,        		0                   );
        SetFubenData_Param(sceneId, x700013_CSP_TIME_DOWN,         x700013_g_Timer7	);
        SetFubenData_Param(sceneId, x700013_CSP_TIME_BACKUP,       x700013_g_Timer7	);
        SetFubenData_Param(sceneId, x700013_CSP_TIME_BISHEN,       x700013_g_Timer7_r	);
        SetFubenData_Param(sceneId, x700013_CSP_COUNTDOWN,         0					);
		SetFubenData_Param(sceneId, x700013_CSP_MONSTER_COUNT,     6                   );--总数24	
	end
end


---------------------------------------------------------------------------------------------------
--添加怪物数据
---------------------------------------------------------------------------------------------------
function x700013_AddMonsterParam( sceneId )

    local arrayId = GetFubenData_Param(sceneId, x700013_CSP_ARRAYID);					    -- 设置离开倒计时次数
    local nCount  = GetFubenData_Param(sceneId, x700013_CSP_COUNT);                        -- 一次创建数量
    local nHaveCount = GetFubenData_Param(sceneId, x700013_CSP_TOTALCOUNT);	--显示刷怪倒计时
	local createCountdown = GetFubenData_Param(sceneId, x700013_CSP_COUNTDOWN);
	local group = GetFubenData_Param(sceneId, x700013_CSP_GROUP)
	if createCountdown > 0 then
		local countTime = createCountdown * 5
		local str = countTime.."秒后出现新的敌人！"
		ShowTips( sceneId, str);
		SetFubenData_Param( sceneId, x700013_CSP_COUNTDOWN, createCountdown - 1);
		return
	end

    --判断是否已经到创建怪物的间隔
    local nTimeDown = GetFubenData_Param(sceneId, x700013_CSP_TIME_DOWN ) - 1
    -- 如果当前刷怪点已经创建了至少一只怪才走刷怪批次之间的倒计时，第一次刷怪前不用倒计时
    if nTimeDown > 0 and nHaveCount > 0 then
        SetFubenData_Param(sceneId, x700013_CSP_TIME_DOWN, nTimeDown )
        return
    else
        local nTimeBack = GetFubenData_Param(sceneId, x700013_CSP_TIME_BACKUP )
        SetFubenData_Param(sceneId, x700013_CSP_TIME_DOWN, nTimeBack )
    end

    local nNeedCreate = GetFubenData_Param(sceneId, x700013_CSP_MONSTER_COUNT)


    --判断创建怪物的总数
    if nHaveCount < nNeedCreate then

        for i = 0,nCount-1 do

            local nTotalCount = GetFubenData_Param( sceneId, x700013_CSP_TOTALCOUNT )

            local pos = x700013_CSP_START + nTotalCount*3

            local objId,nShengWang = x700013_CreateMonster( sceneId,arrayId, group )
            if objId ~= -1 then
                local nBianShen = GetFubenData_Param(sceneId, x700013_CSP_TIME_BISHEN )

                SetFubenData_Param(sceneId, pos + 1, objId ) --设置怪物
                SetFubenData_Param(sceneId, pos + 2, 0     ) --0未变身,1变身,2死亡
                SetFubenData_Param(sceneId, pos + 3, nBianShen    ) --设置变身时间

                SetFubenData_Param(sceneId, x700013_CSP_TOTALCOUNT, nTotalCount + 1 );
            end
        end
    end
	
	SetFubenData_Param(sceneId, x700013_CSP_GROUP, group+1)


    -- nHaveCount = GetFubenData_Param(sceneId, x700013_CSP_TOTALCOUNT);
    -- local msg = "第"..(arrayId + 1).."拨怪创建,已创建："..nHaveCount.." 总数："..nNeedCreate
    -- ShowTips(sceneId,msg)
end

--
function x700013_BosnusMonsterLogic( sceneId )
	--刷奖励怪
	local TotalBian = GetFubenData_Param( sceneId, x700013_CSP_TOTALBIAN )
	local TotalDisapear = GetFubenData_Param( sceneId, x700013_CSP_TOTALDISAPEAR )
	--print( "TotalBian="..TotalBian.."  , TotalDisapear="..TotalDisapear )
	if TotalBian+TotalDisapear == 0 then
		local str = "尽快消灭心魔，虚空南部即将发生扭曲！"
		ShowTips( sceneId, str)
		x700013_SetMonsterParam(sceneId,9)
		SetFubenData_Param(sceneId,x700013_CSP_BONUSLOGIC,0)
	end	
end

--
function x700013_FinalBossLogic( sceneId)
	--显示刷怪倒计时
	local createCountdown = GetFubenData_Param(sceneId, x700013_CSP_COUNTDOWN);
	--print("x700013_FinalBossLogic : createCountdown="..createCountdown)
	if createCountdown > 0 then
		local countTime = createCountdown * 5
		local str = countTime.."秒后，将是最严峻的考验！"
		ShowTips( sceneId, str);
		SetFubenData_Param( sceneId, x700013_CSP_COUNTDOWN, createCountdown - 1);
		return
	end
	
	createCountdown = GetFubenData_Param(sceneId, x700013_CSP_COUNTDOWN);
	if createCountdown == 0 then
		SetFubenData_Param( sceneId, x700013_CSP_COUNTDOWN, -1);
		--delete npc
		local id = GetFubenData_Param( sceneId, x700013_CSP_NPCID);
		DeleteMonster( sceneId, id);
		--create boss
		x700013_CreateBoss( sceneId);

		SetFubenData_Param( sceneId, x700013_CSP_B_BIANSHEN, 1);
		
		SetFubenData_Param(sceneId,x700013_CSP_BOSSLOGIC,0)
		SetFubenData_Param(sceneId,x700013_CSP_BONUSLOGIC,1)
	end
end

function ShowTips( sceneId,msg )

    if msg == nil then
        return
    end

    local humancount = GetFuben_PlayerCount(sceneId);
    for i = 0, humancount - 1 do

        local humanId = GetFuben_PlayerObjId(sceneId, i);	--取得当前场景里人的objId

        BeginQuestEvent(sceneId);
            AddQuestText(sceneId, msg);
        EndQuestEvent();
        DispatchQuestTips(sceneId, humanId);

    end
end



---------------------------------------------------------------------------------------------------
--更新怪物数据
---------------------------------------------------------------------------------------------------
function x700013_UpdateMonsterParam( sceneId )

    --local monstercount = GetFubenData_Param( sceneId,x700013_CSP_MONSTERCONVCOUNT )
    if GetFubenData_Param(sceneId,x700013_CSP_BOSSLOGIC)==1 then
		x700013_FinalBossLogic( sceneId);
        return
    end

	if GetFubenData_Param(sceneId,x700013_CSP_BONUSLOGIC)==1 then
		x700013_BosnusMonsterLogic(sceneId)
		return
	end

    local arrayId = GetFubenData_Param(sceneId, x700013_CSP_ARRAYID);					    -- 设置离开倒计时次数
    local nTotalCount = GetFubenData_Param( sceneId, x700013_CSP_TOTALCOUNT )             -- 取得已创建怪物数量
    local nNeedCreate = GetFubenData_Param(sceneId, x700013_CSP_MONSTER_COUNT)
	local nKill = 0
	
    for i =0, nTotalCount - 1 do

        local pos = x700013_CSP_START  + i * 3

		--怪物id
        local objId = GetFubenData_Param( sceneId,pos + 1 )
		--怪物状态：0未变身,1变身,2死亡
        local state = GetFubenData_Param( sceneId,pos + 2 )
		--变身计数器
        local tme   = GetFubenData_Param( sceneId,pos + 3 )

        if tme > 0 then
            tme = tme - 1
        end
        SetFubenData_Param( sceneId,pos + 3, tme )

		--提示1
		if tme==6 and state==0 then
			if arrayId==2 or arrayId==5 then
				ShowTips(sceneId,"30秒后敌人将逃离虚空，你也会一无所获！")
			end
		end		
		
		--提示2
		if tme==4 and state==0 then
			if arrayId==2 or arrayId==5 then
				ShowTips(sceneId,"20秒后敌人将逃离虚空，你也会一无所获！")
			end
		end
		
		--提示3
		if tme==2 and state==0 then
			if arrayId==2 or arrayId==5 then
				ShowTips(sceneId,"10秒后敌人将逃离虚空，你也会一无所获！")
			end			
		end		
		
        --只有状态为没变身的才执行变身处理
        if tme == 0 and state == 0  then
			--第2和5刷怪点创建的是Boss，不变身
            if arrayId ~= 2 and arrayId ~= 5 and arrayId~=9 then
				--到时间删除Boss怪物
                local OldObjId = GetFubenData_Param( sceneId,pos + 1)

				if OldObjId>0 then
				
					DeleteMonster( sceneId,OldObjId)  --普通怪物变身

					SetFubenData_Param( sceneId, x700013_CSP_B_BIANSHEN, 1);

					local x,z = GetMonsterPosition( sceneId,OldObjId)
					
					local NewObjId = x700013_CreateMonster(sceneId,arrayId + 10,0,x,z )

					SetFubenData_Param( sceneId,pos + 1,  NewObjId )
					SetFubenData_Param( sceneId,pos + 2,  1 )   --设置为变身状态
					SetFubenData_Param( sceneId,pos + 3, -1 )   --时间为-1表示已经处理过变身
					
					local TotalBian = GetFubenData_Param( sceneId, x700013_CSP_TOTALBIAN ) + 1
					SetFubenData_Param( sceneId, x700013_CSP_TOTALBIAN, TotalBian )	
				end

            else  --如果是两个boss
                local OldObjId = GetFubenData_Param( sceneId,pos + 1)
                DeleteMonster( sceneId,OldObjId)  --删除两个怪物

				SetFubenData_Param( sceneId, x700013_CSP_B_BIANSHEN, 1);

                SetFubenData_Param( sceneId,pos + 3, -1 )   --时间为-1表示已经处理过变身	

				local TotalDisapear = GetFubenData_Param( sceneId, x700013_CSP_TOTALDISAPEAR ) + 1
				SetFubenData_Param( sceneId, x700013_CSP_TOTALDISAPEAR, TotalDisapear )	
            end

            local nTimeCount = GetFubenData_Param(sceneId, x700013_CSP_TIME_COUNT)  + 1
            SetFubenData_Param(sceneId, x700013_CSP_TIME_COUNT, nTimeCount)

            local nRefCount = GetFubenData_Param( sceneId,x700013_CSP_MONSTERCONVCOUNT ) + 1
            SetFubenData_Param( sceneId,x700013_CSP_MONSTERCONVCOUNT,nRefCount )		

            -- local msg = "第"..arrayId.."拨怪变身,当前："..nTimeCount.." 总数："..nNeedCreate
            -- ShowTips(sceneId,msg)

            --处理变身总数
        --elseif tme == 0 and state == 2 then
			--如果怪物被杀，立即更新变身计数，不走变身计数器逻辑。这样如果怪物被杀死后下一刷怪点可以立即开始。
		elseif state == 2 then
			--检查是否已经做变身标记，如果做过就跳过
			nKill = nKill + 1
			local isConvert = GetFubenData_Param( sceneId, pos + 3);
			if isConvert ~= -1 then
	            SetFubenData_Param( sceneId, pos + 3, -1 )   --时间为-1表示已经处理过变身

	            local nTimeCount = GetFubenData_Param(sceneId, x700013_CSP_TIME_COUNT)  + 1
	            SetFubenData_Param(sceneId, x700013_CSP_TIME_COUNT, nTimeCount)

	            local nRefCount = GetFubenData_Param( sceneId,x700013_CSP_MONSTERCONVCOUNT ) + 1
	            SetFubenData_Param( sceneId,x700013_CSP_MONSTERCONVCOUNT,nRefCount )

	            -- local msg = "第"..arrayId.."拨怪变身,当前："..nTimeCount.." 总数："..nNeedCreate
	            -- ShowTips(sceneId,msg)
			end
        end
    end

    x700013_AddMonsterParam( sceneId )

    local nTimeCount = GetFubenData_Param(sceneId, x700013_CSP_TIME_COUNT)		--已变身总数
    if nTimeCount>=nNeedCreate or nKill>=nNeedCreate then
        x700013_SetMonsterParam( sceneId,arrayId + 1 )
    end
end

---------------------------------------------------------------------------------------------------
--刷新怪物数据
---------------------------------------------------------------------------------------------------
function x700013_RefreshMonsterParam( sceneId, objId )

    local arrayId = GetFubenData_Param(sceneId, x700013_CSP_ARRAYID);					    -- 设置离开倒计时次数
    local nTotalCount = GetFubenData_Param( sceneId, x700013_CSP_TOTALCOUNT )              -- 取得怪物数量

    for i =0, nTotalCount - 1 do

        local pos = x700013_CSP_START  + i * 3
        local objId_bak = GetFubenData_Param( sceneId,pos + 1 )

        --只有状态为没变身的才执行变身处理
        if objId_bak == objId  then

            SetFubenData_Param( sceneId,pos + 2,  2 )   --设置为变身状态
            return
        end
    end
end

---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700013_CreateMonster(sceneId,index,group,nx,nz)

    local fubenlevel = GetFubenData_Param(sceneId, x700013_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700013_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700013_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700013_g_ScriptId )
	
	for i = 0,nDataCount-1 do

		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700013_g_ScriptId,nIndexFrom,i)
		if idScript == x700013_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel and flag1==group and nFubenType == flag3 then

        
            if flag == index then

 --               for j=0,item.count -1 do

                    local rx = random(-r,r)
                    local x = x1 + rx
                    local rz = random(-r,r)
                    local z = z1 + rz

                    if nx ~= nil and nz ~= nil then
                        x = nx
                        z = nz
                    end
                    local objId = 0
					
					if title~="" then
						objId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700013_g_ScriptId, -1, 21, -1, facedir, "", title)
					else
						objId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700013_g_ScriptId, -1, 21, -1, facedir)
					
					end


                    if flag < 10 then
                        local monstercount = GetFubenData_Param( sceneId,x700013_CSP_MONSTERCOUNT) + 1
                        SetFubenData_Param( sceneId,x700013_CSP_MONSTERCOUNT,monstercount)
                    end
                    return objId,flag3
--                end

            end
        end
	end

    return -1,0

end

function x700013_GetBonus(nDataID)


	local nIndexFrom = GetFubenDataPosByScriptID(x700013_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700013_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700013_g_ScriptId,nIndexFrom,i)
		if idScript == x700013_g_ScriptId and monsterFlag == 2 then
			if type==nDataID then
				return flag3
			end
		end
	end
	
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700013_g_ScriptId,nIndexFrom,i)
		if idScript == x700013_g_ScriptId and monsterFlag == 1 then
			if type==nDataID then
				return flag3
			end
		end
	end
	
	return 0
end

function x700013_OnDie(sceneId, selfId, killerId)

	local xianjinboss = GetFubenData_Param(sceneId, x700013_CSP_XIANJINBOSS)
	if xianjinboss == selfId then
		local humancount = GetFuben_PlayerCount(sceneId);

	--通知玩家
		for i = 0, humancount - 1 do
			local humanId = GetFuben_PlayerObjId(sceneId, i);
			if GetLevel(sceneId, humanId) >= 80 then
				local refixInhExp = AddInherenceExp(sceneId, humanId, 600)
				local str = format("你获得了%d点天赋值", refixInhExp)
				BeginQuestEvent(sceneId);
					AddQuestText(sceneId,str);
				EndQuestEvent();
				DispatchQuestTips(sceneId, humanId)
			end
		end
	end
	
	
	local nDieCount = GetFubenData_Param(sceneId, x700013_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700013_CSP_KILLCOUNT, nDieCount+1);
	SetFubenData_Param(sceneId, x700013_CSP_NKILLMONSTER, nDieCount+1);
	local bossid = GetFubenData_Param(sceneId, x700013_CSP_BOSSID)
	local arrayId = GetFubenData_Param(sceneId, x700013_CSP_ARRAYID);
	local nShengWang = 0
	
	nDieCount = nDieCount+1;
	
	local nTotalCount = GetFubenData_Param( sceneId, x700013_CSP_TOTALCOUNT )
	for i =0, nTotalCount - 1 do
		local pos = x700013_CSP_START  + i * 3
		local objid = GetFubenData_Param( sceneId,pos + 1 )
		if objid==selfId then
			SetFubenData_Param( sceneId,pos + 2,  2 )   --设置为死亡状态
		end
	end

	-- kill enough，创建BOSS
	local TotalDisapear = GetFubenData_Param( sceneId, x700013_CSP_TOTALDISAPEAR )
	if x700013_g_NeedKillMonster == nDieCount+TotalDisapear then
		x700013_SetMonsterParam( sceneId, 8)
		SetFubenData_Param(sceneId,x700013_CSP_BOSSLOGIC,1)
	end
	
	-- BOSS也被杀死了
	if bossid==selfId then
		x700013_OnAllMonsterDead( sceneId) 

		--//--------------------------- 世界喊话 Start--------------------
--			-- final boss
--			local nowTickCount = GetFubenData_Param(sceneId, x700013_CSP_TICKCOUNT)
--
--			local nowTime = x700013_g_TickTime* nowTickCount;
--
--			local nMinute = floor(nowTime/60)
--			local nSec = mod(nowTime,60)
--
--				
--			local strPlayerName = GetName(sceneId, killerId)     -- 杀死怪物的玩家名字
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
--			local strKillTime = format("%d分%d秒", nMinute, nSec) -- 杀死关务的事件
--
--			
--			
--			LuaAllScenceM2Wrold (sceneId,"#R哇塞，人品啊！#G"..strPlayerName.."#R和他的队友仅用了#G"..strKillTime.."#R完成了虚空境的考验！", 0, 1)
			
			
			
			--//--------------------------- 世界喊话 end----------------------
	end

	local nFubenType = GetFubenData_Param(sceneId, x700013_CSP_FUBEN_TYPE)
	if nFubenType == 0 then
		local nDataID = GetMonsterDataID(sceneId,selfId)
		nShengWang = x700013_GetBonus(nDataID)
	
		local humancount = GetFuben_PlayerCount(sceneId);
		for	i = 0, humancount - 1 do
			local humanId = GetFuben_PlayerObjId(sceneId, i);
			--local str = format("%d", nDieCount);
			--BeginQuestEvent(sceneId);
			--AddQuestText(sceneId, str);
			--EndQuestEvent(sceneId);
			--DispatchQuestTips(sceneId, humanId);
			
			-- 给每个人都加声望
			if nShengWang>0 then
				local nOldValue = GetShengWang( sceneId, humanId )
				SetShengWang( sceneId, humanId, nOldValue+nShengWang )
				Msg2Player(sceneId,humanId,"获得声望"..nShengWang,8,2)
			end		
		end
	end
end

function x700013_ProcQuestObjectKilled(sceneId, selfId, objdataId ,objId, MissionId )
	--PrintStr("x700013_ProcQuestObjectKilled")
end

function x700013_OnAllMonsterDead( sceneId)
	x700013_CreateSubmitNpc( sceneId)
end

function x700013_CreateSubmitNpc( sceneId)

	 if x700013_g_SubmitNPC.title~="" then
		CreateMonster(sceneId, x700013_g_SubmitNPC.type, x700013_g_SubmitNPC.x, x700013_g_SubmitNPC.z, 3, 0, -1, x700013_g_SubmitNPC.guid, -1, -1, x700013_g_SubmitNPC.facedir, "",x700013_g_SubmitNPC.title )
	 else
		CreateMonster(sceneId, x700013_g_SubmitNPC.type, x700013_g_SubmitNPC.x, x700013_g_SubmitNPC.z, 3, 0, -1, x700013_g_SubmitNPC.guid, -1, -1, x700013_g_SubmitNPC.facedir)
	 end

	 --// add for 现金副本
	 x700013_CreateXianJinBoss(sceneId)
	 --// add end

	 CallScriptFunction( 701113, "OnSceneBossDie", sceneId, 1)

	 local bBianShen = GetFubenData_Param( sceneId, x700013_CSP_B_BIANSHEN);

	 if bBianShen<=0 then
		CallScriptFunction( 701114, "OnSceneBossDie", sceneId, 1)
	 end
end

----------------------------------------------------------
--创建现金boss
----------------------------------------------------------

function x700013_CreateXianJinBoss(sceneId)
	local nFubenType = GetFubenData_Param(sceneId, x700013_CSP_FUBEN_TYPE)
	if nFubenType ~= 0 then
		return
	end
	
	local nFubenMode = GetFubenData_Param(sceneId, x700013_CSP_FUBEN_MODE)

	if nFubenMode == 0 then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700013_CSP_FUBENLEVEL ) ;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700013_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700013_g_ScriptId )

	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700013_g_ScriptId,nIndexFrom,i)
		if idScript == x700013_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700013_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700013_g_ScriptId, -1, 21,-1,facedir)
			end
			SetFubenData_Param(sceneId, x700013_CSP_XIANJINBOSS, nRet )
		end
	end

	x700013_ShowTipsToAll(sceneId, "翻番宝箱出现！")
end


