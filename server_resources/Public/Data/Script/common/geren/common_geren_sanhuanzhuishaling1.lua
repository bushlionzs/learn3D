--MisDescBegin

x270351_g_ScriptId 					= 270351                  --�ű�ID
x270351_g_MissionId 				= 1391                    --����ID

x270351_g_MissionKind 				= 1                       --��������
x270351_g_LevelLess					= 20                      --�������ŵȼ�  <=0 ��ʾ������

x270351_g_MissionName				= "�����ˡ���������(ͨ����)"                --��������(512)
x270351_g_MissionTarget				= "  ��%s����%s(%d/1)"          --����Ŀ��
x270351_g_MissionInfo				= "\tɱ��@npc_72004��@npc_72005,�ҵ�@npc_137600"            --������Ϣ
x270351_g_ContinueInfo				= "\t������ЩҰ����ô��"  --���������Ϣ
x270351_g_MissionCompleted			= "\t��ô��ͻ����ˣ����ǲ���\n\t�������һ��ǽ�������֯һ֧3�����ϵĶ��飬����������ս#G��������#W��#G�������������#W����ø����Ľ�����"  --���������Ϣ
x270351_g_MissionCompleted1			= "\t��ѡ����ʹ����������������㽫����#G5��#W�Ľ�����ͬʱ����#G5��#W���������"  --���������Ϣ
x270351_g_MissionHelp				= ""   --������ʾ��Ϣ

--Ŀ��
x270351_g_ExtTarget					= { {type=20,n=10 ,target=""} }


--����
x270351_g_ExpBonus					= { 90, 117, 162 , 297 }                    	--���������� ����ֵ��0���ַ���Ϊ�գ���ʾû�и������
x270351_g_BonusItem					= {}	--��������Ʒ

x270351_g_BonusMoney1               = 0    --������������
x270351_g_BonusMoney2               = 0   --������������ϵ��
x270351_g_BonusMoney3               = 0    --�������󶨽��
x270351_g_BonusMoney4               = 0  --��������͢����
x270351_g_BonusMoney5               = 0  --��������������
x270351_g_BonusMoney6               = 0  --����������

x270351_g_BonusChoiceItem           = {}


--MisDescEnd

--����Ŀ��˳��
x270351_MP_TARGET1					= 1         -- Ҫɱ��1
x270351_MP_TARGET2					= 2         -- Ҫɱ��2
x270351_MP_TARGET3					= 3         -- Ҫɱ��3
x270351_MP_TARGET4					= 4         -- 
x270351_MP_TARGET5					= 5         -- 
x270351_MP_TARGET6					= 6         -- 
x270351_MP_COMPLETE                 = 7         -- ��ҽ�����ʱ�ĵȼ�
x270351_MP_ISCOMPLETE				= 0	        -- ������� 0δ��ɣ� 1���

-- ����������ʾ
x270351_g_strAcceptMission          = "�����������񣺡����ˡ���������(ͨ����)"
-- ����������ʾ
x270351_g_strAbandonMission         = "�����������񣺡����ˡ���������(ͨ����)"
-- ���������ʾ
x270351_g_strFinishMission          = "����������񣺡����ˡ���������(ͨ����)"

--����Ŀ��ID
x270351_TARGET_OBJID1				= 9500
x270351_TARGET_OBJID2				= -2
x270351_TARGET_OBJID3				= -2
x270351_TARGET_OBJID4				= -2
x270351_TARGET_OBJID5				= -2

--������Ʒ
x270351_TARGET_ITEMID1				= -2
-- ����������ֹ���������ʱ��(����)
x270351_g_PunishTime                = 2

-- ��������������С�ȼ�
x270351_g_PlayerMinLevel            = 20
-- ���������������ȼ�
x270351_g_PlayerMaxLevel            = 150

x270351_SubmitNPCGUID				= 126040	--������NPC GUID

