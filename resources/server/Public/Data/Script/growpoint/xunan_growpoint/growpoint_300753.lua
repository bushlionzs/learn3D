--�ű��� 300800

--��̬������ʼ������
x300800_g_MissionId 	= 7551
x300800_g_ItemId 		= 13011602
x300800_g_ScriptId 		= 300752
x300800_g_GrowPointType	= 115
x300800_g_ItemCount		= 1


---------------------------------------------------------------------------------------------------
--���ɺ���
---------------------------------------------------------------------------------------------------
function 		x300800_OnCreate(sceneId,growPointType,x,y)
	--����
	local ItemBoxId = ItemBoxEnterScene(x,y,x300800_g_GrowPointType,sceneId,0,x300800_g_ItemId)
end


---------------------------------------------------------------------------------------------------
--��ǰ����
---------------------------------------------------------------------------------------------------
function	 x300800_OnOpen(sceneId,selfId,targetId)
	if IsHaveQuest(sceneId,selfId, x300800_g_MissionId) > 0 then
		if GetItemCount(sceneId,selfId,x300800_g_ItemId) < x300800_g_ItemCount then
			return 0
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

---------------------------------------------------------------------------------------------------
--���պ���
---------------------------------------------------------------------------------------------------
function	 x300800_OnRecycle(sceneId,selfId,targetId)
     return CallScriptFunction( x300800_g_ScriptId, "OnGetGrowPoint", sceneId, selfId, x300800_g_MissionId, x300800_g_ItemId )
end

---------------------------------------------------------------------------------------------------
--�򿪺���
---------------------------------------------------------------------------------------------------
function	x300800_OnProcOver(sceneId,selfId,targetId)

end

function	x300800_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

end
