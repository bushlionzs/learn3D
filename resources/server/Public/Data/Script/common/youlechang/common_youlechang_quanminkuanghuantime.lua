--�޵������Ƕ�ʱ��

--�ű���
x310341_g_ScriptId = 310341

function x310341_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4, Param5 )
	if sceneId ~= 39 then
			return
	end
	
	if 0 == Param1 then -- 09:00
		-- ���� sceneId ���� ���ʱ��
		SetGrowPointIntervalContainer(sceneId, 240, 45000)
	elseif 1 == Param1 then -- 23��00
		RecycleGrowPointByType(sceneId, 240, -1)
	end
end