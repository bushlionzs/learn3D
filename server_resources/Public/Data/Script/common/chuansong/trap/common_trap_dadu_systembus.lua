

x310083_g_ScriptId = 310083

--进入一个 area 时触发
function x310083_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	local selfType = GetObjType(sceneId, selfId)
	if selfType == 9 then	--Bus进入区域 把bus和bus里的人跨场景
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
			--删除BUS
			DeleteBus(sceneId, selfId,1)
		end
	end
end

--玩家在一个 area 呆了一段时间没走则定时触发
function x310083_ProcTiming( sceneId, monsterobjid )

end

--玩家离开一个 area 时触发
function x310083_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end

function x310083_ProcEventEntry( sceneId, monsterobjid )

end

	
