---------------------------------------------------
-- File: 700002_fuben_dawushi_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700002_CSP_FUBENTYPE				= 	0
x700002_CSP_SCRIPTID				=	1
x700002_CSP_TICKCOUNT				= 	2
x700002_CSP_FROMSCENEID				= 	3
x700002_CSP_ISCLOSING				= 	4
x700002_CSP_LEAVECOUNTDOWN			= 	5
x700002_CSP_TEAMID					=	6
x700002_CSP_BACKSCENEX       		=   7
x700002_CSP_BACKSCENEZ      		=   8
x700002_CSP_FUBENLEVEL			=	9

x700002_CSP_KILLCOUNT				=	20
x700002_CSP_FUBEN_SCENE_ID			=	21

x700002_CSP_GAME_STEP				=	22
x700002_CSP_TEMP_STEP				=	23
x700002_CSP_TEMP_TICKCOUNT			=	24
x700002_CSP_B_BAOMU_ING				=	25
x700002_CSP_B_FUBEN_STATUS			=	26
x700002_CSP_STARTNPC_ID				=	27
x700002_CSP_LAOBAN_ID				=	28
x700002_CSP_STEP_NPC_ID				=	29

x700002_CSP_GUANYU_ID				=	30
x700002_CSP_LUSU_ID					=	31
x700002_CSP_STEP_PARAM				=	32
x700002_CSP_MYS_FULL_HP				=	33
x700002_CSP_MYS_B_START_CALL		=	34
x700002_CSP_FINAL_KILLER_ID			=	35

x700002_CSP_GZ_COUNT				=	40
x700002_CSP_GZ_START				=	41   -- 最多20个观众
x700002_CSP_RUN_MONSTER_COUNT		=	60
x700002_CSP_RUN_MONSTER_START		=	61	-- 最多10个逃跑匈奴兵
x700002_CSP_STEP_BOSS_COUNT			=	70
x700002_CSP_STEP_BOSS_START			=	71
x700002_CSP_MONSTER_COUNT			=	80
x700002_CSP_MONSTER_START			=	81


x700002_CSP_HUMAN_COUNT				=	240
x700002_CSP_OBJID_START				=	241
x700002_CSP_GUID_START              =   248



------------------------Scene System Setting -----------------------------------

x700002_g_ScriptId 					= 700002
------------------------- special for fuben----------------------
x700002_g_StartGame					=	0
x700002_g_BaoMuX	=63
x700002_g_BaoMuZ	=52
x700002_g_BaoxinX	=37	
x700002_g_BaoxinZ	=56


x700002_g_BaomuNpcTalkText			= {
									{"第一幕",
									"西厢记"
									},

									{"第二幕",
                                    "单刀会"
									},

									{"第三幕",
									"窦娥冤"
									},

									{"第四幕",
                                    "汉宫秋"
									}

								  }

x700002_g_StepNpcTalkText			= {
										
									{"过雨樱桃血满枝，弄色的奇花红间紫，垂柳已成丝。",
                                    "恶人孙飞虎，欺男霸女实祸害，此贼不除，有情亦难成眷属。"
									 
									},

									{"原来汝等早有埋伏，快快保护君侯！",
									
									},

									{"没来由犯王法，不提防遭刑宪，叫声屈动地惊天！顷刻间游魂先赴森罗殿，怎不将天地也生埋怨。",
                                    "可怜我窦娥今日蒙冤九泉下，定不能饶了那可恨的张驴儿！！"

									},

									{"啊呀~~~！我只道是忠臣皆有用，高枕已无忧，却不想如今只凭佳人平定天下！！"
									}
								}

x700002_g_EndStepNpcTalkText	= {
										
									{"愿天下有情人终能成眷属！",
									 
									},

									{"我乃汉寿亭侯，匹夫安敢如此！",
									 
									},

									{"昏庸知县，十恶的张驴儿，死不足惜。",
									 
									},

									{"陛下~，都是那可恨的毛延寿害得你我天各一方！",
									 

									}
								}


x700002_g_SubmitNPC                 =   { type =25019,guid= 150519,x = 63, z=50,facedir=0, title="" }
x700002_g_LeaveNPC					=   { type =25019,guid= 150519,x = 63, z=50,facedir=0, title="" }	




--Npc类型
x700002_g_NpcCreate				=	{                                          
                                            {name ="报幕Npc",   type= 25052, guid= -1    , x=45, z=29, r=0,  ai=7, aiscript=0,   facedir = 0, title = "", flag=0},
											{name ="老板",		type= 25063, guid= 150518, x=64, z=65, r=0,  ai=7, aiscript=0,   facedir = 180, title = "", flag=1},
									}




x700002_g_GzCreate				=	{

									 }
                                        



-----------------------------------------------------
--Core Logic
--------------------------------------------------
function x700002_StartBaoMu(sceneId)

	local nFubenStatus = GetFubenData_Param(sceneId, x700002_CSP_B_FUBEN_STATUS)  
	if nFubenStatus~= 0 then
		return
	end

	local nNpcId = GetFubenData_Param(sceneId, x700002_CSP_STARTNPC_ID)

	SetFubenData_Param(sceneId, x700002_CSP_B_BAOMU_ING,1)

	SetPatrolId(sceneId, nNpcId, 0)

	
	SetFubenData_Param(sceneId, x700002_CSP_TEMP_STEP,0)
	SetFubenData_Param(sceneId, x700002_CSP_TEMP_TICKCOUNT,0)

	local nCurrentStep = GetFubenData_Param(sceneId, x700002_CSP_GAME_STEP)
	x700002_ShowTipsToAll(sceneId, format("第%d幕报幕开始",nCurrentStep+1))

