--***********************
--Const
--***********************
-------------------------

--MisDescBegin


x300783_g_MissionId 				= 	9410                     --任务ID
x300783_g_ScriptId 					= 	300783                  --脚本ID
x300783_g_MissionKind 				= 	1                       --任务类型
x300783_g_LevelLess					= 	75                      --场景开放等级  <=0 表示不限制


x300783_g_MissionName				= 	"【帮会】帮会跑环"
x300783_g_MissionTarget				= 	""          --任务目标
x300783_g_MissionInfo				= 	"\t时下多事之秋，帮会中有很多棘手的事情需要得力的人去做，我希望你能助上一臂之力。\n\t你是否要接受任务？"         
x300783_g_ContinueInfo				= 	"\t怎么？你连这些简单的帮会任务都无法完成？看来我们要另外物色人选了。"  --任务继续信息
x300783_g_MissionCompleted			= 	"\t你的表现让我很欣慰，希望你以后能够继续为我们的帮会多做贡献！"  --任务完成信息
x300783_g_MissionHelp				=	"\t帮会跑环任务，环数越高，#G经验奖励#W也越高！\n\t帮会跑环中收集的物品，很多可以通过生活技能制作，或和其他玩家交易得来。"          --任务提示信息

--目标
x300783_g_ExtTarget					=	{ {type=20,n=1,target="【帮会】帮会跑环"}}

--奖励

x300783_g_ExpBonus					= 	0;--x300783_AddExpAward               	--奖励：经验
x300783_g_BonusItem					=	{}	--奖励：物品

x300783_g_BonusMoney1               = 	0
x300783_g_BonusMoney2               =   0
x300783_g_BonusMoney3               =   0

x300783_g_BonusChoiceItem           =   {}


--MisDescEnd

x300783_g_GameId					=	1030
x300783_g_DayCountLimited			=	1
x300783_g_nDaySpace					=	5    --多少天能做一次

x300783_g_EnterTime					=	{                       --接受任务的时间
											{min=0*60+0,  max=23*60+59},
										}

x300783_g_MaxStep					=	200
x300783_g_ReplyNpcId				=	138533
x300783_g_ReplyNpcObjId				=	3
----------------------------- common start ------------------------
x300783_G_TYPE_SONGXIN		=1
x300783_G_TYPE_SHOUJI		=2
x300783_G_TYPE_KILL			=3

x300783_g_BaseBonusRate = {1200,1800,2100,2400,2700,3000,3300,3600,3900,4200}  --基础奖励基数
x300783_g_ExtraBonusRate = {1,1.2,1.4,1.6,1.8,2,2.2,2.4,2.6,2.8,3,3.2,3.4,3.6,3.8,4,4.2,4.4,4.6,4.8}  --10环乘数

--x300783_g_NeedGuildValue = {0,50,110,320,650,1150}
x300783_g_NeedGuildValue = {1150,650,320,110,50}

----------------------------- common end---------------------------

----------------------------- 送信 start ------------------------
x300783_g_MissionInfo1				= 	"\t最近帮中事物繁杂，使我无法抽身拜会曾经支持过我们帮会的朋友，请你代我去拜望一下他们，就说：我们在任何情况下也不会忘记曾经帮助过我们的恩人。"
x300783_g_ContinueInfo1				= 	"\t你这么快就找到我们的朋友了？"
x300783_g_MissionCompleted1			= 	"\t你真是太客气了，些许帮助你们不必记挂在心。"
x300783_g_MissionHelp1				=	"\t#G帮会功德#W小于50点，每轮跑环任务可以完成#G100环#W子任务。随着自身帮会功德的增加，子任务环数也会增加，最高为每轮可完成#G200环#W子任务。"          --任务提示信息

x300783_g_MissionTable1 =	{ --needvalue:帮会功德
								{ id=1,  ncount=3, replynpclist = {{id=138600,name="  找到@npc_138600"},{id=138824,name="  找到@npc_138824"},{id=138822,name="  找到@npc_138822"}}},
								{ id=3,  ncount=3, replynpclist = {{id=138800,name="  找到@npc_138800"},{id=138254,name="  找到@npc_138254"},{id=138252,name="  找到@npc_138252"}}},
								{ id=11, ncount=3, replynpclist = {{id=138802,name="  找到@npc_138802"},{id=138811,name="  找到@npc_138811"},{id=138810,name="  找到@npc_138810"}}},
								{ id=13, ncount=3, replynpclist = {{id=138804,name="  找到@npc_138804"},{id=138516,name="  找到@npc_138516"},{id=138810,name="  找到@npc_138810"}}},
								{ id=21, ncount=3, replynpclist = {{id=138812,name="  找到@npc_138812"},{id=138515,name="  找到@npc_138515"},{id=138518,name="  找到@npc_138518"}}},
								{ id=23, ncount=3, replynpclist = {{id=138814,name="  找到@npc_138814"},{id=138817,name="  找到@npc_138817"},{id=138812,name="  找到@npc_138812"}}},
								{ id=31, ncount=3, replynpclist = {{id=138819,name="  找到@npc_138819"},{id=138584,name="  找到@npc_138584"},{id=138802,name="  找到@npc_138802"}}},
								{ id=33, ncount=3, replynpclist = {{id=138109,name="  找到@npc_138109"},{id=138075,name="  找到@npc_138075"},{id=138605,name="  找到@npc_138605"}}},
								{ id=41, ncount=3, replynpclist = {{id=138817,name="  找到@npc_138817"},{id=138075,name="  找到@npc_138075"},{id=138108,name="  找到@npc_138108"}}},
								{ id=43, ncount=3, replynpclist = {{id=138656,name="  找到@npc_138656"},{id=138075,name="  找到@npc_138075"},{id=138108,name="  找到@npc_138108"}}},
								{ id=51, ncount=3, replynpclist = {{id=129326,name="  去边塞找到@npc_129326"},{id=129026,name="  去边塞找到@npc_129026"},{id=129022,name="  去边塞找到@npc_129022"}}},
								{ id=53, ncount=3, replynpclist = {{id=129708,name="  去边塞找到@npc_129708"},{id=129115,name="  去边塞找到@npc_129115"},{id=129118,name="  去边塞找到@npc_129118"}}},
								{ id=61, ncount=3, replynpclist = {{id=129059,name="  去边塞找到@npc_129059"},{id=129026,name="  去边塞找到@npc_129026"},{id=129708,name="  去边塞找到@npc_129708"}}},
								{ id=63, ncount=3, replynpclist = {{id=129022,name="  去边塞找到@npc_129022"},{id=129115,name="  去边塞找到@npc_129115"},{id=129027,name="  去边塞找到@npc_129027"}}},
								{ id=71, ncount=3, replynpclist = {{id=139106,name="  去大都找到@npc_139106"},{id=140991,name="  去大都找到@npc_140991"},{id=140992,name="  去大都找到@npc_140992"}}},
								{ id=73, ncount=3, replynpclist = {{id=139067,name="  去大都找到@npc_139067"},{id=140993,name="  去大都找到@npc_140993"},{id=140986,name="  去大都找到@npc_140986"}}},
								{ id=81, ncount=3, replynpclist = {{id=140417,name="  去大都找到@npc_140417"},{id=140417,name="  去大都找到@npc_140417"},{id=129027,name="  去边塞找到@npc_129027"}}},
								{ id=83, ncount=2, replynpclist = {{id=143008,name="  去威海港找到@npc_143008"},{id=143009,name="  去威海港找到@npc_143009"}}},
								{ id=91, ncount=2, replynpclist = {{id=143014,name="  去威海港找到@npc_143014"},{id=143015,name="  去威海港找到@npc_143015"}}},
								{ id=93, ncount=2, replynpclist = {{id=143031,name="  去威海港找到@npc_143031"},{id=143075,name="  去威海港找到@npc_143075"}}},
								{ id=101,  ncount=3, replynpclist = {{id=138600,name="  找到@npc_138600"},{id=138824,name="  找到@npc_138824"},{id=138822,name="  找到@npc_138822"}}},
								{ id=103,  ncount=3, replynpclist = {{id=138800,name="  找到@npc_138800"},{id=138254,name="  找到@npc_138254"},{id=138252,name="  找到@npc_138252"}}},
								{ id=111, ncount=3, replynpclist = {{id=138802,name="  找到@npc_138802"},{id=138811,name="  找到@npc_138811"},{id=138810,name="  找到@npc_138810"}}},
								{ id=113, ncount=3, replynpclist = {{id=138804,name="  找到@npc_138804"},{id=138516,name="  找到@npc_138516"},{id=138810,name="  找到@npc_138810"}}},
								{ id=121, ncount=3, replynpclist = {{id=138812,name="  找到@npc_138812"},{id=138515,name="  找到@npc_138515"},{id=138518,name="  找到@npc_138518"}}},
								{ id=123, ncount=3, replynpclist = {{id=138814,name="  找到@npc_138814"},{id=138817,name="  找到@npc_138817"},{id=138812,name="  找到@npc_138812"}}},
								{ id=131, ncount=3, replynpclist = {{id=138819,name="  找到@npc_138819"},{id=138584,name="  找到@npc_138584"},{id=138802,name="  找到@npc_138802"}}},
								{ id=133, ncount=3, replynpclist = {{id=138109,name="  找到@npc_138109"},{id=138075,name="  找到@npc_138075"},{id=138605,name="  找到@npc_138605"}}},
								{ id=141, ncount=3, replynpclist = {{id=138817,name="  找到@npc_138817"},{id=138075,name="  找到@npc_138075"},{id=138108,name="  找到@npc_138108"}}},
								{ id=143, ncount=3, replynpclist = {{id=138656,name="  找到@npc_138656"},{id=138075,name="  找到@npc_138075"},{id=138108,name="  找到@npc_138108"}}},
								{ id=151, ncount=3, replynpclist = {{id=129326,name="  去边塞找到@npc_129326"},{id=129026,name="  去边塞找到@npc_129026"},{id=129022,name="  去边塞找到@npc_129022"}}},
								{ id=153, ncount=3, replynpclist = {{id=129708,name="  去边塞找到@npc_129708"},{id=129115,name="  去边塞找到@npc_129115"},{id=129118,name="  去边塞找到@npc_129118"}}},
								{ id=161, ncount=3, replynpclist = {{id=129059,name="  去边塞找到@npc_129059"},{id=129026,name="  去边塞找到@npc_129026"},{id=129708,name="  去边塞找到@npc_129708"}}},
								{ id=163, ncount=3, replynpclist = {{id=129022,name="  去边塞找到@npc_129022"},{id=129115,name="  去边塞找到@npc_129115"},{id=129027,name="  去边塞找到@npc_129027"}}},
								{ id=171, ncount=3, replynpclist = {{id=139106,name="  去大都找到@npc_139106"},{id=140991,name="  去大都找到@npc_140991"},{id=140992,name="  去大都找到@npc_140992"}}},
								{ id=173, ncount=3, replynpclist = {{id=139067,name="  去大都找到@npc_139067"},{id=140993,name="  去大都找到@npc_140993"},{id=140986,name="  去大都找到@npc_140986"}}},
								{ id=181, ncount=3, replynpclist = {{id=140417,name="  去大都找到@npc_140417"},{id=140417,name="  去大都找到@npc_140417"},{id=129027,name="  去边塞找到@npc_129027"}}},
								{ id=183, ncount=2, replynpclist = {{id=143008,name="  去威海港找到@npc_143008"},{id=143009,name="  去威海港找到@npc_143009"}}},
								{ id=191, ncount=2, replynpclist = {{id=143014,name="  去威海港找到@npc_143014"},{id=143015,name="  去威海港找到@npc_143015"}}},
								{ id=193, ncount=2, replynpclist = {{id=143031,name="  去威海港找到@npc_143031"},{id=143075,name="  去威海港找到@npc_143075"}}},
							}
----------------------------- 送信 end---------------------------

----------------------------- 收集 start ------------------------
x300783_g_MissionInfo2				= 	"\t现在世道纷乱，百姓处在水深火热之中，我们帮会中的有识之士准备组织起来保境安民，但目前帮中物资匮急需补充，你可否资助一些？\n"
x300783_g_ContinueInfo2				= 	"\t这件物品着这么难以找到吗？"
x300783_g_MissionCompleted2			= 	"\t谢谢你的慷慨解囊。"
x300783_g_MissionHelp2				=	"\t#G帮会功德#W小于50点，每轮跑环任务可以完成#G100环#W子任务。随着自身帮会功德的增加，子任务环数也会增加，最高为每轮可完成#G200环#W子任务。"          --任务提示信息