-- ��������
x270351_g_MissionDescription        = "\t#Y@myname#W��������̫���ˣ���������Ҫ�����أ�\n\t���������������������������˳������Ĵ������ֵ������������Ļ̵̻ġ����Ƿ�Ը������ǳ�ȥ��Щ���\n��ÿ�ν�ȡ��������Ҫ����һ��#Gͨ����#W��#Gͨ����#W��������ó�����ӻ����˴����򡣣�\n \n#GС��ʾ��\n�ȼ��൱�����5�����ڣ������һ�������ȡ����������Ŀ����ͬ��#W"
-- ������
x270351_g_MissionBook               = "��ӽ���������Լ����������������ٶ�"
-- ���������Ϣ
x270351_g_MissionContinue           = "\t�㻹ûɱ����ֻ������"
-- ����Ŀ��֮һ����
x270351_g_strMissionTarget          = "  ʹ�ñ����е�@item_13810160#W��Ѱ��������%s��#G%s#W(%d/1)"
-- 
x270351_g_ItemID                    = 11990016
x270351_g_AcceptItemID              = 11990017		--����
x270351_g_SubmitItemID              = 13810160--11990018		--��ȡ��������
-- 
x270351_g_MonsterTable              = {
                                        { minLevel = 20, maxLevel = 29, monList = { { id = 3840, objid = 400040, mapid = 158, name = "��ľ����", 	 Place = "������" , posName = "@npc_4000401"  }, { id = 3841, objid = 400041, mapid = 158, name = "��ľ����",   Place = "������" , posName = "@npc_4000411"  }, { id = 3842, objid = 400042, mapid = 158, name = "��������",   Place = "���Ϸ�" , posName = "@npc_4000421"  }, { id = 3843, objid = 400043, mapid = 158, name = "�������",   		Place = "���Ϸ�" , posName = "@npc_4000431"  }, { id = 3844, objid = 400044, mapid = 158, name = "θ������", Place = "�Ϸ�" ,posName = "@npc_4000441"  }, { id = 3845, objid = 400045, mapid = 158, name = "Ů������", Place = "�Ϸ�" ,posName = "@npc_4000451" } }},  
                                        { minLevel = 30, maxLevel = 34, monList = { { id = 3846, objid = 400046, mapid = 204, name = "�������", 	 Place = "���Ϸ�" , posName = "@npc_4000461"  }, { id = 3847, objid = 400047, mapid = 204, name = "β����",   Place = "����" ,   posName = "@npc_4000471"  }, { id = 3849, objid = 400049, mapid = 204, name = "��������",   Place = "������" , posName = "@npc_4000491"  }, { id = 3850, objid = 400050, mapid = 204, name = "���", 					Place = "������" , posName = "@npc_4000501"  } }},
                                        { minLevel = 35, maxLevel = 39, monList = { { id = 3849, objid = 400049, mapid = 204, name = "��������", 	 Place = "������" ,	posName = "@npc_4000491"  }, { id = 3850, objid = 400050, mapid = 204, name = "���", 			Place = "������" , posName = "@npc_4000501"  }, { id = 3852, objid = 400052, mapid = 205, name = "��צ����",   Place = "�Ϸ�" ,   posName = "@npc_4000521"  }, { id = 3853, objid = 400053, mapid = 205, name = "�������",   		Place = "������" , posName = "@npc_4000531"  } }}, 
                                        { minLevel = 40, maxLevel = 44, monList = { { id = 3852, objid = 400052, mapid = 205, name = "��צ����", 	 Place = "�Ϸ�" ,		posName = "@npc_4000521"  }, { id = 3853, objid = 400053, mapid = 205, name = "�������",   Place = "������" , posName = "@npc_4000531"  }, { id = 3854, objid = 400054, mapid = 205, name = "̽����",   Place = "����" ,   posName = "@npc_4000541"  }, { id = 3856, objid = 400056, mapid = 205, name = "��Ѩ��ħ",   		Place = "����" ,   posName = "@npc_4000561"  } }}, 
                                        { minLevel = 45, maxLevel = 49, monList = { { id = 3854, objid = 400054, mapid = 205, name = "̽����", 	 Place = "����" ,		posName = "@npc_4000541"  }, { id = 3856, objid = 400056, mapid = 205, name = "��Ѩ��ħ",   Place = "����" ,	 posName = "@npc_4000561"  }, { id = 3858, objid = 400058, mapid = 206, name = "��������",   Place = "�в�" ,   posName = "@npc_4000581"  }, { id = 3859, objid = 400059, mapid = 206, name = "���˲�³˹", 		Place = "����" ,   posName = "@npc_4000591"  } }}, 
                                        { minLevel = 50, maxLevel = 54, monList = { { id = 3858, objid = 400058, mapid = 206, name = "��������", 	 Place = "�в�" ,		posName = "@npc_4000581"  }, { id = 3859, objid = 400059, mapid = 206, name = "���˲�³˹", Place = "����" ,	 posName = "@npc_4000591"  }, { id = 3862, objid = 400062, mapid = 206, name = "Ѫ����",     Place = "����" ,   posName = "@npc_4000621"  }, { id = 3863, objid = 400063, mapid = 206, name = "������ʿ",   		Place = "������" , posName = "@npc_4000631"  } }}, 
                                        { minLevel = 55, maxLevel = 59, monList = { { id = 3862, objid = 400062, mapid = 206, name = "Ѫ����", 		 Place = "����" ,		posName = "@npc_4000621"  }, { id = 3863, objid = 400063, mapid = 206, name = "������ʿ",   Place = "������" , posName = "@npc_4000631"  }, { id = 3864, objid = 400064, mapid = 207, name = "�綾����",   Place = "���Ϸ�" , posName = "@npc_4000641"  }, { id = 3866, objid = 400066, mapid = 207, name = "��ǯ��Ы",   		Place = "������" , posName = "@npc_4000661"  } }}, 
                                        { minLevel = 60, maxLevel = 64, monList = { { id = 3864, objid = 400064, mapid = 207, name = "�綾����",   Place = "���Ϸ�" , posName = "@npc_4000641"  }, { id = 3866, objid = 400066, mapid = 207, name = "��ǯ��Ы",   Place = "������" , posName = "@npc_4000661"  }, { id = 3868, objid = 400068, mapid = 207, name = "ף��ׯ��Ժ", Place = "����" ,   posName = "@npc_4000681"  }, { id = 3869, objid = 400069, mapid = 207, name = "ף��ׯ����", 		Place = "������" , posName = "@npc_4000691"  } }},                               
 																				{ minLevel = 65, maxLevel = 69, monList = { { id = 3868, objid = 400068, mapid = 207, name = "ף��ׯ��Ժ", Place = "����" ,		posName = "@npc_4000681"	}, { id = 3869, objid = 400069, mapid = 207, name = "ף��ׯ����", Place = "������" , posName = "@npc_4000691"  }, { id = 3870, objid = 400070, mapid = 208, name = "��֮��", 		 Place = "�в�" ,		posName = "@npc_4000701"  }, { id = 3871, objid = 400071, mapid = 208, name = "��֮��", 				Place = "����" ,	 posName = "@npc_4000711"  } }}, 
                                        { minLevel = 70, maxLevel = 74, monList = { { id = 3870, objid = 400070, mapid = 208, name = "��֮��",     Place = "�в�" ,		posName = "@npc_4000701"  }, { id = 3871, objid = 400071, mapid = 208, name = "��֮��", 		Place = "����" ,	 posName = "@npc_4000711"  }, { id = 3872, objid = 400072, mapid = 208, name = "��֮��", 		 Place = "����" ,		posName = "@npc_4000721"  }, { id = 3873, objid = 400073, mapid = 208, name = "ͻ������",   		Place = "���Ϸ�" , posName = "@npc_4000731"  } }}, 
                                        { minLevel = 75, maxLevel = 79, monList = { { id = 3872, objid = 400072, mapid = 208, name = "��֮��",     Place = "����" ,		posName = "@npc_4000721"  }, { id = 3873, objid = 400073, mapid = 208, name = "ͻ������", 	Place = "���Ϸ�" , posName = "@npc_4000731"  }, { id = 3874, objid = 400074, mapid = 209, name = "��֮��", 		 Place = "���Ϸ�" , posName = "@npc_4000741"  }, { id = 3875, objid = 400075, mapid = 209, name = "ͻ�ʽ���", 			Place = "����" ,   posName = "@npc_4000751"  } }}, 
                                        { minLevel = 80, maxLevel = 84, monList = { { id = 3874, objid = 400074, mapid = 209, name = "��֮��",     Place = "���Ϸ�" , posName = "@npc_4000741"  }, { id = 3875, objid = 400075, mapid = 209, name = "ͻ�ʽ���", 	Place = "����" ,   posName = "@npc_4000751"  }, { id = 3876, objid = 400076, mapid = 209, name = "���ׯׯ��", Place = "����" ,		posName = "@npc_4000761"  }, { id = 3877, objid = 400077, mapid = 209, name = "ף��ׯׯ��", 		Place = "����" ,	 posName = "@npc_4000771"  } }}, 
                                        { minLevel = 85, maxLevel = 89, monList = { { id = 3876, objid = 400076, mapid = 209, name = "���ׯׯ��", Place = "����" ,		posName = "@npc_4000761"  }, { id = 3877, objid = 400077, mapid = 209, name = "ף��ׯׯ��", Place = "����" ,	 posName = "@npc_4000771"  }, { id = 3878, objid = 400078, mapid = 210, name = "���ùٱ�",   Place = "������" ,	posName = "@npc_4000781"  }, { id = 3879, objid = 400079, mapid = 210, name = "ͻ������",   		Place = "����" ,	 posName = "@npc_4000791"  } }}, 
                                        { minLevel = 90, maxLevel = 94, monList = { { id = 3878, objid = 400078, mapid = 210, name = "���ùٱ�",   Place = "������" ,	posName = "@npc_4000781"  }, { id = 3879, objid = 400079, mapid = 210, name = "ͻ������", 	Place = "����" ,	 posName = "@npc_4000791"  }, { id = 3880, objid = 400080, mapid = 210, name = "�ҿ�з", 		 Place = "���Ϸ�" ,	posName = "@npc_4000801"  }, { id = 3881, objid = 400081, mapid = 210, name = "�����Ѧ��", 		Place = "����" ,   posName = "@npc_4000811"  } }}, 
                                        { minLevel = 95, maxLevel = 99, monList = { { id = 3880, objid = 400080, mapid = 210, name = "�ҿ�з",     Place = "���ϱ���",posName = "@npc_4000801"  }, { id = 3881, objid = 400081, mapid = 210, name = "�����Ѧ��", Place = "����" ,   posName = "@npc_4000811"  },	{ id = 3882, objid = 400082, mapid = 211, name = "������Ӿ�", Place = "���Ϸ�" , posName = "@npc_4000821"  }, { id = 3883, objid = 400083, mapid = 211, name = "�����ʦ",   		Place = "������" , posName = "@npc_4000831"  } }}, 
                                        { minLevel = 100,maxLevel =160, monList = { { id = 3882, objid = 400082, mapid = 211, name = "������Ӿ�", Place = "���Ϸ�" , posName = "@npc_4000821"  }, { id = 3883, objid = 400083, mapid = 211, name = "�����ʦ", 	Place = "������" , posName = "@npc_4000831"  }, { id = 3884, objid = 400084, mapid = 211, name = "���Ӫ����", Place = "����" ,		posName = "@npc_4000841"  }, { id = 3885, objid = 400085, mapid = 211, name = "�������Ӫ���", Place = "������" , posName = "@npc_4000851"  } }},
                                       
}

