---------------------------------------------------
-- File: fuben_chanchujinkuangdong.lua
-- Author: Shangy
-- Created: 2010-03-22
-- Version: 0.1

----------------------------------------------------

x700093_g_ScriptId		=	700093

x700093_CSP_BOSS3_ID		=	29
FUBEN_HUANGJINKUANGDONG		=	700012

x700093_g_ExitPos= { sceneId = {50,50,50,50}, x=130, z=70, scriptId=x700093_g_ScriptId }

--��ҽ���һ�� area ʱ����
function x700093_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )

	x700093_ShowTips(sceneId, selfId, str)

	local countryId = GetCurCountry( sceneId, selfId )
	
	if zoneId == 0 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferFunc",sceneId,selfId,x700093_g_ExitPos.sceneId[countryId+1],x700093_g_ExitPos.x, x700093_g_ExitPos.z)
	elseif zoneId == 1 then
		local nBoss3ID = CallScriptFunction(FUBEN_HUANGJINKUANGDONG,"GetFubenData_Param",sceneId,x700093_CSP_BOSS3_ID)
		if nBoss3ID == -1 then
			CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferFunc",sceneId,selfId,x700093_g_ExitPos.sceneId[countryId+1],x700093_g_ExitPos.x, x700093_g_ExitPos.z)
		end
	end
end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x700093_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x700093_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x700093_ProcEventEntry( sceneId, monsterobjid )

end

function x700093_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end
