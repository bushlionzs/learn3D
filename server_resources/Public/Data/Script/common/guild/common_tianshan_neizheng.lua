--MisDescBegin 
x300926_g_ScriptId 					= 300926
x300926_g_MissionId 				= 1370
x300926_g_MissionName				= "����᡿��ṱƷ"
x300926_g_MissionInfo				= "������Ϣ"
x300926_g_MissionTarget				= "  �ռ�@item_%d#W(%d/1)"
x300926_g_MissionDescription        = "\t��ṱƷ���񣬷�Ϊ#GѰ��#W��#G����#W���֣���ֻ��Ҫ���հ�����񷢲��˵�Ҫ��������񣬾Ϳ��Ի��#G����#W��#G�ﹱ#W�Ľ�����"
x300926_g_MissionTips               = "�����Ҫ�˽Ȿ�����ϸ�ڣ�������ṱƷ����˵����ť��"
x300926_g_MissionBook               = "�Ͻ�ָ������Ʒ������ɴ��������û�п��Կ�����������չ���"
--MisDescEnd

x300926_g_strFinishAll              = "����첻������ȡ����᡿��ṱƷ������"
x300926_g_strTip                    = "#c00FF00С��ʾ:"
x300926_g_strMissionTip             = "#c00FF00�����Ҫ�˽Ȿ�����ϸ�ڣ������������˵����ť��"
x300926_g_strAddMissionFail         = "����ܵ�����̫���ˣ����������ʧ��"
x300926_g_strMissionComplete        = "\t̫���ˣ����Ȼ���ĸɾ�������"
x300926_g_strMissionFinished        = "��ɡ���᡿��ṱƷ(%d/10)"
x300926_g_strCommitItemFail         = "�ύ��Ʒʧ�ܣ�������ʧ��"
x300926_g_strObtainXP               = "���#R%d#cffcc00�㾭�顣"
x300926_g_strObtainGP               = "���#R%d#cffcc00��ﹱ��"
x300926_g_MissionTarget1			= "  �ҵ�@npc_%d\n  �ҵ�@npc_%d\n  �ҵ�@npc_%d"
x300926_g_MissionContinue			= "\t�뾡����ɽ���������顣"

