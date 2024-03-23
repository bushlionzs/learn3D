 --铁木真的特殊对话

--**********************************
--事件交互入口
--**********************************
function x101000_ProcEventEntry( sceneId, selfId,targetId )
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"\t你是什么人？别挡着大爷的好事。")
	EndQuestEvent(sceneId)
	if IsHaveQuest(sceneId,selfId, 3568) > 0 then
		if GetItemCount(sceneId,selfId,13020312) < 1 then
				AddQuestNumText(sceneId, 3568, "你见过峨嵋派的女弟子吗？",0, 1)
		end
	end
	DispatchQuestEventList(sceneId,selfId,targetId)
	ShowNpcQuestEventList(sceneId,selfId,targetId)
end

function x101000_OnDie(sceneId, selfId, killerId)
	SetMonsterCamp(sceneId,selfId,20)
end