x300783_g_MissionTable2 =	{ --needvalue:帮会功德
							
{ id=2, ncount=4,needitem={{itemid=11020002,count=1},{itemid=11020001,count=1},{itemid=11030401,count=1},{itemid=11030001,count=1}}},
{ id=4, ncount=6,needitem={{itemid=11041010,count=1},{itemid=11041000,count=1},{itemid=11041020,count=1},{itemid=11041030,count=1},{itemid=11041040,count=1},{itemid=11041050,count=1}}},
{ id=6, ncount=6,needitem={{itemid=11000200,count=1},{itemid=11050001,count=1},{itemid=11020002,count=1},{itemid=11020001,count=1},{itemid=11030401,count=1},{itemid=11030001,count=1}}}, 
{ id=7, ncount=8,needitem={{itemid=11000201,count=1},{itemid=11050002,count=1},{itemid=11041010,count=1},{itemid=11041000,count=1},{itemid=11041020,count=1},{itemid=11041030,count=1},{itemid=11041040,count=1},{itemid=11041050,count=1}}},
{ id=9, ncount=6,needitem={{itemid=11000200,count=1},{itemid=11050001,count=1},{itemid=11020002,count=1},{itemid=11020001,count=1},{itemid=11030401,count=1},{itemid=11030001,count=1}}},
{ id=10, ncount=8,needitem={{itemid=11000201,count=1},{itemid=11050002,count=1},{itemid=11041010,count=1},{itemid=11041000,count=1},{itemid=11041020,count=1},{itemid=11041030,count=1},{itemid=11041040,count=1},{itemid=11041050,count=1}}},
{ id=12, ncount=4,needitem={{itemid=11020002,count=1},{itemid=11020001,count=1},{itemid=11030401,count=1},{itemid=11030001,count=1}}},
{ id=14, ncount=6,needitem={{itemid=11041010,count=1},{itemid=11041000,count=1},{itemid=11041020,count=1},{itemid=11041030,count=1},{itemid=11041040,count=1},{itemid=11041050,count=1}}},
{ id=16, ncount=6,needitem={{itemid=11000200,count=1},{itemid=11050001,count=1},{itemid=11020002,count=1},{itemid=11020001,count=1},{itemid=11030401,count=1},{itemid=11030001,count=1}}},
{ id=17, ncount=8,needitem={{itemid=11000201,count=1},{itemid=11050002,count=1},{itemid=11041010,count=1},{itemid=11041000,count=1},{itemid=11041020,count=1},{itemid=11041030,count=1},{itemid=11041040,count=1},{itemid=11041050,count=1}}},
{ id=19, ncount=11,needitem={{itemid=12010200,count=1},{itemid=12020001,count=1},{itemid=12020002,count=1},{itemid=12020003,count=1},{itemid=12020004,count=1},{itemid=12020005,count=1},{itemid=12020006,count=1},{itemid=12010300,count=1},{itemid=14030001,count=1},{itemid=14030006,count=1},{itemid=14030011,count=1}}},
{ id=20, ncount=13,needitem={{itemid=10280040,count=1},{itemid=10290040,count=1},{itemid=10200040,count=1},{itemid=10230040,count=1},{itemid=10250040,count=1},{itemid=10260040,count=1},{itemid=10270040,count=1},{itemid=10010040,count=1},{itemid=10020040,count=1},{itemid=10030040,count=1},{itemid=10040040,count=1},{itemid=10050040,count=1},{itemid=10060040,count=1}}},
{ id=22, ncount=4,needitem={{itemid=11020002,count=1},{itemid=11020001,count=1},{itemid=11030401,count=1},{itemid=11030001,count=1}}},
{ id=24, ncount=6,needitem={{itemid=11041010,count=1},{itemid=11041000,count=1},{itemid=11041020,count=1},{itemid=11041030,count=1},{itemid=11041040,count=1},{itemid=11041050,count=1}}},
{ id=26, ncount=6,needitem={{itemid=11000201,count=1},{itemid=11050002,count=1},{itemid=11020002,count=1},{itemid=11020001,count=1},{itemid=11030401,count=1},{itemid=11030001,count=1}}},
{ id=27, ncount=8,needitem={{itemid=11000201,count=1},{itemid=11050002,count=1},{itemid=11041010,count=1},{itemid=11041000,count=1},{itemid=11041020,count=1},{itemid=11041030,count=1},{itemid=11041040,count=1},{itemid=11041050,count=1}}},
{ id=29, ncount=11,needitem={{itemid=12010200,count=1},{itemid=12020001,count=1},{itemid=12020002,count=1},{itemid=12020003,count=1},{itemid=12020004,count=1},{itemid=12020005,count=1},{itemid=12020006,count=1},{itemid=12010300,count=1},{itemid=14020001,count=1},{itemid=14020006,count=1},{itemid=14020011,count=1}}},
{ id=30, ncount=13,needitem={{itemid=10280040,count=1},{itemid=10290040,count=1},{itemid=10200040,count=1},{itemid=10230040,count=1},{itemid=10250040,count=1},{itemid=10260040,count=1},{itemid=10270040,count=1},{itemid=10010040,count=1},{itemid=10020040,count=1},{itemid=10030040,count=1},{itemid=10040040,count=1},{itemid=10050040,count=1},{itemid=10060040,count=1}}},
{ id=32, ncount=8,needitem={{itemid=11020002,count=1},{itemid=11020001,count=1},{itemid=11030401,count=1},{itemid=11030001,count=1},{itemid=11020006,count=1},{itemid=11020007,count=1},{itemid=11030003,count=1},{itemid=11030402,count=1}}},
{ id=34, ncount=6,needitem={{itemid=11041010,count=1},{itemid=11041000,count=1},{itemid=11041020,count=1},{itemid=11041030,count=1},{itemid=11041040,count=1},{itemid=11041050,count=1}}},
{ id=36, ncount=10,needitem={{itemid=11000201,count=1},{itemid=11050002,count=1},{itemid=11020002,count=1},{itemid=11020001,count=1},{itemid=11030401,count=1},{itemid=11030001,count=1},{itemid=11020006,count=1},{itemid=11020007,count=1},{itemid=11030003,count=1},{itemid=11030402,count=1}}},
{ id=37, ncount=8,needitem={{itemid=11000202,count=1},{itemid=11050003,count=1},{itemid=11041010,count=1},{itemid=11041000,count=1},{itemid=11041020,count=1},{itemid=11041030,count=1},{itemid=11041040,count=1},{itemid=11041050,count=1}}},
{ id=39, ncount=11,needitem={{itemid=12010200,count=1},{itemid=12020001,count=1},{itemid=12020002,count=1},{itemid=12020003,count=1},{itemid=12020004,count=1},{itemid=12020005,count=1},{itemid=12020006,count=1},{itemid=12010300,count=1},{itemid=14030001,count=1},{itemid=14030006,count=1},{itemid=14030011,count=1}}},
{ id=40, ncount=13,needitem={{itemid=10280040,count=1},{itemid=10290040,count=1},{itemid=10200040,count=1},{itemid=10230040,count=1},{itemid=10250040,count=1},{itemid=10260040,count=1},{itemid=10270040,count=1},{itemid=10010040,count=1},{itemid=10020040,count=1},{itemid=10030040,count=1},{itemid=10040040,count=1},{itemid=10050040,count=1},{itemid=10060040,count=1}}},
{ id=42, ncount=4,needitem={{itemid=11020006,count=1},{itemid=11020007,count=1},{itemid=11030003,count=1},{itemid=11030402,count=1}}},
{ id=44, ncount=12,needitem={{itemid=11041010,count=1},{itemid=11041000,count=1},{itemid=11041020,count=1},{itemid=11041030,count=1},{itemid=11041040,count=1},{itemid=11041050,count=1},{itemid=11041011,count=1},{itemid=11041001,count=1},{itemid=11041021,count=1},{itemid=11041031,count=1},{itemid=11041041,count=1},{itemid=11041051,count=1}}},
{ id=46, ncount=6,needitem={{itemid=11000201,count=1},{itemid=11050002,count=1},{itemid=11020006,count=1},{itemid=11020007,count=1},{itemid=11030003,count=1},{itemid=11030402,count=1}}},
{ id=47, ncount=14,needitem={{itemid=11000202,count=1},{itemid=11050003,count=1},{itemid=11041010,count=1},{itemid=11041000,count=1},{itemid=11041020,count=1},{itemid=11041030,count=1},{itemid=11041040,count=1},{itemid=11041050,count=1},{itemid=11041011,count=1},{itemid=11041001,count=1},{itemid=11041021,count=1},{itemid=11041031,count=1},{itemid=11041041,count=1},{itemid=11041051,count=1}}},
{ id=49, ncount=11,needitem={{itemid=12010200,count=1},{itemid=12020001,count=1},{itemid=12020002,count=1},{itemid=12020003,count=1},{itemid=12020004,count=1},{itemid=12020005,count=1},{itemid=12020006,count=1},{itemid=12010300,count=1},{itemid=14030001,count=1},{itemid=14030006,count=1},{itemid=14030011,count=1}}},
{ id=50, ncount=13,needitem={{itemid=10280040,count=1},{itemid=10290040,count=1},{itemid=10200040,count=1},{itemid=10230040,count=1},{itemid=10250040,count=1},{itemid=10260040,count=1},{itemid=10270040,count=1},{itemid=10010040,count=1},{itemid=10020040,count=1},{itemid=10030040,count=1},{itemid=10040040,count=1},{itemid=10050040,count=1},{itemid=10060040,count=1}}},
{ id=52, ncount=4,needitem={{itemid=11020006,count=1},{itemid=11020007,count=1},{itemid=11030003,count=1},{itemid=11030402,count=1}}},
{ id=54, ncount=6,needitem={{itemid=11041011,count=1},{itemid=11041001,count=1},{itemid=11041021,count=1},{itemid=11041031,count=1},{itemid=11041041,count=1},{itemid=11041051,count=1}}},
{ id=56, ncount=6,needitem={{itemid=11000201,count=1},{itemid=11050002,count=1},{itemid=11020006,count=1},{itemid=11020007,count=1},{itemid=11030003,count=1},{itemid=11030402,count=1}}},
{ id=57, ncount=6,needitem={{itemid=11000202,count=1},{itemid=11050003,count=1},{itemid=11041011,count=1},{itemid=11041001,count=1},{itemid=11041021,count=1},{itemid=11041031,count=1}}},
{ id=59, ncount=19,needitem={{itemid=12010300,count=1},{itemid=12020001,count=1},{itemid=12020002,count=1},{itemid=12020003,count=1},{itemid=14030001,count=1},{itemid=14020006,count=1},{itemid=14020011,count=1},{itemid=12010201,count=1},{itemid=12020011,count=1},{itemid=12020012,count=1},{itemid=12020013,count=1},{itemid=12020014,count=1},{itemid=12020015,count=1},{itemid=12020016,count=1},{itemid=12010301,count=1},{itemid=14030002,count=1},{itemid=14030007,count=1},{itemid=14030012,count=1},{itemid=14030012,count=1}}},
{ id=60, ncount=13,needitem={{itemid=10280040,count=1},{itemid=10290040,count=1},{itemid=10200040,count=1},{itemid=10230040,count=1},{itemid=10250040,count=1},{itemid=10260040,count=1},{itemid=10270040,count=1},{itemid=10010040,count=1},{itemid=10020040,count=1},{itemid=10030040,count=1},{itemid=10040040,count=1},{itemid=10050040,count=1},{itemid=10060040,count=1}}},
{ id=62, ncount=4,needitem={{itemid=11020006,count=1},{itemid=11020007,count=1},{itemid=11030003,count=1},{itemid=11030402,count=1}}},
{ id=64, ncount=6,needitem={{itemid=11041011,count=1},{itemid=11041001,count=1},{itemid=11041021,count=1},{itemid=11041031,count=1},{itemid=11041041,count=1},{itemid=11041051,count=1}}},
{ id=66, ncount=6,needitem={{itemid=11000201,count=1},{itemid=11050002,count=1},{itemid=11020006,count=1},{itemid=11020007,count=1},{itemid=11030003,count=1},{itemid=11030402,count=1}}},
{ id=67, ncount=8,needitem={{itemid=11000202,count=1},{itemid=11050003,count=1},{itemid=11041011,count=1},{itemid=11041001,count=1},{itemid=11041021,count=1},{itemid=11041031,count=1},{itemid=11041041,count=1},{itemid=11041051,count=1}}},
{ id=69, ncount=12,needitem={{itemid=12010201,count=1},{itemid=12020011,count=1},{itemid=12020012,count=1},{itemid=12020013,count=1},{itemid=12020014,count=1},{itemid=12020015,count=1},{itemid=12020016,count=1},{itemid=12010301,count=1},{itemid=14020002,count=1},{itemid=14020007,count=1},{itemid=14020012,count=1},{itemid=14020012,count=1}}},
{ id=70, ncount=20,needitem={{itemid=10280040,count=1},{itemid=10270040,count=1},{itemid=10250040,count=1},{itemid=10010040,count=1},{itemid=10030040,count=1},{itemid=10060040,count=1},{itemid=10280050,count=1},{itemid=10290050,count=1},{itemid=10010050,count=1},{itemid=10020050,count=1},{itemid=10030050,count=1},{itemid=10040050,count=1},{itemid=10050050,count=1},{itemid=10060050,count=1},{itemid=10200050,count=1},{itemid=10230050,count=1},{itemid=10250050,count=1},{itemid=10260050,count=1},{itemid=10260050,count=1},{itemid=10270050,count=1}}},
{ id=72, ncount=4,needitem={{itemid=11020006,count=1},{itemid=11020007,count=1},{itemid=11030003,count=1},{itemid=11030402,count=1}}},
{ id=74, ncount=6,needitem={{itemid=11041011,count=1},{itemid=11041001,count=1},{itemid=11041021,count=1},{itemid=11041031,count=1},{itemid=11041041,count=1},{itemid=11041051,count=1}}},
{ id=76, ncount=6,needitem={{itemid=11000201,count=1},{itemid=11050002,count=1},{itemid=11020006,count=1},{itemid=11020007,count=1},{itemid=11030003,count=1},{itemid=11030402,count=1}}},
{ id=77, ncount=8,needitem={{itemid=11000202,count=1},{itemid=11050003,count=1},{itemid=11041011,count=1},{itemid=11041001,count=1},{itemid=11041021,count=1},{itemid=11041031,count=1},{itemid=11041041,count=1},{itemid=11041051,count=1}}},
{ id=79, ncount=11,needitem={{itemid=12010201,count=1},{itemid=12020011,count=1},{itemid=12020012,count=1},{itemid=12020013,count=1},{itemid=12020014,count=1},{itemid=12020015,count=1},{itemid=12020016,count=1},{itemid=12010301,count=1},{itemid=14030002,count=1},{itemid=14030007,count=1},{itemid=14030012,count=1}}},
{ id=80, ncount=13,needitem={{itemid=10280050,count=1},{itemid=10290050,count=1},{itemid=10010050,count=1},{itemid=10020050,count=1},{itemid=10030050,count=1},{itemid=10040050,count=1},{itemid=10050050,count=1},{itemid=10060050,count=1},{itemid=10200050,count=1},{itemid=10230050,count=1},{itemid=10250050,count=1},{itemid=10260050,count=1},{itemid=10270050,count=1}}},
{ id=82, ncount=8,needitem={{itemid=11020006,count=1},{itemid=11020007,count=1},{itemid=11030003,count=1},{itemid=11030402,count=1},{itemid=11020010,count=1},{itemid=11020011,count=1},{itemid=11030005,count=1},{itemid=11030403,count=1}}},
{ id=84, ncount=6,needitem={{itemid=11041011,count=1},{itemid=11041001,count=1},{itemid=11041021,count=1},{itemid=11041031,count=1},{itemid=11041041,count=1},{itemid=11041051,count=1}}},
{ id=86, ncount=10,needitem={{itemid=11000201,count=1},{itemid=11050002,count=1},{itemid=11020006,count=1},{itemid=11020007,count=1},{itemid=11030003,count=1},{itemid=11030402,count=1},{itemid=11020010,count=1},{itemid=11020011,count=1},{itemid=11030005,count=1},{itemid=11030403,count=1}}},
{ id=87, ncount=8,needitem={{itemid=11000202,count=1},{itemid=11050003,count=1},{itemid=11041011,count=1},{itemid=11041001,count=1},{itemid=11041021,count=1},{itemid=11041031,count=1},{itemid=11041041,count=1},{itemid=11041051,count=1}}},
{ id=89, ncount=11,needitem={{itemid=12010201,count=1},{itemid=12020011,count=1},{itemid=12020012,count=1},{itemid=12020013,count=1},{itemid=12020014,count=1},{itemid=12020015,count=1},{itemid=12020016,count=1},{itemid=12010301,count=1},{itemid=14020002,count=1},{itemid=14020007,count=1},{itemid=14020012,count=1}}},
{ id=90, ncount=13,needitem={{itemid=10280050,count=1},{itemid=10290050,count=1},{itemid=10010050,count=1},{itemid=10020050,count=1},{itemid=10030050,count=1},{itemid=10040050,count=1},{itemid=10050050,count=1},{itemid=10060050,count=1},{itemid=10200050,count=1},{itemid=10230050,count=1},{itemid=10250050,count=1},{itemid=10260050,count=1},{itemid=10270050,count=1}}},
{ id=92, ncount=4,needitem={{itemid=11020010,count=1},{itemid=11020011,count=1},{itemid=11030005,count=1},{itemid=11030403,count=1}}},
{ id=94, ncount=12,needitem={{itemid=11041011,count=1},{itemid=11041001,count=1},{itemid=11041021,count=1},{itemid=11041031,count=1},{itemid=11041041,count=1},{itemid=11041051,count=1},{itemid=11041012,count=1},{itemid=11041002,count=1},{itemid=11041022,count=1},{itemid=11041032,count=1},{itemid=11041042,count=1},{itemid=11041052,count=1}}},
{ id=96, ncount=6,needitem={{itemid=11000201,count=1},{itemid=11050002,count=1},{itemid=11020010,count=1},{itemid=11020011,count=1},{itemid=11030005,count=1},{itemid=11030403,count=1}}},
{ id=97, ncount=14,needitem={{itemid=11000202,count=1},{itemid=11050003,count=1},{itemid=11041011,count=1},{itemid=11041001,count=1},{itemid=11041021,count=1},{itemid=11041031,count=1},{itemid=11041041,count=1},{itemid=11041051,count=1},{itemid=11041012,count=1},{itemid=11041002,count=1},{itemid=11041022,count=1},{itemid=11041032,count=1},{itemid=11041042,count=1},{itemid=11041052,count=1}}},
{ id=99, ncount=11,needitem={{itemid=12010201,count=1},{itemid=12020011,count=1},{itemid=12020012,count=1},{itemid=12020013,count=1},{itemid=12020014,count=1},{itemid=12020015,count=1},{itemid=12020016,count=1},{itemid=12010301,count=1},{itemid=14030002,count=1},{itemid=14030007,count=1},{itemid=14030012,count=1}}},
{ id=100, ncount=13,needitem={{itemid=10280050,count=1},{itemid=10290050,count=1},{itemid=10010050,count=1},{itemid=10020050,count=1},{itemid=10030050,count=1},{itemid=10040050,count=1},{itemid=10050050,count=1},{itemid=10060050,count=1},{itemid=10200050,count=1},{itemid=10230050,count=1},{itemid=10250050,count=1},{itemid=10260050,count=1},{itemid=10270050,count=1}}},
{ id=102, ncount=4,needitem={{itemid=11020010,count=1},{itemid=11020011,count=1},{itemid=11030005,count=1},{itemid=11030403,count=1}}},
{ id=104, ncount=6,needitem={{itemid=11041012,count=1},{itemid=11041002,count=1},{itemid=11041022,count=1},{itemid=11041032,count=1},{itemid=11041042,count=1},{itemid=11041052,count=1}}},
{ id=106, ncount=6,needitem={{itemid=11000201,count=1},{itemid=11050002,count=1},{itemid=11020010,count=1},{itemid=11020011,count=1},{itemid=11030005,count=1},{itemid=11030403,count=1}}},
{ id=107, ncount=8,needitem={{itemid=11000202,count=1},{itemid=11050003,count=1},{itemid=11041012,count=1},{itemid=11041002,count=1},{itemid=11041022,count=1},{itemid=11041032,count=1},{itemid=11041042,count=1},{itemid=11041052,count=1}}},
{ id=109, ncount=25,needitem={{itemid=12010201,count=1},{itemid=12020011,count=1},{itemid=12020012,count=1},{itemid=12020013,count=1},{itemid=12020014,count=1},{itemid=12020015,count=1},{itemid=12020016,count=1},{itemid=12010301,count=1},{itemid=14020002,count=1},{itemid=14020007,count=1},{itemid=14020012,count=1},{itemid=14040002,count=1},{itemid=14010002,count=1},{itemid=14010007,count=1},{itemid=14010012,count=1},{itemid=14040006,count=1},{itemid=12010202,count=1},{itemid=12020021,count=1},{itemid=12020021,count=1},{itemid=12020022,count=1},{itemid=12020023,count=1},{itemid=12020024,count=1},{itemid=12020025,count=1},{itemid=12020026,count=1},{itemid=12010302,count=1}}},
{ id=110, ncount=13,needitem={{itemid=10280050,count=1},{itemid=10290050,count=1},{itemid=10010050,count=1},{itemid=10020050,count=1},{itemid=10030050,count=1},{itemid=10040050,count=1},{itemid=10050050,count=1},{itemid=10060050,count=1},{itemid=10200050,count=1},{itemid=10230050,count=1},{itemid=10250050,count=1},{itemid=10260050,count=1},{itemid=10270050,count=1}}},
{ id=112,ncount=4,needitem={{itemid=11020010,count=1},{itemid=11020011,count=1},{itemid=11030005,count=1},{itemid=11030403,count=1}}},
{ id=114, ncount=6,needitem={{itemid=11041012,count=1},{itemid=11041002,count=1},{itemid=11041022,count=1},{itemid=11041032,count=1},{itemid=11041042,count=1},{itemid=11041052,count=1}}},
{ id=116, ncount=6,needitem={{itemid=11000201,count=1},{itemid=11050002,count=1},{itemid=11020010,count=1},{itemid=11020011,count=1},{itemid=11030005,count=1},{itemid=11030403,count=1}}},
{ id=117, ncount=8,needitem={{itemid=11000202,count=1},{itemid=11050003,count=1},{itemid=11041012,count=1},{itemid=11041002,count=1},{itemid=11041022,count=1},{itemid=11041032,count=1},{itemid=11041042,count=1},{itemid=11041052,count=1}}},
{ id=119, ncount=25,needitem={{itemid=12010201,count=1},{itemid=12020011,count=1},{itemid=12020012,count=1},{itemid=12020013,count=1},{itemid=12020014,count=1},{itemid=12020015,count=1},{itemid=12020016,count=1},{itemid=12010301,count=1},{itemid=14020002,count=1},{itemid=14020007,count=1},{itemid=14020012,count=1},{itemid=14040002,count=1},{itemid=14010002,count=1},{itemid=14010007,count=1},{itemid=14010012,count=1},{itemid=14040006,count=1},{itemid=12010202,count=1},{itemid=12020021,count=1},{itemid=12020021,count=1},{itemid=12020022,count=1},{itemid=12020023,count=1},{itemid=12020024,count=1},{itemid=12020025,count=1},{itemid=12020026,count=1},{itemid=12010302,count=1}}},
{ id=120, ncount=20,needitem={{itemid=10280050,count=1},{itemid=10020050,count=1},{itemid=10040050,count=1},{itemid=10060050,count=1},{itemid=10250050,count=1},{itemid=10270050,count=1},{itemid=10280070,count=1},{itemid=10290070,count=1},{itemid=10200060,count=1},{itemid=10230060,count=1},{itemid=10250060,count=1},{itemid=10260060,count=1},{itemid=10270060,count=1},{itemid=10010060,count=1},{itemid=10020060,count=1},{itemid=10030060,count=1},{itemid=10040060,count=1},{itemid=10050060,count=1},{itemid=10050060,count=1},{itemid=10060060,count=1}}},
{ id=122, ncount=4,needitem={{itemid=11020010,count=1},{itemid=11020011,count=1},{itemid=11030005,count=1},{itemid=11030403,count=1}}},
{ id=124, ncount=6,needitem={{itemid=11041012,count=1},{itemid=11041002,count=1},{itemid=11041022,count=1},{itemid=11041032,count=1},{itemid=11041042,count=1},{itemid=11041052,count=1}}},
{ id=126, ncount=6,needitem={{itemid=11000201,count=1},{itemid=11050002,count=1},{itemid=11020010,count=1},{itemid=11020011,count=1},{itemid=11030005,count=1},{itemid=11030403,count=1}}},
{ id=127, ncount=8,needitem={{itemid=11000202,count=1},{itemid=11050003,count=1},{itemid=11041012,count=1},{itemid=11041002,count=1},{itemid=11041022,count=1},{itemid=11041032,count=1},{itemid=11041042,count=1},{itemid=11041052,count=1}}},
{ id=129, ncount=25,needitem={{itemid=12010201,count=1},{itemid=12020011,count=1},{itemid=12020012,count=1},{itemid=12020013,count=1},{itemid=12020014,count=1},{itemid=12020015,count=1},{itemid=12020016,count=1},{itemid=12010301,count=1},{itemid=14020002,count=1},{itemid=14020007,count=1},{itemid=14020012,count=1},{itemid=14040002,count=1},{itemid=14010002,count=1},{itemid=14010007,count=1},{itemid=14010012,count=1},{itemid=14040006,count=1},{itemid=12010202,count=1},{itemid=12020021,count=1},{itemid=12020021,count=1},{itemid=12020022,count=1},{itemid=12020023,count=1},{itemid=12020024,count=1},{itemid=12020025,count=1},{itemid=12020026,count=1},{itemid=12010302,count=1}}},
{ id=130, ncount=20,needitem={{itemid=10280050,count=1},{itemid=10020050,count=1},{itemid=10040050,count=1},{itemid=10060050,count=1},{itemid=10250050,count=1},{itemid=10270050,count=1},{itemid=10280070,count=1},{itemid=10290070,count=1},{itemid=10200060,count=1},{itemid=10230060,count=1},{itemid=10250060,count=1},{itemid=10260060,count=1},{itemid=10270060,count=1},{itemid=10010060,count=1},{itemid=10020060,count=1},{itemid=10030060,count=1},{itemid=10040060,count=1},{itemid=10050060,count=1},{itemid=10050060,count=1},{itemid=10060060,count=1}}},
{ id=132, ncount=4,needitem={{itemid=11020010,count=1},{itemid=11020011,count=1},{itemid=11030005,count=1},{itemid=11030403,count=1}}},
{ id=134, ncount=6,needitem={{itemid=11041012,count=1},{itemid=11041002,count=1},{itemid=11041022,count=1},{itemid=11041032,count=1},{itemid=11041042,count=1},{itemid=11041052,count=1}}},
{ id=136, ncount=6,needitem={{itemid=11000201,count=1},{itemid=11050002,count=1},{itemid=11020010,count=1},{itemid=11020011,count=1},{itemid=11030005,count=1},{itemid=11030403,count=1}}},
{ id=137, ncount=8,needitem={{itemid=11000202,count=1},{itemid=11050003,count=1},{itemid=11041012,count=1},{itemid=11041002,count=1},{itemid=11041022,count=1},{itemid=11041032,count=1},{itemid=11041042,count=1},{itemid=11041052,count=1}}},
{ id=139, ncount=13,needitem={{itemid=14040002,count=1},{itemid=14010002,count=1},{itemid=14010007,count=1},{itemid=14010012,count=1},{itemid=14040006,count=1},{itemid=12010202,count=1},{itemid=12020021,count=1},{itemid=12020022,count=1},{itemid=12020023,count=1},{itemid=12020024,count=1},{itemid=12020025,count=1},{itemid=12020026,count=1},{itemid=12010302,count=1}}},
{ id=140, ncount=13,needitem={{itemid=10280070,count=1},{itemid=10290070,count=1},{itemid=10200060,count=1},{itemid=10230060,count=1},{itemid=10250060,count=1},{itemid=10260060,count=1},{itemid=10270060,count=1},{itemid=10010060,count=1},{itemid=10020060,count=1},{itemid=10030060,count=1},{itemid=10040060,count=1},{itemid=10050060,count=1},{itemid=10060060,count=1}}},
{ id=142, ncount=4,needitem={{itemid=11020010,count=1},{itemid=11020011,count=1},{itemid=11030005,count=1},{itemid=11030403,count=1}}},
{ id=144, ncount=6,needitem={{itemid=11041012,count=1},{itemid=11041002,count=1},{itemid=11041022,count=1},{itemid=11041032,count=1},{itemid=11041042,count=1},{itemid=11041052,count=1}}},
{ id=146, ncount=6,needitem={{itemid=11000201,count=1},{itemid=11050002,count=1},{itemid=11020010,count=1},{itemid=11020011,count=1},{itemid=11030005,count=1},{itemid=11030403,count=1}}},
{ id=147, ncount=8,needitem={{itemid=11000202,count=1},{itemid=11050003,count=1},{itemid=11041012,count=1},{itemid=11041002,count=1},{itemid=11041022,count=1},{itemid=11041032,count=1},{itemid=11041042,count=1},{itemid=11041052,count=1}}},
{ id=149, ncount=13,needitem={{itemid=14040002,count=1},{itemid=14010002,count=1},{itemid=14010007,count=1},{itemid=14010012,count=1},{itemid=14040006,count=1},{itemid=12010202,count=1},{itemid=12020021,count=1},{itemid=12020022,count=1},{itemid=12020023,count=1},{itemid=12020024,count=1},{itemid=12020025,count=1},{itemid=12020026,count=1},{itemid=12010302,count=1}}},
{ id=150, ncount=13,needitem={{itemid=10280070,count=1},{itemid=10290070,count=1},{itemid=10200060,count=1},{itemid=10230060,count=1},{itemid=10250060,count=1},{itemid=10260060,count=1},{itemid=10270060,count=1},{itemid=10010060,count=1},{itemid=10020060,count=1},{itemid=10030060,count=1},{itemid=10040060,count=1},{itemid=10050060,count=1},{itemid=10060060,count=1}}},
{ id=152, ncount=8,needitem={{itemid=11020010,count=1},{itemid=11020011,count=1},{itemid=11030005,count=1},{itemid=11030403,count=1},{itemid=11020014,count=1},{itemid=11020015,count=1},{itemid=11030007,count=1},{itemid=11030404,count=1}}},
{ id=154, ncount=6,needitem={{itemid=11041012,count=1},{itemid=11041002,count=1},{itemid=11041022,count=1},{itemid=11041032,count=1},{itemid=11041042,count=1},{itemid=11041052,count=1}}},
{ id=156, ncount=6,needitem={{itemid=11000201,count=1},{itemid=11050002,count=1},{itemid=11020010,count=1},{itemid=11020011,count=1},{itemid=11030005,count=1},{itemid=11030403,count=1}}},
{ id=157, ncount=8,needitem={{itemid=11000202,count=1},{itemid=11050003,count=1},{itemid=11041012,count=1},{itemid=11041002,count=1},{itemid=11041022,count=1},{itemid=11041032,count=1},{itemid=11041042,count=1},{itemid=11041052,count=1}}},
{ id=159, ncount=13,needitem={{itemid=14040002,count=1},{itemid=14010002,count=1},{itemid=14010007,count=1},{itemid=14010012,count=1},{itemid=14040006,count=1},{itemid=12010202,count=1},{itemid=12020021,count=1},{itemid=12020022,count=1},{itemid=12020023,count=1},{itemid=12020024,count=1},{itemid=12020025,count=1},{itemid=12020026,count=1},{itemid=12010302,count=1}}},
{ id=160, ncount=13,needitem={{itemid=10280070,count=1},{itemid=10290070,count=1},{itemid=10200060,count=1},{itemid=10230060,count=1},{itemid=10250060,count=1},{itemid=10260060,count=1},{itemid=10270060,count=1},{itemid=10010060,count=1},{itemid=10020060,count=1},{itemid=10030060,count=1},{itemid=10040060,count=1},{itemid=10050060,count=1},{itemid=10060060,count=1}}},
{ id=162, ncount=8,needitem={{itemid=11020010,count=1},{itemid=11020011,count=1},{itemid=11030005,count=1},{itemid=11030403,count=1},{itemid=11020014,count=1},{itemid=11020015,count=1},{itemid=11030007,count=1},{itemid=11030404,count=1}}},
{ id=164, ncount=6,needitem={{itemid=11041012,count=1},{itemid=11041002,count=1},{itemid=11041022,count=1},{itemid=11041032,count=1},{itemid=11041042,count=1},{itemid=11041052,count=1}}},
{ id=166, ncount=10,needitem={{itemid=11000202,count=1},{itemid=11050002,count=1},{itemid=11020010,count=1},{itemid=11020011,count=1},{itemid=11030005,count=1},{itemid=11030403,count=1},{itemid=11020014,count=1},{itemid=11020015,count=1},{itemid=11030007,count=1},{itemid=11030404,count=1}}},
{ id=167, ncount=8,needitem={{itemid=11000203,count=1},{itemid=11050003,count=1},{itemid=11041012,count=1},{itemid=11041002,count=1},{itemid=11041022,count=1},{itemid=11041032,count=1},{itemid=11041042,count=1},{itemid=11041052,count=1}}},
{ id=169, ncount=13,needitem={{itemid=14040002,count=1},{itemid=14010002,count=1},{itemid=14010007,count=1},{itemid=14010012,count=1},{itemid=14040006,count=1},{itemid=12010202,count=1},{itemid=12020021,count=1},{itemid=12020022,count=1},{itemid=12020023,count=1},{itemid=12020024,count=1},{itemid=12020025,count=1},{itemid=12020026,count=1},{itemid=12010302,count=1}}},
{ id=170, ncount=13,needitem={{itemid=10280070,count=1},{itemid=10290070,count=1},{itemid=10200060,count=1},{itemid=10230060,count=1},{itemid=10250060,count=1},{itemid=10260060,count=1},{itemid=10270060,count=1},{itemid=10010060,count=1},{itemid=10020060,count=1},{itemid=10030060,count=1},{itemid=10040060,count=1},{itemid=10050060,count=1},{itemid=10060060,count=1}}},
{ id=172, ncount=4,needitem={{itemid=11020014,count=1},{itemid=11020015,count=1},{itemid=11030007,count=1},{itemid=11030404,count=1}}},
{ id=174, ncount=12,needitem={{itemid=11041012,count=1},{itemid=11041002,count=1},{itemid=11041022,count=1},{itemid=11041032,count=1},{itemid=11041042,count=1},{itemid=11041052,count=1},{itemid=11041013,count=1},{itemid=11041003,count=1},{itemid=11041023,count=1},{itemid=11041033,count=1},{itemid=11041043,count=1},{itemid=11041053,count=1}}},
{ id=176, ncount=6,needitem={{itemid=11000202,count=1},{itemid=11050002,count=1},{itemid=11020014,count=1},{itemid=11020015,count=1},{itemid=11030007,count=1},{itemid=11030404,count=1}}},
{ id=177, ncount=14,needitem={{itemid=11000203,count=1},{itemid=11050003,count=1},{itemid=11041012,count=1},{itemid=11041002,count=1},{itemid=11041022,count=1},{itemid=11041032,count=1},{itemid=11041042,count=1},{itemid=11041052,count=1},{itemid=11041013,count=1},{itemid=11041003,count=1},{itemid=11041023,count=1},{itemid=11041033,count=1},{itemid=11041043,count=1},{itemid=11041053,count=1}}},
{ id=179, ncount=13,needitem={{itemid=14040002,count=1},{itemid=14010002,count=1},{itemid=14010007,count=1},{itemid=14010012,count=1},{itemid=14040006,count=1},{itemid=12010202,count=1},{itemid=12020021,count=1},{itemid=12020022,count=1},{itemid=12020023,count=1},{itemid=12020024,count=1},{itemid=12020025,count=1},{itemid=12020026,count=1},{itemid=12010302,count=1}}},
{ id=180, ncount=13,needitem={{itemid=10280070,count=1},{itemid=10290070,count=1},{itemid=10200060,count=1},{itemid=10230060,count=1},{itemid=10250060,count=1},{itemid=10260060,count=1},{itemid=10270060,count=1},{itemid=10010060,count=1},{itemid=10020060,count=1},{itemid=10030060,count=1},{itemid=10040060,count=1},{itemid=10050060,count=1},{itemid=10060060,count=1}}},
{ id=182, ncount=4,needitem={{itemid=11020014,count=1},{itemid=11020015,count=1},{itemid=11030007,count=1},{itemid=11030404,count=1}}},
{ id=184, ncount=12,needitem={{itemid=11041012,count=1},{itemid=11041002,count=1},{itemid=11041022,count=1},{itemid=11041032,count=1},{itemid=11041042,count=1},{itemid=11041052,count=1},{itemid=11041013,count=1},{itemid=11041003,count=1},{itemid=11041023,count=1},{itemid=11041033,count=1},{itemid=11041043,count=1},{itemid=11041053,count=1}}},
{ id=186, ncount=6,needitem={{itemid=11000202,count=1},{itemid=11050002,count=1},{itemid=11020014,count=1},{itemid=11020015,count=1},{itemid=11030007,count=1},{itemid=11030404,count=1}}},
{ id=187, ncount=14,needitem={{itemid=11000203,count=1},{itemid=11050003,count=1},{itemid=11041012,count=1},{itemid=11041002,count=1},{itemid=11041022,count=1},{itemid=11041032,count=1},{itemid=11041042,count=1},{itemid=11041052,count=1},{itemid=11041013,count=1},{itemid=11041003,count=1},{itemid=11041023,count=1},{itemid=11041033,count=1},{itemid=11041043,count=1},{itemid=11041053,count=1}}},
{ id=189, ncount=13,needitem={{itemid=14040002,count=1},{itemid=14010002,count=1},{itemid=14010007,count=1},{itemid=14010012,count=1},{itemid=14040006,count=1},{itemid=12010202,count=1},{itemid=12020021,count=1},{itemid=12020022,count=1},{itemid=12020023,count=1},{itemid=12020024,count=1},{itemid=12020025,count=1},{itemid=12020026,count=1},{itemid=12010302,count=1}}},
{ id=190, ncount=13,needitem={{itemid=10280070,count=1},{itemid=10290070,count=1},{itemid=10200060,count=1},{itemid=10230060,count=1},{itemid=10250060,count=1},{itemid=10260060,count=1},{itemid=10270060,count=1},{itemid=10010060,count=1},{itemid=10020060,count=1},{itemid=10030060,count=1},{itemid=10040060,count=1},{itemid=10050060,count=1},{itemid=10060060,count=1}}},
{ id=192, ncount=4,needitem={{itemid=11020014,count=1},{itemid=11020015,count=1},{itemid=11030007,count=1},{itemid=11030404,count=1}}},
{ id=194, ncount=6,needitem={{itemid=11041013,count=1},{itemid=11041003,count=1},{itemid=11041023,count=1},{itemid=11041033,count=1},{itemid=11041043,count=1},{itemid=11041053,count=1}}},
{ id=196, ncount=6,needitem={{itemid=11000202,count=1},{itemid=11050002,count=1},{itemid=11020014,count=1},{itemid=11020015,count=1},{itemid=11030007,count=1},{itemid=11030404,count=1}}},
{ id=197, ncount=8,needitem={{itemid=11000203,count=1},{itemid=11050003,count=1},{itemid=11041013,count=1},{itemid=11041003,count=1},{itemid=11041023,count=1},{itemid=11041033,count=1},{itemid=11041043,count=1},{itemid=11041053,count=1}}},
{ id=199, ncount=13,needitem={{itemid=14040002,count=1},{itemid=14010002,count=1},{itemid=14010007,count=1},{itemid=14010012,count=1},{itemid=14040006,count=1},{itemid=12010202,count=1},{itemid=12020021,count=1},{itemid=12020022,count=1},{itemid=12020023,count=1},{itemid=12020024,count=1},{itemid=12020025,count=1},{itemid=12020026,count=1},{itemid=12010302,count=1}}},
{ id=200, ncount=13,needitem={{itemid=10280070,count=1},{itemid=10290070,count=1},{itemid=10200060,count=1},{itemid=10230060,count=1},{itemid=10250060,count=1},{itemid=10260060,count=1},{itemid=10270060,count=1},{itemid=10010060,count=1},{itemid=10020060,count=1},{itemid=10030060,count=1},{itemid=10040060,count=1},{itemid=10050060,count=1},{itemid=10060060,count=1}}},
							}
