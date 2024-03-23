-- ����


------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���
x920002_g_scriptId = 920002 --��ʱд���,�����õ�ʱ��һ��Ҫ��.

--��Ҫ�ĵȼ�

--Ч����ID
x920002_g_Impact1 = 7211
x920002_g_Impact2 = -1 --����

--**********************************
--�¼�������ڣ�flag = 0��ʾ�ͷ�Buff��1��ʾBuff��ʧ
--**********************************
function x920002_ProcEventEntry( sceneId, selfId, buffIndex, flag)
    -- ����Buffʱ������л���PKģʽ
	-- �µĲ߻�������Ҫ�л���PKģʽ
  --  if flag == 1 then
  --      SetCurPKMode( sceneId, selfId, 1)
  --  end
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x920002_IsSkillLikeScript( sceneId, selfId)
    --print( "����" )
	return 1; --����ű�����Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x920002_CancelImpacts( sceneId, selfId )
    --print( "����" )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ��(call OnDeplete)������0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x920002_OnConditionCheck( sceneId, selfId )
	--У��ʹ�õ���Ʒ
	if(1~=VerifyUsedItem(sceneId, selfId)) then
		return 0
	end

	-- ��ɫ�ȼ�С��20������ʹ�ô˵���
	if GetLevel( sceneId, selfId) < 20 then
		BeginQuestEvent( sceneId)
		AddQuestText( sceneId, "�ܱ�Ǹ��19����������ܱ����ģ�������ʹ�ÿ��衣" );
		EndQuestEvent()
		DispatchQuestTips( sceneId, selfId)
		return 0
	end

    -- ���Buff���ڲ����ٴ�ʹ��
    if IsHaveSpecificImpact( sceneId, selfId, x920002_g_Impact1) ~= 0 then
		BeginQuestEvent( sceneId)
		AddQuestText( sceneId, "���ܵ���ʹ�ô˵���" )
		EndQuestEvent()
		DispatchQuestTips( sceneId, selfId)
		return 0
    end
	
	--�����ﲻ����ʹ��
	if sceneId == PK_PUNISH_PRISON_SCENE_ID then
		BeginQuestEvent( sceneId)
		AddQuestText( sceneId, "�����в���ʹ�ô˵���" )
		EndQuestEvent()
		DispatchQuestTips( sceneId, selfId)
		return 0
	end
	
	-- �����ս����������
	if GetSceneType(sceneId)==2 then
		BeginQuestEvent( sceneId)
		AddQuestText( sceneId, "ս���в���ʹ�ô˵���" )
		EndQuestEvent()
		DispatchQuestTips( sceneId, selfId)
		return 0		
	end

	return 1; --����Ҫ�κ�����������ʼ�շ���1��
end

--**********************************
--���ļ�⼰������ڣ�
--ϵͳ���ڼ������ĵ�ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1�����Ĵ���ͨ�������Լ���ִ��(call OnActivateOnce)������0�����ļ��ʧ�ܣ��жϺ���ִ�С�
--ע�⣺�ⲻ�⸺�����ĵļ��Ҳ�������ĵ�ִ�С�
--**********************************
function x920002_OnDeplete( sceneId, selfId )
	if DepletingUsedItem(sceneId, selfId) == 1 then
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
function x920002_OnActivateOnce( sceneId, selfId )
	if(-1~=x920002_g_Impact1) then
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x920002_g_Impact1, 0);
	end
	--PK_MODE_MIANJU = 2, defined in GameStruct_Country.h
	SetCurPKMode( sceneId, selfId, 2, 0)

    BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "�����״̬�����Թ��������˼����ڳ�" )
    EndQuestEvent()
    DispatchQuestTips( sceneId, selfId)

	return 1;
end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x920002_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
