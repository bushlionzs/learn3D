-- ��ͯ��


-- ����ͨ�ù��ܽű�
x404834_g_petCommonId = PETCOMMON

--******************************************************************************
-- ���²�����Ҫ����Ҫ�޸ĵĲ���
--******************************************************************************

--�ű��� ���ĳ���ȷ�ű��ţ�
x404834_g_scriptId = 404834

--��׼Ч��ID ���ĳɳ���ʹ��ѱ�����ߵ���Ч��
--g_ImpactID = 0

--******************************************************************************
-- ���ϲ�����Ҫ����Ҫ�޸ĵĲ���
--******************************************************************************

--�ű�

--**********************************
--���뷵�� 1 ������ȷִ����������
--**********************************
function x404834_IsSkillLikeScript( sceneId, selfId)
	return 1
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x404834_OnConditionCheck( sceneId, selfId )
	--У��ʹ�õ���Ʒ
	if(1~=VerifyUsedItem(sceneId, selfId)) then
		return 0
	end

	local petGUID_H = GetHighSectionOfTargetPetGuid( sceneId, selfId )
	local petGUID_L = GetLowSectionOfTargetPetGuid( sceneId, selfId )

	if PetCanReturnToChild( sceneId, selfId, petGUID_H, petGUID_L ) == 0 then
		return 0
	end

	return 1
end

--**********************************
--���ļ�⼰������ڣ�
--ϵͳ���ڼ������ĵ�ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1�����Ĵ���ͨ�������Լ���ִ�У�����0�����ļ��ʧ�ܣ��жϺ���ִ�С�
--ע�⣺�ⲻ�⸺�����ĵļ��Ҳ�������ĵ�ִ�С�
--**********************************
function x404834_OnDeplete( sceneId, selfId )
	if(DepletingUsedItem(sceneId, selfId)) == 1 then
		return 1
	end
	return 0
end

--**********************************
--ֻ��ִ��һ����ڣ�
--������˲�����ܻ���������ɺ��������ӿڣ������������Ҹ��������������ʱ�򣩣�������
--����Ҳ����������ɺ��������ӿڣ����ܵ�һ��ʼ�����ĳɹ�ִ��֮�󣩡�
--����1������ɹ�������0������ʧ�ܡ�
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x404834_OnActivateOnce( sceneId, selfId )
	local petGUID_H = GetHighSectionOfTargetPetGuid( sceneId, selfId )
	local petGUID_L = GetLowSectionOfTargetPetGuid( sceneId, selfId )

	PetReturnToChild( sceneId, selfId, petGUID_H, petGUID_L )

--	SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, g_ImpactID, 0)
	return 1
end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x404834_OnActivateEachTick( sceneId, selfId )
	return 1
end

-- �������û��ʲô�ã����Ǳ�����
function x404834_CancelImpacts( sceneId, selfId )
	return 0
end