end


function x700002_BaoMu(sceneId)

	local bBaomu = GetFubenData_Param(sceneId, x700002_CSP_B_BAOMU_ING)

	if bBaomu<=0 then
		return
	end

	local nNpcId = GetFubenData_Param(sceneId, x700002_CSP_STARTNPC_ID)

	local nCurrentStep = GetFubenData_Param(sceneId, x700002_CSP_GAME_STEP)
			
	NpcTalk(sceneId, nNpcId, x700002_g_BaomuNpcTalkText[nCurrentStep+1][1],  -1)
	

	SetFubenData_Param(sceneId, x700002_CSP_TEMP_STEP,1)
	SetFubenData_Param(sceneId, x700002_CSP_TEMP_TICKCOUNT,1)

end

function x700002_LeaveBaoMu(sceneId)
	local bBaomu = GetFubenData_Param(sceneId, x700002_CSP_B_BAOMU_ING)

	if bBaomu<=0 then
		return
	end

	local nNpcId = GetFubenData_Param(sceneId, x700002_CSP_STARTNPC_ID)

	SetPatrolId(sceneId, nNpcId, 1)

	SetFubenData_Param(sceneId, x700002_CSP_TEMP_STEP,2)
	SetFubenData_Param(sceneId, x700002_CSP_TEMP_TICKCOUNT,0)

end



function x700002_StartScene(sceneId)

	local bBaomu = GetFubenData_Param(sceneId, x700002_CSP_B_BAOMU_ING)

	if bBaomu<=0 then
		return
	end

	SetFubenData_Param(sceneId, x700002_CSP_TEMP_STEP,3)
	SetFubenData_Param(sceneId, x700002_CSP_TEMP_TICKCOUNT,0)

	SetFubenData_Param(sceneId, x700002_CSP_B_BAOMU_ING,0)
	
	local nCurrentGameStep = GetFubenData_Param(sceneId, x700002_CSP_GAME_STEP)+1
	SetFubenData_Param(sceneId, x700002_CSP_GAME_STEP, nCurrentGameStep)
	SetFubenData_Param(sceneId, x700002_CSP_STEP_PARAM, 0)
	

	
	

	
	x700002_CreateStepNpc(sceneId,nCurrentGameStep-1)	-- 介绍的Npc
	
		

	
	
end

function x700002_OnTalkOver(sceneId)
	local nCurrentGameStep = GetFubenData_Param(sceneId, x700002_CSP_GAME_STEP)
	SetFubenData_Param(sceneId, x700002_CSP_TEMP_STEP,4)
	SetFubenData_Param(sceneId, x700002_CSP_TEMP_TICKCOUNT,0)

	if nCurrentGameStep==1 then
		x700002_CreateMonster(sceneId,nCurrentGameStep-1)
	elseif  nCurrentGameStep==2 then
		local nStepNpcId = GetFubenData_Param(sceneId, x700002_CSP_STEP_NPC_ID)
		SetPatrolId(sceneId, nStepNpcId, 2)
		x700002_CreateBoss(sceneId,nCurrentGameStep-1)
		x700002_CreateStep2Npc(sceneId)
	elseif  nCurrentGameStep==3 then
		x700002_CreateMonster(sceneId,nCurrentGameStep-1)
		x700002_CreateBoss(sceneId,nCurrentGameStep-1)
	elseif  nCurrentGameStep==4 then
		local nStepNpcId = GetFubenData_Param(sceneId, x700002_CSP_STEP_NPC_ID)
		x700002_DeleteMonster( sceneId,nStepNpcId )
		SetFubenData_Param(sceneId, x700002_CSP_STEP_NPC_ID,-1)

		x700002_CreateMonster(sceneId,nCurrentGameStep-1)
		x700002_CreateBoss(sceneId,nCurrentGameStep-1)
	end

	
end

function x700002_OnStepEndOver(sceneId)
	local nCurrentGameStep = GetFubenData_Param(sceneId, x700002_CSP_GAME_STEP)
	local nStepNpcId = GetFubenData_Param(sceneId, x700002_CSP_STEP_NPC_ID)

	x700002_DeleteMonster( sceneId,nStepNpcId )

	x700002_ShowTipsToAll(sceneId, format("第%d幕结束",nCurrentGameStep))

	if nCurrentGameStep==4 then
		x700002_OnCompleteAllGame(sceneId)
	else
		x700002_StartBaoMu(sceneId)
	end
	
end


