--ע�⣺

--��Ʒ���ܵ��߼�ֻ��ʹ�û������ܺͽű���ʵ��

--�ű�:

--�����ǽű�����:


--3001.lua
------------------------------------------------------------------------------------------
--һ����Ʒ��Ĭ�Ͻű�

--�ű���
x417002_g_scriptId = 417002 --��ʱд���,�����õ�ʱ��һ��Ҫ��.

--Ч����ID
x417002_g_Impact1 = 8712 

--**********************************
--�¼��������
--**********************************
function x417002_ProcEventEntry( sceneId, selfId, bagIndex,rorf )
	if rorf == 1 then
		if sceneId == 0 then
				local x,z =GetWorldPos(sceneId,selfId)
				if x > 400 then
						local talkrandom =random(1,3)
						if talkrandom == 1 then
							NpcTalk(sceneId, selfId, "���к��������", -1)
						elseif talkrandom == 2 then
							NpcTalk(sceneId, selfId, "�Ҳ������㶼���ҵ�����һ����ˣ���ˣ�", -1)
						elseif talkrandom == 3 then
							NpcTalk(sceneId, selfId, "�㷢�����ˣ����������ˣ�", -1)
						end
				else
						local talkrandom =random(1,3)
						if talkrandom == 1 then
							NpcTalk(sceneId, selfId, "��лʩ����ȣ�", -1)
						elseif talkrandom == 2 then
							NpcTalk(sceneId, selfId, "���ʩ��������Щ���Ҿ�Ҫȥ�������ˣ�", -1)
						elseif talkrandom == 3 then
							NpcTalk(sceneId, selfId, "�����ӷ𣡶�лʩ����", -1)
						end
				end
		elseif sceneId == 56 or sceneId == 156 or sceneId == 256 or sceneId == 356 then
						local talkrandom =random(1,3)
						if talkrandom == 1 then
							NpcTalk(sceneId, selfId, "�Ҹոջ����룬������Ӵ򿪣����ֵ�һ����ͷ����ô�죡", -1)
						elseif talkrandom == 2 then
							NpcTalk(sceneId, selfId, "�һ���Ϊ��������ˣ���л��ʿ��", -1)
						elseif talkrandom == 3 then
							NpcTalk(sceneId, selfId, "��Ȼ������û˵����һ���ܻ80�꣡", -1)
						end
		elseif sceneId == 64 or sceneId == 164 or sceneId == 264 or sceneId == 364 then
						local talkrandom =random(1,3)
						if talkrandom == 1 then
							NpcTalk(sceneId, selfId, "���������Ӧ����ô�ӳ�ȥ�أ�", -1)
						elseif talkrandom == 2 then
							NpcTalk(sceneId, selfId, "���ڴ�����ʲô�������������������˲ҽ�����", -1)
						elseif talkrandom == 3 then
							NpcTalk(sceneId, selfId, "û�뵽���ܻ��ų�����ӣ�лл�㣡", -1)
						end
		elseif sceneId == 67 or sceneId == 167 or sceneId == 267 or sceneId == 367 then
						local talkrandom =random(1,2)
						if talkrandom == 1 then
							NpcTalk(sceneId, selfId, "��л������ȣ�������˵���ܻ80����Ȼ������", -1)
						elseif talkrandom == 2 then
							NpcTalk(sceneId, selfId, "лл������ң��һ���Ϊ�����ˡ�", -1)
						end
							
		end
	end
end

