#!/bin/bash

# Função para exibir um menu de opções
show_menu() {
    dialog --clear --backtitle "Gerenciamento de Serviços" \
    --title "Menu" \
    --menu "Escolha uma opção:" 15 50 10 \
    1 "Iniciar serviço" \
    2 "Parar serviço" \
    3 "Reiniciar serviço" \
    4 "Verificar status do serviço" \
    5 "Ativar serviço na inicialização" \
    6 "Desativar serviço na inicialização" \
    7 "Listar todos os serviços" \
    8 "Habilitar serviço temporariamente" \
    9 "Desabilitar serviço temporariamente" \
    10 "Sair" \
    2>temp
}

# Função para iniciar um serviço
start_service() {
    dialog --inputbox "Digite o nome do serviço a ser iniciado:" 10 50 2>temp
    service_name=$(<temp)
    systemctl start "$service_name"
    dialog --msgbox "Serviço '$service_name' iniciado com sucesso." 10 50
}

# Função para parar um serviço
stop_service() {
    dialog --inputbox "Digite o nome do serviço a ser parado:" 10 50 2>temp
    service_name=$(<temp)
    systemctl stop "$service_name"
    dialog --msgbox "Serviço '$service_name' parado com sucesso." 10 50
}

# Função para reiniciar um serviço
restart_service() {
    dialog --inputbox "Digite o nome do serviço a ser reiniciado:" 10 50 2>temp
    service_name=$(<temp)
    systemctl restart "$service_name"
    dialog --msgbox "Serviço '$service_name' reiniciado com sucesso." 10 50
}

# Função para verificar o status de um serviço
check_service_status() {
    dialog --inputbox "Digite o nome do serviço para verificar o status:" 10 50 2>temp
    service_name=$(<temp)
    status=$(systemctl status "$service_name")
    dialog --title "Status do Serviço $service_name" --msgbox "$status" 20 50
}

# Função para ativar um serviço na inicialização
enable_service() {
    dialog --inputbox "Digite o nome do serviço a ser ativado na inicialização:" 10 50 2>temp
    service_name=$(<temp)
    systemctl enable "$service_name"
    dialog --msgbox "Serviço '$service_name' ativado na inicialização." 10 50
}

# Função para desativar um serviço na inicialização
disable_service() {
    dialog --inputbox "Digite o nome do serviço a ser desativado na inicialização:" 10 50 2>temp
    service_name=$(<temp)
    systemctl disable "$service_name"
    dialog --msgbox "Serviço '$service_name' desativado na inicialização." 10 50
}

# Função para listar todos os serviços
list_all_services() {
    services=$(systemctl list-unit-files --type=service)
    dialog --title "Lista de Serviços" --msgbox "$services" 20 50
}

# Função para habilitar temporariamente um serviço
enable_temporarily() {
    dialog --inputbox "Digite o nome do serviço a ser habilitado temporariamente:" 10 50 2>temp
    service_name=$(<temp)
    systemctl start "$service_name"
    dialog --msgbox "Serviço '$service_name' habilitado temporariamente." 10 50
}

# Função para desabilitar temporariamente um serviço
disable_temporarily() {
    dialog --inputbox "Digite o nome do serviço a ser desabilitado temporariamente:" 10 50 2>temp
    service_name=$(<temp)
    systemctl stop "$service_name"
    dialog --msgbox "Serviço '$service_name' desabilitado temporariamente." 10 50
}

# Loop principal do programa
while true; do
    show_menu
    option=$(<temp)
    case $option in
        1) start_service ;;
        2) stop_service ;;
        3) restart_service ;;
        4) check_service_status ;;
        5) enable_service ;;
        6) disable_service ;;
        7) list_all_services ;;
        8) enable_temporarily ;;
        9) disable_temporarily ;;
        10) break ;;
    esac
done

# Remover arquivo temporário
rm temp
