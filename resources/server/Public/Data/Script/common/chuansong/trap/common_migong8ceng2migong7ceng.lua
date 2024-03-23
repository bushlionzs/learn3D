--(�Թ�8���Թ�7)

x300398_g_ScriptId = 300398
x300398_g_TransPos0	=	"migong8ceng2migong7cengloulan"  
x300398_g_TransPos1	=	"migong8ceng2migong7cengtianshan"  
x300398_g_TransPos2	=	"migong8ceng2migong7cengkunlun"  
x300398_g_TransPos3	=	"migong8ceng2migong7cengdunhuang"


--��ҽ���һ�� area ʱ����
function x300398_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	------------------------------------------------------
	if IsHaveSpecificImpact( sceneId, selfId, 7610) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7607) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7608) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7605) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7616) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7613) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7614) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7611) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7622) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7619) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7620) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7617) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7628) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7625) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7626) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7623) == 1 then
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��δ���������������ʱ�޷�ͨ������������",8,2)
		return
	end
	--�����������������ֹ���͵Ĵ���

	local selfType = GetObjType(sceneId, selfId)
	
	if selfType == 9 then	--Bus�������� ��bus��bus����˿糡��
		local busType = GetBusType(sceneId, selfId)
		if busType == 1 then --BUS_TYPE_NORMAL
			local memberCount = GetBusMemberCount(sceneId, selfId)
			ReadyBusChangeScene(sceneId, sceneId - 1,selfId)--ע�⣺�˲����Ǳ����.BUS�л�������Ҫ����Щ׼������,
			for	i = 0, memberCount - 1 do
				local ObjID = GetBusMemberObjId(sceneId, selfId, i)
				x300398_TransToPosition(sceneId, ObjID)
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

			if busType == 0 or busType == 2 then
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
				x300398_TransToPosition(sceneId, ObjID)
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
	
	x300398_TransToPosition(sceneId, selfId)

end

function x300398_TransToPosition(sceneId, selfId)

	if sceneId == 111 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x300398_g_TransPos0)
	elseif sceneId == 211 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x300398_g_TransPos1)
	elseif sceneId == 311 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x300398_g_TransPos2)
	elseif sceneId == 411 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x300398_g_TransPos3)
	end
end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x300398_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x300398_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x300398_ProcEventEntry( sceneId, monsterobjid )

end