----------------------------- 收集 end---------------------------

----------------------------- 杀怪 start ------------------------
x300783_g_MissionInfo3				= 	"\t无论是过去还是现在，我大元的敌人从未终止过对我们的骚扰，现在有一个艰巨的使命交给你，不管敌人藏身于何处都要彻底的消灭他们。"
x300783_g_ContinueInfo3				= 	"\t你还没有消灭那些敌人，怎么就回来了？"
x300783_g_MissionCompleted3			= 	"\t你的勇于无畏捍卫了我们蒙古人的尊严，你会成为后世景仰的勇士。"
x300783_g_MissionHelp3				=	"\t#G帮会功德#W小于50点，每轮跑环任务可以完成#G100环#W子任务。随着自身帮会功德的增加，子任务环数也会增加，最高为每轮可完成#G200环#W子任务。"          --任务提示信息

x300783_g_MissionTable3 =	{ --needvalue:帮会功德
								{ id=5, ncount=3,needkill={{typeid=691,count=3, name="  前往@npc_81014消灭3个@npc_21003", name1="@npc_21003"},{typeid=692,count=3, name="  前往@npc_81014消灭3个@npc_21004", name1="@npc_21004"},{typeid=686,count=3, name="  前往@npc_81014消灭3个@npc_21010", name1="@npc_21010"}}},
								{ id=8, ncount=3,needkill={{typeid=692,count=3, name="  前往@npc_81014消灭3个@npc_21004", name1="@npc_21004"},{typeid=686,count=3, name="  前往@npc_81014消灭3个@npc_21010", name1="@npc_21010"},{typeid=682,count=3, name="  前往@npc_81014消灭3个@npc_21001", name1="@npc_21001"}}},
								{ id=15, ncount=3,needkill={{typeid=686,count=3, name="  前往@npc_81014消灭3个@npc_21010", name1="@npc_21010"},{typeid=682,count=3, name="  前往@npc_81014消灭3个@npc_21001", name1="@npc_21001"},{typeid=695,count=3, name="  前往@npc_81014消灭3个@npc_21009", name1="@npc_21009"}}},
								{ id=18, ncount=2,needkill={{typeid=1440,count=3, name="  前往@npc_81019消灭3个@npc_2200", name1="@npc_2200"},{typeid=1441,count=3, name="  前往@npc_81019消灭3个@npc_2201", name1="@npc_2201"}}},
								{ id=25, ncount=2,needkill={{typeid=1440,count=3, name="  前往@npc_81019消灭3个@npc_2200", name1="@npc_2200"},{typeid=1441,count=3, name="  前往@npc_81019消灭3个@npc_2201", name1="@npc_2201"}}},
								{ id=28, ncount=3,needkill={{typeid=1411,count=3, name="  前往@npc_81015消灭3个@npc_23005", name1="@npc_23005"},{typeid=1404,count=3, name="  前往@npc_81015消灭3个@npc_23009", name1="@npc_23009"},{typeid=1412,count=3, name="  前往@npc_81015消灭3个@npc_23012", name1="@npc_23012"}}},
								{ id=35, ncount=3,needkill={{typeid=1404,count=3, name="  前往@npc_81015消灭3个@npc_23009", name1="@npc_23009"},{typeid=1409,count=3, name="  前往@npc_81015消灭3个@npc_23001", name1="@npc_23001"},{typeid=1402,count=3, name="  前往@npc_81015消灭3个@npc_23007", name1="@npc_23007"}}},
								{ id=38, ncount=3,needkill={{typeid=1409,count=3, name="  前往@npc_81015消灭3个@npc_23001", name1="@npc_23001"},{typeid=1412,count=3, name="  前往@npc_81015消灭3个@npc_23012", name1="@npc_23012"},{typeid=1402,count=3, name="  前往@npc_81015消灭3个@npc_23007", name1="@npc_23007"}}},
								{ id=45, ncount=2,needkill={{typeid=808,count=3, name="  前往@npc_81016消灭3个@npc_22010", name1="@npc_22010"},{typeid=801,count=3, name="  前往@npc_81016消灭3个@npc_22003", name1="@npc_22003"}}},
								{ id=48, ncount=2,needkill={{typeid=808,count=3, name="  前往@npc_81016消灭3个@npc_22010", name1="@npc_22010"},{typeid=800,count=3, name="  前往@npc_81016消灭3个@npc_22000", name1="@npc_22000"}}},
								{ id=55, ncount=2,needkill={{typeid=800,count=3, name="  前往@npc_81016消灭3个@npc_22000", name1="@npc_22000"},{typeid=807,count=3, name="  前往@npc_81016消灭3个@npc_22008", name1="@npc_22008"}}},
								{ id=58, ncount=1,needkill={{typeid=1450,count=3, name="  前往@npc_81017消灭3个@npc_2202", name1="@npc_2202"}}},
								{ id=65, ncount=1,needkill={{typeid=1451,count=3, name="  前往@npc_81017消灭3个@npc_2203", name1="@npc_2203"}}},
								{ id=68, ncount=1,needkill={{typeid=1208,count=2, name="  前往@npc_81018消灭2个@npc_85050", name1="@npc_85050"}}},
								{ id=75, ncount=1,needkill={{typeid=1207,count=2, name="  前往@npc_81018消灭2个@npc_85051", name1="@npc_85051"}}},
								{ id=78, ncount=1,needkill={{typeid=1682,count=3, name="  前往@npc_81020消灭3个@npc_112102", name1="@npc_112102"}}},
								{ id=85, ncount=1,needkill={{typeid=1686,count=3, name="  前往@npc_81020消灭3个@npc_112101", name1="@npc_112101"}}},
								{ id=88, ncount=1,needkill={{typeid=1702,count=3, name="  前往@npc_81021消灭3个@npc_113101", name1="@npc_113101"}}},
								{ id=95, ncount=1,needkill={{typeid=1706,count=3, name="  前往@npc_81021消灭2个@npc_113106", name1="@npc_113106"}}},
								{ id=98, ncount=1,needkill={{typeid=1713,count=2, name="  前往@npc_81021消灭2个@npc_113113", name1="@npc_113113"}}},
								{ id=105, ncount=2,needkill={{typeid=1440,count=3, name="  前往@npc_81019消灭3个@npc_2200", name1="@npc_2200"},{typeid=1441,count=3, name="  前往@npc_81019消灭3个@npc_2201", name1="@npc_2201"}}},
								{ id=108, ncount=2,needkill={{typeid=1440,count=3, name="  前往@npc_81019消灭3个@npc_2200", name1="@npc_2200"},{typeid=1441,count=3, name="  前往@npc_81019消灭3个@npc_2201", name1="@npc_2201"}}},
								{ id=115, ncount=3,needkill={{typeid=1411,count=3, name="  前往@npc_81015消灭3个@npc_23005", name1="@npc_23005"},{typeid=1404,count=3, name="  前往@npc_81015消灭3个@npc_23009", name1="@npc_23009"},{typeid=1412,count=3, name="  前往@npc_81015消灭3个@npc_23012", name1="@npc_23012"}}},
								{ id=118, ncount=3,needkill={{typeid=1404,count=3, name="  前往@npc_81015消灭3个@npc_23009", name1="@npc_23009"},{typeid=1409,count=3, name="  前往@npc_81015消灭3个@npc_23001", name1="@npc_23001"},{typeid=1402,count=3, name="  前往@npc_81015消灭3个@npc_23007", name1="@npc_23007"}}},
								{ id=125, ncount=3,needkill={{typeid=1409,count=3, name="  前往@npc_81015消灭3个@npc_23001", name1="@npc_23001"},{typeid=1412,count=3, name="  前往@npc_81015消灭3个@npc_23012", name1="@npc_23012"},{typeid=1402,count=3, name="  前往@npc_81015消灭3个@npc_23007", name1="@npc_23007"}}},
								{ id=128, ncount=2,needkill={{typeid=808,count=3, name="  前往@npc_81016消灭3个@npc_22010", name1="@npc_22010"},{typeid=801,count=3, name="  前往@npc_81016消灭3个@npc_22003", name1="@npc_22003"}}},
								{ id=135, ncount=2,needkill={{typeid=808,count=3, name="  前往@npc_81016消灭3个@npc_22010", name1="@npc_22010"},{typeid=800,count=3, name="  前往@npc_81016消灭3个@npc_22000", name1="@npc_22000"}}},
								{ id=138, ncount=2,needkill={{typeid=800,count=3, name="  前往@npc_81016消灭3个@npc_22000", name1="@npc_22000"},{typeid=807,count=3, name="  前往@npc_81016消灭3个@npc_22008", name1="@npc_22008"}}},
								{ id=145, ncount=1,needkill={{typeid=1450,count=3, name="  前往@npc_81017消灭3个@npc_2202", name1="@npc_2202"}}},
								{ id=148, ncount=1,needkill={{typeid=1451,count=3, name="  前往@npc_81017消灭3个@npc_2203", name1="@npc_2203"}}},
								{ id=155, ncount=3,needkill={{typeid=691,count=3, name="  前往@npc_81014消灭3个@npc_21003", name1="@npc_21003"},{typeid=692,count=3, name="  前往@npc_81014消灭3个@npc_21004", name1="@npc_21004"},{typeid=686,count=3, name="  前往@npc_81014消灭3个@npc_21010", name1="@npc_21010"}}},
								{ id=158, ncount=3,needkill={{typeid=692,count=3, name="  前往@npc_81014消灭3个@npc_21004", name1="@npc_21004"},{typeid=686,count=3, name="  前往@npc_81014消灭3个@npc_21010", name1="@npc_21010"},{typeid=682,count=3, name="  前往@npc_81014消灭3个@npc_21001", name1="@npc_21001"}}},
								{ id=165, ncount=3,needkill={{typeid=686,count=3, name="  前往@npc_81014消灭3个@npc_21010", name1="@npc_21010"},{typeid=682,count=3, name="  前往@npc_81014消灭3个@npc_21001", name1="@npc_21001"},{typeid=695,count=3, name="  前往@npc_81014消灭3个@npc_21009", name1="@npc_21009"}}},
								{ id=168, ncount=2,needkill={{typeid=1440,count=3, name="  前往@npc_81019消灭3个@npc_2200", name1="@npc_2200"},{typeid=1441,count=3, name="  前往@npc_81019消灭3个@npc_2201", name1="@npc_2201"}}},
								{ id=175, ncount=2,needkill={{typeid=1440,count=3, name="  前往@npc_81019消灭3个@npc_2200", name1="@npc_2200"},{typeid=1441,count=3, name="  前往@npc_81019消灭3个@npc_2201", name1="@npc_2201"}}},														
								{ id=178, ncount=1,needkill={{typeid=1682,count=3, name="  前往@npc_81020消灭3个@npc_112102", name1="@npc_112102"}}},
								{ id=185, ncount=1,needkill={{typeid=1686,count=3, name="  前往@npc_81020消灭3个@npc_112101", name1="@npc_112101"}}},
								{ id=188, ncount=1,needkill={{typeid=1702,count=3, name="  前往@npc_81021消灭3个@npc_113101", name1="@npc_113101"}}},
								{ id=195, ncount=1,needkill={{typeid=1706,count=3, name="  前往@npc_81021消灭2个@npc_113106", name1="@npc_113106"}}},
								{ id=198, ncount=1,needkill={{typeid=1713,count=2, name="  前往@npc_81021消灭2个@npc_113113", name1="@npc_113113"}}},
							}
