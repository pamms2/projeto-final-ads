#include <stdio.h>
#include <stdlib.h>

//manual de instruções 
void manual(char man) {
    if(man == 's' || man == 'S') {   //caso o usuário queira ver o manual, estes printf serão apresentados
        printf("\nO jogo apresenta 48 casas com pedras (*) e 16 casas vazias (-);\n");
        printf("   As jogadas funcionam da seguinte forma:\n");
        printf("a) Só é possível fazer saltos na diagonal;\n");
        printf("b) Não é possível fazer pulos duplos;\n");
        printf("c) A casa de origem (INICIAL) precisa ter uma pedra (*);\n");
        printf("d) A casa de destino (FINAL) precisa estar vazia (-);\n");
        printf("e) Não é possível fazer saltos que passem sobre casas vazias;\n");
        printf("\n   A pontuação funciona da seguinte forma:\n");
        printf("a) Ao realizar a jogada corretamente, a peça escolhida passará por cima de casa(s) que também apresente(m) pedra(s).\n   Essa(s) pedra(s) será(ão) retirada(s), assim somando o(s) ponto(s);\n");
        printf("b) A contagem de pontos é feita pelo acúmulo de pedras retiradas em todas as jogadas feitas;\n");
        printf("\n   O jogo apresenta 4 dificuldades:\n");
        printf("a) Extremamente fácil: eliminar até 29 pedras;\n");
        printf("b) Fácil: eliminar de 30 a 39 pedras;\n");
        printf("c) Difícil: eliminar de 40 a 44 pedras;\n");
        printf("d) Extremamente difícil: eliminar de 45 a 47 pedras;\n");
        printf("\n   O jogo encerra quando:\n");
        printf("a) O jogador desiste. Para desistir do jogo é necessário digitar 0 na entrada da 'linha de origem/destino' ou\n   na entrada da 'coluna de origem/destino';\n");
        printf("b) O limite de erros é ultrapassado. Ao errar consecutivamente 5 vezes na entrada de dados da casa de destino o jogo \n   é finalizado;\n");
    }
}

//verifica se apresenta essa linha ou coluna no tabuleiro
int verifica(int col_lin) {
    if(col_lin < 1 || col_lin > 8) {
        return 0;
    } else {
        return 1;
    }
}
    
//procedimento para atualizar o valor
void pontuacao(int ponto, int *pontuacao) {
    *pontuacao = *pontuacao - ponto;
} 

//jogada
int jogada(int lin_o, int col_o, int lin_d, int col_d, char tab[8][8], int inc_l, int inc_c) {
    
    int lin_atual,  //linha atual
        col_atual,  //coluna atual
        i,          //variável de controle
        j,          //variável de controle
        ponto = 0;  //quantidade de peças retiradas por jogada
    
    lin_atual = lin_o + inc_l;
    col_atual = col_o + inc_c;
    
    while (lin_atual != lin_d || col_atual != col_d){     //percorrendo a jogada para alterar as pedras do trajeto por espaços vazios
        if(tab[lin_atual - 1][col_atual - 1] == '*') {
            tab[lin_atual - 1][col_atual - 1] = '-';
            ponto++;
        }
        lin_atual += inc_l;
        col_atual += inc_c;
    }
    
    tab[lin_o - 1][col_o - 1] = '-';     //casa inicial fica sem pedra
    tab[lin_d - 1][col_d - 1] = '*';     //casa final recebe uma pedra
    
    return ponto;
    
}

//inicializar tabuleiro
void inic_tab(char m[8][8]) {
    int i,
        j;
    for(i = 0; i < 8; i++) {
        for(j = 0; j < 8; j++) {
            m[i][j] = '*';
        }
    }
    
    for(i = 2; i <= 5; i++) {
        for(j = 2; j <= 5; j++) {
            m[i][j] = '-';
        }
    }
}

