#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int valorDoNo;
    struct No *proximoNo;
} No, *Lista;

No *iniciaLista()
{
    No *noCabeca;
    noCabeca = malloc(sizeof(No));
    noCabeca->proximoNo = NULL;
    return noCabeca;
}

void inserirNumeroNaLista(Lista lista, int valorNovoElemento)
{
    No *novoElemento;
    novoElemento = malloc(sizeof(No));
    novoElemento->valorDoNo = valorNovoElemento;
    novoElemento->proximoNo = lista->proximoNo;
    lista->proximoNo = novoElemento;
}

void imprimirLista(Lista lista)
{
    if (lista->proximoNo == NULL)
    {
        printf("A lista ainda está vazia!");
        return;
    }
    printf("Imprimindo a lista:\n");
    for (No *item = lista->proximoNo; item != NULL; item = item->proximoNo)
    {
        printf("%d", item->valorDoNo);
        if (item->proximoNo != NULL)
            printf(", ");
    }
}

void buscaItem(Lista lista, int numeroBusca)
{
    if (lista->proximoNo == NULL)
    {
        printf("A lista ainda está vazia!");
        return;
    }

    for (No *item = lista->proximoNo; item != NULL; item = item->proximoNo)
    {
        if (item->valorDoNo == numeroBusca)
        {
            printf("Número encontrado!\nValor na memória: %d", &item->valorDoNo);
            return;
        }
    }

    printf("Número não encontrado.");
    return;
}

void buscaItemERemove(Lista lista, int numeroBusca)
{
    No *itemAuxiliar = lista->proximoNo;

    if (lista->proximoNo == NULL)
    {
        printf("A lista ainda está vazia!");
        return;
    }

    for (No *item = lista->proximoNo; item != NULL; item = item->proximoNo)
    {
        if (item->valorDoNo == numeroBusca)
        {
            printf("Item encontrado e removido!");
            break;
        }
        lista = itemAuxiliar;
        itemAuxiliar = itemAuxiliar->proximoNo;
    }

    if (itemAuxiliar)
    {
        lista->proximoNo = itemAuxiliar->proximoNo;
        free(itemAuxiliar);
        return;
    }

    printf("Número não encontrado.");
    return;
}

No *removeMenorItem(Lista lista)
{
    No *listaAuxiliar, *proximoItem, *anterior;
    if (!lista->proximoNo)
        return NULL;
    listaAuxiliar = anterior = lista;
    proximoItem = lista->proximoNo;
    while (proximoItem)
    {
        if (proximoItem->valorDoNo < anterior->proximoNo->valorDoNo)
            anterior = listaAuxiliar;
        listaAuxiliar = proximoItem;
        proximoItem = proximoItem->proximoNo;
    }
    proximoItem = anterior->proximoNo;
    anterior->proximoNo = proximoItem->proximoNo;
    return proximoItem;
}

void ordenarLista(Lista lista)
{
    if (lista->proximoNo == NULL)
    {
        printf("A lista ainda está vazia!");
        return;
    }
    No *listaAuxiliar = malloc(sizeof(No)), *anterior, *minimo;
    listaAuxiliar->proximoNo = lista->proximoNo;
    lista->proximoNo = NULL;
    anterior = lista;
    while (listaAuxiliar->proximoNo != NULL)
    {
        minimo = removeMenorItem(listaAuxiliar);
        anterior->proximoNo = minimo;
        anterior = minimo;
        anterior->proximoNo = NULL;
    }
    free(listaAuxiliar);
    printf("Lista ordenada!\n\n");
}

void inserirItemEmListaOrdenada(Lista lista, int novoItem)
{
    if (lista->proximoNo == NULL)
    {
        printf("A lista ainda está vazia!");
        return;
    }

    No *noAnterior = lista;

    for (No *item = lista->proximoNo; item != NULL; item = item->proximoNo)
    {
        if (novoItem < item->valorDoNo)
        {
            inserirNumeroNaLista(noAnterior, novoItem);
            return;
        }
        noAnterior = item;
    }

    inserirNumeroNaLista(noAnterior, novoItem);
}

void escolha1(Lista lista)
{
    int numero;
    printf("Digite um número: ");
    scanf("%d", &numero);
    inserirNumeroNaLista(lista, numero);
    printf("Número inserido!\n\n");
}

void escolha2(Lista lista)
{
    int numero;
    printf("Digite um número: ");
    scanf("%d", &numero);
    buscaItem(lista, numero);
    printf("\n\n");
}

void escolha3(Lista lista)
{
    int numero;
    printf("Digite um número: ");
    scanf("%d", &numero);
    buscaItemERemove(lista, numero);
    printf("\n\n");
}

void escolha4(Lista lista)
{
    imprimirLista(lista);
    printf("\n\n");
}

void escolha5(Lista lista)
{
    ordenarLista(lista);
    printf("\n\n");
}

void escolha6(Lista lista)
{
    int numero;
    printf("Digite um número: ");
    scanf("%d", &numero);
    inserirItemEmListaOrdenada(lista, numero);
    printf("Número inserido!\n\n");
}

int main(void)
{
    Lista listaDeInteiros = iniciaLista();
    int escolha;

    do
    {
        printf("\n-MENU-\n1 - Inserir um elemento na lista\n2 - Buscar endereço "
               "pelo elemento\n3 - Apagar um elemento\n4 - Imprimir lista\n5 - "
               "Ordenar lista\n6 - Inserir um elemento em uma lista ordenada, sem "
               "alterar a ordenação\n7 - Sair\n");
        printf("Digite sua escolha: ");
        scanf("%d", &escolha);
        printf("\n");

        switch (escolha)
        {
        case 1:
            escolha1(listaDeInteiros);
            break;
        case 2:
            escolha2(listaDeInteiros);
            break;
        case 3:
            escolha3(listaDeInteiros);
            break;
        case 4:
            escolha4(listaDeInteiros);
            break;
        case 5:
            escolha5(listaDeInteiros);
            break;
        case 6:
            escolha6(listaDeInteiros);
            break;
        case 7:
            printf("Encerrando programa...");
            break;
        default:
            printf("Opção inválida.\n\n");
            break;
        }
    } while (escolha != 7);
    return 0;
}