----------------------------- 杀怪 end---------------------------


function x300783_GetMissionId( sceneId, selfId )
	return x300783_g_MissionId
end

function x300783_GetMissionStep(sceneId, selfId)

	local nLastFlag = GetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_CURRENT_ID[1], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[2], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[3])
	if nLastFlag>=x300783_GetMaxStep(sceneId,selfId) then
		nLastFlag = 0
	end
	return nLastFlag+1
	
end

function x300783_SaveMissionStep(sceneId, selfId)

	local nLastFlag = GetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_CURRENT_ID[1], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[2], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[3])



	if nLastFlag<(x300783_GetMaxStep(sceneId,selfId)-1) then
		
		SetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_CURRENT_ID[1], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[2], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[3],nLastFlag+1)
		local myMissionId = x300783_GetMissionId( sceneId, selfId )	
		x300783_DispatchMissionInfo( sceneId, selfId, x300783_g_ReplyNpcObjId, myMissionId, 0 )
	else
		SetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_CURRENT_ID[1], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[2], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[3],0)
		x300783_SetDayCount(sceneId, selfId)
		
		
		
	end
	
  
end

function x300783_ResetMissionStep(sceneId, selfId)
	SetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_CURRENT_ID[1], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[2], MD_GUILD_CIRCLE_MISSION_CURRENT_ID[3],0)
