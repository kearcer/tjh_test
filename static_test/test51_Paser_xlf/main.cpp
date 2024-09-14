#include <atlbase.h>  // Includes CComVariant and CComBSTR.

#include <string>
#include <vector>

#include "Windows.h"
// #include "stdafx.h"

// Include for MSXML (XML DOM)
#import "msxml4.dll" named_guids raw_interfaces_only

// Pack
#pragma pack(1)

// Info for the next block to read out of the file
struct SNextBlock {
    int Test;    // Test == 0x70
    int Length;  // Number of bytes to read
};

#pragma warning(disable : 4200)
// XML Description
struct STextBlock {
    unsigned char Test;  // Test == 0x2A
    int TextLength;      // Number of unicode characters
    wchar_t pXML[];      // XML
};

struct SInt32Block {
    unsigned char Test;  // Test == 0x2A
    int Number;          // Number of unicode characters
};

struct SInt64Block {
    unsigned char Test;  // Test == 0x2A
    ULONGLONG Number;    // Number of unicode characters
};

// Memory Description for File Version 1 (32 Bit)
struct SMemoryBlock32 {
    unsigned char Test1;      // Test == 0x2A
    unsigned int MemorySize;  // Memory size of the object
    unsigned char Test2;      // Test == 0x2A
    int StringLength;         // Length of the String
    wchar_t pString[];        // Memory ID Text of the object
};

// Memory Description for File Version 2 (64 Bit)
struct SMemoryBlock64 {
    unsigned char Test1;   // Test == 0x2A
    ULONGLONG MemorySize;  // Memory size of the object
    unsigned char Test2;   // Test == 0x2A
    int StringLength;      // Length of the String
    wchar_t pString[];     // Memory ID Text of the object
};

#pragma warning(default : 4200)
#pragma pack()

// Example structure to save the found memory blobs in LIF Files
struct SMemoryPosition {
    std::wstring Name;
    ULONGLONG FileOffset;
};

// Read File caller

bool Read(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead) {
    DWORD NumberOfBytesRead;
    if (ReadFile(hFile, lpBuffer, nNumberOfBytesToRead, &NumberOfBytesRead, NULL) == FALSE) return false;
    if (nNumberOfBytesToRead != NumberOfBytesRead) return false;
    return true;
}

// Analyses the xml content and determine the file format version
int AnalyseVersion(STextBlock* pXMLInfo) {
    // Create instance of DOM Document (MSXML2)
    MSXML2::IXMLDOMDocumentPtr Doc;
    HRESULT Result = Doc.CreateInstance(("Msxml2.DOMDocument.4.0"));

    BSTR bstrXML;
    VARIANT_BOOL bIsSuccessful;

    // Create BSTR
    bstrXML = ::SysAllocStringLen(pXMLInfo->pXML, pXMLInfo->TextLength);

    // Load XML String in DOM Document
    Doc->loadXML(bstrXML, &bIsSuccessful);
    SysFreeString(bstrXML);

    MSXML2::IXMLDOMNode* pRoot = NULL;

    // Determine the root element node
    MSXML2::IXMLDOMNodeList* pNodeList = NULL;
    if (Doc->get_childNodes(&pNodeList) == S_OK) {
        if (pNodeList) {
            long Length = 0;
            pNodeList->get_length(&Length);

            for (long i = 0; i < Length; i++) {
                pNodeList->get_item(i, &pRoot);
                MSXML2::DOMNodeType DOMNodeTyp;
                HRESULT hr = pRoot->get_nodeType(&DOMNodeTyp);
                if ((hr == S_OK) && (DOMNodeTyp == MSXML2::NODE_ELEMENT)) break;

                pRoot->Release();
                pRoot = NULL;
            }
            pNodeList->Release();
        }
    }

    BSTR Name;
    BSTR VersionStr;
    int Version = -1;

    if (pRoot != NULL) {
        // Check Root Name
        pRoot->get_nodeName(&Name);
        if (wcscmp(Name, L"LMSDataContainerHeader") != 0) return -1;

        // Cast to XML Element
        MSXML2::IXMLDOMElement* pEle;
        pRoot->QueryInterface(MSXML2::IID_IXMLDOMElement, (void**)&pEle);

        // Get Attribute "Version"
        BSTR AttrName = ::SysAllocStringLen(L"Version", 7);
        VARIANT Value;
        pEle->getAttribute(AttrName, &Value);

        VersionStr = V_BSTR(&Value);

        // Transform string to int
        swscanf_s(VersionStr, L"%d", &Version);
    }

    return Version;
}

