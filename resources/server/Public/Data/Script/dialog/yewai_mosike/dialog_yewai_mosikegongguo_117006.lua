 --密探
x203329_g_ScriptId	= 203329
x203329_g_MissionId	=	827
--**********************************
--事件交互入口
--**********************************
--function x203329_ProcEventEntry( sceneId, selfId,targetId ) 
--local misIndex = GetQuestIndexByID(sceneId, selfId,x203329_g_MissionId) 
--  if GetQuestParam(sceneId, selfId,misIndex,7,1)  < 1 then
--	BeginQuestEvent(sceneId)
--	AddQuestText(sceneId,"\t欢迎你们来到我们斯拉夫人的首都，莫斯科城！\n\t上帝也不希望看到人类相互杀戮，我们的条件很容易满足，请你们尽快给我们一个答复！")
--	EndQuestEvent(sceneId)
--	DispatchQuestEventList(sceneId,selfId,targetId)
--	ShowNpcQuestEventList(sceneId,selfId,targetId)
--	end
--	if IsQuestHaveDone(sceneId, selfId,misIndex)>0 then
--	BeginQuestEvent(sceneId)
--	AddQuestText(sceneId,"\t哼，既然我已经落到你们手里，我无话可说，不过斯拉夫人不会这样屈服的！")
--	EndQuestEvent(sceneId)
--	DispatchQuestEventList(sceneId,selfId,targetId)
--	ShowNpcQuestEventList(sceneId,selfId,targetId)
--	end
--end

function x203329_ProcEventEntry( sceneId, selfId,targetId )            
	BeginQuestEvent(sceneId)                                             
	AddQuestText(sceneId,"\t欢迎你们来到我们斯拉夫人的首都，莫斯科城！\n\t上帝也不希望看到人类相互杀戮，我们的条件很容易满足，请你们尽快给我们一个答复！")     
	EndQuestEvent(sceneId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,827)                                               
	if IsHaveQuest(sceneId,selfId, 827) > 0 then
		if GetQuestParam(sceneId,selfId,misIndex,0) <= 0 then	                     
		 	AddQuestNumText(sceneId, x203330_g_MissionId, "你的阴谋已经败露了！",0, 1)
		end                  
	end                                                                  
	DispatchQuestEventList(sceneId,selfId,targetId)                      
	ShowNpcQuestEventList(sceneId,selfId,targetId)                       
end                                                                    


function x203329_OnDie(sceneId, selfId, killerId)
	SetMonsterCamp(sceneId,selfId,20)
end