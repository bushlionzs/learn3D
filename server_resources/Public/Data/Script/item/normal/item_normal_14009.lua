--�ű���
x414009_g_scriptId = 414009 --��ʱд���,�����õ�ʱ��һ��Ҫ��.
x414009_g_keyID = 12100009 --��ʱд���,�����õ�ʱ��һ��Ҫ��.
x414009_g_keyname = "Կ�ף�9����" --��ʱд���,�����õ�ʱ��һ��Ҫ��.


--��Ҫ�ĵȼ�

--**********************************
--�¼��������
--**********************************
function x414009_ProcEventEntry( sceneId, selfId, bagIndex )
	local HaveKey = HaveItemInBag(sceneId,selfId,x414009_g_keyID)
	
	if HaveKey > 0 then
		OpenRndomBox ( sceneId, selfId, 1, 2, 5, 3, 5, 4, 5, 5, 3, 6, 2) 
		DelItem(sceneId,selfId,x414009_g_keyID,1)
		EraseItem(sceneId,selfId,bagIndex)
		BeginQuestEvent(sceneId)
			local strText = "#Y��ʹ��һ��"..x414009_g_keyname.."��������һ������"
			AddQuestText(sceneId,strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	else
		BeginQuestEvent(sceneId)
			local strText = "#Y�������䣬��Ҫ"..x414009_g_keyname.."һ��"
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
function x414009_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��
end
