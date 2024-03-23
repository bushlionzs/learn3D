
x800053_g_ScriptId = 800053
x800053_g_MissionName = "�����ֽ�"

--�����NPC��
function x800053_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,800053,x800053_g_MissionName,0,-1)
	
end



--�������ť������������ִ�д˽ű�
function x800053_ProcEventEntry( sceneId, selfId, targetId,state,index )	

	--��GL�����ֽ��̵��б�
	GetWorldShopMerchandiseInfo(sceneId, selfId,0)
	
end


--�ж��ܷ����ֽ�
function x800053_OnIsCanBuy( sceneId, selfId,price )
	
	if IsInLoginProtectTime(sceneId, selfId) == 1 then
		local text = "�㻹���ڰ�ȫ����ʱ���ڣ�������������"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 	0
	end

	if GetMoney(sceneId, selfId,0) < price then
		
		local text = "�����������#{_MONEY"..price.."},���򲻳ɹ�"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)
		return 0

	end

	return 1

end


--�ֽ�����
function x800053_OnBuyResult( sceneId, selfId,shopId,price,result )
	
	if result == 3 then			--����ɹ�
		
		local gold,charge,num = GetWorldShopConfigInfo(sceneId, selfId,shopId)

		local text = "ĳ�����ֽ����NPC��������#{_MONEY"..price.."}������������#{_MONEY"..gold.."}�ֽ�"
		LuaAllScenceM2Wrold(sceneId,text,2,1)	

		--�ʼ�����
		local year,monty,day = GetYearMonthDay()
		local hour,min,sec	 = GetHourMinSec()

		local szMail = "����"..year.."��"..monty.."��"..day.."��"..hour.."��"
		if min < 10 then
			szMail = szMail.."0"..min.."������#{_MONEY"..price.."}������������#{_MONEY"..gold.."}�ֽ�"	
		else
			szMail = szMail..min.."������#{_MONEY"..price.."}������������#{_MONEY"..gold.."}�ֽ�"	
		end

		SendNormalMail( sceneId, selfId,GetName(sceneId, selfId),szMail )

	elseif result == 4 then		--����ʧ��
		
		local text = "�ý�Ʊ�ѷ����䶯�����򲻳ɹ���������ѡ��"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)

		--���������ֽ��̵��б�
		GetWorldShopMerchandiseInfo(sceneId, selfId,shopId)

	elseif result == 5 then		--������

		local text = "��������������ʧ��"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)	
	end

end

--�����ȷ����
function x800053_ProcAcceptCheck( sceneId, selfId, NPCId )
	
	return 1

end


--**********************************
--����
--**********************************
function x800053_ProcAccept( sceneId, selfId )
end

--**********************************
--����
--**********************************
function x800053_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x800053_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x800053_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x800053_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x800053_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x800053_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x800053_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end