x310157_g_ScriptId = 310157
 -- ����ս�淨����ID
x310157_g_GameOpenId = 1026

function x310157_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4, Param5 )

    if GetGameOpenById(x310157_g_GameOpenId) <= 0 then
		return
	end

	--���������
	if CountryBattleLite_CheckWeekConfig() == 0 then
		return
	end
	
	
	--��ع㲥
	if actId == 42 then
		
		LuaAllScenceM2Wrold(sceneId,"����ս����20��00�����������˸������ǣ��ŵ����߾��Ĺ�����Բμӣ�",1,1)
		
	elseif actId == 43 then
		
		LuaAllScenceM2Wrold(sceneId,"����ս����5���Ӻ�ʼ�������뾡��������˸������ǣ��ŵ����߾��μ�����ս��",1,1)
		
	elseif actId == 44 then
		
		LuaAllScenceM2Wrold(sceneId,"����ս���Ƚ����У��������ڹ��ҹ���Ա���μӣ�",1,1)
		
	elseif actId == 45then
		
		LuaAllScenceM2Wrold(sceneId,"��������ս�μӽ�ֹʱ�仹��5���ӣ�",1,1)
	
	elseif actId == 46 then
	
	    LuaAllScenceM2Wrold(sceneId,"����ս�Ѿ�������",1,1)
	end

end