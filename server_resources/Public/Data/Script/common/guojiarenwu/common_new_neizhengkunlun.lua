--MisDescBegin

x300512_g_ScriptId 					= 	300512                  --脚本ID
x300512_g_MissionId 				= 	10302                   --任务ID

x300512_g_LevelLess					= 	25                      --场景开放等级  <=0 表示不限制

x300512_g_MissionName				= 	"【个人】国家内政"
x300512_g_MissionTarget				= 	""          --任务目标
x300512_g_ContinueInfo				= 	"\t怎么？你连这些简单的国家内政都无法完成？看来我们要另外物色人选了。"  --任务继续信息
x300512_g_MissionCompleted			= 	"\t信已经送到了？"  --任务完成信息
x300512_g_MissionHelp				=	""          --任务提示信息

--目标
x300512_g_ExtTarget					=	{ {type=20,n=1 ,target=""} }
--奖励
x300512_g_ExpBonus					= 	0   --奖励：经验 (数值填0，字符串为空，表示没有该项奖励)
x300512_g_BonusItem					=	{}	--奖励：物品

x300512_g_BonusMoney1               = 	0   --任务奖励绑定银币
x300512_g_BonusMoney2               =   0   --任务奖励非绑定银币
x300512_g_BonusMoney3               =   0   --任务奖励绑定金币
x300512_g_BonusMoney4               =   0   --任务奖励朝廷声望
x300512_g_BonusMoney5               =   0   --任务奖励江湖声望
x300512_g_BonusMoney6               =   0   --任务奖励荣誉

x300512_g_BonusChoiceItem           =   {}
x300512_g_GroupPoint	=	{ {type=10,id =50,target = "苹果"},{type=10,id =56,target = "野花"},{type=10,id =58,target = "黑箱子"},{type=10,id =55,target = "玉米"}}--专门用于采集点特效用，与任务相关未必就是完成任务的必要因素，因此，只要相关就可以设置这个属性


--MisDescEnd

--任务目标顺序
x300512_MP_MissionType			    = 1         -- 任务类型(1——7)分别代表：送信、打怪、采集、护送、挖掘、收马和材料收集
x300512_MP_TARGET2					= 2         -- 
x300512_MP_TARGET3					= 3         -- 
x300512_MP_TARGET4					= 4         -- 
x300512_MP_TARGET5					= 5         -- 
x300512_MP_TARGET6					= 6         -- 
x300512_MP_FINISH                   = 7         -- 玩家接任务时的等级
x300512_MP_ISCOMPLETE				= 0	        -- 代表完成 0未完成， 1完成

