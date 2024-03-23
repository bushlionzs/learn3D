

x310083_g_ScriptId = 310083

--����һ�� area ʱ����
function x310083_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	local selfType = GetObjType(sceneId, selfId)
	if selfType == 9 then	--Bus�������� ��bus��bus����˿糡��
		local busType = GetBusType(sceneId, selfId)
		if busType == 1 then --BUS_TYPE_NORMAL
			local memberCount = GetBusSize(sceneId, selfId)
			for	i = 0, memberCount - 1 do
				local ObjID = GetBusMemberObjId(sceneId, selfId, i)
				if ObjID ~= -1 then
					DelBusMember(sceneId, ObjID, selfId)
					SetWanFaExpMult(  sceneId, ObjID,  0 )
					CancelSpecificImpact(sceneId,ObjID, 7060)
				end
			end
			--ɾ��BUS
			DeleteBus(sceneId, selfId,1)
		end
	end
end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x310083_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x310083_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end

function x310083_ProcEventEntry( sceneId, monsterobjid )

end

	
