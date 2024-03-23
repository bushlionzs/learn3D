--desc	: "特效练功人偶"道具脚本

x404910_g_scriptId = 404910


x404910_g_DestSceneName = "强效练功人偶"
x404910_g_Get_Exp_Max_Cnt = 15 --击败特效练功人偶或者玩家获得技能经验的人数上限为15人
x404910_g_BossType  = 9527
x404910_g_MissionID = 9092

function x404910_GetMonsterCount(sceneId, selfId)
	local nCount = 0;
	local nMonsterCount = GetMonsterCount(sceneId)
	for i=1,nMonsterCount do
    	local objid		 	= 	GetMonsterObjID(sceneId,i-1)
		--if IsObjValid(sceneId,objid) == 1 and GetHp(sceneId,objid) > 0 then
			local npcType 		= 	GetMonsterDataID(sceneId,objid)

				if npcType == 9526 or npcType == 9527 then
					nCount = nCount + 1
			end
		--end
	end

	return nCount
end

function x404910_ProcEventEntry( sceneId, selfId, BagIndex )

	local nCnt  =  x404910_GetDayCount(sceneId, selfId) + 1
	if    nCnt  >  x404910_g_Get_Exp_Max_Cnt then
		  local strText = "#Y专攻训练：\n\t#W您今天可以获得专攻点数的杀人上限#R已满#W，不能再通过击败练功人偶获得专攻点数。\n \n#Y专防训练：\n\t#W练功人偶可以#G帮助#W您完成“防御之路”任务，击败练功人偶相当于击败#G任何职业#W的玩家。\n \n#Y荣誉：\n\t#W本日荣誉未满的情况下，击败练功人偶仍可以获得荣誉。\n \n\t#R您是否要坚持使用？"
		  BeginQuestEvent(sceneId)
		  AddQuestText(sceneId, strText)
		  EndQuestEvent(sceneId)
		  --DispatchQuestTips(sceneId, selfId)
		  --DispatchQuestInfo(sceneId, selfId, selfId, x404910_g_scriptId, x404910_g_MissionID,  0)
		  DispatchQuestInfoNM(sceneId, selfId, selfId, x404910_g_scriptId, x404910_g_MissionID,  0)
		  --Msg2Player(sceneId,selfId,strText, 8, 2)
		  return 
	else
		  x404910_ProcMyTask( sceneId, selfId)
	end




	------------------------------------------------if x404910_GetMonsterCount(sceneId, selfId) == 10 then
	------------------------------------------------	  BeginQuestEvent(sceneId)
	------------------------------------------------	  AddQuestText(sceneId, "本场景内木桩人过多，请击败后再继续召唤！")
	------------------------------------------------	  EndQuestEvent(sceneId)
	------------------------------------------------	  DispatchQuestTips(sceneId, selfId)
	------------------------------------------------	  return
	------------------------------------------------end
	------------------------------------------------
	--------------------------------------------------删除道具逻辑,使用一次删除一个
	------------------------------------------------local nItemCount = GetItemCountInBag( sceneId, selfId, 12030218)
	------------------------------------------------if nItemCount >= 1 then
	------------------------------------------------		local ret = DelItemByIDInBag( sceneId, selfId, 12030218, 1) --删除物品
	------------------------------------------------else
	------------------------------------------------		return 0
	------------------------------------------------end
	------------------------------------------------
	------------------------------------------------local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )
	------------------------------------------------local ret = CreateMonster( sceneId, x404910_g_BossType, PlayerPosX, PlayerPosZ, 1, -1, x404910_g_scriptId, -1, 21,3*60000) --存活时间3分钟
    ------------------------------------------------
	------------------------------------------------if ret > 0 then
	------------------------------------------------		--DelItem( sceneId, selfId, 12030218, 1); --删除物品
	------------------------------------------------		--local ret = DelItemByIDInBag( sceneId, selfId, 12030218, 1) --删除物品
	------------------------------------------------		local message = "特效练功人偶召唤的怪物出现了"
	------------------------------------------------		Msg2Player(sceneId,selfId,message, 8, 2)
	------------------------------------------------		Msg2Player(sceneId,selfId,message, 8, 3)
	------------------------------------------------		--GLOBAL_CREATE_MONSTER_CNT_PER_SCENE[sceneId] = GLOBAL_CREATE_MONSTER_CNT_PER_SCENE[sceneId] + 1
	------------------------------------------------else
	------------------------------------------------		local strText = format("这里特效练功人偶无法召出怪物" )
	------------------------------------------------		BeginQuestEvent(sceneId)
	------------------------------------------------		AddQuestText(sceneId, strText)
	------------------------------------------------		EndQuestEvent(sceneId)
	------------------------------------------------		DispatchQuestTips(sceneId, selfId)
	------------------------------------------------		Msg2Player(sceneId,selfId,strText, 8, 2)
	------------------------------------------------end