-- 采集任务表
x300512_g_GrowPoint				    = {
                                        { type = 10, id = 50,target = "苹果",  itemId = 13011500, posId = 81000, count = 3, description = "\t我家的宝儿非常想吃#G#{_ITEM13011500}#W，可是我现在脱不开身，所以麻烦你到@npcsp_罕难河草原_81000采一些给我。", tips = "#G点击寻路，找到并采集这些物品完成任务。#W\n如果你能按照要求上交一些#G生活技能的原材料#W或#G生活技能制造的部件#W，#G甘醇马奶酒#W等等，你会获得#G更多的奖励。#W", Pos = "@npcsp_罕难河草原_81000" },
										{ type = 10, id = 56,target = "野花",  itemId = 13011506, posId = 81003, count = 3, description = "\t相传在@npcsp_罕难河草原_81003有#G#{_ITEM13011506}#W，其蜜汁甘甜，十分解渴，你能带三个回来给我么？", tips = "#G点击寻路，找到并采集这些物品完成任务。#W\n如果你能按照要求上交一些#G生活技能的原材料#W或#G生活技能制造的部件#W，#G甘醇马奶酒#W等等，你会获得#G更多的奖励。#W", Pos = "@npcsp_罕难河草原_81003" },
										{ type = 10, id = 58,target = "黑箱子",itemId = 13011508, posId = 81005, count = 3, description = "\t我对@npcsp_王城东门附近_81005奇怪的#G#{_ITEM13011508}#W很感兴趣，你能带三个回来给我么？", tips = "#G点击寻路，找到并采集这些物品完成任务。#W\n如果你能按照要求上交一些#G生活技能的原材料#W或#G生活技能制造的部件#W，#G甘醇马奶酒#W等等，你会获得#G更多的奖励。#W", Pos = "@npcsp_王城东门附近_81005" },
										{ type = 10, id = 55,target = "玉米",  itemId = 13011505, posId = 81001, count = 3, description = "\t说来惭愧，由于我们运输不善，罕难河草原的粮食竟然还没运过来，去那里带些粮食回来吧。", tips = "#G点击寻路，找到并采集这些物品完成任务。#W\n如果你能按照要求上交一些#G生活技能的原材料#W或#G生活技能制造的部件#W，#G甘醇马奶酒#W等等，你会获得#G更多的奖励。#W", Pos = "@npcsp_罕难河草原_81001" },
										
}
-- 接受任务提示
x300512_g_strAcceptMission          = "您接受了任务：【个人】国家内政(%d/10)"
-- 放弃任务提示
x300512_g_strAbandonMission         = "您放弃了任务：【个人】国家内政(%d/10)"
-- 完成任务提示
x300512_g_strFinishMission          = "您完成了任务：【个人】国家内政(%d/10)"
-- 放弃任务后禁止再领任务的时限(分钟)
x300512_g_PunishTime                = 5
-- 交任务NPC GUID
x300512_SubmitNPCGUID				= 129042
-- 任务小提示
x300512_g_MissionTips               = "如果想了解国家内政的细节，请在@npc_129042处查看国家内政说明。"
-- 任务描述
x300512_g_MissionDescription        = "\t作为国家一员，要承担起强盛国家的重任，每日内政大臣处理的事情成百上千，请你也助上一臂之力。\n\t你是否要接受任务？"
-- 任务攻略
x300512_g_MissionBook               = "回报@npc_129042"
-- 高奖环数
x300512_g_HighBonusCircleCount      = 10
-- 每轮环数
x300512_OneRoundCount               = 10
x300512_g_MissionCommentCountOver   = "你今天不能再领取国家内政了，明天再来吧。"
x300512_g_strNotEnoughSpace         = "背包空间不足，无法接受任务"
x300512_g_strMissionFull            = "任务已满，任务接受失败"
x300512_g_strDeliverContinue        = "\t你还没把@item_%d#W送给@npc_%d呢。"
x300512_g_strDeliverComplete        = "\t我的心情好多了，谢谢你带来的消息！"
x300512_g_strKillContinue           = "\t你还没消灭#B%s#W呢。"
x300512_g_strKillComplete           = "\t太好了，你真是祖国的英雄！"
x300512_g_strEscortContinue         = "\t交给你的事都完成了？"
x300512_g_strEscortComplete         = "\t谢谢，你真是帮了大忙。"
x300512_g_strHorseCompinue          = "\t你捉到我要的马了么？"
x300512_g_strHorseComplete          = "\t你捉到我要的马了么？"
x300512_g_strMaterialContinue       = "\t我吩咐你的事情，你已经完成了吗？"
x300512_g_strMaterialComplete       = "\t真是太谢谢你的热心帮助了。"
x300512_g_strCollectContinue        = "\t你还没有采集到我要的东西呢。"
x300512_g_strCollectComplete        = "\t你做起事来还真是干净利落，没想到你这么快就回来了。"
x300512_g_strDigContinue            = "\t你也无法找到它们的埋放地点吗？"
x300512_g_strDigComplete            = "\t恩，果然没错，看来这一带还会有更多的化石材料。"
x300512_g_strGoodHorse              = "\t这是一匹千载难逢的良马幼仔，你真的要把它交给国家吗？"
x300512_g_strNormalHorse            = "\t真是太好了，就在刚才我又收集到了几匹战马，照这个速度的话，用不了多久，我们的骑兵部队就能组建完成。"
x300512_g_strMissionFinishTip       = "任务已经完成，快点回去汇报吧！"
x300512_g_MT_Deliver                = 1
x300512_g_MT_KillMonster            = 2
x300512_g_MT_Collect                = 3
x300512_g_MT_Escort                 = 4
x300512_g_MT_Dig                    = 5
x300512_g_MT_Horse                  = 6
x300512_g_MT_Material               = 7
x300512_CountrySceneList	        = { 50, 150, 250, 350}
x300512_g_IsEnableId                = 1027
-- 送信物品、对话
x300512_g_DeliverTable              = {-- 要送物品Id，目标NPC的Id
                                        { missionItemId = 13011600, talking = "\t我知道了，到时候会将货物准时送达的！", description = "\t把这封信带给我的朋友，军队需要的货物都写在信上。", tips = "" }, 
                                        { missionItemId = 13011600, talking = "\t我知道了，到时候会将货物准时送达的！", description = "\t前方来信说他们的物资需要补充，把这封信带给我的朋友，我要的货物都写在信上。", tips = "" }, 
                                        { missionItemId = 13011600, talking = "\t谢谢，我一切安好，叫他放心吧。", description = "\t最近的几场战争让我很担心，把这封信带给我的朋友，提醒她注意安全。", tips = "" }, 
                                        { missionItemId = 13011600, talking = "\t我知道了，到时候会将货物准时送达的！", description = "\t把这封信带给我的朋友，军队需要的货物都写在信上。", tips = "" }, 
                                        { missionItemId = 13011600, talking = "\t谢谢你带来的这封信，万事俱备真是一个好消息。", description = "\t又见到你真是太好了，我这里有一件私事想要求你帮忙，请把这封信带给我的朋友，告诉他托付我的事情已经准备好了。", tips = "" }, 
                                        { missionItemId = 13011600, talking = "\t谢谢，请你帮我转告他愿我们的友谊天长地久！", description = "\t战争阻碍了我们，我和我的那位朋友很久不见了，你帮我带封信去问候一下。", tips = "" }, 
                                        { missionItemId = 13011600, talking = "\t我的心情好多了，谢谢你带来的消息！", description = "\t听说我的朋友最近心情很坏，你帮我带一封信安慰一下。", tips = "" }, 
                                        { missionItemId = 13011600, talking = "\t我知道了，到时候会将货物准时送达的！", description = "\t把这封信带给我的朋友，我要的货物都写在信上。", tips = "" }, 
                                        { missionItemId = 13011600, talking = "\t谢谢，请你帮我转告他愿我们的友谊天长地久！", description = "\t最近繁重的公务几乎占用了我所有的时间，我和我的朋友已经很久不见了，你帮我带封信去问候一下，让他知道我还没有忘记他这个老朋友。", tips = "" }, 
                                        { missionItemId = 13011600, talking = "\t(看过信后，他长叹了一口气)\n\t谢谢你带来的这封信，不错，人不能一直沉浸在无尽的痛苦之中，毕竟我还有个大儿子。", description = "\t听说我朋友的小儿子在战斗中牺牲了，这件事对他的打击非常大，他的心情现在几近崩溃，请你帮我带这封信交给他，朋友的关怀或许可以缓解一下他内心的伤痛。", tips = "" }, 
                                        { missionItemId = 13011600, talking = "\t感谢你带来的消息，感谢艾哈沐大人帮我儿子找到的这份好差事。", description = "\t不要多问，把这封信带给他，他正在等待。", tips = "" }, 
                                        { missionItemId = 13011600, talking = "\t我的心情好多了，谢谢你带来的消息！", description = "\t战乱让他们妻离子散，我的朋友最近心情很坏，你帮我带一封信安慰一下。", tips = "" }, 
                                        { missionItemId = 13011600, talking = "\t我的心情好多了，谢谢你带来的消息！", description = "\t听说西北叛军刚洗劫了他们那里，我很担心一位朋友的安全，你帮我带封信去问候一下。", tips = "" }, 
                                        { missionItemId = 13011600, talking = "\t感谢你带来的消息。", description = "\t战乱让他们妻离子散，我的朋友最近心情很坏，你帮我带一封信安慰一下。", tips = "" }
}
-- 送信目标
x300512_g_DeliverTarget             = {
                                        { targetId = 129003, description = "\t把@item_%d#W送给@npc_%d#W或收集#G%d#W个@item_%d#W(2倍经验)。" }, 
                                        { targetId = 129039, description = "\t把@item_%d#W送给@npc_%d#W或收集#G%d#W个@item_%d#W(2倍经验)。" }, 
                                        { targetId = 129006, description = "\t把@item_%d#W送给@npc_%d#W或收集#G%d#W个@item_%d#W(2倍经验)。" }, 
                                        { targetId = 129007, description = "\t把@item_%d#W送给@npc_%d#W或收集#G%d#W个@item_%d#W(2倍经验)。" }, 
                                        { targetId = 129018, description = "\t把@item_%d#W送给@npc_%d#W或收集#G%d#W个@item_%d#W(2倍经验)。" }, 
                                        { targetId = 129019, description = "\t把@item_%d#W送给@npc_%d#W或收集#G%d#W个@item_%d#W(2倍经验)。" }, 
                                        { targetId = 129020, description = "\t把@item_%d#W送给@npc_%d#W或收集#G%d#W个@item_%d#W(2倍经验)。" }, 
                                        { targetId = 129021, description = "\t把@item_%d#W送给@npc_%d#W或收集#G%d#W个@item_%d#W(2倍经验)。" }, 
                                        { targetId = 129022, description = "\t把@item_%d#W送给@npc_%d#W或收集#G%d#W个@item_%d#W(2倍经验)。" }, 
                                        { targetId = 129023, description = "\t把@item_%d#W送给@npc_%d#W或收集#G%d#W个@item_%d#W(2倍经验)。" }, 
                                        { targetId = 129024, description = "\t把@item_%d#W送给@npc_%d#W或收集#G%d#W个@item_%d#W(2倍经验)。" }, 
                                        { targetId = 129025, description = "\t把@item_%d#W送给@npc_%d#W或收集#G%d#W个@item_%d#W(2倍经验)。" }, 
                                        { targetId = 129026, description = "\t把@item_%d#W送给@npc_%d#W或收集#G%d#W个@item_%d#W(2倍经验)。" },
										{ targetId = 129027, description = "\t把@item_%d#W送给@npc_%d#W或收集#G%d#W个@item_%d#W。" }
}
-- 杀怪任务表
x300512_g_KillMonsterTable          = {
                                        { monsterId = 594, posId = 15021, count = 3, name = "潜伏士兵", 
                                          target = "  前往@npcsp_塔塔尔部剧场_59632，消灭#R%d#W个@npc_%d#W(%d/%d)或收集#G%d#W个@item_%d#W(2倍经验)",
                                          description = "\t我们不久前派出一些部下，试图穿越记忆之门和我们的祖先取得联系，可是他们在@npcsp_塔塔尔部剧场_59632处遭到了袭击，全军覆没。\n\t你现在赶去那里，除掉那些残暴的@npc_15021！", tips = "" },  -- 怪物类型、寻路、要杀数量
                                        { monsterId = 630, posId = 16007, count = 3, name = "乃蛮斥候", 
                                          target = "  前往@npcsp_克烈部剧场_59632，消灭#R%d#W个@npc_%d#W(%d/%d)或收集#G%d#W个@item_%d#W(2倍经验)",
                                          description = "\t我们不久前派出一些部下，试图穿越记忆之门和我们的祖先取得联系，可是他们在@npcsp_克烈部剧场_59632处遭到了袭击，全军覆没。\n\t你现在赶去那里，除掉那些残暴的@npc_16007！", tips = "" },  -- 怪物类型、寻路、要杀数量
                                        { monsterId = 748, posId = 105315, count = 3, name = "塔塔尔士兵", 
                                          target = "  前往@npcsp_乃蛮部剧场_59632，消灭#R%d#W个@npc_%d#W(%d/%d)或收集#G%d#W个@item_%d#W(2倍经验)",
                                          description = "\t我们不久前派出一些部下，试图穿越记忆之门和我们的祖先取得联系，可是他们在@npcsp_乃蛮部剧场_59632处遭到了袭击，全军覆没。\n\t你现在赶去那里，除掉那些残暴的@npc_105315！", tips = "" },  -- 怪物类型、寻路、要杀数量
                                        { monsterId = 1013, posId = 19014, count = 3, name = "群牧监守备", 
                                          target = "  前往@npcsp_太行山剧场_59632，消灭#R%d#W个@npc_%d#W(%d/%d)或收集#G%d#W个@item_%d#W(2倍经验)",
                                          description = "\t我们不久前派出一些部下，试图穿越记忆之门和我们的祖先取得联系，可是他们在@npcsp_太行山剧场_59632处遭到了袭击，全军覆没。\n\t你现在赶去那里，除掉那些残暴的@npc_19014！", tips = "" },  -- 怪物类型、寻路、要杀数量
                                        { monsterId =641, posId = 20018, count = 3, name = "红寡妇", 
                                          target = "  前往@npcsp_凤翔府剧场_59632，消灭#R%d#W个@npc_%d#W(%d/%d)或收集#G%d#W个@item_%d#W(2倍经验)",
                                          description = "\t我们不久前派出一些部下，试图穿越记忆之门和我们的祖先取得联系，可是他们在@npcsp_凤翔府剧场_59632处遭到了袭击，全军覆没。\n\t你现在赶去那里，除掉那些残暴的@npc_20018！", tips = "" },  -- 怪物类型、寻路、要杀数量
                                        { monsterId = 1003, posId = 18018, count = 3, name = "银狼", 
                                          target = "  前往@npcsp_阿尔金山剧场_59632，消灭#R%d#W个@npc_%d#W(%d/%d)或收集#G%d#W个@item_%d#W(2倍经验)",
                                          description = "\t我们不久前派出一些部下，试图穿越记忆之门和我们的祖先取得联系，可是他们在@npcsp_阿尔金山剧场_59632处遭到了袭击，全军覆没。\n\t你现在赶去那里，除掉那些残暴的@npc_18018！", tips = "" },  -- 怪物类型、寻路、要杀数量
                                        { monsterId = 680, posId = 21035, count = 3, name = "猛安军溃兵", 
                                          target = "  前往@npcsp_蔡州城剧场_59632，消灭#R%d#W个@npc_%d#W(%d/%d)或收集#G%d#W个@item_%d#W(2倍经验)",
                                          description = "\t我们不久前派出一些部下，试图穿越记忆之门和我们的祖先取得联系，可是他们在@npcsp_蔡州城剧场_59632处遭到了袭击，全军覆没。\n\t你现在赶去那里，除掉那些残暴的@npc_21035！", tips = "" },  -- 怪物类型、寻路、要杀数量
}
-- 杀怪任务等级配置(mosterSet里放的是x300512_g_KillMonsterTable怪物索引)
x300512_g_KillMonsterLevel          = {
                                        { minLevel = 25, maxLevel = 30, mosterSet = { 1 } }, 
                                        { minLevel = 30, maxLevel = 35, mosterSet = { 1, 2	} }, 
                                        { minLevel = 35, maxLevel = 40, mosterSet = { 1, 2, 3 } }, 
                                        { minLevel = 40, maxLevel = 50, mosterSet = { 1, 2 , 3, 4 } }, 
                                        { minLevel = 50, maxLevel =160, mosterSet = { 1, 2 , 3, 4, 5 } }, 
                                        --{ minLevel = 50, maxLevel = 60, mosterSet = { 1, 2 , 3, 4, 5, 6 } }, 
                                        --{ minLevel = 60, maxLevel = 160, mosterSet = { 1, 2 , 3, 4, 5, 6, 7 } }
}
-- 采集任务等级配置
x300512_g_CollectLevel              = {
                                        { minLevel = 25, maxLevel = 160, gpSet = { 1, 2, 3, 4  } }, 
}
-- 护送任务表
x300512_g_EscortTable               = {
                                        { escortType = 10,	npcGuid = 129007,	name = "骑乘恢复人",
                                            targetGuid = 129038,	targetname = "中原草药大师",	missionName = "马匹",
                                            finish = "\t谢谢你，总算是送来了，我正要再派人去催呢。",
                                            getmiss = "\t见到你太好了，#Y@myname#W，中原草药大师正需要一匹好马来帮她运送货物，我这里的人手现在很紧张，只好请你帮我把这匹马安全护送她那里去了，你愿意帮我这个忙么？",
                                            intro = "\t骑乘繁殖大师@npc_129007需要把战马送往各地，你去看看他那里有什么需要你帮忙的。",
                                            description = "描述。", 
                                            tips = "小提示。"
                                        }, 
                                        { escortType = 11, npcGuid = 131000, name = "雄鹰长老", 
                                            targetGuid = 131037, targetname = "金虎", missionName = "粮车",
                                            finish = "\t又来了一辆粮车，非常感谢你！", 
                                            getmiss = "\t刚才@npc_131037又派人来催促这批粮食了，我这里实在是脱不开身，你能帮我把这车粮食送到他那里去么？", 
                                            intro = "\t昆仑猎场的粮食是我国粮产的主要来源，你去@npc_131000那里看看有什么需要你帮忙的。",
                                            description = "描述。", 
                                            tips = "小提示。"
                                        }, 
                                        { escortType = 12, npcGuid = 129016, name = "耶律峰",
                                            targetGuid = 129177, targetname = "王城御卫长",   missionName = "村民",
                                            finish = "\t啊，这是谁家的孩子走丢了？好的，我会帮她找到父母的！", 
                                            getmiss = "\t你来的正好，#Y@myname#W，我还正在为怎么把这个迷路的小家伙送回家而发愁呢，我正有要事在身，所以想麻烦你帮我把这个小孩送到@npc_129177那里去，我知道你一定不会拒绝。", 
                                            intro = "\t听说@npc_129016遇到了一些麻烦，你去问问他有没有需要帮助的。",
                                            description = "描述。", 
                                            tips = "小提示。"
                                        }, 
                                        { escortType = 13, npcGuid = 129181, name = "城东商人", 
                                            targetGuid = 129077, targetname = "锻造大师",   missionName = "矿车",
                                            finish = "\t感谢你能及时把这个送过来，我们正等着用呢。", 
                                            getmiss = "\t#Y@myname#W，你来的正好，@npc_129077那里急需这些矿石，我现在有些更重要的事要忙，早听说过你不仅本领高强，而且侠义心肠，这车矿石对你来说应该不是什么麻烦吧？", 
                                            intro = "\t@npc_129181那里遇到了一点麻烦，你能去那边帮忙吗？",
                                            description = "描述。", 
                                            tips = "小提示。"
                                        }, 
                                        { escortType = 14, npcGuid = 129182, name = "城西商人",
                                            targetGuid = 129007, targetname = "骑乘恢复", missionName = "海货",
                                            finish = "\t啊，谢谢你，看来我们今天的晚餐会很丰盛。", 
                                            getmiss = "\t我手里的海产可是鼎鼎有名，慕名而来的人络绎不绝，上次@npc_129007订购了一些，不过我最近人手紧张，能麻烦你帮我送去么？", 
                                            intro = "\t王城汇聚了众多商人他们手里有很多珍奇物品，你去@npc_129182那边看看有什么可以帮得上的。",
                                            description = "描述。", 
                                            tips = "小提示。"
                                        }, 
                                        { escortType = 15, npcGuid = 129066, name = "王国押运官",
                                            targetGuid = 129177, targetname = "王城御卫长",   missionName = "朝廷圣物", 
                                            finish = "\t送来了么？唔，辛苦你了。", 
                                            getmiss = "\t这车中装的是朝廷的圣物，我物色了很久才决定请你担当起这个重要的职责，秘密地将它送到@npc_129177那里，千万不要走漏风声或者私自拆开查看，你知道，过度的好奇心有时候是很危险的。", 
                                            intro = "\t我接到一宗任务，但可惜抽不出身来，可否拜托你来替我做这件事呢？去找@npc_129066吧，他会告诉你更多的。",
                                            description = "描述。", 
                                            tips = "小提示。"
                                        }, 
}                                                                                                   
-- 护送任务等级配置
x300512_g_EscortLevel               = {
                                        { minLevel = 25, maxLevel = 39, missions = 
                                            { 1, 2, 3 }
                                        },
                                        { minLevel = 40, maxLevel = 160, missions = 
                                            { 1, 2, 3, 4, 5, 6 }
                                        },
}
-- 挖掘任务配置
x300512_g_DigTarget                 = {
                                        {   id = 13013000, name = "仙灵玉石", 
                                            target = "\t最近我观察圣山之上灵气异常，其地脉更是有仙龙为照，山中定然有很多鲜为人知的化石材料，请你首先到@npc_129003那里购买一个铁铲，用铁铲去#aB#h00CCFF{goto_%d,%d,%d}(%d，%d)#aE附近探索一番，看看有没有#G%s#W。或收集#G%d#W个@item_%d#W(2倍经验)。", 
                                        }, 
                                        {   id = 13013001, name = "仙灵光石", 
                                            target = "\t最近我观察圣山之上灵气异常，其地脉更是有仙龙为照，山中定然有很多鲜为人知的化石材料，请你首先到@npc_129003那里购买一个铁铲，用铁铲去#aB#h00CCFF{goto_%d,%d,%d}(%d，%d)#aE附近探索一番，看看有没有#G%s#W。或收集#G%d#W个@item_%d#W(2倍经验)。", 
                                        }, 
                                        {   id = 13013002, name = "仙灵彩石", 
                                            target = "\t最近我观察圣山之上灵气异常，其地脉更是有仙龙为照，山中定然有很多鲜为人知的化石材料，请你首先到@npc_129003那里购买一个铁铲，用铁铲去#aB#h00CCFF{goto_%d,%d,%d}(%d，%d)#aE附近探索一番，看看有没有#G%s#W。或收集#G%d#W个@item_%d#W(2倍经验)。", 
                                        }, 
                                        {   id = 13013003, name = "仙灵暗石", 
                                            target = "\t最近我观察圣山之上灵气异常，其地脉更是有仙龙为照，山中定然有很多鲜为人知的化石材料，请你首先到@npc_129003那里购买一个铁铲，用铁铲去#aB#h00CCFF{goto_%d,%d,%d}(%d，%d)#aE附近探索一番，看看有没有#G%s#W。或收集#G%d#W个@item_%d#W(2倍经验)。", 
                                        }, 
                                        {   id = 13013004, name = "仙灵玄石", 
                                            target = "\t最近我观察圣山之上灵气异常，其地脉更是有仙龙为照，山中定然有很多鲜为人知的化石材料，请你首先到@npc_129003那里购买一个铁铲，用铁铲去#aB#h00CCFF{goto_%d,%d,%d}(%d，%d)#aE附近探索一番，看看有没有#G%s#W。或收集#G%d#W个@item_%d#W(2倍经验)。", 
                                        }, 
}
-- 挖掘任务等级配置
x300512_g_DigLevel                  = {
                                        { minLevel = 25, maxLevel = 160, missions = 
                                            { 1, 2, 3 , 4, 5}
                                        },

}
-- 挖掘任务坐标配置
x300512_g_CoordinateLib             = {
                                        { posX = 95, posZ = 17  }, 
                                        { posX = 161, posZ = 18  }, 
                                        { posX = 27, posZ = 108  }, 
                                        { posX = 28, posZ = 161  }, 
                                        { posX = 228, posZ = 164 }, 
}
-- 收马任务配置
x300512_g_GetHorse                  = {
                                        { id = 101, name = "蒙古马", 
                                          info = "\t国家正在征收战马，以供前线，如果你有#G%s#W，请务必上交给我。当然，如果你能找到一匹#G良品以上的%s#W来，我会给你更好的奖励。", 
                                          description = "\t前往@npcsp_马场_90200收集一匹普通或良品(2倍经验)#G%s。"
                                        }, 
                                        { id = 201, name = "三河马", 
                                          info = "\t国家正在征收战马，以供前线，如果你有#G%s#W，请务必上交给我。当然，如果你能找到一匹#G良品以上的%s#W来，我会给你更好的奖励。", 
                                          description = "\t前往@npcsp_马场_90201收集一匹普通或良品(2倍经验)#G%s。"
                                        }, 
                                        { id = 301, name = "伊犁马", 
                                          info = "\t国家正在征收战马，以供前线，如果你有#G%s#W，请务必上交给我。当然，如果你能找到一匹#G良品以上的%s#W来，我会给你更好的奖励。", 
                                          description = "\t前往@npcsp_马场_90202收集一匹普通或良品(2倍经验)#G%s。"
                                        }, 
                                        { id = 401, name = "波斯马", 
                                          info = "\t国家正在征收战马，以供前线，如果你有#G%s#W，请务必上交给我。当然，如果你能找到一匹#G良品以上的%s#W来，我会给你更好的奖励。", 
                                          description = "\t前往@npcsp_马场_90203收集一匹普通或良品(2倍经验)#G%s。"
                                        },
                                        { id = 501, name = "天方马", 
                                          info = "\t国家正在征收战马，以供前线，如果你有#G%s#W，请务必上交给我。当然，如果你能找到一匹#G良品以上的%s#W来，我会给你更好的奖励。", 
                                          description = "\t前往@npcsp_马场_90204收集一匹普通或良品(2倍经验)#G%s。"
                                        },
}
-- 收马任务配置
x300512_g_GetHorseLevel             = { 
                                        { minLevel = 25, maxLevel = 39, missions = 
                                            { 1 }
                                            },
                                        { minLevel = 40, maxLevel = 59, missions = 
                                            { 2 }
                                            },
                                        { minLevel = 60, maxLevel = 160, missions = 
                                            { 3, 4, 5}                                                                        
                                            },
}
-- 材料收集配置
x300512_g_MaterialTable             = {
                                        { base = 12010100, 
                                          advanced = { 12010101, 12010101, 12010101 },
                                          xpCoff = { 2, 2, 2 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "  收集@item_%d",
                                          description = "\t一位统领在和海盗的厮杀中受了重伤，当务之急是给他止血，马奶是疗伤的良药我们正在努力收集。",
                                          target = "  收集@item_%d#W或@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10011101, 
                                          advanced = { 11041030, 11041030, 11041030 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "  去@npc_129027处购买@item_%d",
                                          description = "\t我们军方储备的武器已经不足以装备那支刚组成的部队了，你去@npc_129027那里买一件武器来给我，我要看看适不适合大批量的采购。",
                                          target = "  去@npc_129027处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10021101, 
                                          advanced = { 11041030, 11041030, 11041030 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "  去@npc_129027处购买@item_%d",
                                          description = "\t又要开始战争了，我们目前急于储备的军械物资。",
                                          target = "  去@npc_129027处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10041101, 
                                          advanced = { 11041030, 11041030, 11041030 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "  去@npc_129027处购买@item_%d",
                                          description = "\t又要开始战争了，我们目前急于储备的军械物资。",
                                          target = "  去@npc_129027处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10051101, 
                                          advanced = { 11041050, 11041050, 11041050 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "  去@npc_129027处购买@item_%d",
                                          description = "\t我们军方储备的武器已经不足以装备那支刚组成的部队了，你去@npc_129027那里买一件武器来给我，我要看看是不适合大批量的采购。",
                                          target = "  去@npc_129027处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10061101, 
                                          advanced = { 11041050, 11041050, 11041050 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "  去@npc_129027处购买@item_%d",
                                          description = "\t太子决定派出戍边军平息王城附近的乱匪，现在军用物资短缺，你可否帮忙收集一些。",
                                          target = "  去@npc_129027处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10031101, 
                                          advanced = { 11041000, 11041000, 11041000 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "  去@npc_129027处购买@item_%d",
                                          description = "\t太子决定派出戍边军平息王城附近的乱匪，现在军用物资短缺，你可否帮忙收集一些。",
                                          target = "  去@npc_129027处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10261101, 
                                          advanced = { 11041000, 11041000, 11041000 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "  去@npc_129026处购买@item_%d",
                                          description = "\t又要开始战争了，我们目前急于储备的军械物资。",
                                          target = "  去@npc_129026处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10231101, 
                                          advanced = { 11041040, 11041040, 11041040 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "  去@npc_129026处购买@item_%d",
                                          description = "\t又要开始战争了，我们目前急于储备的军械物资。",
                                          target = "  去@npc_129026处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10271101, 
                                          advanced = { 11041040, 11041040, 11041040 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "  去@npc_129026处购买收集@item_%d",
                                          description = "\t我们的一个士兵要运送一批物资补给前线的战士们，可是现在国库积攒的物资实在难以为继，希望你能帮帮忙。",
                                          target = "  去@npc_129026处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10201101, 
                                          advanced = { 11041020, 11041020, 11041020 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "  去@npc_129026处购买@item_%d",
                                          description = "\t太子决定派出戍边军平息王城附近的乱匪，现在军用物资短缺，你可否帮忙收集一些。",
                                          target = "  去@npc_129026处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10251101, 
                                          advanced = { 11041020, 11041020, 11041020 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t去@npc_129026处购买@item_%d",
                                          description = "\t为了对付叛军，我们训练的强度很大，但是我们的军械物资奇缺，可否帮我们解决一些。",
                                          target = "  去@npc_129026处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10241101, 
                                          advanced = { 11041010, 11041010, 11041010 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t去@npc_129026处购买@item_%d",
                                          description = "\t为了对付叛军，我们训练的强度很大，但是我们的军械物资奇缺，可否帮我们解决一些。",
                                          target = "  去@npc_129026处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 12010001, 
                                          advanced = { 11041010, 11041010, 11041010 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t收集@item_%d",
                                          description = "\t又要开始战争了，我们目前急于储备的军械物资。",
                                          target = "  去@npc_129025处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10011102, 
                                          advanced = { 11041030, 11041031 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t收集@item_%d",
                                          description = "\t我们军方储备的武器已经不足以装备那支刚组成的部队了，你去@npc_129027那里买一件武器来给我，我要看看是不适合大批量的采购。",
                                          target = "  去@npc_129027处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10021102, 
                                          advanced = { 11041030, 11041031 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t收集@item_%d",
                                          description = "\t又要开始战争了，我们目前急于储备的军械物资。",
                                          target = "  去@npc_129027处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10041102, 
                                          advanced = { 11041030, 11041031 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t收集@item_%d",
                                          description = "\t又要开始战争了，我们目前急于储备的军械物资。",
                                          target = "  去@npc_129027处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10051102, 
                                          advanced = { 11041050, 11041051 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t收集@item_%d",
                                          description = "\t太子决定派出戍边军平息王城附近的乱匪，现在军用物资短缺，你可否帮忙收集一些。",
                                          target = "  去@npc_129027处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10061102, 
                                          advanced = { 11041050, 11041051 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t收集@item_%d",
                                          description = "\t我们军方储备的武器已经不足以装备那支刚组成的部队了，你去@npc_129027那里买一件武器来给我，我要看看是不适合大批量的采购。",
                                          target = "  去@npc_129027处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10031102, 
                                          advanced = { 11041000, 11041001 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t收集@item_%d",
                                          description = "\t又要开始战争了，我们目前急于储备的军械物资。",
                                          target = "  去@npc_129027处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10261102, 
                                          advanced = { 11041000, 11041001 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t收集@item_%d",
                                          description = "\t又要开始战争了，我们目前急于储备的军械物资。",
                                          target = "  去@npc_129026处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10231102, 
                                          advanced = { 11041040, 11041041 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t收集@item_%d",
                                          description = "\t我们的一个士兵要运送一批物资补给前线的战士们，可是现在国库积攒的物资实在难以为继，希望你能帮帮忙。",
                                          target = "  去@npc_129026处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10271102, 
                                          advanced = { 11041040, 11041041 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t收集@item_%d",
                                          description = "\t太子决定派出戍边军平息王城附近的乱匪，现在军用物资短缺，你可否帮忙收集一些。",
                                          target = "  去@npc_129026处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10201102, 
                                          advanced = { 11041020, 11041021 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t收集@item_%d",
                                          description = "\t天冷了，我们征讨叛军的军队需要补给，王城装备武器等店的东西物美价廉，可否代为购买以些。",
                                          target = "  去@npc_129026处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10251102, 
                                          advanced = { 11041020, 11041021 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t收集@item_%d",
                                          description = "\t我们的一个士兵要运送一批物资补给前线的战士们，可是现在国库积攒的物资实在难以为继，希望你能帮帮忙。",
                                          target = "  去@npc_129026处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10241102, 
                                          advanced = { 11041010, 11041011 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t收集@item_%d",
                                          description = "\t为了对付叛军，我们训练的强度很大，但是我们的军械物资奇缺，可否帮我们解决一些。",
                                          target = "  去@npc_129026处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 12010002, 
                                          advanced = { 11041010, 11041011 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t收集@item_%d",
                                          description = "\t为了对付叛军，我们训练的强度很大，但是我们的军械物资奇缺，可否帮我们解决一些。",
                                          target = "  去@npc_129025处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10011106, 
                                          advanced = { 11041030, 11041031, 11041032 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t收集@item_%d",
                                          description = "\t我们军方储备的武器已经不足以装备那支刚组成的部队了，你去@npc_139057那里买一件武器来给我，我要看看是不适合大批量的采购。",
                                          target = "  去大都@npc_139057处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10021106, 
                                          advanced = { 11041030, 11041031, 11041032 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t收集@item_%d",
                                          description = "\t太子决定派出戍边军平息王城附近的乱匪，现在军用物资短缺，你可否帮忙收集一些。",
                                          target = "  去大都@npc_139057处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10041106, 
                                          advanced = { 11041030, 11041031, 11041032 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t收集@item_%d",
                                          description = "\t天冷了，我们征讨叛军的军队需要补给，王城装备武器等店的东西物美价廉，可否代为购买以些。",
                                          target = "  去大都@npc_139057处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10051106, 
                                          advanced = { 11041050, 11041051, 11041052 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t收集@item_%d",
                                          description = "\t我们军方储备的武器已经不足以装备那支刚组成的部队了，你去@npc_129027那里买一件武器来给我，我要看看是不适合大批量的采购。",
                                          target = "  去大都@npc_139057处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10061106, 
                                          advanced = { 11041050, 11041051, 11041052 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t收集@item_%d",
                                          description = "\t我们的一个士兵要运送一批物资补给前线的战士们，可是现在国库积攒的物资实在难以为继，希望你能帮帮忙。",
                                          target = "  去大都@npc_139057处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10031106, 
                                          advanced = { 11041000, 11041001, 11041002 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t收集@item_%d",
                                          description = "\t太子决定派出戍边军平息王城附近的乱匪，现在军用物资短缺，你可否帮忙收集一些。",
                                          target = "  去大都@npc_139057处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10261106, 
                                          advanced = { 11041000, 11041001, 11041002 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t收集@item_%d",
                                          description = "\t天冷了，我们征讨叛军的军队需要补给，王城装备武器等店的东西物美价廉，可否代为购买以些。",
                                          target = "  去大都@npc_139058处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10231106, 
                                          advanced = { 11041040, 11041041, 11041042 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t收集@item_%d",
                                          description = "\t天冷了，我们征讨叛军的军队需要补给，王城装备武器等店的东西物美价廉，可否代为购买以些。",
                                          target = "  去大都@npc_139058处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10271106, 
                                          advanced = { 11041040, 11041041, 11041042 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t收集@item_%d",
                                          description = "\t我们的一个士兵要运送一批物资补给前线的战士们，可是现在国库积攒的物资实在难以为继，希望你能帮帮忙。",
                                          target = "  去大都@npc_139058处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10201106, 
                                          advanced = { 11041020, 11041021, 11041022 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t收集@item_%d",
                                          description = "\t我们的一个士兵要运送一批物资补给前线的战士们，可是现在国库积攒的物资实在难以为继，希望你能帮帮忙。",
                                          target = "  去大都@npc_139058处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10251106, 
                                          advanced = { 11041020, 11041021, 11041022 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t收集@item_%d",
                                          description = "\t又要开始战争了，我们目前急于储备的军械物资。",
                                          target = "  去大都@npc_139058处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 10241106, 
                                          advanced = { 11041010, 11041011, 11041012 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t收集@item_%d",
                                          description = "\t又要开始战争了，我们目前急于储备的军械物资。",
                                          target = "  去大都@npc_139058处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        }, 

                                        { base = 12010003, 
                                          advanced = { 11041010, 11041011, 11041012 },
                                          xpCoff = { 2, 3,  4 },
                                          money = { 2000, 5000, 12000 },
                                          baseTarget = "\t收集@item_%d",
                                          description = "\t又要开始战争了，我们目前急于储备的军械物资。",
                                          target = "  去@npc_129025处购买@item_%d#W或去收集@item_%d#W(%d倍经验)#W"
                                        },                                                                               
}
-- 材料收集等级配置
x300512_g_MaterialLevel             = {
                                        { minLevel = 25, maxLevel = 39, missions = 
                                            { 1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 13, 14 }, choose = 1
                                        },
                                        { minLevel = 40, maxLevel = 59, missions = 
                                            { 1, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27 }, choose = 2
                                        },
                                        { minLevel = 60, maxLevel = 160, missions = 
                                            { 1, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40 }, choose = 3
                                        },
}
-- 护送目标可提交的最远距离
x300512_g_EscortMaxDistance         = 20
-- GM任务类型
x300512_g_MissionType               = 0
-- 等级提交物品对应表
x300512_g_Item2Level                = {
                                        { minLevel = 25, maxLevel = 39, 
                                          items = {
                                                    { id = 11020001, count = 10 }, 
                                                    { id = 11020002, count = 10 }, 
                                                    { id = 11030001, count = 10 }, 
                                                    { id = 11030401, count = 10 }, 
                                                }
                                        }, 
                                        { minLevel = 40, maxLevel = 59, 
                                          items = {
                                                    { id = 11020001, count = 10 }, 
                                                    { id = 11020002, count = 10 }, 
                                                    { id = 11030001, count = 10 }, 
                                                    { id = 11030401, count = 10 }, 
                                                    { id = 11020006, count = 10 }, 
                                                    { id = 11020007, count = 10 }, 
                                                    { id = 11030003, count = 10 }, 
                                                    { id = 11030402, count = 10 }, 
                                                }
                                        }, 
                                        { minLevel = 60, maxLevel = 69, 
                                          items = {
                                                    { id = 11020001, count = 10 }, 
                                                    { id = 11020002, count = 10 }, 
                                                    { id = 11030001, count = 10 }, 
                                                    { id = 11030401, count = 10 }, 
                                                    { id = 11020006, count = 10 }, 
                                                    { id = 11020007, count = 10 }, 
                                                    { id = 11030003, count = 10 }, 
                                                    { id = 11030402, count = 10 }, 
                                                    { id = 11020010, count = 10 }, 
                                                    { id = 11020011, count = 10 }, 
                                                    { id = 11030005, count = 10 }, 
                                                    { id = 11030404, count = 10 }, 
                                                }
                                        }, 
                                        { minLevel = 70, maxLevel = 255, 
                                          items = {
                                                    { id = 11020001, count = 10 }, 
                                                    { id = 11020002, count = 10 }, 
                                                    { id = 11030001, count = 10 }, 
                                                    { id = 11030401, count = 10 }, 
                                                    { id = 11020006, count = 10 }, 
                                                    { id = 11020007, count = 10 }, 
                                                    { id = 11030003, count = 10 }, 
                                                    { id = 11030402, count = 10 }, 
                                                    { id = 11020010, count = 10 }, 
                                                    { id = 11020011, count = 10 }, 
                                                    { id = 11030005, count = 10 }, 
                                                    { id = 11030404, count = 10 }, 
                                                    { id = 11020015, count = 10 }, 
                                                    { id = 11020014, count = 10 }, 
                                                    { id = 11030007, count = 10 }, 
                                                    { id = 11030404, count = 10 }, 
                                                }
                                        }, 
}
-- 
x300512_g_FinishBound               = 1000

function x300512_GetRandomItemID( level)
    for i, item in x300512_g_Item2Level do
        if level >= item.minLevel and level <= item.maxLevel then
            return item.items[ random( 1, getn( item.items) ) ]
        end
    end
end

-- 添加送信任务
function x300512_GetDeliverMission( sceneId, selfId, NPCId)
    return x300512_GetDeliverMissionImpl( sceneId, selfId, NPCId)
end

-- 添加打怪任务
function x300512_GetKillMonsterMission( sceneId, selfId, NPCId)
    return x300512_GetKillMonsterMissionImpl( sceneId, selfId, NPCId)
end

-- 添加采集任务
function x300512_GetCollectMission( sceneId, selfId, NPCId)
    return x300512_GetCollectMissionImpl( sceneId, selfId, NPCId)
end

-- 添加护送任务
function x300512_GetEscortMission( sceneId, selfId, NPCId)
    return x300512_GetEscortMissionImpl( sceneId, selfId, NPCId)
end

-- 添加挖掘任务
function x300512_GetDigMission( sceneId, selfId, NPCId)
    return x300512_GetDigMissionImpl( sceneId, selfId, NPCId)
end

-- 添加收马任务
function x300512_GetObtainHorseMission( sceneId, selfId, NPCId)
    return x300512_GetObtainHorseMissionImpl( sceneId, selfId, NPCId)
end

-- 添加收集材料任务
function x300512_GetObtainMaterialMission( sceneId, selfId, NPCId)
    return x300512_GetObtainMaterialMissionImpl( sceneId, selfId, NPCId)
end

-- 获得前5环任务函数集
x300512_g_GetMissionHead            = {
                                        x300512_GetDeliverMission,     -- 送信任务
                                        x300512_GetKillMonsterMission, -- 打怪任务
                                        x300512_GetCollectMission,     -- 采集任务
                                        x300512_GetEscortMission,      -- 护送任务
                                        x300512_GetDigMission          -- 挖掘任务
}
-- 获得后5环任务函数集
x300512_g_GetMissionEnd             = {
                                        x300512_GetObtainHorseMission,      -- 收马任务
                                        x300512_GetObtainMaterialMission    -- 材料收集任务
}
-- 前5环获取任务比例表
x300512_g_HeadMissionTable          = {
                                        {
                                            low = 25, high = 30,            -- 接任务等级段
                                            config = { 20, 20, 20, 20, 20 },-- 每种任务的选取比例
                                        },
                                        {
                                            low = 31, high = 35,            -- 接任务等级段
                                            config = { 20, 20, 20, 20, 20 },-- 每种任务的选取比例
                                        },
                                        {
                                            low = 36, high = 40,            -- 接任务等级段
                                            config = { 20, 20, 20, 20, 20 },-- 每种任务的选取比例
                                        },
                                        {
                                            low = 41, high = 45,            -- 接任务等级段
                                            config = { 20, 20, 20, 20, 20 },-- 每种任务的选取比例
                                        },
                                        {
                                            low = 46, high = 50,            -- 接任务等级段
                                            config = { 20, 20, 20, 20, 20 },-- 每种任务的选取比例
                                        },
                                        {
                                            low = 51, high = 55,            -- 接任务等级段
                                            config = { 20, 20, 20, 20, 20 },-- 每种任务的选取比例
                                        },
                                        {
                                            low = 56, high = 60,            -- 接任务等级段
                                            config = { 20, 20, 20, 20, 20 },-- 每种任务的选取比例
                                        },
                                        {
                                            low = 60, high = 160,            -- 接任务等级段
                                            config = { 20, 20, 20, 20, 20 },-- 每种任务的选取比例
                                        },
}
-- 后5环获取任务比例表
x300512_g_EndMissionTable           = {
                                        {
                                            low = 25, high = 30,            -- 接任务等级段
                                            config = { 20, 80 },            -- 每种任务的选取比例
                                        },
                                        {
                                            low = 31, high = 35,            -- 接任务等级段
                                            config = { 20, 80 },            -- 每种任务的选取比例
                                        },
                                        {
                                            low = 36, high = 40,            -- 接任务等级段
                                            config = { 20, 80 },            -- 每种任务的选取比例
                                        },
                                        {
                                            low = 41, high = 45,            -- 接任务等级段
                                            config = { 20, 80 },            -- 每种任务的选取比例
                                        },
                                        {
                                            low = 46, high = 50,            -- 接任务等级段
                                            config = { 20, 80 },            -- 每种任务的选取比例
                                        },
                                        {
                                            low = 51, high = 55,            -- 接任务等级段
                                            config = { 20, 80 },            -- 每种任务的选取比例
                                        },
                                        {
                                            low = 56, high = 60,            -- 接任务等级段
                                            config = { 20, 80 },            -- 每种任务的选取比例
                                        },
                                        {
                                            low = 61, high = 160,           -- 接任务等级段
                                            config = { 20, 80 },            -- 每种任务的选取比例
                                        },
}

function x300512_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
    if GetGameOpenById( x300512_g_IsEnableId) <= 0 then
        return 0
    end

	local level = GetLevel( sceneId, selfId)
	if level < x300512_g_LevelLess then
		 return
	end

    -- 如果玩家已经接受老国家内政
    local oldMissionId = x300512_GetMD( sceneId, selfId, MD_GUOJIARENWU_RANDMISSIONID)
    if oldMissionId > 0 then
        if IsHaveQuest( sceneId, selfId, oldMissionId) > 0 then
            return
        else
            x300512_SetMD( sceneId, selfId, MD_GUOJIARENWU_RANDMISSIONID, 0)
        end
    end

    local state = GetQuestStateNM( sceneId, selfId, NPCId, x300512_g_MissionId)
    AddQuestNumText( sceneId, x300512_g_MissionId, x300512_g_MissionName, state, 1)
end

function x300512_ProcEventEntry( sceneId, selfId, NPCId, MissionId, nExtIdx)	--点击该任务后执行此脚本
	if IsHaveQuest( sceneId, selfId, x300512_g_MissionId) > 0 then -- 已经接任务了
        local bDone = x300512_CheckSubmit( sceneId, selfId, NPCId)
        SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, 0)
        if bDone > 0 then
            -- 判断是不是交任务NPC
            if GetMonsterGUID( sceneId, NPCId) == x300512_SubmitNPCGUID then
                local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
                local misType = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_MissionType)
                local index = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET2)
                local mp3 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET3)
                if misType == x300512_g_MT_Material then
                    BeginUICommand( sceneId)
                        UICommand_AddInt( sceneId, x300512_g_ScriptId)
                        UICommand_AddInt( sceneId, x300512_g_MissionId)
                        UICommand_AddInt( sceneId, NPCId)
                        UICommand_AddInt( sceneId, x300512_g_MaterialTable[ index].base)
                        UICommand_AddInt( sceneId, x300512_g_MaterialTable[ index].advanced[ mp3] )
                        DispatchUICommand( sceneId, selfId, 104)
                    EndUICommand( sceneId)

                    BeginQuestEvent( sceneId)
                    AddQuestText( sceneId, "#Y"..x300512_g_MissionName)
                        AddQuestText( sceneId, "\t你想上交哪个物品呢？" )
                    EndQuestEvent( sceneId)
                    DispatchQuestEventList( sceneId, selfId, NPCId)
                    return
                elseif misType == x300512_g_MT_Horse then
                    -- 通知客户端显示宠物列表窗口
                    BeginUICommand( sceneId)
                        UICommand_AddInt( sceneId, x300512_g_ScriptId)
                        UICommand_AddInt( sceneId, x300512_g_MissionId)
                        UICommand_AddInt( sceneId, NPCId)
                        DispatchUICommand( sceneId, selfId, 101)
                    EndUICommand( sceneId)

                    BeginQuestEvent( sceneId)
                        AddQuestText( sceneId, "#Y"..x300512_g_MissionName)
                        AddQuestText( sceneId, "\t你想上交哪匹马呢？" )
                    EndQuestEvent( sceneId)
                    DispatchQuestEventList( sceneId, selfId, NPCId)
                    return
                else
                    local id = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET5)
                    local count = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET6)
                    if count > x300512_g_FinishBound then
                        count = count - x300512_g_FinishBound
                    end
                    if GetItemCountInBag( sceneId, selfId, id) >= count then
                        BeginUICommand( sceneId)
                            UICommand_AddInt( sceneId, x300512_g_ScriptId)
                            UICommand_AddInt( sceneId, x300512_g_MissionId)
                            UICommand_AddInt( sceneId, NPCId)
                            UICommand_AddInt( sceneId, id)
                            DispatchUICommand( sceneId, selfId, 104)
                        EndUICommand( sceneId)

                        BeginQuestEvent( sceneId)
                        AddQuestText( sceneId, "#Y"..x300512_g_MissionName)
                            AddQuestText( sceneId, "\t您可以通过选择提交右侧框中的材料，来获得两倍经验和银子的奖励。\n\t如果你点击右侧框中的取消，或关闭右侧框体，你会获得普通的奖励。" )
                        EndQuestEvent( sceneId)
                        DispatchQuestEventList( sceneId, selfId, NPCId)
                    else
                        x300512_DispatchCompletedInfo( sceneId, selfId, NPCId) --完成任务显示
                    end
                end
            else
                x300512_DispatchContinueInfo( sceneId, selfId, NPCId)
            end
        else
            x300512_DispatchContinueInfo( sceneId, selfId, NPCId) --未完成任务显示
        end
	else -- 未接任务
        if GetGameOpenById( x300512_g_IsEnableId) <= 0 then
            return 0
        end

        -- 检查本日完成次数
        local highcircle = x300512_GetMD( sceneId, selfId, MD_GUOJIARENWU_HIGH)
        if x300512_GetMD( sceneId, selfId, MD_GUOJIARENWU_LASTDAY) == GetDayOfYear() then
            if highcircle >= x300512_g_HighBonusCircleCount then
                Msg2Player( sceneId, selfId, x300512_g_MissionCommentCountOver, 8, 2)
                Msg2Player( sceneId, selfId, x300512_g_MissionCommentCountOver, 8, 3)
                return
            end
        end
		x300512_DispatchMissionInfo( sceneId, selfId, NPCId)	--任务信息显示
	end
end

function x300512_ProcAcceptCheck( sceneId, selfId, NPCId)
end

-- 添加送信任务
function x300512_GetDeliverMissionImpl( sceneId, selfId, NPCId)
    -- 检查背包空间
    BeginAddItem( sceneId)
    local index = random( 1, getn( x300512_g_DeliverTable) )
    local item = x300512_g_DeliverTable[ index].missionItemId
    AddItem( sceneId, item, 1)
    local result = EndAddItem( sceneId, selfId)
    if result == 0 then
        Msg2Player( sceneId, selfId, x300512_g_strNotEnoughSpace, 8, 3)
        return result
    end

    -- 添加要送物品
    AddItemListToPlayer( sceneId, selfId)

    -- 添加任务
    result = AddQuest( sceneId, selfId, x300512_g_MissionId, x300512_g_ScriptId, 0, 0, 1, 1)
    if result == 0 then
        -- 删除任务物品
        DelItem( sceneId, selfId, item, 1)
        Msg2Player( sceneId, selfId, x300512_g_strMissionFull, 8, 3)
        return result
    end
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
    local tindex = random( 1, getn( x300512_g_DeliverTarget) )
    -- 保存任务类型
    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_MissionType, x300512_g_MT_Deliver)
    -- 保存目标NPC
    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET2, x300512_g_DeliverTarget[ tindex].targetId)
    -- 保存要送物品索引
    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET3, index)
    -- 保存收集物品ID
    local ritem = x300512_GetRandomItemID( GetLevel( sceneId, selfId) )
    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET5, ritem.id)
    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET6, ritem.count)

    BeginQuestEvent( sceneId)
        --任务继续信息
        AddQuestText( sceneId, "#Y"..x300512_g_MissionName)
        AddQuestText( sceneId, x300512_g_DeliverTable[ index].description)
        AddQuestText( sceneId, "#r" )
        AddQuestText( sceneId, "#Y任务目标:" )
        AddQuestText( sceneId, format( x300512_g_DeliverTarget[ tindex].description, 
                                       x300512_g_DeliverTable[ index].missionItemId, 
                                       x300512_g_DeliverTarget[ tindex].targetId, 
                                       ritem.count, ritem.id) )
        AddQuestText( sceneId, "#r #r#G小提示:#W\n如果你能按照要求上交一些#G生活技能的原材料#W或#G生活技能制造的部件#W，#G甘醇马奶酒#W等等，你会获得#G更多的奖励。#W" )
    EndQuestEvent()
    DispatchQuestEventList( sceneId, selfId, NPCId)
    return 1
end

-- 添加打怪任务
function x300512_GetKillMonsterMissionImpl( sceneId, selfId, NPCId)
    -- 添加任务
    local result = AddQuest( sceneId, selfId, x300512_g_MissionId, x300512_g_ScriptId, 1, 0, 1, 0)
    if result == 0 then
        Msg2Player( sceneId, selfId, x300512_g_strMissionFull, 8, 3)
        return result
    end

    -- 根据玩家等级在表里随机选一种怪
    local level = GetLevel( sceneId, selfId)
    local index = 1
    for i, item in x300512_g_KillMonsterLevel do
        if level >= item.minLevel and level <= item.maxLevel then
            index = item.mosterSet[ random( 1, getn( item.mosterSet) ) ]
            break
        end
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
    -- 保存任务类型
    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_MissionType, x300512_g_MT_KillMonster)
    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET2, index)
    -- 保存收集物品ID
    local ritem = x300512_GetRandomItemID( GetLevel( sceneId, selfId) )
    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET5, ritem.id)
    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET6, ritem.count)

    local count = x300512_g_KillMonsterTable[ index].count
    BeginQuestEvent( sceneId)
        --任务继续信息
        AddQuestText( sceneId, "#Y"..x300512_g_MissionName)
        AddQuestText( sceneId, x300512_g_KillMonsterTable[ index].description)
        AddQuestText( sceneId, "#r" )
        AddQuestText( sceneId, "#Y任务目标:" )
        AddQuestText( sceneId, format( x300512_g_KillMonsterTable[ index].target, 
                                       count, x300512_g_KillMonsterTable[ index].posId, 0, count, 
                                       ritem.count, ritem.id) )
        AddQuestText( sceneId, "#r #r#G小提示:#W\n如果你能按照要求上交一些#G生活技能的原材料#W或#G生活技能制造的部件#W，#G甘醇马奶酒#W等等，你会获得#G更多的奖励。#W" )
    EndQuestEvent()
    DispatchQuestEventList( sceneId, selfId, NPCId)
    return 1
end

-- 添加采集任务
function x300512_GetCollectMissionImpl( sceneId, selfId, NPCId)
    -- 添加任务
    local result = AddQuest( sceneId, selfId, x300512_g_MissionId, x300512_g_ScriptId, 0, 0, 1, 0)
    if result == 0 then
        Msg2Player( sceneId, selfId, x300512_g_strMissionFull, 8, 3)
        return result
    end

    -- 根据等级在表里随机选一个采集点
    local level = GetLevel( sceneId, selfId)
    local index = 1
    for i, item in x300512_g_CollectLevel do
        if level >= item.minLevel and level <= item.maxLevel then
            index = item.gpSet[ random( 1, getn( item.gpSet) ) ]
            break
        end
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
    -- 保存任务类型
    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_MissionType, x300512_g_MT_Collect)
    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET2, index)
    -- 保存收集物品ID
    local ritem = x300512_GetRandomItemID( GetLevel( sceneId, selfId) )
    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET5, ritem.id)
    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET6, ritem.count)

    local count = x300512_g_KillMonsterTable[ index].count
    local itemId = x300512_g_GrowPoint[ index].itemId
    BeginQuestEvent( sceneId)
        --任务继续信息
        AddQuestText( sceneId, "#Y"..x300512_g_MissionName)
        AddQuestText( sceneId, x300512_g_GrowPoint[ index].description)
        AddQuestText( sceneId, "#r" )
        AddQuestText( sceneId, "#Y任务目标:" )
        AddQuestText( sceneId, format( "采集@item_%d#W(%d/%d)或收集#G%d#W个@item_%d#W(2倍经验)", 
                                       itemId, GetItemCountInBag( sceneId, selfId, itemId), x300512_g_GrowPoint[ index].count, 
                                       ritem.count, ritem.id) )
        AddQuestText( sceneId, "#r #r#G小提示:#W\n如果你能按照要求上交一些#G生活技能的原材料#W或#G生活技能制造的部件#W，#G甘醇马奶酒#W等等，你会获得#G更多的奖励。#W" )
    EndQuestEvent()
    DispatchQuestEventList( sceneId, selfId, NPCId)
    return 1
end

-- 添加护送任务
function x300512_GetEscortMissionImpl( sceneId, selfId, NPCId)
    -- 添加任务
    local result = AddQuest( sceneId, selfId, x300512_g_MissionId, x300512_g_ScriptId, 0, 0, 1, 1)
    if result == 0 then
        Msg2Player( sceneId, selfId, x300512_g_strMissionFull, 8, 3)
        return result
    end

    local level = GetLevel( sceneId, selfId)
    local index = 1
    for i, item in x300512_g_EscortLevel do
         if level >= item.minLevel and level <= item.maxLevel then
            index = item.missions[ random( 1, getn( item.missions) ) ]
            break
        end
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
    -- 保存任务类型
    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_MissionType, x300512_g_MT_Escort)
    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET2, index)
    -- 保存收集物品ID
    local ritem = x300512_GetRandomItemID( GetLevel( sceneId, selfId) )
    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET5, ritem.id)
    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET6, ritem.count)

    BeginQuestEvent( sceneId)
        --任务继续信息
        AddQuestText( sceneId, "#Y"..x300512_g_MissionName)
        AddQuestText( sceneId, x300512_g_EscortTable[ index].intro..format( "或收集#G%d#W个@item_%d#W。", ritem.count, ritem.id) )
        AddQuestText( sceneId, "#r #r#G小提示:#W\n如果你能按照要求上交一些#G生活技能的原材料#W或#G生活技能制造的部件#W，#G甘醇马奶酒#W等等，你会获得#G更多的奖励。#W" )
    EndQuestEvent()
    DispatchQuestEventList( sceneId, selfId, NPCId)
    return 1
end

-- 添加挖掘任务
function x300512_GetDigMissionImpl( sceneId, selfId, NPCId)
    -- 添加任务
    local result = AddQuest( sceneId, selfId, x300512_g_MissionId, x300512_g_ScriptId, 0, 0, 1, 0)
    if result == 0 then
        Msg2Player( sceneId, selfId, x300512_g_strMissionFull, 8, 3)
        return result
    end

    local level = GetLevel( sceneId, selfId)
    local index = 1
    for i, item in x300512_g_DigLevel do
         if level >= item.minLevel and level <= item.maxLevel then
            index = item.missions[ random( 1, getn( item.missions) ) ]
            break
        end
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
    local coord = random( 1, getn( x300512_g_CoordinateLib) )
    local posX, posZ
    posX = x300512_g_CoordinateLib[ coord].posX
    posZ = x300512_g_CoordinateLib[ coord].posZ
    -- 保存任务类型
    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_MissionType, x300512_g_MT_Dig)
    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET2, index)
    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET3, coord)
    -- 保存收集物品ID
    local ritem = x300512_GetRandomItemID( GetLevel( sceneId, selfId) )
    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET5, ritem.id)
    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET6, ritem.count)

    local destSceneId = x300512_CountrySceneList[ GetCurCountry( sceneId, selfId) + 1]
    BeginQuestEvent( sceneId)
        --任务继续信息
        AddQuestText( sceneId, "#Y"..x300512_g_MissionName)
        AddQuestText( sceneId, "#Y任务目标:" )
        AddQuestText( sceneId, format( x300512_g_DigTarget[ index].target, 
                                       destSceneId, posX, posZ, posX, posZ, x300512_g_DigTarget[ index].name, 
                                       ritem.count, ritem.id) )
        AddQuestText( sceneId, "#r #r#G小提示:#W\n如果你能按照要求上交一些#G生活技能的原材料#W或#G生活技能制造的部件#W，#G甘醇马奶酒#W等等，你会获得#G更多的奖励。#W" )
    EndQuestEvent()
    DispatchQuestEventList( sceneId, selfId, NPCId)
    return 1
end

-- 添加收马任务
function x300512_GetObtainHorseMissionImpl( sceneId, selfId, NPCId)
    -- 添加任务
    local result = AddQuest( sceneId, selfId, x300512_g_MissionId, x300512_g_ScriptId, 0, 0, 0, 0)
    if result == 0 then
        Msg2Player( sceneId, selfId, x300512_g_strMissionFull, 8, 3)
        return result
    end

    local level = GetLevel( sceneId, selfId)
    local index = 1
    for i, item in x300512_g_GetHorseLevel do
        if level >= item.minLevel and level <= item.maxLevel then
            index = item.missions[ random( 1, getn( item.missions) ) ]
            break
        end
    end

    -- 保存任务类型
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_MissionType, x300512_g_MT_Horse)
    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET2, index)
    -- 骑乘变化调用ProcQuestHorseChanged函数
    SetQuestEvent( sceneId, selfId, x300512_g_MissionId, 3)

    BeginQuestEvent( sceneId)
        --任务继续信息
        AddQuestText( sceneId, "#Y"..x300512_g_MissionName)
        AddQuestText( sceneId, format( x300512_g_GetHorse[ index].info, x300512_g_GetHorse[ index].name, x300512_g_GetHorse[ index].name) )
        AddQuestText( sceneId, "#Y任务目标:" )
        AddQuestText( sceneId, format( x300512_g_GetHorse[ index].description, x300512_g_GetHorse[ index].name) )
    EndQuestEvent()
    DispatchQuestEventList( sceneId, selfId, NPCId)
    return 1
end

-- 添加收集材料任务
function x300512_GetObtainMaterialMissionImpl( sceneId, selfId, NPCId)
    -- 添加任务
    local result = AddQuest( sceneId, selfId, x300512_g_MissionId, x300512_g_ScriptId, 0, 0, 1, 0)
    if result == 0 then
        Msg2Player( sceneId, selfId, x300512_g_strMissionFull, 8, 3)
        return result
    end

    local level = GetLevel( sceneId, selfId)
    local index = 1
    local choose = 1
    for i, item in x300512_g_MaterialLevel do
        if level >= item.minLevel and level <= item.maxLevel then
            index = item.missions[ random( 1, getn( item.missions) ) ]
            choose = random( 1, item.choose)
            break
        end
    end

    -- 保存任务类型
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_MissionType, x300512_g_MT_Material)
    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET2, index)
    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET3, choose)

	local highcircle = x300512_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH)
    BeginQuestEvent( sceneId)
        --任务继续信息
        AddQuestText( sceneId, "#Y"..x300512_g_MissionName)
        AddQuestText( sceneId, x300512_g_MaterialTable[ index].description)
        AddQuestText( sceneId, "#Y任务目标:" )
        AddQuestText( sceneId, format( x300512_g_MaterialTable[ index].target, x300512_g_MaterialTable[ index].base, x300512_g_MaterialTable[ index].advanced[ choose], x300512_g_MaterialTable[ index].xpCoff[ choose] ) )
        AddQuestText( sceneId, "#r #r#G小提示:#W\n如果你能按照要求上交一些#G生活技能的原材料#W或#G生活技能制造的部件#W，#G甘醇马奶酒#W等等，你会获得#G更多的奖励。#W" )
    EndQuestEvent()
    DispatchQuestEventList( sceneId, selfId, NPCId)
    return 1
end

-- 根据等级和选取比例获得添加任务索引
function x300512_GetFuncIndex( sceneId, selfId, misType)
    local level = GetLevel( sceneId, selfId)
    local tbl = x300512_g_HeadMissionTable

    if misType == 1 then
        tbl = x300512_g_EndMissionTable
    end

    -- 随机取值最大值
    local amount = 0
    for i, item in tbl do
        if level >= item.low and level <= item.high then
            for j, iter in item.config do
                amount = amount + iter
            end
            break
        end
    end

    -- 获取随机值
    local rate = 1
    if amount >= 1 then
        rate = random( 1, amount)
    end
    local up = 1
    local down = 1
    local result = 1
    for i, item in tbl do
        if level >= item.low and level <= item.high then
            for j, iter in item.config do
                -- 设置上区间
                up = down + iter
                if rate >= down and rate < up then
                    result = j
                    break
                end
                -- 设置下区间
                down = down + iter
            end
            break
        end
    end

    return result
end

function x300512_DeliverMission( sceneId, selfId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
    local finish   = GetQuestParam( sceneId, selfId, misIndex, 0)
    local complete = GetQuestParam( sceneId, selfId, misIndex, 7)
    local level = GetLevel( sceneId, selfId)
    local misType = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_MissionType)
    local index = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET2)
    local mp3 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET3)
    local mp4 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET4)
    local times = 1
    local xp = x300512_GetExpAward( sceneId, selfId, level) * times
    local money, shengw = x300512_GetMoneyAward( sceneId, selfId, level)
    -- 前5环扣除物品标记
    local bItem = 0
	local advMaterial = 0
	
	if GetGameOpenById( x300512_g_IsEnableId) <= 0 then
		return 0
	end

	-- 检查本日完成次数
	local highcircle = x300512_GetMD( sceneId, selfId, MD_GUOJIARENWU_HIGH)
	if x300512_GetMD( sceneId, selfId, MD_GUOJIARENWU_LASTDAY) == GetDayOfYear() then
		if highcircle >= x300512_g_HighBonusCircleCount then
			Msg2Player( sceneId, selfId, x300512_g_MissionCommentCountOver, 8, 2)
			Msg2Player( sceneId, selfId, x300512_g_MissionCommentCountOver, 8, 3)
			return
		end
	end	

    if misType ~= x300512_g_MT_Material and misType ~= x300512_g_MT_Horse then
        if GetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID) == 1 then
            local cnt = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET6)
            if cnt > x300512_g_FinishBound then
                cnt = cnt - x300512_g_FinishBound
            end
            if DelItem( sceneId, selfId, GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET5), cnt) == 0 then
                Msg2Player( sceneId, selfId, "提交物品失败，无法交任务", 8, 3)
                return
            end
            SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, 0)
            money = money * 4
            xp = xp * 2
            bItem = 1
        end
    end

    if misType == x300512_g_MT_Dig and GetItemCountInBag( sceneId, selfId, x300512_g_DigTarget[ index].id) > 0 then
        -- 删除挖到的物品
        if DelItem( sceneId, selfId, x300512_g_DigTarget[ index].id, 1) == 0 then
            return
        end
    elseif misType == x300512_g_MT_Horse then
        local horseGUID_high = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET4)
        local horseGUID_low = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET5)
        local isGood = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET6)
        local result = FreeHorse( sceneId, selfId, horseGUID_high, horseGUID_low)
        if result <= 0 then
            return
        end
        if isGood == 1 then
            times = 2
        end
    elseif misType == x300512_g_MT_Collect then
        local count = GetItemCountInBag( sceneId, selfId, x300512_g_GrowPoint[ index].itemId)
        if count > 0 then
            if DelItem( sceneId, selfId, x300512_g_GrowPoint[ index].itemId, count) == 0 then
                Msg2Player( sceneId, selfId, "提交物品失败，无法交任务", 8, 3)
                return 0
            end
        end
    elseif misType == x300512_g_MT_Material then
        if GetItemCountInBag( sceneId, selfId, mp4) == 0 then
            Msg2Player( sceneId, selfId, "你没有这个物品或该物品处于锁定状态", 8, 3)
            return
        else
            if DelItem( sceneId, selfId, mp4, 1) == 0 then
                Msg2Player( sceneId, selfId, "提交物品失败，可能是该物品处于锁定状态或已丢失", 8, 3)
                return
            end
        end
        if mp4 ~= x300512_g_MaterialTable[ index].base then
            -- 高倍经验
            for i, item in x300512_g_MaterialTable[ index].advanced do
                if item == mp4 then
                    money = x300512_g_MaterialTable[ index].money[ i]
                    xp = xp * x300512_g_MaterialTable[ index].xpCoff[ i]
					advMaterial = 1
                    break
                end
            end
        end
    elseif misType == x300512_g_MT_Deliver and bItem == 1 then
        -- 如果交物品，尝试删除信件(如果有的话)
        if GetItemCountInBag( sceneId, selfId, x300512_g_DeliverTable[ mp3].missionItemId) > 0 then
            if DelItem( sceneId, selfId, x300512_g_DeliverTable[ mp3].missionItemId, 1) == 0 then
                return
            end
        end
    end
    
	x300512_DeleteMissionBus(sceneId,selfId)
    DelQuest( sceneId, selfId, x300512_g_MissionId)
    if misType ~= x300512_g_MT_Material then
        money = money * times
        shengw = shengw * times
    end
    xp = xp * times
    if( xp > 0) then
        AddExp( sceneId, selfId, xp)
    end
    
    local moneyType = 0
    if money > 0 then
		if IsHaveSpecificImpact( sceneId, selfId, 9011) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9012) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9013) == 1 then
			AddMoney( sceneId, selfId, 0, money)
		else
			if misType == x300512_g_MT_Material then
				if advMaterial == 0 then
					AddMoney( sceneId, selfId, 1, money)
				else
					AddMoney( sceneId, selfId, 0, money)
				end
			else
				AddMoney( sceneId, selfId, 1, money)
			end
		end
    end
    if( shengw > 0) then
        SetShengWang(sceneId, selfId, GetShengWang( sceneId, selfId) + shengw)
    end
    x300512_DisplayAwardInfo( sceneId, selfId, moneyType, money, xp, 0, shengw)
    local strText = format( x300512_g_strFinishMission, x300512_GetMD( sceneId, selfId, MD_GUOJIARENWU_CIRCLE) + 1)
    local highcircle = x300512_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH)
    if level >= 80 then
        local tf = ( highcircle + 1) * 25
        local refixtf = AddInherenceExp( sceneId, selfId, tf)
        Msg2Player( sceneId, selfId, format( "获得#R%s#cffcc00点天赋奖励。", refixtf), 8, 2)
    end
    --if highcircle < x300512_g_HighBonusCircleCount then
      --  strText = strText..format("  本日高奖环数：%d/%d", highcircle + 1, x300512_g_HighBonusCircleCount)
   -- end
    Msg2Player( sceneId, selfId, strText, 8, 3)
    Msg2Player( sceneId, selfId, format( x300512_g_strFinishMission, x300512_GetMD( sceneId, selfId, MD_GUOJIARENWU_CIRCLE) + 1).."。", 8, 2)
    local curCircle = x300512_GetMD( sceneId, selfId, MD_GUOJIARENWU_CIRCLE) + 1
    if curCircle >= 10 then
        curCircle = 0
    end
    x300512_SetMD( sceneId, selfId, MD_GUOJIARENWU_CIRCLE, curCircle)
    x300512_SetMD( sceneId, selfId, MD_GUOJIARENWU_HIGH, highcircle + 1)
    x300512_SetMD( sceneId, selfId, MD_GUOJIARENWU_LASTDAY, GetDayOfYear() )
    if highcircle + 1 == x300512_g_HighBonusCircleCount then
        CallScriptFunction( 203788, "FinishNeizheng", sceneId, selfId)
        local week = x300512_GetCurrentWeek()
        if x300512_GetMD( sceneId, selfId, MD_NEIZHENG_WEEK) ~= week then
            x300512_SetMD( sceneId, selfId, MD_NEIZHENG_WEEK, week)
            x300512_SetMD( sceneId, selfId, MD_NEIZHENG_WEEKCOUNT, 1)
        else
            x300512_SetMD( sceneId, selfId, MD_NEIZHENG_WEEKCOUNT, x300512_GetMD( sceneId, selfId, MD_NEIZHENG_WEEKCOUNT) + 1)
        end
        -- 增加2两国家金钱
        AddCountryResourceEx( sceneId, GetCurCountry( sceneId, selfId), 2, 2000)
        Msg2Player( sceneId, selfId, "完成今天全部内政任务，增加#R2#cffcc00两国家金钱。", 8, 2)
        -- 添加一个绑定的“回魂丹”
        BeginAddItem( sceneId)
        AddBindItem( sceneId, 11990050, 1)
        if EndAddItem( sceneId, selfId) > 0 then
            AddItemListToPlayer( sceneId, selfId)
        else
            Msg2Player( sceneId, selfId, "无法额外奖励物品，请整理道具栏", 8, 3)
        end
        GamePlayScriptLog( sceneId, selfId, 462)
    else
        GamePlayScriptLog( sceneId, selfId, 452)
    end
