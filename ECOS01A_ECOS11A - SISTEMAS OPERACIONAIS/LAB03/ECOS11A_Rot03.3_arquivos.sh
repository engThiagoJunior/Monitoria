#!/bin/bash

# Função para exibir um menu de opções
show_menu() {
    dialog --clear --backtitle "Gerenciamento de Arquivos e Diretórios" \
    --title "Menu" \
    --menu "Escolha uma opção:" 15 50 10 \
    1 "Listar arquivos e diretórios" \
    2 "Criar diretório" \
    3 "Criar arquivo" \
    4 "Copiar arquivo ou diretório" \
    5 "Mover arquivo ou diretório" \
    6 "Renomear arquivo ou diretório" \
    7 "Excluir arquivo ou diretório" \
    8 "Exibir conteúdo de arquivo" \
    9 "Alterar permissões de arquivo ou diretório" \
    10 "Sair" \
    2>temp
}

# Função para listar arquivos e diretórios
list_files_and_directories() {
    files=$(ls -l)
    dialog --title "Lista de Arquivos e Diretórios" --msgbox "$files" 20 50
}

# Função para criar um diretório
create_directory() {
    dialog --inputbox "Digite o nome do diretório a ser criado:" 10 50 2>temp
    dirname=$(<temp)
    mkdir "$dirname"
    dialog --msgbox "Diretório '$dirname' criado com sucesso!" 10 50
}

# Função para criar um arquivo
create_file() {
    dialog --inputbox "Digite o nome do arquivo a ser criado:" 10 50 2>temp
    filename=$(<temp)
    touch "$filename"
    dialog --msgbox "Arquivo '$filename' criado com sucesso!" 10 50
}

# Função para copiar arquivo ou diretório
copy_file_or_directory() {
    dialog --inputbox "Digite o caminho do arquivo ou diretório de origem:" 10 50 2>temp
    source=$(<temp)
    dialog --inputbox "Digite o caminho do diretório de destino:" 10 50 2>temp
    destination=$(<temp)
    cp -r "$source" "$destination"
    dialog --msgbox "Arquivo ou diretório copiado com sucesso para '$destination'." 10 50
}

# Função para mover arquivo ou diretório
move_file_or_directory() {
    dialog --inputbox "Digite o caminho do arquivo ou diretório de origem:" 10 50 2>temp
    source=$(<temp)
    dialog --inputbox "Digite o caminho do diretório de destino:" 10 50 2>temp
    destination=$(<temp)
    mv "$source" "$destination"
    dialog --msgbox "Arquivo ou diretório movido com sucesso para '$destination'." 10 50
}

# Função para renomear arquivo ou diretório
rename_file_or_directory() {
    dialog --inputbox "Digite o nome do arquivo ou diretório antigo:" 10 50 2>temp
    oldname=$(<temp)
    dialog --inputbox "Digite o novo nome para o arquivo ou diretório:" 10 50 2>temp
    newname=$(<temp)
    mv "$oldname" "$newname"
    dialog --msgbox "Arquivo ou diretório renomeado para '$newname' com sucesso!" 10 50
}

# Função para excluir arquivo ou diretório
delete_file_or_directory() {
    dialog --inputbox "Digite o caminho do arquivo ou diretório a ser excluído:" 10 50 2>temp
    target=$(<temp)
    rm -rf "$target"
    dialog --msgbox "Arquivo ou diretório '$target' excluído com sucesso!" 10 50
}

# Função para exibir o conteúdo de um arquivo
display_file_content() {
    dialog --inputbox "Digite o nome do arquivo a ser exibido:" 10 50 2>temp
    filename=$(<temp)
    content=$(cat "$filename")
    dialog --title "Conteúdo de $filename" --msgbox "$content" 20 50
}

# Função para alterar permissões de arquivo ou diretório
change_permissions() {
    dialog --inputbox "Digite o caminho do arquivo ou diretório:" 10 50 2>temp
    target=$(<temp)
    dialog --inputbox "Digite as novas permissões (formato octal):" 10 50 2>temp
    permissions=$(<temp)
    chmod "$permissions" "$target"
    dialog --msgbox "Permissões alteradas com sucesso para '$permissions'." 10 50
}

# Loop principal do programa
while true; do
    show_menu
    option=$(<temp)
    case $option in
        1) list_files_and_directories ;;
        2) create_directory ;;
        3) create_file ;;
        4) copy_file_or_directory ;;
        5) move_file_or_directory ;;
        6) rename_file_or_directory ;;
        7) delete_file_or_directory ;;
        8) display_file_content ;;
        9) change_permissions ;;
        10) break ;;
    esac
done

# Remover arquivo temporário
rm temp
