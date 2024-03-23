--MisDescBegin 
x300928_g_ScriptId 					= 300928
x300928_g_MissionId 				= 1372
x300928_g_MissionName				= "【帮会】帮会贡品"
x300928_g_MissionInfo				= "任务信息"
x300928_g_MissionTarget				= "  收集@item_%d#W(%d/1)"
x300928_g_MissionDescription        = "\t帮会贡品任务，分为#G寻物#W和#G送信#W两种，您只需要按照帮会任务发布人的要求完成任务，就可以获得#G经验#W和#G帮贡#W的奖励。"
x300928_g_MissionTips               = "如果想要了解本任务的细节，请点击帮会贡品任务说明按钮。"
x300928_g_MissionBook               = "上交指定的物品就能完成此任务，如果没有可以考虑向别的玩家收购。"
--MisDescEnd

x300928_g_strFinishAll              = "你今天不能再领取【帮会】帮会贡品任务了"
x300928_g_strTip                    = "#c00FF00小提示:"
x300928_g_strMissionTip             = "#c00FF00如果想要了解本任务的细节，请点击帮会任务说明按钮。"
x300928_g_strAddMissionFail         = "你接受的任务太多了，添加新任务失败"
x300928_g_strMissionComplete        = "\t太好了，你果然做的干净利索。"
x300928_g_strMissionFinished        = "完成【帮会】帮会贡品(%d/10)"
x300928_g_strCommitItemFail         = "提交物品失败，交任务失败"
x300928_g_strObtainXP               = "获得#R%d#cffcc00点经验。"
x300928_g_strObtainGP               = "获得#R%d#cffcc00点帮贡。"
x300928_g_MissionTarget1			= "  找到@npc_%d\n  找到@npc_%d\n  找到@npc_%d"
x300928_g_MissionContinue			= "\t请尽快完成交给你的事情。"

