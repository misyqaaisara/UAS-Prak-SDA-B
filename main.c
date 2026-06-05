#include "header.h"

int main(){
    int n;
    printf("Masukkan jumlah keluarga: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        char nik[20], nama[50];
        int anggota;
        printf("Masukkan Data Keluarga %d : \n",i + 1);
        printf("NIK : ");
        scanf("%s", nik);
        printf("Nama Kepala Keluarga : ");
        scanf(" %[^\n]",nama);
        do {
            printf("Jumlah Anggota Keluarga : ");
            scanf("%d",&anggota);
            if (anggota <= 0){
                printf("Data Tidak Valid\n");
            }
        }while(anggota <= 0);
        tambahKeluarga(nik,nama,anggota);
    }
}


