--������


--�ű��� 301026




--��̬������ʼ������

x301026_g_MissionId = 117


--���ɺ�����ʼ************************************************************************

function 		x301026_OnCreate(sceneId,growPointType,x,y)
	
	local ItemBoxId = ItemBoxEnterScene(x,y,34,sceneId,0,13010260)
	
	
	
end






--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301026_OnOpen(sceneId,selfId,targetId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x301026_g_MissionId)
	if IsHaveQuest(sceneId,selfId, x301026_g_MissionId) > 0 then
			if GetQuestParam(sceneId,selfId,misIndex,0) == 0 then
				if GetItemCount(sceneId,selfId,13010026) < 1 then
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
function	 x301026_OnRecycle(sceneId,selfId,targetId)
	BeginAddItem(sceneId)                                                    
	AddItem( sceneId,13010026, 1 )             
	local ret = EndAddItem(sceneId,selfId)                                 
	if ret > 0 then                                                  
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,format("�õ��ڵ�   %d/1", GetItemCount(sceneId,selfId,13010026)+1))
	        EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)
		AddItemListToPlayer(sceneId,selfId) 
		return 1 
	else                                                             
		BeginQuestEvent(sceneId)                                      
		AddQuestText(sceneId,"��Ʒ��������")                    
		EndQuestEvent(sceneId)                                        
		DispatchQuestTips(sceneId,selfId) 
		return 0
	end   
 
	
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301026_OnProcOver(sceneId,selfId,targetId)

end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301026_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

end