--**********************************
--�о��¼�
--**********************************
function x270351_ProcEnumEvent( sceneId, selfId, NPCId, MissionId )

	local level = GetLevel( sceneId,selfId)
	if(level < x270351_g_PlayerMinLevel) then
		 return 1;
	end

    local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x270351_g_MissionId);
    if(bHaveMission <= 0 and level >= x270351_g_PlayerMinLevel) then
        local state = GetQuestStateNM(sceneId,selfId,NPCId,x270351_g_MissionId)
        AddQuestNumText(sceneId,x270351_g_MissionId,x270351_g_MissionName,state, 30);
    end
end

--**********************************
--������ں���
--**********************************
function x270351_ProcEventEntry(sceneId, selfId, NPCId, MissionId, nExtIdx)	--����������ִ�д˽ű�
	--print("nExtIdx = ",nExtIdx)
	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x270351_g_MissionId)
	if( bHaveMission > 0) then
		local bDone = x270351_CheckSubmit(sceneId, selfId, NPCId)
		if(bDone > 0) then
			if nExtIdx ~= -1 then
				x270351_DispatchCompletedInfo( sceneId, selfId, NPCId, nExtIdx) --���������ʾ
			end
		else
			if nExtIdx ~= -1 then
				x270351_DispatchContinueInfo( sceneId, selfId, NPCId ) --δ���������ʾ
			end
			if sceneId ~=150 then
						SetMonsterCamp(sceneId,NPCId,21)                                                        
						NpcTalk(sceneId, NPCId, "��Ȼ���Ѱ�¶��ֻ�ú���ƴ���������ƣ�", -1)                     
						BeginQuestEvent(sceneId)                                                                
						AddQuestText(sceneId,"\t��ǰ�Ĺ���ͻȻ¶��һ���׶�����������������")                  
						EndQuestEvent()                                                                         
						DispatchQuestEventList(sceneId, selfId, NPCId, x203330_g_ScriptId, x203330_g_MissionId);
			end
		end
	else
		if nExtIdx == 1000 then
    	local level = GetLevel( sceneId, selfId)
        
        if level > x270351_g_PlayerMaxLevel then
    		BeginQuestEvent( sceneId)
                AddQuestText( sceneId, "���Ѿ���һ������70���Ĵ����ˣ����С�»��ǲ����ͷ����ˡ�");
    		EndQuestEvent( sceneId)
    		DispatchQuestEventList( sceneId, selfId, NPCId)
            return 1
        end
			x270351_DispatchMissionInfo( sceneId, selfId, NPCId )	--������Ϣ��ʾ
		else
	    	local level = GetLevel( sceneId, selfId)
	        
	        if level > x270351_g_PlayerMaxLevel then
	    		BeginQuestEvent( sceneId)
	                AddQuestText( sceneId, "���Ѿ���һ������70���Ĵ����ˣ����С�»��ǲ����ͷ����ˡ�");
	    		EndQuestEvent( sceneId)
	    		DispatchQuestEventList( sceneId, selfId, NPCId)
	            return 1
	        end
	        
	        local Times = x270351_GetTimes( sceneId, selfId)
	        --print("Times",Times)
	        if mod(Times,10) == 0 then
				x270351_DispatchMenuInfo( sceneId, selfId, NPCId )	--������Ϣ��ʾ
			else
				x270351_DispatchMissionInfo( sceneId, selfId, NPCId )	--������Ϣ��ʾ
			end
		end
	end
end

---------------------------------------------------------------------------------------------------
--����������
---------------------------------------------------------------------------------------------------
function x270351_ProcAcceptCheck( sceneId, selfId, npcId )
	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x270351_g_MissionId);
	if(bHaveMission > 0) then
		return 0;
	else
		return 1;
	end
end

-- �Ƿ������������ĳͷ�ʱ����
function x270351_IsPunish( sceneId, selfId)
    return 0
end

function x270351_DenoteMonsterPosition( sceneId, selfId, BagIndex )

	local misIndex = GetQuestIndexByID(sceneId, selfId, x270351_g_MissionId)
	local monidx = GetQuestParam( sceneId, selfId, misIndex, 1)
    local index = GetQuestParam( sceneId, selfId, misIndex, 2)
    ----local Place = x270351_g_MonsterTable[index].monList[monidx].Place
    local name = x270351_g_MonsterTable[index].monList[monidx].name
    local posName = x270351_g_MonsterTable[index].monList[monidx].posName
    local mapId = x270351_g_MonsterTable[index].monList[monidx].mapid
    
    if mapId ~= sceneId then
    	local msg = format( "����ǰ��%s��ʹ������׷�ٷ�", posName)
    	Msg2Player( sceneId, selfId, msg, 8, 3)
    else
    	local objId = x270351_g_MonsterTable[index].monList[monidx].objid
    	
    	local obj =  FindMonsterByGUID(sceneId, objId)
    	if IsObjValid(sceneId,obj) ~= 1 then
    		return
    	end
    	    	 
    	local x, z = GetWorldPos( sceneId, obj)
    	
		Msg2Player(sceneId,selfId,format("%s���ڣ�%d,%d�������ε���", name, x, z), 8,3)
    end
   
end



function x270351_DelRequireMissionItem( sceneId, selfId)
	if DelItem( sceneId, selfId, x270351_g_AcceptItemID, 1) == 0 then
		Msg2Player( sceneId, selfId, format( "������ȥ�ӻ����˴�����@item_%d#cffcf00!������������", x270351_g_AcceptItemID), 8, 3)
        return 0
    end
    return 1
end      
     
