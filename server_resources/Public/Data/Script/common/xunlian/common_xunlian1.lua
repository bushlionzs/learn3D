--ѵ������

--MisDescBegin
x300503_g_ScriptId = 300503
x300503_g_MissionName="��е��ѵ��"
x300503_g_MissionId = 5600
--MisDescEnd
--**********************************

--������ں���

--**********************************

function x300503_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
		local winorlose ="\n����ѵ��ʧ��"
		local misIndex = GetQuestIndexByID(sceneId,selfId,x300503_g_MissionId)
			SetQuestByIndex(sceneId,selfId,misIndex,0,GetQuestParam(sceneId,selfId,misIndex,0)-1)
		if GetQuestParam(sceneId,selfId,misIndex,2) < 100 then
			SetQuestByIndex(sceneId,selfId,misIndex,2,GetQuestParam(sceneId,selfId,misIndex,2)+5)
		end
		if GetQuestParam(sceneId,selfId,misIndex,3) < 100 then
			SetQuestByIndex(sceneId,selfId,misIndex,3,GetQuestParam(sceneId,selfId,misIndex,3)+5)
		end
		if GetQuestParam(sceneId,selfId,misIndex,1) > random (1,100) then
				SetQuestByIndex(sceneId,selfId,misIndex,4,GetQuestParam(sceneId,selfId,misIndex,4)+5)
				winorlose ="\nѵ���ɹ��õ�#G5#W��"
		end                                                                                      
			SetQuestByIndex(sceneId,selfId,misIndex,1,GetQuestParam(sceneId,selfId,misIndex,1)-10)
					if GetQuestParam(sceneId,selfId,misIndex,0) > 0 then
											--local feed1=format("��е��(�ɹ�����%d%%)",GetQuestParam(sceneId,selfId,misIndex,1))
      								--local feed2=format("ʳ�﷨(�ɹ�����%d%%)",GetQuestParam(sceneId,selfId,misIndex,2))
      								--local feed3=format("ģ�·�(�ɹ�����%d%%)",GetQuestParam(sceneId,selfId,misIndex,3))
      	    					--BeginQuestEvent(sceneId)
		 									--AddQuestText(sceneId,"��е��ѵ������ɹ��Ļ�����ֻ�����õ�5�֣�ʳ�﷨ѵ������ɹ��Ļ�����ֻ�����õ�4��6�֣�ģ�·�ѵ������ɹ��Ļ�����ֻ�����õ�3��7�֣�ѡ��һ�ַ���ѵ������ɡ�") 
		 									--AddQuestText(sceneId,format("\n�㻹��ѵ����ֻ����  #G%d#W  ��",GetQuestParam(sceneId,selfId,misIndex,0)))
		 									--AddQuestText(sceneId,format("\n������ѵ���Ĳ���÷�Ϊ  #G%d#W",GetQuestParam(sceneId,selfId,misIndex,4))) 
		 									--AddQuestNumText(sceneId, x300503_g_ScriptId, feed1)
      								--AddQuestNumText(sceneId, x300504_g_ScriptId, feed2)
      								--AddQuestNumText(sceneId, x300505_g_ScriptId, feed3)
            					--EndQuestEvent()
            					--DispatchQuestEventList(sceneId, selfId, targetId)
            					BeginQuestEvent(sceneId)
            					AddQuestText(sceneId,"��е��ѵ������ɹ��Ļ�����ֻ�����õ�5�֣�ʳ�﷨ѵ������ɹ��Ļ�����ֻ�����õ�4��6�֣�ģ�·�ѵ������ɹ��Ļ�����ֻ�����õ�3��7�֣�����ظ���һ�ַ���ѵ���Ļ����ɹ��ļ��ʻή�͡�ѡ��һ�ַ���ѵ������ɡ�") 
		 									AddQuestText(sceneId,winorlose) 
		 									AddQuestText(sceneId,format("\n�㻹��ѵ����ֻ����  #G%d#W  ��",GetQuestParam(sceneId,selfId,misIndex,0)))
		 									AddQuestText(sceneId,format("\n������ѵ���Ĳ���÷�Ϊ  #G%d#W",GetQuestParam(sceneId,selfId,misIndex,4))) 
		 									AddQuestNumText(sceneId, x300503_g_ScriptId, "��е��ѵ������")
		 									EndQuestEvent()
		 									DispatchQuestEventList(sceneId, selfId, targetId)
          elseif GetQuestParam(sceneId,selfId,misIndex,0) == 0 then
          			BeginQuestEvent(sceneId)
          			AddQuestText(sceneId,format("��Ĳ���÷�Ϊ#G%d#W,ȥ����ֻ��������������ȥ�ɡ�",GetQuestParam(sceneId,selfId,misIndex,4))) 
          			EndQuestEvent()
            		DispatchQuestEventList(sceneId, selfId, targetId)
         end

	
end
function x300503_ProcEnumEvent(sceneId, selfId, targetId, MissionId)


    if IsHaveQuest(sceneId,selfId, x300503_g_MissionId) > 0 then
        
        local misIndex = GetQuestIndexByID(sceneId,selfId,x300503_g_MissionId)
        if GetQuestParam(sceneId,selfId,misIndex,0) > 0 then
            AddQuestNumText(sceneId, x300503_g_ScriptId, "��е��ѵ������")
        end
    end
	
end

