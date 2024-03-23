
--����ս�����¼�

--MisDescBegin
x310143_g_ScriptId              = 310143
x310143_g_Time					= { min = 2000,max = 2059 }	--ʱ������
x310143_g_minsterGuid			= 129743					--����ս���Ҿ���GUID
x310143_g_PreTime				=  0
x310143_g_AreaTipsInterval		=  2						--�����¼����
x310143_g_AreaTips				= "#R�������й����ڹ����ҹ��ŵ�#aB{goto_%d,%d,%d}(%d,%d)#aE�Ĺ��Ҿ���������پ�Ԯ��"
--MisDescEnd
----------------------------------------------------------------------------------------------
function x310143_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	
	local hour,minute,sec =GetHourMinSec(); --���ʱ���Ƿ���ȷ
	local now = hour *100 + minute
	if now < x310143_g_Time.min or now > x310143_g_Time.max then
		return
	end
	
	local nCurMin = GetMinOfYear()  --����ϴ�����ʱ��
	local nInterval = nCurMin - x310143_g_PreTime
	if nInterval < x310143_g_AreaTipsInterval then
		return	
	end
	
	local nCountry = -1
	local x =0
	local z= 0
	if sceneId == 86 then
		nCountry = 0
		x = 155
		z = 157
	elseif sceneId == 186 then
		nCountry = 1
		x = 150
		z = 167
	elseif sceneId == 286 then
		nCountry = 2
		x = 148
		z = 75
	elseif sceneId == 386 then
		nCountry = 3
		x = 149
		z = 162
	else
		return
	end
	
	if nCountry == GetCurCountry(sceneId,selfId) then  -- ͬ�������˳�
		return
	end
	if CallScriptFunction(310150,"IsMonsterValid_x86",sceneId,2 ) == 1 then
		x310143_g_PreTime = nCurMin
		local msg = format( x310143_g_AreaTips,sceneId,x,z,x,z)
		local msg3 ="#R�ŵ����Ҿ����ܵ��й�Ϯ����"
		LuaAllScenceM2Country( sceneId,msg,nCountry, 2,1)
		LuaAllScenceM2Country( sceneId,msg3,nCountry, 5,1)
	end
end

function x310143_ProcTiming( sceneId, now )

end

--����뿪һ�� area ʱ����
function x310143_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )

end