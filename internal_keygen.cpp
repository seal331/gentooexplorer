#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <vector>
#include <string>
#include <winsock.h>
#include <Windows.h>

typedef unsigned char uchar;
static const std::string b = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";//=
static std::string base64_encode(const std::string& in) {
    std::string out;

    int val = 0, valb = -6;
    for (uchar c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back(b[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) out.push_back(b[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4) out.push_back('=');
    return out;
}


static std::string base64_decode(const std::string& in) {

    std::string out;

    std::vector<int> T(256, -1);
    for (int i = 0; i < 64; i++) T[b[i]] = i;

    int val = 0, valb = -8;
    for (uchar c : in) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
}

int main()
{
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "error" << std::endl;
		exit(1);
	}
    char szPath[128] = "";
    gethostname(szPath, sizeof(szPath));
	unsigned long long physicalMemory = 0;
	GetPhysicallyInstalledSystemMemory(&physicalMemory);
	physicalMemory *= 1024;
    std::string a(szPath);
    std::string watermark = "#PONSUKECOMMUNICATIONS#";
    std::string serial_unencrypted = a + "#PONSUKECOMMUNICATIONS#" + std::to_string(physicalMemory);
    std::cout << base64_encode(serial_unencrypted) << std::endl;
}