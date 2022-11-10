# CHIP-8

Este projeto consiste em um emulador de CHIP-8, criado para o trabalho final da disciplina de Programação III, do semestre 2022/2 da Universidade Federal de Santa Catarina, ministrada pelo professor Gian Ricardo Berkenbrock.

## Regras

Ao abrir o emulador, você se depará com o menu principal. Clique em qualquer um dos jogos para carregá-lo e começar a jogar.

Pressione a tecla `Esc` para pausar/despausar. Enquanto pausado, pode mudar de jogo ou reiniciar o jogo atual simplesmente clicando nele.

Esse é o teclado original que o CHIP-8 espera:
 1 | 2 | 3 | C
---|---|---|---
 4 | 5 | 6 | D
 7 | 8 | 9 | E
 A | 0 | B | F

As teclas foram mapeadas da seguinte forma:
 1 | 2 | 3 | 4
---|---|---|---
 Q | W | E | R
 A | S | D | F
 Z | X | C | V

## Notas do Desenvolvedor

Para adicionar um novo jogo ao emulador, coloque-o na pasta `resources/roms`, seguindo o padrão dos arquivos já existentes. Em seguida, adicione-o na array `GAMELIST` em `include/gui/sfml.h:28`.

Para mudar a velocidade em que a CPU executa as instruções, atualize o valor `STEPS_PER_CYCLE` em `include/gui/sfml.h:19`. Lembrando que o emulador executa 60 ciclos por segundo, logo um valor de 10 levaria a CPU a funcionar em 600 Hz.

Caso queira mudar o mapeamento das teclas ou a escala do display, confira também as outras constantes presentes em `include/gui/sfml.h`.