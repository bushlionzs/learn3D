--##############################################
--##跨服2v2奖牌兑换脚本 by rj 2010-11-4 ##
--##############################################

x303105_g_ScriptId          		= 303105
x303105_g_MissionName       		= "【兑换】英勇勋章兑换奖励"

--源牌子物品ID
x303105_g_Need_SrcItemID			= 12266663

-- 记录兑换的物品的ID
x303105_g_ChangeintoItemID 			= {}
			
-- 记录当前操作的类型 0 表示兑换道具, 1表示兑换称号
x303105_g_OperateType 				= {}						
-- 二级目录显示的文本
x303105_g_Text 						= "#Y【兑换】英勇勋章#W \n \n\t英勇勋章不仅能体现自己的荣耀和实力，也能在我这兑换丰富实用的道具、稀奇少有的坐骑和战场专有的称号。请问你需要兑换什么呢?"
-- 一级目录显示的文本																	
x303105_g_ShowDemoText				= "\t当你在跨服2V2战场中获胜之后，可以拿英勇勋章到我这里进行兑换！"

--AddQuestNumText分支
x303105_g_MoonCake 					= 1
-- x303105_g_ThawRed					= 2
x303105_g_ColouredGlaze				= 3
x303105_g_Gem 						= 4
x303105_g_Azoth						= 5
x303105_g_Horse						= 6
x303105_g_Title						= 7
x303105_g_Majiang					= 8
x303105_g_Jewel						= 9

x303105_g_Back						= 100

--目的奖品集合，id物品的id  num数量 , neednum扣除徽章的数量
x303105_g_Need_DstItemInfo 		= 
{ 
{itemid = 12030254, num = 1, neednum = 4}, 
{itemid = 12030255, num = 1, neednum = 5}, 
{itemid = 12030256, num = 1, neednum = 6}, 
{itemid = 12030257, num = 1, neednum = 7}, 
{itemid = 12030259, num = 1, neednum = 8}, 
-- {itemid = 12050093, num = 1, neednum = 12}, 
-- {itemid = 12050094, num = 1, neednum = 13}, 
{itemid = 11000702, num = 1, neednum = 236}, 
{itemid = 11000701, num = 1, neednum = 236}, 
{itemid = 11000500, num = 1, neednum = 140}, 
{itemid = 11000502, num = 1, neednum = 100}, 
{itemid = 11000503, num = 1, neednum = 160}, 
{itemid = 11000504, num = 1, neednum = 120}, 
{itemid = 11030620, num = 1, neednum = 60}, 
{itemid = 11030636, num = 1, neednum = 60}, 
{itemid = 10297200, num = 1, neednum = 568}, 
{itemid = 10287200, num = 1, neednum = 568}, 
{itemid = 10297201, num = 1, neednum = 1420}, 
{itemid = 10287201, num = 1, neednum = 1420}, 
{itemid = 12030511, num = 1, neednum = 228}, 
{itemid = 12030512, num = 1, neednum = 288}, 
{itemid = 12050262, num = 1, neednum = 192}, 
{itemid = 12050263, num = 1, neednum = 768}, 
{itemid = 12050264, num = 1, neednum = 1728}, 

}

-- 称号奖励表, id 称号ID, name 名称, neednum 需要徽章数量
x303105_g_AttackTitle 			= 
{
	{id = 119, name = "坚如磐石·一", neednum =24},
	{id = 120, name = "坚如磐石·二", neednum = 25},
	{id = 121, name = "坚如磐石·三", neednum = 26},
	{id = 122, name = "铜墙铁壁·一", neednum = 27},
	{id = 123, name = "铜墙铁壁·二", neednum = 29},
	{id = 124, name = "铜墙铁壁·三", neednum = 63},
	{id = 125, name = "坚不可摧·一", neednum = 69},
	{id = 126, name = "坚不可摧·二", neednum = 115},
	{id = 127, name = "坚不可摧·三", neednum = 130},
	{id = 128, name = "金刚不破", neednum = 144},
}

