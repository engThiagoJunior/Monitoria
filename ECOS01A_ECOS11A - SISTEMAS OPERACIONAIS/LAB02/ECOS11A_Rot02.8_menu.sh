#!/bin/bash

# Função para exibir o menu principal
exibir_menu() {
    dialog --clear --backtitle "Shell Script com Dialog" \
    --title "Menu Principal" \
    --menu "Escolha uma opção:" 15 50 7 \
    "1" "Verificar diretório atual (pwd)" \
    "2" "Navegar entre diretórios (cd)" \
    "3" "Listar conteúdo do diretório (ls)" \
    "4" "Exibir manual de um comando (man)" \
    "5" "Exibir conteúdo de um arquivo (cat)" \
    "6" "Exibir primeiras linhas de um arquivo (head)" \
    "7" "Exibir últimas linhas de um arquivo (tail)" \
    "8" "Contar linhas, palavras e caracteres (wc)" \
    "9" "Limpar a tela (clear)" \
    "10" "Criar um arquivo vazio (touch)" \
    "11" "Exibir o conteúdo de um arquivo de forma reversa (tac)" \
    "12" "Exibir informações sobre a memória do sistema (free)" \
    "13" "Exibir um calendário (cal)" \
    "14" "Ordenar as linhas de um arquivo (sort)" \
    "15" "Traduzir ou deletar caracteres (tr)" \
    "16" "Combinar linhas de arquivos de texto (paste)" \
    "17" "Comparar dois arquivos linha por linha (diff)" \
    "18" "Comparar dois arquivos byte por byte (cmp)" \
    "19" "Procurar padrões em arquivos (grep)" \
    "20" "Extrair seções de linhas de arquivos (cut)" \
    2> opcao.txt
}

# Função para executar a opção escolhida pelo usuário
executar_opcao() {
    opcao=$(cat opcao.txt)
    case $opcao in
        1) pwd ;;
        2) dialog --inputbox "Digite o caminho do diretório:" 10 50 2> diretorio.txt
           cd $(cat diretorio.txt) ;;
        3) ls ;;
        4) dialog --inputbox "Digite o nome do comando:" 10 50 2> comando.txt
           man $(cat comando.txt) ;;
        5) dialog --inputbox "Digite o nome do arquivo:" 10 50 2> arquivo.txt
           cat $(cat arquivo.txt) ;;
        6) dialog --inputbox "Digite o nome do arquivo:" 10 50 2> arquivo.txt
           head $(cat arquivo.txt) ;;
        7) dialog --inputbox "Digite o nome do arquivo:" 10 50 2> arquivo.txt
           tail $(cat arquivo.txt) ;;
        8) dialog --inputbox "Digite o nome do arquivo:" 10 50 2> arquivo.txt
           wc $(cat arquivo.txt) ;;
        9) clear ;;
        10) dialog --inputbox "Digite o nome do arquivo a ser criado:" 10 50 2> nome_arquivo.txt
            touch $(cat nome_arquivo.txt) ;;
        11) dialog --inputbox "Digite o nome do arquivo:" 10 50 2> arquivo.txt
            tac $(cat arquivo.txt) ;;
        12) free ;;
        13) cal ;;
        14) dialog --inputbox "Digite o nome do arquivo:" 10 50 2> arquivo.txt
            sort $(cat arquivo.txt) ;;
        15) dialog --inputbox "Digite o nome do arquivo:" 10 50 2> arquivo.txt
            tr '[:lower:]' '[:upper:]' < $(cat arquivo.txt) ;;
        16) dialog --inputbox "Digite o nome do primeiro arquivo:" 10 50 2> arquivo1.txt
            dialog --inputbox "Digite o nome do segundo arquivo:" 10 50 2> arquivo2.txt
            paste $(cat arquivo1.txt) $(cat arquivo2.txt) ;;
        17) dialog --inputbox "Digite o nome do primeiro arquivo:" 10 50 2> arquivo1.txt
            dialog --inputbox "Digite o nome do segundo arquivo:" 10 50 2> arquivo2.txt
            diff $(cat arquivo1.txt) $(cat arquivo2.txt) ;;
        18) dialog --inputbox "Digite o nome do primeiro arquivo:" 10 50 2> arquivo1.txt
            dialog --inputbox "Digite o nome do segundo arquivo:" 10 50 2> arquivo2.txt
            cmp $(cat arquivo1.txt) $(cat arquivo2.txt) ;;
        19) dialog --inputbox "Digite o padrão a ser procurado:" 10 50 2> padrao.txt
            dialog --inputbox "Digite o nome do arquivo:" 10 50 2> arquivo.txt
            grep $(cat padrao.txt) $(cat arquivo.txt) ;;
        20) dialog --inputbox "Digite o nome do arquivo:" 10 50 2> arquivo.txt
            dialog --inputbox "Digite a posição inicial:" 10 50 2> inicio.txt
            dialog --inputbox "Digite a posição final:" 10 50 2> fim.txt
            cut -c$(cat inicio.txt)-$(cat fim.txt) $(cat arquivo.txt) ;;
        *) echo "Opção inválida." ;;
    esac
}

# Executar o script
while true; do
    exibir_menu
    executar_opcao
done