end

function x300512_GetCurrentWeek()
	--取得今天的日期
	local nCurrentTime = ( GetCurrentTime() + 8 * 3600) / 86400 - 4  --换算成天
	local nWeek = floor( nCurrentTime / 7)		 --换算成周,并取整

	return nWeek
end

function x300512_ProcQuestAccept( sceneId, selfId, NPCId, missionId)
	if IsHaveQuestNM( sceneId, selfId, x300512_g_MissionId) > 0 then
        local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
        local finish   = GetQuestParam( sceneId, selfId, misIndex, 0)
        local complete = GetQuestParam( sceneId, selfId, misIndex, 7)
        local level = GetLevel( sceneId, selfId)
        local misType = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_MissionType)
        local index = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET2)
        if finish == 1 and complete == 1 and misType ~= x300512_g_MT_Escort then
            x300512_DeliverMission( sceneId, selfId)
        else
            if ( finish == 1 and complete == 1 and GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET6) < x300512_g_FinishBound) or 
               ( finish == 0 and complete == 0) then
                local PosX,PosZ = GetWorldPos( sceneId, selfId)
                local mp4 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET4)
                if misType == x300512_g_MT_Escort then
                    if mp4 == 0 then
                        if GetBusId( sceneId, selfId) == -1 then
                            -- 创建要护送的Bus
                            local ObjID = CreateBus( sceneId, x300512_g_EscortTable[ index].escortType, PosX, PosZ, 3, 3, 300512, selfId, 1210,x300512_g_MissionId,NPCId)
                        else
                            Msg2Player( sceneId, selfId, "你现在的状态不能进行护送", 8, 3)                        
                        end
                        return
                    elseif mp4 == 1 then
                        -- 删除Bus
                        local busGuid = GetBusId( sceneId, selfId)
                        if busGuid < 0 or IsObjValid( sceneId, busGuid) ~= 1 then						--玩家没有bus
                            return	0			
                        end
                        DeleteBus( sceneId, busGuid, 1)
                        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
                        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
                        SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET6, x300512_g_FinishBound + GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET6) )
                        Msg2Player( sceneId, selfId, x300512_g_strMissionFinishTip, 8, 3)
                    end
                end
                x300512_ProcQuestLogRefresh( sceneId, selfId, x300512_g_MissionId)
            else
                x300512_DeliverMission( sceneId, selfId)
            end
        end
    else
        if GetGameOpenById( x300512_g_IsEnableId) <= 0 then
            return 0
        end

        -- 检查本日完成次数
        local highcircle = x300512_GetMD( sceneId, selfId, MD_GUOJIARENWU_HIGH)
        if x300512_GetMD( sceneId, selfId, MD_GUOJIARENWU_LASTDAY) == GetDayOfYear() then
            if highcircle >= x300512_g_HighBonusCircleCount then
                Msg2Player( sceneId, selfId, x300512_g_MissionCommentCountOver, 8, 2)
                Msg2Player( sceneId, selfId, x300512_g_MissionCommentCountOver, 8, 3)
                return
            end
        end

        local result = 0
        if x300512_g_MissionType > 0 then
            -- 添加GM指令选择的子任务
            if x300512_g_MissionType > 5 and x300512_g_MissionType < 8 then
                result = x300512_g_GetMissionEnd[ x300512_g_MissionType - 5]( sceneId, selfId, NPCId)
            elseif x300512_g_MissionType >= 1 and x300512_g_MissionType <= 5 then
                result = x300512_g_GetMissionHead[ x300512_g_MissionType]( sceneId, selfId, NPCId)
            end
        else
            local curCircle = x300512_GetMD( sceneId, selfId, MD_GUOJIARENWU_CIRCLE)
            if curCircle < 5 then
                result = x300512_g_GetMissionHead[ x300512_GetFuncIndex( sceneId, selfId, 0) ]( sceneId, selfId, NPCId)
                --x300512_ChooseRandomItem( sceneId, selfId)
            else
                result = x300512_g_GetMissionEnd[ x300512_GetFuncIndex( sceneId, selfId, 1) ]( sceneId, selfId, NPCId)
            end
        end

        -- 调试用
        -- result = x300512_g_GetMissionHead[ 3]( sceneId, selfId, NPCId)
        -- result = x300512_g_GetMissionEnd[ 2]( sceneId, selfId, NPCId)

        if result == 0 then
            return
        end

        local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
        local id = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET5)
        local count = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET6)
        local misType = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_MissionType)
        if misType ~= x300512_g_MT_Horse and misType ~= x300512_g_MT_Material then
            if GetItemCountInBag( sceneId, selfId, id) >= count then
                SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
                SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
                Msg2Player( sceneId, selfId, x300512_g_strMissionFinishTip, 8, 3)
            end
        end
        -- SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
        -- SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)

        Msg2Player( sceneId, selfId, format( x300512_g_strAcceptMission, x300512_GetMD( sceneId, selfId, MD_GUOJIARENWU_CIRCLE) + 1), 8, 3)
        Msg2Player( sceneId, selfId, format( x300512_g_strAcceptMission, x300512_GetMD( sceneId, selfId, MD_GUOJIARENWU_CIRCLE) + 1).."。", 8, 2)

        -- 更新任务跟踪
        x300512_ProcQuestLogRefresh( sceneId, selfId, x300512_g_MissionId)

        -- 写日志
        GamePlayScriptLog( sceneId, selfId, 451)
	end
