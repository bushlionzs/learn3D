--MisDescBegin

x300611_g_ScriptId 	  = 300611
x300611_g_MissionKind 				= 	1                       --��������
x300611_g_ExtTarget					=	{ {type=20,n=1,target="��"} }
x300611_MissionName = "���ڽ𡿶һ����ⵥ"

--MisDescEnd	  
						
--������																	   
x300611_g_SubMissionID				=	{ { MissionId=7556,BaoDanId=13080011,LiPeiDanId=13080017 }, 
										  {	MissionId=7557,BaoDanId=13080012,LiPeiDanId=13080018 },
										  {	MissionId=7558,BaoDanId=13080013,LiPeiDanId=13080019 },
										  {	MissionId=7546,BaoDanId=13080014,LiPeiDanId=13080020 },
										  { MissionId=7547,BaoDanId=13080015,LiPeiDanId=13080021 },
										  { MissionId=7548,BaoDanId=13080016,LiPeiDanId=13080022 },
										}

function x300611_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	if x300611_GetBaoDanId(sceneId, selfId) > 0 then
		AddQuestNumText(sceneId,x300611_g_ScriptId,x300611_MissionName,3);
	end

end



--�������ť������������ִ�д˽ű�
function x300611_ProcEventEntry( sceneId, selfId, targetId )

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"\t���������������#G���յ�#W�һ���#G���ⵥ#W��Ȼ�����Ϳ���ȥ��#GѺ�˱�����#W�����ˣ�")
	EndQuestEvent(sceneId)
	DispatchQuestInfo(sceneId, selfId, targetId, x300611_g_ScriptId, -1);

end

--�ж�����Ƿ����ڳ�
function x300611_GetBaoDanId( sceneId, selfId )

	local BaoDanId = 0
	for i,itm in x300611_g_SubMissionID do
		if HaveItem(sceneId, selfId, itm.BaoDanId) > 0 then
			BaoDanId = i
			break
		end
	end

	return BaoDanId

end

--**********************************
--����
--**********************************
function x300611_ProcAcceptCheck( sceneId, selfId, targetId )
	
	local BaoDanId = x300611_GetBaoDanId(sceneId, selfId)
	if BaoDanId == 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�ܱ�Ǹ��������ʾ���������ܽ������⣡")
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
		return	
	end

	local SubIndex = 0
	for i,itm in x300611_g_SubMissionID do
		if IsHaveQuest(sceneId, selfId, itm.MissionId) > 0 then
			SubIndex = i
			break;
		end
	end

	if SubIndex > 0 and SubIndex == BaoDanId then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�����ֱ�ӻظ��ڽ�Ѻ������,����Ҫ��ȡ���ⵥ��")
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
		return				
	end

	--ɾ������
	local ItemCnt = GetItemCount( sceneId, selfId, x300611_g_SubMissionID[BaoDanId].BaoDanId )
	if ItemCnt > 0 then 
		DelItem(sceneId, selfId,x300611_g_SubMissionID[BaoDanId].BaoDanId,ItemCnt)
	end

	--�������ⵥ
	BeginAddItem( sceneId )
	AddItem( sceneId, x300611_g_SubMissionID[BaoDanId].LiPeiDanId, 1 )
	local ret = EndAddItem( sceneId, selfId )
	if ret > 0 then
		AddItemListToPlayer(sceneId,selfId)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"���ⵥ�һ��ɹ���һ·˳��ѽ��")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

		local Readme = "���ⵥ�һ��ɹ���һ·˳��ѽ��" 
		Msg2Player(sceneId,selfId,Readme,8,2)

		return 1
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�����ռ䲻�㣬����������")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end
	
end

--**********************************
--����
--**********************************
function x300611_ProcAccept( sceneId, selfId )
end

--�������
--����1����ɹ���0��������ʧ��
function x300611_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
end


--********************************************************************
--����
--********************************************************************
function x300611_ProcQuestAbandon( sceneId, selfId,MissionId )
end

