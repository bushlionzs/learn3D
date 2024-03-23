--������

x301005_g_GrowpointId = 6 --��Ӧ������ID
x301005_g_ItemIndex = 13020006 --��Ӧ�ռ���Ʒ��ID


--���ɺ�����ʼ************************************************************************
function 	x301005_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301005_g_GrowpointId, sceneId, 0, x301005_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301005_OnOpen(sceneId,selfId,targetId)
	if IsHaveQuest(sceneId,selfId, 2893) > 0 then
		if GetItemCount(sceneId,selfId,x301005_g_ItemIndex) < 5 then
				return 0
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"���Ѿ��ɹ���ܸܸ��") 
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId) 
			return 1
		end
	else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"��û�нӴ�����") 
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId) 
			return 1
	end
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301005_OnRecycle(sceneId,selfId,targetId)
	BeginAddItem(sceneId)                                                    
		AddItem( sceneId,x301005_g_ItemIndex, 1 )             
	  local ret = EndAddItem(sceneId,selfId)                                 
	  if ret > 0 then                                                  
	    AddItemListToPlayer(sceneId,selfId) 
	    BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"�õ�һ��ܸܸ��") 
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId) 
		return 1
	  else                                                             
		  BeginQuestEvent(sceneId)                                      
		  AddQuestText(sceneId,"��Ʒ����������������������")                    
		  EndQuestEvent(sceneId)                                        
		  DispatchQuestTips(sceneId,selfId)                      
	   end           	   
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301005_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