function x700002_OnAllBossOver(sceneId)
	local nCurrentStep = GetFubenData_Param(sceneId, x700002_CSP_GAME_STEP)

	if nCurrentStep==1 then
		x700002_OnCompleteOneStep(sceneId)
	elseif nCurrentStep==2 then
		SetFubenData_Param(sceneId, x700002_CSP_STEP_PARAM, 1)
	elseif nCurrentStep==3 then
		local nParam = GetFubenData_Param(sceneId, x700002_CSP_STEP_PARAM)+1
		SetFubenData_Param(sceneId, x700002_CSP_STEP_PARAM, nParam)
		
		if nParam==2 then  -- 张驴儿和打手都死了
			x700002_ShowTipsToAll(sceneId, "张驴儿和打手都死了， 贪官出现")
			x700002_CreateMonster(sceneId,21)
			x700002_CreateBoss(sceneId,21)
		elseif nParam==4 then  -- 贪官和衙役也死了 
			x700002_ShowTipsToAll(sceneId, "为窦娥报了仇")
			x700002_OnCompleteOneStep(sceneId)
		end
	elseif nCurrentStep==4 then
		local nParam = GetFubenData_Param(sceneId, x700002_CSP_STEP_PARAM)+1
		SetFubenData_Param(sceneId, x700002_CSP_STEP_PARAM, nParam)
		
		local nRunMonsterCount = GetFubenData_Param(sceneId, x700002_CSP_RUN_MONSTER_COUNT)
		if nParam==3 then
			if nRunMonsterCount==0 then
				x700002_ShowTipsToAll(sceneId, "保护好了昭君")
				x700002_OnCompleteOneStep(sceneId)
			end
		elseif nParam==1 then
			local nBossCount = GetFubenData_Param(sceneId, x700002_CSP_STEP_BOSS_COUNT)
			if nBossCount==0 then
				local bMysCall = GetFubenData_Param(sceneId, x700002_CSP_MYS_B_START_CALL )
				if bMysCall==0 then
					--x700002_ShowTipsToAll(sceneId, "you are so crazy...!")
					local nMonsterCount = GetFubenData_Param(sceneId, x700002_CSP_MONSTER_COUNT)

					for i=0, nMonsterCount-1 do
						local nMonsterId = GetFubenData_Param(sceneId, x700002_CSP_MONSTER_START+i)

						if nMonsterId>=0 then
							x700002_DeleteMonster( sceneId,nMonsterId )
							SetFubenData_Param(sceneId, x700002_CSP_MONSTER_START+i,-1)
						end
					end

					x700002_OnCompleteOneStep(sceneId)
				end
			end
		end
	end
end

function x700002_OnAllMonsterOver(sceneId)
	local nCurrentStep = GetFubenData_Param(sceneId, x700002_CSP_GAME_STEP)

	
	if nCurrentStep==1 then
		x700002_ShowTipsToAll(sceneId, "杀死所有小怪，孙飞虎出现")
		x700002_CreateBoss(sceneId,nCurrentStep-1)
	elseif nCurrentStep==2 then
		local nParam = GetFubenData_Param(sceneId, x700002_CSP_STEP_PARAM)

		if nParam==1 then
			SetFubenData_Param(sceneId, x700002_CSP_STEP_PARAM, 2)
			x700002_OnCompleteOneStep(sceneId)
		end
	elseif nCurrentStep==3 then
		local nParam = GetFubenData_Param(sceneId, x700002_CSP_STEP_PARAM)+1
		SetFubenData_Param(sceneId, x700002_CSP_STEP_PARAM, nParam) 

		if nParam==2 then  -- 张驴儿和打手都死了
			x700002_ShowTipsToAll(sceneId, "张驴儿和打手都死了， 贪官出现")
			x700002_CreateMonster(sceneId,21)
			x700002_CreateBoss(sceneId,21)
		elseif nParam==4 then  -- 贪官和衙役也死了 
			x700002_ShowTipsToAll(sceneId, "为窦娥报了仇")
			x700002_OnCompleteOneStep(sceneId)
		end
	elseif nCurrentStep==4 then
		local nParam = GetFubenData_Param(sceneId, x700002_CSP_STEP_PARAM)+1
		SetFubenData_Param(sceneId, x700002_CSP_STEP_PARAM, nParam)

		local nRunMonsterCount = GetFubenData_Param(sceneId, x700002_CSP_RUN_MONSTER_COUNT)
		if nParam==3 then
			if nRunMonsterCount==0 then
				x700002_ShowTipsToAll(sceneId, "保护好了昭君")
				x700002_OnCompleteOneStep(sceneId)
			end
		end
	end
end

function x700002_OnAllRunMonsterOver(sceneId)
	local nCurrentStep = GetFubenData_Param(sceneId, x700002_CSP_GAME_STEP)

	if nCurrentStep~=4 then
		return
	end

	
	local nParam = GetFubenData_Param(sceneId, x700002_CSP_STEP_PARAM)+1
	SetFubenData_Param(sceneId, x700002_CSP_STEP_PARAM, nParam)
	
	local nRunMonsterCount = GetFubenData_Param(sceneId, x700002_CSP_RUN_MONSTER_COUNT)
	if nParam==3 then
		if nRunMonsterCount==0 then
			x700002_ShowTipsToAll(sceneId, "保护好了昭君")
			x700002_OnCompleteOneStep(sceneId)
		end
	end

end


function x700002_OnCompleteAllGame(sceneId)
	x700002_OnFubenSuccess(sceneId)
end

function x700002_OnCompleteOneStep(sceneId)

	
	local nCurrentStep = GetFubenData_Param(sceneId, x700002_CSP_GAME_STEP)

	x700002_AllGzSay(sceneId, "好精彩啊!")
	x700002_LaobanSay(sceneId, "果然佳作")

	if nCurrentStep ==1 then
		

	elseif nCurrentStep ==2 then
		local nStepNpcId = GetFubenData_Param(sceneId, x700002_CSP_STEP_NPC_ID)
		local nGuanyuId = GetFubenData_Param(sceneId, x700002_CSP_GUANYU_ID)
		local nLusucId = GetFubenData_Param(sceneId, x700002_CSP_LUSU_ID)

		if nGuanyuId<0 then
			return
		end

		
		
		if nStepNpcId>=0 then
			x700002_DeleteMonster( sceneId,nStepNpcId )
		end
		x700002_DeleteMonster( sceneId,nLusucId )
		
		SetFubenData_Param(sceneId, x700002_CSP_STEP_NPC_ID,nGuanyuId)

		SetFubenData_Param(sceneId, x700002_CSP_GUANYU_ID,-1)
		SetFubenData_Param(sceneId, x700002_CSP_LUSU_ID,-1)

	elseif nCurrentStep ==3 then
	elseif nCurrentStep	==4 then
		x700002_CreateStepNpc(sceneId,31)
		SetFubenData_Param(sceneId, x700002_CSP_TEMP_STEP,5)
		SetFubenData_Param(sceneId, x700002_CSP_TEMP_TICKCOUNT,0)
		x700002_ShowTipsToAll(sceneId, format("出色地完成了第%d幕",nCurrentStep))

		
		return
	end

	SetFubenData_Param(sceneId, x700002_CSP_TEMP_STEP,5)
	SetFubenData_Param(sceneId, x700002_CSP_TEMP_TICKCOUNT,1)
	
	local nStepNpcId = GetFubenData_Param(sceneId, x700002_CSP_STEP_NPC_ID)
			
	NpcTalk(sceneId, nStepNpcId, x700002_g_EndStepNpcTalkText[nCurrentStep][1],  -1)

	x700002_ShowTipsToAll(sceneId, format("出色地完成了第%d幕",nCurrentStep))
	
