#include <stdio.h>
#include <windows.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s C:\\path\\to\\quickly\\delete\\file.txt .\\path\\to\\dest.txt", argc >= 1 ? argv[0] : "kirishima.exe");
        return 1;
    }
    char* path = argv[1];
    char* dest_path = argv[2];
    printf("Press Enter to Find specified file (%s):\n", path);
    getchar();
    printf("Finding %s...\n", path);
    while (GetFileAttributes(path) == INVALID_FILE_ATTRIBUTES) {}
    printf("Found! open...\n");
    FILE* fp;
    // somehows Windows returns 0x1 to fopen
    while (fp < 0x100) fp = fopen(path, "rb");
    printf("opened (fp=%d), wait 1 sec (to complete write)\n", fp);
    Sleep(1000);
    printf("Open dest_path...\n");
    FILE* fp_dest = fopen(dest_path, "wb");
    if (fp_dest == NULL) {
        printf("failed to open dest_path...\n");
        return 2;
    }
    printf("Start Copy...\n");
    char buffer[1024];
    size_t readed, all = 0;
    while (readed = fread(buffer, 1, 1024, fp)) {
        fwrite(buffer, 1, readed, fp_dest);
        all += readed;
    }
    printf("Copy %d bytes.\n", all);
    return 0;
}