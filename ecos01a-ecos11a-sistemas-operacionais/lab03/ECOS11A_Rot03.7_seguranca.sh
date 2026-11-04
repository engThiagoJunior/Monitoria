#!/bin/bash

# Função para exibir um menu de opções
show_menu() {
    dialog --clear --backtitle "Segurança e Permissões" \
    --title "Menu" \
    --menu "Escolha uma opção:" 15 50 10 \
    1 "Visualizar permissões de arquivos" \
    2 "Alterar permissões de um arquivo" \
    3 "Alterar proprietário de um arquivo" \
    4 "Alterar grupo de um arquivo" \
    5 "Visualizar permissões de um diretório" \
    6 "Alterar permissões de um diretório e seus conteúdos" \
    7 "Verificar integridade de arquivos" \
    8 "Habilitar firewall" \
    9 "Configurar políticas de segurança" \
    10 "Sair" \
    2>temp
}

# Função para visualizar permissões de arquivos
view_file_permissions() {
    dialog --inputbox "Digite o caminho do arquivo:" 10 50 2>temp
    file_path=$(<temp)
    ls -l "$file_path" > temp
    dialog --title "Permissões do arquivo $file_path" --textbox temp 20 80
}

# Função para alterar permissões de um arquivo
change_file_permissions() {
    dialog --inputbox "Digite o caminho do arquivo:" 10 50 2>temp
    file_path=$(<temp)
    dialog --inputbox "Digite as novas permissões (em formato octal):" 10 50 2>temp
    permissions=$(<temp)
    chmod "$permissions" "$file_path"
    dialog --msgbox "Permissões do arquivo $file_path alteradas para $permissions." 10 50
}

# Função para alterar proprietário de um arquivo
change_file_owner() {
    dialog --inputbox "Digite o caminho do arquivo:" 10 50 2>temp
    file_path=$(<temp)
    dialog --inputbox "Digite o novo proprietário:" 10 50 2>temp
    owner=$(<temp)
    chown "$owner" "$file_path"
    dialog --msgbox "Proprietário do arquivo $file_path alterado para $owner." 10 50
}

# Função para alterar grupo de um arquivo
change_file_group() {
    dialog --inputbox "Digite o caminho do arquivo:" 10 50 2>temp
    file_path=$(<temp)
    dialog --inputbox "Digite o novo grupo:" 10 50 2>temp
    group=$(<temp)
    chgrp "$group" "$file_path"
    dialog --msgbox "Grupo do arquivo $file_path alterado para $group." 10 50
}

# Função para visualizar permissões de um diretório
view_directory_permissions() {
    dialog --inputbox "Digite o caminho do diretório:" 10 50 2>temp
    dir_path=$(<temp)
    ls -ld "$dir_path" > temp
    dialog --title "Permissões do diretório $dir_path" --textbox temp 20 80
}

# Função para alterar permissões de um diretório e seus conteúdos
change_directory_permissions() {
    dialog --inputbox "Digite o caminho do diretório:" 10 50 2>temp
    dir_path=$(<temp)
    dialog --inputbox "Digite as novas permissões (em formato octal):" 10 50 2>temp
    permissions=$(<temp)
    chmod -R "$permissions" "$dir_path"
    dialog --msgbox "Permissões do diretório $dir_path e seus conteúdos alteradas para $permissions." 10 50
}

# Função para verificar integridade de arquivos
check_file_integrity() {
    dialog --inputbox "Digite o caminho do arquivo para verificação:" 10 50 2>temp
    file_path=$(<temp)
    md5sum "$file_path" > temp
    dialog --title "Integridade do arquivo $file_path" --textbox temp 20 80
}

# Função para habilitar firewall
enable_firewall() {
    systemctl start firewalld
    dialog --msgbox "Firewall habilitado com sucesso." 10 50
}

# Função para configurar políticas de segurança
configure_security_policies() {
    dialog --msgbox "Funcionalidade não implementada." 10 50
}

# Loop principal do programa
while true; do
    show_menu
    option=$(<temp)
    case $option in
        1) view_file_permissions ;;
        2) change_file_permissions ;;
        3) change_file_owner ;;
        4) change_file_group ;;
        5) view_directory_permissions ;;
        6) change_directory_permissions ;;
        7) check_file_integrity ;;
        8) enable_firewall ;;
        9) configure_security_policies ;;
        10) break ;;
    esac
done

# Remover arquivo temporário
rm temp