end

function x300783_GetMissionTypeById(nStep)
	local nIndex =0
	for i,item in x300783_g_MissionTable1 do
		nIndex = nIndex+1;
		if item.id == nStep then
			return x300783_G_TYPE_SONGXIN, nIndex
		end
	end
	
	local nIndex =0
	for i,item in x300783_g_MissionTable2 do
		nIndex = nIndex+1;
		if item.id == nStep then
			return x300783_G_TYPE_SHOUJI, nIndex
		end
	end

	local nIndex =0
	for i,item in x300783_g_MissionTable3 do
		nIndex = nIndex+1;
		if item.id == nStep then
			return x300783_G_TYPE_KILL, nIndex
		end
	end
end

function x300783_GetMaxStep(sceneId,selfId)
	local nGuildMerit = GetGuildMerit(sceneId,selfId) --帮会功德
	
	local iIndex = 0

	for i, item in x300783_g_NeedGuildValue do
		
		if nGuildMerit>=x300783_g_NeedGuildValue[i] then
			break
		end
		iIndex = iIndex +1
	end
	

	return 200-20*iIndex
	
	
	
end

function x300783_GetData(sceneId, selfId)
	local nStep = x300783_GetMissionStep(sceneId, selfId)
	local nType,nIndex = x300783_GetMissionTypeById(nStep)
	local n1 = mod(nStep,10)

	

	local n2 = (nStep - mod(nStep,10))/10+1
	if n1==0 then
		n1 = 10
		
		n2 = (nStep - mod(nStep,10))/10
	end
	
	local nBaseBonusRate = x300783_g_BaseBonusRate[n1]  --基础奖励基数
	local nExtraBonusRate = x300783_g_ExtraBonusRate[n2] --还数奖励基数
	local nLevel = GetLevel(sceneId, selfId)
	local nExpBonus = nLevel*nBaseBonusRate*nExtraBonusRate

	nExpBonus = tonumber(format("%d",nExpBonus))
	
	return nStep,nType,nIndex,nExpBonus