end

--创建busd成功处理
function x300512_OnCreateBusOK(sceneId, selfId, busId,targetId,MissionId)	

	local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
	local camp = GetCurCamp( sceneId, selfId)
	SetBusCurCamp( sceneId, busId, camp)
	SetBusTimerTick( sceneId , busId, 1000)
	SetBusWaitTime( sceneId , busId, 300)
	SetBusQuestID( sceneId, busId, x300512_g_MissionId)
	SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET4, 1)
	x300512_ProcQuestLogRefresh( sceneId, selfId, x300512_g_MissionId)
end

function x300512_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID)
    if x300512_GetMD( sceneId, selfId, MD_GUOJIARENWU_RANDMISSIONID) > 0 then
        return CallScriptFunction( 300501, "OnOpenItemBox", sceneId, selfId, targetId, gpType, needItemID)
    end

    if IsHaveQuest( sceneId, selfId, x300512_g_MissionId) == 0 then
        Msg2Player( sceneId, selfId, "你没有接受【个人】国家内政，不能采集", 8, 3)
        return 1
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
    local misType = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_MissionType)
    local index = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET2)
    if misType == x300512_g_MT_Collect then
        if x300512_g_GrowPoint[ index].itemId ~= needItemID then
            Msg2Player( sceneId, selfId, "这不是你要采集的物品", 8, 3)
            return 1
        end
        if GetItemCountInBag( sceneId, selfId, needItemID) >= x300512_g_GrowPoint[ index].count then
            Msg2Player( sceneId, selfId, "你已完成任务，不能继续采集", 8, 3)
            return 1
        end
    else
        return 1
    end

    return 0