-- 接任务最低等级
x300928_g_MinLevel                  = 20
-- 每天最大环数
x300928_g_MaxCircle                 = 10
x300928_MP_INDEX1			        = 1         -- 
x300928_MP_INDEX2					= 2         -- 
x300928_MP_INDEX3					= 3         -- 
x300928_MP_INDEX4					= 4         -- 
x300928_MP_INDEX5					= 5         -- 
x300928_MP_INDEX6					= 6         -- 
x300928_MP_FINISH                   = 7         -- 玩家接任务时的等级
x300928_MP_ISCOMPLETE				= 0	        -- 代表完成 0未完成， 1完成
-- 交任务NPC的GUID
x300928_g_MissionNPC                = 132020
-- 寻物配置表
x300928_g_LookforItemTable          = {
                                        { minLevel = 20, maxLevel = 40, 
                                            item = { 
                                                     11000200, 
                                                     11020001, 
                                                     11020002, 
                                                     11030001, 
                                                     12010001, 
                                                     12010100, 
                                                     12010001, 
                                                     12010300, 
                                                     11990201, 
                                                     11050001, 
                                                    }, 
                                            targets = {
                                                    { npcId = 132156, Dialog = "\t这点小事情也要来找我……\n\t好吧!一会我就带人去看看。"	}, --1
                                                    { npcId = 132161, Dialog = "\t没有问题，我的朋友，很高兴能帮上你们的忙。"	}, --2
                                                    { npcId = 132006, Dialog = "\t这个……最近我已经忙的焦头烂额了。\n\t这样吧，我处理完这事就过去。"	}, --3
                                                    { npcId = 132036, Dialog = "\t我很乐意帮忙~不过，请稍等，小女子梳妆完毕，自会前往。"	}, --4
                                                    { npcId = 132160, Dialog = "\t你们要大采购么？要不要我带上货单？"	}, --5
                                                    { npcId = 132025, Dialog = "\t有什么需要我帮助的吗？好吧，我这就动身。"	}, --6
                                                    { npcId = 132023, Dialog = "\t我会去的……不过，要等我的徒弟回来的时候。"	}, --7
                                                },
                                        }, 
                                        { minLevel = 40, maxLevel = 60, 
                                            item = { 
                                                     11000200, 
                                                     11020001, 
                                                     11020002, 
                                                     11030001, 
                                                     12010001, 
                                                     12010100, 
                                                     12010001, 
                                                     12010300, 
                                                     11990202, 
                                                     11050001, 
                                                    }, 
                                            targets = {
                                                    { npcId = 132066, Dialog = "\t郝令让你来的？好吧，我正想去找他，上次他从我这里订购的货物，到现在帐也没付清！"	}, 
                                                    { npcId = 132076, Dialog = "\t哦，找我么？难道有淘汰下来的装备？！好我这就过去。"	}, 
                                                    { npcId = 132063, Dialog = "\t押运官的职责让我不能轻易离开，不过我可以让那些来押运的家伙帮点小忙……"	}, 
                                                    { npcId = 132031, Dialog = "\t帮忙？有报酬么？一会我派个伙计去看看，没有赚头的生意我从来不做！"	}, 
                                                    { npcId = 132072, Dialog = "\t啊？为什么要来找我？"	}, 
                                                    { npcId = 132074, Dialog = "\t这事情……我要先和我妻子说一下，不过我相信她一定会同意的。"	}, 
                                                    { npcId = 132035, Dialog = "\t好，你们帮的人都是我的老顾客，我一定准时到。"	}, 
                                                },
                                        }, 
                                        { minLevel = 60, maxLevel = 160, 
                                            item = { 
                                                     11000201, 
                                                     11020001, 
                                                     11020002, 
                                                     11030001, 
                                                     12010001, 
                                                     12010100, 
                                                     12010001, 
                                                     12010300, 
                                                     11990203, 
                                                     11050001, 
                                                    }, 
                                            targets = {
                                                    { npcId = 132029, Dialog = "\t好的好的，等我把手头上这几件装备铭刻了就过去。"	}, 
                                                    { npcId = 132032, Dialog = "\t很高兴能为贵帮帮忙，我准备一下马上就到。"	}, 
                                                    { npcId = 132080, Dialog = "\t需要我的帮助？没问题！我可是出了名的好说话。"	}, 
                                                    { npcId = 132073, Dialog = "\t很高兴能为贵帮进些微薄之力，我准备一下马上就到。"	}, 
                                                    { npcId = 132065, Dialog = "\t我从不问江湖事，不过你们帮主的面子我还是要给的。\n\t好吧，你先回去，我随后就到。"	}, 
                                                    { npcId = 132030, Dialog = "\t有人找帮忙？等我收拾一下，一会就去。"	}
                                                },
                                        }, 
}
-- 经验奖励系数
x300928_g_xpCoefficient             = {
                                         41,
                                         81,
                                        123,
                                        164,
                                        204,
                                        246,
                                        287,
                                        327,
                                        369,
                                        410,
}

function x300928_ProcEnumEvent( sceneId, selfId, NPCId)
    local level = GetLevel( sceneId, selfId)

    if level < x300928_g_MinLevel then
        return
    end

    if GetGuildID( sceneId, selfId) < 0 then
        return
    end

    local state = GetQuestStateNM( sceneId, selfId, NPCId, x300928_g_MissionId)
    AddQuestNumText( sceneId, x300928_g_MissionId, x300928_g_MissionName, state, 1)
end

