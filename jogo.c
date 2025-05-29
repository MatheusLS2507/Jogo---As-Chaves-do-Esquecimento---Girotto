#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

int main() {
    // Variáveis do jogo
    int opcao;
    int px, py; // Posição do jogador
    int chave_pegou, botao1_ativado, botao2_ativado, botao3_ativado, botao4_ativado;
    int npc_visivel = 1; // Controla se o NPC especial está visível
     int npc2_visivel = 1;
    int espinho_px = 4, espinho_py = 5; // Posição do espinho criado pelo botão 1
    int npc2_x = 6, npc2_y = 6; // Posição do NPC na última fase
    int chave_ultima_fase_visivel = 0; // Controle da chave na última fase
    char tecla;
    int fase = 1; // 1 = Vila, 2 = Fase1, 3 = Fase2, 4 = Fase3 (última fase)
    int mx, my; // Posição do monstro X (fase 1 e 2)
    int vx, vy; // Posição do monstro V (apenas fase 2)
    int i, j;
   
    // Adicionando variáveis para os monstros da última fase
    int monstrov_x = 1, monstrov_y = 1; // Monstro V na fase 4
    int monstrox1_x = 5, monstrox1_y = 29; // Primeiro monstro X na fase 4
    int monstrox2_x = 10, monstrox2_y = 10; // Segundo monstro X na fase 4
    int monstrox3_x = 12, monstrox3_y = 22; // Terceiro monstro X na fase 4
    int parede_removida = 0; // Controla se a parede foi removida na última fase
    
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
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','*','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','*','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','>','*','>','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','*','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','*','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','*','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','*','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','*','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','*','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','*','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','*','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','*','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','*','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','*','.','.','.','.','.','*'},
        {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','D','*','*'}
    };

    char fase3[40][40] = {
        {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#','#','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#','#','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','O','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','#','#','#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','#','#','#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#','#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#','#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','O','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
        {'*','.','.','.','.','.','.','.','*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','D'},
        {'*','.','.','.','.','.','.','.','*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','.','.','.','.','.','.','.','*','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','*'},
        {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'}
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
            botao3_ativado = 0;
            botao4_ativado = 0;
            npc_visivel = 1;
           espinho_px = -1; espinho_py = -1;
            
            parede_removida = 0;
            
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
                            else if(i == 18 && j == 2 && botao2_ativado) printf("@ ");
                            else if(i == 6 && j == 0 && botao2_ativado ) printf("= " );
                            else if(i == 19 && j == 17  ) printf(chave_pegou ? "= " : "D ");
                            else if(i == 1 && j == 1 && !botao1_ativado) printf("O ");
                            else if(i == 1 && j == 4 && !botao2_ativado) printf("O ");
                            else if(espinho_px != 4 && i == espinho_px && j == espinho_py && botao1_ativado) printf("# ");
                            else if(i == 7 && j == 12) printf("> ");
                            else if(i == 7 && j == 14) printf("> ");
                           
                            else if(i == 5 && j == 1 && npc_visivel && botao2_ativado) 
                                printf("P ");
                            else printf("%c ", fase2[i][j]);
                        }
                        printf("\n");
                    }
                }
                else if(fase == 4) {
                    // Desenha a última fase
                    for(i = 0; i < 40; i++) {
                        for(j = 0; j < 40; j++) {
                            if(i == px && j == py) printf("& ");
                            else if(i == monstrov_x && j == monstrov_y) printf("V ");
                            else if(i == monstrox1_x && j == monstrox1_y) printf("X ");
                            else if(i == monstrox2_x && j == monstrox2_y) printf("X ");
                            else if(i == monstrox3_x && j == monstrox3_y) printf("X ");
                            else if(i == 34 && j == 39) printf(chave_pegou ? "= " : "D ");
                            
                            else if(i == 25 && j == 2 && !botao4_ativado) printf("O ");
                            else if(i == 18 && j == 3 && chave_ultima_fase_visivel && !chave_pegou) printf("@ ");
                           
                            
                            // Teleportes
                            else if((i == 34 && j == 5) || (i == 34 && j == 13))
                                printf("> ");
                            else 
                                printf("%c ", fase3[i][j]);
                        }
                        printf("\n");
                    }
                }
                
                printf("\nChave: %s\n", chave_pegou ? "SIM" : "NAO");
                printf("Use WASD para mover, I para interagir\n");
                
                // Verificação de colisão com monstros - CORRIGIDO
                if((fase == 2 && px == mx && py == my) || 
                   (fase == 3 && ((px == mx && py == my) || (px == vx && py == vy))) ||
                   (fase == 4 && ((px == monstrov_x && py == monstrov_y) || 
                                  (px == monstrox1_x && py == monstrox1_y) || 
                                  (px == monstrox2_x && py == monstrox2_y) || 
                                  (px == monstrox3_x && py == monstrox3_y)))) {
                    printf("\nVoce foi pego pelo monstro! Fase reiniciada.\n");
                    getch();
                    
                    if(fase == 2) {
                        px = 1; py = 8;
                        mx = 5; my = 5;
                        chave_pegou = 0;
                        botao1_ativado = 0;
                    } 
                    else if(fase == 3) {
                        px = 2; py = 18;
                        mx = 10; my = 10;
                        vx = 5; vy = 16;
                        chave_pegou = 0;
                        botao1_ativado = 0;
                        botao2_ativado = 0;
                        npc_visivel = 1;
                        espinho_px = -1; espinho_py = -1;
                    }
                    else if(fase == 4) {
                        px = 2; py = 17;
                        chave_pegou = 0;
                        botao3_ativado = 0;
                        botao4_ativado = 0;
                        chave_ultima_fase_visivel = 0;
                        // Reinicia posições dos monstros
                        monstrov_x = 1; monstrov_y = 1;
                        monstrox1_x = 5; monstrox1_y = 29;
                        monstrox2_x = 10; monstrox2_y = 10;
                        monstrox3_x = 12; monstrox3_y = 22;
                    }
                    continue;
                }
                
                // Código para passagem entre fases
                if(fase == 1 && px == 9 && py == 7 && chave_pegou) {
                    printf("\nPassando para a proxima fase...\n");
                    getch();
                    
                    // Inicializa fase1
                    fase = 2;
                    px = 1; py = 8;
                    chave_pegou = 0;
                    botao1_ativado = 0;
                  
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
                    
                    mx = 10; my = 10;
                    vx = 5; vy = 16;
                    continue;
                }
                else if(fase == 3 && px == 19 && py == 17 && chave_pegou) {
                    printf("\nPassando para a fase 3 (ultima fase)...\n");
                    getch();
                    
                    // Inicializa a última fase (fase3)
                    fase = 4;
                    px = 2; py = 17; // Posição inicial do jogador
                    chave_pegou = 0;
                    botao3_ativado = 0;
                    botao4_ativado = 0;
                    
                    chave_ultima_fase_visivel = 0;
                    
                    // Inicializa posições dos monstros da fase 4
                    monstrov_x = 1; monstrov_y = 1;
                    monstrox1_x = 5; monstrox1_y = 29;
                    monstrox2_x = 10; monstrox2_y = 10;
                    monstrox3_x = 12; monstrox3_y = 22;
                   
                    continue;
                }
                else if(fase == 4 && px == 34 && py == 39 && chave_pegou) {
                    printf("\nParabens! Voce completou o jogo!\n");
                    getch();
                    break;
                }
                
                // Movimento dos monstros
                if(fase >= 2 && fase <= 3) {
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
                    if(px >= 10 && px <= 29 && py >= 10 && py <= 29) {
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
                
                // Movimento dos monstros da fase 4
                if(fase == 4) {
                    
                    // Movimento do monstro V (persegue jogador)
                    if(rand() % 3 == 0) { // Move apenas em 1/3 das vezes para não ser muito agressivo
                        int novo_v_x = monstrov_x, novo_v_y = monstrov_y;
                        
                        if(px < monstrov_x && fase3[monstrov_x-1][monstrov_y] != '*') novo_v_x--;
                        else if(px > monstrov_x && fase3[monstrov_x+1][monstrov_y] != '*') novo_v_x++;
                        else if(py < monstrov_y && fase3[monstrov_x][monstrov_y-1] != '*') novo_v_y--;
                        else if(py > monstrov_y && fase3[monstrov_x][monstrov_y+1] != '*') novo_v_y++;
                        
                        if(novo_v_x >= 0 && novo_v_x < 40 && novo_v_y >= 0 && novo_v_y < 40) {
                            if(fase3[novo_v_x][novo_v_y] != '*' && 
                               !(novo_v_x == px && novo_v_y == py)) {
                                monstrov_x = novo_v_x;
                                monstrov_y = novo_v_y;
                            }
                        }
                    }
                    
                    // Movimento dos monstros X (movimento aleatório)
                    // Primeiro monstro X
                    if(rand() % 2 == 0) {
                        int dir = rand() % 4;
                        int novo_x1 = monstrox1_x, novo_y1 = monstrox1_y;
                        
                        if(dir == 0) novo_x1--;
                        else if(dir == 1) novo_x1++;
                        else if(dir == 2) novo_y1--;
                        else if(dir == 3) novo_y1++;
                        
                        if(novo_x1 >= 0 && novo_x1 < 40 && novo_y1 >= 0 && novo_y1 < 40) {
                            if(fase3[novo_x1][novo_y1] != '*' && 
                               !(novo_x1 == px && novo_y1 == py)) {
                                monstrox1_x = novo_x1;
                                monstrox1_y = novo_y1;
                            }
                        }
                    }
                    
                    // Segundo monstro X
                    if(rand() % 2 == 0) {
                        int dir = rand() % 4;
                        int novo_x2 = monstrox2_x, novo_y2 = monstrox2_y;
                        
                        if(dir == 0) novo_x2--;
                        else if(dir == 1) novo_x2++;
                        else if(dir == 2) novo_y2--;
                        else if(dir == 3) novo_y2++;
                        
                        if(novo_x2 >= 0 && novo_x2 < 40 && novo_y2 >= 0 && novo_y2 < 40) {
                            if(fase3[novo_x2][novo_y2] != '*' && 
                               !(novo_x2 == px && novo_y2 == py)) {
                                monstrox2_x = novo_x2;
                                monstrox2_y = novo_y2;
                            }
                        }
                    }
                    
                    // Terceiro monstro X
                    if(rand() % 2 == 0) {
                        int dir = rand() % 4;
                        int novo_x3 = monstrox3_x, novo_y3 = monstrox3_y;
                        
                        if(dir == 0) novo_x3--;
                        else if(dir == 1) novo_x3++;
                        else if(dir == 2) novo_y3--;
                        else if(dir == 3) novo_y3++;
                        
                        if(novo_x3 >= 0 && novo_x3 < 40 && novo_y3 >= 0 && novo_y3 < 40) {
                            if(fase3[novo_x3][novo_y3] != '*' && 
                               !(novo_x3 == px && novo_y3 == py)) {
                                monstrox3_x = novo_x3;
                                monstrox3_y = novo_y3;
                            }
                        }
                    }
                    
                    // Movimento do NPC na última fase
                    if(parede_removida && npc2_visivel) {
                        // Se a porta está aberta, o NPC se move para a direita (até a coluna 20)
                        if(chave_pegou && npc2_y < 20) {
                            npc2_y++;
                        }
                        // Se a porta está fechada, o NPC não se move
                        else if(!chave_pegou) {
                            // Não faz nada - NPC fica parado
                        }
                        
                        // Se o NPC chegou na coluna 20, ele desaparece
                        if(npc2_y >= 20) {
                            npc2_visivel = 0;
                        }
                    }
                }                
                
                tecla = getch();
                
                // Interação com I
                if(tecla == 'i' || tecla == 'I') {
                    // NPC normal
                    if((fase == 1 && px == 1 && py == 3) || 
                       (fase == 2 && px == 1 && py == 8) ||
                       (fase == 3 && px == 2 && py == 18)) {
                        system("cls");
                        if(fase == 1) printf("NPC: Ative o botao (O) para revelar a chave (@)!\n");
                        else if(fase == 2) printf("NPC: O botao (O) cria teleportes (>)!\n");
                        else printf("NPC: O primeiro botao cria um espinho atras de voce, o segundo abre a porta (D) e libera a chave!\n");
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
                        if(py > 0 && fase2[px][py-1] != '*') {
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
                        else if(px > 0 && fase2[px-1][py] != '*') {
                            espinho_px = px-1;
                            espinho_py = py;
                        }
                        
                        printf("\nBotao ativado! Um espinho apareceu atras de voce!\n");
                        getch();
                    }
                    // Segundo botão na Fase2 (abre porta da esquerda e remove espinhos que cercam a chave)
                    else if(fase == 3 && px == 1 && py == 4 && !botao2_ativado) {
                        botao2_ativado = 1;
                        printf("\nBotao ativado! A chave apareceu!\n");
                        
                        // Mostra diálogo do NPC especial
                        system("cls");
                        printf("NPC: Vou parar por aqui, é muito perigoso!\n");
                        printf("Pressione ENTER para continuar...");
                        while(getch() != 13);
                        npc_visivel = 1;
                    }
                    
                    // botão na Fase3 (Última fase - surge chave)
                    else if(fase == 4 && px == 25 && py == 2 && !botao4_ativado) {
                        botao4_ativado = 1;
                        chave_ultima_fase_visivel = 1;
                        printf("\nBotao ativado! A chave apareceu!\n");
                        getch();
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
                    // Teleporte na última fase
                    else if(fase == 4 && ((px == 34 && py == 5) || (px == 34 && py == 14))) {
                        if(px == 34 && py == 5) px = 34, py = 14;
                        else px = 34, py = 5;
                        printf("\nTeleportado!\n");
                        getch();
                    }
                    // Pegar chave
                    else if((fase == 1 && px == 4 && py == 8 && botao1_ativado && !chave_pegou) ||
                            (fase == 2 && px == 8 && py == 2 && !chave_pegou) ||
                            (fase == 3 && px == 18 && py == 2 && !chave_pegou && botao2_ativado) ||
                            (fase == 4 && px == 18 && py == 3 && chave_ultima_fase_visivel && !chave_pegou)) {
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
                       (fase == 3 && novo_px >= 0 && novo_px < 20 && novo_py >= 0 && novo_py < 20) ||
                       (fase == 4 && novo_px >= 0 && novo_px < 40 && novo_py >= 0 && novo_py < 40)) {
                        
                        char celula = '.'; // Valor padrão
                        if(fase == 1) celula = vila[novo_px][novo_py];
                        else if(fase == 2) celula = fase1[novo_px][novo_py];
                        else if(fase == 3) celula = fase2[novo_px][novo_py];
                        else if(fase == 4) celula = fase3[novo_px][novo_py];
                        
                        // Verificações especiais para a última fase
                        if(fase == 4) {
                            // Verifica se o jogador vai para uma posição onde está um monstro
                            if((novo_px == monstrov_x && novo_py == monstrov_y) || 
                               (novo_px == monstrox1_x && novo_py == monstrox1_y) || 
                               (novo_px == monstrox2_x && novo_py == monstrox2_y) || 
                               (novo_px == monstrox3_x && novo_py == monstrox3_y)) {
                                printf("\nVoce foi pego pelo monstro! Fase reiniciada.\n");

                                px = 2; py = 17;
                                chave_pegou = 0;
                                botao3_ativado = 0;
                                botao4_ativado = 0;
                                
                                chave_ultima_fase_visivel = 0;
                                
                                // Reinicia posições dos monstros
                                monstrov_x = 1; monstrov_y = 1;
                                monstrox1_x = 5; monstrox1_y = 29;
                                monstrox2_x = 10; monstrox2_y = 10;
                                monstrox3_x = 12; monstrox3_y = 22;
                               
                                getch();
                                continue;
                            }
                        }
                        
                        // Verifica espinho criado pelo botão 1 na fase 3
                        if(fase == 3 && botao1_ativado && novo_px == espinho_px && novo_py == espinho_py) {
                            printf("\nVoce pisou em um espinho! Fase reiniciada.\n");
                            
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
                           (fase == 3 && novo_px == 19 && novo_py == 17 && chave_pegou) ||
                           (fase == 3 && novo_px == 6 && novo_py == 0 && botao2_ativado) ||
                           (fase == 4 && novo_px == 34 && novo_py == 39 && chave_pegou)) {
                            px = novo_px;
                            py = novo_py;
                        }
                        
                        else if(celula != '*') {
                            // Verifica espinhos fixos
                            if(celula == '#') {
                                printf("\nVoce pisou em um espinho! Fase reiniciada.\n");
                                
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
                                else if(fase == 3) { 
                                    px = 2; py = 18; 
                                    mx = 10; my = 10;
                                    vx = 5; vy = 16;
                                    chave_pegou = 0;
                                    botao1_ativado = 0;
                                    botao2_ativado = 0;
                                    npc_visivel = 1;
                                   espinho_px = -1; espinho_py = -1;
                                }
                                else if(fase == 4) {
                                    px = 2; py = 17;
                                    chave_pegou = 0;
                                    botao3_ativado = 0;
                                    botao4_ativado = 0;
                                    parede_removida = 0;
                                    chave_ultima_fase_visivel = 0;
                                    
                                    // Reinicia posições dos monstros
                                    monstrov_x = 1; monstrov_y = 1;
                                    monstrox1_x = 5; monstrox1_y = 29;
                                    monstrox2_x = 10; monstrox2_y = 10;
                                    monstrox3_x = 12; monstrox3_y = 22;
                                }
                                getch();
                            } 
                            // Verifica porta trancada
                            else if((celula == 'D' || 
                                    (fase == 1 && novo_px == 9 && novo_py == 7) ||
                                    (fase == 2 && novo_px == 9 && novo_py == 7) ||
                                    (fase == 3 && novo_px == 19 && novo_py == 17) ||
                                    (fase == 3 && novo_px == 6 && novo_py == 0) ||
                                    (fase == 4 && novo_px == 34 && novo_py == 39)) && 
                                    !((fase == 1 && chave_pegou) || 
                                      (fase == 2 && chave_pegou) || 
                                      (fase == 3 && chave_pegou) || 
                                      (fase == 3 && botao2_ativado) ||
                                      (fase == 4 && chave_pegou))) {
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
