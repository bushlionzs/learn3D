--�������
------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���

x418110_g_scriptId = 418110
x418110_g_ItemList = {}
x418110_g_LevelMin = 20	
x418110_g_ItemList = {11970021,11990011,10300111,10300120,10300129,12030323,12030396}
x418110_g_ItemList2 = {12030319,12030320,12030321,12030322}
x418110_g_ItemName = {"��ʿ��","������","�置ʱװ��1�죩","����ʱװ��1�죩","����ʱװ��1�죩","100��СǮ��","150��СǮ��"} 
x418110_g_ItemName2 = {"СǮ��","СǮ��","СǮ��","СǮ��"} 
--12030201����ʯ
--12030202�������
--12041101���в�
--12010020С������¶
--12030200С����
--12030319  5��СǮ��  
--12030320  10��СǮ�� 
--12030321  15��СǮ�� 
--12030322  30��СǮ�� 
--12030323  100��СǮ��
--12030396  150��СǮ��


--��Ҫ�ĵȼ�


--**********************************
--�¼��������
--**********************************
function x418110_ProcEventEntry( sceneId, selfId, bagIndex )
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x418110_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x418110_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x418110_OnConditionCheck( sceneId, selfId )
	
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
function x418110_OnDeplete( sceneId, selfId )
	
	--if(DepletingUsedItem(sceneId, selfId)) == 1 then
	--	return 1;
	--end
	--return 0;
	
	return 1;
end

--**********************************
--ֻ��ִ��һ����ڣ�
--������˲�����ܻ���������ɺ��������ӿڣ������������Ҹ��������������ʱ�򣩣�������
--����Ҳ����������ɺ��������ӿڣ����ܵ�һ��ʼ�����ĳɹ�ִ��֮�󣩡�
--����1������ɹ�������0������ʧ�ܡ�
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x418110_OnActivateOnce( sceneId, selfId, impactId )
	
	if GetLevel(sceneId, selfId)< x418110_g_LevelMin then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�ȼ�����")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end

	local j = random(1,7)
	local i = random(1,7)	
	local itemId = 0
	local itemName = 0
	local itemId2 = 0
	local itemName2 = 0
	local nCountry = CallScriptFunction(888888,"GetCountryName",sceneId,selfId)
	local nLevel = GetLevel(sceneId,selfId)
	local k = random(1,4)

	if j < 5 then
			itemId2 = x418110_g_ItemList2[k]
		BeginAddItem(sceneId)
			AddBindItem( sceneId,itemId2, 1 )	--СǮ��1

		local ret = EndAddItem(sceneId,selfId)

		if ret > 0 then
			if(DepletingUsedItem(sceneId, selfId)) == 1 then
--				AddMoney( sceneId, selfId, 1, 500*nLevel )
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"���ź��������������������ף���´κ��ˣ�")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				AddItemListToPlayer(sceneId,selfId)
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"ʹ����Ʒ�쳣��")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end
		end
		
	else
		if i<=7 then
			itemId = x418110_g_ItemList[i]
			itemName = 	x418110_g_ItemName[i]
	BeginAddItem(sceneId)
	AddBindItem( sceneId,itemId, 1 )	--IB��Ʒ1

	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		if(DepletingUsedItem(sceneId, selfId)) == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"�������������������")
			EndQuestEvent(sceneId)
			AddMoney( sceneId, selfId, 1, 500*nLevel )
			local nName=GetName(sceneId,selfId)
			local msg = format("#G��ϲ#R%s����#G��#Y%s#G�����#R%s#G�����˽�Ʒ��ÿ�˶��п��ܻ��������ˣ����ϵ��콱��ʹ��ȥ��ȡ�ɣ�",nCountry,nName,itemName)
			LuaAllScenceM2Wrold (sceneId, msg, 0, 1)--ȫ������
			DispatchQuestTips(sceneId,selfId)
			AddItemListToPlayer(sceneId,selfId)
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"ʹ����Ʒ�쳣��")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end

	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�����������޷��õ���Ʒ������Ҫ������1�������ռ䣡")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	end
		else
			return
		end
	end


end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x418110_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
