--�����NPC��
function x300715_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

		if  GetGuildOfficial(sceneId, selfId) ~= 5 then--�ж��Ƿ�Ϊ����		
					return
		end
			
			AddQuestNumText(sceneId,300715,"����᡿�������",3,1)--���Ӱ�ťA

end

--�������ť������������ִ�д˽ű�
function x300715_ProcEventEntry( sceneId, selfId, targetId,state,index)	

	local x300715xinwu = 0
	
	local x300715jinka = 0
	
	local x300715banghuijingyan = 0
	
	local x300715Readme_5 = ""
	
	local x300715Readme_6 = ""
	
	local x300715Readme_7 = ""	

	if index == 1 then
	
			local GuildId = GetGuildID(sceneId, selfId)--��ð��ID
			
			local GuildLevel,GuildMemcount,GuildExp = GetGuildSimpleData(GuildId)--�õ��������ݣ��ȼ������������飩
							
					if GuildLevel == 1 then					
								x300715xinwu = 1
								x300715jinka = 5
								x300715banghuijingyan = 800								
								if HaveItem( sceneId,selfId,11990001) < 1 then--�ж��Ƿ��а���������ɹ�,���ش���0,���ʧ��,����-1
									x300715Readme_5 = "  #R������"..x300715xinwu.."������#r#W"
								else
									x300715Readme_5 = "  #G������"..x300715xinwu.."������#r"
								end								
								if GetMoney(sceneId, selfId, 0) < 5000 then--�ж����ϵ�Ǯ
									x300715Readme_6 = "  #R����    ��"..x300715jinka.."����#r#W"
								else
									x300715Readme_6 = "  #G����    ��"..x300715jinka.."����#r"
								end								
								if GuildExp < 800 then--�жϰ�ᾭ��
									x300715Readme_7 = "  #R��ᾭ�飺"..x300715banghuijingyan.."�㡣#r#W"
								else
									x300715Readme_7 = "  #G��ᾭ�飺"..x300715banghuijingyan.."�㡣#r"
								end						
					elseif GuildLevel == 2 then					
								x300715xinwu = 2
								x300715jinka = 10
								x300715banghuijingyan = 4000								
								if HaveItem( sceneId,selfId,11990001) < 2 then--�ж��Ƿ��а���������ɹ�,���ش���0,���ʧ��,����-1
									x300715Readme_5 = "  #R������"..x300715xinwu.."������#r#W"
								else
									x300715Readme_5 = "  #G������"..x300715xinwu.."������#r"
								end								
								if GetMoney(sceneId, selfId, 0) < 10000 then--�ж����ϵ�Ǯ
									x300715Readme_6 = "  #R����    ��"..x300715jinka.."����#r#W"
								else
									x300715Readme_6 = "  #G����    ��"..x300715jinka.."����#r"
								end								
								if GuildExp < 4000 then--�жϰ�ᾭ��
									x300715Readme_7 = "  #R��ᾭ�飺"..x300715banghuijingyan.."�㡣#r#W"
								else
									x300715Readme_7 = "  #G��ᾭ�飺"..x300715banghuijingyan.."�㡣#r"
								end								
					elseif GuildLevel == 3 then					
								x300715xinwu = 3
								x300715jinka = 25
								x300715banghuijingyan = 12000								
								if HaveItem( sceneId,selfId,11990001) < 3 then--�ж��Ƿ��а���������ɹ�,���ش���0,���ʧ��,����-1
									x300715Readme_5 = "  #R������"..x300715xinwu.."������#r#W"
								else
									x300715Readme_5 = "  #G������"..x300715xinwu.."������#r"
								end								
								if GetMoney(sceneId, selfId, 0) < 25000 then--�ж����ϵ�Ǯ
									x300715Readme_6 = "  #R����    ��"..x300715jinka.."����#r#W"
								else
									x300715Readme_6 = "  #G����    ��"..x300715jinka.."����#r"
								end								
								if GuildExp < 12000 then--�жϰ�ᾭ��
									x300715Readme_7 = "  #R��ᾭ�飺"..x300715banghuijingyan.."�㡣#r#W"
								else
									x300715Readme_7 = "  #G��ᾭ�飺"..x300715banghuijingyan.."�㡣#r"
								end								
					elseif GuildLevel == 4 then					
								x300715xinwu = 4
								x300715jinka = 50
								x300715banghuijingyan = 40000							
								if HaveItem( sceneId,selfId,11990001) < 4 then--�ж��Ƿ��а���������ɹ�,���ش���0,���ʧ��,����-1
									x300715Readme_5 = "  #R������"..x300715xinwu.."������#r#W"
								else
									x300715Readme_5 = "  #G������"..x300715xinwu.."������#r"
								end								
								if GetMoney(sceneId, selfId, 0) < 50000 then--�ж����ϵ�Ǯ
									x300715Readme_6 = "  #R����    ��"..x300715jinka.."����#r#W"
								else
									x300715Readme_6 = "  #G����    ��"..x300715jinka.."����#r"
								end								
								if GuildExp < 40000 then--�жϰ�ᾭ��
									x300715Readme_7 = "  #R��ᾭ�飺"..x300715banghuijingyan.."�㡣#r#W"
								else
									x300715Readme_7 = "  #G��ᾭ�飺"..x300715banghuijingyan.."�㡣#r"
								end					
					elseif GuildLevel == 5 then					
								x300715xinwu = 5
								x300715jinka = 500
								x300715banghuijingyan = 96000							
								if HaveItem( sceneId,selfId,11990001) < 5 then--�ж��Ƿ��а���������ɹ�,���ش���0,���ʧ��,����-1
									x300715Readme_5 = "  #R������"..x300715xinwu.."������#r#W"
								else
									x300715Readme_5 = "  #G������"..x300715xinwu.."������#r"
								end								
								if GetMoney(sceneId, selfId, 0) < 500000 then--�ж����ϵ�Ǯ
									x300715Readme_6 = "  #R����    ��"..x300715jinka.."����#r#W"
								else
									x300715Readme_6 = "  #G����    ��"..x300715jinka.."����#r"
								end								
								if GuildExp < 96000 then--�жϰ�ᾭ��
									x300715Readme_7 = "  #R��ᾭ�飺"..x300715banghuijingyan.."�㡣#r#W"
								else
									x300715Readme_7 = "  #G��ᾭ�飺"..x300715banghuijingyan.."�㡣#r"
								end			
					elseif GuildLevel == 6 then					
								x300715xinwu = 6
								x300715jinka = 800
								x300715banghuijingyan = 192000							
								if HaveItem( sceneId,selfId,11990001) < 6 then--�ж��Ƿ��а���������ɹ�,���ش���0,���ʧ��,����-1
									x300715Readme_5 = "  #R������"..x300715xinwu.."������#r#W"
								else
									x300715Readme_5 = "  #G������"..x300715xinwu.."������#r"
								end								
								if GetMoney(sceneId, selfId, 0) < 800000 then--�ж����ϵ�Ǯ
									x300715Readme_6 = "  #R����    ��"..x300715jinka.."����#r#W"
								else
									x300715Readme_6 = "  #G����    ��"..x300715jinka.."����#r"
								end								
								if GuildExp < 192000 then--�жϰ�ᾭ��
									x300715Readme_7 = "  #R��ᾭ�飺"..x300715banghuijingyan.."�㡣#r#W"
								else
									x300715Readme_7 = "  #G��ᾭ�飺"..x300715banghuijingyan.."�㡣#r"
								end											
					elseif GuildLevel == 7 then					
								Msg2Player(sceneId,selfId,"���ȼ�Ŀǰֻ���ŵ�7����",8,2)
								Msg2Player(sceneId,selfId,"���ȼ�Ŀǰֻ���ŵ�7����",8,3)
						return						
					end
		
					
			local Readme_1 = "#Y����᡿���������#r"
			
			local Readme_2 = "#W�����ڰ��ĵ�ǰ�ȼ�Ϊ��#G"..GuildLevel.."#W ����#r"
			
			local Readme_3 = "�����ڰ��İ�ᾭ��Ϊ��#G"..GuildExp.."#W �㡣#r ".."#r"
			
			local Readme_4 = "��#G"..(GuildLevel+1).."�����#W��Ҫ����������#r #r"
			
			local Readme_8 = "#W ".."#r���Ƿ�Ҫ������᣿"
			
			local Readme = Readme_1..Readme_2..Readme_3..Readme_4..x300715Readme_5..x300715Readme_6..x300715Readme_7..Readme_8
						
			BeginQuestEvent(sceneId);AddQuestText( sceneId,Readme);EndQuestEvent(sceneId);DispatchQuestInfo(sceneId, selfId, targetId, 300715, -1)
			
	end
	
