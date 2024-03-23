--MisDescBegin

x270352_g_ScriptId 					= 270352                  --脚本ID
x270352_g_MissionId 				= 1392                    --任务ID

x270352_g_MissionKind 				= 1                       --任务类型
x270352_g_LevelLess					= 20                      --场景开放等级  <=0 表示不限制

x270352_g_MissionName				= "【个人】三环任务(通缉令)"                --任务名称(512)
x270352_g_MissionTarget				= "  到%s消灭%s(%d/1)"          --任务目标
x270352_g_MissionInfo				= "\t杀死@npc_72004的@npc_72005,找到@npc_137600"            --任务信息
x270352_g_ContinueInfo				= "\t除掉那些野兽了么？"  --任务继续信息
x270352_g_MissionCompleted			= "\t这么快就回来了？真是不错！\n\t不过，我还是建议你组织一支3人以上的队伍，在我这里挑战#G三环任务#W或#G三环任务（三番令）#W，获得更丰厚的奖励！"  --任务完成信息
x270352_g_MissionCompleted1			= "\t你选择了使用悬赏令完成任务，你将会获得#G5倍#W的奖励，同时消耗#G5环#W任务次数！"  --任务完成信息
x270352_g_MissionHelp				= ""   --任务提示信息

--目标
x270352_g_ExtTarget					= { {type=20,n=10 ,target=""} }


--奖励
x270352_g_ExpBonus					= { 90, 117, 162 , 297 }                    	--奖励：经验 （数值填0，字符串为空，表示没有该项奖励）
x270352_g_BonusItem					= {}	--奖励：物品

x270352_g_BonusMoney1               = 0    --任务奖励绑定银币
x270352_g_BonusMoney2               = 0   --任务现银奖励系数
x270352_g_BonusMoney3               = 0    --任务奖励绑定金币
x270352_g_BonusMoney4               = 0  --任务奖励朝廷声望
x270352_g_BonusMoney5               = 0  --任务奖励江湖声望
x270352_g_BonusMoney6               = 0  --任务奖励荣誉

x270352_g_BonusChoiceItem           = {}


--MisDescEnd

--任务目标顺序
x270352_MP_TARGET1					= 1         -- 要杀怪1
x270352_MP_TARGET2					= 2         -- 要杀怪2
x270352_MP_TARGET3					= 3         -- 要杀怪3
x270352_MP_TARGET4					= 4         -- 
x270352_MP_TARGET5					= 5         -- 
x270352_MP_TARGET6					= 6         -- 
x270352_MP_COMPLETE                 = 7         -- 玩家接任务时的等级
x270352_MP_ISCOMPLETE				= 0	        -- 代表完成 0未完成， 1完成

-- 接受任务提示
x270352_g_strAcceptMission          = "您接受了任务：【个人】三环任务(通缉令)"
-- 放弃任务提示
x270352_g_strAbandonMission         = "您放弃了任务：【个人】三环任务(通缉令)"
-- 完成任务提示
x270352_g_strFinishMission          = "您完成了任务：【个人】三环任务(通缉令)"

--任务目标ID
x270352_TARGET_OBJID1				= 9500
x270352_TARGET_OBJID2				= -2
x270352_TARGET_OBJID3				= -2
x270352_TARGET_OBJID4				= -2
x270352_TARGET_OBJID5				= -2

--任务物品
x270352_TARGET_ITEMID1				= -2
-- 放弃任务后禁止再领任务的时限(分钟)
x270352_g_PunishTime                = 2

-- 接受任务的玩家最小等级
x270352_g_PlayerMinLevel            = 20
-- 接受任务的玩家最大等级
x270352_g_PlayerMaxLevel            = 150

x270352_SubmitNPCGUID				= 129041	--交任务NPC GUID