end

--回收
function x300512_OnRecycle( sceneId, selfId, targetId, gpType, needItemID)
    if x300512_GetMD( sceneId, selfId, MD_GUOJIARENWU_RANDMISSIONID) > 0 then
        return CallScriptFunction( 300501, "OnRecycle", sceneId, selfId, targetId, gpType, needItemID)
    end

    if IsHaveQuest( sceneId, selfId, x300512_g_MissionId) == 0 then
        return 0
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
    local misType = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_MissionType)
    local mp2 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET2)
    local mp3 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET3)
    local mp4 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET4)
    if misType == x300512_g_MT_Collect then
        BeginAddItem( sceneId)
        AddItem( sceneId, needItemID, 1)
        if EndAddItem( sceneId, selfId) > 0 then
            AddItemListToPlayer( sceneId, selfId)
            local count = GetItemCountInBag( sceneId, selfId, needItemID)
            if count >= x300512_g_GrowPoint[ mp2].count then
                x300512_ProcQuestLogRefresh( sceneId, selfId, x300512_g_MissionId)
            else
                SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET4, count)
                Msg2Player( sceneId, selfId, format( "你获得了@item_%d#cffcf00(%d/%d)", needItemID, count, x300512_g_GrowPoint[ mp2].count), 8, 3)
            end
            return 1
        else
            Msg2Player( sceneId, selfId, "无法得到采集物品，请整理道具栏", 8, 3)
        end
    end

    return 0
end

