
x413100_g_scriptId  = 413100--���ڵ��ű�
x413100_g_Impact1   = 14306--Ч��ID�������Ӻ���
x413100_g_Impact2   = -1 --����


--**********************************
--�¼��������
--**********************************
function x413100_ProcEventEntry( sceneId, selfId, bagIndex )
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x413100_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x413100_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x413100_OnConditionCheck( sceneId, selfId )

 --У��ʹ�õ���Ʒ
	if(1~=VerifyUsedItem(sceneId, selfId)) then
		return 0
	end
	local targetId = GetTargetObjID(sceneId, selfId)
	if(0<=targetId) then
		-- Ŀ��������Ѿ��ļ��
--		if(1~=UnitIsFriend(sceneId, selfId, targetId)) then
--			SendOResultToPlayer(sceneId, selfId, OR_INVALID_TARGET)
--			return 0;
--		end
		-- Ŀ������ǵо��ļ��
	--	if(1~=UnitIsEnemy(sceneId, selfId, targetId)) then
	--		SendOResultToPlayer(sceneId, selfId, OR_INVALID_TARGET)
	--		return 0;
	--	end
		-- Ŀ������Ƕ��ѵļ��
--		if(1~=UnitIsPartner(sceneId, selfId, targetId)) then
--			SendOResultToPlayer(sceneId, selfId, OR_INVALID_TARGET)
--			return 0;
--		end
		-- Ŀ�꼶��ļ��
--		if(g_LevelRequire<=GetLevel(sceneId, targetId)) then
--			SendOResultToPlayer(sceneId, selfId, OR_INVALID_TARGET)
--			return 0;
--		end
--		if(g_LevelRequire>=GetLevel(sceneId, targetId)) then
--			SendOResultToPlayer(sceneId, selfId, OR_INVALID_TARGET)
--			return 0;
--		end

	end

	return 1; --����Ҫ�κ�����������ʼ�շ���1��
end
--**********************************
--���ļ�⼰������ڣ�
--ϵͳ���ڼ������ĵ�ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1�����Ĵ���ͨ�������Լ���ִ�У�����0�����ļ��ʧ�ܣ��жϺ���ִ�С�
--ע�⣺�ⲻ�⸺�����ĵļ��Ҳ�������ĵ�ִ�С�
--**********************************
function x413100_OnDeplete( sceneId, selfId )
 	if(DepletingUsedItem(sceneId, selfId)) == 1 then
		return 1;
	end
	return 0;
	
end

function ShowTips( sceneId,selfId,msgTips )

	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,msgTips);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);

end

--**********************************
--ֻ��ִ��һ����ڣ�
--������˲�����ܻ���������ɺ��������ӿڣ������������Ҹ��������������ʱ�򣩣�������
--����Ҳ����������ɺ��������ӿڣ����ܵ�һ��ʼ�����ĳɹ�ִ��֮�󣩡�
--����1������ɹ�������0������ʧ�ܡ�
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x413100_OnActivateOnce( sceneId, selfId )
    if(-1~=x413100_g_Impact1) then
		--���Լ���Ч��
--		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x333201_g_Impact1, 0);
		--��Ŀ���Ч��

		local targetId = GetTargetObjID(sceneId, selfId)
		targetId = 4
		if(0<=targetId) then --UnitUseSkill
		    --ShowTips(sceneId,selfId,"_OnActivateOnce"..targetId )

			SendSpecificImpactToUnit(sceneId, selfId, selfId, targetId, x413100_g_Impact1, 0);
		end
		--�Լ���ΧAE
--		local posX,posZ = GetUnitPosition(sceneId, selfId)
--		SendImpactAroundPosition(sceneId, selfID, posX, posZ, x333201_g_radiusAE, x333201_g_standFlag, x333201_g_levelRequire, x333201_g_effectCount, x333201_g_Impact1, 0)
		--ָ���ص���ΧAE
--		local posX,posZ = GetTargetPosition(sceneId, selfId)
--		SendImpactAroundPosition(sceneId, selfID, posX, posZ, x333201_g_radiusAE, x333201_g_standFlag, x333201_g_levelRequire, x333201_g_effectCount, x333201_g_Impact1, 0)
		--Ŀ�������ΧAE
--		local targetId = GetTargetObjID(sceneId, selfId)
--		if(0<=targetId) then
--			local posX,posZ = GetUnitPosition(sceneId, targetId)
--			SendImpactAroundPosition(sceneId, selfID, posX, posZ, x333201_g_radiusAE, x333201_g_standFlag, x333201_g_levelRequire, x333201_g_effectCount, x333201_g_Impact1, 0)
--		end


	end
	return 1;
end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x413100_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