-- 任务描述
x270352_g_MissionDescription        = "\t#Y@myname#W，见到你太好了，我正有事要找你呢！\n\t最近，有许多怪物从三环副本中逃了出来，四处作恶，闹得整个王国人心惶惶的。你是否愿意帮我们除去这些怪物？\n（每次接取本任务需要消耗一个#G通缉令#W，#G通缉令#W可在王城贸易区杂货商人处购买。）\n \n#G小提示：\n等级相当（相差5级以内）的玩家一起组队领取本任务，任务目标相同。#W"
-- 任务攻略
x270352_g_MissionBook               = "组队进行任务可以极大的提高完成任务的速度"
-- 任务继续信息
x270352_g_MissionContinue           = "\t你还没杀掉那只怪物吗？"
-- 任务目标之一描述
x270352_g_strMissionTarget          = "  使用背包中的@item_13810160#W搜寻并消灭在%s的#G%s#W(%d/1)"
-- 
x270352_g_ItemID                    = 11990016 
x270352_g_AcceptItemID              = 11990017		--消耗
x270352_g_SubmitItemID              = 13810160--11990018		--领取任务后添加
-- 
x270352_g_MonsterTable              = {
                                        { minLevel = 20, maxLevel = 29, monList = { { id = 3840, objid = 400040, mapid = 258, name = "角木熊星",     Place = "西方" ,		posName = "@npc_4000402"  }, { id = 3841, objid = 400041, mapid = 258, name = "奎木狼星",   Place = "东方" ,	 posName = "@npc_4000412"  }, { id = 3842, objid = 400042, mapid = 258, name = "毕月乌星",   Place = "东北方" , posName = "@npc_4000422"	}, { id = 3843, objid = 400043, mapid = 258, name = "翼火蛇星",   		Place = "北方" ,   posName = "@npc_4000432"  }, { id = 3844,objid = 400044, mapid = 258, name = "胃土彘星", Place = "北方" ,posName = "@npc_4000442"  }, { id = 3845,objid = 400045, mapid = 258, name = "女土蝠星", Place = "西北方" ,posName = "@npc_4000452" } }},  
                                        { minLevel = 30, maxLevel = 34, monList = { { id = 3846, objid = 400046, mapid = 304, name = "鬼金羊星",     Place = "南方" ,		posName = "@npc_4000462"  }, { id = 3847, objid = 400047, mapid = 304, name = "尾火虎星",   Place = "西南方" , posName = "@npc_4000472"	 }, { id = 3849, objid = 400049, mapid = 304, name = "龙堡守卫",   Place = "北方" ,		posName = "@npc_4000492"  }, { id = 3850, objid = 400050, mapid = 304, name = "蓝虺", 					Place = "东方" ,   posName = "@npc_4000502"  } }},
                                        { minLevel = 35, maxLevel = 39, monList = { { id = 3849, objid = 400049, mapid = 304, name = "龙堡守卫",     Place = "北方" ,		posName = "@npc_4000492"  }, { id = 3850, objid = 400050, mapid = 304, name = "蓝虺", 			Place = "东方" ,	 posName = "@npc_4000502"  }, { id = 3852, objid = 400052, mapid = 305, name = "长爪翼龙",   Place = "东方" ,   posName = "@npc_4000522"	}, { id = 3853, objid = 400053, mapid = 305, name = "厌火异兽",   		Place = "西南方" , posName = "@npc_4000532"  } }}, 
                                        { minLevel = 40, maxLevel = 44, monList = { { id = 3852, objid = 400052, mapid = 305, name = "长爪翼龙",     Place = "东方" ,   posName = "@npc_4000522"  }, { id = 3853, objid = 400053, mapid = 305, name = "厌火异兽",   Place = "西南方" , posName = "@npc_4000532"	 }, { id = 3854, objid = 400054, mapid = 305, name = "探宝矿工",   Place = "东方" ,		posName = "@npc_4000542"  }, { id = 3856, objid = 400056, mapid = 305, name = "地穴恶魔",   		Place = "东北方" , posName = "@npc_4000562"  } }}, 
                                        { minLevel = 45, maxLevel = 49, monList = { { id = 3854, objid = 400054, mapid = 305, name = "探宝矿工",     Place = "东方" ,		posName = "@npc_4000542"  }, { id = 3856, objid = 400056, mapid = 305, name = "地穴恶魔",   Place = "东北方" , posName = "@npc_4000562"	 }, { id = 3858, objid = 400058, mapid = 306, name = "国王子民",   Place = "东南方" , posName = "@npc_4000582"	}, { id = 3859, objid = 400059, mapid = 306, name = "狼人布鲁斯", 		Place = "西方" ,	 posName = "@npc_4000592"	 } }}, 
                                        { minLevel = 50, maxLevel = 54, monList = { { id = 3858, objid = 400058, mapid = 306, name = "国王子民",     Place = "东南方" , posName = "@npc_4000582"	}, { id = 3859, objid = 400059, mapid = 306, name = "狼人布鲁斯", Place = "西方" ,	 posName = "@npc_4000592"	 }, { id = 3862, objid = 400062, mapid = 306, name = "血蝙蝠", 		 Place = "东方" ,		posName = "@npc_4000622"  }, { id = 3863, objid = 400063, mapid = 306, name = "死亡骑士",   		Place = "东北方" , posName = "@npc_4000632"  } }}, 
                                        { minLevel = 55, maxLevel = 59, monList = { { id = 3862, objid = 400062, mapid = 306, name = "血蝙蝠", 		   Place = "东方" ,		posName = "@npc_4000622"  }, { id = 3863, objid = 400063, mapid = 306, name = "死亡骑士",   Place = "东北方" , posName = "@npc_4000632"	 }, { id = 3864, objid = 400064, mapid = 307, name = "喷毒红蛛",   Place = "东南方" , posName = "@npc_4000642"	}, { id = 3866, objid = 400066, mapid = 307, name = "巨钳毒蝎",   		Place = "西北方" , posName = "@npc_4000662"  } }}, 
                                        { minLevel = 60, maxLevel = 64, monList = { { id = 3864, objid = 400064, mapid = 307, name = "喷毒红蛛",     Place = "东南方" , posName = "@npc_4000642"  }, { id = 3866, objid = 400066, mapid = 307, name = "巨钳毒蝎", 	Place = "东北方" , posName = "@npc_4000662"  }, { id = 3868, objid = 400068, mapid = 307, name = "祝家庄护院", Place = "东方" ,		posName = "@npc_4000682"  }, { id = 3869, objid = 400069, mapid = 307, name = "祝家庄乡勇", 		Place = "东北方" , posName = "@npc_4000692"  } }}, 
 																				{ minLevel = 65, maxLevel = 69, monList = { { id = 3868, objid = 400068, mapid = 307, name = "祝家庄护院",   Place = "东方" ,		posName = "@npc_4000682"	}, { id = 3869, objid = 400069, mapid = 307, name = "祝家庄乡勇", Place = "东北方" , posName = "@npc_4000692"  }, { id = 3870, objid = 400070, mapid = 308, name = "冰之灵", 		 Place = "中部" ,		posName = "@npc_4000702"  }, { id = 3871, objid = 400071, mapid = 308, name = "炎之灵", 				Place = "东方" ,	 posName = "@npc_4000712"  } }}, 
                                        { minLevel = 70, maxLevel = 74, monList = { { id = 3870, objid = 400070, mapid = 308, name = "冰之灵",       Place = "中部" ,		posName = "@npc_4000702"  }, { id = 3871, objid = 400071, mapid = 308, name = "炎之灵", 		Place = "东方" ,	 posName = "@npc_4000712"  }, { id = 3872, objid = 400072, mapid = 308, name = "地之灵", 		 Place = "北方" ,		posName = "@npc_4000722"  }, { id = 3873, objid = 400073, mapid = 308, name = "突厥蛮卫",   		Place = "东北方" , posName = "@npc_4000732"  } }}, 
                                        { minLevel = 75, maxLevel = 79, monList = { { id = 3872, objid = 400072, mapid = 308, name = "地之灵",       Place = "北方" ,		posName = "@npc_4000722"  }, { id = 3873, objid = 400073, mapid = 308, name = "突厥蛮卫", 	Place = "东北方" , posName = "@npc_4000732"  }, { id = 3874, objid = 400074, mapid = 309, name = "聚之灵", 		 Place = "西北方" , posName = "@npc_4000742"  }, { id = 3875, objid = 400075, mapid = 309, name = "突厥禁军", 			Place = "东北方" , posName = "@npc_4000752"  } }}, 
                                        { minLevel = 80, maxLevel = 84, monList = { { id = 3874, objid = 400074, mapid = 309, name = "聚之灵",       Place = "西北方" , posName = "@npc_4000742"  }, { id = 3875, objid = 400075, mapid = 309, name = "突厥禁军", 	Place = "东北方" , posName = "@npc_4000752"  }, { id = 3876, objid = 400076, mapid = 309, name = "扈家庄庄丁", Place = "西南方" ,	posName = "@npc_4000762"  }, { id = 3877, objid = 400077, mapid = 309, name = "祝家庄庄丁", 		Place = "东方" ,	 posName = "@npc_4000772"  } }}, 
                                        { minLevel = 85, maxLevel = 89, monList = { { id = 3876, objid = 400076, mapid = 309, name = "扈家庄庄丁",   Place = "西南方" ,	posName = "@npc_4000762"  }, { id = 3877, objid = 400077, mapid = 309, name = "祝家庄庄丁", Place = "东方" ,	 posName = "@npc_4000772"  }, { id = 3878, objid = 400078, mapid = 310, name = "县衙官兵",   Place = "中部" ,		posName = "@npc_4000782"  }, { id = 3879, objid = 400079, mapid = 310, name = "突厥蛮兵",   		Place = "中部" ,	 posName = "@npc_4000792"  } }}, 
                                        { minLevel = 90, maxLevel = 94, monList = { { id = 3878, objid = 400078, mapid = 310, name = "县衙官兵",     Place = "中部" ,		posName = "@npc_4000782"  }, { id = 3879, objid = 400079, mapid = 310, name = "突厥蛮兵", 	Place = "中部" ,	 posName = "@npc_4000792"  }, { id = 3880, objid = 400080, mapid = 310, name = "灰壳蟹", 		 Place = "北方" ,		posName = "@npc_4000802"  }, { id = 3881, objid = 400081, mapid = 310, name = "金国怯薛军", 		Place = "中部" ,   posName = "@npc_4000812"  } }}, 
                                        { minLevel = 95, maxLevel = 99, monList = { { id = 3880, objid = 400080, mapid = 310, name = "灰壳蟹",       Place = "北方" ,		posName = "@npc_4000802"  }, { id = 3881, objid = 400081, mapid = 310, name = "金国怯薛军", Place = "中部" ,	 posName = "@npc_4000812"  },	{ id = 3882, objid = 400082, mapid = 311, name = "金国质子军", Place = "西北方" , posName = "@npc_4000822"  }, { id = 3883, objid = 400083, mapid = 311, name = "随军巫师",   		Place = "东北方" , posName = "@npc_4000832"  } }}, 
                                        { minLevel = 100,maxLevel =160, monList = { { id = 3882, objid = 400082, mapid = 311, name = "金国质子军",   Place = "西北方" , posName = "@npc_4000822"  }, { id = 3883, objid = 400083, mapid = 311, name = "随军巫师", 	Place = "东北方" , posName = "@npc_4000832"  }, { id = 3884, objid = 400084, mapid = 311, name = "神机营精锐", Place = "西方" ,		posName = "@npc_4000842"  }, { id = 3885, objid = 400085, mapid = 311, name = "金国乌月营斥候", Place = "东南方" , posName = "@npc_4000852"  } }},
}

