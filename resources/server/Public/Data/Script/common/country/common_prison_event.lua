
--监狱BUFF对应的事件
function x300816_ProcEventEntry( sceneId, selfId, bufIndex,rorf )

	if rorf == 0 then --Active
		--
	else -- FadeOut
		SetPKValue(sceneId, selfId, 0)		
	end

end

