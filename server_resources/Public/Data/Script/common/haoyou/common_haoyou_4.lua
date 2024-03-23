
x601004_g_ScriptId = 601004
x601004_g_Exp	=	10000;

--间隔发作时调用
function x601004_OnIntervalOverEvent( sceneId, selfId )
end

--生效时调用
function x601004_OnActiveEvent( sceneId, selfId )
	AddExp(sceneId, selfId, x601004_g_Exp);
	hf_DisplayAwardInfo(sceneId, selfId, -1, -1, -1, -1, 0, x601004_g_Exp, -1, 0);
end

--效果消散时调用
function x601004_OnFadeOutEvent( sceneId, selfId )
end