--**********************************
--列举事件
--**********************************
function x270352_ProcEnumEvent( sceneId, selfId, NPCId, MissionId )

	local level = GetLevel( sceneId,selfId)
	if(level < x270352_g_PlayerMinLevel) then
		 return 1;
	end

    local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x270352_g_MissionId);
    if(bHaveMission <= 0 and level >= x270352_g_PlayerMinLevel) then
        local state = GetQuestStateNM(sceneId,selfId,NPCId,x270352_g_MissionId)
        AddQuestNumText(sceneId,x270352_g_MissionId,x270352_g_MissionName,state, 30);
    end
end

--**********************************
--任务入口函数
--**********************************
function x270352_ProcEventEntry(sceneId, selfId, NPCId, MissionId, nExtIdx)	--点击该任务后执行此脚本
	--print("nExtIdx = ",nExtIdx)
	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x270352_g_MissionId)
	if( bHaveMission > 0) then
		local bDone = x270352_CheckSubmit(sceneId, selfId, NPCId)
		if(bDone > 0) then
			if nExtIdx ~= -1 then
				x270352_DispatchCompletedInfo( sceneId, selfId, NPCId, nExtIdx) --完成任务显示
			end
		else
			if nExtIdx ~= -1 then
				x270352_DispatchContinueInfo( sceneId, selfId, NPCId ) --未完成任务显示
			end
			if sceneId ~=250 then
						SetMonsterCamp(sceneId,NPCId,21)                                                        
						NpcTalk(sceneId, NPCId, "既然事已败露，只好和你拼个鱼死网破！", -1)                     
						BeginQuestEvent(sceneId)                                                                
						AddQuestText(sceneId,"\t面前的怪物突然露出一副凶恶的嘴脸，向你冲来！")                  
						EndQuestEvent()                                                                         
						DispatchQuestEventList(sceneId, selfId, NPCId, x203330_g_ScriptId, x203330_g_MissionId);
			end
		end
	else
		if nExtIdx == 1000 then
    	local level = GetLevel( sceneId, selfId)
        
        if level > x270352_g_PlayerMaxLevel then
    		BeginQuestEvent( sceneId)
                AddQuestText( sceneId, "您已经是一个高于70级的大侠了，这点小事还是不用劳烦您了。");
    		EndQuestEvent( sceneId)
    		DispatchQuestEventList( sceneId, selfId, NPCId)
            return 1
        end
			x270352_DispatchMissionInfo( sceneId, selfId, NPCId )	--任务信息显示
		else
	    	local level = GetLevel( sceneId, selfId)
	        
	        if level > x270352_g_PlayerMaxLevel then
	    		BeginQuestEvent( sceneId)
	                AddQuestText( sceneId, "您已经是一个高于70级的大侠了，这点小事还是不用劳烦您了。");
	    		EndQuestEvent( sceneId)
	    		DispatchQuestEventList( sceneId, selfId, NPCId)
	            return 1
	        end
	        
	        local Times = x270352_GetTimes( sceneId, selfId)
	        --print("Times",Times)
	        if mod(Times,10) == 0 then
				x270352_DispatchMenuInfo( sceneId, selfId, NPCId )	--任务信息显示
			else
				x270352_DispatchMissionInfo( sceneId, selfId, NPCId )	--任务信息显示
			end
		end
	end
end

---------------------------------------------------------------------------------------------------
--检测接受条件
---------------------------------------------------------------------------------------------------
function x270352_ProcAcceptCheck( sceneId, selfId, npcId )
	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x270352_g_MissionId);
	if(bHaveMission > 0) then
		return 0;
	else
		return 1;
	end
end

-- 是否处于任务放弃后的惩罚时间内
function x270352_IsPunish( sceneId, selfId)
    return 0
end

function x270352_DenoteMonsterPosition( sceneId, selfId, BagIndex )

	local misIndex = GetQuestIndexByID(sceneId, selfId, x270352_g_MissionId)
	local monidx = GetQuestParam( sceneId, selfId, misIndex, 1)
    local index = GetQuestParam( sceneId, selfId, misIndex, 2)
    ----local Place = x270352_g_MonsterTable[index].monList[monidx].Place
    local name = x270352_g_MonsterTable[index].monList[monidx].name
    local posName = x270352_g_MonsterTable[index].monList[monidx].posName
    local mapId = x270352_g_MonsterTable[index].monList[monidx].mapid
    
    if mapId ~= sceneId then
    	local msg = format( "请先前往%s再使用三环追踪符", posName)
    	Msg2Player( sceneId, selfId, msg, 8, 3)
    else
    	local objId = x270352_g_MonsterTable[index].monList[monidx].objid
    	
    	local obj =  FindMonsterByGUID(sceneId, objId)
    	if IsObjValid(sceneId,obj) ~= 1 then
    		return
    	end
    	 
    	local x, z = GetWorldPos( sceneId, obj)
		Msg2Player(sceneId,selfId,format("%s正在（%d,%d）附近游荡！", name, x, z), 8,3)
    end
   
end



function x270352_DelRequireMissionItem( sceneId, selfId)
	if DelItem( sceneId, selfId, x270352_g_AcceptItemID, 1) == 0 then
		Msg2Player( sceneId, selfId, format( "请您先去杂货商人处购买@item_%d#cffcf00!再来接受任务", x270352_g_AcceptItemID), 8, 3)
        return 0
    end
    return 1
end      
     
function x270352_AddAcceptMissionItem( sceneId, selfId)

	BeginAddItem(sceneId)
    AddBindItem( sceneId, x270352_g_SubmitItemID,1 )
    local ret = EndAddItem(sceneId,selfId)
    
	local name = GetName(sceneId,selfId)
	if name == nil then
		name = "ErrorName"
	end

    if ret > 0 then
    	Msg2Player( sceneId, selfId, format( "你获得了1个@item_%d!", x270352_g_SubmitItemID), 8, 3)
        AddItemListToPlayer(sceneId,selfId)
	else
		LuaScenceM2Player(sceneId, selfId, "#cffcf00物品栏已满，无法得到任务道具！", name , 2,1)
	    LuaScenceM2Player(sceneId, selfId, "#cffcf00物品栏已满，无法得到任务道具！", name , 3,1)
	end
	return ret
		        
