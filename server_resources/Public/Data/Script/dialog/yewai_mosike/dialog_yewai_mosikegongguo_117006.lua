 --��̽
x203329_g_ScriptId	= 203329
x203329_g_MissionId	=	827
--**********************************
--�¼��������
--**********************************
--function x203329_ProcEventEntry( sceneId, selfId,targetId ) 
--local misIndex = GetQuestIndexByID(sceneId, selfId,x203329_g_MissionId) 
--  if GetQuestParam(sceneId, selfId,misIndex,7,1)  < 1 then
--	BeginQuestEvent(sceneId)
--	AddQuestText(sceneId,"\t��ӭ������������˹�����˵��׶���Ī˹�Ƴǣ�\n\t�ϵ�Ҳ��ϣ�����������໥ɱ¾�����ǵ��������������㣬�����Ǿ��������һ���𸴣�")
--	EndQuestEvent(sceneId)
--	DispatchQuestEventList(sceneId,selfId,targetId)
--	ShowNpcQuestEventList(sceneId,selfId,targetId)
--	end
--	if IsQuestHaveDone(sceneId, selfId,misIndex)>0 then
--	BeginQuestEvent(sceneId)
--	AddQuestText(sceneId,"\t�ߣ���Ȼ���Ѿ��䵽����������޻���˵������˹�����˲������������ģ�")
--	EndQuestEvent(sceneId)
--	DispatchQuestEventList(sceneId,selfId,targetId)
--	ShowNpcQuestEventList(sceneId,selfId,targetId)
--	end
--end

function x203329_ProcEventEntry( sceneId, selfId,targetId )            
	BeginQuestEvent(sceneId)                                             
	AddQuestText(sceneId,"\t��ӭ������������˹�����˵��׶���Ī˹�Ƴǣ�\n\t�ϵ�Ҳ��ϣ�����������໥ɱ¾�����ǵ��������������㣬�����Ǿ��������һ���𸴣�")     
	EndQuestEvent(sceneId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,827)                                               
	if IsHaveQuest(sceneId,selfId, 827) > 0 then
		if GetQuestParam(sceneId,selfId,misIndex,0) <= 0 then	                     
		 	AddQuestNumText(sceneId, x203330_g_MissionId, "�����ı�Ѿ���¶�ˣ�",0, 1)
		end                  
	end                                                                  
	DispatchQuestEventList(sceneId,selfId,targetId)                      
	ShowNpcQuestEventList(sceneId,selfId,targetId)                       
end                                                                    


function x203329_OnDie(sceneId, selfId, killerId)
	SetMonsterCamp(sceneId,selfId,20)
end