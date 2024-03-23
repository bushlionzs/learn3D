--�Թ�5���Թ�4

x300594_g_ScriptId = 300594
x300594_g_TransPosloulan  ="damashige2bosi1"
x300594_g_TransPoslaiyin  ="damashige2bosi2"
x300594_g_TransPoskunlun  ="damashige2bosi3"
x300594_g_TransPosdunhuang="damashige2bosi4"


--��ҽ���һ�� area ʱ����
function x300594_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	--print("x300594_ProcAreaEntered sceneId = " .. sceneId .. " selfId = " .. selfId)
	local selfType = GetObjType(sceneId, selfId)
	
	if selfType == 1 then 
		------------------------------------------------------
		if IsHaveSpecificImpact( sceneId, selfId, 7610) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7607) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7608) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7605) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7616) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7613) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7614) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7611) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7622) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7619) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7620) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7617) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7628) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7625) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7626) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7623) == 1 then
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ��δ���������������ʱ�޷�ͨ������������",8,2)
			return
		end
		--�����������������ֹ���͵Ĵ���
		------------------------------------------------------
	end
	
	if selfType == 9 then	--Bus�������� ��bus��bus����˿糡��
		local busType = GetBusType(sceneId, selfId)
		if busType == 1 then --BUS_TYPE_NORMAL
			local memberCount = GetBusMemberCount(sceneId, selfId)
			local daduSceneId = 0
			ReadyBusChangeScene(sceneId, daduSceneId,selfId)--ע�⣺�˲����Ǳ����.BUS�л�������Ҫ����Щ׼������,
			for	i = 0, memberCount - 1 do
				local ObjID = GetBusMemberObjId(sceneId, selfId, i)
				x300594_TransToPosition(sceneId, ObjID)
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

	local guo = GetCurCountry(sceneId,selfId)
	
	x300594_TransToPosition(sceneId, selfId)
	
end

function x300594_TransToPosition(sceneId, selfId)

	local guo = GetCurCountry(sceneId,selfId)
	
	if guo == 0 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x300594_g_TransPosloulan)
		
		elseif guo == 1 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x300594_g_TransPoslaiyin)
		
		elseif guo == 2 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x300594_g_TransPoskunlun)
		
		elseif guo == 3 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x300594_g_TransPosdunhuang)
	
	end
end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x300594_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x300594_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x300594_ProcEventEntry( sceneId, monsterobjid )

end