end

function x270352_GetQuestIndex( sceneId, selfId, NPCId)
	local level = GetLevel( sceneId, selfId)
	local teamSize = GetNearTeamCount( sceneId, selfId)
    for i = 0, teamSize - 1 do
    	local memberId = GetNearTeamMember( sceneId, selfId, i)
        if memberId ~= selfId and IsPlayerStateNormal( sceneId, memberId) == 1 then
            if IsInDist( sceneId, selfId, NPCId, 30) == 1 then  --距离NPC 30米以内 
                local teamLevel = GetLevel( sceneId, memberId)
                if abs( teamLevel - level) <= 5 then
                   	if IsHaveQuestNM(sceneId, memberId, x270352_g_MissionId) == 1 then
                       	local misIndex = GetQuestIndexByID( sceneId, memberId, x270352_g_MissionId)
                       	local midx = GetQuestParam( sceneId, memberId, misIndex, 1)
                       	local idx = GetQuestParam( sceneId, memberId, misIndex, 2)
        				return idx, midx
        		   end
                end
            end
        end
    end
    return 0,0
end

function x270352_GetQuest( sceneId, selfId, NPCId, index, monIndex)
    
    local idx = index
    local midx = monIndex
    
    if IsHaveQuestNM(sceneId, selfId, x270352_g_MissionId) == 0 then
        -- 检查能否领取
        local ret, strMsg = CallScriptFunction( 270355, "CountCheck", sceneId, selfId)
        if ret == 0 then
            Msg2Player( sceneId, selfId, strMsg, 8, 3)
            return 0, 0
        end

		if x270352_DelRequireMissionItem( sceneId, selfId) <= 0 then                 
			return 0, 0                                                                    
		end  
		local ret = AddQuest( sceneId, selfId, x270352_g_MissionId, x270352_g_ScriptId, 1, 0, 0, 1)
    	if(ret == 0) then
            Msg2Player( sceneId, selfId, "任务已满，任务接受失败", 8, 3)
    		return 0, 0
    	end
		 -- 更新计数
        CallScriptFunction( 270355, "UpdateCount", sceneId, selfId, 1)                                                                        
		if x270352_AddAcceptMissionItem( sceneId, selfId) <= 0 then 
    		return 0, 0
    	end

       

        if index == 0 and monIndex == 0 then
        	idx, midx = x270352_GetQuestIndex(sceneId, selfId, NPCId)
        	if idx == 0 and midx == 0 then
            -- get player level
            local level = GetLevel( sceneId, selfId)
            for i, item in x270352_g_MonsterTable do
                if level >= item.minLevel and level <= item.maxLevel then
                    idx = i
                    midx = random( 1, getn( item.monList) )
                    	if midx < 1 or midx > getn( item.monList) then
	                    	midx = 1
	                    end
                    break
                 end   
                end
            end
        end
        
        if idx < 1 or idx > getn(x270352_g_MonsterTable) then
        	idx = 1
        	local level = GetLevel( sceneId, selfId)
            for i, item in x270352_g_MonsterTable do
                if level >= item.minLevel and level <= item.maxLevel then
                    idx = i
                    break
                end
            end    
        end
        if midx < 1 or midx > getn(x270352_g_MonsterTable[idx].monList) then
        	midx = 1
        end
        
        local misIndex = GetQuestIndexByID( sceneId, selfId, x270352_g_MissionId)
        SetQuestByIndex( sceneId, selfId, misIndex, 1, midx)
        SetQuestByIndex( sceneId, selfId, misIndex, 2, idx)

        -- 设置任务完成标记
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)

        -- 显示提示信息
        Msg2Player( sceneId, selfId, x270352_g_strAcceptMission, 8, 3)
        -- 系统消息
        Msg2Player( sceneId, selfId, x270352_g_strAcceptMission, 8, 2)

    	x270352_QuestLogRefresh( sceneId, selfId, x270352_g_MissionId )

        -- 显示任务信息
        x270352_ShowMissionInfo( sceneId, selfId, NPCId)

        SetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_LEADER, 0)
        SetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_ASSIST, 0)

        -- 写日志
        GamePlayScriptLog( sceneId, selfId, 611)
    end

    return idx, midx
end
---------------------------------------------------------------------------------------------------
--接受条件
---------------------------------------------------------------------------------------------------
function x270352_ProcQuestAccept( sceneId, selfId, NPCId, missionId )

	if IsHaveQuestNM(sceneId, selfId, x270352_g_MissionId) == 0 then
		----------------------------------------------------------------------------
		if GetBagSpace(sceneId,selfId) <= 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"背包已满，请整理背包，再接取任务！")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return
		end
		
        local index = 0
        local monIndex = 0
        if GetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_LEADER) == 0 then
            index, monIndex = x270352_GetQuest( sceneId, selfId, NPCId, 0, 0)

            local level = GetLevel( sceneId, selfId)
            -- 给队伍成员添加任务
            --local teamSize = GetNearTeamCount( sceneId, selfId)
            --for i = 0, teamSize - 1 do
            --    local memberId = GetNearTeamMember( sceneId, selfId, i)
            --    if memberId ~= selfId and IsPlayerStateNormal( sceneId, memberId) == 1 then
            --        if IsInDist( sceneId, selfId, memberId, 5) == 1 then
            --            local teamLevel = GetLevel( sceneId, memberId)
            --            if abs( teamLevel - level) <= 5 and teamLevel >= 20 and teamLevel < 70 and IsInDist( sceneId, memberId, NPCId, 3) == 1 then
            --                x270352_DispatchMissionInfo( sceneId, memberId, NPCId)
            --                SetPlayerRuntimeData( sceneId, memberId, RD_GUILDCONTEND_KILL_LEADER, index)
            --                SetPlayerRuntimeData( sceneId, memberId, RD_GUILDCONTEND_KILL_ASSIST, monIndex)
            --            else
            --                Msg2Player( sceneId, selfId, format( "您的队友%s和您等级差距过大，未和您一起领取本次任务", GetName( sceneId, memberId) ), 8, 3)
            --            end
            --        else
            --            Msg2Player( sceneId, selfId, format( "您的队友%s和您距离过远，未和您一起领取本次任务", GetName( sceneId, memberId) ), 8, 3)
            --        end
            --    end
            --end
        else
            local index = GetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_LEADER)
            local monIndex = GetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_ASSIST)
            x270352_GetQuest( sceneId, selfId, NPCId, index, monIndex)
        end
    else
		local misIndex = GetQuestIndexByID(sceneId, selfId, x270352_g_MissionId)
		local completed = GetQuestParam(sceneId, selfId, misIndex, x270352_MP_ISCOMPLETE)

		if completed == 1 then
			local result = x270352_CheckPlayerBagFull(sceneId,selfId)
			if result == 1 then
                -- 删除道具
                if DelItem( sceneId, selfId, x270352_g_ItemID, 1) == 0 then
                    Msg2Player( sceneId, selfId, format( "很抱歉，你没有@item_%d#cffcc00", x270352_g_ItemID), 8, 3)
                    return
                end               
                DelItem( sceneId, selfId, x270352_g_SubmitItemID, 1)                          
		    				DelQuest(sceneId, selfId, x270352_g_MissionId)
                --CallScriptFunction( 203803, "FinishSanhuanling", sceneId, selfId)

                Msg2Player( sceneId, selfId, x270352_g_strFinishMission, 8, 2)
                Msg2Player( sceneId, selfId, x270352_g_strFinishMission, 8, 3)

		    	x270352_GetBonus( sceneId,selfId,NPCId, 0, 5)

                CallScriptFunction( 270355, "UpdateCount", sceneId, selfId, 4)

                -- 写日志
                GamePlayScriptLog( sceneId, selfId, 612)
		    else
		    	BeginQuestEvent( sceneId )
				AddQuestText( sceneId,"包裹已满！")
				EndQuestEvent()
				DispatchQuestTips(sceneId, selfId);
		    end

		else
			BeginQuestEvent( sceneId )
				AddQuestText( sceneId,"任务没有完成！")
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId);
		end
	end
