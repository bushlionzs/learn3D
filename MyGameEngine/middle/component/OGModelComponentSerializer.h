#ifndef OGMODELCOMPONENTSERIALIZER_H
#define OGMODELCOMPONENTSERIALIZER_H


#include "OgreSerializer.h"


enum TiXmlEncoding;
class TiXmlElement;

namespace Orphigine
{
	class ModelComponent;
	class ModelComponentSerializerImpl;
	class XMLAttributes;

	class  ModelComponentSerializer : public Serializer
	{
		friend class ModelComponentSerializerImpl;
	public:
		ModelComponentSerializer( );
		virtual ~ModelComponentSerializer( );

		virtual void exportModelComponent( const ModelComponent& modelComponent, const String& fileName, Endian endianMode = ENDIAN_NATIVE );
		virtual void importModelComponent( DataStreamPtr& stream, ModelComponent& modelComponent );

	protected:
		static const String msCurrentVersion;
		typedef std::map< String, ModelComponentSerializerImpl*> ModelComponentSerializerImplMap;
		ModelComponentSerializerImplMap mModelComponentSerializers;
	};

	class ModelComponentSerializerImpl : public Serializer
	{
	public:
		ModelComponentSerializerImpl( );
		virtual ~ModelComponentSerializerImpl( );

		virtual void exportModelComponent( const ModelComponent& modelComponent, const String& filename, Endian endianMode = ENDIAN_NATIVE );
		virtual void importModelComponent( DataStreamPtr& stream, ModelComponent& modelComponent );

	protected:
		virtual void writeModelComponent( const ModelComponent& modelComponent );
		virtual void writeMasterEntity( const ModelComponent& ModelComponent, const Entity* pEntity = NULL );
		virtual void writeEntity( const ModelComponent& modelComponent, const Entity& entity, const Entity* pMasterEntity = NULL );

		virtual void readModelComponent( DataStreamPtr& stream, ModelComponent& modelComponent );
		virtual void readMasterEntity( DataStreamPtr& stream, ModelComponent& modelComponent );
		virtual void readEntity( DataStreamPtr& stream, ModelComponent& modelComponent, Entity* pMasterEntity = NULL );

		virtual uint32 calcSize( const ModelComponent& modelComponent ) const;
		virtual uint32 calcMasterEntitySize( const ModelComponent& modelComponent, const Entity* pEntity = NULL ) const;
		virtual uint32 calcEntitySize( const ModelComponent& modelComponent, const Entity& entity, const Entity* pMasterEntity = NULL ) const;
	private:
		String mFileType;
		String mFileName;
	};

	class ModelComponentSerializerImpl_v0_0_1 : public ModelComponentSerializerImpl
	{
	public:
		ModelComponentSerializerImpl_v0_0_1( );
		virtual ~ModelComponentSerializerImpl_v0_0_1( );

		virtual void exportModelComponent( const ModelComponent& modelComponent, const String& filename, Endian endianMode = ENDIAN_NATIVE );
		virtual void importModelComponent( DataStreamPtr& stream, ModelComponent& modelComponent );

	protected:
		void loadElement( const TiXmlElement &element, TiXmlEncoding encoding, ModelComponent& modelComponent );
		void startElement( const String& element, const XMLAttributes& attributes, ModelComponent& modelComponent );
		void endElement( const String& element );

	private:
		Entity* mMasterEntity;
		MoveObject* mLastMovable;
		Node* mLastAttachNode;
		String mFileType;
		String mFileName;

	};
}

#endif // OGMODELCOMPONENTSERIALIZER_H
