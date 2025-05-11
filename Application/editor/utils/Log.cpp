/*
Copyright(c) 2016-2025 Panos Karabelas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

//= INCLUDES =================
#include <OgreHeader.h>
#include "Log.h"
#include "../World/Entity.h"
//============================

//= NAMESPACES ===============
using namespace std;
//============================

namespace spartan
{
    namespace
    {
       
    }

    void Log::Initialize()
    {
      
    }

    void Log::SetLogger(ILogger* logger_in)
    {
       
    }

    void Log::SetLogToFile(const bool log)
    {
      
    }

    // all functions resolve to this one
    void Log::Write(const char* text, const LogType type)
    {
       
    }

    void Log::WriteFInfo(const char* text, ...)
    {
    
    }

    void Log::WriteFWarning(const char* text, ...)
    {
      
    }

    void Log::WriteFError(const char* text, ...)
    {
        
    }

    void Log::Write(const string& text, const LogType type)
    {
        Write(text.c_str(), type);
    }

    void Log::WriteFInfo(const string text, ...)
    {
       
    }

    void Log::WriteFWarning(const string text, ...)
    {
       
    }

    void Log::WriteFError(const string text, ...)
    {
        
    }

    void Log::Write(const weak_ptr<Entity>& entity, const LogType type)
    {
        entity.expired() ? Write("Null", type) : Write(entity.lock()->GetObjectName(), type);
    }

    void Log::Write(const shared_ptr<Entity>& entity, const LogType type)
    {
        entity ? Write(entity->GetObjectName(), type) : Write("Null", type);
    }

    void Log::Write(const Ogre::Vector2& value, const LogType type)
    {
       
    }

    void Log::Write(const Ogre::Vector3& value, const LogType type)
    {
        
    }

    void Log::Write(const Ogre::Vector4& value, const LogType type)
    {
        
    }

    void Log::Write(const Ogre::Quaternion& value, const LogType type)
    {
     
    }

    void Log::Write(const Ogre::Matrix4& value, const LogType type)
    {
        
    }
}