function x270351_AddAcceptMissionItem( sceneId, selfId)

	BeginAddItem(sceneId)
    AddBindItem( sceneId, x270351_g_SubmitItemID,1 )
    local ret = EndAddItem(sceneId,selfId)
    
	local name = GetName(sceneId,selfId)
	if name == nil then
		name = "ErrorName"
	end

    if ret > 0 then
    	Msg2Player( sceneId, selfId, format( "������1��@item_%d!", x270351_g_SubmitItemID), 8, 3)
        AddItemListToPlayer(sceneId,selfId)
	else
		LuaScenceM2Player(sceneId, selfId, "#cffcf00��Ʒ���������޷��õ�������ߣ�", name , 2,1)
	    LuaScenceM2Player(sceneId, selfId, "#cffcf00��Ʒ���������޷��õ�������ߣ�", name , 3,1)
	end
	return ret
		        
end

function x270351_GetQuestIndex( sceneId, selfId, NPCId)
	local level = GetLevel( sceneId, selfId)
	local teamSize = GetNearTeamCount( sceneId, selfId)
    for i = 0, teamSize - 1 do
    	local memberId = GetNearTeamMember( sceneId, selfId, i)
        if memberId ~= selfId and IsPlayerStateNormal( sceneId, memberId) == 1 then
            if IsInDist( sceneId, selfId, NPCId, 30) == 1 then  --����NPC 30������ 
                local teamLevel = GetLevel( sceneId, memberId)
                if abs( teamLevel - level) <= 5 then
                   	if IsHaveQuestNM(sceneId, memberId, x270351_g_MissionId) == 1 then
                       	local misIndex = GetQuestIndexByID( sceneId, memberId, x270351_g_MissionId)
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
function x270351_GetQuest( sceneId, selfId, NPCId, index, monIndex)
    local idx = index
    local midx = monIndex
    if IsHaveQuestNM(sceneId, selfId, x270351_g_MissionId) == 0 then
        -- ����ܷ���ȡ
        local ret, strMsg = CallScriptFunction( 270355, "CountCheck", sceneId, selfId)
        if ret == 0 then
            Msg2Player( sceneId, selfId, strMsg, 8, 3)
            return 0, 0
        end

		if x270351_DelRequireMissionItem( sceneId, selfId) <= 0 then                 
			return 0, 0                                                                    
		end
		local ret = AddQuest( sceneId, selfId, x270351_g_MissionId, x270351_g_ScriptId, 1, 0, 0, 1)
    	if(ret == 0) then
            Msg2Player( sceneId, selfId, "�����������������ʧ��", 8, 3)
    		return 0, 0
    	end
		-- ���¼���
        CallScriptFunction( 270355, "UpdateCount", sceneId, selfId, 1)
                         		                                                         
		if x270351_AddAcceptMissionItem( sceneId, selfId) <= 0 then 
    		return 0, 0
    	end

        

        if index == 0 and monIndex == 0 then
        	idx, midx = x270351_GetQuestIndex(sceneId, selfId, NPCId)
        	if idx == 0 and midx == 0 then
            -- get player level
            local level = GetLevel( sceneId, selfId)
            for i, item in x270351_g_MonsterTable do
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
        
        if idx < 1 or idx > getn(x270351_g_MonsterTable) then
        	idx = 1
        	local level = GetLevel( sceneId, selfId)
            for i, item in x270351_g_MonsterTable do
                if level >= item.minLevel and level <= item.maxLevel then
                    idx = i
                    break
                end  
            end          	
        end
        if midx < 1 or midx > getn(x270351_g_MonsterTable[idx].monList) then
        	midx = 1
        end
        
        local misIndex = GetQuestIndexByID( sceneId, selfId, x270351_g_MissionId)
        SetQuestByIndex( sceneId, selfId, misIndex, 1, midx)
        SetQuestByIndex( sceneId, selfId, misIndex, 2, idx)

        -- ����������ɱ��
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)

        -- ��ʾ��ʾ��Ϣ
        Msg2Player( sceneId, selfId, x270351_g_strAcceptMission, 8, 3)
        -- ϵͳ��Ϣ
        Msg2Player( sceneId, selfId, x270351_g_strAcceptMission, 8, 2)

    	x270351_QuestLogRefresh( sceneId, selfId, x270351_g_MissionId )

        -- ��ʾ������Ϣ
        x270351_ShowMissionInfo( sceneId, selfId, NPCId)

        SetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_LEADER, 0)
        SetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_ASSIST, 0)

        -- д��־
        GamePlayScriptLog( sceneId, selfId, 611)
    end

    return idx, midx
end
---------------------------------------------------------------------------------------------------
--��������
---------------------------------------------------------------------------------------------------
function x270351_ProcQuestAccept( sceneId, selfId, NPCId, missionId )
	if IsHaveQuestNM(sceneId, selfId, x270351_g_MissionId) == 0 then
		----------------------------------------------------------------------------
		if GetBagSpace(sceneId,selfId) <= 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"���������������������ٽ�ȡ����")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return
		end		
		
        local index = 0
        local monIndex = 0
        if GetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_LEADER) == 0 then
            index, monIndex = x270351_GetQuest( sceneId, selfId, NPCId, 0, 0)

            local level = GetLevel( sceneId, selfId)
            -- �������Ա�������
            --local teamSize = GetNearTeamCount( sceneId, selfId)
            --for i = 0, teamSize - 1 do
            --    local memberId = GetNearTeamMember( sceneId, selfId, i)
            --    if memberId ~= selfId and IsPlayerStateNormal( sceneId, memberId) == 1 then
            --        if IsInDist( sceneId, selfId, memberId, 5) == 1 then
            --            local teamLevel = GetLevel( sceneId, memberId)
            --            if abs( teamLevel - level) <= 5 and teamLevel >= 20 and teamLevel < 70 and IsInDist( sceneId, memberId, NPCId, 3) == 1 then
            --                x270351_DispatchMissionInfo( sceneId, memberId, NPCId)
            --                SetPlayerRuntimeData( sceneId, memberId, RD_GUILDCONTEND_KILL_LEADER, index)
            --                SetPlayerRuntimeData( sceneId, memberId, RD_GUILDCONTEND_KILL_ASSIST, monIndex)
            --            else
            --                Msg2Player( sceneId, selfId, format( "���Ķ���%s�����ȼ�������δ����һ����ȡ��������", GetName( sceneId, memberId) ), 8, 3)
            --            end
            --        else
            --            Msg2Player( sceneId, selfId, format( "���Ķ���%s���������Զ��δ����һ����ȡ��������", GetName( sceneId, memberId) ), 8, 3)
            --        end
            --    end
            --end
        else
            local index = GetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_LEADER)
            local monIndex = GetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_ASSIST)
            x270351_GetQuest( sceneId, selfId, NPCId, index, monIndex)
        end
    else
		local misIndex = GetQuestIndexByID(sceneId, selfId, x270351_g_MissionId)
		local completed = GetQuestParam(sceneId, selfId, misIndex, x270351_MP_ISCOMPLETE)

		if completed == 1 then
			local result = x270351_CheckPlayerBagFull(sceneId,selfId)
			if result == 1 then
                -- ɾ������
                if DelItem( sceneId, selfId, x270351_g_ItemID, 1) == 0 then
                    Msg2Player( sceneId, selfId, format( "�ܱ�Ǹ����û��@item_%d#cffcc00", x270351_g_ItemID), 8, 3)
                    return
                end
                DelItem( sceneId, selfId, x270351_g_SubmitItemID, 1) 
		    				DelQuest(sceneId, selfId, x270351_g_MissionId)
                --CallScriptFunction( 203802, "FinishSanhuanling", sceneId, selfId)
                
                Msg2Player( sceneId, selfId, x270351_g_strFinishMission, 8, 2)
                Msg2Player( sceneId, selfId, x270351_g_strFinishMission, 8, 3)

		    	x270351_GetBonus( sceneId,selfId,NPCId, 0, 5)

                CallScriptFunction( 270355, "UpdateCount", sceneId, selfId, 4)

                -- д��־
                GamePlayScriptLog( sceneId, selfId, 612)
		    else
		    	BeginQuestEvent( sceneId )
				AddQuestText( sceneId,"����������")
				EndQuestEvent()
				DispatchQuestTips(sceneId, selfId);
		    end

		else
			BeginQuestEvent( sceneId )
				AddQuestText( sceneId,"����û����ɣ�")
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId);
		end
	end
