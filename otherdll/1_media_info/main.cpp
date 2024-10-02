/*
 * @Author: Jiahui Tang jiahui.tang@leica-microsystems.com
 * @Date: 2024-09-30 15:21:52
 * @LastEditors: Jiahui Tang jiahui.tang@leica-microsystems.com
 * @LastEditTime: 2024-09-30 15:29:28
 * @FilePath: \tjh_test\otherdll\1_media_info\main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/*  Copyright (c) MediaArea.net SARL. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license that can
 *  be found in the License.html file in the root of the source tree.
 */

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Example for MediaInfoLib
// Command line version
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifdef MEDIAINFO_LIBRARY
    #include "MediaInfo/MediaInfo.h" //Staticly-loaded library (.lib or .a or .so)
    #define MediaInfoNameSpace MediaInfoLib;
#else //MEDIAINFO_LIBRARY
    #include "MediaInfoDLL/MediaInfoDLL.h" //Dynamicly-loaded library (.dll or .so)
    #define MediaInfoNameSpace MediaInfoDLL;
#endif //MEDIAINFO_LIBRARY
#include <iostream>
#include <iomanip>
#include <string>

using namespace MediaInfoNameSpace;

#ifdef __MINGW32__
    #ifdef _UNICODE
        #define _itot _itow
    #else //_UNICODE
        #define _itot itoa
    #endif //_UNICODE
#endif //__MINGW32

int main()
{
    MediaInfo MI;
    std::string all;
    MI.Open("C:\\ProgramData\\Leica Microsystems\\Enersight Desktop\\images\\1\\1.jpg");
    MI.Option("Complete");
    all = MI.Inform();
    MI.Close();

    std::cout << all << std::endl;

    return 0;
}

