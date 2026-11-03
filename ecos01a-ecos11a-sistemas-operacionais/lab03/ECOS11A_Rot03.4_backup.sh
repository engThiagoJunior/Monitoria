#!/bin/bash

# Função para exibir um menu de opções
show_menu() {
    dialog --clear --backtitle "Backup e Restauração" \
    --title "Menu" \
    --menu "Escolha uma opção:" 15 50 10 \
    1 "Criar backup de diretório" \
    2 "Restaurar backup de diretório" \
    3 "Comprimir diretório" \
    4 "Descomprimir arquivo" \
    5 "Sincronizar diretórios" \
    6 "Criar imagem de disco" \
    7 "Montar imagem de disco" \
    8 "Desmontar imagem de disco" \
    9 "Criar backup do MBR" \
    10 "Restaurar backup do MBR" \
    11 "Sair" \
    2>temp
}

# Função para criar backup de diretório
backup_directory() {
    dialog --inputbox "Digite o caminho do diretório a ser copiado:" 10 50 2>temp
    source_dir=$(<temp)
    dialog --inputbox "Digite o caminho do diretório de destino do backup:" 10 50 2>temp
    destination_dir=$(<temp)
    cp -r "$source_dir" "$destination_dir"
    dialog --msgbox "Backup do diretório '$source_dir' criado com sucesso em '$destination_dir'." 10 50
}

# Função para restaurar backup de diretório
restore_backup() {
    dialog --inputbox "Digite o caminho do diretório de backup:" 10 50 2>temp
    backup_dir=$(<temp)
    dialog --inputbox "Digite o caminho do diretório de destino da restauração:" 10 50 2>temp
    destination_dir=$(<temp)
    cp -r "$backup_dir" "$destination_dir"
    dialog --msgbox "Diretório restaurado com sucesso em '$destination_dir'." 10 50
}

# Função para comprimir diretório
compress_directory() {
    dialog --inputbox "Digite o caminho do diretório a ser comprimido:" 10 50 2>temp
    source_dir=$(<temp)
    dialog --inputbox "Digite o nome do arquivo de saída (com extensão .tar.gz):" 10 50 2>temp
    output_file=$(<temp)
    tar -czvf "$output_file" "$source_dir"
    dialog --msgbox "Diretório '$source_dir' comprimido com sucesso em '$output_file'." 10 50
}

# Função para descomprimir arquivo
decompress_file() {
    dialog --inputbox "Digite o caminho do arquivo a ser descomprimido:" 10 50 2>temp
    input_file=$(<temp)
    dialog --inputbox "Digite o caminho do diretório de destino da descompressão:" 10 50 2>temp
    output_dir=$(<temp)
    tar -xzvf "$input_file" -C "$output_dir"
    dialog --msgbox "Arquivo '$input_file' descomprimido com sucesso em '$output_dir'." 10 50
}

# Função para sincronizar diretórios
sync_directories() {
    dialog --inputbox "Digite o caminho do diretório de origem:" 10 50 2>temp
    source_dir=$(<temp)
    dialog --inputbox "Digite o caminho do diretório de destino:" 10 50 2>temp
    destination_dir=$(<temp)
    rsync -avh "$source_dir" "$destination_dir"
    dialog --msgbox "Diretórios sincronizados com sucesso." 10 50
}

# Função para criar imagem de disco
create_disk_image() {
    dialog --inputbox "Digite o caminho do dispositivo de bloco (ex: /dev/sda):" 10 50 2>temp
    block_device=$(<temp)
    dialog --inputbox "Digite o caminho do arquivo de imagem a ser criado:" 10 50 2>temp
    output_file=$(<temp)
    dd if="$block_device" of="$output_file" bs=4M
    dialog --msgbox "Imagem de disco criada com sucesso em '$output_file'." 10 50
}

# Função para montar imagem de disco
mount_disk_image() {
    dialog --inputbox "Digite o caminho do arquivo de imagem:" 10 50 2>temp
    disk_image=$(<temp)
    dialog --inputbox "Digite o caminho do diretório de montagem:" 10 50 2>temp
    mount_point=$(<temp)
    mkdir -p "$mount_point"
    mount "$disk_image" "$mount_point"
    dialog --msgbox "Imagem de disco '$disk_image' montada com sucesso em '$mount_point'." 10 50
}

# Função para desmontar imagem de disco
unmount_disk_image() {
    dialog --inputbox "Digite o caminho do diretório de montagem:" 10 50 2>temp
    mount_point=$(<temp)
    umount "$mount_point"
    dialog --msgbox "Imagem de disco desmontada com sucesso." 10 50
}

# Função para criar backup do MBR
backup_mbr() {
    dialog --inputbox "Digite o caminho do dispositivo de bloco (ex: /dev/sda):" 10 50 2>temp
    block_device=$(<temp)
    dd if="$block_device" of=mbr_backup.img bs=512 count=1
    dialog --msgbox "Backup do MBR criado com sucesso em 'mbr_backup.img'." 10 50
}

# Função para restaurar backup do MBR
restore_mbr() {
    dialog --inputbox "Digite o caminho do arquivo de backup do MBR:" 10 50 2>temp
    backup_file=$(<temp)
    dialog --inputbox "Digite o caminho do dispositivo de bloco (ex: /dev/sda):" 10 50 2>temp
    block_device=$(<temp)
    dd if="$backup_file" of="$block_device" bs=512 count=1
    dialog --msgbox "Backup do MBR restaurado com sucesso." 10 50
}

# Loop principal do programa
while true; do
    show_menu
    option=$(<temp)
    case $option in
        1) backup_directory ;;
         2) restore_backup ;;
        3) compress_directory ;;
        4) decompress_file ;;
        5) sync_directories ;;
        6) create_disk_image ;;
        7) mount_disk_image ;;
        8) unmount_disk_image ;;
        9) backup_mbr ;;
        10) restore_mbr ;;
        11) break ;;
    esac
done

# Remover arquivo temporário
rm temp