end

---------------------------------------------------------------------------------------------------
--��������
---------------------------------------------------------------------------------------------------
function x270351_ProcQuestAbandon( sceneId, selfId, MissionId)
	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x270351_g_MissionId);
	if bHaveMission > 0 then
		local misIndex = GetQuestIndexByID(sceneId, selfId, x270351_g_MissionId); 
		DelQuest(sceneId, selfId, x270351_g_MissionId);
		DelItem( sceneId, selfId, x270351_g_SubmitItemID, 1)
		
        BeginQuestEvent( sceneId)
        AddQuestText( sceneId, x270351_g_strAbandonMission)
        EndQuestEvent( sceneId)
        DispatchQuestTips( sceneId, selfId)
        Msg2Player( sceneId, selfId, x270351_g_strAbandonMission, 8, 2)
	end
end

---------------------------------------------------------------------------------------------------
--��������Ƿ���ύ
---------------------------------------------------------------------------------------------------
function x270351_CheckSubmit( sceneId, selfId, NPCId)

	local misIndex = GetQuestIndexByID(sceneId, selfId, x270351_g_MissionId);
	return GetQuestParam(sceneId, selfId, misIndex, x270351_MP_ISCOMPLETE);

end

---------------------------------------------------------------------------------------------------
--��ý���
---------------------------------------------------------------------------------------------------
function x270351_GetBonus( sceneId, selfId,NpcID, SelectId, times)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x270351_g_MissionId)
	--��������
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
	local exp =( 1000 * 0.01 * level * x270351_g_ExpBonus[n]) * times
    if exp > 0 then
		AddExp( sceneId, selfId, exp)
  		Msg2Player( sceneId, selfId, format( "���#R����%d��#cffcf00�Ľ���", exp), 8, 2)
        BeginQuestEvent( sceneId)
        AddQuestText( sceneId, format( "���#R����%d��#cffcf00�Ľ���", exp) )
        EndQuestEvent( sceneId)
        DispatchQuestTips( sceneId, selfId)
	end

	--������Ǯ1
	if x270351_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x270351_g_BonusMoney1 * level * times)
	    Msg2Player(sceneId,selfId,format("���#R����#{_MONEY%d}#cffcf00�Ľ�����", x270351_g_BonusMoney1 * level),4,2)
        Msg2Player(sceneId,selfId,format("���#R����#{_MONEY%d}#cffcf00�Ľ���", x270351_g_BonusMoney1 * level),8,3)
	end

	--������Ǯ2
	if x270351_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x270351_g_BonusMoney2 * level)
	    Msg2Player(sceneId,selfId,format("���#R����#{_MONEY%d}#cffcf00�Ľ�����", x270351_g_BonusMoney2 * level),4,2)
        Msg2Player(sceneId,selfId,format("���#R����#{_MONEY%d}#cffcf00�Ľ���", x270351_g_BonusMoney2 * level),8,3)
	end

	--������Ǯ1
	if x270351_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x270351_g_BonusMoney3 )
	    Msg2Player(sceneId,selfId,format("��ý�#{_MONEY%d}�Ľ�����", x270351_g_BonusMoney3),4,2)
	end

	--��������
	if x270351_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
		nRongYu = nRongYu + x270351_g_BonusMoney4
		SetRongYu( sceneId, selfId, nRongYu )
		Msg2Player(sceneId,selfId,format("��ý�������%d�Ľ�����", x270351_g_BonusMoney4),4,2)
	end

	--��͢����
	if x270351_g_BonusMoney5 > 0 then
		local nShengWang = GetShengWang( sceneId, selfId )
		nShengWang = nShengWang + x270351_g_BonusMoney5
		SetShengWang( sceneId, selfId, nShengWang )
		Msg2Player(sceneId,selfId,format("��ó�͢����%d�Ľ�����", x270351_g_BonusMoney5),4,2)
	end

	--��͢����
	if x270351_g_BonusMoney6 > 0 then
		AddHonor(sceneId,selfId,x270351_g_BonusMoney6)
		Msg2Player(sceneId,selfId,format("�������ֵ%d�Ľ�����", x270351_g_BonusMoney6),4,2)
	end

 	--�����̶���Ʒ
		for i, item in x270351_g_BonusItem do
 		BeginAddItem(sceneId)
		AddItem( sceneId, item.item, item.n )
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
			AddItemListToPlayer(sceneId,selfId)
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"��Ʒ���������޷��õ�������Ʒ��")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end
    end

	--������ѡ��Ʒ
	for i, item in x270351_g_BonusChoiceItem do
	    if item.item == SelectId then
	        BeginAddItem(sceneId)
			AddItem( sceneId, item.item, item.n )
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��Ʒ���������޷��õ�������Ʒ��")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end

			--��ȡ��أ��뷵�أ���ֹ�ظ����
			return
		end
    end

end

