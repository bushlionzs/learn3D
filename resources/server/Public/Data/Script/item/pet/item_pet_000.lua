--ע�⣺

--��Ʒ���ܵ��߼�ֻ��ʹ�û������ܺͽű���ʵ��

--�ű�:

--�����ǽű�����:


--3001.lua
------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���
x416000_g_scriptId = 416000 --��ʱд���,�����õ�ʱ��һ��Ҫ��.
x416000_g_MissionId ={3209,3309,3409,3709}
--��Ҫ�ĵȼ�

--Ч����ID
x416000_g_Impact1 = 8001 --��ʱд���
x416000_g_Impact2 = -1 --����

--**********************************
--�¼��������
--**********************************
function x416000_ProcEventEntry( sceneId, selfId, bagIndex,torf )
if IsHaveQuest(sceneId,selfId, x416000_g_MissionId[1]) > 0 then
	local misIndex = GetQuestIndexByID( sceneId, selfId, x416000_g_MissionId[1] )
	if torf == 0 then
				if GetHorseCount(sceneId,selfId) > 0 then
						if IsHaveMount(sceneId, selfId,1) > 0 then
								SetQuestByIndex(sceneId,selfId,misIndex,7,1)
								SetQuestByIndex(sceneId,selfId,misIndex,0,1)
							 CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,14,0 )
				    elseif IsHaveMount(sceneId, selfId,11) > 0 then
				    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
								SetQuestByIndex(sceneId,selfId,misIndex,0,1)
								CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,14,0 )
				    elseif IsHaveMount(sceneId, selfId,21) > 0 then
				    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
								SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						   CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,14,0 )
				    elseif IsHaveMount(sceneId, selfId,31) > 0 then
				    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
								SetQuestByIndex(sceneId,selfId,misIndex,0,1)
							  CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,14,0 )
				    elseif IsHaveMount(sceneId, selfId,41) > 0 then
				    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
								SetQuestByIndex(sceneId,selfId,misIndex,0,1)
							 CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,14,0 )
				    elseif IsHaveMount(sceneId, selfId,51) > 0 then
				    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
								SetQuestByIndex(sceneId,selfId,misIndex,0,1)
								CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,14,0 )
						end
				end
	elseif torf == 1 then
								SetQuestByIndex(sceneId,selfId,misIndex,7,0)
								SetQuestByIndex(sceneId,selfId,misIndex,0,0)
	end
end
if IsHaveQuest(sceneId,selfId, x416000_g_MissionId[2]) > 0 then
	local misIndex = GetQuestIndexByID( sceneId, selfId, x416000_g_MissionId[2] )
	if torf == 0 then
				if GetHorseCount(sceneId,selfId) > 0 then
						if IsHaveMount(sceneId, selfId,1) > 0 then
								SetQuestByIndex(sceneId,selfId,misIndex,7,1)
								SetQuestByIndex(sceneId,selfId,misIndex,0,1)
							 CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,14,0 )
				    elseif IsHaveMount(sceneId, selfId,11) > 0 then
				    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
								SetQuestByIndex(sceneId,selfId,misIndex,0,1)
								CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,14,0 )
				    elseif IsHaveMount(sceneId, selfId,21) > 0 then
				    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
								SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						   CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,14,0 )
				    elseif IsHaveMount(sceneId, selfId,31) > 0 then
				    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
								SetQuestByIndex(sceneId,selfId,misIndex,0,1)
							  CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,14,0 )
				    elseif IsHaveMount(sceneId, selfId,41) > 0 then
				    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
								SetQuestByIndex(sceneId,selfId,misIndex,0,1)
							 CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,14,0 )
				    elseif IsHaveMount(sceneId, selfId,51) > 0 then
				    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
								SetQuestByIndex(sceneId,selfId,misIndex,0,1)
								CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,14,0 )
						end
				end
	elseif torf == 1 then
								SetQuestByIndex(sceneId,selfId,misIndex,7,0)
								SetQuestByIndex(sceneId,selfId,misIndex,0,0)
	end
