#!/bin/bash

# Criar arquivo1 com um soneto
echo "Criando arquivo1 com soneto..."
cat <<EOF > arquivo1.txt
Soneto de Fidelidade

De tudo, ao meu amor serei atento
Antes, e com tal zelo, e sempre, e tanto
Que mesmo em face do maior encanto
Dele se encante mais meu pensamento.

Quero vivê-lo em cada vão momento
E em seu louvor hei de espalhar meu canto
E rir meu riso e derramar meu pranto
Ao seu pesar ou seu contentamento.

E assim, quando mais tarde me procure
Quem sabe a morte, angústia de quem vive
Quem sabe a solidão, fim de quem ama.

Eu possa me dizer do amor (que tive):
Que não seja imortal, posto que é chama
Mas que seja infinito enquanto dure.
EOF

# Criar arquivo2 com um poema
echo "Criando arquivo2 com poema..."
cat <<EOF > arquivo2.txt
A Máquina do Mundo

E como eu palmilhasse vagamente
Uma estrada de Minas, pedregosa,
E fosse o próprio caminhar uma saudade
Que lembra, e dor, e coisa dolorosa,

E como através de uma moldura
Olhasse um céu sem cor na primavera,
E fosse a sombra de toda a ternura
Minha intenção incerta e passageira,

E como fosse uma ave repentina
A quebrar-se na curva de uma estrada
Que se deixa em silêncio na campina,

Minha alma, de repente, se embriagada
De uma brisa sutil, que me divina
O íntimo sentido da jornada.
EOF

# Realizar busca por palavras nos arquivos
echo "Buscando por 'amor' nos arquivos:"
grep 'amor' arquivo1.txt arquivo2.txt
echo

echo "Buscando por 'céu' nos arquivos:"
grep 'céu' arquivo1.txt arquivo2.txt
echo

# Remover os arquivos criados após a execução do script (opcional)
# rm arquivo1.txt arquivo2.txt
