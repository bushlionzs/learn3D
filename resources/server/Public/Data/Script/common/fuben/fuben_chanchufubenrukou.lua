--创建十字井任务NPC

x700095_g_MissionName="金矿洞"

--脚本号
x700095_g_ScriptId = 700095

---------------------------------- enter day and time --------------------------
x700095_g_EnterTime					=	{                       --活动时间段
											{min=0*60+29, max=1*60+1},
											{min=10*60+29, max=11*60+1},
											{min=14*60+29, max=15*60+1},
											{min=16*60+29, max=17*60+1},
										}

x700095_g_EnterDay					=	{0,1,2,3,4,5,6};

---------------------------------- enter day and time end --------------------------
x700095_g_HoldTime		= 1800*1000


-- flag: 怪物类型， 0：30级， 1：50级，2：70级 3：90级，
x700095_g_Npc_MonsterData ={
	{name="1号",type=28500,guid=150581,title="30入口",monsterflag=1, scriptid = 700012, level=30},
	{name="2号",type=28501,guid=150582,title="50入口",monsterflag=2, scriptid = 700012, level=50},
	{name="3号",type=28502,guid=150583,title="70入口",monsterflag=3, scriptid = 700012, level=70},
	{name="4号",type=28503,guid=150584,title="90入口",monsterflag=4, scriptid = 700012, level=90},
}

