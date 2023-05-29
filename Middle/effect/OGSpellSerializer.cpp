#include "OgreHeader.h"
#include "OGSpellSerializer.h"
#include "OGImpactManager.h"
#include "platform_log.h"
#include "OGSpell.h"
#include "OgreString.h"

namespace Orphigine
{
	String	SpellsSerializer::ms_currentVersion = "[SkillSerializer_v1.00]";
	bool SpellsSerializer::importSkillFromStream(Ogre::DataStreamPtr& stream,SkillCollection* sc,bool isLoadOnDamand)
	{
		determineEndianness(stream);
		// Check header
		readFileHeader(stream);
		//WARNING_LOG("Importing Skills..",Ogre::LML_TRIVIAL);
		unsigned short streamID;
		while(!stream->eof())
		{
			streamID = readChunk(stream);
			switch (streamID)
			{
			case SKILL_EDITOR_SEGMENT:
				{
					String editorSegment = this->readString(stream);
					unsigned int segmentLen = (unsigned int)editorSegment.length();
					unsigned int copyrightLen = (unsigned int)mCopyRight.length();

					if(segmentLen >= copyrightLen)
						editorSegment = editorSegment.substr(copyrightLen,segmentLen - copyrightLen);
					if(sc)
						sc->m_editorSegment = editorSegment;
					break;
				}
			case SKILL_SINGLE_SKILL:
				{
					String skillName = this->readString(stream);

					Spell* skill = ImpactManager::getSingleton().getSkillTemplate(skillName);
					if (!skill)
					{
						skill = ImpactManager::getSingleton().createSkillTemplate(skillName);
						if(sc)
							sc->m_skillMap[skillName] = skill;
						skill->loadBinary(this,stream);
					}
					else
					{
						
						if (isLoadOnDamand)
						{
							skill->clear();
							skill->loadBinary(this,stream);
						} 
						else
						{
							long skipOffset = skill->calcSerializedSize() //mCurrentstreamLen
								- STREAM_OVERHEAD_SIZE - skillName.length() - 1;
							stream->skip(skipOffset);
						}
						if(sc)
							sc->m_skillMap[skillName] = skill;
					}
					break;
				}
			}
		}
		//WARNING_LOG("Skills imported.",Ogre::LML_TRIVIAL);
		return true;
	}
	bool SpellsSerializer::importSkillFromStream1(Ogre::DataStreamPtr& stream,SkillCollection* sc)
	{
		determineEndianness(stream);
		readFileHeader(stream);
		//WARNING_LOG("Importing Skills..",Ogre::LML_TRIVIAL);
		unsigned short streamID;
		while(!stream->eof())
		{
			streamID = readChunk(stream);
			switch (streamID)
			{
			case SKILL_EDITOR_SEGMENT:
				{
					String editorSegment = this->readString(stream);
					unsigned int segmentLen = (unsigned int)editorSegment.length();
					unsigned int copyrightLen = (unsigned int)mCopyRight.length();
					if(segmentLen >= copyrightLen)
						editorSegment = editorSegment.substr(copyrightLen,segmentLen - copyrightLen);
					if(sc)
						sc->m_editorSegment = editorSegment;
					break;
				}
			case SKILL_SINGLE_SKILL:
				{
					String skillName = this->readString(stream);
					String lowerskillName = skillName;
					Ogre::StringUtil::toLowerCase(lowerskillName);
					if(sc)
					{
						std::map<String,Spell*>::iterator itSkill = sc->m_skillMap.find(lowerskillName);
						if(itSkill != sc->m_skillMap.end() && itSkill->second)
						{
							itSkill->second->loadBinary(this,stream);
						}
						else
						{
							//因为不读取，所以直接跳过相应数据段长
							long skipOffset = mCurrentstreamLen - STREAM_OVERHEAD_SIZE - skillName.length() - 1;
							stream->skip(skipOffset);
						}						
					}
					break;
				}
			}
		}
		//WARNING_LOG("Skills imported.",Ogre::LML_TRIVIAL);
		return true;
	}
	bool SpellsSerializer::getSkillInfoFromStream(Ogre::DataStreamPtr& stream,SkillInfoStr& skillInfo)
	{
		skillInfo.skillNum=0;
		skillInfo.skillName.clear();
		size_t startPos = stream->tell();
		determineEndianness(stream);
		// Check header
		readFileHeader(stream);
		unsigned short streamID;
		while(!stream->eof())
		{
			streamID = readChunk(stream);
			switch (streamID)
			{
			case SKILL_EDITOR_SEGMENT:
				{
					String editorSegment = this->readString(stream);
					unsigned int segmentLen = (unsigned int)editorSegment.length();
					unsigned int copyrightLen = (unsigned int)mCopyRight.length();
					if(segmentLen >= copyrightLen)
						skillInfo.editorSegment = editorSegment.substr(copyrightLen,segmentLen - copyrightLen);
					break;
				}
			case SKILL_SINGLE_SKILL:
				{
					String skillName = this->readString(stream);
					String lowerskillName = skillName;
					Ogre::StringUtil::toLowerCase(lowerskillName);
					long skipOffset =  mCurrentstreamLen - STREAM_OVERHEAD_SIZE - skillName.length() - 1;
					++skillInfo.skillNum;
					skillInfo.skillName.push_back(lowerskillName);
					stream->skip(skipOffset);
					break;
				}
			}
		}
		//WARNING_LOG("Skills imported.",Ogre::LML_TRIVIAL);
		stream->seek(startPos);//恢复到起始位置
		return true;
	}

}