void LoadExample_LIF() {
    HANDLE hFile = NULL;
    void* pXMLMem = NULL;
    void* pMemBlockInfoMem = NULL;

    try {
        char* pFileName = "d:\\images\\Circle Spots.lif";
        char* pOutXMLFileName = "d:\\Experiment_LIF.xml";

        // Open existing file
        hFile = CreateFile(pFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);

        // Check
        if (hFile == INVALID_HANDLE_VALUE) return throw false;

        // Read Header
        SNextBlock Block;
        if (!Read(hFile, &Block, sizeof(SNextBlock))) throw false;

        // Check
        if (Block.Test != 0x70) throw false;

        // Alloc Memory
        void* pXMLMem = new unsigned char[Block.Length];

        // Read into Memory
        if (!Read(hFile, pXMLMem, Block.Length)) throw false;

        // cast to structure
        STextBlock* pXMLInfo = (STextBlock*)pXMLMem;

        // Check
        if (pXMLInfo->Test != 0x2A) throw false;

        // Read out XML string (UNICODE! 16 Bit!)
        std::wstring strXml(pXMLInfo->pXML, pXMLInfo->TextLength);

        // Evaluate XML Data
        wprintf(strXml.c_str());
        wprintf(L"\r\n");

        // write XML to an xml file that can be viewed with a browser
        FILE* stream;
        if ((0 != fopen_s(&stream, pOutXMLFileName, "w+"))) throw false;
        fwprintf(stream, L"%s", strXml.c_str());
        fclose(stream);

        int Version = AnalyseVersion(pXMLInfo);
        if ((Version < 1) || (Version > 2)) throw false;

        std::vector<SMemoryPosition> Positions;

        do {  // for each memory blob -> try to read as much as you can!
            // Read Size
            if (!Read(hFile, &Block, sizeof(SNextBlock))) break;  // Exit

            // Check
            if (Block.Test != 0x70) {
                wprintf(L"Read error!\r\n");
                break;
            }

            // Alloc Memory
            void* pMemBlockInfoMem = new unsigned char[Block.Length];

            // Read Info Memory
            if (!Read(hFile, pMemBlockInfoMem, Block.Length)) {
                wprintf(L"Read error!\r\n");
                break;
            }

            LARGE_INTEGER MemSize;
            std::wstring strMemoryName;

            if (Version == 1) {  // LAS AF 1.6 and older
                // Cast to stucture
                SMemoryBlock32* pMemInfo = (SMemoryBlock32*)pMemBlockInfoMem;

                // Check
                if (pMemInfo->Test1 != 0x2A) {
                    wprintf(L"Read error!\r\n");
                    break;
                }

                // Check
                if (pMemInfo->Test2 != 0x2A) {
                    wprintf(L"Read error!\r\n");
                    break;
                }

                MemSize.QuadPart = pMemInfo->MemorySize;
                strMemoryName = std::wstring(pMemInfo->pString, pMemInfo->StringLength);

                // Analyse Info
                wprintf(L"Size: %u, id: %s", pMemInfo->MemorySize, strMemoryName.c_str());
                wprintf(L"\r\n");
            } else {
                // Cast to stucture
                SMemoryBlock64* pMemInfo = (SMemoryBlock64*)pMemBlockInfoMem;

                // Check
                if (pMemInfo->Test1 != 0x2A) {
                    wprintf(L"Read error!\r\n");
                    break;
                }

                // Check
                if (pMemInfo->Test2 != 0x2A) {
                    wprintf(L"Read error!\r\n");
                    break;
                }

                MemSize.QuadPart = pMemInfo->MemorySize;
                strMemoryName = std::wstring(pMemInfo->pString, pMemInfo->StringLength);

                // Analyse Info
                wprintf(L"Size: %I64u, id: %s", pMemInfo->MemorySize, strMemoryName.c_str());
                wprintf(L"\r\n");
            }

            LARGE_INTEGER LIDummy;
            LIDummy.QuadPart = 0;

            // Determine the current File Position (just an example)
            LARGE_INTEGER CurFilePos;
            SetFilePointerEx(hFile, LIDummy, &CurFilePos, FILE_CURRENT);

            SMemoryPosition Info;
            Info.Name = strMemoryName;
            Info.FileOffset = CurFilePos.QuadPart;

            Positions.push_back(Info);

            // Ignore the image memory and jump to the next blob
            SetFilePointerEx(hFile, MemSize, 0, FILE_CURRENT);

            // delete Info Memo
            delete[] pMemBlockInfoMem;
            pMemBlockInfoMem = NULL;

        } while (1);

        wprintf(L"Found: %d Memory Objects", (int)Positions.size());
        wprintf(L"\r\n");
    } catch (bool bOK) {
        if (bOK == false) wprintf(L"Error!\r\n");
    }

    CloseHandle(hFile);

    if (pXMLMem) delete[] pXMLMem;
    if (pMemBlockInfoMem) delete[] pMemBlockInfoMem;
}

