--�߾�ͨ��2ͨ����ˮ��

x300480_g_ScriptId = 300480
x300480_g_TransPosLou="loulanbianjingexit2xiaoshuidao"
x300480_g_TransPosLai="laiyinbianjingexit2xiaoshuidao"
x300480_g_TransPosKun="kunlunbianjingexit2xiaoshuidao"
x300480_g_TransPosDun="dunhuangbianjingexit2xiaoshuidao"
x300480_g_Notice = "���ĵȼ�������#R20��#Y���޷�ǰ���ص���"

--��ҽ���һ�� area ʱ����
function x300480_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	--print("x300480_ProcAreaEntered sceneId = " .. sceneId .. " selfId = " .. selfId)
	local selfType = GetObjType(sceneId, selfId)

	if selfType == 1 then 
			------------------------------------------------------
			if IsHaveSpecificImpact( sceneId, selfId, 7610) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7607) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7608) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7605) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7616) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7613) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7614) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7611) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7622) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7619) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7620) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7617) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7628) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7625) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7626) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7623) == 1 then
				Msg2Player(sceneId,selfId,"�ܱ�Ǹ��δ���������������ʱ�޷�ͨ������������",8,2)
				return
			end
			--�����������������ֹ���͵Ĵ���
			------------------------------------------------------
			
			local nLevel = GetLevel(sceneId, selfId)
			if nLevel < 20 then 
					Msg2Player(sceneId,selfId,"#Y"..x300480_g_Notice.."#W",4,3)
					return
			end
	end

	if selfType == 9 then	--Bus�������� ��bus��bus����˿糡��
		--print("Bus�������� ��bus��bus����˿糡��")
		local busType = GetBusType(sceneId, selfId)
		if busType == 1 then --BUS_TYPE_NORMAL
			local memberCount = GetBusMemberCount(sceneId, selfId)
			ReadyBusChangeScene(sceneId, sceneId + 1, selfId)--ע�⣺�˲����Ǳ����.BUS�л�������Ҫ����Щ׼������,
			for	i = 0, memberCount - 1 do
				local ObjID = GetBusMemberObjId(sceneId, selfId, i)
				x300480_TransToPosition(sceneId, ObjID)
			end
			--ɾ��BUS,����Ա���ڳ���
			DeleteBus(sceneId, selfId,0)
			return
		end
	elseif selfType == 1 then	--���
		if IsPlayerMutexState(sceneId, selfId,PLAYER_STATE_PROTECTTIME) == 1 then
			return 
		end

		local busId = GetBusId(sceneId, selfId)
		if busId ~= -1 then
			local busType = GetObjType(sceneId, busId)
			if busType == 3 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "�ܱ�Ǹ������Ŀ��е�Σ�գ��ܾ�����ó�����");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return	
			end

			local IsInDist = 0
			local busType = GetBusType(sceneId, busId)
			if busType == 0 then		--�����ڳ�
				--�жϾ���	
				IsInDist = IsValidMyselfBus(sceneId,selfId)
			elseif busType == 2 then	--����ڳ�
				IsInDist = IsValidGuildBus(sceneId,selfId)		
			elseif busType == 3 then	--��������
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "�����ڻ��ͣ�������ô����");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return			
			end
			
			if IsInDist == 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "��Ļ���Ŀ������̫Զ�ˣ�������ô����");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return
			end
				
			local memberCount = GetBusMemberCount(sceneId, busId)
			ReadyBusChangeScene(sceneId, sceneId + 1, busId)--ע�⣺�˲����Ǳ����.BUS�л�������Ҫ����Щ׼������,
			for	i = 0, memberCount - 1 do
				local ObjID = GetBusMemberObjId(sceneId, busId, i)
				x300480_TransToPosition(sceneId, ObjID)
			end
			--ɾ��BUS,����Ա���ڳ���
			DeleteBus(sceneId, busId,0)
			return
		end
		
		local isBusMember = IsBusMember(sceneId, selfId)
--		if isBusMember == 1 then
--			return
--		end
	end
	
	x300480_TransToPosition(sceneId, selfId)
end

function x300480_TransToPosition(sceneId, selfId)
	if sceneId == 51 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x300480_g_TransPosLou)
	elseif sceneId == 151 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x300480_g_TransPosLai)
	elseif sceneId == 251 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x300480_g_TransPosKun)
	elseif sceneId == 351 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x300480_g_TransPosDun)
	end
end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x300480_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x300480_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x300480_ProcEventEntry( sceneId, monsterobjid )

end
