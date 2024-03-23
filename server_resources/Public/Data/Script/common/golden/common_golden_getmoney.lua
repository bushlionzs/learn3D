
x800055_g_ScriptId = 800055
x800055_g_MissionName = "ȡ���ֽ�/����"

--�����NPC��
function x800055_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,800055,x800055_g_MissionName,0,-1)
	
end



--�������ť������������ִ�д˽ű�
function x800055_ProcEventEntry( sceneId, selfId, targetId,state,index )	

	--��GL����ȡ��
	WorldBankRetakMoney(sceneId, selfId)

end

--��ȡ���
function x800055_OnRetakeResult( sceneId, selfId, gold,goldNum,siller,sillerNum )
		
	if goldNum >0 then

		local text = "���Ѿ��ɹ���ȡ�˼��۷��ص�"..goldNum.."���ֽ��ܼ�#{_MONEY"..gold.."}�ֽ�"	
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)

		--�ʼ�֪ͨ
		local year,monty,day = GetYearMonthDay()
		local hour,min,sec	 = GetHourMinSec()

		local szMail = "����"..year.."��"..monty.."��"..day.."��"..hour.."��"
		if min < 10 then
			szMail = szMail.."0"..min.."�ɹ���ȡ�˼����˻ص�"..goldNum.."���ֽ��ܼ�#{_MONEY"..gold.."}�ֽ�"
		else
			szMail = szMail..min.."�ɹ���ȡ�˼����˻ص�"..goldNum.."���ֽ��ܼ�#{_MONEY"..gold.."}�ֽ�"
		end
		
		SendNormalMail( sceneId, selfId,GetName(sceneId, selfId),szMail )

	end

	if sillerNum >0 then

		local text = "�����۵�"..sillerNum.."���ֽ��ѳɹ��۳����ܼƻ������#{_MONEY"..siller.."}"	
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)

		--�ʼ�֪ͨ
		local year,monty,day = GetYearMonthDay()
		local hour,min,sec	 = GetHourMinSec()

		local szMail = "����"..year.."��"..monty.."��"..day.."��"..hour.."��"
		if min < 10 then
			szMail = szMail.."0"..min.."�ɹ���ȡ�����۳�"..sillerNum.."���ֽ��õ����棬�ܼ�#{_MONEY"..siller.."}����"
		else
			szMail = szMail..min.."�ɹ���ȡ�����۳�"..sillerNum.."���ֽ��õ����棬�ܼ�#{_MONEY"..siller.."}����"
		end

		SendNormalMail( sceneId, selfId,GetName(sceneId, selfId),szMail )

	end

	if goldNum<=0 and sillerNum<=0 then
	
		local text = "��û�����������˻ص��ֽ����ȡ��"	
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,text );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,text,8,2)

	end

	return 1

end


--�����ȷ����
function x800055_ProcAcceptCheck( sceneId, selfId, NPCId )
	
	return 1

end


--**********************************
--����
--**********************************
function x800055_ProcAccept( sceneId, selfId )

end


--**********************************
--����
--**********************************
function x800055_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x800055_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x800055_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x800055_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x800055_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x800055_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x800055_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end