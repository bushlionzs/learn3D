

#ifndef _CEGUIWindowFactoryManager_h_
#define _CEGUIWindowFactoryManager_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include "CEGUISingleton.h"
#include "CEGUILogger.h"
#include "CEGUIIteratorBase.h"
#include <map>
#include <vector>

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4275)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{

class CEGUIEXPORT WindowFactoryManager : public Singleton<WindowFactoryManager>
{
public:
    
    struct CEGUIEXPORT FalagardWindowMapping
    {
        String  d_windowType;
        String  d_lookName;
        String  d_baseType;
    };

    
	class CEGUIEXPORT AliasTargetStack
	{
	public:
		
		AliasTargetStack(void) {}


		
		~AliasTargetStack(void) {}


		
		const String&	getActiveTarget(void) const;

		
		uint	getStackedTargetCount(void) const;


	private:
		friend class WindowFactoryManager;
		typedef std::vector<String>	TargetTypeStack;		

		TargetTypeStack	d_targetStack;		
	};


	
	
	WindowFactoryManager(void)
	{
		
	}


	
	~WindowFactoryManager(void)
	{
		
	}


	
	
	static	WindowFactoryManager&	getSingleton(void);


	
	static	WindowFactoryManager*	getSingletonPtr(void);


	
	void	addFactory(WindowFactory* factory);


	
	void	removeFactory(const String& name);


	
	void	removeFactory(WindowFactory* factory);


	
	void	removeAllFactories(void)		{d_factoryRegistry.clear();}


	
	WindowFactory*	getFactory(const String& type) const;


    
    bool	isFactoryPresent(const String& name) const;


	
	void	addWindowTypeAlias(const String& aliasName, const String& targetType);


	
	void	removeWindowTypeAlias(const String& aliasName, const String& targetType);

    
    void addFalagardWindowMapping(const String& newType, const String& targetType, const String& lookName);

    
    void removeFalagardWindowMapping(const String& type);

    
    bool isFalagardMappedType(const String& type) const;

    
    const String& getMappedLookForType(const String& type) const;


    
    String getDereferencedAliasType(const String& type) const;

private:
	
	typedef	std::map<String, WindowFactory*>	WindowFactoryRegistry;		
	typedef std::map<String, AliasTargetStack>	TypeAliasRegistry;		
    typedef std::map<String, FalagardWindowMapping> FalagardMapRegistry;    

	WindowFactoryRegistry	d_factoryRegistry;			
	TypeAliasRegistry		d_aliasRegistry;			
    FalagardMapRegistry     d_falagardRegistry;         

public:
	
	typedef	ConstBaseIterator<WindowFactoryRegistry>	WindowFactoryIterator;
	typedef ConstBaseIterator<TypeAliasRegistry>		TypeAliasIterator;
    typedef ConstBaseIterator<FalagardMapRegistry>      FalagardMappingIterator;

	
	WindowFactoryIterator	getIterator(void) const;


	
	TypeAliasIterator	getAliasIterator(void) const;


    
    FalagardMappingIterator getFalagardMappingIterator() const;
};

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
