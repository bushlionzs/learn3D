
x300382_g_ScriptId = 300382

--�������ʱ����
function x300382_OnIntervalOverEvent( sceneId, selfId )
	if sceneId == 0 then
		local level = GetLevel(sceneId, selfId)
		local exp = level * level
		AddExp ( sceneId , selfId , exp )
	end
end

--��Чʱ����
function x300382_OnActiveEvent( sceneId, selfId )
end

--Ч����ɢʱ����
function x300382_OnFadeOutEvent( sceneId, selfId )
end

function x300382_ProcEventEntry()
end