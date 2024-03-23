
--MisDescBegin
x300826_g_ScriptId =  300826
x300826_g_MissionKind 				= 	1                       --任务类型
x300826_g_Mis_Count = 1
x300826_g_LevelLess					= 	40 
x300826_g_LevelLess1				=	65
x300826_g_ExtTarget					=	{ {type=20,n=10,target="马车"} }
x300826_g_BonusMoney8				=	100
x300826_g_GuildExpBonus				=	1
--MisDescEnd

--x300826_g_BangExp 					=	1

--要杀的怪的个数
x300826_g_NeedKilledNum				= 1

x300826_g_PreMissionId				=	{
											{ 7602,7603,7604,7605,7606,7607 },--楼兰仙人谷除妖
											{ 7734,7735,7736,7737,7738,7739 },--天山仙人谷除妖
											{ 7728,7729,7730,7731,7732,7733 },--昆仑仙人谷除妖
											{ 7722,7723,7724,7725,7726,7727 },--敦煌仙人谷除妖
										}


										 
x300826_g_SubMissionId				=	{
											{ 
											--楼兰仙人谷除妖
												{ MissionId=7602, MissionName = "【帮会】仙人谷除妖", MissionTarget = "  打败@npc_44002", MissionInfo = "\t为了支援帮会的建设，我们通常会挑选一些帮内的精兵强将去完成王城大将军所发出的悬赏任务，今天共有六个任务，你会随机得到其中一个。\n\t#G邪灵萨满#W：他本是一位伟大的萨满，却因为深爱的人意外惨死而开始嫉恨所有处在幸福当中的人们，他用自己强大的法术四处破坏，不断残杀，被国师和大将军击败后，逃进了仙人谷，并在那里召唤出了大群的元素生物保护自己。但是他的邪恶和恐惧却并未从这片土地上消失，你的任务就是让他和他邪恶的智慧从这个世界上彻底消失。\n\t此任务每天只能接取一次，放弃任务后只能在次日再次领取。\n\t你准备好接取仙人谷除妖之#G邪灵萨满任务#W吗？#r\t当帮主发布#G除妖令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t@npc_44002非常危险，最好本帮成员组队共同前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。\n", SubmitNPCGUID = 123723,	ExpBonus = 0,NPCName = "@npc_123723",Completed ="已经干掉了那个邪灵萨满！？太好了，这是你应得的报酬，请收下。",Missionruse="你可以和帮会内其他成员一起，组队完成任务！建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",objdataId = 9723}, 
												{ MissionId=7603, MissionName = "【帮会】仙人谷除妖", MissionTarget = "  打败@npc_45001", MissionInfo = "\t为了支援帮会的建设，我们通常会挑选一些帮内的精兵强将去完成王城大将军所发出的悬赏任务，今天共有六个任务，你会随机得到其中一个。\n\t#G嗜血人屠#W：地传说他是一个很普通的屠夫，原本一直在王城中做生意，一次地震后，人们意外地发现在他家院内藏有无数骸骨，直到那时人们才发现原来他所贩卖的生猪竟然是用邪术变化的无辜百姓，事情败露后这个嗜血的屠夫逃进了边塞的仙人谷，只是每逢月圆的午夜他都会从藏身的仙人谷中走出来作恶。\n\t此任务每天只能接取一次，放弃任务后只能在次日再次领取。\n\t你准备好接取仙人谷除妖之#G嗜血人屠任务#W吗？#r\t当帮主发布#G除妖令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t@npc_45001非常危险，最好本帮成员组队前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。\n\n",	SubmitNPCGUID = 123723, ExpBonus = 0,NPCName = "@npc_123723",Completed ="你的胜利归来让我觉得很欣慰，这是你应得的报酬，请收下。",Missionruse="你可以和帮会内其他成员一起，组队完成任务！建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",objdataId =9724 },
												{ MissionId=7604, MissionName = "【帮会】仙人谷除妖", MissionTarget = "  打败@npc_45002", MissionInfo = "\t为了支援帮会的建设，我们通常会挑选一些帮内的精兵强将去完成王城大将军所发出的悬赏任务，今天共有六个任务，你会随机得到其中一个。\n\t#G走尸人魔#W：走尸人魔原本是王国内的一员勇将，还是大将军苏儿台的师傅，在一次与邪魔的战斗中被邪灵附体，日子一天天过去，邪灵最终腐蚀了他的意志和肉体，他终于成为了一具受邪灵摆布的行尸走肉。被大将军射瞎了一只眼睛后，他也逃进了仙人谷。\n\t此任务每天只能接取一次，放弃任务后只能在次日再次领取。\n\t你准备好接取仙人谷除妖之#G走尸人魔任务#W吗？#r\t当帮主发布收#G除妖令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t@npc_45002极度危险，最好本帮成员组队前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。\n\n",SubmitNPCGUID = 123723,	ExpBonus = 0,NPCName = "@npc_123723",Completed ="看到你归来的表情，我就知道此行一定相当顺利 ，这是你应得的报酬，请收下。",Missionruse="你可以和帮会内其他成员一起，组队完成任务！建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",objdataId =9725 },
												{ MissionId=7605, MissionName = "【帮会】仙人谷除妖", MissionTarget = "  打败@npc_44006", MissionInfo = "\t为了支援帮会的建设，我们通常会挑选一些帮内的精兵强将去完成王城大将军所发出的悬赏任务，今天共有六个任务，你会随机得到其中一个。\n\t#G五通鬼婆#W：居住在仙人谷中的一个面目憎恶的老太婆，相传她善于变化，经常用些糕点来诱拐百姓家的小孩子，被拐走的孩子都是有去无回，人们憎恨却又拿她没有办法，只得家家闭户。\n\t此任务每天只能接取一次，放弃任务后只能在次日再次领取。\n\t你准备好接取仙人谷除妖之#G五通鬼婆任务#W吗？#r\t当帮主发布G除妖令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t@npc_44006比较危险，最好本帮成员组队前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。\n\n", SubmitNPCGUID = 123723,	ExpBonus = 0,NPCName = "@npc_123723",Completed ="我一直在等着你的好消息，这些是你应得的报酬，请收下吧。",Missionruse="你可以和帮会内其他成员一起，组队完成任务！建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",objdataId =9726 }, 
												{ MissionId=7606, MissionName = "【帮会】仙人谷除妖", MissionTarget = "  打败@npc_45006", MissionInfo = "\t为了支援帮会的建设，我们通常会挑选一些帮内的精兵强将去完成王城大将军所发出的悬赏任务，今天共有六个任务，你会随机得到其中一个。\n\t#G铁甲尸王#W：不知什么朝代一位忠心的大将军，死后依然没有忘记生前君主的委托，固执地守卫着自己的疆土。他视所有王国的人们为敌人，现在他正在仙人谷召集着自己的军队，随时准备攻打王城，维护他那早已失去在历史上烟消云散的帝国疆土。\n\t此任务每天只能接取一次，放弃任务后只能在次日再次领取。\n\t你准备好接取仙人谷除之#G铁甲尸王任务#W吗？#r\t当帮主发布#G除妖令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t@npc_45006异常凶猛，最好本帮成员组队前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。\n\n",	SubmitNPCGUID = 123723, ExpBonus = 0,NPCName = "@npc_123723",Completed ="看来我是杞人忧天了，你的实力证明了一切，这是你应得的报酬，请收下。",Missionruse="你可以和帮会内其他成员一起，组队完成任务！建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",objdataId =9727 },
												{ MissionId=7607, MissionName = "【帮会】仙人谷除妖", MissionTarget = "  打败@npc_43004", MissionInfo = "\t为了支援帮会的建设，我们通常会挑选一些帮内的精兵强将去完成王城大将军所发出的悬赏任务，今天共有六个任务，你会随机得到其中一个。\n\t#G幽冥死神#W：一个谜一样的恶魔，通常我们都称他为“噩梦”，他出没于黑暗之中，仿佛地府的恶魔，雪亮的镰刀每一次的挥舞都会夺走一条鲜活的生命，侥幸逃生的人都称他为终生的噩梦！\n\t你准备好接取仙人谷除妖之#G幽冥死神任务#W吗？#r\t当帮主发布#G除妖令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t@npc_43004非常危险，最好本帮成员组队前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。\n\n",SubmitNPCGUID = 138533,	ExpBonus = 0,NPCName = "@npc_123723",Completed ="太好了，这次的任务你完成得非常成功，这是你应得的报酬，请收下。",Missionruse="你可以和帮会内其他成员一起，组队完成任务！建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",objdataId =9728 },
											},
											{ 
											--天山仙人谷除妖
												{ MissionId=7734, MissionName = "【帮会】仙人谷除妖", MissionTarget = "  打败@npc_44002", MissionInfo = "\t为了支援帮会的建设，我们通常会挑选一些帮内的精兵强将去完成王城大将军所发出的悬赏任务，今天共有六个任务，你会随机得到其中一个。\n\t#G邪灵萨满#W：他本是一位伟大的萨满，却因为深爱的人意外惨死而开始嫉恨所有处在幸福当中的人们，他用自己强大的法术四处破坏，不断残杀，被国师和大将军击败后，逃进了仙人谷，并在那里召唤出了大群的元素生物保护自己。但是他的邪恶和恐惧却并未从这片土地上消失，你的任务就是让他和他邪恶的智慧从这个世界上彻底消失。\n\t此任务每天只能接取一次，放弃任务后只能在次日再次领取。\n\t你准备好接取仙人谷除妖之#G邪灵萨满任务#W吗？#r\t当帮主发布#G除妖令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t@npc_44002非常危险，最好本帮成员组队共同前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。\n", SubmitNPCGUID = 126020,	ExpBonus = 0,NPCName = "@npc_126020",Completed ="已经干掉了那个邪灵萨满！？太好了，这是你应得的报酬，请收下。",Missionruse="你可以和帮会内其他成员一起，组队完成任务！建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",objdataId = 9723}, 
												{ MissionId=7735, MissionName = "【帮会】仙人谷除妖", MissionTarget = "  打败@npc_45001", MissionInfo = "\t为了支援帮会的建设，我们通常会挑选一些帮内的精兵强将去完成王城大将军所发出的悬赏任务，今天共有六个任务，你会随机得到其中一个。\n\t#G嗜血人屠#W：地传说他是一个很普通的屠夫，原本一直在王城中做生意，一次地震后，人们意外地发现在他家院内藏有无数骸骨，直到那时人们才发现原来他所贩卖的生猪竟然是用邪术变化的无辜百姓，事情败露后这个嗜血的屠夫逃进了边塞的仙人谷，只是每逢月圆的午夜他都会从藏身的仙人谷中走出来作恶。\n\t此任务每天只能接取一次，放弃任务后只能在次日再次领取。\n\t你准备好接取仙人谷除妖之#G嗜血人屠任务#W吗？#r\t当帮主发布#G除妖令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t@npc_45001非常危险，最好本帮成员组队前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。\n\n",	SubmitNPCGUID = 126020, ExpBonus = 0,NPCName = "@npc_126020",Completed ="你的胜利归来让我觉得很欣慰，这是你应得的报酬，请收下。",Missionruse="你可以和帮会内其他成员一起，组队完成任务！建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",objdataId =9724 },
												{ MissionId=7736, MissionName = "【帮会】仙人谷除妖", MissionTarget = "  打败@npc_45002", MissionInfo = "\t为了支援帮会的建设，我们通常会挑选一些帮内的精兵强将去完成王城大将军所发出的悬赏任务，今天共有六个任务，你会随机得到其中一个。\n\t#G走尸人魔#W：走尸人魔原本是王国内的一员勇将，还是大将军苏儿台的师傅，在一次与邪魔的战斗中被邪灵附体，日子一天天过去，邪灵最终腐蚀了他的意志和肉体，他终于成为了一具受邪灵摆布的行尸走肉。被大将军射瞎了一只眼睛后，他也逃进了仙人谷。\n\t此任务每天只能接取一次，放弃任务后只能在次日再次领取。\n\t你准备好接取仙人谷除妖之#G走尸人魔任务#W吗？#r\t当帮主发布收#G除妖令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t@npc_45002极度危险，最好本帮成员组队前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。\n\n",SubmitNPCGUID = 126020,	ExpBonus = 0,NPCName = "@npc_126020",Completed ="看到你归来的表情，我就知道此行一定相当顺利 ，这是你应得的报酬，请收下。",Missionruse="你可以和帮会内其他成员一起，组队完成任务！建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",objdataId =9725 },
												{ MissionId=7737, MissionName = "【帮会】仙人谷除妖", MissionTarget = "  打败@npc_44006", MissionInfo = "\t为了支援帮会的建设，我们通常会挑选一些帮内的精兵强将去完成王城大将军所发出的悬赏任务，今天共有六个任务，你会随机得到其中一个。\n\t#G五通鬼婆#W：居住在仙人谷中的一个面目憎恶的老太婆，相传她善于变化，经常用些糕点来诱拐百姓家的小孩子，被拐走的孩子都是有去无回，人们憎恨却又拿她没有办法，只得家家闭户。\n\t此任务每天只能接取一次，放弃任务后只能在次日再次领取。\n\t你准备好接取仙人谷除妖之#G五通鬼婆任务#W吗？#r\t当帮主发布G除妖令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t@npc_44006比较危险，最好本帮成员组队前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。\n\n", SubmitNPCGUID = 126020,	ExpBonus = 0,NPCName = "@npc_126020",Completed ="我一直在等着你的好消息，这些是你应得的报酬，请收下吧。",Missionruse="你可以和帮会内其他成员一起，组队完成任务！建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",objdataId =9726 }, 
												{ MissionId=7738, MissionName = "【帮会】仙人谷除妖", MissionTarget = "  打败@npc_45006", MissionInfo = "\t为了支援帮会的建设，我们通常会挑选一些帮内的精兵强将去完成王城大将军所发出的悬赏任务，今天共有六个任务，你会随机得到其中一个。\n\t#G铁甲尸王#W：不知什么朝代一位忠心的大将军，死后依然没有忘记生前君主的委托，固执地守卫着自己的疆土。他视所有王国的人们为敌人，现在他正在仙人谷召集着自己的军队，随时准备攻打王城，维护他那早已失去在历史上烟消云散的帝国疆土。\n\t此任务每天只能接取一次，放弃任务后只能在次日再次领取。\n\t你准备好接取仙人谷除之#G铁甲尸王任务#W吗？#r\t当帮主发布#G除妖令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t@npc_45006异常凶猛，最好本帮成员组队前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。\n\n",	SubmitNPCGUID = 126020, ExpBonus = 0,NPCName = "@npc_126020",Completed ="看来我是杞人忧天了，你的实力证明了一切，这是你应得的报酬，请收下。",Missionruse="你可以和帮会内其他成员一起，组队完成任务！建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",objdataId =9727 },
												{ MissionId=7739, MissionName = "【帮会】仙人谷除妖", MissionTarget = "  打败@npc_43004", MissionInfo = "\t为了支援帮会的建设，我们通常会挑选一些帮内的精兵强将去完成王城大将军所发出的悬赏任务，今天共有六个任务，你会随机得到其中一个。\n\t#G幽冥死神#W：一个谜一样的恶魔，通常我们都称他为“噩梦”，他出没于黑暗之中，仿佛地府的恶魔，雪亮的镰刀每一次的挥舞都会夺走一条鲜活的生命，侥幸逃生的人都称他为终生的噩梦！\n\t你准备好接取仙人谷除妖之#G幽冥死神任务#W吗？#r\t当帮主发布#G除妖令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t@npc_43004非常危险，最好本帮成员组队前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。\n\n",SubmitNPCGUID = 126020,	ExpBonus = 0,NPCName = "@npc_126020",Completed ="太好了，这次的任务你完成得非常成功，这是你应得的报酬，请收下。",Missionruse="你可以和帮会内其他成员一起，组队完成任务！建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",objdataId =9728 },
											},

											{ 
											--昆仑仙人谷除妖
												{ MissionId=7728, MissionName = "【帮会】仙人谷除妖", MissionTarget = "  打败@npc_44002", MissionInfo = "\t为了支援帮会的建设，我们通常会挑选一些帮内的精兵强将去完成王城大将军所发出的悬赏任务，今天共有六个任务，你会随机得到其中一个。\n\t#G邪灵萨满#W：他本是一位伟大的萨满，却因为深爱的人意外惨死而开始嫉恨所有处在幸福当中的人们，他用自己强大的法术四处破坏，不断残杀，被国师和大将军击败后，逃进了仙人谷，并在那里召唤出了大群的元素生物保护自己。但是他的邪恶和恐惧却并未从这片土地上消失，你的任务就是让他和他邪恶的智慧从这个世界上彻底消失。\n\t此任务每天只能接取一次，放弃任务后只能在次日再次领取。\n\t你准备好接取仙人谷除妖之#G邪灵萨满任务#W吗？#r\t当帮主发布#G除妖令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t@npc_44002非常危险，最好本帮成员组队共同前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。\n", SubmitNPCGUID = 129020,	ExpBonus = 0,NPCName = "@npc_129020",Completed ="已经干掉了那个邪灵萨满！？太好了，这是你应得的报酬，请收下。",Missionruse="你可以和帮会内其他成员一起，组队完成任务！建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",objdataId = 9723}, 
												{ MissionId=7729, MissionName = "【帮会】仙人谷除妖", MissionTarget = "  打败@npc_45001", MissionInfo = "\t为了支援帮会的建设，我们通常会挑选一些帮内的精兵强将去完成王城大将军所发出的悬赏任务，今天共有六个任务，你会随机得到其中一个。\n\t#G嗜血人屠#W：地传说他是一个很普通的屠夫，原本一直在王城中做生意，一次地震后，人们意外地发现在他家院内藏有无数骸骨，直到那时人们才发现原来他所贩卖的生猪竟然是用邪术变化的无辜百姓，事情败露后这个嗜血的屠夫逃进了边塞的仙人谷，只是每逢月圆的午夜他都会从藏身的仙人谷中走出来作恶。\n\t此任务每天只能接取一次，放弃任务后只能在次日再次领取。\n\t你准备好接取仙人谷除妖之#G嗜血人屠任务#W吗？#r\t当帮主发布#G除妖令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t@npc_45001非常危险，最好本帮成员组队前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。\n\n",	SubmitNPCGUID = 129020, ExpBonus = 0,NPCName = "@npc_129020",Completed ="你的胜利归来让我觉得很欣慰，这是你应得的报酬，请收下。",Missionruse="你可以和帮会内其他成员一起，组队完成任务！建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",objdataId =9724 },
												{ MissionId=7730, MissionName = "【帮会】仙人谷除妖", MissionTarget = "  打败@npc_45002", MissionInfo = "\t为了支援帮会的建设，我们通常会挑选一些帮内的精兵强将去完成王城大将军所发出的悬赏任务，今天共有六个任务，你会随机得到其中一个。\n\t#G走尸人魔#W：走尸人魔原本是王国内的一员勇将，还是大将军苏儿台的师傅，在一次与邪魔的战斗中被邪灵附体，日子一天天过去，邪灵最终腐蚀了他的意志和肉体，他终于成为了一具受邪灵摆布的行尸走肉。被大将军射瞎了一只眼睛后，他也逃进了仙人谷。\n\t此任务每天只能接取一次，放弃任务后只能在次日再次领取。\n\t你准备好接取仙人谷除妖之#G走尸人魔任务#W吗？#r\t当帮主发布收#G除妖令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t@npc_45002极度危险，最好本帮成员组队前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。\n\n",SubmitNPCGUID = 129020,	ExpBonus = 0,NPCName = "@npc_129020",Completed ="看到你归来的表情，我就知道此行一定相当顺利 ，这是你应得的报酬，请收下。",Missionruse="你可以和帮会内其他成员一起，组队完成任务！建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",objdataId =9725 },
												{ MissionId=7731, MissionName = "【帮会】仙人谷除妖", MissionTarget = "  打败@npc_44006", MissionInfo = "\t为了支援帮会的建设，我们通常会挑选一些帮内的精兵强将去完成王城大将军所发出的悬赏任务，今天共有六个任务，你会随机得到其中一个。\n\t#G五通鬼婆#W：居住在仙人谷中的一个面目憎恶的老太婆，相传她善于变化，经常用些糕点来诱拐百姓家的小孩子，被拐走的孩子都是有去无回，人们憎恨却又拿她没有办法，只得家家闭户。\n\t此任务每天只能接取一次，放弃任务后只能在次日再次领取。\n\t你准备好接取仙人谷除妖之#G五通鬼婆任务#W吗？#r\t当帮主发布G除妖令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t@npc_44006比较危险，最好本帮成员组队前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。\n\n", SubmitNPCGUID = 129020,	ExpBonus = 0,NPCName = "@npc_129020",Completed ="我一直在等着你的好消息，这些是你应得的报酬，请收下吧。",Missionruse="你可以和帮会内其他成员一起，组队完成任务！建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",objdataId =9726 }, 
												{ MissionId=7732, MissionName = "【帮会】仙人谷除妖", MissionTarget = "  打败@npc_45006", MissionInfo = "\t为了支援帮会的建设，我们通常会挑选一些帮内的精兵强将去完成王城大将军所发出的悬赏任务，今天共有六个任务，你会随机得到其中一个。\n\t#G铁甲尸王#W：不知什么朝代一位忠心的大将军，死后依然没有忘记生前君主的委托，固执地守卫着自己的疆土。他视所有王国的人们为敌人，现在他正在仙人谷召集着自己的军队，随时准备攻打王城，维护他那早已失去在历史上烟消云散的帝国疆土。\n\t此任务每天只能接取一次，放弃任务后只能在次日再次领取。\n\t你准备好接取仙人谷除之#G铁甲尸王任务#W吗？#r\t当帮主发布#G除妖令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t@npc_45006异常凶猛，最好本帮成员组队前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。\n\n",	SubmitNPCGUID = 129020, ExpBonus = 0,NPCName = "@npc_129020",Completed ="看来我是杞人忧天了，你的实力证明了一切，这是你应得的报酬，请收下。",Missionruse="你可以和帮会内其他成员一起，组队完成任务！建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",objdataId =9727 },
												{ MissionId=7733, MissionName = "【帮会】仙人谷除妖", MissionTarget = "  打败@npc_43004", MissionInfo = "\t为了支援帮会的建设，我们通常会挑选一些帮内的精兵强将去完成王城大将军所发出的悬赏任务，今天共有六个任务，你会随机得到其中一个。\n\t#G幽冥死神#W：一个谜一样的恶魔，通常我们都称他为“噩梦”，他出没于黑暗之中，仿佛地府的恶魔，雪亮的镰刀每一次的挥舞都会夺走一条鲜活的生命，侥幸逃生的人都称他为终生的噩梦！\n\t你准备好接取仙人谷除妖之#G幽冥死神任务#W吗？#r\t当帮主发布#G除妖令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t@npc_43004非常危险，最好本帮成员组队前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。\n\n",SubmitNPCGUID = 129020,	ExpBonus = 0,NPCName = "@npc_129020",Completed ="太好了，这次的任务你完成得非常成功，这是你应得的报酬，请收下。",Missionruse="你可以和帮会内其他成员一起，组队完成任务！建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",objdataId =9728 },
											},
											{ 
											--敦煌仙人谷除妖
												{ MissionId=7722, MissionName = "【帮会】仙人谷除妖", MissionTarget = "  打败@npc_44002", MissionInfo = "\t为了支援帮会的建设，我们通常会挑选一些帮内的精兵强将去完成王城大将军所发出的悬赏任务，今天共有六个任务，你会随机得到其中一个。\n\t#G邪灵萨满#W：他本是一位伟大的萨满，却因为深爱的人意外惨死而开始嫉恨所有处在幸福当中的人们，他用自己强大的法术四处破坏，不断残杀，被国师和大将军击败后，逃进了仙人谷，并在那里召唤出了大群的元素生物保护自己。但是他的邪恶和恐惧却并未从这片土地上消失，你的任务就是让他和他邪恶的智慧从这个世界上彻底消失。\n\t此任务每天只能接取一次，放弃任务后只能在次日再次领取。\n\t你准备好接取仙人谷除妖之#G邪灵萨满任务#W吗？#r\t当帮主发布#G除妖令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t@npc_44002非常危险，最好本帮成员组队共同前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。\n", SubmitNPCGUID = 132020,	ExpBonus = 0,NPCName = "@npc_132020",Completed ="已经干掉了那个邪灵萨满！？太好了，这是你应得的报酬，请收下。",Missionruse="你可以和帮会内其他成员一起，组队完成任务！建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",objdataId = 9723}, 
												{ MissionId=7723, MissionName = "【帮会】仙人谷除妖", MissionTarget = "  打败@npc_45001", MissionInfo = "\t为了支援帮会的建设，我们通常会挑选一些帮内的精兵强将去完成王城大将军所发出的悬赏任务，今天共有六个任务，你会随机得到其中一个。\n\t#G嗜血人屠#W：地传说他是一个很普通的屠夫，原本一直在王城中做生意，一次地震后，人们意外地发现在他家院内藏有无数骸骨，直到那时人们才发现原来他所贩卖的生猪竟然是用邪术变化的无辜百姓，事情败露后这个嗜血的屠夫逃进了边塞的仙人谷，只是每逢月圆的午夜他都会从藏身的仙人谷中走出来作恶。\n\t此任务每天只能接取一次，放弃任务后只能在次日再次领取。\n\t你准备好接取仙人谷除妖之#G嗜血人屠任务#W吗？#r\t当帮主发布#G除妖令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t@npc_45001非常危险，最好本帮成员组队前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。\n\n",	SubmitNPCGUID = 132020, ExpBonus = 0,NPCName = "@npc_132020",Completed ="你的胜利归来让我觉得很欣慰，这是你应得的报酬，请收下。",Missionruse="你可以和帮会内其他成员一起，组队完成任务！建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",objdataId =9724 },
												{ MissionId=7724, MissionName = "【帮会】仙人谷除妖", MissionTarget = "  打败@npc_45002", MissionInfo = "\t为了支援帮会的建设，我们通常会挑选一些帮内的精兵强将去完成王城大将军所发出的悬赏任务，今天共有六个任务，你会随机得到其中一个。\n\t#G走尸人魔#W：走尸人魔原本是王国内的一员勇将，还是大将军苏儿台的师傅，在一次与邪魔的战斗中被邪灵附体，日子一天天过去，邪灵最终腐蚀了他的意志和肉体，他终于成为了一具受邪灵摆布的行尸走肉。被大将军射瞎了一只眼睛后，他也逃进了仙人谷。\n\t此任务每天只能接取一次，放弃任务后只能在次日再次领取。\n\t你准备好接取仙人谷除妖之#G走尸人魔任务#W吗？#r\t当帮主发布收#G除妖令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t@npc_45002极度危险，最好本帮成员组队前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。\n\n",SubmitNPCGUID = 132020,	ExpBonus = 0,NPCName = "@npc_132020",Completed ="看到你归来的表情，我就知道此行一定相当顺利 ，这是你应得的报酬，请收下。",Missionruse="你可以和帮会内其他成员一起，组队完成任务！建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",objdataId =9725 },
												{ MissionId=7725, MissionName = "【帮会】仙人谷除妖", MissionTarget = "  打败@npc_44006", MissionInfo = "\t为了支援帮会的建设，我们通常会挑选一些帮内的精兵强将去完成王城大将军所发出的悬赏任务，今天共有六个任务，你会随机得到其中一个。\n\t#G五通鬼婆#W：居住在仙人谷中的一个面目憎恶的老太婆，相传她善于变化，经常用些糕点来诱拐百姓家的小孩子，被拐走的孩子都是有去无回，人们憎恨却又拿她没有办法，只得家家闭户。\n\t此任务每天只能接取一次，放弃任务后只能在次日再次领取。\n\t你准备好接取仙人谷除妖之#G五通鬼婆任务#W吗？#r\t当帮主发布G除妖令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t@npc_44006比较危险，最好本帮成员组队前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。\n\n", SubmitNPCGUID = 132020,	ExpBonus = 0,NPCName = "@npc_132020",Completed ="我一直在等着你的好消息，这些是你应得的报酬，请收下吧。",Missionruse="你可以和帮会内其他成员一起，组队完成任务！建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",objdataId =9726 }, 
												{ MissionId=7726, MissionName = "【帮会】仙人谷除妖", MissionTarget = "  打败@npc_45006", MissionInfo = "\t为了支援帮会的建设，我们通常会挑选一些帮内的精兵强将去完成王城大将军所发出的悬赏任务，今天共有六个任务，你会随机得到其中一个。\n\t#G铁甲尸王#W：不知什么朝代一位忠心的大将军，死后依然没有忘记生前君主的委托，固执地守卫着自己的疆土。他视所有王国的人们为敌人，现在他正在仙人谷召集着自己的军队，随时准备攻打王城，维护他那早已失去在历史上烟消云散的帝国疆土。\n\t此任务每天只能接取一次，放弃任务后只能在次日再次领取。\n\t你准备好接取仙人谷除之#G铁甲尸王任务#W吗？#r\t当帮主发布#G除妖令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t@npc_45006异常凶猛，最好本帮成员组队前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。\n\n",	SubmitNPCGUID = 132020, ExpBonus = 0,NPCName = "@npc_132020",Completed ="看来我是杞人忧天了，你的实力证明了一切，这是你应得的报酬，请收下。",Missionruse="你可以和帮会内其他成员一起，组队完成任务！建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",objdataId =9727 },
												{ MissionId=7727, MissionName = "【帮会】仙人谷除妖", MissionTarget = "  打败@npc_43004", MissionInfo = "\t为了支援帮会的建设，我们通常会挑选一些帮内的精兵强将去完成王城大将军所发出的悬赏任务，今天共有六个任务，你会随机得到其中一个。\n\t#G幽冥死神#W：一个谜一样的恶魔，通常我们都称他为“噩梦”，他出没于黑暗之中，仿佛地府的恶魔，雪亮的镰刀每一次的挥舞都会夺走一条鲜活的生命，侥幸逃生的人都称他为终生的噩梦！\n\t你准备好接取仙人谷除妖之#G幽冥死神任务#W吗？#r\t当帮主发布#G除妖令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点，建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",MissionHelp = "\t@npc_43004非常危险，最好本帮成员组队前往除之！随着你所在帮会等级的提高，你获得的奖励也会相应增加。\n\n",SubmitNPCGUID = 132020,	ExpBonus = 0,NPCName = "@npc_132020",Completed ="太好了，这次的任务你完成得非常成功，这是你应得的报酬，请收下。",Missionruse="你可以和帮会内其他成员一起，组队完成任务！建帮时间低于24小时或入帮时间低于24小时，不能获得帮会经验！",objdataId =9728 },
											},
										}

