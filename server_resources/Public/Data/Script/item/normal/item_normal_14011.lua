--�ű���
x414011_g_scriptId = 414011 --��ʱд���,�����õ�ʱ��һ��Ҫ��.
x414011_g_keyID = 12101000 --��ʱд���,�����õ�ʱ��һ��Ҫ��.
x414011_g_keyname = "����Կ��" --��ʱд���,�����õ�ʱ��һ��Ҫ��.


--��Ҫ�ĵȼ�

--**********************************
--�¼��������
--**********************************
function x414011_ProcEventEntry( sceneId, selfId, bagIndex )
	local HaveKey = HaveItemInBag(sceneId,selfId,x414011_g_keyID)
	
	if HaveKey > 0 then
		OpenRndomBox ( sceneId, selfId, 11, 11, 5, 11, 5, 11, 5, 11, 3, 11, 2) 
		DelItem(sceneId,selfId,x414011_g_keyID,1)
		EraseItem(sceneId,selfId,bagIndex)
		BeginQuestEvent(sceneId)
			local strText = "#Y��ʹ��һ��"..x414011_g_keyname.."��������һ������"
			AddQuestText(sceneId,strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	else
		BeginQuestEvent(sceneId)
			local strText = "#Y�������䣬��Ҫ"..x414011_g_keyname.."һ��"
			AddQuestText(sceneId,strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	end
end

--**********************************
--�����Ʒ��ʹ�ù����Ƿ������ڼ��ܣ�
--ϵͳ����ִ�п�ʼʱ�����������ķ���ֵ���������ʧ������Ժ�������Ƽ��ܵ�ִ�С�
--����1���������Ƶ���Ʒ�����Լ������Ƽ��ܵ�ִ�У�����0�����Ժ���Ĳ�����
--**********************************
function x414011_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��
end