-- ��������͵ȼ�
x300926_g_MinLevel                  = 20
-- ÿ�������
x300926_g_MaxCircle                 = 10
x300926_MP_INDEX1			        = 1         -- 
x300926_MP_INDEX2					= 2         -- 
x300926_MP_INDEX3					= 3         -- 
x300926_MP_INDEX4					= 4         -- 
x300926_MP_INDEX5					= 5         -- 
x300926_MP_INDEX6					= 6         -- 
x300926_MP_FINISH                   = 7         -- ��ҽ�����ʱ�ĵȼ�
x300926_MP_ISCOMPLETE				= 0	        -- ������� 0δ��ɣ� 1���
-- ������NPC��GUID
x300926_g_MissionNPC                = 126020
-- Ѱ�����ñ�
x300926_g_LookforItemTable          = {
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
                                                    { npcId = 126126, Dialog = "\t���С����ҲҪ�����ҡ���\n\t�ð�!һ���Ҿʹ���ȥ������"	}, --1
                                                    { npcId = 126135, Dialog = "\tû�����⣬�ҵ����ѣ��ܸ����ܰ������ǵ�æ��"	}, --2
                                                    { npcId = 126006, Dialog = "\t�������������Ѿ�æ�Ľ�ͷ�ö��ˡ�\n\t�����ɣ��Ҵ��������¾͹�ȥ��"	}, --3
                                                    { npcId = 126036, Dialog = "\t�Һ������æ~���������Եȣ�СŮ����ױ��ϣ��Ի�ǰ����"	}, --4
                                                    { npcId = 126134, Dialog = "\t����Ҫ��ɹ�ô��Ҫ��Ҫ�Ҵ��ϻ�����"	}, --5
                                                    { npcId = 126025, Dialog = "\t��ʲô��Ҫ�Ұ������𣿺ðɣ�����Ͷ���"	}, --6
                                                    { npcId = 126023, Dialog = "\t�һ�ȥ�ġ���������Ҫ���ҵ�ͽ�ܻ�����ʱ��"	}, --7
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
                                                    { npcId = 126066, Dialog = "\t���������������ģ��ðɣ�������ȥ�������ϴ����������ﶩ���Ļ����������Ҳû���壡"	}, 
                                                    { npcId = 126076, Dialog = "\tŶ������ô���ѵ�����̭������װ������������͹�ȥ��"	}, 
                                                    { npcId = 126063, Dialog = "\tѺ�˹ٵ�ְ�����Ҳ��������뿪�������ҿ�������Щ��Ѻ�˵ļһ���Сæ����"	}, 
                                                    { npcId = 126031, Dialog = "\t��æ���б���ô��һ�����ɸ����ȥ������û��׬ͷ�������Ҵ���������"	}, 
                                                    { npcId = 126072, Dialog = "\t����ΪʲôҪ�����ң�"	}, 
                                                    { npcId = 126074, Dialog = "\t�����顭����Ҫ�Ⱥ�������˵һ�£�������������һ����ͬ��ġ�"	}, 
                                                    { npcId = 126035, Dialog = "\t�ã����ǰ���˶����ҵ��Ϲ˿ͣ���һ��׼ʱ����"	}, 
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
                                                    { npcId = 126029, Dialog = "\t�õĺõģ����Ұ���ͷ���⼸��װ�������˾͹�ȥ��"	}, 
                                                    { npcId = 126032, Dialog = "\t�ܸ�����Ϊ����æ����׼��һ�����Ͼ͵���"	}, 
                                                    { npcId = 126080, Dialog = "\t��Ҫ�ҵİ�����û���⣡�ҿ��ǳ������ĺ�˵����"	}, 
                                                    { npcId = 126073, Dialog = "\t�ܸ�����Ϊ����Щ΢��֮������׼��һ�����Ͼ͵���"	}, 
                                                    { npcId = 126065, Dialog = "\t�ҴӲ��ʽ����£��������ǰ����������һ���Ҫ���ġ�\n\t�ðɣ����Ȼ�ȥ�������͵���"	}, 
                                                    { npcId = 126030, Dialog = "\t�����Ұ�æ��������ʰһ�£�һ���ȥ��"	}
                                                },
                                        }, 
}
-- ���齱��ϵ��
x300926_g_xpCoefficient             = {
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

function x300926_ProcEnumEvent( sceneId, selfId, NPCId)
    local level = GetLevel( sceneId, selfId)

    if level < x300926_g_MinLevel then
        return
    end

    if GetGuildID( sceneId, selfId) < 0 then
        return
    end

    local state = GetQuestStateNM( sceneId, selfId, NPCId, x300926_g_MissionId)
    AddQuestNumText( sceneId, x300926_g_MissionId, x300926_g_MissionName, state, 1)
end

function x300926_ProcEventEntry( sceneId, selfId, NPCId, MissionId, iClickIndex)

	local level = GetLevel( sceneId, selfId)

    if level < x300926_g_MinLevel then
        return
    end

    local guildId = GetGuildID( sceneId, selfId)
    if guildId < 0 then
        Msg2Player( sceneId, selfId, "����δ�����κΰ�ᣬ������ȡ����᡿��ṱƷ", 8, 3)
        return
    end

    if IsHaveQuest( sceneId, selfId, x300926_g_MissionId) == 0 then
        -- δ������
        local curDay = GetDayOfYear()
        
        if x300926_GetMD( sceneId, selfId, MD_BANGHUI_CIRCLE) == 0 then
			x300926_SetMD( sceneId, selfId, MD_BANGHUI_CIRCLE, 1)
		end
		
        if x300926_GetMD( sceneId, selfId, MD_BANGHUI_CIRCLE) > x300926_g_MaxCircle then
            if curDay == x300926_GetMD( sceneId, selfId, MD_BANGHUI_LASTDAY) then
                if x300926_GetMD( sceneId, selfId, MD_BANGHUI_TIMES) >= x300926_g_MaxCircle then
                    Msg2Player( sceneId, selfId, x300926_g_strFinishAll, 8, 3)
                    return
                else
                    x300926_SetMD( sceneId, selfId, MD_BANGHUI_CIRCLE, 1)
                    x300926_DispatchMissionInfo( sceneId, selfId, NPCId)
                end
            else
                x300926_SetMD( sceneId, selfId, MD_BANGHUI_LASTDAY, curDay)
                x300926_SetMD( sceneId, selfId, MD_BANGHUI_CIRCLE, 1)
                x300926_SetMD( sceneId, selfId, MD_BANGHUI_TIMES, 0)
            end
        else
            if x300926_GetMD( sceneId, selfId, MD_BANGHUI_TIMES) >= x300926_g_MaxCircle then
				if curDay == x300926_GetMD( sceneId, selfId, MD_BANGHUI_LASTDAY) then
					if x300926_GetMD( sceneId, selfId, MD_BANGHUI_TIMES) >= x300926_g_MaxCircle then
						Msg2Player( sceneId, selfId, x300926_g_strFinishAll, 8, 3)
						return
					else
						x300926_SetMD( sceneId, selfId, MD_BANGHUI_CIRCLE, 1)
						x300926_DispatchMissionInfo( sceneId, selfId, NPCId)
					end
				else
					x300926_SetMD( sceneId, selfId, MD_BANGHUI_LASTDAY, curDay)
					x300926_SetMD( sceneId, selfId, MD_BANGHUI_CIRCLE, 1)
					x300926_SetMD( sceneId, selfId, MD_BANGHUI_TIMES, 0)
				end
            else
                x300926_DispatchMissionInfo( sceneId, selfId, NPCId)
            end
        end
    else
        -- �ѽ�����
        local misIndex = GetQuestIndexByID( sceneId, selfId, x300926_g_MissionId)
        local mp0 = GetQuestParam( sceneId, selfId, misIndex, x300926_MP_ISCOMPLETE)
        local mp7 = GetQuestParam( sceneId, selfId, misIndex, x300926_MP_FINISH)
        if mp0 == 1 and mp7 == 1 then
            x300926_DispatchMissionComplete( sceneId, selfId, NPCId)
        else
            x300926_DispatchMissionContinue( sceneId, selfId, NPCId)
        end
    end
end

-- ��ʾ������Ϣ
function x300926_DispatchMissionInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)
		--������Ϣ
		AddQuestText( sceneId, "#Y"..x300926_g_MissionName)
		AddQuestText( sceneId, x300926_g_MissionDescription)
		AddQuestText( sceneId, " " )

		--��������Ϣ
        local level = GetLevel( sceneId, selfId)
        local circle = x300926_GetMD( sceneId, selfId, MD_BANGHUI_CIRCLE)
        local xp = level * x300926_g_xpCoefficient[ circle]
        -- local money, shengw = x300926_GetMoneyAward( sceneId, selfId, level)
        if( xp > 0) then
            AddQuestExpBonus( sceneId, xp)
        end
        AddQuestMoneyBonus8( sceneId, circle)
		--С��ʾ
        AddQuestText( sceneId, x300926_g_strTip)
        AddQuestText( sceneId, x300926_g_strMissionTip)
	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, NPCId, x300926_g_ScriptId, x300926_g_MissionId)
