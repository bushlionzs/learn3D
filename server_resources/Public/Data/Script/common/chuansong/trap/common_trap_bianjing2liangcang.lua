--�߾�ͨ����������

x550106_g_ScriptId = 550106
x550106_g_TransPosLou="dixialiangcang"
x550106_g_TransPosLai="dixialiangcang"
x550106_g_TransPosKun="dixialiangcang"
x550106_g_TransPosDun="dixialiangcang"
x550106_g_Notice = "���ĵȼ�������#R20��#Y���޷�ǰ���������֣�"


--��ҽ���һ�� area ʱ����
function x550106_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	--print("x550106_ProcAreaEntered sceneId = " .. sceneId .. " selfId = " .. selfId)
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
					Msg2Player(sceneId,selfId,"#Y"..x550106_g_Notice.."#W",4,3)
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
				x550106_TransToPosition(sceneId, ObjID)
			end
			--ɾ��BUS,����Ա���ڳ���
			DeleteBus(sceneId, selfId,0)
			return
		end
	elseif selfType == 1 then	--���
		local busId = GetBusId(sceneId, selfId)
		if busId ~= -1 then
			local busType = GetBusType(sceneId, busId)
			if busType == 3 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "�ܱ�Ǹ������Ŀ��е�Σ�գ��ܾ�����ó�����");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return	
			end

			if busType == 0 or busType == 2 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "�ܱ�Ǹ������Ŀ��е�Σ�գ��ܾ�����ó�����");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return	
			end

			local IsInDist = 0
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
				x550106_TransToPosition(sceneId, ObjID)
			end
			--ɾ��BUS,����Ա���ڳ���
			DeleteBus(sceneId, busId,0)
			return
		end
		
--		local isBusMember = IsBusMember(sceneId, selfId)
--		if isBusMember == 1 then
--			return
--		end
	end
	
	x550106_TransToPosition(sceneId, selfId)
end

function x550106_TransToPosition(sceneId, selfId)

	local nCountry = GetCurCountry(sceneId,selfId)
	
	if sceneId == 51 and nCountry == 0 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550106_g_TransPosLou)
	elseif sceneId == 151 and nCountry == 1 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550106_g_TransPosLai)
	elseif sceneId == 251 and nCountry == 2 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550106_g_TransPosKun)
	elseif sceneId == 351 and nCountry == 3 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550106_g_TransPosDun)
	else
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"һ�����ص�����������֮���⣡���޷�����ǰ�У�")
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)		
	end
end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x550106_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x550106_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550106_ProcEventEntry( sceneId, monsterobjid )

end