end
if IsHaveQuest(sceneId,selfId, x416000_g_MissionId[3]) > 0 then
	local misIndex = GetQuestIndexByID( sceneId, selfId, x416000_g_MissionId[3] )
	if torf == 0 then
				if GetHorseCount(sceneId,selfId) > 0 then
						if IsHaveMount(sceneId, selfId,1) > 0 then
								SetQuestByIndex(sceneId,selfId,misIndex,7,1)
								SetQuestByIndex(sceneId,selfId,misIndex,0,1)
							 CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,14,0 )
				    elseif IsHaveMount(sceneId, selfId,11) > 0 then
				    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
								SetQuestByIndex(sceneId,selfId,misIndex,0,1)
								CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,14,0 )
				    elseif IsHaveMount(sceneId, selfId,21) > 0 then
				    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
								SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						   CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,14,0 )
				    elseif IsHaveMount(sceneId, selfId,31) > 0 then
				    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
								SetQuestByIndex(sceneId,selfId,misIndex,0,1)
							  CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,14,0 )
				    elseif IsHaveMount(sceneId, selfId,41) > 0 then
				    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
								SetQuestByIndex(sceneId,selfId,misIndex,0,1)
							 CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,14,0 )
				    elseif IsHaveMount(sceneId, selfId,51) > 0 then
				    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
								SetQuestByIndex(sceneId,selfId,misIndex,0,1)
								CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,14,0 )
						end
				end
	elseif torf == 1 then
								SetQuestByIndex(sceneId,selfId,misIndex,7,0)
								SetQuestByIndex(sceneId,selfId,misIndex,0,0)
	end
end
if IsHaveQuest(sceneId,selfId, x416000_g_MissionId[4]) > 0 then
	local misIndex = GetQuestIndexByID( sceneId, selfId, x416000_g_MissionId[4] )
	if torf == 0 then
				if GetHorseCount(sceneId,selfId) > 0 then
						if IsHaveMount(sceneId, selfId,1) > 0 then
								SetQuestByIndex(sceneId,selfId,misIndex,7,1)
								SetQuestByIndex(sceneId,selfId,misIndex,0,1)
							 CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,14,0 )
				    elseif IsHaveMount(sceneId, selfId,11) > 0 then
				    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
								SetQuestByIndex(sceneId,selfId,misIndex,0,1)
								CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,14,0 )
				    elseif IsHaveMount(sceneId, selfId,21) > 0 then
				    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
								SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						   CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,14,0 )
				    elseif IsHaveMount(sceneId, selfId,31) > 0 then
				    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
								SetQuestByIndex(sceneId,selfId,misIndex,0,1)
							  CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,14,0 )
				    elseif IsHaveMount(sceneId, selfId,41) > 0 then
				    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
								SetQuestByIndex(sceneId,selfId,misIndex,0,1)
							 CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,14,0 )
				    elseif IsHaveMount(sceneId, selfId,51) > 0 then
				    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
								SetQuestByIndex(sceneId,selfId,misIndex,0,1)
								CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId,14,0 )
						end
				end
	elseif torf == 1 then
								SetQuestByIndex(sceneId,selfId,misIndex,7,0)
								SetQuestByIndex(sceneId,selfId,misIndex,0,0)
	end
end

-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x416000_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x416000_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x416000_OnConditionCheck( sceneId, selfId )
	--У��ʹ�õ���Ʒ
	--if(1~=VerifyUsedItem(sceneId, selfId)) then
		--return 0
	--end
	--return 1; --����Ҫ�κ�����������ʼ�շ���1��
end

--**********************************
--���ļ�⼰������ڣ�
--ϵͳ���ڼ������ĵ�ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1�����Ĵ���ͨ�������Լ���ִ�У�����0�����ļ��ʧ�ܣ��жϺ���ִ�С�
--ע�⣺�ⲻ�⸺�����ĵļ��Ҳ�������ĵ�ִ�С�
--**********************************
function x416000_OnDeplete( sceneId, selfId )
	--if(DepletingUsedItem(sceneId, selfId)) then
		--return 1;
	--end
	--return 0;
end

--**********************************
--ֻ��ִ��һ����ڣ�
--������˲�����ܻ���������ɺ��������ӿڣ������������Ҹ��������������ʱ�򣩣�������
--����Ҳ����������ɺ��������ӿڣ����ܵ�һ��ʼ�����ĳɹ�ִ��֮�󣩡�
--����1������ɹ�������0������ʧ�ܡ�
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x416000_OnActivateOnce( sceneId, selfId )
	--if(-1~=x416000_g_Impact1) then
		--SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x416000_g_Impact1, 0);
	--end
	--return 1;
end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x416000_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