function x300826_IsHavePreMission(sceneId, selfId)
	local nCountry = GetCurCountry( sceneId, selfId )
	for i,itm in x300826_g_PreMissionId[nCountry+1] do
		if IsHaveQuestNM( sceneId, selfId, itm ) > 0 then	-- 如果有这个任务
			return 1
		end
	end
	return -1
end

function x300826_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
	if x300826_IsHavePreMission(sceneId, selfId) > 0 then
		return 0
	end
	
	local nCountry = GetCurCountry( sceneId, selfId )

	for i,itm in x300826_g_SubMissionId[nCountry+1] do
		if IsHaveQuestNM( sceneId, selfId, itm.MissionId ) > 0 then	-- 如果有这个任务
			return 0
		end
	end
	if GetGuildID( sceneId, selfId ) == -1 then
		--不在帮会中
		return
	end
	local Level = GetLevel(sceneId, selfId)
	if Level >= 65 and Level <= 100 then	-- 如果可以接这个任务
		local state = GetQuestStateNM( sceneId, selfId, targetId, MissionId);
		AddQuestTextNM( sceneId, selfId, targetId, MissionId, 8, state ) -- 显示任务信息
		--AddQuestNumText( sceneId, MissionId, "【帮会】仙人谷除妖", state);
		return 1
	end
	
