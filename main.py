#pip install pyserial


import serial

# Configurações da porta COM
porta = 'COM1'  # Defina a porta COM correta para a sua balança
baud_rate = 9600  # Taxa de transmissão (baud rate)

# Inicializa a conexão serial
conexao = serial.Serial(porta, baud_rate)

# Verifica se a conexão foi estabelecida
if conexao.is_open:
    print('Conexão estabelecida com sucesso.')
else:
    print('Falha ao estabelecer conexão.')

# Envia comando para obter o peso da balança
comando_peso = b'PESO\r\n'  # Comando para obter o peso, verifique o comando correto na documentação da sua balança
conexao.write(comando_peso)

# Lê a resposta da balança
resposta = conexao.readline().decode().strip()  # Decodifica os bytes recebidos e remove espaços extras

# Exibe o peso
print('Peso:', resposta)

# Fecha a conexão serial
conexao.close()
