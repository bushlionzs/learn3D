--author: 	jiangchao
--function:	��������ս�㲥
--date:		2010-09-23

--�ű���
x300970_g_ScriptId = 300970

function x300970_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4, Param5 )
	
	if GetWeek() == 0 then --����ԭ�еĴ���������������������
		return
	end
	
	local nWorldId = GetWorldIdEx()
	local nGuid , nRank = GetToplistInfo(nWorldId, 0 , 0) --��ȡ�ȼ����а�ĵ�һ��
	if nRank < 50 then
		return
	end

	for i=0, 3 do 
		if GetCountryKingGuildIdNM(i) < 0 then
			x300970_BroadcastMsg2Country(sceneId , i , Param1)
		end
	end
end
			
			

function x300970_BroadcastMsg2Country(sceneId , nCountryID , Param1)			
	--��ع㲥
	if Param1 == 0 then
		
		LuaAllScenceM2Country(sceneId,"����ս������ʱ�佫��14��00��ʼ����μӱ����İ������׼����", nCountryID , CHAT_RIGHTDOWN,1)
		LuaAllScenceM2Country(sceneId,"����ս������ʱ�佫��14��00��ʼ����μӱ����İ������׼����", nCountryID , CHAT_LEFTDOWN, 1)
		LuaAllScenceM2Country(sceneId,"����ս������ʱ�佫��14��00��ʼ����μӱ����İ������׼����", nCountryID , CHAT_MAIN_RIGHTDOWN, 1)
		
	elseif Param1 == 1 then
		
		LuaAllScenceM2Country(sceneId,"����ս������ʱ�佫��14��00��ʼ����μӱ����İ������׼����", nCountryID , CHAT_RIGHTDOWN,1)
		LuaAllScenceM2Country(sceneId,"����ս������ʱ�佫��14��00��ʼ����μӱ����İ������׼����", nCountryID , CHAT_LEFTDOWN, 1)
		LuaAllScenceM2Country(sceneId,"����ս������ʱ�佫��14��00��ʼ����μӱ����İ������׼����", nCountryID , CHAT_MAIN_RIGHTDOWN, 1)
		
	elseif Param1 == 2 then
		
		LuaAllScenceM2Country(sceneId,"����ս������ʱ�佫��14��00��ʼ����μӱ����İ������׼����",nCountryID , CHAT_RIGHTDOWN,1)      
		LuaAllScenceM2Country(sceneId,"����ս������ʱ�佫��14��00��ʼ����μӱ����İ������׼����",nCountryID , CHAT_LEFTDOWN, 1)      
		LuaAllScenceM2Country(sceneId,"����ս������ʱ�佫��14��00��ʼ����μӱ����İ������׼����",nCountryID , CHAT_MAIN_RIGHTDOWN, 1)
		
	elseif Param1 == 3 then
		
		LuaAllScenceM2Country(sceneId,"����ս������ʱ�佫��14��00��ʼ����μӱ����İ������׼����",nCountryID , CHAT_RIGHTDOWN,1)      
		LuaAllScenceM2Country(sceneId,"����ս������ʱ�佫��14��00��ʼ����μӱ����İ������׼����",nCountryID , CHAT_LEFTDOWN, 1)      
		LuaAllScenceM2Country(sceneId,"����ս������ʱ�佫��14��00��ʼ����μӱ����İ������׼����",nCountryID , CHAT_MAIN_RIGHTDOWN, 1)
	
	elseif Param1 == 4 then
	
	    LuaAllScenceM2Country(sceneId,"����ս��������ʼ����μӵİ��ǰ���������ǹ��ҹ���Ա��������",nCountryID , CHAT_RIGHTDOWN,1)      
	    LuaAllScenceM2Country(sceneId,"����ս��������ʼ����μӵİ��ǰ���������ǹ��ҹ���Ա��������",nCountryID , CHAT_LEFTDOWN, 1)      
	    LuaAllScenceM2Country(sceneId,"����ս��������ʼ����μӵİ��ǰ���������ǹ��ҹ���Ա��������",nCountryID , CHAT_MAIN_RIGHTDOWN, 1)
	elseif Param1 == 5 then
	
	    LuaAllScenceM2Country(sceneId,"����ս��������ʼ����μӵİ��ǰ���������ǹ��ҹ���Ա��������",nCountryID , CHAT_RIGHTDOWN,1)      
	    LuaAllScenceM2Country(sceneId,"����ս��������ʼ����μӵİ��ǰ���������ǹ��ҹ���Ա��������",nCountryID , CHAT_LEFTDOWN, 1)      
	    LuaAllScenceM2Country(sceneId,"����ս��������ʼ����μӵİ��ǰ���������ǹ��ҹ���Ա��������",nCountryID , CHAT_MAIN_RIGHTDOWN, 1)
	elseif Param1 == 6 then
	
	    LuaAllScenceM2Country(sceneId,"����ս��������ʼ����μӵİ��ǰ���������ǹ��ҹ���Ա��������",nCountryID , CHAT_RIGHTDOWN,1)      
	    LuaAllScenceM2Country(sceneId,"����ս��������ʼ����μӵİ��ǰ���������ǹ��ҹ���Ա��������",nCountryID , CHAT_LEFTDOWN, 1)      
	    LuaAllScenceM2Country(sceneId,"����ս��������ʼ����μӵİ��ǰ���������ǹ��ҹ���Ա��������",nCountryID , CHAT_MAIN_RIGHTDOWN, 1)
	elseif Param1 == 7 then
	
	    LuaAllScenceM2Country(sceneId,"����ս������������",nCountryID , CHAT_RIGHTDOWN,1)      
	    LuaAllScenceM2Country(sceneId,"����ս������������",nCountryID , CHAT_LEFTDOWN, 1)      
	    LuaAllScenceM2Country(sceneId,"����ս������������",nCountryID , CHAT_MAIN_RIGHTDOWN, 1)
	elseif Param1 == 8 then
	
		LuaAllScenceM2Country(sceneId,"����ս������20��00�ֿ���������ǰ����׼����",nCountryID , CHAT_RIGHTDOWN,1)      
		LuaAllScenceM2Country(sceneId,"����ս������20��00�ֿ���������ǰ����׼����",nCountryID , CHAT_LEFTDOWN, 1)      
		LuaAllScenceM2Country(sceneId,"����ս������20��00�ֿ���������ǰ����׼����",nCountryID , CHAT_MAIN_RIGHTDOWN, 1)
	elseif Param1 == 9 then
	
		LuaAllScenceM2Country(sceneId,"����ս����ʼ�ˣ�",nCountryID , CHAT_RIGHTDOWN,1)      
		LuaAllScenceM2Country(sceneId,"����ս����ʼ�ˣ�",nCountryID , CHAT_LEFTDOWN, 1)      
		LuaAllScenceM2Country(sceneId,"����ս����ʼ�ˣ�",nCountryID , CHAT_MAIN_RIGHTDOWN, 1)
	end
end