function x300928_ProcEventEntry( sceneId, selfId, NPCId, MissionId, iClickIndex)
	
	local level = GetLevel( sceneId, selfId)

    if level < x300928_g_MinLevel then
        return
    end

    local guildId = GetGuildID( sceneId, selfId)
    if guildId < 0 then
        Msg2Player( sceneId, selfId, "你尚未加入任何帮会，不能领取【帮会】帮会贡品", 8, 3)
        return
    end

    if IsHaveQuest( sceneId, selfId, x300928_g_MissionId) == 0 then
        -- 未接任务
        local curDay = GetDayOfYear()

		if x300928_GetMD( sceneId, selfId, MD_BANGHUI_CIRCLE) == 0 then
			x300928_SetMD( sceneId, selfId, MD_BANGHUI_CIRCLE, 1)
		end
		
        if x300928_GetMD( sceneId, selfId, MD_BANGHUI_CIRCLE) > x300928_g_MaxCircle then
            if curDay == x300928_GetMD( sceneId, selfId, MD_BANGHUI_LASTDAY) then
                if x300928_GetMD( sceneId, selfId, MD_BANGHUI_TIMES) >= x300928_g_MaxCircle then
                    Msg2Player( sceneId, selfId, x300928_g_strFinishAll, 8, 3)
                    return
                else
                    x300928_SetMD( sceneId, selfId, MD_BANGHUI_CIRCLE, 1)
                    x300928_DispatchMissionInfo( sceneId, selfId, NPCId)
                end
            else
                x300928_SetMD( sceneId, selfId, MD_BANGHUI_LASTDAY, curDay)
                x300928_SetMD( sceneId, selfId, MD_BANGHUI_CIRCLE, 1)
                x300928_SetMD( sceneId, selfId, MD_BANGHUI_TIMES, 0)
            end
        else
            if x300928_GetMD( sceneId, selfId, MD_BANGHUI_TIMES) >= x300928_g_MaxCircle then
				if curDay == x300928_GetMD( sceneId, selfId, MD_BANGHUI_LASTDAY) then
					if x300928_GetMD( sceneId, selfId, MD_BANGHUI_TIMES) >= x300928_g_MaxCircle then
						Msg2Player( sceneId, selfId, x300928_g_strFinishAll, 8, 3)
						return
					else
						x300928_SetMD( sceneId, selfId, MD_BANGHUI_CIRCLE, 1)
						x300928_DispatchMissionInfo( sceneId, selfId, NPCId)
					end
				else
					x300928_SetMD( sceneId, selfId, MD_BANGHUI_LASTDAY, curDay)
					x300928_SetMD( sceneId, selfId, MD_BANGHUI_CIRCLE, 1)
					x300928_SetMD( sceneId, selfId, MD_BANGHUI_TIMES, 0)
				end
            else
                x300928_DispatchMissionInfo( sceneId, selfId, NPCId)
            end
        end
    else
        -- 已接任务
        local misIndex = GetQuestIndexByID( sceneId, selfId, x300928_g_MissionId)
        local mp0 = GetQuestParam( sceneId, selfId, misIndex, x300928_MP_ISCOMPLETE)
        local mp7 = GetQuestParam( sceneId, selfId, misIndex, x300928_MP_FINISH)
        if mp0 == 1 and mp7 == 1 then
            x300928_DispatchMissionComplete( sceneId, selfId, NPCId)
        else
            x300928_DispatchMissionContinue( sceneId, selfId, NPCId)
        end
    end
end

-- 显示任务信息
function x300928_DispatchMissionInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)
		--任务信息
		AddQuestText( sceneId, "#Y"..x300928_g_MissionName)
		AddQuestText( sceneId, x300928_g_MissionDescription)
		AddQuestText( sceneId, " " )

		--任务奖励信息
        local level = GetLevel( sceneId, selfId)
        local circle = x300928_GetMD( sceneId, selfId, MD_BANGHUI_CIRCLE)
        local xp = level * x300928_g_xpCoefficient[ circle]
        -- local money, shengw = x300928_GetMoneyAward( sceneId, selfId, level)
        if( xp > 0) then
            AddQuestExpBonus( sceneId, xp)
        end
        AddQuestMoneyBonus8( sceneId, circle)
		--小提示
        AddQuestText( sceneId, x300928_g_strTip)
        AddQuestText( sceneId, x300928_g_strMissionTip)
	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, NPCId, x300928_g_ScriptId, x300928_g_MissionId)
end