end





function x700002_EnterTick(sceneId,nowTickCount)

	local nFubenStatus = GetFubenData_Param(sceneId, x700002_CSP_B_FUBEN_STATUS)  
	if nFubenStatus~= 0 then
		return
	end
	
	local bBaomu = GetFubenData_Param(sceneId, x700002_CSP_B_BAOMU_ING)

    local nNpcId = GetFubenData_Param(sceneId, x700002_CSP_STARTNPC_ID)

	
	
	
	

	if bBaomu<=0 then
		local nStatus = GetFubenData_Param(sceneId, x700002_CSP_TEMP_STEP) 
		local nCurrentStep = GetFubenData_Param(sceneId, x700002_CSP_GAME_STEP)

		
		if nStatus==3 then  -- 关卡Npc刚刚创建出来
			local nTickCount = GetFubenData_Param(sceneId, x700002_CSP_TEMP_TICKCOUNT)+1
			SetFubenData_Param(sceneId, x700002_CSP_TEMP_TICKCOUNT,nTickCount)

			
			local nTextCount = x700002_GetStepTextCount(sceneId,nCurrentStep)
			
			if nTickCount>nTextCount then
				x700002_OnTalkOver(sceneId)
			else
				local nStepNpcId = GetFubenData_Param(sceneId, x700002_CSP_STEP_NPC_ID)
				NpcTalk(sceneId, nStepNpcId, x700002_g_StepNpcTalkText[nCurrentStep][nTickCount],  -1)
			end
		elseif nStatus==5 then
			
			local nTickCount = GetFubenData_Param(sceneId, x700002_CSP_TEMP_TICKCOUNT)+1
			SetFubenData_Param(sceneId, x700002_CSP_TEMP_TICKCOUNT,nTickCount)
			
				
			local nTextCount = x700002_GetEndStepTextCount(sceneId,nCurrentStep)
			if nTickCount>nTextCount then
				
				x700002_OnStepEndOver(sceneId)
				
			else
				local nStepNpcId = GetFubenData_Param(sceneId, x700002_CSP_STEP_NPC_ID)
				NpcTalk(sceneId, nStepNpcId, x700002_g_EndStepNpcTalkText[nCurrentStep][nTickCount],  -1)
			end
			
		elseif	nStatus==4 then
			if nCurrentStep==4 then
				local nBossCount = GetFubenData_Param(sceneId, x700002_CSP_STEP_BOSS_COUNT)
				local nMysId = GetFubenData_Param(sceneId, x700002_CSP_STEP_BOSS_START)
				local bCalled = GetFubenData_Param(sceneId, x700002_CSP_MYS_B_START_CALL )	
				
				if nBossCount>0 then
					if bCalled<=0 then
						if nMysId>=0 then
							
							local nCurrentHp = GetHp( sceneId, nMysId )
							local nFullHp = GetFubenData_Param(sceneId, x700002_CSP_MYS_FULL_HP )
							
							if nCurrentHp< nFullHp then
								SetFubenData_Param(sceneId, x700002_CSP_MYS_B_START_CALL,1 )
								NpcTalk(sceneId, nMysId, "汉人反悔，赶快去报信！",  -1)
								x700002_CreateStep4RunMonster(sceneId)
							end
						end
					end
				end
						
			end


			if nCurrentStep==4 then
		
				local nRunMonsterCount = GetFubenData_Param(sceneId, x700002_CSP_RUN_MONSTER_COUNT)

				for i=0, nRunMonsterCount-1 do
					local nMonsterId = GetFubenData_Param(sceneId, x700002_CSP_RUN_MONSTER_START+i)
					
					if( IsObjValid(sceneId,nMonsterId) ~= 1 )then
						--增加debug日志
						WriteLog(1,format("goulanqutai getworldpos 1:count=%d,id=%d,index=%d,step=%d,nFubenStatus=%d",nRunMonsterCount,nMonsterId,i,nCurrentStep,nFubenStatus))
						return
					end
					

					local x,z =GetWorldPos(sceneId,nMonsterId)

					if x==x700002_g_BaoxinX and z==x700002_g_BaoxinZ then
						x700002_OnFubenFailed(sceneId,4)
						break;
					end
				end
			end
		end

		
	else
		local nBaomuTickCount = GetFubenData_Param(sceneId, x700002_CSP_TEMP_TICKCOUNT)+1
		SetFubenData_Param(sceneId, x700002_CSP_TEMP_TICKCOUNT,nBaomuTickCount)

		if( IsObjValid(sceneId,nNpcId) ~= 1 )then
			--增加debug日志
			WriteLog(1,format("goulanqutai getworldpos 2:id=%d,nFubenStatus=%d",nNpcId,nFubenStatus))
			return
		end	
		

		local x,z =GetWorldPos(sceneId,nNpcId)
		local nBaomuStatus = GetFubenData_Param(sceneId, x700002_CSP_TEMP_STEP)
		
		if nBaomuStatus==0 then
			if x==x700002_g_BaoMuX and z==x700002_g_BaoMuZ then  -- 还没有报幕
				x700002_BaoMu(sceneId)
				return
			end			
		elseif nBaomuStatus==1 then		-- 开始报幕了
			local nCurrentStep = GetFubenData_Param(sceneId, x700002_CSP_GAME_STEP)
			local nTextCount = x700002_GetNpcTextCount(sceneId,nCurrentStep+1)
			if nBaomuTickCount>nTextCount then
				x700002_LeaveBaoMu(sceneId)
			else
				NpcTalk(sceneId, nNpcId, x700002_g_BaomuNpcTalkText[nCurrentStep+1][nBaomuTickCount],  -1)
			end
		elseif nBaomuStatus==2 then		-- 开始离开了
			if nBaomuTickCount==1 then
				x700002_StartScene(sceneId)
			end
		else
			return
		end
		
	end