end


--选中任务
function x300826_ProcEventEntry( sceneId, selfId, targetId, MissionId )
	local index = 1
	local IsHaveQuest = 0
	

	local nCountry = GetCurCountry( sceneId, selfId )
	
	for i,itm in x300826_g_SubMissionId[nCountry+1] do
		if IsHaveQuestNM( sceneId, selfId, itm.MissionId ) > 0 then	-- 如果有这个任务
	
			IsHaveQuest = 1
			MissionId = itm.MissionId
			index = i
			break
		end
	end

	if(IsHaveQuest > 0) then
		local bDone = x300826_CheckSubmit(sceneId, selfId, MissionId);
		if(bDone > 0) then
			x300826_DispatchCompletedInfo( sceneId, selfId, targetId,index) --完成任务显示
		else
			x300826_DispatchContinueInfo( sceneId, selfId, targetId,index ) --未完成任务显示
		end
	else
	
		local day =  mod(GetDayTime(),1000) + GetGuildID( sceneId, selfId )

		if day < 0 then
			day = 0
		end

		index =  mod(day,6)
		index = index + 1

--		 local num = random(1,60)
--		 if num <= 10 then
--			 index = 1
--		 elseif num <= 20 then
--			 index = 2
--		 elseif num <= 30 then
--			 index = 3
--		 elseif num <= 40 then
--			 index = 4
--		 elseif num <= 50 then
--			 index = 5
--		 else  
--			index = 6
--		 end

		x300826_DispatchMissionInfo( sceneId, selfId, targetId, index)--x300826_g_SubMissionId[nCountry+1][index].MissionId)		--任务信息显示
	end