--称号奖励表, 同上
x303105_g_DefenceTitle 			= 
{
	{id = 129, name = "势如破竹·一", neednum =24},
	{id = 130, name = "势如破竹·二", neednum = 25},
	{id = 131, name = "势如破竹·三", neednum = 26},
	{id = 132, name = "摧枯拉朽·一", neednum = 27},
	{id = 133, name = "摧枯拉朽·二", neednum = 29},
	{id = 134, name = "摧枯拉朽·三", neednum = 63},
	{id = 135, name = "横扫千军·一", neednum = 69},
	{id = 136, name = "横扫千军·二", neednum = 115},
	{id = 137, name = "横扫千军·三", neednum = 130},
	{id = 138, name = "登峰造极", neednum = 144},
}

-- 标题表 title 标题 event 事件ID id 兑换的物品ID,这里的ID对应x303105_g_Need_DstItemInfo里的itemid,要兑换的物品
x303105_g_MoonCakelevel 			=
 { {title = "六味月饼", event = 10, id = 12030254},
   {title = "七星月饼", event = 11, id = 12030255},
   {title = "八宝月饼", event = 12, id = 12030256},
   {title = "九珍月饼", event = 13, id = 12030257},
   {title = "十全月饼", event = 14, id = 12030259}}
-- x303105_g_ThawRedlevel 			= 
   -- { {title = "四级融雪丹", event = 15, id = 12050093},
	-- {title = "五级融雪丹", event = 16, id = 12050094}}
x303105_g_ColouredGlazelevel 			= 
{{title = "神天琉璃", event = 17, id = 11000702},
 {title = "天级琉璃", event = 18, id = 11000701}}
 
x303105_g_Azothlevel 			=
 { {title = "黄紫海蓝水银", event = 19, id = 11000500},
	 {title = "黄紫水火水银", event = 20, id = 11000502}, 
	 {title = "黄紫晕光水银", event = 21, id = 11000503},
	 {title = "黄紫炫彩水银", event = 22, id = 11000504}}	
	 														  
x303105_g_Gemlevel 			= 
{   {title = "高级宝石图谱", event = 23, id = 11030620},
	{title = "炼银钻图谱", event = 24, id = 11030636}}
	
x303105_g_Jewellevel 			= 
{ 	{title = "天传远征手镯", event = 25, id = 10297200},
	{title = "天传远征戒指", event = 26, id = 10287200}, 
	{title = "冥传远征手镯", event = 27, id = 10297201},
	{title = "冥传远征戒指", event = 28, id = 10287201}}
	
x303105_g_Majianglevel 			= 
{ 	{title = "掌门牌：碰碰胡(7天)礼包", event = 29, id = 12030511},
	{title = "掌门牌：清一色(7天)礼包", event = 30, id = 12030512}}
	
x303105_g_Horselevel 			= 
{ 	{title = "蛊毒蝎子降世符(50级全能)", event = 31, id = 12050262},
	{title = "赤炼螳螂降世符(70级全能)", event = 32, id = 12050263}, 
	{title = "飞爪翼龙降世符(80级全能)", event = 33, id = 12050264}}


-- 称号显示表, title显示的标题名称, event 事件的ID,id, 在这里特殊对应, 这里的id对应的是称号奖励表表的名称	
x303105_g_TitleLevel				= 
{{title = "防御称号", event = 40, id = x303105_g_AttackTitle},
 {title = "攻击称号", event = 41, id = x303105_g_DefenceTitle} }																 

