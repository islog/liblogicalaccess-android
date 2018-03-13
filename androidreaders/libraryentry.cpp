#include "androidreaderprovider.hpp"
#include "morphosamreaderprovider.hpp"
#include <string>

#ifdef _MSC_VER
#include "logicalaccess/msliblogicalaccess.h"
#else
#ifndef LIBLOGICALACCESS_API
#define LIBLOGICALACCESS_API
#endif
#ifndef DISABLE_PRAGMA_WARNING
#define DISABLE_PRAGMA_WARNING /**< \brief winsmcrd.h was modified to support            \
                                  this macro, to avoid MSVC specific warnings            \
                                  pragma */
#endif
#endif

extern "C" {
LIBLOGICALACCESS_API char *getLibraryName()
{
    return (char *)READER_ANDROID;
}

LIBLOGICALACCESS_API void
getAndroidReader(std::shared_ptr<logicalaccess::AndroidReaderProvider> *rp)
{
    if (rp != NULL)
    {
        *rp = logicalaccess::AndroidReaderProvider::getSingletonInstance();
    }
}

LIBLOGICALACCESS_API void
getMORPHO_SAMReader(std::shared_ptr<logicalaccess::MorphoSAMReaderProvider> *rp)
{
    if (rp != NULL)
    {
        *rp = logicalaccess::MorphoSAMReaderProvider::getSingletonInstance();
    }
}

LIBLOGICALACCESS_API bool getReaderInfoAt(unsigned int index, char *readername,
                                          size_t readernamelen, void **getterfct)
{
    bool ret = false;
    if (readername != NULL && readernamelen == PLUGINOBJECT_MAXLEN && getterfct != NULL)
    {
        switch (index)
        {
        case 0:
        {
            *getterfct = (void *)&getAndroidReader;
            sprintf(readername, READER_ANDROID);
            ret = true;
        }
        case 1:
        {
            *getterfct = (void *)&getMORPHO_SAMReader;
            sprintf(readername, READER_MORPHO_SAM);
            ret = true;
        }
        break;
        }
    }

    return ret;
}
}