end

function x300926_DispatchMissionContinue( sceneId, selfId, NPCId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300926_g_MissionId)
    local mp1 = GetQuestParam( sceneId, selfId, misIndex, x300926_MP_INDEX1)
    local mp2 = GetQuestParam( sceneId, selfId, misIndex, x300926_MP_INDEX2)
    local mp3 = GetQuestParam( sceneId, selfId, misIndex, x300926_MP_INDEX3)
    local mp4 = GetQuestParam( sceneId, selfId, misIndex, x300926_MP_INDEX4)
    local mp5 = GetQuestParam( sceneId, selfId, misIndex, x300926_MP_INDEX5)
    local mp6 = GetQuestParam( sceneId, selfId, misIndex, x300926_MP_INDEX6)
    local found = mp4 + mp5 + mp6
    local npcGuid = GetMonsterGUID( sceneId, NPCId)
    local level = GetLevel( sceneId, selfId)
    local array = {}
    local strDialog = ""

    if npcGuid == x300926_g_MissionNPC then
        strDialog = x300926_g_MissionContinue
    else
        -- ���Ҷ�Ӧ�ȼ�������Ŀ��
        for i, item in x300926_g_LookforItemTable do
            --if level >= item.minLevel and level < item.maxLevel then
                if mp2 ~= 0 then
                	local bupdate = 0
                    array = item.targets

                    if npcGuid == mp1 then
                        for i, item in array do
                            if npcGuid == item.npcId then
                                strDialog = item.Dialog
                                mp4 = 1
                                SetQuestByIndex( sceneId, selfId, misIndex, x300926_MP_INDEX4, mp4)
                                Msg2Player( sceneId, selfId, format( "���Ѿ��ҵ���@npc_%d(%d/3)", npcGuid, found + 1), 8, 3)
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
                                SetQuestByIndex( sceneId, selfId, misIndex, x300926_MP_INDEX5, mp5)
                                Msg2Player( sceneId, selfId, format( "���Ѿ��ҵ���@npc_%d(%d/3)", npcGuid, found + 1), 8, 3)
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
                                SetQuestByIndex( sceneId, selfId, misIndex, x300926_MP_INDEX6, mp6)
                                Msg2Player( sceneId, selfId, format( "���Ѿ��ҵ���@npc_%d(%d/3)", npcGuid, found + 1), 8, 3)
                                bupdate = 1
                                break
                            end
                        end
                    end
                    if mp4 == 1 and mp5 == 1 and mp6 == 1 then
                        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
                        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
                        Msg2Player( sceneId, selfId, "������ˡ���᡿��ṱƷ", 8, 3)
                        bupdate = 1
                    end
                    if bupdate == 1 then
                    	x300926_ProcQuestLogRefresh( sceneId, selfId, x300926_g_MissionId)
                    	break
                    end
                else
                    --array = item.item
                    strDialog = format( x300926_g_MissionTarget, mp1, GetQuestParam( sceneId, selfId, misIndex, 0))
                end
                --break
            --end
        end
    end

    BeginQuestEvent( sceneId)
        --���������Ϣ
        AddQuestText( sceneId, "#Y"..x300926_g_MissionName)
        AddQuestText( sceneId, strDialog)
    EndQuestEvent()
    DispatchQuestEventList( sceneId, selfId, NPCId)
