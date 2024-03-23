------------------------------------------------------------------------------------------
--����ټ���ű�
--�ű���
x300818_g_scriptId 		= 300818 
--��Ʒ��
x300818_g_ItemID		= 12030015
--��Ҫ�ĵȼ�
x300818_g_LevelMin		= 20

--���ټ������б�
x300818_g_SceneList 	= { 50,		--¥������
							51,		--¥���߾�
							58,    --¥�����
							150,	--��ɽ����
							151,	--��ɽ�߾�
							158,    --��ɽ���
							250,	--��������
							251,	--���ر߾�
							258,    --�������
							350,	--�ػ�����
							351,	--�ػͱ߾�
							358,    --�ػ����
							76,		--¥���ŵ�
							176,	--��ɽ�ŵ�
							276,	--���عŵ�
							376,	--�ػ͹ŵ�
							86,		--¥���ŵ�
							186,	--��ɽ�ŵ�
							286,	--���عŵ�
							386,	--�ػ͹ŵ�
							2,		--̩ɽ
							3,		--����ͼ
							4,		--̫��ɽ
							5,		--���踮
							6,		--���ݳ�
							7,		--����
							8,		--����̩ɽ
							9,		--��Ҷ��
							10,     --��ɳĮ
							11,     --�������
							13,		--�͸��
							16,		--��˹��ԭ
							17,		--Ī˹�ƹ���
							18,		--��������
							19,		--��������
							20,		--������
							21,		--��ʥ����۹�
							22,		--��ռͥ�۹�
							23,		--����ʿ��
							24,		--Ү·����
							25,		--���ΰ뵺
							26,		--����
							27,		--����
							29,		--���ݵ�
							30,		--����
							31,		--���
							33,		--ӡ�Ⱥ�
							32,		--������
							34,		--צ�۵�
							35,		--���Ŵ���
							}
--�������ս�ڼ��ͼ�з�Χ���ü��
x300818_g_lingdicheck 	= {							
							  { sceneId= 6,	time1 = 960,time2 = 1020,x1 = 28,x2 = 107,z1 =41,z2 =123},	--���ݳ�
							  { sceneId= 9,	time1 = 960,time2 = 1020,x1 = 132,x2 = 187,z1 =15,z2 =97},	--��Ҷ��
							  { sceneId= 13,time1 = 960,time2 = 1020,x1 = 31,x2 = 126,z1 =165,z2 =236},   --�͸��
							  { sceneId= 18,time1 = 960,time2 = 1020,x1 = 180,x2 = 210,z1 =28,z2 =60},  	--��������
							  { sceneId= 21,time1 = 960,time2 = 1020,x1 = 130,x2 = 288,z1 =70,z2 =191},	--��ʥ����۹�
							  { sceneId= 24,time1 = 960,time2 = 1020,x1 = 84,x2 = 174,z1 =55,z2 =136},	--Ү·����
							  --{ sceneId= 27,time1 = 960,time2 = 1020,x1 = 100,x2 = 100,z1 =100,z2 =100},   --����
							  --{ sceneId= 31,time1 = 960,time2 = 1020,x1 = 100,x2 = 100,z1 =100,z2 =100},	--���
							  --{ sceneId= 34,time1 = 960,time2 = 1020,x1 = 100,x2 = 100,z1 =100,z2 =100},	--צ�۵�
							}
--**********************************
--�¼��������
--**********************************
function x300818_ProcEventEntry( sceneId, selfId, bagIndex )
end

function x300818_IsSkillLikeScript( sceneId, selfId)
	return 1; --����ű���Ҫ����֧��
end

--GL�ص�
function x300818_OnReturn1(sceneId, selfId,MissionData,MissionId,targetId)
	if MissionData >=24 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��ÿСʱֻ��ʹ��25�ΰ���ټ��")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ÿСʱֻ��ʹ��25�ΰ���ټ��",8,2)			
		return
	end
	if HaveItem(sceneId, selfId,x300818_g_ItemID)>0 then
			DelItem(sceneId, selfId,x300818_g_ItemID,1)
		else
			return	--�쳣���
		end
	local posX,posZ = GetWorldPos(sceneId, selfId)
	SendGuildConvokeMsg(sceneId, selfId,posX,posZ)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "���ѳɹ�ʹ�ð���ټ���")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"���ѳɹ�ʹ�ð���ټ���",8,2)	
	local guildid = GetGuildID(sceneId, selfId)
	SetGuildQuestData(sceneId,guildid,GD_GUILD_INDEX_CONVOKE_COUNT,1,1)