function x300928_DispatchMissionContinue( sceneId, selfId, NPCId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300928_g_MissionId)
    local mp1 = GetQuestParam( sceneId, selfId, misIndex, x300928_MP_INDEX1)
    local mp2 = GetQuestParam( sceneId, selfId, misIndex, x300928_MP_INDEX2)
    local mp3 = GetQuestParam( sceneId, selfId, misIndex, x300928_MP_INDEX3)
    local mp4 = GetQuestParam( sceneId, selfId, misIndex, x300928_MP_INDEX4)
    local mp5 = GetQuestParam( sceneId, selfId, misIndex, x300928_MP_INDEX5)
    local mp6 = GetQuestParam( sceneId, selfId, misIndex, x300928_MP_INDEX6)
    local found = mp4 + mp5 + mp6
    local npcGuid = GetMonsterGUID( sceneId, NPCId)
    local level = GetLevel( sceneId, selfId)
    local array = {}
    local strDialog = ""

    if npcGuid == x300928_g_MissionNPC then
        strDialog = x300928_g_MissionContinue
    else
        -- 查找对应等级的任务目标
        for i, item in x300928_g_LookforItemTable do
            --if level >= item.minLevel and level < item.maxLevel then
                if mp2 ~= 0 then
                	local bupdate = 0
                    array = item.targets

                    if npcGuid == mp1 then
                        for i, item in array do
                            if npcGuid == item.npcId then
                                strDialog = item.Dialog
                                mp4 = 1
                                SetQuestByIndex( sceneId, selfId, misIndex, x300928_MP_INDEX4, mp4)
                                Msg2Player( sceneId, selfId, format( "你已经找到了@npc_%d(%d/3)", npcGuid, found + 1), 8, 3)
                                bupdate = 1
                                break
                            end
                        end
                    end
                    if npcGuid == mp2 then
                        for i, item in array do
                            if npcGuid == item.npcId then
                                strDialog = item.Dialog
                                mp5 = 1
                                SetQuestByIndex( sceneId, selfId, misIndex, x300928_MP_INDEX5, mp5)
                                Msg2Player( sceneId, selfId, format( "你已经找到了@npc_%d(%d/3)", npcGuid, found + 1), 8, 3)
                                bupdate = 1
                                break
                            end
                        end
                    end
                    if npcGuid == mp3 then
                        for i, item in array do
                            if npcGuid == item.npcId then
                                strDialog = item.Dialog
                                mp6 = 1
                                SetQuestByIndex( sceneId, selfId, misIndex, x300928_MP_INDEX6, mp6)
                                Msg2Player( sceneId, selfId, format( "你已经找到了@npc_%d(%d/3)", npcGuid, found + 1), 8, 3)
                                bupdate = 1
                                break
                            end
                        end
                    end
                    if mp4 == 1 and mp5 == 1 and mp6 == 1 then
                        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
                        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
                        Msg2Player( sceneId, selfId, "你完成了【帮会】帮会贡品", 8, 3)
                        bupdate = 1
                    end
                    if bupdate == 1 then
                    	x300928_ProcQuestLogRefresh( sceneId, selfId, x300928_g_MissionId)
                    	break
                    end
                else
                    --array = item.item
                    strDialog = format( x300928_g_MissionTarget, mp1, GetQuestParam( sceneId, selfId, misIndex, 0))
                end
                --break
            --end
        end
    end

    BeginQuestEvent( sceneId)
        --任务继续信息
        AddQuestText( sceneId, "#Y"..x300928_g_MissionName)
        AddQuestText( sceneId, strDialog)
    EndQuestEvent()
    DispatchQuestEventList( sceneId, selfId, NPCId)
end

function x300928_DispatchMissionComplete( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)
		-- 任务完成信息
		AddQuestText( sceneId, "#Y"..x300928_g_MissionName)
		-- AddQuestText( sceneId, x300928_g_MissionDescription)
		-- AddQuestText( sceneId, " " )
		AddQuestText( sceneId, x300928_g_strMissionComplete)

        local level = GetLevel( sceneId, selfId)
        local circle = x300928_GetMD( sceneId, selfId, MD_BANGHUI_CIRCLE)
        local xp = level * x300928_g_xpCoefficient[ circle]
        if( xp > 0) then
            AddQuestExpBonus( sceneId, xp)
        end
        AddQuestMoneyBonus8( sceneId, circle)
	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, NPCId, x300928_g_ScriptId, x300928_g_MissionId)
end

