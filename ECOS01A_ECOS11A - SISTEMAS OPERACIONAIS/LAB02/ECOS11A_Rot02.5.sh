#!/bin/bash

# Função para exibir lista de arquivos e permitir seleção usando dialog
listar_e_selecionar_arquivo() {
    # Obter lista de arquivos no diretório
    arquivos=$(ls)

    # Converter lista de arquivos em array para exibir no dialog
    arquivos_array=()
    for arquivo in $arquivos; do
        arquivos_array+=("$arquivo" "")
    done

    # Exibir lista de arquivos e obter seleção do usuário
    dialog --title "Selecionar Arquivo" --menu "Escolha um arquivo:" 20 50 10 "${arquivos_array[@]}" 2> selecao.txt

    # Ler seleção do arquivo escolhido
    arquivo_selecionado=$(cat selecao.txt)
    echo "Arquivo selecionado: $arquivo_selecionado"
}

# Chamada da função
listar_e_selecionar_arquivo
