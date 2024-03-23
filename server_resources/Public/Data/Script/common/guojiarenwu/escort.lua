--内政护送任务 add by 齐亮（090114）

--MisDescBegin

x300519_g_ScriptId = 300519
-- 护送任务ID
x300519_g_EscortMissionID           = 6450
x300519_g_EscortMissionID_End       = 6461
-- 任务名称
x300519_g_MissionName = "【个人】内政任务"
-- 任务目标和任务攻略(送信)
x300519_g_EscortTarget0  = "找到@npc_%s"
-- 任务目标和任务攻略(护送)
x300519_g_EscortTarget1  = "将%s安全护送到@npc_%d那里。"
-- 任务未完成时NPC对话内容
x300519_g_MissionContinue   = "\t你还没将%s护送到@npc_%d处呢！"

--MisDescEnd
-- 任务完成标记
-- 任务参数编号含义
x300519_g_IsComplete        = 0 -- 完成标记
x300519_g_SubMission        = 1 -- 护送任务编号，x300519_g_EscortTable表索引
x300519_g_Phase             = 2 -- 任务阶段：0、寻找请求护送NPC；1、开始护送并把它带到目的NPC处；2、护送完成，回到内政任务发布人处交任务
-- 
x300519_OneRoundCount	= 10
x300519_HighBonusCircleCount = 10		--每日几环高奖
x300519_LevelToCapital	= 300		--大都任务的开始等级
-- 挖掘目标坐标库
x300519_g_EscortTable     = 
{
                            { missionId=6450, escortType = 10,	npcGuid = 138505,	name = "吉尔格",
                            	targetGuid = 138109,	targetname = "巴图",	missionName = "马匹",
                            	finish = "\t谢谢你，总算是送来了，我正要再派人去催呢。",
                            	getmiss = "\t见到你太好了，#Y@myname#W，戍边校尉巴图需要一匹良种战马来让王城斥候能够为他及时提供咸海湾等地的战况，我这里的人手现在很紧张，只好请你帮我把这匹马安全护送到城南门外的戍边校尉@npc_138109那里去了，你愿意帮我这个忙么？",
                            	intro = "\t骑乘繁殖大师@npc_138505需要把战马送往各地，你去看看他那里有什么需要你帮忙的。"
                            }, 
                            { missionId=6451, escortType = 11, npcGuid = 138270, name = "拉木尔", 
                            	targetGuid = 138263, targetname = "驿丞穆合", missionName = "粮车",
                            	finish = "\t又来了一辆粮车，非常感谢你！", 
                            	getmiss = "\t刚才@npc_138263又派人来催促这批粮食了，我这里的实在是脱不开身，你能帮我把这车粮食送到他那里去么？", 
                            	intro = "\t灵芝牧场的粮食是我国粮产的主要来源，你去农场主@npc_138270那里看看有什么需要你帮忙的。" 
                            }, 
                            { missionId=6452, escortType = 12, npcGuid = 138075, name = "耶律峰",
                            	targetGuid = 138055, targetname = "哈森",   missionName = "村民",
                            	finish = "\t啊，这是谁家的孩子走丢了？好的，我会帮他找到父母的！", 
                            	getmiss = "\t你来的正好，#Y@myname#W，我还正在为怎么把这个迷路的小家伙送回家而发愁呢，我的年纪大了，腿脚也不好，上下山都不方便，所以想麻烦你帮我把这个小孩送到王城戍边校尉@npc_138055那里去，我知道你一定不会拒绝。", 
                            	intro = "\t听说忽突忽家族族长@npc_138075遇到了一些麻烦，你去问问他有没有需要帮助的。" 
                            }, 
                            { missionId=6453, escortType = 13, npcGuid = 138182, name = "金矿主哈尔巴拉", 
                            	targetGuid = 138721, targetname = "玄石驿站",   missionName = "矿车",
                            	finish = "\t感谢你能及时把这个送过来，我们正等着用呢。", 
                            	getmiss = "\t#Y@myname#W，你来的正好，@npc_138721那里急需这些矿石，你也知道最近这一带都不太安全，我早听说过你不仅本领高强，而且侠义心肠，这车矿石对你来说应该不是什么麻烦吧？", 
                            	intro = "\t@npc_138182那里总是缺少人手，你能去那边帮忙吗？" 
                            }, 
                            { missionId=6454, escortType = 14, npcGuid = 138110, name = "卓玛",
                            	targetGuid = 138114, targetname = "阿木尔", missionName = "海货",
                            	finish = "\t啊，谢谢你，看来我们今天的晚餐会很丰盛。", 
                            	getmiss = "\t我们这里的海产可是鼎鼎有名，慕名而来的人络绎不绝，上次水晶村村长@npc_138114订购了一些，不过我们最近人手紧张，能麻烦你帮我送去么？", 
                            	intro = "\t珍珠渔港那里海产丰富，你去@npc_138110那边看看有什么可以帮得上的。" 
                            }, 
                            { missionId=6455, escortType = 15, npcGuid = 138518, name = "忽秃鲁",
                            	targetGuid = 138058, targetname = "满都拉图",   missionName = "朝廷圣物", 
                            	finish = "\t送来了么？唔，辛苦你了。", 
                            	getmiss = "\t这车中装的是朝廷的圣物，太子殿下物色了很久才决定请你担当起这个重要的职责，秘密地将它送到@npc_138058那里，千万不要走漏风声或者私自拆开查看，你知道，过度的好奇心有时候是很危险的。", 
                            	intro = "\t我接到一宗任务，但可惜抽不出身来，可否拜托你来替我做这件事呢？去找@npc_138518吧，他会告诉你更多的。" 
                            }, 
                            
                            { missionId=6456, escortType = 10,	npcGuid = 139069,	name = "马全",
                            	targetGuid = 139406,	targetname = "努尔博达",	missionName = "马匹",
                            	finish = "\t马全送来的骏马？很好。",
                            	getmiss = "\t见到你太好了，#Y@myname#W，我帮赵王@npc_139406大人物色了一匹骏马，但是最近生意繁忙，一时脱不开身，你能帮我将这骏马送给他吗？",
                            	intro = "\t大都最有名的骑乘技能大师@npc_139069需要人帮忙，你不妨去他那里看看。"
                            }, 
                            { missionId=6457, escortType = 11, npcGuid = 140900, name = "米粒", 
                            	targetGuid = 139807, targetname = "范遥", missionName = "粮车",
                            	finish = "\t这粮食来的很是时候，非常感谢你！", 
                            	getmiss = "\t刚才明教又派人来催促这批粮食了，我这里的实在是脱不开身，你能帮我把这车粮食送到@npcsp_明教总坛_139807吗？", 
                            	intro = "\t大都@npcsp_米记粮店_140900最近似乎接了一大笔订单，你不妨去他那里看看。" 
                            }, 
                            { missionId=6458, escortType = 41, npcGuid = 140902, name = "虚无道长",
                            	targetGuid = 140400, targetname = "巫山真人",   missionName = "女香客",
                            	finish = "\t竟有如此命数之人？待贫道仔细算上一番。", 
                            	getmiss = "\t你来的正好，#Y@myname#W，方才一位女香客前来问卦，可是我无法看透她的命数，你能把她带到我的师傅巫山真人那里去么？", 
                            	intro = "\t听说@npc_140902颇有神通，如今他正在天桥附近，你不妨去他那里看看。" 
                            }, 
                            { missionId=6459, escortType = 13, npcGuid = 140550, name = "切尔不花", 
                            	targetGuid = 140200, targetname = "范文虎",   missionName = "矿车",
                            	finish = "\t感谢你能及时把这个送过来，我们正等着用呢。", 
                            	getmiss = "\t#Y@myname#W，你来的正好，这批精铜矿是给@npcsp_汉军营_140200打造神臂弩中机括所用，可是我公务缠身，只好麻烦你劳累一番了。", 
                            	intro = "\t最近@npc_140550将军征集了一批精铜，准备给汉军营送去，你去他那里看看有没有什么帮得上忙的。" 
                            }, 
                            { missionId=6460, escortType = 14, npcGuid = 140903, name = "店小二",
                            	targetGuid = 140007, targetname = "张士诚", missionName = "海货",
                            	finish = "\t啊，谢谢你，帮主一定会对盐帮今晚的大宴很满意。", 
                            	getmiss = "\t我们这里的海产可是鼎鼎有名，慕名而来的人络绎不绝，盐帮江东舵主@npc_140007订购了一些，不过我们最近人手紧张，能麻烦你帮我送去么？", 
                            	intro = "\t大都最出名的@npcsp_海产店_140903最近运来了大批的海产，你去那边看看有什么可以帮得上的。" 
                            }, 
                            { missionId=6461, escortType = 15, npcGuid = 140554, name = "李员外",
                            	targetGuid = 139300, targetname = "智障禅师",   missionName = "朝廷圣物", 
                            	finish = "\t送来了么？唔，辛苦你了。", 
                            	getmiss = "\t这车中装的是我敬献给高僧们的香油钱。还要有劳你送到大相国寺的@npc_139300那里，千万不要走漏了风声或者私自拆开查看，你知道，有些事情实在是不可明言。", 
                            	intro = "\t大都的富豪@npc_140554最近想请大相国寺的高僧们做一场法事。你去他那里看看吧。" 
                            }, 
}                                                                                                   