end

function x300926_DispatchMissionComplete( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)
		-- ���������Ϣ
		AddQuestText( sceneId, "#Y"..x300926_g_MissionName)
		-- AddQuestText( sceneId, x300926_g_MissionDescription)
		-- AddQuestText( sceneId, " " )
		AddQuestText( sceneId, x300926_g_strMissionComplete)

        local level = GetLevel( sceneId, selfId)
        local circle = x300926_GetMD( sceneId, selfId, MD_BANGHUI_CIRCLE)
        local xp = level * x300926_g_xpCoefficient[ circle]
        if( xp > 0) then
            AddQuestExpBonus( sceneId, xp)
        end
        AddQuestMoneyBonus8( sceneId, circle)
	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, NPCId, x300926_g_ScriptId, x300926_g_MissionId)
end

function x300926_ProcQuestAccept( sceneId, selfId, NPCId)

	local level = GetLevel( sceneId, selfId)

    if level < x300926_g_MinLevel then
        return
    end

    local guildId = GetGuildID( sceneId, selfId)
    if guildId < 0 then
        Msg2Player( sceneId, selfId, "����δ�����κΰ�ᣬ������ȡ����᡿��ṱƷ", 8, 3)
        return
    end

    if IsHaveQuest( sceneId, selfId, x300926_g_MissionId) == 0 then
        if AddQuest( sceneId, selfId, x300926_g_MissionId, x300926_g_ScriptId, 0, 0, 1, 1) == 0 then
            Msg2Player( sceneId, selfId, x300926_g_strAddMissionFail, 8, 3)
            Msg2Player( sceneId, selfId, x300926_g_strAddMissionFail.."��", 8, 2)
            return
        end

        local missionType = random( 1, 2)
        local level = GetLevel( sceneId, selfId)
        local id = 0
        for i, item in x300926_g_LookforItemTable do
            if level >= item.minLevel and level < item.maxLevel then
                if missionType == 1 then
                    -- �ռ�����
                    id = item.item[ random( 1, getn( item.item) ) ]

                    local misIndex = GetQuestIndexByID( sceneId, selfId, x300926_g_MissionId)
                    SetQuestByIndex( sceneId, selfId, misIndex, x300926_MP_INDEX1, id)
                    SetQuestByIndex( sceneId, selfId, misIndex, x300926_MP_INDEX6, missionType)

					local itemcount = GetItemCountInBag( sceneId, selfId, id)
                    BeginQuestEvent( sceneId)
                        --���������Ϣ
                        AddQuestText( sceneId, "#Y"..x300926_g_MissionName)
                        AddQuestText( sceneId, x300926_g_MissionDescription)
                        AddQuestText( sceneId, "#r" )
                        AddQuestText( sceneId, "#Y����Ŀ�꣺" )
                        AddQuestText( sceneId, format( x300926_g_MissionTarget, id, itemcount >= 1 and 1 or 0) )
                    EndQuestEvent()

                    -- ��鱳�����Ƿ���������Ʒ
                    if itemcount >= 1 then
                        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
                        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
                    end
                else
                    -- ���ţ����ѡ��3��NPC
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

                    local misIndex = GetQuestIndexByID( sceneId, selfId, x300926_g_MissionId)
                    SetQuestByIndex( sceneId, selfId, misIndex, x300926_MP_INDEX1, item.targets[ targets[ 1] ].npcId)
                    SetQuestByIndex( sceneId, selfId, misIndex, x300926_MP_INDEX2, item.targets[ targets[ 2] ].npcId)
                    SetQuestByIndex( sceneId, selfId, misIndex, x300926_MP_INDEX3, item.targets[ targets[ 3] ].npcId)

                    BeginQuestEvent( sceneId)
                        --���������Ϣ
                        AddQuestText( sceneId, "#Y"..x300926_g_MissionName)
                        AddQuestText( sceneId, x300926_g_MissionDescription)
                        AddQuestText( sceneId, "#r" )
                        AddQuestText( sceneId, "#Y����Ŀ�꣺" )
                        AddQuestText( sceneId, format( x300926_g_MissionTarget1, 
                            item.targets[ targets[ 1] ].npcId, 
                            item.targets[ targets[ 2] ].npcId, 
                            item.targets[ targets[ 3] ].npcId ) )
                    EndQuestEvent()
                end
                break
            end
        end
        DispatchQuestEventList( sceneId, selfId, NPCId)
        Msg2Player( sceneId, selfId, "����������񡾰�᡿��ṱƷ", 8, 3)
        Msg2Player( sceneId, selfId, "����������񡾰�᡿��ṱƷ��", 8, 2)
    else
        local misIndex = GetQuestIndexByID( sceneId, selfId, x300926_g_MissionId)
        local mp1 = GetQuestParam( sceneId, selfId, misIndex, x300926_MP_INDEX1)
        local mp2 = GetQuestParam( sceneId, selfId, misIndex, x300926_MP_INDEX2)
        local mp3 = GetQuestParam( sceneId, selfId, misIndex, x300926_MP_INDEX3)
        local mp0 = GetQuestParam( sceneId, selfId, misIndex, x300926_MP_ISCOMPLETE)
        local mp7 = GetQuestParam( sceneId, selfId, misIndex, x300926_MP_FINISH)
        if mp0 ~= 1 or mp7 ~= 1 then
        	return
        end
        
        local circle = x300926_GetMD( sceneId, selfId, MD_BANGHUI_CIRCLE)
        local level = GetLevel( sceneId, selfId)

        if mp2 == 0 then
            if DelItem( sceneId, selfId, mp1, 1) == 0 then
                Msg2Player( sceneId, selfId, x300926_g_strCommitItemFail, 8, 3)
                return
            end
        end
        DelQuest( sceneId, selfId, x300926_g_MissionId)

        local curDay = GetDayOfYear()
        x300926_SetMD( sceneId, selfId, MD_BANGHUI_CIRCLE, circle + 1)
        if curDay ~= x300926_GetMD( sceneId, selfId, MD_BANGHUI_LASTDAY) then
            x300926_SetMD( sceneId, selfId, MD_BANGHUI_TIMES, 1)
        else
            x300926_SetMD( sceneId, selfId, MD_BANGHUI_TIMES, x300926_GetMD( sceneId, selfId, MD_BANGHUI_TIMES) + 1)
        end

        local xp = level * x300926_g_xpCoefficient[ circle]
        AddExp( sceneId, selfId, xp)
        Msg2Player( sceneId, selfId, format( x300926_g_strObtainXP, xp), 8, 2)
        Msg2Player( sceneId, selfId, format( x300926_g_strObtainGP, circle), 8, 2)
        AddGuildUserPoint( sceneId, selfId, circle)
        Msg2Player( sceneId, selfId, format( x300926_g_strMissionFinished, circle), 8, 3)
        x300926_SetMD( sceneId, selfId, MD_BANGHUI_LASTDAY, curDay)
    end
