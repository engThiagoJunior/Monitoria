#!/bin/bash

# Função para exibir um menu de opções
show_menu() {
    dialog --clear --backtitle "Configuração de Rede" \
    --title "Menu" \
    --menu "Escolha uma opção:" 15 50 10 \
    1 "Visualizar configuração de rede" \
    2 "Configurar endereço IP" \
    3 "Configurar gateway padrão" \
    4 "Configurar DNS" \
    5 "Reiniciar interface de rede" \
    6 "Verificar conectividade de rede" \
    7 "Exibir informações sobre interfaces de rede" \
    8 "Exibir tabela de roteamento" \
    9 "Exibir estatísticas de interface de rede" \
    10 "Sair" \
    2>temp
}

# Função para visualizar configuração de rede
view_network_config() {
    network_config=$(ifconfig)
    dialog --title "Configuração de Rede" --msgbox "$network_config" 20 50
}

# Função para configurar endereço IP
configure_ip_address() {
    dialog --inputbox "Digite o nome da interface de rede:" 10 50 2>temp
    interface=$(<temp)
    dialog --inputbox "Digite o novo endereço IP:" 10 50 2>temp
    ip_address=$(<temp)
    ifconfig "$interface" "$ip_address"
    dialog --msgbox "Endereço IP configurado com sucesso para a interface '$interface'." 10 50
}

# Função para configurar gateway padrão
configure_default_gateway() {
    dialog --inputbox "Digite o endereço IP do gateway padrão:" 10 50 2>temp
    gateway=$(<temp)
    route add default gw "$gateway"
    dialog --msgbox "Gateway padrão configurado com sucesso para '$gateway'." 10 50
}

# Função para configurar DNS
configure_dns() {
    dialog --inputbox "Digite o endereço do servidor DNS:" 10 50 2>temp
    dns_server=$(<temp)
    echo "nameserver $dns_server" > /etc/resolv.conf
    dialog --msgbox "Servidor DNS configurado com sucesso para '$dns_server'." 10 50
}

# Função para reiniciar interface de rede
restart_network_interface() {
    dialog --inputbox "Digite o nome da interface de rede a ser reiniciada:" 10 50 2>temp
    interface=$(<temp)
    ifdown "$interface" && ifup "$interface"
    dialog --msgbox "Interface de rede '$interface' reiniciada com sucesso." 10 50
}

# Função para verificar conectividade de rede
check_network_connectivity() {
    dialog --inputbox "Digite o endereço IP ou domínio para verificar a conectividade:" 10 50 2>temp
    target=$(<temp)
    ping -c 4 "$target" > ping_result.txt
    dialog --title "Resultados do Teste de Ping" --textbox ping_result.txt 20 50
    rm ping_result.txt
}

# Função para exibir informações sobre interfaces de rede
show_network_interface_info() {
    ifconfig > network_interfaces.txt
    dialog --title "Informações sobre Interfaces de Rede" --textbox network_interfaces.txt 20 50
    rm network_interfaces.txt
}

# Função para exibir tabela de roteamento
show_routing_table() {
    route > routing_table.txt
    dialog --title "Tabela de Roteamento" --textbox routing_table.txt 20 50
    rm routing_table.txt
}

# Função para exibir estatísticas de interface de rede
show_network_interface_stats() {
    netstat -i > interface_stats.txt
    dialog --title "Estatísticas de Interface de Rede" --textbox interface_stats.txt 20 50
    rm interface_stats.txt
}

# Loop principal do programa
while true; do
    show_menu
    option=$(<temp)
    case $option in
        1) view_network_config ;;
        2) configure_ip_address ;;
        3) configure_default_gateway ;;
        4) configure_dns ;;
        5) restart_network_interface ;;
        6) check_network_connectivity ;;
        7) show_network_interface_info ;;
        8) show_routing_table ;;
        9) show_network_interface_stats ;;
        10) break ;;
    esac
done

# Remover arquivo temporário
rm temp
