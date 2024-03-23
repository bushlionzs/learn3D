--Const
--***********************
-------------------------

--上周排行版称号


x310601_g_ScriptId 			= 310601                  --脚本ID
x310601_g_Name              ="排行榜奖励"
x310601_g_NotEnouth         ="很遗憾，您在上周挑战赛中没有获得名次！"
x310601_g_RepeatAward       ="您已经领取过该排行榜的奖励了!"
x310601_g_SuccessAward      ="您成功领取了该排行榜的奖励!"


--
--屠龙排行榜	和氏璧排行榜	小喇叭排行榜	赤血号排行榜
--杀敌排行榜	祝家庄排行榜	战场等级排行榜	夏王墓排行榜
--放烟花排行榜	印度河排行榜	智力竞赛排行榜	轮回台排行榜
--玫瑰排行榜	景教堂排行榜	神龙宝藏排行榜	囚龙岛排行榜


x310601_g_ToplistInfo       =   {
{ClassName = "祝家庄", ClassIndex = 1,TitleClassID = 57, Desc = "祝家庄排行榜只有三番模式下才能入榜。请注意，如果副本中每环剩余怪物数过多，其成绩将不会被记入排行榜。完成此副本时间最短的前100名玩家可以登上排行榜。",    --祝家庄排行榜
           TitleInfo =
            {
                   {LevelStart=1,LevelEnd=1,TitleID = 71},
                   {LevelStart=2,LevelEnd=3,TitleID = 72},
                   {LevelStart=4,LevelEnd=20,TitleID = 73},
                   {LevelStart=21,LevelEnd=50,TitleID = 74},
                   {LevelStart=51,LevelEnd=100,TitleID = 75}
            }
       	} ,
       {ClassName = "战场等级", ClassIndex = 2,TitleClassID = 17, Desc = "战场等级排行榜记录着真正的PK强者。玩家初始战场等级为500，战场等级超过500的玩家才有资格出现在排行榜上。参与阔亦田战场每胜利一场+1，每失败一场-1。战场等级最高的前100名玩家可以登上排行榜。",   --战场等级排行榜
       TitleInfo =
             {
                    {LevelStart=1,LevelEnd=1,TitleID = 51},
                    {LevelStart=2,LevelEnd=3,TitleID = 52},
                    {LevelStart=4,LevelEnd=20,TitleID = 53},
                    {LevelStart=21,LevelEnd=50,TitleID = 54},
                    {LevelStart=51,LevelEnd=100,TitleID = 55}
             }
        } ,
        {ClassName = "夏王墓", ClassIndex = 3,TitleClassID = 63, Desc = "夏王墓排行榜只有三番模式下才能入榜。请注意，如果副本中每环剩余怪物数过多，其成绩将不会被记入排行榜。完成此副本时间最短的前100名玩家可以登上排行榜。",   --夏王墓排行榜
       TitleInfo =
             {
                    {LevelStart=1,LevelEnd=1,TitleID = 92},
                    {LevelStart=2,LevelEnd=3,TitleID = 93},
                    {LevelStart=4,LevelEnd=20,TitleID = 94},
                    {LevelStart=21,LevelEnd=50,TitleID = 95},
                    {LevelStart=51,LevelEnd=100,TitleID = 96}
             }
        } ,
        {ClassName = "放烟花", ClassIndex = 4,TitleClassID = 49, Desc = "燃放任何种类的烟花都将增长你在烟花排行榜内的分数，烂漫烟花分数最高的前100名玩家可以登上排行榜。",   --放烟花排行榜
           TitleInfo =
            {
                   {LevelStart=1,LevelEnd=1,TitleID = 46},
                   {LevelStart=2,LevelEnd=3,TitleID = 47},
                   {LevelStart=4,LevelEnd=20,TitleID = 48},
                   {LevelStart=21,LevelEnd=50,TitleID = 49},
                   {LevelStart=51,LevelEnd=100,TitleID = 50}
            }
       } ,
        {ClassName = "印度河", ClassIndex = 5,TitleClassID = 65, Desc = "印度河排行榜只有三番模式下才能入榜。请注意，如果副本中每环剩余怪物数过多，其成绩将不会被记入排行榜。完成此副本时间最短的前100名玩家可以登上排行榜。",   --印度河排行榜
           TitleInfo =
            {
                   {LevelStart=1,LevelEnd=1,TitleID = 97},
                   {LevelStart=2,LevelEnd=3,TitleID = 98},
                   {LevelStart=4,LevelEnd=20,TitleID = 99},
                   {LevelStart=21,LevelEnd=50,TitleID = 100},
                   {LevelStart=51,LevelEnd=100,TitleID = 101}
            }
       } ,
        {ClassName = "智力竞赛", ClassIndex = 6,TitleClassID = 37, Desc = "智力竞赛排行榜将累计一周每次智力竞赛的总分数，总分最高的前100名玩家可以登上排行榜。",   --智力竞赛
                TitleInfo =
                 {
                        {LevelStart=1,LevelEnd=1,TitleID = 31},
                        {LevelStart=2,LevelEnd=3,TitleID = 32},
                        {LevelStart=4,LevelEnd=20,TitleID = 33},
                        {LevelStart=21,LevelEnd=50,TitleID = 34},
                        {LevelStart=51,LevelEnd=100,TitleID = 35}
                 }
            } ,
        {ClassName = "轮回台", ClassIndex = 7,TitleClassID = 59, Desc = "轮回台排行榜记录着守卫国家轮回台的勇士。如果完成副本时剩余怪物数过多，其成绩将不会被记入排行榜。完成此副本时间最短的前100名玩家可以登上排行榜",  --轮回台
            TitleInfo =
             {
                    {LevelStart=1,LevelEnd=1,TitleID = 76},
                    {LevelStart=2,LevelEnd=3,TitleID = 77},
                    {LevelStart=4,LevelEnd=20,TitleID = 78},
                    {LevelStart=21,LevelEnd=50,TitleID = 79},
                    {LevelStart=51,LevelEnd=100,TitleID = 80}
             }
        } ,
		{ClassName = "玫瑰", ClassIndex = 8,TitleClassID = 31, Desc = "收到过玫瑰花的男女玩家将入驻玫瑰排行榜，任何玫瑰花都会增加1点恋爱指数，恋爱指数最高的前100名玩家可以登上排行榜。",    --	玫瑰排行榜
           TitleInfo =
            {
                   {LevelStart=1,LevelEnd=1,TitleID = 26},
                   {LevelStart=2,LevelEnd=3,TitleID = 27},
                   {LevelStart=4,LevelEnd=20,TitleID = 28},
                   {LevelStart=21,LevelEnd=50,TitleID = 29},
                   {LevelStart=51,LevelEnd=100,TitleID = 30}
            }
		} ,
		{ClassName = "大教堂", ClassIndex = 9,TitleClassID = 61, Desc = "大教堂排行榜只有三番模式下才能入榜。请注意，如果副本中每环剩余怪物数过多，其成绩将不会被记入排行榜。完成此副本时间最短的前100名玩家可以登上排行榜。",    --	景教堂排行榜
           TitleInfo =
            {
                   {LevelStart=1,LevelEnd=1,TitleID = 111},
                   {LevelStart=2,LevelEnd=3,TitleID = 112},
                   {LevelStart=4,LevelEnd=20,TitleID = 113},
                   {LevelStart=21,LevelEnd=50,TitleID = 114},
                   {LevelStart=51,LevelEnd=100,TitleID = 91}
            }
		} ,
        {ClassName = "神龙宝藏", ClassIndex = 10,TitleClassID = 43, Desc = "神龙宝藏排行榜会记录下寻宝数量最多的探宝家，每使用一张神龙藏宝图挖掘宝藏都将被记录，挖宝次数最高的前100名玩家可以登上排行榜。",  		--神龙宝藏排行榜 

           TitleInfo =
            {
                   {LevelStart=1,LevelEnd=1,TitleID = 36},
                   {LevelStart=2,LevelEnd=3,TitleID = 37},
                   {LevelStart=4,LevelEnd=20,TitleID = 38},
                   {LevelStart=21,LevelEnd=50,TitleID = 39},
                   {LevelStart=51,LevelEnd=100,TitleID = 40}
            }
       } ,
       
	    {ClassName = "囚龙岛", ClassIndex = 11,TitleClassID = 51, Desc = "囚龙岛排行榜只有三番模式下才能入榜。请注意，如果副本中每环剩余怪物数过多，其成绩将不会被记入排行榜。完成此副本时间最短的前100名玩家可以登上排行榜。", --囚龙岛排行榜
                TitleInfo =
                 {
                        {LevelStart=1,LevelEnd=1,TitleID = 56},
                        {LevelStart=2,LevelEnd=3,TitleID = 57},
                        {LevelStart=4,LevelEnd=20,TitleID = 58},
                        {LevelStart=21,LevelEnd=50,TitleID = 59},
                        {LevelStart=51,LevelEnd=100,TitleID = 60}
                 }
            } ,
	    
		{ClassName = "屠龙", ClassIndex = 12,TitleClassID = 45, Desc = "屠龙排行榜会记录下真正的屠龙勇士，每杀死一只天龙之魂都将增加你的屠龙数，屠龙数最高的前100名玩家可以登上排行榜。",   --屠龙排行榜
		
           TitleInfo =
            {
                   {LevelStart=1,LevelEnd=1,TitleID = 41},
                   {LevelStart=2,LevelEnd=3,TitleID = 42},
                   {LevelStart=4,LevelEnd=20,TitleID = 43},
                   {LevelStart=21,LevelEnd=50,TitleID = 44},
                   {LevelStart=51,LevelEnd=100,TitleID = 45}
            }
       } ,     
       {ClassName = "和氏璧", ClassIndex = 13,TitleClassID = 53, Desc = "和氏璧排行榜只有三番模式下才能入榜。请注意，如果副本中每环剩余怪物数过多，其成绩将不会被记入排行榜。完成此副本时间最短的前100名玩家可以登上排行榜。",   --和氏璧排行榜
           TitleInfo =
            {
                   {LevelStart=1,LevelEnd=1,TitleID = 61},
                   {LevelStart=2,LevelEnd=3,TitleID = 62},
                   {LevelStart=4,LevelEnd=20,TitleID = 63},
                   {LevelStart=21,LevelEnd=50,TitleID = 64},
                   {LevelStart=51,LevelEnd=100,TitleID = 65}
            }
       } ,
       {ClassName = "小喇叭", ClassIndex = 14,TitleClassID = 47,  --"用小喇叭尽情的表达您的高谈阔论吧！您的声音将传遍整个世界！使用小喇叭广播次数最多的前100名玩家可以登上排行榜。",
                TitleInfo =
                 {
                        {LevelStart=1,LevelEnd=1,TitleID = 102},
                        {LevelStart=2,LevelEnd=3,TitleID = 103},
                        {LevelStart=4,LevelEnd=20,TitleID = 104},
                        {LevelStart=21,LevelEnd=50,TitleID = 105},
                        {LevelStart=51,LevelEnd=100,TitleID = 106}
                 }
            } ,
       {ClassName = "赤血号", ClassIndex = 15,TitleClassID = 55, Desc = "赤血号排行榜只有三番模式下才能入榜。请注意，如果副本中每环剩余怪物数过多，其成绩将不会被记入排行榜。完成此副本时间最短的前100名的玩家可以登上排行榜。",   --赤血号排行榜

           TitleInfo =
            {
                   {LevelStart=1,LevelEnd=1,TitleID = 66},
                   {LevelStart=2,LevelEnd=3,TitleID = 67},
                   {LevelStart=4,LevelEnd=20,TitleID = 68},
                   {LevelStart=21,LevelEnd=50,TitleID = 69},
                   {LevelStart=51,LevelEnd=100,TitleID = 70}
            }
       } ,
        {ClassName = "杀敌", ClassIndex = 16,TitleClassID = 15, Desc = "杀敌排行榜记录着异国有效杀敌数最多的勇士们。杀死不低于自己等级20级以上的异国玩家才能增加杀敌数，如果2小时内杀死同一个异国玩家超过10次，则再次杀死该玩家将不再增加杀敌数。有效杀敌数最多的前100名玩家可以登上排行榜。",  --杀敌
            TitleInfo =
             {
                    {LevelStart=1,LevelEnd=1,TitleID = 21},
                    {LevelStart=2,LevelEnd=3,TitleID = 22},
                    {LevelStart=4,LevelEnd=20,TitleID = 23},
                    {LevelStart=21,LevelEnd=50,TitleID = 24},
                    {LevelStart=51,LevelEnd=100,TitleID = 25}
             }
        },
	 }
    

                