end

function x300783_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
	if GetGameOpenById(x300783_g_GameId)<=0 then
		return
	end

	if IsPlayerStateNormal(sceneId,selfId ) <= 0 then
		return
	end

	local level = GetLevel( sceneId,selfId )
    if level < x300783_g_LevelLess then
       return
    end

  if GetGuildID( sceneId, selfId ) == -1 then
		return 0
	end  

	local myMissionId = x300783_GetMissionId( sceneId, selfId )
	
	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		AddQuestNumText(sceneId, myMissionId, x300783_g_MissionName,8,1);
		
	else
		local state = GetQuestStateNM(sceneId, selfId, targetId, myMissionId);

		AddQuestNumText(sceneId, myMissionId, x300783_g_MissionName,state,state);

	end


	DispatchQuestEventList(sceneId, selfId, targetId)


	
end





---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300783_ProcEventEntry( sceneId, selfId, targetId, MissionId, nExt )
	
	
	
	if GetGameOpenById(x300783_g_GameId)<=0 then
		x300783_ShowTips(sceneId, selfId, "此活动未开启")
		return
	end

	local myMissionId = x300783_GetMissionId( sceneId, selfId )	
	
	

	
	
	
		
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		if nExt~=30 then
		
		x300783_DispatchMissionInfo( sceneId, selfId, targetId, myMissionId, 0 )
		else
			x300783_ShowTips(sceneId, selfId, "你没有任务"..x300783_g_MissionName)
			return
		end
		
		
	else
		if nExt==7 then -- 任务完成
			x300783_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
			
		elseif nExt==30 then
			x300783_DispatchSongxinInfo( sceneId, selfId, targetId,myMissionId )
		else
			
			x300783_DispatchContinueInfo( sceneId, selfId, targetId,myMissionId )
		end
	end
	
end



function x300783_DispatchSongxinInfo( sceneId, selfId, NPCId,MissionId )
	local nStep,nType,nIndex,nExpBonus = x300783_GetData(sceneId, selfId)

	if nType~=x300783_G_TYPE_SONGXIN then
		return
	end

	

	local myMissionId = x300783_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	
	SetQuestByIndex( sceneId, selfId, misIndex, 0, 1 )
	SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
	

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"#Y"..x300783_g_MissionName)
	
	AddQuestText( sceneId,"\t你真是太客气了，些许帮助你们不必记挂在心。")
	
	AddQuestText(sceneId," ")

	EndQuestEvent()

	DispatchQuestEventList( sceneId, selfId, NPCId)

	x300783_QuestLogRefresh( sceneId, selfId, myMissionId)
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x300783_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId, nExt )
	

	local nStep,nType,nIndex,nExpBonus = x300783_GetData(sceneId, selfId)

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300783_g_MissionName)
		
			
		AddQuestText(sceneId,x300783_g_MissionInfo)
		AddQuestText(sceneId," ")
			
		--AddQuestText( sceneId,"#Y任务目标:")
					
		AddQuestText( sceneId,x300783_g_MissionTarget)
		--AddQuestText(sceneId," ")

		
		if nExpBonus > 0 then
			AddQuestExpBonus( sceneId, nExpBonus)
		end

		AddQuestText( sceneId,"#G小提示：#W\n\t#G帮会功德#W小于50点，每轮跑环任务可以完成#G100环#W子任务。随着自身帮会功德的增加，子任务环数也会增加，最高为每轮可完成#G200环#W子任务。")
	

	EndQuestEvent()
	
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300783_g_ScriptId, MissionId,0);
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300783_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	local myMissionId = x300783_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300783_g_MissionName)
		AddQuestText(sceneId," ")
		AddQuestText(sceneId,"\t您还没有完成本次任务，请赶快去完成吧！")
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300783_g_ScriptId, MissionId,0);
	


end







---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300783_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	local myMissionId = x300783_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	local nStep,nType,nIndex,nExpBonus = x300783_GetData(sceneId, selfId)
	

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300783_g_MissionName)
		AddQuestText(sceneId,"\t#Y@myname#W，感谢你所做出的贡献，相信在大家的共同努力下，我们的帮会一定会更加强盛。")
	

	
	if nExpBonus > 0 then
		AddQuestExpBonus( sceneId, nExpBonus)
	end

	
		
	EndQuestEvent()
	
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300783_g_ScriptId, MissionId);

end


function x300783_ProcAcceptCheck(sceneId, selfId, targetId, MissionId )
	
	if GetGameOpenById(x300783_g_GameId)<=0 then
		
		return 0;
	end
	return 1;

end

function x300783_CheckRequest(sceneId, selfId)
	if GetGameOpenById(x300783_g_GameId)<=0 then
		x300783_ShowTips(sceneId, selfId, "此活动未开启")
		return 0
	end


	local myMissionId = x300783_GetMissionId( sceneId, selfId )

	if GetLevel(sceneId, selfId) <x300783_g_LevelLess then
		x300783_ShowTips(sceneId, selfId, "您的等级不足，无法接取此任务")
		return 0
	end

	if GetGuildID( sceneId, selfId ) == -1 then
		x300783_ShowTips(sceneId, selfId, "您还没有加入帮会，无法接取此任务")
		return 0
	end

	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) > 0 then
		x300783_ShowTips(sceneId, selfId, "您已经接取了该任务，请先完成当前任务")
		return 0;
	end


	if x300783_g_DayCountLimited >0 then
		local nDayCount, nLastDay = x300783_GetDayCount(sceneId, selfId)

		
		if nDayCount>= x300783_g_DayCountLimited then
			local today = GetDayOfYear() 

			local nNeedDay = x300783_g_nDaySpace-(today-nLastDay)

			x300783_ShowTips(sceneId, selfId, format("很抱歉，【帮会】帮会跑环任务，请%d天后来接任务！",nNeedDay))
			return 0;
		end
	end

	

	return 1;

