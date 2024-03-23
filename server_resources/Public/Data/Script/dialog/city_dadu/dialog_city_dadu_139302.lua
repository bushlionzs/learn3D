 --铁木真的特殊对话

--**********************************
--事件交互入口
--**********************************
function x101002_ProcEventEntry( sceneId, selfId,targetId )
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"\t阿弥陀佛，佛门净地请施主不要到处乱走。")
	EndQuestEvent(sceneId)
	if IsHaveQuest(sceneId,selfId, 3574) > 0 then
				AddQuestNumText(sceneId, 3574, "色即是空",0, 1)
	end
	DispatchQuestEventList(sceneId,selfId,targetId)
	ShowNpcQuestEventList(sceneId,selfId,targetId)
end

function x101002_OnDie(sceneId, selfId, killerId)
	SetMonsterCamp(sceneId,selfId,20)
end