end


--�����ȷ����
function x300715_ProcAcceptCheck( sceneId, selfId, NPCId )

			local guildid = GetGuildID(sceneId, selfId)
	
			local GuildLevel,GuildMemcount,GuildExp = GetGuildSimpleData(guildid)--�õ��������ݣ��ȼ������������飩			
			
			if  GetGuildOfficial(sceneId, selfId) == 5 then--�ж��Ƿ�Ϊ����
						if GuildLevel == 1 then--�жϰ��ɵȼ�1-2
							if GetMoney(sceneId, selfId, 0) >= 5000 then--�ж����ϵ�Ǯ
									if HaveItem( sceneId,selfId,11990001) >= 1 then--�ж��Ƿ��а���������ɹ�,���ش���0,���ʧ��,����-1
											if GuildExp >= 800 then
													CostMoney(sceneId, selfId, 0,5000,304)--��Ǯ
													DelItem( sceneId,selfId,11990001,1 )--ɾ����
													SubGuildExp(sceneId,selfId, 800)--ɾ����ᾭ��
													GuildLevelup(sceneId, selfId)--���������
													Msg2Player(sceneId,selfId,"���⣡���⣡��������~",6)
													Msg2Player(sceneId,selfId,"���⣡���⣡��������~",8,2)
													Msg2Player(sceneId,selfId,"���⣡���⣡��������~",8,3)
											else
												Msg2Player(sceneId,selfId,"�ܱ�Ǹ����ᾭ�鲻�����޷�������ᣡ",8,2)
												Msg2Player(sceneId,selfId,"�ܱ�Ǹ����ᾭ�鲻�����޷�������ᣡ",8,3)
											end
									else
										Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������ﲻ�����޷�������ᣡ",8,2)
										Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������ﲻ�����޷�������ᣡ",8,3)
									end
							else
								Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������ϵ������������޷�������ᣡ",8,2)
								Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������ϵ������������޷�������ᣡ",8,3)
							end
					elseif GuildLevel == 2 then--2-3					
							if GetMoney(sceneId, selfId, 0) >= 10000 then--�ж����ϵ�Ǯ
									if HaveItem( sceneId,selfId,11990001) >= 2 then--�ж��Ƿ��а���������ɹ�,���ش���0,���ʧ��,����-1
											if GuildExp >= 4000 then
													
													CostMoney(sceneId, selfId, 0,10000,304)--��Ǯ
													DelItem( sceneId,selfId,11990001,2 )--ɾ����
													SubGuildExp(sceneId,selfId, 4000)--ɾ����ᾭ��
													GuildLevelup(sceneId, selfId)--���������	
													Msg2Player(sceneId,selfId,"���⣡���⣡��������~",6)
													Msg2Player(sceneId,selfId,"���⣡���⣡��������~",8,2)
													Msg2Player(sceneId,selfId,"���⣡���⣡��������~",8,3)
											else
												Msg2Player(sceneId,selfId,"�ܱ�Ǹ����ᾭ�鲻�����޷�������ᣡ",8,2)
												Msg2Player(sceneId,selfId,"�ܱ�Ǹ����ᾭ�鲻�����޷�������ᣡ",8,3)
											end
									else
										Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������ﲻ�����޷�������ᣡ",8,2)
										Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������ﲻ�����޷�������ᣡ",8,3)
									end
							else
								Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������ϵ������������޷�������ᣡ",8,2)
								Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������ϵ������������޷�������ᣡ",8,3)
							end
							
					elseif GuildLevel == 3 then--3-4
					
							if GetMoney(sceneId, selfId, 0) >= 25000 then--�ж����ϵ�Ǯ
									if HaveItem( sceneId,selfId,11990001) >= 3 then--�ж��Ƿ��а���������ɹ�,���ش���0,���ʧ��,����-1
											if GuildExp >= 12000 then
													
													CostMoney(sceneId, selfId, 0,25000,304)--��Ǯ
													DelItem( sceneId,selfId,11990001,3 )--ɾ����
													SubGuildExp(sceneId,selfId, 12000)--ɾ����ᾭ��
													GuildLevelup(sceneId, selfId)--���������	
													Msg2Player(sceneId,selfId,"���⣡���⣡��������~",6)
													Msg2Player(sceneId,selfId,"���⣡���⣡��������~",8,2)
													Msg2Player(sceneId,selfId,"���⣡���⣡��������~",8,3)
											else
												Msg2Player(sceneId,selfId,"�ܱ�Ǹ����ᾭ�鲻�����޷�������ᣡ",8,2)
												Msg2Player(sceneId,selfId,"�ܱ�Ǹ����ᾭ�鲻�����޷�������ᣡ",8,3)
											end
									else
										Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������ﲻ�����޷�������ᣡ",8,2)
										Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������ﲻ�����޷�������ᣡ",8,3)
									end
							else
								Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������ϵ������������޷�������ᣡ",8,2)
								Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������ϵ������������޷�������ᣡ",8,3)
							end
								
					elseif GuildLevel == 4 then--4-5
					
							if GetMoney(sceneId, selfId, 0) >= 50000 then--�ж����ϵ�Ǯ
									if HaveItem( sceneId,selfId,11990001) >= 4 then--�ж��Ƿ��а���������ɹ�,���ش���0,���ʧ��,����-1
											if GuildExp >= 40000 then
													
													CostMoney(sceneId, selfId, 0,50000,304)--��Ǯ
													DelItem( sceneId,selfId,11990001,4 )--ɾ����
													SubGuildExp(sceneId,selfId, 40000)--ɾ����ᾭ��
													GuildLevelup(sceneId, selfId)--���������	
													Msg2Player(sceneId,selfId,"���⣡���⣡��������~",6)
													Msg2Player(sceneId,selfId,"���⣡���⣡��������~",8,2)
													Msg2Player(sceneId,selfId,"���⣡���⣡��������~",8,3)
											else
												Msg2Player(sceneId,selfId,"�ܱ�Ǹ����ᾭ�鲻�����޷�������ᣡ",8,2)
												Msg2Player(sceneId,selfId,"�ܱ�Ǹ����ᾭ�鲻�����޷�������ᣡ",8,3)
											end
									else
										Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������ﲻ�����޷�������ᣡ",8,2)
										Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������ﲻ�����޷�������ᣡ",8,3)
									end
							else
								Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������ϵ������������޷�������ᣡ",8,2)
								Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������ϵ������������޷�������ᣡ",8,3)
							end				

					elseif GuildLevel == 5 then--5-6
					
							if GetMoney(sceneId, selfId, 0) >= 500000 then--�ж����ϵ�Ǯ
									if HaveItem( sceneId,selfId,11990001) >= 5 then--�ж��Ƿ��а���������ɹ�,���ش���0,���ʧ��,����-1
											if GuildExp >= 96000 then
													
													CostMoney(sceneId, selfId, 0,500000,304)--��Ǯ
													DelItem( sceneId,selfId,11990001,5 )--ɾ����
													SubGuildExp(sceneId,selfId, 96000)--ɾ����ᾭ��
													GuildLevelup(sceneId, selfId)--���������	
													Msg2Player(sceneId,selfId,"���⣡���⣡��������~",6)
													Msg2Player(sceneId,selfId,"���⣡���⣡��������~",8,2)
													Msg2Player(sceneId,selfId,"���⣡���⣡��������~",8,3)
											else
												Msg2Player(sceneId,selfId,"�ܱ�Ǹ����ᾭ�鲻�����޷�������ᣡ",8,2)
												Msg2Player(sceneId,selfId,"�ܱ�Ǹ����ᾭ�鲻�����޷�������ᣡ",8,3)
											end
									else
										Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������ﲻ�����޷�������ᣡ",8,2)
										Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������ﲻ�����޷�������ᣡ",8,3)
									end
							else
								Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������ϵ������������޷�������ᣡ",8,2)
								Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������ϵ������������޷�������ᣡ",8,3)
							end				

					elseif GuildLevel == 6 then--6-7
					
							if GetMoney(sceneId, selfId, 0) >= 800000 then--�ж����ϵ�Ǯ
									if HaveItem( sceneId,selfId,11990001) >= 6 then--�ж��Ƿ��а���������ɹ�,���ش���0,���ʧ��,����-1
											if GuildExp >= 192000 then
													
													CostMoney(sceneId, selfId, 0,800000,304)--��Ǯ
													DelItem( sceneId,selfId,11990001,6 )--ɾ����
													SubGuildExp(sceneId,selfId, 192000)--ɾ����ᾭ��
													GuildLevelup(sceneId, selfId)--���������	
													Msg2Player(sceneId,selfId,"���⣡���⣡��������~",6)
													Msg2Player(sceneId,selfId,"���⣡���⣡��������~",8,2)
													Msg2Player(sceneId,selfId,"���⣡���⣡��������~",8,3)
											else
												Msg2Player(sceneId,selfId,"�ܱ�Ǹ����ᾭ�鲻�����޷�������ᣡ",8,2)
												Msg2Player(sceneId,selfId,"�ܱ�Ǹ����ᾭ�鲻�����޷�������ᣡ",8,3)
											end
									else
										Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������ﲻ�����޷�������ᣡ",8,2)
										Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������ﲻ�����޷�������ᣡ",8,3)
									end
							else
								Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������ϵ������������޷�������ᣡ",8,2)
								Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������ϵ������������޷�������ᣡ",8,3)
							end				
					end
			else
				Msg2Player(sceneId,selfId,"�����ǰ�����",8,2)
				Msg2Player(sceneId,selfId,"�����ǰ�����",8,3)
			end
			
end

--**********************************
--����
--**********************************
function x300715_ProcAccept( sceneId, sceneId )

end

--**********************************
--����
--**********************************
function x300715_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x300715_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300715_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x300715_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x300715_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x300715_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x300715_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end