---------------------------------------------------------------------------------------------------
--�ύ���񣬲��������Ƿ���ɻ���������ʾ���������Ϣ�������������Ϣ
---------------------------------------------------------------------------------------------------
function x270351_ProcQuestSubmit( sceneId, selfId, NPCId, selectRadioId, MissionId)

	--�ж��Ƿ�������
	local bHaveMission = IsHaveQuestNM(sceneId, selfId, x270351_g_MissionId);
	if bHaveMission > 0 then

		local misIndex = GetQuestIndexByID(sceneId, selfId, x270351_g_MissionId)
		local completed = GetQuestParam(sceneId, selfId, misIndex, x270351_MP_ISCOMPLETE)

		if completed == 1 then
			local result = x270351_CheckPlayerBagFull(sceneId,selfId)
			if result == 1 then
		    	DelQuest(sceneId, selfId, x270351_g_MissionId)
                --CallScriptFunction( 203802, "FinishSanhuanling", sceneId, selfId)

                BeginQuestEvent( sceneId)
                AddQuestText( sceneId, x270351_g_strFinishMission)
                EndQuestEvent( sceneId)
                DispatchQuestTips( sceneId, selfId)
                Msg2Player( sceneId, selfId, x270351_g_strFinishMission, 8, 2)

		    	x270351_GetBonus( sceneId,selfId,NPCId,selectRadioId, 1)
					DelItem( sceneId, selfId, x270351_g_SubmitItemID, 1)
                -- д��־
                GamePlayScriptLog( sceneId, selfId, 612)
		    else
		    	BeginQuestEvent( sceneId )
				AddQuestText( sceneId,"����������")
				EndQuestEvent()
				DispatchQuestTips(sceneId, selfId);
		    end

		else
			BeginQuestEvent( sceneId )
				AddQuestText( sceneId,"����û����ɣ�")
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId);
		end
	else

		BeginQuestEvent( sceneId )
			AddQuestText( sceneId,"���񲻴��ڣ���ȡ������Ϣʧ�ܣ�")
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId);

		return
	end

end

---------------------------------------------------------------------------------------------------
--�����Ұ�������
---------------------------------------------------------------------------------------------------
function x270351_CheckPlayerBagFull( sceneId ,selfId)


	local result = 1

	local j = 0

	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������

	--��ͨ�Ľ������
	BeginAddItem(sceneId)
	for j, item in x270351_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
    end

    --������ѡ��Ʒ
	for j, item in x270351_g_BonusChoiceItem do
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

-- �����������ʾ������Ϣ
function x270351_ShowMissionInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)
        -- ��������
		AddQuestText(sceneId, "#Y"..x270351_g_MissionName)

		--����Ŀ��
		--AddQuestText( sceneId, "#Y����Ŀ�꣺")
		AddQuestText( sceneId, "\t��Щ���ﲢ������һ���ط�ͣ�������ǻ��ڶ�Ӧ�ĵ�ͼ���ε���\n\t�����ʹ���Ҹ����#G����׷�ٷ�#W��������������ľ���λ�á�")
        local misIndex = GetQuestIndexByID( sceneId, selfId, x270351_g_MissionId)
        local monidx = GetQuestParam( sceneId, selfId, misIndex, 1)
        local index = GetQuestParam( sceneId, selfId, misIndex, 2)
        AddQuestText( sceneId, "\n#Y����Ŀ�꣺")
        AddQuestText( sceneId, format( x270351_g_MissionTarget, x270351_g_MonsterTable[ index].monList[ monidx].posName, x270351_g_MonsterTable[ index].monList[ monidx].name, 0) )
		AddQuestText( sceneId, " ")
	EndQuestEvent()
    DispatchQuestEventList( sceneId, selfId, NPCId)
end

function x270351_DispatchMenuInfo( sceneId, selfId, NPCId)
	BeginQuestEvent(sceneId)

		--������Ϣ
		AddQuestText(sceneId, "#Y"..x270351_g_MissionName)
		AddQuestText(sceneId, "\t���һ��ͨ�����ͬ�����һ����������ÿ��ͨ����������10����ÿ��������6�֡�\n\t��������ȡ���ǵ�1������#G����һ�α��ܵ�������������#W��#Gһ��ͨ����#W����ȷ��Ҫ��ȡ��������(ͨ����)��\n��#Gͨ����#W��������ó�����ӻ����˴����򡣣�\n#Yע��#W��\n\t��ȡ1�ֱ�����󣬵���ֻ������������������һ�Ρ�\n\t��ȡ4�ֱ�����󣬵��첻��������������������")
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x270351_g_MissionId)
		AddQuestNumText(sceneId,x270351_g_MissionId,"��Ҫ��ȡ����ͨ����",13,1000 )	
	
		EndQuestEvent()
	 DispatchQuestEventList( sceneId, selfId, NPCId)
	 
	--DispatchQuestInfoNM(sceneId, selfId, NPCId, x270351_g_ScriptId, x270351_g_MissionId)
