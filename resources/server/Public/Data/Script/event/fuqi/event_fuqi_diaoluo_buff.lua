
x300395_g_ScriptId = 300395

--�������ʱ����
function x300395_OnIntervalOverEvent( sceneId, selfId )
	
	SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId,7535, 0);
	BeginAddItem(sceneId)
	AddItem( sceneId, 12030061, 2 )
	AddItem( sceneId, 12030062, 2 )
	AddItem( sceneId, 12030063, 2 )
	AddItem( sceneId, 12030064, 2 )
	
	DropItemListToScene(sceneId, selfId, 1)
end

--��Чʱ����
function x300395_OnActiveEvent( sceneId, selfId )
end

--Ч����ɢʱ����
function x300395_OnFadeOutEvent( sceneId, selfId )
end

function x300395_ProcEventEntry()
end