--放弃任务
function x300512_ProcQuestAbandon( sceneId, selfId, MissionId)
	local bHaveMission	= IsHaveQuestNM( sceneId, selfId, x300512_g_MissionId)
	if bHaveMission > 0 then
		local misIndex = GetQuestIndexByID(sceneId, selfId, x300512_g_MissionId)
        local misType = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_MissionType)
        local m2 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET2)
        local m3 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET3)
        local m4 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET4)

        if misType == x300512_g_MT_Deliver then    -- 送信任务
            local count = GetItemCount( sceneId, selfId, x300512_g_DeliverTable[ m3].missionItemId)
            if count > 0 then
                -- 删除任务物品
                if DelItem( sceneId, selfId, x300512_g_DeliverTable[ m3].missionItemId, count) == 0 then
                    Msg2Player( sceneId, selfId, "删除信件失败，不能放弃任务", 8, 3)
                    return
                end
            end
        elseif misType == x300512_g_MT_Escort then
            if m4 == 1 then
                -- 删除Bus
                local busGuid = GetBusId( sceneId, selfId)
                if busGuid >= 0 and IsObjValid( sceneId, busGuid) == 1 then						--玩家没有bus
                    DeleteBus( sceneId, busGuid, 1)
                end
            end
        elseif misType == x300512_g_MT_Dig then
            -- 删除挖到的物品
            if GetItemCountInBag( sceneId, selfId, x300512_g_DigTarget[ m2].id) > 0 then
                if DelItem( sceneId, selfId, x300512_g_DigTarget[ m2].id, 1) == 0 then
                    Msg2Player( sceneId, selfId, "删除挖掘到的物品失败，不能放弃任务", 8, 3)
                    return
                end
            end
        elseif misType == x300512_g_MT_Collect then
            local count = GetItemCountInBag( sceneId, selfId, x300512_g_GrowPoint[ m2].itemId)
            if count > 0 then
                if DelItem( sceneId, selfId, x300512_g_GrowPoint[ m2].itemId, count) == 0 then
                    Msg2Player( sceneId, selfId, "删除采集到的物品失败，不能放弃任务", 8, 3)
                    return
                end
            end
        end
		DelQuest( sceneId, selfId, x300512_g_MissionId)

        BeginQuestEvent( sceneId)
        AddQuestText( sceneId, format( x300512_g_strAbandonMission, x300512_GetMD( sceneId, selfId, MD_GUOJIARENWU_CIRCLE) + 1) )
        EndQuestEvent( sceneId)
        DispatchQuestTips( sceneId, selfId)
        Msg2Player( sceneId, selfId, format( x300512_g_strAbandonMission, x300512_GetMD( sceneId, selfId, MD_GUOJIARENWU_CIRCLE) + 1), 8, 2)

        -- 更新放弃任务时间
        x300512_SetMD( sceneId, selfId, MD_GUOJIARENWU_ABANDON, GetMinOfDay() )
        x300512_SetMD( sceneId, selfId, MD_GUOJIARENWU_LASTDAY, GetDayOfYear() )
        x300512_SetTimes( sceneId, selfId, x300512_GetTimes( sceneId, selfId) + 1)
        x300512_SetMD( sceneId, selfId, MD_GUOJIARENWU_HIGH, x300512_g_HighBonusCircleCount)
	end
end

--检查任务是否可提交
function x300512_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId, selfId, x300512_g_MissionId)
	return GetQuestParam(sceneId, selfId, misIndex, x300512_MP_ISCOMPLETE)
end

function x300512_DisplayAwardInfo( sceneId, selfId, moneyType, money, expAward, honorType, honor) --提示玩家金钱经验声望的奖励信息
	local strInfo;

	if expAward > 0 then
		strInfo = format("#Y获得#R经验%d#Y的奖励。", expAward);
		Msg2Player(sceneId, selfId, strInfo, 8, 2)
	end

	if honor > 0 then
		if honorType == 0 then --声望
			strInfo = format("#Y获得#R声望%d#Y的奖励。", honor);
		elseif honorType == 1 then	--声望
			strInfo = format("#Y获得#R声望%d#Y的奖励。", honor);
		elseif honorType == 2 then --PK
			strInfo = format("#Y获得#RPK值%d#Y的奖励。", honor);
		elseif honorType == 3 then --荣誉
			strInfo = format("#Y获得#R荣誉%d#Y的奖励。", honor);
		elseif honorType == 4 then -- 帮贡
			strInfo = format("#Y获得#R帮贡%d#Y的奖励。", honor);
		elseif honorType == 5 then -- 文采
			strInfo = format("#Y获得#R文采%d#Y的奖励。", honor);
		end

		Msg2Player(sceneId, selfId, strInfo, 8, 2)
	end
end

--获得奖励
function x300512_GetBonus( sceneId, selfId,NPCId, SelectId )
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)

	--奖励金钱1
	if x300512_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x300512_g_BonusMoney1 )
	    Msg2Player(sceneId,selfId,format("获得#R银卡#{_MONEY%d}#W的奖励。", x300512_g_BonusMoney1),4,2)
	end

	--奖励金钱2
	if x300512_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x300512_g_BonusMoney2 )
	    Msg2Player(sceneId,selfId,format("获得银币#{_MONEY%d}的奖励。", x300512_g_BonusMoney2),4,2)
	end

	--奖励金钱1
	if x300512_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x300512_g_BonusMoney3 )
	    Msg2Player(sceneId,selfId,format("获得金卡#{_MONEY%d}的奖励。", x300512_g_BonusMoney3),4,2)
	end

	--江湖声望
	if x300512_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
		nRongYu = nRongYu + x300512_g_BonusMoney4
		SetRongYu( sceneId, selfId, nRongYu )
		Msg2Player(sceneId,selfId,format("获得江湖声望%d的奖励。", x300512_g_BonusMoney4),4,2)
	end

	--朝廷声望
	if x300512_g_BonusMoney5 > 0 then
		local nShengWang = GetShengWang( sceneId, selfId )
		nShengWang = nShengWang + x300512_g_BonusMoney5
		SetShengWang( sceneId, selfId, nShengWang )
		Msg2Player(sceneId,selfId,format("获得朝廷声望%d的奖励。", x300512_g_BonusMoney5),4,2)
	end

	--朝廷声望
	if x300512_g_BonusMoney6 > 0 then
		AddHonor(sceneId,selfId,x300512_g_BonusMoney6)
		Msg2Player(sceneId,selfId,format("获得荣誉值%d的奖励。", x300512_g_BonusMoney6),4,2)
	end

 	--奖励固定物品
		for i, item in x300512_g_BonusItem do
 		BeginAddItem(sceneId)
		AddItem( sceneId, item.item, item.n )
		local result = EndAddItem(sceneId,selfId)
		if result > 0 then
			AddItemListToPlayer(sceneId,selfId)
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"物品栏已满，无法得到任务物品！")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end
    end

	--奖励可选物品
	for i, item in x300512_g_BonusChoiceItem do
	    if item.item == SelectId then
	        BeginAddItem(sceneId)
			AddItem( sceneId, item.item, item.n )
			local result = EndAddItem(sceneId,selfId)
			if result > 0 then
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

function x300512_DeleteMissionBus(sceneId,selfId)
	
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
    local misType = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_MissionType)
    if misType == x300512_g_MT_Escort then
        local mp4 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET4)
        if mp4 == 1 then
            local busGuid = GetBusId( sceneId, selfId)
            if busGuid >= 0 and IsObjValid( sceneId, busGuid) == 1 then
                DeleteBus( sceneId, busGuid, 1)
            end
        end
    end
   
end

--提交任务，不管任务是否完成或是任务，显示任务继续信息或是任务完成信息
function x300512_ProcQuestSubmit( sceneId, selfId, NPCId, RadioId, MissionId)
    
    x300512_DeliverMission( sceneId, selfId)
end

--检查玩家包裹已满
function x300512_CheckPlayerBagFull( sceneId ,selfId)
	local result = 1

	local j = 0

	local bAdd = 0 --是否已经在固定物品奖励添加检测中已经检查出包裹已满

	--普通的奖励检查
	BeginAddItem(sceneId)
	for j, item in x300512_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
    end

    --奖励可选物品
	for j, item in x300512_g_BonusChoiceItem do
		AddItem( sceneId, item.item, item.n )
    end
		
	local result = EndAddItem(sceneId,selfId)
	if(result > 0) then
		result = 1;
	else
		result = 0;
	end

	return result
end

--向客户端发送任务信息
function x300512_DispatchMissionInfo( sceneId, selfId, NPCId)
	local highcircle = x300512_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH)

	BeginQuestEvent( sceneId)
		--任务信息
		AddQuestText( sceneId, "#Y"..x300512_g_MissionName)
		AddQuestText( sceneId, x300512_g_MissionDescription)
		AddQuestText( sceneId, " " )

		--任务奖励信息
        local level = GetLevel( sceneId, selfId)
        local xp = x300512_GetExpAward( sceneId, selfId, level)
        local money, shengw = x300512_GetMoneyAward( sceneId, selfId, level)
        if( xp > 0) then
            AddQuestExpBonus( sceneId, xp)
        end
        if( money > 0) then
            -- 如果有江湖请柬的Buff才显示现银奖励
            if IsHaveSpecificImpact( sceneId, selfId, 9011) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9012) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9013) == 1 then
                AddQuestMoneyBonus2( sceneId, money)
            else
                AddQuestMoneyBonus1( sceneId, money)
            end
        end
        if( shengw > 0) then
            AddQuestMoneyBonus5( sceneId, shengw)
        end
        if level >= 80 then
            AddQuestGeniusBonus( sceneId, RefixInherenceExp( sceneId, selfId, ( highcircle + 1) * 25) )
        end
		--小提示
        AddQuestText( sceneId, "#c00FF00小提示:" )
        AddQuestText( sceneId, "#c00FF00如果想要了解本任务的细节，请点击国家内政说明按钮。" )
	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, NPCId, x300512_g_ScriptId, x300512_g_MissionId)
end

-- 金钱和声望奖励
function x300512_GetMoneyAward( sceneId, selfId, startlevel)
	x300512_CheckDayChanged( sceneId, selfId)
	local circle = x300512_GetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE)
	local highcircle = x300512_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH)

	circle = circle + 1	
	if circle > x300512_OneRoundCount then
		circle = 1
	end	

	highcircle = highcircle + 1	

	local BonusMoney = startlevel	
	local shengw = 5
	if highcircle <= x300512_g_HighBonusCircleCount then
		BonusMoney = BonusMoney * 5
		shengw = 25
	end	
	return BonusMoney,shengw;	
end

--检查日期有没有变化，并重置高奖次数，并保存新的日期
function x300512_CheckDayChanged( sceneId, selfId)
	local lastDay = x300512_GetMD(sceneId, selfId, MD_GUOJIARENWU_LASTDAY)
	local today = GetDayOfYear()
	if lastDay ~= today then	--日期变化
		x300512_SetMD(sceneId, selfId, MD_GUOJIARENWU_LASTDAY, today)
		x300512_SetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH, 0)
        x300512_SetMD( sceneId, selfId, MD_GUOJIARENWU_CIRCLE, 0)
	end
end

-- 经验奖励
function x300512_GetExpAward( sceneId, selfId, startlevel)
	x300512_CheckDayChanged( sceneId, selfId)
	local circle = x300512_GetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE)
	local highcircle = x300512_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH)

	circle = circle + 1
	if circle > x300512_OneRoundCount then
		circle = 1
	end

	highcircle = highcircle + 1

	local exp_rate
	if GetLevel( sceneId, selfId) >= 60 then
		exp_rate = 3650
	else
		exp_rate = 3650
	end

	local BonusExp = startlevel * exp_rate * ( circle * 2 - 1) / 200
	if highcircle <= x300512_g_HighBonusCircleCount then
		BonusExp = BonusExp * 5
	end
    -- 环数减半，所以经验翻倍
    BonusExp = BonusExp * 2
	return BonusExp
end

--向客户端发送任务未完成
function x300512_DispatchContinueInfo( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
    local misType = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_MissionType)
    local mp2 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET2)
    local mp3 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET3)
    local mp4 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET4)
    local strInfo = ""
    local level = GetLevel( sceneId, selfId)

    if misType == x300512_g_MT_Deliver then    -- 送信任务
        if GetMonsterGUID( sceneId, NPCId) == mp2 then
            -- 删除信件
            if DelItem( sceneId, selfId, x300512_g_DeliverTable[ mp3].missionItemId, 1) == 0 then
                return
            end
            strInfo = x300512_g_DeliverTable[ mp3].talking
            SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
            SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
            SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET6, GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET6) + x300512_g_FinishBound)  -- 标记送信完成，如果不交物品用它来判断可否交任务
            x300512_ProcQuestLogRefresh( sceneId, selfId, x300512_g_MissionId)

            Msg2Player( sceneId, selfId, x300512_g_strMissionFinishTip, 8, 3)
        else
            strInfo = format( x300512_g_strDeliverContinue, x300512_g_DeliverTable[ mp3].missionItemId, mp2)
        end

        BeginQuestEvent( sceneId)
            --任务继续信息
            AddQuestText( sceneId, "#Y"..x300512_g_MissionName)
            AddQuestText( sceneId, strInfo)
            AddQuestText( sceneId, "#r #r#G小提示:#W\n如果你能按照要求上交一些#G生活技能的原材料#W或#G生活技能制造的部件#W，#G甘醇马奶酒#W等等，你会获得#G更多的奖励。#W" )
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, NPCId)
    elseif misType == x300512_g_MT_Escort then  -- 护送任务
        BeginQuestEvent( sceneId)
            --任务完成信息
            AddQuestText( sceneId, "#Y"..x300512_g_MissionName)
            if mp4 == 0 and GetMonsterGUID( sceneId, NPCId) == x300512_g_EscortTable[ mp2].npcGuid then
                AddQuestText( sceneId, x300512_g_EscortTable[ mp2].getmiss)
            elseif mp4 == 1 and GetMonsterGUID( sceneId, NPCId) == x300512_g_EscortTable[ mp2].targetGuid then
                local x, z = GetWorldPos( sceneId, selfId)
                local busGuid = GetBusId( sceneId, selfId)
                if busGuid < 0 then
                    return
                end
                local bx, bz = GetWorldPos( sceneId, busGuid)
                if abs( x - bx) > x300512_g_EscortMaxDistance or abs( z - bz) > x300512_g_EscortMaxDistance then
                    Msg2Player( sceneId, selfId, "护送目标离你太远，无法完成任务", 8, 3)
                    return
                end
                AddQuestText( sceneId, x300512_g_EscortTable[ mp2].finish)
            else
                AddQuestText( sceneId, x300512_g_strEscortContinue)
                AddQuestText( sceneId, "#r #r#G小提示:#W\n如果你能按照要求上交一些#G生活技能的原材料#W或#G生活技能制造的部件#W，#G甘醇马奶酒#W等等，你会获得#G更多的奖励。#W" )
                EndQuestEvent()
                DispatchQuestEventList( sceneId, selfId, NPCId, x300512_g_ScriptId, x300512_g_MissionId)
                return
            end
        EndQuestEvent()
        DispatchQuestInfoNM( sceneId, selfId, NPCId, x300512_g_ScriptId, x300512_g_MissionId)
    elseif misType == x300512_g_MT_Horse then
        BeginQuestEvent( sceneId)
            --任务继续信息
            AddQuestText( sceneId, "#Y"..x300512_g_MissionName)
            AddQuestText( sceneId, x300512_g_strHorseComplete)
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, NPCId)
    elseif misType == x300512_g_MT_Material then
        BeginQuestEvent( sceneId)
            --任务继续信息
            AddQuestText( sceneId, "#Y"..x300512_g_MissionName)
            AddQuestText( sceneId, x300512_g_strMaterialContinue)
            AddQuestText( sceneId, "#r #r#G小提示:#W\n如果你能按照要求上交一些#G生活技能的原材料#W或#G生活技能制造的部件#W，#G甘醇马奶酒#W等等，你会获得#G更多的奖励。#W" )
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, NPCId)
    elseif misType == x300512_g_MT_Dig then
        BeginQuestEvent( sceneId)
            --任务继续信息
            AddQuestText( sceneId, "#Y"..x300512_g_MissionName)
            AddQuestText( sceneId, x300512_g_strDigContinue)
            AddQuestText( sceneId, "#r #r#G小提示:#W\n如果你能按照要求上交一些#G生活技能的原材料#W或#G生活技能制造的部件#W，#G甘醇马奶酒#W等等，你会获得#G更多的奖励。#W" )
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, NPCId)
    elseif misType == x300512_g_MT_KillMonster then
        BeginQuestEvent( sceneId)
            --任务继续信息
            AddQuestText( sceneId, "#Y"..x300512_g_MissionName)
            AddQuestText( sceneId, format( x300512_g_strKillContinue, x300512_g_KillMonsterTable[ mp2].name) )
            AddQuestText( sceneId, "#r #r#G小提示:#W\n如果你能按照要求上交一些#G生活技能的原材料#W或#G生活技能制造的部件#W，#G甘醇马奶酒#W等等，你会获得#G更多的奖励。#W" )
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, NPCId)
    elseif misType == x300512_g_MT_Collect then
        BeginQuestEvent( sceneId)
            --任务继续信息
            AddQuestText( sceneId, "#Y"..x300512_g_MissionName)
            AddQuestText( sceneId, x300512_g_strCollectContinue)
            AddQuestText( sceneId, "#r #r#G小提示:#W\n如果你能按照要求上交一些#G生活技能的原材料#W或#G生活技能制造的部件#W，#G甘醇马奶酒#W等等，你会获得#G更多的奖励。#W" )
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, NPCId)
    end
