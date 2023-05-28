import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;
import java.util.Scanner;

import gnu.io.*;

public class SerialCommunicationExample {

    private static final String PORT_NAME = "COM1"; // Defina a porta COM correta para a sua balança
    private static final int BAUD_RATE = 9600; // Taxa de transmissão (baud rate)
    private static final int DATA_BITS = SerialPort.DATABITS_8;
    private static final int STOP_BITS = SerialPort.STOPBITS_1;
    private static final int PARITY = SerialPort.PARITY_NONE;

    public static void main(String[] args) {
        try {
            // Configura a conexão serial
            SerialPort serialPort = (SerialPort) CommPortIdentifier.getPortIdentifier(PORT_NAME)
                    .open(SerialCommunicationExample.class.getSimpleName(), 2000);
            serialPort.setSerialPortParams(BAUD_RATE, DATA_BITS, STOP_BITS, PARITY);

            // Obtem os fluxos de entrada e saída da porta serial
            InputStream inputStream = serialPort.getInputStream();
            OutputStream outputStream = serialPort.getOutputStream();

            // Envia comando para obter o peso da balança
            String comandoPeso = "PESO\r\n"; // Comando para obter o peso, verifique o comando correto na documentação da sua balança
            outputStream.write(comandoPeso.getBytes(StandardCharsets.UTF_8));

            // Lê a resposta da balança
            Scanner scanner = new Scanner(inputStream, StandardCharsets.UTF_8);
            String resposta = scanner.nextLine();

            // Exibe o peso
            System.out.println("Peso: " + resposta);

            // Fecha a conexão serial
            scanner.close();
            outputStream.close();
            inputStream.close();
            serialPort.close();
        } catch (NoSuchPortException | PortInUseException | UnsupportedCommOperationException | IOException e) {
            e.printStackTrace();
        }
    }
}
