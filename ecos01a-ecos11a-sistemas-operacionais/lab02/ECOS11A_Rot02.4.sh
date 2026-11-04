#!/bin/bash

# Função para realizar backup de um diretório
realizar_backup() {
    diretorio=$1
    data=$(date +"%Y-%m-%d")
    tar -czvf backup_$data.tar.gz $diretorio
}

# Chamada da função (passando o diretório como argumento)
realizar_backup /caminho/do/diretorio
