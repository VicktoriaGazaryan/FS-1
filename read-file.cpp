#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>
#include <errno.h>
using namespace std;
const size_t BUFFER_SIZE = 1024; 

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Ошибка: введите имя файла.\n";
        return 1;
    }

    int fileDescriptor = open(argv[1], O_RDONLY);
    if (fileDescriptor == -1) {
        cout << "Ошибка: не удалось открыть файл \"" << argv[1] << "\": " << strerror(errno) << "\n";
        return 1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;
       string line;

    while ((bytesRead = read(fileDescriptor, buffer, sizeof(buffer))) > 0) {

        for (ssize_t i = 0; i < bytesRead; ++i) {
            if (buffer[i] == '\n') {
             cout << line << '\n'; 
                line.clear(); 
            } else {
                line += buffer[i]; 
        }
    }

  
    if (bytesRead == -1) {
            cout << "Ошибка: не удалось прочитать файл \"" << argv[1] << "\": " << strerror(errno) << "\n";
        close(fileDescriptor);
        return 1;
    }

    if (!line.empty()) {
        cout << line << '\n';
    }


    close(fileDescriptor);
    return 0;
}
}



    
