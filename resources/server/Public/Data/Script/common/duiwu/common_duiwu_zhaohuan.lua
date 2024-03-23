--ע�⣺

--��Ʒ���ܵ��߼�ֻ��ʹ�û������ܺͽű���ʵ��

--�ű�:

--�����ǽű�����:

------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���
x310501_g_scriptId = 310501 --��ʱд���,�����õ�ʱ��һ��Ҫ��.
x310501_g_lingdicheck 	= {							
							  { sceneId= 6,	time1 = 960,time2 = 1020,x1 = 28,x2 = 107,z1 =41,z2 =123},	--���ݳ�
							  { sceneId= 9,	time1 = 960,time2 = 1020,x1 = 132,x2 = 187,z1 =15,z2 =97},	--��Ҷ��
							  { sceneId= 13,time1 = 960,time2 = 1020,x1 = 31,x2 = 126,z1 =165,z2 =236},   --�͸��
							  { sceneId= 18,time1 = 960,time2 = 1020,x1 = 180,x2 = 210,z1 =28,z2 =60},  	--��������
							  { sceneId= 21,time1 = 960,time2 = 1020,x1 = 130,x2 = 288,z1 =70,z2 =191},	--��ʥ����۹�
							  { sceneId= 24,time1 = 960,time2 = 1020,x1 = 84,x2 = 174,z1 =55,z2 =136},	--Ү·����
							  { sceneId= 27,time1 = 960,time2 = 1020,x1 = 100,x2 = 100,z1 =100,z2 =100},   --����
							  { sceneId= 31,time1 = 960,time2 = 1020,x1 = 100,x2 = 100,z1 =100,z2 =100},	--���
							  { sceneId= 34,time1 = 960,time2 = 1020,x1 = 100,x2 = 100,z1 =100,z2 =100},	--צ�۵�
							}
--��Ҫ�ĵȼ�

--Ч����ID

--**********************************
--�¼��������
--**********************************
function x310501_ProcEventEntry( sceneId, selfId, bagIndex )
-- ����Ҫ����ӿڣ���Ҫ�����պ���
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x310501_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x310501_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x310501_OnConditionCheck( sceneId, selfId )
	--У��ʹ�õ���Ʒ
	if(1~=VerifyUsedItem(sceneId, selfId)) then
		return 0
	end
	local msg = nil
	local level = GetLevel(sceneId,selfId)
	local nNeedLevel = x310501_GetNeedLevel(sceneId, selfId)
	if level < 10 then
	   msg = "�ܱ�Ǹ��10������ʹ�ö����ټ��"
	elseif HasTeam(sceneId, selfId) ~= 1 then
		msg = "�ܱ�Ǹ������δ��������޷�ʹ�á�"
	elseif (GetTeamSize(sceneId, selfId) < 2) then
		msg = "�ܱ�Ǹ�������ڵĶ����г�ԱС��2�ˣ��޷�ʹ�á�";
	elseif 0 == nNeedLevel then
		msg = "�ܱ�Ǹ�������ڵ�ͼ�޷�ʹ�øõ��ߡ�";
	end
	--У���Ƿ�Ϊ�������սʱ���ڽ��÷�Χ
	if  GetWeek() == 6 then
		if x310501_lingdicheck(sceneId, selfId) == 1 then
			msg = "�ܱ�Ǹ�����������ս�ڼ䣬���޷������ͼ�ڸ���ʹ�ö����ټ��";
		end	
	end
	if msg ~= nil then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,msg)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
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
function x310501_OnDeplete( sceneId, selfId )
	return 1;
end

--**********************************
--ֻ��ִ��һ����ڣ�
--������˲�����ܻ���������ɺ��������ӿڣ������������Ҹ��������������ʱ�򣩣�������
--����Ҳ����������ɺ��������ӿڣ����ܵ�һ��ʼ�����ĳɹ�ִ��֮�󣩡�
--����1������ɹ�������0������ʧ�ܡ�
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x310501_OnActivateOnce( sceneId, selfId )
	local nNeedLevel = x310501_GetNeedLevel(sceneId, selfId)
	if(DepletingUsedItem(sceneId, selfId)) == 1 then
	
		msg = "��ʹ���˶����ټ���,���Ķ��ѻᾡ�������"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,msg)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		
		CallUpTeamMember( sceneId, selfId, nNeedLevel )
	end
	return 1;
end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x310501_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end