void LoadExample_LOF() {
    HANDLE hFile = NULL;
    void* pXMLMem = NULL;
    void* pMemBlockInfoMem = NULL;

    try {
        char* pFileName = "C:\\WorkSpace\\mytest\\tjh_test\\static_test\\test51_Paser_xlf\\SingleImage.lof";
        char* pOutXMLFileName = "C:\\WorkSpace\\mytest\\tjh_test\\static_test\\test51_Paser_xlf\\SingleImage_out.xml";

        // Open existing file
        hFile = CreateFile(pFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);

        // Check
        if (hFile == INVALID_HANDLE_VALUE) return throw false;

        // Read next Block
        SNextBlock Block;
        if (!Read(hFile, &Block, sizeof(SNextBlock))) throw false;

        // Check
        if (Block.Test != 0x70) throw false;

        // Alloc Memory
        void* pHeader = new unsigned char[Block.Length];

        // Read into Memory
        if (!Read(hFile, pHeader, Block.Length)) throw false;

        // cast to structure
        STextBlock* pTypeInfo = (STextBlock*)pHeader;

        // Check
        if (pTypeInfo->Test != 0x2a) throw false;

        // Read Text (UNICODE! 16 Bit!)
        std::wstring strType(pTypeInfo->pXML, pTypeInfo->TextLength);

        // Pointer after the text
        unsigned char* pPointer = (unsigned char*)pTypeInfo->pXML + pTypeInfo->TextLength * 2;

        // Major file format version
        SInt32Block* pMajorVersion = (SInt32Block*)pPointer;
        // Check
        if (pMajorVersion->Test != 0x2a) throw false;

        // Minor file format version
        pPointer += 5;  // 1 Test byte + 4 bytes for integer
        SInt32Block* pMinorVersion = (SInt32Block*)(pPointer);
        // Check
        if (pMinorVersion->Test != 0x2a) throw false;

        // Memory Size
        pPointer += 5;  // 1 Test byte + 4 bytes for integer
        SInt64Block* pMemorySize = (SInt64Block*)(pPointer);
        // Check
        if (pMemorySize->Test != 0x2a) throw false;

        wprintf(L"Type: %s, Major Version: %d, Minor Version: %d, Size: %I64u", strType.c_str(), pMajorVersion->Number,
                pMinorVersion->Number, pMemorySize->Number);
        wprintf(L"\r\n");

        // Check whether header is valid
        bool bOK = true;
        std::wstring wideConst(L"LMS_Object_File");
        bool a = (strType == wideConst);
        bOK &= a;
        bOK &= pMajorVersion->Number == 1;
        bOK &= pMinorVersion->Number == 0;

        if (bOK == false) {
            throw false;
        }

        LARGE_INTEGER MemSize;
        MemSize.QuadPart = pMemorySize->Number;

        LARGE_INTEGER LIDummy;
        LIDummy.QuadPart = 0;

        // Determine the current File Position (just an example)
        LARGE_INTEGER CurFilePos;
        SetFilePointerEx(hFile, LIDummy, &CurFilePos, FILE_CURRENT);

        // Ignore the object memory and jump to the XML description
        SetFilePointerEx(hFile, MemSize, 0, FILE_CURRENT);

        // Read next Block (XML Header)
        if (!Read(hFile, &Block, sizeof(SNextBlock))) throw false;

        // Check
        if (Block.Test != 0x70) throw false;

        // Alloc Memory
        void* pXMLMem = new unsigned char[Block.Length];

        // Read XML into Memory
        if (!Read(hFile, pXMLMem, Block.Length)) throw false;

        // cast to structure
        STextBlock* pXMLInfo = (STextBlock*)pXMLMem;

        // Check
        if (pXMLInfo->Test != 0x2a) throw false;

        // read out XML string (UNICODE! 16 Bit!)
        std::wstring strXml(pXMLInfo->pXML, pXMLInfo->TextLength);

        // Evaluate XML Data
        wprintf(strXml.c_str());
        wprintf(L"\r\n");

        // write XML to an xml file that can be viewed with a browser
        FILE* stream;
        if ((0 != fopen_s(&stream, pOutXMLFileName, "w+"))) throw false;

        fwprintf(stream, L"%s", strXml.c_str());
        fclose(stream);
    } catch (bool bOK) {
        if (bOK == false) wprintf(L"Error!\r\n");
    }

    CloseHandle(hFile);

    if (pXMLMem) delete[] pXMLMem;
}

int main() {
    CoInitialize(NULL);  // for MSXML
    LoadExample_LOF();
    // LoadExample_LIF();
    CoUninitialize();
    return 0;
};