end

---------------------------------------------------------------------------------------------------
--检查任务是否可提交
---------------------------------------------------------------------------------------------------
function x300826_CheckSubmit(sceneId, selfId,MissionId)

	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
	return GetQuestParam(sceneId, selfId, misIndex, 7);

end


---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300826_DispatchCompletedInfo( sceneId, selfId, targetId,index )
	
	BeginQuestEvent(sceneId)

		--任务完成信息
		local nCountry = GetCurCountry( sceneId, selfId )

		AddQuestText(sceneId,"#Y"..x300826_g_SubMissionId[nCountry+1][index].MissionName)
		AddQuestText(sceneId,x300826_g_SubMissionId[nCountry+1][index].Completed)
		AddQuestText(sceneId," ")

		--1、经验
		local level = GetLevel(sceneId, selfId)
		--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
		local ExpBonus = ceil ( (100 * 3 * level * 15*1*1 ) )
		ExpBonus =floor(ExpBonus+0.5)
		if ExpBonus> 0 then
			AddQuestExpBonus(sceneId, ExpBonus )
		end
		--2 帮供
		if x300826_g_BonusMoney8>0 then
			AddQuestMoneyBonus8(sceneId,x300826_g_BonusMoney8)
		end
		--3 帮会经验
		if x300826_g_GuildExpBonus>0 then
			AddQuestGuildExpBonus(sceneId,x300826_g_GuildExpBonus)
		end
		EndQuestEvent(sceneId)
		DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x300826_g_ScriptId, x300826_g_SubMissionId[nCountry+1][index].MissionId);

