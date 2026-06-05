#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KALORI_PER_ORANG 2000
#define TABLE_SIZE 101

/* === STRUCT DATA === */

typedef struct {
    char nama[30];
    int kalori;
} BahanPangan;

typedef struct Keluarga {
    char nik[20];
    char nama[50];
    int anggota;
    int totalKalori;
    struct Keluarga *next;
} Keluarga;

typedef struct HashNode {
    char nik[20];
    Keluarga *data;
    struct HashNode *next;
} HashNode;

/* === VARIABEL GLOBAL === */

extern BahanPangan bahan[];
extern int jumlahBahan;

extern Keluarga *head;
extern HashNode *hashTable[TABLE_SIZE];

/* === PROTOTYPE FUNGSI=== */

unsigned int hashFunction(char *nik);
void insertHash(Keluarga *kel);
Keluarga *searchHash(char *nik);

void tambahKeluarga(char *nik, char *nama, int anggota);

int linearSearch(char nama[]);

void swap(Keluarga *a, Keluarga *b);
int partition(Keluarga arr[], int low, int high);
void quickSort(Keluarga arr[], int low, int high);

void rekomendasiBantuan(int targetKalori);

void tampilkanSemua();

#endif