end

--向客户端发送任务完成信息
function x300512_DispatchCompletedInfo( sceneId, selfId, NPCId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
    local misType = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_MissionType)
    local mp2 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET2)
    local mp3 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET3)
    local level = GetLevel( sceneId, selfId)
    local strInfo = ""
    local xp = x300512_GetExpAward( sceneId, selfId, level)
    local money, shengw = x300512_GetMoneyAward( sceneId, selfId, level)
	local highcircle = x300512_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH)

    if misType == x300512_g_MT_Deliver then    -- 送信任务
        strInfo = x300512_g_strDeliverComplete
    elseif misType == x300512_g_MT_Escort then
        strInfo = x300512_g_strEscortComplete
    elseif misType == x300512_g_MT_Collect then
        strInfo = x300512_g_strCollectComplete
    elseif misType == x300512_g_MT_KillMonster then
        strInfo = x300512_g_strKillComplete
    elseif misType == x300512_g_MT_Dig then
        strInfo = x300512_g_strDigComplete
    end

    BeginQuestEvent( sceneId)
        --任务完成信息
        AddQuestText( sceneId, "#Y"..x300512_g_MissionName)
        AddQuestText( sceneId, strInfo)

        if misType ~= x300512_g_MT_Horse then
            --任务奖励信息
            if( xp > 0) then
                AddQuestExpBonus( sceneId, xp)
            end
            if( money > 0) then
                if misType == x300512_g_MT_Material then
                    AddQuestMoneyBonus2( sceneId, money)
                else
                    -- 如果有江湖请柬的Buff才显示现银奖励
                    if IsHaveSpecificImpact( sceneId, selfId, 9011) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9012) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9013) == 1 then
                        AddQuestMoneyBonus2( sceneId, money)
                    else
                        AddQuestMoneyBonus1( sceneId, money)
                    end
                end
            end
            if( shengw > 0) then
                AddQuestMoneyBonus5( sceneId, shengw)
            end
            if level >= 80 then
                AddQuestGeniusBonus( sceneId, RefixInherenceExp( sceneId, selfId, ( highcircle + 1) * 25) )
            end
        end
    EndQuestEvent()
    DispatchQuestInfoNM( sceneId, selfId, NPCId, x300512_g_ScriptId, x300512_g_MissionId)
end

--怪物被杀的消息处理
function x300512_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
    if IsPlayerStateNormal( sceneId, selfId) ~= 1 then
        return
    end

    local misIndex = 0
    local teamSize = GetNearTeamCount( sceneId, selfId)
    -- print( "附近队伍人数："..teamSize)

    if teamSize <= 1 then -- 非组队，单独做任务
        if IsHaveQuest( sceneId, selfId, x300512_g_MissionId) <= 0 then
            return
        end
        misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
        if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
            -- 如果任务已完成
            --return
        end
        local index   = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET2)
        local m1Kill  = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET4)

        if objdataId == x300512_g_KillMonsterTable[ index].monsterId and m1Kill < x300512_g_KillMonsterTable[ index].count then
            SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET4, m1Kill + 1)
        else
            -- 如果杀死的不是任务目标怪
            return
        end

    	--检测任务是否完成
        m1Kill = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET4)
    	if m1Kill >= x300512_g_KillMonsterTable[ index].count then
    		SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
    		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
            SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET6, x300512_g_FinishBound + GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET6) )
            Msg2Player( sceneId, selfId, x300512_g_strMissionFinishTip, 8, 3)
        else
            Msg2Player( sceneId, selfId, format( "已消灭#G%s#cffcf00(%d/%d)", x300512_g_KillMonsterTable[ index].name, m1Kill, x300512_g_KillMonsterTable[ index].count), 8, 3)
    	end

        x300512_ProcQuestLogRefresh( sceneId, selfId, x300512_g_MissionId)
    else
        for i = 0, teamSize - 1 do
            local memberId = GetNearTeamMember( sceneId, selfId, i)
            if memberId >= 0 and IsPlayerStateNormal( sceneId, memberId) == 1 then
                if IsHaveQuest( sceneId, memberId, x300512_g_MissionId) > 0 then -- 如果该成员接受了国家内政
                    misIndex = GetQuestIndexByID( sceneId, memberId, x300512_g_MissionId)
                    if GetQuestParam( sceneId, memberId, misIndex, 0) == 0 or GetQuestParam( sceneId, memberId, misIndex, 7) == 0 and GetQuestParam( sceneId, memberId, misIndex, x300512_MP_MissionType) == x300512_g_MT_KillMonster then -- 如果该成员的国家内政没完成并且任务类型也是杀怪任务
                        local index   = GetQuestParam( sceneId, memberId, misIndex, x300512_MP_TARGET2)
                        local m1Kill  = GetQuestParam( sceneId, memberId, misIndex, x300512_MP_TARGET4)

                        if objdataId == x300512_g_KillMonsterTable[ index].monsterId and m1Kill < x300512_g_KillMonsterTable[ index].count then
                            SetQuestByIndex( sceneId, memberId, misIndex, x300512_MP_TARGET4, m1Kill + 1)
                        end

                        --检测任务是否完成
                        m1Kill = GetQuestParam( sceneId, memberId, misIndex, x300512_MP_TARGET4)
                        if m1Kill >= x300512_g_KillMonsterTable[ index].count then
                            SetQuestByIndex( sceneId, memberId, misIndex, 0, 1)
                            SetQuestByIndex( sceneId, memberId, misIndex, 7, 1)
                            SetQuestByIndex( sceneId, memberId, misIndex, x300512_MP_TARGET6, x300512_g_FinishBound + GetQuestParam( sceneId, memberId, misIndex, x300512_MP_TARGET6) )
                        end

                        x300512_ProcQuestLogRefresh( sceneId, memberId, x300512_g_MissionId)
                    end
                end
            end
        end
    end
end

--物品改变
function x300512_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId)
    if IsHaveQuest( sceneId, selfId, x300512_g_MissionId) == 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
    local misType = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_MissionType)
    local index = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET2)
    local mp3 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET3)
    local mp4 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET4)

    if misType == x300512_g_MT_Dig then
        if GetItemCountInBag( sceneId, selfId, x300512_g_DigTarget[ index].id) >= 1 then
            if GetQuestParam( sceneId, selfId, misIndex, 0) == 0 and GetQuestParam( sceneId, selfId, misIndex, 7) == 0 then
                SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
                SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
                Msg2Player( sceneId, selfId, x300512_g_strMissionFinishTip, 8, 3)
            end
            if GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET6) < x300512_g_FinishBound then
                SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET6, x300512_g_FinishBound + GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET6) )
            end
        else
            SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
            SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)
            if GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET6) > x300512_g_FinishBound then
                SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET6, GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET6) - x300512_g_FinishBound)
            end
        end
    elseif misType == x300512_g_MT_Material then
        local have = 0
        if GetItemCountInBag( sceneId, selfId, x300512_g_MaterialTable[ index].base) >= 1 or GetItemCountInBag( sceneId, selfId, x300512_g_MaterialTable[ index].advanced[ mp3] ) >= 1 then
            if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
                return
            end
            SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
            SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
            Msg2Player( sceneId, selfId, x300512_g_strMissionFinishTip, 8, 3)
        else
            SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
            SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)
        end
    elseif misType == x300512_g_MT_Collect then
        local count = GetItemCountInBag( sceneId, selfId, x300512_g_GrowPoint[ index].itemId)
        SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET4, count)
        if count >= x300512_g_GrowPoint[ index].count then
            if GetQuestParam( sceneId, selfId, misIndex, 0) == 0 and GetQuestParam( sceneId, selfId, misIndex, 7) == 0 then
                SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
                SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
                Msg2Player( sceneId, selfId, x300512_g_strMissionFinishTip, 8, 3)
            end
            if GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET6) < x300512_g_FinishBound then
                SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET6, x300512_g_FinishBound + GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET6) )
            end
        else
            SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
            SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)
            if GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET6) > x300512_g_FinishBound then
                SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET6, GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET6) - x300512_g_FinishBound)
            end
        end
    end

    -- 前5环任务可以检查是不是代交物品
    if misType ~= x300512_g_MT_Material and misType ~= x300512_g_MT_Horse then
        local id = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET5)
        local count = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET6)
        if GetItemCountInBag( sceneId, selfId, id) >= count then
            SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
            SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
            --Msg2Player( sceneId, selfId, x300512_g_strMissionFinishTip, 8, 3)
        else
            if GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET6) < x300512_g_FinishBound then
                SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
                SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)
            end
        end
    end

    x300512_ProcQuestLogRefresh( sceneId, selfId, x300512_g_MissionId)
end

--单击NPC事件
function x300512_ProcQuestAttach( sceneId, selfId, NPCId, npcGuid, misIndex, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
    local misType = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_MissionType)
    local mp2 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET2)
    local mp4 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET4)
    local finish = GetQuestParam( sceneId, selfId, misIndex, 0)
    local complete = GetQuestParam( sceneId, selfId, misIndex, 7)

    if finish == 0 and complete == 0 then
        if misType == x300512_g_MT_Deliver and npcGuid == mp2 then
            AddQuestNumText( sceneId, x300512_g_MissionId, x300512_g_MissionName, 6, x300512_g_MissionId)
        end
        if misType == x300512_g_MT_Escort then
            if npcGuid == x300512_g_EscortTable[ mp2].npcGuid and mp4 == 0 then
                AddQuestNumText( sceneId, x300512_g_MissionId, x300512_g_MissionName, 6)
            elseif npcGuid == x300512_g_EscortTable[ mp2].targetGuid and mp4 == 1 then
                AddQuestNumText( sceneId, x300512_g_MissionId, x300512_g_MissionName, 6)
            end
        end
    else
        if misType == x300512_g_MT_Deliver and npcGuid == mp2 and GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET6) < x300512_g_FinishBound then
            AddQuestNumText( sceneId, x300512_g_MissionId, x300512_g_MissionName, 6, x300512_g_MissionId)
        end
        if misType == x300512_g_MT_Escort and GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET6) < x300512_g_FinishBound then
            if npcGuid == x300512_g_EscortTable[ mp2].npcGuid and mp4 == 0 then
                AddQuestNumText( sceneId, x300512_g_MissionId, x300512_g_MissionName, 6)
            elseif npcGuid == x300512_g_EscortTable[ mp2].targetGuid and mp4 == 1 then
                AddQuestNumText( sceneId, x300512_g_MissionId, x300512_g_MissionName, 6)
            end
        end
    end
end

-- 任务跟踪更新
function x300512_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    if IsHaveQuest( sceneId, selfId, x300512_g_MissionId) ~= 1 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
    local misType = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_MissionType)
    local mp2 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET2)
    local mp3 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET3)
    local mp4 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET4)
    local mp5 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET5)
    local mp6 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET6)
    if mp6 > x300512_g_FinishBound then
        mp6 = mp6 - x300512_g_FinishBound
    end
    local curCircle = x300512_GetMD( sceneId, selfId, MD_GUOJIARENWU_CIRCLE)
    local highcircle = x300512_GetMD( sceneId, selfId, MD_GUOJIARENWU_HIGH)

    if misType == x300512_g_MT_Material then
        -- 察看背包里有没有要收集的物品
        if GetItemCountInBag( sceneId, selfId, x300512_g_MaterialTable[ mp2].base) >= 1 or GetItemCountInBag( sceneId, selfId, x300512_g_MaterialTable[ mp2].advanced[ mp3] ) >= 1 then
            SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
            SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
        else
            SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
            SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)
        end
    elseif misType == x300512_g_MT_Horse then
        local have = 0
        for i = 0, 5 do
            local hid = GetHorseDataID( sceneId, selfId, i)
            local htype = mod( hid, 10)
            if hid >= x300512_g_GetHorse[ mp2].id and hid < x300512_g_GetHorse[ mp2].id + 100 and htype > 0 and htype < 5 then
                have = 1
                break
            end
        end

        if have == 1 then
            SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
            SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
        else
            SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
            SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)
        end
    end

    local finish = GetQuestParam( sceneId, selfId, misIndex, 0)
    local complete = GetQuestParam( sceneId, selfId, misIndex, 7)
        local strInfo = ""
        local strDescription = ""
        local tips = "#W如果你能按照要求上交一些#G生活技能的原材料#W或#G生活技能制造的部件#W，#G甘醇马奶酒#W等等，你会获得#G更多的奖励。#W"
        if misType == x300512_g_MT_Deliver then    -- 送信任务
            strInfo = format( "  把@item_%d#W送给@npc_%d或收集#G%d#W个@item_%d#W(2倍经验)", x300512_g_DeliverTable[ mp3].missionItemId, mp2, mp6, mp5)
            strDescription = x300512_g_DeliverTable[ mp3].description
        elseif misType == x300512_g_MT_KillMonster then    -- 杀怪任务
            strInfo = format( x300512_g_KillMonsterTable[ mp2].target, x300512_g_KillMonsterTable[ mp2].count, x300512_g_KillMonsterTable[ mp2].posId, 
                                      mp4, x300512_g_KillMonsterTable[ mp2].count, mp6, mp5)
            strDescription = x300512_g_KillMonsterTable[ mp2].description
        elseif misType == x300512_g_MT_Collect then    -- 采集任务
            strInfo = format( "  到%s#W采集#G%s#W(%d/%d)或收集#G%d#W个@item_%d#W(2倍经验)", x300512_g_GrowPoint[ mp2].Pos, 
                                      x300512_g_GrowPoint[ mp2].target, mp4, x300512_g_GrowPoint[ mp2].count, mp6, mp5)
            strDescription = x300512_g_GrowPoint[ mp2].description
            tips = x300512_g_GrowPoint[ mp2].tips
        elseif misType == x300512_g_MT_Escort then    -- 护送任务
            if mp4 == 0 then
                strInfo = format( "  找到@npc_%d#W或收集#G%d#W个@item_%d#W(2倍经验)", x300512_g_EscortTable[ mp2].npcGuid, mp6, mp5)
            elseif mp4 == 1 then
                strInfo = format( "  将%s安全护送到@npc_%d#W那里或收集#G%d#W个@item_%d#W(2倍经验)", x300512_g_EscortTable[ mp2].missionName, x300512_g_EscortTable[ mp2].targetGuid, mp6, mp5)
            end
            strDescription = x300512_g_EscortTable[ mp2].intro
        elseif misType == x300512_g_MT_Dig then -- 挖掘任务
            local destSceneId = x300512_CountrySceneList[ GetCurCountry( sceneId, selfId) + 1]
            local posX, posZ
            posX = x300512_g_CoordinateLib[ mp3].posX
            posZ = x300512_g_CoordinateLib[ mp3].posZ
            --做数量修正
			if mp6 > x300512_g_FinishBound then
				mp6 = mp6 - x300512_g_FinishBound
			end
            strInfo = format( "  到#aB#h00CCFF{goto_%d,%d,%d}(%d，%d)#aE#W附近使用@item_12030020#W挖掘(%d/1)或收集#G%d#W个@item_%d#W(2倍经验)", destSceneId, posX, posZ, posX, posZ, finish, mp6, mp5)
            strDescription = format( x300512_g_DigTarget[ mp2].target, destSceneId, posX, posZ, posX, posZ, x300512_g_DigTarget[ mp2].name, mp6, mp5)
        elseif misType == x300512_g_MT_Horse then
            strInfo = format( x300512_g_GetHorse[ mp2].description, x300512_g_GetHorse[ mp2].name)
            strDescription = format( x300512_g_GetHorse[ mp2].description, x300512_g_GetHorse[ mp2].name)
            tips = ""
        elseif misType == x300512_g_MT_Material then
            strDescription = format( x300512_g_MaterialTable[ mp2].target, x300512_g_MaterialTable[ mp2].base, x300512_g_MaterialTable[ mp2].advanced[ mp3], x300512_g_MaterialTable[ mp2].xpCoff[ mp3] )
            strInfo = strDescription
        end
    BeginQuestEvent(sceneId)
    if finish == 1 and complete == 1 then
        AddQuestLogCustomText( sceneId,
                                "",                             -- 标题
                                format( "%s(%d/10)", x300512_g_MissionName, curCircle + 1),          -- 任务名字
                                "任务已经完成，请回去向@npc_129042#W汇报！",      -- 任务目标
                                "",                             -- 任务NPC
                                strInfo,                        -- 任务攻略
                                strDescription,                 -- 任务描述
                                tips)                           -- 任务提示
    else
        AddQuestLogCustomText( sceneId,
                                "",                             -- 标题
                                format( "%s(%d/10)", x300512_g_MissionName, curCircle + 1),          -- 任务名字
                                strInfo,                        -- 任务目标
                                "",                             -- 任务NPC
                                strInfo,                        -- 任务攻略
                                strDescription,                 -- 任务描述
                                tips)                           -- 任务提示
    end
    local level = GetLevel( sceneId, selfId)
    local xp = x300512_GetExpAward( sceneId, selfId, level)
    local money, shengw = x300512_GetMoneyAward( sceneId, selfId, level)
    if( xp > 0) then
        AddQuestExpBonus( sceneId, xp)
    end
    if( money > 0) then
        if misType == x300512_g_MT_Material then
            AddQuestMoneyBonus2( sceneId, money)
        else
            -- 如果有江湖请柬的Buff才显示现银奖励
            if IsHaveSpecificImpact( sceneId, selfId, 9011) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9012) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9013) == 1 then
                AddQuestMoneyBonus2( sceneId, money)
            else
                AddQuestMoneyBonus1( sceneId, money)
            end
        end
    end
    if( shengw > 0) then
        AddQuestMoneyBonus5( sceneId, shengw)
    end
    if level >= 80 then
        AddQuestGeniusBonus( sceneId, RefixInherenceExp( sceneId, selfId, ( highcircle + 1) * 25) )
    end
    EndQuestEvent()
    DispatchQuestLogUpdate( sceneId, selfId, MissionId)
