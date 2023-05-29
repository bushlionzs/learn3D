#include "OgreHeader.h"
#include "OGModelComponent.h"
#include "OGModelComponentSerializer.h"
#include "OGFlags.h"

//#include <OgreUTFString.h>
#include <platform_log.h>
#include <OgreEntity.h>
#include <OgreTagPoint.h>
#include <OgreSceneNode.h>
#include <OgreSkeletonInstance.h>
#include "lexical_cast_util.h"
#include "tinyxml/tinyxml.h"


namespace Orphigine
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const String ModelComponentSerializer::msCurrentVersion = "[ModelComponentSerializer_v1.00]";

static const String csModelComponentXmlVersion = "[ModelComponentSerializer_v0.01]";

ModelComponentSerializer::ModelComponentSerializer( )
{
	// Set up map
	mModelComponentSerializers.insert( ModelComponentSerializerImplMap::value_type( msCurrentVersion, new ModelComponentSerializerImpl( ) ) );
	mModelComponentSerializers.insert( ModelComponentSerializerImplMap::value_type( csModelComponentXmlVersion, new ModelComponentSerializerImpl_v0_0_1( ) ) );
}

ModelComponentSerializer::~ModelComponentSerializer( )
{
	// delete map
	for ( ModelComponentSerializerImplMap::iterator i = mModelComponentSerializers.begin(); i != mModelComponentSerializers.end( ); ++i )
	{
		delete i->second;
	}
	mModelComponentSerializers.clear( );
}

void ModelComponentSerializer::exportModelComponent( const ModelComponent& modelComponent, const String& fileName, Endian endianMode )
{
	ModelComponentSerializerImplMap::iterator impl = mModelComponentSerializers.find( msCurrentVersion );
	if ( impl == mModelComponentSerializers.end( ) )
	{
		OGRE_EXCEPT( Ogre::Exception::ERR_INTERNAL_ERROR, "Cannot find serializer implementation for "
			"current version " + msCurrentVersion, "ModelComponentSerializer::exportModelComponent" );
	}

	impl->second->exportModelComponent( modelComponent, fileName, endianMode );
}