function x310601_ProcEnumEvent(sceneId, selfId, NPCId)

    local WeekDay = GetWeek()
    local Min = GetMinOfDay()
    if(WeekDay < 1 or WeekDay > 6) then
        return
    end
    if(WeekDay == 1 and Min < 60 ) then
        return
    end
    if(WeekDay == 6 and Min > 60*23 ) then
        return
    end

	if GetUpdateDBBeforeToggle()==1 or GetUpdateDBAfterToggle()==1 then
		return
	end	
    --local dayTime = GetDayTime()
    --if(dayTime < 10031) then
		--return
   	--end	
   
    local nTitleIndex = x310601_GetTitleIndex()
        
	AddQuestNumText(sceneId,x310601_g_ScriptId,"领取上周挑战赛奖励\r",3,100)
end

--囚龙岛排行榜  和氏璧排行榜 赤血号排行榜 祝家庄排行榜 战场等级排行榜  轮回台
--  1               5             7             9            10          11
--  GetToplistRankEx

function x310601_IsMultiChampion(nTitleIndex)
	--local MultiChampionTab = {1,5,7,9,10,11}
	if(nTitleIndex == 1 or nTitleIndex == 3 or nTitleIndex == 5 or nTitleIndex == 7 or nTitleIndex == 9 or nTitleIndex == 11 or nTitleIndex == 13 or nTitleIndex == 15) then
		return 1
	end
	return 0