end

--强行加任务
function x300512_OnForceAddMission( sceneId, selfId, NPCId, MissionId)
end

-- 获得放弃任务时间
function x300512_GetTimes( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_DAOBAOKE_TIMES[ 1], MD_DAOBAOKE_TIMES[ 2], MD_DAOBAOKE_TIMES[ 3] )
end

-- 设置放弃任务时间
function x300512_SetTimes( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_DAOBAOKE_TIMES[ 1], MD_DAOBAOKE_TIMES[ 2], MD_DAOBAOKE_TIMES[ 3], value)
end

function x300512_GetMD( sceneId, selfId, mdName)
    return GetQuestData( sceneId, selfId, mdName[ 1], mdName[ 2], mdName[ 3] )
end

function x300512_SetMD( sceneId, selfId, mdName, value)
    SetQuestData( sceneId, selfId, mdName[ 1], mdName[ 2], mdName[ 3], value)
end

function x300512_OnCommitItem( sceneId, selfId, MissionId, NPCId, horseGUID_high, horseGUID_low, iHorseIndex)
    if IsHaveQuest( sceneId, selfId, x300512_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
    local misType = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_MissionType)
    local level = GetLevel( sceneId, selfId)
	local highcircle = x300512_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH)
    if misType ~= x300512_g_MT_Material and misType ~= x300512_g_MT_Horse then
        --任务奖励信息
        local xp = x300512_GetExpAward( sceneId, selfId, level) * 2
        local money, shengw = x300512_GetMoneyAward( sceneId, selfId, level)
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x300512_g_MissionName)
            AddQuestText( sceneId, x300512_g_strMaterialComplete)

            if( xp > 0) then
                AddQuestExpBonus( sceneId, xp)
            end
            if( money > 0) then
                if IsHaveSpecificImpact( sceneId, selfId, 9011) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9012) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9013) == 1 then
                    AddQuestMoneyBonus2( sceneId, money * 4)
                else
                    AddQuestMoneyBonus1( sceneId, money * 4)
                end
            end
            if( shengw > 0) then
                AddQuestMoneyBonus5( sceneId, shengw)
            end
            if level >= 80 then
                AddQuestGeniusBonus( sceneId, RefixInherenceExp( sceneId, selfId, ( highcircle + 1) * 25) )
            end
        EndQuestEvent()
        DispatchQuestContinueInfoNM( sceneId, selfId, NPCId, x300512_g_ScriptId, x300512_g_MissionId)
        -- 设置交物品完成任务标记
        SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, 1)
    else
        local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
        local misType = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_MissionType)
        local mp2 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET2)
        local mp3 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET3)
        --任务奖励信息
        local xp = x300512_GetExpAward( sceneId, selfId, level)
        local money, shengw = x300512_GetMoneyAward( sceneId, selfId, level)

        if horseGUID_low == 0 then
            if GetItemCountInBag( sceneId, selfId, x300512_g_MaterialTable[ mp2].base) < 1 then
                Msg2Player( sceneId, selfId, "你没有这个物品或该物品处于锁定状态", 8, 3)
                return
            end
            SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET4, x300512_g_MaterialTable[ mp2].base)
            -- 提交基础物品
        elseif horseGUID_low == 1 then
            if GetItemCountInBag( sceneId, selfId, x300512_g_MaterialTable[ mp2].advanced[ mp3] ) < 1 then
                Msg2Player( sceneId, selfId, "你没有这个物品或该物品处于锁定状态", 8, 3)
                return
            end
            -- 提交高级物品
            for i, item in x300512_g_MaterialTable[ mp2].advanced do
                if x300512_g_MaterialTable[ mp2].advanced[ mp3] == item then
                    xp = x300512_g_MaterialTable[ mp2].xpCoff[ i] * xp
                    money = x300512_g_MaterialTable[ mp2].money[ i]
                    SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET4, item)
                    break
                end
            end
        elseif horseGUID_low == -1 then
            Msg2Player( sceneId, selfId, "请选择要提交的物品", 8, 3)
            return
        end

        local mp4 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET4)
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x300512_g_MissionName)
            AddQuestText( sceneId, x300512_g_strMaterialComplete)

            if( xp > 0) then
                AddQuestExpBonus( sceneId, xp)
            end
            if( money > 0) then
				if IsHaveSpecificImpact( sceneId, selfId, 9011) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9012) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9013) == 1 then
					AddQuestMoneyBonus2( sceneId, money)
				else
					if misType == x300512_g_MT_Material then
						local advMaterial = 0
						if mp4 ~= x300512_g_MaterialTable[ mp2].base then
							-- 高倍经验
							for i, item in x300512_g_MaterialTable[ mp2].advanced do
								if item == mp4 then
									advMaterial = 1
									break
								end
							end
						end
						if advMaterial == 0 then
							AddQuestMoneyBonus1( sceneId, money)
						else
							AddQuestMoneyBonus2( sceneId, money)
						end
					else
						AddQuestMoneyBonus1( sceneId, money)
					end
				end
            end
            if( shengw > 0) then
                AddQuestMoneyBonus5( sceneId, shengw)
            end
            if level >= 80 then
                AddQuestGeniusBonus( sceneId, RefixInherenceExp( sceneId, selfId, ( highcircle + 1) * 25) )
            end
        EndQuestEvent()
        DispatchQuestInfoNM( sceneId, selfId, NPCId, x300512_g_ScriptId, x300512_g_MissionId)
        SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, 0)
    end

    -- 关闭界面
    BeginUICommand( sceneId)
        DispatchUICommand( sceneId, selfId, 105)
    EndUICommand( sceneId)
end

-- 挖掘事件回调
function x300512_OnDigbyShovel( sceneId, selfId)
	-- 判断有没有任务及是否完成
	if IsHaveQuestNM( sceneId, selfId, x300512_g_MissionId) <= 0 then
		return 0
	end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
    local misType = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_MissionType)
    local finish = GetQuestParam( sceneId, selfId, misIndex, 0)
    local complete = GetQuestParam( sceneId, selfId, misIndex, 7)
    local mp2 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET2)
    local mp3 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET3)

    if misType ~= x300512_g_MT_Dig then
        return 0
    end
    if finish == 1 and complete == 1 and GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET6) > x300512_g_FinishBound then
        return 0
    end

    local destSceneId = x300512_CountrySceneList[ GetCurCountry( sceneId, selfId) + 1]
    if sceneId ~= destSceneId then
        return 0
    end

	-- 获得当前坐标
    local x, z = GetWorldPos( sceneId, selfId)
    local posX, posZ
    posX = x300512_g_CoordinateLib[ mp3].posX
    posZ = x300512_g_CoordinateLib[ mp3].posZ

    if abs( x - posX) > 2 or abs( z - posZ) > 2 then
        --挖掘地点不对
        Msg2Player( sceneId, selfId, format( "这里什么也没有，请在灵气旺盛的(%d，%d)附近使用。", posX, posZ), 8, 3)
        return 0
    end

    -- 挖到物品，添加到背包
    BeginAddItem( sceneId)
    AddItem( sceneId, x300512_g_DigTarget[ mp2].id, 1)
    local result = EndAddItem( sceneId, selfId)
    if result == 0 then
        Msg2Player( sceneId, selfId, "背包已满，无法放入挖到的物品", 8, 3)
        Msg2Player( sceneId, selfId, "背包已满，无法放入挖到的物品！", 8, 2)
        return 1
    end
    AddItemListToPlayer( sceneId, selfId)
    Msg2Player( sceneId, selfId, "你得到了"..x300512_g_DigTarget[ mp2].name.."。", 8, 2)
    Msg2Player( sceneId, selfId, "你得到了"..x300512_g_DigTarget[ mp2].name, 8, 3)
    
    -- 设置任务完成标记
    SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
    SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
    Msg2Player(sceneId, selfId, x300512_g_strMissionFinishTip, 8, 3)
    -- 更新Q面板
    x300512_ProcQuestLogRefresh( sceneId, selfId, x300512_g_MissionId)

    -- 消耗铁铲可用次数
    CallScriptFunction( 300331, "LogicDeplete", sceneId, selfId)

    return 1
end

-- 骑乘变化回调函数
function x300512_ProcQuestHorseChanged( sceneId, selfId, horseId, MissionId)
    if IsHaveQuest( sceneId, selfId, x300512_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
    local misType = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_MissionType)
    local finish = GetQuestParam( sceneId, selfId, misIndex, 0)
    local complete = GetQuestParam( sceneId, selfId, misIndex, 7)

    if misType ~= x300512_g_MT_Horse then
        return
    end

    local mp2 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET2)
    local id = x300512_g_GetHorse[ mp2].id
    local have = 0
    if IsHaveHorse( sceneId, selfId, horseId) <= 0 then
        for i = 0, 5 do
            local hid = GetHorseDataID( sceneId, selfId, i)
            local htype = mod( hid, 10)
            if hid >= id and hid < id + 100 and htype > 0 and htype < 5 then
                have = 1
                break
            end
        end

        if have == 1 then
            SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
            SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
            Msg2Player( sceneId, selfId, x300512_g_strMissionFinishTip, 8, 3)
            x300512_ProcQuestLogRefresh( sceneId, selfId, x300512_g_MissionId)
        else
            SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
            SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)
            x300512_ProcQuestLogRefresh( sceneId, selfId, x300512_g_MissionId)
        end
        return
    end

    local htype = mod( horseId, 10)
    if horseId >= id and horseId < id + 100 and htype > 0 and htype < 5 then
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
        Msg2Player( sceneId, selfId, x300512_g_strMissionFinishTip, 8, 3)
        x300512_ProcQuestLogRefresh( sceneId, selfId, x300512_g_MissionId)
    end
end

-- 提交骑乘
function x300512_OnCommitPet( sceneId, selfId, MissionId, NPCId, horseGUID_high, horseGUID_low, iHorseIndex)
    if IsHaveQuest( sceneId, selfId, x300512_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
    local misType = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_MissionType)
    local horseID = GetHorseDataID( sceneId, selfId, iHorseIndex)
    local htype = mod( horseID, 10)
    local mp2 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET2)
    local id = x300512_g_GetHorse[ mp2].id
    local level = GetLevel( sceneId, selfId)
    local times = 1
	local highcircle = x300512_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH)

    local strInfo = ""
    local isGood = 0
    if horseID >= id and horseID < id + 100 and htype > 0 and htype < 5 then
        if htype ~= 1 and horseID > 100 then
            -- 良品马
            strInfo = x300512_g_strGoodHorse
            isGood = 1
            times = 2
        else
            -- 普通马
            strInfo = x300512_g_strNormalHorse
        end
        SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET4, horseGUID_high)
        SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET5, horseGUID_low)
        SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET6, isGood)

        BeginQuestEvent( sceneId)
        --任务名称
        AddQuestText( sceneId, "#Y"..x300512_g_MissionName)
        AddQuestText( sceneId, strInfo)

  		--任务奖励信息
        local xp = x300512_GetExpAward( sceneId, selfId, level) * times
        local money, shengw = x300512_GetMoneyAward( sceneId, selfId, level)
        money = money * times
        shengw = shengw * times
        if( xp > 0) then
            AddQuestExpBonus( sceneId, xp)
        end
        if( money > 0) then
            -- 如果有江湖请柬的Buff才显示现银奖励
            if IsHaveSpecificImpact( sceneId, selfId, 9011) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9012) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9013) == 1 then
                AddQuestMoneyBonus2( sceneId, money)
            else
                AddQuestMoneyBonus1( sceneId, money)
            end
        end
        if( shengw > 0) then
            AddQuestMoneyBonus5( sceneId, shengw)
        end
        if level >= 80 then
            AddQuestGeniusBonus( sceneId, RefixInherenceExp( sceneId, selfId, ( highcircle + 1) * 25) )
        end
        EndQuestEvent()
        DispatchQuestInfoNM( sceneId, selfId, NPCId, x300512_g_ScriptId, x300512_g_MissionId)
    else
        Msg2Player( sceneId, selfId, "这不是我要的马", 8, 3)
        return
    end

    -- 关闭界面
    BeginUICommand( sceneId)
        DispatchUICommand( sceneId, selfId, 102)
    EndUICommand( sceneId)
end

-- 创建要护送的Bus后，在这里设置使其能自动跟随玩家
function x300512_OnIntoBusEvent( sceneId, selfId, NPCId)
    --print( "x300519_OnIntoBusEvent" )
	local IsOwner = IsTheBusOwner( sceneId, selfId, NPCId)
	if IsOwner == 1 then
		-- 如果是玩家本人设置跟随
		AddBusMember( sceneId, selfId, NPCId)
	end
end

function x300512_OnBusStopWhenOwnerFarAway( sceneId, selfId)
	local strText = "你离护送的目标太远了，护送目标无法跟随你。"

	BeginQuestEvent( sceneId)
		AddQuestText( sceneId, strText)
	EndQuestEvent( sceneId)
	DispatchQuestTips( sceneId, selfId)

	Msg2Player( sceneId, selfId, strText, 8, 2)
end

function x300512_OnWaitTimeOut( sceneId, BusId)
	local selfId = GetBusMemberObjId( sceneId, BusId, 0)	
	if selfId == -1 then
		--玩家不在线
		if IsObjValid( sceneId, BusId) == 1 then
		    DeleteBus( sceneId, BusId, 1)
		end
		return
	end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
    local misType = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_MissionType)
    if misType ~= x300512_g_MT_Escort then
		return
    end

	DeleteBus( sceneId, BusId, 1)
	SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET4, 0)
    Msg2Player( sceneId, selfId, "由于你离开护送目标时间过久，你的护送目标消失了，请重新接取任务", 8, 3)
    Msg2Player( sceneId, selfId, "由于你离开护送目标时间过久，你的护送目标消失了，请重新接取任务。", 8, 2)

    x300512_ProcQuestLogRefresh( sceneId, selfId, x300512_g_MissionId)
end

function x300512_OnDie( sceneId, BusId, idKiller)
	local selfId = GetBusMemberObjId( sceneId, BusId, 0)	
	if selfId == -1 then
		return
	end

	-- 设置任务数据
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
    local misType = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_MissionType)
    if misType ~= x300512_g_MT_Escort then
		return
    end
	-- 当前任务阶段标记，每个阶段下的任务目标都不一样：0、寻找请求护送NPC；1、开始护送并把它带到目的NPC处；2、护送完成，回到国家内政发布人处交任务
	SetQuestByIndex( sceneId, selfId, misIndex, x300512_MP_TARGET4, 0)
	-- 更新Q面板
    x300512_ProcQuestLogRefresh( sceneId, selfId, x300512_g_MissionId)
	Msg2Player(sceneId, selfId, "护送目标已经死亡，请重新接取任务", 8, 3)
end

-- 用于测试的GM指令函数，用来选择任务类型
function x300512_GMCommand( param0, param1, param2)
    x300512_g_MissionType = param0
end

function x300512_OnCommitCancel( sceneId, selfId, NPCId)
    if IsHaveQuest( sceneId, selfId, x300512_g_MissionId) == 0 then
        return
    end

    -- 检查当前是第几环，前5环如果正常完成任务的话按取消可以继续交任务
    local curCircle = x300512_GetMD( sceneId, selfId, MD_GUOJIARENWU_CIRCLE)
    if curCircle >= 5 then
        return
    end

    local bFinished = 0
    -- 根据任务类型检查是否正常完成
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300512_g_MissionId)
    local misType = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_MissionType)
    local mp2 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET2)
    local mp3 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET3)
    local mp4 = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET4)
    if misType == x300512_g_MT_Deliver then
        bFinished = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET6)
    elseif misType == x300512_g_MT_KillMonster then
        bFinished = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET6)
    elseif misType == x300512_g_MT_Collect then
        bFinished = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET6)
    elseif misType == x300512_g_MT_Escort then
        bFinished = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET6)
    elseif misType == x300512_g_MT_Dig then
        bFinished = GetQuestParam( sceneId, selfId, misIndex, x300512_MP_TARGET6)
    end

    if bFinished > x300512_g_FinishBound then
        x300512_DispatchCompletedInfo( sceneId, selfId, NPCId)
        -- 设置交物品完成任务标记
        SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, 0)
    end
end