end

---------------------------------------------------------------------------------------------------
--放弃任务
---------------------------------------------------------------------------------------------------
function x270352_ProcQuestAbandon( sceneId, selfId, MissionId)
	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x270352_g_MissionId);
	if bHaveMission > 0 then
		local misIndex = GetQuestIndexByID(sceneId, selfId, x270352_g_MissionId); 
		DelQuest(sceneId, selfId, x270352_g_MissionId);
		DelItem( sceneId, selfId, x270352_g_SubmitItemID, 1)
		
        BeginQuestEvent( sceneId)
        AddQuestText( sceneId, x270352_g_strAbandonMission)
        EndQuestEvent( sceneId)
        DispatchQuestTips( sceneId, selfId)
        Msg2Player( sceneId, selfId, x270352_g_strAbandonMission, 8, 2)
	end
end

---------------------------------------------------------------------------------------------------
--检查任务是否可提交
---------------------------------------------------------------------------------------------------
function x270352_CheckSubmit( sceneId, selfId, NPCId)

	local misIndex = GetQuestIndexByID(sceneId, selfId, x270352_g_MissionId);
	return GetQuestParam(sceneId, selfId, misIndex, x270352_MP_ISCOMPLETE);

end

---------------------------------------------------------------------------------------------------
--获得奖励
---------------------------------------------------------------------------------------------------
function x270352_GetBonus( sceneId, selfId,NpcID, SelectId, times)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x270352_g_MissionId)
	--奖励经验
	local level = GetLevel( sceneId, selfId)
    local n = 0
    if level >= 20 and level < 40 then 
        n = 1
    elseif level < 60 then
        n = 2
    elseif level < 74 then
        n = 3
    else
        n = 4
    end  
	local exp =( 1000 * 0.01 * level * x270352_g_ExpBonus[n]) * times
    if exp > 0 then
		AddExp( sceneId, selfId, exp)
  		Msg2Player( sceneId, selfId, format( "获得#R经验%d点#cffcf00的奖励", exp), 8, 2)
        BeginQuestEvent( sceneId)
        AddQuestText( sceneId, format( "获得#R经验%d点#cffcf00的奖励", exp) )
        EndQuestEvent( sceneId)
        DispatchQuestTips( sceneId, selfId)
	end

	--奖励金钱1
	if x270352_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x270352_g_BonusMoney1 * level * times)
	    Msg2Player(sceneId,selfId,format("获得#R银卡#{_MONEY%d}#cffcf00的奖励。", x270352_g_BonusMoney1 * level),4,2)
        Msg2Player(sceneId,selfId,format("获得#R银卡#{_MONEY%d}#cffcf00的奖励", x270352_g_BonusMoney1 * level),8,3)
	end

	--奖励金钱2
	if x270352_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x270352_g_BonusMoney2 * level)
	    Msg2Player(sceneId,selfId,format("获得#R现银#{_MONEY%d}#cffcf00的奖励。", x270352_g_BonusMoney2 * level),4,2)
        Msg2Player(sceneId,selfId,format("获得#R现银#{_MONEY%d}#cffcf00的奖励", x270352_g_BonusMoney2 * level),8,3)
	end

	--奖励金钱1
	if x270352_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x270352_g_BonusMoney3 )
	    Msg2Player(sceneId,selfId,format("获得金卡#{_MONEY%d}的奖励。", x270352_g_BonusMoney3),4,2)
	end

	--江湖声望
	if x270352_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
		nRongYu = nRongYu + x270352_g_BonusMoney4
		SetRongYu( sceneId, selfId, nRongYu )
		Msg2Player(sceneId,selfId,format("获得江湖声望%d的奖励。", x270352_g_BonusMoney4),4,2)
	end

	--朝廷声望
	if x270352_g_BonusMoney5 > 0 then
		local nShengWang = GetShengWang( sceneId, selfId )
		nShengWang = nShengWang + x270352_g_BonusMoney5
		SetShengWang( sceneId, selfId, nShengWang )
		Msg2Player(sceneId,selfId,format("获得朝廷声望%d的奖励。", x270352_g_BonusMoney5),4,2)
	end

	--朝廷声望
	if x270352_g_BonusMoney6 > 0 then
		AddHonor(sceneId,selfId,x270352_g_BonusMoney6)
		Msg2Player(sceneId,selfId,format("获得荣誉值%d的奖励。", x270352_g_BonusMoney6),4,2)
	end

 	--奖励固定物品
		for i, item in x270352_g_BonusItem do
 		BeginAddItem(sceneId)
		AddItem( sceneId, item.item, item.n )
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
			AddItemListToPlayer(sceneId,selfId)
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"物品栏已满，无法得到任务物品！")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end
    end

	--奖励可选物品
	for i, item in x270352_g_BonusChoiceItem do
	    if item.item == SelectId then
	        BeginAddItem(sceneId)
			AddItem( sceneId, item.item, item.n )
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"物品栏已满，无法得到任务物品！")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end

			--获取完必，请返回，防止重复添加
			return
		end
    end

end

---------------------------------------------------------------------------------------------------
--提交任务，不管任务是否完成或是任务，显示任务继续信息或是任务完成信息
---------------------------------------------------------------------------------------------------
function x270352_ProcQuestSubmit( sceneId, selfId, NPCId, selectRadioId, MissionId)
	--判断是否有任务
	local bHaveMission = IsHaveQuestNM(sceneId, selfId, x270352_g_MissionId);
	if bHaveMission > 0 then

		local misIndex = GetQuestIndexByID(sceneId, selfId, x270352_g_MissionId)
		local completed = GetQuestParam(sceneId, selfId, misIndex, x270352_MP_ISCOMPLETE)

		if completed == 1 then
			local result = x270352_CheckPlayerBagFull(sceneId,selfId)
			if result == 1 then
		    	DelQuest(sceneId, selfId, x270352_g_MissionId)
                --CallScriptFunction( 203803, "FinishSanhuanling", sceneId, selfId)

                BeginQuestEvent( sceneId)
                AddQuestText( sceneId, x270352_g_strFinishMission)
                EndQuestEvent( sceneId)
                DispatchQuestTips( sceneId, selfId)
                Msg2Player( sceneId, selfId, x270352_g_strFinishMission, 8, 2)

		    	x270352_GetBonus( sceneId,selfId,NPCId,selectRadioId, 1)
	       	DelItem( sceneId, selfId, x270352_g_SubmitItemID, 1)

                -- 写日志
                GamePlayScriptLog( sceneId, selfId, 612)
		    else
		    	BeginQuestEvent( sceneId )
				AddQuestText( sceneId,"包裹已满！")
				EndQuestEvent()
				DispatchQuestTips(sceneId, selfId);
		    end

		else
			BeginQuestEvent( sceneId )
				AddQuestText( sceneId,"任务没有完成！")
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId);
		end
	else

		BeginQuestEvent( sceneId )
			AddQuestText( sceneId,"任务不存在，获取任务信息失败！")
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId);

		return
	end