end



function x300783_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
	
	if x300783_CheckRequest(sceneId, selfId)<=0 then
		
		return 0;
	end

	local myMissionId = x300783_GetMissionId( sceneId, selfId )
	--------------------------- add for Mission full check --------------
	local bFullMission = IsQuestFullNM(sceneId,selfId)
	
	if bFullMission>0 then
		x300783_ShowTips(sceneId, selfId, "任务已满，无法接受任务")
		return 0
	end
	---------------------------- add end -------------------------------
	local nStep,nType,nIndex,nExpBonus = x300783_GetData(sceneId, selfId)

	local ret = AddQuest( sceneId, selfId, myMissionId, x300783_g_ScriptId, 1, 0, 1,1)-- 给玩家添加任务		
		
	if ret > 0 then
		local str = "您接受了任务："..x300783_g_MissionName;
		x300783_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)


		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

		local nRandom =0;
		if nType == x300783_G_TYPE_SONGXIN then
			nRandom = random(1,x300783_g_MissionTable1[nIndex].ncount)
		elseif nType == x300783_G_TYPE_SHOUJI then
			nRandom = random(1,x300783_g_MissionTable2[nIndex].ncount)
		elseif nType == x300783_G_TYPE_KILL then
			nRandom = random(1,x300783_g_MissionTable3[nIndex].ncount)
		end
	
		SetQuestByIndex( sceneId, selfId, misIndex, 6, nRandom )
		

		x300783_ShowSubMission( sceneId, selfId, targetId,MissionId,nRandom )

		if nType == x300783_G_TYPE_SHOUJI then
			x300783_CheckShoujiHaveAll(sceneId, selfId, nRandom)
		end

		GamePlayScriptLog(sceneId, selfId, 1271)
		return 1
	else
		
		x300783_ShowTips(sceneId, selfId, "接受任务错误")
	
	end


end


function x300783_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x300783_ProcQuestAbandon( sceneId, selfId, MissionId )

	local myMissionId = x300783_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )


	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )


	

	local ret = DelQuestNM( sceneId, selfId, myMissionId )

	if ret>0 then

		local str = "您放弃了任务:"..x300783_g_MissionName;
	    x300783_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)

	
		--x300783_SetDayCount(sceneId, selfId)

		
		
	else
		x300783_ShowTips(sceneId, selfId, "放弃任务失败")
	end

	
end



function x300783_ProcQuestSubmit( sceneId, selfId, targetId, selectRadioId, MissionId )
	
	
	
	if GetGameOpenById(x300783_g_GameId)<=0 then
		x300783_ShowTips(sceneId, selfId, "此活动未开启")
		return 0;
	end

	

	local myMissionId = x300783_GetMissionId( sceneId, selfId )

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )


	local nStep,nType,nIndex,nExpBonus = x300783_GetData(sceneId, selfId)
	
	if x300783_CheckSubmit(sceneId, selfId )>0 then
		if nType == x300783_G_TYPE_SHOUJI then
			if x300783_SubmitShouji(sceneId, selfId,targetId)<=0 then
				return 0
			end
		end
		
		local ret = DelQuestNM( sceneId, selfId, myMissionId )

		if ret>0 then

			local str = "您完成了任务:"..x300783_g_MissionName;
			x300783_ShowTips(sceneId, selfId, str)
			Msg2Player(sceneId,selfId,str,8,2)

			
			
			x300783_GiveReward(sceneId,selfId)

			x300783_SaveMissionStep(sceneId, selfId)

			 CallScriptFunction( 300783, "ProcEventEntry", sceneId, selfId, targetId, x300783_g_MissionId )	
			GamePlayScriptLog(sceneId, selfId, 1272)
			
		else
			x300783_ShowTips(sceneId, selfId, "交任务失败")
		end
		
	end
end


function x300783_SubmitShouji(sceneId, selfId,targetId)
	
	
	local myMissionId = x300783_GetMissionId( sceneId, selfId )

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	local nRandom = GetQuestParam( sceneId, selfId, misIndex, 6 )



	local nStep,nType,nIndex,nExpBonus = x300783_GetData(sceneId, selfId)
	
	if nType ~= x300783_G_TYPE_SHOUJI then
		return 1
	end
	
	local itemid_t = x300783_g_MissionTable2[nIndex].needitem[nRandom].itemid
	local count_t = x300783_g_MissionTable2[nIndex].needitem[nRandom].count

	
	if GetItemClass(itemid_t)~=10 then

		local nRet = DelItem(sceneId, selfId,itemid_t,count_t)
		
		if nRet<=0 then
			x300783_ShowTips(sceneId, selfId, "删除物品失败")
			
			return 0
		else
		
		end
	
	else
		--如果是装备
		
		
		local nItemCount = GetItemCount( sceneId, selfId, itemid_t )
		
		BeginUICommand( sceneId)
			UICommand_AddInt( sceneId, x300783_g_ScriptId)
			UICommand_AddInt( sceneId, myMissionId)
			UICommand_AddInt( sceneId, targetId)
			UICommand_AddInt( sceneId, itemid_t)
			
			
			DispatchUICommand( sceneId, selfId, 106)  --104
		EndUICommand( sceneId)

		BeginQuestEvent( sceneId)
		AddQuestText( sceneId, "#Y"..x300783_g_MissionName)
			AddQuestText( sceneId, "\t你需要选择一件上交的物品" )
		EndQuestEvent( sceneId)
		DispatchQuestEventList( sceneId, selfId, targetId)

		--AskDeleteWhichEquip(sceneId, selfId,itemid_t,count_t)  --发送给客户端删除哪个装备

		return 0
	end

	return 1
end

function x300783_OnComitSubmitItem(sceneId, selfId,bagIndex)

	local myMissionId = x300783_GetMissionId( sceneId, selfId )

	local nStep,nType,nIndex,nExpBonus = x300783_GetData(sceneId, selfId)
	
	if x300783_CheckSubmit(sceneId, selfId )>0 then
		
		if EraseItem(sceneId, selfId,bagIndex)>0 then
			local ret = DelQuestNM( sceneId, selfId, myMissionId )

			if ret>0 then

				local str = "您完成了任务:"..x300783_g_MissionName;
				x300783_ShowTips(sceneId, selfId, str)
				Msg2Player(sceneId,selfId,str,8,2)

				
				
				x300783_GiveReward(sceneId,selfId)

				x300783_SaveMissionStep(sceneId, selfId)


				GamePlayScriptLog(sceneId, selfId, 1272)
				
			else
				x300783_ShowTips(sceneId, selfId, "交任务失败")
			end
		else
			x300783_ShowTips(sceneId, selfId, "删除物品失败")
		end
		
	end
end



function x300783_GiveReward(sceneId,selfId)
	
	if GetGameOpenById(x300783_g_GameId)<=0 then
		x300783_ShowTips(sceneId, selfId, "此活动未开启")
		return 0;
	end

	local nStep,nType,nIndex,nExpBonus = x300783_GetData(sceneId, selfId)

	if nType ==x300783_G_TYPE_SONGXIN then
	end
	
	AddExp(sceneId,selfId,nExpBonus)
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, "#o您获得了#R经验"..nExpBonus.."点#o的奖励");
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId,selfId,"#o您完成了【帮会】帮会跑环任务，获得了#R经验"..nExpBonus.."点#o的奖励",4,2)
	
	
end



function x300783_CheckSubmit(sceneId, selfId )
	
	if GetGameOpenById(x300783_g_GameId)<=0 then
		x300783_ShowTips(sceneId, selfId, "此活动未开启")
		return 0;
	end

	local myMissionId = x300783_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )
	local nRandom = GetQuestParam( sceneId, selfId, misIndex, 6 )


	

	if (bCompleted)<=0 then
		return 0
	end

	local nStep,nType,nIndex,nExpBonus = x300783_GetData(sceneId, selfId)

	if nType==x300783_G_TYPE_SONGXIN then
	
	elseif nType == x300783_G_TYPE_SHOUJI then
		local itemid_t = x300783_g_MissionTable2[nIndex].needitem[nRandom].itemid
		local count_t = x300783_g_MissionTable2[nIndex].needitem[nRandom].count
		local nItemCount = GetItemCount( sceneId, selfId, itemid_t )
		if nItemCount<count_t then
			return 0
		end
		
	end

	return 1;
end






---------------------------------------------------------------------------------------------------
--向客户端发送题目
---------------------------------------------------------------------------------------------------
function x300783_ShowSubMission( sceneId, selfId, NPCId,MissionId, nRandom )


	
	local myMissionId = x300783_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	local nStep,nType,nIndex,nExpBonus = x300783_GetData(sceneId, selfId)

	local nStep,nType,nIndex,nExpBonus = x300783_GetData(sceneId, selfId)

	

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"#Y"..x300783_g_MissionName)
	if nType == x300783_G_TYPE_SONGXIN then
		local strName = x300783_g_MissionTable1[nIndex].replynpclist[nRandom].name
		AddQuestText(sceneId,x300783_g_MissionInfo1)
		AddQuestText( sceneId,"\n#Y任务目标:")
		AddQuestText(sceneId,"#W"..strName)
	elseif nType == x300783_G_TYPE_SHOUJI then
		local str1 = "收集"..x300783_g_MissionTable2[nIndex].needitem[nRandom].count.."个#G@itemid_"..x300783_g_MissionTable2[nIndex].needitem[nRandom].itemid.."\n"
		
		AddQuestText(sceneId,x300783_g_MissionInfo2)
		AddQuestText( sceneId,"\n#Y任务目标:")
		AddQuestText(sceneId,"#W"..str1)
	elseif nType == x300783_G_TYPE_KILL then
		local str1 =x300783_g_MissionTable3[nIndex].needkill[nRandom].name.."\n"
		
		AddQuestText(sceneId,x300783_g_MissionInfo3)
		AddQuestText( sceneId,"\n#Y任务目标:")
		AddQuestText(sceneId,"#W"..str1)
	end
	--AddQuestText( sceneId,"#Y任务回复:")
	--AddQuestText( sceneId,"找到@npc_"..x300783_g_ReplyNpcId)
	--AddQuestText(sceneId," ")

	
	if nExpBonus > 0 then
		AddQuestExpBonus( sceneId, nExpBonus)
	end

	

	EndQuestEvent()

	DispatchQuestEventList( sceneId, selfId, NPCId)
	--DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300783_g_ScriptId, myMissionId,0);
	


end







---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300783_QuestLogRefresh( sceneId, selfId, MissionId)
	
	local myMissionId = x300783_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end
		
	BeginQuestEvent(sceneId)	
			
		
	AddQuestLogCustomText( sceneId,
							"",						-- 标题
							x300783_GetMissionName(sceneId,selfId),        -- 任务名字
							x300783_GetMissionTask(sceneId,selfId),		--任务目标
							"@npc_"..x300783_GetReplyNpcId(sceneId,selfId),			--任务NPC
							x300783_GetMissionMethod(sceneId,selfId),               --任务攻略
							x300783_GetMissionText(sceneId,selfId),	--任务描述
							x300783_GetMissionHelp(sceneId,selfId)					--任务小提示
							)

	--1、经验
	local nStep,nType,nIndex,nExpBonus = x300783_GetData(sceneId, selfId)

	if nExpBonus > 0 then
		AddQuestExpBonus( sceneId, nExpBonus)
	end

	
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	

end

function x300783_GetMissionName(sceneId,selfId)
	
	local nStep,nType,nIndex,nExpBonus = x300783_GetData(sceneId, selfId)

	return x300783_g_MissionName..format("(%d/%d)",nStep,x300783_GetMaxStep(sceneId,selfId));
end

