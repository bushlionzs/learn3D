--������

x301312_g_GrowpointId = 178 --��Ӧ������ID
x301312_g_ItemIndex = 13030089 --��Ӧ�ռ���Ʒ��ID


--���ɺ�����ʼ************************************************************************
function 	x301312_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301312_g_GrowpointId, sceneId, 0, x301312_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301312_OnOpen(sceneId,selfId,targetId)
if IsHaveQuest(sceneId,selfId, 1608) > 0 then
if GetItemCount(sceneId,selfId,13030089) == 0 then
		if GetItemCount(sceneId,selfId,13030087) == 1 then
	
		  return 0
		end
else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"���Ѿ������ˣ�") 
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId) 
			return 1
end
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
function	 x301312_OnRecycle(sceneId,selfId,targetId)
	BeginAddItem(sceneId)                                                    
		AddItem( sceneId,13030089, 1 )  
		AddQuestText(sceneId,"���������Ʒ�����㣡")           
		local ret = EndAddItem(sceneId,selfId)                                 
	  if ret > 0 then                                                  
	    AddItemListToPlayer(sceneId,selfId) 
	    DelItem(sceneId, selfId, 13030087, 1)
	  else                                                             
		  BeginQuestEvent(sceneId)                                      
		  AddQuestText(sceneId,"��Ʒ����������������������")                    
		  EndQuestEvent(sceneId)                                        
		  DispatchQuestTips(sceneId,selfId)                      
	   end           	               
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301312_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