end

function x300926_ProcQuestAttach( sceneId, selfId, NPCId, npcGuid, misIndex, MissionId)
    if IsHaveQuest( sceneId, selfId, x300926_g_MissionId) == 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x300926_g_MissionId)
    local mp1 = GetQuestParam( sceneId, selfId, misIndex, x300926_MP_INDEX1)
    local mp2 = GetQuestParam( sceneId, selfId, misIndex, x300926_MP_INDEX2)
    local mp3 = GetQuestParam( sceneId, selfId, misIndex, x300926_MP_INDEX3)
    local mp4 = GetQuestParam( sceneId, selfId, misIndex, x300926_MP_INDEX4)
    local mp5 = GetQuestParam( sceneId, selfId, misIndex, x300926_MP_INDEX5)
    local mp6 = GetQuestParam( sceneId, selfId, misIndex, x300926_MP_INDEX6)

    if npcGuid == mp1 and mp4 == 0 then
        AddQuestNumText( sceneId, x300926_g_MissionId, x300926_g_MissionName, 6)
    end

    if npcGuid == mp2 and mp5 == 0 then
        AddQuestNumText( sceneId, x300926_g_MissionId, x300926_g_MissionName, 6)
    end

    if npcGuid == mp3 and mp6 == 0 then
        AddQuestNumText( sceneId, x300926_g_MissionId, x300926_g_MissionName, 6)
    end