--每个地图NPC出现个数
x700095_g_Info_List = { 
	{mapid =87,	 createcount = 10, monsterflag=1, nPosLen = 12, poslist = {{x=80,z=80},{x=90,z=90},{x=100,z=100},{x=110,z=110},{x=120,z=120},{x=130,z=130},{x=140,z=140},{x=150,z=30},{x=160,z=160},{x=170,z=170},{x=180,z=180},{x=190,z=190}}},
	{mapid =86,	 createcount = 10, monsterflag=2, nPosLen = 12, poslist = {{x=80,z=80},{x=90,z=90},{x=100,z=100},{x=110,z=110},{x=120,z=120},{x=130,z=130},{x=140,z=140},{x=150,z=30},{x=160,z=160},{x=170,z=170},{x=180,z=180},{x=190,z=190}}},
	{mapid =89, createcount = 10, monsterflag=3, nPosLen = 12, poslist = {{x=80,z=80},{x=90,z=90},{x=100,z=100},{x=110,z=110},{x=120,z=120},{x=130,z=130},{x=140,z=140},{x=150,z=30},{x=160,z=160},{x=170,z=170},{x=180,z=180},{x=190,z=190}}},
	{mapid =51, createcount = 10, monsterflag=4, nPosLen = 12, poslist = {{x=80,z=80},{x=90,z=90},{x=100,z=100},{x=110,z=110},{x=120,z=120},{x=130,z=130},{x=140,z=140},{x=150,z=30},{x=160,z=160},{x=170,z=170},{x=180,z=180},{x=190,z=190}}},
	{mapid =187,	 createcount = 10, monsterflag=1, nPosLen = 12, poslist = {{x=80,z=80},{x=90,z=90},{x=100,z=100},{x=110,z=110},{x=120,z=120},{x=130,z=130},{x=140,z=140},{x=150,z=30},{x=160,z=160},{x=170,z=170},{x=180,z=180},{x=190,z=190}}},
	{mapid =186,	 createcount = 10, monsterflag=2, nPosLen = 12, poslist = {{x=80,z=80},{x=90,z=90},{x=100,z=100},{x=110,z=110},{x=120,z=120},{x=130,z=130},{x=140,z=140},{x=150,z=30},{x=160,z=160},{x=170,z=170},{x=180,z=180},{x=190,z=190}}},
	{mapid =189, createcount = 10, monsterflag=3, nPosLen = 12, poslist = {{x=80,z=80},{x=90,z=90},{x=100,z=100},{x=110,z=110},{x=120,z=120},{x=130,z=130},{x=140,z=140},{x=150,z=30},{x=160,z=160},{x=170,z=170},{x=180,z=180},{x=190,z=190}}},
	{mapid =151, createcount = 10, monsterflag=4, nPosLen = 12, poslist = {{x=80,z=80},{x=90,z=90},{x=100,z=100},{x=110,z=110},{x=120,z=120},{x=130,z=130},{x=140,z=140},{x=150,z=30},{x=160,z=160},{x=170,z=170},{x=180,z=180},{x=190,z=190}}},
	{mapid =287,	 createcount = 10, monsterflag=1, nPosLen = 12, poslist = {{x=80,z=80},{x=90,z=90},{x=100,z=100},{x=110,z=110},{x=120,z=120},{x=130,z=130},{x=140,z=140},{x=150,z=30},{x=160,z=160},{x=170,z=170},{x=180,z=180},{x=190,z=190}}},
	{mapid =286,	 createcount = 10, monsterflag=2, nPosLen = 12, poslist = {{x=80,z=80},{x=90,z=90},{x=100,z=100},{x=110,z=110},{x=120,z=120},{x=130,z=130},{x=140,z=140},{x=150,z=30},{x=160,z=160},{x=170,z=170},{x=180,z=180},{x=190,z=190}}},
	{mapid =289, createcount = 10, monsterflag=3, nPosLen = 12, poslist = {{x=80,z=80},{x=90,z=90},{x=100,z=100},{x=110,z=110},{x=120,z=120},{x=130,z=130},{x=140,z=140},{x=150,z=30},{x=160,z=160},{x=170,z=170},{x=180,z=180},{x=190,z=190}}},
	{mapid =251, createcount = 10, monsterflag=4, nPosLen = 12, poslist = {{x=80,z=80},{x=90,z=90},{x=100,z=100},{x=110,z=110},{x=120,z=120},{x=130,z=130},{x=140,z=140},{x=150,z=30},{x=160,z=160},{x=170,z=170},{x=180,z=180},{x=190,z=190}}},
	{mapid =387,	 createcount = 10, monsterflag=1, nPosLen = 12, poslist = {{x=80,z=80},{x=90,z=90},{x=100,z=100},{x=110,z=110},{x=120,z=120},{x=130,z=130},{x=140,z=140},{x=150,z=30},{x=160,z=160},{x=170,z=170},{x=180,z=180},{x=190,z=190}}},
	{mapid =386,	 createcount = 10, monsterflag=2, nPosLen = 12, poslist = {{x=80,z=80},{x=90,z=90},{x=100,z=100},{x=110,z=110},{x=120,z=120},{x=130,z=130},{x=140,z=140},{x=150,z=30},{x=160,z=160},{x=170,z=170},{x=180,z=180},{x=190,z=190}}},
	{mapid =389, createcount = 10, monsterflag=3, nPosLen = 12, poslist = {{x=80,z=80},{x=90,z=90},{x=100,z=100},{x=110,z=110},{x=120,z=120},{x=130,z=130},{x=140,z=140},{x=150,z=30},{x=160,z=160},{x=170,z=170},{x=180,z=180},{x=190,z=190}}},
	{mapid =351, createcount = 10, monsterflag=4, nPosLen = 12, poslist = {{x=80,z=80},{x=90,z=90},{x=100,z=100},{x=110,z=110},{x=120,z=120},{x=130,z=130},{x=140,z=140},{x=150,z=30},{x=160,z=160},{x=170,z=170},{x=180,z=180},{x=190,z=190}}},
}


function x700095_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4,Param5 )

	if x700095_CheckDay(sceneId)<=0 then
		return
	end

	local strFmt = "产出副本开始了"
	local msg = format(strFmt)
	--LuaAllScenceM2Wrold (sceneId, msg, 4, 1)
	x700095_MsgToCountry(sceneId, msg, 4, 1);

    x700095_CreateEnterNpc( sceneId,actId)