end
-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700002_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)

end

-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  当副本创建成功时， 开始刷怪和npc
--*********************************************************
-----------------------------------------------------------
function x700002_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  副本场景id
	x700002_CreateNpc( sceneId)
	x700002_CreateGz(sceneId)
	
	local weekIndex = GetWeekIndex()
	local nHumanCount = GetScenePlayerCount( sceneId)
	if nHumanCount > 0 then
	    for i = 0, nHumanCount do
	        local objId = GetScenePlayerObjId( sceneId,i)
	        if objId >= 0 then
	        	SetQuestData(sceneId, objId, MD_FUBEN_HUAPI_FLAG[1], MD_FUBEN_HUAPI_FLAG[2], MD_FUBEN_HUAPI_FLAG[3], 0)
	        end
	    end
	end
end

function x700002_GetNpcTextCount(sceneId,nIndex)

	local nTextList = x700002_g_BaomuNpcTalkText[nIndex]
	local nCount =0
	for i,item in nTextList do
		nCount = nCount+1
	end

	return nCount;
end


function x700002_GetStepTextCount(sceneId,nIndex)

	local nTextList = x700002_g_StepNpcTalkText[nIndex]
	local nCount =0
	for i,item in nTextList do
		nCount = nCount+1
	end

	return nCount;
end

function x700002_GetEndStepTextCount(sceneId,nIndex)
	local nTextList = x700002_g_EndStepNpcTalkText[nIndex]
	local nCount =0
	for i,item in nTextList do
		nCount = nCount+1
	end

	return nCount;
end



function x700002_CreateStepNpc(sceneId,index)
	

	local fubenlevel = GetFubenData_Param(sceneId, x700002_CSP_FUBENLEVEL ) ;
	local nIndexFrom = GetFubenDataPosByScriptID(x700002_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700002_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700002_g_ScriptId,nIndexFrom,i)
		if idScript == x700002_g_ScriptId and monsterFlag == 3 and levelmin <= fubenlevel and levelmax >= fubenlevel then
			if flag == index   then

				local nRet = 0
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700002_g_ScriptId,-1,camp,-1, facedir, "", title);
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700002_g_ScriptId,-1,camp,-1, facedir);
				
				end

				SetFubenData_Param(sceneId, x700002_CSP_STEP_NPC_ID, nRet)
			end
		end
        
    end

	
end

function x700002_CreateStep2Npc(sceneId)

	local nCurrentGameStep = GetFubenData_Param(sceneId, x700002_CSP_GAME_STEP)

	if nCurrentGameStep~= 2 then
		return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700002_CSP_FUBENLEVEL ) ;
	local nIndexFrom = GetFubenDataPosByScriptID(x700002_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700002_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700002_g_ScriptId,nIndexFrom,i)
		if idScript == x700002_g_ScriptId and monsterFlag == 4 and levelmin <= fubenlevel and levelmax >= fubenlevel then
			local nRet = 0
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700002_g_ScriptId,-1,camp,-1, facedir,  "",title);
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700002_g_ScriptId,-1,camp,-1, facedir);
			
			end

            if flag == 0 then
				SetFubenData_Param(sceneId, x700002_CSP_GUANYU_ID, nRet)
			elseif 	flag == 1 then
				SetFubenData_Param(sceneId, x700002_CSP_LUSU_ID, nRet)
            end
        end
    end
end

function x700002_CreateStep4RunMonster(sceneId)

	local nCurrentGameStep = GetFubenData_Param(sceneId, x700002_CSP_GAME_STEP)

	if nCurrentGameStep~= 4 then
		return
	end

	local nRunCount = 0 --GetFubenData_Param(sceneId, x700002_CSP_STEP_BOSS_COUNT ) ;
	local nCount =nRunCount;

	local fubenlevel = GetFubenData_Param(sceneId, x700002_CSP_FUBENLEVEL ) ;
	local nIndexFrom = GetFubenDataPosByScriptID(x700002_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700002_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700002_g_ScriptId,nIndexFrom,i)
		if idScript == x700002_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel then
			for j=0,count -1 do
				local rx = random(-r,r)
				local x = x + rx
				local rz = random(-r,r)
				local z = z + rz

				local nRet = 0
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700002_g_ScriptId,-1,21,-1, facedir,  "",title);
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700002_g_ScriptId,-1,21,-1, facedir);
				
				end

				if patrolid>=0 then
						SetPatrolId(sceneId, nRet, patrolid)
				end
				SetFubenData_Param(sceneId, x700002_CSP_RUN_MONSTER_START+ nCount, nRet)
				nCount = nCount +1
			end
			
        end
    end 

	SetFubenData_Param(sceneId, x700002_CSP_RUN_MONSTER_COUNT, nCount)

	x700002_ShowTipsToAll(sceneId, "匈奴兵去报信了，赶快阻止他们")
