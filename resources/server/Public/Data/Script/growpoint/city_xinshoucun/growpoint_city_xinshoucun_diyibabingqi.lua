--������

x301307_g_GrowpointId = 172 --��Ӧ������ID
x301307_g_ItemIndex = {10011001,10021001,10031001,10041001,10051001,10061001} --��Ӧ�ռ���Ʒ��ID

--���ɺ�����ʼ************************************************************************
function 	x301307_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301307_g_GrowpointId, sceneId, 0, x301307_g_ItemIndex[1])
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301307_OnOpen(sceneId,selfId,targetId)
if IsHaveQuest(sceneId,selfId, 3002) > 0 then
local zhiye =GetZhiye( sceneId, selfId)+1
if GetItemCount(sceneId,selfId,x301307_g_ItemIndex[zhiye]) == 0 then
	
		  return 0
	
else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"���Ѿ������ǰ������������̫̰��") 
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId) 
			return 1
end

else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"��û�д�����") 
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId) 
			return 1
end
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301307_OnRecycle(sceneId,selfId,targetId)
	BeginAddItem(sceneId)  
	if GetZhiye( sceneId, selfId) == 0   then                                               
		AddItem( sceneId,10011001, 1 )
			BeginQuestEvent(sceneId)                                      
		  AddQuestText(sceneId,"��������Ʒ��#R�Ҵ���")                    
		  EndQuestEvent(sceneId)                                        
		  DispatchQuestTips(sceneId,selfId) 
	end  
	if  GetZhiye( sceneId, selfId) ==1   then
		AddItem( sceneId,10021001, 1 )
					BeginQuestEvent(sceneId)                                      
		  AddQuestText(sceneId,"��������Ʒ��#R�Ҵ���")                    
		  EndQuestEvent(sceneId)                                        
		  DispatchQuestTips(sceneId,selfId) 
	end    
	if  GetZhiye( sceneId, selfId) ==2   then
		AddItem( sceneId,10031001, 1 )
					BeginQuestEvent(sceneId)                                      
		  AddQuestText(sceneId,"��������Ʒ��#R�Ҵ���")                    
		  EndQuestEvent(sceneId)                                        
		  DispatchQuestTips(sceneId,selfId) 
	end    
	if  GetZhiye( sceneId, selfId) ==3   then
		AddItem( sceneId,10041001, 1 )
					BeginQuestEvent(sceneId)                                      
		  AddQuestText(sceneId,"��������Ʒ��#R�Ҵ�ǹ")                    
		  EndQuestEvent(sceneId)                                        
		  DispatchQuestTips(sceneId,selfId) 
	end    
	if  GetZhiye( sceneId, selfId) ==4   then
		AddItem( sceneId,10051001, 1 ) 
					BeginQuestEvent(sceneId)                                      
		  AddQuestText(sceneId,"��������Ʒ��#R�Ҵ���")                    
		  EndQuestEvent(sceneId)                                        
		  DispatchQuestTips(sceneId,selfId) 
	end    
	if  GetZhiye( sceneId, selfId) ==5   then
		AddItem( sceneId,10061001, 1 )
					BeginQuestEvent(sceneId)                                      
		  AddQuestText(sceneId,"��������Ʒ��#R�Ҵ��")                    
		  EndQuestEvent(sceneId)                                        
		  DispatchQuestTips(sceneId,selfId) 
	end         
		local ret = EndAddItem(sceneId,selfId)                                 
	  if ret > 0 then                                                  
	    AddItemListToPlayer(sceneId,selfId) 
	  else                                                             
		  BeginQuestEvent(sceneId)                                      
		  AddQuestText(sceneId,"��Ʒ��������������������")                    
		  EndQuestEvent(sceneId)                                        
		  DispatchQuestTips(sceneId,selfId)                      
	   end           	               
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301307_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