function x310501_GetNeedLevel(sceneId, selfId)
	if sceneId == 52 or sceneId == 152 or sceneId == 252 or sceneId == 352 or 
	   sceneId == 87 or sceneId == 187 or sceneId == 287 or sceneId == 387 or 
	   sceneId == 98 or sceneId == 198 or sceneId == 298 or sceneId == 398 or
	   sceneId == 99 or sceneId == 199 or sceneId == 299 or sceneId == 399 or
	   sceneId == 100 or sceneId == 200 or sceneId == 300 or sceneId == 400 or
	   sceneId == 101 or sceneId == 201 or sceneId == 301 or sceneId == 401 or
	   sceneId == 102 or sceneId == 202 or sceneId == 302 or sceneId == 402 or
	   sceneId == 89 or sceneId == 189  or sceneId == 289  or sceneId == 389  then
		return 10
	elseif sceneId == 53 or sceneId == 153 or sceneId == 253 or sceneId == 353 then
		return 15
	elseif	sceneId == 55 or sceneId == 155 or sceneId == 255 or sceneId == 355 then
	    return 20
	elseif	sceneId == 54 or sceneId == 154 or sceneId == 254 or sceneId == 354  or
			sceneId == 104 or sceneId == 204 or sceneId == 304 or sceneId == 404 or
			sceneId == 105 or sceneId == 205 or sceneId == 305 or sceneId == 405 or
			sceneId == 106 or sceneId == 206 or sceneId == 306 or sceneId == 406 or
			sceneId == 107 or sceneId == 207 or sceneId == 307 or sceneId == 407 or
			sceneId == 108 or sceneId == 208 or sceneId == 308 or sceneId == 408 or
			sceneId == 109 or sceneId == 209 or sceneId == 309 or sceneId == 409 or
			sceneId == 110 or sceneId == 210 or sceneId == 310 or sceneId == 410 or
			sceneId == 111 or sceneId == 211 or sceneId == 311 or sceneId == 411 then
	    return 25
	elseif sceneId == 56 or sceneId == 156 or sceneId == 256 or sceneId == 356  then
		return 30
	elseif	sceneId == 57 or sceneId == 157 or sceneId == 257 or sceneId == 357 or
			sceneId == 103 or sceneId == 203  or sceneId == 303  or sceneId == 403 then
	    return 35
	elseif sceneId == 0  or sceneId == 51 or sceneId == 151 or sceneId == 251 or 
		   sceneId == 351 or sceneId == 50 or sceneId == 150 or sceneId == 250 or
		   sceneId == 58 or sceneId == 158 or sceneId == 258 or sceneId == 358 or
		   sceneId == 86 or sceneId == 186 or sceneId == 286 or sceneId == 386 or
		   sceneId == 36 or sceneId == 37 or sceneId == 38 or  sceneId == 15 or
		   sceneId == 350 or sceneId == 2 or sceneId == 3 or sceneId == 4 or sceneId == 5 or 
		   sceneId == 6 or sceneId == 7 or sceneId == 8 or sceneId == 9 or sceneId == 10 or
		   sceneId == 11 or sceneId == 13 or sceneId == 16 or sceneId == 17 or sceneId == 18 or
		   sceneId == 19 or sceneId == 20 or sceneId == 21 or sceneId == 22 or sceneId == 23 or
		   sceneId == 24 or sceneId == 25 or sceneId == 26 or sceneId == 27 or sceneId == 29 or
		   sceneId == 30 or sceneId == 31 or sceneId == 32 or sceneId == 33 or sceneId == 34 or sceneId == 35 or sceneId == 76 or sceneId == 176 or sceneId == 276 or sceneId == 376 then
		return 40
	elseif	sceneId == 501 then
	    return 45
	elseif  sceneId == 503 then
		return 50
	elseif  sceneId == 504 then
		return 55
	elseif  sceneId == 506 then
		return 60
	elseif  sceneId == 507 then
		return 65
	elseif   sceneId == 509 then
		return 70
	elseif  sceneId == 508  then
		return 75
	elseif  sceneId == 510  then
		return 80
	elseif sceneId == 511 then
		return 84
	elseif sceneId == 512 then
		return 88
	elseif sceneId == 513 then
		return 90
	elseif sceneId == 514 then
		return 92
	elseif sceneId == 515 then
		return 94
	elseif sceneId == 516 then
		return 96
	elseif sceneId == 517 then
		return 98
	elseif  sceneId == 518 then
		return 100
	end
	return 0
end

--����Ƿ����������ս�ڼ����ڽ�ֹ�ټ���Χ��
function x310501_lingdicheck( sceneId, selfId )
	local ret = 0
    local minute = GetMinOfDay()
	local posX,posZ = GetWorldPos(sceneId, selfId)
	if  GetWeek() == 6 then
		for i,itm in x310501_g_lingdicheck do
			if sceneId == itm.sceneId and minute >=itm.time1 and minute <= itm.time2 and posX >=itm.x1 and posX <=itm.x2 and posZ >=itm.z1 and posZ <=itm.z2 then
				ret = 1
				break
			end
		end
	end
	return ret
end	