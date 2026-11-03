#!/bin/bash

# Função para criar diretório usando dialog
criar_diretorio() {
    # Exibir caixa de diálogo de entrada para obter o nome do diretório
    dialog --title "Criar Diretório" --inputbox "Digite o nome do diretório:" 10 50 2> nome_diretorio.txt

    # Ler o nome do diretório digitado
    nome_diretorio=$(cat nome_diretorio.txt)

    # Criar o diretório
    mkdir "$nome_diretorio" && echo "Diretório '$nome_diretorio' criado com sucesso."
}

# Chamada da função
criar_diretorio