-- 兑换时显示的文本, 以标题表中的event为key对应显示的内容, 称号的兑换,在没有
-- 称号的时候第一次显示的文本也在这里配置, 升级显示的文本在x303105_g_TitleText,里配置
-- [event] = "text"
x303105_g_title = 
{
-- [8] = "兑换四喜月饼要5个英勇勋章,确定兑换吗?",
 -- [9] = "兑换五仁月饼要5个英勇勋章,确定兑换吗?",
 [10] = "\t兑换#G六味月饼#W需要#R4个#W英勇勋章,确定兑换吗?",
 [11] = "\t兑换#G七星月饼#W需要#R5个#W英勇勋章,确定兑换吗?",
 [12] = "\t兑换#G八宝月饼#W,需要#R6个#W英勇勋章,确定兑换吗?",
 [13] = "\t兑换#G九珍月饼#W,需要#R7个#W英勇勋章,确定兑换吗?",
 [14] = "\t兑换#G十全月饼#W,需要#R8个#W英勇勋章,确定兑换吗?",
 -- [15] = "兑换四级融雪丹,需要12个英勇勋章,确定兑换吗?",
 -- [16] = "兑换五级融雪丹,需要24个英勇勋章,确定兑换吗?",
 [17] = "\t兑换#G神天琉璃#W,需要#R236个#W英勇勋章,确定兑换吗?",
 [18] = "\t兑换#G天级琉璃#W,需要#R236个#W英勇勋章,确定兑换吗?",
 [19] = "\t兑换#G黄紫海蓝水银#W,需要#R140个#W英勇勋章,确定兑换吗?",
 [20] = "\t兑换#G黄紫水火水银#W,需要#R100个#W英勇勋章,确定兑换吗?",
 [21] = "\t兑换#G黄紫晕光水银#W,需要#R160个#W英勇勋章,确定兑换吗?",
 [22] = "\t兑换#G黄紫炫彩水银#W,需要#R120个#W英勇勋章,确定兑换吗?",
 [23] = "\t兑换#G高级宝石图谱#W,需要#R60个#W英勇勋章,确定兑换吗?",
 [24] = "\t兑换#G炼银钻图谱#W,需要#R60个#W英勇勋章,确定兑换吗?",
 [25] = "\t兑换#G天传远征手镯#W,需要#R568个#W英勇勋章,确定兑换吗?",
 [26] = "\t兑换#G天传远征戒指#W,需要#R568个#W英勇勋章,确定兑换吗?",
 [27] = "\t兑换#G冥传远征手镯#W,需要#R1420个#W英勇勋章,确定兑换吗?",
 [28] = "\t兑换#G冥传远征戒指#W,需要#R1420个#W英勇勋章,确定兑换吗",
 [29] = "\t兑换#G掌门牌：碰碰胡(7天)礼包#W,需要#R228个#W英勇勋章,确定兑换吗?",
 [30] = "\t兑换#G掌门牌：清一色(7天)礼包#W,需要#R288个#W英勇勋章,确定兑换吗",
 [31] = "\t兑换#G蛊毒蝎子降世符(50级全能)#W,需要#R192个#W英勇勋章,确定兑换吗?",
 [32] = "\t兑换#G赤炼螳螂降世符(70级全能)#W,需要#R768个#W英勇勋章,确定兑换吗?",
 [33] = "\t兑换#G飞爪翼龙降世符(80级全能)#W,需要#R1728个#W英勇勋章,确定兑换吗?",
 [40] = "\t兑换#G坚如磐石·一#W称号（防御+30）需要#R24个#W英勇勋章，是否确认兑换？",
 [41] = "\t兑换#G势如破竹·一#W称号（攻击+30）需要#R24个#W英勇勋章，是否确认兑换？",}														  																
  
