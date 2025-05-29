# Jogo-Girotto-As-Chaves-do-Esquecimetno

A ideia do jogo é simples, porém extremamente trabalhosa: em cada fase, o jogador precisa encontrar uma chave, interagir com ela para abrir uma porta, e então atravessar essa porta para ir para a próxima fase. No entanto, o caminho até a chave nem sempre é fácil. Existem obstáculos como paredes, espinhos, monstros e até botões misteriosos. O jogador precisa prestar atenção em tudo e usar os comandos corretos para vencer os desafios.

Os controles são bem intuitivos: usamos W, A, S, D para mover o personagem (cima, esquerda, baixo e direita, respectivamente) e interagir com o que estiver embaixo do jogador. Essa interação é usada para coletar a chave, apertar botões ou ativar certos elementos do mapa.

No mapa do jogo, usamos símbolos para representar os diferentes elementos. O jogador é representado pelo símbolo &. Paredes são representadas por * e bloqueiam a movimentação. A chave que precisa ser coletada aparece como @. A porta trancada aparece como D e, ao pegar a chave, ela se transforma em uma porta aberta. Existem também espinhos (#) que fazem o jogador reiniciar a fase caso encoste neles — se isso acontecer três vezes, o jogo volta ao menu principal. Além disso, há botões (O) que podem ser ativados quando o jogador está em cima deles, e dependendo da fase eles têm efeitos diferentes, como abrir passagens secretas ou liberar inimigos.

Outro elemento interessante são os teleportes, simbolizados por >. Eles sempre vêm em pares e, ao pisar em um, o jogador é transportado automaticamente para o outro ponto do mapa. Já os monstros aparecem em duas versões: o monstro nível 1 (X), que se move aleatoriamente em uma das quatro direções, e o monstro nível 2 (V), que tem uma lógica simples para seguir o jogador. Se qualquer um desses monstros encostar no jogador, a fase também reinicia.

O jogo começa com um menu principal com três opções: iniciar jogo, ver os créditos ou sair. Ao escolher iniciar, o jogador entra na fase 1. A cada fase superada, o jogo carrega a próxima automaticamente. Quando a terceira fase é concluída, o jogador recebe uma mensagem de parabéns e retorna ao menu.

Para rodar o jogo, é necessário ter um compilador C. Nós usamos o GCC. Em sistemas Linux ou macOS, basta compilar com o comando gcc jogo.c -o jogo e executar com ./jogo. No Windows, o comando seria gcc jogo.c -o jogo.exe seguido de jogo.exe.

Esse projeto foi uma grande oportunidade de aprendizado. Conseguimos aplicar conceitos como a manipulação de matrizes bidimensionais para criar os mapas, a organização do código em funções, o uso de bibliotecas como conio.h para capturar entradas do teclado sem precisar apertar Enter, e criamos lógicas para movimentação, interação, colisões e sistema de fases. Também aprendemos muito sobre planejamento e divisão de tarefas em dupla.

Mesmo sendo um projeto aparentemente """""simples""""", ele nos ensinou bastante sobre como pensar em lógica de programação, como resolver problemas e como transformar uma ideia em código. Tivemos bastante dificuldade em algumas partes, como fazer a movimentação dos monstros, lidar com teletransporte e criar o sistema de reinício de fases, mas com pesquisa, ajuda de colegas e muita tentativa e erro, conseguimos resolver.

Ajuda com a I.A.: No início, tentamos fazer tudo sem utilizar inteligência artificial, mas, com o tempo, tornou-se difícil encaixar as lógicas ideais sozinhos, ainda mais considerando que nunca tínhamos feito um projeto tão complexo como este. Por isso, pedimos ajuda principalmente para entender como aplicar as lógicas corretas no código e fazer com que tudo funcionasse, como, por exemplo, a movimentação dos NPCs no mapa e o funcionamento do teletransporte. Em compensação, aprendemos muitas coisas novas durante o processo.

Ficamos muito orgulhosos do resultado final. Claro que há muitas melhorias possíveis, como adicionar uma história, criar mais fases, deixar os inimigos mais inteligentes, colocar sons ou até pensar em uma interface gráfica futuramente. Mas, para um primeiro projeto de programação, foi uma experiência muito valiosa.

Agradecemos por jogar e esperamos que você se divirta tanto quanto a gente se divertiu fazendo(ou talvez tenha sentindo um poucooooooooooooooo de dor de cabeça fazendoa dsdakdkdkad)!

Jogo desenvolvido por: Artur Lobato e Matheus Lima.
