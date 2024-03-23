
x310351_g_ScriptId = 310351
x310351_g_MissionName = "��ͨǮׯ�ʻ�"

--�����NPC��
function x310351_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x310351_g_ScriptId,x310351_g_MissionName,3,-1)
	
end



--�������ť������������ִ�д˽ű�
function x310351_ProcEventEntry( sceneId, selfId, targetId,state,index )	
		
	if index == -1 then
	
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y��ͨǮׯ�ʻ�#W\n\t35��������ҿ��ڴ˿�ͨǮׯ�ʻ�,��ͨ��Ҫ����#G1#W��������\n\t��ȷ��Ҫ��ͨǮׯ�ʻ���")
		EndQuestEvent(sceneId)	
		AddQuestNumText(sceneId,x310351_g_ScriptId,"��ͨǮׯ�ʻ�",3,1)
		DispatchQuestEventList(sceneId, selfId, targetId);
		
	elseif index == 1 then
					
		if GetMoney(sceneId, selfId,0) < GetStockRegisterCharge() then
		
			local text = "\t���ź�������������㣬��ͨǮׯ�ʻ���Ҫ����#R#{_MONEY"..GetStockRegisterCharge().."}#W������"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,text );
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId, selfId, targetId);		
			return
			
		end
	
		if GetMergeDBToggle() == 1 then
		local text = "\tĿǰ���������������������������кϲ���׼��������Ǯׯϵͳ��ʱ�رգ��������ϲ���ɺ󼴻Ὺ�š�"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId);
		return 	
	end
	
	if GetUpdateDBBeforeToggle() == 1 then
		local text = "\tĿǰ�����������ڽ������ݿ�������׼��������Ǯׯϵͳ��ʱ�رգ����ݿ�������ɺ󼴻Ὺ�š�"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId);
		return 	
	end
		
	if IsEnableStockAccount(sceneId, selfId) == 1 then
		local text = "\t���Ѿ���ͨ��Ǯׯ�ʻ��ˣ�"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId);
		return
	end
	
	--�ȼ��ж�
	if GetLevel(sceneId, selfId) < 35 then
	
		local text = "\tֻ��35�����ϵ���Ҳ��ܿ�ͨǮׯ�ʻ���"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId);		
		return
		
	end
		
	if GetMoney(sceneId, selfId,0) < GetStockRegisterCharge() then
	
		local text = "\t���ź�������������㣬��ͨǮׯ�ʻ���Ҫ����#R#{_MONEY"..GetStockRegisterCharge().."}#W����#B��"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId);		
		return
		
	end
	
		RegisterStockAccount( sceneId, selfId )

		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"\t��ϲ���ɹ���ͨǮׯ�ʻ��������Խ���Ǯׯ���н����ˡ�\n\t��ע�⣺�������ʻ�����#G30��#Wû�н����κν��ײ���������ϵͳ�Զ�ɾ�����ʻ����ʽ�ֱ�ӷ��������ı����У���ǵü�ʱ���н���Ŷ��")
		EndQuestEvent(sceneId)	
		DispatchQuestEventList(sceneId, selfId, targetId);
		
	end
		
end


--�ж��ܷ�ͨ
function x310351_OnIsCanRegister( sceneId, selfId )

	if GetMergeDBToggle() == 1 then
		local text = "\tĿǰ���������������������������кϲ���׼��������Ǯׯϵͳ��ʱ�رգ��������ϲ���ɺ󼴻Ὺ�š�"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
	end
	
	if GetUpdateDBBeforeToggle() == 1 then
		local text = "\tĿǰ�����������ڽ������ݿ�������׼��������Ǯׯϵͳ��ʱ�رգ����ݿ�������ɺ󼴻Ὺ�š�"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
	end
	
	if IsEnableStockAccount(sceneId, selfId) == 1 then
		local text = "\t���Ѿ���ͨ��Ǯׯ�ʻ��ˣ�"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 0
	end
	
	return 1

end


--��ͨ���
function x310351_OnRegisterResult( sceneId, selfId,result )
	
	if result == 0 then			--��ͨʧ��
		
		local text = "\t��ͨʧ�ܣ����Ժ�����"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)

	elseif result == 1 then		--��ͨ�ɹ�
		
		local text = "\t��ϲ���ɹ���ͨǮׯ�ʻ���"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		
	end

end