end

function x700095_CheckSceneValid(sceneId)
	for i,item in x700095_g_Info_List do
		if item.mapid == sceneId then
			return 1
		end
	end

	return 0
end

function x700095_GetNpcCreateFlag(sceneId)
	for i,item in x700095_g_Info_List do
		if item.mapid == sceneId then
			return item.monsterflag
		end
	end

	return 0
end

function x700095_GetCreateCount(sceneId)

	for i,item in x700095_g_Info_List do
		if item.mapid == sceneId then
			return item.createcount
		end
	end

	return 0
end

function x700095_CreateEnterNpc( sceneId,actId)
	if x700095_CheckSceneValid(sceneId)<=0 then
		return
	end
	

	local nCreateCount = x700095_GetCreateCount(sceneId);
	
	if nCreateCount==0 then
		return
	end

	local nCreateFlag = x700095_GetNpcCreateFlag(sceneId);
	
	
	
	
	local nLen = 0
	local posList_t
	for i, item in x700095_g_Info_List do
		if sceneId == item.mapid then
			
			nLen = item.nPosLen

			posList_t = item.poslist
			break
		end
	end
	

	if nLen < nCreateCount then
		return
	end
	
	
	local randomlist = {}
	
	--生成随机队列
	for i=1, nCreateCount do
		local nRandom = random(1,nLen)
		while 1 do
			local bRanded = 0
			for j,item in randomlist do
				if item == posindex then
					nRandom = random(1,nLen)
					bRanded = 1
				end
			end

			if bRanded == 0 then
				randomlist[i] = nRandom --记录已经随机过的
				break
			end
		end


	end
	--生成随机队列end
	
	--创建怪物
	local nType = x700095_g_Npc_MonsterData[nCreateFlag].type
	local nGuid = x700095_g_Npc_MonsterData[nCreateFlag].guid
	local strTitle = x700095_g_Npc_MonsterData[nCreateFlag].title

	for i=1, nCreateCount do
		local x = posList_t[randomlist[i]].x
		local z = posList_t[randomlist[i]].z
		
		local nObjId = CreateMonster(sceneId, nType, x, z, 7, -1, -1, nGuid, 20, x700095_g_HoldTime, 0, strTitle)
		
		if nObjId <0 then
			WriteLog(1, format("x700095_CreateEnterNpc创建怪物失败 nObjId = %d,sceneId=%d, nType=%d, x=%d, z=%d,nGuid=%X,strTitle=%s",nObjId,sceneId, nType, x, z,nGuid,strTitle))
		end
	end


	local strFmt = "产出副本入口刷出来了"
	local msg = format(strFmt,x,z )
	--LuaAllScenceM2Wrold (sceneId, msg, 0, 1)
	x700095_MsgToCountry(sceneId, msg, 0, 1);

end



function x700095_CheckDay(sceneId)
	local weekDay = GetWeek()
	for i, item in x700095_g_EnterDay do
		if weekDay==item then
			
			
			return 1;
			
		end
	end

	return 0;
end

function x700095_CheckTime(sceneId)
	local hour,minute,sec =GetHourMinSec();
	local nowtime = hour*60+minute
	
	for i, item in x700095_g_EnterTime do
		if nowtime >= item.min and nowtime <= item.max then
			
			
			return 1;
			
		end
	end
	
	return 0
end

function x700095_MsgToCountry(sceneId, msg, nParam1, nParam2)
	if sceneId==50 then
		LuaAllScenceM2Country(sceneId, msg, 0, nParam1, nParam2)
	elseif sceneId==150 then
		LuaAllScenceM2Country(sceneId, msg, 1, nParam1, nParam2)
	elseif sceneId==250 then
		LuaAllScenceM2Country(sceneId, msg, 2, nParam1, nParam2)
	elseif sceneId==350 then
		LuaAllScenceM2Country(sceneId, msg, 3, nParam1, nParam2)
	end

