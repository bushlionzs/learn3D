
--效果的ID

--**********************************
--事件交互入口
--**********************************
function x417005_ProcEventEntry( sceneId, selfId, bagIndex,rorf )
	local zhiye = GetZhiye(sceneId, selfId);
	local MissionId = 1441 + zhiye;
	if IsHaveQuestNM(sceneId, selfId, MissionId) > 0 then
		local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId)
		SetQuestByIndex(sceneId,selfId,misIndex,0,1)
		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	end
end


