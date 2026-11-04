#!/bin/bash

# Função para exibir o menu principal
exibir_menu_principal() {
    dialog --clear --backtitle "Menu da BIOS" \
    --title "Configurações da BIOS" \
    --menu "Use as setas para cima e para baixo para navegar, e Enter para selecionar." 15 50 5 \
    "1" "Configurações de inicialização" \
    "2" "Configurações de dispositivo" \
    "3" "Configurações de data e hora" \
    "4" "Sair" \
    2> escolha_menu_principal.txt
}

# Função para exibir o menu de configurações de inicialização
exibir_menu_inicializacao() {
    dialog --clear --backtitle "Menu da BIOS" \
    --title "Configurações de Inicialização" \
    --menu "Use as setas para cima e para baixo para navegar, e Enter para selecionar." 15 50 5 \
    "1" "Ordem de inicialização" \
    "2" "Opções avançadas de inicialização" \
    "3" "Configurações de boot seguro" \
    "4" "Voltar ao menu principal" \
    2> escolha_menu_inicializacao.txt
}

# Função para exibir o menu de configurações de dispositivo
exibir_menu_dispositivo() {
    dialog --clear --backtitle "Menu da BIOS" \
    --title "Configurações de Dispositivo" \
    --menu "Use as setas para cima e para baixo para navegar, e Enter para selecionar." 15 50 5 \
    "1" "Disco rígido" \
    "2" "Unidades de CD/DVD" \
    "3" "Unidades USB" \
    "4" "Rede" \
    "5" "Voltar ao menu principal" \
    2> escolha_menu_dispositivo.txt
}

# Função para exibir o menu de configurações de data e hora
exibir_menu_data_hora() {
    dialog --clear --backtitle "Menu da BIOS" \
    --title "Configurações de Data e Hora" \
    --menu "Use as setas para cima e para baixo para navegar, e Enter para selecionar." 15 50 5 \
    "1" "Data" \
    "2" "Hora" \
    "3" "Fuso horário" \
    "4" "Voltar ao menu principal" \
    2> escolha_menu_data_hora.txt
}

# Função principal
principal() {
    while true; do
        exibir_menu_principal
        escolha_menu_principal=$(cat escolha_menu_principal.txt)
        case $escolha_menu_principal in
            1) while true; do
                   exibir_menu_inicializacao
                   escolha_menu_inicializacao=$(cat escolha_menu_inicializacao.txt)
                   case $escolha_menu_inicializacao in
                       1) dialog --msgbox "Configurações de ordem de inicialização" 10 50 ;;
                       2) dialog --msgbox "Opções avançadas de inicialização" 10 50 ;;
                       3) dialog --msgbox "Configurações de boot seguro" 10 50 ;;
                       4) break ;;
                   esac
               done ;;
            2) while true; do
                   exibir_menu_dispositivo
                   escolha_menu_dispositivo=$(cat escolha_menu_dispositivo.txt)
                   case $escolha_menu_dispositivo in
                       1) dialog --msgbox "Configurações de disco rígido" 10 50 ;;
                       2) dialog --msgbox "Configurações de unidades de CD/DVD" 10 50 ;;
                       3) dialog --msgbox "Configurações de unidades USB" 10 50 ;;
                       4) dialog --msgbox "Configurações de rede" 10 50 ;;
                       5) break ;;
                   esac
               done ;;
            3) while true; do
                   exibir_menu_data_hora
                   escolha_menu_data_hora=$(cat escolha_menu_data_hora.txt)
                   case $escolha_menu_data_hora in
                       1) dialog --msgbox "Configurações de data" 10 50 ;;
                       2) dialog --msgbox "Configurações de hora" 10 50 ;;
                       3) dialog --msgbox "Configurações de fuso horário" 10 50 ;;
                       4) break ;;
                   esac
               done ;;
            4) echo "Saindo..."
               exit ;;
        esac
    done
}

# Chamada da função principal
principal