end
	
	--���м��ͨ�� 
	--ɾ����Ʒ
function x300818_OnActivateOnce( sceneId, selfId )
	-- ����Ƿ����
	local offcial = GetGuildOfficial(sceneId, selfId)
	if offcial~=5 and offcial~=4 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ������ǰ���ǰ����򸱰����޷�ʹ�ð���ټ��")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ������ǰ���ǰ����򸱰����޷�ʹ�ð���ټ��",8,2)		
		return		
	end
	
	-- ��鳡���Ƿ���Ч����

		if x300818_checkscene(sceneId, selfId) == 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "�ܱ�Ǹ������ǰ���ڵ�ͼ�޷�ʹ�ð���ټ��")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ������ǰ���ڵ�ͼ�޷�ʹ�ð���ټ��",8,2)		
			return		
		end

	--����Ƿ����������ս�ڼ����ڽ�ֹ�ټ���Χ��
	if  GetWeek() == 6 then
		if x300818_lingdicheck(sceneId, selfId) == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "�ܱ�Ǹ�����������ս�ڼ䣬���޷������ͼ�ڸ���ʹ�ð���ټ��")
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����������ս�ڼ䣬���޷������ͼ�ڸ���ʹ�ð���ټ��",8,2)		
			return		
		end	
	end

	-- ���λ�ø����Ŀ��ô��͵�
	if x300818_checkposition(sceneId, selfId) == 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��������λ�õĿ��ô��͵�̫�٣�������ѡ��λ�÷����ټ��")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������λ�õĿ��ô��͵�̫�٣�������ѡ��λ�÷����ټ��",8,2)		
		return
	end
	
	-- ���ÿСʱʹ�ô���
	GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_CONVOKE_COUNT, x300818_g_scriptId, -1, "OnReturn1", -1 )
end

--**********************************
--ֱ��ȡ��Ч����
--ϵͳ��ֱ�ӵ�������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���Ѿ�ȡ����ӦЧ��������ִ�к�������������0��û�м�⵽���Ч��������ִ�С�
--**********************************
function x300818_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

--**********************************
--���������ڣ�
--ϵͳ���ڼ��ܼ���ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1���������ͨ�������Լ���ִ�У�����0���������ʧ�ܣ��жϺ���ִ�С�
--**********************************
function x300818_OnConditionCheck( sceneId, selfId )
	return 1; --����Ҫ�κ�����������ʼ�շ���1��
end

--**********************************
--���ļ�⼰������ڣ�
--ϵͳ���ڼ������ĵ�ʱ����������ӿڣ���������������ķ���ֵȷ���Ժ�������Ƿ�ִ�С�
--����1�����Ĵ���ͨ�������Լ���ִ�У�����0�����ļ��ʧ�ܣ��жϺ���ִ�С�
--ע�⣺�ⲻ�⸺�����ĵļ��Ҳ�������ĵ�ִ�С�
--**********************************
function x300818_OnDeplete( sceneId, selfId )
	return 1;
end

--**********************************
--��������������ڣ�
--�������ܻ���ÿ����������ʱ��������ӿڡ�
--���أ�1�����´�������0���ж�������
--ע�������Ǽ�����Чһ�ε����
--**********************************
function x300818_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end

-- ���λ�úϷ���
function x300818_checkposition( sceneId, selfId)
	
	local posX,posZ = GetWorldPos(sceneId, selfId)
	local selfposX = floor(posX)
	local selfposZ = floor(posZ)
	
	if IsPosCanGo(sceneId,selfposX,selfposZ)==0 then
		return 0
	end
	
	return 1
end

--��鳡��
function x300818_checkscene( sceneId, selfId )
	
	local ret = 0
	for i,item in x300818_g_SceneList do
		if sceneId == item then
			ret = 1
			break
		end
	end
	
	return ret
	
end

--����Ƿ����������ս�ڼ����ڽ�ֹ�ټ���Χ��
function x300818_lingdicheck( sceneId, selfId )
	local ret = 0
    local minute = GetMinOfDay()
	local posX,posZ = GetWorldPos(sceneId, selfId)
	for i,itm in x300818_g_lingdicheck do
		if sceneId == itm.sceneId and minute >=itm.time1 and minute <= itm.time2 and posX >=itm.x1 and posX <=itm.x2 and posZ >=itm.z1 and posZ <=itm.z2 then
			ret = 1
			break
		end
	end
	return ret
end	