-- 称号升级显示文本 包括所有类型称号的升级显示的文本,以称号的ID为KEY对应显示的文本
x303105_g_TitleText = 
{
[129] = "\t您现在的称号是#G势如破竹·一#W称号（攻击+30），需要#R25个#W英勇勋章可升级为#G势如破竹·二#W称号（攻击+60），是否确认兑换？",
[130] = "\t您现在的称号是#G势如破竹·二#W称号（攻击+60），需要#R26个#W英勇勋章可升级为#G势如破竹·三#W称号（攻击+90），是否确认兑换？",
[131] = "\t您现在的称号是#G势如破竹·三#W称号（攻击+90），需要#R27个#W英勇勋章可升级为#G摧枯拉朽·一#W称号（攻击+120），是否确认兑换？",
[132] = "\t您现在的称号是#G摧枯拉朽·一#W称号（攻击+120），需要#R29个#W英勇勋章可升级为#G摧枯拉朽·二#W称号（攻击+180），是否确认兑换？",
[133] = "\t您现在的称号是#G摧枯拉朽·二#W称号（攻击+180），需要#R63个#W英勇勋章可升级为#G摧枯拉朽·三#W称号（攻击+240），是否确认兑换？",
[134] = "\t您现在的称号是#G摧枯拉朽·三#W称号（攻击+240），需要#R69个#W英勇勋章可升级为#G横扫千军·一#W称号（攻击+300），是否确认兑换？",
[135] = "\t您现在的称号是#G横扫千军·一#W称号（攻击+300），需要#R115个#W英勇勋章可升级为#G横扫千军·二#W称号（攻击+390），是否确认兑换？",
[136] = "\t您现在的称号是#G横扫千军·二#W称号（攻击+390），需要#R130个#W英勇勋章可升级为#G横扫千军·三#W称号（攻击+480），是否确认兑换？",
[137] = "\t您现在的称号是#G横扫千军·三#W称号（攻击+480），需要#R144个#W英勇勋章可升级为#G登峰造极#W称号（攻击+600），是否确认兑换？",
[138] = "\t您现在的称号是#G登峰造极#W称号（攻击+600），需要#R144个#W英勇勋章可以续费15日，是否确认兑换？",

[119] = "\t您现在的称号是#G坚如磐石·一#W称号（防御+30），需要#R25个#W英勇勋章可升级为#G坚如磐石·二#W称号（防御+60），是否确认兑换？",
[120] = "\t您现在的称号是#G坚如磐石·二#W称号（防御+60），需要#R26个#W英勇勋章可升级为#G坚如磐石·三#W称号（防御+90），是否确认兑换？",
[121] = "\t您现在的称号是#G坚如磐石·三#W称号（防御+90），需要#R27个#W英勇勋章可升级为#G铜墙铁壁·一#W称号（防御+120），是否确认兑换？",
[122] = "\t您现在的称号是#G铜墙铁壁·一#W称号（防御+120），需要#R29个#W英勇勋章可升级为#G铜墙铁壁·二#W称号（防御+180），是否确认兑换？",
[123] = "\t您现在的称号是#G铜墙铁壁·二#W称号（防御+180），需要#R63个#W英勇勋章可升级为#G铜墙铁壁·三#W称号（防御+240），是否确认兑换？",
[124] = "\t您现在的称号是#G铜墙铁壁·三#W称号（防御+240），需要#R69个#W英勇勋章可升级为#G坚不可摧·一#W称号（防御+300），是否确认兑换？",
[125] = "\t您现在的称号是#G坚不可摧·一#W称号（防御+300），需要#R115个#W英勇勋章可升级为#G坚不可摧·二#W称号（防御+390），是否确认兑换？",
[126] = "\t您现在的称号是#G坚不可摧·二#W称号（防御+390），需要#R130个#W英勇勋章可升级为#G坚不可摧·三#W称号（防御+480），是否确认兑换？",
[127] = "\t您现在的称号是#G坚不可摧·三#W称号（防御+480），需要#R144个#W英勇勋章可升级为#G金刚不破#W称号（防御+600），是否确认兑换？",
[128] = "\t您现在的称号是#G金刚不破#W称号（防御+600），需要#R144个#W英勇勋章可以续费15日，是否确认兑换？",

}  
  
----------------------------------------------------------------------------------------------
--枚举
----------------------------------------------------------------------------------------------
function x303105_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
 	AddQuestNumText(sceneId, x303105_g_ScriptId, "【兑换】称号", 3, x303105_g_Title)
  	AddQuestNumText(sceneId, x303105_g_ScriptId, "【兑换】月饼", 3, x303105_g_MoonCake)
 	-- AddQuestNumText(sceneId, x303105_g_ScriptId, "融雪丹类道具", 3, x303105_g_ThawRed)
 	AddQuestNumText(sceneId, x303105_g_ScriptId, "【兑换】琉璃", 3, x303105_g_ColouredGlaze)
 	AddQuestNumText(sceneId, x303105_g_ScriptId, "【兑换】图谱", 3, x303105_g_Gem)
 	AddQuestNumText(sceneId, x303105_g_ScriptId, "【兑换】水银", 3, x303105_g_Azoth)
 	AddQuestNumText(sceneId, x303105_g_ScriptId, "【兑换】首饰", 3, x303105_g_Jewel) 
 	AddQuestNumText(sceneId, x303105_g_ScriptId, "【兑换】坐骑", 3, x303105_g_Horse)	
 	AddQuestNumText(sceneId, x303105_g_ScriptId, "【兑换】掌门牌", 3, x303105_g_Majiang)