end

function x310601_GetTitleID(sceneId, selfId)	--
	local nTitleIndex = x310601_GetTitleIndex()
    local nTitleType = x310601_g_ToplistInfo[nTitleIndex].TitleClassID
    --local nTitleRank = GetToplistRank(sceneId,selfId,nTitleType)
	local nTitleRank = 1
	if x310601_IsMultiChampion(nTitleIndex) == 1 then
		nTitleRank = GetToplistRankEx(sceneId,selfId,nTitleType) + 1
	else	
		nTitleRank = GetToplistRank(sceneId,selfId,nTitleType) + 1
	end
    local TitleInfo = x310601_g_ToplistInfo[nTitleIndex].TitleInfo
    for i, s in TitleInfo do
        if nTitleRank >= s.LevelStart and nTitleRank <= s.LevelEnd then
            return s.TitleID
        end
    end
    return -1
end

function x310601_GetTitleIndex()	--
	local nWeekIndex = GetWeekIndex() --since 2010-01-25
	local nTitleIndex = mod(nWeekIndex,16)
    if nTitleIndex == 0 then
        nTitleIndex = 16
    end
	nTitleIndex = nTitleIndex -1	--上周的
	if nTitleIndex == 0 then
		nTitleIndex = 16
	end

    return nTitleIndex
