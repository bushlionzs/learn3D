--������

x301310_g_GrowpointId = 176 --��Ӧ������ID
x301310_g_ItemIndex = 13030081 --��Ӧ�ռ���Ʒ��ID


--���ɺ�����ʼ************************************************************************
function 	x301310_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301310_g_GrowpointId, sceneId, 0, x301310_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301310_OnOpen(sceneId,selfId,targetId)
--if IsHaveQuest(sceneId,selfId, 2715) > 0 then
local isHaveMission = IsHaveQuestNM(sceneId,selfId,3039)
		if isHaveMission == 1 then
		if GetItemCount(sceneId,selfId,13030081) == 0 then

		  return 0
		else
    	  	BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"���Ѿ�ץ����С�з��")
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
			return 1
		end
		else
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"�����ʯͷ���Ǳ��ҷ��ĺã�")
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
    	return 1
    end

end
--end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301310_OnRecycle(sceneId,selfId,targetId)
		local x,y = GetWorldPos ( sceneId, selfId )
		x,y = floor ( x + random ( 1,2 ) ) , floor ( y + random ( 1,2 ) )
		CreateMonster(sceneId,1838, x, y, 1, 0, -1,-1,21,30000)
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301310_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

