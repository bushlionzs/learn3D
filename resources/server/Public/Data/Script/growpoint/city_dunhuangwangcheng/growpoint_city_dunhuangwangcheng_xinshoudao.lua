--������

x301200_g_GrowpointId = 150 --��Ӧ������ID
x301200_g_ItemIndex = 10010010--��Ӧ�ռ���Ʒ��ID


--���ɺ�����ʼ************************************************************************
function 	x301200_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301200_g_GrowpointId, sceneId, 0, x301200_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301200_OnOpen(sceneId,selfId,targetId)
--if IsHaveQuest(sceneId,selfId, 2715) > 0 then
if GetItemCount(sceneId,selfId,10010010) == 0 then
	if GetZhiye( sceneId, selfId)==0 then
		     return 0  	                 
	else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"�����ְҵ����") 
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId) 
			return 1
	end
else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"���Ѿ���һ��������") 
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId) 
			return 1
end
--else
--			BeginQuestEvent(sceneId)
--			AddQuestText(sceneId,"��û�нӴ�����") 
--			EndQuestEvent()
--			DispatchQuestTips(sceneId, selfId) 
--			return 1
end
--end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301200_OnRecycle(sceneId,selfId,targetId)
	BeginAddItem(sceneId)                                                    
		AddBindItem( sceneId,10010010, 1 ) 
		local ret = EndAddItem(sceneId,selfId)                                 
	  if ret > 0 then                                                  
	    AddItemListToPlayer(sceneId,selfId) 
	  else                                                             
		  BeginQuestEvent(sceneId)                                      
		  AddQuestText(sceneId,"��Ʒ����������������������")                    
		  EndQuestEvent(sceneId)                                        
		  DispatchQuestTips(sceneId,selfId)                      
	   end    
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301200_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