end



---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300826_DispatchContinueInfo( sceneId, selfId, targetId,index )
	
	BeginQuestEvent(sceneId)

		--任务继续信息
		local nCountry = GetCurCountry( sceneId, selfId )

		AddQuestText(sceneId,"#Y"..x300826_g_SubMissionId[nCountry+1][index].MissionName)
		AddQuestText(sceneId,format("%s", x300826_g_SubMissionId[nCountry+1][index].MissionInfo))
		AddQuestText(sceneId," ")

		--任务目标
		AddQuestText( sceneId,"#Y完成情况：")
		AddQuestText(sceneId, "未完成");

		--1、经验
		local level = GetLevel(sceneId, selfId)
		--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
		local ExpBonus = ceil ( (100 * 3 * level * 15*1*1 ) )
		ExpBonus =floor(ExpBonus+0.5)
		if ExpBonus> 0 then
			AddQuestExpBonus(sceneId, ExpBonus )
		end
		
		--2 经验
		if x300826_g_BonusMoney8>0 then
			AddQuestMoneyBonus8(sceneId,x300826_g_BonusMoney8)
		end
		--3 帮会经验
		if x300826_g_GuildExpBonus>0 then
			AddQuestGuildExpBonus(sceneId,x300826_g_GuildExpBonus)
		end

		
	--任务提示信息
	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, targetId, x300826_g_ScriptId, x300826_g_SubMissionId[nCountry+1][index].MissionId,0);

end


---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x300826_DispatchMissionInfo( sceneId, selfId, NPCId,index )

	BeginQuestEvent(sceneId)

		--任务信息
		local BangExp =x300826_g_BangExp
    	local nCountry = GetCurCountry( sceneId, selfId )

		AddQuestText(sceneId,"#Y"..x300826_g_SubMissionId[nCountry+1][index].MissionName)
		AddQuestText(sceneId,format("%s", x300826_g_SubMissionId[nCountry+1][index].MissionInfo))
		AddQuestText(sceneId," ")

		--任务目标
		AddQuestText( sceneId,"#Y任务目标：")
		AddQuestText( sceneId,format("%s", x300826_g_SubMissionId[nCountry+1][index].MissionTarget))
		AddQuestText( sceneId," ")

		--提示信息
		if x300826_g_SubMissionId[nCountry+1][index].MissionHelp ~= "" then

			AddQuestText(sceneId,"#Y任务提示：")
			AddQuestText(sceneId,format("%s", x300826_g_SubMissionId[nCountry+1][index].MissionHelp))
			AddQuestText(sceneId," ")
		end

		--任务奖励信息

		--1、经验
		local level = GetLevel(sceneId, selfId)
		--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
		local ExpBonus = ceil ( (100 * 3 * level * 15*1*1 ) )
		ExpBonus =floor(ExpBonus+0.5)
		if ExpBonus > 0 then
			AddQuestExpBonus(sceneId, ExpBonus )
		end
		
		--2 帮供
		if x300826_g_BonusMoney8>0 then
			AddQuestMoneyBonus8(sceneId,x300826_g_BonusMoney8)
		end
		--3 帮会经验
		if x300826_g_GuildExpBonus>0 then
			AddQuestGuildExpBonus(sceneId,x300826_g_GuildExpBonus)
		end
		EndQuestEvent(sceneId)
		DispatchQuestInfoNM(sceneId, selfId, NPCId, x300826_g_ScriptId, x300826_g_SubMissionId[nCountry+1][index].MissionId);
		
