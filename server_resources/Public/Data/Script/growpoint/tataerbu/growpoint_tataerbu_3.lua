--������


--�ű��� 301027




--��̬������ʼ������

x301027_g_MissionId = 117


--���ɺ�����ʼ************************************************************************

function 		x301027_OnCreate(sceneId,growPointType,x,y)
	
	local ItemBoxId = ItemBoxEnterScene(x,y,35,sceneId,0,13010270)
	
	
	
end






--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301027_OnOpen(sceneId,selfId,targetId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x301027_g_MissionId)
	if IsHaveQuest(sceneId,selfId, x301027_g_MissionId) > 0 then
			if GetQuestParam(sceneId,selfId,misIndex,0) == 0 then
				if GetItemCount(sceneId,selfId,13010026) == 1 then
						return 0
				end
		  else
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"���޷�������")                    
					EndQuestEvent(sceneId)                                        
					DispatchQuestTips(sceneId,selfId)
					return 1 
			end
	else
		BeginQuestEvent(sceneId)                                      
		AddQuestText(sceneId,"��û���������")                    
		EndQuestEvent(sceneId)                                        
		DispatchQuestTips(sceneId,selfId) 
		return 1
	end

end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301027_OnRecycle(sceneId,selfId,targetId)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"������� 1/1")  
	  EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)

		return 0
 
	
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301027_OnProcOver(sceneId,selfId,targetId)

end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301027_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

end
