--�̻� �������
------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���

x418103_g_scriptId = 418103
--��Ҫ�ĵȼ�


--**********************************
--�¼��������
--**********************************
function x418103_ProcEventEntry( sceneId, selfId, bagIndex )
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x418103_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x418103_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x418103_OnConditionCheck( sceneId, selfId )
	
	--У��ʹ�õ���Ʒ
	
	if(1~=VerifyUsedItem(sceneId, selfId)) then
		return 0
	end
	return 1; --����Ҫ�κ�����������ʼ�շ���1��
end

--**********************************
--���ļ�⼰������ڣ�
--ϵͳ���ڼ������ĵ�ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1�����Ĵ���ͨ�������Լ���ִ�У�����0�����ļ��ʧ�ܣ��жϺ���ִ�С�
--ע�⣺�ⲻ�⸺�����ĵļ��Ҳ�������ĵ�ִ�С�
--**********************************
function x418103_OnDeplete( sceneId, selfId )
	return 1;
end

--**********************************
--ֻ��ִ��һ����ڣ�
--������˲�����ܻ���������ɺ��������ӿڣ������������Ҹ��������������ʱ�򣩣�������
--����Ҳ����������ɺ��������ӿڣ����ܵ�һ��ʼ�����ĳɹ�ִ��֮�󣩡�
--����1������ɹ�������0������ʧ�ܡ�
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x418103_OnActivateOnce( sceneId, selfId, impactId )
	if(DepletingUsedItem(sceneId, selfId)) == 1 then
	local j=random(1,10);
	if j==1 then
	SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId,8338, 0);
	elseif j==2 then
	SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId,8339, 0);
	elseif j==3 then
	SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId,8340, 0);
	elseif j==4 then
	SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId,8341, 0);
	elseif j==5 then
	SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId,8342, 0);
	elseif j==6 then
	SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId,8343, 0);
	elseif j==7 then
	SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId,8344, 0);
	elseif j==8 then
	SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId,8345, 0);
	elseif j==9 then
	SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId,8346, 0);
	elseif j==10 then
	SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId,8347, 0);
  end

  		--������ش���
		x418103_OnTopListYanghua(sceneId,selfId)

		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "��ʹ�����̻�");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"��ʹ�����̻�",CHAT_TYPE_SELF,CHAT_RIGHTDOWN)
	end
end	

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x418103_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end

---------------------------------------------------------------------------------------------------
--�̷�����
---------------------------------------------------------------------------------------------------
function x418103_OnTopListYanghua(mapId,playerId)

	
	--ȡ���ϴμ�¼���ܺʹ���
	local lastweek = GetQuestData( mapId, playerId, MD_YANHUA_WEEK[1], MD_YANHUA_WEEK[2], MD_YANHUA_WEEK[3] )
	local curcount = GetQuestData( mapId, playerId, MD_YANHUA_COUNT[1], MD_YANHUA_COUNT[2], MD_YANHUA_COUNT[3] )
	
	--ȡ�õ�ǰ�ܣ������ǰ�����ϴμ�¼���ܲ�ƥ�䣬���������
	local curweek = CallScriptFunction( 888888, "GetWorldWeek", mapId)
	if lastweek ~= curweek then
		curcount = 0
	end

	
	--������أ�Ȼ���¼
	curcount = curcount + 1
	SetQuestData( mapId, playerId, MD_YANHUA_COUNT[1], MD_YANHUA_COUNT[2], MD_YANHUA_COUNT[3], curcount )
	SetQuestData( mapId, playerId, MD_YANHUA_WEEK[1], MD_YANHUA_WEEK[2], MD_YANHUA_WEEK[3], curweek )

	--����������ݵ�gl
	SendToplistKeyValue2GL(mapId, playerId, YANHUA_TOPLIST, curcount)
	
end