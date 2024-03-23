--�ű��� 300802

--��̬������ʼ������
x300802_g_MissionId 	= 7557
x300802_g_ItemId 		= 13011604
x300802_g_ScriptId 		= 300758
x300802_g_GrowPointType	= 117
x300802_g_ItemCount		= 1


---------------------------------------------------------------------------------------------------
--���ɺ���
---------------------------------------------------------------------------------------------------
function 		x300802_OnCreate(sceneId,growPointType,x,y)
	--����
	local ItemBoxId = ItemBoxEnterScene(x,y,x300802_g_GrowPointType,sceneId,0,x300802_g_ItemId)
end


---------------------------------------------------------------------------------------------------
--��ǰ����
---------------------------------------------------------------------------------------------------
function	 x300802_OnOpen(sceneId,selfId,targetId)
	if IsHaveQuest(sceneId,selfId, x300802_g_MissionId) > 0 then
		if GetItemCount(sceneId,selfId,x300802_g_ItemId) < x300802_g_ItemCount then
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
function	 x300802_OnRecycle(sceneId,selfId,targetId)
local x = GetItemBoxWorldPosX(sceneId,targetId)
	local z = GetItemBoxWorldPosZ(sceneId,targetId)
   	
   	local posx = x - 5;
   	local posz = z;
    CreateMonster(sceneId,9560, posx, posz, 16,50, -1,-1,21,1000 * 60 *3 )
   	
   	local posx = x;
   	local posz = z - 5;
   	CreateMonster(sceneId,9560, posx, posz, 16,50, -1,-1,21,1000 * 60 *3 )
   	
   	local posx = x + 5;
   	local posz = z;
   	CreateMonster(sceneId,9560, posx, posz, 16,50, -1,-1,21,1000 * 60 *3 )
	--return CallScriptFunction( x300801_g_ScriptId, "OnGetGrowPoint", sceneId, selfId, x300801_g_MissionId, x300801_g_ItemId )
     return CallScriptFunction( x300802_g_ScriptId, "OnGetGrowPoint", sceneId, selfId, x300802_g_MissionId, x300802_g_ItemId )
end

---------------------------------------------------------------------------------------------------
--�򿪺���
---------------------------------------------------------------------------------------------------
function	x300802_OnProcOver(sceneId,selfId,targetId)

end

function	x300802_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

end