void ModelComponentSerializer::importModelComponent( DataStreamPtr& stream, ModelComponent& modelComponent )
{
	//determineEndianness( stream );

	// Read header and determine the version
	unsigned short headerID;

	// Read header ID
	readShorts( stream, &headerID, 1 );

	ModelComponentSerializerImplMap::iterator impl;
	String ver = csModelComponentXmlVersion;

	if ( headerID != HEADER_STREAM_ID )
	{
		impl = mModelComponentSerializers.find( csModelComponentXmlVersion );

		if ( impl == mModelComponentSerializers.end( ) )
		{
			OGRE_EXCEPT( Exception::ERR_INTERNAL_ERROR, "File header not found", "ModelComponentSerializer::importModelComponent" );
		}
	}
	else
	{
		// Read version
		ver = readStringBin( stream );

		// Find the implementation to use
		impl = mModelComponentSerializers.find( ver );
	
		if ( impl == mModelComponentSerializers.end( ) )
		{
			OGRE_EXCEPT( Exception::ERR_INTERNAL_ERROR, "Cannot find serializer implementation for "
				"current version " + ver, "ModelComponentSerializer::importModelComponent" );
		}
	}

	// Jump back to start
	stream->seek( 0 );

	// Call implementation
	impl->second->importModelComponent( stream, modelComponent );

	// Warn on old version of mesh
	if ( ver != msCurrentVersion )
	{
		//WARNING_LOG("ModelComponent %s is an older format, should upgrade it", stream->getName().c_str());
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum ModelComponentChunkID
{
	MC_MODEL = 0x1000,
	MC_FRAME = 0x0100,
	MC_ENTITY = 0x0200,
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ModelComponentSerializerImpl::ModelComponentSerializerImpl( )
{
	mFileType = "MODB";	
	mVersion = ModelComponentSerializer::msCurrentVersion;
}

ModelComponentSerializerImpl::~ModelComponentSerializerImpl( )
{
}

void ModelComponentSerializerImpl::exportModelComponent( const ModelComponent& modelComponent, const String& filename, Endian endianMode )
{	
	
}

void ModelComponentSerializerImpl::writeModelComponent( const ModelComponent& modelComponent )
{
	
}

void ModelComponentSerializerImpl::writeMasterEntity( const ModelComponent& modelComponent, const Entity* pEntity )
{
	
}

void ModelComponentSerializerImpl::writeEntity( const ModelComponent& modelComponent, const Entity& entity, const Entity* pMasterEntity )
{
	
}

void ModelComponentSerializerImpl::importModelComponent( DataStreamPtr& stream, ModelComponent& modelComponent )
{	
	mFileName = stream->getName( );
	// LogManager::getSingleton( ).logMessage( "ModelComponentSerializer import data...", LML_TRIVIAL );
	determineEndianness( stream );

	uint16 headerID = 0;
	readShorts( stream, &headerID, 1 );
	if ( headerID == HEADER_STREAM_ID )
	{
		String version = readStringBin( stream );
		if ( version != mVersion )
		{
			OGRE_EXCEPT( Exception::ERR_INTERNAL_ERROR, "Invalid file: version incompatible, file reports " + version + 
				" Serializer is version " + mVersion, "ModelComponentSerializerImpl::importModelComponent" );
		}
	}
	else
	{
		OGRE_EXCEPT( Exception::ERR_INTERNAL_ERROR, "Invalid file: no header", "ModelComponentSerializerImpl::readFileHeader" );
	}

	String FileType = readStringBin( stream );
    String CopyRight = readStringBin( stream );

	if ( FileType != mFileType )
	{
		OGRE_EXCEPT( Exception::ERR_INTERNAL_ERROR, "Invalid file: type incompatible, file reports " + String( FileType ) + 
			" Serializer is type " + mFileType, "ModelComponentSerializerImpl::importModelComponent" );
	}

	readModelComponent( stream, modelComponent );
	// LogManager::getSingleton( ).logMessage( "ModelComponentSerializer import successful.", LML_TRIVIAL );
}

void ModelComponentSerializerImpl::readModelComponent( DataStreamPtr& stream, ModelComponent& modelComponent )
{
	uint16 chunkId = readChunk( stream );
	if( chunkId != MC_MODEL )
	{
		WARNING_LOG("Load ModelComponent From Stream Failed. ChunkId Error");
		skipChunk( stream );
		return;
	}

	while( !stream->eof( ) )
	{
		readShorts( stream, &chunkId, 1 );
		switch ( chunkId )
		{
		case MC_FRAME:
			readMasterEntity( stream, modelComponent );
			break;
		case MC_ENTITY:
			readEntity( stream, modelComponent  );
			break;
		}
	}
}

void ModelComponentSerializerImpl::readMasterEntity( DataStreamPtr& stream, ModelComponent& modelComponent )
{
	String mSkeletonName = readStringBin( stream );
	Entity* pMasterEntity = modelComponent.createMasterMovableObject( mSkeletonName );

	uint16 chunkId;
	readShorts( stream, &chunkId, 1 );

	while ( !stream->eof( ) && chunkId == MC_ENTITY )
	{
		readEntity( stream, modelComponent, pMasterEntity );
		readShorts( stream, &chunkId, 1 );
	}
}

void ModelComponentSerializerImpl::readEntity( DataStreamPtr& stream, ModelComponent& modelComponent, Entity* pMasterEntity )
{
	String meshName;
	String boneName;
	bool normalise;
	bool receiveDecals;
	bool hasBoneName;
	bool offset;

	Vector3 translate;
	Vector3 scale;
	Quaternion rotation;

	meshName = readStringBin( stream );
	readBools( stream, &normalise, 1 );
	readBools( stream, &receiveDecals, 1 );
	readBools( stream, &hasBoneName, 1 );
	boneName = readStringBin( stream );
	readBools( stream, &offset, 1 );

	readData( stream, &translate, 1, sizeof( Vector3 ) );
	readData( stream, &rotation, 1, sizeof( Quaternion ) );
	readData( stream, &scale, 1, sizeof( Vector3 ) );

	Entity* pEntity = modelComponent.createMovableObject( meshName, pMasterEntity );

	pEntity->setNormaliseNormals( normalise );

	if ( receiveDecals )
	{
		pEntity->addQueryFlags( OQF_DECAL_TARGET );
		if ( pMasterEntity )
			pMasterEntity->addQueryFlags( OQF_DECAL_TARGET );
	}

	Node* pNode = NULL;

	if (hasBoneName && pMasterEntity != NULL)
	{
		pNode = pMasterEntity->attachObjectToBone(boneName, pEntity);
	}
	else
	{
		modelComponent.getParent()->attachObject(pEntity);
	}
		

	if ( offset && pNode == NULL )
	{
		SceneNode* pSceneNode = pEntity->getParentSceneNode( );

		// Detach form parent and attach to new offset scene node
		SceneNode* attachNode = pSceneNode->createChildSceneNode(BLANKSTRING);
		modelComponent.getSceneNodes( ).push_back( attachNode );

		pSceneNode->detachObject( pEntity->getName( ) );
		attachNode->attachObject( pEntity );
		pNode = attachNode;
	}

	if ( pNode != NULL )
	{
		pNode->setPosition( translate );
		pNode->setOrientation( rotation );
		pNode->setScale( scale );

		pNode->setInitialState( );
	}
}

uint32 ModelComponentSerializerImpl::calcSize( const ModelComponent& modelComponent ) const
{
	size_t totalSize = Serializer::STREAM_OVERHEAD_SIZE;

	const ModelComponent::ObjectList& masterObjects = modelComponent.getMasterMovableObjects( );
	ModelComponent::ObjectList::const_iterator it = masterObjects.begin( );
	for ( ; it != masterObjects.end( ); ++it )
	{
		Entity* pMasterEntity = const_cast<Entity*>( static_cast<const Entity*>( *it ) );

		if ( pMasterEntity == NULL )
			continue;

		totalSize += calcMasterEntitySize( modelComponent, pMasterEntity );
	}

	totalSize += calcMasterEntitySize( modelComponent, NULL );

	return totalSize;
}

uint32 ModelComponentSerializerImpl::calcMasterEntitySize( const ModelComponent& modelComponent, const Entity* pEntity ) const
{
	return 0;
}

uint32 ModelComponentSerializerImpl::calcEntitySize( 
	const ModelComponent& modelComponent, 
	const Entity& entity, 
	const Entity* pMasterEntity ) const
{
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool __nocaseequal( const String&l, const char *r )
{
	return _stricmp( l.c_str(), r ) == 0;
}

struct ConvertBuffer
{
	std::vector<wchar_t> wideCharBuffer;
	std::vector<char> multiByteBuffer;
};

static const basic_string<char>& expat_to_local_win32( basic_string<char>& r, const basic_string<char>& s, ConvertBuffer& buffers )
{
#ifdef __DAMN_MICROSOFT__
	buffers.utfString.assign( s );

	const wstring& wstr = buffers.utfString.asWStr( );
	int cchWideChar = wstr.length( ) + 1;
	const wchar_t* pWideStr = wstr.c_str( );
#else
	int cchWideChar = MultiByteToWideChar( CP_UTF8, MB_ERR_INVALID_CHARS, s.c_str(), s.length() + 1, NULL, 0 );
	if ( cchWideChar <= 0 )
	{
		OGRE_EXCEPT( Exception::ERR_INVALIDPARAMS, "Can't convert UTF8 '" + s + "' to MBCS", "expat_to_local_win32" );
	}

	buffers.wideCharBuffer.resize( cchWideChar );
	int cchConvertedWideChar = MultiByteToWideChar( CP_UTF8, MB_ERR_INVALID_CHARS, s.c_str( ), s.length( ) + 1, &buffers.wideCharBuffer.front( ), cchWideChar );
	if ( cchConvertedWideChar != cchWideChar )
	{
		OGRE_EXCEPT( Exception::ERR_INVALIDPARAMS, "Can't convert UTF8 '" + s + "' to MBCS", "expat_to_local_win32" );
	}

	const wchar_t* pWideStr = &buffers.wideCharBuffer.front( );
#endif

	int cbMultiByte = WideCharToMultiByte( 936, 0, pWideStr, cchWideChar, NULL, 0, NULL, NULL );
	if ( cbMultiByte <= 0 )
	{
		OGRE_EXCEPT( Exception::ERR_INVALIDPARAMS, "Can't convert UTF8 '" + s + "' to MBCS", "expat_to_local_win32" );
	}

	buffers.multiByteBuffer.resize( cbMultiByte );
	int cchConvertedMultiByte = WideCharToMultiByte( 936, 0, pWideStr, cchWideChar, &buffers.multiByteBuffer.front(), cbMultiByte, NULL, NULL );
	if ( cchConvertedMultiByte != cbMultiByte )
	{
		OGRE_EXCEPT( Exception::ERR_INVALIDPARAMS, "Can't convert UTF8 '" + s + "' to MBCS", "expat_to_local_win32" );
	}

	return r.assign( &buffers.multiByteBuffer.front( ), cchConvertedMultiByte - 1 );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class XMLAttributes
{
public:
	XMLAttributes( );
	~XMLAttributes( );

	void remove( const String& name );
	void removeAll( );

	bool exists( const String& name ) const;
	size_t getCount( ) const;

	const String& getName( size_t index ) const;

	const String& getValue( size_t index ) const;
	const String& getValue( const String& name ) const;
	void setValue( const String& name, const String& value );

protected:
	typedef std::map<String, String> AttributeMap;
	AttributeMap mAttributes;
};

inline XMLAttributes::XMLAttributes( )
{
}

inline XMLAttributes::~XMLAttributes( )
{
}

inline void XMLAttributes::remove( const String& name )
{
	AttributeMap::iterator it = mAttributes.find( name );

	if ( it == mAttributes.end( ) )
	{
		OGRE_EXCEPT( Exception::ERR_ITEM_NOT_FOUND,
			"The specified attribute named '" + name + "' doesn't exists for this XMLAttributes block",
			"XMLAttributes::remove" );
	}

	mAttributes.erase( it );
}

inline void XMLAttributes::removeAll( )
{
	mAttributes.clear();
}

inline bool XMLAttributes::exists( const String& name ) const
{
	return mAttributes.find( name ) != mAttributes.end( );
}

inline size_t XMLAttributes::getCount( ) const
{
	return mAttributes.size( );
}

inline const String& XMLAttributes::getName( size_t index ) const
{
	if ( index >= mAttributes.size( ) )
	{
		OGRE_EXCEPT( Exception::ERR_ITEM_NOT_FOUND,
			"The specified index is out of range for this XMLAttributes block", "XMLAttributes::getName" );
	}

	AttributeMap::const_iterator it = mAttributes.begin( );
	std::advance( it, index );

	return it->first;
}

inline const String& XMLAttributes::getValue( size_t index ) const
{
	if ( index >= mAttributes.size( ) )
	{
		OGRE_EXCEPT( Exception::ERR_ITEM_NOT_FOUND,
			"The specified index is out of range for this XMLAttributes block", "XMLAttributes::getValue" );
	}

	AttributeMap::const_iterator it = mAttributes.begin( );
	std::advance( it, index );

	return it->second;
}

inline const String& XMLAttributes::getValue( const String& name ) const
{
	AttributeMap::const_iterator it = mAttributes.find( name );

	if ( it == mAttributes.end( ) )
	{
		OGRE_EXCEPT( Exception::ERR_ITEM_NOT_FOUND,
			"No value exists for an attribute named '" + name + "'", "XMLAttributes::getValue" );
	}

	return it->second;
}

inline void XMLAttributes::setValue( const String& name, const String& value )
{
	pair<AttributeMap::iterator, bool> inserted = mAttributes.insert( AttributeMap::value_type( name, value ) );

	if ( !inserted.second )
	{
		inserted.first->second = value;
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ModelComponentSerializerImpl_v0_0_1::ModelComponentSerializerImpl_v0_0_1( ) : mMasterEntity( NULL ), mLastMovable( NULL ), mLastAttachNode( NULL )
{
	mFileType = "MODB";	
	mVersion = csModelComponentXmlVersion;
}

ModelComponentSerializerImpl_v0_0_1::~ModelComponentSerializerImpl_v0_0_1( )
{
}

void ModelComponentSerializerImpl_v0_0_1::exportModelComponent( const ModelComponent& modelComponent, const String& filename, Endian endianMode )
{

}

void ModelComponentSerializerImpl_v0_0_1::importModelComponent( DataStreamPtr& stream, ModelComponent& modelComponent )
{
	mFileName = stream->getName( );
	//determineEndianness( stream );

	TiXmlDocument xmldoc;
	TiXmlElement *pRootElement = NULL;

	xmldoc.Parse( stream->getAsString( ).c_str( ) );
	
	if( xmldoc.Error( ) )
	{
		OGRE_EXCEPT( Exception::ERR_INTERNAL_ERROR, "Invalid file: file format incompatible, file reports " + mVersion + 
			" Serializer is version " + mVersion, "ModelComponentSerializerImpl_v0_0_1::importModelComponent" );
	}

	TiXmlEncoding encoding = TIXML_ENCODING_UNKNOWN;		
	TiXmlNode *pNode = xmldoc.FirstChild( );
	while( pNode )
	{

		TiXmlDeclaration* dec = pNode->ToDeclaration( );
		if( dec )
		{
			const char* enc = dec->Encoding( );
			assert( enc );

			if ( *enc == 0 )
				encoding = TIXML_ENCODING_UTF8;
			else if (_stricmp( enc, "UTF-8") == 0 )
				encoding = TIXML_ENCODING_UTF8;
			else if (_stricmp( enc, "UTF8") == 0 )
				encoding = TIXML_ENCODING_UTF8;	// incorrect, but be nice
			else 
				encoding = TIXML_ENCODING_LEGACY;
			break;
		}

		pNode = pNode->NextSiblingElement( );
	}

	// 获取xml文件的root element，取得它的value，用于判断当前解析的是合并后的文件还是合并前的文件
	pRootElement = xmldoc.RootElement( );
	if ( pRootElement == NULL )
	{
		OGRE_EXCEPT( Exception::ERR_INTERNAL_ERROR, "Invalid file: file format incompatible, file reports " + mVersion + 
			" Serializer is version " + mVersion, "ModelComponentSerializerImpl_v0_0_1::importModelComponent" );
	}

	loadElement( *pRootElement, encoding, modelComponent );

	xmldoc.Clear();
}

void ModelComponentSerializerImpl_v0_0_1::loadElement( const TiXmlElement& element, TiXmlEncoding encoding, ModelComponent& modelComponent )
{
	String sElementName = element.Value( );
	XMLAttributes tmp;
	const TiXmlAttribute *pXA = element.FirstAttribute( );

	if( encoding != TIXML_ENCODING_UTF8 )
	{
		while( pXA )
		{
			tmp.setValue( pXA->Name( ), pXA->Value( ) );
			pXA = pXA->Next( );
		}
	}
	else
	{
		std::string sName, sValue;
		ConvertBuffer buf;
		while( pXA )
		{			
			expat_to_local_win32( sName, pXA->Name(), buf );
			expat_to_local_win32( sValue, pXA->Value(), buf );
			tmp.setValue( sName, sValue );
			pXA = pXA->Next( );
		}
	}


	startElement( sElementName, tmp, modelComponent );

	const TiXmlNode *pNode = element.FirstChild( );
	while( pNode )
	{
		const TiXmlElement *pTE = pNode->ToElement( );
		if( pTE )
			loadElement( *pTE , encoding, modelComponent );
		pNode = pNode->NextSiblingElement( );
	}

	endElement( sElementName );
}

void ModelComponentSerializerImpl_v0_0_1::startElement( const String& element, const XMLAttributes& attributes, ModelComponent& modelComponent )
{
	if ( __nocaseequal( element,"entity" ) )
	{
		if ( mLastMovable || mLastAttachNode )
		{
			OGRE_EXCEPT( Exception::ERR_INVALIDPARAMS, "Invalidate model resource " + mFileName, "ModelComponentSerializerImpl_v0_0_1::startElement" );
		}

		// Get the mesh name
		const String& meshName = attributes.getValue( "mesh" );
		Entity* pEntity = modelComponent.createMovableObject( meshName, mMasterEntity );
		mLastMovable = pEntity;

		// Determinate which node to attach to
		bool hasBoneName = false;
		String boneName;
		if ( attributes.exists( "node" ) )
		{
			hasBoneName = true;
			boneName = attributes.getValue( "node" );
		}

		// Determinate should be normalise normal
		bool normalise = false;
		if (attributes.exists("normalise"))
		{
			normalise = lexical_cast<bool>(attributes.getValue("normalise").c_str());
		}

		// Determinate it's decal target
		bool receiveDecals = false;
		if (attributes.exists("receive_decals"))
		{
			receiveDecals = lexical_cast<bool>(attributes.getValue("receive_decals").c_str());
		}

		pEntity->setNormaliseNormals( normalise );

		if ( receiveDecals )
		{
			pEntity->addQueryFlags( OQF_DECAL_TARGET );
			if ( mMasterEntity )
			{
				mMasterEntity->addQueryFlags( OQF_DECAL_TARGET );
			}
		}

		if (hasBoneName && mMasterEntity != NULL)
		{
			mLastAttachNode = mMasterEntity->attachObjectToBone(boneName, pEntity);
		}
		else
		{
			modelComponent.getParent()->attachObject(pEntity);
		}
	}
	else if ( __nocaseequal( element,"offset" ) )
	{
		if ( mLastMovable == NULL )
			OGRE_EXCEPT( Exception::ERR_INVALIDPARAMS, "Invalidate model resource " + mFileName, 
				"ModelComponentSerializerImpl_v0_0_1::startElement" );

		if ( mLastAttachNode == NULL )
		{
			SceneNode* pNode = mLastMovable->getParentSceneNode( );
			if ( pNode != modelComponent.getParent( ) )
				OGRE_EXCEPT( Exception::ERR_INVALIDPARAMS, "Invalidate model resource " + mFileName,
					"ModelComponentSerializerImpl_v0_0_1::startElement" );

			// Detach form parent and attach to new offset scene node
			SceneNode* attachNode = pNode->createChildSceneNode(BLANKSTRING);
			modelComponent.getSceneNodes( ).push_back( attachNode );

			pNode->detachObject( mLastMovable->getName( ) );
			attachNode->attachObject( mLastMovable );
			mLastAttachNode = attachNode;
		}
	}
	else if ( __nocaseequal( element,"translate" ) )
	{
		if ( !mLastAttachNode )
			OGRE_EXCEPT( Exception::ERR_INVALIDPARAMS, "Invalidate model resource " + mFileName,
				"ModelComponentSerializerImpl_v0_0_1::startElement" );

		mLastAttachNode->setPosition(
			lexical_cast<Ogre::Real>(attributes.getValue("x").c_str()),
			lexical_cast<Ogre::Real>(attributes.getValue("y").c_str()),
			lexical_cast<Ogre::Real>(attributes.getValue("z").c_str()));

		mLastAttachNode->setInitialState( );
	}
	else if ( __nocaseequal( element, "rotate" ) )
	{
		if ( !mLastAttachNode )
			OGRE_EXCEPT( Exception::ERR_INVALIDPARAMS, "Invalidate model resource " + mFileName,
				"ModelComponentSerializerImpl_v0_0_1::startElement" );

		mLastAttachNode->setOrientation(
			lexical_cast<Ogre::Real>(attributes.getValue("w").c_str()),
			lexical_cast<Ogre::Real>(attributes.getValue("x").c_str()),
			lexical_cast<Ogre::Real>(attributes.getValue("y").c_str()),
			lexical_cast<Ogre::Real>(attributes.getValue("z").c_str()));


		mLastAttachNode->setInitialState( );
	}
	else if ( __nocaseequal( element, "scale" ) )
	{
		if (!mLastAttachNode)
			OGRE_EXCEPT( Exception::ERR_INVALIDPARAMS, "Invalidate model resource " + mFileName,
			"ModelComponentSerializerImpl_v0_0_1::startElement" );

		mLastAttachNode->setScale(
			lexical_cast<Ogre::Real>(attributes.getValue("x").c_str()),
			lexical_cast<Ogre::Real>(attributes.getValue("y").c_str()),
			lexical_cast<Ogre::Real>(attributes.getValue("z").c_str()));

		mLastAttachNode->setInitialState( );
	}
	else if ( __nocaseequal( element, "frame" )  || __nocaseequal( element, "skeleton" ) )
	{
		if ( mMasterEntity != NULL )
			OGRE_EXCEPT( Exception::ERR_INVALIDPARAMS, "Invalidate model resource " + mFileName, "ModelComponentSerializerImpl_v0_0_1::startElement" );

		// Load the skeleton frame文件就是骨骼文件
		const String& skeletonName = attributes.getValue( "name" );
		mMasterEntity = modelComponent.createMasterMovableObject( skeletonName );
	}
	else if ( __nocaseequal( element,"model" ) )
	{
	}
	else
	{
		OGRE_EXCEPT( Exception::ERR_INTERNAL_ERROR, 
			"Unexpected data was found while parsing the model file: '" + element + "' is unknown.",
			"ModelComponentSerializerImpl_v0_0_1::startElement" );
	}
}

void ModelComponentSerializerImpl_v0_0_1::endElement( const String& element )
{
	if ( __nocaseequal( element,"entity" ) )
	{
		mLastMovable = NULL;
		mLastAttachNode = NULL;
	}
	else if ( __nocaseequal( element,"offset" ) )
	{
		assert( mLastMovable );
		assert( mLastAttachNode );
		mLastAttachNode = NULL;
	}
	else if ( __nocaseequal( element,"translate" ) )
	{
		assert( mLastAttachNode );
	}
	else if ( __nocaseequal( element,"rotate" ) )
	{
		assert( mLastAttachNode );
	}
	else if ( __nocaseequal( element,"scale" ) )
	{
		assert( mLastAttachNode );
	}
	else if ( __nocaseequal( element ,"frame" ) || __nocaseequal( element, "skeleton" ) )
	{
	}
	else if ( __nocaseequal( element,"model" ) )
	{
	}
	else
	{
		OGRE_EXCEPT( Exception::ERR_INTERNAL_ERROR, 
			"Unexpected data was found while parsing the model file: '" + element + "' is unknown.",
			"ModelComponentSerializerImpl_v0_0_1::endElement" );
	}
}

}
