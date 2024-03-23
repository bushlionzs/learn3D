-- 职业转换

-- PROFESSION_WUSHI	        = 0,    武士
-- PROFESSION_JIANXIA	    = 1,    剑侠
-- PROFESSION_QISHE	        = 2,    骑射
-- PROFESSION_HUOQIANG	    = 3,    火枪
-- PROFESSION_XIANZHI	    = 4,    先知
-- PROFESSION_SAMAN	        = 5,    萨满
-- PROFESSION_SHIZIJUN	    = 6,    十字军
-- PROFESSION_SHENGHUOSHI   = 7,    圣火使
-- PROFESSION_CIKE 	        = 8,    刺客
-- PROFESSION_JINWEIJUN     = 9,    禁卫军
-- PROFESSION_YINXIUSHI     = 10,   隐修士
-- PROFESSION_LAMA 	        = 11,   僧侣

-- 配置表
x570044_g_ChangeConfiguration   = {
                                    { professionId1 = 0, professionId2 = 6, 
                                      cost = { 
                                        { minLevel = 20, maxLevel =  35, itemId = 12250001, count = 1, moneyCoff = 1000 }, 
                                        { minLevel = 35, maxLevel = 160, itemId = 12250001, count = 1, moneyCoff = 1000 }, 
                                      }
                                    }, 
                                    { professionId1 = 1, professionId2 = 7, 
                                      cost = { 
                                        { minLevel = 20, maxLevel =  35, itemId = 12250001, count = 1, moneyCoff = 1000 }, 
                                        { minLevel = 35, maxLevel = 160, itemId = 12250001, count = 1, moneyCoff = 1000 }, 
                                      }
                                    }, 
                                    { professionId1 = 2, professionId2 = 8, 
                                      cost = { 
                                        { minLevel = 20, maxLevel =  35, itemId = 12250001, count = 1, moneyCoff = 1000 }, 
                                        { minLevel = 35, maxLevel = 160, itemId = 12250001, count = 1, moneyCoff = 1000 }, 
                                      }
                                    }, 
                                    { professionId1 = 3, professionId2 = 9, 
                                      cost = { 
                                        { minLevel = 20, maxLevel =  35, itemId = 12250001, count = 1, moneyCoff = 1000 }, 
                                        { minLevel = 35, maxLevel = 160, itemId = 12250001, count = 1, moneyCoff = 1000 }, 
                                      }
                                    }, 
                                    { professionId1 = 4, professionId2 = 10, 
                                      cost = { 
                                        { minLevel = 20, maxLevel =  35, itemId = 12250001, count = 1, moneyCoff = 1000 }, 
                                        { minLevel = 35, maxLevel = 160, itemId = 12250001, count = 1, moneyCoff = 1000 }, 
                                      }
                                    }, 
                                    { professionId1 = 5, professionId2 = 11, 
                                      cost = { 
                                        { minLevel = 20, maxLevel =  35, itemId = 12250001, count = 1, moneyCoff = 1000 }, 
                                        { minLevel = 35, maxLevel = 160, itemId = 12250001, count = 1, moneyCoff = 1000 }, 
                                      }
                                    }, 
}
-- 职业转换后清除原有被动技能列表，数组一维索引是当前职业转职前的职业ID，每次登录后清除原职业的被动技能
x570044_g_DispelSkillList           = {
                                        { 1341, 1342, 1343, 1344, 1345, 1346, 1347, 1348, 1349, 1350, 1351, 1352, 1353, 1354, 1355, 1356, 1357, 1358, 1359, 1360, 1361, 1362, 1363, 1364, 1365, 1366, 1367, 1368, 1369, 1370, 1371, 1372, 1373, 1374, 1375, 1376, 1377, 1378, 1379, 1380 }, 
                                        { 2121, 2122, 2123, 2124, 2125, 2126, 2127, 2128, 2129, 2130, 2131, 2132, 2133, 2134, 2135, 2136, 2137, 2138, 2139, 2140, 2141, 2142, 2143, 2144, 2145, 2146, 2147, 2148, 2149, 2150 }, 
                                        { 3131, 3132, 3133, 3134, 3135, 3136, 3137, 3138, 3139, 3140, 3141, 3142, 3143, 3144, 3145, 3146, 3147, 3148, 3149, 3150, 3151, 3152, 3153, 3154, 3155, 3156, 3157, 3158, 3159, 3160 }, 
                                        { 4121, 4122, 4123, 4124, 4125, 4126, 4127, 4128, 4129, 4130, 4131, 4132, 4133, 4134, 4135, 4136, 4137, 4138, 4139, 4140, 4141, 4142, 4143, 4144, 4145, 4146, 4147, 4148, 4149, 4150 }, 
                                        { 5131, 5132, 5133, 5134, 5135, 5136, 5137, 5138, 5139, 5140, 5141, 5142, 5143, 5144, 5145, 5146, 5147, 5148, 5149, 5150, 5151, 5152, 5153, 5154, 5155, 5156, 5157, 5158, 5159, 5160 }, 
                                        { 6201, 6202, 6203, 6204, 6205, 6206, 6207, 6208, 6209, 6210, 6131, 6132, 6133, 6134, 6135, 6136, 6137, 6138, 6139, 6140, 6141, 6142, 6143, 6144, 6145, 6146, 6147, 6148, 6149, 6150, 6151, 6152, 6153, 6154, 6155, 6156, 6157, 6158, 6159, 6160 }, 
                                        { 17150, 17151, 17152, 17153, 17154, 17155, 17156, 17157, 17158, 17159, 17160, 17161, 17162, 17163, 17164, 17165, 17166, 17167, 17168, 17169, 17170, 17171, 17172, 17173, 17174, 17175, 17176, 17177, 17178, 17179, 17180, 17181, 17182, 17183, 17184, 17185, 17186, 17187, 17188, 17189 }, 
                                        { 18160, 18161, 18162, 18163, 18164, 18165, 18166, 18167, 18168, 18169, 18170, 18171, 18172, 18173, 18174, 18175, 18176, 18177, 18178, 18179, 18180, 18181, 18182, 18183, 18184, 18185, 18186, 18187, 18188, 18189 }, 
                                        { 19120, 19121, 19122, 19123, 19124, 19125, 19126, 19127, 19128, 19129, 19130, 19131, 19132, 19133, 19134, 19135, 19136, 19137, 19138, 19139, 19140, 19141, 19142, 19143, 19144, 19145, 19146, 19147, 19148, 19149 }, 
                                        { 20120, 20121, 20122, 20123, 20124, 20125, 20126, 20127, 20128, 20129, 20130, 20131, 20132, 20133, 20134, 20135, 20136, 20137, 20138, 20139, 20140, 20141, 20142, 20143, 20144, 20145, 20146, 20147, 20148, 20149 }, 
                                        { 21110, 21111, 21112, 21113, 21114, 21115, 21116, 21117, 21118, 21119, 21120, 21121, 21122, 21123, 21124, 21125, 21126, 21127, 21128, 21129, 21130, 21131, 21132, 21133, 21134, 21135, 21136, 21137, 21138, 21139 }, 
                                        { 22000, 22001, 22002, 22003, 22004, 22005, 22006, 22007, 22008, 22009, 22010, 22011, 22012, 22013, 22014, 22015, 22016, 22017, 22018, 22019, 22180, 22181, 22182, 22183, 22184, 22185, 22186, 22187, 22188, 22189, 22190, 22191, 22192, 22193, 22194, 22195, 22196, 22197, 22198, 22199, 22200, 22201, 22202, 22203, 22204, 22205, 22206, 22207, 22208, 22209 }, 
}