end

function x310601_ProcEventEntry(sceneId, selfId, NPCId, scriptid, index)	--点击该任务后执行此脚本
	local titleIndex = x310601_GetTitleIndex()
	--x310601_g_ToplistInfo[nTitleIndex].TitleClassID
    local titleID = x310601_GetTitleID(sceneId, selfId, NPCId)

    BeginQuestEvent(sceneId)
    
    local TitleDesc;
	local nLevel = GetLevel(sceneId, selfId)
	local nExp = nLevel * 240000
    local sex = GetSex(sceneId,selfId)
    local nTitleClassID = x310601_g_ToplistInfo[titleIndex].TitleClassID
	local TitleInfo = x310601_g_ToplistInfo[titleIndex].TitleInfo
	local TitleID = TitleInfo[1].TitleID
    local TitleBuffName = GetImpactNameByTitleID(TitleID)
	local TitleName = GetTitleNameByTitleID(TitleID, sex)
	local nTitleIndex = x310601_GetTitleIndex()
    local nTitleType = x310601_g_ToplistInfo[nTitleIndex].TitleClassID

	local nTitleRank = 1
	if x310601_IsMultiChampion(nTitleIndex) == 1 then
		nTitleRank = GetToplistRankEx(sceneId,selfId,nTitleType) + 1
	else	
		nTitleRank = GetToplistRank(sceneId,selfId,nTitleType) + 1
	end

   if nTitleRank <= 100 and nTitleRank > 0 then
    TitleDesc = "#Y领取上周赛事奖励\r\n\r\n#W上周进行的是#G"..x310601_g_ToplistInfo[titleIndex].ClassName.."挑战赛#W，目前正在颁奖。\r\n#W你在上周的比赛中获得了第#G"..nTitleRank.."#W名。\n您将会获得#G"..nExp.."#W点经验奖励，和以下额外奖励：\n\r\n"
   else
    TitleDesc = "#Y领取上周赛事奖励\r\n\r\n#W上周进行的是#G"..x310601_g_ToplistInfo[titleIndex].ClassName.."挑战赛#W，目前正在颁奖。\r\n#W你在上周的比赛中#G没有获得名次#W。\n如果您在上周比赛中取得名次将会获得#G"..nExp.."#W点经验奖励，和以下额外奖励：\n\r\n"
   end
    TitleDesc = TitleDesc.."#Y".."名次    ".."称号及属性".."\n"
    TitleDesc = TitleDesc.."#W".."1       #G"..TitleName.."#W："..TitleBuffName.."\r\n"

	TitleID = TitleInfo[2].TitleID
    TitleBuffName = GetImpactNameByTitleID(TitleID)
	TitleName = GetTitleNameByTitleID(TitleID, sex)
    TitleDesc = TitleDesc.."2~3     #G"..TitleName.."#W："..TitleBuffName.."\r\n"

	TitleID = TitleInfo[3].TitleID
    TitleBuffName = GetImpactNameByTitleID(TitleID)
	TitleName = GetTitleNameByTitleID(TitleID, sex)
    TitleDesc = TitleDesc.."4~20    #G"..TitleName.."#W："..TitleBuffName.."\r\n"

    TitleID = TitleInfo[4].TitleID
    TitleBuffName = GetImpactNameByTitleID(TitleID)
	TitleName = GetTitleNameByTitleID(TitleID, sex)
    TitleDesc = TitleDesc.."21~50   #G"..TitleName.."#W："..TitleBuffName.."\r\n"
    
    TitleID = TitleInfo[5].TitleID
    TitleBuffName = GetImpactNameByTitleID(TitleID)
	TitleName = GetTitleNameByTitleID(TitleID, sex)
    TitleDesc = TitleDesc.."51~100  #G"..TitleName.."#W："..TitleBuffName
    
    AddQuestText(sceneId,"#Y"..TitleDesc)
     ---AddQuestText(sceneId,"#Y"..TitleBuffName)
    EndQuestEvent()
    DispatchQuestInfo(sceneId, selfId, NPCId, x310601_g_ScriptId,-1);