end

---------------------------------------------------------------------------------------------------
--检查玩家包裹已满
---------------------------------------------------------------------------------------------------
function x270352_CheckPlayerBagFull( sceneId ,selfId)


	local result = 1

	local j = 0

	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满

	--普通的奖励检查
	BeginAddItem(sceneId)
	for j, item in x270352_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
    end

    --奖励可选物品
	for j, item in x270352_g_BonusChoiceItem do
		AddItem( sceneId, item.item, item.n )
    end
		
	local ret = EndAddItem(sceneId,selfId)
	if(ret > 0) then
		result = 1;
	else
		result = 0;
	end

	return result
end

-- 接受任务后显示任务信息
function x270352_ShowMissionInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)
        -- 任务名称
		AddQuestText(sceneId, "#Y"..x270352_g_MissionName)

		--任务目标
		--AddQuestText( sceneId, "#Y任务目标：")
		AddQuestText( sceneId, "\t这些怪物并不会在一个地方停留，他们会在对应的地图中游荡。\n\t你可以使用我给你的#G三环追踪符#W，它会告诉你怪物的具体位置。")
        local misIndex = GetQuestIndexByID( sceneId, selfId, x270352_g_MissionId)
        local monidx = GetQuestParam( sceneId, selfId, misIndex, 1)
        local index = GetQuestParam( sceneId, selfId, misIndex, 2)
        AddQuestText( sceneId, "\n#Y任务目标：")
        AddQuestText( sceneId, format( x270352_g_MissionTarget, x270352_g_MonsterTable[ index].monList[ monidx].posName, x270352_g_MonsterTable[ index].monList[ monidx].name, 0) )
		AddQuestText( sceneId, " ")
	EndQuestEvent()
    DispatchQuestEventList( sceneId, selfId, NPCId)
end

function x270352_DispatchMenuInfo( sceneId, selfId, NPCId)
	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId, "#Y"..x270352_g_MissionName)
		AddQuestText(sceneId, "\t完成一轮通缉令等同于完成一次三环任务，每轮通缉令任务有10环，每天可以完成6轮。\n\t您即将领取的是第1环，会#G消耗一次本周的三环副本次数#W和#G一个通缉令#W。你确定要领取三环任务(通缉令)吗？\n（#G通缉令#W可在王城贸易区杂货商人处购买。）\n#Y注意#W：\n\t领取1轮本任务后，当天只可完成三环任务（三番令）一次。\n\t领取4轮本任务后，当天不可完成三环任务（三番令）。")
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x270352_g_MissionId)
		AddQuestNumText(sceneId,x270352_g_MissionId,"我要领取三环通缉令",13,1000 )	
	
		EndQuestEvent()
	 DispatchQuestEventList( sceneId, selfId, NPCId)
	 
	--DispatchQuestInfoNM(sceneId, selfId, NPCId, x270352_g_ScriptId, x270352_g_MissionId)