end
---------------------------------------------------------------------------------------------------
--��ͻ��˷���������Ϣ
---------------------------------------------------------------------------------------------------
function x270351_DispatchMissionInfo( sceneId, selfId, NPCId )

	local level = GetLevel(sceneId,selfId);
	
	BeginQuestEvent(sceneId)

		--������Ϣ
		AddQuestText(sceneId, "#Y"..x270351_g_MissionName)
		AddQuestText(sceneId, x270351_g_MissionDescription)
		--AddQuestText(sceneId, "\n#GС��ʾ")
		AddQuestText(sceneId, x270351_g_MissionHelp)

		--��������Ϣ

		--1������
		--if x270351_g_ExpBonus> 0 then
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
		local exp =( 1000 * 0.01 * level * x270351_g_ExpBonus[n])
		if exp > 0 then
			AddQuestExpBonus( sceneId, exp )
		end

		--2����Ǯ1
		if x270351_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1( sceneId, x270351_g_BonusMoney1 * level)
		end

		--3����Ǯ2
		if x270351_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2( sceneId, x270351_g_BonusMoney2 * level)
		end
		--4����Ǯ3
		if x270351_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3( sceneId, x270351_g_BonusMoney3 )
		end

		--��������
		if x270351_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4( sceneId, x270351_g_BonusMoney4 )
		end

		--��͢����
		if x270351_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5( sceneId, x270351_g_BonusMoney5 )
		end

		--����ֵ
		if x270351_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6( sceneId, x270351_g_BonusMoney6 )
		end


		--5���̶���Ʒ
		for i, item in x270351_g_BonusItem do
		   	AddQuestItemBonus( sceneId, item.item, item.n)
	    end

		--6����ѡ��Ʒ
		for i, item in x270351_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus( sceneId, item.item, item.n)
	    end

	EndQuestEvent()
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x270351_g_ScriptId, x270351_g_MissionId)
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x270351_DispatchContinueInfo( sceneId, selfId, NPCId )

	local misIndex = GetQuestIndexByID(sceneId, selfId, x270351_g_MissionId);

	BeginQuestEvent(sceneId)

		--���������Ϣ
		AddQuestText(sceneId,"#Y"..x270351_g_MissionName)
		AddQuestText(sceneId,x270351_g_MissionContinue)
		AddQuestText(sceneId," ")

	EndQuestEvent()
	DispatchQuestEventList( sceneId, selfId, NPCId)
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x270351_DispatchCompletedInfo( sceneId, selfId, NPCId, nExtIdx)
    if nExtIdx == 30 then
        BeginQuestEvent(sceneId)
            AddQuestText(sceneId,"#Y"..x270351_g_MissionName)
            AddQuestText(sceneId, "\t��ô�����������Щ���\n\t�����ʹ��#G������#W��������񣬽�����#G5��#W�ľ��飬����#G5��#W���������#G���������ڽ���̳ǳ��ۣ�\n\t#W��Ȼ����Ҳ����ֱ��������񣬻�������ľ��飬ֻ����һ�����������" )
            AddQuestText(sceneId," ")

            local state = GetQuestStateNM( sceneId, selfId, NPCId, x270351_g_MissionId)
            AddQuestNumText( sceneId, x270351_g_MissionId, "ʹ���������������", 3, 31)
            AddQuestNumText( sceneId, x270351_g_MissionId, "ֱ���������", 3, 32)
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, NPCId)
    elseif nExtIdx == 31 then
        if GetQuestData(sceneId, selfId, MD_FUBEN_QIULONGDAO_DAYCOUNT[1], MD_FUBEN_QIULONGDAO_DAYCOUNT[2], MD_FUBEN_QIULONGDAO_DAYCOUNT[3] ) >= 21
            and x270351_GetTimes( sceneId, selfId) > 5 then
            Msg2Player( sceneId, selfId, "���ܲ�����ʹ����������������ˡ�", 8, 3)
            return
        end
        local count = GetQuestData( sceneId, selfId, MD_FUBEN_QIULONGDAO_TODAYCOUNT[1], MD_FUBEN_QIULONGDAO_TODAYCOUNT[2], MD_FUBEN_QIULONGDAO_TODAYCOUNT[3] )
        local times = x270351_GetTimes( sceneId, selfId)
        --print("count",count,times)
        if GetQuestData( sceneId, selfId, MD_FUBEN_QIULONGDAO_TODAYCOUNT[1], MD_FUBEN_QIULONGDAO_TODAYCOUNT[2], MD_FUBEN_QIULONGDAO_TODAYCOUNT[3] ) >= 6 
            and x270351_GetTimes( sceneId, selfId) > 6 then
            Msg2Player( sceneId, selfId, "���첻����ʹ����������������ˡ�", 8, 3)
            return
        end
        BeginQuestEvent(sceneId)
            AddQuestText(sceneId,"#Y"..x270351_g_MissionName)
            AddQuestText(sceneId, x270351_g_MissionCompleted1)
            AddQuestText(sceneId, "\t��ȷ��Ҫʹ��������ô��" )
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
            local exp =( 1000 * 0.01 * level * x270351_g_ExpBonus[n])
            if exp > 0 then
                AddQuestExpBonus( sceneId, exp * 5)
            end
            if x270351_g_BonusMoney1 > 0 then
                AddQuestMoneyBonus1(sceneId, x270351_g_BonusMoney1 * level * 5)
            end

        EndQuestEvent()
        DispatchQuestInfoNM(sceneId, selfId, NPCId, x270351_g_ScriptId, x270351_g_MissionId)
    elseif nExtIdx == 32 then
	BeginQuestEvent(sceneId)

		--���������Ϣ
		AddQuestText(sceneId,"#Y"..x270351_g_MissionName)
		AddQuestText(sceneId,x270351_g_MissionCompleted)
		AddQuestText(sceneId," ")

  		--��������Ϣ

		--1������
		-- if x270351_g_ExpBonus > 0 then
			-- AddQuestExpBonus(sceneId, x270351_g_ExpBonus[n])
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
		local exp =( 1000 * 0.01 * level * x270351_g_ExpBonus[n])
		if exp > 0 then
			AddQuestExpBonus(sceneId, exp )
		end

		--2����Ǯ1
		if x270351_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x270351_g_BonusMoney1 * level)
		end

		--3����Ǯ2
		if x270351_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x270351_g_BonusMoney2 * level)
		end
		--4����Ǯ3
		if x270351_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x270351_g_BonusMoney3 )
		end

		--��������
		if x270351_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x270351_g_BonusMoney4 )
		end

		--��͢����
		if x270351_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x270351_g_BonusMoney5 )
		end

		--����ֵ
		if x270351_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x270351_g_BonusMoney6 )
		end


		--5���̶���Ʒ
		for i, item in x270351_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	    end

		--6����ѡ��Ʒ
		for i, item in x270351_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	    end
	EndQuestEvent()
	--DispatchQuestEventList(sceneId,selfId,NPCId);
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x270351_g_ScriptId, x270351_g_MissionId);
    end
end

---------------------------------------------------------------------------------------------------
--���ﱻɱ����Ϣ����
---------------------------------------------------------------------------------------------------
function x270351_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

    if IsPlayerStateNormal( sceneId, selfId) ~= 1 then
        return
    end
     -------------------------------------------------------
    --����ӵĸ������Ҳ�������������Ϣ
    local x,z = GetWorldPos(sceneId, selfId)
    local teamId = GetTeamId(sceneId, selfId)
    local count = GetNearPlayerCount(sceneId, selfId, x, z, 30)
    for i = 0, count - 1 do
    	local memberId = GetNearPlayerMember( sceneId, selfId, i)
    	if memberId ~= selfId and IsPlayerStateNormal( sceneId, memberId) == 1 then
        	local teamId1 = GetTeamId(sceneId, memberId)
        	if teamId ~= teamId1 or teamId == -1 or teamId1 == -1 then
	            if IsHaveQuestNM(sceneId, memberId, x270351_g_MissionId) == 1 then
	                local misIndex = GetQuestIndexByID( sceneId, memberId, x270351_g_MissionId)
	                local monidx = GetQuestParam( sceneId, memberId, misIndex, 1)
                    local index = GetQuestParam( sceneId, memberId, misIndex, 2)
                    local name = x270351_g_MonsterTable[index].monList[monidx].name
                    if objdataId == x270351_g_MonsterTable[ index].monList[ monidx].id then
		                SetQuestByIndex( sceneId, memberId, misIndex, 0, 1)
			            SetQuestByIndex( sceneId, memberId, misIndex, 7, 1)
			            SetQuestByIndex( sceneId, memberId, misIndex, 6, 1)
			            Msg2Player( sceneId, memberId, format( "%s�ѱ����𣬡����ˡ���������(ͨ����)�������", name), 8, 3)
			            Msg2Player( sceneId, memberId, format( "%s�ѱ����𣬡����ˡ���������(ͨ����)�������", name), 8, 2)
			            x270351_QuestLogRefresh( sceneId, memberId, x270351_g_MissionId)
			        end
	        	end
	        end
        end
    end
       
    
    
    -------------------------------------------------------
    local misIndex = 0
    local teamSize = GetNearTeamCount( sceneId, selfId)
    -- print( "��������������"..teamSize)

    if teamSize <= 1 then -- ����ӣ�����������
        
        if IsHaveQuest( sceneId, selfId, x270351_g_MissionId) <= 0 then
            return
        end
        misIndex = GetQuestIndexByID( sceneId, selfId, x270351_g_MissionId)
        local monidx = GetQuestParam( sceneId, selfId, misIndex, 1)
        local index = GetQuestParam( sceneId, selfId, misIndex, 2)
        local name = x270351_g_MonsterTable[index].monList[monidx].name
        if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
            -- ������������
            return
        end

        if objdataId == x270351_g_MonsterTable[ index].monList[ monidx].id then
            SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
            SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
            SetQuestByIndex( sceneId, selfId, misIndex, 6, 1)
            Msg2Player( sceneId, selfId, format( "%s�ѱ����𣬡����ˡ���������(ͨ����)�������", name), 8, 3)
            Msg2Player( sceneId, selfId, format( "%s�ѱ����𣬡����ˡ���������(ͨ����)�������", name), 8, 2)
        else
            -- ���ɱ���Ĳ�������Ŀ���
            return
        end

        x270351_QuestLogRefresh( sceneId, selfId, x270351_g_MissionId)
    else
        for i = 0, teamSize - 1 do
            local memberId = GetNearTeamMember( sceneId, selfId, i)
            if memberId >= 0 and IsPlayerStateNormal( sceneId, memberId) == 1 then
                if IsHaveQuest( sceneId, memberId, x270351_g_MissionId) > 0 then -- ����ó�Ա��������������
                    misIndex = GetQuestIndexByID( sceneId, memberId, x270351_g_MissionId)
                    local monidx = GetQuestParam( sceneId, memberId, misIndex, 1)
                    local index = GetQuestParam( sceneId, memberId, misIndex, 2)
                    local name = x270351_g_MonsterTable[index].monList[monidx].name
                    if GetQuestParam( sceneId, memberId, misIndex, 0) == 0 or GetQuestParam( sceneId, memberId, misIndex, 7) == 0 then
                        local missionMonster = 1
                        if objdataId == x270351_g_MonsterTable[ index].monList[ monidx].id then
                            SetQuestByIndex( sceneId, memberId, misIndex, 0, 1)
                            SetQuestByIndex( sceneId, memberId, misIndex, 7, 1)
                            SetQuestByIndex( sceneId, memberId, misIndex, 6, 1)
                            Msg2Player( sceneId, memberId, format( "%s�ѱ����𣬡����ˡ���������(ͨ����)�������", name), 8, 3)
                            Msg2Player( sceneId, memberId, format( "%s�ѱ����𣬡����ˡ���������(ͨ����)�������", name), 8, 2)
                        else
                            missionMonster = 0
                        end

                        if missionMonster == 1 then
                            x270351_QuestLogRefresh( sceneId, memberId, x270351_g_MissionId)
                        end
                    end
                end
            end
        end
    end
