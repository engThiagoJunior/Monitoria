#!/bin/bash

# Função para exibir um menu de opções
show_menu() {
    dialog --clear --backtitle "Monitoramento de Recursos" \
    --title "Menu" \
    --menu "Escolha uma opção:" 15 50 10 \
    1 "Monitorar uso de CPU" \
    2 "Monitorar uso de memória" \
    3 "Monitorar uso de disco" \
    4 "Monitorar uso de rede" \
    5 "Verificar processos em execução" \
    6 "Verificar espaço em disco" \
    7 "Verificar uso de memória RAM" \
    8 "Verificar uso de swap" \
    9 "Listar usuários logados" \
    10 "Sair" \
    2>temp
}

# Função para monitorar uso de CPU
monitor_cpu() {
    top -n 1 | grep "Cpu(s)" > temp
    cpu_usage=$(awk '{print $2+$4+$6}' temp)
    dialog --msgbox "Uso atual de CPU: $cpu_usage%" 10 50
}

# Função para monitorar uso de memória
monitor_memory() {
    free -m > temp
    total_memory=$(awk 'NR==2{print $2}' temp)
    used_memory=$(awk 'NR==2{print $3}' temp)
    dialog --msgbox "Uso atual de memória: $used_memory MB de $total_memory MB" 10 50
}

# Função para monitorar uso de disco
monitor_disk() {
    df -h > temp
    dialog --textbox temp 20 50
}

# Função para monitorar uso de rede
monitor_network() {
    ifconfig > temp
    dialog --textbox temp 20 50
}

# Função para verificar processos em execução
check_processes() {
    ps aux > temp
    dialog --textbox temp 20 80
}

# Função para verificar espaço em disco
check_disk_space() {
    df -h > temp
    dialog --textbox temp 20 50
}

# Função para verificar uso de memória RAM
check_memory_usage() {
    free -m > temp
    dialog --textbox temp 20 50
}

# Função para verificar uso de swap
check_swap_usage() {
    swapon -s > temp
    dialog --textbox temp 20 50
}

# Função para listar usuários logados
list_logged_users() {
    who > temp
    dialog --textbox temp 20 50
}

# Loop principal do programa
while true; do
    show_menu
    option=$(<temp)
    case $option in
        1) monitor_cpu ;;
        2) monitor_memory ;;
        3) monitor_disk ;;
        4) monitor_network ;;
        5) check_processes ;;
        6) check_disk_space ;;
        7) check_memory_usage ;;
        8) check_swap_usage ;;
        9) list_logged_users ;;
        10) break ;;
    esac
done

# Remover arquivo temporário
rm temp