//apresentar o tabuleiro
void apr_tab(char m[8][8]) {
    int i,
        j;
    printf("  ");
    for(i = 0; i < 8; i++) {
        printf("%d ", i + 1);
    }
    printf("\n");
    for(i = 0 ; i< 8; i++) {
        printf("%d ", i + 1);
        for(j = 0; j < 8; j++) {
            printf("%c ", m[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    char tab[8][8],                     //tabuleiro (representação)
         man,                           //resposta se quer ver o manual
         resp;                          //resposta se o jogador quer jogar novamente 
    int lin_o,                          //linha de origem
        col_o,                          //coluna de origem
        lin_d,                          //linha de destino
        col_d,                          //coluna de destino
        lin_atual,                      //linha atual
        col_atual,                      //coluna atual
        i,                              //variáveL de controle
        j,                              //variáveL de controle
        ponto,                          //quantidade de peças retiradas por jogada
        sobrar = 48,                    //quantidade de peças restantes no tabuleiro
        erro = 0,                       //quantidade de erros para assim finalizar o jogo
        inc_l,                          //incremento da linha (para saber a direção que terá que percorrer)
        inc_c,                          //incremento da coluna (para saber a direção que terá que percorrer)
        vazio,                          //para ver se tem casa vazia no meio do trajeto
        qtdd;                           //quantidade de jogadas em uma partida
   
    do {
        qtdd = 0;                       //reiniciando a quantidade de jogadas ao reiniciar o jogo
        sobrar = 48;                    //reiniciando a quantidade de peças que sobraram ao reiniciar o jogo
        
        printf("\nJOGO DA ELIMINAÇÃO DE PEDRAS\n");
        printf("\nO objetivo do jogo é eliminar o máximo de peças possível!\n");
        do {
            printf("Deseja ver o manual? (S/N)\n");
            scanf(" %c", &man);
            if(man != 's' && man != 'S' && man != 'n' && man != 'N') {
                printf("\nDigite uma resposta válida\n\n");
            }
        } while(man != 's' && man != 'S' && man != 'n' && man != 'N');
        
        manual(man);
        printf("\n"); 
        inic_tab(tab);  
        
        do {
            //apresentar o tabuleiro
            apr_tab(tab);
            printf("\n");
            
            erro = 0;       //reiniciando o contador de erros
            
            do {
                do {
                    printf("\nDigite a linha de origem: ");
                    scanf("%d", &lin_o);
                    if(lin_o == 0) {                            //caso digite 0 sairá deste "do while" que pede a linha de origem
                        break;
                    }
                    if(!verifica(lin_o)) {                      //crítica de dados, é necessário colocar uma linha presente no tabuleiro
                        printf("\nDigite uma linha válida!\n");    
                    }
                } while(!verifica(lin_o));                      //enquanto não acertar a linha não vai sair desse loop
                
                if(lin_o == 0) {                                //saindo do primeiro "do while" ele saíra desse que contém a escolha da primeira casa
                    break;
                }
                
                do {
                    printf("\nDigite a coluna de origem: ");
                    scanf("%d", &col_o);
                    if(col_o == 0) {                           //caso digite 0 sairá deste "do while" que pede a coluna de origem   
                        break;
                    } 
                    if(!verifica(col_o)) {                     //crítica de dados, é necessário colocar uma coluna presente no tabuleiro
                        printf("\nDigite uma coluna válida!\n");  
                    }
                } while(!verifica(col_o));                     //enquanto não acertar a coluna não vai sair desse loop
                
                if(col_o == 0) {                               //saindo do primeiro "do while" ele saíra desse que contém a escolha da primeira casa
                }
                
                if(tab[lin_o - 1][col_o - 1] == '-') {        
                    printf("\nDigite uma casa que apresente pedra!\n");
                }
                
            } while(tab[lin_o - 1][col_o - 1] == '-');        //esse "do" repetirá enquanto a pessoa não escolher uma casa válida, ou seja, que apresente uma pedra
            
            if(col_o == 0 || lin_o == 0) {                    //caso a linha de origem ou a coluna de origem tenham sido tidas como 0, o "do" que prossegue o jogo acaba
                break; 
            }
            
            do {
                do {
                    printf("\nDigite a linha de destino: ");
                    scanf("%d", &lin_d);                
                    if(lin_d == 0) {                         //caso digite 0 sairá deste "do while" que pede a linha de destino
                        break;
                    }
                    if(!verifica(lin_d)) {                   //crítica de dados, é necessário colocar uma linha presente no tabuleiro  
                        printf("\nDigite uma linha válida\n");
                    }
                } while(!verifica(lin_d));                   //enquanto não acertar a linha não vai sair desse loop
                
                if(lin_d == 0) {                             //saindo do primeiro "do while" ele saíra desse que contém a escolha da casa de destino
                    break;
                }
                
                do {
                    printf("\nDigite a coluna de destino: ");
                    scanf("%d", &col_d);
                    if(col_d == 0) {                        //caso digite 0 sairá deste "do while" que pede a coluna de destino
                        break;
                    }
                    if(!verifica(col_d)) {                 //crítica de dados, é necessário colocar uma coluna presente no tabuleiro  
                        printf("\nDigite uma coluna válida!\n");
                    }
                } while(!verifica(col_d));                 //enquanto não acertar a coluna não vai sair desse loop
                
                if(col_d == 0) {                           //saindo do primeiro "do while" ele saíra desse que contém a escolha da casa de destino
                    break;
                }
                
                //todo erro de linha e coluna de destino são contados aqui, tendo um limite de 5 erros consecutivos
                if(tab[lin_d - 1][col_d - 1] == '*') {                          //ERRO 1 - apresentar pedra na casa de destino
                    printf("\nDigite uma casa que não apresente pedra!\n");
                    erro++;
                    if(erro == 4) {
                        printf("\nO próximo erro resultará no fim do jogo!\n");
                    }
                } else {
                    if (abs(lin_o - lin_d) != abs(col_o - col_d)) {             //ERRO 2 - as casas não estarem na diagonal             
                        printf("\nOs pontos não estão na diagonal\n");
                        erro++;
                        if(erro == 4) {
                            printf("\nO próximo erro resultará no fim do jogo!\n");
                        }
                    } else {
                        if(abs(lin_o - lin_d) == abs(col_o - col_d)) {          //ERRO 3 - apresentar casas vazias no meio do trajeto da pedra
                            if(lin_o < lin_d) {
                                inc_l = 1;
                            } else {
                                inc_l = -1;
                            }
                            if(col_o < col_d) {
                                inc_c = 1;
                            } else {
                                inc_c = -1;
                            }
                            
                            lin_atual = lin_o + inc_l;
                            col_atual = col_o + inc_c;
                            vazio = 0;
                            
                            while((lin_atual != lin_d || col_atual != col_d) && vazio == 0) {
                                
                                if(tab[lin_atual - 1][col_atual - 1] == '-') {
                                    vazio++;   
                                }
                                
                                lin_atual += inc_l;
                                col_atual += inc_c;
                                
                            }
                            
                            if(vazio != 0) {
                                printf("\nHá casa(s) vazia(s) no trajeto da pedra!\n");
                                erro++;
                                if(erro == 4) {
                                    printf("\nO próximo erro resultará no fim do jogo!\n");
                                }
                            }
                        }
                    } 
                } 
                
                //caso o jogador atinja 4 erros ele será alertado que ao errar mais uma vez o jogo será finalizado
                
                if(erro == 5) {    //atingindo 5 erros o "do while" que pede a casa de destino encerra
                    break;
                }
                
            } while(tab[lin_d - 1][col_d - 1] == '*' || abs(lin_o - lin_d) != abs(col_o - col_d) || vazio != 0);   //enquanto os erros persistirem o loop continuará
            
            if(col_d == 0 || lin_d == 0) {        //caso a linha de destino ou a linha de origem sejam 0, o loop que prossegue o jogo finaliza
                break;
            }
            if(erro == 5) {                       //se 5 erros forem cometidos, o loop que prossegue o jogo é finalizado
                break;
            }
            
            if(col_d != 0 && lin_d != 0 && col_o != 0 && lin_o != 0) {
                //processar a jogada
                ponto = jogada(lin_o, col_o, lin_d, col_d, tab, inc_l, inc_c);
                pontuacao(ponto, &sobrar);
                qtdd++;
                
                //mostrar estatísticas
                printf("\nSalto de (%d, %d) para (%d, %d) com %d pedra(s) eliminada(s) neste salto;\n", lin_o, col_o, lin_d, col_d, ponto);
                printf("%d pedras eliminadas; restam %d pedras no tabuleiro.\n\n", ponto, sobrar);
            }
        } while(col_d != 0 && lin_d != 0 && col_o != 0 && lin_o != 0);
        
        //final do jogo
        printf("\nJogo encerrado!\n");
        printf("Você eliminou %d peça(s), em %d jogadas, ", 48 - sobrar, qtdd);
        if(sobrar == 48) {
            printf("não completando nenhum modo!");
        } else {
            if(48 - sobrar <= 29) {
            printf("completando o modo 'Extremamente Fácil'!"); 
            } else {
                if(48 - sobrar <= 39 && 48 - sobrar > 29) {
                    printf("completando o modo 'Fácil'!");
                } else {
                    if(48 - sobrar <= 44 && 48 - sobrar > 39) {
                        printf("completando o modo 'Difícil'!");
                    } else {
                        if(48 - sobrar <= 47 && 48 - sobrar > 44) {
                            printf("completando o modo 'Extremamente Difícil'!");
                        }
                    }
                }
            }
        }
        
        //verificação se quer jogar novamente
        do {   
            printf("\n\nDeseja jogar novamente? (S/N)\n");
            scanf(" %c", &resp);
            if(resp != 'n' && resp != 'N' && resp != 's' && resp != 'S') {
                printf("\nDigite uma resposta válida!\n\n");
            }
        } while(resp != 'n' && resp != 'N' && resp != 's' && resp != 'S');
        
    } while(resp == 's' || resp == 'S');

    return 0;
}