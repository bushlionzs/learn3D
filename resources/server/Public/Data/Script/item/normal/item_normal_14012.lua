--�ű���
x414012_g_scriptId = 414012 --��ʱд���,�����õ�ʱ��һ��Ҫ��.
x414012_g_keyID = 12101001 --��ʱд���,�����õ�ʱ��һ��Ҫ��.
x414012_g_keyname = "����Կ��" --��ʱд���,�����õ�ʱ��һ��Ҫ��.


--��Ҫ�ĵȼ�

--**********************************
--�¼��������
--**********************************
function x414012_ProcEventEntry( sceneId, selfId, bagIndex )
	local HaveKey = HaveItemInBag(sceneId,selfId,x414012_g_keyID)
	
	if HaveKey > 0 then
		OpenRndomBox ( sceneId, selfId, 13, 13, 5, 13, 5, 13, 5, 13, 3, 13, 2) 
		DelItem(sceneId,selfId,x414012_g_keyID,1)
		EraseItem(sceneId,selfId,bagIndex)
		BeginQuestEvent(sceneId)
			local strText = "#Y��ʹ��һ��"..x414012_g_keyname.."��������һ������"
			AddQuestText(sceneId,strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	else
		BeginQuestEvent(sceneId)
			local strText = "#Y�������䣬��Ҫ"..x414012_g_keyname.."һ��"
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
function x414012_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��
end
