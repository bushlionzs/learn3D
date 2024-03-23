x300752_g_scriptId  = 300752
x300752_g_Impact1   = -1 --Ч��ID
x300752_g_Impact2   = -1 --����

x300752_g_MissionId 	= -1			--����ID
x300752_g_ItemId 		= 12030107		--�ر�ͼID
x300752_g_ScriptId 		= 300752		--�ű�ID

x300752_g_UseSceneID1	= 50			--ʹ����Ʒ����
x300752_g_UseSceneID2	= 150			--ʹ����Ʒ����
x300752_g_UseSceneID3	= 250			--ʹ����Ʒ����
x300752_g_UseSceneID4	= 350			--ʹ����Ʒ����
x300752_g_UsePosX		= 198			--ʹ����Ʒλ��
x300752_g_UsePosZ		= 46


x300752_g_CreateMonsterID	= 9560;		--���������Ĺ�ID
x300752_g_MonsterPos	= {{x = 185, z = 49},
						   {x = 184, z = 57},
						   {x = 190, z = 63},
						   {x = 198, z = 64},
						   {x = 205, z = 63},
						   {x = 214, z = 49},
						   {x = 214, z = 36},
						   {x = 201, z = 30},
						   {x = 190, z = 31},
						   {x = 187, z = 41}}
						   
x300752_g_GiveItemID	= 12110206;		--����ҵ���ƷID
x300752_g_GiveExp		= 1000;			--����ҵľ���
x300752_g_GiveScriptID	= 300330;		--�ر�ͼ����Ľű�ID
x300752_g_GiveMissionID	= 8050;			--�ر�ͼ���������ID


--**********************************
--�¼��������
--**********************************
function x300752_ProcEventEntry( sceneId, selfId, bagIndex )
--SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x300752_g_Impact1, 0); --��Ч
    local playerLevel = GetLevel( sceneId, selfId)
    if playerLevel < 20 then
        BeginQuestEvent( sceneId)
        AddQuestText( sceneId,"��ĵȼ�̫�ͣ����޷�����ر�ͼ�İ���" )
        EndQuestEvent( sceneId)
        DispatchQuestTips( sceneId, selfId)
        Msg2Player( sceneId, selfId, "��ĵȼ�̫�ͣ����޷�����ر�ͼ�İ��أ�", 8, 2)
        return 0;
    end

    --DelQuest(sceneId, selfId, x300752_g_GiveMissionID)
	local x,z = GetWorldPos( sceneId, selfId)
    local bHaveMission	= IsHaveQuestNM( sceneId, selfId, x300752_g_GiveMissionID)
    if( bHaveMission > 0) then
        BeginQuestEvent( sceneId)
        AddQuestText( sceneId,"���Ѿ��вر�ͼ�����ˣ��޷��ظ���ȡ��" )
        EndQuestEvent( sceneId)
        DispatchQuestTips( sceneId, selfId)
        Msg2Player( sceneId, selfId, "���Ѿ��вر�ͼ�����ˣ��޷��ظ���ȡ��", 8, 2)
        return 0;
    end

    if IsQuestFullNM( sceneId, selfId) == 1 then
        Msg2Player( sceneId, selfId, "�����������������ʧ��", 8, 3)
        return 0
    end

    if DelItemByIndexInBag( sceneId, selfId, bagIndex, 1) == 0 then
        Msg2Player( sceneId, selfId, "�򿪲ر�ͼ�����쳣���޷��鿴�����", 8, 3)
        return 0
    end

    --������
    if CallScriptFunction( x300752_g_GiveScriptID, "OnForceAddMission", sceneId, selfId, -1, x300752_g_GiveMissionID ) > 0 then
        -- ɾ��������Ĳر�ͼ
        --DelItemByIndexInBag( sceneId, selfId, bagIndex, 1)
		
		x300752_UpdateTopList(sceneId, selfId)
    end
    -- BeginQuestEvent(sceneId)
    -- AddQuestText(sceneId,"��ϲ��������ˡ�Ѱ�����񡿣�������ͨ��Q����ѯ������Ϣ��")
    -- EndQuestEvent(sceneId)
    -- DispatchQuestTips(sceneId,selfId)
    -- local Readme = "��ϲ��������ˡ�Ѱ�����񡿣�������ͨ��Q����ѯ������Ϣ��"
    -- Msg2Player(sceneId,selfId,Readme,8,2)

    return 1;
end

function x300752_UpdateTopList(sceneId,selfId)

	local lastday = GetQuestData( sceneId, selfId, MD_BAOZANG_DAY[1], MD_BAOZANG_DAY[2], MD_BAOZANG_DAY[3] )
	local curCount = GetQuestData( sceneId, selfId, MD_BAOZANG_COUNT[1], MD_BAOZANG_COUNT[2], MD_BAOZANG_COUNT[3] )
	local curday = GetWeekFirstDay()
	if lastday ~= curday then
		curCount = 0
	end
	curCount = curCount + 1
	SetQuestData( sceneId, selfId, MD_BAOZANG_COUNT[1], MD_BAOZANG_COUNT[2], MD_BAOZANG_COUNT[3], curCount )
	SetQuestData( sceneId, selfId, MD_BAOZANG_DAY[1], MD_BAOZANG_DAY[2], MD_BAOZANG_DAY[3], curday )
	
	SendToplistKeyValue2GL(sceneId, selfId, BAOZANG_TOPLIST, curCount)
	
end

function x300752_IsSkillLikeScript( sceneId, selfId)
 
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x300752_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x300752_OnConditionCheck( sceneId, selfId )
	return 0
end

function x300752_OnDeplete( sceneId, selfId )
	if DepletingUsedItem(sceneId, selfId) == 1 then
		return 1;
	end
	return 0
end

function x300752_OnActivateOnce( sceneId, selfId )
end

function x300752_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end

