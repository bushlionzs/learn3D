
--����ս�����¼�

--MisDescBegin
x310146_g_ScriptId              = 310146
x310146_g_Time					= { min = 2000,max = 2059 }	--ʱ������
x310146_g_minsterGuid			= 129746					--����ս���Ҿ���GUID
x310146_g_PreTime				=  0
x310146_g_AreaTipsInterval		=  2						--�����¼����
x310146_g_AreaTips				= "#R�������й����ڹ����ҹ����#aB{goto_%d,%d,%d}(%d,%d)#aE�ı����ξ�������پ�Ԯ��"
--MisDescEnd
----------------------------------------------------------------------------------------------
function x310146_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	
	local hour,minute,sec =GetHourMinSec(); --���ʱ���Ƿ���ȷ
	local now = hour *100 + minute
	if now < x310146_g_Time.min or now > x310146_g_Time.max then
		return
	end
	
	local nCurMin = GetMinOfYear()  --����ϴ�����ʱ��
	local nInterval = nCurMin - x310146_g_PreTime
	if nInterval < x310146_g_AreaTipsInterval then
		return	
	end
	
	local nCountry = -1
	local x =0
	local z= 0
	if sceneId == 58 then
		nCountry = 0
		x = 128
		z = 112
	elseif sceneId == 158 then
		nCountry = 1
		x = 128
		z = 112
	elseif sceneId == 258 then
		nCountry = 2
		x = 128
		z = 144
	elseif sceneId == 358 then
		nCountry = 3
		x = 128
		z = 144
	else
		return
	end
	
	if nCountry == GetCurCountry(sceneId,selfId) then  -- ͬ�������˳�
		return
	end
	
	if CallScriptFunction(310150,"IsMonsterValid_x58",sceneId,2 ) == 1 then
		x310146_g_PreTime = nCurMin
		local msg = format( x310146_g_AreaTips,sceneId,x,z,x,z)
		local msg3 ="#R��ǹ��Ҿ����ܵ��й�Ϯ����"
		LuaAllScenceM2Country( sceneId,msg,nCountry, 2,1)
		LuaAllScenceM2Country( sceneId,msg3,nCountry, 5,1)
	end
end

function x310146_ProcTiming( sceneId, now )

end

--����뿪һ�� area ʱ����
function x310146_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )

end