function x300928_ProcQuestAccept( sceneId, selfId, NPCId)
	
	local level = GetLevel( sceneId, selfId)

    if level < x300928_g_MinLevel then
        return
    end
	
    local guildId = GetGuildID( sceneId, selfId)
    if guildId < 0 then
        Msg2Player( sceneId, selfId, "你尚未加入任何帮会，不能领取【帮会】帮会贡品", 8, 3)
        return
    end

    if IsHaveQuest( sceneId, selfId, x300928_g_MissionId) == 0 then
        if AddQuest( sceneId, selfId, x300928_g_MissionId, x300928_g_ScriptId, 0, 0, 1, 1) == 0 then
            Msg2Player( sceneId, selfId, x300928_g_strAddMissionFail, 8, 3)
            Msg2Player( sceneId, selfId, x300928_g_strAddMissionFail.."。", 8, 2)
            return
        end

        local missionType = random( 1, 2)
        local level = GetLevel( sceneId, selfId)
        local id = 0
        for i, item in x300928_g_LookforItemTable do
            if level >= item.minLevel and level < item.maxLevel then
                if missionType == 1 then
                    -- 收集材料
                    id = item.item[ random( 1, getn( item.item) ) ]

                    local misIndex = GetQuestIndexByID( sceneId, selfId, x300928_g_MissionId)
                    SetQuestByIndex( sceneId, selfId, misIndex, x300928_MP_INDEX1, id)
                    SetQuestByIndex( sceneId, selfId, misIndex, x300928_MP_INDEX6, missionType)

					local itemcount = GetItemCountInBag( sceneId, selfId, id)
                    BeginQuestEvent( sceneId)
                        --任务继续信息
                        AddQuestText( sceneId, "#Y"..x300928_g_MissionName)
                        AddQuestText( sceneId, x300928_g_MissionDescription)
                        AddQuestText( sceneId, "#r" )
                        AddQuestText( sceneId, "#Y任务目标：" )
                        AddQuestText( sceneId, format( x300928_g_MissionTarget, id, itemcount >= 1 and 1 or 0) )
                    EndQuestEvent()

                    -- 检查背包里是否有任务物品
                    if itemcount >= 1 then
                        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
                        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
                    end
                else
                    -- 送信，随机选择3个NPC
                    local targets = {}
                    targets[ 1] = random( 1, getn( item.targets) )
                    local rndm = random( 1, getn( item.targets) )
                    while rndm == targets[ 1] do
                        rndm = random( 1, getn( item.targets) )
                    end
                    targets[ 2] = rndm
                    rndm = random( 1, getn( item.targets) )
                    while rndm == targets[ 1] or rndm == targets[ 2] do
                        rndm = random( 1, getn( item.targets) )
                    end
                    targets[ 3] = rndm

                    local misIndex = GetQuestIndexByID( sceneId, selfId, x300928_g_MissionId)
                    SetQuestByIndex( sceneId, selfId, misIndex, x300928_MP_INDEX1, item.targets[ targets[ 1] ].npcId)
                    SetQuestByIndex( sceneId, selfId, misIndex, x300928_MP_INDEX2, item.targets[ targets[ 2] ].npcId)
                    SetQuestByIndex( sceneId, selfId, misIndex, x300928_MP_INDEX3, item.targets[ targets[ 3] ].npcId)

                    BeginQuestEvent( sceneId)
                        --任务继续信息
                        AddQuestText( sceneId, "#Y"..x300928_g_MissionName)
                        AddQuestText( sceneId, x300928_g_MissionDescription)
                        AddQuestText( sceneId, "#r" )
                        AddQuestText( sceneId, "#Y任务目标：" )
                        AddQuestText( sceneId, format( x300928_g_MissionTarget1, 
                            item.targets[ targets[ 1] ].npcId, 
                            item.targets[ targets[ 2] ].npcId, 
                            item.targets[ targets[ 3] ].npcId ) )
                    EndQuestEvent()
                end
                break
            end
        end
        DispatchQuestEventList( sceneId, selfId, NPCId)
        Msg2Player( sceneId, selfId, "你接受了任务【帮会】帮会贡品", 8, 3)
        Msg2Player( sceneId, selfId, "你接受了任务【帮会】帮会贡品。", 8, 2)
    else
        local misIndex = GetQuestIndexByID( sceneId, selfId, x300928_g_MissionId)
        local mp1 = GetQuestParam( sceneId, selfId, misIndex, x300928_MP_INDEX1)
        local mp2 = GetQuestParam( sceneId, selfId, misIndex, x300928_MP_INDEX2)
        local mp3 = GetQuestParam( sceneId, selfId, misIndex, x300928_MP_INDEX3)
        local mp0 = GetQuestParam( sceneId, selfId, misIndex, x300928_MP_ISCOMPLETE)
        local mp7 = GetQuestParam( sceneId, selfId, misIndex, x300928_MP_FINISH)
        if mp0 ~= 1 or mp7 ~= 1 then
        	return
        end
        
        local circle = x300928_GetMD( sceneId, selfId, MD_BANGHUI_CIRCLE)
        local level = GetLevel( sceneId, selfId)

        if mp2 == 0 then
            if DelItem( sceneId, selfId, mp1, 1) == 0 then
                Msg2Player( sceneId, selfId, x300928_g_strCommitItemFail, 8, 3)
                return
            end
        end
        DelQuest( sceneId, selfId, x300928_g_MissionId)

        local curDay = GetDayOfYear()
        x300928_SetMD( sceneId, selfId, MD_BANGHUI_CIRCLE, circle + 1)
        if curDay ~= x300928_GetMD( sceneId, selfId, MD_BANGHUI_LASTDAY) then
            x300928_SetMD( sceneId, selfId, MD_BANGHUI_TIMES, 1)
        else
            x300928_SetMD( sceneId, selfId, MD_BANGHUI_TIMES, x300928_GetMD( sceneId, selfId, MD_BANGHUI_TIMES) + 1)
        end

        local xp = level * x300928_g_xpCoefficient[ circle]
        AddExp( sceneId, selfId, xp)
        Msg2Player( sceneId, selfId, format( x300928_g_strObtainXP, xp), 8, 2)
        Msg2Player( sceneId, selfId, format( x300928_g_strObtainGP, circle), 8, 2)
        AddGuildUserPoint( sceneId, selfId, circle)
        Msg2Player( sceneId, selfId, format( x300928_g_strMissionFinished, circle), 8, 3)
        x300928_SetMD( sceneId, selfId, MD_BANGHUI_LASTDAY, curDay)
    end
