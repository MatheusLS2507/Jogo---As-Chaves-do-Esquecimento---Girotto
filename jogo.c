#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

int main() {
    // Variáveis do jogo
    int opcao;
    int px, py; // Posição do jogador
    int chave_pegou, botao1_ativado, botao2_ativado;
    int npc_visivel = 1; // Controla se o NPC especial está visível
    int espinho_px = -1, espinho_py = -1; // Posição do espinho criado pelo botão 1
    char tecla;
    int fase = 1; // 1 = Vila, 2 = Fase1, 3 = Fase2
    int mx, my; // Posição do monstro X (fase 1 e 2)
    int vx, vy; // Posição do monstro V (apenas fase 2)
    int i, j;
    int tentativas = 0; // Contador de tentativas para cada fase
    
    // Mapas
    char vila[10][10] = {
        {'*','*','*','*','*','*','*','*','*','*'},
        {'*','.','.','P','>','*','>','.','O','*'},
        {'*','.','.','.','.','*','.','.','.','*'},
        {'*','.','.','.','.','*','.','.','.','*'},
        {'*','.','.','.','.','*','.','.','.','*'},
        {'*','.','#','#','.','*','*','*','*','*'},
        {'*','.','#','#','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','*'},
        {'*','*','*','*','*','*','*','D','*','*'}
    };
    
    char fase1[10][10] = {
        {'*','*','*','*','*','*','*','*','*','*'},
        {'*','.','.','O','.','.','.','.','P','*'},
        {'*','*','*','*','*','.','.','.','.','*'},
        {'*','.','.','.','*','.','.','.','.','*'},
        {'*','.','.','.','*','.','.','.','.','*'},
        {'*','.','.','.','*','.','.','.','.','*'},
        {'*','.','.','.','*','.','.','.','.','*'},
        {'*','.','.','.','*','.','.','.','.','*'},
        {'*','.','@','.','*','.','.','.','.','*'},
        {'*','*','*','*','*','*','*','D','*','*'}
    };

    char fase2[20][20] = {
        {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
        {'*','O','#','#','O','#','#','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','#','#','.','#','#','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','#','#','.','#','#','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','*','*','*','*','*','*','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','*','.','.','V','.','.','*'},
        {'D','.','.','.','.','.','.','.','.','.','.','.','.','*','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','>','*','>','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','*','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','*','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','X','.','.','*','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','*','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','*','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','*','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','*','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','*','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','*','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','*','.','.','.','.','.','*'},
        {'*','@','.','.','.','.','.','.','.','.','.','.','.','*','.','.','.','.','.','*'},
        {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','D','*','*'}
    };

    // Inicializa gerador de números aleatórios
    srand(time(NULL));
    
    // Menu principal
    while(1) {
        system("cls");
        printf("===============================================================================\n");
        printf("                 AS CHAVES DO ESQUECIMENTO!                  \n");
        printf("===============================================================================\n");
        printf("\n");
        printf("1 - Iniciar Jogo\n");
        printf("2 - Creditos\n");
        printf("3 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        if(opcao == 3) break;
        
        if(opcao == 2) {
            system("cls");
            printf("CREDITOS\n");
            printf("Jogo desenvolvido por ARTUR LOBATO E MATHEUS LIMA\n");
            printf("Pressione qualquer tecla para voltar...");
            getch();
            continue;
        }
        
        if(opcao == 1) {
            // Inicializa a vila
            fase = 1;
            px = 1; py = 1;
            chave_pegou = 0;
            botao1_ativado = 0;
            botao2_ativado = 0;
            npc_visivel = 1;
            espinho_px = -1; espinho_py = -1;
            tentativas = 0;
            
            while(1) {
                system("cls");
                
                // Desenha o mapa atual
                if(fase == 1) {
                    for(i = 0; i < 10; i++) {
                        for(j = 0; j < 10; j++) {
                            if(i == px && j == py) printf("& ");
                            else if(i == 4 && j == 8 && botao1_ativado) printf("@ ");
                            else if(i == 1 && j == 8 && !botao1_ativado) printf("O ");
                            else if(i == 9 && j == 7) printf(chave_pegou ? "= " : "D ");
                            else printf("%c ", vila[i][j]);
                        }
                        printf("\n");
                    }
                } 
                else if(fase == 2) {
                    for(i = 0; i < 10; i++) {
                        for(j = 0; j < 10; j++) {
                            if(i == px && j == py) printf("& ");
                            else if(i == mx && j == my) printf("X ");
                            else if(i == 8 && j == 2 && !chave_pegou) printf("@ ");
                            else if(i == 9 && j == 7) printf(chave_pegou ? "= " : "D ");
                            else if(i == 1 && j == 3 && !botao1_ativado) printf("O ");
                            else if(i == 1 && j == 1 && botao1_ativado) printf("> ");
                            else if(i == 3 && j == 1 && botao1_ativado) printf("> ");
                            else printf("%c ", fase1[i][j]);
                        }
                        printf("\n");
                    }
                }
                else if(fase == 3) {
                    for(i = 0; i < 20; i++) {
                        for(j = 0; j < 20; j++) {
                            if(i == px && j == py) printf("& ");
                            else if(i == vx && j == vy) printf("V ");
                            else if(i == mx && j == my) printf("X ");
                            else if(i == 18 && j == 0 && !chave_pegou && botao2_ativado) printf("@ ");
                            else if(i == 6 && j == 0) printf(botao2_ativado ? "= " : "D ");
                            else if(i == 1 && j == 1 && !botao1_ativado) printf("O ");
                            else if(i == 1 && j == 4 && !botao2_ativado) printf("O ");
                            else if(espinho_px != -1 && i == espinho_px && j == espinho_py && botao1_ativado) printf("# ");
                            else if(i == 7 && j == 12) printf("> ");
                            else if(i == 7 && j == 14) printf("> ");
                            else if(!botao2_ativado && (
                                   (i == 18 && j == 1) ||
                                   (i == 17 && j == 0) ||
                                   (i == 19 && j == 0) ||
                                   (i == 15 && j == 0) ||
                                   (i == 16 && j == 0) || 
                                   (i == 19 && j == 1) || 
                                   (i == 19 && j == 2) || 
                                   (i == 19 && j == 3))) 
                                printf("# ");
                            else if(i == 5 && j == 1 && npc_visivel && botao2_ativado) 
                                printf("P ");
                            else printf("%c ", fase2[i][j]);
                        }
                        printf("\n");
                    }
                }
                
                printf("\nChave: %s\n", chave_pegou ? "SIM" : "NAO");
                printf("Use WASD para mover, E para interagir, Q para sair\n");
                printf("Tentativas: %d/3\n", tentativas);
                
                // Código para passagem entre fases
                if(fase == 1 && px == 9 && py == 7 && chave_pegou) {
                    printf("\nPassando para a proxima fase...\n");
                    getch();
                    
                    // Inicializa fase1
                    fase = 2;
                    px = 1; py = 8;
                    chave_pegou = 0;
                    botao1_ativado = 0;
                    tentativas = 0;
                    mx = 5; my = 5;
                    continue;
                }
                else if(fase == 2 && px == 9 && py == 7 && chave_pegou) {
                    printf("\nPassando para a fase 2...\n");
                    getch();
                    
                    // Inicializa fase2
                    fase = 3;
                    px = 2; py = 18;
                    chave_pegou = 0;
                    botao1_ativado = 0;
                    botao2_ativado = 0;
                    npc_visivel = 1;
                    espinho_px = -1; espinho_py = -1;
                    tentativas = 0;
                    mx = 10; my = 10;
                    vx = 5; vy = 16;
                    continue;
                }
                else if(fase == 3 && px == 19 && py == 17 && chave_pegou) {
                    printf("\nParabens! Voce completou o jogo!\n");
                    getch();
                    break;
                }
                
                // Movimento dos monstros
                if(fase >= 2) {
                    // Monstro X (movimento aleatório)
                    int dir = rand() % 4;
                    int novo_mx = mx, novo_my = my;
                    
                    if(dir == 0) novo_mx--;
                    else if(dir == 1) novo_mx++;
                    else if(dir == 2) novo_my--;
                    else if(dir == 3) novo_my++;
                    
                    // Verifica se pode mover
                    if(fase == 2) {
                        if(novo_mx >= 0 && novo_mx < 10 && novo_my >= 0 && novo_my < 10) {
                            if(fase1[novo_mx][novo_my] != '*' && 
                               !(novo_mx == px && novo_my == py)) {
                                mx = novo_mx;
                                my = novo_my;
                            }
                        }
                    } else if(fase == 3) {
                        if(novo_mx >= 0 && novo_mx < 20 && novo_my >= 0 && novo_my < 20) {
                            if(fase2[novo_mx][novo_my] != '*' && 
                               !(novo_mx == px && novo_my == py)) {
                                mx = novo_mx;
                                my = novo_my;
                            }
                        }
                    }
                }
                
                if(fase == 3) {
                    // Monstro V (persegue jogador)
                    if(px >= 13 && px <= 19 && py >= 13 && py <= 19) {
                        int novo_vx = vx, novo_vy = vy;
                        
                        if(px < vx && fase2[vx-1][vy] != '*') novo_vx--;
                        else if(px > vx && fase2[vx+1][vy] != '*') novo_vx++;
                        else if(py < vy && fase2[vx][vy-1] != '*') novo_vy--;
                        else if(py > vy && fase2[vx][vy+1] != '*') novo_vy++;
                        
                        if(novo_vx >= 0 && novo_vx < 20 && novo_vy >= 0 && novo_vy < 20) {
                            if(fase2[novo_vx][novo_vy] != '*' && 
                               !(novo_vx == px && novo_vy == py)) {
                                vx = novo_vx;
                                vy = novo_vy;
                            }
                        }
                    }
                }
                
                // Verificação de colisão com monstros
                if((fase == 2 && px == mx && py == my) || 
                   (fase == 3 && (px == mx && py == my || px == vx && py == vy))) {
                    printf("\nVoce foi pego pelo monstro! Fase reiniciada.\n");
                    tentativas++;
                    
                    if(tentativas >= 3) {
                        printf("\nVoce perdeu! Voltando ao menu principal.\n");
                        getch();
                        break;
                    }
                    
                    if(fase == 2) {
                        px = 1; py = 8;
                        mx = 5; my = 5;
                        chave_pegou = 0;
                        botao1_ativado = 0;
                    } else {
                        px = 2; py = 18;
                        mx = 10; my = 10;
                        vx = 5; vy = 16;
                        chave_pegou = 0;
                        botao1_ativado = 0;
                        botao2_ativado = 0;
                        npc_visivel = 1;
                        espinho_px = -1; espinho_py = -1;
                    }
                    getch();
                    continue;
                }
                
                tecla = getch();
                
                if(tecla == 'q' || tecla == 'Q') break;
                
                // Interação com E
                if(tecla == 'e' || tecla == 'E') {
                    // NPC normal
                    if((fase == 1 && px == 1 && py == 3) || 
                       (fase == 2 && px == 1 && py == 8) ||
                       (fase == 3 && px == 2 && py == 18)) {
                        system("cls");
                        if(fase == 1) printf("NPC: Ative o botao (O) para revelar a chave (@)!\n");
                        else if(fase == 2) printf("NPC: O botao (O) cria teleportes (>)!\n");
                        else printf("NPC: O primeiro botao cria um espinho atras de voce, o segundo abre a porta (D) e remove os espinhos!\n");
                        printf("Pressione ENTER para continuar...");
                        while(getch() != 13);
                    }
                    // Botão na Vila (gera chave)
                    else if(fase == 1 && px == 1 && py == 8 && !botao1_ativado) {
                        botao1_ativado = 1;
                        printf("\nBotao ativado! A chave apareceu!\n");
                        getch();
                    }
                    // Botão na Fase1 (gera teleportes)
                    else if(fase == 2 && px == 1 && py == 3 && !botao1_ativado) {
                        botao1_ativado = 1;
                        printf("\nBotao ativado! Teleportes apareceram!\n");
                        getch();
                    }
                    // Primeiro botão na Fase2 (gera espinho atrás do jogador)
                    else if(fase == 3 && px == 1 && py == 1 && !botao1_ativado) {
                        botao1_ativado = 1;
                        
                        // Determina a posição do espinho atrás do jogador
                        if(py > 1 && fase2[px][py-1] != '*') {
                            espinho_px = px;
                            espinho_py = py-1;
                        }
                        else if(px < 19 && fase2[px+1][py] != '*') {
                            espinho_px = px+1;
                            espinho_py = py;
                        }
                        else if(py < 19 && fase2[px][py+1] != '*') {
                            espinho_px = px;
                            espinho_py = py+1;
                        }
                        else if(px > 1 && fase2[px-1][py] != '*') {
                            espinho_px = px-1;
                            espinho_py = py;
                        }
                        
                        printf("\nBotao ativado! Um espinho apareceu atras de voce!\n");
                        getch();
                    }
                    // Segundo botão na Fase2 (abre porta da esquerda e remove espinhos que cercam a chave)
                    else if(fase == 3 && px == 1 && py == 4 && !botao2_ativado) {
                        botao2_ativado = 1;
                        printf("\nBotao ativado! A porta da esquerda foi aberta e os espinhos que cercam a chave foram removidos!\n");
                        
                        // Mostra diálogo do NPC especial
                        system("cls");
                        printf("NPC: Aqui e a sala do tesouro!\n");
                        printf("Pressione ENTER para continuar...");
                        while(getch() != 13);
                        npc_visivel = 0;
                    }
                    // Teleporte na Vila
                    else if(fase == 1 && ((px == 1 && py == 4) || (px == 1 && py == 6))) {
                        if(px == 1 && py == 4) px = 1, py = 6;
                        else px = 1, py = 4;
                        printf("\nTeleportado!\n");
                        getch();
                    }
                    // Teleporte na Fase1
                    else if(fase == 2 && botao1_ativado && ((px == 1 && py == 1) || (px == 3 && py == 1))) {
                        if(px == 1 && py == 1) px = 3, py = 1;
                        else px = 1, py = 1;
                        printf("\nTeleportado!\n");
                        getch();
                    }
                    // Teleporte na Fase2
                    else if(fase == 3 && ((px == 7 && py == 12) || (px == 7 && py == 14))) {
                        if(px == 7 && py == 12) px = 7, py = 14;
                        else px = 7, py = 12;
                        printf("\nTeleportado!\n");
                        getch();
                    }
                    // Pegar chave
                    else if((fase == 1 && px == 4 && py == 8 && botao1_ativado && !chave_pegou) ||
                            (fase == 2 && px == 8 && py == 2 && !chave_pegou) ||
                            (fase == 3 && px == 18 && py == 0 && !chave_pegou && botao2_ativado)) {
                        chave_pegou = 1;
                        printf("\nChave coletada! A porta esta aberta!\n");
                        getch();
                    }
                }
                // Movimentação
                else {
                    int novo_px = px, novo_py = py;
                    
                    if(tecla == 'w' || tecla == 'W') novo_px--;
                    else if(tecla == 's' || tecla == 'S') novo_px++;
                    else if(tecla == 'a' || tecla == 'A') novo_py--;
                    else if(tecla == 'd' || tecla == 'D') novo_py++;
                    
                    // Verifica colisões
                    if((fase == 1 && novo_px >= 0 && novo_px < 10 && novo_py >= 0 && novo_py < 10) ||
                       (fase == 2 && novo_px >= 0 && novo_px < 10 && novo_py >= 0 && novo_py < 10) ||
                       (fase == 3 && novo_px >= 0 && novo_px < 20 && novo_py >= 0 && novo_py < 20)) {
                        
                        char celula;
                        if(fase == 1) celula = vila[novo_px][novo_py];
                        else if(fase == 2) celula = fase1[novo_px][novo_py];
                        else celula = fase2[novo_px][novo_py];
                        
                        // Verifica espinho criado pelo botão 1
                        if(fase == 3 && botao1_ativado && novo_px == espinho_px && novo_py == espinho_py) {
                            printf("\nVoce pisou em um espinho! Fase reiniciada.\n");
                            tentativas++;
                            
                            if(tentativas >= 3) {
                                printf("\nVoce perdeu! Voltando ao menu principal.\n");
                                getch();
                                break;
                            }
                            
                            px = 2; py = 18;
                            mx = 10; my = 10;
                            vx = 5; vy = 16;
                            chave_pegou = 0;
                            botao1_ativado = 0;
                            botao2_ativado = 0;
                            npc_visivel = 1;
                            espinho_px = -1; espinho_py = -1;
                            getch();
                            continue;
                        }
                        
                        // Verifica espinhos ao redor da chave (se o botão 2 não estiver ativado)
                        if(fase == 3 && !botao2_ativado && (
                           (novo_px == 18 && novo_py == 1) ||
                           (novo_px == 17 && novo_py == 0) ||
                           (novo_px == 15 && novo_py == 0) ||
                           (novo_px == 16 && novo_py == 0) || 
                           (novo_px == 19 && novo_py == 1) || 
                           (novo_px == 19 && novo_py == 2) || 
                           (novo_px == 19 && novo_py == 3))) {
                            
                            printf("\nVoce pisou em um espinho! Fase reiniciada.\n");
                            tentativas++;
                            
                            if(tentativas >= 3) {
                                printf("\nVoce perdeu! Voltando ao menu principal.\n");
                                getch();
                                break;
                            }
                            
                            px = 2; py = 18;
                            mx = 10; my = 10;
                            vx = 5; vy = 16;
                            chave_pegou = 0;
                            botao1_ativado = 0;
                            botao2_ativado = 0;
                            npc_visivel = 1;
                            espinho_px = -1; espinho_py = -1;
                            getch();
                            continue;
                        }
                        
                        // Verifica portas
                        if((fase == 1 && novo_px == 9 && novo_py == 7 && chave_pegou) ||
                           (fase == 2 && novo_px == 9 && novo_py == 7 && chave_pegou) ||
                           (fase == 3 && novo_px == 6 && novo_py == 0 && botao2_ativado)) {
                            px = novo_px;
                            py = novo_py;
                        }
                        else if(celula != '*') {
                            // Verifica espinhos fixos
                            if(celula == '#') {
                                printf("\nVoce pisou em um espinho! Fase reiniciada.\n");
                                tentativas++;
                                
                                if(tentativas >= 3) {
                                    printf("\nVoce perdeu! Voltando ao menu principal.\n");
                                    getch();
                                    break;
                                }
                                
                                if(fase == 1) { 
                                    px = 1; py = 1; 
                                    chave_pegou = 0;
                                    botao1_ativado = 0;
                                } 
                                else if(fase == 2) { 
                                    px = 1; py = 8; 
                                    mx = 5; my = 5;
                                    chave_pegou = 0;
                                    botao1_ativado = 0;
                                }
                                else { 
                                    px = 2; py = 18; 
                                    mx = 10; my = 10;
                                    vx = 5; vy = 16;
                                    chave_pegou = 0;
                                    botao1_ativado = 0;
                                    botao2_ativado = 0;
                                    npc_visivel = 1;
                                    espinho_px = -1; espinho_py = -1;
                                }
                                getch();
                            } 
                            // Verifica porta trancada
                            else if((celula == 'D' || 
                                    (fase == 1 && novo_px == 9 && novo_py == 7) ||
                                    (fase == 2 && novo_px == 9 && novo_py == 7) ||
                                    (fase == 3 && novo_px == 6 && novo_py == 0)) && 
                                    !((fase == 1 && chave_pegou) || 
                                      (fase == 2 && chave_pegou) || 
                                      (fase == 3 && botao2_ativado))) {
                                printf("\nPorta trancada! Encontre a chave ou ative o botao correspondente.\n");
                                getch();
                            }
                            else {
                                px = novo_px;
                                py = novo_py;
                            }
                        }
                    }
                }
            }
        }
    }
    
    printf("\nObrigado por jogar!\n");
    return 0;
}