end


function x310601_ProcAccept( sceneId, selfId, targetId, MissionId, index )
    local titleIndex = x310601_GetTitleIndex()
    local titleID = x310601_GetTitleID(sceneId, selfId)
    --print(titleID)
    --titleID = 57
    --print(titleID)

    
    
    if titleID < 0 then
        --print("2")
		Msg2Player(sceneId,selfId,x310601_g_NotEnouth,8,2)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId,x310601_g_NotEnouth);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
    elseif IsTitleActive(sceneId, selfId, titleID) > 0 then
        --print("1")
        Msg2Player(sceneId,selfId,x310601_g_RepeatAward,8,2)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId,x310601_g_RepeatAward);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
	else
         --print("3")
        AwardTitle(sceneId, selfId, titleID)
        local level = GetLevel(sceneId, selfId)
        local exp = level * 240000
        AddExp(sceneId, selfId, exp)  
        
		Msg2Player(sceneId,selfId,x310601_g_SuccessAward,8,2)

		local sex = GetSex(sceneId,selfId)
		local TitleName = GetTitleNameByTitleID(titleID, sex)
		local msg = "您获得了"..TitleName.."称号。"
		Msg2Player(sceneId,selfId,msg,8,2)
		msg = "您获得了"..exp.."点经验。"
		Msg2Player(sceneId,selfId,msg,8,2)
		   
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId,x310601_g_SuccessAward);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
    end

    return 1
end
function x310601_ProcAcceptCheck( sceneId, selfId, targetId, MissionId, index )
    return 1
end
function x310601_ProcQuestAccept( sceneId, selfId, targetId, MissionId, index )
    
end

	