end


---------------------------------------------------------------------------------------------------
--获得奖励
---------------------------------------------------------------------------------------------------
function x300826_OnReturn1(sceneId, selfId,MissionData,MissionId,targetId)
	local curTime = GetCurrentTime()
	local isMultiple = 0
	if curTime - MissionData < 2*60*60 then
		isMultiple = 1
	end
	local joinguildtime = MissionId
	x300826_GetBonus( sceneId,selfId, isMultiple, joinguildtime )
end

function x300826_GetBonus( sceneId, selfId,isMultiple,joinguildtime)	--奖励经验
	local level = GetLevel(sceneId, selfId)
	--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
	local ExpBonus = ceil ( (100 * 3 * level * 15*1*1 ) )
	ExpBonus =floor(ExpBonus+0.5)
	local GuildLevel = GetGuildSimpleData(GetGuildID( sceneId, selfId ))--得到帮会简单数据(等级) 
    if ExpBonus > 0 then
        local text1 = "你完成了任务：【帮会】仙人谷除妖"
    	local text2 = "获得#R经验"..ExpBonus.."点#o的奖励"
		--local text3 = "获得#R帮会功德1点#o的奖励"
    	--AddGuildMerit(sceneId, selfId,1)
    	AddExp(sceneId, selfId, ExpBonus);
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, text1);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, text2);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		-- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, text3);
		-- EndQuestEvent(sceneId)
		-- DispatchQuestTips(sceneId,selfId)
  		Msg2Player(sceneId,selfId,text1,8,2)
  		Msg2Player(sceneId,selfId,text2,8,2) 
		--Msg2Player(sceneId,selfId,text3,8,2)  
		if isMultiple == 1 then
			local ExpBonus1 = ceil (100 * 3 * level * 15*1*1 *3)
			local Exp3 = ceil (100 * 3 * level * 15*1*1*3 )
			local ExpBonus2 = ceil (100 * 3 * level * 15*1*1 *2)
			local pos = GetGuildOfficial(sceneId, selfId)
			local text3 = "获得#R使命点2点#o的奖励"
				AddGuildShiMing(sceneId, selfId,2)
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, text3);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)	
				Msg2Player(sceneId,selfId,text3,8,2)
			if pos == 5 then
				local guildid =GetGuildID(sceneId, selfId)
				if  GetGuildCacheFreeParam(guildid,GD_GUILD_INDEX_CHIEF_MULTIMISSION_DAY) == GetDayOfYear() then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "帮主职位只能领取一次除妖令奖励");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					Msg2Player(sceneId,selfId,"帮主职位只能领取一次除妖令奖励",8,2)
				else
					AddExp(sceneId, selfId, ExpBonus1);	
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "额外获得#R经验"..Exp3.."点#o的奖励");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,"帮会多倍任务额外获得#R经验"..Exp3.."点#o的奖励",8,2)
					SetGuildQuestData(sceneId,GetGuildID(sceneId,selfId),GD_GUILD_INDEX_CHIEF_MULTIMISSION_DAY,GetDayOfYear(),0)
				end
			elseif pos == 4 then
				local guildid =GetGuildID(sceneId, selfId)
				if  GetGuildCacheFreeParam(guildid,GD_GUILD_INDEX_ASSCHIEF_MULTIMISSION_DAY) == GetDayOfYear() then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "副帮主职位只能领取一次除妖令奖励");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					Msg2Player(sceneId,selfId,"副帮主职位只能领取一次除妖令奖励",8,2)
				else
					AddExp(sceneId, selfId, ExpBonus2);	
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "额外获得#R经验"..ExpBonus2.."点#o的奖励");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,"帮会多倍任务额外获得#R经验"..ExpBonus2.."点#o的奖励",8,2)
					SetGuildQuestData(sceneId,GetGuildID(sceneId,selfId),GD_GUILD_INDEX_ASSCHIEF_MULTIMISSION_DAY,GetDayOfYear(),0)
				end
			else
				AddExp(sceneId, selfId, ExpBonus);	
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "额外获得#R经验"..ExpBonus.."点#o的奖励");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)	
				Msg2Player(sceneId,selfId,"帮会多倍任务额外获得#R经验"..ExpBonus.."点#o的奖励",8,2)
			end
		end
		if 	GuildLevel == 2 then
			local level = GetLevel(sceneId, selfId)
			local exp = ceil (100 * 3 * level * 15*0.25*1 )
			AddExp(sceneId, selfId, exp);
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "额外获得#R经验"..exp.."点#o的奖励");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)	
			Msg2Player(sceneId,selfId,"帮会等级2级额外获得#R经验"..exp.."点#o的奖励",8,2)
		end
		if 	GuildLevel == 3 then
			local level = GetLevel(sceneId, selfId)
			local exp = ceil (100 * 3 * level * 15*0.5*1 )
			AddExp(sceneId, selfId, exp);	
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "额外获得#R经验"..exp.."点#o的奖励");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)	
			Msg2Player(sceneId,selfId,"帮会等级3级额外获得#R经验"..exp.."点#o的奖励",8,2)
		end
		if 	GuildLevel == 4 then
			local level = GetLevel(sceneId, selfId)
			local exp = ceil (100 * 3 * level * 15*0.75*1 )
			AddExp(sceneId, selfId, exp);	
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "额外获得#R经验"..exp.."点#o的奖励");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)	
			Msg2Player(sceneId,selfId,"帮会等级4级额外获得#R经验"..exp.."点#o的奖励",8,2)
		end
		if 	GuildLevel == 5 then
			local level = GetLevel(sceneId, selfId)
			local exp = ceil (100 * 3 * level * 15*1*1 )
			AddExp(sceneId, selfId, exp);	
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "额外获得#R经验"..exp.."点#o的奖励");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)	
			Msg2Player(sceneId,selfId,"帮会等级5级额外获得#R经验"..exp.."点#o的奖励",8,2)
		end
	end
--奖励帮贡
    if x300826_g_BonusMoney8 > 0 then
		AddGuildUserPoint(sceneId,selfId,x300826_g_BonusMoney8)	--增加帮贡
		local BonusMoney8 = x300826_g_BonusMoney8
		local pointText = "获得#R帮贡"..BonusMoney8.."点#o的奖励"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, pointText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)			
  		Msg2Player(sceneId,selfId,pointText,8,2)
		if isMultiple == 1 then
			local pos = GetGuildOfficial(sceneId, selfId)
			if pos == 5 then
				local guildid =GetGuildID(sceneId, selfId)
				if  GetGuildCacheFreeParam(guildid,GD_GUILD_INDEX_CHIEF_MULTIMISSION_DAY) == GetDayOfYear() then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "帮主职位只能领取一次除妖令奖励");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					Msg2Player(sceneId,selfId,"帮主职位只能领取一次除妖令奖励",8,2)
				else
					AddGuildUserPoint(sceneId,selfId,300)	--增加帮贡
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "额外获得#R帮贡300点#o的奖励");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,"帮会多倍任务额外获得#R帮贡300点#o的奖励",8,2)
					SetGuildQuestData(sceneId,GetGuildID(sceneId,selfId),GD_GUILD_INDEX_CHIEF_MULTIMISSION_DAY,GetDayOfYear(),0)
				end
			elseif pos == 4 then
				local guildid =GetGuildID(sceneId, selfId)
				if  GetGuildCacheFreeParam(guildid,GD_GUILD_INDEX_ASSCHIEF_MULTIMISSION_DAY) == GetDayOfYear() then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "副帮主职位只能领取一次除妖令奖励");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					Msg2Player(sceneId,selfId,"副帮主职位只能领取一次除妖令奖励",8,2)
				else
					AddGuildUserPoint(sceneId,selfId,200)	--增加帮贡
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "额外获得#R帮贡200点#o的奖励");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,"帮会多倍任务额外获得#R帮贡200点#o的奖励",8,2)
					SetGuildQuestData(sceneId,GetGuildID(sceneId,selfId),GD_GUILD_INDEX_ASSCHIEF_MULTIMISSION_DAY,GetDayOfYear(),0)
				end
			else
				AddGuildUserPoint(sceneId,selfId,100)	--增加帮贡
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "额外获得#R帮贡100点#o的奖励");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)	
				Msg2Player(sceneId,selfId,"帮会多倍任务额外获得#R帮贡100点#o的奖励",8,2)
			end
		end
	end