-- 显示完成信息
function x300519_OnCanCompleteMission( sceneId, selfId, targetId, MissionId)
    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y"..x300519_g_MissionName)
        
        AddQuestText( sceneId, "\t交给你的事都办完了？" )
    EndQuestEvent()

	DispatchQuestInfoNM( sceneId, selfId, targetId, x300519_g_ScriptId, MissionId)
end

-- 显示任务未完成时NPC的对话信息
function x300519_ShowMissionContinueInfo( sceneId, selfId, targetId, MissionId)

    local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
    local id = GetQuestParam( sceneId, selfId, misIndex, x300519_g_SubMission)
    if (id == nil or id < 1 or id > getn(x300519_g_EscortTable)) then
		return
    end
    -- 接任务NPC的GUID
    local npcGuid = x300519_g_EscortTable[id].npcGuid
    -- 护送目标NPC的GUID
    local destGuid = x300519_g_EscortTable[id].targetGuid
    -- 点击NPC的GUID
    local targetGuid = GetMonsterGUID( sceneId, targetId)
    local phase = GetQuestParam( sceneId, selfId, misIndex, x300519_g_Phase)
	local submitguid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex )

    if npcGuid == targetGuid then
	--领取护送的NPC
	--print("busid"..GetBusId(sceneId, selfId))
	if (phase ~= 0) then
		return
	end
	
	BeginQuestEvent( sceneId)
		-- 任务名称
		AddQuestText( sceneId, "#Y"..x300519_g_MissionName)
		-- 任务描述
		AddQuestText( sceneId, "#Y任务描述：" )
		AddQuestText( sceneId, x300519_g_EscortTable[id].getmiss)
		AddQuestText( sceneId, " " )
		-- 任务目标
		AddQuestText( sceneId, "#Y任务目标：" )
		AddQuestText( sceneId, format( x300519_g_EscortTarget1, x300519_g_EscortTable[id].missionName, x300519_g_EscortTable[id].targetGuid) )

		local curlevel = GetLevel(sceneId, selfId)
		local exp = x300519_GetExpAward ( sceneId, selfId, curlevel );
		local money,shengw = x300519_GetMoneyAward ( sceneId, selfId, curlevel );

		if(exp > 0) then
			AddQuestExpBonus(sceneId, exp)
		end
		if(money > 0) then
			AddQuestMoneyBonus2(sceneId, money)
		end

		if(shengw > 0) then
			AddQuestMoneyBonus5(sceneId, shengw)
		end

	EndQuestEvent()
	DispatchQuestContinueInfoNM( sceneId, selfId, targetId, x300519_g_ScriptId, MissionId )

    elseif targetGuid == destGuid then -- 护送目的NPC
	--print("busid"..GetBusId(sceneId, selfId))
        -- 显示完成护送信息
	if (phase ~= 1) then
		return
	end
	
	if GetBusId(sceneId, selfId) <= 0 or IsValidMyselfBus(sceneId, selfId, MissionId) == 0 then	--护送bus必须在身边
		QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId)
	else
	        BeginQuestEvent( sceneId)
			AddQuestText( sceneId, "#Y"..x300519_g_MissionName)
			AddQuestText( sceneId, x300519_g_EscortTable[id].finish)
		EndQuestEvent()
		DispatchQuestContinueInfoNM( sceneId, selfId, targetId, x300519_g_ScriptId, MissionId)
	end
    elseif targetGuid == submitguid then
        BeginQuestEvent( sceneId)
            -- 任务名称
            AddQuestText( sceneId, "#Y"..x300519_g_MissionName)

		if (phase == 1) then
			AddQuestText(sceneId, format(x300519_g_MissionContinue, x300519_g_EscortTable[id].missionName, x300519_g_EscortTable[id].targetGuid))
		elseif (phase == 0) then
	            AddQuestText( sceneId, "\t交给你的事办完了？" )		--要改
		end
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, targetId)
    end
