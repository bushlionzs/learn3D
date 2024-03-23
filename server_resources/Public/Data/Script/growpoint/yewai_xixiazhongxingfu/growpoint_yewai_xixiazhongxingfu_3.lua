--������

x301218_g_GrowpointId = 170 --��Ӧ������ID
x301218_g_ItemIndex = 13030067 --��Ӧ�ռ���Ʒ��ID
x301218_g_BossType					= 	815                    --BOSS ID
x301218_g_BossCreate				=	{{	hash=1, type=x301218_g_BossType, x=44, z=210, ai=9, aiscript=-1	}}
x301218_g_Bossid =-1
---------------------------------------------------------------------------------------------------
--����BOSS
---------------------------------------------------------------------------------------------------
function x301218_CreateBoss(sceneId)
	for i, item in x301218_g_BossCreate do
		x301218_g_Bossid = CreateMonster(sceneId, x301218_g_BossType, 44, 210, 5, 1001, -1,-1,21);
		
	end

end										


--���ɺ�����ʼ************************************************************************
function 	x301218_OnCreate(sceneId,growPointType,x,y)
--    print(11111111)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301218_g_GrowpointId, sceneId, 0, x301218_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301218_OnOpen(sceneId,selfId,targetId)
		local nFindObjid = 1
		local nMonsterCount = GetMonsterCount(sceneId)
		for i=1,nMonsterCount do
    		local objid = GetMonsterObjID(sceneId,i-1)
    		if objid == x301218_g_Bossid then
    			nFindObjid = 0
    			break
    		end
		end
		if nFindObjid == 1 then
    	local isHaveMission = IsHaveQuestNM(sceneId,selfId,468);
    	if isHaveMission == 1 then
    		if GetItemCount(sceneId,selfId,13030067) == 0 then
    	    return 0;
    	  else
    	  	BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"���Ѿ��õ��˱�����ָ")
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
					return 1
				end
    	else
    	    return 1;
    	end
   	else
   		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"�ƺ�����ֻ�������ڶ���")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
   		return 1
   	end

end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301218_OnRecycle(sceneId,selfId,targetId)
   x301218_CreateBoss(sceneId)
   return 1
  --return CallScriptFunction( MISSION_SCRIPT, "OnRecycle", sceneId, selfId, targetId, x301218_g_GrowpointId, x301218_g_ItemIndex )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301218_OnProcOver(sceneId,selfId,targetId)
  	--return CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )

end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

