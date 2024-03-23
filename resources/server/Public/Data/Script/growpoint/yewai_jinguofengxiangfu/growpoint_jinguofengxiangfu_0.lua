--������

x301207_g_GrowpointId = 157 --��Ӧ������ID
x301207_g_ItemIndex = 13030022 --��Ӧ�ռ���Ʒ��ID
x301207_g_BossType					= 	647                    --BOSS ID
x301207_g_BossCreate				=	{{	hash=1, type=x301207_g_BossType, x=182, z=121, ai=9, aiscript=1001	}}
x301207_g_Bossid =-1
---------------------------------------------------------------------------------------------------
--����BOSS
---------------------------------------------------------------------------------------------------
function x301207_CreateBoss(sceneId)
	for i, item in x301207_g_BossCreate do
		x301207_g_Bossid = CreateMonster(sceneId, x301207_g_BossType, 182, 121, 5, 1001, -1,-1,21);
		
	end

end										


--���ɺ�����ʼ************************************************************************
function 	x301207_OnCreate(sceneId,growPointType,x,y)

	local ItemBoxId = ItemBoxEnterScene(x, y, x301207_g_GrowpointId, sceneId, 0, x301207_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301207_OnOpen(sceneId,selfId,targetId)
		local nFindObjid = 1
		local nMonsterCount = GetMonsterCount(sceneId)
		for i=1,nMonsterCount do
    		local objid = GetMonsterObjID(sceneId,i-1)
    		if objid == x301207_g_Bossid then
    			nFindObjid = 0
    			break
    		end
		end
		if nFindObjid == 1 then
    	local isHaveMission = IsHaveQuestNM(sceneId,selfId,359);
    	if isHaveMission == 1 then
    		if GetItemCount(sceneId,selfId,13030022) == 0 then
    	    return 0;
    	  else
    	  	BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"���Ѿ��õ������˾�")
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					return 1
				end
    	else
    	    return 1;
    	end
   	else
   		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"�����Ѿ����ٻ���")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
   		return 1
   	end

end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301207_OnRecycle(sceneId,selfId,targetId)
   x301207_CreateBoss(sceneId)
   return 0
  --return CallScriptFunction( MISSION_SCRIPT, "OnRecycle", sceneId, selfId, targetId, x301207_g_GrowpointId, x301207_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301207_OnProcOver(sceneId,selfId,targetId)
  	--return CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )

end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