end

-- 创建要护送的Bus后，在这里设置使其能自动跟随玩家
function x300519_OnIntoBusEvent( sceneId, selfId, targetId)
    --print( "x300519_OnIntoBusEvent" )
	local IsOwner = IsTheBusOwner( sceneId, selfId, targetId)
	if IsOwner == 1 then
		-- 如果是玩家本人设置跟随
		AddBusMember( sceneId, selfId, targetId)
	end
end

function x300519_OnIntoBusAfter( sceneId, selfId, BusID)
    --print( "*****x300519_OnIntoBusAfter*****" )
end

function x300519_OnLeaveBusEvent( sceneId, selfId, BusId)
    --print( "离开Bus" )
end

function x300519_OnDie( sceneId, BusId, idKiller)
	local selfId = GetBusMemberObjId(sceneId,BusId,0)	
	if (selfId == -1) then
		return
	end
	local MissionId = x300519_GetRandMissionId(sceneId, selfId);
	-- 设置任务数据
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	-- 完成标记
	SetQuestByIndex( sceneId, selfId, misIndex, x300519_g_IsComplete, 0)
	-- 当前任务阶段标记，每个阶段下的任务目标都不一样：0、寻找请求护送NPC；1、开始护送并把它带到目的NPC处；2、护送完成，回到内政任务发布人处交任务
	SetQuestByIndex( sceneId, selfId, misIndex, x300519_g_Phase, 0)
	-- 更新Q面板
	x300519_ProcQuestLogRefresh( sceneId, selfId, MissionId, misIndex)
	Msg2Player(sceneId, selfId, "护送目标已经死亡，请重新接取任务", 8, 3)
