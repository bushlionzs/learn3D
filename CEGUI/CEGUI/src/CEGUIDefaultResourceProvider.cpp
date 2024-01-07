

#include "CEGUIDefaultResourceProvider.h"
#include "CEGUIExceptions.h"

#include <fstream>


namespace CEGUI
{
















    void DefaultResourceProvider::loadRawDataContainer(const String& filename, RawDataContainer& output, const String& resourceGroup)
    {
        if (filename.empty() || (filename == (utf8*)""))
        {
            throw InvalidRequestException((utf8*)
                "DefaultResourceProvider::load - Filename supplied for data loading must be valid");
        }

        std::ifstream dataFile(filename.c_str(), std::ios::binary|std::ios::ate);
        if( dataFile.fail())
        {
            throw InvalidRequestException((utf8*)
                "DefaultResourceProvider::load - " + filename + " does not exist");
        }
        std::streampos size = dataFile.tellg();
        dataFile.seekg (0, std::ios::beg);

        unsigned char* buffer = new unsigned char [size];

        try {
            dataFile.read(reinterpret_cast<char*>(buffer), size);
        }
        catch(std::ifstream::failure e) {
            delete [] buffer;
            throw GenericException((utf8*)
                "DefaultResourceProvider::loadRawDataContainer - Problem reading " + filename);
        }

        dataFile.close();

        
        output.setData(buffer);
        output.setSize(size);
        
    }

} 
