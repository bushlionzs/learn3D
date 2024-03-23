-- ����¯��


------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���
x300341_g_scriptId = 300341

--��Ҫ�ĵȼ�

--Ч����ID
x300341_g_Impact1 = 7210
x300341_g_Impact2 = -1 --����

-- ʹ�ô���Ʒ������ID
x300341_g_MissionId = 8051
-- ʹ�á�����¯�㡱X����
x300341_g_MP_PosX               = 2
-- ʹ�á�����¯�㡱Z����
x300341_g_MP_PosZ               = 3
-- ʹ�á�����¯�㡱ʱ��
x300341_g_MP_UseTime            = 4
-- ����Ŀ�곡��
x300341_g_MP_TargetScene        = 5

--**********************************
--�¼��������
--**********************************
function x300341_ProcEventEntry( sceneId, selfId, bagIndex)
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x300341_IsSkillLikeScript( sceneId, selfId)
    --print( "����¯��" )
	return 1; --����ű�����Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x300341_CancelImpacts( sceneId, selfId)
    --print( "*****CancelImpacts*****" )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ��(call OnDeplete)������0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x300341_OnConditionCheck( sceneId, selfId)
	--У��ʹ�õ���Ʒ
	if( 1 ~= VerifyUsedItem( sceneId, selfId) ) then
		return 0
	end

	-- �������Ƿ�����˲�ԭ��������
    if IsHaveQuestNM( sceneId, selfId, x300341_g_MissionId) == 0 then	-- ���û���������
		BeginQuestEvent( sceneId)
		AddQuestText( sceneId, "��û�н��ܡ���ԭ���������񣬲���ʹ�ô˵���" )
		EndQuestEvent()
		DispatchQuestTips( sceneId, selfId)
        return 0
    end

	-- ������û�������ض��ĳ���ʹ�ô���Ʒ
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300341_g_MissionId)
    local missionScene = GetQuestParam( sceneId, selfId, misIndex, x300341_g_MP_TargetScene)
    if sceneId ~= missionScene then
        local baseScene = ( GetCurCountry( sceneId, selfId) ) * 100 + 50
        missionScene = missionScene - baseScene
        local str = "������ʹ��Ҳû��Ч�������������Թ������ð�"
        if missionScene == 36 then
            str = "������ʹ��Ҳû��Ч������������@npcsp_��Ȫ��_82004�ð�"
        elseif missionScene == 37 then
            str = "������ʹ��Ҳû��Ч������������@npcsp_����ɽ_82005�ð�"
        elseif missionScene == 39 then
            str = "������ʹ��Ҳû��Ч������������@npcsp_��Ҷ��_82006�ð�"
        end

		BeginQuestEvent( sceneId)
		AddQuestText( sceneId, str)
		EndQuestEvent()
		DispatchQuestTips( sceneId, selfId)
		return 0
    end

	return 1
end

--**********************************
--���ļ�⼰������ڣ�
--ϵͳ���ڼ������ĵ�ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1�����Ĵ���ͨ�������Լ���ִ��(call OnActivateOnce)������0�����ļ��ʧ�ܣ��жϺ���ִ�С�
--ע�⣺�ⲻ�⸺�����ĵļ��Ҳ�������ĵ�ִ�С�
--**********************************
function x300341_OnDeplete( sceneId, selfId)
	if DepletingUsedItem( sceneId, selfId) == 1 then
		return 1;
	end
	return 0;
end

--**********************************
--ֻ��ִ��һ����ڣ�
--������˲�����ܻ���������ɺ��������ӿڣ������������Ҹ��������������ʱ�򣩣�������
--����Ҳ����������ɺ��������ӿڣ����ܵ�һ��ʼ�����ĳɹ�ִ��֮�󣩡�
--����1������ɹ�������0������ʧ�ܡ�
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x300341_OnActivateOnce( sceneId, selfId)
    -- ��Buff
	-- if( -1 ~= x300341_g_Impact1) then
		-- SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300341_g_Impact1, 0);
	-- end

    -- ����NPC
    local x, z = GetWorldPos( sceneId, selfId)
    local ObjId = CreateMonster( sceneId, 3120, x, z, 0, 0, -1, -1, 20, 180000)

    -- ��¼NPCλ��
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300341_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x300341_g_MP_PosX, x)
    SetQuestByIndex( sceneId, selfId, misIndex, x300341_g_MP_PosZ, z)
    -- ����ʹ����Ʒʱ��
    local curTime = GetCurrentTime()
    SetQuestByIndex( sceneId, selfId, misIndex, x300341_g_MP_UseTime, curTime)

    -- ��ʾ
    BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "���������ﶼ����¯�����գ��������������ϸ����׻���䱦��" )
    EndQuestEvent( sceneId)
    DispatchQuestTips( sceneId, selfId)

	return 1;
end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x300341_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