-- 奖励帮会经验
	local bangExp = x300826_g_GuildExpBonus 
	if bangExp > 0 then
		if joinguildtime == -1 or GetCurrentTime()-joinguildtime<24*3600 then
			BeginQuestEvent(sceneId)
			AddQuestText( sceneId, "很抱歉，您加入帮会时间低于24小时，不能获得帮会经验。" )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			Msg2Player(sceneId,selfId,"很抱歉，您加入帮会时间低于24小时，不能获得帮会经验。",8,2)
			return
		end
		--local gongde = GetGuildMerit(sceneId, selfId)
		--if 	gongde >= 5 then
			AddGuildExp(sceneId,selfId,bangExp)
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "获得#R帮会经验"..bangExp.."点#o的奖励");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)			
			Msg2Player(sceneId,selfId,format("获得#R帮会经验"..bangExp.."点#o的奖励"),8,2)
		-- else
			-- BeginQuestEvent(sceneId)
			-- AddQuestText( sceneId, "很抱歉，帮会功德低于5点，不能获得帮会经验。" )
			-- EndQuestEvent( sceneId )
			-- DispatchQuestTips( sceneId, selfId )
			-- Msg2Player(sceneId,selfId,"很抱歉，帮会功德低于5点，不能获得帮会经验。",8,2)
		-- end
	end
		
end



--**********************************
--接受
--**********************************
function x300826_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	if IsQuestFullNM( sceneId, selfId )==1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"可接任务数量已满")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 
	end

	if GetGuildID( sceneId, selfId ) == -1 then
		--不在帮会中
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "你不是帮会成员，请先加入帮会再来领取！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,"你不是帮会成员，请先加入帮会再来领取！",8,2)
		return
	end
	
	local guildid = GetGuildID( sceneId, selfId )
	local GuildLevel = GetGuildSimpleData(guildid)--得到帮会简单数据(等级)
	if 	GuildLevel < 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，帮会等级到达3级才可以接取仙人谷除妖任务！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,"很抱歉，帮会等级到达3级才可以接取仙人谷除妖任务！",8,2)
	return 
	end
	
	if x300826_GetDayCount(sceneId, selfId) >= x300826_g_Mis_Count then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "你今天已经领取过仙人谷除妖或粮仓除妖任务了，请明天再来吧！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "你今天已经领取过仙人谷除妖或粮仓除妖任务了，请明天再来吧！"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return
	end


	--检查前置任务
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, MissionId )
	if FrontMissiontId1 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
			return 
		end
	end
	if FrontMissiontId2 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
			return 
		end
	end
	if FrontMissiontId3 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
			return
		end
	end
	
	if AddQuestNM( sceneId, selfId,MissionId) == 1 then
 
		BeginQuestEvent(sceneId)
		--接任务写日志
		GamePlayScriptLog(sceneId,selfId,111)

 		AddQuestText(sceneId, "你接受了任务：【帮会】仙人谷除妖")
 		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "你接受了任务：【帮会】仙人谷除妖"
		Msg2Player(sceneId,selfId,Readme,8,2)	

		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		SetQuestByIndex(sceneId, selfId, misIndex, 7, 0);
		SetQuestByIndex(sceneId, selfId, misIndex, 0, 0);
	end
	
end


--完成任务
--返回1代表成功，0代表交任务失败
function x300826_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- 如果没这个任务直接退出
		return 0
	end

	if DelQuestNM( sceneId, selfId, MissionId) < 1 then
		return 
	end
	

	--交任务写日志
	GamePlayScriptLog(sceneId,selfId,112)

	x300826_SetDayCount(sceneId, selfId)

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, "");
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	--GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_MULTI_MISSION_CHUYAO, x300826_g_ScriptId,MissionId,"OnReturn1",targetId)
	GetJoinGuildTime(sceneId,selfId,x300826_g_ScriptId)
	return 0
end

function x300826_OnMemberJoinTimeReturn( sceneId, selfId, param )

	GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_MULTI_MISSION_CHUYAO, x300826_g_ScriptId,param,"OnReturn1",-1)

end

function x300826_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )

	local nCountry = GetCurCountry( sceneId, selfId )

	for i,itm in x300826_g_SubMissionId[nCountry+1] do
		local bHaveMission = IsHaveQuestNM(sceneId, selfId,itm.MissionId );

		if bHaveMission > 0 then
			if npcGuid == itm.SubmitNPCGUID then
				local state = GetQuestStateNM(sceneId,selfId,npcId,itm.MissionId)
				AddQuestNumText(sceneId, itm.MissionId, itm.MissionName,7,state);
				break;
			end
		end
	end

end




--********************************************************************
--放弃
--********************************************************************
function x300826_ProcQuestAbandon( sceneId, selfId,MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- 如果没有这个任务
		return
	end

	DelQuestNM( sceneId, selfId, MissionId)
	local Readme = "你放弃了任务：【帮会】仙人谷除妖"
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, Readme);
    EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	Msg2Player(sceneId,selfId,Readme,8,2)
	x300826_SetDayCount(sceneId, selfId)
end


function x300826_OnReturn(sceneId, selfId,MissionData,MissionId,targetId)

	local CurDaytime = GetDayTime()						--当前时间(天)

 		                                                  --可以做任务
 		BeginQuestEvent(sceneId)
 		AddQuestText(sceneId, "接受仙人谷除妖任务成功，快去做吧！")
 		EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			local Readme = "接受仙人谷除妖任务成功，快去做吧！"
			Msg2Player(sceneId,selfId,Readme,8,2)
		AddQuestNM( sceneId, selfId,MissionId)
	--else
	    --BeginQuestEvent(sceneId)
		--AddQuestText(sceneId, "帮会今天还没有发布该任务！")
		--EndQuestEvent(sceneId)
		--	DispatchQuestTips(sceneId,selfId)
			--local Readme = "帮会今天还没有发布该任务！"
			--Msg2Player(sceneId,selfId,Readme,8,2)
		--DispatchQuestTips(sceneId,selfId)
	--end

  --  DispatchQuestEventList(sceneId, selfId, -1)
end


--********************************************************************
--接受
--********************************************************************
function x300826_ProcAccept( sceneId, selfId )
end

