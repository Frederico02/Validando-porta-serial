import serial
import tkinter as tk
from tkinter import messagebox

def verificar_comunicacao():
    porta = 'COM1'  # Defina a porta COM correta para a sua balança
    baud_rate = 9600  # Taxa de transmissão (baud rate)

    try:
        conexao = serial.Serial(porta, baud_rate)
        conexao.close()
        return True
    except serial.SerialException:
        return False

def tentar_novamente():
    if verificar_comunicacao():
        iniciar_interface()
    else:
        messagebox.showerror('Erro', 'Falha ao estabelecer conexão.')
        escolha = messagebox.askquestion('Tentar Novamente', 'Deseja tentar novamente?')
        if escolha == 'yes':
            tentar_novamente()
        else:
            window.destroy()

def obter_peso():
    # Configurações da porta COM
    porta = 'COM1'  # Defina a porta COM correta para a sua balança
    baud_rate = 9600  # Taxa de transmissão (baud rate)

    # Inicializa a conexão serial
    conexao = serial.Serial(porta, baud_rate)

    # Envia comando para obter o peso da balança
    comando_peso = b'PESO\r\n'  # Comando para obter o peso, verifique o comando correto na documentação da sua balança
    conexao.write(comando_peso)

    # Lê a resposta da balança
    resposta = conexao.readline().decode().strip()  # Decodifica os bytes recebidos e remove espaços extras

    # Exibe o peso
    peso_label.config(text='Peso: ' + resposta)

    # Fecha a conexão serial
    conexao.close()

def iniciar_interface():
    global window, peso_label

    window = tk.Tk()
    window.title('Obter Peso da Balança')

    peso_label = tk.Label(window, text='Peso: ')
    peso_label.pack()

    obter_peso_button = tk.Button(window, text='Obter Peso', command=obter_peso)
    obter_peso_button.pack()

    window.mainloop()

def iniciar_programa():
    if verificar_comunicacao():
        iniciar_interface()
    else:
        messagebox.showerror('Erro', 'Falha ao estabelecer conexão.')
        escolha = messagebox.askquestion('Tentar Novamente', 'Deseja tentar novamente?')
        if escolha == 'yes':
            tentar_novamente()
        else:
            window.destroy()

iniciar_programa()