end

function x404910_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x404910_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x404910_OnConditionCheck( sceneId, selfId )
	return 0
end

function x404910_OnDeplete( sceneId, selfId )

	return 0
end

function x404910_OnActivateOnce( sceneId, selfId )
end

function x404910_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end

function x404910_OnDie(sceneId, selfId, killerId)--怪死亡添加日志

	--召唤怪物的人可以获得如同杀死与他同等级异国玩家的效果（可以获得荣誉和专精技能经验点）
	--功能与“练功人偶”一致，但是可以提高普通获得专精经验的杀人上限
    --这里需要实现逻辑
	--to be fixed!!!

	--杀死怪物的人可以获得如同杀死与他同等级异国玩家的效果（可以获得荣誉和专精技能经验点）
	--to be fixed!!!


	--把下面的这个函数的实现重构一遍
	--function x888888_CalculateHonor( mapId, diedId, killerId )
	--需要判断二者的级别是否相等
	--from function x888888_HonorNumCalculate( mapId, diedId, killerId )

	local killerLevel = GetLevel(sceneId, killerId)
	local diedLevel   = killerLevel

	--（被杀者等级的平方/（杀人者等级+被杀者等级））/2
	local honor = (diedLevel * diedLevel / (killerLevel + diedLevel)) / 2
	local killerCountry = GetCurCountry(sceneId, killerId)
	--四舍五入
	local tempHonor = floor(honor);
	if honor >= tempHonor + 0.5 then
		honor = tempHonor + 1
	else
		honor = tempHonor
	end

	if x404910_IsCanAddHonor(sceneId, selfId, killerId) == 1 then
		SetHonorInfo(sceneId, killerId, "HONORNUM", GetHonorInfo(sceneId, killerId, "HONORNUM") +honor)
		AddHonor(sceneId, killerId, honor)
		local szMsg = "获得荣誉#G" .. honor .. "#o点"
		local killerName = GetName(sceneId,killerId)
		LuaScenceM2Player(sceneId, killerId, szMsg, killerName, CHAT_RIGHTDOWN, 1 )
	end

	--获得专精技能点
	--to be fixed!!!
	local nCnt  =  x404910_GetDayCount(sceneId, killerId) + 1
	if    nCnt  >  x404910_g_Get_Exp_Max_Cnt then
		  return -1
	else
		local strMSG = AddInherenceZhuanGongExp(sceneId,killerId)
		Msg2Player(sceneId,killerId,strMSG,8,2)
		x404910_SetDayCount(sceneId, killerId)
	end

end



--练功人偶和特效练功人偶公用同一个MD
--每次判断的最大次数不同
---------------------------------------------------------------------------------------------------
--取得获取专精技能经验点的人数
--from common_daguanyuan_tianfu.lua
---------------------------------------------------------------------------------------------------
function x404910_GetDayCount(sceneId, selfId)
	if x404910_g_Get_Exp_Max_Cnt > 0 then
		local today = GetDayOfYear()
		--local lastday = GetQuestData(sceneId, selfId, MD_FUBEN_DAGUANYUAN_SHANGXIANG_DATE[1], MD_FUBEN_DAGUANYUAN_SHANGXIANG_DATE[2], MD_FUBEN_DAGUANYUAN_SHANGXIANG_DATE[3])
		local lastday = GetQuestData(sceneId, selfId, MD_TISHENSHADAI_DATE[1], MD_TISHENSHADAI_DATE[2], MD_TISHENSHADAI_DATE[3])
		if lastday ~= today then
			return 0
		end

		--local daycount =  GetQuestData(sceneId, selfId, MD_FUBEN_DAGUANYUAN_SHANGXIANG_DAYCOUNT[1], MD_FUBEN_DAGUANYUAN_SHANGXIANG_DAYCOUNT[2], MD_FUBEN_DAGUANYUAN_SHANGXIANG_DAYCOUNT[3])
		local daycount =  GetQuestData(sceneId, selfId, MD_TISHENSHADAI_DAYCOUNT[1], MD_TISHENSHADAI_DAYCOUNT[2], MD_TISHENSHADAI_DAYCOUNT[3])
		return daycount

	end
	return 0
end



