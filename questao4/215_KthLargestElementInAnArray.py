class Solution(object):
    def findKthLargest(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        def median_of_medians(arr, k):
            # Caso base: se houver apenas um elemento
            if len(arr) == 1:
                return arr[0]

            # Dividir em grupos de no máximo 5 elementos
            groups = [arr[i:i+5] for i in range(0, len(arr), 5)]

            # Encontrar a mediana de cada grupo
            medians = [sorted(group)[len(group) // 2] for group in groups]

            # Encontra a mediana das medianas
            if len(medians) == 1:
                pivot = medians[0]
            else:
                pivot = median_of_medians(medians, len(medians) // 2)

            # Particionar o array em torno do pivô
            low = [x for x in arr if x < pivot]
            high = [x for x in arr if x > pivot]
            equals = [x for x in arr if x == pivot]

            # Decidir qual parte explorar
            if k < len(low):
                return median_of_medians(low, k)
            elif k < len(low) + len(equals):
                return pivot
            else:
                return median_of_medians(high, k - len(low) - len(equals))

        # Ajustar para encontrar o k-ésimo maior elemento
        return median_of_medians(nums, len(nums) - k)