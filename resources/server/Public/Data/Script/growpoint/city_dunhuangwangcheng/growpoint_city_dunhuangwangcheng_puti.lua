--������

x301225_g_GrowpointId = 184 --��Ӧ������ID
x301225_g_ItemIndex = 13030081 --��Ӧ�ռ���Ʒ��ID


--���ɺ�����ʼ************************************************************************
function 	x301225_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301225_g_GrowpointId, sceneId, 0, x301225_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301225_OnOpen(sceneId,selfId,targetId)
--if IsHaveQuest(sceneId,selfId, 2715) > 0 then
local isHaveMission = IsHaveQuestNM(sceneId,selfId,1718)
		if isHaveMission == 1 then
		if GetItemCount(sceneId,selfId,13030105) == 0 then

		  return 0
		else
    	  	BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"���Ѿ��������������")
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
			return 1
		end
		else
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"���ص�������ֹ��ӽ���ſ�����")
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
    	return 1
    end

end
--end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301225_OnRecycle(sceneId,selfId,targetId)
		local x,y = GetWorldPos ( sceneId, selfId )
		x,y = floor ( x + random ( 1,2 ) ) , floor ( y + random ( 1,2 ) )
		CreateMonster(sceneId,1150, x, y, 5, 0, -1,-1,21,120000)
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301225_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

