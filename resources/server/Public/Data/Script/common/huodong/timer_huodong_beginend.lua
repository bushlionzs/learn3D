--�ű���
x302500_g_ScriptId = 302500						
x302500_g_DayInfo1 = {
						{m = 12,d = 24},
						{m = 12,d = 25},
					}
----------------------------------------------------------------------
--������Ч
----------------------------------------------------------------------
function x302500_PlayEffect1(sceneId,selfId )

    --�����ж�
    if sceneId ~= 0 and sceneId ~= 50 and sceneId ~= 150 and sceneId ~= 250 and sceneId ~= 350 and sceneId ~= 15  then 
	  return
	end

	--�����ж�
	local year,month,day = GetYearMonthDay()
	local find1 = 0
	for i,item in x302500_g_DayInfo1 do
		if item.m == month and item.d == day then
			find1 = 1
			break
		end
	end

    --������Ч
	if find1 == 1 then

		CallScriptFunction( 888894, "PlayClientCameraEffect", sceneId, selfId,29,1)
	end

end

----------------------------------------------------------------------
--ֹͣ��Ч
----------------------------------------------------------------------
function x302500_StopEffect1(sceneId)
    --�����ж�
	if sceneId ~= 0 and sceneId ~= 50 and sceneId ~= 150 and sceneId ~= 250 and sceneId ~= 350 and sceneId ~= 15  then 
	  return
	end
	local year,month,day = GetYearMonthDay()
	local find1 = 0
	for i,item in x302500_g_DayInfo1 do
		if item.m == month and item.d == day then
			find1 = 1
			break
		end
	end

	if find1 == 0 then
		local humancount = GetScenePlayerCount(sceneId);
		for	i = 0, humancount - 1 do
			local humanId = GetScenePlayerObjId(sceneId, i);
			if IsPlayerStateNormal( sceneId,humanId ) == 1 then
				CallScriptFunction( 888894, "PlayClientCameraEffect", sceneId, humanId,29,0)
			end
		end
	end	
end

----------------------------------------------------------------------
--��װ����,���ⲿ����
----------------------------------------------------------------------
function x302500_PlayEffect(sceneId,selfId )
	x302500_PlayEffect1(sceneId,selfId )
end

----------------------------------------------------------------------
--��װ����,���
----------------------------------------------------------------------
function x302500_StopEffect(sceneId)
	x302500_StopEffect1(sceneId)
end


----------------------------------------------------------------------
--���ݳ���������Ч
----------------------------------------------------------------------
function x302500_PlayEffectBySceneId(sceneId )
	
	--�����ж�
    if sceneId ~= 0 and sceneId ~= 50 and sceneId ~= 150 and sceneId ~= 250 and sceneId ~= 350 and sceneId ~= 15  then 
	  return 0
	end

	--�����ж�
	local year,month,day = GetYearMonthDay()
	local item = x302500_g_DayInfo1[1]
	if item.m ~= month or item.d ~= day then
		return 0
	end
	
	--10��������
	local md = GetMinOfDay()
	if md < 0 or md >= 10*60*1000 then
		return 0
	end
	
	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			CallScriptFunction( 888894, "PlayClientCameraEffect", sceneId, humanId,29,1)
		end
	end
	
	return 1
end

----------------------------------------------------------------------
--���ݳ���ֹͣ��Ч
----------------------------------------------------------------------
function x302500_StopEffectBySceneId(sceneId)
	x302500_StopEffect1(sceneId)
end

----------------------------------------------------------------------
--��ʱ���¼�
----------------------------------------------------------------------
function x302500_OnTimerDoingStart( SceneId, actId, Param1, Param2, Param3, Param4, Param5 )

	--�ȼ���Ƿ��ǲ�����Ч
	if x302500_PlayEffectBySceneId( SceneId) == 1 then
		return
	end

	--������Ч
	x302500_StopEffectBySceneId(SceneId)
	
end
