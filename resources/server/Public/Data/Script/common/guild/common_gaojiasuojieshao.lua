
x300747_g_ScriptId = 300747


--�����ı�����
x300747_g_MissionName="�߼���֮ս"


--MisDescEnd
--**********************************
--������ں���
--**********************************
function x300747_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�

			--�Ϸ�����
		    if GetMergeDBToggle() == 1 then
		        return
		    end
		    
		    --�������ݿ⿪��
				local UpdateDBflag = GetUpdateDBBeforeToggle()
				if UpdateDBflag==1 then
					return
				end
		    
		    --���Է�����
		    --if GetTestServerToggle() == 0 then
		    --    return
		    --end
		
		    --ս���Լ��Ŀ���
		    if GetBattleSceneToggle( BATTLESCENE_TYPE_GUILDBATTLE ) == 0 then
		        return
		    end

			BeginQuestEvent(sceneId);
		
			local localexp = (GetLevel( sceneId, selfId )) * 1000*0.3*5		
		
			local Readme_1 = "#Y�����ս����#W#r"
		
			local Readme_2 = "#Gһ����ս������#W#r"
			
			local Readme_3 = "��������ÿ�ܶ��������17��00-18��30֮�䱨����ϵͳ����20��00�Զ�������ս��#r"
			
			local Readme_4 = "#G����ʤ���ж���#W#r"
			
			local Readme_5 = "  1���涨ʱ���ڣ��������ȴﵽ100�ֵ�һ����ʤ��#r"
			
			local Readme_6 = "  2���ڹ涨ʱ����δ�ֳ�ʤ��������ָߵ�һ����ʤ��#r"

			local Readme_7 = "#G����ս������#W#r"	
			
			local Readme_8 = "  1��ս���е�4�����ֿ���ռ�죬ռ���ÿ�����ֽ�����һ����֡�#r"
			
			local Readme_9= "  2��ռ��ȫ��4�����ֽ�������ֵ�˫���������֡�#r"
			
			local Readme_10= "  3���ڶ�ȡ����ʱ����ʹ�ü��ܣ�ÿ�ύһ�μ�10�֡�#r"
			
			local Readme_11= "  4����������ڱ����ֿ⽻����Ҳ�����Ѿ�ռ���2���ٽ�����������һ��������"
			
			local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5..Readme_6..Readme_7..Readme_8..Readme_9..Readme_10..Readme_11
				
			AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId);DispatchQuestInfoNM( sceneId, selfId, targetId, -1, -1,2 );
	
	
end

--**********************************
--�о��¼�
--**********************************
function x300747_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

end


--********************
--����������
--**********************************
function x300747_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x300747_ProcAccept( sceneId, selfId )

	
end

--**********************************
--����
--**********************************
function x300747_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x300747_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300747_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x300747_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x300747_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x300747_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x300747_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