function x300783_GetMissionTask(sceneId,selfId)
	local myMissionId = x300783_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	
	local value0 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	local value7 = GetQuestParam( sceneId, selfId, misIndex, 7 )
	local nRandom = GetQuestParam( sceneId, selfId, misIndex, 6 )
	local nStep,nType,nIndex,nExpBonus = x300783_GetData(sceneId, selfId)

	local str1=""

	if nType == x300783_G_TYPE_SONGXIN then
		local strName = x300783_g_MissionTable1[nIndex].replynpclist[nRandom].name
		str1 = format(""..strName.."(%d/1)",value0)

		if value0>=1 then
			str1 = "#G"..str1
		else
			str1 = "#W"..str1
		end

		return str1
		
	elseif nType == x300783_G_TYPE_SHOUJI then
		

		local id = x300783_g_MissionTable2[nIndex].needitem[nRandom].itemid
		local count_t = x300783_g_MissionTable2[nIndex].needitem[nRandom].count
		
		local strTail = format("(%d/%d)",value0,count_t)
		if value0>=count_t then
			strTail = "#G"..strTail
		else
			strTail = "#W"..strTail
		end
		str1 = str1.."  #W收集"..count_t.."个#G@itemid_"..id..strTail
		

		return str1
	elseif  nType == x300783_G_TYPE_KILL then
		local name_t = x300783_g_MissionTable3[nIndex].needkill[nRandom].name
		local count_t = x300783_g_MissionTable3[nIndex].needkill[nRandom].count
		
		local strTail = format("(%d/%d)\n",value0,count_t)
		if value0>=count_t then
			strTail = "#G"..strTail
		else
			strTail = "#W"..strTail
		end
		str1 = str1.."#G"..name_t..strTail

		return str1
	end
	

	

	
end

function x300783_GetReplyNpcId(sceneId,selfId)
	return x300783_g_ReplyNpcId;
end

function x300783_GetMissionMethod(sceneId,selfId)
	

	local myMissionId = x300783_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	local nStep,nType,nIndex,nExpBonus = x300783_GetData(sceneId, selfId)
	local nRandom = GetQuestParam( sceneId, selfId, misIndex, 6 )

	local str1=""

	if nType == x300783_G_TYPE_SONGXIN then
		local strName = x300783_g_MissionTable1[nIndex].replynpclist[nRandom].name
		str1 = ""..strName
	elseif nType == x300783_G_TYPE_SHOUJI then
		
		local id = x300783_g_MissionTable2[nIndex].needitem[nRandom].itemid
		local count_t = x300783_g_MissionTable2[nIndex].needitem[nRandom].count
		
		str1 = str1.."\t#W收集"..count_t.."个#G@itemid_"..id


	elseif nType == x300783_G_TYPE_KILL then
		local name_t = x300783_g_MissionTable3[nIndex].needkill[nRandom].name
		local count_t = x300783_g_MissionTable3[nIndex].needkill[nRandom].count
		
		str1 = str1.."#G"..name_t


		
	end

	return str1
end

function x300783_GetMissionText(sceneId,selfId)
	
	

	return x300783_g_MissionInfo
end

function x300783_GetMissionHelp(sceneId,selfId)
	local nStep,nType,nIndex,nExpBonus = x300783_GetData(sceneId, selfId)
	if nType == x300783_G_TYPE_SONGXIN then
		return x300783_g_MissionHelp1
	elseif nType == x300783_G_TYPE_SHOUJI then
		return x300783_g_MissionHelp2
	elseif nType == x300783_G_TYPE_KILL then
		return x300783_g_MissionHelp3
	end

	return " "
	
end



function x300783_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300783_QuestLogRefresh( sceneId, selfId, MissionId );
end

--// system function start
function x300783_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	
	local myMissionId = x300783_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	local nRandom = GetQuestParam( sceneId, selfId, misIndex, 6 )

	local nStep,nType,nIndex,nExpBonus = x300783_GetData(sceneId, selfId)

	if nType ~= x300783_G_TYPE_SONGXIN then
		return
	end

	if nType == x300783_G_TYPE_SONGXIN then
		if value1<=0 then
			local nReplyNpcId = x300783_g_MissionTable1[nIndex].replynpclist[nRandom].id

			if npcGuid==nReplyNpcId then
				AddQuestNumText(sceneId, myMissionId, x300783_g_MissionName,2,30);
			end
		end
		
	end
	
	

	
end

---------------------------------------------------------------------------------------------------
--取得当前次数
---------------------------------------------------------------------------------------------------
function x300783_GetDayCount(sceneId, selfId)



	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_DATE[1], MD_GUILD_CIRCLE_MISSION_DATE[2],MD_GUILD_CIRCLE_MISSION_DATE[3] );
	
	if today>=lastday then
		if (today-lastday)>=x300783_g_nDaySpace then  --如果在周期之外
			return 0
		end
	else
		return 0
	end

	local daycount = GetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_DAYCOUNT[1], MD_GUILD_CIRCLE_MISSION_DAYCOUNT[2],MD_GUILD_CIRCLE_MISSION_DAYCOUNT[3] );

	return daycount, lastday;

	

end

---------------------------------------------------------------------------------------------------
--设置当天次数
---------------------------------------------------------------------------------------------------
function x300783_SetDayCount(sceneId, selfId)

	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_DATE[1], MD_GUILD_CIRCLE_MISSION_DATE[2], MD_GUILD_CIRCLE_MISSION_DATE[3])
	
	if today>=lastday then
		if (today-lastday)>=x300783_g_nDaySpace then  --如果在周期之外
			SetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_DATE[1], MD_GUILD_CIRCLE_MISSION_DATE[2], MD_GUILD_CIRCLE_MISSION_DATE[3], today)
			SetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_DAYCOUNT[1], MD_GUILD_CIRCLE_MISSION_DAYCOUNT[2], MD_GUILD_CIRCLE_MISSION_DAYCOUNT[3], 1)
		else
			local daycount = GetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_DAYCOUNT[1], MD_GUILD_CIRCLE_MISSION_DAYCOUNT[2], MD_GUILD_CIRCLE_MISSION_DAYCOUNT[3])
			SetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_DAYCOUNT[1], MD_GUILD_CIRCLE_MISSION_DAYCOUNT[2], MD_GUILD_CIRCLE_MISSION_DAYCOUNT[3], daycount+1)
		end
	else --如果是跨年
		SetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_DATE[1], MD_GUILD_CIRCLE_MISSION_DATE[2], MD_GUILD_CIRCLE_MISSION_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_GUILD_CIRCLE_MISSION_DAYCOUNT[1], MD_GUILD_CIRCLE_MISSION_DAYCOUNT[2], MD_GUILD_CIRCLE_MISSION_DAYCOUNT[3], 1)
		
	end
	
	
	
	
end

function x300783_CheckSceneOnKill(sceneId, selfId)
	return 1
end


-------------------------------------------------------------------------------
-- Kill
-------------------------------------------------------------------------------

function x300783_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

	
	local myMissionId = x300783_GetMissionId( sceneId, selfId )

	local HumenNum = GetMonsterOwnerCount( sceneId, objId ) --取得这个怪物死后拥有分配权的人数
	for i = 0, HumenNum-1 do
		local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --取得拥有分配权的人的objId
		if humanObjId ~= -1 then
			if IsHaveQuestNM( sceneId, humanObjId, myMissionId ) > 0 then	--如果这个人拥有任务
				x300783_OnValidKillObject( sceneId, humanObjId, objdataId, objId, myMissionId )
			end
		end
	end
	
end

function x300783_OnValidKillObject( sceneId, selfId, objdataId, objId, MissionId )

	if x300783_CheckSceneOnKill(sceneId, selfId)<=0 then
		return 0;
	end

	local myMissionId = x300783_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	
	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )


	if bCompleted>0 then
		return
	end

	local nStep,nType,nIndex,nExpBonus = x300783_GetData(sceneId, selfId)
	local nRandom = GetQuestParam( sceneId, selfId, misIndex, 6 )

	if nType ~= x300783_G_TYPE_KILL then
		return
	end

	local bFind = 0
	local iIndex2 = 0
	--PrintStr(iIndex2)


	if x300783_g_MissionTable3[nIndex].needkill[nRandom].typeid == objdataId then
		
		bFind =1 
			
	end	

	--PrintStr(iIndex2)

	if bFind<=0 then
		return
	end
	
	local value = GetQuestParam( sceneId, selfId, misIndex, 0 )+1
	--PrintStr(x300783_g_MissionTable3[nIndex].needkill[iIndex2+1].count)
	local count_t =x300783_g_MissionTable3[nIndex].needkill[nRandom].count
	local name_t = x300783_g_MissionTable3[nIndex].needkill[nRandom].name

	local name1_t = x300783_g_MissionTable3[nIndex].needkill[nRandom].name1

	
	if count_t>=value then
		SetQuestByIndex( sceneId, selfId, misIndex, 0, value )
		x300783_ShowTips(sceneId, selfId, format("已杀死%s#Y(%d/%d)",name1_t,value,count_t))
		
		
		if count_t==value then
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
			x300783_ShowTips(sceneId, selfId, "已完成任务:"..x300783_g_MissionName)
		end
	
	end

	x300783_QuestLogRefresh( sceneId, selfId, myMissionId );
	
end


--// system end


-------------------------------------------------------------------
-- OnItemChange
-------------------------------------------------------------------
--物品改变
function x300783_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId, nChangeType, nCount)

    local myMissionId = x300783_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nStep,nType,nIndex,nExpBonus = x300783_GetData(sceneId, selfId)

	if nType ~= x300783_G_TYPE_SHOUJI then
		return
	end

	local nRandom = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	local itemid_t	= x300783_g_MissionTable2[nIndex].needitem[nRandom].itemid
	local count_t	= x300783_g_MissionTable2[nIndex].needitem[nRandom].count
	if itemid_t==itemdataId then
		local Num = GetItemCount( sceneId, selfId, itemdataId )

		if Num<count_t then
			SetQuestByIndex( sceneId, selfId, misIndex, 0, Num )
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
		else
			SetQuestByIndex( sceneId, selfId, misIndex, 0, count_t )
			
			local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )

			if bCompleted<=0 then
				SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
				
				--x300783_ShowTips(sceneId, selfId, "已完成任务:"..x300783_g_MissionName)
				
			end
		end
		
	end


	x300783_QuestLogRefresh( sceneId, selfId, myMissionId );

    
	
end

function x300783_CheckShoujiHaveAll(sceneId, selfId, nRandom)
	local nStep,nType,nIndex,nExpBonus = x300783_GetData(sceneId, selfId)

	if nType ~= x300783_G_TYPE_SHOUJI then
		return
	end

	local itemid_t = x300783_g_MissionTable2[nIndex].needitem[nRandom].itemid
	x300783_ProcQuestItemChanged( sceneId, selfId,itemid_t, -1, -1, -1)
	
end

function x300783_OnSelectSubmitItem( sceneId, selfId , bagIndex, nGuid_Serial, nGuid_Server, nGuid_World)

	if x300783_CheckSubmit(sceneId, selfId )<=0 then
		return 0
	end

	local myMissionId = x300783_GetMissionId( sceneId, selfId )
	
	if IsHaveQuest( sceneId, selfId, myMissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId)

	local nStep,nType,nIndex,nExpBonus = x300783_GetData(sceneId, selfId)
	
	if nType ~= x300783_G_TYPE_SHOUJI then
		return 0
	end


	--x300783_ShowTips(sceneId, selfId, format("bagIndex=%d,itemGuid1=%d, itemGuild2=%d, itemGuid3=%d",bagIndex , nGuid_Serial, nGuid_Server, nGuid_World))

	local nRandom = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	local itemid_t = x300783_g_MissionTable2[nIndex].needitem[nRandom].itemid
	local count_t = x300783_g_MissionTable2[nIndex].needitem[nRandom].count

	if (CheckItemMatchInBag( sceneId, selfId , bagIndex, itemid_t,nGuid_Serial, nGuid_Server, nGuid_World))>0 then  --如果物品检查正确
		x300783_OnComitSubmitItem(sceneId, selfId,bagIndex)
	end
end


-- 离开帮会
function x300783_OnLeaveGuild(sceneId, selfId, MissionId)

	DelQuestNM( sceneId, selfId, MissionId)
	local message = format("您已经不在帮会中了，删除了任务：%s", x300783_g_MissionName);
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId, selfId, message, 8, 2);	
	
end