end
---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x270352_DispatchMissionInfo( sceneId, selfId, NPCId )

	local level = GetLevel(sceneId,selfId);
	
	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId, "#Y"..x270352_g_MissionName)
		AddQuestText(sceneId, x270352_g_MissionDescription)
		--AddQuestText(sceneId, "\n#G小提示")
		AddQuestText(sceneId, x270352_g_MissionHelp)

		--任务奖励信息

		--1、经验
		--if x270352_g_ExpBonus> 0 then
		local level= GetLevel( sceneId, selfId)
		local n = 0
		if level >= 20 and level < 40 then 
			n = 1
		elseif level < 60 then
			n = 2
		elseif level < 74 then
			n = 3
		else
		  n = 4
		end  
		local exp =( 1000 * 0.01 * level * x270352_g_ExpBonus[n])
		if exp > 0 then
			AddQuestExpBonus( sceneId, exp )
		end

		--2、金钱1
		if x270352_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1( sceneId, x270352_g_BonusMoney1 * level)
		end

		--3、金钱2
		if x270352_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2( sceneId, x270352_g_BonusMoney2 * level)
		end
		--4、金钱3
		if x270352_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3( sceneId, x270352_g_BonusMoney3 )
		end

		--江湖声望
		if x270352_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4( sceneId, x270352_g_BonusMoney4 )
		end

		--朝廷声望
		if x270352_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5( sceneId, x270352_g_BonusMoney5 )
		end

		--荣誉值
		if x270352_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6( sceneId, x270352_g_BonusMoney6 )
		end


		--5、固定物品
		for i, item in x270352_g_BonusItem do
		   	AddQuestItemBonus( sceneId, item.item, item.n)
	    end

		--6、可选物品
		for i, item in x270352_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus( sceneId, item.item, item.n)
	    end

	EndQuestEvent()
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x270352_g_ScriptId, x270352_g_MissionId)
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x270352_DispatchContinueInfo( sceneId, selfId, NPCId )

	local misIndex = GetQuestIndexByID(sceneId, selfId, x270352_g_MissionId);

	BeginQuestEvent(sceneId)

		--任务继续信息
		AddQuestText(sceneId,"#Y"..x270352_g_MissionName)
		AddQuestText(sceneId,x270352_g_MissionContinue)
		AddQuestText(sceneId," ")

	EndQuestEvent()
	DispatchQuestEventList( sceneId, selfId, NPCId)
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x270352_DispatchCompletedInfo( sceneId, selfId, NPCId, nExtIdx)
    if nExtIdx == 30 then
        BeginQuestEvent(sceneId)
            AddQuestText(sceneId,"#Y"..x270352_g_MissionName)
            AddQuestText(sceneId, "\t这么快就消灭了那些怪物？\n\t如果你使用#G悬赏令#W来完成任务，将会获得#G5倍#W的经验，消耗#G5环#W任务次数。#G（悬赏令在金币商城出售）\n\t#W当然，你也可以直接完成任务，获得正常的经验，只消耗一环任务次数。" )
            AddQuestText(sceneId," ")

            local state = GetQuestStateNM( sceneId, selfId, NPCId, x270352_g_MissionId)
            AddQuestNumText( sceneId, x270352_g_MissionId, "使用悬赏令完成任务", 3, 31)
            AddQuestNumText( sceneId, x270352_g_MissionId, "直接完成任务", 3, 32)
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, NPCId)
    elseif nExtIdx == 31 then
        if GetQuestData(sceneId, selfId, MD_FUBEN_QIULONGDAO_DAYCOUNT[1], MD_FUBEN_QIULONGDAO_DAYCOUNT[2], MD_FUBEN_QIULONGDAO_DAYCOUNT[3] ) >= 21
            and x270352_GetTimes( sceneId, selfId) > 5 then
            Msg2Player( sceneId, selfId, "本周不能再使用悬赏令完成任务了。", 8, 3)
            return
        end
        local count = GetQuestData( sceneId, selfId, MD_FUBEN_QIULONGDAO_TODAYCOUNT[1], MD_FUBEN_QIULONGDAO_TODAYCOUNT[2], MD_FUBEN_QIULONGDAO_TODAYCOUNT[3] )
        local times = x270352_GetTimes( sceneId, selfId)
        --print("count",count,times)
        if GetQuestData( sceneId, selfId, MD_FUBEN_QIULONGDAO_TODAYCOUNT[1], MD_FUBEN_QIULONGDAO_TODAYCOUNT[2], MD_FUBEN_QIULONGDAO_TODAYCOUNT[3] ) >= 6 
            and x270352_GetTimes( sceneId, selfId) > 6 then
            Msg2Player( sceneId, selfId, "今天不能再使用悬赏令完成任务了。", 8, 3)
            return
        end
        BeginQuestEvent(sceneId)
            AddQuestText(sceneId,"#Y"..x270352_g_MissionName)
            AddQuestText(sceneId, x270352_g_MissionCompleted1)
            AddQuestText(sceneId, "\t你确定要使用悬赏令么？" )
            AddQuestText(sceneId, " " )

            local level= GetLevel(sceneId,selfId)
            if level >= 20 and level < 40 then 
                n = 1
            elseif level < 60 then
                n = 2
            elseif level < 74 then
                n = 3
            else
              n = 4
            end  		
            local exp =( 1000 * 0.01 * level * x270352_g_ExpBonus[n])
            if exp > 0 then
                AddQuestExpBonus( sceneId, exp * 5)
            end
            if x270352_g_BonusMoney1 > 0 then
                AddQuestMoneyBonus1(sceneId, x270352_g_BonusMoney1 * level * 5)
            end

        EndQuestEvent()
        DispatchQuestInfoNM(sceneId, selfId, NPCId, x270352_g_ScriptId, x270352_g_MissionId)
    elseif nExtIdx == 32 then
	BeginQuestEvent(sceneId)

		--任务完成信息
		AddQuestText(sceneId,"#Y"..x270352_g_MissionName)
		AddQuestText(sceneId,x270352_g_MissionCompleted)
		AddQuestText(sceneId," ")

  		--任务奖励信息

		--1、经验
		-- if x270352_g_ExpBonus > 0 then
			-- AddQuestExpBonus(sceneId, x270352_g_ExpBonus[n])
		-- end
		local level= GetLevel(sceneId,selfId)
		if level >= 20 and level < 40 then 
			n = 1
		elseif level < 60 then
			n = 2
		elseif level < 74 then
			n = 3
		else
		  n = 4
		end  		
		local exp =( 1000 * 0.01 * level * x270352_g_ExpBonus[n])
		if exp > 0 then
			AddQuestExpBonus(sceneId, exp )
		end

		--2、金钱1
		if x270352_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x270352_g_BonusMoney1 * level)
		end

		--3、金钱2
		if x270352_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x270352_g_BonusMoney2 * level)
		end
		--4、金钱3
		if x270352_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x270352_g_BonusMoney3 )
		end

		--江湖声望
		if x270352_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x270352_g_BonusMoney4 )
		end

		--朝廷声望
		if x270352_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x270352_g_BonusMoney5 )
		end

		--荣誉值
		if x270352_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x270352_g_BonusMoney6 )
		end


		--5、固定物品
		for i, item in x270352_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	    end

		--6、可选物品
		for i, item in x270352_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	    end
	EndQuestEvent()
	--DispatchQuestEventList(sceneId,selfId,NPCId);
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x270352_g_ScriptId, x270352_g_MissionId);
    end
end

---------------------------------------------------------------------------------------------------
--怪物被杀的消息处理
---------------------------------------------------------------------------------------------------
function x270352_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

    if IsPlayerStateNormal( sceneId, selfId) ~= 1 then
        return
    end
        
    local misIndex = 0
    local teamSize = GetNearTeamCount( sceneId, selfId)
    -- print( "附近队伍人数："..teamSize)

     -------------------------------------------------------
    --非组队的附近玩家也共享完成任务信息
    local x,z = GetWorldPos(sceneId, selfId)
    local teamId = GetTeamId(sceneId, selfId)
    local count = GetNearPlayerCount(sceneId, selfId, x, z, 30)
    for i = 0, count - 1 do
    	local memberId = GetNearPlayerMember( sceneId, selfId, i)
    	if memberId ~= selfId and IsPlayerStateNormal( sceneId, memberId) == 1 then
        	local teamId1 = GetTeamId(sceneId, memberId)
        	if teamId ~= teamId1 or teamId == -1 or teamId1 == -1 then
	            if IsHaveQuestNM(sceneId, memberId, x270352_g_MissionId) == 1 then
	                local misIndex = GetQuestIndexByID( sceneId, memberId, x270352_g_MissionId)
	                local monidx = GetQuestParam( sceneId, memberId, misIndex, 1)
                    local index = GetQuestParam( sceneId, memberId, misIndex, 2)
                    local name = x270352_g_MonsterTable[index].monList[monidx].name
                    if objdataId == x270352_g_MonsterTable[ index].monList[ monidx].id then
		                SetQuestByIndex( sceneId, memberId, misIndex, 0, 1)
			            SetQuestByIndex( sceneId, memberId, misIndex, 7, 1)
			            SetQuestByIndex( sceneId, memberId, misIndex, 6, 1)
			            Msg2Player( sceneId, memberId, format( "%s已被消灭，【个人】三环任务(通缉令)任务完成", name), 8, 3)
			            Msg2Player( sceneId, memberId, format( "%s已被消灭，【个人】三环任务(通缉令)任务完成", name), 8, 2)
			            x270352_QuestLogRefresh( sceneId, memberId, x270352_g_MissionId)
			        end
	        	end
	        end
        end
    end
       
    
    
    -------------------------------------------------------
    if teamSize <= 1 then -- 非组队，单独做任务
        
        if IsHaveQuest( sceneId, selfId, x270352_g_MissionId) <= 0 then
            return
        end
        misIndex = GetQuestIndexByID( sceneId, selfId, x270352_g_MissionId)
        local monidx = GetQuestParam( sceneId, selfId, misIndex, 1)
        local index = GetQuestParam( sceneId, selfId, misIndex, 2)
        local name = x270352_g_MonsterTable[index].monList[monidx].name
        if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
            -- 如果任务已完成
            return
        end

        if objdataId == x270352_g_MonsterTable[ index].monList[ monidx].id then
            SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
            SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
            SetQuestByIndex( sceneId, selfId, misIndex, 6, 1)
            Msg2Player( sceneId, selfId, format( "%s已被消灭，【个人】三环任务(通缉令)任务完成", name), 8, 3)
            Msg2Player( sceneId, selfId, format( "%s已被消灭，【个人】三环任务(通缉令)任务完成", name), 8, 2)
        else
            -- 如果杀死的不是任务目标怪
            return
        end

        x270352_QuestLogRefresh( sceneId, selfId, x270352_g_MissionId)
    else
        for i = 0, teamSize - 1 do
            local memberId = GetNearTeamMember( sceneId, selfId, i)
            if memberId >= 0 and IsPlayerStateNormal( sceneId, memberId) == 1 then
                if IsHaveQuest( sceneId, memberId, x270352_g_MissionId) > 0 then -- 如果该成员接受了狩猎任务
                    misIndex = GetQuestIndexByID( sceneId, memberId, x270352_g_MissionId)
                    local monidx = GetQuestParam( sceneId, memberId, misIndex, 1)
                    local index = GetQuestParam( sceneId, memberId, misIndex, 2)
                    local name = x270352_g_MonsterTable[index].monList[monidx].name
                    if GetQuestParam( sceneId, memberId, misIndex, 0) == 0 or GetQuestParam( sceneId, memberId, misIndex, 7) == 0 then
                        local missionMonster = 1
                        if objdataId == x270352_g_MonsterTable[ index].monList[ monidx].id then
                            SetQuestByIndex( sceneId, memberId, misIndex, 0, 1)
                            SetQuestByIndex( sceneId, memberId, misIndex, 7, 1)
                            SetQuestByIndex( sceneId, memberId, misIndex, 6, 1)
                            Msg2Player( sceneId, memberId, format( "%s已被消灭，【个人】三环任务(通缉令)任务完成", name), 8, 3)
                            Msg2Player( sceneId, memberId, format( "%s已被消灭，【个人】三环任务(通缉令)任务完成", name), 8, 2)
                        else
                            missionMonster = 0
                        end

                        if missionMonster == 1 then
                            x270352_QuestLogRefresh( sceneId, memberId, x270352_g_MissionId)
                        end
                    end
                end
            end
        end
    end
