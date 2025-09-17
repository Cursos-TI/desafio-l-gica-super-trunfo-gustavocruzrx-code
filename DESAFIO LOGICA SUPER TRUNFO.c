#include <stdio.h>

// Definição da estrutura de uma carta
typedef struct {
    char nome[30];
    int forca;
    int velocidade;
    int inteligencia;
    int defesa;
} Carta;

int main() {
    // Duas cartas de exemplo
    Carta carta1 = {"Dragão", 90, 70, 60, 80};
    Carta carta2 = {"Fênix", 85, 95, 75, 70};

    int modo;

    printf("=== SUPER TRUNFO ===\n");
    printf("Escolha o modo de jogo:\n");
    printf("1 - Desafio 1 (comparação simples)\n");
    printf("2 - Desafio 2 (múltiplos atributos + menu)\n");
    printf("3 - Desafio 3 (dois atributos + ternário)\n");
    printf("Opção: ");
    scanf("%d", &modo);

    int escolha, valor1 = 0, valor2 = 0;

    switch (modo) {
        case 1: // DESAFIO 1
            printf("\n--- Desafio 1 ---\n");
            printf("Escolha o atributo:\n");
            printf("1 - Força\n");
            printf("2 - Velocidade\n");
            printf("3 - Inteligência\n");
            printf("4 - Defesa\n");
            scanf("%d", &escolha);

            if (escolha == 1) {
                valor1 = carta1.forca;
                valor2 = carta2.forca;
            } else if (escolha == 2) {
                valor1 = carta1.velocidade;
                valor2 = carta2.velocidade;
            } else if (escolha == 3) {
                valor1 = carta1.inteligencia;
                valor2 = carta2.inteligencia;
            } else {
                valor1 = carta1.defesa;
                valor2 = carta2.defesa;
            }

            if (valor1 > valor2) {
                printf("Carta 1 (%s) venceu!\n", carta1.nome);
            } else if (valor2 > valor1) {
                printf("Carta 2 (%s) venceu!\n", carta2.nome);
            } else {
                printf("Empate!\n");
            }
            break;

        case 2: // DESAFIO 2
            printf("\n--- Desafio 2 ---\n");
            printf("Escolha a comparação:\n");
            printf("1 - Força\n");
            printf("2 - Velocidade\n");
            printf("3 - Inteligência\n");
            printf("4 - Defesa\n");
            printf("5 - Força e Velocidade\n");
            scanf("%d", &escolha);

            switch (escolha) {
                case 1: valor1 = carta1.forca; valor2 = carta2.forca; break;
                case 2: valor1 = carta1.velocidade; valor2 = carta2.velocidade; break;
                case 3: valor1 = carta1.inteligencia; valor2 = carta2.inteligencia; break;
                case 4: valor1 = carta1.defesa; valor2 = carta2.defesa; break;
                case 5: valor1 = carta1.forca + carta1.velocidade;
                        valor2 = carta2.forca + carta2.velocidade; break;
                default: printf("Opção inválida!\n"); return 0;
            }

            if (valor1 > valor2) {
                printf("Carta 1 (%s) venceu!\n", carta1.nome);
            } else if (valor2 > valor1) {
                printf("Carta 2 (%s) venceu!\n", carta2.nome);
            } else {
                printf("Empate!\n");
            }
            break;

        case 3: // DESAFIO 3
            printf("\n--- Desafio 3 ---\n");
            printf("Escolha a combinação:\n");
            printf("1 - Força + Defesa\n");
            printf("2 - Velocidade + Inteligência\n");
            scanf("%d", &escolha);

            if (escolha == 1) {
                valor1 = carta1.forca + carta1.defesa;
                valor2 = carta2.forca + carta2.defesa;
            } else if (escolha == 2) {
                valor1 = carta1.velocidade + carta1.inteligencia;
                valor2 = carta2.velocidade + carta2.inteligencia;
            } else {
                printf("Opção inválida!\n");
                return 0;
            }

            // Operador ternário decide o resultado
            (valor1 > valor2) ? printf("Carta 1 (%s) venceu!\n", carta1.nome) :
            (valor2 > valor1) ? printf("Carta 2 (%s) venceu!\n", carta2.nome) :
                                printf("Empate!\n");
            break;

        default:
            printf("Modo inválido!\n");
    }

    return 0;
}