end

---------------------------------------------------------------------------------------------------
--��Ʒ�ı�
---------------------------------------------------------------------------------------------------
function x270351_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
--	local misIndex = GetQuestIndexByID(sceneId, selfId, x270351_g_MissionId);
--	
--	if(itemdataId == x270351_TARGET_OBJID1 ) then
--		local targetcount	= GetQuestParam(sceneId, selfId, misIndex, x270351_MP_TARGET1);
--		if(targetcount < x270351_g_ExtTarget[x270351_MP_TARGET1+1].n) then
--			targetcount	= targetcount + 1;
--			BeginQuestEvent(sceneId);
--			AddQuestText(sceneId,"�ѻ��"..x270351_g_ExtTarget[x270351_MP_TARGET1+1].target..":"..targetcount.."/"..x270351_g_ExtTarget[x270351_MP_TARGET1+1].n);
--			EndQuestEvent();
--			DispatchQuestTips(sceneId, selfId);
--			SetQuestByIndex(sceneId, selfId, misIndex, x270351_MP_TARGET1, targetcount )
--		end
--	end
--	
--	--��������Ƿ����
--	local targetcount1	= GetQuestParam(sceneId, selfId, misIndex, x270351_MP_TARGET1);
--	if(targetcount1 == x270351_g_ExtTarget[x270351_MP_TARGET1+1].n) then
--		SetQuestByIndex(sceneId, selfId, misIndex, x270351_MP_ISCOMPLETE, 1 )
--	end
end

---------------------------------------------------------------------------------------------------
--����NPC�¼�
---------------------------------------------------------------------------------------------------
function x270351_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

	if npcGuid == x270351_SubmitNPCGUID then
		local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x270351_g_MissionId);
		if(bHaveMission > 0) then
			local state = GetQuestStateNM(sceneId,selfId,npcId,x270351_g_MissionId)
			AddQuestNumText(sceneId, x270351_g_MissionId, x270351_g_MissionName,state,30);
		end
	end

end

---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x270351_QuestLogRefresh( sceneId, selfId, MissionId)
    if IsHaveQuest( sceneId, selfId, x270351_g_MissionId) == 0 then
        return
    end

	local misIndex = GetQuestIndexByID( sceneId, selfId, x270351_g_MissionId)
    local monidx = GetQuestParam( sceneId, selfId, misIndex, 1)
    local index = GetQuestParam( sceneId, selfId, misIndex, 2)
    local kill = GetQuestParam( sceneId, selfId, misIndex, 6)
    
    --�����޸�������ֹ������ʾ��ȫ
    if index < 1 or index > getn(x270351_g_MonsterTable) then
    	index = 1
    	local level = GetLevel( sceneId, selfId)
        for i, item in x270351_g_MonsterTable do
            if level >= item.minLevel and level <= item.maxLevel then
                index = i
                SetQuestByIndex(sceneId, selfId, misIndex, 2, index )
                break
            end
        end    
    end
    
    if monidx < 1 or monidx > getn(x270351_g_MonsterTable[index].monList) then
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
		local exp =( 1000 * 0.01 * level * x270351_g_ExpBonus[n])
		if exp > 0 then
			AddQuestExpBonus( sceneId, exp)
		end
        if x270351_g_BonusMoney1 > 0 then
            AddQuestMoneyBonus1( sceneId, x270351_g_BonusMoney1 * level)
        end

        AddQuestLogCustomText( sceneId,
                                "",                             -- ����
                                format( "�����ˡ���������(ͨ����)(%d/10)", x270351_GetTimes( sceneId, selfId) ),           -- ��������
                                format( x270351_g_strMissionTarget, x270351_g_MonsterTable[ index].monList[ monidx].posName, x270351_g_MonsterTable[ index].monList[ monidx].name, kill),
                                "@npcsp_[��������]�����_126040",                             --����NPC
                                x270351_g_MissionBook,
                                x270351_g_MissionDescription,
                                ""
                                )

	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, x270351_g_MissionId)
end

function x270351_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    x270351_QuestLogRefresh( sceneId, selfId, MissionId)
end

---------------------------------------------------------------------------------------------------
--ǿ�м�����
---------------------------------------------------------------------------------------------------
function x270351_OnForceAddMission( sceneId, selfId, npcId, MissionId)
end

-- ��ý�����������
function x270351_GetDate( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_XUNAN_DATE[ 1], MD_XUNAN_DATE[ 2], MD_XUNAN_DATE[ 3] )
end

-- ���ý�����������
function x270351_SetDate( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_XUNAN_DATE[ 1], MD_XUNAN_DATE[ 2], MD_XUNAN_DATE[ 3], value)
end

function x270351_GetTimes( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_ZHUISHA_CIRCLE[ 1], MD_ZHUISHA_CIRCLE[ 2], MD_ZHUISHA_CIRCLE[ 3] )
end

function x270351_SetTimes( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_ZHUISHA_CIRCLE[ 1], MD_ZHUISHA_CIRCLE[ 2], MD_ZHUISHA_CIRCLE[ 3], value)
end

