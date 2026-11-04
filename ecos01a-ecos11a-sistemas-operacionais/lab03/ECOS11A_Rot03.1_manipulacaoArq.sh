#!/bin/bash

# Função para exibir um menu de opções
show_menu() {
    dialog --clear --backtitle "Manipulação de Arquivos" \
    --title "Menu" \
    --menu "Escolha uma opção:" 15 50 10 \
    1 "Criar arquivo" \
    2 "Criar diretório" \
    3 "Copiar arquivo" \
    4 "Mover arquivo" \
    5 "Renomear arquivo" \
    6 "Apagar arquivo" \
    7 "Apagar diretório" \
    8 "Exibir conteúdo do arquivo" \
    9 "Listar arquivos no diretório" \
    10 "Sair" \
    2>temp
}

# Função para criar um arquivo
create_file() {
    dialog --inputbox "Digite o nome do arquivo a ser criado:" 10 50 2>temp
    filename=$(<temp)
    touch "$filename"
    dialog --msgbox "Arquivo '$filename' criado com sucesso!" 10 50
}

# Função para criar um diretório
create_directory() {
    dialog --inputbox "Digite o nome do diretório a ser criado:" 10 50 2>temp
    dirname=$(<temp)
    mkdir "$dirname"
    dialog --msgbox "Diretório '$dirname' criado com sucesso!" 10 50
}

# Função para copiar um arquivo
copy_file() {
    dialog --inputbox "Digite o nome do arquivo a ser copiado:" 10 50 2>temp
    source=$(<temp)
    dialog --inputbox "Digite o nome do novo arquivo (cópia):" 10 50 2>temp
    destination=$(<temp)
    cp "$source" "$destination"
    dialog --msgbox "Arquivo '$source' copiado para '$destination' com sucesso!" 10 50
}

# Função para mover um arquivo
move_file() {
    dialog --inputbox "Digite o nome do arquivo a ser movido:" 10 50 2>temp
    source=$(<temp)
    dialog --inputbox "Digite o novo destino para o arquivo:" 10 50 2>temp
    destination=$(<temp)
    mv "$source" "$destination"
    dialog --msgbox "Arquivo '$source' movido para '$destination' com sucesso!" 10 50
}

# Função para renomear um arquivo
rename_file() {
    dialog --inputbox "Digite o nome do arquivo a ser renomeado:" 10 50 2>temp
    oldname=$(<temp)
    dialog --inputbox "Digite o novo nome para o arquivo:" 10 50 2>temp
    newname=$(<temp)
    mv "$oldname" "$newname"
    dialog --msgbox "Arquivo '$oldname' renomeado para '$newname' com sucesso!" 10 50
}

# Função para apagar um arquivo
delete_file() {
    dialog --inputbox "Digite o nome do arquivo a ser apagado:" 10 50 2>temp
    filename=$(<temp)
    rm "$filename"
    dialog --msgbox "Arquivo '$filename' apagado com sucesso!" 10 50
}

# Função para apagar um diretório
delete_directory() {
    dialog --inputbox "Digite o nome do diretório a ser apagado:" 10 50 2>temp
    dirname=$(<temp)
    rm -r "$dirname"
    dialog --msgbox "Diretório '$dirname' apagado com sucesso!" 10 50
}

# Função para exibir o conteúdo de um arquivo
display_file_content() {
    dialog --inputbox "Digite o nome do arquivo a ser exibido:" 10 50 2>temp
    filename=$(<temp)
    content=$(cat "$filename")
    dialog --title "Conteúdo de $filename" --msgbox "$content" 20 50
}

# Função para listar arquivos no diretório
list_files() {
    files=$(ls)
    dialog --title "Arquivos no Diretório" --msgbox "$files" 20 50
}

# Loop principal do programa
while true; do
    show_menu
    option=$(<temp)
    case $option in
        1) create_file ;;
        2) create_directory ;;
        3) copy_file ;;
        4) move_file ;;
        5) rename_file ;;
        6) delete_file ;;
        7) delete_directory ;;
        8) display_file_content ;;
        9) list_files ;;
        10) break ;;
    esac
done

# Remover arquivo temporário
rm temp
