
--����ս�����¼�

--MisDescBegin
x310141_g_ScriptId              = 310141
x310141_g_Time					= { min = 2000,max = 2059 }	--ʱ������
x310141_g_minsterGuid			= 129741					--����ս���Ҿ���GUID
x310141_g_PreTime				=  0
x310141_g_AreaTipsInterval		=  2						--�����¼����
x310141_g_AreaTips				= "#R�������й����ڹ����ҹ��߾�#aB{goto_%d,%d,%d}(%d,%d)#aE�����Ź��ر�������پ�Ԯ��"
--MisDescEnd
----------------------------------------------------------------------------------------------
function x310141_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	local hour,minute,sec =GetHourMinSec(); --���ʱ���Ƿ���ȷ
	local now = hour *100 + minute
	if now < x310141_g_Time.min or now > x310141_g_Time.max then
		return
	end
	
	local nCurMin = GetMinOfYear()  --����ϴ�����ʱ��
	local nInterval = nCurMin - x310141_g_PreTime
	if nInterval < x310141_g_AreaTipsInterval then
		return	
	end
	
	local nCountry = -1
	local x =0
	local z= 0
	if sceneId == 51 then
		nCountry = 0
		x = 126
		z = 81
	elseif sceneId == 151 then
		nCountry = 1
		x = 127
		z = 82
	elseif sceneId == 251 then
		nCountry = 2
		x = 126
		z = 166
	elseif sceneId == 351 then
		nCountry = 3
		x = 126
		z = 166
	else
		return
	end
	if nCountry == GetCurCountry(sceneId,selfId) then  -- ͬ�������˳�
		return
	end
	if CallScriptFunction(310150,"IsMonsterValid_x51",sceneId,2 ) == 1 then
		x310141_g_PreTime = nCurMin
		local msg = format( x310141_g_AreaTips,sceneId,x,z,x,z)
		local msg3 ="#R�߾��������Ҿ����ܵ��й�Ϯ����"
		LuaAllScenceM2Country( sceneId,msg,nCountry, 2,1)
		LuaAllScenceM2Country( sceneId,msg3,nCountry, 5,1)
	end
end

function x310141_ProcTiming( sceneId, now )

end

--����뿪һ�� area ʱ����
function x310141_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )

end