end

-- 提交任务，返回0表示失败，返回1成功
function x300519_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId, farScriptId, constMD_Rand, retMissionId)
    return 1
end

-- 显示任务信息
function x300519_ShowMissionInfo( sceneId, selfId, targetId, MissionId)
    
	local rand = 1
	-- 得到子任务对应的护送目标
	for i, oneitem in x300519_g_EscortTable do
		if oneitem.missionId == MissionId then
			rand = i
			break;
		end
	end
	-- 保存护送任务目标索引
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	SetQuestByIndex( sceneId, selfId, misIndex, x300519_g_SubMission, rand)
    
    BeginQuestEvent( sceneId)
        -- 任务名称
        AddQuestText( sceneId, "#Y"..x300519_g_MissionName)
 
        -- 任务描述
        AddQuestText( sceneId, "#Y任务描述：" )
        AddQuestText( sceneId, x300519_g_EscortTable[rand].intro)
        AddQuestText( sceneId, " " )
        -- 任务目标
        AddQuestText( sceneId, "#Y任务目标：" )
        AddQuestText( sceneId, format( x300519_g_EscortTarget0, x300519_g_EscortTable[rand].npcGuid) )

    EndQuestEvent()
    DispatchQuestInfoNM( sceneId, selfId, targetId, x300519_g_ScriptId, MissionId, 1)
end

function x300519_CheckIfCanSubmit( sceneId, selfId, targetId, MissionId, misIndex)
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then
		return 0
	end

	local phase = GetQuestParam( sceneId, selfId, misIndex, x300519_g_Phase)
	if phase == 2 then
		return 1
	else
		return 0
	end
end

