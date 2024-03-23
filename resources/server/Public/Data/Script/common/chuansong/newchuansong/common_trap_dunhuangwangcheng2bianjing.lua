--����ͨ���߾�

x550100_g_ScriptId = 550100
x550100_g_TransPosLou="loulanwangcheng2bianjing"
x550100_g_TransPosLai="laiyinwangcheng2bianjing"
x550100_g_TransPosKun="kunlunwangcheng2bianjing"
x550100_g_TransPosDun="dunhuangwangcheng2bianjing"
x550100_g_Notice = "���ĵȼ�������#R20��#Y���޷�ǰ������������"


--��ҽ���һ�� area ʱ����
function x550100_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	--print("x550100_ProcAreaEntered sceneId = " .. sceneId .. " selfId = " .. selfId)
	local selfType = GetObjType(sceneId, selfId)
	
	if selfType == 1 then 
			------------------------------------------------------
			if IsHaveQuestNM( sceneId, selfId, 7537) ~= 0 or  IsHaveQuestNM( sceneId, selfId, 7538) ~= 0 or IsHaveQuestNM( sceneId, selfId, 7539) ~= 0 then
				Msg2Player(sceneId,selfId,"�ܱ�Ǹ��δ���������������ʱ�޷�ͨ������������",8,2)
				return
			end
			--�����������������ֹ���͵Ĵ���
			------------------------------------------------------
			
			local nLevel = GetLevel(sceneId, selfId)
			if nLevel < 20 then 
					Msg2Player(sceneId,selfId,"#Y"..x550100_g_Notice.."#W",4,3)
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
				x550100_TransToPosition(sceneId, ObjID)
			end
			--ɾ��BUS,����Ա���ڳ���
			DeleteBus(sceneId, selfId,0)
			return
		end
	elseif selfType == 1 then	--���
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
				x550100_TransToPosition(sceneId, ObjID)
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
	
	x550100_TransToPosition(sceneId, selfId)
end

function x550100_TransToPosition(sceneId, selfId)
	if sceneId == 50 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550100_g_TransPosLou)
	elseif sceneId == 150 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550100_g_TransPosLai)
	elseif sceneId == 250 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550100_g_TransPosKun)
	elseif sceneId == 350 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550100_g_TransPosDun)
	end
end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x550100_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x550100_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550100_ProcEventEntry( sceneId, monsterobjid )

end

