#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar o valor e o índice original do array
typedef struct {
    int value; // Valor do elemento
    int index; // Índice original do elemento
} Element;

// Função para mesclar subarrays durante a contagem de inversões
void mergeAndCount(Element arr[], int left, int mid, int right, int* result) {
    int n1 = mid - left + 1; // Tamanho do subarray esquerdo
    int n2 = right - mid; // Tamanho do subarray direito

    // Aloca memória para os subarrays temporários
    Element* leftArr = (Element*)malloc(n1 * sizeof(Element));
    Element* rightArr = (Element*)malloc(n2 * sizeof(Element));

    // Copia os dados para os subarrays temporários
    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        rightArr[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;

    // Mescla os subarrays enquanto conta as inversões
    while (i < n1 && j < n2) {
        if (leftArr[i].value <= rightArr[j].value) { // Nenhuma inversão
            result[leftArr[i].index] += j; // Adiciona o número de elementos à direita que foram processados
            arr[k++] = leftArr[i++]; // Copia o elemento do subarray esquerdo
        } else {
            arr[k++] = rightArr[j++]; // Copia o elemento do subarray direito
        }
    }

    // Copia os elementos restantes do subarray esquerdo
    while (i < n1) {
        result[leftArr[i].index] += j; // Considera todos os elementos processados no subarray direito
        arr[k++] = leftArr[i++];
    }

    // Copia os elementos restantes do subarray direito
    while (j < n2) {
        arr[k++] = rightArr[j++];
    }

    // Libera a memória alocada para os subarrays temporários
    free(leftArr);
    free(rightArr);
}

// Função recursiva para o algoritmo de Merge Sort modificado
void mergeSortAndCount(Element arr[], int left, int right, int* result) {
    if (left < right) {
        int mid = left + (right - left) / 2; // Calcula o ponto médio
        mergeSortAndCount(arr, left, mid, result); // Ordena e conta as inversões no subarray esquerdo
        mergeSortAndCount(arr, mid + 1, right, result); // Ordena e conta as inversões no subarray direito
        mergeAndCount(arr, left, mid, right, result); // Mescla os dois subarrays e conta as inversões cruzadas
    }
}

// Função para contar as inversões
void countInversions(Element* elements, int size, int* result) {
    mergeSortAndCount(elements, 0, size - 1, result); // Chama o Merge Sort modificado
}

// Função principal para resolver o problema
int* countSmaller(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize; // Define o tamanho do array de retorno
    int* result = (int*)calloc(numsSize, sizeof(int)); // Inicializa o array de resultados com zeros
    if (numsSize == 0) { // Caso o array esteja vazio
        return result;
    }

    // Cria uma estrutura de elementos com valores e índices
    Element* elements = (Element*)malloc(numsSize * sizeof(Element));
    for (int i = 0; i < numsSize; i++) {
        elements[i].value = nums[i]; // Valor do elemento
        elements[i].index = i; // Índice original
    }

    countInversions(elements, numsSize, result); // Conta os elementos menores à direita
    free(elements); // Libera a memória alocada para os elementos

    return result; // Retorna o array de resultados
}