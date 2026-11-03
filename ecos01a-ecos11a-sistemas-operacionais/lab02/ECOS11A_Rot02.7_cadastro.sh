#!/bin/bash

# Função para exibir o formulário de cadastro
exibir_formulario() {
    dialog --title "Cadastro de Alunos" --form "Preencha os dados do aluno:" 15 50 4 \
        "Nome:" 1 1 "" 1 10 40 0 \
        "Matrícula:" 2 1 "" 2 10 20 0 \
        "Horário:" 3 1 "$(date +"%H:%M:%S")" 3 10 20 0 \
        2> tmp.txt
}

# Função para exibir o resultado do cadastro
exibir_resultado() {
    dialog --title "Cadastro Concluído" --msgbox "Aluno cadastrado com sucesso!" 10 50
}

# Função para salvar os dados do cadastro em um arquivo
salvar_cadastro() {
    cat tmp.txt >> cadastro_alunos.txt
}

# Função principal
principal() {
    exibir_formulario
    if [ $? -eq 0 ]; then
        salvar_cadastro
        exibir_resultado
    fi
}

# Chama a função principal
principal
