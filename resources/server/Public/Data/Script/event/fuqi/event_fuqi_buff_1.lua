
x300380_g_ScriptId = 300380
--�������ʱ����
function x300380_OnIntervalOverEvent( sceneId, selfId )
	if sceneId == 0 then
		local level = GetLevel(sceneId, selfId)
		local exp = level * level
		AddExp ( sceneId , selfId , exp )
	end
end

--��Чʱ����
function x300380_OnActiveEvent( sceneId, selfId )
end

--Ч����ɢʱ����
function x300380_OnFadeOutEvent( sceneId, selfId )
end

function x300380_ProcEventEntry()
end