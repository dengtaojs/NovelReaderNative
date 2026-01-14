//
// Created by Dengt on 1/13/2026.
//

#include "TextTools.h"
#include <uchardet/uchardet.h>

namespace novel
{
    std::string getCharset(const char* data, size_t size)
    {
        auto detector = uchardet_new();

        uchardet_handle_data(detector, data, size);
        uchardet_data_end(detector);
        std::string charset = uchardet_get_charset(detector);

        uchardet_delete(detector);
        return charset;
    }

}