end



function x700095_ProcEnumEvent( sceneId, selfId, targetId, index )
	local nNpcGuid = GetNpcGuid(sceneId,targetId)
	
	local nIndex = 0;
	local bFind = 0;
	local nLevelLimit = 0
	for i, item in x700095_g_Npc_MonsterData do
		nIndex = nIndex + 1
		if item.guid == nNpcGuid then
			bFind = 1
			nLevelLimit = item.level
			break
		end
	end

	if bFind == 0 then
		return
	end

	local nLevel = GetLevel(sceneId, selfId)
	if nLevel <= nLevelLimit then

		return
		
	end	

	AddQuestNumText(sceneId,x700095_g_ScriptId, x700095_g_MissionName, 14, 0)


end


function x700095_ProcEventEntry( sceneId , selfId , targetId , state , nExt )
	
	if nExt == nil then
		return
	end


	x700095_DispatchChanchuFubenMode(sceneId , selfId , targetId  , nExt)
	
end

function x700095_DispatchChanchuFubenMode(sceneId , selfId , targetId  , nExt)
	if nExt == nil then
		return
	end

	
	if nExt == 0 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"选择进入模式")
			AddQuestNumText(sceneId,x700095_g_ScriptId, x700095_g_MissionName.."普通模式", 14, 1)
			--AddQuestNumText(sceneId,x700095_g_ScriptId, x700095_g_MissionName.."现金模式", 14, 2)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId, targetId)
	else
		x700095_DispatchDetailMode(sceneId , selfId , targetId  , nExt)
	end
	
end

function x700095_DispatchDetailMode(sceneId , selfId , targetId  , nExt)

	if nExt == nil then
		return
	end

	local nNpcGuid = GetNpcGuid(sceneId,targetId)
	
	local nIndex = 0;
	local bFind = 0;
	local nLevelLimit = 0
	for i, item in x700095_g_Npc_MonsterData do
		nIndex = nIndex + 1
		if item.guid == nNpcGuid then
			bFind = 1
			nLevelLimit = item.level
			break
		end
	end

	if bFind == 0 then
		return
	end

	BeginQuestEvent(sceneId)
		
		if nExt ==1 then
			AddQuestText(sceneId,"#Y"..x700095_g_MissionName.."普通模式")
		elseif nExt ==2 then
			AddQuestText(sceneId,"#Y"..x700095_g_MissionName.."现金模式")
		else
			return
		end
		--任务信息
		AddQuestText(sceneId,"剧情描述")

		if nExt ==1 then
			AddQuestText(sceneId,"副本说明："..x700095_g_MissionName.."普通模式")
		elseif nExt ==2 then
			AddQuestText(sceneId,"副本说明："..x700095_g_MissionName.."现金模式")
		else
			return
		end

		
	EndQuestEvent()

	x700095_SaveChanchuFubenFubenTalkMode(sceneId, selfId, nExt)
	x700095_SaveChanchuFubenIndex(sceneId, selfId, nIndex)
	x700095_SaveChanchuFubenTalkNPCID(sceneId, selfId, targetId)

	DispatchQuestInfo(sceneId, selfId, targetId, x700095_g_ScriptId, -1);
end

---------------------------------------------------------------------------------------------------
--申请进入副本
---------------------------------------------------------------------------------------------------
function x700095_ProcAcceptCheck( sceneId, selfId, NPCId )

    return 1
end

----------------------------------------------------------------------------------------------
--点确定后
----------------------------------------------------------------------------------------------
function x700095_ProcAccept( sceneId, selfId )
	local nMode = x700095_GetChanchuFubenFubenTalkMode(sceneId, selfId)

	if nMode<=0 or nMode>3 then
		return
	end

	local nIndex = x700095_GetChanchuFubenIndex(sceneId, selfId)
	local nScriptId = x700095_g_Npc_MonsterData[nIndex].scriptid
	
	nMode = nMode -1
	CallScriptFunction(FUBEN_COMMON_SCRIPT, "OnRequestEnterFuben", sceneId, selfId, nMode, 0, nScriptId);
	
	--写日志
	local msg = format("x700095_ProcAccept 产出, sceneId = %d, name = %s, nMode = %d, nScriptId = %d", sceneId,GetName(sceneId, selfId), nMode,nScriptId);

	WriteLog(1,msg)