end

---------------------------------------------------------------------------------------------------
--物品改变
---------------------------------------------------------------------------------------------------
function x270352_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
--	local misIndex = GetQuestIndexByID(sceneId, selfId, x270352_g_MissionId);
--	
--	if(itemdataId == x270352_TARGET_OBJID1 ) then
--		local targetcount	= GetQuestParam(sceneId, selfId, misIndex, x270352_MP_TARGET1);
--		if(targetcount < x270352_g_ExtTarget[x270352_MP_TARGET1+1].n) then
--			targetcount	= targetcount + 1;
--			BeginQuestEvent(sceneId);
--			AddQuestText(sceneId,"已获得"..x270352_g_ExtTarget[x270352_MP_TARGET1+1].target..":"..targetcount.."/"..x270352_g_ExtTarget[x270352_MP_TARGET1+1].n);
--			EndQuestEvent();
--			DispatchQuestTips(sceneId, selfId);
--			SetQuestByIndex(sceneId, selfId, misIndex, x270352_MP_TARGET1, targetcount )
--		end
--	end
--	
--	--检测任务是否完成
--	local targetcount1	= GetQuestParam(sceneId, selfId, misIndex, x270352_MP_TARGET1);
--	if(targetcount1 == x270352_g_ExtTarget[x270352_MP_TARGET1+1].n) then
--		SetQuestByIndex(sceneId, selfId, misIndex, x270352_MP_ISCOMPLETE, 1 )
--	end
end

---------------------------------------------------------------------------------------------------
--单击NPC事件
---------------------------------------------------------------------------------------------------
function x270352_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

	if npcGuid == x270352_SubmitNPCGUID then
		local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x270352_g_MissionId);
		if(bHaveMission > 0) then
			local state = GetQuestStateNM(sceneId,selfId,npcId,x270352_g_MissionId)
			AddQuestNumText(sceneId, x270352_g_MissionId, x270352_g_MissionName,state,30);
		end
	end

end

---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x270352_QuestLogRefresh( sceneId, selfId, MissionId)
    if IsHaveQuest( sceneId, selfId, x270352_g_MissionId) == 0 then
        return
    end

	local misIndex = GetQuestIndexByID( sceneId, selfId, x270352_g_MissionId)
    local monidx = GetQuestParam( sceneId, selfId, misIndex, 1)
    local index = GetQuestParam( sceneId, selfId, misIndex, 2)
    local kill = GetQuestParam( sceneId, selfId, misIndex, 6)
    
    
    --做个修复处理，防止任务显示不全
    if index < 1 or index > getn(x270352_g_MonsterTable) then
    	index = 1
    	local level = GetLevel( sceneId, selfId)
        for i, item in x270352_g_MonsterTable do
            if level >= item.minLevel and level <= item.maxLevel then
                index = i
                SetQuestByIndex(sceneId, selfId, misIndex, 2, index )
                break
            end
        end    
    end
    
    if monidx < 1 or monidx > getn(x270352_g_MonsterTable[index].monList) then
    	monidx = 1
    	SetQuestByIndex(sceneId, selfId, misIndex, 1, monidx )
    end
    

	BeginQuestEvent(sceneId)
        --local level= GetLevel( sceneId, selfId)
        local level = GetLevel( sceneId, selfId)
        local n = 0
		if level >= 20 and level < 40 then 
			n = 1
		elseif level < 60 then
			n = 2
		elseif level < 74 then
			n = 3
		else
            n = 4
		end      
		local exp =( 1000 * 0.01 * level * x270352_g_ExpBonus[n])
		if exp > 0 then
			AddQuestExpBonus( sceneId, exp)
		end
        if x270352_g_BonusMoney1 > 0 then
            AddQuestMoneyBonus1( sceneId, x270352_g_BonusMoney1 * level)
        end

        AddQuestLogCustomText( sceneId,
                                "",                             -- 标题
                                format( "【个人】三环任务(通缉令)(%d/10)", x270352_GetTimes( sceneId, selfId) ),           -- 任务名字
                                format( x270352_g_strMissionTarget, x270352_g_MonsterTable[ index].monList[ monidx].posName, x270352_g_MonsterTable[ index].monList[ monidx].name, kill),
                                "@npcsp_[三环副本]景彦多_129041",                             --任务NPC
                                x270352_g_MissionBook,
                                x270352_g_MissionDescription,
                                ""
                                )

	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, x270352_g_MissionId)
end

function x270352_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    x270352_QuestLogRefresh( sceneId, selfId, MissionId)
end

---------------------------------------------------------------------------------------------------
--强行加任务
---------------------------------------------------------------------------------------------------
function x270352_OnForceAddMission( sceneId, selfId, npcId, MissionId)
end

-- 获得接受任务日期
function x270352_GetDate( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_XUNAN_DATE[ 1], MD_XUNAN_DATE[ 2], MD_XUNAN_DATE[ 3] )
end

-- 设置接受任务日期
function x270352_SetDate( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_XUNAN_DATE[ 1], MD_XUNAN_DATE[ 2], MD_XUNAN_DATE[ 3], value)
end

function x270352_GetTimes( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_ZHUISHA_CIRCLE[ 1], MD_ZHUISHA_CIRCLE[ 2], MD_ZHUISHA_CIRCLE[ 3] )
end

function x270352_SetTimes( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_ZHUISHA_CIRCLE[ 1], MD_ZHUISHA_CIRCLE[ 2], MD_ZHUISHA_CIRCLE[ 3], value)
end

