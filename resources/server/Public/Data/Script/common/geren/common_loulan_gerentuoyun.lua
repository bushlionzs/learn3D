--MisDescBegin

x300817_g_ScriptId 	  = 300817
x300817_g_MissionKind 				= 	1                       --��������
x300817_g_Mis_Count   = 1--ÿ������Ĵ���
x300817_g_ExtTarget					=	{ {type=20,n=1,target="��"} }
x300817_g_MissionName = "���˹ٸ���"

--MisDescEnd

x300817_CostGold		= 1000

x300817_g_SubMissionID		=	{ {	MisID=7001,DestPosX = 162,DestPosZ = 165 },
								  {	MisID=7009,DestPosX = 163,DestPosZ = 122 },
								  {	MisID=7010,DestPosX = 48,DestPosZ = 210 },
								  {	MisID=7543,DestPosX = 48,DestPosZ = 210 },
								  {	MisID=7544,DestPosX = 48,DestPosZ = 210 },	
								  {	MisID=7545,DestPosX = 48,DestPosZ = 210 },											  
								}																		

function x300817_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
	AddQuestNumText(sceneId,x300817_g_ScriptId,x300817_g_MissionName,3,-1)

end



--�������ť������������ִ�д˽ű�
function x300817_ProcEventEntry( sceneId, selfId, targetId, MissionId,nExtIdx )

	-- local bRet = x300817_IsCanAccept( sceneId, selfId )

	-- if bRet == 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t������ȡ�ٸ�Ѻ�˺󣬲�����#Y1���𿨣��ֽ�#W���Ǿ��ܽ��ٸ������͵�����Ŀ�ĵغܽ��ĵط���#r\tѡ���ֽ����ѣ������԰�B���򿪰������棬��#G����ʹ��#W#Y�ֽ�/��#W�����϶Թ����ɡ�");
		EndQuestEvent(sceneId)
		DispatchQuestInfo(sceneId, selfId, targetId, x300817_g_ScriptId,  -1);
		return
	-- end
	-- if GetGoldMode( sceneId, selfId ) == 1 then
				-- �ֽ�ģʽ
				-- if GetMoney(sceneId, selfId,2) < x300817_CostGold then
					-- BeginQuestEvent(sceneId)
					-- AddQuestText(sceneId, "�ܱ�Ǹ��������Я�����ֽ𲻹�֧���������˷��á�");
					-- EndQuestEvent(sceneId)
					-- DispatchQuestTips(sceneId,selfId)
					-- Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������Я�����ֽ𲻹�֧���������˷��á�",8,2)	
					-- return -2
				-- end
			-- else 
				-- ��ģʽ
				-- if GetMoney(sceneId, selfId,3) < x300817_CostGold then
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
function x300817_IsCanAccept( sceneId, selfId )
	
	local bHaveMission = 0
	for i,itm in x300817_g_SubMissionID do

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
				if GetMoney(sceneId, selfId,2) < x300817_CostGold then
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "�ܱ�Ǹ��������Я�����ֽ𲻹�֧���������˷��á�");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������Я�����ֽ𲻹�֧���������˷��á�",8,2)	
					return -2
				end
			else 
				-- ��ģʽ
				if GetMoney(sceneId, selfId,3) < x300817_CostGold then
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
function x300817_ProcAcceptCheck( sceneId, selfId, targetId, MissionId )
				
	local bRet = x300817_IsCanAccept( sceneId, selfId )

	if bRet ~= 1 then
		return
	end

	--�õ�����ֽ�����ģʽ
	if GetGoldMode( sceneId, selfId ) == 1 then
		--�ֽ�ģʽ
		if CostMoney( sceneId, selfId, 2,x300817_CostGold,301 ) == -1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "�ܱ�Ǹ��������Я�����ֽ𲻹�֧���������˷��á�");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������Я�����ֽ𲻹�֧���������˷��á�",8,2)	
			return
		end
	else 
		--��ģʽ
		if CostMoney( sceneId, selfId, 3,x300817_CostGold,301 ) == -1 then
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

	for i,itm in x300817_g_SubMissionID do

		local bHaveMission = IsHaveQuestNM(sceneId, selfId,itm.MisID )
		if bHaveMission > 0 then
			if i == 1 then
				if BusId ~=-1 then
					ReadyBusChangeScene(sceneId, 58,BusId)
					NewWorld(sceneId, selfId, 58, itm.DestPosX, itm.DestPosZ, x300817_g_ScriptId)	
					DeleteBus(sceneId, BusId,0)		
				end
			elseif i == 2 then
				if BusId ~=-1 then
					ReadyBusChangeScene(sceneId, 86,BusId)
					NewWorld(sceneId, selfId, 86, itm.DestPosX, itm.DestPosZ, x300817_g_ScriptId)	
					DeleteBus(sceneId, BusId,0)			
				end
			else
				if BusId ~=-1 then
					ReadyBusChangeScene(sceneId, 51,BusId)
					NewWorld(sceneId, selfId, 51, itm.DestPosX, itm.DestPosZ, x300817_g_ScriptId)	
					DeleteBus(sceneId, BusId,0)			
				end
			end
		end
	end

end


--**********************************
--����
--**********************************
function x300817_ProcAccept( sceneId, selfId )	
end

--�������
--����1����ɹ���0��������ʧ��
function x300817_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
end


--********************************************************************
--����
--********************************************************************
function x300817_ProcQuestAbandon( sceneId, selfId,MissionId )  	
end


function x300817_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
end

---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300817_QuestLogRefresh( sceneId, selfId, MissionId)
end

function x300817_ProcQuestLogRefresh( sceneId, selfId, MissionId)

end




