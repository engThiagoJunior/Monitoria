#!/bin/bash

# Exemplo de script que utiliza comandos básicos do Linux

# Parte 1: Explorando o Sistema de Arquivos
echo "1. Utilizando o comando pwd:"
pwd

echo "2. Listando o conteúdo do diretório atual:"
ls

# Criando um novo diretório
echo "3. Criando um novo diretório:"
mkdir novo_diretorio

# Criando um novo arquivo vazio
echo "4. Criando um novo arquivo vazio:"
touch novo_arquivo.txt

# Parte 2: Manipulação de Arquivos e Diretórios
# Copiando o arquivo para um novo local
echo "5. Copiando o arquivo para um novo local:"
cp novo_arquivo.txt novo_diretorio/

# Movendo o arquivo para um novo local
echo "6. Movendo o arquivo para um novo local:"
mv novo_arquivo.txt novo_diretorio/

# Excluindo o arquivo
echo "7. Excluindo o arquivo:"
rm novo_diretorio/novo_arquivo.txt

# Excluindo o diretório
echo "8. Excluindo o diretório:"
rmdir novo_diretorio

# Parte 3: Visualização e Manipulação de Arquivos
# Visualizando o conteúdo de um arquivo
echo "9. Visualizando o conteúdo de um arquivo:"
echo "Conteúdo do arquivo exemplo" > arquivo_exemplo.txt
cat arquivo_exemplo.txt

# Visualizando as primeiras linhas de um arquivo
echo "10. Visualizando as primeiras linhas de um arquivo:"
head arquivo_exemplo.txt

# Visualizando as últimas linhas de um arquivo
echo "11. Visualizando as últimas linhas de um arquivo:"
tail arquivo_exemplo.txt

# Contando o número de linhas, palavras e caracteres em um arquivo
echo "12. Contando o número de linhas, palavras e caracteres em um arquivo:"
wc arquivo_exemplo.txt

# Parte 4: Criação e Execução de Shell Scripts
# Criando um novo script
echo "13. Criando um novo script:"
touch meu_script.sh
echo '#!/bin/bash' > meu_script.sh
echo 'echo "Este é meu primeiro script em shell!"' >> meu_script.sh
chmod +x meu_script.sh

# Executando o script
echo "14. Executando o script:"
./meu_script.sh

# Conclusão
echo "Concluído! O script executou todos os comandos previstos no roteiro de laboratório."