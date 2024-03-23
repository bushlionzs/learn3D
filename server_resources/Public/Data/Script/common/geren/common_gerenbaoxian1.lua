--MisDescBegin

x300610_g_ScriptId 	  = 300610
x300610_g_MissionKind 				= 	1                       --��������
x300610_g_ExtTarget					=	{ {type=20,n=1,target="��"} }
x300610_MissionName = "���ڽ𡿱���"

--MisDescEnd	  
						
--������																	   
x300610_g_SubMissionID				=	{ { MissionId=7556,BaoDanId=13080011,iCostMoney=250 }, 
										  {	MissionId=7557,BaoDanId=13080012,iCostMoney=500 },
										  {	MissionId=7558,BaoDanId=13080013,iCostMoney=750 },
										  {	MissionId=7546,BaoDanId=13080014,iCostMoney=1500 },
										  { MissionId=7547,BaoDanId=13080015,iCostMoney=2000 },
										  { MissionId=7548,BaoDanId=13080016,iCostMoney=2500 },
										}

function x300610_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	if x300610_IsHaveCashbox(sceneId, selfId) == 1 then
		AddQuestNumText(sceneId,x300610_g_ScriptId,x300610_MissionName,3);
	end

end



--�������ť������������ִ�д˽ű�
function x300610_ProcEventEntry( sceneId, selfId, targetId )

	BeginQuestEvent(sceneId)
	local Readme_1 ="\t����û�а׳Ե���ͣ����������Ѻ�˵ĺڽ����Ͷ���Ļ�������Ҫ������#GѺ���5%#W��Ϊ����#r"
	local Readme_2 ="\t������Ѻ�˺ڽ�ɹ�������ɸ��ı��𶼲����˻�������#r"
	local Readme_3 ="\t�����Ѻ�˺ڽ�ʱ�����ķ����������˽��ߣ������쳣�����������ʧ�����������ںڽ�Ѻ�˵�����ظ��������ύ����#G����#W����ȡ#G���ⵥ#W��#r"
	local Readme_4 ="\t����ȡ��#G���ⵥ#W�󣬿��Իص�������#G�ύ���ⵥ#W��������ύ��#G���ⵥ#Wû�����⣬���ǽ���������#G�⸶#W���⸶�Ľ��Ϊ����ȡ�ڽ�Ѻ������ʱ��#GѺ���һ��#W��#r"
	local Readme_5 ="\t��������������Ҫ���Ͻ���Ͷ����"
	
	local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
	AddQuestText(sceneId,Readme)
	EndQuestEvent(sceneId)
	DispatchQuestInfo(sceneId, selfId, targetId, x300610_g_ScriptId, -1);

end

--�ж�����Ƿ����ڳ�
function x300610_IsHaveCashbox( sceneId, selfId )

	local BusObjId = GetBusId(sceneId,selfId)
	if BusObjId ~= -1 then
		if GetBusType(sceneId,BusObjId) == 0 then --��ͨ�ڳ�
			return 1
		end
	end

	return 0

end

--**********************************
--����
--**********************************
function x300610_ProcAcceptCheck( sceneId, selfId, targetId )

	if x300610_IsHaveCashbox(sceneId, selfId) == 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�ܱ�Ǹ�������ڻ���״̬���ܲμ�Ͷ����")
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������ڻ���״̬���ܲμ�Ͷ����",8,2)
		return
	end

	local SubIndex = 0
	for i,itm in x300610_g_SubMissionID do
		if IsHaveQuest(sceneId, selfId, itm.MissionId) > 0 then
			SubIndex = i
			break;
		end
	end

	if SubIndex == 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�ܱ�Ǹ��ֻ����ȡ�˺ڽ�Ѻ��������ܲμ�Ͷ����")
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ����ȡ�˺ڽ�Ѻ��������ܲμ�Ͷ����",8,2)
		return		
	end

	local IsHaveBaoDan = 0
	for i,itm in x300610_g_SubMissionID do
		if HaveItem(sceneId, selfId, itm.BaoDanId) > 0 then
			IsHaveBaoDan = 1
			break;
		end
	end

	if IsHaveBaoDan == 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�ܱ�Ǹ�����������Ѿ��б����ˣ����ȶһ����ⵥ�⸶������ٴ�����Ͷ����")
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����������Ѿ��б����ˣ����ȶһ����ⵥ�⸶������ٴ�����Ͷ����",8,2)
		return		
	end

	local money = GetMoney(sceneId, selfId,0)	
	if money < x300610_g_SubMissionID[SubIndex].iCostMoney then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�ܱ�Ǹ�������ϵ�����������֧�����գ�")
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������ϵ�����������֧�����գ�",8,2)
		return
	end

	BeginAddItem( sceneId )
	AddItem( sceneId, x300610_g_SubMissionID[SubIndex].BaoDanId, 1 )
	local ret = EndAddItem( sceneId, selfId )
	if ret > 0 then
		AddItemListToPlayer(sceneId,selfId)
		local num = CostMoney( sceneId , selfId ,0, x300610_g_SubMissionID[SubIndex].iCostMoney,301)	--�ɹ�����1 ʧ�ܷ���-1
		if num == -1 then
			--��Ӧ�ó����������
			return
		end

		local Readme = "Ͷ���ɹ�,�۳���������#R#{_MONEY"..x300610_g_SubMissionID[SubIndex].iCostMoney.."}" 
		Msg2Player(sceneId,selfId,Readme,8,2)

		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"Ͷ���ɹ���")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId);
		--Msg2Player(sceneId,selfId, "�۳���������#{_MONEY"..x300610_g_SubMissionID[SubIndex].iCostMoney.."}",8,2)
		return 1
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�ܱ�Ǹ�����ı����ռ䲻�㣬����������")
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
		Msg2Player(sceneId,selfId, "�ܱ�Ǹ�����ı����ռ䲻�㣬����������",8,2)
		return 0
	end

end

--**********************************
--����
--**********************************
function x300610_ProcAccept( sceneId, selfId )
end

--�������
--����1����ɹ���0��������ʧ��
function x300610_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
end


--********************************************************************
--����
--********************************************************************
function x300610_ProcQuestAbandon( sceneId, selfId,MissionId )
end

