
x300383_g_ScriptId = 300383

--�������ʱ����
function x300383_OnIntervalOverEvent( sceneId, selfId )
	if sceneId == 0 then
		local level = GetLevel(sceneId, selfId)
		local exp = level * level
		AddExp ( sceneId , selfId , exp )
	end
end

--��Чʱ����
function x300383_OnActiveEvent( sceneId, selfId )
end

--Ч����ɢʱ����
function x300383_OnFadeOutEvent( sceneId, selfId )
end

function x300383_ProcEventEntry()
end