-------------------------------------`--------------------------------------------------------------
--更新当天获取专精技能经验点的人
--from common_daguanyuan_tianfu.lua
---------------------------------------------------------------------------------------------------
function x404910_SetDayCount(sceneId, selfId)
	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_TISHENSHADAI_DATE[1], MD_TISHENSHADAI_DATE[2], MD_TISHENSHADAI_DATE[3])
	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_TISHENSHADAI_DATE[1], MD_TISHENSHADAI_DATE[2], MD_TISHENSHADAI_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_TISHENSHADAI_DAYCOUNT[1], MD_TISHENSHADAI_DAYCOUNT[2], MD_TISHENSHADAI_DAYCOUNT[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, MD_TISHENSHADAI_DAYCOUNT[1], MD_TISHENSHADAI_DAYCOUNT[2], MD_TISHENSHADAI_DAYCOUNT[3])
		SetQuestData(sceneId, selfId, MD_TISHENSHADAI_DAYCOUNT[1], MD_TISHENSHADAI_DAYCOUNT[2], MD_TISHENSHADAI_DAYCOUNT[3], daycount+1)
	end
end


function x404910_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x404910_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x404910_OnConditionCheck( sceneId, selfId )
	return 0
end

function x404910_OnDeplete( sceneId, selfId )

	return 0
end

function x404910_OnActivateOnce( sceneId, selfId )
end

function x404910_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end

function x404910_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
end

function x404910_ProcAccept( sceneId, selfId )
end

function x404910_ProcMyTask( sceneId, selfId)

	if GetSceneType(sceneId) ~=0 then
			BeginQuestEvent(sceneId)
		  AddQuestText(sceneId, "这里无法使用该道具，请前往普通场景！")
		  EndQuestEvent(sceneId)
		  DispatchQuestTips(sceneId, selfId)
		  return 
	end

	if x404910_GetMonsterCount(sceneId, selfId) == 50 then
		  BeginQuestEvent(sceneId)
		  AddQuestText(sceneId, "本场景内人偶过多，请击败后再继续召唤！")
		  EndQuestEvent(sceneId)
		  DispatchQuestTips(sceneId, selfId)
		  return
	end

	local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )
	local nGuid   = GetGUID(sceneId,    selfId)
	local nCampId = 21
	--local nCampId = GetCurCamp(sceneId, selfId)

	--删除道具逻辑,使用一次删除一个
	local nItemCount = GetItemCountInBag( sceneId, selfId, 12030218)
	--print("-------------------->",nItemCount)
	if nItemCount >= 1 then
			local ret = DelItemByIDInBag( sceneId, selfId, 12030218, 1) --删除物品
	else
			--print("------------------------------------")
			return 0
	end
	local r0 = random(-1,1)
	local r1 = random(-1,1)
	local ret = CreateMonster( sceneId, x404910_g_BossType, PlayerPosX+r0, PlayerPosZ+r1, 7, -1, x404910_g_scriptId, nGuid, 21, 3*60000) --存活时间3分钟

	if ret > 0 then
					local message = "强效练功人偶出现了"
					Msg2Player(sceneId,selfId,message, 8, 2)
					Msg2Player(sceneId,selfId,message, 8, 3)
	else
					local strText = format("这里无法召出强效练功人偶" )
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, strText)
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId, selfId)
					Msg2Player(sceneId,selfId,strText, 8, 2)
	end
end


--********************
--检测接受条件
--**********************************
function x404910_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

function x404910_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	x404910_ProcMyTask( sceneId, selfId)
end



function x404910_IsCanAddHonor(sceneId, selfId, killerId)
	--每天的荣誉限制 如果天数变了 更新之
	local today = GetDayOfYear()
	local honorDay = GetHonorInfo(sceneId, killerId, "HONORDAY") 
	if today ~= honorDay then
		SetHonorInfo(sceneId, killerId, "HONORDAY", today)
		SetHonorInfo(sceneId, killerId, "HONORNUM", 0)
	end
	
	local selfLevel = GetLevel(sceneId, killerId)
	local honorNum = GetHonorInfo(sceneId, killerId, "HONORNUM")
	local honorMax = 0
	if IsHaveSpecificImpact( sceneId, killerId, 9016) > 0 then
		honorMax = selfLevel * 40
	else
		honorMax = selfLevel * 20
	end
	
	if honorNum >= honorMax then
		Msg2Player(sceneId,killerId,"你今天已经达到每日杀人荣誉上限，今天不能再通过击杀木偶人来获得荣誉。", 8, 2) 
		return -1
	end
	
	return 1
end