end

function x300926_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300926_g_MissionId)
    local mp1 = GetQuestParam( sceneId, selfId, misIndex, x300926_MP_INDEX1)
    local mp2 = GetQuestParam( sceneId, selfId, misIndex, x300926_MP_INDEX2)
    local mp3 = GetQuestParam( sceneId, selfId, misIndex, x300926_MP_INDEX3)
    local mp4 = GetQuestParam( sceneId, selfId, misIndex, x300926_MP_INDEX4)
    local mp5 = GetQuestParam( sceneId, selfId, misIndex, x300926_MP_INDEX5)
    local mp6 = GetQuestParam( sceneId, selfId, misIndex, x300926_MP_INDEX6)
    local level = GetLevel( sceneId, selfId)
    local circle = x300926_GetMD( sceneId, selfId, MD_BANGHUI_CIRCLE)
    local xp = level * x300926_g_xpCoefficient[ circle]

	BeginQuestEvent( sceneId)
    if mp2 == 0 then
        AddQuestLogCustomText( sceneId,
                                "",                             -- ����
                                x300926_g_MissionName..format( "(%d/%d)", x300926_GetMD( sceneId, selfId, MD_BANGHUI_CIRCLE), x300926_g_MaxCircle), -- ��������
                                format( x300926_g_MissionTarget, mp1, GetQuestParam( sceneId, selfId, misIndex, 0)),
                                "",                             --����NPC
                                x300926_g_MissionBook,          --
                                x300926_g_MissionDescription,
                                x300926_g_MissionTips)
        if( xp > 0) then
            AddQuestExpBonus( sceneId, xp)
        end
        AddQuestMoneyBonus8( sceneId, circle)
    else
        local strTarget = ""
        if mp4 == 1 then
            strTarget = strTarget.."#G"..format( "  �ҵ�@npc_%d(1/1)\n", mp1)
        else
            strTarget = strTarget.."#W"..format( "  �ҵ�@npc_%d(0/1)\n", mp1)
        end
        if mp5 == 1 then
            strTarget = strTarget.."#G"..format( "  �ҵ�@npc_%d(1/1)\n", mp2)
        else
            strTarget = strTarget.."#W"..format( "  �ҵ�@npc_%d(0/1)\n", mp2)
        end
        if mp6 == 1 then
            strTarget = strTarget.."#G"..format( "  �ҵ�@npc_%d(1/1)", mp3)
        else
            strTarget = strTarget.."#W"..format( "  �ҵ�@npc_%d(0/1)", mp3)
        end
        AddQuestLogCustomText( sceneId,
                                "",                             -- ����
                                x300926_g_MissionName..format( "(%d/%d)", x300926_GetMD( sceneId, selfId, MD_BANGHUI_CIRCLE), x300926_g_MaxCircle), -- ��������
                                strTarget,
                                "",                             --����NPC
                                format( x300926_g_MissionTarget1, mp1, mp2, mp3),          --
                                x300926_g_MissionDescription,
                                x300926_g_MissionTips)
        if( xp > 0) then
            AddQuestExpBonus( sceneId, xp)
        end
        AddQuestMoneyBonus8( sceneId, circle)
    end
	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