end

function x300928_ProcQuestAttach( sceneId, selfId, NPCId, npcGuid, misIndex, MissionId)
    if IsHaveQuest( sceneId, selfId, x300928_g_MissionId) == 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x300928_g_MissionId)
    local mp1 = GetQuestParam( sceneId, selfId, misIndex, x300928_MP_INDEX1)
    local mp2 = GetQuestParam( sceneId, selfId, misIndex, x300928_MP_INDEX2)
    local mp3 = GetQuestParam( sceneId, selfId, misIndex, x300928_MP_INDEX3)
    local mp4 = GetQuestParam( sceneId, selfId, misIndex, x300928_MP_INDEX4)
    local mp5 = GetQuestParam( sceneId, selfId, misIndex, x300928_MP_INDEX5)
    local mp6 = GetQuestParam( sceneId, selfId, misIndex, x300928_MP_INDEX6)

    if npcGuid == mp1 and mp4 == 0 then
        AddQuestNumText( sceneId, x300928_g_MissionId, x300928_g_MissionName, 6)
    end

    if npcGuid == mp2 and mp5 == 0 then
        AddQuestNumText( sceneId, x300928_g_MissionId, x300928_g_MissionName, 6)
    end

    if npcGuid == mp3 and mp6 == 0 then
        AddQuestNumText( sceneId, x300928_g_MissionId, x300928_g_MissionName, 6)
    end
end