--脚本号
x570044_g_ScriptId = 570044

function x570044_OnChangeProfession( sceneId, selfId, NPCId)
    local level = GetLevel( sceneId, selfId)
    -- 根据职业找到转换需要的物品和数量以及花费值
    local myProfession = GetZhiye( sceneId, selfId)
    local targetProf = nil
    local changeItem = nil
    for i, item in x570044_g_ChangeConfiguration do
        if myProfession == item.professionId1 or myProfession == item.professionId2 then
            if myProfession == item.professionId1 then
                targetProf = item.professionId2
            else
                targetProf = item.professionId1
            end
            for j, subitem in item.cost do
                if level >= subitem.minLevel and level < subitem.maxLevel then
                    changeItem = subitem
                    break
                end
            end
            break
        end
    end

    if changeItem == nil then
        return
    end

	local money = changeItem.moneyCoff * level
	if GetMoney( sceneId, selfId, 1) < money and GetMoney( sceneId, selfId, 0) < money then
        Msg2Player( sceneId, selfId, "你的银卡或现银不足", 8, 3)
		return
	end
    if GetItemCountInBag( sceneId, selfId, changeItem.itemId) < changeItem.count then
        Msg2Player( sceneId, selfId, format( "你没有@item_%d", changeItem.itemId), 8, 3)
        return
    end

    -- 扣钱
    local mtype = 1
    if GetSillerMode( sceneId, selfId ) == 1 then
        if CostMoney( sceneId, selfId, 0, money) ~= 1 then
            if CostMoney(sceneId, selfId, 1, money) ~= 1 then
                Msg2Player( sceneId, selfId, "扣费失败，请稍候再试", 8, 3)
                return
            end
            mtype = 1
        end
        mtype = 0
    else
        if CostMoney( sceneId, selfId, 1, money) ~= 1 then
            if CostMoney(sceneId, selfId, 0, money) ~= 1 then
                Msg2Player( sceneId, selfId, "扣费失败，请稍候再试", 8, 3)
                return
            end
            mtype = 0
        end
        mtype = 1
    end

    -- 删除物品
    if DelItem( sceneId, selfId, changeItem.itemId, changeItem.count) == 0 then
        Msg2Player( sceneId, selfId, "提交物品失败，请稍候再试", 8, 3)
        AddMoney( sceneId, selfId, mtype, money)
        return
    end

    local profession = GetZhiye( sceneId, selfId) + 1
    for i, item in x570044_g_DispelSkillList[ profession] do
        DispelSpecificImpact( sceneId, selfId, item, 1)
    end

    -- 职业转换
    ChangeProfession( sceneId, selfId)

	BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y职业转换" )
        AddQuestText( sceneId, "转换成功。" )
	EndQuestEvent()
	DispatchQuestEventList( sceneId, selfId, NPCId)

    -- 给一个无敌Buff，避免在返回期间被杀
    SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, 9801, 200)

    -- 把玩家返回登录界面
    KickPlayer( sceneId, selfId, 2)
    -- 设置T人安全时间
    SetKickTime( sceneId, selfId, 10000)
end

function x570044_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
    AddQuestNumText( sceneId, x570044_g_ScriptId, "职业转换", 3, 1)
end

function x570044_ProcEventEntry( sceneId, selfId, NPCId, idScript, buttonIdx)
    local level = GetLevel( sceneId, selfId)
    if level < 70 then
        Msg2Player( sceneId, selfId, "70级以上才能进行职业转换", 8, 3)
        return
    end

    if buttonIdx == 1 then
        -- 根据职业找到转换需要的物品和数量以及花费值
        local myProfession = GetZhiye( sceneId, selfId)
        for i, item in x570044_g_ChangeConfiguration do
            if myProfession == item.professionId1 or myProfession == item.professionId2 then
                for j, subitem in item.cost do
                    if level >= subitem.minLevel and level < subitem.maxLevel then
                        OpenChangeProfessionUI( sceneId, selfId, NPCId, idScript, subitem.itemId, subitem.count, subitem.moneyCoff)
                        break
                    end
                end
                break
            end
        end
    end
end

