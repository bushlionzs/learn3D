
x601005_g_ScriptId = 601005
x601005_g_Exp	=	15000;

--�������ʱ����
function x601005_OnIntervalOverEvent( sceneId, selfId )
end

--��Чʱ����
function x601005_OnActiveEvent( sceneId, selfId )
	AddExp(sceneId, selfId, x601005_g_Exp);
	hf_DisplayAwardInfo(sceneId, selfId, -1, -1, -1, -1, 0, x601005_g_Exp, -1, 0);
end

--Ч����ɢʱ����
function x601005_OnFadeOutEvent( sceneId, selfId )
end