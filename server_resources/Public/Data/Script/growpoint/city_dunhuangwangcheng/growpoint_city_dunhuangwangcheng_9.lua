--������

x301010_g_GrowpointId = 11 --��Ӧ������ID
x301010_g_ItemIndex = 13011003 --��Ӧ�ռ���Ʒ��ID
x301010_g_MissionId = 2895
x301010_g_Bossid =-1
x301010_g_DemandItem ={{id=13020007,num=1},{id=13020008,num=1},{id=13020009,num=1}}

--���ɺ�����ʼ************************************************************************
function 	x301010_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301010_g_GrowpointId, sceneId, 0, x301010_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301010_OnOpen(sceneId,selfId,targetId)
		local misIndex = GetQuestIndexByID(sceneId,selfId,x301010_g_MissionId)
		if IsHaveQuest(sceneId,selfId, x301010_g_MissionId) > 0 then
			if GetItemCount(sceneId,selfId,x301010_g_DemandItem[3].id) >= x301010_g_DemandItem[3].num then
					return 0
			else
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"�ںڵ�ʯ��ɢ����а��Ĺ�ԣ��ƺ���Ҫһ����ʯ���ܿ�������")
					EndQuestEvent()
					DispatchQuestEventList(sceneId, selfId, selfId);
					return 1
			end
		end
		return 1
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301010_OnRecycle(sceneId,selfId,targetId)
		local misIndex = GetQuestIndexByID(sceneId,selfId,x301010_g_MissionId)
		if IsHaveQuest(sceneId,selfId, x301010_g_MissionId) > 0 then
						DelItem( sceneId,selfId,x301010_g_DemandItem[3].id, x301010_g_DemandItem[3].num )
						BeginAddItem(sceneId)
						AddItem( sceneId, x301010_g_DemandItem[1].id, x301010_g_DemandItem[1].num )
    				EndAddItem(sceneId,selfId)
    				AddItemListToPlayer(sceneId,selfId)
    				BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"�ںڵ�ʯ���ſ������³�һ���ںڵ����ӡ�")
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, selfId);
						return 0
		end
		return 0

end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301010_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

