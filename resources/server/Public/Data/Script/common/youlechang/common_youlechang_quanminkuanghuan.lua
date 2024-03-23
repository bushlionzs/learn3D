--������

x310335_g_GrowpointId = 240 --��Ӧ������ID
x310335_g_ItemIndex = 10018001 --��Ӧ�ռ���Ʒ��ID

x310335_g_GameId = 1042

--���ɺ�����ʼ************************************************************************
function 	x310335_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x310335_g_GrowpointId, sceneId, 0, x310335_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x310335_OnOpen(sceneId,selfId,targetId)
	if GetGameOpenById(x310335_g_GameId) <= 0 then
		Msg2Player(sceneId,selfId,"�˻�ѹر�",8,3)
		return 1
	end
    if GetTopListInfo_MinLevel( GetWorldID( sceneId, selfId) ) < 65 then
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ���ȼ����а����һ�����δ��65�����޷��ɼ�",8,3)
        return 1
    end
	return 0
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x310335_OnRecycle(sceneId,selfId,targetId)
	GamePlayScriptLog(sceneId, selfId, 1621)
	local nHumanCount = GetScenePlayerCount(sceneId)
	for i=0,nHumanCount do
  		local objId = GetScenePlayerObjId(sceneId,i)
  		if IsPlayerStateNormal(sceneId,objId) == 1 then
  			local level = GetLevel(sceneId,objId)
  				if selfId == objId then
  					if level >64 then
  						AddExp(sceneId,selfId, level*500)
  						Msg2Player( sceneId, selfId, format("����Ѱ��ħŮ��ˮ���򣬻��%d�㾭��",level*500), 8, 2) 
  					else	                                                                                   
  						Msg2Player( sceneId, objId, format("��������65�����޷��ɼ�ħŮ��ˮ����"), 8, 2)
  					end	
  				else
  					if level >64 then
  						AddExp(sceneId,objId, level*100)
  						Msg2Player( sceneId, objId, format("�������Ѱ����ħŮ��ˮ����ÿ�˻��%d�㾭��",level*100), 8, 2)
  					end	
  				end
  		end
	end
        
	return 1
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x310335_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x310335_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
