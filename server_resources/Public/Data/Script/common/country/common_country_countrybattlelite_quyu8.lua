
--����ս�����¼�

--MisDescBegin
x310147_g_ScriptId              = 310147
x310147_g_Time					= { min = 2000,max = 2059 }	--ʱ������
x310147_g_minsterGuid			= 129747					--����ս���Ҿ���GUID
x310147_g_PreTime				=  0
x310147_g_AreaTipsInterval		=  2						--�����¼����
x310147_g_AreaTips				= "#R�������й����ڹ����ҹ����#aB{goto_%d,%d,%d}(%d,%d)#aE����ǰͳ�죬����پ�Ԯ��"
--MisDescEnd
----------------------------------------------------------------------------------------------
function x310147_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	
	local hour,minute,sec =GetHourMinSec(); --���ʱ���Ƿ���ȷ
	local now = hour *100 + minute
	if now < x310147_g_Time.min or now > x310147_g_Time.max then
		return
	end
	
	local nCurMin = GetMinOfYear()  --����ϴ�����ʱ��
	local nInterval = nCurMin - x310147_g_PreTime
	if nInterval < x310147_g_AreaTipsInterval then
		return	
	end
	
	local nCountry = -1
	local x =0
	local z= 0
	if sceneId == 58 then
		nCountry = 0
		x = 96
		z = 76
	elseif sceneId == 158 then
		nCountry = 1
		x = 96
		z = 76
	elseif sceneId == 258 then
		nCountry = 2
		x = 160
		z = 180
	elseif sceneId == 358 then
		nCountry = 3
		x = 160
		z = 180
	else
		return
	end
	
	if nCountry == GetCurCountry(sceneId,selfId) then  -- ͬ�������˳�
		return
	end
	if CallScriptFunction(310150,"IsMonsterValid_x58",sceneId,3 ) == 1 then
		x310147_g_PreTime = nCurMin
		local msg = format( x310147_g_AreaTips,sceneId,x,z,x,z)
		local msg3 ="#R��ǹ��Ҿ����ܵ��й�Ϯ����"
		LuaAllScenceM2Country( sceneId,msg,nCountry, 2,1)
		LuaAllScenceM2Country( sceneId,msg3,nCountry, 5,1)
	end
end

function x310147_ProcTiming( sceneId, now )

end

--����뿪һ�� area ʱ����
function x310147_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )

end