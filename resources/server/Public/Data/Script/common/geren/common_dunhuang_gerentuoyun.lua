--MisDescBegin

x300849_g_ScriptId 	  = 300849
x300849_g_MissionKind 			= 	1                       --��������
x300849_g_Mis_Count   = 1--ÿ������Ĵ���
x300849_g_ExtTarget					=	{ {type=20,n=1,target="��"} }
x300849_g_MissionName = "���˹ٸ���"

--MisDescEnd

x300849_CostGold		= 1000

x300849_g_SubMissionID		=	{ {	MisID=7608,DestPosX = 94,DestPosZ = 91 },
								  {	MisID=7609,DestPosX = 106,DestPosZ = 135 },
								  {	MisID=7610,DestPosX = 208,DestPosZ = 35 },
								  {	MisID=7611,DestPosX = 208,DestPosZ = 35 },
								  {	MisID=7612,DestPosX = 208,DestPosZ = 35 },	
								  {	MisID=7613,DestPosX = 208,DestPosZ = 35 },											  
								}																		

function x300849_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
	AddQuestNumText(sceneId,x300849_g_ScriptId,x300849_g_MissionName,3,-1)

end



--�������ť������������ִ�д˽ű�
function x300849_ProcEventEntry( sceneId, selfId, targetId, MissionId,nExtIdx )

	-- local bRet = x300849_IsCanAccept( sceneId, selfId )

	-- if bRet == 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t������ȡ�ٸ�Ѻ�˺󣬲�����#Y1���𿨣��ֽ�#W���Ǿ��ܽ��ٸ������͵�����Ŀ�ĵغܽ��ĵط���#r\tѡ���ֽ����ѣ������԰�B���򿪰������棬��#G����ʹ��#W#Y�ֽ�/��#W�����϶Թ����ɡ�");
		EndQuestEvent(sceneId)
		DispatchQuestInfo(sceneId, selfId, targetId, x300849_g_ScriptId,  -1);
		return
	-- end
	-- if GetGoldMode( sceneId, selfId ) == 1 then
				-- �ֽ�ģʽ
				-- if GetMoney(sceneId, selfId,2) < x300849_CostGold then
					-- BeginQuestEvent(sceneId)
					-- AddQuestText(sceneId, "�ܱ�Ǹ��������Я�����ֽ𲻹�֧���������˷��á�");
					-- EndQuestEvent(sceneId)
					-- DispatchQuestTips(sceneId,selfId)
					-- Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������Я�����ֽ𲻹�֧���������˷��á�",8,2)	
					-- return -2
				-- end
			-- else 
				-- ��ģʽ
				-- if GetMoney(sceneId, selfId,3) < x300849_CostGold then
					-- BeginQuestEvent(sceneId)
					-- AddQuestText(sceneId, "�ܱ�Ǹ��������Я���Ľ𿨲���֧���������˷��á�");
					-- EndQuestEvent(sceneId)
					-- DispatchQuestTips(sceneId,selfId)
					-- Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������Я���Ľ𿨲���֧���������˷��á�",8,2)	
					-- return -2
				-- end
			-- end

end