end
	

function x700002_CreateBoss(sceneId,index)
	
	local nBossCount = 0 --GetFubenData_Param(sceneId, x700002_CSP_STEP_BOSS_COUNT ) ;
	local nCount =nBossCount;

	local fubenlevel = GetFubenData_Param(sceneId, x700002_CSP_FUBENLEVEL ) ;
	local nIndexFrom = GetFubenDataPosByScriptID(x700002_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700002_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700002_g_ScriptId,nIndexFrom,i)
		if idScript == x700002_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel then
            if flag == index   then
				for j=0,count -1 do

					local rx = random(-r,r)
					local x = x + rx
					local rz = random(-r,r)
					local z = z + rz

					local nRet = 0
					if title~="" then
						nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700002_g_ScriptId,-1,21,-1, facedir,  "",title);
					else
						nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700002_g_ScriptId,-1,21,-1, facedir);
					
					end


					if patrolid>=0 then
						SetPatrolId(sceneId, nRet, patrolid)
					end

					SetFubenData_Param(sceneId, x700002_CSP_STEP_BOSS_START + nCount, nRet)
					
					nCount = nCount+1

					if index ==3 then
						local nFullHp = GetHp( sceneId, nRet )
						SetFubenData_Param(sceneId, x700002_CSP_MYS_FULL_HP,nFullHp )
						SetFubenData_Param(sceneId, x700002_CSP_MYS_B_START_CALL,0 )
						break;
					end
				end
            end

			
        end
    end

	SetFubenData_Param(sceneId, x700002_CSP_STEP_BOSS_COUNT, nCount ) ;

end





---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700002_CreateMonster(sceneId,index)


    local fubenlevel = GetFubenData_Param(sceneId, x700002_CSP_FUBENLEVEL ) ;

	local nMonsterCount = GetFubenData_Param(sceneId, x700002_CSP_MONSTER_COUNT ) ;
	local nCount =nMonsterCount;

	local nIndexFrom = GetFubenDataPosByScriptID(x700002_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700002_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700002_g_ScriptId,nIndexFrom,i)
		if idScript == x700002_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then
			
            if flag == index  then
				for j=0,count -1 do

					local rx = random(-r,r)
					local x = x + rx
					local rz = random(-r,r)
					local z = z + rz
					local monsterid = 0
					if title~="" then
						monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700002_g_ScriptId,-1,21,-1,facedir,  "",title);
					else
						monsterid = CreateMonster(sceneId, type, x, z, ai, aiscript, x700002_g_ScriptId,-1,21,-1,facedir);
					end

					if patrolid>=0 then
						SetPatrolId(sceneId, monsterid, patrolid)
					end

					SetFubenData_Param(sceneId, x700002_CSP_MONSTER_START+nCount, monsterid ) ;
					nCount = nCount +1
				end
            end
        end
    end


	SetFubenData_Param(sceneId, x700002_CSP_MONSTER_COUNT, nCount ) ;

end






function x700002_CreateNpc( sceneId )
	

	local fubenlevel = GetFubenData_Param(sceneId, x700002_CSP_FUBENLEVEL ) ;

	for i, item in x700002_g_NpcCreate do

       
		local nRet = 0
		if item.title~="" then
			nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, -1,item.guid,-1,-1,item.facedir,  "",item.title);
		else
			nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, -1,item.guid,-1,-1,item.facedir);
		
		end

		if item.flag==0 then
			SetFubenData_Param(sceneId, x700002_CSP_STARTNPC_ID, nRet)
			SetFubenData_Param(sceneId, x700002_CSP_GAME_STEP,x700002_g_StartGame)
			x700002_StartBaoMu(sceneId)
		elseif item.flag==1 then
			SetFubenData_Param(sceneId, x700002_CSP_LAOBAN_ID, nRet)
		end
		
	end

    
end

function x700002_CreateGz( sceneId )
	

	local nGzCount = GetFubenData_Param(sceneId, x700002_CSP_GZ_COUNT ) ;
	local nCount =nGzCount;

	for i, item in x700002_g_GzCreate do

		local nRet = 0
		if item.title~="" then
			nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, -1,-1,-1,-1,item.facedir, "", item.title);
		else
			nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, -1,-1,-1,-1,item.facedir);
		
		end
		
		SetFubenData_Param(sceneId, x700002_CSP_GZ_START+nCount, nRet ) ;
		nCount = nCount+1
	end

	SetFubenData_Param(sceneId, x700002_CSP_GZ_COUNT, nCount ) ;
    
end


function x700002_AllGzSay(sceneId, str)
	local nGzCount = GetFubenData_Param(sceneId, x700002_CSP_GZ_COUNT ) ;

	for i=0, nGzCount-1 do
		local nGzId = GetFubenData_Param(sceneId, x700002_CSP_GZ_START+i)
		NpcTalk(sceneId, nGzId, str,  -1)
	end
end


function x700002_LaobanSay(sceneId, str)
	local laoban = GetFubenData_Param(sceneId, x700002_CSP_LAOBAN_ID)
	NpcTalk(sceneId, laoban, str,  -1)
end



function x700002_ShowTipsToAll(sceneId, str)

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