--处理中间环节的提交，或返回1代表最后环节的提交，由主脚本处理
function x300519_ProcQuestSubmitOrContinue( sceneId, selfId, targetId, MissionId)

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	local phase = GetQuestParam( sceneId, selfId, misIndex, x300519_g_Phase)

	if phase == 0 then
		if IsBusMember(sceneId, selfId) == 1 then
			local strTip = "你已处于护送状态，无法领取新的护送任务！"
			Msg2Player(sceneId, selfId, strTip, 8, 3)				
			Msg2Player(sceneId, selfId, strTip, 8, 2)
			return 0
		end

		local PosX,PosZ = GetWorldPos( sceneId, selfId)
		-- 创建要护送的Bus
		local id = GetQuestParam( sceneId, selfId, misIndex, x300519_g_SubMission)
		if (id == nil or id < 1 or id > getn(x300519_g_EscortTable)) then
			return 0
		end
		local ObjID = CreateBus( sceneId, x300519_g_EscortTable[id].escortType, PosX, PosZ, 3, 3, 300519, selfId, 1210,MissionId,targetId)
		return 0

	elseif phase == 1 then
		-- 获得护送对象的Guid
		-- 删除护送对象
		local busGuid = GetBusId(sceneId, selfId)
		if (busGuid < 0) or (IsObjValid (sceneId,busGuid) ~= 1) then						--玩家没有bus
			return	0			
		end
		if (MissionId ~= GetBusQuestID(sceneId, busGuid)) then	--如果玩家当前bus不是任务所需要的bus,任务放弃
			return	0			
		end
		DeleteBus( sceneId, busGuid, 1)
		-- update phase
		SetQuestByIndex( sceneId, selfId, misIndex, x300519_g_Phase, 2)
		-- set mission finish
		SetQuestByIndex( sceneId, selfId, misIndex, x300519_g_IsComplete, 1)
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
		Msg2Player(sceneId, selfId, "任务已经完成，快点回去汇报吧！", 8, 3)
		QuestCom( sceneId, selfId, MissionId)
		-- update Q panel
		x300519_ProcQuestLogRefresh( sceneId, selfId, MissionId, misIndex)
		return 0
	elseif phase == 2 then
		return 1
	else
		return 0
	end
end

function x300519_OnCreateBusOK(sceneId,selfId,busId,targetId,MissionId)	

		local camp = GetCurCamp(sceneId, selfId)
		SetBusCurCamp(sceneId, busId, camp)
		SetBusTimerTick(sceneId , busId, 1000)
		SetBusWaitTime(sceneId , busId, 300)
		SetBusQuestID(sceneId, busId, MissionId)
		
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
		
		SetQuestByIndex( sceneId, selfId, misIndex, x300519_g_Phase, 1)		
		-- update Q panel
		x300519_ProcQuestLogRefresh( sceneId, selfId, MissionId, misIndex)	
end

--由300501调用
function x300519_AfterAccept( sceneId, selfId, targetId, MissionId, misIndex)
	-- 当前任务阶段标记，每个阶段下的任务目标都不一样：0、寻找请求护送NPC；1、开始护送并把它带到目的NPC处；2、护送完成，回到内政任务发布人处交任务
	SetQuestByIndex( sceneId, selfId, misIndex, x300519_g_Phase, 0)
	-- 更新Q面板
	x300519_ProcQuestLogRefresh( sceneId, selfId, MissionId, misIndex)
end

function x300519_ProcQuestAttach( sceneId, selfId, targetId, npcGuid, misIndex, MissionId)

	MissionId = x300519_GetRandMissionId(sceneId, selfId)
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then
		return 0
	end

	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);

	local submitguid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex )
	--如果是任务提交人，显示选项
	if submitguid ~= -1 and submitguid == npcGuid then	
		local state = GetQuestStateNM(sceneId, selfId, npcGuid, MissionId);
		AddQuestTextNM(sceneId, selfId, npcGuid, MissionId, state, -1);
		return 1
	end

	local id = GetQuestParam( sceneId, selfId, misIndex, x300519_g_SubMission)
	if (id == nil or id < 1 or id > getn(x300519_g_EscortTable) ) then
		return 0
	end
	-- 根据保存的护送任务号得到源和目的NPC的GUID
	local srcNpc = x300519_g_EscortTable[id].npcGuid
	local dstNpc = x300519_g_EscortTable[id].targetGuid
	if npcGuid == srcNpc then -- 请求护送NPC
		local phase = GetQuestParam( sceneId, selfId, misIndex, x300519_g_Phase)
		if phase == 0 then
			AddQuestNumText( sceneId, MissionId, x300519_g_MissionName, 13)
		end
	elseif npcGuid == dstNpc then -- 护送目标NPC
		local phase = GetQuestParam( sceneId, selfId, misIndex, x300519_g_Phase)
		if phase == 1 then
			AddQuestNumText( sceneId, MissionId, x300519_g_MissionName, 13)
		end
	end
    return 1
end