function x300926_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId)
    if IsHaveQuest( sceneId, selfId, x300926_g_MissionId) == 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x300926_g_MissionId)
    if GetQuestParam( sceneId, selfId, misIndex, x300926_MP_FINISH) == 1
		and GetQuestParam( sceneId, selfId, misIndex, x300926_MP_ISCOMPLETE) == 1 then
		return
	end
    
    local id = GetQuestParam( sceneId, selfId, misIndex, x300926_MP_INDEX1)
    if id == itemdataId then
        SetQuestByIndex( sceneId, selfId, misIndex, x300926_MP_FINISH, 1)
        SetQuestByIndex( sceneId, selfId, misIndex, x300926_MP_ISCOMPLETE, 1)
        Msg2Player( sceneId, selfId, "������ˡ���᡿��ṱƷ", 8, 3)
    end
end

function x300926_ProcQuestAbandon( sceneId, selfId, MissionId)
    if IsHaveQuest( sceneId, selfId, x300926_g_MissionId) == 0 then
        return
    end

    DelQuest( sceneId, selfId, x300926_g_MissionId)
    x300926_SetMD( sceneId, selfId, MD_BANGHUI_LASTDAY, GetDayOfYear() )
    x300926_SetMD( sceneId, selfId, MD_BANGHUI_CIRCLE, 1)
    x300926_SetMD( sceneId, selfId, MD_BANGHUI_TIMES, x300926_g_MaxCircle)
    Msg2Player( sceneId, selfId, "����������񡾰�᡿��ṱƷ", 8, 3)
end

function x300926_GetMD( sceneId, selfId, mdName)
    return GetQuestData( sceneId, selfId, mdName[ 1], mdName[ 2], mdName[ 3] )
end

function x300926_SetMD( sceneId, selfId, mdName, value)
    SetQuestData( sceneId, selfId, mdName[ 1], mdName[ 2], mdName[ 3], value)
end

