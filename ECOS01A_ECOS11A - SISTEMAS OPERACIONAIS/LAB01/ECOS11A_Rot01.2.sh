#!/bin/bash

# Criar arquivo1
echo "Criando arquivo1..."
for ((i=1; i<=20; i++)); do
    echo "Linha $i do arquivo1" >> arquivo1.txt
done

# Criar arquivo2
echo "Criando arquivo2..."
for ((i=1; i<=20; i++)); do
    echo "Linha $i do arquivo2" >> arquivo2.txt
done

# Visualizar o conteúdo de arquivo1
echo "Conteúdo de arquivo1:"
cat arquivo1.txt
echo

# Visualizar o conteúdo de arquivo2
echo "Conteúdo de arquivo2:"
cat arquivo2.txt
echo

# Copiar arquivo1 para arquivo1_copia.txt
echo "Copiando arquivo1 para arquivo1_copia.txt..."
cp arquivo1.txt arquivo1_copia.txt

# Comparar os arquivos arquivo1 e arquivo2
echo "Comparando os arquivos arquivo1 e arquivo2:"
diff arquivo1.txt arquivo2.txt
echo

# Comparar os arquivos arquivo1 e arquivo1_copia
echo "Comparando os arquivos arquivo1 e arquivo1_copia:"
cmp arquivo1.txt arquivo1_copia.txt
echo

# Visualizar as primeiras linhas de arquivo1
echo "Primeiras linhas de arquivo1:"
head arquivo1.txt
echo

# Visualizar as últimas linhas de arquivo2
echo "Últimas linhas de arquivo2:"
tail arquivo2.txt
echo

# Contar o número de linhas, palavras e caracteres de arquivo1
echo "Contagem de linhas, palavras e caracteres de arquivo1:"
wc arquivo1.txt
echo

# Contar o número de linhas, palavras e caracteres de arquivo2
echo "Contagem de linhas, palavras e caracteres de arquivo2:"
wc arquivo2.txt
echo

# Remover os arquivos criados após a execução do script (opcional)
# rm arquivo1.txt arquivo2.txt arquivo1_copia.txt