function x300519_ProcQuestLogRefresh( sceneId, selfId, MissionId, misIndex)

    
    
    if MissionId== nil or MissionId < 0 then
        return 0
    end
    
    if IsHaveQuestNM(sceneId,selfId,MissionId) <= 0 then
        return 0
    end
        
    local misIndex = GetQuestIndexByID(sceneId,selfId,MissionId)
    local id = GetQuestParam( sceneId, selfId, misIndex, x300519_g_SubMission)
    if (id == nil or id < 1 or id > getn(x300519_g_EscortTable)) then
		return 0
    end
    local phase = GetQuestParam( sceneId, selfId, misIndex, x300519_g_Phase)

	local strName;
	strName = x300519_g_MissionName;
	local circle = x300519_GetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE)
	if (circle >= x300519_OneRoundCount) then
		circle = 1
	else
		circle = circle + 1
	end
	strName = strName.."("..circle;
	strName = strName.."/"..x300519_OneRoundCount;
	strName = strName..")";

	local reply_npcid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex );
	local strReplyNPC = "@npc_"..reply_npcid
	BeginQuestEvent(sceneId)
	    if phase == 0 then -- 找到提供护送目标的NPC
		--MissionTitle, MissionName, MissionTarget, MissionNPC, MissionProcess, MissionComment, MissionTip
		AddQuestLogCustomText( sceneId,
					"",                             -- 标题
					strName,          -- 任务名字
					format( "  "..x300519_g_EscortTarget0, x300519_g_EscortTable[id].npcGuid),
					strReplyNPC,             --任务NPC
					format( x300519_g_EscortTarget0, x300519_g_EscortTable[id].npcGuid),
					x300519_g_EscortTable[id].intro,
					"" )
	    elseif phase == 1 then
		AddQuestLogCustomText( sceneId,
					"",                             -- 标题
					strName,          -- 任务名字
					format( "  "..x300519_g_EscortTarget1, x300519_g_EscortTable[id].missionName, x300519_g_EscortTable[id].targetGuid),
					strReplyNPC,             --任务NPC
					format( x300519_g_EscortTarget1, x300519_g_EscortTable[id].missionName, x300519_g_EscortTable[id].targetGuid),
					x300519_g_EscortTable[id].getmiss,
					"注意途中不要离护送目标太远" )
	    elseif phase == 2 then
		AddQuestLogCustomText( sceneId,
					"",                             -- 标题
					strName,          -- 任务名字
					"  任务完成，回复"..strReplyNPC,
					strReplyNPC,             --任务NPC
					"任务完成，回复"..strReplyNPC,
					x300519_g_EscortTable[id].finish,
					"" )
	    end
		
		local phase = GetQuestParam( sceneId, selfId, misIndex, x300519_g_Phase)
		if (phase ~= 0) then
			--任务奖励
			local curlevel = GetLevel(sceneId, selfId)
			local exp = x300519_GetExpAward ( sceneId, selfId, curlevel );
			local money,shengw = x300519_GetMoneyAward ( sceneId, selfId, curlevel );
			if(exp > 0) then
				AddQuestExpBonus(sceneId, exp)
			end
			if(money > 0) then
				AddQuestMoneyBonus2(sceneId, money)
			end
			if(shengw > 0) then
				AddQuestMoneyBonus5(sceneId, shengw)
			end
		end

	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

-- 放弃任务处理
function x300519_ProcQuestAbandon(sceneId, selfId, MissionId)
	MissionId = x300519_GetRandMissionId(sceneId, selfId)

	local busGuid = GetBusId(sceneId, selfId)
	if (busGuid > 0) and (IsObjValid (sceneId,busGuid) == 1)then
		if (MissionId == GetBusQuestID(sceneId, busGuid)) then	--如果玩家当前bus不是任务所需要的bus,任务放弃
			DeleteBus( sceneId, busGuid, 1)
		end
	end

	CallScriptFunction( 300501, "ProcQuestAbandon", sceneId, selfId, MissionId)
end

function x300519_GetRandMissionId(sceneId, selfId)
	return x300519_GetMD(sceneId, selfId, MD_GUOJIARENWU_RANDMISSIONID)
end

function x300519_OnBusStopWhenOwnerFarAway(sceneId, selfId)

	local strText = "你离护送目标太远，护送目标停止"

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)

	Msg2Player(sceneId,selfId,strText,8,2)
end

function x300519_SetMD(sceneId, selfId, MDNAME, value)
	SetQuestData(sceneId, selfId, MDNAME[1], MDNAME[2], MDNAME[3], value);
end

function x300519_GetMD(sceneId, selfId, MDNAME)

	return GetQuestData(sceneId, selfId, MDNAME[1], MDNAME[2], MDNAME[3])
