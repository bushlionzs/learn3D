--����·ͨ����

x300474_g_ScriptId = 300474
x300474_g_TransPos="baoding2dadu"
x300474_g_Notice = "���ĵȼ�������#R40��#Y���޷�ǰ����ԭ�󶼣�"

--��ҽ���һ�� area ʱ����
function x300474_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )

	local selfType = GetObjType(sceneId, selfId)
	
	if selfType == 1 then 
		------------------------------------------------------
		if IsHaveSpecificImpact( sceneId, selfId, 7610) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7607) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7608) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7605) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7616) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7613) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7614) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7611) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7622) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7619) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7620) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7617) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7628) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7625) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7626) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7623) == 1 then
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ��δ���������������ʱ�޷�ͨ������������",8,2)
			return
		end
		--�����������������ֹ���͵Ĵ���
		------------------------------------------------------
		if IsHaveSpecificImpact(sceneId, selfId,7702) == 1 then
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ����ս���޷�������ԭ�󶼣�",8,2)
			return
		end
		--����������������ֹ����󶼵Ĵ���
		------------------------------------------------------
	end
	
	if selfType == 9 then	--Bus�������� ��bus��bus����˿糡��
		local busType = GetBusType(sceneId, selfId)
		if busType == 1 then --BUS_TYPE_NORMAL
			local memberCount = GetBusMemberCount(sceneId, selfId)
			local daduSceneId = 0
			ReadyBusChangeScene(sceneId, daduSceneId, selfId)--ע�⣺�˲����Ǳ����.BUS�л�������Ҫ����Щ׼������,
			for	i = 0, memberCount - 1 do
				local ObjID = GetBusMemberObjId(sceneId, selfId, i)
				CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,ObjID,x300474_g_TransPos)
			end
			--ɾ��BUS,����Ա���ڳ���
			DeleteBus(sceneId, selfId,0)
			return
		end
	elseif selfType == 1 then	--���
--		local isBusMember = IsBusMember(sceneId, selfId)
--		if isBusMember == 1 then
--			return
--		end
	end
	
	local strText = ""
	local CanTrans = IsCashboxState(sceneId,selfId)	
	if CanTrans == 1 then
		BeginQuestEvent(sceneId)
			strText = "#Y���ڻ��߻���״̬�У���������"
			AddQuestText(sceneId,strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end
	
	local nLevel = GetLevel(sceneId, selfId)
	if nLevel < 10 then 
		Msg2Player(sceneId,selfId,"#Y"..x300474_g_Notice.."#W",4,3)
	else	
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x300474_g_TransPos)
	end
	
end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x300474_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x300474_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x300474_ProcEventEntry( sceneId, monsterobjid )

end