function x300826_OnDie( sceneId,objId,killerId )

	if killerId == -1 then
		--出错了
		return 
	end

	if IsObjValid(sceneId,killerId)  == 0 then
		--无效OBJ
		return
	end

	local ObjType = GetObjType(sceneId,killerId)

	if ObjType == 3 then		-- 被PET杀死
		ObjType = 1
		killerId = GetOwnerID(sceneId, killerId)
	end

	if ObjType ~= 1 then
		return
	end

	if IsPlayerStateNormal( sceneId,killerId ) ~= 1 then
		return
	end

	local MissionId = -1
	local objdataId = -1
	local nCountry = GetCurCountry( sceneId, killerId )
	
 	for it,itm in x300826_g_SubMissionId[nCountry+1] do
		if IsHaveQuestNM( sceneId, killerId, itm.MissionId ) > 0 then	-- 如果有这个任务
			MissionId = itm.MissionId
			objdataId = itm.objdataId
			break
		end
	end

	local strText = "";
	if MissionId ~= -1 and objdataId == GetMonsterDataID(sceneId,objId) then

		--先算自己的任务数据qq
		local misIndex = GetQuestIndexByID( sceneId, killerId, MissionId )
		local KilledNum = GetQuestParam( sceneId, killerId, misIndex, 0 )

		if KilledNum < x300826_g_NeedKilledNum then	
			SetQuestByIndex( sceneId, killerId, misIndex, 0, KilledNum+1 )
			x300826_QuestLogRefresh( sceneId, killerId, MissionId)

			BeginQuestEvent(sceneId)
			
			if GetName(sceneId,objId) == "" then
				strText = format( "已经杀死怪物: %d/%d", KilledNum+1, x300826_g_NeedKilledNum )
			else
				strText = format( "已经杀死%s: %d/%d", GetName(sceneId,objId), KilledNum+1, x300826_g_NeedKilledNum )
			end

			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, killerId )

			if KilledNum == x300826_g_NeedKilledNum - 1 then
				--完成了～～	
				SetQuestByIndex(sceneId, killerId, misIndex, 7, 1);
				local str = format("%s完成任务",GetName(sceneId,killerId) )
			end
		end

	end

	if GetGuildID(sceneId, killerId) == -1 or HasTeam(sceneId, killerId) < 1 then		--不在帮会或队伍中，只判断自己是否有任务
		return 
	end

	--算同帮同队成员任务数据
	local num =  GetNearTeamCount(sceneId, killerId)
	for	i=0,num-1 do

		local member = GetNearTeamMember(sceneId, killerId,i)
		if member ~= -1 and member ~= killerId and GetGuildID(sceneId, member) == GetGuildID(sceneId, killerId) and IsPlayerStateNormal( sceneId,member ) == 1 then

			local MissionId = -1
			local objdataId = -1

			for n,itm in x300826_g_SubMissionId[nCountry+1] do
				if IsHaveQuestNM( sceneId, member, itm.MissionId ) > 0 then	-- 如果有这个任务
					MissionId = itm.MissionId
					objdataId = itm.objdataId
					break
				end
			end
			if GetHp(sceneId, member) > 0 then
				if MissionId ~= -1  and objdataId == GetMonsterDataID(sceneId,objId)  then
					local MemberMisIndex = GetQuestIndexByID( sceneId, member, MissionId )
					local MemberKilledNum = GetQuestParam( sceneId, member, MemberMisIndex, 0 )

					if MemberKilledNum < x300826_g_NeedKilledNum then	
				
						BeginQuestEvent(sceneId)
						if GetName(sceneId,objId) == "" then
							strText = format( "已经杀死怪物: %d/%d", MemberKilledNum+1, x300826_g_NeedKilledNum )
						else
							strText = format( "已经杀死%s: %d/%d", GetName(sceneId,objId), MemberKilledNum+1, x300826_g_NeedKilledNum )
						end
						AddQuestText( sceneId, strText )
						EndQuestEvent( sceneId )
						DispatchQuestTips( sceneId, member )

						SetQuestByIndex( sceneId, member, MemberMisIndex, 0, MemberKilledNum+1 )
						if MemberKilledNum == x300826_g_NeedKilledNum - 1 then
							--完成了～～
							local str = format("%s完成任务",GetName(sceneId,member) )
							SetQuestByIndex(sceneId, member, MemberMisIndex, 7, 1);
						end				
					end
				end
			end
		end    
	end

end


--杀死怪物
function x300826_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
						   --场景ID, 自己的ID, 怪物表位置号, 怪物objId, 任务ID

end



---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300826_QuestLogRefresh( sceneId, selfId, MissionId)

	local nCountry = GetCurCountry( sceneId, selfId )

	for i,itm in x300826_g_SubMissionId[nCountry+1] do 
		local bHaveMission = IsHaveQuestNM(sceneId, selfId,itm.MissionId );
		if bHaveMission > 0 then
		
			BeginQuestEvent(sceneId)	
			local level = GetLevel(sceneId, selfId)
			--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
			local ExpBonus = ceil ( (100 * 3 * level * 15*1*1 ) )
			ExpBonus =floor(ExpBonus+0.5)
			if ExpBonus > 0 then
			AddQuestExpBonus(sceneId, ExpBonus);		
			end
			if x300826_g_BonusMoney8 > 0 then
			AddQuestMoneyBonus8(sceneId, x300826_g_BonusMoney8 )	--增加帮贡
			end
			if x300826_g_GuildExpBonus>0 then
			AddQuestGuildExpBonus(sceneId,x300826_g_GuildExpBonus)
			end

			local misIndex = GetQuestIndexByID(sceneId, selfId, itm.MissionId);
			local num = GetQuestParam(sceneId, selfId,misIndex,0)
			local text = format("(%d/%d)",num,1)


		    AddQuestLogCustomText( sceneId,
									"",						-- 标题
									itm.MissionName,        -- 任务名字
									itm.MissionTarget..text,		--任务目标
									itm.NPCName,			--任务NPC
									itm.Missionruse,               --任务攻略
									itm.MissionInfo,	--任务描述
									"随着你所在帮会等级的提高，你获得的奖励也会相应增加。"					--任务小提示
									)
			EndQuestEvent(sceneId)
			DispatchQuestLogUpdate(sceneId, selfId, itm.MissionId);
			break
		end
	end

end

function x300826_ProcQuestLogRefresh( sceneId, selfId, MissionId)

	x300826_QuestLogRefresh( sceneId, selfId, MissionId );
end

---------------------------------------------------------------------------------------------------
--取得此任务当天当前已完成次数
---------------------------------------------------------------------------------------------------
function x300826_GetDayCount(sceneId, selfId)

	if x300826_g_Mis_Count > 0 then

		local today = GetDayOfYear()

		local lastday = GetQuestData(sceneId, selfId, MD_GUILD_KILLMONSTER_DATE[1], MD_GUILD_KILLMONSTER_DATE[2], MD_GUILD_KILLMONSTER_DATE[3])

		if lastday ~= today then
			return 0
		end

		local daycount =  GetQuestData(sceneId, selfId, MD_GUILD_KILLMONSTER_COUNT[1], MD_GUILD_KILLMONSTER_COUNT[2], MD_GUILD_KILLMONSTER_COUNT[3])
		return daycount

	end

	return 0
end

---------------------------------------------------------------------------------------------------
--更新当天接任务次数
---------------------------------------------------------------------------------------------------
function x300826_SetDayCount(sceneId, selfId)
	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, MD_GUILD_KILLMONSTER_DATE[1], MD_GUILD_KILLMONSTER_DATE[2], MD_GUILD_KILLMONSTER_DATE[3])

	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_GUILD_KILLMONSTER_DATE[1], MD_GUILD_KILLMONSTER_DATE[2], MD_GUILD_KILLMONSTER_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_GUILD_KILLMONSTER_COUNT[1], MD_GUILD_KILLMONSTER_COUNT[2], MD_GUILD_KILLMONSTER_COUNT[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, MD_GUILD_KILLMONSTER_COUNT[1], MD_GUILD_KILLMONSTER_COUNT[2], MD_GUILD_KILLMONSTER_COUNT[3])
		SetQuestData(sceneId, selfId, MD_GUILD_KILLMONSTER_COUNT[1], MD_GUILD_KILLMONSTER_COUNT[2], MD_GUILD_KILLMONSTER_COUNT[3], daycount+1)
	end
end