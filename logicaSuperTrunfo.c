#include <stdio.h>
#include <string.h>

// Estrutura que guarda as informações de cada carta
struct Carta {
    char estado[3];          // Ex: "BA"
    char codigo[4];          // Ex: "A01"
    char nomeCidade[50];
    int populacao;
float pib;
    float area;
    int pontosTuristicos;
    float densidadePopulacional;
    float pibPerCapita;
};

// Função que calcula propriedades derivadas
void calcularPropriedades(struct Carta *c) {
    if (c->area > 0)
        c->densidadePopulacional = c->populacao / c->area;
    else
        c->densidadePopulacional = 0;

    if (c->populacao > 0)
        c->pibPerCapita = c->pib * 1000000000 / c->populacao; 
    else
        c->pibPerCapita = 0;
}

// Função para registrar uma carta
void registrarCarta(struct Carta *c) {
    printf("Digite o estado (ex: BA): ");
    scanf("%2s", c->estado);

    printf("Digite o código da carta (ex: A01): ");
    scanf("%3s", c->codigo);

    printf("Digite o nome da cidade: ");
    scanf(" %[^\n]", c->nomeCidade);

    printf("Digite a população: ");
    scanf("%d", &c->populacao);

    printf("Digite o PIB (em bilhões): ");
    scanf("%f", &c->pib);

    printf("Digite a área (em km²): ");
    scanf("%f", &c->area);

    printf("Digite o número de pontos turísticos: ");
    scanf("%d", &c->pontosTuristicos);

    // Calcula propriedades derivadas
    calcularPropriedades(c);
}

// Função para exibir os dados da carta
void mostrarCarta(struct Carta c) {
    printf("\n===== CARTA REGISTRADA =====\n");
    printf("Estado: %s\n", c.estado);
    printf("Código: %s\n", c.codigo);
    printf("Cidade: %s\n", c.nomeCidade);
    printf("População: %d habitantes\n", c.populacao);
    printf("PIB: %.2f bilhões\n", c.pib);
    printf("Área: %.2f km²\n", c.area);
    printf("Pontos Turísticos: %d\n", c.pontosTuristicos);
    printf("Densidade Populacional: %.2f hab/km²\n", c.densidadePopulacional);
    printf("PIB per Capita: %.2f R$/habitante\n", c.pibPerCapita);
    printf("============================\n");
}

int main() {
    struct Carta c1;

    printf("=== Cadastro de Carta de Cidade ===\n");
    registrarCarta(&c1);
    mostrarCarta(c1);

    return 0;
}
