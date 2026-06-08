#include "header.h"

/* =========================
   DATA BAHAN PANGAN
   ========================= */

BahanPangan bahan[] = {
    {"Beras", 3600},
    {"Telur", 700},
    {"Minyak", 900},
    {"Susu", 600},
    {"Mie Instan", 400}
};

int jumlahBahan = sizeof(bahan) / sizeof(bahan[0]);

Keluarga *head = NULL;
HashNode *hashTable[TABLE_SIZE] = {NULL};

/* =========================
   HASH TABLE
   ========================= */

unsigned int hashFunction(char *nik) {
    unsigned int hash = 0;

    while (*nik) {
        hash = hash * 31 + *nik;
        nik++;
    }

    return hash % TABLE_SIZE;
}

void insertHash(Keluarga *kel) {
    unsigned int index = hashFunction(kel->nik);

    HashNode *newNode = (HashNode *)malloc(sizeof(HashNode));

    strcpy(newNode->nik, kel->nik);
    newNode->data = kel;
    newNode->next = hashTable[index];

    hashTable[index] = newNode;
}

Keluarga *searchHash(char *nik) {
    unsigned int index = hashFunction(nik);

    HashNode *temp = hashTable[index];

    while (temp != NULL) {
        if (strcmp(temp->nik, nik) == 0)
            return temp->data;

        temp = temp->next;
    }

    return NULL;
}

/* =========================
   LINKED LIST
   ========================= */

void tambahKeluarga(char *nik, char *nama, int anggota) {

    Keluarga *baru = (Keluarga *)malloc(sizeof(Keluarga));

    strcpy(baru->nik, nik);
    strcpy(baru->nama, nama);

    baru->anggota = anggota;
    baru->totalKalori = anggota * KALORI_PER_ORANG;

    baru->next = head;
    head = baru;

    insertHash(baru);
}

/* =========================
   LINEAR SEARCH
   ========================= */

int linearSearch(char nama[]) {

    for (int i = 0; i < jumlahBahan; i++) {
        if (strcmp(bahan[i].nama, nama) == 0)
            return i;
    }

    return -1;
}

/* =========================
   QUICK SORT
   ========================= */

void swap(Keluarga *a, Keluarga *b) {
    Keluarga temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Keluarga arr[], int low, int high) {

    int pivot = arr[high].totalKalori;
    int i = low - 1;

    for (int j = low; j < high; j++) {

        if (arr[j].totalKalori > pivot) {

            i++;

            Keluarga temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    Keluarga temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quickSort(Keluarga arr[], int low, int high) {

    if (low < high) {

        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/* =========================
   GREEDY
   ========================= */

void rekomendasiBantuan(int targetKalori) {

    printf("\nRekomendasi Bantuan:\n");

    int sisa = targetKalori;

    while (sisa > 0) {

        int terbaik = -1;

        for (int i = 0; i < jumlahBahan; i++) {

            if (bahan[i].kalori <= sisa) {

                if (terbaik == -1 ||
                    bahan[i].kalori > bahan[terbaik].kalori) {

                    terbaik = i;
                }
            }
        }

        if (terbaik == -1)
            break;

        printf("- %s (%d kkal)\n",
               bahan[terbaik].nama,
               bahan[terbaik].kalori);

        sisa -= bahan[terbaik].kalori;
    }

    printf("Sisa kebutuhan: %d kkal\n", sisa);
}

/* =========================
   DISPLAY
   ========================= */

void tampilkanSemua() {

    int count = 0;
    Keluarga *temp = head;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    if (count == 0)
        return;

    Keluarga arr[count];

    temp = head;

    for (int i = 0; i < count; i++) {
        arr[i] = *temp;
        temp = temp->next;
    }

    quickSort(arr, 0, count - 1);

    printf("\n===== PRIORITAS BANTUAN =====\n");

    for (int i = 0; i < count; i++) {

        printf("\nNIK            : %s\n", arr[i].nik);
        printf("Nama           : %s\n", arr[i].nama);
        printf("Anggota        : %d\n", arr[i].anggota);
        printf("Total Kalori   : %d kkal\n", arr[i].totalKalori);

        rekomendasiBantuan(arr[i].totalKalori);
    }
}