function x300928_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300928_g_MissionId)
    local mp1 = GetQuestParam( sceneId, selfId, misIndex, x300928_MP_INDEX1)
    local mp2 = GetQuestParam( sceneId, selfId, misIndex, x300928_MP_INDEX2)
    local mp3 = GetQuestParam( sceneId, selfId, misIndex, x300928_MP_INDEX3)
    local mp4 = GetQuestParam( sceneId, selfId, misIndex, x300928_MP_INDEX4)
    local mp5 = GetQuestParam( sceneId, selfId, misIndex, x300928_MP_INDEX5)
    local mp6 = GetQuestParam( sceneId, selfId, misIndex, x300928_MP_INDEX6)
    local level = GetLevel( sceneId, selfId)
    local circle = x300928_GetMD( sceneId, selfId, MD_BANGHUI_CIRCLE)
    local xp = level * x300928_g_xpCoefficient[ circle]

	BeginQuestEvent( sceneId)
    if mp2 == 0 then
        AddQuestLogCustomText( sceneId,
                                "",                             -- 标题
                                x300928_g_MissionName..format( "(%d/%d)", x300928_GetMD( sceneId, selfId, MD_BANGHUI_CIRCLE), x300928_g_MaxCircle), -- 任务名字
                                format( x300928_g_MissionTarget, mp1, GetQuestParam( sceneId, selfId, misIndex, 0)),
                                "",                             --任务NPC
                                x300928_g_MissionBook,          --
                                x300928_g_MissionDescription,
                                x300928_g_MissionTips)
        if( xp > 0) then
            AddQuestExpBonus( sceneId, xp)
        end
        AddQuestMoneyBonus8( sceneId, circle)
    else
        local strTarget = ""
        if mp4 == 1 then
            strTarget = strTarget.."#G"..format( "  找到@npc_%d(1/1)\n", mp1)
        else
            strTarget = strTarget.."#W"..format( "  找到@npc_%d(0/1)\n", mp1)
        end
        if mp5 == 1 then
            strTarget = strTarget.."#G"..format( "  找到@npc_%d(1/1)\n", mp2)
        else
            strTarget = strTarget.."#W"..format( "  找到@npc_%d(0/1)\n", mp2)
        end
        if mp6 == 1 then
            strTarget = strTarget.."#G"..format( "  找到@npc_%d(1/1)", mp3)
        else
            strTarget = strTarget.."#W"..format( "  找到@npc_%d(0/1)", mp3)
        end
        AddQuestLogCustomText( sceneId,
                                "",                             -- 标题
                                x300928_g_MissionName..format( "(%d/%d)", x300928_GetMD( sceneId, selfId, MD_BANGHUI_CIRCLE), x300928_g_MaxCircle), -- 任务名字
                                strTarget,
                                "",                             --任务NPC
                                format( x300928_g_MissionTarget1, mp1, mp2, mp3),          --
                                x300928_g_MissionDescription,
                                x300928_g_MissionTips)
        if( xp > 0) then
            AddQuestExpBonus( sceneId, xp)
        end
        AddQuestMoneyBonus8( sceneId, circle)
    end
	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

function x300928_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId)
    if IsHaveQuest( sceneId, selfId, x300928_g_MissionId) == 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x300928_g_MissionId)
    if GetQuestParam( sceneId, selfId, misIndex, x300928_MP_FINISH) == 1
		and GetQuestParam( sceneId, selfId, misIndex, x300928_MP_ISCOMPLETE) == 1 then
		return
	end
    
    local id = GetQuestParam( sceneId, selfId, misIndex, x300928_MP_INDEX1)
    if id == itemdataId then
        SetQuestByIndex( sceneId, selfId, misIndex, x300928_MP_FINISH, 1)
        SetQuestByIndex( sceneId, selfId, misIndex, x300928_MP_ISCOMPLETE, 1)
        Msg2Player( sceneId, selfId, "你完成了【帮会】帮会贡品", 8, 3)
    end
end

function x300928_ProcQuestAbandon( sceneId, selfId, MissionId)
    if IsHaveQuest( sceneId, selfId, x300928_g_MissionId) == 0 then
        return
    end

    DelQuest( sceneId, selfId, x300928_g_MissionId)
    x300928_SetMD( sceneId, selfId, MD_BANGHUI_LASTDAY, GetDayOfYear() )
    x300928_SetMD( sceneId, selfId, MD_BANGHUI_CIRCLE, 1)
    x300928_SetMD( sceneId, selfId, MD_BANGHUI_TIMES, x300928_g_MaxCircle)
    Msg2Player( sceneId, selfId, "你放弃了任务【帮会】帮会贡品", 8, 3)
end

function x300928_GetMD( sceneId, selfId, mdName)
    return GetQuestData( sceneId, selfId, mdName[ 1], mdName[ 2], mdName[ 3] )
end

function x300928_SetMD( sceneId, selfId, mdName, value)
    SetQuestData( sceneId, selfId, mdName[ 1], mdName[ 2], mdName[ 3], value)
end

