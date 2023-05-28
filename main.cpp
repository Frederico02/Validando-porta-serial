#include <iostream>
#include <windows.h>

int main() {
    HANDLE hSerial;
    DCB dcbSerialParams = { 0 };
    COMMTIMEOUTS timeouts = { 0 };

    // Configurações da porta COM
    LPCSTR portName = "COM1";  // Defina a porta COM correta para a sua balança

    // Abre a porta serial
    hSerial = CreateFileA(portName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cout << "Falha ao abrir a porta serial." << std::endl;
        return 1;
    }

    // Configura as propriedades da porta serial
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cout << "Falha ao obter as propriedades da porta serial." << std::endl;
        CloseHandle(hSerial);
        return 1;
    }
    dcbSerialParams.BaudRate = CBR_9600;  // Taxa de transmissão (baud rate)
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cout << "Falha ao configurar as propriedades da porta serial." << std::endl;
        CloseHandle(hSerial);
        return 1;
    }

    // Configura os timeouts da porta serial
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    if (!SetCommTimeouts(hSerial, &timeouts)) {
        std::cout << "Falha ao configurar os timeouts da porta serial." << std::endl;
        CloseHandle(hSerial);
        return 1;
    }

    // Envia comando para obter o peso da balança
    char comandoPeso[] = "PESO\r\n";  // Comando para obter o peso, verifique o comando correto na documentação da sua balança
    DWORD bytesWritten;
    if (!WriteFile(hSerial, comandoPeso, sizeof(comandoPeso) - 1, &bytesWritten, NULL)) {
        std::cout << "Falha ao enviar o comando para a porta serial." << std::endl;
        CloseHandle(hSerial);
        return 1;
    }

    // Lê a resposta da balança
    char resposta[256];
    DWORD bytesRead;
    if (!ReadFile(hSerial, resposta, sizeof(resposta) - 1, &bytesRead, NULL)) {
        std::cout << "Falha ao ler a resposta da porta serial." << std::endl;
        CloseHandle(hSerial);
        return 1;
    }
    resposta[bytesRead] = '\0';

    // Exibe o peso
    std::cout << "Peso: " << resposta << std::endl;

    // Fecha a porta serial
    CloseHandle(hSerial);

    return 0;
}