end

----------------------------------------------------------------------------------------------
--默认事件
----------------------------------------------------------------------------------------------
function x303105_ProcEventEntry(sceneId, selfId, targetId, idScript, idExt)

	x303105_g_OperateType[GetGUID(sceneId, selfId)] = 0
	if idExt == x303105_g_MoonCake then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, x303105_g_Text);
		for i, name in x303105_g_MoonCakelevel do
	  		AddQuestNumText(sceneId, x303105_g_ScriptId, name.title, 3, name.event)
		end
		AddQuestNumText(sceneId, x303105_g_ScriptId, "返回上层", 1, x303105_g_Back)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId, targetId)
	-- elseif idExt == x303105_g_ThawRed then
		-- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, x303105_g_Text)
		-- for i, name in x303105_g_ThawRedlevel do
	  		-- AddQuestNumText(sceneId, x303105_g_ScriptId, name.title, 3, name.event)
		-- end
		-- AddQuestNumText(sceneId, x303105_g_ScriptId, "返回上层", 3, x303105_g_Back)
		-- EndQuestEvent()
		-- DispatchQuestEventList(sceneId, selfId, targetId)
	elseif idExt == x303105_g_ColouredGlaze then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, x303105_g_Text)
		for i, name in x303105_g_ColouredGlazelevel do
	  		AddQuestNumText(sceneId, x303105_g_ScriptId, name.title, 3, name.event)
		end
		AddQuestNumText(sceneId, x303105_g_ScriptId, "返回上层", 1, x303105_g_Back)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId, targetId)	
		
	elseif idExt == x303105_g_Gem then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, x303105_g_Text)
		for i, name in x303105_g_Gemlevel do
	  		AddQuestNumText(sceneId, x303105_g_ScriptId, name.title, 3, name.event)
		end
		AddQuestNumText(sceneId, x303105_g_ScriptId, "返回上层", 1, x303105_g_Back)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId, targetId)	
		
	elseif idExt == x303105_g_Azoth then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, x303105_g_Text);
		for i, name in x303105_g_Azothlevel do
			AddQuestNumText(sceneId, x303105_g_ScriptId, name.title, 3, name.event)
		end
		AddQuestNumText(sceneId, x303105_g_ScriptId, "返回上层", 1, x303105_g_Back)  
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId, targetId)
		
	elseif idExt == x303105_g_Horse then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, x303105_g_Text);
		for i, name in x303105_g_Horselevel do
	  		AddQuestNumText(sceneId, x303105_g_ScriptId, name.title, 3, name.event)
	  end
	  AddQuestNumText(sceneId, x303105_g_ScriptId, "返回上层", 1, x303105_g_Back)
	  EndQuestEvent()
	  DispatchQuestEventList(sceneId, selfId, targetId)	
	  
	elseif idExt == x303105_g_Jewel then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, x303105_g_Text);
		for i, name in x303105_g_Jewellevel do
	  		AddQuestNumText(sceneId, x303105_g_ScriptId, name.title, 3, name.event)
	  end
	  AddQuestNumText(sceneId, x303105_g_ScriptId, "返回上层", 1, x303105_g_Back)
	  EndQuestEvent()
	  DispatchQuestEventList(sceneId, selfId, targetId)	
	  
	elseif idExt == x303105_g_Majiang then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, x303105_g_Text);
		for i, name in x303105_g_Majianglevel do
	  		AddQuestNumText(sceneId, x303105_g_ScriptId, name.title, 3, name.event)
	  end
	  AddQuestNumText(sceneId, x303105_g_ScriptId, "返回上层", 1, x303105_g_Back)
	  EndQuestEvent()
	  DispatchQuestEventList(sceneId, selfId, targetId)	 
	     
	elseif idExt == x303105_g_Title then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, x303105_g_Text);
		for i, name in x303105_g_TitleLevel do
	  		AddQuestNumText(sceneId, x303105_g_ScriptId, name.title, 3, name.event)
		end
		AddQuestNumText(sceneId, x303105_g_ScriptId, "返回上层", 1, x303105_g_Back)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId, targetId)
		
	elseif idExt == x303105_g_Back then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, x303105_g_ShowDemoText)
	 	EndQuestEvent()
 		x303105_ProcEnumEvent(sceneId, selfId, targetId, -1)
 		DispatchQuestEventList(sceneId, selfId, targetId)
	  -- 处理三级子菜单	
	elseif idExt >= x303105_g_MoonCakelevel[1].event and  idExt <= x303105_g_MoonCakelevel[getn(x303105_g_MoonCakelevel)].event then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【兑换】月饼#W\n")
		for i, it in x303105_g_MoonCakelevel do
			if it.event == idExt then
				-- 记录要兑换的道具ID
				x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)] = it.id
	  		AddQuestText(sceneId, x303105_g_title[idExt])
				AddQuestItemBonus(sceneId, it.id, 1)
				EndQuestEvent()
	 			DispatchQuestInfo(sceneId, selfId, targetId, x303105_g_ScriptId, -1)
	 			return
	 		end
	 	end 	
	-- elseif idExt >= x303105_g_ThawRedlevel[1].event and idExt <= x303105_g_ThawRedlevel[getn(x303105_g_ThawRedlevel)].event then
		-- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, "#Y融雪丹类领取#W\n")
		-- EndQuestEvent()
		-- for i, it in x303105_g_ThawRedlevel do
			-- if it.event == idExt then
				--记录要兑换的道具ID
				-- x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)] = it.id
				-- AddQuestText(sceneId, x303105_g_title[idExt])
	 			-- DispatchQuestInfo(sceneId, selfId, targetId, x303105_g_ScriptId, -1)
	 			-- return
			-- end
		-- end
	elseif idExt >= x303105_g_ColouredGlazelevel[1].event and idExt <= x303105_g_ColouredGlazelevel[getn(x303105_g_ColouredGlazelevel)].event then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【兑换】琉璃#W\n")
		for i, it in x303105_g_ColouredGlazelevel do
			if it.event == idExt then
				-- 记录要兑换的道具ID
				x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)] = it.id
	  		AddQuestText(sceneId, x303105_g_title[idExt])
				AddQuestItemBonus(sceneId, it.id, 1)
				EndQuestEvent()
	 			DispatchQuestInfo(sceneId, selfId, targetId, x303105_g_ScriptId, -1)	 
	 			return					
			end
		end 	
				
	elseif idExt >= x303105_g_Gemlevel[1].event and idExt <= x303105_g_Gemlevel[getn(x303105_g_Gemlevel)].event then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【兑换】图谱#W\n")
		for i, it in x303105_g_Gemlevel do
			if it.event == idExt then
				-- 记录要兑换的道具ID
				x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)] = it.id
	  		AddQuestText(sceneId, x303105_g_title[idExt])
				AddQuestItemBonus(sceneId, it.id, 1)
				EndQuestEvent()
	 			DispatchQuestInfo(sceneId, selfId, targetId, x303105_g_ScriptId, -1)	 
	 			return					
			end
		end  		
					
	elseif idExt >= x303105_g_Azothlevel[1].event and idExt <= x303105_g_Azothlevel[getn(x303105_g_Azothlevel)].event then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【兑换】水银#W\n")
		for i, it in x303105_g_Azothlevel do
			if it.event == idExt then
				-- 记录要兑换的道具ID
				x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)] = it.id
	  		AddQuestText(sceneId, x303105_g_title[idExt])
				AddQuestItemBonus(sceneId, it.id, 1)
				EndQuestEvent()
	 			DispatchQuestInfo(sceneId, selfId, targetId, x303105_g_ScriptId, -1)	 
	 			return					
			end
		end  
	
	elseif idExt >= x303105_g_Jewellevel[1].event and idExt <= x303105_g_Jewellevel[getn(x303105_g_Jewellevel)].event then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【兑换】首饰#W\n")
		for i, it in x303105_g_Jewellevel do
			if it.event == idExt then
				-- 记录要兑换的道具ID
				x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)] = it.id
	  		AddQuestText(sceneId, x303105_g_title[idExt])
				AddQuestItemBonus(sceneId, it.id, 1)
				EndQuestEvent()
	 			DispatchQuestInfo(sceneId, selfId, targetId, x303105_g_ScriptId, -1)	
	 			return 					
			end
		end
		
	elseif idExt >= x303105_g_Majianglevel[1].event and idExt <= x303105_g_Majianglevel[getn(x303105_g_Majianglevel)].event then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【兑换】掌门牌#W\n")
		for i, it in x303105_g_Majianglevel do
			if it.event == idExt then
				-- 记录要兑换的道具ID
				x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)] = it.id
	  		AddQuestText(sceneId, x303105_g_title[idExt])
				AddQuestItemBonus(sceneId, it.id, 1)
				EndQuestEvent()
	 			DispatchQuestInfo(sceneId, selfId, targetId, x303105_g_ScriptId, -1)	
	 			return 					
			end
		end 	
		
	elseif idExt >= x303105_g_Horselevel[1].event and idExt <= x303105_g_Horselevel[getn(x303105_g_Horselevel)].event then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【兑换】坐骑#W\n")
		
		for i, it in x303105_g_Horselevel do
			if it.event == idExt then
				-- 记录要兑换的道具ID
				x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)] = it.id
	  		AddQuestText(sceneId, x303105_g_title[idExt])
				AddQuestItemBonus(sceneId, it.id, 1)
				EndQuestEvent()
	 			DispatchQuestInfo(sceneId, selfId, targetId, x303105_g_ScriptId, -1)	
	 			return 					
			end
		end 
	elseif idExt >= x303105_g_TitleLevel[1].event and idExt <= x303105_g_TitleLevel[getn(x303105_g_TitleLevel)].event then
		-- 更改操作类型
		local TitleID = 0
		x303105_g_OperateType[GetGUID(sceneId, selfId)] = 1
		
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【兑换】称号#W\n")
		
		-- 检测是否有该类型的称号
		for i, it in x303105_g_TitleLevel do
			if it.event == idExt then
				
				for j, title in it.id do
					if IsHaveTitle(sceneId, selfId, title.id) > 0 then
							TitleID = title.id
					end
				end		
				
				--记录称号对应的表
				x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)] = it.id	
			
				if TitleID > 0 then
					AddQuestText(sceneId, x303105_g_TitleText[TitleID])
				else
					AddQuestText(sceneId, x303105_g_title[idExt])
				end
				EndQuestEvent()
				DispatchQuestInfo(sceneId, selfId, targetId, x303105_g_ScriptId, -1)
				return	 					
			end
		end  				 											
	end
