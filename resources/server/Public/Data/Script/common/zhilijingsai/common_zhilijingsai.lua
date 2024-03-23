x300150_g_scriptId = 300150
x300150_g_Impact1	= 9825

--����״̬
x300150_g_METAIL_GAME_INVALID = -1
x300150_g_METAIL_GAME_STARTING = 0
x300150_g_METAIL_GAME_STARTED = 1
x300150_g_METAIL_GAME_THINK = 2
x300150_g_METAIL_GAME_FINISH = 3

--�������
x300150_g_METAIL_GAME_ITEM_NUM = 3

--��������
x300150_g_TotalQuests = 20
x300150_g_ThinkTimeLen = 5000


--�����
function x300150_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4 )
	--print( "_ProcEventEntry")
	local sceneType = GetSceneType(sceneId);
	if sceneType ~= 0 then
		return
	end
	
	MentalGameAskRandSeed( sceneId, actId )
	
	SetMentalGameStatus( sceneId, x300150_g_METAIL_GAME_STARTING )

	SetSystemTimerTick( sceneId, x300150_g_scriptId, "ProcTiming", actId, 30*1000 ) --0.5���Ӻ�ʼ
end

--���Tick
function x300150_ProcTiming( sceneId, actId, uTime )
	
	--print( "_ProcTiming sceneId="..sceneId.." actid="..actId.." uTime="..uTime)

	local status = GetMentalGameStatus( sceneId )
	
	if status == x300150_g_METAIL_GAME_STARTING then
		--print("_ProcTiming_STARTING")
		-- 2���Ӻ󣬴����Զ���ʼ����
		SetMentalGameStatus( sceneId, x300150_g_METAIL_GAME_STARTED )
		
		SetSystemTimerTick( sceneId, x300150_g_scriptId, "ProcTiming", actId, 5000 ) --5���Ӻ���⣬��ʱ���ñ�����

	elseif status == x300150_g_METAIL_GAME_STARTED then
		--print("_ProcTiming_STARTED")
		local MentalGameCycle = GetMentalGameCycle( sceneId )
		if MentalGameCycle < x300150_g_TotalQuests then
		
			
			MentalGameBroadCastQuiz( sceneId, actId, MentalGameCycle, 0 ) --����
			
			SetSystemTimerTick( sceneId, x300150_g_scriptId, "ProcTiming", actId, x300150_g_ThinkTimeLen ) --3����˼��ʱ�䣬��ʱ�����ʹ�õ���

			SetMentalGameStatus( sceneId, x300150_g_METAIL_GAME_THINK )

			IncMentalGameCycle( sceneId )	--��������+1
			
			MentalGameAskNameList( sceneId, actId )	--�������а�
		elseif MentalGameCycle == x300150_g_TotalQuests then
			SetMentalGameStatus( sceneId, x300150_g_METAIL_GAME_STARTED )
			SetSystemTimerTick( sceneId, x300150_g_scriptId, "ProcTiming", actId, 5*1000 ) --���������ͣ��5����
			IncMentalGameCycle( sceneId )	--��������+1
			MentalGameAskNameList( sceneId, actId )	--�������а�
		else
			SetMentalGameStatus( sceneId, x300150_g_METAIL_GAME_FINISH )
			--print("		_ProcTiming_STARTED 1111111")
			MentalGameGiveAward( sceneId, actId )
			MentalGameFinished( sceneId,actId) --֪ͨ�ͻ����Ѿ����� 

		end
		
	elseif status == x300150_g_METAIL_GAME_THINK then
		--print("_ProcTiming_THINK")
		SetMentalGameStatus( sceneId, x300150_g_METAIL_GAME_STARTED )
	
		SetSystemTimerTick( sceneId, x300150_g_scriptId, "ProcTiming", actId, 11*1000 ) --10���Ӵ���ʱ�䣬��ʱ����Դ���

	elseif status == x300150_g_METAIL_GAME_FINISH then
	--print("_ProcTiming_FINISH")
	    MentalGameGiveAward( sceneId, actId )
		SetMentalGameStatus( sceneId, x300150_g_METAIL_GAME_INVALID )
		
	end
end

--��ʼ�
function x300150_StartGame( sceneId, actId )

	--print( "_StartGame")
--	Msg2Player(  sceneId, selfId,"Ҫ��ʾ����Ϣ" , MSG2PLAYER_PARA )

  --��ʼ������
	InitMentalGame( sceneId, actId )	--��ʼ������
	
	--������Ҵ���������
	SetAllPlayerRuntimeDataInScene( sceneId, RD_HUMAN_MENTALGAME, -1 )

	--����״̬Ϊ��ʼ��ing
	SetMentalGameStatus( sceneId, x300150_g_METAIL_GAME_STARTING )

	
	--��ͻ��˹㲥����
	BroadCastMentalGameStart(sceneId, actId)

end