--����Ƿ��ܽ��ܴ�����
--����ֵ��-2--�ֽ𲻹�  -1--û��������� 0--�ڳ�������Ч����	1--���Խ�������
function x300849_IsCanAccept( sceneId, selfId )
	
	local bHaveMission = 0
	for i,itm in x300849_g_SubMissionID do

		bHaveMission = IsHaveQuestNM(sceneId, selfId,itm.MisID )
		if bHaveMission > 0 then
			local valid = IsValidMyselfBus(sceneId, selfId,itm.MisID)
			if valid == 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "�ܱ�Ǹ��������û�ڸ������޷�����,���ҵ���������");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������û�ڸ������޷�����,���ҵ���������",8,2)
				return 0
			end
		
			--�õ�����ֽ�����ģʽ
			if GetGoldMode( sceneId, selfId ) == 1 then
				-- �ֽ�ģʽ
				if GetMoney(sceneId, selfId,2) < x300849_CostGold then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "�ܱ�Ǹ��������Я�����ֽ𲻹�֧���������˷��á�");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������Я�����ֽ𲻹�֧���������˷��á�",8,2)	
					return -2
				end
			else 
				-- ��ģʽ
				if GetMoney(sceneId, selfId,3) < x300849_CostGold then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "�ܱ�Ǹ��������Я���Ľ𿨲���֧���������˷��á�");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������Я���Ľ𿨲���֧���������˷��á�",8,2)	
					return -2
				end
			end

			return 1
						
		end

	end

	-- if IsHaveQuestNM(sceneId, selfId,7001 ) > 0 then
		-- ��7001
		-- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, "�ܱ�Ǹ������ֻ���ܿ�Խ���߾��Ĺٸ����������⡣");
		-- EndQuestEvent(sceneId)
		-- DispatchQuestTips(sceneId,selfId)
		-- Msg2Player(sceneId,selfId,"�ܱ�Ǹ������ֻ���ܵ���#G��ת��#W��#G���ƹ�#W�������⡣",8,2)
	-- else
		--û���κιٸ�Ѻ��
		 BeginQuestEvent(sceneId)
		 AddQuestText(sceneId, "�ܱ�Ǹ������������ȡ�ٸ��������ܽ������ˣ�");
		 EndQuestEvent(sceneId)
		 DispatchQuestTips(sceneId,selfId)
		 Msg2Player(sceneId,selfId,"�ܱ�Ǹ������������ȡ�ٸ��������ܽ������ˣ�",8,2)
	-- end

	return -1;

end


--**********************************
--����
--**********************************
function x300849_ProcAcceptCheck( sceneId, selfId, targetId, MissionId )
				
	local bRet = x300849_IsCanAccept( sceneId, selfId )

	if bRet ~= 1 then
		return
	end

	--�õ�����ֽ�����ģʽ
	if GetGoldMode( sceneId, selfId ) == 1 then
		--�ֽ�ģʽ
		if CostMoney( sceneId, selfId, 2,x300849_CostGold,301 ) == -1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "�ܱ�Ǹ��������Я�����ֽ𲻹�֧���������˷��á�");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������Я�����ֽ𲻹�֧���������˷��á�",8,2)	
			return
		end
	else 
		--��ģʽ
		if CostMoney( sceneId, selfId, 3,x300849_CostGold,301 ) == -1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "�ܱ�Ǹ��������Я���Ľ𿨲���֧���������˷��á�");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������Я���Ľ𿨲���֧���������˷��á�",8,2)	
			return
		end
	end

	local InBus = IsBusMember(sceneId, selfId)

	if InBus ~= 1 then
		return
	end

	local BusId = GetBusId(sceneId, selfId)

	for i,itm in x300849_g_SubMissionID do

		local bHaveMission = IsHaveQuestNM(sceneId, selfId,itm.MisID )
		if bHaveMission > 0 then
			if i == 1 then
				if BusId ~=-1 then
					ReadyBusChangeScene(sceneId, 358,BusId)
					NewWorld(sceneId, selfId, 358, itm.DestPosX, itm.DestPosZ, x300849_g_ScriptId)	
					DeleteBus(sceneId, BusId,0)	
				end
			elseif i == 2 then
				if BusId ~=-1 then
					ReadyBusChangeScene(sceneId, 386,BusId)
					NewWorld(sceneId, selfId, 386, itm.DestPosX, itm.DestPosZ, x300849_g_ScriptId)	
					DeleteBus(sceneId, BusId,0)	
				end
			else
				if BusId ~=-1 then
					ReadyBusChangeScene(sceneId, 351,BusId)
					NewWorld(sceneId, selfId, 351, itm.DestPosX, itm.DestPosZ, x300849_g_ScriptId)	
					DeleteBus(sceneId, BusId,0)			
				end
			end
		end
	end

end


--**********************************
--����
--**********************************
function x300849_ProcAccept( sceneId, selfId )	
end

--�������
--����1����ɹ���0��������ʧ��
function x300849_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
end


--********************************************************************
--����
--********************************************************************
function x300849_ProcQuestAbandon( sceneId, selfId,MissionId )  	
end


function x300849_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
end

---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300849_QuestLogRefresh( sceneId, selfId, MissionId)
end

function x300849_ProcQuestLogRefresh( sceneId, selfId, MissionId)

end




