x888887_g_ScriptId = 888887
x888887_g_maillevel = {5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80}											

function x888887_leveluptest( sceneId, objId, level )
		for i, item in x888887_g_maillevel do 
		if level == x888887_g_maillevel[i] then
		local text=format("#{levelup_notice_%03d}",level)
		SendNormalMail(sceneId,objId,GetName(sceneId,objId),text)		
				if GetCurCountry(sceneId,objId) == 0 then--¥��
						if level == 20 then
							--Msg2Player(sceneId,objId,"��ϲ������"..level.."��,�����ڿ��Ե����ǵ�#aB{goto_50,270,100}���Է���ȡ��#aE����ȡ�߶���Էѣ�",4,2)
						elseif level == 30 then
							--Msg2Player(sceneId,objId,"��ϲ������"..level.."��,�����ڿ��Ե����ǵ�#aB{goto_50,270,100}���Է���ȡ��#aE����ȡ�߶���Էѣ�",4,2)
						elseif level == 40 then
							--Msg2Player(sceneId,objId,"��ϲ������"..level.."��,�����ڿ��Ե����ǵ�#aB{goto_50,270,100}���Է���ȡ��#aE����ȡ�߶���Էѣ�",4,2)
						elseif level == 50 then
							--Msg2Player(sceneId,objId,"��ϲ������"..level.."��,�����ڿ��Ե����ǵ�#aB{goto_50,270,100}���Է���ȡ��#aE����ȡ�߶���Էѣ�",4,2)
						elseif level == 60 then
							--Msg2Player(sceneId,objId,"��ϲ������"..level.."��,�����ڿ��Ե����ǵ�#aB{goto_50,270,100}���Է���ȡ��#aE����ȡ�߶���Էѣ�",4,2)
						end							
				elseif GetCurCountry(sceneId,objId) == 1 then--��ɽ					
						if level == 20 then
							--Msg2Player(sceneId,objId,"��ϲ������"..level.."��,�����ڿ��Ե����ǵ�#aB{goto_150,270,100}���Է���ȡ��#aE����ȡ�߶���Էѣ�",4,2)
						elseif level == 30 then
							--Msg2Player(sceneId,objId,"��ϲ������"..level.."��,�����ڿ��Ե����ǵ�#aB{goto_150,270,100}���Է���ȡ��#aE����ȡ�߶���Էѣ�",4,2)
						elseif level == 40 then
							--Msg2Player(sceneId,objId,"��ϲ������"..level.."��,�����ڿ��Ե����ǵ�#aB{goto_150,270,100}���Է���ȡ��#aE����ȡ�߶���Էѣ�",4,2)
						elseif level == 50 then
							--Msg2Player(sceneId,objId,"��ϲ������"..level.."��,�����ڿ��Ե����ǵ�#aB{goto_150,270,100}���Է���ȡ��#aE����ȡ�߶���Էѣ�",4,2)
						elseif level == 60 then
							--Msg2Player(sceneId,objId,"��ϲ������"..level.."��,�����ڿ��Ե����ǵ�#aB{goto_150,270,100}���Է���ȡ��#aE����ȡ�߶���Էѣ�",4,2)
						end						
				elseif GetCurCountry(sceneId,objId) == 2 then--����					
						if level == 20 then
							--Msg2Player(sceneId,objId,"��ϲ������"..level.."��,�����ڿ��Ե����ǵ�#aB{goto_250,270,100}���Է���ȡ��#aE����ȡ�߶���Էѣ�",4,2)
						elseif level == 30 then
							--Msg2Player(sceneId,objId,"��ϲ������"..level.."��,�����ڿ��Ե����ǵ�#aB{goto_250,270,100}���Է���ȡ��#aE����ȡ�߶���Էѣ�",4,2)
						elseif level == 40 then
							--Msg2Player(sceneId,objId,"��ϲ������"..level.."��,�����ڿ��Ե����ǵ�#aB{goto_250,270,100}���Է���ȡ��#aE����ȡ�߶���Էѣ�",4,2)
						elseif level == 50 then
							--Msg2Player(sceneId,objId,"��ϲ������"..level.."��,�����ڿ��Ե����ǵ�#aB{goto_250,270,100}���Է���ȡ��#aE����ȡ�߶���Էѣ�",4,2)
						elseif level == 60 then
							--Msg2Player(sceneId,objId,"��ϲ������"..level.."��,�����ڿ��Ե����ǵ�#aB{goto_250,270,100}���Է���ȡ��#aE����ȡ�߶���Էѣ�",4,2)
						end						
				elseif GetCurCountry(sceneId,objId) == 3 then--�ػ�
						if level == 20 then
							--Msg2Player(sceneId,objId,"��ϲ������"..level.."��,�����ڿ��Ե����ǵ�#aB{goto_350,270,100}���Է���ȡ��#aE����ȡ�߶���Էѣ�",4,2)
						elseif level == 30 then
							--Msg2Player(sceneId,objId,"��ϲ������"..level.."��,�����ڿ��Ե����ǵ�#aB{goto_350,270,100}���Է���ȡ��#aE����ȡ�߶���Էѣ�",4,2)
						elseif level == 40 then
							--Msg2Player(sceneId,objId,"��ϲ������"..level.."��,�����ڿ��Ե����ǵ�#aB{goto_350,270,100}���Է���ȡ��#aE����ȡ�߶���Էѣ�",4,2)
						elseif level == 50 then
							--Msg2Player(sceneId,objId,"��ϲ������"..level.."��,�����ڿ��Ե����ǵ�#aB{goto_350,270,100}���Է���ȡ��#aE����ȡ�߶���Էѣ�",4,2)
						elseif level == 60 then
							--Msg2Player(sceneId,objId,"��ϲ������"..level.."��,�����ڿ��Ե����ǵ�#aB{goto_350,270,100}���Է���ȡ��#aE����ȡ�߶���Էѣ�",4,2)
						end						
				end		
		end
		end	
end


function x888887_firstintest( sceneId, objId)
			
		local text=format("#{levelup_notice_000}")
		if text == "" then
			return
		end
		SendNormalMail(sceneId,objId,GetName(sceneId,objId),text)
			
end