--���ܺ���
--�����ɹ�
function x300150_OnSignUpSuccessed( sceneId, selfId, actId )
--	print( "_OnSignUpSuccessed\n")
	--����
	local status = GetMentalGameStatus( sceneId )
	--print( "_OnSignUpSuccessed"..status .." "..x300150_g_METAIL_GAME_STARTING)
	if status ~= x300150_g_METAIL_GAME_STARTING then
		return
	end
	
	local nSignUpIndex = SignUpMentalGame( sceneId, selfId, actId )
	if nSignUpIndex == -1 then
		return --����ʧ���ˣ���
	end
	
	--�����������
	SetPlayerRuntimeData(sceneId, selfId, RD_HUMAN_MENTALGAME, nSignUpIndex)
	
	--ȥ������״̬
	
	--���ӡ��������޵С�������״̬
	SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x300150_g_Impact1, 0);--9825  ���������
	
	--���������5���������
	InitMentalGame_Player( sceneId, selfId, x300150_g_METAIL_GAME_ITEM_NUM );
	--��¼��������
	GamePlayScriptLog( sceneId, selfId, 91)
	--֪ͨ�ͻ�����ʾ����
	ShowMentalGameInterface( sceneId, selfId, actId )
end

--���ܺ���
--ȡ������
function x300150_OnUnSignUp( sceneId, selfId, actId )
	--ȥ����ҡ��������޵С�������״̬
	CancelSpecificImpact(sceneId, selfId, x300150_g_Impact1);
end

function x300150_GiveAward( sceneId, selfId, score, sortid )

--	local exp = GetLevel(sceneId, selfId) * score * 2.25;
--	if sortid < 3 then
--		if sortid == 0 then
--			exp = exp * 2.5;
--		elseif sortid == 1 then
--			exp = exp * 2;
--		else
--			exp = exp * 1.5
--		end
--	end
--	AddExp(sceneId, selfId, exp);
--	local str = format("�ڱ��������������������%d����Ľ�����", exp);
--	hf_DisplayAwardInfo(sceneId, selfId, -1, -1, -1, 0, 0, exp, 0, 0);
	local gudingjiangli = ( GetLevel(sceneId, selfId) * 2000 ) /2;
	local fujiajiangli	= 0
	--( GetLevel(sceneId, selfId) * score * 10 ) /2;
		if score < 460 then
			fujiajiangli = ( GetLevel(sceneId, selfId) * score * 10 ) /2;
		else
			fujiajiangli = ( GetLevel(sceneId, selfId) * score * 10 )
		end	
	local paimingjiangli = gudingjiangli + fujiajiangli;
	local paimingtishi;
	if sortid < 3 then
		if sortid == 0 then
			paimingjiangli = paimingjiangli * 2;
--			paimingtishi = format("�ڱ��δ����У�%s����˵�һ����", GetName(sceneId, selfId));
--			--Msg2Player(sceneId, selfId, paimingtishi, 2, 4);
--			LuaAllScenceM2Wrold(sceneId, paimingtishi,4,1)
		elseif sortid == 1 then
			paimingjiangli = paimingjiangli * 1.5;
--			paimingtishi = format("�ڱ��δ����У�%s����˵ڶ�����", GetName(sceneId, selfId));
--			--Msg2Player(sceneId, selfId, paimingtishi, 2, 4);
--			LuaAllScenceM2Wrold(sceneId, paimingtishi,4,1)
		else
			paimingjiangli = paimingjiangli * 1.2
--			paimingtishi = format("�ڱ��δ����У�%s����˵�������", GetName(sceneId, selfId));
--			--Msg2Player(sceneId, selfId, paimingtishi, 2, 4);
--			LuaAllScenceM2Wrold(sceneId, paimingtishi,4, 1)
		end
	end
	AddExp(sceneId, selfId, paimingjiangli);
	--��¼�������
	GamePlayScriptLog( sceneId, selfId, 92)
	
	local str = "";
	if(sortid < 3) then
		if(fujiajiangli > 0) then
			str = format("#o�ڱ��������������������#r#R%d�㾭��#o�Ĺ̶�����,#r#R%d�㾭��#o�ĸ��ӽ���,#r�������ڱ��δ����л����#R��%d��#o,#r�������#R%d�㾭��#o���ܽ�����", gudingjiangli, fujiajiangli, sortid+1, paimingjiangli);
		else
			str = format("#o�ڱ��������������������#r#R%d�㾭��#o�Ĺ̶�����,#r�������ڱ��δ����л����#R��%d��#o,#r�������#R%d�㾭��#o���ܽ�����", gudingjiangli, sortid+1, paimingjiangli);
		end
	else
		if(fujiajiangli > 0) then
			str = format("#o�ڱ��������������������#r#R%d�㾭��#o�Ĺ̶�����,#r#R%d�㾭��#o�ĸ��ӽ���,#r�������#R%d�㾭��#o���ܽ�����", gudingjiangli, fujiajiangli, paimingjiangli);
		else
			str = format("#o�ڱ��������������������#r#R%d�㾭��#o�Ĺ̶�����,#r�������#R%d�㾭��#o���ܽ�����", gudingjiangli, paimingjiangli);
		end
		
	end
	Msg2Player(sceneId, selfId, str, 4, 2);
end