end

function x300519_OnWaitTimeOut(sceneId,BusId)
	local selfId = GetBusMemberObjId(sceneId,BusId,0)	
	if (selfId == -1) then
		--玩家不在线
		if (IsObjValid (sceneId,BusId) == 1) then
		    DeleteBus(sceneId, BusId,1)
		end
		return
	end

	local MissionId = x300519_GetRandMissionId(sceneId, selfId)
	if (MissionId ~= GetBusQuestID(sceneId, BusId)) then	--如果玩家当前bus不是任务所需要的bus,不处理
		return
	end

	DeleteBus(sceneId, BusId,1)
	x300519_RollbackBusMission (sceneId, selfId, MissionId)

end

function x300519_RollbackBusMission(sceneId, selfId, MissionId)

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)

	--只有处于阶段1才能回滚
	if (1 ~= GetQuestParam( sceneId, selfId, misIndex, x300519_g_Phase)) then
		return
	end

	-- 完成标记
	SetQuestByIndex( sceneId, selfId, misIndex, x300519_g_IsComplete, 0)
	-- 当前任务阶段标记，每个阶段下的任务目标都不一样：0、寻找请求护送NPC；1、开始护送并把它带到目的NPC处；2、护送完成，回到内政任务发布人处交任务
	SetQuestByIndex( sceneId, selfId, misIndex, x300519_g_Phase, 0)
	-- 更新Q面板
	x300519_ProcQuestLogRefresh( sceneId, selfId, MissionId)

	local strText = "由于你离开护送目标时间过久，你的护送目标消失了，请重新接取任务"
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)

	Msg2Player(sceneId,selfId,strText,8,2)

end
function x300519_ClearBusMission(sceneId, selfId)
	local MissionId = x300519_GetRandMissionId(sceneId, selfId)
	if MissionId >= x300519_g_EscortMissionID and MissionId <= x300519_g_EscortMissionID_End then	--护送
		x300519_RollbackBusMission (sceneId, selfId, MissionId)
	end
end

function x300519_ProcEventEntry( sceneId, selfId, targetId, MissionId)
	return 1
end

--检查日期有没有变化，并重置高奖次数，并保存新的日期
function x300519_CheckDayChanged(sceneId, selfId)

	local lastDay = x300519_GetMD(sceneId, selfId, MD_GUOJIARENWU_LASTDAY)
	local today = GetDayOfYear()
	if lastDay ~= today then	--日期变化
		x300519_SetMD(sceneId, selfId, MD_GUOJIARENWU_LASTDAY, today)	
		x300519_SetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH, 0)
	end
end

--经验奖励
function x300519_GetExpAward(sceneId, selfId, startlevel)

	x300519_CheckDayChanged(sceneId, selfId)
	local circle = x300519_GetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE)
	local highcircle = x300519_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH)
	
	circle = circle + 1
	if (circle > x300519_OneRoundCount) then
		circle = 1
	end

	highcircle = highcircle + 1

	local exp_rate
	if GetLevel(sceneId, selfId) >= 60 then
		exp_rate = 3650
	else
		exp_rate = 2800
	end

	local BonusExp = startlevel * exp_rate * (circle * 2 - 1) / 200
	if (highcircle <= x300519_HighBonusCircleCount) then
		BonusExp = BonusExp * 5
	end
    -- 环数减半，所以经验翻倍
    BonusExp = BonusExp * 2
	return BonusExp;

end

--金钱奖励
function x300519_GetMoneyAward(sceneId, selfId, startlevel)

	x300519_CheckDayChanged(sceneId, selfId)
	local circle = x300519_GetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE)
	local highcircle = x300519_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH)

	circle = circle + 1
	if (circle > x300519_OneRoundCount) then
		circle = 1
	end

	highcircle = highcircle + 1

	local BonusMoney = startlevel
	local shengw = 5
	if (highcircle <= x300519_HighBonusCircleCount) then
		BonusMoney = BonusMoney * 5
		shengw = 25
	end
	return BonusMoney, shengw;
end


function x300519_CheckSubmitNPC( sceneId,idMission,npcGUID )

	for i,item in x300519_g_EscortTable do
		if item.missionId == idMission then
			if item.npcGuid == npcGUID or item.targetGuid == npcGUID then
				return 1
			else
				return 0
			end
		end
	end
	
	return 0
end