
x300384_g_ScriptId = 300384

--�������ʱ����
function x300384_OnIntervalOverEvent( sceneId, selfId )
	if sceneId == 0 then
		local level = GetLevel(sceneId, selfId)
		local exp = level * level
		AddExp ( sceneId , selfId , exp )
	end
end

--��Чʱ����
function x300384_OnActiveEvent( sceneId, selfId )
end

--Ч����ɢʱ����
function x300384_OnFadeOutEvent( sceneId, selfId )
end

function x300384_ProcEventEntry()
end