end

----------------------------------------------------------------------------------------------
--检测接受条件
----------------------------------------------------------------------------------------------
function x303105_ProcAcceptCheck(sceneId, selfId, npcId)
	-- 获取徽章数量
	local nSrcItemNum = GetItemCount(sceneId, selfId, x303105_g_Need_SrcItemID)
	
	if x303105_g_OperateType[GetGUID(sceneId, selfId)] == 1 then
		-- 是否有该称号
		local nTitleLevel = 0
		local nIndex = 0
		-- 获取称号级别
		for i, it in x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)] do
			if IsHaveTitle(sceneId, selfId, it.id) > 0 then
					nTitleLevel = it.id
					nIndex = i
					
			end
		end
		local level = GetLevel(sceneId, selfId)
		local nlevel= floor(level/10)
		local mlevel =(nlevel+1)*10
		
		
		if level < 40 then
			Msg2Player(sceneId,selfId,"很抱歉，达到40级才可兑换或升级称号", 8, 3)
			Msg2Player(sceneId,selfId,"很抱歉，达到40级才可兑换或升级称号", 8, 2)
			return
		end
		
		if nIndex >= nlevel and nIndex <10 then
			Msg2Player(sceneId, selfId, format( "当您达到#G%d级#o时才可兑换下一级称号",mlevel), 8, 3)
			Msg2Player(sceneId, selfId, format( "当您达到#G%d级#o时才可兑换下一级称号",mlevel), 8, 2)
			return
		end		
		
		local num = 0
		if nIndex + 1 <= getn(x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)]) then
			num = x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)][nIndex + 1].neednum
		else
			num = x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)][nIndex].neednum
		end
		
		
		
		-- 检测令牌数量
		if nSrcItemNum < num then
			Msg2Player(sceneId, selfId, "你的英勇勋章数量不足，无法兑换", 8, 3)
			Msg2Player(sceneId, selfId, "你的英勇勋章数量不足，无法兑换", 8, 2)
			return
		end
		
		--删除牌子
		if 0 == DelItem(sceneId, selfId, x303105_g_Need_SrcItemID, num) then
			return
		end  	
		
		
		local nTitleID = 0
		if nTitleLevel > 0 then
			-- 删除称号
			DeleteTitle(sceneId,selfId, x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)][nIndex].id)
			if nIndex + 1 <= getn(x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)]) then
				nTitleID = x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)][nIndex + 1].id
			else
				nTitleID = x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)][nIndex].id
			end
		else
			nTitleID = x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)][1].id
		end
		
		--添加称号
		AwardTitle(sceneId,selfId, nTitleID)	
		
		WriteLog(1, format("x303105_ProcAcceptCheck 1 GetTitle OK: SceneId(%d) GUID(%d) GetTitleID(%d)", 
   			sceneId, GetGUID(sceneId, selfId), nTitleID))
   			
	else
		-- 检测是徽章数量
		for i, item in x303105_g_Need_DstItemInfo do
			if item.itemid == x303105_g_ChangeintoItemID[GetGUID(sceneId, selfId)] then
				if nSrcItemNum < item.neednum then
					Msg2Player(sceneId, selfId, "你的英勇勋章数量不足，无法兑换", 8, 3)
					Msg2Player(sceneId, selfId, "你的英勇勋章数量不足，无法兑换", 8, 2)
					return
				else 
						 --删除牌子
					 if 0 == DelItem(sceneId, selfId, x303105_g_Need_SrcItemID, item.neednum) then
					 		return
					 end
					-- 添加物品
					if EndAddItem(sceneId, selfId) > 0 then
						 BeginAddItem(sceneId)
						 AddBindItem(sceneId, item.itemid, item.num)
						 
						 WriteLog(1, format("x303105_ProcAcceptCheck 2 GetItem OK: SceneId(%d) GUID(%d) GetItemID(%d) GetItemNum(%d)", 
					 		sceneId, GetGUID(sceneId, selfId), item.itemid, item.num))
	
						 AddItemListToPlayer(sceneId,selfId)
					     
					     WriteLog(1, format("x303105_ProcAcceptCheck 3 DeleteItem OK: SceneId(%d) GUID(%d) DeleteItemID(%d) DeleteItemNum(%d)", 
    					 	sceneId, GetGUID(sceneId, selfId), x303105_g_Need_SrcItemID, item.neednum))
					else
						Msg2Player(sceneId, selfId, "背包剩余空间不足，无法得到兑换物品", 8, 3)
						return
					end
				end
			end
		end
	end
	
end


----------------------------------------------------------------------------------------------
--称号变更回调
----------------------------------------------------------------------------------------------
function x303105_OnChangeSelfTitle(sceneId, selfId, titleId, type)

	if type ~= 2 then
		return
	end
	
	--称谓降级
	for i, item in x303105_g_TitleLevel do
		for j, title in item.id do
			if title.id == titleId then
				if j ~= 1 then
					AwardTitle(sceneId, selfId, item.id[j - 1].id)
					Msg2Player(sceneId, selfId, format("由于【%s】称号过期，降级为【%s】", title.name, item.id[j - 1].name), 8, 3)
				end
				return
			end
		end
	end
end