function x700002_OnDie(sceneId, selfId, killerId)
	
	
	local nFubenStatus = GetFubenData_Param(sceneId, x700002_CSP_B_FUBEN_STATUS)  
	if nFubenStatus~= 0 then
		return
	end
	local nDieCount = GetFubenData_Param(sceneId, x700002_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700002_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	local nNpcObjId = GetFubenData_Param(sceneId, x700002_CSP_STARTNPC_ID)

	

	local bBoss  = 0;

	
	local nCurrentStep = GetFubenData_Param(sceneId, x700002_CSP_GAME_STEP)


	local nBossCount = GetFubenData_Param(sceneId, x700002_CSP_STEP_BOSS_COUNT)
	

	

	for i = 0, nBossCount - 1 do
		local nBossID = GetFubenData_Param(sceneId, x700002_CSP_STEP_BOSS_START + i)
		if nBossID>=0 then
			if nBossID== selfId then
				for j=i, nBossCount-2 do
					local nNextId = GetFubenData_Param(sceneId, x700002_CSP_STEP_BOSS_START+j+1)
					SetFubenData_Param(sceneId, x700002_CSP_STEP_BOSS_START+j, nNextId)
					
				end
				SetFubenData_Param(sceneId, x700002_CSP_STEP_BOSS_START+nBossCount-1,-1)
				SetFubenData_Param(sceneId, x700002_CSP_STEP_BOSS_COUNT,nBossCount-1)

				bBoss = i+1;

				if nCurrentStep==2 then

					x700002_CreateMonster(sceneId,nCurrentStep-1)
					x700002_ShowTipsToAll(sceneId, "伏兵出现！")
				end

				if (nBossCount-1)==0 then
					x700002_OnAllBossOver(sceneId)
					
					--//add in 2009-3-18
					if nCurrentStep==4 then
						SetFubenData_Param(sceneId, x700002_CSP_FINAL_KILLER_ID,killerId)
					end
					--//add end

				end
				break;
			end
		end
	end

	


	local nMonsterCount = GetFubenData_Param(sceneId, x700002_CSP_MONSTER_COUNT)

	for i=0, nMonsterCount-1 do
		local nMonsterId = GetFubenData_Param(sceneId, x700002_CSP_MONSTER_START+i)
		if nMonsterId== selfId then
			for j=i, nMonsterCount-2 do
				local nNextId = GetFubenData_Param(sceneId, x700002_CSP_MONSTER_START+j+1)
				SetFubenData_Param(sceneId, x700002_CSP_MONSTER_START+j, nNextId)
				
			end
			SetFubenData_Param(sceneId, x700002_CSP_MONSTER_START+nMonsterCount-1,-1)
			SetFubenData_Param(sceneId, x700002_CSP_MONSTER_COUNT,nMonsterCount-1)
			if (nMonsterCount-1)==0 then
				x700002_OnAllMonsterOver(sceneId)
			end
			break
		end
	end


	if nCurrentStep ==2 then
		local nStepNpcId = GetFubenData_Param(sceneId, x700002_CSP_STEP_NPC_ID)
		local nGuanyuId = GetFubenData_Param(sceneId, x700002_CSP_GUANYU_ID)
		local nLusucId = GetFubenData_Param(sceneId, x700002_CSP_LUSU_ID)

		if nStepNpcId== selfId then
			x700002_ShowTipsToAll(sceneId, "周仓被杀")
			GetFubenData_Param(sceneId, x700002_CSP_STEP_NPC_ID,-1)
		elseif  nGuanyuId== selfId then
			GetFubenData_Param(sceneId, x700002_CSP_GUANYU_ID,-1)
			x700002_OnFubenFailed(sceneId,nCurrentStep)
		end
	end

	if nCurrentStep==4 then
		
		local nRunMonsterCount = GetFubenData_Param(sceneId, x700002_CSP_RUN_MONSTER_COUNT)

		for i=0, nRunMonsterCount-1 do
			local nMonsterId = GetFubenData_Param(sceneId, x700002_CSP_RUN_MONSTER_START+i)
			if nMonsterId== selfId then
				for j=i, nRunMonsterCount-2 do
					local nNextId = GetFubenData_Param(sceneId, x700002_CSP_RUN_MONSTER_START+j+1)
					SetFubenData_Param(sceneId, x700002_CSP_RUN_MONSTER_START+j, nNextId)
					
				end
				SetFubenData_Param(sceneId, x700002_CSP_RUN_MONSTER_START+nRunMonsterCount-1,-1)
				SetFubenData_Param(sceneId, x700002_CSP_RUN_MONSTER_COUNT,nRunMonsterCount-1)
				if (nRunMonsterCount-1)==0 then
					x700002_OnAllRunMonsterOver(sceneId)
				end
				break
			end
		end
	end
	


	
end

function x700002_OnFubenFailed(sceneId,nParam)
	local nFubenStatus = GetFubenData_Param(sceneId, x700002_CSP_B_FUBEN_STATUS)  
	if nFubenStatus~= 0 then
		return
	end


	if nParam==2 then
		x700002_ShowTipsToAll(sceneId, "关羽被杀，副本失败")

		local nStepNpcId = GetFubenData_Param(sceneId, x700002_CSP_STEP_NPC_ID)
		local nGuanyuId = GetFubenData_Param(sceneId, x700002_CSP_GUANYU_ID)
		local nLusucId = GetFubenData_Param(sceneId, x700002_CSP_LUSU_ID)

		if nStepNpcId>=0  then
			x700002_DeleteMonster( sceneId,nStepNpcId )
			SetFubenData_Param(sceneId, x700002_CSP_STEP_NPC_ID,-1)
		end

		if nLusucId>=0 then
			x700002_DeleteMonster( sceneId,nLusucId )
			SetFubenData_Param(sceneId, x700002_CSP_LUSU_ID,-1)
		end

	elseif nParam==4 then
		
		x700002_ShowTipsToAll(sceneId, "匈奴兵报信成功，副本失败")
		local nRunMonsterCount = GetFubenData_Param(sceneId, x700002_CSP_RUN_MONSTER_COUNT)

		for i=0, nRunMonsterCount-1 do
			local nMonsterId = GetFubenData_Param(sceneId, x700002_CSP_RUN_MONSTER_START+i)
			if nMonsterId>=0 then
				x700002_DeleteMonster( sceneId,nMonsterId )
				SetFubenData_Param(sceneId, x700002_CSP_RUN_MONSTER_START+i,-1)
			end
		end
	else
		return
	end
	SetFubenData_Param(sceneId, x700002_CSP_B_FUBEN_STATUS,2)  -- 失败
	

	local nMonsterCount = GetFubenData_Param(sceneId, x700002_CSP_MONSTER_COUNT)

	for i=0, nMonsterCount-1 do
		local nMonsterId = GetFubenData_Param(sceneId, x700002_CSP_MONSTER_START+i)

		if nMonsterId>=0 then
			x700002_DeleteMonster( sceneId,nMonsterId )
			SetFubenData_Param(sceneId, x700002_CSP_MONSTER_START+i,-1)
		end
	end

	local nBossCount = GetFubenData_Param(sceneId, x700002_CSP_STEP_BOSS_COUNT)

	for i = 0, nBossCount - 1 do
		local nBossID = GetFubenData_Param(sceneId, x700002_CSP_STEP_BOSS_START + i)
		if nBossID>=0 then
			x700002_DeleteMonster( sceneId,nBossID )
			SetFubenData_Param(sceneId, x700002_CSP_STEP_BOSS_START+i,-1)
		end
	end

	x700002_ShowTipsToAll(sceneId, "副本失败，请离开副本")


	x700002_AllGzSay(sceneId, "可惜了")
	x700002_LaobanSay(sceneId, "真遗憾啊")

	local nNpcId = GetFubenData_Param(sceneId, x700002_CSP_STARTNPC_ID)
	NpcTalk(sceneId, nNpcId, "...",  -1)
	
	x700002_CreateLeaveNpc( sceneId)
end

function x700002_OnFubenSuccess(sceneId)

	local nFubenStatus = GetFubenData_Param(sceneId, x700002_CSP_B_FUBEN_STATUS)  
	if nFubenStatus~= 0 then
		return
	end
	SetFubenData_Param(sceneId, x700002_CSP_B_FUBEN_STATUS,1)  -- 成功
	x700002_ShowTipsToAll(sceneId, "副本完成，请退出副本。")

	x700002_AllGzSay(sceneId, "英雄")
	x700002_LaobanSay(sceneId, "好家伙")

	local nNpcId = GetFubenData_Param(sceneId, x700002_CSP_STARTNPC_ID)
	NpcTalk(sceneId, nNpcId, "英雄们，可以离开副本了",  -1)
	x700002_CreateSubmitNpc( sceneId)

--	--//--------------------------- 世界喊话 Start--------------------
--			-- 副本完成
--
--		--//add in 2009-3-18
--		local killerId = GetFubenData_Param(sceneId, x700002_CSP_FINAL_KILLER_ID)
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
--		--//add end
--
--		local nowTickCount = GetFubenData_Param(sceneId, x700002_CSP_TICKCOUNT)
--
--		local nowTime = x700002_g_TickTime* nowTickCount;
--
--		local nMinute = floor(nowTime/60)
--		local nSec = mod(nowTime,60)
--
--		
--		local strKillTime = format("%d分%d秒", nMinute, nSec) -- 杀死关务的事件
--
--		LuaAllScenceM2Wrold (sceneId,"#R一唱三叹,余音绕梁，#G"..strKillTime.."#R后，勾栏曲台的戏幕已经落下，但#G"..strPlayerName.."#R和他的朋友们依然如痴如醉。", 0, 1)
--		
	--//--------------------------- 世界喊话 end----------------------
end



function x700002_CreateSubmitNpc( sceneId)
	if x700002_g_SubmitNPC.title~="" then
	  CreateMonster(sceneId, x700002_g_SubmitNPC.type, x700002_g_SubmitNPC.x, x700002_g_SubmitNPC.z, 3, 0, -1, x700002_g_SubmitNPC.guid, -1, -1,x700002_g_SubmitNPC.facedir, "", x700002_g_SubmitNPC.title )
	else
	  CreateMonster(sceneId, x700002_g_SubmitNPC.type, x700002_g_SubmitNPC.x, x700002_g_SubmitNPC.z, 3, 0, -1, x700002_g_SubmitNPC.guid, -1, -1,x700002_g_SubmitNPC.facedir )
	
	end
end

function x700002_CreateLeaveNpc( sceneId)
	if x700002_g_LeaveNPC.title~="" then
		CreateMonster(sceneId, x700002_g_LeaveNPC.type, x700002_g_LeaveNPC.x, x700002_g_LeaveNPC.z, 3, 0, -1, x700002_g_LeaveNPC.guid, -1, -1,x700002_g_LeaveNPC.facedir, "", x700002_g_LeaveNPC.title )
	else
		CreateMonster(sceneId, x700002_g_LeaveNPC.type, x700002_g_LeaveNPC.x, x700002_g_LeaveNPC.z, 3, 0, -1, x700002_g_LeaveNPC.guid, -1, -1,x700002_g_LeaveNPC.facedir )
	
	end
end

function x700002_DeleteMonster(sceneId,selfId)
	if IsObjValid(sceneId,selfId) == 1 and GetHp(sceneId,selfId ) > 0 then
		DeleteMonster(sceneId,selfId)
	end
end

