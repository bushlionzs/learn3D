
x800054_g_ScriptId = 800054
x800054_g_MissionName = "�����ֽ�"

--�����NPC��
function x800054_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x800054_g_ScriptId,x800054_g_MissionName,0,-1)
	
end



--�������ť������������ִ�д˽ű�
function x800054_ProcEventEntry( sceneId, selfId, targetId,state,index )	

	if GetMergeDBToggle() == 1 then
		local text = "Ϊ��ϲ������ֽ������ʱ�رգ�������ɺ󼴿�����ʹ��"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	
	end
	
	if GetUpdateDBBeforeToggle() == 1 then
		local text = "Ϊ������ݿ��������ֽ������ʱ�رգ�������ɺ󼴿�����ʹ��"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	
	end
	
	if GetWorldGoldShopToggle() == 0 then
		local text = "�ֽ���۹����ѹر�"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	
	end
	
	--֪ͨ�ͻ��˵������۽���
	OpenWorldShopSell(sceneId, selfId,0)
	
end


--�ж��ܷ����
function x800054_OnIsCanSell( sceneId, selfId,shopId )
	
	if IsInLoginProtectTime(sceneId, selfId) == 1 then
		local text = "�㻹���ڰ�ȫ����ʱ���ڣ�������������"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
	end

	if GetMergeDBToggle() == 1 then
		local text = "Ϊ��ϲ������ֽ������ʱ�رգ�������ɺ󼴿�����ʹ��"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
	end
	
	if GetUpdateDBBeforeToggle() == 1 then
		local text = "Ϊ������ݿ��������ֽ������ʱ�رգ�������ɺ󼴿�����ʹ��"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
	end
	
	if GetWorldGoldShopToggle() == 0 then
		local text = "�ֽ���۹����ѹر�"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	
	end

	--�����̵�ID�õ����۵��ֽ��������
	local gold,charge,num = GetWorldShopConfigInfo(sceneId, selfId,shopId)
	local costGold = gold + charge

	if costGold <= 0 or gold <=0 or charge <=0 then
		--��Ӧ�ó��ֵ����
		return 0
	end
	
	if GetMoney(sceneId, selfId,2) < costGold then
		
		local text = "����ֽ���#{_MONEY"..costGold.."},���۲��ɹ�"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 0

	end

	return 1

end


--�����ϼܲ������
function x800054_OnSellResult( sceneId, selfId,shopId,price,result )
	
	if result == 0 then			--�̵���
		
		local text = "�����б������������һ��ʱ�����������ֽ�"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)

	elseif result == 1 then		--����ѳ�����������
		
		local gold,charge,num = GetWorldShopConfigInfo(sceneId, selfId,shopId)

		local text = "���Ѿ���"..num.."�ʼ��ۻ��ڵȴ��ɽ��У������ټ���"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		
	elseif result == 2 then		--���۳ɹ�

		local gold,charge,num = GetWorldShopConfigInfo(sceneId, selfId,shopId)

		local text = "ĳ�����ֽ����NPC��������#{_MONEY"..gold.."}�ֽ𣬱��Ϊ#{_MONEY"..price.."}��������Ҫ�����ѣ���ȥ�����ɣ�"
		LuaAllScenceM2Wrold(sceneId,text,2,1)
		
		--�ʼ�������
		local year,monty,day = GetYearMonthDay()
		local hour,min,sec	 = GetHourMinSec()

		local szMail = "����"..year.."��"..monty.."��"..day.."��"..hour.."��"
		if min < 10 then
			--���Ӳ���10��ǰ�油һ��0����ʾ��
			szMail = szMail.."0"..min.."������#{_MONEY"..gold.."}�ֽ𣬱��Ϊ#{_MONEY"..price.."}����"
		else
			szMail = szMail..min.."������#{_MONEY"..gold.."}�ֽ𣬱��Ϊ#{_MONEY"..price.."}����"
		end
		
		SendNormalMail( sceneId, selfId,GetName(sceneId, selfId),szMail )

	elseif result == 5 then		--������

		local text = "���������������һ��ʱ���������ۻ����ֽ�"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
	end

end

--�����ȷ����
function x800054_ProcAcceptCheck( sceneId, selfId, NPCId )
	
	return 1

end


--**********************************
--����
--**********************************
function x800054_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800054_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x800054_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x800054_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x800054_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x800054_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x800054_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x800054_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end