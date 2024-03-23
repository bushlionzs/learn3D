--ע�⣺

--��Ʒ���ܵ��߼�ֻ��ʹ�û������ܺͽű���ʵ��

--�ű�:

--�����ǽű�����:

--3001.lua
------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���
x300324_g_scriptId = 300324 --��ʱд���,�����õ�ʱ��һ��Ҫ��.

--**********************************
--�¼��������
--**********************************


x300324_g_MissionList = {	{mission=8067, id = 13011800, posX=96, posZ=91 }, 
							{mission=8068, id = 13011801,posX=352, posZ=172 },
							{mission=8069, id = 13011802,posX=461, posZ=297 },
							{mission=8070, id = 13011803,posX=358, posZ=391 },
							{mission=8071, id = 13011804,posX=466, posZ=399 },
							{mission=8072, id = 13011805,posX=114, posZ=321 },
							{mission=8073, id = 13011806,posX=209, posZ=313 }	}


function x300324_ProcEventEntry( sceneId, selfId, Index, sign )

	if sign==1 then

		SetViewBeastie( sceneId, selfId, 0 )

		for i, item in x300324_g_MissionList do
			if IsHaveQuestNM( sceneId, selfId, item.mission ) > 0 then
				local ItemCnt = GetItemCount( sceneId, selfId, item.id )
				if ItemCnt == 0 then
					local message = format("û��ץ��������%d��%d�����������ɣ�", item.posX, item.posZ)
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, message)
					DispatchQuestTips(sceneId, selfId)
					EndQuestEvent(sceneId)
					Msg2Player(sceneId,selfId,message, 8, 2)
					return
				end
			end
		end
		
	end
					
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x300324_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x300324_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x300324_OnConditionCheck( sceneId, selfId )
	--У��ʹ�õ���Ʒ
	--if(1~=VerifyUsedItem(sceneId, selfId)) then
		--return 0
	--end
	return 1; --����Ҫ�κ�����������ʼ�շ���1��
end

--**********************************
--���ļ�⼰������ڣ�
--ϵͳ���ڼ������ĵ�ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1�����Ĵ���ͨ�������Լ���ִ�У�����0�����ļ��ʧ�ܣ��жϺ���ִ�С�
--ע�⣺�ⲻ�⸺�����ĵļ��Ҳ�������ĵ�ִ�С�
--**********************************
function x300324_OnDeplete( sceneId, selfId )
	--if(DepletingUsedItem(sceneId, selfId)) then
		--return 1;
	--end
	return 1;
end

--**********************************
--ֻ��ִ��һ����ڣ�
--������˲�����ܻ���������ɺ��������ӿڣ������������Ҹ��������������ʱ�򣩣�������
--����Ҳ����������ɺ��������ӿڣ����ܵ�һ��ʼ�����ĳɹ�ִ��֮�󣩡�
--����1������ɹ�������0������ʧ�ܡ�
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x300324_OnActivateOnce( sceneId, selfId )
	--if(-1~=x300324_g_Impact1) then
		--SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x300324_g_Impact1, 0);
	--end
	return 1;
end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x300324_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