end

----------------------------------------------------------------------------------------------
--申请进入副本成功后, 删除Monster
----------------------------------------------------------------------------------------------
function x700095_CheckChanchuApproveRequest(sceneId,selfId, nMode, nScriptId)
	if nScriptId == nil then
		return
	end
	
	--判断是不是产出副本
	local bFind = 0
	for i,item in x700095_g_Npc_MonsterData do
		if item.scriptid == nScriptId then
			bFind = 1
			break;
		end
	end

	if bFind ==0 then
		return
	end

	--判断模式是否匹配
	if nMode == nil then
		return
	end

	if nMode<0 or nMode>1 then
		return
	end

	local nMode_Save = x700095_GetChanchuFubenFubenTalkMode(sceneId, selfId) - 1

	if nMode_Save ~= nMode then
		return
	end

	local npcId = x700095_GetChanchuFubenTalkNPCID(sceneId, selfId)

	if npcId>=0 then
		DeleteMonster( sceneId,npcId )
		--写日志
		local msg = format("x700095_CheckChanchuApproveRequest 申请成功删除NPC, sceneId = %d, name = %s, nMode = %d, nScriptId = %d, npcId=%d", sceneId,GetName(sceneId, selfId), nMode,nScriptId,npcId);

		WriteLog(1,msg)
	end


end


function x700095_SaveChanchuFubenTalkNPCID(sceneId, selfId, nValue)
	SetQuestData(sceneId, selfId, MD_CHANCHU_FUBEN_TALK_NPC_OBJID[1], MD_CHANCHU_FUBEN_TALK_NPC_OBJID[2], MD_CHANCHU_FUBEN_TALK_NPC_OBJID[3], nValue)
end

function x700095_GetChanchuFubenTalkNPCID(sceneId, selfId)
	return GetQuestData(sceneId, selfId, MD_CHANCHU_FUBEN_TALK_NPC_OBJID[1], MD_CHANCHU_FUBEN_TALK_NPC_OBJID[2], MD_CHANCHU_FUBEN_TALK_NPC_OBJID[3])
end

function x700095_SaveChanchuFubenIndex(sceneId, selfId, nValue)
	SetQuestData(sceneId, selfId, MD_CHANCHU_FUBEN_TALK_LEVEL[1], MD_CHANCHU_FUBEN_TALK_LEVEL[2], MD_CHANCHU_FUBEN_TALK_LEVEL[3], nValue)
end

function x700095_GetChanchuFubenIndex(sceneId, selfId)
	return GetQuestData(sceneId, selfId, MD_CHANCHU_FUBEN_TALK_LEVEL[1], MD_CHANCHU_FUBEN_TALK_LEVEL[2], MD_CHANCHU_FUBEN_TALK_LEVEL[3])
end


function x700095_SaveChanchuFubenFubenTalkMode(sceneId, selfId, nValue)
	SetQuestData(sceneId, selfId, MD_CHANCHU_FUBEN_TALK_MODE[1], MD_CHANCHU_FUBEN_TALK_MODE[2], MD_CHANCHU_FUBEN_TALK_MODE[3], nValue)
end

function x700095_GetChanchuFubenFubenTalkMode(sceneId, selfId)
	return GetQuestData(sceneId, selfId, MD_CHANCHU_FUBEN_TALK_MODE[1], MD_CHANCHU_FUBEN_TALK_MODE[2], MD_CHANCHU_FUBEN_TALK_MODE[3])
end


